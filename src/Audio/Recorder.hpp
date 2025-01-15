/*
 * src/Audio/Recorder.hpp
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
#include <string>

/* Local inclusions for inheritances. */
#include "MasterControl/AbstractVirtualAudioDevice.hpp"

/* Local inclusions for usages. */
#include "Libraries/Math/CartesianFrame.hpp"
#include "Libraries/Math/Vector.hpp"

/* https://kcat.strangesoft.net/openal-extensions/SOFT_loopback.txt */
namespace Emeraude::Audio
{
	/**
	 * @brief The audio recorder class.
	 * @extends Emeraude::MasterControl::AbstractVirtualAudioDevice This is a virtual audio device.
	 */
	class Recorder final : public MasterControl::AbstractVirtualAudioDevice
	{
		public:

			/**
			 * @brief Constructs a recorder.
			 * @param name A reference to a name.
			 */
			explicit Recorder (const std::string & name) noexcept;

		private:

			/** @copydoc Emeraude::MasterControl::AbstractVirtualDevice::updateDeviceFromCoordinates() */
			void updateDeviceFromCoordinates (const Libraries::Math::CartesianFrame< float > & worldCoordinates, const Libraries::Math::Vector< 3, float > & worldVelocity) noexcept override;
	};
}
