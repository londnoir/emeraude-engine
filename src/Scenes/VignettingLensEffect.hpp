/*
 * Emeraude/Scenes/VignettingLensEffect.hpp
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

/* Forward declarations */
namespace Emeraude
{
	namespace Graphics
	{
		class ImageResource;
	}

	namespace Vulkan
	{
		class Image;
	}
}

namespace Emeraude::Scenes
{
	class VignettingLensEffect final : public Saphir::FramebufferEffectInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VignettingLensEffect"};

			/**
			 * @brief Constructs a vignetting lense effect.
			 * @param strength The strength of the effect. Default 1.
			 */
			explicit VignettingLensEffect (float strength = 1.0F) noexcept;

			//void activate (const Graphics::Program & program, unsigned int & nextTextureUnit) const noexcept override;

			void setStrength (float value) noexcept;

			[[nodiscard]]
			float strength () const noexcept;

		private:

			static constexpr auto VignettingTexture = "em_VignettingTexture";
			static constexpr auto Strength = "em_Strength";

			[[nodiscard]]
			bool requestScreenCoordinates () const noexcept override;

			bool generate (Saphir::ShaderGenerator & generator, int samples) const noexcept override;

			std::shared_ptr< Graphics::ImageResource > m_image;
			std::shared_ptr< Vulkan::Image > m_texture{};
			float m_strength = 1.0F;
	};
}
