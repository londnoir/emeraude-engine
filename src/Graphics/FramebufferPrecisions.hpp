/*
 * Emeraude/Graphics/FramebufferPrecisions.hpp
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

/* C/C++ standard libraries. */
#include <cstdint>

namespace Emeraude::Graphics
{
	/**
	 * @brief The framebuffer precisions class.
	 */
	class FramebufferPrecisions
	{
		public:

			static constexpr auto RedBitsKey = "Video/View/RedBits";
			static constexpr auto DefaultRedBits = 8U;
			static constexpr auto GreenBitsKey = "Video/View/GreenBits";
			static constexpr auto DefaultGreenBits = 8U;
			static constexpr auto BlueBitsKey = "Video/View/BlueBits";
			static constexpr auto DefaultBlueBits = 8U;
			static constexpr auto AlphaBitsKey = "Video/View/AlphaBits";
			static constexpr auto DefaultAlphaBits = 8U;
			static constexpr auto DepthBitsKey = "Video/View/DepthBits";
			static constexpr auto DefaultDepthBits = 32U;
			static constexpr auto StencilBitsKey = "Video/View/StencilBits";
			static constexpr auto DefaultStencilBits = 0U;
			static constexpr auto SamplesKey = "Video/View/Samples";
			static constexpr auto DefaultSamples = 1U;

			/**
			 * @brief Default constructor.
			 */
			FramebufferPrecisions () noexcept = default;

			/**
			 * @brief Constructs a framebuffer precisions.
			 * @param redBits
			 * @param greenBits
			 * @param blueBits
			 * @param alphaBits
			 * @param depthBits
			 * @param stencilBits
			 * @param samples
			 */
			FramebufferPrecisions (uint32_t redBits, uint32_t greenBits, uint32_t blueBits, uint32_t alphaBits, uint32_t depthBits, uint32_t stencilBits, uint32_t samples) noexcept;

			/**
			 * @brief Returns red component bits.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t redBits () const noexcept;

			/**
			 * @brief Returns green component bits.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t greenBits () const noexcept;

			/**
			 * @brief Returns blue component bits.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t blueBits () const noexcept;

			/**
			 * @brief Returns alpha component bits.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t alphaBits () const noexcept;

			/**
			 * @brief Returns color buffer bits.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t colorBits () const noexcept;

			/**
			 * @brief Returns depth buffer bits.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t depthBits () const noexcept;

			/**
			 * @brief Returns stencil buffer bits.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t stencilBits () const noexcept;

			/**
			 * @brief Returns framebuffer samples.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t samples () const noexcept;

		private:

			uint32_t m_redBits = DefaultRedBits;
			uint32_t m_greenBits = DefaultGreenBits;
			uint32_t m_blueBits = DefaultBlueBits;
			uint32_t m_alphaBits = DefaultAlphaBits;
			uint32_t m_depthBits = DefaultDepthBits;
			uint32_t m_stencilBits = DefaultStencilBits;
			uint32_t m_samples = DefaultSamples;
	};
}
