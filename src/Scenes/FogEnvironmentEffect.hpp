/*
 * Emeraude/Scenes/FogEnvironmentEffect.hpp
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
#include "Saphir/EffectInterface.hpp"

/* Local inclusions for usages. */
#include "PixelFactory/Color.hpp"

namespace Emeraude::Scenes
{
	class FogEnvironmentEffect final : public Saphir::EffectInterface
	{
		public:

			enum class FogMode
			{
				Linear,
				Exponential,
				Exponential2,
				Exponential2Alt
			};

			/** @brief Class identifier. */
			static constexpr auto ClassId{"FogEnvironmentEffect"};

			/**
			 * @brief Constructs the fog environment effect.
			 * @param mode The fog algorithm. Default FogMode::Exponential.
			 */
			FogEnvironmentEffect (FogMode mode = FogMode::Exponential, bool highQuality = true) noexcept;

			//void activate (const Graphics::Program & program, unsigned int & nextTextureUnit) const noexcept override;

			void setDensity (float density) noexcept;

			void setLinearRange (float start, float end) noexcept;

			void setColor (const Libraries::PixelFactory::Color< float > & color) noexcept;

			void useBackgroundColor () noexcept;

			[[nodiscard]]
			FogMode mode () const noexcept;

			[[nodiscard]]
			float density () const noexcept;

			[[nodiscard]]
			float linearStart () const noexcept;

			[[nodiscard]]
			float endStart () const noexcept;

			[[nodiscard]]
			const Libraries::PixelFactory::Color< float > & color () const noexcept;

		private:

			static constexpr auto FogDensity = "em_FogDensity";
			static constexpr auto FogStart = "em_FogStart";
			static constexpr auto FogEnd = "em_FogEnd";
			static constexpr auto FogColor = "em_FogColor";

			static constexpr auto FogVertexDistance = "em_FogVertexDistance";

			bool generate (Saphir::ShaderGenerator & generator) const noexcept override;

			FogMode m_mode;
			/* Only for linear mode. */
			float m_Start = 0.0F;
			float m_End = 1.0F;
			/* Only for exponential mode */
			float m_density = 1.0F;
			/* Fog color */
			Libraries::PixelFactory::Color< float > m_color{};
			/* Per vertex or pixel */
			bool m_highQuality = true;
			bool m_useBackgroundColor = false;
	};
}
