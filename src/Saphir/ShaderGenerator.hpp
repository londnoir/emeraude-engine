/*
 * Emeraude/Saphir/ShaderGenerator.hpp
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
#include <set>
#include <string>

/* Local inclusions for inheritances. */
#include "CodeGeneratorInterface.hpp"

/* Local inclusions for usages. */
#include "emeraude_config.hpp"
#include "Math/Vector.hpp"
#include "PixelFactory/Color.hpp"
#include "Types.hpp"
#include "Graphics/Types.hpp"
#include "Code.hpp"

/* GLSL Stages */
#include "VertexShader.hpp"
#include "TesselationControlShader.hpp"
#include "TesselationEvaluationShader.hpp"
#include "GeometryShader.hpp"
#include "FragmentShader.hpp"
#include "ComputeShader.hpp"
#include "EffectInterface.hpp"
/* GLSL data type or helpers */
#include "Keys.hpp"
#include "SetIndexes.hpp"
#include "Declaration/SpecializationConstant.hpp"
#include "Declaration/Structure.hpp"
#include "Declaration/Sampler.hpp"
#include "Declaration/UniformBlock.hpp"
#include "Declaration/ShaderStorageBlock.hpp"
#include "Declaration/InputAttribute.hpp"
#include "Declaration/InputPrimitive.hpp"
#include "Declaration/InputBlock.hpp"
#include "Declaration/StageInput.hpp"
#include "Declaration/OutputPrimitive.hpp"
#include "Declaration/OutputBlock.hpp"
#include "Declaration/StageOutput.hpp"
#include "Declaration/OutputFragment.hpp"
#include "Declaration/Function.hpp"
#include "Declaration/TexelBuffer.hpp"
#include "Declaration/PushConstantBlock.hpp"

namespace Emeraude::Saphir
{
	/**
	 * @brief This class generates saphir shaders in GLSL.
	 */
	class ShaderGenerator final : public CodeGeneratorInterface
	{
		public:

			static constexpr auto ClassId{"ShaderGenerator"};

			/* Settings keys */
			static constexpr auto GLSLVersionKey = "Video/Shader/Generator/GLSLVersion";
			static constexpr auto DefaultGLSLVersion = "460";
			static constexpr auto GLSLProfileKey = "Video/Shader/Generator/GLSLProfile";
			static constexpr auto DefaultGLSLProfile = "core";
			static constexpr auto HighQualityReflectionEnabledKey = "Video/Shader/Generator/HighQualityReflectionEnabled";
			static constexpr auto DefaultHighQualityReflectionEnabled = false;
			static constexpr auto HighQualityLightShaderEnabledKey = "Video/Shader/Generator/HighQualityLightShaderEnabled";
			static constexpr auto DefaultHighQualityLightShaderEnabled = false;
			static constexpr auto NormalMappingEnabledKey = "Video/Shader/Generator/NormalMappingEnabled";
			static constexpr auto DefaultNormalMappingEnabled = true;
			static constexpr auto DisplayDataTransactionErrorsKey = "Video/Shader/Generator/DisplayDataTransactionErrors";
			static constexpr auto DefaultDisplayDataTransactionErrors = BOOLEAN_FOLLOWING_DEBUG;

			/** @brief Defines the scope of a synthesized variable. */
			enum class VariableScope
			{
				/** @brief The variable is only used in the current shader. */
				Local,
				/** @brief The variable is only an output for the next stage. */
				ToNextStage,
				/** @brief The variable is used in the shader and an output for the next stage. */
				Both
			};

			/**
			 * @brief Constructs a generator for a specific shader.
			 * @param shader A reference to shader smart pointer to generate.
			 */
			explicit ShaderGenerator (const std::shared_ptr< AbstractShader > & shader) noexcept;

