/*
 * Emeraude/Saphir/ShaderGenerator.cpp
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

#include "ShaderGenerator.hpp"

/* C/C++ standard libraries. */
#include <sstream>
#include <utility>
#include <algorithm>
#include <cstring>

/* Local inclusions */
#include "Graphics/RenderTarget/ShadowMap/Texture2D.hpp"
#include "Graphics/RenderTarget/ShadowMap/Cubemap.hpp"
#include "Graphics/RenderTarget/Texture/Texture2D.hpp"
#include "Graphics/RenderTarget/Texture/Cubemap.hpp"
#include "Graphics/RenderTarget/View/Texture2D.hpp"
#include "Graphics/RenderTarget/View/Cubemap.hpp"
#include "Graphics/RenderableInstance/Unique.hpp"
#include "Settings.hpp"
#include "Tracer.hpp"

namespace Emeraude::Saphir
{
	using namespace Libraries;
	using namespace Graphics;
	using namespace Keys;
	using namespace Declaration;

	ShaderGenerator::ShaderGenerator (const std::shared_ptr< AbstractShader > & shader) noexcept
		: m_shaderTarget(shader)
	{
		auto * coreSettings = Settings::instance(SettingsType::Core);
		m_version = coreSettings->get(GLSLVersionKey, DefaultGLSLVersion);
		m_profile = coreSettings->get(GLSLProfileKey, DefaultGLSLProfile);
	}

	ShaderGenerator::ShaderGenerator (const std::shared_ptr< AbstractShader > & shader, std::string version, std::string profile) noexcept
		: m_shaderTarget(shader), m_version(std::move(version)), m_profile(std::move(profile))
	{

	}

	ShaderGenerator::ShaderGenerator (const std::shared_ptr< AbstractShader > & shader, ModelMatrixType modelMatricesType, RenderPassType renderPassType) noexcept
		: m_shaderTarget(shader),
		  m_modelMatricesType(modelMatricesType),
		  m_renderPassType(renderPassType)
	{
		auto * coreSettings = Settings::instance(SettingsType::Core);
		m_version = coreSettings->get(GLSLVersionKey, DefaultGLSLVersion);
		m_profile = coreSettings->get(GLSLProfileKey, DefaultGLSLProfile);
	}

	ShaderGenerator::ShaderGenerator (const std::shared_ptr< AbstractShader > & shader, ModelMatrixType modelMatricesType, RenderPassType renderPassType, std::string version, std::string profile) noexcept
		: m_shaderTarget(shader), m_version(std::move(version)), m_profile(std::move(profile)), m_modelMatricesType(modelMatricesType), m_renderPassType(renderPassType)
	{

	}

	void
	ShaderGenerator::setIndexes (const SetIndexes & setIndexes) noexcept
	{
		m_indexes = setIndexes;
	}

	const SetIndexes &
	ShaderGenerator::indexes () const noexcept
	{
		return m_indexes;
	}

	ShaderType
	ShaderGenerator::shaderType () const noexcept
	{
		return m_shaderTarget->type();
	}

	std::string
	ShaderGenerator::shaderName () const noexcept
	{
		if ( m_shaderTarget == nullptr )
		{
			return {"Undefined"};
		}

		return m_shaderTarget->name();
	}

	RenderPassType
	ShaderGenerator::renderPassType () const noexcept
	{
		return m_renderPassType;
	}

	ModelMatrixType
	ShaderGenerator::modelMatricesType () const noexcept
	{
		return m_modelMatricesType;
	}

	void
	ShaderGenerator::setExtensionBehavior (const char * extension, const char * behavior) noexcept
	{
		std::stringstream code{};

		code << GLSL::Define::Extension << ' ' << extension << " : " << behavior;

		m_headers.emplace_back(code.str());
	}

	const char *
	ShaderGenerator::outputFragment () const noexcept
	{
		return ShaderVariables::OutputFragment;
	}

	bool
	ShaderGenerator::declare (const SpecializationConstant & declaration) noexcept
	{
		if ( !declaration.isValid() )
		{
			Tracer::error(ClassId, "The specialization constant is invalid for code generation !");

			return false;
		}

		if ( std::ranges::any_of(m_specializationConstants, [declaration] (const auto & existing) {return existing.name() == declaration.name();}) )
		{
			TraceWarning{ClassId} << "A specialization constant declaration named '" << declaration.name() << "' already exists !";

			return true;
		}

		m_specializationConstants.emplace_back(declaration);
		
		TraceDebug{ClassId} << "A specialization constant '" << declaration.name() << "' has been declared to " << to_string(m_shaderTarget->type()) << " '" << m_shaderTarget->name() << "' !";

		return true;
	}

	bool
	ShaderGenerator::declare (const Structure & declaration) noexcept
	{
		if ( !declaration.isValid() )
		{
			Tracer::error(ClassId, "The structure is invalid for code generation !");

			return false;
		}

		if ( std::ranges::any_of(m_structures, [declaration] (const auto & existing) {return existing.name() == declaration.name();}) )
		{
			TraceWarning{ClassId} << "A structure declaration named '" << declaration.name() << "' already exists !";

			return true;
		}

		m_structures.emplace_back(declaration);

		TraceDebug{ClassId} << "A structure '" << declaration.name() << "' has been declared to " << to_string(m_shaderTarget->type()) << " '" << m_shaderTarget->name() << "' !";

		return true;
	}

	bool
	ShaderGenerator::declare (const Sampler & declaration) noexcept
	{
		if ( !declaration.isValid() )
		{
			Tracer::error(ClassId, "The sampler declaration is invalid for code generation !");

			return false;
		}

		if ( std::ranges::any_of(m_samplers, [declaration] (const auto & existing) {return existing.name() == declaration.name();}) )
		{
			TraceWarning{ClassId} << "A sampler declaration named '" << declaration.name() << "' already exists !";

			return true;
		}

		m_samplers.emplace_back(declaration);

		TraceDebug{ClassId} << "A sampler '" << declaration.name() << "' has been declared to " << to_string(m_shaderTarget->type()) << " '" << m_shaderTarget->name() << "' !";

		return true;
	}

	bool
	ShaderGenerator::declare (const UniformBlock & declaration) noexcept
	{
		if ( !declaration.isValid() )
		{
			Tracer::error(ClassId, "The uniform block is invalid for code generation !");

			return false;
		}

		if ( std::ranges::any_of(m_uniformBlocks, [declaration] (const auto & existing) {return existing.instanceName() == declaration.instanceName();}) )
		{
			TraceWarning{ClassId} << "An uniform block declaration named '" << declaration.name() << "' already exists !";

			return true;
		}

		m_uniformBlocks.emplace_back(declaration);

		TraceDebug{ClassId} << "An uniform block '" << declaration.name() << "' has been declared to " << to_string(m_shaderTarget->type()) << " '" << m_shaderTarget->name() << "' !";

		return true;
	}

	bool
	ShaderGenerator::declare (const ShaderStorageBlock & declaration) noexcept
	{
		if ( !declaration.isValid() )
		{
			Tracer::error(ClassId, "The shader storage block is invalid for code generation !");

			return false;
		}

		if ( std::ranges::any_of(m_shaderStorageBlocks, [declaration] (const auto & existing) {return existing.instanceName() == declaration.instanceName();}) )
		{
			TraceWarning{ClassId} << "A shader storage block declaration named '" << declaration.name() << "' already exists !";

			return true;
		}

		m_shaderStorageBlocks.emplace_back(declaration);

		TraceDebug{ClassId} << "A shader storage '" << declaration.name() << "' has been declared to " << to_string(m_shaderTarget->type()) << " '" << m_shaderTarget->name() << "' !";

		return true;
	}

