/*
 * Emeraude/Audio/Manager.hpp
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
#include <string>
#include <vector>

/* Local inclusions for inheritances. */
#include "ServiceInterface.hpp"
#include "ConsoleControllable.hpp"

/* Local inclusions for usages. */
#include "Source.hpp" // FIXME
#include "WaveFactory/Types.hpp"

/* Third-party libraries */
#include "OpenAL.EFX.hpp"

/* Forward declarations. */
namespace Emeraude
{
	class Arguments;
	class Settings;
}

namespace Emeraude::Audio
{
	/** @brief The playing mode enumeration. */
	enum class PlayMode
	{
		Once,
		Loop
	};

	/**
	 * @brief The audio manager service class.
	 * @extends Emeraude::ServiceInterface This is a service.
	 * @extends Libraries::Observable
	 */
	class Manager final : public ServiceInterface, public ConsoleControllable
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"AudioManagerService"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/* Settings keys */
			static constexpr auto EnabledKey = "Audio/Enabled";
			static constexpr auto DefaultEnabled = true;
			static constexpr auto PlaybackFrequencyKey = "Audio/PlaybackFrequency";
			static constexpr auto DefaultPlaybackFrequency = 22050;
			static constexpr auto MasterVolumeKey = "Audio/MasterVolume";
			static constexpr auto DefaultMasterVolume = 0.75F;
			static constexpr auto SFXVolumeKey = "Audio/SFXVolume";
			static constexpr auto DefaultSFXVolume = 0.6F;
			static constexpr auto MusicVolumeKey = "Audio/MusicVolume";
			static constexpr auto DefaultMusicVolume = 0.5F;
			static constexpr auto MusicChunkSizeKey = "Audio/MusicChunkSize";
			static constexpr auto DefaultMusicChunkSize = 8192;
			static constexpr auto OpenALUseALUTKey = "Audio/OpenAL/UseALUT";
			static constexpr auto DefaultOpenALUseALUT = true;
			static constexpr auto OpenALUseEFXExtensionsKey = "Audio/OpenAL/UseEFXExtensions";
			static constexpr auto DefaultOpenALUseEFXExtensions = true;
			static constexpr auto OpenALRefreshRateKey = "Audio/OpenAL/RefreshRate";
			static constexpr auto DefaultOpenALRefreshRate = 46;
			static constexpr auto OpenALSyncStateKey = "Audio/OpenAL/SyncState";
			static constexpr auto DefaultOpenALSyncState = 0;
			static constexpr auto OpenALMaxMonoSourceCountKey = "Audio/OpenAL/MaxMonoSourceCount";
			static constexpr auto DefaultOpenALMaxMonoSourceCount = 32;
			static constexpr auto OpenALMaxStereoSourceCountKey = "Audio/OpenAL/MaxStereoSourceCount";
			static constexpr auto DefaultOpenALMaxStereoSourceCount = 2;

			/** @brief Observable notification codes. */
			enum NotificationCode
			{
				SpeakerCreated,
				SpeakerDestroyed,
				/* Enumeration boundary. */
				MaxEnum
			};

			/** @brief The distance model to use with audio source for mixing. */
			enum class DistanceModel
			{
				Inverse,
				InverseClamped,
				Linear,
				LinearClamped,
				Exponent,
				ExponentClamped
			};

