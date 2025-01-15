/*
 * src/Scenes/StaticEntity.cpp
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

#include "StaticEntity.hpp"

/* Local inclusions. */
#include "Scenes/Scene.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Physics;

	const size_t StaticEntity::ClassUID{getClassUID(ClassId)};

	StaticEntity::StaticEntity (const std::string & name, uint32_t sceneTimeMS, const CartesianFrame< float > & coordinates) noexcept
		: AbstractEntity(name, sceneTimeMS), m_cartesianFrame(coordinates)
	{

	}

	void
	StaticEntity::scale (const Vector< 3, float > & factor, TransformSpace transformSpace) noexcept
	{
		switch ( transformSpace )
		{
			case TransformSpace::Local :
				m_cartesianFrame.setScalingFactor(factor);
				break;

			case TransformSpace::Parent :
			case TransformSpace::World :
				/* TODO: Reorient the scale vector to world. */
				break;
		}

		this->onLocationDataUpdate();
	}

	void
	StaticEntity::scale (float factor, TransformSpace transformSpace) noexcept
	{
		switch ( transformSpace )
		{
			case TransformSpace::Local :
				m_cartesianFrame.setScalingFactor(factor);
				break;

			case TransformSpace::Parent :
			case TransformSpace::World :
				/* TODO: Reorient the scale vector to world. */
				break;
		}

		this->onLocationDataUpdate();
	}

	void
	StaticEntity::scaleX (float factor, TransformSpace transformSpace) noexcept
	{
		switch ( transformSpace )
		{
			case TransformSpace::Local :
				m_cartesianFrame.setScalingXFactor(factor);
				break;

			case TransformSpace::Parent :
			case TransformSpace::World :
				/* TODO: Reorient the scale vector to world. */
				break;
		}

		this->onLocationDataUpdate();
	}

	void
	StaticEntity::scaleY (float factor, TransformSpace transformSpace) noexcept
	{
		switch ( transformSpace )
		{
			case TransformSpace::Local :
				m_cartesianFrame.setScalingYFactor(factor);
				break;

			case TransformSpace::Parent :
			case TransformSpace::World :
				/* TODO: Reorient the scale vector to world. */
				break;
		}

		this->onLocationDataUpdate();
	}

	void
	StaticEntity::scaleZ (float factor, TransformSpace transformSpace) noexcept
	{
		switch ( transformSpace )
		{
			case TransformSpace::Local :
				m_cartesianFrame.setScalingZFactor(factor);
				break;

			case TransformSpace::Parent :
			case TransformSpace::World :
				/* TODO: Reorient the scale vector to world. */
				break;
		}

		this->onLocationDataUpdate();
	}

	bool
	StaticEntity::onProcessLogics (const Scene & scene) noexcept
	{
		this->updateAnimations(scene.cycle());

		return false;
	}

	bool
	StaticEntity::onUnhandledNotification (const ObservableTrait * observable, int notificationCode, const std::any & /*data*/) noexcept
	{
		if ( observable->is(PhysicalObjectProperties::ClassUID) )
		{
			return true;
		}

#ifdef DEBUG
		/* NOTE: Don't know what is it, goodbye ! */
		TraceInfo{ClassId} <<
			"Received an unhandled notification (Code:" << notificationCode << ") from observable '" << whoIs(observable->classUID()) << "' (UID:" << observable->classUID() << ")  ! "
			"Forgetting it ...";
#endif

		return false;
	}

	bool
	StaticEntity::playAnimation (Animations::id_t /*identifier*/, const Libraries::Variant & /*value*/) noexcept
	{
		return false;
	}
}
