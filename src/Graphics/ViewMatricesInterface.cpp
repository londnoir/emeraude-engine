/*
 * src/Graphics/ViewMatricesInterface.cpp
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

#include "ViewMatricesInterface.hpp"

/* Local inclusions. */
#include "Graphics/Renderer.hpp"

namespace Emeraude::Graphics
{
	static constexpr auto TracerTag{"ViewMatricesInterface"};

	std::shared_ptr< Vulkan::DescriptorSetLayout >
	ViewMatricesInterface::getDescriptorSetLayout () const noexcept
	{
		auto & layoutManager = Renderer::instance()->layoutManager();

		/* NOTE: Create a unique identifier for the descriptor set layout. */
		const std::string UUID{TracerTag};

		auto descriptorSetLayout = layoutManager.getDescriptorSetLayout(UUID);

		if ( descriptorSetLayout == nullptr )
		{
			descriptorSetLayout = layoutManager.prepareNewDescriptorSetLayout(UUID);
			descriptorSetLayout->setIdentifier(TracerTag, "Matrices", "DescriptorSetLayout");
			descriptorSetLayout->declareUniformBuffer(0, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT);

			if ( !layoutManager.createDescriptorSetLayout(descriptorSetLayout) )
			{
				return nullptr;
			}
		}

		return descriptorSetLayout;
	}
}
