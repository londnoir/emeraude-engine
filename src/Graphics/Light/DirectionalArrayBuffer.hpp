/*
 * Emeraude/Graphics/Light/DirectionalArrayBuffer.hpp
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
#include <vector>

/* Local inclusions */
#include "ArrayBufferInterface.hpp"
#include "Scenes/DirectionalLight.hpp"

namespace Emeraude::Graphics::Light
{
	/**
	 * @brief The directional light array buffer class. This will manage the GPU buffer to set light information to shaders.
	 * @extends Emeraude::Graphics::ArrayBufferInterface The base class of light array buffer.
	 */
	class DirectionalArrayBuffer final : public ArrayBufferInterface
	{
		public:

			static constexpr auto MaxActivableLight = 2UL;

			/**
			 * @brief Constructs a buffer of lights.
			 * @param maxLight The maximum light in the buffer.
			 * @param HWAlignmentSize Space in an UBO for alignment expressed in bytes (will be divided by 4 to meet float). Given by Utility::getUniformBufferOffsetAlignment().
			 */
			explicit DirectionalArrayBuffer (size_t maxLight, size_t HWAlignmentSize = 256) noexcept;

			/** @copydoc Emeraude::Graphics::ArrayBufferInterface::maxActivableLight() */
			[[nodiscard]]
			size_t maxActivableLight () const noexcept override;

			/** @copydoc Emeraude::Graphics::ArrayBufferInterface::renderPassType() */
			[[nodiscard]]
			RenderPassType renderPassType () const noexcept override;

			/** @copydoc Emeraude::Graphics::ArrayBufferInterface::addLightToAmbient() */
			void addLightToAmbient (Libraries::Math::Vector< 4, float > & sceneAmbientColor, const Scenes::LightSet & lightSet, const Libraries::Math::Vector< 3, float > & cameraPosition) const noexcept override;

			/** @copydoc Emeraude::Graphics::ArrayBufferInterface::initialize() */
			[[nodiscard]]
			bool initialize () noexcept override;

			/** @copydoc Emeraude::Graphics::ArrayBufferInterface::updateVideoMemoryForRendering() */
			bool updateVideoMemory (const Libraries::Math::Matrix< 4, float > & view) noexcept override;

			//void bindToProgram (const Program & program, size_t lightIndex) const noexcept override;

			//void activateShadowMap (const Program & program, size_t lightIndex, unsigned int & nextTextureUnit) const noexcept override;

			//void activateShadowMap (const Program & program, const ModelMatricesUBO & modelMatrices, size_t lightIndex, unsigned int & nextTextureUnit) const noexcept override;

			/**
			 * @brief clear
			 */
			void clear () noexcept override;

			/** @copydoc Emeraude::Graphics::ArrayBufferInterface::printMemoryRequirement() */
			void printMemoryRequirement () const noexcept override;

			/**
			 * @brief Adds a new light to the buffer.
			 * @param light The new light.
			 * @return bool
			 */
			bool addLight (const std::shared_ptr< Scenes::DirectionalLight > & light) noexcept;

			/**
			 * @brief Removes a new light from the buffer.
			 * @param light The light to delete.
			 */
			void removeLight (const std::shared_ptr< Scenes::DirectionalLight > & light) noexcept;

			/**
			 * @brief Returns a lights list.
			 * @return const vector< shared_ptr< DirectionalLight > &
			 */
			[[nodiscard]]
			const std::vector< std::shared_ptr< Scenes::DirectionalLight > > & lights () const noexcept;

		private:

			std::unique_ptr< Vulkan::UniformBufferObject > m_uniformBufferObject{};
			std::vector< std::shared_ptr< Scenes::DirectionalLight > > m_lights{};
			size_t m_limit = 64;
			size_t m_alignmentCount = 64;
			size_t m_alignmentSize = 256;
	};
}
