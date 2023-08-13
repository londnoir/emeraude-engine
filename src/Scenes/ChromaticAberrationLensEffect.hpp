/*
 * Emeraude/Scenes/ChromaticAberrationLensEffect.hpp
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
#include "Math/Vector.hpp"

namespace Emeraude::Scenes
{
	class ChromaticAberrationLensEffect final : public Saphir::FramebufferEffectInterface
	{
		public:

			/**
			 * Parametric constructor.
			 *
			 * @param xScale Difference on X.
			 * @param yScale Difference on Y.
			 */
			ChromaticAberrationLensEffect (float xScale, float yScale) noexcept;

			//void activate (const Graphics::Program & program, unsigned int & nextTextureUnit) const noexcept override;

		private:

			static constexpr auto RedOffset = "em_RedOffset";
			static constexpr auto GreenOffset = "em_GreenOffset";
			static constexpr auto BlueOffset = "em_BlueOffset";

			[[nodiscard]]
			bool overrideFragmentFetching () const noexcept override;

			bool generate (Saphir::ShaderGenerator & generator, int samples) const noexcept override;

			mutable int m_samples = 0;
			Libraries::Math::Vector< 2, float > m_redOffset{};
			Libraries::Math::Vector< 2, float > m_greenOffset{};
			Libraries::Math::Vector< 2, float > m_blueOffset{};
	};
}
