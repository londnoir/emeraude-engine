/*
 * src/MasterControl/AbstractVirtualAudioDevice.cpp
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

#include "AbstractVirtualAudioDevice.hpp"

/* Local inclusions. */
#ifdef DEBUG
	#include "Tracer.hpp"
#endif

namespace Emeraude::MasterControl
{
	using namespace Libraries;

#ifdef DEBUG
	static constexpr auto TracerTag{"VirtualAudioDevice"};
#endif

	AbstractVirtualAudioDevice::AbstractVirtualAudioDevice (const std::string & name, ConnexionType allowedConnexionType) noexcept
		: AbstractVirtualDevice(name, DeviceType::Audio, allowedConnexionType)
	{

	}

	void
	AbstractVirtualAudioDevice::onSourceConnected (AbstractVirtualDevice * sourceDevice) noexcept
	{
		auto * sourceAudioDevice = dynamic_cast< AbstractVirtualAudioDevice * >(sourceDevice);

		if ( sourceAudioDevice != nullptr )
		{
			this->onSourceConnected(sourceAudioDevice);
		}
	}

	void
	AbstractVirtualAudioDevice::onTargetConnected (AbstractVirtualDevice * targetDevice) noexcept
	{
		auto * targetAudioDevice = dynamic_cast< AbstractVirtualAudioDevice * >(targetDevice);

		if ( targetAudioDevice != nullptr )
		{
			this->onTargetConnected(targetAudioDevice);
		}
	}

	void
	AbstractVirtualAudioDevice::onSourceDisconnected (AbstractVirtualDevice * sourceDevice) noexcept
	{
		auto * sourceAudioDevice = dynamic_cast< AbstractVirtualAudioDevice * >(sourceDevice);

		if ( sourceAudioDevice != nullptr )
		{
			this->onSourceDisconnected(sourceAudioDevice);
		}
	}

	void
	AbstractVirtualAudioDevice::onTargetDisconnected (AbstractVirtualDevice * targetDevice) noexcept
	{
		auto * targetAudioDevice = dynamic_cast< AbstractVirtualAudioDevice * >(targetDevice);

		if ( targetAudioDevice != nullptr )
		{
			this->onTargetDisconnected(targetAudioDevice);
		}
	}

	void
	AbstractVirtualAudioDevice::onSourceConnected (AbstractVirtualAudioDevice * sourceDevice) noexcept
	{
#ifdef DEBUG
		TraceInfo{TracerTag} << "The virtual source audio device '" << sourceDevice->id() << "' connected !";
#endif
	}

	void
	AbstractVirtualAudioDevice::onTargetConnected (AbstractVirtualAudioDevice * targetDevice) noexcept
	{
#ifdef DEBUG
		TraceInfo{TracerTag} << "The virtual source audio target '" << targetDevice->id() << "' connected !";
#endif
	}

	void
	AbstractVirtualAudioDevice::onSourceDisconnected (AbstractVirtualAudioDevice * sourceDevice) noexcept
	{
#ifdef DEBUG
		TraceInfo{TracerTag} << "The virtual source audio device '" << sourceDevice->id() << "' disconnected !";
#endif
	}

	void
	AbstractVirtualAudioDevice::onTargetDisconnected (AbstractVirtualAudioDevice * targetDevice) noexcept
	{
#ifdef DEBUG
		TraceInfo{TracerTag} << "The virtual source audio target '" << targetDevice->id() << "' disconnected !";
#endif
	}
}
