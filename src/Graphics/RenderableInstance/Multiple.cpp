/*
 * Emeraude/Graphics/RenderableInstance/Multiple.cpp
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

#include "Multiple.hpp"

/* Local inclusions. */
#include "Tracer.hpp"
#include "Vulkan/CommandBuffer.hpp"
#include "Vulkan/PipelineLayout.hpp"
#include "Vulkan/TransferManager.hpp"

namespace Emeraude::Graphics::RenderableInstance
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Emeraude::Vulkan;

	Multiple::Multiple (const std::shared_ptr< Renderable::Interface > & renderable, const std::vector< Coordinates< float > > & instanceLocations) noexcept
		: Abstract(renderable, LightingEnabled | ShadowsCastingEnabled | ReceivingShadows | EnableInstancing), m_instanceCount(instanceLocations.size())
	{
		if ( !this->commonInitialization(&instanceLocations, renderable.get()) )
		{
			Tracer::error(ClassId, "Unable to create the renderable multiple instance !");
		}
	}

	Multiple::Multiple (const std::shared_ptr< Renderable::Interface > & renderable, size_t instanceCount) noexcept
		: Abstract(renderable, LightingEnabled | ShadowsCastingEnabled | ReceivingShadows | EnableInstancing), m_instanceCount(instanceCount)
	{
		if ( !this->commonInitialization(nullptr, renderable.get()) )
		{
			Tracer::error(ClassId, "Unable to create the renderable multiple instance !");
		}
	}

	bool
	Multiple::commonInitialization (const std::vector< Coordinates< float > > * instanceLocations, Renderable::Interface * renderable) noexcept
	{
		if ( m_instanceCount == 0 )
		{
			this->setBroken("The location list is empty !");

			return false;
		}

		/* NOTE: Reserve the actual data place to speed up the local storage. */
		m_localData.resize(m_instanceCount * Multiple::VBOElementCount());

		if ( instanceLocations != nullptr )
		{
			if ( !this->setLocalData(*instanceLocations, 0) )
			{
				this->setBroken("Unable to set local matrix data !");

				return false;
			}
		}
		else
		{
			this->resetLocalData();
		}

		/* Create a vertex buffer object to hold locations in video memory
		 * according to the size of local data. */
		if ( !this->createModelMatrices() )
		{
			this->setBroken("Unable to initialize the model matrix VBO !");

			return false;
		}

		this->observe(renderable);

		return true;
	}

	bool
	Multiple::isModelMatricesCreated () const noexcept
	{
		if ( m_vertexBufferObject == nullptr )
		{
			return false;
		}

		return m_vertexBufferObject->isCreated();
	}

	size_t
	Multiple::instanceCount () const noexcept
	{
		return m_instanceCount;
	}

	bool
	Multiple::useModelUniformBufferObject () const noexcept
	{
		return false;
	}

	bool
	Multiple::useModelVertexBufferObject () const noexcept
	{
		return true;
	}

	bool
	Multiple::updateVideoMemoryForRendering (const std::shared_ptr< Graphics::RenderTarget::Abstract > & /*renderTarget*/) noexcept
	{
		return true;
	}

	size_t
	Multiple::VBOElementCount () noexcept
	{
		const auto modelMatrixElementCount = 4 * attributeSize(VertexAttributeType::ModelMatrixR0);
		const auto normalModelMatrixElementCount = 3 * attributeSize(VertexAttributeType::NormalModelMatrixR0);

		return modelMatrixElementCount + normalModelMatrixElementCount;
	}

	void
	Multiple::resetLocalData () noexcept
	{
		const auto limit = this->instanceCount();
		constexpr auto identity3 = Matrix< 3, float >::identity();
		constexpr auto identity4 = Matrix< 4, float >::identity();

		/* Starting offset in video memory */
		size_t elementOffset = 0;

		// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)

		for ( size_t instanceIndex = 0; instanceIndex < limit; instanceIndex++ )
		{
			identity4.copy(m_localData.data() + elementOffset);

			elementOffset += 4 * attributeSize(VertexAttributeType::ModelMatrixR0); /* mat4 is 4 vectors */

			identity3.copy(m_localData.data() + elementOffset);

			elementOffset += 3 * attributeSize(VertexAttributeType::NormalModelMatrixR0); /* mat4 is 3 vectors */
		}

		// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)

		this->disableFlag(IsPositionSynchronized);
	}

	bool
	Multiple::setLocalData (const std::vector< Coordinates< float > > & instanceLocations, size_t localDataOffset) noexcept
	{
		/* Check against the local data. */
		if ( instanceLocations.size() + localDataOffset > m_instanceCount )
		{
			Tracer::error(ClassId, "Local data overflow !");

			return false;
		}

		/* Starting offset in video memory */
		size_t elementOffset = localDataOffset * Multiple::VBOElementCount();

		// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)

		for ( const auto & instanceLocation : instanceLocations )
		{
			const auto modelMatrix = instanceLocation.modelMatrix();

			modelMatrix.copy(m_localData.data() + elementOffset);

			elementOffset += 4 * attributeSize(VertexAttributeType::ModelMatrixR0); /* mat4 is 4 vectors */

			const auto normalModelMatrix = modelMatrix.inverse().transpose().toMatrix3();

			normalModelMatrix.copy(m_localData.data() + elementOffset);

			elementOffset += 3 * attributeSize(VertexAttributeType::NormalModelMatrixR0); /* mat4 is 3 vectors */
		}

		// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)

		this->disableFlag(IsPositionSynchronized);

		return true;
	}

	bool
	Multiple::createModelMatrices () noexcept
	{
		const std::lock_guard< std::mutex > lock{m_GPUMemoryAccess};

		if ( this->isModelMatricesCreated() )
		{
			return true;
		}

		auto * transferManager = TransferManager::instance(TransferType::Graphics);

		const auto vertexElementCount = Multiple::VBOElementCount();
		const auto vertexCount = m_localData.size() / vertexElementCount;

		m_vertexBufferObject = std::make_unique< VertexBufferObject >(transferManager->device(), vertexCount, vertexElementCount);
		m_vertexBufferObject->setIdentifier("Multiple-ModelVBO-VertexBufferObject");

		if ( !m_vertexBufferObject->create(*transferManager, m_localData) )
		{
			Tracer::error(ClassId, "Unable to create the vertex buffer object (VBO) !");

			m_vertexBufferObject.reset();

			return false;
		}

		this->enableFlag(IsPositionSynchronized);

		return true;
	}

	bool
	Multiple::updateModelMatrices (const std::vector< Coordinates< float > > & instanceLocations, size_t localDataOffset) noexcept
	{
		const std::lock_guard< std::mutex > lock{m_GPUMemoryAccess};

#ifdef DEBUG
		if ( !this->isModelMatricesCreated() )
		{
			Tracer::error(ClassId, "Trying to map an uninitialized VBO.");

			return false;
		}
#endif

		/* FIXME: Check this functionality
		if ( this->isFlagEnabled(IsPositionSynchronized) )
		{
			return true;
		}*/

		/* NOTE: Create the data vector to init the VBO directly. */
		if ( !this->setLocalData(instanceLocations, localDataOffset) )
		{
			return false;
		}

		if ( !m_vertexBufferObject->writeData(*TransferManager::instance(TransferType::Graphics), {m_localData.data(), m_localData.size()}) )
		{
			Tracer::error(ClassId, "Unable to write data to the VBO.");

			return false;
		}

		this->enableFlag(IsPositionSynchronized);

		return true;
	}

	bool
	Multiple::resetModelMatrices () noexcept
	{
		const std::lock_guard< std::mutex > lock{m_GPUMemoryAccess};

#ifdef DEBUG
		if ( !this->isModelMatricesCreated() )
		{
			Tracer::error(ClassId, "Trying to map an uninitialized VBO.");

			return false;
		}
#endif

		this->resetLocalData();

		if ( !m_vertexBufferObject->writeData(*TransferManager::instance(TransferType::Graphics), {m_localData.data(), m_localData.size()}) )
		{
			Tracer::error(ClassId, "Unable to write data to the VBO.");

			return false;
		}

		this->enableFlag(IsPositionSynchronized);

		return true;
	}

	void
	Multiple::bindInstanceLayer (const CommandBuffer & commandBuffer, const PipelineLayout & pipelineLayout, size_t layerIndex, uint32_t & setOffset) const noexcept
	{
		const auto * geometry = this->renderable()->geometry();

		/* Bind the material UBO (Should be set #1). */
		commandBuffer.bind(
			*this->renderable()->material(layerIndex)->descriptorSet(),
			pipelineLayout,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			setOffset++
		);

		/*  Bind the geometry VBO(/IBO) and the model matrix VBO */
		commandBuffer.bind(*geometry, *m_vertexBufferObject, layerIndex);
	}

	bool
	Multiple::coordinatesToModelMatrices (const std::vector< Libraries::Math::Coordinates< float > > & coordinates, std::vector< Libraries::Math::Matrix< 4, float > > & modelMatrices, bool strict) noexcept
	{
		if ( coordinates.empty() )
		{
			return false;
		}

		if ( strict && coordinates.size() != modelMatrices.size() )
		{
			return false;
		}

		const size_t limit = std::min(coordinates.size(), modelMatrices.size());

		for ( size_t index = 0; index < limit; index++ )
		{
			modelMatrices[index] = coordinates[index].modelMatrix();
		}

		return true;
	}
}
