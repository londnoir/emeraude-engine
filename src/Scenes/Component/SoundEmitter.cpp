/*
 * src/Scenes/Component/SoundEmitter.cpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2025 - Sébastien Léon Claude Christian Bémelmans "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Emeraude-Engine; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Complete project and additional information can be found at :
 * https://github.com/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#include "SoundEmitter.hpp"

/* STL inclusions. */
#include <any>
#include <memory>
#include <string>

/* Local inclusions. */
#include "Abstract.hpp"
#include "Animations/Types.hpp"
#include "Audio/Manager.hpp"
#include "Audio/SoundResource.hpp"
#include "Audio/Source.hpp"
#include "Libs/Math/CartesianFrame.hpp"
#include "Libs/Math/Cuboid.hpp"
#include "Libs/Math/Sphere.hpp"
#include "Physics/MovableTrait.hpp"
#include "Resources/ResourceTrait.hpp"
#include "Scenes/AbstractEntity.hpp"
#include "Tracer.hpp"
#include "Libs/Variant.hpp"

namespace EmEn::Scenes::Component
{
	using namespace EmEn::Libs;
	using namespace EmEn::Libs::Math;
	using namespace Animations;
	using namespace Audio;

	SoundEmitter::SoundEmitter (const std::string & name, const AbstractEntity & parentEntity, bool permanent) noexcept
		: Abstract(name, parentEntity)
	{
		this->setFlag(KeepInactiveSourceAlive, permanent);
	}

	void
	SoundEmitter::move (const CartesianFrame< float > & worldCoordinates) noexcept
	{
		if ( m_source == nullptr )
		{
			return;
		}

		this->updateSource(worldCoordinates);
	}

	void
	SoundEmitter::processLogics (const Scene & /*scene*/) noexcept
	{
		if ( m_source == nullptr )
		{
			return;
		}

		if ( !this->isFlagEnabled(KeepInactiveSourceAlive) && m_source->isStopped() )
		{
			this->releaseSource();
		}
	}

	bool
	SoundEmitter::shouldRemove () const noexcept
	{
		return false;
	}

	bool
	SoundEmitter::onNotification (const ObservableTrait * observable, int notificationCode, const std::any & /*data*/) noexcept
	{
		if ( observable->is(SoundResource::ClassUID) )
		{
			switch ( notificationCode )
			{
				case Resources::ResourceTrait::LoadFinished :
					this->playAttachedSound();
					break;

				case Resources::ResourceTrait::LoadFailed :
					this->releaseAttachedSound();
					break;

				default:
#ifdef EMERAUDE_DEBUG_OBSERVER_PATTERN
					TraceDebug{ClassId} << "Event #" << notificationCode << " from a sound resource ignored.";
#endif
					break;
			}

			return false;
		}

#ifdef DEBUG
		/* NOTE: Don't know what is it, goodbye ! */
		TraceInfo{ClassId} <<
			"Received an unhandled notification (Code:" << notificationCode << ") from observable '" << whoIs(observable->classUID()) << "' (UID:" << observable->classUID() << ")  ! "
			"Forgetting it ...";
#endif

		return false;
	}

	bool
	SoundEmitter::playAnimation (uint8_t animationID, const Variant & value, size_t cycle) noexcept
	{
		switch ( animationID )
		{
			case EmittingState :
				if ( value.asBool() )
				{
					this->resume();
				}
				else
				{
					this->pause();
				}
				return true;

			case Gain :
				this->setGain(value.asFloat());
				return true;

			default:
				return false;
		}
	}

	bool
	SoundEmitter::requestSource () noexcept
	{
		if ( m_source != nullptr )
		{
			return true;
		}

		m_source = Manager::instance()->requestSource();

		if ( m_source == nullptr )
		{
			return false;
		}

		this->updateSource(this->getWorldCoordinates());

		return true;
	}

	void
	SoundEmitter::updateSource (const CartesianFrame< float > & worldCoordinates) const noexcept
	{
		/* Copy absolute position in world space coordinates. */
		m_source->setPosition(worldCoordinates.position());

		/* Sets the direction of the source. */
		m_source->setDirection(worldCoordinates.backwardVector());

		if ( this->velocityDistortionEnabled() )
		{
			/* Copy current velocity to sound source for deforming effect. */
			// FIXME: Remove the need of a dynamic cast.
			const auto * movable = dynamic_cast< const Physics::MovableTrait * >(&this->parentEntity());

			if ( movable != nullptr )
			{
				m_source->setVelocity(movable->getWorldVelocity());
			}
		}
	}

	void
	SoundEmitter::releaseSource () noexcept
	{
		m_source->removeSound();
		m_source.reset();
	}

	void
	SoundEmitter::releaseAttachedSound () noexcept
	{
		this->disableFlag(Loop);

		m_attachedSound.reset();
	}

	void
	SoundEmitter::attachSound (const std::shared_ptr< SoundResource > & sound, float gain, bool loop) noexcept
	{
		this->setFlag(Loop, loop);

		m_attachedSound = sound;
		m_gain = gain;
	}

	void
	SoundEmitter::play (const std::shared_ptr< SoundResource > & sound, float gain, bool loop, bool replaceSound) noexcept
	{
		if ( !replaceSound && m_source != nullptr && m_source->isPlaying() )
		{
			return;
		}

		this->attachSound(sound, gain, loop);

		/* NOTE: Delay the sound play if not loaded. */
		if ( m_attachedSound->isLoaded() )
		{
			this->playAttachedSound();
		}
		else
		{
			this->observe(m_attachedSound.get());
		}
	}

	void
	SoundEmitter::replay () noexcept
	{
		/* No previous sound ... */
		if ( m_attachedSound == nullptr )
		{
			return;
		}

		/* If source is present and is playing, we rewind the sound. */
		if ( m_source != nullptr && m_source->isPlaying() )
		{
			m_source->rewind();

			return;
		}

		this->playAttachedSound();
	}

	void
	SoundEmitter::playAttachedSound () noexcept
	{
		/* NOTE : Get an available audio source. */
		if ( !this->requestSource() )
		{
#ifdef DEBUG
			Tracer::debug(ClassId, "No more audio source available !");
#endif
			return;
		}

		m_source->setGain(m_gain);
		m_source->play(m_attachedSound, this->isFlagEnabled(Loop) ? Source::PlayMode::Loop : Source::PlayMode::Once);
	}

	void
	SoundEmitter::stop () const noexcept
	{
		if ( m_source == nullptr || m_attachedSound == nullptr )
		{
			return;
		}

		m_source->stop();
	}

	void
	SoundEmitter::pause () const noexcept
	{
		if ( m_source == nullptr || m_attachedSound == nullptr )
		{
			return;
		}

		m_source->pause();
	}

	void
	SoundEmitter::resume () const noexcept
	{
		if ( m_source == nullptr || m_attachedSound == nullptr )
		{
			return;
		}

		m_source->resume();
	}

	void
	SoundEmitter::rewind () const noexcept
	{
		if ( m_source == nullptr || m_attachedSound == nullptr )
		{
			return;
		}

		m_source->rewind();
	}

	bool
	SoundEmitter::isPlaying () const noexcept
	{
		if ( m_source == nullptr || m_attachedSound == nullptr )
		{
			return false;
		}

		return m_source->isPlaying();
	}

	void
	SoundEmitter::clear () noexcept
	{
		this->stop();

		this->releaseAttachedSound();

		if ( m_source != nullptr )
		{
			this->releaseSource();
		}

		m_gain = 8.0F;
	}
}
