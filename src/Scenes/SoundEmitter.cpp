/*
 * Emeraude/Scenes/SoundEmitter.cpp
 * This file is part of Emeraude
 *
 * Copyright (C) 2012-2023 - "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Emeraude is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emeraude; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Complete project and additional information can be found at :
 * https://bitbucket.org/londnoir/emeraude
 * 
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#include "SoundEmitter.hpp"

/* Local inclusions */
#include "Tracer.hpp"
#include "Audio/Manager.hpp"
#include "AbstractEntity.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Animations;
	using namespace Audio;

	SoundEmitter::SoundEmitter (const std::string & name, const AbstractEntity & parentEntity, bool permanent) noexcept
		: AbstractComponent(name, parentEntity)
	{
		m_flags[KeepInactiveSourceAlive] = permanent;
	}

	const char *
	SoundEmitter::getComponentType () const noexcept
	{
		return "SoundEmitter";
	}

	void
	SoundEmitter::move () noexcept
	{
		if ( m_source == nullptr )
			return;

		this->updateSource();
	}

	void
	SoundEmitter::processLogics (const Scene &, size_t) noexcept
	{
		if ( !m_flags[KeepInactiveSourceAlive] && !m_source->isStopped() )
			this->releaseSource();
	}

	bool
	SoundEmitter::onNotification (const Observable * observable, int notificationCode, const std::any &) noexcept
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
					TraceDebug{ClassId} << "Event #" << notificationCode << " from a sound resource ignored.";
					break;
			}

			return false;
		}

#ifdef DEBUG
		/* NOTE: Don't know what is it, goodbye ! */
		TraceInfo{ClassId} <<
			"Received an unhandled event from observable @" << observable << " (code:" << notificationCode << ") ! "
			"Forgetting it ...";
#endif

		return false;
	}

	bool
	SoundEmitter::playAnimation (Animations::id_t id, const Variant & value) noexcept
	{
		return false;
	}

	bool
	SoundEmitter::requestSource () noexcept
	{
		if ( m_source != nullptr )
			return true;

		m_source = Manager::instance()->requestSource();

		if ( m_source == nullptr )
			return false;

		this->updateSource();

		return true;
	}

	void
	SoundEmitter::updateSource () const noexcept
	{
		const auto worldCoordinates = this->getWorldCoordinates();

		/* Copy absolute position in world space coordinates. */
		m_source->setPosition(worldCoordinates.position());

		/* Sets the direction of the source. */
		m_source->setDirection(worldCoordinates.forwardVector());

		/* Copy current velocity to sound source for deforming effect. */
		const auto movable = dynamic_cast< const Physics::MovableTrait * >(&this->parentEntity());

		if ( movable != nullptr )
			m_source->setVelocity(movable->getWorldVelocity());
	}

	void
	SoundEmitter::releaseSource () noexcept
	{
		m_source.reset();
	}

	void
	SoundEmitter::releaseAttachedSound () noexcept
	{
		m_attachedSound.reset();
		m_flags[Loop] = false;
	}

	void
	SoundEmitter::play (const std::shared_ptr< SoundResource > & sound, bool loop) noexcept
	{
		/* Register first the sound and playing parameter. */
		m_attachedSound = sound;
		m_flags[Loop] = loop;

		/* NOTE: Delay the sound play if not loaded. */
		if ( m_attachedSound->isLoaded() )
			this->playAttachedSound();
		else
			this->observe(m_attachedSound.get());
	}

	void
	SoundEmitter::replay () noexcept
	{
		/* No previous sound ... */
		if ( m_attachedSound == nullptr )
			return;

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
		/* NOTE: Get an available audio source. */
		if ( !this->requestSource() )
		{
			Tracer::warning(ClassId, "No more audio source available !");

			return;
		}

		m_source->play(m_attachedSound.get(), m_flags[Loop] ? Source::PlayMode::Loop : Source::PlayMode::Once);
	}

	void
	SoundEmitter::stop () const noexcept
	{
		if ( m_source == nullptr || m_attachedSound == nullptr )
			return;

		m_source->stop();
	}

	void
	SoundEmitter::pause () const noexcept
	{
		if ( m_source == nullptr || m_attachedSound == nullptr )
			return;

		m_source->pause();
	}

	void
	SoundEmitter::resume () const noexcept
	{
		if ( m_source == nullptr || m_attachedSound == nullptr )
			return;

		m_source->resume();
	}

	void
	SoundEmitter::rewind () const noexcept
	{
		if ( m_source == nullptr || m_attachedSound == nullptr )
			return;

		m_source->rewind();
	}

	bool
	SoundEmitter::isPlaying () const noexcept
	{
		if ( m_source == nullptr || m_attachedSound == nullptr )
			return false;

		return m_source->isPlaying();
	}

	void
	SoundEmitter::clear () noexcept
	{
		this->releaseAttachedSound();

		this->releaseSource();
	}
}
