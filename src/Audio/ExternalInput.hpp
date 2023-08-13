/*
 * Emeraude/Audio/ExternalInput.hpp
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
#include <thread>
#include <vector>

/* Local inclusions for inheritances. */
#include "ServiceInterface.hpp"

/* Local inclusions for usages. */
#include "Path/File.hpp"
#include "WaveFactory/Types.hpp"

/* Third-party libraries */
#include "Third-Party-Inclusion/openal.hpp"

/* Forward declarations. */
namespace Emeraude
{
	class Arguments;
	class Settings;
}

namespace Emeraude::Audio
{
	/**
	 * @brief Class that define a device to grab audio from outside of the engine like a real microphone.
	 * @extends Emeraude::Audio::ServiceInterface This is a service.
	 */
	class ExternalInput final : public ServiceInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"AudioExternalInputService"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/* Settings keys */
			static constexpr auto RecorderFrequencyKey = "Audio/Frequency";
			static constexpr auto DefaultRecorderFrequency = 22050;
			static constexpr auto RecorderBufferSizeKey = "Audio/BufferSize";
			static constexpr auto DefaultRecorderBufferSize = 32;

			/**
			 * @brief Constructs the external audio input.
			 * @param arguments A reference to the core arguments.
			 * @param coreSettings A reference to the core settings.
			 */
			ExternalInput (const Arguments & arguments, Settings & coreSettings) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			ExternalInput (const ExternalInput & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			ExternalInput (ExternalInput && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			ExternalInput & operator= (const ExternalInput & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			ExternalInput & operator= (ExternalInput && copy) noexcept = delete;

			/**
			 * @brief Destructor.
			 */
			~ExternalInput () override;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::ServiceInterface::usable() */
			[[nodiscard]]
			bool usable () const noexcept override;

			/**
			 * @brief Returns whether the capture is enabled.
			 * @return bool
			 */
			[[nodiscard]]
			bool isRecording () const noexcept;

			/**
			 * @brief Starts the recording.
			 */
			void start () noexcept;

			/**
			 * @brief Stops the recording.
			 */
			void stop () noexcept;

			/**
			 * @brief Saves the recording to file.
			 * @param filepath A reference to a file
			 * @return bool
			 */
			bool saveRecord (const Libraries::Path::File & filepath) noexcept;

		private:

			/** @copydoc Emeraude::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc Emeraude::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

			/**
			 * @brief Process the capture task.
			 */
			void process () noexcept;

			/**
			 * @brief Queries devices informations.
			 * @return bool.
			 */
			bool queryDevices () noexcept;

			// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members) NOTE: Services inter-connexions.
			const Arguments & m_arguments;
			Settings & m_coreSettings;
			// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
			ALCdevice * m_device = nullptr;
			std::vector< std::string > m_availableCaptureDevices{};
			std::vector< ALshort > m_samples{};
			std::thread m_process{};
			Libraries::WaveFactory::Frequency m_frequency = Libraries::WaveFactory::Frequency::PCM44100Hz;
			bool m_isRecording = false;
	};
}
