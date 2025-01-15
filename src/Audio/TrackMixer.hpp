/*
 * src/Audio/TrackMixer.hpp
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
#include <array>
#include <memory>

/* Local inclusions for inheritances. */
#include "ServiceInterface.hpp"
#include "ConsoleControllable.hpp"
#include "Libraries/ObserverTrait.hpp"

/* Local inclusions for usages. */
#include "MusicResource.hpp"
#include "Source.hpp"

/* Forward declarations. */
namespace Emeraude
{
	namespace Audio
	{
		class Manager;
	}

	namespace Resources
	{
		class Manager;
	}

	class PrimaryServices;
}

namespace Emeraude::Audio
{
	/**
	 * @brief The track mixer service class.
	 * @extends Emeraude::ServiceInterface This is a service.
	 * @extends Emeraude::ConsoleControllable This can be controlled by the console.
	 * @extends Libraries::ObserverTrait
	 */
	class TrackMixer final : public ServiceInterface, public ConsoleControllable, public Libraries::ObserverTrait
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"TrackMixerService"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/** @brief Observable notification codes. */
			enum NotificationCode
			{
				MusicPlaying,
				MusicSwitching,
				MusicPaused,
				MusicResumed,
				MusicStopped,
				/* Enumeration boundary. */
				MaxEnum
			};

			/**
			 * @brief Constructs the external audio input.
			 * @param primaryServices A reference to primary services.
			 * @param resourceManager A reference to the resource manager.
			 * @param audioManager A reference to the audio manager.
			 */
			TrackMixer (PrimaryServices & primaryServices, Resources::Manager & resourceManager, Manager & audioManager) noexcept;

			/** @copydoc Libraries::ObservableTrait::classUID() const */
			[[nodiscard]]
			size_t
			classUID () const noexcept override
			{
				return ClassUID;
			}

			/** @copydoc Libraries::ObservableTrait::is() const */
			[[nodiscard]]
			bool
			is (size_t classUID) const noexcept override
			{
				return classUID == ClassUID;
			}

			/** @copydoc Emeraude::ServiceInterface::usable() */
			[[nodiscard]]
			bool
			usable () const noexcept override
			{
				return m_flags[ServiceInitialized];
			}

			/**
			 * @brief Updates the track mixer.
			 */
			void update () noexcept;

			/**
			 * @brief Sets the track gain.
			 * @param volume The gain.
			 */
			void setVolume (float volume) noexcept;

			/**
			 * @brief Returns the current gain.
			 * @return float
			 */
			[[nodiscard]]
			float
			volume () const noexcept
			{
				return m_gain;
			}

			/**
			 * @brief Plays a soundtrack.
			 * @param track A reference to a music resource.
			 * @param fade Enable fading. Default false.
			 * @return bool
			 */
			bool setSoundTrack (const std::shared_ptr< MusicResource > & track, bool fade = false) noexcept;

			/**
			 * @brief Returns whether the soundtrack is playing.
			 * @return bool
			 */
			[[nodiscard]]
			bool isPlaying () const noexcept;

			/**
			 * @brief Pauses the music.
			 * @return void
			 */
			void pause () noexcept;

			/**
			 * @brief Resumes the music.
			 * @return void
			 */
			void resume () noexcept;

			/**
			 * @brief Stops the music.
			 * @return void
			 */
			void stop () noexcept;

		private:

			/** @brief The track type enumerations. */
			enum class PlayingTrack : uint8_t
			{
				None,
				TrackA,
				TrackB
			};

			/** @copydoc Emeraude::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc Emeraude::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

			/** @copydoc Libraries::ObserverTrait::onNotification() */
			[[nodiscard]]
			bool onNotification (const Libraries::ObservableTrait * observable, int notificationCode, const std::any & data) noexcept override;

			/**
			 * @brief Fades a track.
			 * @param track A reference to the track.
			 * @param step The step of raising or lowering the volume.
			 * @return bool
			 */
			bool fadeTrack (Source & track, float step) const noexcept;

			/**
			 * @brief Check the music resource loading.
			 * @param track A reference to a music resource smart pointer.
			 * @return bool
			 */
			[[nodiscard]]
			bool checkTrackLoading (const std::shared_ptr< MusicResource > & track) noexcept;

			/* Flag names. */
			static constexpr auto ServiceInitialized{0UL};
			static constexpr auto IsFadingWasDemanded{1UL};
			static constexpr auto IsTrackingFading{2UL};

			PrimaryServices & m_primaryServices;
			Resources::Manager & m_resourceManager;
			Manager & m_audioManager;
			std::shared_ptr< Source > m_trackA;
			std::shared_ptr< Source > m_trackB;
			float m_gain{0.0F};
			PlayingTrack m_playingTrack{PlayingTrack::None};
			std::shared_ptr< MusicResource > m_loadingTrack;
			std::array< bool, 8 > m_flags{
				false/*ServiceInitialized*/,
				false/*IsFadingWasDemanded*/,
				false/*IsTrackingFading*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
