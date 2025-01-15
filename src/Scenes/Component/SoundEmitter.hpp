/*
 * src/Scenes/Component/SoundEmitter.hpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2024 - "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emeraude-Engine; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Complete project and additional information can be found at :
 * https://bitbucket.org/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#pragma once

/* STL inclusions. */
#include <any>
#include <cstddef>
#include <memory>
#include <string>

/* Local inclusions for inheritances. */
#include "Abstract.hpp"
#include "Libraries/ObserverTrait.hpp"

/* Local inclusions for usages. */
#include "Animations/Types.hpp"
#include "Audio/SoundResource.hpp"
#include "Audio/Source.hpp"
#include "Libraries/Math/CartesianFrame.hpp"
#include "Libraries/Math/Cuboid.hpp"
#include "Libraries/Math/Sphere.hpp"
#include "Libraries/Variant.hpp"

namespace Emeraude::Scenes::Component
{
	/**
	 * @brief Defines a sound source emitter.
	 * @note You can virtually define infinite number of sound emitter, they are not strictly linked to hardware.
	 * @extends Emeraude::Scenes::Component::Abstract The base class for each entity component.
	 * @extends Libraries::ObserverTrait This component observes sound loading events.
	 */
	class SoundEmitter final : public Abstract, public Libraries::ObserverTrait
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"SoundEmitter"};

			/**
			 * @brief Constructs a sound emitter.
			 * @param name The name of the renderable instance.
			 * @param parentEntity A reference to the parent entity.
			 * @param permanent Set the sound emitter regularly in use. Default false.
			 */
			SoundEmitter (const std::string & name, const AbstractEntity & parentEntity, bool permanent = false) noexcept;

			/** @copydoc Emeraude::Scenes::Component::Abstract::getComponentType() */
			[[nodiscard]]
			const char *
			getComponentType () const noexcept override
			{
				return ClassId;
			}

			/** @copydoc Emeraude::Scenes::Component::Abstract::boundingBox() const */
			[[nodiscard]]
			const Libraries::Math::Cuboid< float > &
			boundingBox () const noexcept override
			{
				return NullBoundingBox;
			}

			/** @copydoc Emeraude::Scenes::Component::Abstract::boundingSphere() const */
			[[nodiscard]]
			const Libraries::Math::Sphere< float > &
			boundingSphere () const noexcept override
			{
				return NullBoundingSphere;
			}

			/** @copydoc Emeraude::Scenes::Component::Abstract::move() */
			void move (const Libraries::Math::CartesianFrame< float > & worldCoordinates) noexcept override;

			/** @copydoc Emeraude::Scenes::Component::Abstract::processLogics() */
			void processLogics (const Scene & scene) noexcept override;

			/** @copydoc Emeraude::Scenes::Component::Abstract::shouldRemove() */
			bool shouldRemove () const noexcept override;

			/**
			 * @brief Enables/Disables the sound distortion with entity velocity.
			 * @param state The state.
			 * @return void
			 */
			void
			enableVelocityDistortion (bool state) noexcept
			{
				this->setFlag(VelocityDistortionEnabled, state);
			}

			/**
			 * @brief Returns whether the sound distortion with entity velocity is enabled.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			velocityDistortionEnabled () const noexcept
			{
				return this->isFlagEnabled(VelocityDistortionEnabled);
			}

			/**
			 * @brief Changes the gain of the source emitter.
			 * @param gain An positive value.
			 * @retur void
			 */
			void
			setGain (float gain) noexcept
			{
				m_gain = std::abs(gain);

				if ( this->isPlaying() )
				{
					m_source->setGain(m_gain);
				}
			}

			/**
			 * @brief Returns the last applied gain.
			 * @retur float
			 */
			[[nodiscard]]
			float
			gain () const noexcept
			{
				return m_gain;
			}

			/**
			 * @brief Attaches a sound to the source for further playback.
			 * @param sound A reference to an audio buffer.
			 * @param gain Set the gain for playing the sound. Default 1.0.
			 * @param loop The loop play mode state. Default false.
			 * @return void
			 */
			void attachSound (const std::shared_ptr< Audio::SoundResource > & sound, float gain = 1.0F, bool loop = false) noexcept;

			/**
			 * @brief Sends a sound to play to the underlying source.
			 * @note This function will wait the sound to be fully loaded before playing it.
			 * @param sound A reference to an audio buffer.
			 * @param gain Set the gain for playing the sound. Default 1.0.
			 * @param loop The loop play mode state. Default false.
			 * @param replaceSound Replace sound if the source is playing. Default true.
			 * @return void
			 */
			void play (const std::shared_ptr< Audio::SoundResource > & sound, float gain = 1.0F, bool loop = false, bool replaceSound = true) noexcept;

			/**
			 * @brief Replays the previous sound if exists.
			 * @note The sound will be rewound if source is playing.
			 * @return void
			 */
			void replay () noexcept;

			/**
			 * @brief Stops the playing.
			 * @return void
			 */
			void stop () const noexcept;

			/**
			 * @brief Pauses the playing.
			 * @return void
			 */
			void pause () const noexcept;

			/**
			 * @brief Resumes a paused sound.
			 * @return void
			 */
			void resume () const noexcept;

			/**
			 * @brief Rewinds the sound.
			 * @return void
			 */
			void rewind () const noexcept;

			/**
			 * @brief Returns whether the source is playing something or not.
			 * @return bool
			 */
			[[nodiscard]]
			bool isPlaying () const noexcept;

			/**
			 * @brief Removes attached sound.
			 * @return void
			 */
			void clear () noexcept;

		private:

			/** @copydoc Emeraude::Animations::AnimatableInterface::playAnimation() */
			bool playAnimation (Animations::id_t identifier, const Libraries::Variant & value) noexcept override;

			/** @copydoc Libraries::ObserverTrait::onNotification() */
			[[nodiscard]]
			bool onNotification (const Libraries::ObservableTrait * observable, int notificationCode, const std::any & data) noexcept override;

			/**
			 * @brief Gets an available audio source from the manager.
			 * @return bool
			 */
			bool requestSource () noexcept;

			/**
			 * @brief Updates the source properties with the entity.
			 * @param worldCoordinates A reference to a coordinates.
			 * @return void
			 */
			void updateSource (const Libraries::Math::CartesianFrame< float > & worldCoordinates) const noexcept;

			/**
			 * @brief Release an audio source.
			 * @return void
			 */
			void releaseSource () noexcept;

			/**
			 * @brief Plays the attached sound resource.
			 * @return void
			 */
			void playAttachedSound () noexcept;

			/**
			 * @brief Releases the attached sound resource.
			 * @return void
			 */
			void releaseAttachedSound () noexcept;

			/* Flag names. */
			static constexpr auto KeepInactiveSourceAlive{UnusedFlag + 0UL};
			static constexpr auto Loop{UnusedFlag + 1UL};
			static constexpr auto VelocityDistortionEnabled{UnusedFlag + 2UL};

			std::shared_ptr< Audio::Source > m_source;
			std::shared_ptr< Audio::SoundResource > m_attachedSound;
			float m_gain{8.0F};
	};
}
