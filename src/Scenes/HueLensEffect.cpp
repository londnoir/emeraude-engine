/*
 * Emeraude/Scenes/HueLensEffect.cpp
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

#include "HueLensEffect.hpp"

/* Local inclusions */
#include "Saphir/ShaderGenerator.hpp"
#include "Graphics/PostProcessor.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Saphir;
	using namespace Saphir::Keys;
	using namespace Graphics;

	HueLensEffect::HueLensEffect (float hue) noexcept
		: m_hue(hue)
	{

	}

	bool
	HueLensEffect::generate (ShaderGenerator & gen, int /*samples*/) const noexcept
	{
		if ( gen.shaderType() == ShaderType::FragmentShader )
		{
			//gen.declare(Declaration::Uniform{Declaration::VariableType::Float, Hue, "0.0"});

			gen.addComment("Hue control.");

			// FIXME : Set a parametric output fragment coming from the generator.
			Code{gen} <<
				"const mat3 toYIQ = mat3(0.299, 0.587, 0.114, 0.595716, -0.274453, -0.321263, 0.211456, -0.522591, 0.311135);" << Line::End <<
				"const mat3 toRGB = mat3(1.0, 0.9563, 0.6210, 1.0, -0.2721, -0.6474, 1.0, -1.107, 1.7046);" << Line::Blank <<

				"const vec3 yiq = toYIQ * " << PostProcessor::Fragment << ".rgb;" << Line::End <<
				"const float hue = atan(yiq.z, yiq.y) + " << Hue << ";" << Line::End <<
				"const float chroma = sqrt(yiq.z * yiq.z + yiq.y * yiq.y);" << Line::Blank <<

				"const vec3 color = vec3(yiq.x, chroma * cos(hue), chroma * sin(hue));" << Line::Blank <<

				PostProcessor::Fragment << " = vec4(toRGB * color, " << PostProcessor::Fragment << ".a);";
		}

		return true;
	}

	/*void
	HueLensEffect::activate (const Program & program, unsigned int &) const noexcept
	{
		program.sendUniform(Hue, m_hue);
	}*/

	void
	HueLensEffect::setHue (float value) noexcept
	{
		//auto clamp = std::floor(value);

		m_hue = value;// - clamp;
	}

	float
	HueLensEffect::hue () const noexcept
	{
		return m_hue;
	}
}
