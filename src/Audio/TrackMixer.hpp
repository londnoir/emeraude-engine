/*
 * Emeraude/Audio/TrackMixer.hpp
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
#include <array>
#include <memory>

/* Local inclusions for inheritances. */
#include "ServiceInterface.hpp"
#include "ConsoleControllable.hpp"
#include "Observable.hpp"
#include "Observer.hpp"

/* Local inclusions for usages. */
#include "MusicResource.hpp"
#include "Source.hpp"

/* Forward declarations. */
namespace Emeraude
{
	namespace Resources
	{
		class Manager;
	}

	class Arguments;
	class Settings;
}

namespace Emeraude::Audio
{
	class Manager;

	/**
	 * @brief The track mixer service class.
	 * @extends Emeraude::ServiceInterface This is a service.
	 * @extends Emeraude::ConsoleControllable This can be controlled by the console.
	 * @extends Libraries::Observer
	 */
	class TrackMixer final : public ServiceInterface, public ConsoleControllable, public Libraries::Observer
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
			 * @param arguments A reference to the core arguments.
			 * @param coreSettings A reference to the core settings.
			 * @param resourceManager A reference to the resource manager.
			 * @param audioManager A reference to the audio manager.
			 */
			TrackMixer (const Arguments & arguments, Settings & coreSettings, Resources::Manager & resourceManager, Manager & audioManager) noexcept;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::ServiceInterface::usable() */
			[[nodiscard]]
			bool usable () const noexcept override;

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
			float volume () const noexcept;

			/**
			 * @brief Plays a sound track.
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

			/** @brief Console function to play a music. */
			int CFPlay (const std::vector< std::string > & parameters) noexcept;

			/** @brief Console function to pause music playback. */
			int CFPause (const std::vector< std::string > & parameters) noexcept;

			/** @brief Console function to stop music playback. */
			int CFStop (const std::vector< std::string > & parameters) noexcept;

		private:

			/** @brief The track type enumerations. */
			enum class PlayingTrack
			{
				None,
				TrackA,
				TrackB
			};

			/** @copydoc Emeraude::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc Emeraude::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

			/** @copydoc Libraries::Observer::onTerminate() */
			[[nodiscard]]
			bool onNotification (const Libraries::Observable * observable, int notificationCode, const std::any & data) noexcept override;

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
			static constexpr auto Usable = 0UL;
			static constexpr auto IsFadingWasDemanded = 1UL;
			static constexpr auto IsTrackingFading = 2UL;

			// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members) NOTE: Services inter-connexions.
			const Arguments & m_arguments;
			Settings & m_coreSettings;
			Resources::Manager & m_resourceManager;
			Manager & m_audioManager;
			// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
			std::shared_ptr< Source > m_trackA{};
			std::shared_ptr< Source > m_trackB{};
			float m_gain = 0.0F;
			PlayingTrack m_playingTrack = PlayingTrack::None;
			std::shared_ptr< MusicResource > m_loadingTrack{};
			std::array< bool, 8 > m_flags{ // NOLINT(*-magic-numbers)
				false/*Usable*/,
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