	bool
	ShaderGenerator::declare (const InputAttribute & declaration) noexcept
	{
		if ( declaration.arraySize() > 0 )
		{
			if ( m_shaderTarget->type() != ShaderType::GeometryShader )
			{
				TraceError{ClassId} <<
					"Unable to add vertex attribute array to a non geometry shader. "
					"This is a " << to_string(m_shaderTarget->type()) << " (" << m_shaderTarget->name() << ") !";

				return false;
			}
		}
		else
		{
			if ( m_shaderTarget->type() != ShaderType::VertexShader )
			{
				TraceError{ClassId} <<
					"Unable to add vertex attribute to a non vertex shader. "
					"This is a " << to_string(m_shaderTarget->type()) << " (" << m_shaderTarget->name() << ") !";

				return false;
			}
		}

		if ( !declaration.isValid() )
		{
			Tracer::error(ClassId, "The input attribute is invalid for code generation !");

			return false;
		}

		if ( declaration.isModelMatricesVBOAttribute() && m_modelMatricesType != ModelMatrixType::VertexBufferObject )
		{
			TraceError{ClassId} << "Unable to add a matrix vertex attribute to a vertex shader without model matrices VBO enabled !";

			return false;
		}

		if ( std::ranges::any_of(m_inputAttributes, [declaration] (const auto & existing) {return existing.name() == declaration.name();}) )
		{
			TraceWarning{ClassId} << "An input attribute declaration named '" << declaration.name() << "' already exists !";

			return true;
		}

		m_inputAttributes.emplace_back(declaration);

		TraceDebug{ClassId} << "An input attribute '" << declaration.name() << "' has been declared to " << to_string(m_shaderTarget->type()) << " '" << m_shaderTarget->name() << "' !";

		return true;
	}

	bool
	ShaderGenerator::declare (const InputPrimitive & declaration) noexcept
	{
		if ( m_shaderTarget->type() != ShaderType::GeometryShader )
		{
			TraceError{ClassId} <<
				"Unable to add input primitive to a non geometry shader. "
				"This is a " << to_string(m_shaderTarget->type()) << " (" << m_shaderTarget->name() << ") !";

			return false;
		}

		if ( !declaration.isValid() )
		{
			Tracer::error(ClassId, "The input primitive is invalid for code generation !");

			return false;
		}

		if ( std::ranges::any_of(m_inputPrimitives, [declaration] (const auto & existing) {return existing.name() == declaration.name();}) )
		{
			TraceWarning{ClassId} << "An input primitive declaration named '" << declaration.name() << "' already exists !";

			return true;
		}

		m_inputPrimitives.emplace_back(declaration);

		TraceDebug{ClassId} << "An input primitive '" << declaration.name() << "' has been declared to " << to_string(m_shaderTarget->type()) << " '" << m_shaderTarget->name() << "' !";

		return true;
	}

	bool
	ShaderGenerator::declare (const InputBlock & declaration) noexcept
	{
		if ( !declaration.isValid() )
		{
			Tracer::error(ClassId, "The input block is invalid for code generation !");

			return false;
		}

		if ( std::ranges::any_of(m_inputBlocks, [declaration] (const auto & existing) {return existing.instanceName() == declaration.instanceName();}) )
		{
			TraceWarning{ClassId} << "An input block declaration named '" << declaration.name() << "' already exists !";

			return true;
		}

		m_inputBlocks.emplace_back(declaration);

		TraceDebug{ClassId} << "An input block '" << declaration.name() << "' has been declared to " << to_string(m_shaderTarget->type()) << " '" << m_shaderTarget->name() << "' !";

		return true;
	}

	bool
	ShaderGenerator::declare (const StageInput & declaration) noexcept
	{
		if ( m_shaderTarget->type() == ShaderType::VertexShader )
		{
			Tracer::error(ClassId, "Unable to add a stage input variable to a vertex shader. This is the beginning of the program !");

			return false;
		}

		if ( !declaration.isValid() )
		{
			Tracer::error(ClassId, "The stage input is invalid for code generation !");

			return false;
		}

		if ( declaration.isNonFixedArraySize() && m_shaderTarget->type() != ShaderType::GeometryShader )
		{
			TraceError{ClassId} <<
				"Unable to add an unlimited input array (var[]) to a non geometry shader. "
				"This is a " << to_string(m_shaderTarget->type()) << " (" << m_shaderTarget->name() << ") !";

			return false;
		}

		if ( std::ranges::any_of(m_stageInputs, [declaration] (const auto & existing) {return existing.name() == declaration.name();}) )
		{
			TraceWarning{ClassId} << "A stage input declaration named '" << declaration.name() << "' already exists !";

			return true;
		}

		m_stageInputs.emplace_back(declaration);

		TraceDebug{ClassId} << "A stage input '" << declaration.name() << "' has been declared to " << to_string(m_shaderTarget->type()) << " '" << m_shaderTarget->name() << "' !";

		return true;
	}

	bool
	ShaderGenerator::declare (const OutputPrimitive & declaration) noexcept
	{
		if ( m_shaderTarget->type() != ShaderType::GeometryShader )
		{
			TraceError{ClassId} <<
				"Unable to add output primitive to a non geometry shader. "
				"This is a " << to_string(m_shaderTarget->type()) << " (" << m_shaderTarget->name() << ") !";

			return false;
		}

		if ( !declaration.isValid() )
		{
			Tracer::error(ClassId, "The output primitive is invalid for code generation !");

			return false;
		}

		if ( std::ranges::any_of(m_outputPrimitives, [declaration] (const auto & existing) {return existing.name() == declaration.name();}) )
		{
			TraceWarning{ClassId} << "An output primitive declaration named '" << declaration.name() << "' already exists !";

			return true;
		}

		m_outputPrimitives.emplace_back(declaration);

		TraceDebug{ClassId} << "An output primitive '" << declaration.name() << "' has been declared to " << to_string(m_shaderTarget->type()) << " '" << m_shaderTarget->name() << "' !";

		return true;
	}

	bool
	ShaderGenerator::declare (const OutputBlock & declaration) noexcept
	{
		if ( !declaration.isValid() )
		{
			Tracer::error(ClassId, "The output block is invalid for code generation !");

			return false;
		}

		if ( std::ranges::any_of(m_outputBlocks, [declaration] (const auto & existing) {return existing.instanceName() == declaration.instanceName();}) )
		{
			TraceWarning{ClassId} << "An output block declaration named '" << declaration.name() << "' already exists !";

			return true;
		}

		m_outputBlocks.emplace_back(declaration);

		TraceDebug{ClassId} << "An output block '" << declaration.name() << "' has been declared to " << to_string(m_shaderTarget->type()) << " '" << m_shaderTarget->name() << "' !";

		return true;
	}

	bool
	ShaderGenerator::declare (const StageOutput & declaration) noexcept
	{
		if ( m_shaderTarget->type() == ShaderType::FragmentShader )
		{
			Tracer::error(ClassId, "Unable to add a stage output variable to a fragment shader. This is the end of the program !");

			return false;
		}

		if ( !declaration.isValid() )
		{
			Tracer::error(ClassId, "The stage output is invalid for code generation !");

			return false;
		}

		if ( std::ranges::any_of(m_stageOutputs, [declaration] (const auto & existing) {return existing.name() == declaration.name();}) )
		{
			TraceWarning{ClassId} << "A stage output declaration named '" << declaration.name() << "' already exists !";

			return true;
		}

		m_stageOutputs.emplace_back(declaration);

		TraceDebug{ClassId} << "A stage output '" << declaration.name() << "' has been declared to " << to_string(m_shaderTarget->type()) << " '" << m_shaderTarget->name() << "' !";

		return true;
	}

	bool
	ShaderGenerator::declare(const OutputFragment & declaration) noexcept
	{
		if ( m_shaderTarget->type() != ShaderType::FragmentShader )
		{
			TraceError{ClassId} <<
				"Unable to add output fragment to a non fragment shader. "
				"This is a " << to_string(m_shaderTarget->type()) << " (" << m_shaderTarget->name() << ") !";

			return false;
		}

		if ( !declaration.isValid() )
		{
			Tracer::error(ClassId, "The output fragment is invalid for code generation !");

			return false;
		}

		if ( std::ranges::any_of(m_outputFragments, [declaration] (const auto & existing) {return existing.name() == declaration.name();}) )
		{
			TraceWarning{ClassId} << "An output fragment declaration named '" << declaration.name() << "' already exists !";

			return true;
		}

		m_outputFragments.emplace_back(declaration);

		TraceDebug{ClassId} << "An output fragment '" << declaration.name() << "' has been declared to " << to_string(m_shaderTarget->type()) << " '" << m_shaderTarget->name() << "' !";

		return true;
	}

