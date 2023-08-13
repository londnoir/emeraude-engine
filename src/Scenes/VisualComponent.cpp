/*
 * Emeraude/Scenes/VisualComponent.cpp
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

#include "VisualComponent.hpp"

/* Local inclusions. */
#include "AbstractEntity.hpp"
#include "Resources/ResourceTrait.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Animations;
	using namespace Physics;
	using namespace Graphics;

	VisualComponent::VisualComponent (const std::string & name, const AbstractEntity & parentEntity, const std::shared_ptr< Renderable::Interface > & renderable) noexcept
		: AbstractComponent(name, parentEntity), m_renderableInstance(std::make_shared< RenderableInstance::Unique >(renderable, this->getWorldCoordinates()))
	{

	}

	const RenderableInstance::Abstract *
	VisualComponent::getRenderableInstance () const noexcept
	{
		return m_renderableInstance.get();
	}

	RenderableInstance::Abstract *
	VisualComponent::getRenderableInstance () noexcept
	{
		return m_renderableInstance.get();
	}

	const char *
	VisualComponent::getComponentType () const noexcept
	{
		return "VisualComponent";
	}

	void
	VisualComponent::move () noexcept
	{
		m_renderableInstance->updateWithModel(this->getWorldCoordinates());
	}

	void
	VisualComponent::processLogics (const Scene &, size_t cycle) noexcept
	{
		if ( m_renderableInstance->isBroken() )
		{
			this->notify(RemoveBrokenComponent);

			return;
		}

		this->updateAnimations(cycle);
	}

	bool
	VisualComponent::playAnimation (Animations::id_t, const Variant &) noexcept
	{
		return false;
	}
}
