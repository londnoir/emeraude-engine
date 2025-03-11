/*
 * src/Graphics/FramebufferPrecisions.hpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2025 - Sébastien Léon Claude Christian Bémelmans "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Emeraude-Engine; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Complete project and additional information can be found at :
 * https://github.com/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#pragma once

/* STL inclusions. */
#include <cstdint>

/* Local inclusions. */
#include "SettingKeys.hpp"

namespace EmEn::Graphics
{
	/**
	 * @brief The framebuffer precisions class.
	 */
	class FramebufferPrecisions
	{
		public:

			/**
			 * @brief Constructs a default framebuffer precisions.
			 */
			FramebufferPrecisions () noexcept = default;

			/**
			 * @brief Constructs a framebuffer precisions.
			 * @param redBits A value for red channel bits precision of the color buffer.
			 * @param greenBits A value for green channel bits precision of the color buffer.
			 * @param blueBits A value for blue channel bits precision of the color buffer.
			 * @param alphaBits A value for alpha channel bits precision of the color buffer.
			 * @param depthBits A value for bits precision of the depth buffer.
			 * @param stencilBits A value for bits precision of the stencil buffer.
			 * @param samples The number of sampler of the color buffer.
			 */
			FramebufferPrecisions (uint32_t redBits, uint32_t greenBits, uint32_t blueBits, uint32_t alphaBits, uint32_t depthBits, uint32_t stencilBits, uint32_t samples) noexcept;

			/**
			 * @brief Returns red component bits.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t
			redBits () const noexcept
			{
				return m_redBits;
			}

			/**
			 * @brief Returns green component bits.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t
			greenBits () const noexcept
			{
				return m_greenBits;
			}

			/**
			 * @brief Returns blue component bits.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t
			blueBits () const noexcept
			{
				return m_blueBits;
			}

			/**
			 * @brief Returns alpha component bits.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t
			alphaBits () const noexcept
			{
				return m_alphaBits;
			}

			/**
			 * @brief Returns color buffer bits.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t
			colorBits () const noexcept
			{
				return m_redBits + m_greenBits + m_blueBits + m_alphaBits;
			}

			/**
			 * @brief Returns depth buffer bits.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t
			depthBits () const noexcept
			{
				return m_depthBits;
			}

			/**
			 * @brief Returns stencil buffer bits.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t
			stencilBits () const noexcept
			{
				return m_stencilBits;
			}

			/**
			 * @brief Returns framebuffer samples.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t
			samples () const noexcept
			{
				return m_samples;
			}

		private:

			uint32_t m_redBits{DefaultVideoFramebufferRedBits};
			uint32_t m_greenBits{DefaultVideoFramebufferGreenBits};
			uint32_t m_blueBits{DefaultVideoFramebufferBlueBits};
			uint32_t m_alphaBits{DefaultVideoFramebufferAlphaBits};
			uint32_t m_depthBits{DefaultVideoFramebufferDepthBits};
			uint32_t m_stencilBits{DefaultVideoFramebufferStencilBits};
			uint32_t m_samples{DefaultVideoFramebufferSamples};
	};
}
