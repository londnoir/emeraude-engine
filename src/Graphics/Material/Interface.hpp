/*
 * src/Graphics/Material/Interface.hpp
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

#pragma once

/* STL inclusions. */
#include <cstdint>
#include <memory>
#include <string>

/* Local inclusions for inheritances. */
#include "Resources/ResourceTrait.hpp"

/* Local inclusions for usages. */
#include "Graphics/Types.hpp" // BlendingMode

/* Forward declaration */
namespace EmEn
{
	namespace Vulkan
	{
		class DescriptorSet;
		class DescriptorSetLayout;
		class LayoutManager;
		class UniformBufferObject;
		class SharedUniformBuffer;
	}

	namespace Physics
	{
		class PhysicalSurfaceProperties;
	}

	namespace Saphir
	{
		namespace Declaration
		{
			class UniformBlock;
		}

		namespace Generator
		{
			class Abstract;
		}

		class LightGenerator;
		class VertexShader;
		class FragmentShader;
	}

	namespace Graphics
	{
		class Renderer;
	}
}

namespace EmEn::Graphics::Material
{
	/** @brief Material interface flag bits. */
	enum MaterialFlagBits
	{
		Created = 1,
		BlendingEnabled = 2,
		TexturingEnabled = 4,
		Animated = 8,
		HighQualityReflection = 16,
		NormalMapping = 32,
		Displacement = 64,
		UsesPrimaryTextureCoordinates = 128,
		ComputesPrimaryTextureCoordinates = 256,
		PrimaryTextureCoordinatesUses3D = 512,
		UsesSecondaryTextureCoordinates = 1024,
		ComputesSecondaryTextureCoordinates = 2048,
		SecondaryTextureCoordinatesUses3D = 4096,
		UsesNormals = 8192,
		UsesTangentSpace = 16384, /* Overrides UsesNormals */
		UsesVertexColors = 32768
	};

	/**
	 * @brief This is the base of all material compatible with the graphic engine.
	 * @extends EmEn::Resources::ResourceTrait Every material is a resource.
	 */
	class Interface : public Resources::ResourceTrait
	{
		public:

