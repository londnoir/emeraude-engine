/*
 * src/Scenes/Component/Microphone.cpp
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

#include "Microphone.hpp"

/* STL inclusions. */
#include <string>
#include <ostream>
#include <array>

/* Local inclusions. */
#include "Scenes/AbstractEntity.hpp"

namespace Emeraude::Scenes::Component
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Animations;
	using namespace Audio;

	Microphone::Microphone (const std::string & name, const AbstractEntity & parentEntity) noexcept
		: Abstract(name, parentEntity), MasterControl::AbstractVirtualAudioDevice(name, MasterControl::ConnexionType::Output)
	{

	}

	const char *
	Microphone::getComponentType () const noexcept
	{
		return ClassId;
	}

	const Cuboid< float > &
	Microphone::boundingBox () const noexcept
	{
		return NullBoundingBox;
	}

	const Sphere< float > &
	Microphone::boundingSphere () const noexcept
	{
		return NullBoundingSphere;
	}

	void
	Microphone::move (const CartesianFrame< float > & worldCoordinates) noexcept
	{
		this->updateDeviceFromCoordinates(worldCoordinates, this->getWorldVelocity());
	}

	void
	Microphone::processLogics (const Scene & /*scene*/) noexcept
	{

	}

	bool
	Microphone::shouldRemove () const noexcept
	{
		return false;
	}

	void
	Microphone::updateDeviceFromCoordinates (const CartesianFrame< float > & worldCoordinates, const Vector< 3, float > & worldVelocity) noexcept
	{
		if ( !this->hasOutputConnected() )
		{
			return;
		}

		for ( const auto & output : this->outputs() )
		{
			output->updateDeviceFromCoordinates(worldCoordinates, worldVelocity);
		}
	}

	void
	Microphone::onTargetConnected (AbstractVirtualAudioDevice * targetDevice) noexcept
	{
		/* Initialize the target device with coordinates. */
		targetDevice->updateDeviceFromCoordinates(this->getWorldCoordinates(), this->getWorldVelocity());
	}

	bool
	Microphone::playAnimation (uint8_t animationID, const Variant & value, size_t cycle) noexcept
	{
		return false;
	}

	std::ostream &
	operator<< (std::ostream & out, const Microphone & /*microphone*/)
	{
		std::array< ALfloat, 12 > properties{0};

		Manager::instance()->listenerProperties(properties);

		return out <<
			"Audio Listener information" "\n"
			"Position: " << properties[0] << ", " << properties[1] << ", " << properties[2] << "\n"
			"Forward: " << properties[3] << ", " << properties[4] << ", " << properties[5] << "\n"
			"Upward: " << properties[6] << ", " << properties[7] << ", " << properties[8] << "\n"
			"Velocity: " << properties[9] << ", " << properties[10] << ", " << properties[11] << '\n';
	}

	std::string
	to_string (const Microphone & obj) noexcept
	{
		std::stringstream output;

		output << obj;

		return output.str();
	}
}
