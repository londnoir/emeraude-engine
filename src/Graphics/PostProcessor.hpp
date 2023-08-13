/*
 * Emeraude/Graphics/PostProcessor.hpp
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
#include "PixelFactory/Area.hpp"
/* Local inclusions for usages. */
/* VULKAN_DEV */
//#include "Framebuffer.hpp"
#include "Saphir/FramebufferEffectInterface.hpp"
#include "Geometry/IndexedVertexResource.hpp"

namespace Emeraude::Graphics
{
	/**
	 * @brief The PostProcessor class
	 */
	class PostProcessor final
	{
		friend class View;

		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"PostProcessor"};

			/* GLSL variables. */
			static constexpr auto Fragment = "em_Fragment";

			/**
			 * Construct a offscreen framebuffer for post-rendering effects.
			 *
			 * @param width The framebuffer width.
			 * @param height The framebuffer height.
			 * @param colorBufferBits The desired color precision.
			 * @param depthBufferBits The desired depth precision.
			 * @param stencilBufferBits The desired stencil precision.
			 * @param samples The desired multisample multiplier.
			 */
			PostProcessor (unsigned int width, unsigned int height, unsigned int colorBufferBits, unsigned int depthBufferBits, unsigned int stencilBufferBits, unsigned int samples) noexcept;

			/**
			 * Returns whether the post-processor is usable.
			 *
			 * @return bool
			 */
			[[nodiscard]]
			bool usable () const noexcept;

			/**
			 * Updates the program of the post processor if requested.
			 *
			 * @return bool
			 */
			//bool updateVideoMemoryForRendering () noexcept;

			/**
			 * Sets a list of post effect.
			 *
			 * @param effectsList The list of shader effects.
			 */
			void setEffectsList (const Saphir::FramebufferEffectsList & effectsList) noexcept;

			/** Clear every effects. */
			void clearEffects () noexcept;

			/** Prepares the post-processor for drawing to the off-screen framebuffer. */
			void begin () noexcept;

			/** Release post-processor to let draw the off-screen framebuffer to view framebuffer. */
			void end () noexcept;

			/**
			 * Render the off-screen buffer with effects to the default framebuffer.
			 *
			 * @param region The viewport area to blit/copy the render.
			 */
			void render (const Libraries::PixelFactory::Area< size_t > & region) const noexcept;

			/**
			 * Returns a pointer to the framebuffer responsible for the post-processor.
			 *
			 * @return const Framebuffer *
			 */
			//[[nodiscard]]
			//const Framebuffer * framebuffer () const noexcept;

			/**
			 * Returns whether the framebuffer is using multisample.
			 *
			 * @return bool
			 */
			[[nodiscard]]
			bool isMultisamplingEnabled () const noexcept;

			/**
			 * Sets the background color for the framebuffer.
			 *
			 * @param color A reference to a color.
			 */
			void setBackgroundColor (const Libraries::PixelFactory::Color< float > & color) noexcept;

		private:

			/* Flag names. */
			static constexpr auto UpdateRequested = 0UL;
			static constexpr auto Usable = 1UL;

			/**
			 * Resize the framebuffer.
			 *
			 * @param width The new width.
			 * @param height The new height.
			 * @return bool
			 */
			bool resize (unsigned int width, unsigned int height) noexcept;

			bool loadGeometry () noexcept;

			/**
			 * Load the post-processor shading program.
			 *
			 * @return bool
			 */
			bool loadProgram () noexcept;

			bool buildFramebuffer (unsigned int width, unsigned int height, unsigned int colorBufferBits, unsigned int depthBufferBits, unsigned int stencilBufferBits, unsigned int samples) noexcept;

			//Framebuffer m_framebuffer{};
			//std::shared_ptr< Vulkan::Texture2D > m_colorBuffer{};
			//RenderBufferObject m_extraBuffer{};
			std::unique_ptr< Geometry::IndexedVertexResource > m_geometry{};
			Saphir::FramebufferEffectsList m_effectsList{};
			//std::shared_ptr< Program > m_program{};
			//RasterizationMode m_rasterizationMode{};
			std::array< bool, 8 > m_flags{
				false/*UpdateRequested, Say if post-processor effects need update for shading programs. */,
				false/*Usable*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
