/*
 * Emeraude/Scenes/SoundEmitter.hpp
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

#pragma once

/* C/C++ standard libraries. */
#include <memory>
#include <utility>

/* Local inclusions for inheritances. */
#include "AbstractComponent.hpp"
#include "Observer.hpp"

/* Local inclusions for usages. */
#include "Audio/Source.hpp"
#include "Audio/SoundResource.hpp"

namespace Emeraude::Scenes
{
	/**
	 * @brief Defines a sound source emitter.
	 * @extends Emeraude::Scenes::AbstractComponent The base class for each entity component.
	 * @extends Observer This component observes sound loading events.
	 */
	class SoundEmitter final : public AbstractComponent, public Libraries::Observer
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

			/** @copydoc Emeraude::Scenes::AbstractComponent::getComponentType() */
			[[nodiscard]]
			const char * getComponentType () const noexcept override;

			/**
			 * @brief Sends a sound to play to the underlying source.
			 * @note This function will wait the sound to be fully loaded before playing it.
			 * @param sound A reference to an audio buffer.
			 * @param loop The loop play mode state. Default false.
			 * @return void
			 */
			void play (const std::shared_ptr< Audio::SoundResource > & sound, bool loop = false) noexcept;

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

			/* Flag names. */
			static constexpr auto KeepInactiveSourceAlive = 0UL;
			static constexpr auto Loop = 1UL;

			/** @copydoc Emeraude::Scenes::AbstractComponent::move() */
			void move () noexcept override;

			/** @copydoc Emeraude::Scenes::AbstractComponent::processLogics() */
			void processLogics (const Scene & scene, size_t cycle) noexcept override;

			/** @copydoc Emeraude::Animations::Interface::playAnimation() */
			bool playAnimation (Animations::id_t id, const Libraries::Variant & value) noexcept override;

			/** @copydoc Libraries::Observer::onNotification() */
			[[nodiscard]]
			bool onNotification (const Libraries::Observable * observable, int notificationCode, const std::any & data) noexcept override;

			/**
			 * @brief Gets an available audio source from the manager.
			 * @return bool
			 */
			bool requestSource () noexcept;

			/**
			 * @brief Updates the source properties with the entity.
			 * @return void
			 */
			void updateSource () const noexcept;

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

			std::shared_ptr< Audio::Source > m_source{};
			std::shared_ptr< Audio::SoundResource > m_attachedSound{};
			std::array< bool, 8 > m_flags{
				false/*KeepInactiveSourceAlive*/,
				false/*Loop*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
