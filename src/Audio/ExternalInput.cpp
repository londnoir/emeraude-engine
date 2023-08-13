/*
 * Emeraude/Audio/ExternalInput.cpp
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

#include "ExternalInput.hpp"

/* C/C++ standard libraries. */
#include <iostream>
#include <cstring>

/* Local inclusions */
#include "WaveFactory/Wave.hpp"
#include "Tracer.hpp"
#include "Arguments.hpp"
#include "Settings.hpp"
#include "Manager.hpp"

namespace Emeraude::Audio
{
	using namespace Libraries;

	const size_t ExternalInput::ClassUID{Observable::getClassUID()};

	ExternalInput::ExternalInput (const Arguments & arguments, Settings & coreSettings) noexcept
		: ServiceInterface(ClassId), m_arguments(arguments), m_coreSettings(coreSettings)
	{

	}

	ExternalInput::~ExternalInput ()
	{
		if ( m_process.joinable() )
			m_process.join();
	}

	bool
	ExternalInput::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	ExternalInput::usable () const noexcept
	{
		return m_device != nullptr;
	}

	bool
	ExternalInput::onInitialize () noexcept
	{
		if ( !Audio::Manager::isAudioAvailable() )
		{
			Tracer::warning(ClassId, "Audio external input disabled at startup.");

			return true;
		}

		if ( alcIsExtensionPresent(nullptr, "ALC_EXT_CAPTURE") == AL_FALSE )
			return false;

		/* Checks configuration file */
		const auto frequency = WaveFactory::toFrequency(m_coreSettings.getAs< unsigned int >(RecorderFrequencyKey, DefaultRecorderFrequency));
		const auto bufferSize = m_coreSettings.getAs< unsigned int >(RecorderBufferSizeKey, DefaultRecorderBufferSize);

		if ( frequency == WaveFactory::Frequency::Invalid )
		{
			Tracer::warning(ClassId, Blob() << "Invalid recorder frequency in configuration file ! Leaving to default (" << DefaultRecorderFrequency << " Hz).");
		}
		else
		{
			m_frequency = frequency;
		}

		if ( !this->queryDevices() )
		{
			Tracer::error(ClassId, "There is no capture device available !");

			return false;
		}

		m_device = alcCaptureOpenDevice(nullptr, static_cast< ALuint >(m_frequency), AL_FORMAT_MONO16, bufferSize * 1024);

		if ( m_device == nullptr )
		{
			Tracer::error(ClassId, "Unable to open default capture device !");

			return false;
		}

		return true;
	}

	bool
	ExternalInput::onTerminate () noexcept
	{
		if ( m_device != nullptr )
		{
			alcCaptureCloseDevice(m_device);

			m_device = nullptr;
		}

		return true;
	}

	bool
	ExternalInput::isRecording () const noexcept
	{
		return m_isRecording;
	}

	void
	ExternalInput::start () noexcept
	{
		if ( !this->usable() )
		{
			Tracer::warning(ClassId, "The audio external input is unavailable !");

			return;
		}

		if ( m_isRecording )
			return;

		m_samples.clear();

		alcCaptureStart(m_device);

		m_isRecording = true;

		m_process = std::thread(&ExternalInput::process, this);
	}

	void
	ExternalInput::stop () noexcept
	{
		if ( !this->usable() )
		{
			Tracer::warning(ClassId, "The audio external input is unavailable !");

			return;
		}

		if ( !m_isRecording )
			return;

		alcCaptureStop(m_device);

		m_isRecording = false;
	}

	bool
	ExternalInput::saveRecord (const Libraries::Path::File & filepath) noexcept
	{
		if ( m_isRecording )
		{
			Tracer::warning(ClassId, "The recorder is still running !");

			return false;
		}

		if ( m_samples.empty() )
		{
			Tracer::warning(ClassId, "There is no record to save !");

			return false;
		}

		WaveFactory::Wave< short int > file;

		if ( !file.initialize(m_samples, WaveFactory::Channels::Mono, m_frequency) )
		{
			Tracer::error(ClassId, "Unable to initialize wave data !");

			return false;
		}

		if ( !file.writeFile(filepath) )
		{
			Tracer::error(ClassId, "Unable to save the record to a file !");

			return false;
		}

		return true;
	}

	void
	ExternalInput::process () noexcept
	{
		while ( m_isRecording )
		{
			ALCint sampleCount = 0;

			alcGetIntegerv(m_device, ALC_CAPTURE_SAMPLES, 1, &sampleCount);

			if ( sampleCount > 0 )
			{
				auto offset = m_samples.size();

				m_samples.resize(offset + static_cast< size_t >(sampleCount));

				alcCaptureSamples(m_device, &m_samples[offset], sampleCount);
			}
		}
	}

	bool
	ExternalInput::queryDevices () noexcept
	{
		if ( alcIsExtensionPresent(nullptr, "ALC_EXT_CAPTURE") == ALC_FALSE )
			return false;

		auto devices = alcGetString(nullptr, ALC_CAPTURE_DEVICE_SPECIFIER);

		if ( devices )
		{
			while ( std::strlen(devices) > 0 )
			{
				m_availableCaptureDevices.push_back(devices);

				devices += std::strlen(devices) + 1;
			}

			std::cout << "[OpenAL] Capture devices :\n";

			for ( auto & deviceName : m_availableCaptureDevices )
				std::cout << " - " << deviceName << '\n';

			std::cout << "[OpenAL] Default capture device : " << alcGetString(nullptr, ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER) << '\n' << std::endl;
		}

		return !m_availableCaptureDevices.empty();
	}
}
