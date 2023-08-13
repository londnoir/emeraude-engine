/*
 * Emeraude/Scenes/LocatableInterface.cpp
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

#include "LocatableInterface.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Libraries::Math;

	void
	LocatableInterface::moveTo (const Vector< 3, float > & position, TransformSpace transformSpace) noexcept
	{
		switch ( transformSpace )
		{
			case TransformSpace::Local :
				this->getWritableLocalCoordinates().translateAlongLocalAxis(position);
				break;

			case TransformSpace::Parent :
			case TransformSpace::World :
				this->getWritableLocalCoordinates().setPosition(position);
				break;
		}
	}

	void
	LocatableInterface::moveOnXAxisTo (float xPosition, TransformSpace transformSpace) noexcept
	{
		switch ( transformSpace )
		{
			case TransformSpace::Local :
				this->getWritableLocalCoordinates().translateAlongLocalXAxis(xPosition);
				break;

			case TransformSpace::Parent :
			case TransformSpace::World :
				this->getWritableLocalCoordinates().setXPosition(xPosition);
				break;
		}
	}

	void
	LocatableInterface::moveOnYAxisTo (float yPosition, TransformSpace transformSpace) noexcept
	{
		switch ( transformSpace )
		{
			case TransformSpace::Local :
				this->getWritableLocalCoordinates().translateAlongLocalYAxis(yPosition);
				break;

			case TransformSpace::Parent :
			case TransformSpace::World :
				this->getWritableLocalCoordinates().setYPosition(yPosition);
				break;
		}
	}

	void
	LocatableInterface::moveOnZAxisTo (float zPosition, TransformSpace transformSpace) noexcept
	{
		switch ( transformSpace )
		{
			case TransformSpace::Local :
				this->getWritableLocalCoordinates().translateAlongLocalZAxis(zPosition);
				break;

			case TransformSpace::Parent :
			case TransformSpace::World :
				this->getWritableLocalCoordinates().setZPosition(zPosition);
				break;
		}
	}

	void
	LocatableInterface::moveBy (const Vector< 3, float > & distance, TransformSpace transformSpace) noexcept
	{
		switch ( transformSpace )
		{
			case TransformSpace::Local :
				this->getWritableLocalCoordinates().translateAlongLocalAxis(distance);
				break;

			case TransformSpace::Parent :
			case TransformSpace::World :
				this->getWritableLocalCoordinates().translateAlongWorldAxis(distance);
				break;
		}
	}

	void
	LocatableInterface::moveOnXAxisBy (float xDistance, TransformSpace transformSpace) noexcept
	{
		switch ( transformSpace )
		{
			case TransformSpace::Local :
				this->getWritableLocalCoordinates().translateAlongLocalXAxis(xDistance);
				break;

			case TransformSpace::Parent :
			case TransformSpace::World :
				this->getWritableLocalCoordinates().translateAlongWorldXAxis(xDistance);
				break;
		}
	}

	void
	LocatableInterface::moveOnYAxisBy (float yDistance, TransformSpace transformSpace) noexcept
	{
		switch ( transformSpace )
		{
			case TransformSpace::Local :
				this->getWritableLocalCoordinates().translateAlongLocalYAxis(yDistance);
				break;

			case TransformSpace::Parent :
			case TransformSpace::World :
				this->getWritableLocalCoordinates().translateAlongWorldYAxis(yDistance);
				break;
		}
	}

	void
	LocatableInterface::moveOnZAxisBy (float zDistance, TransformSpace transformSpace) noexcept
	{
		switch ( transformSpace )
		{
			case TransformSpace::Local :
				this->getWritableLocalCoordinates().translateAlongLocalZAxis(zDistance);
				break;

			case TransformSpace::Parent :
			case TransformSpace::World :
				this->getWritableLocalCoordinates().translateAlongWorldZAxis(zDistance);
				break;
		}
	}

	void
	LocatableInterface::rotate (float radian, const Vector< 3, float > & axis, TransformSpace transformSpace) noexcept
	{
		switch ( transformSpace )
		{
			case TransformSpace::Local :
				/* NOTE: special cases for straight axis. */
				if ( axis == Vector< 3, float >::positiveX() )
					this->getWritableLocalCoordinates().pitch(radian);
				else if ( axis == Vector< 3, float >::positiveY() )
					this->getWritableLocalCoordinates().yaw(radian);
				else if ( axis == Vector< 3, float >::positiveZ() )
					this->getWritableLocalCoordinates().roll(radian);
				else
					this->getWritableLocalCoordinates().rotate(radian, (this->localCoordinates().modelMatrix() * Vector< 4, float >(axis, 0.0F)).toVector3());
				break;

			case TransformSpace::Parent :
			case TransformSpace::World :
				this->getWritableLocalCoordinates().rotate(radian, axis);
				break;
		}
	}

	void
	LocatableInterface::scale (const Vector< 3, float > & factor) noexcept
	{
		this->getWritableLocalCoordinates().setScaleVector(factor);
	}

	void
	LocatableInterface::scale (float xFactor, float yFactor, float zFactor) noexcept
	{
		this->getWritableLocalCoordinates().setScaleVector(xFactor, yFactor, zFactor);
	}

	void
	LocatableInterface::scale (float factor) noexcept
	{
		this->getWritableLocalCoordinates().setScaleVector(factor);
	}

	void
	LocatableInterface::lookAt (const Libraries::Math::Vector< 3, float > & target) noexcept
	{
		this->getWritableLocalCoordinates().lookAt(target);
	}

	void
	LocatableInterface::pointTo (const Libraries::Math::Vector< 3, float > & target) noexcept
	{
		this->getWritableLocalCoordinates().pointTo(target);
	}
}
