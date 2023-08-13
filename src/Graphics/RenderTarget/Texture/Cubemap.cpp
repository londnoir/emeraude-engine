/*
 * Emeraude/Graphics/RenderTarget/Texture/Cubemap.cpp
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

#include "Cubemap.hpp"

/* Local inclusions */
#include "Resources/Manager.hpp"
#include "Tracer.hpp"

/* Defining the resource manager class id. */
template<>
const char * const Emeraude::Resources::Container< Emeraude::Graphics::RenderTarget::Texture::Cubemap >::ClassId{"RenderToCubemapContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t Emeraude::Resources::Container< Emeraude::Graphics::RenderTarget::Texture::Cubemap >::ClassUID{Observable::getClassUID()};

namespace Emeraude::Graphics::RenderTarget::Texture
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Vulkan;
	using namespace Saphir;
	using namespace Saphir::Keys;

	const size_t Cubemap::ClassUID{Observable::getClassUID()};

	Cubemap::Cubemap (const std::string & name, uint32_t size, uint32_t colorCount) noexcept
		: Abstract(name, {}, {size, size, 1}, RenderType::CubicView)
	{

	}

	Cubemap::Cubemap (const std::string & name) noexcept
		: Cubemap(name, 64, 4)
	{
		Tracer::warning(ClassId, "This resource are not intended to build that way !");
	}

	float
	Cubemap::aspectRatio () const noexcept
	{
		return 1.0F;
	}

	bool
	Cubemap::isCubemap () const noexcept
	{
		return true;
	}

	bool
	Cubemap::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	const char *
	Cubemap::classLabel () const noexcept
	{
		return ClassId;
	}

	const ViewMatricesInterface &
	Cubemap::viewMatrices () const noexcept
	{
		return m_viewMatrices;
	}

	ViewMatricesInterface &
	Cubemap::viewMatrices () noexcept
	{
		return m_viewMatrices;
	}

	void
	Cubemap::updateDeviceFromCoordinates (const Coordinates< float > & worldCoordinates, const Vector< 3, float > & worldVelocity) noexcept
	{
		m_viewMatrices.updateViewCoordinates(worldCoordinates, worldVelocity);
	}

	void
	Cubemap::updateProperties (bool isPerspectiveProjection, float distance, float fovOrNear) noexcept
	{
		const auto & extent = this->extent();

		if ( isPerspectiveProjection )
		{
			m_viewMatrices.updatePerspectiveViewProperties(static_cast< float >(extent.width), static_cast< float >(extent.height), distance, fovOrNear);
		}
		else
		{
			m_viewMatrices.updateOrthographicViewProperties(static_cast< float >(extent.width), static_cast< float >(extent.height), distance, fovOrNear);
		}
	}

	void
	Cubemap::onSourceConnected (AbstractVirtualVideoDevice * /*sourceDevice*/) noexcept
	{
		m_viewMatrices.create(*this);
	}

	void
	Cubemap::onSourceDisconnected (AbstractVirtualVideoDevice * /*sourceDevice*/) noexcept
	{
		m_viewMatrices.destroy();
	}

	std::shared_ptr< Cubemap >
	Cubemap::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->renderToCubemaps().getResource(resourceName, directLoad);
	}

	std::shared_ptr< Cubemap >
	Cubemap::getDefault () noexcept
	{
		return Resources::Manager::instance()->renderToCubemaps().getDefaultResource();
	}

	Saphir::Declaration::UniformBlock
	Cubemap::getViewUniformBlock (uint32_t set, uint32_t binding) noexcept
	{
		Declaration::Structure structure{Structs::CubemapFace, UniformBlocks::Component::Instance};
		structure.addMember(Declaration::VariableType::Matrix4, UniformBlocks::Component::ViewMatrix);
		structure.addMember(Declaration::VariableType::Matrix4, UniformBlocks::Component::ProjectionMatrix);
		structure.addMember(Declaration::VariableType::Matrix4, UniformBlocks::Component::ViewProjectionMatrix);
		structure.addMember(Declaration::VariableType::FloatVector4, UniformBlocks::Component::PositionWorldSpace);
		structure.addMember(Declaration::VariableType::FloatVector4, UniformBlocks::Component::Velocity);
		structure.addMember(Declaration::VariableType::FloatVector4, UniformBlocks::Component::ViewProperties);
		structure.addMember(Declaration::VariableType::FloatVector4, "_padding");

		Declaration::UniformBlock block{set, binding, Declaration::MemoryLayout::Std140, UniformBlocks::View, BufferBackedBlocks::View};
		block.addArrayMember(structure, 6);

		return block;
	}
}
