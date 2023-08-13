/*
 * Emeraude/Scenes/GrayscaleLensEffect.hpp
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

#pragma once

/* Local inclusions for inheritance */
#include "Saphir/FramebufferEffectInterface.hpp"

/* Local inclusions for usages. */
#include "PixelFactory/Color.hpp"

namespace Emeraude::Scenes
{
	class GrayscaleLensEffect final : public Saphir::FramebufferEffectInterface
	{
		public:

			enum class Mode
			{
				/* Gray = (Red + Green + Blue) / 3 */
				Average,
				/* Gray = 0.2989 * Red + 0.5866 * Green + 0.1145 * Blue */
				LumaRec601_1,
				/* Gray = 0.2126 * Red + 0.7152 * Green + 0.0722 * Blue */
				LumaRec709,
				/* Gray = 0.2220 * Red + 0.7067 * Green + 0.0713 * Blue */
				LumaITU,
				/* Gray = ( max(Red, Green, Blue) + min(Red, Green, Blue) ) / 2 */
				Desaturation,
				/* Gray = min(Red, Green, Blue) OR Gray = max(Red, Green, Blue) */
				Decomposition,
				/* Gray = Red OR Gray = Green OR ... */
				SingleChannel,
				ShadesScale,
				EightBits
			};

			enum class Option
			{
				None,
				/* Options for mode SingleChannel */
				RedChannel,
				GreenChannel,
				BlueChannel,
				AlphaChannel,
				/* Options for mode decomposition */
				Min,
				Max
			};

			/** @brief Class identifier. */
			static constexpr auto ClassId{"GrayscaleLensEffect"};

			GrayscaleLensEffect (Mode mode = Mode::Average, Option option = Option::None) noexcept;

			//void activate (const Graphics::Program & program, unsigned int & nextTextureUnit) const noexcept override;

			void setMode (Mode mode) noexcept;

			[[nodiscard]]
			Mode mode () const noexcept;

			void setOption (Option option) noexcept;

			[[nodiscard]]
			Option option () const noexcept;

			void setScaleLevel (unsigned int level) noexcept;

			[[nodiscard]]
			unsigned int scaleLevel () const noexcept;

			/** Sets the teint used for the colored scale. */
			void setTeint (const Libraries::PixelFactory::Color< float > & teint) noexcept;

			[[nodiscard]]
			const Libraries::PixelFactory::Color< float > & teint () const noexcept;

		private:

			static constexpr auto Teint = "em_Teint";
			static constexpr auto ScaleLevel = "em_ScaleLevel";

			bool generate (Saphir::ShaderGenerator & generator, int samples) const noexcept override;

			Libraries::PixelFactory::Color< float > m_teint = Libraries::PixelFactory::White;
			Mode m_mode = Mode::Average;
			Option m_option = Option::None;
			unsigned int m_scaleLevel = 16;
	};
}
