/*
 * Emeraude/Scenes/GrayscaleLensEffect.cpp
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

#include "GrayscaleLensEffect.hpp"

/* Local inclusions */
#include "Graphics/PostProcessor.hpp"
#include "Saphir/ShaderGenerator.hpp"
#include "Tracer.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Saphir;
	using namespace Saphir::Keys;
	using namespace Graphics;

	bool
	GrayscaleLensEffect::generate (ShaderGenerator & gen, int /*samples*/) const noexcept
	{
		if ( gen.shaderType() == ShaderType::FragmentShader )
		{
			//gen.declare(Declaration::Uniform{Declaration::VariableType::FloatVector4, Teint, "vec4(1.0)"});

			gen.addComment("Gray scale effect.");

			switch ( m_mode )
			{
				case Mode::Average :
					Code{gen} <<
						"const float GrayScaleValue = clamp(((" << PostProcessor::Fragment << ".r + " << PostProcessor::Fragment << ".g + " << PostProcessor::Fragment << ".b) / 3), 0.0, 1.0);";
					break;

				case Mode::LumaRec601_1 :
					Code{gen} <<
						"const float GrayScaleValue = clamp(0.2989 * " << PostProcessor::Fragment << ".r + 0.5866 * " << PostProcessor::Fragment << ".g + 0.1145 * " << PostProcessor::Fragment << ".b, 0.0, 1.0);";
					break;

				case Mode::LumaRec709 :
					Code{gen} <<
						"const float GrayScaleValue = clamp(0.2126 * " << PostProcessor::Fragment << ".r + 0.7152 * " << PostProcessor::Fragment << ".g + 0.0722 * " << PostProcessor::Fragment << ".b, 0.0, 1.0);";
					break;

				case Mode::LumaITU :
					Code{gen} <<
						"const float GrayScaleValue = clamp(0.2220 * " << PostProcessor::Fragment << ".r + 0.7067 * " << PostProcessor::Fragment << ".g + 0.0713 * " << PostProcessor::Fragment << ".b, 0.0, 1.0);";
					break;

				case Mode::Desaturation :
					Code{gen} <<
						"const float GrayScaleValue = ( min(min(" << PostProcessor::Fragment << ".r, " << PostProcessor::Fragment << ".g), " << PostProcessor::Fragment << ".b) + max(max(" << PostProcessor::Fragment << ".r, " << PostProcessor::Fragment << ".g), " << PostProcessor::Fragment << ".b) ) * 0.5;";
					break;

				case Mode::Decomposition :
					switch ( m_option )
					{
						case Option::Min :
							Code{gen} <<
								"const float GrayScaleValue = min(min(" << PostProcessor::Fragment << ".r, " << PostProcessor::Fragment << ".g), " << PostProcessor::Fragment << ".b);";
							break;

						case Option::Max :
							Code{gen} <<
								"const float GrayScaleValue = max(max(" << PostProcessor::Fragment << ".r, " << PostProcessor::Fragment << ".g), " << PostProcessor::Fragment << ".b);";
							break;

						case Option::None :
						case Option::RedChannel :
						case Option::GreenChannel :
						case Option::BlueChannel :
						case Option::AlphaChannel :
						default:
							Tracer::error(ClassId, "Bad option for Decomposition grayscale !");
							break;
					}
					break;

				case Mode::SingleChannel :
					switch ( m_option )
					{
						case Option::RedChannel :
							Code{gen} <<
								"const float GrayScaleValue = " << PostProcessor::Fragment << ".r;";
							break;

						case Option::GreenChannel :
							Code{gen} <<
								"const float GrayScaleValue = " << PostProcessor::Fragment << ".g;";
							break;

						case Option::BlueChannel :
							Code{gen} <<
								"const float GrayScaleValue = " << PostProcessor::Fragment << ".b;";
							break;

						case Option::AlphaChannel :
							Code{gen} <<
								"const float GrayScaleValue = " << PostProcessor::Fragment << ".a;";
							break;

						case Option::None :
						case Option::Min :
						case Option::Max :
						default:
							Tracer::error(ClassId, "Bad option for SingleChannel grayscale !");
							break;
					}

					break;

				case Mode::ShadesScale :
					//gen.declare(Declaration::Uniform{Declaration::VariableType::Float, ScaleLevel, "16.0"});

					Code{gen} <<
						"const float GrayScaleFactor = 1.0 / " << ScaleLevel << ";" << Line::End <<
						"const float GrayScaleAverage = (" << PostProcessor::Fragment << ".r + " << PostProcessor::Fragment << ".g + " << PostProcessor::Fragment << ".b) / 3.0;" << Line::End <<
						"const float GrayScaleValue = clamp(round((GrayScaleAverage / GrayScaleFactor) + 0.5) * GrayScaleFactor, 0.0, 1.0);";
					break;

				case Mode::EightBits :
					Code{gen} <<
						"const float GrayScaleFactor = 1.0 / 4;" << Line::End <<
						"const float R = clamp(round((" << PostProcessor::Fragment << ".r / GrayScaleFactor) + 0.5) * GrayScaleFactor, 0.0, 1.0);" << Line::End <<
						"const float G = clamp(round((" << PostProcessor::Fragment << ".g / GrayScaleFactor) + 0.5) * GrayScaleFactor, 0.0, 1.0);" << Line::End <<
						"const float B = clamp(round((" << PostProcessor::Fragment << ".b / GrayScaleFactor) + 0.5) * GrayScaleFactor, 0.0, 1.0);";

					Code{gen} <<
						PostProcessor::Fragment << " = vec4(R, G, B, " << PostProcessor::Fragment << ".a);";
					/* NOTE: This case, use its own output. */
					return true;

			}

			/* Fragment recomposition with grayscale value. This is common to each case. */
			Code{gen} <<
				PostProcessor::Fragment << " = vec4((" << Teint << " * GrayScaleValue).rgb, " << PostProcessor::Fragment << ".a);";
		}

		return true;
	}

	GrayscaleLensEffect::GrayscaleLensEffect (Mode mode, Option option) noexcept
		: m_teint(PixelFactory::White), m_mode(mode), m_option(option)
	{

	}

	/*void
	GrayscaleLensEffect::activate (const Program & program, unsigned int &) const noexcept
	{
		program.sendUniform(Teint, m_teint);

		if ( m_mode == Mode::ShadesScale )
		{
			program.sendUniform(ScaleLevel, static_cast< float >(m_scaleLevel));
		}
	}*/

	void
	GrayscaleLensEffect::setMode (Mode mode) noexcept
	{
		m_mode = mode;
	}

	void
	GrayscaleLensEffect::setOption (Option option) noexcept
	{
		m_option = option;
	}

	GrayscaleLensEffect::Mode
	GrayscaleLensEffect::mode () const noexcept
	{
		return m_mode;
	}

	GrayscaleLensEffect::Option
	GrayscaleLensEffect::option () const noexcept
	{
		return m_option;
	}

	void
	GrayscaleLensEffect::setScaleLevel (unsigned int level) noexcept
	{
		if ( m_mode != Mode::ShadesScale )
		{
			Tracer::warning(ClassId, "Setting scale level is only usable with ShadesScale mode !");

			return;
		}

		m_scaleLevel = level;
	}

	unsigned int
	GrayscaleLensEffect::scaleLevel () const noexcept
	{
		return m_scaleLevel;
	}

	void
	GrayscaleLensEffect::setTeint (const PixelFactory::Color< float > & teint) noexcept
	{
		m_teint = teint;
	}

	const PixelFactory::Color< float > &
	GrayscaleLensEffect::teint () const noexcept
	{
		return m_teint;
	}
}