			/**
			 * @brief Destructs the material interface.
			 */
			~Interface () override = default;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Interface (const Interface & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Interface (Interface && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			Interface & operator= (const Interface & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			Interface & operator= (Interface && copy) noexcept = delete;

			/**
			 * @brief Returns whether the material is animated.
			 * @note This function is used to sort the rendering Z order.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isAnimated () const noexcept
			{
				return this->isFlagEnabled(Animated);
			}

			/**
			 * @brief Returns whether the material is opaque and do not use blending.
			 * @note This function is used to sort the rendering Z order.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isOpaque () const noexcept
			{
				return !this->isFlagEnabled(BlendingEnabled);
			}

			/**
			 * @brief Returns whether the material is using textures.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			usingTexture () const noexcept
			{
				return this->isFlagEnabled(TexturingEnabled);
			}

			/**
			 * @brief Returns whether the material is using primary texture coordinates vertex attributes.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			usingPrimaryTextureCoordinates () const noexcept
			{
				if ( !this->isFlagEnabled(TexturingEnabled) )
				{
					return false;
				}

				return this->isFlagEnabled(UsesPrimaryTextureCoordinates);
			}

			/**
			 * @brief Returns whether the material is computing primary texture coordinates from vertices position.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			computesPrimaryTextureCoordinates () const noexcept
			{
				if ( !this->isFlagEnabled(TexturingEnabled) )
				{
					return false;
				}

				return this->isFlagEnabled(ComputesPrimaryTextureCoordinates);
			}

			/**
			 * @brief Returns whether the material primary texture coordinates are expressed in 3D.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			primaryTextureCoordinatesUses3D () const noexcept
			{
				if ( !this->isFlagEnabled(TexturingEnabled) )
				{
					return false;
				}

				return this->isFlagEnabled(PrimaryTextureCoordinatesUses3D);
			}

			/**
			 * @brief Returns whether the material is using secondary texture coordinates vertex attributes.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			usingSecondaryTextureCoordinates () const noexcept
			{
				if ( !this->isFlagEnabled(TexturingEnabled) )
				{
					return false;
				}

				return this->isFlagEnabled(UsesSecondaryTextureCoordinates);
			}

			/**
			 * @brief Returns whether the material is computing secondary texture coordinates from vertices position.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			computesSecondaryTextureCoordinates () const noexcept
			{
				if ( !this->isFlagEnabled(TexturingEnabled) )
				{
					return false;
				}

				return this->isFlagEnabled(ComputesSecondaryTextureCoordinates);
			}

			/**
			 * @brief Returns whether the material secondary texture coordinates are expressed in 3D.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			secondaryTextureCoordinatesUses3D () const noexcept
			{
				if ( !this->isFlagEnabled(TexturingEnabled) )
				{
					return false;
				}

				return this->isFlagEnabled(SecondaryTextureCoordinatesUses3D);
			}

			/**
			 * @brief Returns whether the material is using normal vertex attributes.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			usingNormals () const noexcept
			{
				if ( this->isFlagEnabled(UsesTangentSpace) )
				{
					return true;
				}

				return this->isFlagEnabled(UsesNormals);
			}

			/**
			 * @brief Returns whether the material is using tangent space.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			usingTangentSpace () const noexcept
			{
				return this->isFlagEnabled(UsesTangentSpace);
			}

			/**
			 * @brief Returns whether the material is using vertex color attributes.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			usingVertexColors () const noexcept
			{
				return this->isFlagEnabled(UsesVertexColors);
			}

			/**
			 * @brief Enables the blending mode using json data.
			 * @param data A reference to a json value.
			 * @return void
			 */
			void enableBlendingFromJson (const Json::Value & data) noexcept;

			/**
			 * @brief Creates the material in the video memory.
			 * @param renderer A reference to the graphics renderer.
			 * @return bool
			 */
			virtual bool create (Renderer & renderer) noexcept = 0;

			/**
			 * @brief Releases the material from the video memory.
			 * @return void
			 */
			virtual void destroy () noexcept = 0;

			/**
			 * @brief Returns whether the material is usable.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isCreated () const noexcept = 0;

			/**
			 * @brief Returns whether the material needs individual matrices to work.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isComplex () const noexcept = 0;

			/**
			 * @brief Setups the light generator with this material.
			 * @param lightGenerator A reference to the light generator.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool setupLightGenerator (Saphir::LightGenerator & lightGenerator) const noexcept = 0;

			/**
			 * @brief Generates the code responsible for the vertex shader.
			 * @param generator A reference to the graphics shader generator.
			 * @param vertexShader A reference to the vertex shader.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool generateVertexShaderCode (Saphir::Generator::Abstract & generator, Saphir::VertexShader & vertexShader) const noexcept = 0;

			/**
			 * @brief Generates the code responsible for the fragment shader.
			 * @param generator A reference to the graphics shader generator.
			 * @param lightGenerator A reference to the light generator.
			 * @param fragmentShader A reference to the fragment shader.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool generateFragmentShaderCode (Saphir::Generator::Abstract & generator, Saphir::LightGenerator & lightGenerator, Saphir::FragmentShader & fragmentShader) const noexcept = 0;

			/**
			 * @brief Returns the physical surface properties.
			 * @return const Physics::PhysicalSurfaceProperties &
			 */
			[[nodiscard]]
			virtual const Physics::PhysicalSurfaceProperties & physicalSurfaceProperties () const noexcept = 0;

			/**
			 * @brief Returns the physical surface properties.
			 * @return Physics::PhysicalSurfaceProperties &
			 */
			[[nodiscard]]
			virtual Physics::PhysicalSurfaceProperties & physicalSurfaceProperties () noexcept = 0;

			/**
			 * @brief Returns the number of frame.
			 * @note If underlying texture is not animated, it returns 1.
			 * @return uint32_t
			 */
			[[nodiscard]]
			virtual uint32_t frameCount () const noexcept = 0;

			/**
			 * @brief Returns the duration in milliseconds.
			 * @note If underlying texture is not animated, it returns 0.
			 * @return uint32_t
			 */
			[[nodiscard]]
			virtual uint32_t duration () const noexcept = 0;

			/**
			 * @brief Returns the frame index for the current time.
			 * @param sceneTime The total time of the scene in milliseconds.
			 * @return size_t
			 */
			[[nodiscard]]
			virtual uint32_t frameIndexAt (uint32_t sceneTime) const noexcept = 0;

			/**
			 * @brief Enables a blending and set the desired mode.
			 * @param mode The blending mode.
			 * @return void
			 */
			virtual void enableBlending (BlendingMode mode) noexcept = 0;

			/**
			 * @brief Returns the blending mode.
			 * @return BlendingMode
			 */
			[[nodiscard]]
			virtual BlendingMode blendingMode () const noexcept = 0;

			/**
			 * @brief Returns the variables or the code to get the fragment color produced by this material.
			 * @note This is used for the final color without further effect application such as lighting.
			 * @return std::string
			 */
			[[nodiscard]]
			virtual std::string fragmentColor () const noexcept = 0;

			/**
			 * @brief Returns the descriptor set layout for this material after creation.
			 * @return std::shared_ptr< Vulkan::DescriptorSetLayout >
			 */
			[[nodiscard]]
			virtual std::shared_ptr< Vulkan::DescriptorSetLayout > descriptorSetLayout () const noexcept = 0;

			/**
			 * @brief Returns the light position in the UBO.
			 * @return uint32_t
			 */
			[[nodiscard]]
			virtual uint32_t UBOIndex () const noexcept = 0;

			/**
			 * @brief Returns the light alignment in the UBO.
			 * @return uint32_t
			 */
			[[nodiscard]]
			virtual uint32_t UBOAlignment () const noexcept = 0;

			/**
			 * @brief Returns the light offset in bytes in the UBO.
			 * @note This is the same as UBOIndex() * UBOAlignment().
			 * @return uint32_t
			 */
			[[nodiscard]]
			virtual uint32_t UBOOffset () const noexcept = 0;

			/**
			 * @brief Returns the descriptor set for this material.
			 * @return const Vulkan::DescriptorSet *
			 */
			[[nodiscard]]
			virtual const Vulkan::DescriptorSet * descriptorSet () const noexcept = 0;

			/**
			 * @brief Returns the uniform block explaining how the material works.
			 * @param set The set index.
			 * @param binding The binding point in the set.
			 * @return Saphir::Declaration::UniformBlock
			 */
			[[nodiscard]]
			virtual Saphir::Declaration::UniformBlock getUniformBlock (uint32_t set, uint32_t binding) const noexcept = 0;

		protected:

			/**
			 * @brief Constructs a material interface.
			 * @param name The name of the resource.
			 * @param resourceFlagBits The resource flag bits.
			 */
			explicit Interface (const std::string & name, uint32_t resourceFlagBits) noexcept;

			/**
			 * @brief Returns the shared uniform buffer corresponding to this material.
			 * @param renderer A reference to the graphics renderer.
			 * @param identifier A reference to a string.
			 * @return std::shared_ptr< Vulkan::SharedUniformBuffer >
			 */
			[[nodiscard]]
			std::shared_ptr< Vulkan::SharedUniformBuffer > getSharedUniformBuffer (Renderer & renderer, const std::string & identifier) const noexcept;

			/**
			 * @brief Returns the shared uniform buffer identifier corresponding to this material.
			 * @return std::string
			 */
			[[nodiscard]]
			virtual std::string getSharedUniformBufferIdentifier () const noexcept = 0;

			/**
			 * @brief Creates the material data into the shared uniform buffer.
			 * @param renderer A reference to the graphics renderer.
			 * @param identifier A reference to a string.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool createElementInSharedBuffer (Renderer & renderer, const std::string & identifier) noexcept = 0;

			/**
			 * @brief Gets or creates the descriptor set layout for this material.
			 * @param layoutManager A reference to the layout manager.
			 * @param identifier A reference to a string.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool createDescriptorSetLayout (Vulkan::LayoutManager & layoutManager, const std::string & identifier) noexcept = 0;

			/**
			 * @brief Creates the descriptor set for this material.
			 * @param renderer A reference to the graphics renderer.
			 * @param uniformBufferObject A reference to the material uniform buffer object.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool createDescriptorSet (Renderer & renderer, const Vulkan::UniformBufferObject & uniformBufferObject) noexcept = 0;

			/**
			 * @brief Events for child class when the material is loaded on GPU.
			 * @return void
			 */
			virtual void onMaterialLoaded () noexcept = 0;

		private:

			/** @copydoc EmEn::Resources::ResourceTrait::onDependenciesLoaded() */
			[[nodiscard]]
			bool onDependenciesLoaded () noexcept override;
	};
}