	bool
	ShaderGenerator::declare (const Function & declaration) noexcept
	{
		if ( !declaration.isValid() )
		{
			Tracer::error(ClassId, "The function is invalid for code generation !");

			return false;
		}

		if ( std::ranges::any_of(m_functions, [declaration] (const auto & existing) {return existing.name() == declaration.name();}) )
		{
			TraceWarning{ClassId} << "A function declaration named '" << declaration.name() << "' already exists !";

			return true;
		}

		m_functions.emplace_back(declaration);

		TraceDebug{ClassId} << "A function '" << declaration.name() << "' has been declared to " << to_string(m_shaderTarget->type()) << " '" << m_shaderTarget->name() << "' !";

		return true;
	}

	bool
	ShaderGenerator::declare (const TexelBuffer & declaration) noexcept
	{
		if ( !declaration.isValid() )
		{
			Tracer::error(ClassId, "The texel buffer is invalid for code generation !");

			return false;
		}

		if ( std::ranges::any_of(m_texelBuffers, [declaration] (const auto & existing) {return existing.name() == declaration.name();}) )
		{
			TraceWarning{ClassId} << "A texel buffer declaration named '" << declaration.name() << "' already exists !";

			return true;
		}

		m_texelBuffers.emplace_back(declaration);

		TraceDebug{ClassId} << "a texel buffer '" << declaration.name() << "' has been declared to " << to_string(m_shaderTarget->type()) << " '" << m_shaderTarget->name() << "' !";

		return true;
	}

	bool
	ShaderGenerator::declare (const PushConstantBlock & declaration) noexcept
	{
		if ( !declaration.isValid() )
		{
			Tracer::error(ClassId, "The push constant is invalid for code generation !");

			return false;
		}

		if ( std::ranges::any_of(m_pushConstantBlocks, [declaration] (const auto & existing) {return existing.name() == declaration.name();}) )
		{
			TraceWarning{ClassId} << "A push constant declaration named '" << declaration.name() << "' already exists !";

			return true;
		}

		m_pushConstantBlocks.emplace_back(declaration);

		TraceDebug{ClassId} << "A push constant '" << declaration.name() << "' has been declared to " << to_string(m_shaderTarget->type()) << " '" << m_shaderTarget->name() << "' !";

		return true;
	}

	bool
	ShaderGenerator::applyEffectsList (const EffectsList & effectsList) noexcept
	{
		return std::ranges::all_of(effectsList, [this] (const auto & effect) {
			return effect->generate(*this);
		});
	}

	bool
	ShaderGenerator::requestVertexShaderSynthesizeInstruction (const char * variableName, VariableScope scope) noexcept // NOLINT
	{
		/* NOTE: The generator must edit a vertex shader. */
		if ( m_shaderTarget->type() != ShaderType::VertexShader )
		{
			Tracer::error(ClassId, "Synthesize vertex position can only occurs in the vertex shader stage !");

			return false;
		}

		if ( !ShaderGenerator::isSyntheticVariableAllowed(variableName) )
		{
			TraceError{ClassId} << "Unable to synthesize '" << variableName << "' variable for " << to_string(m_shaderTarget->type()) << " '" << m_shaderTarget->name() << "' !";

			return false;
		}

		auto requestFound = false;

		for ( auto & request : m_requests )
		{
			if ( std::strcmp(request.first, variableName) == 0  )
			{
				/* NOTE: The variable is present, but needs to override the scope. */
				if ( request.second != scope )
				{
					request.second = VariableScope::Both;
				}

				requestFound = true;
			}
		}

		if ( !requestFound )
		{
			/* NOTE: Prerequisite for special shader variables.
			 * NOTE²: Ignorable Clang-Tidy warning for "Function XXX is within a recursive call chain". */
			if ( std::strcmp(variableName, ShaderVariables::PositionTextureSpace) == 0 )
			{
				if ( !this->requestVertexShaderSynthesizeInstruction(ShaderVariables::PositionViewSpace, VariableScope::Local) )
				{
					return false;
				}

				if ( !this->requestVertexShaderSynthesizeInstruction(ShaderVariables::TangentViewSpace, VariableScope::Local) )
				{
					return false;
				}

				if ( !this->requestVertexShaderSynthesizeInstruction(ShaderVariables::BinormalViewSpace, VariableScope::Local) )
				{
					return false;
				}

				if ( !this->requestVertexShaderSynthesizeInstruction(ShaderVariables::NormalViewSpace, VariableScope::Local) )
				{
					return false;
				}
			}

			m_requests.emplace_back(variableName, scope);
		}

		return true;
	}

	bool
	ShaderGenerator::synthesizeVertexPositionInWorldSpace (std::string & topInstructions, std::string & outputInstructions, VariableScope scope, bool asGLStandardPosition) noexcept
	{
		if ( !this->declare(InputAttribute{VertexAttributeType::Position}) )
		{
			return false;
		}

		std::stringstream code{};

		code << '\t';

		if ( asGLStandardPosition )
		{
			code << "gl_Position = ";
		}
		else
		{
			if ( scope == VariableScope::Local )
			{
				code << "const vec4 ";
			}
			else if ( !this->declare(StageOutput{ShaderVariables::PositionWorldSpace, GLSL::Smooth}) )
			{
				return false;
			}

			code << ShaderVariables::PositionWorldSpace << " = ";
		}

		switch ( m_modelMatricesType )
		{
			case ModelMatrixType::UniformBufferObject :
				if ( !this->declare(RenderableInstance::Unique::getModelUniformBlock(m_indexes.set(SetType::PerModel))) )
				{
					return false;
				}

				code << ShaderGenerator::modelUniform(UniformBlocks::Component::ModelMatrix) << " * vec4(" << Attributes::Position << ", 1.0);";
				break;

			case ModelMatrixType::VertexBufferObject :
				if ( !this->declare(InputAttribute{VertexAttributeType::ModelMatrixR0}) )
				{
					return false;
				}

				code << Attributes::ModelMatrix << " * vec4(" << Attributes::Position << ", 1.0);";
				break;

			case ModelMatrixType::Invalid :
				code << "// Invalid matrix type !" "\n";

				return false;
		}

		code << '\n';

		if ( scope != VariableScope::ToNextStage )
		{
			topInstructions.append(code.str());
		}
		else
		{
			outputInstructions.append(code.str());
		}

		return true;
	}

	bool
	ShaderGenerator::synthesizeVertexPositionInViewSpace (std::string & topInstructions, std::string & outputInstructions, VariableScope scope) noexcept
	{
		if ( !this->declare(InputAttribute{VertexAttributeType::Position}) )
		{
			return false;
		}

		std::stringstream code{};

		code << '\t';

		if ( scope == VariableScope::Local )
		{
			code << "const vec4 ";
		}
		else if ( !this->declare(StageOutput{ShaderVariables::PositionViewSpace, GLSL::Smooth}) )
		{
			return false;
		}

		code << ShaderVariables::PositionViewSpace << " = ";

		switch ( m_modelMatricesType )
		{
			case ModelMatrixType::UniformBufferObject :
				if ( !this->declare(RenderableInstance::Unique::getModelUniformBlock(m_indexes.set(SetType::PerModel))) )
				{
					return false;
				}

				code << ShaderGenerator::modelUniform(UniformBlocks::Component::ModelViewMatrix) << " * vec4(" << Attributes::Position << ", 1.0);" "\n";
				break;

			case ModelMatrixType::VertexBufferObject :
				if ( !this->prepareModelViewMatrixFromVBO() )
				{
					return false;
				}

				code << ShaderVariables::ModelViewMatrix << " * vec4(" << Attributes::Position << ", 1.0);" "\n";
				break;

			case ModelMatrixType::Invalid :
				code << "// Invalid matrix type !" "\n";

				return false;
		}

		if ( scope != VariableScope::ToNextStage )
		{
			topInstructions.append(code.str());
		}
		else
		{
			outputInstructions.append(code.str());
		}

		return true;
	}