			/**
			 * @brief Constructs a generator for a specific shader with GLSL version and profile specified.
			 * @param shader A reference to shader smart pointer to generate.
			 * @param version A string for the GLSL version, example "460" [std::move].
			 * @param profile A string for the GLSL compilation profile, example "core" [std::move].
			 */
			ShaderGenerator (const std::shared_ptr< AbstractShader > & shader, std::string version, std::string profile) noexcept;

			/**
			 * @brief Constructs a generator for a specific shader.
			 * @param shader A reference to shader smart pointer to generate.
			 * @param modelMatricesType Describes how the model data will be available to the shader, useful for vertex an geometry stages.
			 * @param renderPassType Describes the lighting strategy.
			 */
			ShaderGenerator (const std::shared_ptr< AbstractShader > & shader, Graphics::ModelMatrixType modelMatricesType, Graphics::RenderPassType renderPassType) noexcept;

			/**
			 * @brief Constructs a generator for a specific shader.
			 * @param shader A reference to shader smart pointer to generate.
			 * @param modelMatricesType Describes how the model data will be available to the shader, useful for vertex an geometry stages.
			 * @param renderPassType Describes the lighting strategy.
			 * @param version A string for the GLSL version, example "460" [std::move].
			 * @param profile A string for the GLSL compilation profile, example "core" [std::move].
			 */
			ShaderGenerator (const std::shared_ptr< AbstractShader > & shader, Graphics::ModelMatrixType modelMatricesType, Graphics::RenderPassType renderPassType, std::string version, std::string profile) noexcept;

			/**
			 * @brief Returns the type of shader being generated.
			 * @return Type
			 */
			[[nodiscard]]
			ShaderType shaderType () const noexcept;

			/**
			 * @brief Returns the name of shader being generated.
			 * @return Type
			 */
			[[nodiscard]]
			std::string shaderName () const noexcept;

			/**
			 * @brief Sets the set indexes.
			 * @param setIndexes A reference to a set indexes.
			 * @return void
			 */
			void setIndexes (const SetIndexes & setIndexes) noexcept;

			/**
			 * @brief Returns the set indexes.
			 * @return const SetIndexes &
			 */
			[[nodiscard]]
			const SetIndexes & indexes () const noexcept;

			/**
			 * @brief Returns the model matrices type of the current shader being generated.
			 * @return ModelMatricesType
			 */
			[[nodiscard]]
			Graphics::ModelMatrixType modelMatricesType () const noexcept;

			/**
			 * @brief Returns the render pass type of the current shader being generated.
			 * @return RenderPassType
			 */
			[[nodiscard]]
			Graphics::RenderPassType renderPassType () const noexcept;

			/**
			 * @brief Sets a GLSL extension behavior.
			 * @param extension The target extension.
			 * @param behavior The behavior.
			 * @return void
			 */
			void setExtensionBehavior (const char * extension, const char * behavior = nullptr) noexcept;

			/**
			 * @brief Returns the name of the output fragment.
			 * @note Only useful with fragment shader.
			 * @return const char *
			 */
			[[nodiscard]]
			const char * outputFragment () const noexcept;

			/**
			 * @brief Declare a specialization constant to be used in the shader.
			 * @param declaration A reference to a SpecializationConstant.
			 * @return bool
			 */
			bool declare (const Declaration::SpecializationConstant & declaration) noexcept;

			/**
			 * @brief Declare a structure to be used in the shader.
			 * @param declaration A reference to a ShaderStructure.
			 * @return bool
			 */
			bool declare (const Declaration::Structure & declaration) noexcept;

			/**
			 * @brief Declares a sampler to be used in the shader.
			 * @param declaration A reference to a Sampler.
			 * @return bool
			 */
			bool declare (const Declaration::Sampler & declaration) noexcept;

			/**
			 * @brief Declares an uniform block to be used in the shader.
			 * @param declaration A reference to a ShaderUniformBlock.
			 * @return bool
			 */
			bool declare (const Declaration::UniformBlock & declaration) noexcept;

