/*
 * Emeraude/Scenes/FogEnvironmentEffect.cpp
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

#include "FogEnvironmentEffect.hpp"

/* Local inclusions */
#include "Tracer.hpp"
#include "Saphir/ShaderGenerator.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Saphir;
	using namespace Saphir::Keys;

	bool
	FogEnvironmentEffect::generate (ShaderGenerator & gen) const noexcept
	{
		switch ( gen.shaderType() )
		{
			case ShaderType::VertexShader :
				/* Fog per vertex */
				if ( !m_highQuality )
				{
					gen.declare(Declaration::StageOutput{24, GLSL::Float, FogVertexDistance});

					gen.addComment("Fog effect.");

					Code{gen} <<
						FogVertexDistance << " = length(" << Attributes::Position << ");";
				}
				break;

			case ShaderType::FragmentShader :
			{
				constexpr auto FogFactor = "fogFactor";

				/* Adds color vector */
				if ( !m_useBackgroundColor )
				{
					const auto defaultValue = (std::stringstream{} << "vec4(" << m_color.red() << ", " << m_color.green() << ", " << m_color.blue() << ", " << m_color.alpha() << ")").str();

					//gen.declare(Declaration::Uniform{Declaration::VariableType::FloatVector4, FogColor, defaultValue.c_str()});
				}

				Declaration::Function function("get_fog_factor", GLSL::Float);
				function.addInParameter(GLSL::Float, "z", true);

				/* Adds fog function to program */
				switch ( m_mode )
				{
					/* Formula : fogFactor = (end - z) / (end - execute) */
					case FogMode::Linear :
						//gen.declare(Declaration::Uniform{Declaration::VariableType::Float, FogStart, "0.0"});
						//gen.declare(Declaration::Uniform{Declaration::VariableType::Float, FogEnd, "1.0"});

						Code{function} <<
							"return clamp((" << FogEnd << " - z) / (" << FogEnd << " - " << FogStart << "), 0.0, 1.0);";
						break;

					/* Formula : fogFactor = e [exp] -(density * z) */
					case FogMode::Exponential :
						//gen.declare(Declaration::Uniform{Declaration::VariableType::Float, FogDensity, "1.0"});

						Code{function} <<
							"return clamp(exp(-(z * " << FogDensity << ")), 0.0, 1.0);";
						break;

					/* Formula : fogFactor = e [exp] -(density * z)² */
					case FogMode::Exponential2 :
						//gen.declare(Declaration::Uniform{Declaration::VariableType::Float, FogDensity, "1.0"});

						Code{function} <<
							"float factor = z * " << FogDensity << ";" << Line::End <<
							"return clamp(exp(-(factor * factor)), 0.0, 1.0);";
						break;

					case FogMode::Exponential2Alt :
						//gen.declare(Declaration::Uniform{Declaration::VariableType::Float, FogDensity, "1.0"});

						Code{function} <<
									   "return clamp(exp2(-fogFactor * fogFactor * z * z * 1.442695), 0.0, 1.0);";
						break;
				}

				gen.declare(function);

				gen.addComment("Fog effect.");

				/* Fog per pixel */
				if ( m_highQuality )
				{
					Code{gen} <<
						"float fogFactor = " << function.callCode("gl_FragCoord.z / gl_FragCoord.w") << ';';
				}
				/* Fog per vertex */
				else
				{
					gen.declare(Declaration::StageInput{24, GLSL::Float, FogVertexDistance});

					Code{gen} <<
						"float fogFactor = " << function.callCode(FogVertexDistance) << ';';
				}

				/* Final process */
				if ( m_useBackgroundColor )
				{
					Code{gen} <<
						 ShaderVariables::OutputFragment << " = vec4(" << ShaderVariables::OutputFragment << ".rgb, mix(0.0, 1.0, fogFactor));";
				}
				else
				{
					Code{gen} <<
						 ShaderVariables::OutputFragment << " = mix(" << FogColor << ", " << ShaderVariables::OutputFragment << ", fogFactor);";
				}
			}
				break;

			case ShaderType::TesselationControlShader :
			case ShaderType::TesselationEvaluationShader :
			case ShaderType::GeometryShader :
			case ShaderType::ComputeShader :
				/* Do nothing ... */
				break;
		}

		return true;
	}

	FogEnvironmentEffect::FogEnvironmentEffect (FogMode mode, bool highQuality) noexcept
		: m_mode(mode), m_highQuality(highQuality)
	{

	}

	void
	FogEnvironmentEffect::setDensity (float density) noexcept
	{
		if ( density < 0.0F )
		{
			Tracer::warning(ClassId, "Fog intensity must be positive !");

			return;
		}

		if ( m_mode == FogMode::Linear )
		{
			Tracer::warning(ClassId, "Changing density doesn't affect linear fog.");
		}

		m_density = density;
	}

	void
	FogEnvironmentEffect::setLinearRange (float start, float end) noexcept
	{
		if ( m_mode != FogMode::Linear )
		{
			Tracer::warning(ClassId, "Changing range doesn't affect exponential fog.");
		}

		m_Start = std::min(start, end);
		m_End = std::max(start, end);
	}

	void
	FogEnvironmentEffect::setColor (const PixelFactory::Color< float > & color) noexcept
	{
		m_color = color;
		m_useBackgroundColor = false;
	}

	void
	FogEnvironmentEffect::useBackgroundColor () noexcept
	{
		m_useBackgroundColor = true;
	}

	FogEnvironmentEffect::FogMode
	FogEnvironmentEffect::mode () const noexcept
	{
		return m_mode;
	}

	float
	FogEnvironmentEffect::density () const noexcept
	{
		return m_density;
	}

	float
	FogEnvironmentEffect::linearStart () const noexcept
	{
		return m_Start;
	}

	float
	FogEnvironmentEffect::endStart () const noexcept
	{
		return m_End;
	}

	const PixelFactory::Color< float > &
	FogEnvironmentEffect::color () const noexcept
	{
		return m_color;
	}

	/*void
	FogEnvironmentEffect::activate (const Program & program, unsigned int &) const noexcept
	{
		switch ( m_mode )
		{
			case FogMode::Linear :
				program.sendUniform(FogStart, m_Start);
				program.sendUniform(FogEnd, m_End);
				break;

			case FogMode::Exponential :
			case FogMode::Exponential2 :
			case FogMode::Exponential2Alt :
				program.sendUniform(FogDensity, m_density);
				break;
		}

		if ( m_useBackgroundColor )
		{
			Core::instance()->graphicsRenderer().setBlendingMode(Graphics::BlendingMode::Normal);
		}
		else
		{
			program.sendUniform(FogColor, m_color);
		}
	}*/
}
