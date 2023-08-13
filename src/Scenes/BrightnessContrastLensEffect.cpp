/*
 * Emeraude/Scenes/BrightnessContrastLensEffect.cpp
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

#include "BrightnessContrastLensEffect.hpp"

/* C/C++ standard libraries. */
#include <cmath>

/* Local inclusions */
#include "Saphir/ShaderGenerator.hpp"
#include "Graphics/PostProcessor.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Saphir;
	using namespace Saphir::Keys;
	using namespace Graphics;

	BrightnessContrastLensEffect::BrightnessContrastLensEffect (float brightness, float contrast) noexcept
		: m_brightness(brightness), m_contrast(std::abs(contrast))
	{

	}

	bool
	BrightnessContrastLensEffect::generate (ShaderGenerator & gen, int /*samples*/) const noexcept
	{
		if ( gen.shaderType() == ShaderType::FragmentShader )
		{
			//gen.declare(Declaration::Uniform{Declaration::VariableType::Float, Brightness, "0.0"});
			//gen.declare(Declaration::Uniform{Declaration::VariableType::Float, Contrast, "1.0"});

			gen.addComment("Brightness/Contrast control.");

			// FIXME : Set a parametric output fragment coming from the generator.
			Code{gen} <<
				"const vec3 bcCorrection = ((" << PostProcessor::Fragment << ".rgb - 0.5) * max(" << Contrast << ", 0.0)) + 0.5;" << Line::Blank <<

				"bcCorrection += " << Brightness << ";" << Line::Blank <<

				PostProcessor::Fragment << " = vec4(clamp(bcCorrection, 0.0, 1.0), " << PostProcessor::Fragment << ".a);";
		}

		return true;
	}

	/*void
	BrightnessContrastLensEffect::activate (const Program & program, unsigned int &) const noexcept
	{
		program.sendUniform(Brightness, m_brightness);
		program.sendUniform(Contrast, m_contrast);
	}*/

	void
	BrightnessContrastLensEffect::setBrightness (float value) noexcept
	{
		m_brightness = value;
	}

	float
	BrightnessContrastLensEffect::brightness () const noexcept
	{
		return m_brightness;
	}

	void
	BrightnessContrastLensEffect::setContrast (float value) noexcept
	{
		m_contrast = std::abs(value);
	}

	float
	BrightnessContrastLensEffect::contrast () const noexcept
	{
		return m_contrast;
	}
}
