/*
 * Emeraude/Graphics/RenderTarget/Texture/Texture2D.cpp
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

#include "Texture2D.hpp"

/* Local inclusions */
#include "Resources/Manager.hpp"
#include "Tracer.hpp"

/* Defining the resource manager class id. */
template<>
const char * const Emeraude::Resources::Container< Emeraude::Graphics::RenderTarget::Texture::Texture2D >::ClassId{"RenderToTexture2DContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t Emeraude::Resources::Container< Emeraude::Graphics::RenderTarget::Texture::Texture2D >::ClassUID{Observable::getClassUID()};

namespace Emeraude::Graphics::RenderTarget::Texture
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Vulkan;
	using namespace Saphir;
	using namespace Saphir::Keys;

	const size_t Texture2D::ClassUID{Observable::getClassUID()};

	Texture2D::Texture2D (const std::string & name, uint32_t width, uint32_t height, uint32_t colorCount) noexcept
		: Abstract(name, {}, {width, height, 1}, RenderType::View)
	{

	}

	Texture2D::Texture2D (const std::string & name) noexcept
		: Texture2D(name, 64, 64)
	{
		Tracer::warning(ClassId, "This resource are not intended to build that way !");
	}

	bool
	Texture2D::isCubemap () const noexcept
	{
		return false;
	}

	bool
	Texture2D::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	const char *
	Texture2D::classLabel () const noexcept
	{
		return ClassId;
	}

	const ViewMatricesInterface &
	Texture2D::viewMatrices () const noexcept
	{
		return m_viewMatrices;
	}

	ViewMatricesInterface &
	Texture2D::viewMatrices () noexcept
	{
		return m_viewMatrices;
	}

	void
	Texture2D::updateDeviceFromCoordinates (const Coordinates< float > & worldCoordinates, const Vector< 3, float > & worldVelocity) noexcept
	{
		m_viewMatrices.updateViewCoordinates(worldCoordinates, worldVelocity);
	}

	void
	Texture2D::updateProperties (bool isPerspectiveProjection, float distance, float fovOrNear) noexcept
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
	Texture2D::onSourceConnected (AbstractVirtualVideoDevice * /*sourceDevice*/) noexcept
	{
		m_viewMatrices.create(*this);
	}

	void
	Texture2D::onSourceDisconnected (AbstractVirtualVideoDevice * /*sourceDevice*/) noexcept
	{
		m_viewMatrices.destroy();
	}

	std::shared_ptr< Texture2D >
	Texture2D::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->renderToTexture2Ds().getResource(resourceName, directLoad);
	}

	std::shared_ptr< Texture2D >
	Texture2D::getDefault () noexcept
	{
		return Resources::Manager::instance()->renderToTexture2Ds().getDefaultResource();
	}

	Declaration::UniformBlock
	Texture2D::getViewUniformBlock (uint32_t set, uint32_t binding) noexcept
	{
		Declaration::UniformBlock block{set, binding, Declaration::MemoryLayout::Std140, UniformBlocks::View, BufferBackedBlocks::View};
		block.addMember(Declaration::VariableType::Matrix4, UniformBlocks::Component::ViewMatrix);
		block.addMember(Declaration::VariableType::Matrix4, UniformBlocks::Component::ProjectionMatrix);
		block.addMember(Declaration::VariableType::Matrix4, UniformBlocks::Component::ViewProjectionMatrix);
		block.addMember(Declaration::VariableType::FloatVector4, UniformBlocks::Component::PositionWorldSpace);
		block.addMember(Declaration::VariableType::FloatVector4, UniformBlocks::Component::Velocity);
		block.addMember(Declaration::VariableType::FloatVector4, UniformBlocks::Component::ViewProperties);

		return block;
	}
}
