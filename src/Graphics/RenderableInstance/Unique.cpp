/*
 * Emeraude/Graphics/RenderableInstance/Unique.cpp
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

#include "Unique.hpp"

/* C/C++ standard libraries. */
#include <cstring>

/* Local inclusions. */
#include "Graphics/RenderTarget/ShadowMap/Abstract.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/ViewMatricesInterface.hpp"
#include "Tracer.hpp"
#include "Vulkan/CommandBuffer.hpp"
#include "Vulkan/DescriptorSet.hpp"
#include "Vulkan/PipelineLayout.hpp"
#include "Vulkan/TransferManager.hpp"

namespace Emeraude::Graphics::RenderableInstance
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Emeraude::Vulkan;
	using namespace Saphir;
	using namespace Saphir::Keys;

	Unique::Unique (const std::shared_ptr< Renderable::Interface > & renderable, const Coordinates< float > & location) noexcept
		: Abstract(renderable, LightingEnabled | ShadowsCastingEnabled | ReceivingShadows)
	{
		if ( !this->createModelMatrices() )
		{
			this->setBroken("Unable to initialize the model matrix UBO !");

			return;
		}

		if ( !this->updateModelMatrices(&location, nullptr, nullptr) )
		{
			this->setBroken("Unable to update the model matrix UBO !");

			return;
		}

		this->observe(renderable.get());
	}

	bool
	Unique::isModelMatricesCreated () const noexcept
	{
		if ( m_uniformBufferObject == nullptr )
		{
			return false;
		}

		return m_uniformBufferObject->isCreated();
	}

	size_t
	Unique::instanceCount () const noexcept
	{
		return 1;
	}

	bool
	Unique::useModelUniformBufferObject () const noexcept
	{
		return true;
	}

	bool
	Unique::useModelVertexBufferObject () const noexcept
	{
		return false;
	}

	bool
	Unique::updateVideoMemoryForRendering (const std::shared_ptr< Graphics::RenderTarget::Abstract > & renderTarget) noexcept
	{
		return this->updateWithView(*renderTarget);
	}

	bool
	Unique::createModelMatrices () noexcept
	{
		const std::lock_guard< std::mutex > lock{m_GPUMemoryAccess};

		if ( this->isModelMatricesCreated() )
		{
			return true;
		}

		constexpr auto bytes = 4 * UniformBufferObject::Matrix4fSize + 2 * UniformBufferObject::Matrix3fSize;

		m_uniformBufferObject = std::make_unique< UniformBufferObject >(TransferManager::instance(TransferType::Graphics)->device(), bytes);
		m_uniformBufferObject->setIdentifier("Unique-ModelUBO-UniformBufferObject");

		if ( !m_uniformBufferObject->createOnHardware() )
		{
			Tracer::error(ClassId, "Unable to create the uniform buffer object (UBO) !");

			m_uniformBufferObject.reset();

			return false;
		}

		auto modelDescriptorSetLayout = Renderer::instance()->getModelDescriptorSetLayout(*this);

		if ( modelDescriptorSetLayout == nullptr )
		{
			Tracer::error(ClassId, "Unable to get the descriptor set layout !");

			return false;
		}

		m_modelDescriptorSet = std::make_unique< DescriptorSet >(Renderer::instance()->descriptorPool(), modelDescriptorSetLayout);
		m_modelDescriptorSet->setIdentifier("Unique-Unique-DescriptorSet");

		if ( !m_modelDescriptorSet->create() )
		{
			m_modelDescriptorSet.reset();

			Tracer::error(ClassId, "Unable to create the descriptor set !");

			return false;
		}

		if ( !m_modelDescriptorSet->writeUniformBufferObject(*m_uniformBufferObject, 0) )
		{
			Tracer::error(ClassId, "Unable to write UBO to the descriptor set !");

			return false;
		}

		return true;
	}

	bool
	Unique::updateModelMatrices (const Coordinates< float > * location, const RenderTarget::Abstract * renderTarget, const RenderTarget::Abstract * shadowMap) noexcept
	{
		const std::lock_guard< std::mutex > lock{m_GPUMemoryAccess};

#ifdef DEBUG
		if ( !this->isModelMatricesCreated() )
		{
			Tracer::error(ClassId, "Trying to update an uninitialized UBO.");

			return false;
		}
#endif

		/* FIXME: Check this functionality
		if ( this->isFlagEnabled(IsPositionSynchronized) )
		{
			return true;
		}*/

		{
			auto * pointer = m_uniformBufferObject->mapMemory< float >();

			if ( pointer == nullptr )
			{
				return false;
			}

			size_t offset = 0;

			// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)

			/* NOTE: Matrices related to the model. */
			if ( location != nullptr )
			{
				/* The model matrix (4x4)
				 * NOTE: Keep the model matrix for next update with view and shadow. */
				m_modelMatrixCopy = location->modelMatrix();

				std::memcpy(&pointer[offset], m_modelMatrixCopy.data(), UniformBufferObject::Matrix4fSize);
				offset += UniformBufferObject::Matrix4Room;

				/* The model normal matrix (3x3) */
				//const auto normalModelMatrix = m_modelMatrixCopy.toMatrix3();
				const auto normalModelMatrix = m_modelMatrixCopy.inverse().transpose().toMatrix3();

				std::memcpy(&pointer[offset], normalModelMatrix.data(), UniformBufferObject::Matrix3fSize);
				offset += UniformBufferObject::Matrix3Room;
			}
			else
			{
				offset += UniformBufferObject::Matrix4Room + UniformBufferObject::Matrix3Room;
			}

			/* NOTE: Matrices related to the view. */
			if ( renderTarget != nullptr )
			{
				/* The model view matrix (4x4) */
				const auto modelViewMatrix = renderTarget->viewMatrices().viewMatrix(0) * m_modelMatrixCopy;

				std::memcpy(&pointer[offset], modelViewMatrix.data(), UniformBufferObject::Matrix4fSize);
				offset += UniformBufferObject::Matrix4Room;

				/* The normal matrix (3x3) */
				const auto normalMatrix = modelViewMatrix.inverse().toMatrix3().transpose();

				std::memcpy(&pointer[offset], normalMatrix.data(), UniformBufferObject::Matrix3fSize);
				offset += UniformBufferObject::Matrix3Room;

				/* The model view projection matrix (4x4) */
				//const auto modelViewProjectionMatrix = renderTarget->.viewMatrices()projectionMatrix() * renderTarget->viewMatrices().viewMatrix() * m_modelMatrixCopy;
				const auto modelViewProjectionMatrix = renderTarget->viewMatrices().viewProjectionMatrix(0) * m_modelMatrixCopy;

				std::memcpy(&pointer[offset], modelViewProjectionMatrix.data(), UniformBufferObject::Matrix4fSize);
				offset += UniformBufferObject::Matrix4Room;
			}
			else
			{
				offset += UniformBufferObject::Matrix4Room + UniformBufferObject::Matrix3Room + UniformBufferObject::Matrix4Room;
			}

			/* NOTE: Matrices related to the light. */
			if ( shadowMap != nullptr )
			{
				const auto modelLightMatrix = RenderTarget::ShadowMap::Abstract::ScaleBiasMatrix * shadowMap->viewMatrices().viewProjectionMatrix(0) * m_modelMatrixCopy;

				/* The model lightView lightProjection matrix (4x4) */
				std::memcpy(&pointer[offset], modelLightMatrix.data(), UniformBufferObject::Matrix4fSize);
			}

			// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)

			m_uniformBufferObject->unmapMemory();
		}

		this->enableFlag(IsPositionSynchronized);

		return true;
	}

	bool
	Unique::resetModelMatrices () noexcept
	{
		const std::lock_guard< std::mutex > lock{m_GPUMemoryAccess};

#ifdef DEBUG
		if ( !this->isModelMatricesCreated() )
		{
			Tracer::error(ClassId, "Trying to update an uninitialized UBO.");

			return false;
		}
#endif

		constexpr auto identity3 = Matrix< 4, float >::identity();
		constexpr auto identity4 = Matrix< 4, float >::identity();

		{
			auto * pointer = m_uniformBufferObject->mapMemory< float >();

			if ( pointer == nullptr )
			{
				return false;
			}

			size_t offset = 0;

			// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)

			/* The model matrix 4x4 */
			std::memcpy(&pointer[offset], identity4.data(), UniformBufferObject::Matrix4fSize);
			offset += UniformBufferObject::Matrix4Room;

			/* The model normal matrix 3x3 */
			std::memcpy(&pointer[offset], identity3.data(), UniformBufferObject::Matrix3fSize);
			offset += UniformBufferObject::Matrix3Room;

			/* The model view matrix 4x4 */
			std::memcpy(&pointer[offset], identity4.data(), UniformBufferObject::Matrix4fSize);
			offset += UniformBufferObject::Matrix4Room;

			/* The normal matrix 3x3 */
			std::memcpy(&pointer[offset], identity3.data(), UniformBufferObject::Matrix3fSize);
			offset += UniformBufferObject::Matrix3Room;

			/* The model view projection matrix 4x4 */
			std::memcpy(&pointer[offset], identity4.data(), UniformBufferObject::Matrix4fSize);
			offset += UniformBufferObject::Matrix4Room;

			/* The model lightView lightProjection matrix 4x4 */
			std::memcpy(&pointer[offset], identity4.data(), UniformBufferObject::Matrix4fSize);
			//offset += UniformBufferObject::Matrix4Room;

			// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)

			m_uniformBufferObject->unmapMemory();
		}

		m_modelMatrixCopy.reset();

		return true;
	}

	bool
	Unique::updateWithModel (const Libraries::Math::Coordinates< float > & location) noexcept
	{
		this->disableFlag(IsPositionSynchronized);

		return this->updateModelMatrices(&location, nullptr, nullptr);
	}

	bool
	Unique::updateWithView (const RenderTarget::Abstract & renderTarget) noexcept
	{
		return this->updateModelMatrices(nullptr, &renderTarget, nullptr);
	}

	bool
	Unique::updateWithShadowMap (const RenderTarget::Abstract & shadowMap) noexcept
	{
		return this->updateModelMatrices(nullptr, nullptr, &shadowMap);
	}

	void
	Unique::bindInstanceLayer (const CommandBuffer & commandBuffer, const PipelineLayout & pipelineLayout, size_t layerIndex, uint32_t & setOffset) const noexcept
	{
		const auto * geometry = this->renderable()->geometry();

		/* Bind the model matrix UBO (Should be set #1). */
		commandBuffer.bind(
			*m_modelDescriptorSet,
			pipelineLayout,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			setOffset++
		);

		/* Bind the material UBO (Should be set #3). */
		commandBuffer.bind(
			*this->renderable()->material(layerIndex)->descriptorSet(),
			pipelineLayout,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			setOffset++
		);

		/* Bind the geometry VBO(/IBO) */
		commandBuffer.bind(*geometry, layerIndex);
	}

	Declaration::UniformBlock
	Unique::getModelUniformBlock (uint32_t set, uint32_t binding) noexcept
	{
		Declaration::UniformBlock block{set, binding, Declaration::MemoryLayout::Std140, UniformBlocks::Model, BufferBackedBlocks::Model};
		block.addMember(Declaration::VariableType::Matrix4, UniformBlocks::Component::ModelMatrix);
		block.addMember(Declaration::VariableType::Matrix3, UniformBlocks::Component::NormalModelMatrix);
		block.addMember(Declaration::VariableType::Matrix4, UniformBlocks::Component::ModelViewMatrix);
		block.addMember(Declaration::VariableType::Matrix3, UniformBlocks::Component::NormalMatrix);
		block.addMember(Declaration::VariableType::Matrix4, UniformBlocks::Component::ModelViewProjectionMatrix);
		// FIXME : Remove this declaration for a push constant
		block.addMember(Declaration::VariableType::Matrix4, UniformBlocks::Component::ModelLightMatrix);

		return block;
	}
}
