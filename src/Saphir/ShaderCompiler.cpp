/*
 * Emeraude/Saphir/ShaderCompiler.cpp
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

#include "ShaderCompiler.hpp"

/* C/C++ standard libraries. */
#include <string>

/* Local inclusions */
#include "Tracer.hpp"
#include "Arguments.hpp"
#include "Settings.hpp"
#include "SourceCodeParser.hpp"
#include "AbstractShader.hpp"

namespace Emeraude::Saphir
{
	using namespace Libraries;

	const size_t ShaderCompiler::ClassUID{Observable::getClassUID()};

	ShaderCompiler::ShaderCompiler (const Arguments & arguments, Settings & coreSettings) noexcept
		: ServiceInterface(ClassId), m_arguments(arguments), m_coreSettings(coreSettings)
	{

	}

	bool
	ShaderCompiler::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	ShaderCompiler::usable () const noexcept
	{
		return m_flags[IsGLSLangInitialized];
	}

	bool
	ShaderCompiler::onInitialize () noexcept
	{
		Tracer::info(ClassId, Blob() << "GLSLang GLSL version supported : " << glslang::GetGlslVersionString());

		if ( !glslang::InitializeProcess() )
		{
			Tracer::error(ClassId, "Unable to initialize GLSLang process !");

			return false;
		}

		m_builtInResource.maxLights = 32;
		m_builtInResource.maxClipPlanes = 6;
		m_builtInResource.maxTextureUnits = 32;
		m_builtInResource.maxTextureCoords = 32;
		m_builtInResource.maxVertexAttribs = 64;
		m_builtInResource.maxVertexUniformComponents = 4096;
		m_builtInResource.maxVaryingFloats = 64;
		m_builtInResource.maxVertexTextureImageUnits = 32;
		m_builtInResource.maxCombinedTextureImageUnits = 80;
		m_builtInResource.maxTextureImageUnits = 32;
		m_builtInResource.maxFragmentUniformComponents = 4096;
		m_builtInResource.maxDrawBuffers = 32;
		m_builtInResource.maxVertexUniformVectors = 128;
		m_builtInResource.maxVaryingVectors = 8;
		m_builtInResource.maxFragmentUniformVectors = 16;
		m_builtInResource.maxVertexOutputVectors = 16;
		m_builtInResource.maxFragmentInputVectors = 15;
		m_builtInResource.minProgramTexelOffset = -8;
		m_builtInResource.maxProgramTexelOffset = 7;
		m_builtInResource.maxClipDistances = 8;
		m_builtInResource.maxComputeWorkGroupCountX = 65535;
		m_builtInResource.maxComputeWorkGroupCountY = 65535;
		m_builtInResource.maxComputeWorkGroupCountZ = 65535;
		m_builtInResource.maxComputeWorkGroupSizeX = 1024;
		m_builtInResource.maxComputeWorkGroupSizeY = 1024;
		m_builtInResource.maxComputeWorkGroupSizeZ = 64;
		m_builtInResource.maxComputeUniformComponents = 1024;
		m_builtInResource.maxComputeTextureImageUnits = 16;
		m_builtInResource.maxComputeImageUniforms = 8;
		m_builtInResource.maxComputeAtomicCounters = 8;
		m_builtInResource.maxComputeAtomicCounterBuffers = 1;
		m_builtInResource.maxVaryingComponents = 60;
		m_builtInResource.maxVertexOutputComponents = 64;
		m_builtInResource.maxGeometryInputComponents = 64;
		m_builtInResource.maxGeometryOutputComponents = 128;
		m_builtInResource.maxFragmentInputComponents = 128;
		m_builtInResource.maxImageUnits = 8;
		m_builtInResource.maxCombinedImageUnitsAndFragmentOutputs = 8;
		m_builtInResource.maxCombinedShaderOutputResources = 8;
		m_builtInResource.maxImageSamples = 0;
		m_builtInResource.maxVertexImageUniforms = 0;
		m_builtInResource.maxTessControlImageUniforms = 0;
		m_builtInResource.maxTessEvaluationImageUniforms = 0;
		m_builtInResource.maxGeometryImageUniforms = 0;
		m_builtInResource.maxFragmentImageUniforms = 8;
		m_builtInResource.maxCombinedImageUniforms = 8;
		m_builtInResource.maxGeometryTextureImageUnits = 16;
		m_builtInResource.maxGeometryOutputVertices = 256;
		m_builtInResource.maxGeometryTotalOutputComponents = 1024;
		m_builtInResource.maxGeometryUniformComponents = 1024;
		m_builtInResource.maxGeometryVaryingComponents = 64;
		m_builtInResource.maxTessControlInputComponents = 128;
		m_builtInResource.maxTessControlOutputComponents = 128;
		m_builtInResource.maxTessControlTextureImageUnits = 16;
		m_builtInResource.maxTessControlUniformComponents = 1024;
		m_builtInResource.maxTessControlTotalOutputComponents = 4096;
		m_builtInResource.maxTessEvaluationInputComponents = 128;
		m_builtInResource.maxTessEvaluationOutputComponents = 128;
		m_builtInResource.maxTessEvaluationTextureImageUnits = 16;
		m_builtInResource.maxTessEvaluationUniformComponents = 1024;
		m_builtInResource.maxTessPatchComponents = 120;
		m_builtInResource.maxPatchVertices = 32;
		m_builtInResource.maxTessGenLevel = 64;
		m_builtInResource.maxViewports = 16;
		m_builtInResource.maxVertexAtomicCounters = 0;
		m_builtInResource.maxTessControlAtomicCounters = 0;
		m_builtInResource.maxTessEvaluationAtomicCounters = 0;
		m_builtInResource.maxGeometryAtomicCounters = 0;
		m_builtInResource.maxFragmentAtomicCounters = 8;
		m_builtInResource.maxCombinedAtomicCounters = 8;
		m_builtInResource.maxAtomicCounterBindings = 1;
		m_builtInResource.maxVertexAtomicCounterBuffers = 0;
		m_builtInResource.maxTessControlAtomicCounterBuffers = 0;
		m_builtInResource.maxTessEvaluationAtomicCounterBuffers = 0;
		m_builtInResource.maxGeometryAtomicCounterBuffers = 0;
		m_builtInResource.maxFragmentAtomicCounterBuffers = 1;
		m_builtInResource.maxCombinedAtomicCounterBuffers = 1;
		m_builtInResource.maxAtomicCounterBufferSize = 16384;
		m_builtInResource.maxTransformFeedbackBuffers = 4;
		m_builtInResource.maxTransformFeedbackInterleavedComponents = 64;
		m_builtInResource.maxCullDistances = 8;
		m_builtInResource.maxCombinedClipAndCullDistances = 8;
		m_builtInResource.maxSamples = 4;

		m_builtInResource.limits.nonInductiveForLoops = true;
		m_builtInResource.limits.whileLoops = true;
		m_builtInResource.limits.doWhileLoops = true;
		m_builtInResource.limits.generalUniformIndexing = true;
		m_builtInResource.limits.generalAttributeMatrixVectorIndexing = true;
		m_builtInResource.limits.generalVaryingIndexing = true;
		m_builtInResource.limits.generalSamplerIndexing = true;
		m_builtInResource.limits.generalVariableIndexing = true;
		m_builtInResource.limits.generalConstantMatrixVectorIndexing = true;

		//m_includer.pushExternalLocalDirectory("");

		m_flags[IsGLSLangInitialized] = true;

		return true;
	}

