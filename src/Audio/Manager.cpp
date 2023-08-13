/*
 * Emeraude/Audio/Manager.cpp
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

#include "Manager.hpp"

/* C/C++ standard libraries. */
#include <cstring>
#include <iostream>

/* Local inclusions */
#include "Arguments.hpp"
#include "Math/Base.hpp"
#include "Settings.hpp"
#include "Source.hpp"
#include "Tracer.hpp"
#include "Utility.hpp"

namespace Emeraude::Audio
{
	using namespace Libraries;
	using namespace Libraries::Math;

	const size_t Manager::ClassUID{Observable::getClassUID()};
	Manager * Manager::s_instance{nullptr}; // NOLINT NOTE: Singleton behavior

	Manager::Manager (const Arguments & arguments, Settings & coreSettings) noexcept
		: ServiceInterface(ClassId), ConsoleControllable(ClassId), m_arguments(arguments), m_coreSettings(coreSettings)
	{
		if ( s_instance != nullptr )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", constructor called twice !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

			std::terminate();
		}

		s_instance = this;
	}

	Manager::~Manager ()
	{
		s_instance = nullptr;
	}

	Manager *
	Manager::instance () noexcept
	{
		return s_instance;
	}

	bool
	Manager::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	Manager::onInitialize () noexcept // NOLINT(readability-function-cognitive-complexity)
	{
		m_flags[UsingALUT] = m_coreSettings.getAs< bool >(OpenALUseALUTKey, DefaultOpenALUseALUT);

		m_flags[Usable] = !m_arguments.get("--disable-audio").isPresent() && m_coreSettings.getAs< bool >(EnabledKey, DefaultEnabled);

		if ( !Manager::isAudioAvailable() )
		{
			Tracer::warning(ClassId, "Audio manager disabled at startup.");

			return true;
		}

		/* Sets the frequency playback. */
		m_playbackFrequency = WaveFactory::toFrequency(m_coreSettings.getAs< unsigned int >(PlaybackFrequencyKey, DefaultPlaybackFrequency));

		/* Sets the music chunk size in bytes. */
		m_musicChunkSize = m_coreSettings.getAs< unsigned long int >(MusicChunkSizeKey, DefaultMusicChunkSize);

		/* OpenAL Utility Toolkit. */
		if ( m_flags[UsingALUT] )
		{
			Tracer::info(ClassId, "Initializing OpenAL device and context with ALUT ...");

			auto argc = m_arguments.getArgc();

			if ( alutInit(&argc, m_arguments.getArgvCopy()) == AL_TRUE )
			{
				m_context = alcGetCurrentContext();

				if ( alcGetErrors(m_device, "alcGetCurrentContext()", __FILE__, __LINE__) || m_context == nullptr )
				{
					Tracer::error(ClassId, "Unable to get the audio context !");

					return false;
				}

				m_device = alcGetContextsDevice(m_context);

				if ( alcGetErrors(m_device, "alcGetContextsDevice()", __FILE__, __LINE__) || m_device == nullptr )
				{
					Tracer::error(ClassId, "Unable to get the audio device from current context !");

					return false;
				}

			}
			else
			{
				Tracer::error(ClassId, "Unable to initialize audio API !");

				return false;
			}
		}
		else
		{
			Tracer::info(ClassId, "Initializing OpenAL device and context manually ...");

			this->queryDevices();

			/* Take the default device. */
			m_device = alcOpenDevice(nullptr);

			if ( alcGetErrors(m_device, "alcOpenDevice()", __FILE__, __LINE__) || m_device == nullptr )
			{
				Tracer::error(ClassId, "Unable to get the default audio device !");

				return false;
			}

			std::array attrList{
				ALC_FREQUENCY, static_cast< int >(m_playbackFrequency),
				ALC_REFRESH, m_coreSettings.getAs< int >(OpenALRefreshRateKey, DefaultOpenALRefreshRate),
				ALC_SYNC, m_coreSettings.getAs< int >(OpenALSyncStateKey, DefaultOpenALSyncState),
				ALC_MONO_SOURCES, m_coreSettings.getAs< int >(OpenALMaxMonoSourceCountKey, DefaultOpenALMaxMonoSourceCount),
				ALC_STEREO_SOURCES, m_coreSettings.getAs< int >(OpenALMaxStereoSourceCountKey, DefaultOpenALMaxStereoSourceCount),
				0
			};

			/* Context creation and set it as default. */
			m_context = alcCreateContext(m_device, attrList.data());

			if ( alcGetErrors(m_device, "alcCreateContext()", __FILE__, __LINE__) || m_context == nullptr )
			{
				Tracer::error(ClassId, "Unable to load an audio context !");

				return false;
			}

			if ( alcMakeContextCurrent(m_context) == AL_FALSE || alcGetErrors(m_device, "alcMakeContextCurrent()", __FILE__, __LINE__) )
			{
				Tracer::error(ClassId, "Unable set the current audio context !");

				return false;
			}
		}

		/* OpenAL EFX extensions. */
		if ( m_coreSettings.getAs< bool >(OpenALUseEFXExtensionsKey, DefaultOpenALUseEFXExtensions) )
		{
			m_EFX = std::make_shared< EFX >(m_device);

			if ( m_EFX->isAvailable() )
			{
				Tracer::success(ClassId, "OpenAL EFX extension available.");
			}
			else
			{
				Tracer::warning(ClassId, "OpenAL EFX extension unavailable !");
			}
		}

		if ( !this->saveContextAttributes() )
		{
			return false;
		}

		/* NOTE: Be sure of playback frequency allowed by ths OpenAL context. */
		m_playbackFrequency = WaveFactory::toFrequency(m_contextAttributes[ALC_FREQUENCY]);

		Manager::setMasterVolume(m_coreSettings.getAs< float >(MasterVolumeKey, DefaultMasterVolume));

		/* Create all sources available minus the default one. */
		for ( int index = 0; index < m_contextAttributes[ALC_MONO_SOURCES]; index++ )
		{
			auto source = std::make_shared< Source >();

			if ( !source->isCreated() )
			{
				Tracer::warning(ClassId, Blob() << "Unable to create the source #" << index << " !");

				break;
			}

			m_sources.emplace_back(source);
		}

		if ( m_sources.empty() )
		{
			Tracer::warning(ClassId, "No audio source available at all !");

			return false;
		}

		m_defaultSource = *m_sources.begin();

		/* NOTE: Check for missing errors from audio lib initialization. */
		if ( alcGetErrors(m_device, "AudioInit", __FILE__, __LINE__) )
		{
			Tracer::warning(ClassId, "There was unread problem with ALC during initialization !");
		}

		if ( alGetErrors("AudioInit", __FILE__, __LINE__) )
		{
			Tracer::warning(ClassId, "There was unread problem with AL during initialization !");
		}

		return true;
	}

	bool
	Manager::onTerminate () noexcept
	{
		if ( !this->usable() )
		{
			return true;
		}

		/* NOTE: Check for missing errors from audio lib execution. */
		if ( alGetErrors("AudioRelease", __FILE__, __LINE__) )
		{
			Tracer::warning(ClassId, "There was unread problem with AL during execution !");
		}

		if ( alcGetErrors(m_device, "AudioRelease", __FILE__, __LINE__) )
		{
			Tracer::warning(ClassId, "There was unread problem with ALC during execution !");
		}

		/* OpenAL Utility Toolkit. */
		if ( m_flags[UsingALUT] )
		{
			Tracer::info(ClassId, "Cleaning OpenAL device and context with ALUT ...");

			if ( alutExit() == AL_FALSE )
			{
				Tracer::error(ClassId, alutGetErrorString(alutGetError()));

				return false;
			}

			m_context = nullptr;
			m_device = nullptr;

			return true;
		}

		alcMakeContextCurrent(nullptr);

		if ( m_context != nullptr )
		{
			alcDestroyContext(m_context);

			m_context = nullptr;
		}

		if ( m_device != nullptr )
		{
			alcCloseDevice(m_device);

			m_device = nullptr;
		}

		return true;
	}

	void
	Manager::setState (bool state) noexcept
	{
		m_flags[MainState] = state;
	}

	bool
	Manager::usable () const noexcept
	{
		if ( !m_flags[Usable] )
		{
			return false;
		}

		if ( m_device == nullptr )
		{
			return false;
		}

		if ( m_context == nullptr )
		{
			return false;
		}

		return true;
	}

	std::shared_ptr< EFX >
	Manager::getEFX () noexcept
	{
		return m_EFX;
	}

	std::shared_ptr< Source >
	Manager::defaultSource () const noexcept
	{
		return m_defaultSource;
	}

	void
	Manager::play (const PlayableInterface * sample, Source::PlayMode mode, float gain) const noexcept
	{
		if ( m_defaultSource == nullptr )
		{
			return;
		}

		m_defaultSource->setGain(gain);
		m_defaultSource->play(sample, mode);
	}

	bool
	Manager::isAudioAvailable () noexcept
	{
		if ( s_instance == nullptr )
		{
			return false;
		}

		return s_instance->m_flags[Usable];
	}

	WaveFactory::Frequency
	Manager::frequencyPlayback () const noexcept
	{
		return m_playbackFrequency;
	}

	size_t
	Manager::musicChunkSize () const noexcept
	{
		return m_musicChunkSize;
	}

	void
	Manager::setMetersPerUnit (float meters) noexcept
	{
		if ( !m_flags[Usable] || !EFX::isAvailable() )
		{
			return;
		}

		if ( meters < 0.0F )
		{
			Tracer::warning(ClassId, "Meters per unit must more than zero !");

			return;
		}

		alListenerf(AL_METERS_PER_UNIT, meters);
	}

	float
	Manager::metersPerUnit () const noexcept
	{
		ALfloat meters = AL_DEFAULT_METERS_PER_UNIT;

		if ( m_flags[Usable] && EFX::isAvailable() )
		{
			alGetListenerf(AL_METERS_PER_UNIT, &meters);
		}

		return meters;
	}

	std::string
	Manager::getALCVersionString () const noexcept
	{
		ALCint major = 0;
		ALCint minor = 0;

		if ( m_contextAttributes.empty() )
		{
			alcGetIntegerv(m_device, ALC_MAJOR_VERSION, 1, &major);
			alcGetIntegerv(m_device, ALC_MINOR_VERSION, 1, &minor);
		}
		else
		{
			major = m_contextAttributes.at(ALC_MAJOR_VERSION);
			minor = m_contextAttributes.at(ALC_MINOR_VERSION);
		}

		return (std::stringstream{} << major << '.' << minor).str();
	}

	std::string
	Manager::getEFXVersionString () const noexcept
	{
		ALCint major = 0;
		ALCint minor = 0;

		/*if ( m_contextAttributes.empty() )
		{
			alcGetIntegerv(m_device, ALC_MAJOR_VERSION, 1, &major);
			alcGetIntegerv(m_device, ALC_MINOR_VERSION, 1, &minor);
		}
		else*/
		{
			major = m_contextAttributes.at(ALC_EFX_MAJOR_VERSION);
			minor = m_contextAttributes.at(ALC_EFX_MINOR_VERSION);
		}

		return (std::stringstream{} << major << '.' << minor).str();
	}

	size_t
	Manager::getAvailableSourceCount () const noexcept
	{
		size_t count = 0;

		for ( const auto & source : m_sources )
		{
			if ( source.use_count() == 1 )
			{
				count++;
			}
		}

		return count;
	}

	std::shared_ptr< Source >
	Manager::requestSource () const noexcept
	{
		/* FIXME: Find a better way to deliver quickly an available source. */
		for ( const auto & source : m_sources )
		{
			if ( source.use_count() == 1 )
			{
				return source;
			}
		}

		return nullptr;
	}

	void
	Manager::setMasterVolume (float gain) noexcept
	{
		if ( !m_flags[Usable] )
		{
			return;
		}

		alListenerf(AL_GAIN, Math::clampToUnit(gain));
	}

	float
	Manager::masterVolume () noexcept
	{
		ALfloat gain = 0.0F;

		if ( m_flags[Usable] )
		{
			alGetListenerf(AL_GAIN, &gain);
		}

		return gain;
	}

	void
	Manager::setDistanceModel (DistanceModel model) noexcept
	{
		if ( !m_flags[Usable] )
		{
			return;
		}

		switch ( model )
		{
			case DistanceModel::ExponentClamped :
				alDistanceModel(AL_EXPONENT_DISTANCE_CLAMPED);
				break;

			case DistanceModel::Exponent :
				alDistanceModel(AL_EXPONENT_DISTANCE);
				break;

			case DistanceModel::LinearClamped :
				alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);
				break;

			case DistanceModel::Linear :
				alDistanceModel(AL_LINEAR_DISTANCE);
				break;

			case DistanceModel::InverseClamped :
				alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
				break;

			case DistanceModel::Inverse :
				alDistanceModel(AL_INVERSE_DISTANCE);
				break;
		}
	}

	Manager::DistanceModel
	Manager::distanceModel () const noexcept
	{
		if ( m_flags[Usable] )
		{
			switch ( alGetInteger(AL_DISTANCE_MODEL) )
			{
				case AL_INVERSE_DISTANCE :
					return DistanceModel::Inverse;

				case AL_INVERSE_DISTANCE_CLAMPED :
					return DistanceModel::InverseClamped;

				case AL_LINEAR_DISTANCE :
					return DistanceModel::Linear;

				case AL_LINEAR_DISTANCE_CLAMPED :
					return DistanceModel::LinearClamped;

				case AL_EXPONENT_DISTANCE :
					return DistanceModel::Exponent;

				case AL_EXPONENT_DISTANCE_CLAMPED :
					return DistanceModel::ExponentClamped;
			}
		}

		return DistanceModel::Inverse;
	}

	void
	Manager::setDopplerFactor (float dopplerFactor) noexcept
	{
		if ( !m_flags[Usable] )
		{
			return;
		}

		if ( dopplerFactor < 0.0F )
		{
			Tracer::warning(ClassId, "Doppler factor must be zero or positive !");

			return;
		}

		/* Scale for source and listener velocities.
		 * (default:1.0, range:0.0-INF+) */
		alDopplerFactor(dopplerFactor);
	}

	float
	Manager::dopplerFactor () const noexcept
	{
		if ( !m_flags[Usable] )
		{
			return 1.0F;
		}

		return alGetFloat(AL_DOPPLER_FACTOR);
	}

	void
	Manager::setSpeedOfSound (float speed) noexcept
	{
		if ( !m_flags[Usable] )
		{
			return;
		}

		if ( speed <= 0.0F )
		{
			Tracer::warning(ClassId, "Speed of sound must more than zero !");

			return;
		}

		/* The speed at which sound waves are assumed to travel,
		 * when calculating the doppler effect.
		 * (default:343.3, range:0.0001-INF+) */
		alSpeedOfSound(speed);
	}

	float
	Manager::speedOfSound () noexcept
	{
		if ( !m_flags[Usable] )
		{
			return 343.3F; // NOLINT(*-magic-numbers)
		}

		return alGetFloat(AL_SPEED_OF_SOUND);
	}

	// NOLINTBEGIN(*-magic-numbers)
	void
	Manager::setListenerProperties (const std::array< ALfloat, 12 > & properties) noexcept
	{
		if ( m_flags[Usable] )
		{
			alListenerfv(AL_POSITION, properties.data());
			alListenerfv(AL_ORIENTATION, properties.data() + 3);
			alListenerfv(AL_VELOCITY, properties.data() + 9);
		}
	}
	// NOLINTEND(*-magic-numbers)

	// NOLINTBEGIN(*-magic-numbers)
	void
	Manager::listenerProperties (std::array< ALfloat, 12 > & properties) const noexcept // NOLINT(*-magic-numbers)
	{
		if ( m_flags[Usable] )
		{
			alGetListenerfv(AL_POSITION, properties.data());
			alGetListenerfv(AL_ORIENTATION, properties.data() + 3);
			alGetListenerfv(AL_VELOCITY, properties.data() + 9);
		}
	}
	// NOLINTEND(*-magic-numbers)

	bool
	Manager::state () const noexcept
	{
		return m_flags[MainState];
	}

	std::string
	Manager::getAPIInformation () noexcept
	{
		if ( !m_flags[Usable] )
		{
			return "API not loaded !";
		}

		std::stringstream output{};

		/* OpenAL basic information. */
		output <<
			"OpenAL API information" "\n"
			" - Vendor : " << alGetString(AL_VENDOR) << "\n"
			" - Renderer : " << alGetString(AL_RENDERER) << "\n"
			" - Version : " << alGetString(AL_VERSION) << "\n"
			" - ALC Version : " << this->getALCVersionString() << "\n"
			" - EFX Version : " << this->getEFXVersionString() << "\n";

		/* OpenAL extensions. */
		{
			auto extensions = String::explode(alGetString(AL_EXTENSIONS), ' ', false);

			if ( extensions.empty() )
			{
				output << "No AL extension available !" "\n";
			}
			else
			{
				output << "Available AL extensions :" "\n";

				for ( const auto & extension : extensions )
				{
					output << " - " << extension << '\n';
				}
			}
		}

		/* Advanced information via ALC. */
		output << "ALC information" "\n";

		/* ALC Capabilities (read before) */
		for ( const auto & pair : m_contextAttributes )
		{
			output << " - " << alcKeyToLabel(pair.first) << " : " << pair.second << "\n";
		}

		/* ALC extensions */
		{
			auto extensions = String::explode(alcGetString(nullptr, ALC_EXTENSIONS), ' ', false);

			if ( extensions.empty() )
			{
				output << "No ALC extension available !" "\n";
			}
			else
			{
				output << "Available ALC extensions :" "\n";

				for ( const auto & extension : extensions )
				{
					output << " - " << extension << '\n';
				}
			}
		}

		return output.str();
	}

	std::vector< std::string >
	Manager::getDeviceName (const ALCchar * list) noexcept
	{
		std::vector< std::string > devices{};

		if ( list != nullptr )
		{
			while ( std::strlen(list) > 0 )
			{
				devices.emplace_back(list);

				list += std::strlen(list) + 1; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
			}
		}

		return devices;
	}

	void
	Manager::queryDevices () noexcept
	{
		const ALCchar * devices = alcGetString(nullptr, ALC_DEVICE_SPECIFIER);

		if ( devices != nullptr )
		{
			while ( std::strlen(devices) > 0 )
			{
				m_availableAudioDevices.emplace_back(devices);

				devices += std::strlen(devices) + 1; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
			}

			std::cout << "[OpenAL] Devices :" "\n";

			for ( const auto & deviceName : m_availableAudioDevices )
			{
				std::cout << " - " << deviceName << '\n';
			}

			std::cout << "[OpenAL] Default device : " << alcGetString(nullptr, ALC_DEFAULT_DEVICE_SPECIFIER) << '\n';
		}

		if ( alcIsExtensionPresent(nullptr, "ALC_ENUMERATE_ALL_EXT") == ALC_TRUE )
		{
			devices = alcGetString(nullptr, ALC_ALL_DEVICES_SPECIFIER);

			if ( devices != nullptr )
			{
				std::cout << "[OpenAL] All devices :\n";

				while ( std::strlen(devices) > 0 )
				{
					std::cout << " - " << devices << '\n';

					devices += std::strlen(devices) + 1; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
				}

				std::cout << "[OpenAL] Default all devices : " << alcGetString(nullptr, ALC_DEFAULT_ALL_DEVICES_SPECIFIER) << '\n';
			}
		}

		alcFlushErrors(m_device);
	}

	std::vector< ALCint >
	Manager::getDeviceAttributes () const noexcept
	{
		std::vector< ALCint > attributes{};

		ALCint size = 0;

		alcGetIntegerv(m_device, ALC_ATTRIBUTES_SIZE, 1, &size);

		if ( size > 0 )
		{
			attributes.resize(size);

			alcGetIntegerv(m_device, ALC_ALL_ATTRIBUTES, size, attributes.data());
		}

		if ( alcGetErrors(m_device, "alcGetIntegerv", __FILE__, __LINE__) )
		{
			Tracer::warning(ClassId, "Unable to fetch device attributes correctly !");
		}

		return attributes;
	}

	bool
	Manager::saveContextAttributes () noexcept
	{
		const auto attributes = this->getDeviceAttributes();

		if ( attributes.empty() )
		{
			Tracer::error(ClassId, "Unable to retrieve context attributes !");

			return false;
		}

		for ( size_t index = 0; index < attributes.size(); index += 2 )
		{
			if ( attributes[index] == 0 )
			{
				break;
			}

			m_contextAttributes[attributes[index]] = attributes[index+1];
		}

		/* Forgotten device attributes... */
		// NOLINTBEGIN(*-magic-numbers)
		const std::array< ALint, 9 > keys{
			ALC_FORMAT_CHANNELS_SOFT, // Not handled on Linux platform
			ALC_FORMAT_TYPE_SOFT, // Not handled on Linux platform
			ALC_NUM_HRTF_SPECIFIERS_SOFT,
			ALC_CONNECTED,
			0x1997,//ALC_AMBISONIC_LAYOUT_SOFT, Not handled and tokenized on Linux platform
			0x1998,//ALC_AMBISONIC_SCALING_SOFT, Not handled and tokenized on Linux platform
			0x1999,//ALC_AMBISONIC_ORDER_SOFT, Not handled and tokenized on Linux platform
			0x199B,//ALC_MAX_AMBISONIC_ORDER_SOFT, Not handled and tokenized on Linux platform
			0x19AC//ALC_OUTPUT_MODE_SOFT, Not handled and tokenized on Linux platform
		};
		// NOLINTEND(*-magic-numbers)

		for ( auto key : keys )
		{
			ALCint value = 0;

			alcGetIntegerv(m_device, key, 1, &value);

			if ( alcGetErrors(m_device, "alcGetIntegerv", __FILE__, __LINE__) )
			{
				Tracer::warning(ClassId, Blob() << "Unable to fetch device attribute 0x" << std::hex << key << " !");

				continue;
			}

			m_contextAttributes[key] = value;
		}

		return true;
	}
}
