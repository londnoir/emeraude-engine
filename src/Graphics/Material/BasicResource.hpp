/*
 * Emeraude/Graphics/Material/BasicResource.hpp
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
#include <string>
#include <vector>

/* Local inclusions for inheritances. */
#include "Interface.hpp"

/* Local inclusions for usages. */
#include "Resources/Container.hpp"
#include "Component/TypeTexture.hpp"

/* Forward declarations. */
namespace Emeraude
{
	namespace Graphics
	{
		class Renderer;
	}

	namespace Vulkan
	{
		class SharedUniformBuffer;
	}
}

namespace Emeraude::Graphics::Material
{
	/**
	 * @brief The basic material class use only one component.
	 * @extends Emeraude::Graphics::Material::Interface This is a material.
	 */
	class BasicResource final : public Interface
	{
		friend class Resources::Container< BasicResource >;

		using ResourceTrait::load;

		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"MaterialBasicResource"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs a basic material.
			 * @param name A reference to a string for the resource name.
			 * @param resourceFlagBits The resource flag bits. Default none.
			 */
			explicit BasicResource (const std::string & name, int resourceFlagBits = 0) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			BasicResource (const BasicResource & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			BasicResource (BasicResource && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			BasicResource & operator= (const BasicResource & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			BasicResource & operator= (BasicResource && copy) noexcept = delete;

			/**
			 * @brief Destructs the basic material.
			 */
			~BasicResource () override;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Libraries::Resources::ResourceTrait::classLabel() */
			[[nodiscard]]
			const char * classLabel () const noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load() */
			bool load () noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load(const Json::Value &) */
			bool load (const Json::Value & data) noexcept override;

			/** @copydoc Emeraude::ShaderGenerationInterface::generateShaderCode() */
			[[nodiscard]]
			bool generateShaderCode (Saphir::ShaderGenerator & gen, const Graphics::Geometry::Interface & geometry) const noexcept override;

			/** @copydoc Emeraude::Graphics::Material::create() */
			bool create () noexcept override;

			/** @copydoc Emeraude::Graphics::Material::destroy() */
			void destroy () noexcept override;

			/** @copydoc Emeraude::Graphics::Material::isCreated() */
			[[nodiscard]]
			bool isCreated () const noexcept override;

			/** @copydoc Emeraude::Graphics::Material::physicalSurfaceProperties() const */
			[[nodiscard]]
			const Physics::PhysicalSurfaceProperties & physicalSurfaceProperties () const noexcept override;

			/** @copydoc Emeraude::Graphics::Material::physicalSurfaceProperties() */
			[[nodiscard]]
			Physics::PhysicalSurfaceProperties & physicalSurfaceProperties () noexcept override;

			/** @copydoc Emeraude::Graphics::Material::frameCount() */
			[[nodiscard]]
			size_t frameCount () const noexcept override;

			/** @copydoc Emeraude::Graphics::Material::duration() */
			[[nodiscard]]
			float duration () const noexcept override;

			/** @copydoc Emeraude::Graphics::Material::isTranslucent() */
			[[nodiscard]]
			bool isTranslucent () const noexcept override;

			/** @copydoc Emeraude::Graphics::Material::enableBlending() */
			void enableBlending () noexcept override;

			/** @copydoc Emeraude::Graphics::Material::setBlendingMode() */
			void setBlendingMode (BlendingMode mode) noexcept override;

			/** @copydoc Emeraude::Graphics::Material::blendingMode() */
			[[nodiscard]]
			BlendingMode blendingMode () const noexcept override;

			/** @copydoc Emeraude::Graphics::Material::descriptorSetLayout() */
			[[nodiscard]]
			std::shared_ptr< Vulkan::DescriptorSetLayout > descriptorSetLayout () const noexcept override;

			/** @copydoc Emeraude::Graphics::Material::descriptorSet() */
			[[nodiscard]]
			const Vulkan::DescriptorSet * descriptorSet () const noexcept override;

			/**
			 * @brief Enables the vertex color.
			 * @return void
			 */
			void enableVertexColor () noexcept;

			/**
			 * @brief Sets a color as material apparence.
			 * @param color A reference to a color.
			 * @return void
			 */
			void setColor (const Libraries::PixelFactory::Color< float > & color) noexcept;

			/**
			 * @brief Sets a texture as material apparence.
			 * @param color A reference to a texture resource smart pointer.
			 * @param enableAlpha Enable the use of alpha channel for opacity/blending operation. Default false.
			 * @return bool
			 */
			[[nodiscard]]
			bool setTexture (const std::shared_ptr< TextureResource::Abstract > & texture, bool enableAlpha = false) noexcept;

			/**
			 * @brief Sets the global material auto-illumination amount.
			 * @param amount A value.
			 * @return void
			 */
			void setAutoIlluminationAmount (float amount) noexcept;

			/**
			 * @brief Returns the global material auto-illumination value.
			 * @return float
			 */
			[[nodiscard]]
			float autoIlluminationAmount () noexcept;

			/**
			 * @brief Sets the global material opacity value.
			 * @param value A value between 0.0 and 1.0.
			 * @return void
			 */
			void setOpacity (float value) noexcept;

			/**
			 * @brief ComponentTypeInterface material opacity value.
			 * @return float
			 */
			[[nodiscard]]
			float opacity () noexcept;

			/**
			 * @brief Returns a basic material resource by its name.
			 * @param resourceName A reference to a string.
			 * @param directLoad Use the direct loading mode. Default false.
			 * @return std::shared_ptr< BasicResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< BasicResource > get (const std::string & resourceName, bool directLoad = false) noexcept;

			/**
			 * @brief Returns the default basic material resource.
			 * @return std::shared_ptr< BasicResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< BasicResource > getDefault () noexcept;

			/**
			 * @brief Gets the material uniform block.
			 * @param set The set number used in the descriptor set.
			 * @param binding The binding used number the in descriptor set. Default = 0.
			 * @return Saphir::Declaration::UniformBlock
			 */
			[[nodiscard]]
			static Saphir::Declaration::UniformBlock getMaterialUniformBlock (uint32_t set, uint32_t binding = 0) noexcept;

		private:

			/**
			 * @brief Updates the UBO with material properties.
			 * @return void
			 */
			bool updateVideoMemory () noexcept;

			/**
			 * @brief Adds the material into the shared uniform buffer.
			 * @return bool
			 */
			[[nodiscard]]
			bool registerToSharedUniformBuffer () noexcept;

			/**
			 * @brief Removes the material from the shared uniform buffer.
			 * @return void
			 */
			void unregisterFromSharedUniformeBuffer () noexcept;

			/**
			 * @brief Creates the basic material shared uniform buffer.
			 * @return bool
			 */
			[[nodiscard]]
			static bool createSharedUniformBuffer () noexcept;

			/**
			 * @brief Destroys the basic material shared uniform.
			 * @return void
			 */
			static void destroySharedUniformBuffer () noexcept;

			static std::unique_ptr< Vulkan::SharedUniformBuffer > s_sharedUniformBuffer;

			std::shared_ptr< Vulkan::DescriptorSetLayout > m_descriptorSetLayout{};
			std::unique_ptr< Vulkan::DescriptorSet > m_descriptorSet{};
			Physics::PhysicalSurfaceProperties m_physicalSurfaceProperties{};
			std::unique_ptr< Component::TypeTexture > m_textureComponent{};
			BlendingMode m_blendingMode{BlendingMode::None};
			// NOLINTBEGIN(*-magic-numbers)
			std::array< float, 8 > m_materialProperties{
				// Color (4)
				0.3F, 0.3F, 0.3F, 1.0F,
				// Opacity, auto-illumination, unused, unused.
				1.0F, 0.0F, 0.0F, 0.0F
			};
			// NOLINTEND(*-magic-numbers)
			uint32_t m_sharedUBOIndex{0};
			bool m_dynamicColorEnabled{false};
	};
}

/* Expose the resource manager as a convenient type. */
namespace Emeraude::Resources
{
	using BasicMaterials = Container< Graphics::Material::BasicResource >;
}
