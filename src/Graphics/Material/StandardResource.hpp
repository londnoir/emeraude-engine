/*
 * Emeraude/Graphics/Material/StandardResource.hpp
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
#include "Component/Interface.hpp"

namespace Emeraude::Graphics::Material
{
	/**
	 * @brief The standard material resource of the engine.
	 */
	class StandardResource final : public Interface
	{
		friend class Resources::Container< StandardResource >;

		using ResourceTrait::load;

		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"MaterialStandardResource"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs a material.
			 * @param name A reference to a string for the resource name.
			 * @param resourceFlagBits The resource flag bits. Default none.
			 */
			explicit StandardResource (const std::string & name, int resourceFlagBits = 0) noexcept;

			/**
			 * @brief Destructs the material.
			 */
			~StandardResource () override;

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
			bool generateShaderCode (Saphir::ShaderGenerator & generator, const Graphics::Geometry::Interface & geometry) const noexcept override;

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
			 * @brief Sets a color for the ambient, diffuse and ComponentTypeInterface.
			 * @param color A reference to a color.
			 * @param shininess A positive value. Default 32.0.
			 * @return void
			 */
			void setColor (const Libraries::PixelFactory::Color< float > & color, float shininess = 32.0F) noexcept;

			/**
			 * @brief Sets a color for the diffuse component and another for ambient and specular component.
			 * @param diffuseColor A reference to a color.
			 * @param altColor A reference to a color.
			 * @param shininess A positive value. Default 32.0.
			 * @return void
			 */
			void setColor (const Libraries::PixelFactory::Color< float > & diffuseColor, const Libraries::PixelFactory::Color< float > & altColor, float shininess = 32.0F) noexcept;

			/**
			 * @brief Sets a texture for the ambient, diffuse and specular component.
			 * @param texture A reference to a texture smart pointer.
			 * @param shininess A positive value. Default 32.0.
			 * @return void
			 */
			void setTexture (const std::shared_ptr< TextureResource::Abstract > & texture, float shininess = 32.0F) noexcept;

			/**
			 * @brief Sets a texture for the diffuse component and another for ambient and specular component.
			 * @param diffuseTexture A reference to a texture smart pointer.
			 * @param altTexture A reference to a texture smart pointer.
			 * @param shininess A positive value. Default 32.0.
			 * @return void
			 */
			void setTexture (const std::shared_ptr< TextureResource::Abstract > & diffuseTexture, const std::shared_ptr< TextureResource::Abstract > & altTexture, float shininess = 32.0F) noexcept;

			/**
			 * @brief Sets a texture for the diffuse component and a color for ambient and specular component.
			 * @param diffuseTexture A reference to a texture smart pointer.
			 * @param altColor A reference to a color.
			 * @param shininess A positive value. Default 32.0.
			 * @return void
			 */
			void setTexture (const std::shared_ptr< TextureResource::Abstract > & diffuseTexture, const Libraries::PixelFactory::Color< float > & altColor, float shininess = 32.0F) noexcept;

			/**
			 * @brief Sets the ambient component as a color.
			 * @param color A reference to a color.
			 * @return void
			 */
			void setAmbientComponent (const Libraries::PixelFactory::Color< float > & color) noexcept;

			/**
			 * @brief Sets the ambient component as a texture.
			 * @param texture A reference to a texture smart pointer.
			 * @return void
			 */
			void setAmbientComponent (const std::shared_ptr< TextureResource::Abstract > & texture) noexcept;

			/**
			 * @brief Sets the diffuse component as a color.
			 * @param color A reference to a color.
			 * @return void
			 */
			void setDiffuseComponent (const Libraries::PixelFactory::Color< float > & color) noexcept;

			/**
			 * @brief Sets the diffuse component as a texture.
			 * @param texture A reference to a texture smart pointer.
			 * @return void
			 */
			void setDiffuseComponent (const std::shared_ptr< TextureResource::Abstract > & texture) noexcept;

			/**
			 * @brief Sets the specular component as a color.
			 * @param color A reference to a color.
			 * @param shininess A positive value.
			 * @return void
			 */
			void setSpecularComponent (const Libraries::PixelFactory::Color< float > & color, float shininess = 32.0F) noexcept;

			/**
			 * @brief Sets the specular component as a texture.
			 * @param color A reference to a texture smart pointer.
			 * @param shininess A positive value. Default 32.0.
			 * @return void
			 */
			void setSpecularComponent (const std::shared_ptr< TextureResource::Abstract > & texture, float shininess = 32.0F) noexcept;

			/**
			 * @brief Sets the auto-illumination component as a value.
			 * @param value The initial amount of auto-illumination.
			 * @param amount The control amount. Default 100%.
			 * @return void
			 */
			void setAutoIlluminationComponent (float value, float amount = 1.0F) noexcept;

			/**
			 * @brief Sets the auto-illumination component as a color.
			 * @param color A reference to a color.
			 * @param amount The control amount. Default 100%.
			 * @return void
			 */
			void setAutoIlluminationComponent (const Libraries::PixelFactory::Color< float > & color, float amount = 1.0F) noexcept;

			/**
			 * @brief Sets the auto-illumination component as a texture.
			 * @param texture A reference to a texture smart pointer.
			 * @param amount The control amount. Default 100%.
			 * @return void
			 */
			void setAutoIlluminationComponent (const std::shared_ptr< TextureResource::Abstract > & texture, float amount = 1.0F) noexcept;

			/**
			 * @brief Sets the opacity component as a value.
			 * @param value The initial amount of opacity.
			 * @param amount The control amount. Default 100%.
			 * @return void
			 */
			void setOpacityComponent (float value, float amount = 1.0F) noexcept;

			/**
			 * @brief Sets the opacity component as a texure.
			 * @param texture A reference to a texture smart pointer.
			 * @param amount The control amount. Default 100%.
			 * @return void
			 */
			void setOpacityComponent (const std::shared_ptr< TextureResource::Abstract > & texture, float amount = 1.0F) noexcept;

			/**
			 * @brief Sets the normal component as a texure.
			 * @param texture A reference to a texture smart pointer.
			 * @param scale The scale value. Default 1.0.
			 * @return void
			 */
			void setNormalComponent (const std::shared_ptr< TextureResource::Abstract > & texture, float scale = 1.0F) noexcept;

			/**
			 * @brief Sets the reflection component as a texure.
			 * @param texture A reference to a texture smart pointer.
			 * @param amount The control amount. Default 50%.
			 * @return void
			 */
			void setReflectionComponent (const std::shared_ptr< TextureResource::Abstract > & texture, float amount = 0.5F) noexcept;

			/**
			 * @brief Returns a standard material resource by its name.
			 * @param resourceName A reference to a string.
			 * @param directLoad Use the direct loading mode. Default false.
			 * @return std::shared_ptr< StandardResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< StandardResource > get (const std::string & resourceName, bool directLoad = false) noexcept;

			/**
			 * @brief Returns the default standard material resource.
			 * @return std::shared_ptr< StandardResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< StandardResource > getDefault () noexcept;

		private:

			std::shared_ptr< Vulkan::DescriptorSetLayout > m_descriptorSetLayout{};
			std::unique_ptr< Vulkan::DescriptorSet > m_descriptorSet{};
			Physics::PhysicalSurfaceProperties m_physicalSurfaceProperties{};
			std::unordered_map< ComponentType, std::unique_ptr< Component::Interface > > m_components{};
			BlendingMode m_blendingMode{BlendingMode::None};
	};
}

/* Expose the resource manager as a convenient type. */
namespace Emeraude::Resources
{
	using StandardMaterials = Container< Graphics::Material::StandardResource >;
}
