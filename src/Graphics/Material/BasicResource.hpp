/*
 * src/Graphics/Material/BasicResource.hpp
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
#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>

/* Local inclusions for inheritances. */
#include "Interface.hpp"

/* Local inclusions for usages. */
#include "Libs/PixelFactory/Color.hpp"
#include "Saphir/Declaration/UniformBlock.hpp"
#include "Graphics/TextureResource/Abstract.hpp"
#include "Graphics/Types.hpp"
#include "Vulkan/SharedUniformBuffer.hpp"
#include "Physics/PhysicalSurfaceProperties.hpp"
#include "Resources/Container.hpp"
#include "Component/Texture.hpp"

namespace EmEn::Graphics::Material
{
	/**
	 * @brief The basic material class use only one component.
	 * @extends EmEn::Graphics::Material::Interface This is a material.
	 */
	class BasicResource final : public Interface
	{
		friend class Resources::Container< BasicResource >;

		using ResourceTrait::load;

		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"MaterialBasicResource"};

			/* Shader specific keys. */
			static constexpr auto SurfaceColor{"SurfaceColor"};

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
			 * @return BasicResource &
			 */
			BasicResource & operator= (const BasicResource & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return BasicResource &
			 */
			BasicResource & operator= (BasicResource && copy) noexcept = delete;

			/**
			 * @brief Destructs the basic material.
			 */
			~BasicResource () override;

			/** @copydoc EmEn::Libs::ObservableTrait::classUID() const */
			[[nodiscard]]
			size_t
			classUID () const noexcept override
			{
				return ClassUID;
			}

			/** @copydoc EmEn::Libs::ObservableTrait::is() const */
			[[nodiscard]]
			bool
			is (size_t classUID) const noexcept override
			{
				return classUID == ClassUID;
			}

			/** @copydoc EmEn::Resources::ResourceTrait::classLabel() const */
			[[nodiscard]]
			const char *
			classLabel () const noexcept override
			{
				return ClassId;
			}

			/** @copydoc EmEn::Resources::ResourceTrait::load() */
			bool load () noexcept override;

			/** @copydoc EmEn::Resources::ResourceTrait::load(const Json::Value &) */
			bool load (const Json::Value & data) noexcept override;

			/** @copydoc EmEn::Graphics::Material::Interface::create() */
			bool create (Renderer & renderer) noexcept override;

			/** @copydoc EmEn::Graphics::Material::Interface::destroy() */
			void destroy () noexcept override;

			/** @copydoc EmEn::Graphics::Material::Interface::isCreated() */
			[[nodiscard]]
			bool
			isCreated () const noexcept override
			{
				return this->isFlagEnabled(Created);
			}

			/** @copydoc EmEn::Graphics::Material::Interface::isComplex() */
			[[nodiscard]]
			bool
			isComplex () const noexcept override
			{
				return false;
			}

			/** @copydoc EmEn::Graphics::Material::Interface::setupLightGenerator() */
			[[nodiscard]]
			bool setupLightGenerator (Saphir::LightGenerator & lightGenerator) const noexcept override;

			/** @copydoc EmEn::Graphics::Material::Interface::generateVertexShaderCode() */
			[[nodiscard]]
			bool generateVertexShaderCode (Saphir::Generator::Abstract & generator, Saphir::VertexShader & vertexShader) const noexcept override;

			/** @copydoc EmEn::Graphics::Material::Interface::generateFragmentShaderCode() */
			[[nodiscard]]
			bool generateFragmentShaderCode (Saphir::Generator::Abstract & generator, Saphir::LightGenerator & lightGenerator, Saphir::FragmentShader & fragmentShader) const noexcept override;

			/** @copydoc EmEn::Graphics::Material::Interface::physicalSurfaceProperties() const */
			[[nodiscard]]
			const Physics::PhysicalSurfaceProperties &
			physicalSurfaceProperties () const noexcept override
			{
				return m_physicalSurfaceProperties;
			}

			/** @copydoc EmEn::Graphics::Material::Interface::physicalSurfaceProperties() */
			[[nodiscard]]
			Physics::PhysicalSurfaceProperties &
			physicalSurfaceProperties () noexcept override
			{
				return m_physicalSurfaceProperties;
			}

			/** @copydoc EmEn::Graphics::Material::Interface::frameCount() */
			[[nodiscard]]
			uint32_t frameCount () const noexcept override;

			/** @copydoc EmEn::Graphics::Material::Interface::duration() */
			[[nodiscard]]
			uint32_t duration () const noexcept override;

			/** @copydoc EmEn::Graphics::Material::Interface::frameIndexAt() */
			[[nodiscard]]
			uint32_t frameIndexAt (uint32_t sceneTime) const noexcept override;

			/** @copydoc EmEn::Graphics::Material::Interface::enableBlending() */
			void enableBlending (BlendingMode mode) noexcept override;

			/** @copydoc EmEn::Graphics::Material::Interface::blendingMode() */
			[[nodiscard]]
			BlendingMode blendingMode () const noexcept override;

			/** @copydoc EmEn::Graphics::Material::Interface::fragmentColor() */
			[[nodiscard]]
			std::string fragmentColor () const noexcept override;

			/** @copydoc EmEn::Graphics::Material::Interface::descriptorSetLayout() */
			[[nodiscard]]
			std::shared_ptr< Vulkan::DescriptorSetLayout >
			descriptorSetLayout () const noexcept override
			{
				return m_descriptorSetLayout;
			}

			/** @copydoc EmEn::Graphics::Material::Interface::UBOIndex() */
			[[nodiscard]]
			uint32_t
			UBOIndex () const noexcept override
			{
				return m_sharedUBOIndex;
			}

			/** @copydoc EmEn::Graphics::Material::Interface::UBOAlignment() */
			[[nodiscard]]
			uint32_t
			UBOAlignment () const noexcept override
			{
				return m_sharedUniformBuffer->blockAlignedSize();
			}

			/** @copydoc EmEn::Graphics::Material::Interface::UBOOffset() */
			[[nodiscard]]
			uint32_t
			UBOOffset () const noexcept override
			{
				return m_sharedUBOIndex * m_sharedUniformBuffer->blockAlignedSize();
			}

			/** @copydoc EmEn::Graphics::Material::Interface::descriptorSet() */
			[[nodiscard]]
			const Vulkan::DescriptorSet *
			descriptorSet () const noexcept override
			{
				//return m_sharedUniformBuffer->descriptorSet(m_sharedUBOIndex);
				return m_descriptorSet.get();
			}

			/** @copydoc EmEn::Graphics::Material::Interface::getUniformBlock() */
			[[nodiscard]]
			Saphir::Declaration::UniformBlock getUniformBlock (uint32_t set, uint32_t binding) const noexcept override;

			/**
			 * @brief Enables the vertex color.
			 * @return void
			 */
			void enableVertexColor () noexcept;

			/**
			 * @brief Sets a color as material appearance.
			 * @note Dynamic properties.
			 * @param color A reference to a color.
			 * @return bool
			 */
			bool setColor (const Libs::PixelFactory::Color< float > & color) noexcept;

			/**
			 * @brief Sets a texture as material appearance.
			 * @param texture A reference to a texture resource smart pointer.
			 * @param enableAlpha Enable the use of alpha channel for opacity/blending operation. Default false.
			 * @return bool
			 */
			bool setTexture (const std::shared_ptr< TextureResource::Abstract > & texture, bool enableAlpha = false) noexcept;

			/**
			 * @brief Sets a color for the specular component.
			 * @note Dynamic properties.
			 * @param color A reference to a color.
			 * @return bool
			 */
			bool setSpecularComponent (const Libs::PixelFactory::Color< float > & color) noexcept;

			/**
			 * @brief Sets a color for the specular component.
			 * @note Dynamic properties.
			 * @param color A reference to a color.
			 * @param shininess The shininess value.
			 * @return bool
			 */
			bool setSpecularComponent (const Libs::PixelFactory::Color< float > & color, float shininess) noexcept;

			/**
			 * @brief Sets the global material opacity value.
			 * @note Dynamic properties.
			 * @param value A value between 0.0 and 1.0.
			 * @return bool
			 */
			bool setOpacity (float value) noexcept;

			/**
			 * @brief Sets the shininess value.
			 * @note Dynamic properties.
			 * @param value A value between 0.0 and infinity.
			 * @return bool
			 */
			bool setShininess (float value) noexcept;

			/**
			 * @brief Sets the global material auto-illumination amount.
			 * @note Dynamic properties.
			 * @param amount A value.
			 * @return bool
			 */
			bool setAutoIlluminationAmount (float amount) noexcept;

			/**
			 * @brief Returns the diffuse color.
			 * @note Dynamic properties.
			 * @return Libraries::PixelFactory::Color< float >
			 */
			[[nodiscard]]
			Libs::PixelFactory::Color< float >
			diffuseColor () noexcept
			{
				return {
					m_materialProperties[DiffuseColorOffset],
					m_materialProperties[DiffuseColorOffset+1],
					m_materialProperties[DiffuseColorOffset+2],
					m_materialProperties[DiffuseColorOffset+3]
				};
			}

			/**
			 * @brief Returns the specular color.
			 * @note Dynamic properties.
			 * @return Libraries::PixelFactory::Color< float >
			 */
			[[nodiscard]]
			Libs::PixelFactory::Color< float >
			specularColor () noexcept
			{
				return {
					m_materialProperties[SpecularColorOffset],
					m_materialProperties[SpecularColorOffset+1],
					m_materialProperties[SpecularColorOffset+2],
					m_materialProperties[SpecularColorOffset+3]
				};
			}

			/**
			 * @brief Returns the material shininess value.
			 * @note Dynamic properties.
			 * @return float
			 */
			[[nodiscard]]
			float
			shininess () const noexcept
			{
				return m_materialProperties[ShininessOffset];
			}

			/**
			 * @brief ComponentTypeInterface material opacity value.
			 * @note Dynamic properties.
			 * @return float
			 */
			[[nodiscard]]
			float
			opacity () const noexcept
			{
				return m_materialProperties[OpacityOffset];
			}

			/**
			 * @brief Returns the global material auto-illumination value.
			 * @note Dynamic properties.
			 * @return float
			 */
			[[nodiscard]]
			float
			autoIlluminationAmount () const noexcept
			{
				return m_materialProperties[AutoIlluminationOffset];
			}

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

		private:

			/** @copydoc EmEn::Graphics::Material::Interface::getSharedUniformBufferIdentifier() */
			[[nodiscard]]
			std::string getSharedUniformBufferIdentifier () const noexcept override;

			/** @copydoc EmEn::Graphics::Material::Interface::createElementInSharedBuffer() */
			[[nodiscard]]
			bool createElementInSharedBuffer (Renderer & renderer, const std::string & identifier) noexcept override;

			/** @copydoc EmEn::Graphics::Material::Interface::createDescriptorSetLayout() */
			[[nodiscard]]
			bool createDescriptorSetLayout (Vulkan::LayoutManager & layoutManager, const std::string & identifier) noexcept override;

			/** @copydoc EmEn::Graphics::Material::Interface::createDescriptorSet() */
			[[nodiscard]]
			bool createDescriptorSet (Renderer & renderer, const Vulkan::UniformBufferObject & uniformBufferObject) noexcept override;

			/** @copydoc EmEn::Graphics::Material::Interface::onMaterialLoaded() */
			void onMaterialLoaded () noexcept override;

			/**
			 * @brief Creates the necessary data onto the GPU for this material.
			 * @param renderer A reference to the graphics renderer.
			 * @return bool
			 */
			[[nodiscard]]
			bool createVideoMemory (Renderer & renderer) noexcept;

			/**
			 * @brief Updates the UBO with material properties.
			 * @return void
			 */
			bool updateVideoMemory () const noexcept;

			/**
			 * @brief Generates the fragment shader code using a texture.
			 * @param fragmentShader A reference to the fragment shader.
			 * @param materialSet The set number of the material.
			 * @return bool
			 */
			[[nodiscard]]
			bool generateFragmentShaderCodeWithTexture (Saphir::FragmentShader & fragmentShader, uint32_t materialSet) const noexcept;

			/**
			 * @brief Generates the fragment shader code without texturing.
			 * @param fragmentShader A reference to the fragment shader.
			 * @return bool
			 */
			[[nodiscard]]
			bool generateFragmentShaderCodeWithoutTexture (Saphir::FragmentShader & fragmentShader) const noexcept;

			/* Flag names. */
			static constexpr auto DynamicColorEnabled{0UL};
			static constexpr auto EnableOpacity{1UL};
			static constexpr auto EnableAutoIllumination{2UL};

			/* Uniform buffer object offset to write data. */
			static constexpr auto DiffuseColorOffset{0UL};
			static constexpr auto SpecularColorOffset{4UL};
			static constexpr auto ShininessOffset{8UL};
			static constexpr auto OpacityOffset{9UL};
			static constexpr auto AutoIlluminationOffset{10UL};

			/* Default values. */
			static constexpr auto DefaultDiffuseColor{Libs::PixelFactory::Grey};
			static constexpr auto DefaultSpecularColor{Libs::PixelFactory::White};
			static constexpr auto DefaultShininess{200.0F};
			static constexpr auto DefaultOpacity{1.0F};
			static constexpr auto DefaultAutoIllumination{0.0F};

			Physics::PhysicalSurfaceProperties m_physicalSurfaceProperties;
			std::unique_ptr< Component::Texture > m_textureComponent;
			BlendingMode m_blendingMode{BlendingMode::None};
			std::array< float, 12 > m_materialProperties{
				/* Diffuse color (4), */
				DefaultDiffuseColor.red(), DefaultDiffuseColor.green(), DefaultDiffuseColor.blue(), DefaultDiffuseColor.alpha(),
				/* Specular color (4), */
				DefaultSpecularColor.red(), DefaultSpecularColor.green(), DefaultSpecularColor.blue(), DefaultSpecularColor.alpha(),
				/* Shininess (1), Opacity (1), AutoIlluminationColor (1), Unused (1). */
				DefaultShininess, DefaultOpacity, DefaultAutoIllumination, 0.0F
			};
			std::shared_ptr< Vulkan::DescriptorSetLayout > m_descriptorSetLayout;
			std::unique_ptr< Vulkan::DescriptorSet > m_descriptorSet;
			std::shared_ptr< Vulkan::SharedUniformBuffer > m_sharedUniformBuffer;
			uint32_t m_sharedUBOIndex{0};
			std::array< bool, 8 > m_flags{
				false/*DynamicColorEnabled*/,
				false/*EnableOpacity*/,
				false/*EnableAutoIllumination*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}

/* Expose the resource manager as a convenient type. */
namespace EmEn::Resources
{
	using BasicMaterials = Container< Graphics::Material::BasicResource >;
}
