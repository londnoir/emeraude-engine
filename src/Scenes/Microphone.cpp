/*
 * Emeraude/Scenes/Microphone.cpp
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

#include "Microphone.hpp"

/* Local inclusions */
#include "Audio/Manager.hpp"
#include "Audio/Utility.hpp"
#include "Node.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Animations;
	using namespace Audio;

	Microphone::Microphone (const std::string & name, const AbstractEntity & parentEntity) noexcept
		: AbstractComponent(name, parentEntity), MasterControl::AbstractVirtualAudioDevice(name, MasterControl::ConnexionType::Output)
	{
		auto * audioManager = Manager::instance();

		if ( audioManager != nullptr && audioManager->usable() )
		{
			audioManager->setMetersPerUnit(Physics::SI::Meter< float >);

			audioManager->setMasterVolume(0.75F); // NOLINT(*-magic-numbers)

			audioManager->setDistanceModel(Manager::DistanceModel::LinearClamped);
		}
	}

	const char *
	Microphone::getComponentType () const noexcept
	{
		return "Microphone";
	}

	void
	Microphone::move () noexcept
	{
		this->updateDeviceFromCoordinates(this->getWorldCoordinates(), this->getWorldVelocity());
	}

	void
	Microphone::processLogics (const Scene & /*scene*/, size_t /*cycle*/) noexcept
	{
		this->updateDeviceFromCoordinates(this->getWorldCoordinates(), this->getWorldVelocity());
	}

	void
	Microphone::updateDeviceFromCoordinates (const Coordinates< float > & worldCoordinates, const Vector< 3, float > & worldVelocity) noexcept
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
	Microphone::playAnimation (Animations::id_t /*identifier*/, const Variant & /*value*/) noexcept
	{
		return false;
	}

	std::ostream &
	operator<< (std::ostream & out, const Microphone & /*microphone*/)
	{
		// NOLINTBEGIN(*-magic-numbers)
		std::array< ALfloat, 12 > properties{0};

		Manager::instance()->listenerProperties(properties);

		return out <<
			"Audio Listener information" "\n"
			"Position: " << properties[0] << ", " << properties[1] << ", " << properties[2] << "\n"
			"Forward: " << properties[3] << ", " << properties[4] << ", " << properties[5] << "\n"
			"Upward: " << properties[6] << ", " << properties[7] << ", " << properties[8] << "\n"
			"Velocity: " << properties[9] << ", " << properties[10] << ", " << properties[11] << '\n';
		// NOLINTEND(*-magic-numbers)
	}

	std::string
	to_string (const Microphone & obj) noexcept
	{
		return (std::stringstream{} << obj).str();
	}
}
