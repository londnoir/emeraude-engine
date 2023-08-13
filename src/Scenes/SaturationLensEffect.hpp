/*
 * Emeraude/Scenes/SaturationLensEffect.hpp
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
	class SaturationLensEffect final : public Saphir::FramebufferEffectInterface
	{
		public:

			/**
			 * Parametric constructor.
			 *
			 * @param saturation The initial saturation value. 0.0 does nothing.
			 */
			explicit SaturationLensEffect (float saturation = 0.0F) noexcept;

			//void activate (const Graphics::Program & program, unsigned int & nextTextureUnit) const noexcept override;

			void setSaturation (float value) noexcept;

			[[nodiscard]]
			float saturation () const noexcept;

		private:

			static constexpr auto Saturation = "em_Saturation";

			bool generate (Saphir::ShaderGenerator & gen, int samples) const noexcept override;

			float m_saturation = 0.0F;
	};
}