	bool
	ShaderGenerator::synthesizeVertexPositionInScreenSpace (std::string & outputInstructions) noexcept
	{
		if ( !this->declare(InputAttribute{VertexAttributeType::Position}) )
		{
			return false;
		}

		std::stringstream code{};

		switch ( m_modelMatricesType )
		{
			case ModelMatrixType::UniformBufferObject :
				if ( !this->declare(RenderableInstance::Unique::getModelUniformBlock(m_indexes.set(SetType::PerModel))) )
				{
					return false;
				}

				/* FIXME: Switch between dynamic model UBO or static model UBO */
				if ( false )
				{
					code << '\t' << "gl_Position = " <<
						ShaderGenerator::viewUniform(UniformBlocks::Component::ProjectionMatrix) << " * " <<
						ShaderGenerator::viewUniform(UniformBlocks::Component::ViewMatrix) << " * " <<
						ShaderGenerator::modelUniform(UniformBlocks::Component::ModelMatrix) << " * "
						"vec4(" << Attributes::Position << ", 1.0);" "\n";
				}
				else
				{
					code << '\t' << "gl_Position = " << ShaderGenerator::modelUniform(UniformBlocks::Component::ModelViewProjectionMatrix) << " * vec4(" << Attributes::Position << ", 1.0);" "\n";
				}
				break;

			case ModelMatrixType::VertexBufferObject :
				if ( !this->prepareModelViewProjectionMatrixFromVBO() )
				{
					return false;
				}

				code << '\t' << "gl_Position = " << ShaderVariables::ModelViewProjectionMatrix << " * vec4(" << Attributes::Position << ", 1.0);" "\n";
				break;

			case ModelMatrixType::Invalid :
				code << "// Invalid matrix type !" "\n";

				return false;
		}

		outputInstructions.append(code.str());

		return true;
	}

	bool
	ShaderGenerator::synthesizeVertexPositionInTextureSpace (std::string & topInstructions, std::string & outputInstructions, VariableScope scope) noexcept
	{
		std::stringstream code{};

		code <<
			'\t' << GLSL::Float << " positionTextureX = dot(-" << ShaderVariables::PositionViewSpace << ".xyz, " << ShaderVariables::TangentViewSpace << ");" "\n" <<
			'\t' << GLSL::Float << " positionTextureY = dot(-" << ShaderVariables::PositionViewSpace << ".xyz, " << ShaderVariables::BinormalViewSpace << ");" "\n" <<
			'\t' << GLSL::Float << " positionTextureZ = dot(-" << ShaderVariables::PositionViewSpace << ".xyz, " << ShaderVariables::NormalViewSpace << ");" "\n\n";

		topInstructions.append(code.str());

		if ( scope == VariableScope::Local )
		{
			std::stringstream subCode{};

			subCode << '\t' << "const vec4 " << ShaderVariables::PositionTextureSpace << " = vec4(positionTextureX, positionTextureY, positionTextureZ, 1.0);" "\n";

			topInstructions.append(subCode.str());
		}
		else
		{
			if ( !this->declare(StageOutput{ShaderVariables::PositionTextureSpace, GLSL::Smooth}) )
			{
				return false;
			}

			std::stringstream subCode{};

			subCode << '\t' << ShaderVariables::PositionTextureSpace << " = vec4(positionTextureX, positionTextureY, positionTextureZ, 1.0);" "\n";

			if ( scope != VariableScope::ToNextStage )
			{
				topInstructions.append(subCode.str());
			}
			else
			{
				outputInstructions.append(subCode.str());
			}
		}

		return true;
	}

	bool
	ShaderGenerator::synthesizeVertexColor (std::string & outputInstructions) noexcept
	{
		if ( !this->declare(StageOutput{ShaderVariables::Color, GLSL::Smooth}) )
		{
			return false;
		}

		if ( !this->declare(InputAttribute{VertexAttributeType::VertexColor}) )
		{
			return false;
		}

		std::stringstream code{};

		code << '\t' << ShaderVariables::Color << " = " << Attributes::Color << ';' << '\n';

		outputInstructions.append(code.str());

		return true;
	}

	bool
	ShaderGenerator::synthesizeVertexTextureCoordinates (std::string & outputInstructions, const char * TCVariableName) noexcept
	{
		/* Default value for primary texture coordinates in 2D. */
		auto attributeType = VertexAttributeType::Primary2DTextureCoordinates;
		const auto * attributeName = Attributes::Primary2DTextureCoordinates;

		std::stringstream code{};

		code << '\t';

		if ( std::strcmp(TCVariableName, ShaderVariables::Primary2DTextureCoordinates) != 0 )
		{
			if ( std::strcmp(TCVariableName, ShaderVariables::Primary3DTextureCoordinates) == 0 )
			{
				attributeType = VertexAttributeType::Primary3DTextureCoordinates;
				attributeName = Attributes::Primary3DTextureCoordinates;
			}
			else if ( std::strcmp(TCVariableName, ShaderVariables::Secondary2DTextureCoordinates) == 0 )
			{
				attributeType = VertexAttributeType::Secondary2DTextureCoordinates;
				attributeName = Attributes::Secondary2DTextureCoordinates;
			}
			else if ( std::strcmp(TCVariableName, ShaderVariables::Secondary3DTextureCoordinates) == 0 )
			{
				attributeType = VertexAttributeType::Secondary3DTextureCoordinates;
				attributeName = Attributes::Secondary3DTextureCoordinates;
			}
			else
			{
				TraceError{ClassId} << "Texture coordinates variable '" << TCVariableName << "' is not handled !";

				return false;
			}
		}

		if ( !this->declare(StageOutput{TCVariableName, GLSL::Smooth}) )
		{
			return false;
		}

		if ( !this->declare(InputAttribute{attributeType}) )
		{
			return false;
		}

		code << TCVariableName << " = " << attributeName << ";" "\n";

		outputInstructions.append(code.str());

		return true;
	}

	bool
	ShaderGenerator::synthesizeVertexVectorInWorldSpace (std::string & topInstructions, std::string & outputInstructions, VertexAttributeType vectorType, VariableScope scope) noexcept
	{
		const char * attributeName = nullptr;
		const char * vectorName = nullptr;

		switch ( vectorType )
		{
			case VertexAttributeType::Tangent :
				attributeName = Attributes::Tangent;
				vectorName = ShaderVariables::TangentWorldSpace;
				break;

			case VertexAttributeType::Binormal :
				attributeName = Attributes::Binormal;
				vectorName = ShaderVariables::BinormalWorldSpace;
				break;

			case VertexAttributeType::Normal :
				attributeName = Attributes::Normal;
				vectorName = ShaderVariables::NormalWorldSpace;
				break;

			/* NOTE: Ignorable "Unreachable code" warning. */
			default :
				Tracer::error(ClassId, "The synthetic vertex vector in world space can only be the tangent, the bi-normal or the normal !");

				return false;
		}

		if ( !this->declare(InputAttribute{vectorType}) )
		{
			return false;
		}

		std::stringstream code{};

		code << '\t';

		if ( scope == VariableScope::Local )
		{
			code << "const vec3 ";
		}
		else if ( !this->declare(StageOutput{vectorName, GLSL::Smooth}) )
		{
			return false;
		}

		code << vectorName << " = ";

		switch ( m_modelMatricesType )
		{
			case ModelMatrixType::UniformBufferObject :
				if ( !this->declare(RenderableInstance::Unique::getModelUniformBlock(m_indexes.set(SetType::PerModel))) )
				{
					return false;
				}

				code << "normalize(" << ShaderGenerator::modelUniform(UniformBlocks::Component::NormalModelMatrix) << " * " << attributeName << ");";
				break;

			case ModelMatrixType::VertexBufferObject :
				if ( !this->declare(InputAttribute{VertexAttributeType::NormalModelMatrixR0}) )
				{
					return false;
				}

				code << "normalize(" << Attributes::NormalModelMatrix << " * " << attributeName << ");";
				break;

			case ModelMatrixType::Invalid :
				code << "// Invalid matrix type !" "\n";

				return false;
		}

		code << '\n';

		if ( scope != VariableScope::ToNextStage )
		{
			topInstructions.append(code.str());
		}
		else
		{
			outputInstructions.append(code.str());
		}

		return true;
	}

