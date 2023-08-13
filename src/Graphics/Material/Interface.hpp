/*
 * Emeraude/Graphics/Material/Interface.hpp
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
#include <string>

/* Local inclusions for inheritances. */
#include "Resources/ResourceTrait.hpp"
#include "Saphir/ShaderGenerationInterface.hpp"

/* Local inclusions for usages. */
#include "Saphir/ShaderGenerator.hpp"
#include "Physics/PhysicalSurfaceProperties.hpp"

/* Forward declarations. */
namespace Emeraude::Graphics
{
	namespace Geometry
	{
		class Interface;
	}

	namespace TextureResource
	{
		class Abstract;
	}
}

/* Forward declaration */
namespace Emeraude::Vulkan
{
	class DescriptorSet;
	class DescriptorSetLayout;
}

namespace Emeraude::Graphics::Material
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
	 * @extends Emeraude::Resources::ResourceTrait Every material is a resource.
	 * @extends Emeraude::Saphir::ShaderGenerationInterface Every material must be able to interact with shader code generation.
	 */
	class Interface : public Resources::ResourceTrait, public Saphir::ShaderGenerationInterface
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
			 * @brief Creates the material in the video memory.
			 * @return bool
			 */
			virtual bool create () noexcept = 0;

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
			 * @brief Returns the number of frame. If underlying texture is not animated, it returns 1.
			 * @return size_t
			 */
			[[nodiscard]]
			virtual size_t frameCount () const noexcept = 0;

			/**
			 * @brief Returns the duration in milliseconds. If underlying texture is not animated, it returns 0.
			 * @note 1.0 is 1 second.
			 * @return float
			 */
			[[nodiscard]]
			virtual float duration () const noexcept = 0;

			/**
			 * @brief Returns whether the material is translucent.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isTranslucent () const noexcept = 0;

			/**
			 * @brief Returns whether the material is opaque.
			 * @return bool
			 */
			[[nodiscard]]
			virtual
			inline
			bool
			isOpaque () const noexcept final
			{
				return !this->isTranslucent();
			}

			/**
			 * @brief Returns whether the material need a blending mode.
			 * @return void
			 */
			virtual void enableBlending () noexcept = 0;

			/**
			 * @brief Returns whether the material need a blending mode.
			 * @param mode The blending mode.
			 * @return void
			 */
			virtual void setBlendingMode (BlendingMode mode) noexcept = 0;

			/**
			 * @brief Returns the blending mode.
			 * @return BlendingMode
			 */
			[[nodiscard]]
			virtual BlendingMode blendingMode () const noexcept = 0;

			/**
			 * @brief Returns whether the material is using textures.
			 * @return bool
			 */
			[[nodiscard]]
			virtual
			bool
			usingTexture () const noexcept final
			{
				return this->isFlagEnabled(TexturingEnabled);
			}

			/**
			 * @brief Returns whether the material is using primary texture coordinates vertex attributes.
			 * @return bool
			 */
			[[nodiscard]]
			virtual
			bool
			usingPrimaryTextureCoordinates () const noexcept final
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
			virtual
			bool
			computesPrimaryTextureCoordinates () const noexcept final
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
			virtual
			bool
			primaryTextureCoordinatesUses3D () const noexcept final
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
			virtual
			bool
			usingSecondaryTextureCoordinates () const noexcept final
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
			virtual
			bool
			computesSecondaryTextureCoordinates () const noexcept final
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
			virtual
			bool
			secondaryTextureCoordinatesUses3D () const noexcept final
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
			virtual
			bool
			usingNormals () const noexcept final
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
			virtual
			bool
			usingTangentSpace () const noexcept final
			{
				return this->isFlagEnabled(UsesTangentSpace);
			}

			/**
			 * @brief Returns whether the material is using vertex color attributes.
			 * @return bool
			 */
			[[nodiscard]]
			virtual
			bool
			usingVertexColors () const noexcept final
			{
				return this->isFlagEnabled(UsesVertexColors);
			}

			/**
			 * @brief Returns the descriptor set layout for this material.
			 * @return std::shared_ptr< Vulkan::DescriptorSetLayout >
			 */
			[[nodiscard]]
			virtual std::shared_ptr< Vulkan::DescriptorSetLayout > descriptorSetLayout () const noexcept = 0;

			/**
			 * @brief Returns the descriptor set for this material.
			 * @return const Vulkan::DescriptorSet *
			 */
			[[nodiscard]]
			virtual const Vulkan::DescriptorSet * descriptorSet () const noexcept = 0;

		protected:

			/**
			 * @brief Constructs a material interface.
			 * @param name The name of the resource.
			 * @param resourceFlagBits The resource flag bits.
			 */
			explicit Interface (const std::string & name, uint32_t resourceFlagBits) noexcept;

		private:

			/** @copydoc Emeraude::Resources::ResourceTrait::onDependenciesLoaded() */
			[[nodiscard]]
			bool onDependenciesLoaded () noexcept override;
	};
}
