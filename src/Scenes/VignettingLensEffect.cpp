/*
 * Emeraude/Scenes/VignettingLensEffect.cpp
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

#include "VignettingLensEffect.hpp"

/* C/C++ standard libraries. */
#include <cmath>

/* Local inclusions */
#include "Saphir/ShaderGenerator.hpp"
#include "Graphics/PostProcessor.hpp"
#include "Graphics/ImageResource.hpp"
#include "Vulkan/Image.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Saphir;
	using namespace Saphir::Keys;
	using namespace Graphics;

	VignettingLensEffect::VignettingLensEffect (float strength) noexcept
		: m_image(ImageResource::get("Miscellaneous/_vignetting", true))/*, m_texture(Image::Usage::Texture, true)*/, m_strength(strength)
	{
		//if ( !m_texture.initialize(m_image->data()) )
		//	Tracer::error(ClassId, "Unable to get Vignetting texture !");
	}

	bool
	VignettingLensEffect::generate (ShaderGenerator & gen, int /*samples*/) const noexcept
	{
		switch ( gen.shaderType() )
		{
			case ShaderType::VertexShader :

				break;

			case ShaderType::FragmentShader :
				//gen.declare(Declaration::Uniform{Declaration::VariableType::Sampler2D, VignettingTexture});
				//gen.declare(Declaration::Uniform{Declaration::VariableType::Float, Strength, "1.0"});

				gen.declare(Declaration::StageInput{ShaderVariables::Primary2DTextureCoordinates, GLSL::Smooth});

				gen.addComment("Vignetting effect.");

				Code{gen} << "cont vec4 cColor = texture(" << VignettingTexture << ", " << ShaderVariables::Primary2DTextureCoordinates << ");";
				Code{gen} << "vColor.rgb = clamp(((vColor.rgb - 0.5) * max(" << Strength << ", 0.0)) + 0.5, 0.0, 1.0);";
				Code{gen} << PostProcessor::Fragment << " = vec4(" << PostProcessor::Fragment << ".rgb * vColor.rgb, 1.0);";
				break;

			case ShaderType::TesselationControlShader :
			case ShaderType::TesselationEvaluationShader :
			case ShaderType::GeometryShader :
			case ShaderType::ComputeShader :
				/* Do nothing for these... */
				break;
		}

		return true;
	}

	/*void
	VignettingLensEffect::activate (const Program & program, unsigned int & nextTextureUnit) const noexcept
	{
		program.bind(VignettingTexture, m_texture, nextTextureUnit++);
		program.sendUniform(Strength, m_strength);
	}*/

	bool
	VignettingLensEffect::requestScreenCoordinates () const noexcept
	{
		return true;
	}

	void
	VignettingLensEffect::setStrength (float value) noexcept
	{
		m_strength = std::abs(value);
	}

	float
	VignettingLensEffect::strength () const noexcept
	{
		return m_strength;
	}
}
