/*
 * src/Overlay/PixelBufferSurface.hpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2024 - "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emeraude-Engine; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Complete project and additional information can be found at :
 * https://bitbucket.org/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#pragma once

/* STL inclusions. */
#include <cstdint>
#include <memory>
#include <string>

/* Local inclusions for inheritances. */
#include "AbstractSurface.hpp"

/* Local inclusions for usages. */
#include "FramebufferProperties.hpp"
#include "Graphics/TextureResource/Abstract.hpp"
#include "Libraries/Math/Rectangle.hpp"
#include "Libraries/PixelFactory/Pixmap.hpp"
#include "Vulkan/DescriptorSet.hpp"

namespace Emeraude::Overlay
{
	/**
	 * @brief The base class of all overlay surfaces using a pixel buffer.
	 * @extends Emeraude::Overlay::AbstractSurface This is a surface.
	 */
	class PixelBufferSurface : public AbstractSurface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"PixelBufferSurface"};

			/** 
			 * @brief Constructs a default pixel buffer surface.
			 * @param framebufferProperties A reference to the overlay framebuffer properties.
			 * @param name A reference to a string.
			 * @param geometry A reference to a rectangle for the surface geometry on screen. Default the whole screen.
			 * @param depth A depth value to order surface on the screen. Default 0.0.
			 */
			PixelBufferSurface (const FramebufferProperties & framebufferProperties, const std::string & name, const Libraries::Math::Rectangle< float > & geometry = {}, float depth = 0.0F) noexcept;

			/** @copydoc Emeraude::Overlay::AbstractSurface::descriptorSet() const */
			[[nodiscard]]
			const Vulkan::DescriptorSet * descriptorSet () const noexcept final;

			/** @copydoc Emeraude::Overlay::AbstractSurface::createOnHardware() */
			[[nodiscard]]
			bool createOnHardware (Graphics::Renderer & renderer) noexcept final;

			/** @copydoc Emeraude::Overlay::AbstractSurface::destroyFromHardware() */
			bool destroyFromHardware () noexcept final;

			[[nodiscard]]
			Libraries::PixelFactory::Pixmap< uint8_t > &
			pixmap () noexcept
			{
				return m_localData;
			}

		private:

			/** @copydoc Emeraude::Overlay::AbstractSurface::createDescriptorSet() */
			[[nodiscard]]
			bool createDescriptorSet (Graphics::Renderer & renderer) noexcept final;

			/** @copydoc Emeraude::Overlay::AbstractSurface::onPhysicalRepresentationUpdate() */
			[[nodiscard]]
			bool onPhysicalRepresentationUpdate (Graphics::Renderer & renderer) noexcept final;

			/** @copydoc Emeraude::Overlay::AbstractSurface::onVideoMemoryUpdate() */
			[[nodiscard]]
			bool onVideoMemoryUpdate (Graphics::Renderer & renderer) noexcept final;

			/**
			 * @brief Creates the Vulkan image.
			 * @param renderer A reference to the renderer.
			 * @return bool
			 */
			[[nodiscard]]
			bool createImage (Graphics::Renderer & renderer) noexcept;

			/**
			 * @brief Creates the Vulkan image view.
			 * @return bool
			 */
			[[nodiscard]]
			bool createImageView () noexcept;

			/**
			 * @brief Gets a Vulkan sampler.
			 * @param renderer A reference to the renderer.
			 * @return bool
			 */
			[[nodiscard]]
			bool getSampler (Graphics::Renderer & renderer) noexcept;

			Libraries::PixelFactory::Pixmap< uint8_t > m_localData;
			std::shared_ptr< Vulkan::Image > m_image;
			std::shared_ptr< Vulkan::ImageView > m_imageView;
			std::shared_ptr< Vulkan::Sampler > m_sampler;
			std::unique_ptr< Vulkan::DescriptorSet > m_descriptorSet;
	};
}
