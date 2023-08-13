/*
 * Emeraude/Scenes/FilmGrainLensEffect.cpp
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

#include "FilmGrainLensEffect.hpp"

/* Local inclusions */
#include "Tracer.hpp"
#include "Saphir/ShaderGenerator.hpp"
#include "Graphics/PostProcessor.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Saphir;
	using namespace Saphir::Keys;
	using namespace Graphics;

	bool
	FilmGrainLensEffect::generate (ShaderGenerator & gen, int /*samples*/) const noexcept
	{
		if ( gen.shaderType() == ShaderType::VertexShader )
		{
			//gen.declare(Declaration::Uniform{Declaration::VariableType::Float, RandomA, "0.0"});
			//gen.declare(Declaration::Uniform{Declaration::VariableType::Float, RandomB, "0.5"});
			//gen.declare(Declaration::Uniform{Declaration::VariableType::Float, RandomC, "1.0"});

			gen.addComment("Film grain effect.");

			// FIXME : Set a parametric output fragment coming from the generator.
			Code{gen} <<
				"if ( "
					"mod(gl_FragCoord.y, " << RandomA << ") < 0.02 || "
					"( "
						"mod(gl_FragCoord.x, " << RandomB << ") < 0.05 && "
						"mod(gl_FragCoord.y, " << RandomA << " * 2) < 0.05"
					" )"
				" )" << Line::End <<
				'\t' << PostProcessor::Fragment << " = mix(" << PostProcessor::Fragment << ", vec4(" << RandomA << ", " << RandomB << ", " << RandomC << ", 1.0), 0.5);";
		}

		return true;
	}

	/*void
	FilmGrainLensEffect::activate (const Graphics::Program & program, unsigned int &) const noexcept
	{
		program.sendUniform(RandomA, Libraries::Utility::random(0.0F, 1.0F));
		program.sendUniform(RandomB, Libraries::Utility::random(0.0F, 1.0F));
		program.sendUniform(RandomC, Libraries::Utility::random(0.0F, 1.0F));
	}*/

	bool
	FilmGrainLensEffect::requestScreenSize () const noexcept
	{
		return true;
	}
}
