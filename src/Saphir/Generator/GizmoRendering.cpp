/*
 * src/Saphir/Generator/GizmoRendering.cpp
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

#include "GizmoRendering.hpp"

/* Local inclusions. */
#include "Settings.hpp"

namespace Emeraude::Saphir::Generator
{
	using namespace Libraries;
	using namespace Graphics;
	using namespace Vulkan;
	using namespace Keys;

	GizmoRendering::GizmoRendering (Settings & settings, const std::shared_ptr< const Graphics::RenderTarget::Abstract > & renderTarget) noexcept
		: Abstract(settings, ClassId, renderTarget)
	{

	}

	void
	GizmoRendering::prepareUniformSets (SetIndexes & /*setIndexes*/) noexcept
	{

	}

	bool
	GizmoRendering::onGenerateProgram (Program & /*program*/) noexcept
	{
		return false;
	}

	bool
	GizmoRendering::onGenerateProgramLayout (const SetIndexes & /*setIndexes*/, std::vector< std::shared_ptr< DescriptorSetLayout > > & /*descriptorSetLayouts*/, std::vector< VkPushConstantRange > & /*pushConstantRanges*/) noexcept
	{
		return true;
	}

	bool
	GizmoRendering::generateVertexShader (Program & /*program*/) noexcept
	{
		return false;
	}

	bool
	GizmoRendering::generateFragmentShader (Program & /*program*/) noexcept
	{
		return false;
	}

	bool
	GizmoRendering::onGraphicsPipelineConfiguration (const Program & /*program*/, GraphicsPipeline & /*graphicsPipeline*/) noexcept
	{

		return true;
	}
}