	bool
	ShaderGenerator::synthesizeVertexVectorInViewSpace (std::string & topInstructions, std::string & outputInstructions, VertexAttributeType vectorType, VariableScope scope) noexcept
	{
		const char * attributeName = nullptr;
		const char * vectorName = nullptr;

		switch ( vectorType )
		{
			case VertexAttributeType::Tangent :
				attributeName = Attributes::Tangent;
				vectorName = ShaderVariables::TangentViewSpace;
				break;

			case VertexAttributeType::Binormal :
				attributeName = Attributes::Binormal;
				vectorName = ShaderVariables::BinormalViewSpace;
				break;

			case VertexAttributeType::Normal :
				attributeName = Attributes::Normal;
				vectorName = ShaderVariables::NormalViewSpace;
				break;

			/* NOTE: Ignorable "Unreachable code" warning. */
			default :
				Tracer::error(ClassId, "The synthetic vertex vector in view space can only be the tangent, the bi-normal or the normal !");

				return false;
		}

		if ( !this->declare(InputAttribute{vectorType}) )
		{
			return false;
		}

		std::stringstream code{};

		code << '\t';

		if ( scope == VariableScope::Local )
		{
			code << "const vec3 ";
		}
		else if ( !this->declare(StageOutput{vectorName, GLSL::Smooth}) )
		{
			return false;
		}

		code << vectorName << " = ";

		switch ( m_modelMatricesType )
		{
			case ModelMatrixType::UniformBufferObject :
				if ( !this->declare(RenderableInstance::Unique::getModelUniformBlock(m_indexes.set(SetType::PerModel))) )
				{
					return false;
				}

				code << "normalize(" << ShaderGenerator::modelUniform(UniformBlocks::Component::NormalMatrix) << " * " << attributeName << ");";
				break;

			case ModelMatrixType::VertexBufferObject :
				if ( !this->prepareNormalMatrixFromVBO() )
				{
					return false;
				}

				code << "normalize(" << ShaderVariables::NormalMatrix << " * " << attributeName << ");";
				break;

			case ModelMatrixType::Invalid :
				code << "// Invalid matrix type !" "\n";
				break;
		}

		code << '\n';

		if ( scope != VariableScope::ToNextStage )
		{
			topInstructions.append(code.str());
		}
		else
		{
			outputInstructions.append(code.str());
		}

		return true;
	}

	bool
	ShaderGenerator::synthesizeWorldTBNMatrix (std::string & topInstructions, std::string & outputInstructions, ShaderGenerator::VariableScope scope) noexcept
	{
		if ( !this->declare(InputAttribute{VertexAttributeType::Tangent}) )
		{
			return false;
		}

		if ( !this->declare(InputAttribute{VertexAttributeType::Binormal}) )
		{
			return false;
		}

		if ( !this->declare(InputAttribute{VertexAttributeType::Normal}) )
		{
			return false;
		}

		if ( !this->declare(StageOutput{ShaderVariables::WorldTBNMatrix, GLSL::Smooth}) )
		{
			return false;
		}

		std::stringstream code{};

		switch ( m_modelMatricesType )
		{
			case ModelMatrixType::UniformBufferObject :
			{
				const auto modelMatrix = ShaderGenerator::modelUniform(UniformBlocks::Component::ModelMatrix);

				if ( !this->declare(RenderableInstance::Unique::getModelUniformBlock(m_indexes.set(SetType::PerModel))) )
				{
					return false;
				}

				code <<
					"	const vec4 worldT = normalize(" << modelMatrix << " * vec4(" << Attributes::Tangent << ", 0.0));" "\n"
					"	const vec4 worldB = normalize(" << modelMatrix << " * vec4(" << Attributes::Binormal << ", 0.0));" "\n"
					"	const vec4 worldN = normalize(" << modelMatrix << " * vec4(" << Attributes::Normal << ", 0.0));" "\n";
			}
				break;

			case ModelMatrixType::VertexBufferObject :
				if ( !this->declare(InputAttribute{VertexAttributeType::ModelMatrixR0}) )
				{
					return false;
				}

				code <<
					"	const vec4 worldT = normalize(" << Attributes::ModelMatrix << " * vec4(" << Attributes::Tangent << ", 0.0));" "\n"
					"	const vec4 worldB = normalize(" << Attributes::ModelMatrix << " * vec4(" << Attributes::Binormal << ", 0.0));" "\n"
					"	const vec4 worldN = normalize(" << Attributes::ModelMatrix << " * vec4(" << Attributes::Normal << ", 0.0));" "\n";
				break;

			case ModelMatrixType::Invalid :
				code << "	// Invalid matrix type !" "\n";

				return false;
		}

		topInstructions.append(code.str());

		{
			std::stringstream matrixCode{};

			matrixCode << '\t' << ShaderVariables::WorldTBNMatrix << " = mat3(worldT.xyz, worldB.xyz, worldN.xyz);" "\n";

			if ( scope != VariableScope::ToNextStage )
			{
				topInstructions.append(matrixCode.str());
			}
			else
			{
				outputInstructions.append(matrixCode.str());
			}
		}

		return true;
	}

	bool
	ShaderGenerator::synthesizeViewTBNMatrix (std::string & topInstructions, std::string & outputInstructions, ShaderGenerator::VariableScope scope) noexcept
	{
		if ( !this->declare(InputAttribute{VertexAttributeType::Tangent}) )
		{
			return false;
		}

		if ( !this->declare(InputAttribute{VertexAttributeType::Binormal}) )
		{
			return false;
		}

		if ( !this->declare(InputAttribute{VertexAttributeType::Normal}) )
		{
			return false;
		}

		if ( !this->declare(StageOutput{ShaderVariables::ViewTBNMatrix, GLSL::Smooth}) )
		{
			return false;
		}

		std::stringstream code{};

		switch ( m_modelMatricesType )
		{
			case ModelMatrixType::UniformBufferObject :
			{
				const auto normalMatrix = ShaderGenerator::modelUniform(UniformBlocks::Component::NormalMatrix);

				if ( !this->declare(RenderableInstance::Unique::getModelUniformBlock(m_indexes.set(SetType::PerModel))) )
				{
					return false;
				}

				code <<
					"	const vec3 viewT = normalize(" << normalMatrix << " * " << Attributes::Tangent << ");" "\n"
					"	const vec3 viewB = normalize(" << normalMatrix << " * " << Attributes::Binormal << ");" "\n"
					"	const vec3 viewN = normalize(" << normalMatrix << " * " << Attributes::Normal << ");" "\n";
			}
				break;

			case ModelMatrixType::VertexBufferObject :
				if ( !this->prepareNormalMatrixFromVBO() )
				{
					return false;
				}

				code <<
					"	const vec3 viewT = normalize(" << ShaderVariables::NormalMatrix << " * " << Attributes::Tangent << ");" "\n"
					"	const vec3 viewB = normalize(" << ShaderVariables::NormalMatrix << " * " << Attributes::Binormal << ");" "\n"
					"	const vec3 viewN = normalize(" << ShaderVariables::NormalMatrix << " * " << Attributes::Normal << ");" "\n";
				break;

			case ModelMatrixType::Invalid :
				code << "	// Invalid matrix type !" "\n";

				return false;
		}

		topInstructions.append(code.str());

		{
			std::stringstream matrixCode;

			matrixCode << '\t' << ShaderVariables::ViewTBNMatrix << " = transpose(mat3(viewT, viewB, viewN));" "\n";

			if ( scope != VariableScope::ToNextStage )
			{
				topInstructions.append(matrixCode.str());
			}
			else
			{
				outputInstructions.append(matrixCode.str());
			}
		}

		return true;
	}

