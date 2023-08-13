/*
 * Emeraude/Graphics/RenderableInstance/Multiple.hpp
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
#include "Math/Coordinates.hpp"

namespace Emeraude::Graphics::RenderableInstance
{
	/**
	 * @brief This is a renderable object that use a VBO to determine multiple locations for the renderable object.
	 * @extends Emeraude::Graphics::RenderableInstance::Abstract It needs the base of a renderable instance.
	 */
	class Multiple final : public Abstract
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"RenderableInstanceMultiple"};

			/**
			 * @brief Constructs a renderable instance.
			 * @param renderable A reference to a smart pointer of a renderable object.
			 * @param instanceLocations A reference to a vector of coordinates. The max location count will be extracted from size().
			 */
			Multiple (const std::shared_ptr< Renderable::Interface > & renderable, const std::vector< Libraries::Math::Coordinates< float > > & instanceLocations) noexcept;

			/**
			 * @brief Constructs a renderable instance.
			 * @param renderable A reference to a smart pointer of a renderable object.
			 * @param instanceCount The maximum of number of locations hold by this instance.
			 */
			Multiple (const std::shared_ptr< Renderable::Interface > & renderable, size_t instanceCount) noexcept;

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
			 * @brief Updates model matrices in video memory from a list of coordinates.
			 * @warning The list size must fit the initial VBO size.
			 * @param instanceLocations A reference to a vector of coordinates.
			 * @param localDataOffset The offset in VBO of the first instance to apply the modification. Default from execute.
			 * @return bool
			 */
			bool updateModelMatrices (const std::vector< Libraries::Math::Coordinates< float > > & instanceLocations, size_t localDataOffset = 0) noexcept;

		private:

			/**
			 * @brief Common code from the constructors.
			 * @param instanceLocations A pointer to a coordinates list.
			 * @param renderable A pointer to the renderable to enable the observation.
			 * @return bool
			 */
			[[nodiscard]]
			bool commonInitialization (const std::vector< Libraries::Math::Coordinates< float > > * instanceLocations, Renderable::Interface * renderable) noexcept;

			/** @copydoc Emeraude::Graphics::RenderableInstance::Abstract::createModelMatrices() */
			[[nodiscard]]
			bool createModelMatrices () noexcept override;

			/** @copydoc Emeraude::Graphics::RenderableInstance::Abstract::instanceCount() */
			[[nodiscard]]
			size_t instanceCount () const noexcept override;

			/** @copydoc Emeraude::Graphics::RenderableInstance::Abstract::createModelMatrices() */
			void bindInstanceLayer (const Vulkan::CommandBuffer & commandBuffer, const Vulkan::PipelineLayout & pipelineLayout, size_t layerIndex, uint32_t & setOffset) const noexcept override;

			/**
			 * @brief Resets local data to identity matrices.
			 * @return void
			 */
			void resetLocalData () noexcept;

			/**
			 * @brief Transforms local model matrices from a list of locations.
			 * @param instanceLocations A reference to a coordinates list.
			 * @param localDataOffset The first instance to update in the local data. Default from execute.
			 * @return bool
			 */
			[[nodiscard]]
			bool setLocalData (const std::vector< Libraries::Math::Coordinates< float > > & instanceLocations, size_t localDataOffset = 0) noexcept;

			/**
			 * @brief Returns the number of element in VBO per call.
			 * @return size_t
			 */
			[[nodiscard]]
			static size_t VBOElementCount () noexcept;

			/**
			 * @brief Converts a list of coordinates to a list of model matrices.
			 * @param coordinates A reference to a list of coordinates.
			 * @param modelMatrices A reference to a list of model matrices.
			 * @param strict Ensure the twos vector are same size. Default no.
			 * @return bool
			 */
			static bool coordinatesToModelMatrices (const std::vector< Libraries::Math::Coordinates< float > > & coordinates, std::vector< Libraries::Math::Matrix< 4, float > > & modelMatrices, bool strict = false) noexcept;

			std::unique_ptr< Vulkan::VertexBufferObject > m_vertexBufferObject{};
			std::vector< float > m_localData{};
			size_t m_instanceCount;
	};
}