			/**
			 * @brief Declares a shader storage block to be used in the shader.
			 * @param declaration A reference to a shader storage block.
			 * @return bool
			 */
			bool declare (const Declaration::ShaderStorageBlock & declaration) noexcept;

			/**
			 * @brief Declares a vertex attribute to be used in a vertex shader.
			 * @warning Will return false on other type of shader than vertex.
			 * @param declaration A reference to a shader input attribute.
			 * @return bool
			 */
			bool declare (const Declaration::InputAttribute & declaration) noexcept;

			/**
			 * @brief Declares an input primitive to be used in a geometry shader.
			 * @warning Will return false on other type of shader than geometry.
			 * @param declaration A reference to a ShaderInputPrimitive.
			 * @return bool
			 */
			bool declare (const Declaration::InputPrimitive & declaration) noexcept;

			/**
			 * @brief Declares an input block to be used in the shader.
			 * @param declaration A reference to a InputBlock.
			 * @return bool
			 */
			bool declare (const Declaration::InputBlock & declaration) noexcept;

			/**
			 * @brief Declares an stage input variable to be used in the shader.
			 * @warning Will return false if the type of the shader is vertex. There is no previous stage there.
			 * @param declaration A reference to a ShaderStageInput.
			 * @return bool
			 */
			bool declare (const Declaration::StageInput & declaration) noexcept;

			/**
			 * @brief Declares an output primitive to be used in the shader.
			 * @warning Will return false on other type of shader than geometry.
			 * @param declaration A reference to a ShaderOutputPrimitive.
			 * @return bool
			 */
			bool declare (const Declaration::OutputPrimitive & declaration) noexcept;

			/**
			 * @brief Declares an output block to be used in the shader.
			 * @param declaration A reference to a OutputBlock.
			 * @return bool
			 */
			bool declare (const Declaration::OutputBlock & declaration) noexcept;

			/**
			 * @brief Declares an stage output variable to be used in the shader.
			 * @warning Will return false if the type of the shader is fragment. There is no more stage after it.
			 * @param declaration A reference to a ShaderStageOutput.
			 * @return bool
			 */
			bool declare (const Declaration::StageOutput & declaration) noexcept;

			/**
			 * @brief Declares a fragment output to be used in a fragment shader.
			 * @warning Will return false on other type of shader than fragment.
			 * @param declaration A reference to a OutputBlock.
			 * @return bool
			 */
			bool declare (const Declaration::OutputFragment & declaration) noexcept;

			/**
			 * @brief Requests a synthesize instruction in a vertex shader.
			 * @warning This function is recursive for the variable "PositionTextureSpace".
			 * @param variableName The variable name to synthesize. This should be a key from Keys::ShaderVariables namespace.
			 * @param scope Set the variable scope in the vertex shader. Default VariableScope::ToNextStage.
			 * @return bool
			 */
			bool requestVertexShaderSynthesizeInstruction (const char * variableName, VariableScope scope = VariableScope::ToNextStage) noexcept;

			/**
			 * @brief Declares default output fragment.
			 * @return bool
			 */
			inline
			bool
			declareDefaultOutputFragment () noexcept
			{
				return this->declare(Declaration::OutputFragment{0, Keys::GLSL::FloatVector4, Keys::ShaderVariables::OutputFragment});
			}

			/**
			 * @brief Declares a function to be used in the shader.
			 * @param declaration A reference to a ShaderFunction.
			 * @return bool
			 */
			bool declare (const Declaration::Function & declaration) noexcept;

			/**
			 * @brief Declares a texel buffer to be used in the shader (Vulkan only).
			 * @param declaration A reference to a texel buffer.
			 * @return bool
			 */
			bool declare (const Declaration::TexelBuffer & declaration) noexcept;

			/**
			 * @brief Declares a push constant block to be used in the shader (Vulkan only).
			 * @param declaration A reference to a push constant block.
			 * @return bool
			 */
			bool declare (const Declaration::PushConstantBlock & declaration) noexcept;

