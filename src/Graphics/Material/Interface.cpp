/*
 * src/Graphics/Material/Interface.cpp
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

#include "Interface.hpp"

/* Local inclusions. */
#include "Helpers.hpp"
#include "Graphics/Renderer.hpp"
#include "Saphir/Declaration/UniformBlock.hpp"
#include "Tracer.hpp"
#include "Libs/FastJSON.hpp"
#include "Vulkan/SharedUBOManager.hpp"

namespace EmEn::Graphics::Material
{
	using namespace EmEn::Libs;

	constexpr auto TracerTag{"MaterialInterface"};

	Interface::Interface (const std::string & name, uint32_t resourceFlagBits) noexcept
		: ResourceTrait(name, resourceFlagBits)
	{

	}

	void
	Interface::enableBlendingFromJson (const Json::Value & data) noexcept
	{
		const auto blendingModeStr = FastJSON::getString(data, JKBlendingMode, NormalBlendingString);

		if ( blendingModeStr.empty() )
		{
			return;
		}

		const auto blendingMode = to_BlendingMode(blendingModeStr);

		if ( blendingMode == BlendingMode::None )
		{
			return;
		}

		this->enableBlending(blendingMode);
	}

	std::shared_ptr< Vulkan::SharedUniformBuffer >
	Interface::getSharedUniformBuffer (Renderer & renderer, const std::string & identifier) const noexcept
	{
		auto sharedUniformBuffer = renderer.sharedUBOManager().getSharedUniformBuffer(identifier);

		if ( sharedUniformBuffer != nullptr )
		{
			return sharedUniformBuffer;
		}

		const auto size = this->getUniformBlock(0, 0).bytes();

		return renderer.sharedUBOManager().createSharedUniformBuffer(identifier, size);
	}

	bool
	Interface::onDependenciesLoaded () noexcept
	{
		auto * renderer = Renderer::instance();

		if ( renderer == nullptr )
		{
			TraceError{TracerTag} << "Unable to reach the graphics renderer for material resource (" << this->classLabel() << ") '" << this->name() << "' !";

			return false;
		}

		if ( !this->isCreated() && !this->create(*renderer) )
		{
			TraceError{TracerTag} << "Unable to load material resource (" << this->classLabel() << ") '" << this->name() << "' !";

			return false;
		}

		this->onMaterialLoaded();

		return true;
	}
}
