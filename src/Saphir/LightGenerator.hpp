/*
 * Emeraude/Saphir/LightGenerator.hpp
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
#include <array>

/* Local inclusions for inheritances. */
#include "ShaderGenerationInterface.hpp"

/* Local inclusions for usages. */
#include "PixelFactory/Color.hpp"
#include "Graphics/Types.hpp"

namespace Emeraude::Saphir
{
	/**
	 * @brief Structure for fake lightning.
	 */
	struct BuiltInLightning
	{
		float ambientLevel;
		Libraries::PixelFactory::Color< float > ambientColor;
		Libraries::Math::Vector< 4, float > direction;
		Libraries::PixelFactory::Color< float > diffuseColor;
		Libraries::PixelFactory::Color< float > specularColor;
	};

	/**
	 * @brief The light model generator is responsible for generating
	 * GLSL lighting code independently from a light processor.
	 * @extends Emeraude::Saphir::ShaderGenerationInterface The light code model generation needs to interact with shader generations.
	 */
	class LightGenerator final : public ShaderGenerationInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"LightGenerator"};

			/**
			 * @brief Construct the light model generator.
			 */
			LightGenerator () noexcept;

			/**
			 * @brief Construct the light model generator and bypass the settings.
			 * @param highQualityEnabled
			 * @param normalMappingEnabled
			 * @param PCFSample
			 * @param PCFRadius
			 */
			LightGenerator (bool highQualityEnabled, bool normalMappingEnabled, unsigned int PCFSample, float PCFRadius) noexcept;

			/** @copydoc Emeraude::ShaderGenerationInterface::generateShaderCode() */
			[[nodiscard]]
			bool generateShaderCode (ShaderGenerator & gen, const Graphics::Geometry::Interface & geometry) const noexcept override;

			/**
			 * @brief Sets built-in lightning parameters.
			 * @param ambientLevel A float for the ambient level.
			 * @param ambientColor A reference to a color for ambient.
			 * @param direction A reference to a vector.
			 * @param diffuseColor A reference to a color for diffuse.
			 * @param specularColor A reference to a color for specular.
			 * @return void
			 */
			void setupBuiltInLightning (float ambientLevel, Libraries::PixelFactory::Color< float > ambientColor, Libraries::Math::Vector< 4, float > direction, Libraries::PixelFactory::Color< float > diffuseColor, Libraries::PixelFactory::Color< float > specularColor) noexcept;
			
			/**
			 * @brief Set the normal map in use.
			 * @warning This method will returns false when the normal mapping is not enabled.
			 * @param normalMap The variable name of normal map.
			 * @param textureCoordinates The variable name of texture coordinates used by normal map.
			 * @return bool
			 */
			bool useNormalMap (const std::string & normalMap, const std::string & textureCoordinates) noexcept;

			/**
			 * @brief Declares the use of specular component and parameters.
			 * @todo Check the usefulness of this method.
			 * @param shininessVariable The variable name of the shininess control.
			 * @return void
			 */
			void useSpecularComponent (const std::string & shininessVariable) noexcept;

		private:

			enum class DepthTextureFunction: int
			{
				Texture = 0,
				TextureProj = 1,
				TextureGather = 2
			};

			enum class LightType: int
			{
				Directional = 0,
				Point = 1,
				Spot = 2
			};

			/**
			 * @brief Declares light uniform block (UBO) for vertex and fragment shader stages.
			 * @param gen A reference to the shader generator.
			 * @param set The set number used in the descriptor set.
			 * @param bindingPoint The binding used number the in descriptor set.
			 * @return void
			 */
			void declareUniformBlocks (ShaderGenerator & gen, uint32_t set, uint32_t bindingPoint) const noexcept;

			/**
			 * @brief Declares shader output block for the vertex shader stage.
			 * @param gen A reference to the shader generator.
			 * @param type The type of the light.
			 * @param usingShadowMap Enables the shadow mapping code generation.
			 * @return void
			 */
			void declareOutputBlocks (ShaderGenerator & gen, LightType type, bool usingShadowMap) const noexcept;

			/**
			 * @brief Declares shader input block for the fragment shader stage.
			 * @param gen A reference to the shader generator.
			 * @param type The type of the light.
			 * @param usingShadowMap Enables the shadow mapping code generation.
			 * @return void
			 */
			void declareInputBlocks (ShaderGenerator & gen, LightType type, bool usingShadowMap) const noexcept;

			/**
			 * @brief Generates the vertex shader source code for one fixed directional light (Gouraud shading).
			 * @note Light calculation is done in vertex shader.
			 * @param gen A reference to the shader generator.
			 * @param geometry A reference to the geometry.
			 * @return void
			 */
			void generateBuiltInLightGouraudVertexShader (ShaderGenerator & gen, const Graphics::Geometry::Interface & geometry) const noexcept;

			/**
			 * @brief Generates the fragment shader source code for one fixed directional light (Gouraud shading).
			 * @note Light calculation is done in vertex shader (Gouraud shading).
			 * @param gen A reference to the shader generator.
			 * @return void
			 */
			void generateBuiltInLightGouraudFragmentShader (ShaderGenerator & gen) const noexcept;

			/**
			 * @brief Generates the vertex shader source code for one fixed directional light (Phong Shading).
			 * @note Light calculation is done in fragment shader.
			 * @param gen A reference to the shader generator.
			 * @param geometry A reference to the geometry.
			 * @return void
			 */
			void generateFakeLightHQVertexShader (ShaderGenerator & gen, const Graphics::Geometry::Interface & geometry) const noexcept;

			/**
			 * @brief Generates the fragment shader source code for one fixed directional light (Phong Shading).
			 * @note Light calculation is done in fragment shader.
			 * @param gen A reference to the shader generator.
			 * @return void
			 */
			void generateFakeLightHQFragmentShader (ShaderGenerator & gen) const noexcept;

			/**
			 * @brief Generates the vertex shader light source code.
			 * @param gen A reference to the shader generator.
			 * @param geometry A reference to the geometry.
			 * @param type The type of the light.
			 * @param usingShadowMap Enables the shadow mapping code generation.
			 * @return void
			 */
			void generateVertexShader (ShaderGenerator & gen, const Graphics::Geometry::Interface & geometry, LightType type, bool usingShadowMap) const noexcept;

			/**
			 * @brief Generates the fragment shader light source code.
			 * @param gen A reference to the shader generator.
			 * @param type The type of the light.
			 * @param usingShadowMap Enables the shadow mapping code generation.
			 * @return void
			 */
			void generateFragmentShader (ShaderGenerator & gen, LightType type, bool usingShadowMap) const noexcept;

			/**
			 * @brief generate2DShadowMapCode
			 * @param shadowMap
			 * @param fragmentPosition
			 * @param function
			 * @return std::string
			 */
			[[nodiscard]]
			std::string generate2DShadowMapCode (const std::string & shadowMap, const std::string & fragmentPosition, DepthTextureFunction function) const noexcept;

			/**
			 * @brief generate3DShadowMapCode
			 * @param shadowMap
			 * @param directionWorldSpace
			 * @param nearFar
			 * @return std::string
			 */
			[[nodiscard]]
			std::string generate3DShadowMapCode (const std::string & shadowMap, const std::string & directionWorldSpace, const std::string & nearFar) const noexcept;

			/**
			 * @brief Gets the right component for a light variable input.
			 * @param componentName The component name of the light.
			 * @return string
			 */
			[[nodiscard]]
			static std::string lightUniform (const char * componentName) noexcept;

			/**
			 * @brief Gets the right component for a light interstage variable.
			 * @param componentName The component name of the light.
			 * @return string
			 */
			[[nodiscard]]
			static std::string lightVariable (const char * componentName) noexcept;

			/**
			 * @brief Gets the right name for a light interstage variable.
			 * @param instanceName The instance name of the structure.
			 * @param componentName The component name of the light.
			 * @param index The index of the light. Only for multiple light by program.
			 * @return string
			 */
			[[nodiscard]]
			[[deprecated("Make a reduced code length function.")]]
			static std::string variable (const char * instanceName, const char * componentName, const char * index = nullptr) noexcept;

			/* Flag names. */
			static constexpr auto HighQualityEnabled = 0UL;
			static constexpr auto NormalMappingEnabled = 1UL;
			static constexpr auto UsingSpecularComponent = 2UL;
			static constexpr auto UsingNormalMap = 3UL;
			static constexpr auto DiscardBackFaceWithNormalMap = 4UL;

			/* Shader specific keys */
			static constexpr auto LightFinalColor = "lightFinalColor";
			static constexpr auto LightAmbientColor = "lightAmbientColor";
			static constexpr auto LightDiffuseColor = "lightDiffuseColor";
			static constexpr auto LightSpecularColor = "lightSpecularColor";
			static constexpr auto ShadowFactor = "ShadowFactor";
			static constexpr auto Distance = "Distance";
			static constexpr auto AttenuationFactor = "AttenuationFactor";
			static constexpr auto SpotFactor = "SpotFactor";

			unsigned int m_PCFSample{0};
			float m_PCFRadius{1.0F};
			std::string m_normalMap{};
			std::string m_normalMapTextureCoordinates{};
			std::string m_shininessVariable{};
			// NOLINTBEGIN(*-magic-numbers)
			BuiltInLightning m_builtInLightning{
				.ambientLevel = 0.10F,
				.ambientColor = Libraries::PixelFactory::ColorFromInteger< uint8_t, float >(57, 120, 235),
				.direction{-0.25F, -0.1F, -0.25F, 1.0F},
				.diffuseColor = Libraries::PixelFactory::ColorFromInteger< uint8_t, float >(255, 223, 175),
				.specularColor = Libraries::PixelFactory::ColorFromInteger< uint8_t, float >(255, 249, 240)
			};
			std::array< bool, 8 > m_flags{
				false/*HighQualityEnabled*/,
				false/*NormalMappingEnabled*/,
				false/*UsingSpecularComponent*/,
				false/*UsingNormalMap*/,
				true/*DiscardBackFaceWithNormalMap*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
			// NOLINTEND(*-magic-numbers)
	};
}