			/**
			 * @brief Applies a list of effect to a shader.
			 * @param effectsList The list of effect to apply.
			 * @return bool
			 */
			bool applyEffectsList (const EffectsList & effectsList) noexcept;

			/**
			 * @brief Generates and returns the shader source code in GLSL.
			 * @return std::string
			 */
			[[nodiscard]]
			std::string generateSourceCode () noexcept;

			/**
			 * @brief Writes the source code to the targeted shader.
			 * @return bool
			 */
			bool writeShader () noexcept;

			/**
			 * @brief Returns a shader variable location for a variable name.
			 * @param shaderVariable The name of a shader variable. See Emeraude::Saphir::Keys::ShaderVariables enumeration.
			 * @return uint32_t
			 */
			[[nodiscard]]
			static uint32_t getShaderVariableLocation (Key shaderVariable) noexcept;

			/**
			 * @brief Returns a shader variable location for a variable name.
			 * @param shaderVariable The name of a shader variable. See Emeraude::Saphir::Keys::ShaderVariables enumeration.
			 * @return Key
			 */
			[[nodiscard]]
			static Key getShaderVariableType (Key shaderVariable) noexcept;

			/**
			 * @brief Returns the full variable name from a view uniform block.
			 * @param componentName A c-string for the desired component.
			 * @return std::string
			 */
			[[nodiscard]]
			static std::string viewUniform (const char * componentName) noexcept;

			/**
			 * @brief Returns the full variable name from an indexed view uniform block.
			 * @param memberName A c-string for the desired member.
			 * @param indexVariableName
			 * @param componentName A c-string for the desired component.
			 * @return std::string
			 */
			[[nodiscard]]
			static std::string viewIndexedUniform (const char * memberName, const char * indexVariableName, const char * componentName) noexcept;

			/**
			 * @brief Returns the full variable name from a model uniform block.
			 * @param componentName A c-string for the desired component.
			 * @return std::string
			 */
			[[nodiscard]]
			static std::string modelUniform (const char * componentName) noexcept;

			/**
			 * @brief Returns the full variable name from a material uniform block.
			 * @param componentName A c-string for the desired component.
			 * @return std::string
			 */
			[[nodiscard]]
			static std::string materialUniform (const char * componentName) noexcept;

			/**
			 * @brief Returns the number of declarations type in a string.
			 * @return std:string;
			 */
			[[nodiscard]]
			std::string getDeclarationStats () const noexcept;

		private:

			/**
			 * @brief Generates final unique instructions.
			 * @param topInstructions A reference to the top instructions string.
			 * @param outputInstructions  A reference to the output instructions string.
			 * @return bool
			 */
			[[nodiscard]]
			bool generateMainUniqueInstructions (std::string & topInstructions, std::string & outputInstructions) noexcept;

			/**
			 * @brief Generates the shader file header.
			 * @param code A reference to a stream.
			 * @return void
			 */
			void generateHeaders (std::stringstream & code) const noexcept;

			/**
			 * @brief Generates shader declarations.
			 * @tparam declaration_t The type of declaration. This should be derived from Declaration::Interface.
			 * @param code A reference to a stream.
			 * @param declarations A reference to a list of declaration.
			 * @param comment A section comment. Default none.
			 * @return void
			 */
			template< typename declaration_t, std::enable_if_t< std::is_base_of_v< Declaration::Interface, declaration_t >, bool > = false >
			static
			void
			generateDeclarations (std::stringstream & code, const std::vector< declaration_t > & declarations, const char * comment = nullptr) noexcept
			{
				if ( declarations.empty() )
				{
					code << "/* No " << comment << " */" "\n\n";

					return;
				}

				if ( comment != nullptr )
				{
					code << "/* " << comment << " */" "\n";
				}

				for ( const auto & declaration : declarations )
				{
					code << declaration.sourceCode();
				}

				code << '\n';
			}

			/**
			 * @brief Creates a local variable for modelView matrix with VBO.
			 * @return bool
			 */
			[[nodiscard]]
			bool prepareModelViewMatrixFromVBO () noexcept;

