/*
 * src/Audio/HardwareOutput.hpp
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

#pragma once

/* STL inclusions. */
#include <string>

/* Local inclusions for inheritances. */
#include "MasterControl/AbstractVirtualAudioDevice.hpp"

/* Local inclusions for usages. */
#include "Libraries/Math/CartesianFrame.hpp"
#include "Libraries/Math/Vector.hpp"
#include "Audio/Manager.hpp"

namespace Emeraude::Audio
{
	/**
	 * @brief The hardware output class.
	 * @extends Emeraude::MasterControl::AbstractVirtualAudioDevice This is a virtual audio device.
	 */
	class HardwareOutput final : public MasterControl::AbstractVirtualAudioDevice
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"HardwareOutput"};

			/**
			 * @brief Constructs the hardware output.
			 * @param name A reference to a name.
			 * @param audioManager A reference to the audioManager.
			 */
			HardwareOutput (const std::string & name, Audio::Manager & audioManager) noexcept;

		private:

			/** @copydoc Emeraude::MasterControl::AbstractVirtualDevice::updateDeviceFromCoordinates() */
			void updateDeviceFromCoordinates (const Libraries::Math::CartesianFrame< float > & worldCoordinates, const Libraries::Math::Vector< 3, float > & worldVelocity) noexcept override;

			Audio::Manager * m_audioManager{nullptr};
	};
}
