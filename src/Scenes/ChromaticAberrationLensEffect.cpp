/*
 * Emeraude/Scenes/ChromaticAberrationLensEffect.cpp
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

#include "ChromaticAberrationLensEffect.hpp"

/* Local inclusions */
#include "Tracer.hpp"
#include "Saphir/ShaderGenerator.hpp"
#include "Graphics/PostProcessor.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Saphir;
	using namespace Saphir::Keys;
	using namespace Graphics;

	ChromaticAberrationLensEffect::ChromaticAberrationLensEffect (float xScale, float yScale) noexcept
	{
		m_redOffset[X] = Utility::random(-xScale, xScale);
		m_redOffset[Y] = Utility::random(-yScale, yScale);

		m_greenOffset[X] = Utility::random(-xScale, xScale);
		m_greenOffset[Y] = Utility::random(-yScale, yScale);

		m_blueOffset[X] = Utility::random(-xScale, xScale);
		m_blueOffset[Y] = Utility::random(-yScale, yScale);
	}

	bool
	ChromaticAberrationLensEffect::generate (ShaderGenerator & gen, int samples) const noexcept
	{
		if ( gen.shaderType() == ShaderType::FragmentShader )
		{
			m_samples = samples;

			gen.addComment("Basic chromatic aberration effect.");

			Code{gen} << "float r, g, b;";

			if ( samples > 0 )
			{
				//gen.declare(Declaration::Uniform{Declaration::VariableType::Sampler2DMS, Uniforms::PrimaryTexture});
				//gen.declare(Declaration::Uniform{Declaration::VariableType::SIntVector2, RedOffset, "ivec2(0, 0)"});
				//gen.declare(Declaration::Uniform{Declaration::VariableType::SIntVector2, GreenOffset, "ivec2(0, 0)"});
				//gen.declare(Declaration::Uniform{Declaration::VariableType::SIntVector2, BlueOffset, "ivec2(0, 0)"});

				Code{gen} <<
					"ivec2 texCoords = ivec2(gl_FragCoord.xy);" << Line::Blank <<

					"for ( int subSample = 0; subSample < " << samples << "; subSample++ )" << Line::End <<
					"{" << Line::End <<
					"	r += texelFetch(" << Uniforms::PrimaryTexture << ", texCoords + " << RedOffset << ", subSample).r;" << Line::End <<
					"	g += texelFetch(" << Uniforms::PrimaryTexture << ", texCoords + " << GreenOffset << ", subSample).g;" << Line::End <<
					"	b += texelFetch(" << Uniforms::PrimaryTexture << ", texCoords + " << BlueOffset << ", subSample).b;" << Line::End <<
					"}" << Line::Blank <<

					"r = clamp(r / " << samples << ", 0.0, 1.0);" << Line::End <<
					"g = clamp(g / " << samples << ", 0.0, 1.0);" << Line::End <<
					"b = clamp(b / " << samples << ", 0.0, 1.0);" << Line::End;
			}
			else
			{
				//gen.declare(Declaration::Uniform{Declaration::VariableType::Sampler2D, Uniforms::PrimaryTexture});
				//gen.declare(Declaration::Uniform{Declaration::VariableType::FloatVector2, RedOffset, "vec2(0.0, 0.0)"});
				//gen.declare(Declaration::Uniform{Declaration::VariableType::FloatVector2, GreenOffset, "vec2(0.0, 0.0)"});
				//gen.declare(Declaration::Uniform{Declaration::VariableType::FloatVector2, BlueOffset, "vec2(0.0, 0.0)"});

				gen.declare(Declaration::StageInput{ShaderVariables::Primary2DTextureCoordinates, GLSL::Smooth});

				Code{gen} <<
					"r = texture(" << Uniforms::PrimaryTexture << ", " << ShaderVariables::Primary2DTextureCoordinates << " + " << RedOffset << ").r;" << Line::End <<
					"g = texture(" << Uniforms::PrimaryTexture << ", " << ShaderVariables::Primary2DTextureCoordinates << " + " << GreenOffset << ").g;" << Line::End <<
					"b = texture(" << Uniforms::PrimaryTexture << ", " << ShaderVariables::Primary2DTextureCoordinates << " + " << BlueOffset << ").b;" << Line::End;
			}

			// FIXME : Set a parametric output fragment coming from the generator.
			Code{gen} <<
				"vec4 " << PostProcessor::Fragment << " = vec4(r, g, b, 1.0);";
		}

		return true;
	}

	/*void
	ChromaticAberrationLensEffect::activate (const Program & program, unsigned int &) const noexcept
	{
		if ( m_samples )
		{
			program.sendUniform(RedOffset, Vector< int, 2 >(0, 0));
			program.sendUniform(GreenOffset, Vector< int, 2 >(1, 1));
			program.sendUniform(BlueOffset, Vector< int, 2 >(-1, -1));
		}
		else
		{
			program.sendUniform(RedOffset, m_redOffset);
			program.sendUniform(GreenOffset, m_greenOffset);
			program.sendUniform(BlueOffset, m_blueOffset);
		}
	}*/

	bool
	ChromaticAberrationLensEffect::overrideFragmentFetching () const noexcept
	{
		return true;
	}
}
