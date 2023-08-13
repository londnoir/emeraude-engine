/*
 * Emeraude/Scenes/Microphone.hpp
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

/* C/C++ standard libraries */
#include <string>
#include <sstream>
#include <iostream>

/* Local inclusions for inheritances. */
#include "AbstractComponent.hpp"
#include "MasterControl/AbstractVirtualAudioDevice.hpp"

namespace Emeraude::Scenes
{
	/**
	 * @brief This class defines a physical point of capturing sound in the world.
	 * Like ears from a creature or microphone from a camera.
	 * @extends Emeraude::Scenes::AbstractComponent The base class for each entity component.
	 * @extends Emeraude::MasterControl::AbstractVirtualAudioDevice This is a virtual audio device.
	 */
	class Microphone final : public AbstractComponent, public MasterControl::AbstractVirtualAudioDevice
	{
		public:

			/**
			 * @brief Constructs a microphone.
			 * @param name The name of the component.
			 * @param parentEntity A reference to the parent entity.
			 */
			Microphone (const std::string & name, const AbstractEntity & parentEntity) noexcept;

			/** @copydoc Emeraude::Scenes::AbstractComponent::getComponentType() */
			[[nodiscard]]
			const char * getComponentType () const noexcept override;

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const Microphone & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend std::string to_string (const Microphone & obj) noexcept;

		private:

			/** @copydoc Emeraude::Scenes::AbstractComponent::move() */
			void move () noexcept override;

			/** @copydoc Emeraude::Scenes::AbstractComponent::processLogics() */
			void processLogics (const Scene & scene, size_t cycle) noexcept override;

			/** @copydoc Emeraude::MasterControl::AbstractVirtualDevice::updateDeviceFromCoordinates() */
			void updateDeviceFromCoordinates (const Libraries::Math::Coordinates< float > & worldCoordinates, const Libraries::Math::Vector< 3, float > & worldVelocity) noexcept override;

			/** @copydoc Emeraude::MasterControl::AbstractVirtualAudioDevice::onTargetConnected() */
			void onTargetConnected (AbstractVirtualAudioDevice * targetDevice) noexcept override;

			/** @copydoc Emeraude::Animations::AnimatableInterface::playAnimation() */
			bool playAnimation (Animations::id_t id, const Libraries::Variant & value) noexcept override;
	};
}