	bool
	ShaderGenerator::synthesizeWorldToTangentMatrix (std::string & topInstructions, std::string & outputInstructions, VariableScope scope) noexcept
	{
		if ( !this->declare(InputAttribute{VertexAttributeType::Tangent}) )
		{
			return false;
		}

		if ( !this->declare(InputAttribute{VertexAttributeType::Binormal}) )
		{
			return false;
		}

		if ( !this->declare(InputAttribute{VertexAttributeType::Normal}) )
		{
			return false;
		}

		if ( !this->declare(StageOutput{ShaderVariables::WorldToTangentMatrix, GLSL::Smooth}) )
		{
			return false;
		}

		std::stringstream code{};

		switch ( m_modelMatricesType )
		{
			case ModelMatrixType::UniformBufferObject :
				if ( !this->declare(RenderableInstance::Unique::getModelUniformBlock(m_indexes.set(SetType::PerModel))) )
				{
					return false;
				}

				code << '\t' << ShaderVariables::WorldToTangentMatrix << " = " << ShaderGenerator::modelUniform(UniformBlocks::Component::NormalMatrix) << " * mat3(" << Attributes::Tangent << ", " << Attributes::Binormal << ", " << Attributes::Normal << ");" << '\n';
				break;

			case ModelMatrixType::VertexBufferObject :
				if ( !this->declare(RenderTarget::View::Texture2D::getViewUniformBlock(m_indexes.set(SetType::PerView))) )
				{
					return false;
				}

				if ( !this->declare(InputAttribute{VertexAttributeType::NormalModelMatrixR0}) )
				{
					return false;
				}

				code << '\t' << ShaderVariables::WorldToTangentMatrix << " = " << Attributes::NormalModelMatrix << " * mat3(" << Attributes::Tangent << ", " << Attributes::Binormal << ", " << Attributes::Normal << ");" << '\n';
				break;

			case ModelMatrixType::Invalid :
				code << "// Invalid matrix type !" "\n";

				return false;
		}

		if ( scope != VariableScope::ToNextStage )
		{
			topInstructions.append(code.str());
		}
		else
		{
			outputInstructions.append(code.str());
		}

		return true;
	}

	bool
	ShaderGenerator::isSyntheticVariableAllowed (const char * variableName) noexcept
	{
		constexpr std::array< const char *, 19 > variables{
			GLSL::Vertex::Out::Position,
			ShaderVariables::PositionWorldSpace,
			ShaderVariables::GLPositionWorldSpace,
			ShaderVariables::PositionViewSpace,
			ShaderVariables::PositionTextureSpace,
			ShaderVariables::Color,
			ShaderVariables::Primary2DTextureCoordinates,
			ShaderVariables::Primary3DTextureCoordinates,
			ShaderVariables::Secondary2DTextureCoordinates,
			ShaderVariables::Secondary3DTextureCoordinates,
			ShaderVariables::TangentWorldSpace,
			ShaderVariables::TangentViewSpace,
			ShaderVariables::BinormalWorldSpace,
			ShaderVariables::BinormalViewSpace,
			ShaderVariables::NormalWorldSpace,
			ShaderVariables::NormalViewSpace,
			ShaderVariables::WorldTBNMatrix,
			ShaderVariables::ViewTBNMatrix,
			ShaderVariables::WorldToTangentMatrix
		};

		return std::ranges::any_of(variables, [variableName] (const auto & name) {
			return std::strcmp(name, variableName) == 0;
		});
	}

	bool
	ShaderGenerator::prepareModelViewMatrixFromVBO () noexcept
	{
		for ( const auto & pair : m_uniquePreparations )
		{
			if ( std::strcmp(pair.first, ShaderVariables::ModelViewMatrix) == 0 )
			{
				return true;
			}
		}

		if ( !this->declare(RenderTarget::View::Texture2D::getViewUniformBlock(m_indexes.set(SetType::PerView))) )
		{
			return false;
		}

		if ( !this->declare(InputAttribute{VertexAttributeType::ModelMatrixR0}) )
		{
			return false;
		}

		std::stringstream code{};

		code << GLSL::ConstMatrix4 << ' ' << ShaderVariables::ModelViewMatrix << " = " << ShaderGenerator::viewUniform(UniformBlocks::Component::ViewMatrix) << " * " << Attributes::ModelMatrix << ';';

		m_uniquePreparations.emplace_back(ShaderVariables::ModelViewMatrix, code.str());

		return true;
	}

	bool
	ShaderGenerator::prepareNormalMatrixFromVBO () noexcept
	{
		for ( const auto & pair : m_uniquePreparations )
		{
			if ( std::strcmp(pair.first, ShaderVariables::NormalMatrix) == 0 )
			{
				return true;
			}
		}

		if ( !this->prepareModelViewMatrixFromVBO() )
		{
			return false;
		}

		std::stringstream code{};

		code << "const mat3 " << ShaderVariables::NormalMatrix << " = transpose(mat3(inverse(" << ShaderVariables::ModelViewMatrix << ")));";

		m_uniquePreparations.emplace_back(ShaderVariables::NormalMatrix, code.str());

		return true;
	}

	bool
	ShaderGenerator::prepareModelViewProjectionMatrixFromVBO () noexcept
	{
		for ( const auto & pair : m_uniquePreparations )
		{
			if ( std::strcmp(pair.first, ShaderVariables::NormalMatrix) == 0 )
			{
				return true;
			}
		}

		if ( !this->declare(RenderTarget::View::Texture2D::getViewUniformBlock(m_indexes.set(SetType::PerView))) )
		{
			return false;
		}

		if ( !this->declare(InputAttribute{VertexAttributeType::ModelMatrixR0}) )
		{
			return false;
		}

		std::stringstream code{};

		code << "const mat4 " << ShaderVariables::ModelViewProjectionMatrix << " = " << ShaderGenerator::viewUniform(UniformBlocks::Component::ViewProjectionMatrix) << " * " << Attributes::ModelMatrix << ';';

		m_uniquePreparations.emplace_back(ShaderVariables::ModelViewProjectionMatrix, code.str());

		return true;
	}

	bool
	ShaderGenerator::synthesizeRequestInstructions (std::string & topInstructions, std::string & outputInstructions) noexcept
	{
		for ( const auto & request : m_requests )
		{
			if ( std::strcmp(request.first, GLSL::Vertex::Out::Position) == 0 )
			{
				if ( !this->synthesizeVertexPositionInScreenSpace(outputInstructions) )
				{
					return false;
				}

				continue;
			}

			if ( std::strcmp(request.first, ShaderVariables::PositionWorldSpace) == 0 )
			{
				if ( !this->synthesizeVertexPositionInWorldSpace(topInstructions, outputInstructions, request.second, false) )
				{
					return false;
				}

				continue;
			}

			if ( std::strcmp(request.first, ShaderVariables::GLPositionWorldSpace) == 0 )
			{
				if ( !this->synthesizeVertexPositionInWorldSpace(topInstructions, outputInstructions, request.second, true) )
				{
					return false;
				}

				continue;
			}

			if ( std::strcmp(request.first, ShaderVariables::PositionViewSpace) == 0 )
			{
				if ( !this->synthesizeVertexPositionInViewSpace(topInstructions, outputInstructions, request.second) )
				{
					return false;
				}

				continue;
			}

			if ( std::strcmp(request.first, ShaderVariables::PositionTextureSpace) == 0 )
			{
				if ( !this->synthesizeVertexPositionInTextureSpace(topInstructions, outputInstructions, request.second) )
				{
					return false;
				}

				continue;
			}

			if ( std::strcmp(request.first, ShaderVariables::Color) == 0 )
			{
				if ( !this->synthesizeVertexColor(outputInstructions) )
				{
					return false;
				}

				continue;
			}

			/* Texture coordinates flavors. */
			{
				const std::array< const char *, 4 > textureCoordinates{
					ShaderVariables::Primary2DTextureCoordinates,
					ShaderVariables::Primary3DTextureCoordinates,
					ShaderVariables::Secondary2DTextureCoordinates,
					ShaderVariables::Secondary3DTextureCoordinates
				};

				auto found = false;

				for ( const auto & shaderVariable : textureCoordinates )
				{
					if ( std::strcmp(request.first, shaderVariable) != 0 )
					{
						continue;
					}

					if ( !this->synthesizeVertexTextureCoordinates(outputInstructions, shaderVariable) )
					{
						return false;
					}

					found = true;
				}

				if ( found )
				{
					continue;
				}
			}

			if ( std::strcmp(request.first, ShaderVariables::TangentWorldSpace) == 0 )
			{
				if ( !this->synthesizeVertexVectorInWorldSpace(topInstructions, outputInstructions, VertexAttributeType::Tangent, request.second) )
				{
					return false;
				}

				continue;
			}

			if ( std::strcmp(request.first, ShaderVariables::TangentViewSpace) == 0 )
			{
				if ( !this->synthesizeVertexVectorInViewSpace(topInstructions, outputInstructions, VertexAttributeType::Tangent, request.second) )
				{
					return false;
				}

				continue;
			}

			if ( std::strcmp(request.first, ShaderVariables::BinormalWorldSpace) == 0 )
			{
				if ( !this->synthesizeVertexVectorInWorldSpace(topInstructions, outputInstructions, VertexAttributeType::Binormal, request.second) )
				{
					return false;
				}

				continue;
			}

			if ( std::strcmp(request.first, ShaderVariables::BinormalViewSpace) == 0 )
			{
				if ( !this->synthesizeVertexVectorInViewSpace(topInstructions, outputInstructions, VertexAttributeType::Binormal, request.second) )
				{
					return false;
				}

				continue;
			}

			if ( std::strcmp(request.first, ShaderVariables::NormalWorldSpace) == 0 )
			{
				if ( !this->synthesizeVertexVectorInWorldSpace(topInstructions, outputInstructions, VertexAttributeType::Normal, request.second) )
				{
					return false;
				}

				continue;
			}

			if ( std::strcmp(request.first, ShaderVariables::NormalViewSpace) == 0 )
			{
				if ( !this->synthesizeVertexVectorInViewSpace(topInstructions, outputInstructions, VertexAttributeType::Normal, request.second) )
				{
					return false;
				}

				continue;
			}

			if ( std::strcmp(request.first, ShaderVariables::WorldTBNMatrix) == 0 )
			{
				if ( !this->synthesizeWorldTBNMatrix(topInstructions, outputInstructions, request.second) )
				{
					return false;
				}

				continue;
			}

			if ( std::strcmp(request.first, ShaderVariables::ViewTBNMatrix) == 0 )
			{
				if ( !this->synthesizeViewTBNMatrix(topInstructions, outputInstructions, request.second) )
				{
					return false;
				}

				continue;
			}


			if ( std::strcmp(request.first, ShaderVariables::WorldToTangentMatrix) == 0 )
			{
				if ( !this->synthesizeWorldToTangentMatrix(topInstructions, outputInstructions, request.second) )
				{
					return false;
				}

				continue;
			}
		}

		return true;
	}

