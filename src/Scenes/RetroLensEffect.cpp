/*
 * Emeraude/Scenes/RetroLensEffect.cpp
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

#include "RetroLensEffect.hpp"

/* Local inclusions */
#include "Saphir/ShaderGenerator.hpp"
#include "Graphics/PostProcessor.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Saphir;
	using namespace Saphir::Keys;
	using namespace Graphics;

	bool
	RetroLensEffect::generate (ShaderGenerator & gen, int /*samples*/) const noexcept
	{
		if ( gen.shaderType() == ShaderType::FragmentShader )
		{
			gen.addComment("Retro effect.");

			Code{gen} <<
				"const float scale = 1.0 / 4;" << Line::Blank <<

				"const float rComp = clamp(round((" << PostProcessor::Fragment << ".r / scale) + 0.5) * scale, 0.0, 1.0);" << Line::End <<
				"const float gComp = clamp(round((" << PostProcessor::Fragment << ".g / scale) + 0.5) * scale, 0.0, 1.0);" << Line::End <<
				"const float bComp = clamp(round((" << PostProcessor::Fragment << ".b / scale) + 0.5) * scale, 0.0, 1.0);" << Line::Blank <<

				PostProcessor::Fragment << " = vec4(rComp, gComp, bComp, " << PostProcessor::Fragment << ".a);";
		}

		return true;
	}
}