			/**
			 * @brief Creates a local variable for normal matrix with VBO.
			 * @return bool
			 */
			[[nodiscard]]
			bool prepareNormalMatrixFromVBO () noexcept;

			/**
			 * @brief Creates a local variable for modelViewProjection matrix with VBO.
			 * @return bool
			 */
			[[nodiscard]]
			bool prepareModelViewProjectionMatrixFromVBO () noexcept;

			/**
			 * @brief Synthesizes instructions before generating the final source code.
			 * @param topInstructions Every instructions that should be on the top of the main() function.
			 * @param outputInstructions Every instructions that should be at the end of the main() function.
			 * @return bool
			 */
			bool synthesizeRequestInstructions (std::string & topInstructions, std::string & outputInstructions) noexcept;

			/**
			 * @brief Synthesizes the vertex position in world space in the vertex shader.
			 * @note gl_Position = gl_modelMatrix * gl_Vertex;
			 * @param topInstructions Every instructions that should be on the top of the main() function.
			 * @param outputInstructions Every instructions that should be at the end of the main() function.
			 * @param scope Set the variable scope in the vertex shader.
			 * @param asGLStandardPosition Synthesize as gl_Position for specific shaders.
			 * @return bool
			 */
			bool synthesizeVertexPositionInWorldSpace (std::string & topInstructions, std::string & outputInstructions, VariableScope scope, bool asGLStandardPosition = false) noexcept;

			/**
			 * @brief Synthesizes the vertex position in view space in the vertex shader.
			 * @note gl_Position = gl_modelViewMatrix * gl_Vertex;
			 * @param topInstructions Every instructions that should be on the top of the main() function.
			 * @param outputInstructions Every instructions that should be at the end of the main() function.
			 * @param scope Set the variable scope in the vertex shader.
			 * @return bool
			 */
			bool synthesizeVertexPositionInViewSpace (std::string & topInstructions, std::string & outputInstructions, VariableScope scope) noexcept;

			/**
			 * @brief Synthesizes the vertex position in screen space in the vertex shader.
			 * @note gl_Position = gl_modelViewProjectionMatrix * gl_Vertex;
			 * @param outputInstructions Every instructions that should be at the end of the main() function.
			 * @return bool
			 */
			bool synthesizeVertexPositionInScreenSpace (std::string & outputInstructions) noexcept;

			/**
			 * @brief Synthesizes the vertex position in texture space in the vertex shader.
			 * @note gl_Position = gl_modelViewProjectionMatrix * gl_Vertex;
			 * @param topInstructions Every instructions that should be on the top of the main() function.
			 * @param outputInstructions Every instructions that should be at the end of the main() function.
			 * @param scope Set the variable scope in the vertex shader.
			 * @return bool
			 */
			bool synthesizeVertexPositionInTextureSpace (std::string & topInstructions, std::string & outputInstructions, VariableScope scope) noexcept;

			/**
			 * @brief Synthesizes the vertex color in the vertex shader.
			 * @note This will not generate a local variable.
			 * @param outputInstructions Every instructions that should be at the end of the main() function.
			 * @return bool
			 */
			bool synthesizeVertexColor (std::string & outputInstructions) noexcept;

			/**
			 * @brief Synthesizes the vertex texture coordinates in the vertex shader.
			 * @note This will not generate a local variable.
			 * @param outputInstructions Every instructions that should be at the end of the main() function.
			 * @param TCVariableName The name of the texture coordinates variable.
			 * @return bool
			 */
			bool synthesizeVertexTextureCoordinates (std::string & outputInstructions, const char * TCVariableName) noexcept;

