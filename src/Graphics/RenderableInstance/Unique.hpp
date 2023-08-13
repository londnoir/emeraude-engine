/*
 * Emeraude/Graphics/RenderableInstance/Unique.hpp
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

#pragma once

/* C/C++ standard libraries. */
#include <memory>
#include <mutex>

/* Local inclusions for inheritances. */
#include "Abstract.hpp"

/* Local inclusions for usages. */
#include "Math/Coordinates.hpp"
#include "Vulkan/DescriptorSet.hpp"
#include "Vulkan/UniformBufferObject.hpp"

namespace Emeraude::Graphics::RenderableInstance
{
	/**
	 * @brief This is a renderable object that use an UBO to determine the location of the renderable object.
	 * @extends Emeraude::Graphics::RenderableInstance::Abstract It needs the base of a renderable instance.
	 */
	class Unique final : public Abstract
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"RenderableInstanceUnique"};

			/**
			 * @brief Constructs a renderable instance.
			 * @param renderable A reference to a smart pointer of a renderable object.
			 * @param location A reference to a coordinates for the initial location. Default origin.
			 */
			explicit Unique (const std::shared_ptr< Renderable::Interface > & renderable, const Libraries::Math::Coordinates< float > & location = {}) noexcept;

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::isCreated() */
			[[nodiscard]]
			bool isModelMatricesCreated () const noexcept override;

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::resetMatrices() */
			bool resetModelMatrices () noexcept override;

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::useModelUniformBufferObject() */
			[[nodiscard]]
			bool useModelUniformBufferObject () const noexcept override;

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::useModelVertexBufferObject() */
			[[nodiscard]]
			bool useModelVertexBufferObject () const noexcept override;

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::useModelVertexBufferObject() */
			bool updateVideoMemoryForRendering (const std::shared_ptr< Graphics::RenderTarget::Abstract > & renderTarget) noexcept override;

			/**
			 * @brief Updates model matrices in video memory.
			 * @param location A pointer to the model matrix. It can be nullptr.
			 * @param Abstract A pointer to the render target. It can be nullptr.
			 * @param shadowMap A pointer to the shadowMap. It can be nullptr.
			 * @return bool
			 */
			bool updateModelMatrices (const Libraries::Math::Coordinates< float > * location, const RenderTarget::Abstract * renderTarget, const RenderTarget::Abstract * shadowMap) noexcept;

			/**
			 * @brief Updates model matrices in video memory.
			 * @param location A reference to a model matrix representing the object.
			 * @return bool
			 */
			bool updateWithModel (const Libraries::Math::Coordinates< float > & location) noexcept;

			/**
			 * @brief Updates model matrices in video memory for a specific view.
			 * @param renderTarget A reference to the render target.
			 * @return bool
			 */
			bool updateWithView (const RenderTarget::Abstract & renderTarget) noexcept;

			/**
			 * @brief Updates model matrices in video memory for a specific view.
			 * @param shadowMap A reference to the shadow map.
			 * @return bool
			 */
			[[deprecated("This will be removed, old OpenGL behavior not more useful in Vulkan")]]
			bool updateWithShadowMap (const RenderTarget::Abstract & shadowMap) noexcept;

			/**
			 * @brief Gets the model matrices uniform block.
			 * @param set The set number used in the descriptor set.
			 * @param binding The binding used number the in descriptor set. Default 0.
			 * @return Saphir::Declaration::UniformBlock
			 */
			[[nodiscard]]
			static Saphir::Declaration::UniformBlock getModelUniformBlock (uint32_t set, uint32_t binding = 0) noexcept;

		private:

			/** @copydoc Emeraude::Graphics::RenderableInstance::Abstract::createModelMatrices() */
			[[nodiscard]]
			bool createModelMatrices () noexcept override;

			/** @copydoc Emeraude::Graphics::RenderableInstance::Abstract::instanceCount() */
			[[nodiscard]]
			size_t instanceCount () const noexcept override;

			/** @copydoc Emeraude::Graphics::RenderableInstance::Abstract::createModelMatrices() */
			void bindInstanceLayer (const Vulkan::CommandBuffer & commandBuffer, const Vulkan::PipelineLayout & pipelineLayout, size_t layerIndex, uint32_t & setOffset) const noexcept override;

			Libraries::Math::Matrix< 4, float > m_modelMatrixCopy{};
			std::unique_ptr< Vulkan::UniformBufferObject > m_uniformBufferObject{};
			std::unique_ptr< Vulkan::DescriptorSet > m_modelDescriptorSet{};
	};
}