	bool
	ShaderCompiler::onTerminate () noexcept
	{
		if ( m_flags[IsGLSLangInitialized] )
		{
			glslang::FinalizeProcess();

			m_flags[IsGLSLangInitialized] = false;
		}

		return true;
	}

	EShLanguage
	ShaderCompiler::shaderType (ShaderType shaderType) noexcept
	{
		switch ( shaderType )
		{
			case ShaderType::VertexShader :
				return EShLangVertex;

			case ShaderType::TesselationControlShader :
				return EShLangTessControl;

			case ShaderType::TesselationEvaluationShader :
				return EShLangTessEvaluation;

			case ShaderType::GeometryShader :
				return EShLangGeometry;

			case ShaderType::FragmentShader :
				return EShLangFragment;

			case ShaderType::ComputeShader :
				return EShLangCompute;

			default:
				Tracer::error(ClassId, "Unknown shader type !");

				return EShLangCount;
		}
	}

	bool
	ShaderCompiler::compile (const std::shared_ptr< AbstractShader > & shader) noexcept
	{
		if ( shader == nullptr )
		{
			Tracer::error(ClassId, "Null pointer given !");

			return false;
		}

		const std::string shaderIdentifier = (std::stringstream{} << to_string(shader->type()) << " '" << shader->name() << "'").str();

		/* NOTE: The shader must have a source code before a compilation can occur. */
		if ( !shader->isGenerated() )
		{
			TraceError{ClassId} << "The shader '" << shader->name() << "' has an empty source code !";

			return false;
		}

		/* NOTE: If a binary is already present, we remove it. */
		if ( shader->isCompiled() )
		{
			shader->clearBinary();
		}

		if ( m_coreSettings.getAs< bool >(ShowGeneratedSourceCodeKey, DefaultShowGeneratedSourceCode) )
		{
			const SourceCodeParser parser{shader->sourceCode()};

			TraceInfo{ClassId} << "\n"
				"****** START OF GENERATED GLSL SHADER CODE " << shaderIdentifier << " ******" "\n" <<
				parser.getParsedSourceCode() <<
				"****** END OF GENERATED GLSL SHADER CODE " << shaderIdentifier << " ******" "\n";
		}

		/* NOTE: Convert shader type to GLSLang type. */
		const auto type = ShaderCompiler::shaderType(shader->type());
		const auto * sourceCodeCString = shader->sourceCode().c_str();

		glslang::TShader glslShader{type};
		glslShader.setStrings(&sourceCodeCString, 1);
		glslShader.setEnvInput(glslang::EShSourceGlsl, type, glslang::EShClientVulkan, m_defaultVersion);
		glslShader.setEnvClient(glslang::EShClientVulkan, glslang::EShTargetVulkan_1_3);
		glslShader.setEnvTarget(glslang::EShTargetSpv, glslang::EShTargetSpv_1_6);

		/* NOTE: Preprocess the source code. */
		std::string preprocessedSource{};

		if ( glslShader.preprocess(&m_builtInResource, m_defaultVersion, m_profile, m_flags[ForceDefaultVersionAndProfile], m_flags[ForwardCompatible], m_messageFilter, &preprocessedSource, m_includer) )
		{
			Tracer::success(ClassId, "GLSL shader preprocessing succeed !");

			preprocessedSource.erase(std::unique(preprocessedSource.begin(), preprocessedSource.end(), [] (char chrA, char chrB) {
				return chrA == '\n' && chrB == '\n';
			}),preprocessedSource.end());

			if ( m_coreSettings.getAs< bool >(ShowPreprocessedSourceCodeKey, DefaultShowPreprocessedSourceCode) )
			{
				const SourceCodeParser parser{preprocessedSource};

				TraceInfo{ClassId} << "\n"
					"****** START OF PREPROCESSED GLSL SHADER CODE " << shaderIdentifier << " ******" "\n" <<
					parser.getParsedSourceCode() <<
					"****** END OF PREPROCESSED GLSL SHADER CODE " << shaderIdentifier << " ******" "\n";
			}

			const auto * c_string = preprocessedSource.c_str();

			glslShader.setStrings(&c_string, 1);
		}
		else
		{
			TraceError{ClassId} <<
				"GLSL shader preprocessing failed !" "\n"
				"Debugging log :" << glslShader.getInfoDebugLog();

			ShaderCompiler::printCompilationErrors(shaderIdentifier, preprocessedSource, glslShader.getInfoLog());

			return false;
		}

		/* NOTE: Parse the final source code. */
		if ( !glslShader.parse(&m_builtInResource, m_defaultVersion, m_profile, m_flags[ForceDefaultVersionAndProfile], m_flags[ForwardCompatible], m_messageFilter, m_includer) )
		{
			TraceError{ClassId} <<
				"GLSL shader parsing failed !" "\n"
				"Debugging log :" << glslShader.getInfoDebugLog();

			ShaderCompiler::printCompilationErrors(shaderIdentifier, preprocessedSource, glslShader.getInfoLog());

			return false;
		}

		Tracer::success(ClassId, "GLSL shader parsing succeed !");

		/* NOTE: Link the shader. */
		glslang::TProgram program{};
		program.addShader(&glslShader);

		if ( !program.link(m_messageFilter) )
		{
			TraceError{ClassId} <<
				"GLSL shader linking failed !" "\n"
				"Debugging log :" << glslShader.getInfoDebugLog();

			ShaderCompiler::printCompilationErrors(shaderIdentifier, preprocessedSource, glslShader.getInfoLog());

			return false;
		}

		Tracer::success(ClassId, "GLSL shader linking succeed !");

		/* NOTE: Retrieve the binary data. */
		spv::SpvBuildLogger logger{};
		glslang::SpvOptions spvOptions{};

		glslang::GlslangToSpv(*program.getIntermediate(type), shader->m_binaryCode, &logger, &spvOptions);

		const auto messages = logger.getAllMessages();

		if ( !messages.empty() )
		{
			TraceInfo{ClassId} << "GLSL to SPIR-V messages : " << logger.getAllMessages();
		}

		return true;
	}

	void
	ShaderCompiler::printCompilationErrors (const std::string & shaderIdentifier, const std::string & sourceCode, const char * infoLog) noexcept
	{
		SourceCodeParser parser{sourceCode};

		auto errors = String::explode(infoLog, '\n');

		for ( const auto & error : errors )
		{
			const std::string::difference_type number = std::count(error.begin(), error.end(), ':');

			if ( number > 1 )
			{
				auto chunks = String::explode(error, ':');

				auto line = std::stoi(chunks[2]);
				auto column = std::stoi(chunks[1]);

				parser.notice(line, column, error);
			}
			else
			{
				parser.notice(error);
			}
		}

		TraceError{ClassId} << "\n"
			"****** START OF ERRONEOUS GLSL SHADER CODE " << shaderIdentifier << " ******" "\n" <<
			parser.getParsedSourceCode() <<
			"****** END OF ERRONEOUS GLSL SHADER CODE " << shaderIdentifier << " ******" "\n";
	}
}
