/*
 * Emeraude/Scenes/SaturationLensEffect.cpp
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

#include "SaturationLensEffect.hpp"

/* Local inclusions */
#include "Saphir/ShaderGenerator.hpp"
#include "Graphics/PostProcessor.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Saphir;
	using namespace Saphir::Keys;
	using namespace Graphics;

	SaturationLensEffect::SaturationLensEffect (float saturation) noexcept
		: m_saturation(saturation)
	{

	}

	bool
	SaturationLensEffect::generate (ShaderGenerator & gen, int /*samples*/) const noexcept
	{
		if ( gen.shaderType() == ShaderType::FragmentShader )
		{
			//gen.declare(Declaration::Uniform{Declaration::VariableType::Float, Saturation, "1.0"});

			gen.addComment("Saturation control.");

			Code{gen} <<
				/* NOTE: Algorithm from Chapter 16 of OpenGL Shading Language. */
				"float intensity = dot(" << PostProcessor::Fragment << ".rgb, vec3(0.2125, 0.7154, 0.0721));" << Line::Blank <<

				PostProcessor::Fragment << " = vec4(mix(vec3(intensity), " << PostProcessor::Fragment << ".rgb, " << Saturation << "), " << PostProcessor::Fragment << ".a);";
		}

		return true;
	}

	/*void
	SaturationLensEffect::activate (const Program & program, unsigned int &) const noexcept
	{
		program.sendUniform(Saturation, m_saturation);
	}*/

	void
	SaturationLensEffect::setSaturation (float value) noexcept
	{
		m_saturation = value;
	}

	float
	SaturationLensEffect::saturation () const noexcept
	{
		return m_saturation;
	}
}
