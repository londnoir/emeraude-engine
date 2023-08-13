/*
 * Emeraude/MasterControl/AbstractVirtualVideoDevice.cpp
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

#include "AbstractVirtualVideoDevice.hpp"

/* Local inclusions. */
#ifdef DEBUG
	#include "Tracer.hpp"
#endif

namespace Emeraude::MasterControl
{
	using namespace Libraries;

#ifdef DEBUG
	constexpr auto TracerTag{"VirtualVideoDevice"};
#endif

	AbstractVirtualVideoDevice::AbstractVirtualVideoDevice (const std::string & name, ConnexionType allowedConnexionType) noexcept
		: AbstractVirtualDevice(name, DeviceType::Video, allowedConnexionType)
	{

	}

	void
	AbstractVirtualVideoDevice::onSourceConnected (AbstractVirtualDevice * sourceDevice) noexcept
	{
		auto * sourceVideoDevice = dynamic_cast< AbstractVirtualVideoDevice * >(sourceDevice);

		if ( sourceVideoDevice != nullptr )
		{
			this->onSourceConnected(sourceVideoDevice);
		}
	}

	void
	AbstractVirtualVideoDevice::onTargetConnected (AbstractVirtualDevice * targetDevice) noexcept
	{
		auto * targetVideoDevice = dynamic_cast< AbstractVirtualVideoDevice * >(targetDevice);

		if ( targetVideoDevice != nullptr )
		{
			this->onTargetConnected(targetVideoDevice);
		}
	}

	void
	AbstractVirtualVideoDevice::onSourceDisconnected (AbstractVirtualDevice * sourceDevice) noexcept
	{
		auto * sourceVideoDevice = dynamic_cast< AbstractVirtualVideoDevice * >(sourceDevice);

		if ( sourceVideoDevice != nullptr )
		{
			this->onSourceDisconnected(sourceVideoDevice);
		}
	}

	void
	AbstractVirtualVideoDevice::onTargetDisconnected (AbstractVirtualDevice * targetDevice) noexcept
	{
		auto * targetVideoDevice = dynamic_cast< AbstractVirtualVideoDevice * >(targetDevice);

		if ( targetVideoDevice != nullptr )
		{
			this->onTargetDisconnected(targetVideoDevice);
		}
	}

	void
	AbstractVirtualVideoDevice::onSourceConnected (AbstractVirtualVideoDevice * sourceDevice) noexcept
	{
#ifdef DEBUG
		TraceInfo{TracerTag} << "The virtual source video device '" << sourceDevice->id() << "' connected !";
#endif
	}

	void
	AbstractVirtualVideoDevice::onTargetConnected (AbstractVirtualVideoDevice * targetDevice) noexcept
	{
#ifdef DEBUG
		TraceInfo{TracerTag} << "The virtual source video target '" << targetDevice->id() << "' connected !";
#endif
	}

	void
	AbstractVirtualVideoDevice::onSourceDisconnected (AbstractVirtualVideoDevice * sourceDevice) noexcept
	{
#ifdef DEBUG
		TraceInfo{TracerTag} << "The virtual source video device '" << sourceDevice->id() << "' disconnected !";
#endif
	}

	void
	AbstractVirtualVideoDevice::onTargetDisconnected (AbstractVirtualVideoDevice * targetDevice) noexcept
	{
#ifdef DEBUG
		TraceInfo{TracerTag} << "The virtual source video target '" << targetDevice->id() << "' disconnected !";
#endif
	}
}