			/**
			 * @brief Synthesizes the vertex tangent, bi-normal or normal vector in world space in the vertex shader.
			 * @param topInstructions Every instructions that should be on the top of the main() function.
			 * @param outputInstructions Every instructions that should be at the end of the main() function.
			 * @param vectorType The vector type to generate.
			 * @param scope Set the variable scope in the vertex shader.
			 * @return bool
			 */
			bool synthesizeVertexVectorInWorldSpace (std::string & topInstructions, std::string & outputInstructions, Graphics::VertexAttributeType vectorType, VariableScope scope) noexcept;

			/**
			 * @brief Synthesizes the vertex tangent, bi-normal or normal vector in view space variable in the vertex shader.
			 * @param topInstructions Every instructions that should be on the top of the main() function.
			 * @param outputInstructions Every instructions that should be at the end of the main() function.
			 * @param vectorType The vector type to generate.
			 * @param scope Set the variable scope in the vertex shader.
			 * @return bool
			 */
			bool synthesizeVertexVectorInViewSpace (std::string & topInstructions, std::string & outputInstructions, Graphics::VertexAttributeType vectorType, VariableScope scope) noexcept;

			/**
			 * @brief synthesizeWorldTBNMatrix
			 * @param topInstructions
			 * @param outputInstructions
			 * @param scope
			 * @return bool
			 */
			bool synthesizeWorldTBNMatrix (std::string & topInstructions, std::string & outputInstructions, VariableScope scope) noexcept;

			/**
			 * @brief synthesizeViewTBNMatrix
			 * @param topInstructions
			 * @param outputInstructions
			 * @param scope
			 * @return bool
			 */
			bool synthesizeViewTBNMatrix (std::string & topInstructions, std::string & outputInstructions, VariableScope scope) noexcept;

			/**
			 * @brief Synthesizes the matrix to get the vertex normal in world space from normal map.
			 * @param outputInstructions Every instructions that should be at the end of the main() function.
			 * @return bool
			 */
			bool synthesizeWorldToTangentMatrix (std::string & topInstructions, std::string & outputInstructions, VariableScope scope) noexcept;

			/**
			 * @brief Checks whether a synthetic variable is allowed.
			 * @param variableName A pointer to a C-string for the variable name.
			 * @return bool
			 */
			[[nodiscard]]
			static bool isSyntheticVariableAllowed (const char * variableName) noexcept;

			std::shared_ptr< Saphir::AbstractShader > m_shaderTarget;
			std::string m_version;
			std::string m_profile;
			SetIndexes m_indexes{};
			Graphics::ModelMatrixType m_modelMatricesType = Graphics::ModelMatrixType::UniformBufferObject;
			Graphics::RenderPassType m_renderPassType = Graphics::RenderPassType::None;
			std::vector< std::string > m_headers{};
			std::vector< std::pair< const char *, std::string > > m_uniquePreparations{}; // ie normalMatrix for VBO
			std::vector< std::pair< const char *, VariableScope > > m_requests{};
			std::vector< Declaration::Function > m_functions{};
			std::vector< Declaration::Structure > m_structures{};
			std::vector< Declaration::UniformBlock > m_uniformBlocks{};
			std::vector< Declaration::ShaderStorageBlock > m_shaderStorageBlocks{};
			std::vector< Declaration::InputBlock > m_inputBlocks{};
			std::vector< Declaration::OutputBlock > m_outputBlocks{};
			std::vector< Declaration::PushConstantBlock > m_pushConstantBlocks{}; // FIXME: Only one is authorized !
			std::vector< Declaration::SpecializationConstant > m_specializationConstants{};
			std::vector< Declaration::Sampler > m_samplers{};
			std::vector< Declaration::TexelBuffer > m_texelBuffers{};
			std::vector< Declaration::StageInput > m_stageInputs{};
			std::vector< Declaration::StageOutput > m_stageOutputs{};
			std::vector< Declaration::InputAttribute > m_inputAttributes{};
			std::vector< Declaration::InputPrimitive > m_inputPrimitives{};
			std::vector< Declaration::OutputPrimitive > m_outputPrimitives{};
			std::vector< Declaration::OutputFragment > m_outputFragments{};
	};
}