			/**
			 * @brief Constructs an audio manager.
			 * @param arguments A reference to the core arguments.
			 * @param coreSettings A reference to the core settings.
			 */
			Manager (const Arguments & arguments, Settings & coreSettings) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Manager (const Manager & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Manager (Manager && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			Manager & operator= (const Manager & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			Manager & operator= (Manager && copy) noexcept = delete;

			/**
			 * @brief Destructs the audio manager.
			 */
			~Manager () override;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::ServiceInterface::usable() */
			[[nodiscard]]
			bool usable () const noexcept override;

			/**
			 * @brief Sets the main state of the audio manager.
			 * @param state The state.
			 */
			void setState (bool state) noexcept;

			/**
			 * @brief Returns the main state of the audio manager.
			 * @return bool
			 */
			[[nodiscard]]
			bool state () const noexcept;

			/**
			 * @brief Returns the EFX extension checker.
			 * @return std::shared_ptr< EFX >
			 */
			[[nodiscard]]
			std::shared_ptr< EFX > getEFX () noexcept;

			/**
			 * @brief Returns the default Source.
			 * @return std::shared_ptr< Source >
			 */
			[[nodiscard]]
			std::shared_ptr< Source > defaultSource () const noexcept;

			/**
			 * @brief Plays a sound on the default source.
			 * @param sample A pointer on a playable interface.
			 * @param mode The play mode. Default Once.
			 * @param gain The gain of the channel to play the sound.
			 */
			void play (const PlayableInterface * sample, Source::PlayMode mode = Source::PlayMode::Once, float gain = 1.0F) const noexcept;

			/**
			 * @brief Returns the API (OpenAL) information.
			 * @return std::string
			 */
			[[nodiscard]]
			std::string getAPIInformation () noexcept;

			/**
			 * @brief Returns whether the audio was enabled at startup.
			 * @return bool
			 */
			[[nodiscard]]
			static bool isAudioAvailable () noexcept;

			/**
			 * @brief Returns the frequency playback.
			 * @return Frequency
			 */
			[[nodiscard]]
			Libraries::WaveFactory::Frequency frequencyPlayback () const noexcept;

			/**
			 * @brief Returns the music chunk size for streaming.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t musicChunkSize () const noexcept;

			/**
			 * @brief Sets the master volume.
			 * @param gain The gain from 0.0 to 1.0.
			 */
			void setMasterVolume (float gain) noexcept;

			/**
			 * @brief Returns the master volume.
			 * @return float
			 */
			[[nodiscard]]
			float masterVolume () noexcept;

			/**
			 * @brief Sets the distance model for the sound attenuation.
			 * @param model One of the DistanceModel enum values.
			 */
			void setDistanceModel (DistanceModel model) noexcept;

			/**
			 * @brief Returns the current distance model in use for the sound attenuation.
			 * @return DistanceModel
			 */
			[[nodiscard]]
			DistanceModel distanceModel () const noexcept;

			/**
			 * @brief Sets the doppler effect factor.
			 * @param dopplerFactor
			 */
			void setDopplerFactor (float dopplerFactor) noexcept;

			/**
			 * @brief Returns the current doppler effect factor.
			 * @return float
			 */
			[[nodiscard]]
			float dopplerFactor () const noexcept;

			/**
			 * @brief Sets the speed of sound.
			 * @param speed The value in unit per second.
			 */
			void setSpeedOfSound (float speed) noexcept;

			/**
			 * @brief Returns the current speed of sound.
			 * @return float
			 */
			[[nodiscard]]
			float speedOfSound () noexcept;

			/**
			 * @brief Sets the listener properties.
			 * @param properties An array of parameters. The first 3 floats are for position,
			 * the next 3 floats are for orientation and the 3 lasts for velocity.
			 */
			void setListenerProperties (const std::array< ALfloat, 12 > & properties) noexcept; // NOLINT(*-magic-numbers)

			/**
			 * @brief Returns the listener properties by reference.
			 * @param properties An array of parameters. The first 3 floats are for position,
			 * the next 3 floats are for orientation and the 3 lasts for velocity.
			 */
			void listenerProperties (std::array< ALfloat, 12 > & properties) const noexcept; // NOLINT(*-magic-numbers)

			/**
			 * @brief Sets meters per unit.
			 * @note Requires EFX extension.
			 * @param meters The speed in meters par unit.
			 */
			void setMetersPerUnit (float meters) noexcept;

			/**
			 * @brief Returns meters per unit.
			 * @note Requires EFX extension.
			 * @return float
			 */
			[[nodiscard]]
			float metersPerUnit () const noexcept;

			/**
			 * @brief Returns the ALC version as a string.
			 * @return std::string
			 */
			[[nodiscard]]
			std::string getALCVersionString () const noexcept;

			/**
			 * @brief Returns the EFX version as a string.
			 * @return std::string
			 */
			[[nodiscard]]
			std::string getEFXVersionString () const noexcept;

			/**
			 * @brief Returns the number of available audio source.
			 * @return size_t.
			 */
			[[nodiscard]]
			size_t getAvailableSourceCount () const noexcept;

			/**
			 * @brief Returns an available audio source.
			 * @return std::shared_ptr< Source >
			 */
			[[nodiscard]]
			std::shared_ptr< Source > requestSource () const noexcept;

			/**
			 * @brief Returns the instance of the audio manager.
			 * @return Manager *
			 */
			[[nodiscard]]
			static Manager * instance () noexcept;

		private:

			/** @copydoc Emeraude::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc Emeraude::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

			/**
			 * @brief Returns the split device name from the raw API data.
			 * @param list The raw list from OpenAL.
			 * @return vector< string >
			 */
			[[nodiscard]]
			static std::vector< std::string > getDeviceName (const ALCchar * list) noexcept;

			/**
			 * @brief Queries the available device and save it.
			 */
			void queryDevices () noexcept;

			/**
			 * @brief Returns the device attributes.
			 * @return std::vector< ALCint >
			 */
			[[nodiscard]]
			std::vector< ALCint > getDeviceAttributes () const noexcept;

			/**
			 * @brief Gets and save a copy of the context attributes into the manager.
			 * @return bool
			 */
			bool saveContextAttributes () noexcept;

			/* Flag names. */
			static constexpr auto Usable = 0UL;
			static constexpr auto MainState = 1UL;
			static constexpr auto UsingALUT = 2UL;

			static Manager * s_instance; // NOLINT NOTE: Singleton behavior

			// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members) NOTE: Services inter-connexions.
			const Arguments & m_arguments;
			Settings & m_coreSettings;
			// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
			ALCdevice * m_device = nullptr;
			ALCcontext * m_context = nullptr;
			std::vector< std::string > m_availableAudioDevices{};
			std::shared_ptr< EFX > m_EFX{};
			std::map< ALCint, ALCint > m_contextAttributes{};
			std::shared_ptr< Source > m_defaultSource{};
			std::vector< std::shared_ptr< Source > > m_sources{};
			Libraries::WaveFactory::Frequency m_playbackFrequency{Libraries::WaveFactory::Frequency::PCM22050Hz};
			size_t m_musicChunkSize{DefaultMusicChunkSize};
			std::array< bool, 8 > m_flags{ // NOLINT(*-magic-numbers)
				true/*Usable*/,
				false/*MainState*/,
				false/*UsingALUT*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