	std::string
	ShaderGenerator::getDeclarationStats () const noexcept
	{
		std::stringstream output{};

		output <<
			"Shader declarations : " "\n"
			"Function : " << m_functions.size() << "\n"
			"Structure : " << m_structures.size() << "\n"
			"Uniform block : " << m_uniformBlocks.size() << "\n"
			"Shader storage block : " << m_shaderStorageBlocks.size() << "\n"
			"Input block : " << m_inputBlocks.size() << "\n"
			"Output block : " <<  m_outputBlocks.size() << "\n"
			"Push constant block (<= 1) : " << m_pushConstantBlocks.size() << "\n"
			"Specialization constant : " << m_specializationConstants.size() << "\n"
			"Sampler : " << m_samplers.size() << "\n"
			"Texel : " << m_texelBuffers.size() << "\n"
			"Stage input : " << m_stageInputs.size() << "\n"
			"Stage input : " << m_stageOutputs.size() << "\n"
			"Input attribute (VS) : " << m_inputAttributes.size() << "\n"
			"Input primitive (GS) : " << m_inputPrimitives.size() << "\n"
			"Output primitive (GS) : " << m_outputPrimitives.size() << "\n"
			"Output fragment (FS) : " << m_outputFragments.size() << "\n";

		return output.str();
	}

	bool
	ShaderGenerator::generateMainUniqueInstructions (std::string & topInstructions, std::string & outputInstructions) noexcept
	{
		if ( !this->synthesizeRequestInstructions(topInstructions, outputInstructions) )
		{
			return false;
		}

		if ( !m_uniquePreparations.empty() )
		{
			for ( const auto & line : m_uniquePreparations )
			{
				topInstructions += line.second;
			}

			topInstructions += '\n';
		}

		return true;
	}

	void
	ShaderGenerator::generateHeaders (std::stringstream & code) const noexcept
	{
		/* NOTE: This must be the first line of the source code.
		 * This is the version and the profile of the current shader. */
		code << GLSL::Define::Version << ' ' << m_version << ' ' << m_profile << '\n';

		/* Adds defines and other pre-processor instructions. */
		if ( !m_headers.empty() )
		{
			for ( const auto & line : m_headers )
			{
				code << line << '\n';
			}
		}

		code << '\n';

#if IS_EMBEDDED_PLATFORM
		code << Precision << ' ' << GLSL::PrecisionType::Medium << ' ' << Float << ';' << "\n\n";
#endif

		code << "/* " << to_string(m_shaderTarget->type()) << " : " << m_shaderTarget->name() << " */" "\n\n";
	}

	std::string
	ShaderGenerator::generateSourceCode () noexcept
	{
		std::stringstream code{};
		std::string topInstructions{};
		std::string outputInstructions{};

		/* NOTE: This will add some declarations. */
		if ( !this->generateMainUniqueInstructions(topInstructions, outputInstructions) )
		{
			return {};
		}

		this->generateHeaders(code);

		ShaderGenerator::generateDeclarations(code, m_functions, "Functions");
		ShaderGenerator::generateDeclarations(code, m_structures, "Structures");
		ShaderGenerator::generateDeclarations(code, m_uniformBlocks, "Uniform blocks (OpenGL/Vulkan UBO)");
		ShaderGenerator::generateDeclarations(code, m_shaderStorageBlocks, "Shader storage blocks (OpenGL/Vulkan SSBO)");
		ShaderGenerator::generateDeclarations(code, m_inputBlocks, "Input blocks (From previous stage)");
		ShaderGenerator::generateDeclarations(code, m_outputBlocks, "Output blocks (To next stage)");
		ShaderGenerator::generateDeclarations(code, m_pushConstantBlocks, "Push constant block (Vulkan)");
		ShaderGenerator::generateDeclarations(code, m_specializationConstants, "Specialization constants");
		ShaderGenerator::generateDeclarations(code, m_samplers, "Samplers");
		ShaderGenerator::generateDeclarations(code, m_texelBuffers, "Texel buffers");
		ShaderGenerator::generateDeclarations(code, m_stageInputs, "Stage inputs (From previous stage)");
		ShaderGenerator::generateDeclarations(code, m_stageOutputs, "Stage outputs (To next stage)");

		/* NOTE: Code per specific type of shader. */
		switch ( m_shaderTarget->type() )
		{
			case ShaderType::VertexShader :
				ShaderGenerator::generateDeclarations(code, m_inputAttributes, "Input vertex attributes (Vertex shader only)");
				break;

			case ShaderType::GeometryShader :
				ShaderGenerator::generateDeclarations(code, m_inputPrimitives, "Input primitives (Geometry shader only)");
				ShaderGenerator::generateDeclarations(code, m_outputPrimitives, "Output primitives (Geometry shader only)");
				break;

			case ShaderType::FragmentShader :
				ShaderGenerator::generateDeclarations(code, m_outputFragments, "Output fragments (Fragment shader only)");
				break;

			default:
				break;
		}

		/* NOTE: Generate the main() function code. */
		code <<
			 "void main ()" "\n"
			 "{" "\n" <<
			 this->getCode(topInstructions, outputInstructions) <<
			 "}" "\n";

		return code.str();
	}

