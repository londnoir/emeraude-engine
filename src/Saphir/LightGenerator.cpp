/*
 * Emeraude/Saphir/LightGenerator.cpp
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

#include "LightGenerator.hpp"

/* Local inclusions */
#include "Graphics/Light/Processor.hpp"
#include "Graphics/RenderTarget/ShadowMap/Cubemap.hpp"
#include "Graphics/RenderTarget/ShadowMap/Texture2D.hpp"
#include "Graphics/RenderTarget/Texture/Cubemap.hpp"
#include "Graphics/RenderTarget/Texture/Texture2D.hpp"
#include "Graphics/RenderTarget/View/Cubemap.hpp"
#include "Graphics/RenderTarget/View/Texture2D.hpp"
#include "Graphics/RenderableInstance/Unique.hpp"
#include "Settings.hpp"
#include "ShaderGenerator.hpp"
#include "Code.hpp"
#include "Tracer.hpp"

namespace Emeraude::Saphir
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Libraries::PixelFactory;
	using namespace Graphics;
	using namespace Keys;
	using namespace Vulkan;

	LightGenerator::LightGenerator () noexcept
	{
		auto * coreSettings = Settings::instance(SettingsType::Core);
		m_PCFSample = coreSettings->getAs< unsigned int >(Graphics::RenderTarget::ShadowMap::Abstract::PCFSampleKey, Graphics::RenderTarget::ShadowMap::Abstract::DefaultPCFSample);
		m_PCFRadius = coreSettings->getAs< float >(Graphics::RenderTarget::ShadowMap::Abstract::PCFRadiusKey, Graphics::RenderTarget::ShadowMap::Abstract::DefaultPCFRadius);
		m_flags[HighQualityEnabled] = coreSettings->getAs< bool >(ShaderGenerator::HighQualityLightShaderEnabledKey, ShaderGenerator::DefaultHighQualityLightShaderEnabled);
		m_flags[NormalMappingEnabled] = coreSettings->getAs< bool >(ShaderGenerator::NormalMappingEnabledKey, ShaderGenerator::DefaultNormalMappingEnabled);
	}

	LightGenerator::LightGenerator (bool highQualityEnabled, bool normalMappingEnabled, unsigned int PCFSample, float PCFRadius) noexcept
		: m_PCFSample(PCFSample), m_PCFRadius(PCFRadius)
	{
		m_flags[HighQualityEnabled] = highQualityEnabled;
		m_flags[NormalMappingEnabled] = normalMappingEnabled;
	}

	void
	LightGenerator::setupBuiltInLightning (float ambientLevel, Color< float > ambientColor, Vector< 4, float > direction, Color< float > diffuseColor, Color< float > specularColor) noexcept
	{
		m_builtInLightning.ambientLevel = ambientLevel;
		m_builtInLightning.ambientColor = ambientColor;
		m_builtInLightning.direction = direction;
		m_builtInLightning.diffuseColor = diffuseColor;
		m_builtInLightning.specularColor = specularColor;
	}

	bool
	LightGenerator::useNormalMap (const std::string & normalMap, const std::string & textureCoordinates) noexcept
	{
		if ( !m_flags[NormalMappingEnabled] )
		{
			Tracer::warning(ClassId, "The normal mapping code generation is disabled !");

			return false;
		}

		m_flags[UsingNormalMap] = true;
		m_normalMap = normalMap;
		m_normalMapTextureCoordinates = textureCoordinates;

		return true;
	}

	void
	LightGenerator::useSpecularComponent (const std::string & shininessVariable) noexcept
	{
		m_flags[UsingSpecularComponent] = true;
		m_shininessVariable = shininessVariable;
	}

	std::string
	LightGenerator::lightUniform (const char * componentName) noexcept
	{
		return (std::stringstream{} << BufferBackedBlocks::Light << '.' << componentName).str();
	}

	std::string
	LightGenerator::lightVariable (const char * componentName) noexcept
	{
		return (std::stringstream{} << ShaderVariables::Light << '.' << componentName).str();
	}

	std::string
	LightGenerator::variable (const char * instanceName, const char * componentName, const char * index) noexcept
	{
		std::stringstream code{};

		/* ie: "isv_PointLight[lightIndex].directionViewSpace" */
		code << instanceName;

		if ( index != nullptr )
		{
			code << '[' << index << ']';
		}

		code << '.' << componentName;

		return code.str();
	}

	void
	LightGenerator::declareUniformBlocks (ShaderGenerator & gen, uint32_t set, uint32_t bindingPoint) const noexcept
	{
		switch ( gen.renderPassType() )
		{
			case RenderPassType::DirectionalLightPass :
			case RenderPassType::DirectionalLightPassNoShadow :
			{
				Declaration::UniformBlock block{set, bindingPoint, Declaration::MemoryLayout::Std140, UniformBlocks::Light, BufferBackedBlocks::Light};
				block.addMember(Declaration::VariableType::FloatVector4, UniformBlocks::Component::DiffuseColor);
				block.addMember(Declaration::VariableType::FloatVector4, UniformBlocks::Component::SpecularColor);
				block.addMember(Declaration::VariableType::FloatVector4, UniformBlocks::Component::DirectionWorldSpace);
				block.addMember(Declaration::VariableType::FloatVector4, UniformBlocks::Component::DirectionViewSpace);

				if ( gen.renderPassType() == RenderPassType::DirectionalLightPass )
				{
					block.addMember(Declaration::VariableType::Matrix4, UniformBlocks::Component::LightMatrix);
				}

				gen.declare(block);
			}
				break;

			case RenderPassType::PointLightPass :
			case RenderPassType::PointLightPassNoShadow :
			{
				Declaration::UniformBlock block{set, bindingPoint, Declaration::MemoryLayout::Std140, UniformBlocks::Light, BufferBackedBlocks::Light};
				block.addMember(Declaration::VariableType::FloatVector4, UniformBlocks::Component::DiffuseColor);
				block.addMember(Declaration::VariableType::FloatVector4, UniformBlocks::Component::SpecularColor);
				block.addMember(Declaration::VariableType::FloatVector4, UniformBlocks::Component::PositionWorldSpace);
				block.addMember(Declaration::VariableType::FloatVector4, UniformBlocks::Component::PositionViewSpace);
				block.addMember(Declaration::VariableType::Float, UniformBlocks::Component::Radius);

				//if ( gen.renderPassType() == RenderPassType::PointLightPass )
				//	block.addMember(Declaration::VariableType::Matrix4, UniformBlocks::Component::LightMatrix);

				gen.declare(block);
			}
				break;

			case RenderPassType::SpotLightPass :
			case RenderPassType::SpotLightPassNoShadow :
			{
				Declaration::UniformBlock block{set, bindingPoint, Declaration::MemoryLayout::Std140, UniformBlocks::Light, BufferBackedBlocks::Light};
				block.addMember(Declaration::VariableType::FloatVector4, UniformBlocks::Component::DiffuseColor);
				block.addMember(Declaration::VariableType::FloatVector4, UniformBlocks::Component::SpecularColor);
				block.addMember(Declaration::VariableType::FloatVector4, UniformBlocks::Component::PositionWorldSpace);
				block.addMember(Declaration::VariableType::FloatVector4, UniformBlocks::Component::PositionViewSpace);
				block.addMember(Declaration::VariableType::FloatVector4, UniformBlocks::Component::DirectionWorldSpace);
				block.addMember(Declaration::VariableType::FloatVector4, UniformBlocks::Component::DirectionViewSpace);
				block.addMember(Declaration::VariableType::Float, UniformBlocks::Component::Radius);
				block.addMember(Declaration::VariableType::Float, UniformBlocks::Component::InnerCosAngle);
				block.addMember(Declaration::VariableType::Float, UniformBlocks::Component::OuterCosAngle);

				if ( gen.renderPassType() == RenderPassType::SpotLightPass )
				{
					block.addMember(Declaration::VariableType::Matrix4, UniformBlocks::Component::LightMatrix);
				}

				gen.declare(block);
			}
				break;

			default :
				/* NOTE: No other type of render pass needs uniform blocks. */
				break;
		}
	}

	void
	LightGenerator::declareOutputBlocks (ShaderGenerator & gen, LightType type, bool usingShadowMap) const noexcept
	{
		if ( gen.shaderType() != ShaderType::VertexShader )
		{
			Tracer::error(ClassId, "Declaring output block must be done within the vertex shader stage !");

			return;
		}

		switch ( type )
		{
			case LightType::Directional :
				if ( usingShadowMap || m_flags[UsingNormalMap] )
				{
					Declaration::OutputBlock block{ShaderBlocks::Light, 0, ShaderVariables::Light};

					if ( usingShadowMap )
					{
						block.addMember(Declaration::VariableType::FloatVector4, ShaderBlocks::Component::PositionLightSpace, GLSL::Smooth);
					}

					if ( m_flags[UsingNormalMap] )
					{
						block.addMember(Declaration::VariableType::FloatVector3, ShaderBlocks::Component::DirectionTextureSpace, GLSL::Smooth);

						if ( !m_flags[HighQualityEnabled] )
						{
							block.addMember(Declaration::VariableType::FloatVector3, ShaderBlocks::Component::ViewDirectionTextureSpace, GLSL::Smooth);
						}
					}

					gen.declare(block);
				}
				break;

			case LightType::Point :
				{
					Declaration::OutputBlock block{ShaderBlocks::Light, 1, ShaderVariables::Light};

					if ( usingShadowMap )
					{
						block.addMember(Declaration::VariableType::FloatVector4,  ShaderBlocks::Component::DirectionWorldSpace, GLSL::Smooth);
					}

					block.addMember(Declaration::VariableType::FloatVector3, ShaderBlocks::Component::DirectionViewSpace, GLSL::Smooth);

					if ( m_flags[UsingNormalMap] )
					{
						block.addMember(Declaration::VariableType::FloatVector3, ShaderBlocks::Component::DirectionTextureSpace, GLSL::Smooth);
					}

					if ( !m_flags[HighQualityEnabled] )
					{
						block.addMember(Declaration::VariableType::Float, ShaderBlocks::Component::AttenuationFactor, GLSL::Smooth);
					}

					gen.declare(block);
				}
				break;

			case LightType::Spot :
				{
					Declaration::OutputBlock block{ShaderBlocks::Light, 2, ShaderVariables::Light};

					if ( usingShadowMap )
					{
						block.addMember(Declaration::VariableType::FloatVector4, ShaderBlocks::Component::PositionLightSpace, GLSL::Smooth);
					}

					block.addMember(Declaration::VariableType::FloatVector3, ShaderBlocks::Component::DirectionViewSpace, GLSL::Smooth);

					if ( m_flags[UsingNormalMap] )
					{
						block.addMember(Declaration::VariableType::FloatVector3,ShaderBlocks::Component::DirectionTextureSpace, GLSL::Smooth);
					}

					if ( !m_flags[HighQualityEnabled] )
					{
						block.addMember(Declaration::VariableType::Float, ShaderBlocks::Component::AttenuationFactor, GLSL::Smooth);
						block.addMember(Declaration::VariableType::Float, ShaderBlocks::Component::SpotFactor, GLSL::Smooth);
					}

					gen.declare(block);
				}
				break;
		}
	}

	void
	LightGenerator::declareInputBlocks (ShaderGenerator & gen, LightType type, bool usingShadowMap) const noexcept
	{
		if ( gen.shaderType() != ShaderType::FragmentShader )
		{
			Tracer::error(ClassId, "Declaring output block must be done within the fragment shader stage !");

			return;
		}

		switch ( type )
		{
			case LightType::Directional :
				if ( usingShadowMap || m_flags[UsingNormalMap] )
				{
					Declaration::InputBlock block{ShaderBlocks::Light, 0, ShaderVariables::Light};

					if ( usingShadowMap )
					{
						block.addMember(Declaration::VariableType::FloatVector4,ShaderBlocks::Component::PositionLightSpace, GLSL::Smooth);
					}

					if ( m_flags[UsingNormalMap] )
					{
						block.addMember(Declaration::VariableType::FloatVector3, ShaderBlocks::Component::DirectionTextureSpace, GLSL::Smooth);

						if ( !m_flags[HighQualityEnabled] )
						{
							block.addMember(Declaration::VariableType::FloatVector3, ShaderBlocks::Component::ViewDirectionTextureSpace, GLSL::Smooth);
						}
					}

					gen.declare(block);
				}
				break;

			case LightType::Point :
				{
					Declaration::InputBlock block{ShaderBlocks::Light, 1, ShaderVariables::Light};

					if ( usingShadowMap )
					{
						block.addMember(Declaration::VariableType::FloatVector4, ShaderBlocks::Component::DirectionWorldSpace, GLSL::Smooth);
					}

					block.addMember(Declaration::VariableType::FloatVector3, ShaderBlocks::Component::DirectionViewSpace, GLSL::Smooth);

					if ( m_flags[UsingNormalMap] )
					{
						block.addMember(Declaration::VariableType::FloatVector3, ShaderBlocks::Component::DirectionTextureSpace, GLSL::Smooth);
					}

					if ( !m_flags[HighQualityEnabled] )
					{
						block.addMember(Declaration::VariableType::Float, ShaderBlocks::Component::AttenuationFactor, GLSL::Smooth);
					}

					gen.declare(block);
				}
				break;

			case LightType::Spot :
				{
					Declaration::InputBlock block{ShaderBlocks::Light, 2, ShaderVariables::Light};

					if ( usingShadowMap )
					{
						block.addMember(Declaration::VariableType::FloatVector4, ShaderBlocks::Component::PositionLightSpace, GLSL::Smooth);
					}

					block.addMember(Declaration::VariableType::FloatVector3, ShaderBlocks::Component::DirectionViewSpace, GLSL::Smooth);

					if ( m_flags[UsingNormalMap] )
					{
						block.addMember(Declaration::VariableType::FloatVector3, ShaderBlocks::Component::DirectionTextureSpace, GLSL::Smooth);
					}

					if ( !m_flags[HighQualityEnabled] )
					{
						block.addMember(Declaration::VariableType::Float, ShaderBlocks::Component::AttenuationFactor, GLSL::Smooth);
						block.addMember(Declaration::VariableType::Float, ShaderBlocks::Component::SpotFactor, GLSL::Smooth);
					}

					gen.declare(block);
				}
				break;
		}
	}

	bool
	LightGenerator::generateShaderCode (ShaderGenerator & gen, const Geometry::Interface & geometry) const noexcept
	{
		bool usingShadowMap = false;

		switch ( gen.renderPassType() )
		{
			case RenderPassType::SimplePass :
				/* NOTE: A simple pass to no involve lighting. */
			case RenderPassType::AmbientPass :
				/* FIXME: The ambient pass could do something. Must check ... */
				return true;

			case RenderPassType::SimpleWithFakeLightPass :
				switch ( gen.shaderType() )
				{
					case ShaderType::VertexShader :

						if ( m_flags[HighQualityEnabled] )
						{
							this->generateFakeLightHQVertexShader(gen, geometry);
						}
						else
						{
							this->generateBuiltInLightGouraudVertexShader(gen, geometry);
						}

						break;

					case ShaderType::FragmentShader :

						if ( m_flags[HighQualityEnabled] )
						{
							this->generateFakeLightHQFragmentShader(gen);
						}
						else
						{
							this->generateBuiltInLightGouraudFragmentShader(gen);
						}

						break;

					default :
						return true;
				}
				break;

			/* Directional light code generation for vertex and fragment shader. */
			case RenderPassType::DirectionalLightPass :
				usingShadowMap = true;

				[[fallthrough]];

			case RenderPassType::DirectionalLightPassNoShadow :
				switch ( gen.shaderType() )
				{
					case ShaderType::VertexShader :
						this->generateVertexShader(gen, geometry, LightType::Directional, usingShadowMap);

						break;

					case ShaderType::FragmentShader :
						this->generateFragmentShader(gen, LightType::Directional, usingShadowMap);

						break;

					default :
						return true;
				}
				break;

			/* Point light code generation for vertex and fragment shader. */
			case RenderPassType::PointLightPass :
				usingShadowMap = true;

				[[fallthrough]];

			case RenderPassType::PointLightPassNoShadow :
				switch ( gen.shaderType() )
				{
					case ShaderType::VertexShader :
						this->generateVertexShader(gen, geometry, LightType::Point, usingShadowMap);

						break;

					case ShaderType::FragmentShader :
						this->generateFragmentShader(gen, LightType::Point, usingShadowMap);

						break;

					default :
						return true;
				}
				break;

			/* Spot light code generation for vertex and fragment shader. */
			case RenderPassType::SpotLightPass :
				usingShadowMap = true;

				[[fallthrough]];

			case RenderPassType::SpotLightPassNoShadow :
				switch ( gen.shaderType() )
				{
					case ShaderType::VertexShader :
						this->generateVertexShader(gen, geometry, LightType::Spot, usingShadowMap);
						break;

					case ShaderType::FragmentShader :
						this->generateFragmentShader(gen, LightType::Spot, usingShadowMap);
						break;

					default :
						return true;
				}
				break;

			case RenderPassType::None :
				Tracer::error(ClassId, "Calling the light code generation render pass set to 'None' !");
				return false;
		}

		return true;
	}

	void
	LightGenerator::generateBuiltInLightGouraudVertexShader (ShaderGenerator & gen, const Graphics::Geometry::Interface &geometry) const noexcept
	{
		if ( !m_flags[UsingNormalMap] )
		{
			Tracer::warning(ClassId, "Normal mapping is not available with Gouraud shading technics !");
		}

		if ( !geometry.normalEnabled() )
		{
			Tracer::error(ClassId, "Normal must be available in the vertex attributes to compute lighting !");

			return;
		}

		/* Declares the light output block to fragment shader. */
		this->declareOutputBlocks(gen, LightType::Directional, false);

		/* Diffuse component per vertex. */
		{
			gen.declare(Declaration::InputAttribute{VertexAttributeType::Normal});
			gen.declare(Declaration::StageOutput{ShaderVariables::DiffuseFactor, GLSL::Smooth});

			Code{gen} <<
				"const vec3 L = -normalize(" << m_builtInLightning.direction << ".xyz);";

			Code{gen, Location::Output} <<
				ShaderVariables::DiffuseFactor << " = max(0.0, dot(L, " << Attributes::Normal << "));";
		}

		/* Optional specular component per vertex. */
		if ( m_flags[UsingSpecularComponent] )
		{
			//gen.declare(Declaration::Uniform{Declaration::VariableType::Float, m_shininessVariable.c_str(), "90.0"});
			gen.declare(Declaration::StageOutput{ShaderVariables::SpecularFactor, GLSL::Smooth});

			Code{gen} <<
				"const vec3 invV = -normalize(" << Attributes::Position << ".xyz);" << Line::End <<
				"const vec3 R = -reflect(L, " << Attributes::Normal << ");";

			Code{gen, Location::Output} <<
				ShaderVariables::SpecularFactor << " = pow(max(0.0, dot(invV, R)), " << m_shininessVariable << ");";
		}
	}

	void
	LightGenerator::generateBuiltInLightGouraudFragmentShader (ShaderGenerator & gen) const noexcept
	{
		if ( !m_flags[UsingNormalMap] )
		{
			Tracer::warning(ClassId, "Normal mapping is not available with Gouraud shading technics !");
		}

		/* Declares the light input block from vertex shader. */
		this->declareInputBlocks(gen, LightType::Directional, false);

		Code{gen, Location::Top} <<
			"vec4 " << LightFinalColor << " = vec4(0.0, 0.0, 0.0, 1.0);";

		/* Ambient component. */
		{
			gen.addComment("Ambient component");

			Code{gen} <<
				 "const vec4 " << LightAmbientColor << " = vec4(" << m_builtInLightning.ambientColor.toVector3< float >() << " * " << m_builtInLightning.ambientLevel << ", 1.0);";

			/* Apply light specular color on the output. */
			Code{gen} <<
				LightFinalColor << " += " << LightAmbientColor << ';';
		}

		/* Diffuse component per vertex. */
		{
			gen.addComment("Diffuse component");

			gen.declare(Declaration::StageInput{ShaderVariables::DiffuseFactor, GLSL::Smooth});

			Code{gen} <<
				"const vec4 " << LightDiffuseColor << " = vec4(" << m_builtInLightning.diffuseColor.toVector3< float >() << " * " << ShaderVariables::DiffuseFactor << ", 1.0);";

			Code{gen} <<
				LightFinalColor << " += " << LightDiffuseColor << ';';
		}

		/* Optional specular component. */
		if ( m_flags[UsingSpecularComponent] )
		{
			gen.addComment("Specular component");

			/* Compute specular component per vertex. */
			gen.declare(Declaration::StageInput{ShaderVariables::SpecularFactor, GLSL::Smooth});

			Code{gen} <<
				"const vec4 " << LightSpecularColor << " = vec4(" << m_builtInLightning.specularColor.toVector3< float >() << " * " << ShaderVariables::SpecularFactor << ", 1.0);";

			/* Apply light specular color on the output. */
			Code{gen} <<
				LightFinalColor << " += " << LightSpecularColor << ';';
		}

		/* Apply light specular color on the output. */
		Code{gen, Location::Output} <<
			ShaderVariables::OutputFragment << " *= " << LightFinalColor << ';';
	}

	void
	LightGenerator::generateFakeLightHQVertexShader (ShaderGenerator & gen, const Graphics::Geometry::Interface & geometry) const noexcept
	{
		if ( !geometry.normalEnabled() )
		{
			Tracer::warning(ClassId, "Normal must be available in the vertex attributes to compute lighting !");

			return;
		}

		/* Declares the light output block to fragment shader. */
		this->declareOutputBlocks(gen, LightType::Directional, false);

		/* Diffuse component (all lights). */
		if ( m_flags[UsingNormalMap] )
		{
			/* Compute diffuse component per fragment using a normal map. */
			gen.requestVertexShaderSynthesizeInstruction(ShaderVariables::ViewTBNMatrix, ShaderGenerator::VariableScope::ToNextStage);
		}
		else
		{
			/* Compute diffuse component per fragment. */
			gen.requestVertexShaderSynthesizeInstruction(ShaderVariables::NormalViewSpace, ShaderGenerator::VariableScope::ToNextStage);
		}

		/* Optional specular component (all lights). */
		if ( m_flags[UsingSpecularComponent] )
		{
			if ( m_flags[UsingNormalMap] )
			{
				if ( m_flags[HighQualityEnabled] )
				{
					/* Compute specular component per fragment using a normal map. */
					gen.requestVertexShaderSynthesizeInstruction(ShaderVariables::PositionViewSpace, ShaderGenerator::VariableScope::ToNextStage);
					gen.requestVertexShaderSynthesizeInstruction(ShaderVariables::ViewTBNMatrix, ShaderGenerator::VariableScope::ToNextStage);
				}
				else
				{
					/* Compute specular component per vertex using a normal map. */
					gen.requestVertexShaderSynthesizeInstruction(ShaderVariables::ViewTBNMatrix, ShaderGenerator::VariableScope::Local);
					gen.requestVertexShaderSynthesizeInstruction(ShaderVariables::PositionViewSpace, ShaderGenerator::VariableScope::Local);

					Code{gen} <<
							  LightGenerator::lightVariable(ShaderBlocks::Component::ViewDirectionTextureSpace) << " = normalize(" << ShaderVariables::ViewTBNMatrix << " * " << ShaderVariables::PositionViewSpace << ".xyz);";
				}
			}
			else
			{
				/* Compute specular component per fragment. */
				gen.requestVertexShaderSynthesizeInstruction(ShaderVariables::PositionViewSpace, ShaderGenerator::VariableScope::ToNextStage);
				gen.requestVertexShaderSynthesizeInstruction(ShaderVariables::NormalViewSpace, ShaderGenerator::VariableScope::ToNextStage);
			}
		}
	}

	/**
	 * @brief Generates the fragment shader source code for one fixed directional light.
	 * @note Light calculation is done in fragment shader.
	 * @param gen A reference to the shader generator.
	 * @return void
	 */
	void
	LightGenerator::generateFakeLightHQFragmentShader (ShaderGenerator & gen) const noexcept
	{
		/* Declares the light input block from vertex shader. */
		this->declareInputBlocks(gen, LightType::Directional, false);

		/* NOTE: Light direction for the whole light code. */
		if ( m_flags[UsingNormalMap] )
		{
			gen.declare(Declaration::StageInput{ShaderVariables::ViewTBNMatrix, GLSL::Smooth});

			Code{gen} <<
					  "const vec3 LViewSpace = normalize(" << LightGenerator::lightUniform(UniformBlocks::Component::DirectionViewSpace) << ".xyz);" << Line::End <<
					  "const vec3 L = " << ShaderVariables::ViewTBNMatrix << " * LViewSpace;";
		}
		else
		{
			Code{gen} <<
					  "const vec3 L = " << LightGenerator::lightUniform(UniformBlocks::Component::DirectionViewSpace) << ".xyz;";
		}

		Code::EmptyLine(gen);

		/* Diffuse component. */
		{
			if ( m_flags[UsingNormalMap] )
			{
				/* NOTE: Get a sample from a texture in range [0,1], convert it to a normalized range of [-1, 1]. */
				Code{gen} <<
					"const vec3 N = normalize(texture(" << m_normalMap << ", " << m_normalMapTextureCoordinates << ").rgb * 2.0 - 1.0);" << Line::End <<
					"float " << ShaderVariables::DiffuseFactor << " = max(0.0, dot(-L, N));";
			}
			else
			{
				/* Compute diffuse component per fragment. */
				gen.declare(Declaration::StageInput{ShaderVariables::NormalViewSpace, GLSL::Smooth});

				Code{gen} <<
					"float " << ShaderVariables::DiffuseFactor << " = max(0.0, dot(-L, " << ShaderVariables::NormalViewSpace << "));";
			}

			Code{gen} <<
				"const vec4 " << LightDiffuseColor << " = vec4(" << m_builtInLightning.diffuseColor.toVector3< float >() << " * " << ShaderVariables::DiffuseFactor << ", 1.0);";

			/* Apply light diffuse color on the output. */
			Code{gen, Location::Output} <<
				ShaderVariables::OutputFragment << " *= " << LightDiffuseColor << ';';
		}

		/* Optional specular component. */
		if ( m_flags[UsingSpecularComponent] )
		{
			if ( m_flags[UsingNormalMap] )
			{
				//gen.declare(Declaration::Uniform{Declaration::VariableType::Float, m_shininessVariable.c_str(), "1.0"});
				gen.declare(Declaration::StageInput{ShaderVariables::ViewTBNMatrix, GLSL::Smooth});
				gen.declare(Declaration::StageInput{ShaderVariables::PositionViewSpace, GLSL::Smooth});

				Code{gen} <<
						  "const vec3 invV = normalize(" << ShaderVariables::ViewTBNMatrix << " * " << ShaderVariables::PositionViewSpace << ".xyz);" << Line::End <<
						  "const vec3 R = reflect(-L, N);" << Line::End <<
						  "float " << ShaderVariables::SpecularFactor << " = pow(max(0.0, dot(invV, R)), " << m_shininessVariable << ");";
			}
			else
			{
				/* Compute specular component per fragment. */
				//gen.declare(Declaration::Uniform{Declaration::VariableType::Float, m_shininessVariable.c_str(), "1.0"});
				gen.declare(Declaration::StageInput{ShaderVariables::PositionViewSpace, GLSL::Smooth});
				gen.declare(Declaration::StageInput{ShaderVariables::NormalViewSpace, GLSL::Smooth});

				Code{gen} <<
						  "const vec3 R = reflect(-L, " << ShaderVariables::NormalViewSpace << ");" << Line::End <<
						  "const vec3 invV = normalize(" << ShaderVariables::PositionViewSpace << ".xyz);" << Line::End <<
						  "float " << ShaderVariables::SpecularFactor << " = pow(max(0.0, dot(invV, R)), " << m_shininessVariable << ");";
			}

			Code{gen} <<
				"const vec4 " << LightSpecularColor << " = vec4(" << m_builtInLightning.specularColor.toVector3< float >() << " * " << ShaderVariables::SpecularFactor << ", 1.0);";

			/* Apply light specular color on the output. */
			Code{gen, Location::Output} <<
				ShaderVariables::OutputFragment << " *= " << LightSpecularColor << ';';
		}
	}

	void
	LightGenerator::generateVertexShader (ShaderGenerator & gen, const Geometry::Interface & geometry, LightType type, bool usingShadowMap) const noexcept
	{
		if ( !geometry.normalEnabled() )
		{
			Tracer::warning(ClassId, "Normal must be available in the vertex attributes to compute lighting !");

			return;
		}

		/* Declare the light UBO. */
		this->declareUniformBlocks(gen, 0, 1);

		/* Declares the light output block to fragment shader. */
		this->declareOutputBlocks(gen, type, usingShadowMap);

		/* NOTE: Light direction is requested by specular component per vertex. */
		if ( type == LightType::Directional )
		{
			/* NOTE: With directional light we already have a direction vector. */
			if ( !m_flags[HighQualityEnabled] )
			{
				Code{gen} <<
					 "const vec3 L = normalize(" << LightGenerator::lightUniform(UniformBlocks::Component::DirectionViewSpace) << ".xyz);";
			}
		}
		else
		{
			gen.requestVertexShaderSynthesizeInstruction(ShaderVariables::PositionViewSpace, ShaderGenerator::VariableScope::Local);

			/* NOTE: With point and spotlights, we need to compute the direction vector. We let the distance vector for attenuation. */
			Code{gen} <<
				  "const vec3 " << Distance << " = " << ShaderVariables::PositionViewSpace << ".xyz - " << LightGenerator::lightUniform(UniformBlocks::Component::PositionViewSpace) << ".xyz;";

			if ( !m_flags[HighQualityEnabled] )
			{
				Code{gen} <<
					  "const vec3 L = normalize(" << Distance << ");" << Line::End <<
					  LightGenerator::lightVariable(ShaderBlocks::Component::DirectionViewSpace) << " = L;";
			}
		}

		/* Shadow " << GLSL::Discard << " code (all lights). */
		if ( usingShadowMap )
		{
			/* NOTE: Sending data to retrieve the computed fragment into the shadow map. */
			gen.declare(Declaration::InputAttribute{VertexAttributeType::Position});

			switch ( gen.modelMatricesType() )
			{
				case ModelMatrixType::UniformBufferObject :
					if ( !gen.declare(RenderableInstance::Unique::getModelUniformBlock(gen.indexes().set(SetType::PerModel))) )
					{
						TraceWarning{ClassId} << "Unable to declare model uniform block !";
					}

					if ( type == LightType::Point )
					{
						Code{gen, Location::Output} <<
							LightGenerator::lightVariable(ShaderBlocks::Component::DirectionWorldSpace) << " = " <<
							LightGenerator::lightUniform(UniformBlocks::Component::PositionWorldSpace) << " - " <<
							ShaderGenerator::modelUniform(UniformBlocks::Component::ModelMatrix) << " * "
							"vec4(" << Attributes::Position<< ", 1.0);";
					}
					else
					{
						Code{gen, Location::Output} <<
							LightGenerator::lightVariable(ShaderBlocks::Component::PositionLightSpace) << " = " <<
							ShaderGenerator::modelUniform(UniformBlocks::Component::ModelLightMatrix) << " * "
							"vec4(" << Attributes::Position << ", 1.0);";
					}
					break;

				case ModelMatrixType::VertexBufferObject :
					gen.declare(Declaration::InputAttribute{VertexAttributeType::ModelMatrixR0});

					if ( type == LightType::Point )
					{
						Code{gen, Location::Output} <<
							LightGenerator::lightVariable(ShaderBlocks::Component::DirectionWorldSpace) << " = " <<
							LightGenerator::lightUniform(UniformBlocks::Component::PositionWorldSpace) << " - " <<
							Attributes::ModelMatrix << " * "
							"vec4(" << Attributes::Position << ", 1.0);";
					}
					else
					{
						Code{gen, Location::Output} <<
							LightGenerator::lightVariable(ShaderBlocks::Component::PositionLightSpace) << " = " <<
							LightGenerator::lightUniform(UniformBlocks::Component::LightMatrix) << " * " <<
							Attributes::ModelMatrix << " * "
							"vec4(" << Attributes::Position << ", 1.0);";
					}
					break;

				case ModelMatrixType::Invalid :
					Tracer::error(ClassId, "Invalid matrix type !");
					break;
			}
		}

		/* Attenuation " << GLSL::Discard << " code (point and spotlights). */
		if ( type != LightType::Directional )
		{
			if ( m_flags[HighQualityEnabled] )
			{
				/* Compute attenuation per fragment. */
				gen.requestVertexShaderSynthesizeInstruction(ShaderVariables::PositionViewSpace, ShaderGenerator::VariableScope::ToNextStage);
			}
			else
			{
				/* Compute attenuation per vertex. */
				const auto radius = LightGenerator::lightVariable(UniformBlocks::Component::Radius);
				const auto attenuationFactor = LightGenerator::lightVariable(ShaderBlocks::Component::AttenuationFactor);

				Code{gen} <<
					"if ( " << radius << " > 0.0 ) " << Line::End <<
					'{' << Line::End <<
					"	const vec3 DR = abs(" << Distance << ") / " << radius << ';' << Line::Blank <<

					"	" << attenuationFactor << " = max(0.0, 1.0 - dot(DR, DR));" << Line::End <<
					'}' << Line::End <<
					"else" << Line::End <<
					'{' << Line::End <<
					"	" << attenuationFactor << " = 1.0;" << Line::End <<
					'}';
			}
		}

		/* Cone " << GLSL::Discard << " code (spot lights). */
		if ( type == LightType::Spot )
		{
			if ( m_flags[HighQualityEnabled] )
			{
				/* Compute cone per fragment. */
				gen.requestVertexShaderSynthesizeInstruction(ShaderVariables::PositionViewSpace, ShaderGenerator::VariableScope::ToNextStage);
			}
			else
			{
				/* Compute cone per vertex. */
				const auto directionViewSpace = LightGenerator::lightUniform(UniformBlocks::Component::DirectionViewSpace);
				const auto innerCosAngle = LightGenerator::lightUniform(UniformBlocks::Component::InnerCosAngle);
				const auto outerCosAngle = LightGenerator::lightUniform(UniformBlocks::Component::OuterCosAngle);
				const auto spotFactor = LightGenerator::lightVariable(ShaderBlocks::Component::SpotFactor);

				Code{gen} <<
					"const float theta = dot(L, " << directionViewSpace << ".xyz);" << Line::End <<
					"const float epsilon = " << innerCosAngle << " - " << outerCosAngle << ";" << Line::Blank <<
					spotFactor << " = clamp((theta - " << outerCosAngle << ") / epsilon, 0.0, 1.0);";
			}
		}

		/* Diffuse component (all lights). */
		if ( m_flags[UsingNormalMap] )
		{
			if ( m_flags[DiscardBackFaceWithNormalMap] )
			{
				gen.requestVertexShaderSynthesizeInstruction(ShaderVariables::NormalViewSpace, ShaderGenerator::VariableScope::ToNextStage);
			}

			if ( m_flags[HighQualityEnabled] )
			{
				/* Compute diffuse component per fragment using a normal map. */
				gen.requestVertexShaderSynthesizeInstruction(ShaderVariables::ViewTBNMatrix, ShaderGenerator::VariableScope::ToNextStage);
			}
			else
			{
				/* Compute diffuse component per vertex using a normal map. */
				gen.requestVertexShaderSynthesizeInstruction(ShaderVariables::ViewTBNMatrix, ShaderGenerator::VariableScope::Local);

				Code{gen} <<
					LightGenerator::lightVariable(ShaderBlocks::Component::DirectionTextureSpace) << " = normalize(" << ShaderVariables::ViewTBNMatrix << " * L);";
			}
		}
		else
		{
			if ( m_flags[HighQualityEnabled] )
			{
				/* Compute diffuse component per fragment. */
				gen.requestVertexShaderSynthesizeInstruction(ShaderVariables::NormalViewSpace, ShaderGenerator::VariableScope::ToNextStage);
			}
			else
			{
				/* Compute diffuse component per vertex. */
				gen.requestVertexShaderSynthesizeInstruction(ShaderVariables::NormalViewSpace, ShaderGenerator::VariableScope::Local);
				gen.declare(Declaration::StageOutput{ShaderVariables::DiffuseFactor, GLSL::Smooth});

				Code{gen} <<
					ShaderVariables::DiffuseFactor << " = dot(-L, " << ShaderVariables::NormalViewSpace << ");";
			}
		}

		/* Optional specular component (all lights). */
		if ( m_flags[UsingSpecularComponent] )
		{
			if ( m_flags[UsingNormalMap] )
			{
				if ( m_flags[HighQualityEnabled] )
				{
					/* Compute specular component per fragment using a normal map. */
					gen.requestVertexShaderSynthesizeInstruction(ShaderVariables::PositionViewSpace, ShaderGenerator::VariableScope::ToNextStage);
					gen.requestVertexShaderSynthesizeInstruction(ShaderVariables::ViewTBNMatrix, ShaderGenerator::VariableScope::ToNextStage);
				}
				else
				{
					/* Compute specular component per vertex using a normal map. */
					gen.requestVertexShaderSynthesizeInstruction(ShaderVariables::ViewTBNMatrix, ShaderGenerator::VariableScope::Local);

					if ( type == LightType::Directional )
					{
						gen.requestVertexShaderSynthesizeInstruction(ShaderVariables::PositionViewSpace, ShaderGenerator::VariableScope::Local);

						Code{gen} <<
							LightGenerator::lightVariable(ShaderBlocks::Component::ViewDirectionTextureSpace) << " = "
							"normalize(" << ShaderVariables::ViewTBNMatrix << " * " << ShaderVariables::PositionViewSpace << ".xyz);";
					}
					else
					{
						gen.requestVertexShaderSynthesizeInstruction(ShaderVariables::PositionViewSpace, ShaderGenerator::VariableScope::Local);
						gen.declare(Declaration::StageOutput{ShaderVariables::PositionTextureSpace,  GLSL::Smooth});

						Code{gen} <<
							ShaderVariables::PositionTextureSpace << " = "
							"normalize(" << ShaderVariables::ViewTBNMatrix << " * " << ShaderVariables::PositionViewSpace << ".xyz);";
					}
				}
			}
			else
			{
				if ( m_flags[HighQualityEnabled] )
				{
					/* Compute specular component per fragment. */
					gen.requestVertexShaderSynthesizeInstruction(ShaderVariables::PositionViewSpace, ShaderGenerator::VariableScope::ToNextStage);
					gen.requestVertexShaderSynthesizeInstruction(ShaderVariables::NormalViewSpace, ShaderGenerator::VariableScope::ToNextStage);
				}
				else
				{
					/* Compute specular component per vertex. */
					//gen.declare(Declaration::Uniform{Declaration::VariableType::Float, m_shininessVariable.c_str(), "1.0"});
					gen.requestVertexShaderSynthesizeInstruction(ShaderVariables::PositionViewSpace, ShaderGenerator::VariableScope::Local);
					gen.requestVertexShaderSynthesizeInstruction(ShaderVariables::NormalViewSpace, ShaderGenerator::VariableScope::Local);
					gen.declare(Declaration::StageOutput{ShaderVariables::SpecularFactor, GLSL::Smooth});

					Code{gen} <<
						"const vec3 invV = normalize(" << ShaderVariables::PositionViewSpace << ".xyz);" << Line::End <<
						"const vec3 R = reflect(-L, " << ShaderVariables::NormalViewSpace << ");" << Line::Blank <<
						ShaderVariables::SpecularFactor << " = pow(max(0.0, dot(invV, R)), " << m_shininessVariable << ");";
				}
			}
		}
	}

	void
	LightGenerator::generateFragmentShader (ShaderGenerator & gen, LightType type, bool usingShadowMap) const noexcept
	{
		/* Declare the light UBO. */
		this->declareUniformBlocks(gen, 0, 1);

		/* Declares the light input block from vertex shader. */
		this->declareInputBlocks(gen, type, usingShadowMap);

		/* Declaring the variables which will be modulated through the whole light code. */
		{
			const auto diffuseColor = LightGenerator::lightUniform(UniformBlocks::Component::DiffuseColor);

			Code{gen} <<
				"vec4 " << LightDiffuseColor << " = " << diffuseColor << ';';

			if ( m_flags[UsingSpecularComponent] )
			{
				const auto specularColor = LightGenerator::lightUniform(UniformBlocks::Component::SpecularColor);

				Code{gen} <<
					"vec4 " << LightSpecularColor << " = " << specularColor << ';';
			}
		}

		/* NOTE: Light direction for the whole light code. */
		if ( m_flags[UsingNormalMap] )
		{
			if ( m_flags[HighQualityEnabled] )
			{
				gen.declare(Declaration::StageInput{ShaderVariables::ViewTBNMatrix, GLSL::Smooth});

				if ( type == LightType::Directional )
				{
					const auto directionViewSpace = LightGenerator::lightUniform(UniformBlocks::Component::DirectionViewSpace);

					Code{gen} <<
						"const vec3 LViewSpace = normalize(" << directionViewSpace << ".xyz);" << Line::End <<
						"const vec3 L = " << ShaderVariables::ViewTBNMatrix << " * LViewSpace;";
				}
				else
				{
					const auto positionViewSpace = LightGenerator::lightUniform(UniformBlocks::Component::PositionViewSpace);

					gen.declare(Declaration::StageInput{ShaderVariables::PositionViewSpace, GLSL::Smooth});

					Code{gen} <<
						"const vec3 " << Distance << " = " << ShaderVariables::PositionViewSpace << ".xyz - " << positionViewSpace << ".xyz;" << Line::End <<
						"const vec3 LViewSpace = normalize(" << Distance << ");" << Line::End <<
						"const vec3 L = " << ShaderVariables::ViewTBNMatrix << " * LViewSpace;";
				}
			}
			else
			{
				const auto directionTextureSpace = LightGenerator::lightVariable(ShaderBlocks::Component::DirectionTextureSpace);

				if ( type == LightType::Directional )
				{
					const auto directionViewSpace = LightGenerator::lightUniform(UniformBlocks::Component::DirectionViewSpace);

					Code{gen} <<
						"const vec3 LViewSpace = normalize(" << directionViewSpace << ".xyz);" << Line::End <<
						"const vec3 L = " << directionTextureSpace << ';';
				}
				else
				{
					const auto directionViewSpace = LightGenerator::lightVariable(ShaderBlocks::Component::DirectionViewSpace);

					Code{gen} <<
						"const vec3 LViewSpace = normalize(" << directionViewSpace << ".xyz);" << Line::End <<
						"const vec3 L = " << directionTextureSpace << ';';
				}
			}
		}
		else
		{
			if ( m_flags[HighQualityEnabled] )
			{
				if ( type == LightType::Directional )
				{
					/* NOTE: With directional light we already have a direction vector. */
					Code{gen} <<
						"const vec3 L = " << LightGenerator::lightUniform(UniformBlocks::Component::DirectionViewSpace) << ".xyz;";
				}
				else
				{
					gen.declare(Declaration::StageInput{ShaderVariables::PositionViewSpace, GLSL::Smooth});

					Code{gen} <<
						"const vec3 " << Distance << " = " << ShaderVariables::PositionViewSpace << ".xyz - " << LightGenerator::lightUniform(UniformBlocks::Component::PositionViewSpace) << ".xyz;" << Line::End <<
						"const vec3 L = normalize(" << Distance << ");";
				}
			}
			else
			{
				/* NOTE: No need to have L computed here. */
			}
		}

		/* Shadow " << GLSL::Discard << " code (all lights). */
		if ( usingShadowMap )
		{
			gen.addComment("Shadow computation");

			Code{gen} <<
				"float " << ShadowFactor << " = 1.0;";

			switch ( type )
			{
				case LightType::Directional :
					//gen.declare(Declaration::Uniform{Declaration::VariableType::Sampler2DShadow, Uniforms::ShadowMap});

					gen.addInstruction(this->generate2DShadowMapCode(Uniforms::ShadowMap, LightGenerator::lightVariable(ShaderBlocks::Component::PositionLightSpace), DepthTextureFunction::TextureGather));
					break;

				case LightType::Point :
					//gen.declare(Declaration::Uniform{Declaration::VariableType::SamplerCube/*SamplerCubeShadow*/, Uniforms::ShadowMap}); /* FIXME: samplerCubeShadow bugs with GLSL texture(); */
					//gen.declare(Declaration::Uniform{Declaration::VariableType::FloatVector2, Uniforms::NearFar, "vec2(0.0, 1.0)"});

					gen.addInstruction(this->generate3DShadowMapCode(Uniforms::ShadowMap, LightGenerator::lightVariable(ShaderBlocks::Component::DirectionWorldSpace), Uniforms::NearFar));
					break;

				case LightType::Spot :
					//gen.declare(Declaration::Uniform{Declaration::VariableType::Sampler2DShadow, Uniforms::ShadowMap});

					gen.addInstruction(this->generate2DShadowMapCode(Uniforms::ShadowMap, LightGenerator::lightVariable(ShaderBlocks::Component::PositionLightSpace), DepthTextureFunction::TextureProj));
					break;
			}

			/* NOTE: Discard the fragment if the shadow is totally black.
			 * Think of we are in additive rendering. Ambient pass already did all the fragments. */
			Code{gen} <<
				"if ( " << ShadowFactor << " <= 0.0 ) {discard;}" << Line::Blank <<

				/* Applies shadow to output variables. */
				LightDiffuseColor << " *= " << ShadowFactor << ';' << Line::End <<
				( m_flags[UsingSpecularComponent] ? "" : "//" ) << LightSpecularColor << " *= " << ShadowFactor << ';';
		}

		/* Attenuation " << GLSL::Discard << " code (point and spot lights).
		 * FIXME: TODO, optimize when no radius appears. */
		if ( type == LightType::Point || type == LightType::Spot )
		{
			if ( m_flags[HighQualityEnabled] )
			{
				/* Compute attenuation per fragment. */
				const auto radius = LightGenerator::lightUniform(UniformBlocks::Component::Radius);

				Code{gen} <<
					"if ( " << radius << " > 0.0 ) " << Line::End <<
					'{' << Line::End <<
					"	const vec3 DR = abs(" << Distance << ") / " << radius << ";" << Line::End <<
					"	const float " << AttenuationFactor << " = max(0.0, 1.0 - dot(DR, DR));" << Line::Blank <<

					"	if ( " << AttenuationFactor << " <= 0.0 ) {discard;}" << Line::Blank <<

					"	" << LightDiffuseColor << " *= " << AttenuationFactor << ';' << Line::End <<
					( m_flags[UsingSpecularComponent] ? "	" : "	//" ) << LightSpecularColor << " *= " << AttenuationFactor << ';' << Line::End <<
					'}';
			}
			else
			{
				/* Compute attenuation per vertex. */
				const auto attenuationFactor = LightGenerator::lightVariable(ShaderBlocks::Component::AttenuationFactor);

				Code{gen} <<
					"if ( " << attenuationFactor << " <= 0.0 ) {discard;}" << Line::Blank <<

					/* Applies radius attenuation to output variables. */
					LightDiffuseColor << " *= " << attenuationFactor << ';' << Line::End <<
					( m_flags[UsingSpecularComponent] ? "	" : "	//" ) << LightSpecularColor << " *= " << attenuationFactor << ';';
			}
		}

		/* Cone " << GLSL::Discard << " code (spot lights). */
		if ( type == LightType::Spot )
		{
			std::string spotFactor{};

			if ( m_flags[HighQualityEnabled] )
			{
				/* Compute cone per fragment. */
				const auto innerCosAngle = LightGenerator::lightUniform(UniformBlocks::Component::InnerCosAngle);
				const auto outerCosAngle = LightGenerator::lightUniform(UniformBlocks::Component::OuterCosAngle);
				const auto directionViewSpace = LightGenerator::lightUniform(UniformBlocks::Component::DirectionViewSpace);

				if ( m_flags[UsingNormalMap] )
				{
					Code{gen} <<
						"const float theta = dot(LViewSpace, " << directionViewSpace << ".xyz);";
				}
				else
				{
					Code{gen} <<
						"const float theta = dot(L, " << directionViewSpace << ".xyz);";
				}

				Code{gen} <<
					"const float epsilon = " << innerCosAngle << " - " << outerCosAngle << ';' << Line::End <<
					"const float " << SpotFactor << " = clamp((theta - " << outerCosAngle << ") / epsilon, 0.0, 1.0);";

				spotFactor.assign(SpotFactor);
			}
			else
			{
				/* Compute cone per vertex. */
				spotFactor = LightGenerator::lightVariable(ShaderBlocks::Component::SpotFactor);
			}

			Code{gen} <<
				"if ( " << spotFactor << " <= 0.0 ) {discard;}" << Line::Blank <<

				/* Applies spot factor to output variables. */
				LightDiffuseColor << " *= " << spotFactor << ';' << Line::End <<
				( m_flags[UsingSpecularComponent] ? "	" : "	//" ) << LightSpecularColor << " *= " << spotFactor << ';';
		}

		/* Diffuse component (all lights). */
		{
			if ( m_flags[UsingNormalMap] )
			{
				if ( m_flags[DiscardBackFaceWithNormalMap] )
				{
					gen.declare(Declaration::StageInput{ShaderVariables::NormalViewSpace, GLSL::Smooth});

					Code{gen} <<
						"if ( dot(-LViewSpace, " << ShaderVariables::NormalViewSpace << ") < -0.5 ) {discard;}";
				}

				/* NOTE: Get a sample from a texture in range [0,1], convert it to a normalized range of [-1, 1]. */
				Code{gen} <<
					"const vec3 N = normalize(texture(" << m_normalMap << ", " << m_normalMapTextureCoordinates << ").rgb * 2.0 - 1.0);" << Line::Blank <<

					"float " << ShaderVariables::DiffuseFactor << " = dot(-L, N);";
			}
			else
			{
				if ( m_flags[HighQualityEnabled] )
				{
					/* Compute diffuse component per fragment. */
					gen.declare(Declaration::StageInput{ShaderVariables::NormalViewSpace, GLSL::Smooth});

					Code{gen} <<
						"float " << ShaderVariables::DiffuseFactor << " = dot(-L, " << ShaderVariables::NormalViewSpace << ");";
				}
				else
				{
					/* Compute diffuse component per vertex. */
					gen.declare(Declaration::StageInput{ShaderVariables::DiffuseFactor, GLSL::Smooth});
				}
			}

			Code{gen} <<
				"if ( " << ShaderVariables::DiffuseFactor << " <= 0.0 ) {discard;}" << Line::Blank <<

				/* Applies diffuse factor to diffuse output. */
				LightDiffuseColor << " *= " << ShaderVariables::DiffuseFactor << ';';
		}

		/* Optional specular component (all lights). */
		if ( m_flags[UsingSpecularComponent] )
		{
			if ( m_flags[UsingNormalMap] )
			{
				//gen.declare(Declaration::Uniform{Declaration::VariableType::Float, m_shininessVariable.c_str(), "1.0"});

				if ( m_flags[HighQualityEnabled] )
				{
					gen.declare(Declaration::StageInput{ShaderVariables::ViewTBNMatrix, GLSL::Smooth});
					gen.declare(Declaration::StageInput{ShaderVariables::PositionViewSpace, GLSL::Smooth});

					Code{gen} <<
						"const vec3 invV = normalize(" << ShaderVariables::ViewTBNMatrix << " * " << ShaderVariables::PositionViewSpace << ".xyz);";
				}
				else
				{
					if ( type == LightType::Directional )
					{
						Code{gen} <<
							"const vec3 invV = " << LightGenerator::lightVariable(ShaderBlocks::Component::ViewDirectionTextureSpace) << ';';
					}
					else
					{
						gen.declare(Declaration::StageInput{ShaderVariables::PositionTextureSpace, GLSL::Smooth});

						Code{gen} <<
							"const vec3 invV = " << ShaderVariables::PositionTextureSpace << ';';
					}
				}

				/* NOTE: Here N comes from diffuse computation. */
				Code{gen} <<
					"const vec3 R = reflect(-L, N);" << Line::End <<
					"const float " << ShaderVariables::SpecularFactor << " = pow(max(0.0, dot(invV, R)), " << m_shininessVariable << ");";
			}
			else
			{
				if ( m_flags[HighQualityEnabled] )
				{
					/* Compute specular component per fragment. */
					//gen.declare(Declaration::Uniform{Declaration::VariableType::Float, m_shininessVariable.c_str(), "1.0"});
					gen.declare(Declaration::StageInput{ShaderVariables::PositionViewSpace, GLSL::Smooth});
					gen.declare(Declaration::StageInput{ShaderVariables::NormalViewSpace, GLSL::Smooth});

					Code{gen} <<
						"const vec3 R = reflect(-L, " << ShaderVariables::NormalViewSpace << ");" << Line::End <<
						"const vec3 invV = normalize(" << ShaderVariables::PositionViewSpace << ".xyz);" << Line::End <<
						"const float " << ShaderVariables::SpecularFactor << " = pow(max(0.0, dot(invV, R)), " << m_shininessVariable << ");";
				}
				else
				{
					/* Compute specular component per vertex. */
					gen.declare(Declaration::StageInput{ShaderVariables::SpecularFactor, GLSL::Smooth});
				}
			}

			/* Applies specular factor to specular output. */
			Code{gen} <<
				LightSpecularColor << " *= " << ShaderVariables::SpecularFactor << ';';
		}
	}

	std::string
	LightGenerator::generate2DShadowMapCode (const std::string & shadowMap, const std::string & fragmentPosition, DepthTextureFunction function) const noexcept
	{
		std::stringstream code{};

		code << "/* Shadow map 2D resolution. */" "\n\n";

		if ( m_PCFSample > 0 )
		{
			code << GLSL::ConstInteger << " offset = " << m_PCFSample << ";" "\n\n";

			switch ( function )
			{
				/* NOTE: OpenGL 3.2 (GLSL 150) - float textureOffset(sampler2DShadow sampler, vec4 P, ivec2 offset, [float bias]); */
				case DepthTextureFunction::Texture :
					code <<
						"for ( " << GLSL::Integer << " idy = -offset; idy <= offset; idy++ )" "\n"
						"	for ( " << GLSL::Integer << " idx = -offset; idx <= offset; idx++ )" "\n"
						"		" << ShadowFactor << " += textureOffset(" << shadowMap << ", " << fragmentPosition << ".xyz, ivec2(idx, idy));" "\n\n";
					break;

				/* NOTE: OpenGL 4.0 (GLSL 400) - float textureProjOffset(sampler2DShadow sampler, vec4 P, ivec2 offset, [float bias]); */
				case DepthTextureFunction::TextureProj :
					code <<
						"for ( " << GLSL::Integer << " idy = -offset; idy <= offset; idy++ )" "\n"
						"	for ( " << GLSL::Integer << " idx = -offset; idx <= offset; idx++ )" "\n"
						"		" << ShadowFactor << " += textureProjOffset(" << shadowMap << ", " << fragmentPosition << ", ivec2(idx, idy));" "\n\n";
					break;

				/* NOTE: OpenGL 4.6 (GLSL 460) - vec4 textureGatherOffset(gsampler2DShadow sampler, vec2 P, float refZ, ivec2 offset); */
				case DepthTextureFunction::TextureGather :
					code <<
						"for ( " << GLSL::Integer << " idy = -offset; idy <= offset; idy++ )" "\n"
						"{" "\n"
						"	for ( " << GLSL::Integer << " idx = -offset; idx <= offset; idx++ )" "\n"
						"	{" "\n"
						"		const vec4 gather = textureGatherOffset(" << shadowMap << ", " << fragmentPosition << ".xy, " << fragmentPosition << ".z, ivec2(idx, idy));" "\n"
						"		const vec2 shadowSize = textureSize(" << shadowMap << ", 0);" "\n"
						"		const vec2 texelCoord = " << fragmentPosition << ".xy * shadowSize;" "\n"
						"		const vec2 sampleCoord = fract(texelCoord + 0.5);" "\n\n"

						"		const float texelY0 = mix(gather.w, gather.x, sampleCoord.y);" "\n"
						"		const float texelY1 = mix(gather.z, gather.y, sampleCoord.y);" "\n"
						"		" << ShadowFactor << " += mix(texelY0, texelY1, sampleCoord.x);" "\n"
						"	}" "\n"
						"}" "\n\n";
					break;
			}

			code << ShadowFactor << " /= pow(float(offset) * 2.0 + 1.0, 2);" "\n";
		}
		else
		{
			switch ( function )
			{
				/* NOTE: OpenGL 3.2 (GLSL 150) - float texture(sampler2DShadow sampler, vec3 P, [float bias]); */
				case DepthTextureFunction::Texture :
					code << ShadowFactor << " = texture(" << shadowMap << ", " << fragmentPosition << ".xyz);" "\n\n";
					break;

				/* NOTE: OpenGL 4.0 (GLSL 400) - float textureProj(sampler2DShadow sampler, vec4 P, [float bias]); */
				case DepthTextureFunction::TextureProj :
					code << ShadowFactor << " = textureProj(" << shadowMap << ", " << fragmentPosition << ");" "\n\n";
					break;

				/* NOTE: OpenGL 4.6 (GLSL 460) - vec4 textureGather(gsampler2DShadow sampler, vec2 P, float refZ); */
				case DepthTextureFunction::TextureGather :
					code <<
						"const vec4 gather = textureGather(" << shadowMap << ", " << fragmentPosition << ".xy, " << fragmentPosition << ".z);" "\n"
						"const vec2 shadowSize = textureSize(" << shadowMap << ", 0);" "\n"
						"const vec2 texelCoord = " << fragmentPosition << ".xy * shadowSize;" "\n"
						"const vec2 sampleCoord = fract(texelCoord + 0.5);" "\n\n"

						"const float texelY0 = mix(gather.w, gather.x, sampleCoord.y);" "\n"
						"const float texelY1 = mix(gather.z, gather.y, sampleCoord.y);" "\n" <<
						ShadowFactor << " = mix(texelY0, texelY1, sampleCoord.x);" "\n\n";
					break;
			}
		}

		return code.str();
	}

	std::string
	LightGenerator::generate3DShadowMapCode (const std::string & shadowMap, const std::string & directionWorldSpace, const std::string & nearFar) const noexcept
	{
		std::stringstream code{};

		code << "/* Shadow map 3D resolution. */" "\n\n";

		if ( m_PCFSample > 0 )
		{
			code <<
				"const vec3 lookupVector = vec3(-" << directionWorldSpace << ".x, " << directionWorldSpace << ".y, " << directionWorldSpace << ".z);" "\n"
				"const float depth = length(lookupVector);" "\n\n"

				"const vec3 sampleOffsetDirections[20] = vec3[] (" "\n"
				"	vec3( 1,  1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1,  1,  1)," "\n"
				"	vec3( 1,  1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1,  1, -1)," "\n"
				"	vec3( 1,  1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1,  1,  0)," "\n"
				"	vec3( 1,  0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1,  0, -1)," "\n"
				"	vec3( 0,  1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0,  1, -1)" "\n"
				");" "\n"

				"const float diskRadius = " << m_PCFRadius << ";" "\n\n"

				"for ( " << GLSL::Integer << " index = 0; index < 20; ++index )" "\n"
				"{" "\n"
				"	const float smallestDepth = texture(" << shadowMap << ", lookupVector + sampleOffsetDirections[index] * diskRadius).r * " << nearFar << ".y;" "\n\n"

				"	if ( smallestDepth - 0.01 > depth )" "\n"
				"	{" "\n"
				"		" << ShadowFactor << " += 1.0;" "\n"
				"	}" "\n"
				"}" "\n\n" <<

				ShadowFactor << " /= 20.0;" "\n\n";
		}
		else
		{
			code <<
				"const vec3 lookupVector = vec3(-" << directionWorldSpace << ".x, " << directionWorldSpace << ".y, " << directionWorldSpace << ".z);" "\n"
				"const float smallestDepth = texture(" << shadowMap << ", lookupVector).r * " << nearFar << ".y;" "\n"
				"const float depth = length(lookupVector);" "\n\n"

				"if ( smallestDepth + 0.01 < depth )" "\n"
				"{" "\n"
				"	" << ShadowFactor << " = 0.0;" "\n"
				"}" "\n\n";
		}

		return code.str();
	}
}
