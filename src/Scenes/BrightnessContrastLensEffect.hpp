/*
 * Emeraude/Scenes/BrightnessContrastLensEffect.hpp
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

/* Local inclusions for inheritances. */
#include "Saphir/FramebufferEffectInterface.hpp"

/* Local inclusions for usages. */
#include "Graphics/TextureResource/Texture2D.hpp"

namespace Emeraude::Scenes
{
	class BrightnessContrastLensEffect final : public Saphir::FramebufferEffectInterface
	{
		public:

			/**
			 * Parametric constructor.
			 *
			 * @param brightness The initial brightness value. 0.0 does nothing.
			 * @param contrast The initial contrast value. 1.0 does nothing.
			 */
			BrightnessContrastLensEffect (float brightness = 0.0F, float contrast = 1.0F) noexcept;

			//void activate (const Graphics::Program & program, unsigned int & nextTextureUnit) const noexcept override;

			/**
			 * Sets the brightness.
			 *
			 * @param value The brightness value.
			 */
			void setBrightness (float value) noexcept;

			/**
			 * Returns the brightness value.
			 *
			 * @return float
			 */
			[[nodiscard]]
			float brightness () const noexcept;

			/**
			 * Sets the contrast.
			 *
			 * @param value The contrast value.
			 */
			void setContrast (float value) noexcept;

			/**
			 * Returns the contrast value.
			 *
			 * @return float
			 */
			[[nodiscard]]
			float contrast () const noexcept;

		private:

			static constexpr auto Brightness = "em_Brightness";
			static constexpr auto Contrast = "em_Contrast";

			bool generate (Saphir::ShaderGenerator & generator, int samples) const noexcept override;

			float m_brightness = 0.0F;
			float m_contrast = 1.0F;
	};
}
