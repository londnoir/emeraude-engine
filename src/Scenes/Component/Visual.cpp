/*
 * src/Scenes/Component/Visual.cpp
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

#include "Visual.hpp"

/* STL inclusions. */
#include <any>
#include <memory>
#include <string>

/* Local inclusions. */
#include "Abstract.hpp"
#include "Animations/Types.hpp"
#include "Graphics/RenderableInstance/Unique.hpp"
#include "Libs/Math/CartesianFrame.hpp"
#include "Libs/Math/Cuboid.hpp"
#include "Libs/Math/Sphere.hpp"
#include "Libs/ObserverTrait.hpp"
#include "Libs/Variant.hpp"
#include "Scenes/Scene.hpp"

namespace EmEn::Scenes::Component
{
	using namespace EmEn::Libs;
	using namespace EmEn::Libs::Math;
	using namespace Animations;
	using namespace Physics;
	using namespace Graphics;

	Visual::Visual (const std::string & name, const AbstractEntity & parentEntity, const std::shared_ptr< Renderable::Interface > & renderable) noexcept
		: Abstract(name, parentEntity),
		m_renderableInstance(std::make_shared< RenderableInstance::Unique >(renderable, this->getWorldCoordinates(), renderable->isSprite() ? RenderableInstance::FacingCamera : 0))
	{
		this->observe(m_renderableInstance.get());
	}

	std::shared_ptr< Graphics::RenderableInstance::Abstract >
	Visual::getRenderableInstance () const noexcept
	{
		return m_renderableInstance;
	}

	const char *
	Visual::getComponentType () const noexcept
	{
		return ClassId;
	}

	const Cuboid< float > &
	Visual::boundingBox () const noexcept
	{
		return m_renderableInstance->renderable()->boundingBox();
	}

	const Sphere< float > &
	Visual::boundingSphere () const noexcept
	{
		return m_renderableInstance->renderable()->boundingSphere();
	}

	void
	Visual::move (const CartesianFrame< float > & worldCoordinates) noexcept
	{
		m_renderableInstance->updateModelMatrix(worldCoordinates);
	}

	void
	Visual::processLogics (const Scene & scene) noexcept
	{
		if ( m_renderableInstance->isBroken() )
		{
			return;
		}

		if ( m_renderableInstance->isAnimated() )
		{
			m_renderableInstance->updateFrameIndex(scene.lifetimeMS() - this->parentEntity().birthTime());
		}

		this->updateAnimations(scene.cycle());
	}

	bool
	Visual::shouldRemove () const noexcept
	{
		return m_renderableInstance->isBroken();
	}

	bool
	Visual::playAnimation (uint8_t animationID, const Libs::Variant & value, size_t cycle) noexcept
	{
		return false;
	}

	bool
	Visual::onNotification (const ObservableTrait * observable, int notificationCode, const std::any & /*data*/) noexcept
	{
		if ( observable == m_renderableInstance.get() )
		{
			switch ( notificationCode )
			{
				case RenderableInstance::Abstract::ReadyToSetupOnGPU :
					this->notify(ComponentContentModified);
					break;

				default:
					break;
			}

			return true;
		}

		/* NOTE: Auto-forget */
		return false;
	}
}