	bool
	ShaderGenerator::writeShader () noexcept
	{
		TraceDebug{ClassId} <<
			"Writing " << to_string(m_shaderTarget->type()) << " '" << m_shaderTarget->name() << "' code ... " "\n" <<
			this->getDeclarationStats();

		const auto sourceCode = this->generateSourceCode();

		if ( sourceCode.empty() )
		{
			TraceError{ClassId} << "The generated source code is empty for " << to_string(m_shaderTarget->type()) << " (" << m_shaderTarget->name() << ") !";

			return false;
		}

		m_shaderTarget->setSourceCode(sourceCode);

		/* NOTE: Declarations per specific type of shader. */
		switch ( m_shaderTarget->type() )
		{
			case ShaderType::VertexShader :
				if ( !m_inputAttributes.empty() )
				{
					auto vertexShader = std::static_pointer_cast< VertexShader >(m_shaderTarget);

					if ( m_modelMatricesType == ModelMatrixType::VertexBufferObject )
					{
						vertexShader->enableInstancing();
					}

					for ( const auto & object : m_inputAttributes )
					{
						vertexShader->declareAttribute(static_cast< VertexAttributeType >(object.location()));
					}
				}
				break;

			case ShaderType::FragmentShader :
				if ( !m_outputFragments.empty() )
				{
					auto fragmentShader = std::static_pointer_cast< FragmentShader >(m_shaderTarget);

					for ( const auto & object : m_outputFragments )
					{
						fragmentShader->declareOutput(object.name());
					}
				}
				break;

			default:
				break;
		}

		for ( const auto & object : m_samplers )
		{
			m_shaderTarget->declareUniform(object.name());
		}

		for ( const auto & object : m_uniformBlocks )
		{
			m_shaderTarget->declareUniformBlock(object.name());
		}

		for ( const auto & object : m_shaderStorageBlocks )
		{
			m_shaderTarget->declareShaderStorageBlock(object.name());
		}

		return true;
	}

	std::string
	ShaderGenerator::viewUniform (const char * componentName) noexcept
	{
		return (std::stringstream{} << BufferBackedBlocks::View << '.' << componentName).str();
	}

	std::string
	ShaderGenerator::viewIndexedUniform (const char * memberName, const char * indexVariableName, const char * componentName) noexcept
	{
		return (std::stringstream{} << BufferBackedBlocks::View << '.' << memberName << '[' << indexVariableName << ']' << '.' << componentName).str();
	}

	std::string
	ShaderGenerator::modelUniform (const char * componentName) noexcept
	{
		return (std::stringstream{} << BufferBackedBlocks::Model << '.' << componentName).str();
	}

	std::string
	ShaderGenerator::materialUniform (const char * componentName) noexcept
	{
		return (std::stringstream{} << BufferBackedBlocks::Material << '.' << componentName).str();
	}

	uint32_t
	ShaderGenerator::getShaderVariableLocation (Key shaderVariable) noexcept
	{
		const std::array< const char *, 25 > names{
			ShaderVariables::PositionWorldSpace,
			//ShaderVariables::GLPositionWorldSpace,
			ShaderVariables::PositionViewSpace,
			ShaderVariables::PositionTextureSpace,
			ShaderVariables::Color,
			ShaderVariables::Primary2DTextureCoordinates,
			ShaderVariables::Primary3DTextureCoordinates,
			ShaderVariables::Secondary2DTextureCoordinates,
			ShaderVariables::Secondary3DTextureCoordinates,
			ShaderVariables::TangentWorldSpace,
			ShaderVariables::TangentViewSpace,
			ShaderVariables::BinormalWorldSpace,
			ShaderVariables::BinormalViewSpace,
			ShaderVariables::NormalWorldSpace,
			ShaderVariables::NormalViewSpace,
			ShaderVariables::ModelViewMatrix,
			ShaderVariables::NormalMatrix,
			ShaderVariables::ModelViewProjectionMatrix,
			ShaderVariables::WorldTBNMatrix,
			ShaderVariables::ViewTBNMatrix,
			ShaderVariables::WorldToTangentMatrix,
			ShaderVariables::OutputFragment,
			ShaderVariables::FragCoord,
			ShaderVariables::Light,
			ShaderVariables::DiffuseFactor,
			ShaderVariables::SpecularFactor
		};

		uint32_t location = 0;

		for ( const auto * name : names )
		{
			if ( std::strcmp(shaderVariable, name) == 0 )
			{
				break;
			}

			location++;
		}

		return location;
	}

	Key
	ShaderGenerator::getShaderVariableType (Key shaderVariable) noexcept // NOLINT(readability-function-cognitive-complexity)
	{
		if ( std::strcmp(shaderVariable, ShaderVariables::PositionWorldSpace) == 0 )
		{
			return GLSL::FloatVector4;
		}

		if ( std::strcmp(shaderVariable, ShaderVariables::GLPositionWorldSpace) == 0 )
		{
			return GLSL::FloatVector4;
		}

		if ( std::strcmp(shaderVariable, ShaderVariables::PositionViewSpace) == 0 )
		{
			return GLSL::FloatVector4;
		}

		if ( std::strcmp(shaderVariable, ShaderVariables::PositionTextureSpace) == 0 )
		{
			return GLSL::FloatVector4;
		}

		if ( std::strcmp(shaderVariable, ShaderVariables::Color) == 0 )
		{
			return GLSL::FloatVector4;
		}

		if ( std::strcmp(shaderVariable, ShaderVariables::Primary2DTextureCoordinates) == 0 )
		{
			return GLSL::FloatVector2;
		}

		if ( std::strcmp(shaderVariable, ShaderVariables::Primary3DTextureCoordinates) == 0 )
		{
			return GLSL::FloatVector3;
		}

		if ( std::strcmp(shaderVariable, ShaderVariables::Secondary2DTextureCoordinates) == 0 )
		{
			return GLSL::FloatVector2;
		}

		if ( std::strcmp(shaderVariable, ShaderVariables::Secondary3DTextureCoordinates) == 0 )
		{
			return GLSL::FloatVector3;
		}

		if ( std::strcmp(shaderVariable, ShaderVariables::TangentWorldSpace) == 0 )
		{
			return GLSL::FloatVector3;
		}

		if ( std::strcmp(shaderVariable, ShaderVariables::TangentViewSpace) == 0 )
		{
			return GLSL::FloatVector3;
		}

		if ( std::strcmp(shaderVariable, ShaderVariables::BinormalWorldSpace) == 0 )
		{
			return GLSL::FloatVector3;
		}

		if ( std::strcmp(shaderVariable, ShaderVariables::BinormalViewSpace) == 0 )
		{
			return GLSL::FloatVector3;
		}

		if ( std::strcmp(shaderVariable, ShaderVariables::NormalWorldSpace) == 0 )
		{
			return GLSL::FloatVector3;
		}

		if ( std::strcmp(shaderVariable, ShaderVariables::NormalViewSpace) == 0 )
		{
			return GLSL::FloatVector3;
		}

		if ( std::strcmp(shaderVariable, ShaderVariables::ModelViewMatrix) == 0 )
		{
			return GLSL::Matrix4;
		}

		if ( std::strcmp(shaderVariable, ShaderVariables::NormalMatrix) == 0 )
		{
			return GLSL::Matrix3;
		}

		if ( std::strcmp(shaderVariable, ShaderVariables::ModelViewProjectionMatrix) == 0 )
		{
			return GLSL::Matrix4;
		}

		if ( std::strcmp(shaderVariable, ShaderVariables::WorldTBNMatrix) == 0 )
		{
			return GLSL::Matrix3;
		}

		if ( std::strcmp(shaderVariable, ShaderVariables::ViewTBNMatrix) == 0 )
		{
			return GLSL::Matrix4;
		}

		if ( std::strcmp(shaderVariable, ShaderVariables::WorldToTangentMatrix) == 0 )
		{
			return GLSL::Matrix3;
		}

		if ( std::strcmp(shaderVariable, ShaderVariables::OutputFragment) == 0 )
		{
			return GLSL::FloatVector4;
		}

		if ( std::strcmp(shaderVariable, ShaderVariables::FragCoord) == 0 )
		{
			return GLSL::FloatVector4;
		}

		if ( std::strcmp(shaderVariable, ShaderVariables::Light) == 0 )
		{
			return GLSL::Float;
		}

		if ( std::strcmp(shaderVariable, ShaderVariables::DiffuseFactor) == 0 )
		{
			return GLSL::Float;
		}

		if ( std::strcmp(shaderVariable, ShaderVariables::SpecularFactor) == 0 )
		{
			return GLSL::Float;
		}

		return nullptr;
	}
}
