/*
 * Emeraude/Graphics/Light/ArrayBufferInterface.hpp
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

/* Local inclusions */
#include "Math/Vector.hpp"
#include "Math/Matrix.hpp"
#include "PixelFactory/Color.hpp"
#include "Vulkan/UniformBufferObject.hpp"
#include "Graphics/Types.hpp"

/* Forward declaration */
namespace Emeraude::Scenes
{
	class AbstractLightEmitter;
	class LightSet;
}

namespace Emeraude::Graphics::Light
{
	class Program;

	/**
	 * @brief The ArrayBufferInterface class
	 */
	class ArrayBufferInterface
	{
		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			ArrayBufferInterface (const ArrayBufferInterface & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			ArrayBufferInterface (ArrayBufferInterface && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return ArrayBufferInterface &
			 */
			ArrayBufferInterface & operator= (const ArrayBufferInterface & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return ArrayBufferInterface &
			 */
			ArrayBufferInterface & operator= (ArrayBufferInterface && copy) noexcept = default;

			/** 
			 * @brief Destructs the array buffer interface.
			 */
			virtual ~ArrayBufferInterface () = default;

			/**
			 * @brief Gives the max number of light activable at once.
			 * @param size_t
			 */
			[[nodiscard]]
			virtual size_t maxActivableLight () const noexcept = 0;

			/**
			 * @brief Returns the render pass type for convenience.
			 * @return RenderPassType
			 */
			[[nodiscard]]
			virtual RenderPassType renderPassType () const noexcept = 0;

			/**
			 * @brief Base method to add a light ambient component to the scene ambient color.
			 * @param sceneAmbientColor The scene ambient color.
			 * @param lightSet A reference to the light set to get the ambient computation rules.
			 * @param cameraPosition The absolute camera position to compute impact of the light to scene ambient.
			 */
			virtual void addLightToAmbient (Libraries::Math::Vector< 4, float > & sceneAmbientColor, const Scenes::LightSet & lightSet, const Libraries::Math::Vector< 3, float > & cameraPosition) const noexcept = 0;

			/**
			 * @brief Initializes UBO for the light buffer.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool initialize () noexcept = 0;

			/**
			 * @brief Updates UBOs.
			 * @param view A reference to the view matrix.
			 * @return bool
			 */
			virtual bool updateVideoMemory (const Libraries::Math::Matrix< 4, float > & view) noexcept = 0;

			/**
			 * @brief Enables one light shadow map from the lights to the program.
			 * @param program The current program.
			 * @param lightIndex From which light to execute in the buffer.
			 * @param nextTextureUnit The current texture unit.
			 */
			//virtual void activateShadowMap (const Program & program, size_t lightIndex, unsigned int & nextTextureUnit) const noexcept = 0;

			/**
			 * @brief Enables one light shadow map from the lights to the program.
			 * @param program The current program.
			 * @param modelMatrices The model matrices UBO of the current object being rendered.
			 * @param lightIndex From which light to execute in the buffer.
			 * @param nextTextureUnit The current texture unit.
			 */
			//virtual void activateShadowMap (const Program & program, const ModelMatricesUBO & modelMatrices, size_t lightIndex, unsigned int & nextTextureUnit) const noexcept = 0;

			/** @brief Clears lights. */
			virtual void clear () noexcept = 0;

			/** @brief Prints light memory information attached to this buffer. */
			virtual void printMemoryRequirement () const noexcept = 0;

		protected:

			/** 
			 * @brief Constructs an array buffer interface.
			 */
			ArrayBufferInterface () noexcept = default;
	};
}
