/*
 * src/Saphir/Generator/Abstract.hpp
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
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

/* Local inclusions for inheritances. */
#include "Libs/NameableTrait.hpp"

/* Local inclusions for usages. */
#include "Graphics/Geometry/Interface.hpp"
#include "Graphics/Material/Interface.hpp"
#include "Saphir/AbstractShader.hpp"
#include "Saphir/Program.hpp"
#include "Saphir/SetIndexes.hpp"

namespace EmEn
{
	namespace Graphics
	{
		namespace RenderTarget
		{
			class Abstract;
		}

		class VertexBufferFormatManager;
		class Renderer;
	}

	namespace Vulkan
	{
		class DescriptorSetLayout;
	}

	class Settings;
}

namespace EmEn::Saphir::Generator
{
	/**
	 * @brief The base class for every shader program generator.
	 * @extends EmEn::Libs::NameableTrait This will hold the name of the program generated.
	 */
	class Abstract : public Libs::NameableTrait
	{
		public:

			static constexpr auto DefaultGLSLVersion{"460"};
			static constexpr auto DefaultGLSLProfile{"core"};

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Abstract (const Abstract & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Abstract (Abstract && copy) noexcept = default;

			/**
			 * @brief Assignment operator.
			 * @param copy A reference to the copied instance.
			 * @return Abstract &
			 */
			Abstract & operator= (const Abstract & copy) noexcept = default;

			/**
			 * @brief Move operator.
			 * @param copy A reference to the copied instance.
			 * @return Abstract &
			 */
			Abstract & operator= (Abstract && copy) noexcept = default;

			/** 
			 * @brief Destructs the abstract shader generator.
			 */
			~Abstract () override = default;

			/**
			 * @brief Enables debugging. This will print stats and generated source code.
			 * @param state The state
			 * @return void
			 */
			void
			enableDebugging (bool state) noexcept
			{
				m_flags[Debug] = state;
			}

			/**
			 * @brief Returns whether the debugging is enabled.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			debuggingEnabled () const noexcept
			{
				return m_flags[Debug];
			}

			/**
			 * @brief Returns whether the use of normal mapping is allowed.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			normalMappingEnabled () const noexcept
			{
				return m_flags[NormalMappingEnabled];
			}

			/**
			 * @brief Returns whether the light shader generation is high quality (most operation is performed per-fragment).
			 * @return bool
			 */
			[[nodiscard]]
			bool
			highQualityLightEnabled () const noexcept
			{
				return m_flags[HighQualityLightEnabled];
			}

			/**
			 * @brief Returns whether the reflection shader generation is high quality (most operation is performed per-fragment).
			 * @return bool
			 */
			[[nodiscard]]
			bool
			highQualityReflectionEnabled () const noexcept
			{
				return m_flags[HighQualityReflectionEnabled];
			}

			/**
			 * @brief Returns the render target pointer.
			 * @return std::shared_ptr< const Graphics::RenderTarget::Abstract >
			 */
			[[nodiscard]]
			virtual
			std::shared_ptr< const Graphics::RenderTarget::Abstract >
			renderTarget () const noexcept
			{
				return m_renderTarget;
			}

			/**
			 * @brief Returns the shader program.
			 * @return std::shared_ptr< Program >
			 */
			[[nodiscard]]
			std::shared_ptr< Program >
			program () const noexcept
			{
				return m_program;
			}

			/**
			 * @brief Returns the next available location for shaders.
			 * @param increment The increment value for the next location. Default 1.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t getNextShaderVariableLocation (uint32_t increment = 1) noexcept;

			/**
			 * @brief Generates the program shaders source codes.
			 * @param vertexBufferFormatManager A reference to the vertex buffer format manager.
			 * @param GLSLVersion The GLSL version in use. Default "460".
			 * @param GLSLProfile The GLSL profile in use. Default "core".
			 * @return bool
			 */
			[[nodiscard]]
			bool generateProgram (Graphics::VertexBufferFormatManager & vertexBufferFormatManager, const std::string & GLSLVersion = DefaultGLSLVersion, const std::string & GLSLProfile = DefaultGLSLProfile) noexcept;

			/**
			 * @brief Generates all layout for the graphics pipeline.
			 * @param renderer A reference to the renderer to manage redundant layouts.
			 * @return bool
			 */
			[[nodiscard]]
			bool generateProgramLayout (Graphics::Renderer & renderer) noexcept;

			/**
			 * @brief Creates the final Vulkan graphics pipeline.
			 * @param renderer A reference to the renderer to manage redundant resources.
			 * @return bool
			 */
			[[nodiscard]]
			bool createGraphicsPipeline (Graphics::Renderer & renderer) noexcept;

			/**
			 * @brief Declares the view uniform block according to input information.
			 * @param shader A reference to a shader where to declare the uniform block.
			 * @param binding The binding point number. Default 0.
			 * @return bool
			 */
			[[nodiscard]]
			bool declareViewUniformBlock (AbstractShader & shader, uint32_t binding = 0) const noexcept;

			/**
			 * @brief Declares the view uniform block according to input information.
			 * @param material A reference to a material.
			 * @param shader A reference to a shader where to declare the uniform block.
			 * @param binding The binding point number. Default 0.
			 * @return bool
			 */
			[[nodiscard]]
			bool declareMaterialUniformBlock (const Graphics::Material::Interface & material, AbstractShader & shader, uint32_t binding = 0) const noexcept;

			/**
			 * @brief Declares the push constant block according to input information.
			 * @param shader A reference to a shader where to declare the uniform block.
			 * @return bool
			 */
			[[nodiscard]]
			bool declareMatrixPushConstantBlock (AbstractShader & shader) const noexcept;

			/**
			 * @brief Returns whether program will use an optional material.
			 * @note Can be overridden to return directly false.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool materialEnabled () const noexcept = 0;

			/**
			 * @brief Returns the material interface pointer.
			 * @note Should be overridden to use material.
			 * @warning Can be null, check with GraphicsShaderGenerator::materialEnabled().
			 * @return const Graphics::Material::Interface *
			 */
			[[nodiscard]]
			virtual const Graphics::Material::Interface * material () const noexcept = 0;

			/**
			 * @brief Returns the geometry interface pointer.
			 * @return const Graphics::Geometry::Interface *
			 */
			[[nodiscard]]
			virtual const Graphics::Geometry::Interface * geometry () const noexcept = 0;

		protected:

			/** 
			 * @brief Constructs an abstract shader generator.
			 * @param settings A reference to the core settings.
			 * @param name A reference to string for the program being generated.
			 * @param renderTarget A reference to a renderTarget smart pointer.
			 */
			Abstract (Settings & settings, const std::string & name, const std::shared_ptr< const Graphics::RenderTarget::Abstract > & renderTarget) noexcept;

			/**
			 * @brief Generates the fall-back vertex shader stage of the graphics pipeline.
			 * @param program A reference to the program being constructed.
			 * @return bool
			 */
			[[nodiscard]]
			bool generateFallBackVertexShader (Program & program) noexcept;

			/**
			 * @brief Generates the fall-back fragment shader stage of the graphics pipeline.
			 * @param program A reference to the program being constructed.
			 * @return bool
			 */
			[[nodiscard]]
			bool generateFallBackFragmentShader (Program & program) noexcept;

			/**
			 * @brief Prepares the uniform sets according to incoming rendering information.
			 * @param setIndexes A reference to the set indexes structure.
			 * @return void
			 */
			virtual void prepareUniformSets (SetIndexes & setIndexes) noexcept = 0;

			/**
			 * @brief Main method to generate program shaders.
			 * @param program A reference to the program being constructed.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool onGenerateProgram (Program & program) noexcept = 0;

			/**
			 * @brief Methods to override for generating specific program layout.
			 * @note The render target descriptor set layout is already present.
			 * @param setIndexes A reference to a set indexes structure.
			 * @param descriptorSetLayouts A reference to as list of descriptor set layouts to complete.
			 * @param pushConstantRanges A reference to as list of push constant ranges to complete.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool onGenerateProgramLayout (const SetIndexes & setIndexes, std::vector< std::shared_ptr< Vulkan::DescriptorSetLayout > > & descriptorSetLayouts, std::vector< VkPushConstantRange > & pushConstantRanges) noexcept = 0;

			/**
			 * @brief Configures the graphics pipeline from child shader generators.
			 * @param program A reference to the constructed program.
			 * @param graphicsPipeline A reference to the graphics pipeline to set up.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool onGraphicsPipelineConfiguration (const Program & program, Vulkan::GraphicsPipeline & graphicsPipeline) noexcept = 0;

			/**
			 * @brief Generates push constant ranges from push constant blocks code declaration.
			 * @todo: Check for a better way to use push constant from the right shader declaration to the right stage in vulkan, maybe store push constant at program level instead of shader.
			 * @param pushConstantBlocks A reference to a vector of push constant blocks.
			 * @param pushConstantRanges A reference to a vector of push constant ranges.
			 * @param stageFlags
			 * @return void
			 */
			static void generatePushConstantRanges (const std::vector< Declaration::PushConstantBlock > & pushConstantBlocks, std::vector< VkPushConstantRange > & pushConstantRanges, VkShaderStageFlags stageFlags) noexcept;

		private:

			/* Flag names */
			static constexpr auto Debug{0UL};
			static constexpr auto NormalMappingEnabled{1UL};
			static constexpr auto HighQualityLightEnabled{2UL};
			static constexpr auto HighQualityReflectionEnabled{3UL};

			std::shared_ptr< const Graphics::RenderTarget::Abstract > m_renderTarget;
			std::shared_ptr< Program > m_program;
			uint32_t m_nextShaderVariableLocation{0};
			std::array< bool, 8 > m_flags{
				false/*Debug*/,
				false/*NormalMappingEnabled*/,
				false/*HighQualityLightEnabled*/,
				false/*HighQualityReflectionEnabled*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
