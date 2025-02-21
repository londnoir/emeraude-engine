/*
 * src/Overlay/FramebufferProperties.hpp
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
#include <cmath>
#include <array>
#include <string>

/* Local inclusions for usages. */
#include "Libraries/Math/Rectangle.hpp"

namespace Emeraude::Overlay
{
	/**
	 * @brief Defines a framebuffer properties for overlay usage.
	 */
	class FramebufferProperties final
	{
		public:

			/** 
			 * @brief Constructs a default framebuffer properties.
			 */
			FramebufferProperties () noexcept = default;

			/**
			 * @brief Constructs a framebuffer properties.
			 * @param width The framebuffer width in pixel.
			 * @param height The framebuffer height in pixel.
			 * @param scaleX The scale in X.
			 * @param scaleY The scale in Y.
			 */
			FramebufferProperties (uint32_t width, uint32_t height, float scaleX, float scaleY) noexcept;

			/**
			 * @brief Constructs a framebuffer properties.
			 * @param data A reference to an array of unsigned integer.
			 * @param scaleX The scale in X.
			 * @param scaleY The scale in Y.
			 */
			FramebufferProperties (const std::array< uint32_t, 2 > & data, float scaleX, float scaleY) noexcept;

			/**
			 * @brief Sets the framebuffer resolution.
			 * @param width The framebuffer width.
			 * @param height the framebuffer height.
			 * @return void
			 */
			void
			setResolution (uint32_t width, uint32_t height) noexcept
			{
				m_resolution[0] = width;
				m_resolution[1] = height;

				this->updateScaledResolution();
			}

			/**
			 * @brief Sets the framebuffer resolution.
			 * @param data A reference to an array of unsigned integer.
			 * @return void
			 */
			void
			setResolution (const std::array< uint32_t, 2 > & data) noexcept
			{
				m_resolution = data;

				this->updateScaledResolution();
			}

			/**
			 * @brief Sets the framebuffer scaling.
			 * @param scaleX The scale in X.
			 * @param scaleY The scale in Y.
			 * @return void
			 */
			void
			setScale (float scaleX, float scaleY) noexcept
			{
				m_scaleX = scaleX;
				m_scaleY = scaleY;

				this->updateScaledResolution();
			}

			/**
			 * @brief Sets the framebuffer scaling.
			 * @param scale The scale uniform on both axis.
			 * @return void
			 */
			void
			setScale (float scale) noexcept
			{
				m_scaleX = scale;
				m_scaleY = scale;

				this->updateScaledResolution();
			}

			/**
			 * @brief Checks whether the framebuffer info are valid.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isValid () const noexcept
			{
				return m_resolution[0] * m_resolution[1] != 0;
			}

			/**
			 * @brief Returns the resolution.
			 * @return const std::array< uint32_t, 2 > &
			 */
			[[nodiscard]]
			const std::array< uint32_t, 2 > &
			resolution () const noexcept
			{
				return m_resolution;
			}

			/**
			 * @brief Returns the framebuffer width.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t
			width () const noexcept
			{
				return m_resolution[0];
			}

			/**
			 * @brief Returns the framebuffer height.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t
			height () const noexcept
			{
				return m_resolution[1];
			}

			/**
			 * @brief Returns the scale to apply in X.
			 * @return float
			 */
			[[nodiscard]]
			float
			scaleX () const noexcept
			{
				return m_scaleX;
			}

			/**
			 * @brief Returns the scale to apply in Y.
			 * @return float
			 */
			[[nodiscard]]
			float
			scaleY () const noexcept
			{
				return m_scaleY;
			}

			/**
			 * @brief Returns the biggest scaling factor.
			 * @return float
			 */
			[[nodiscard]]
			float
			maxScale () const noexcept
			{
				return std::max(m_scaleX, m_scaleY);
			}

			/**
			 * @brief Returns the inverse scale to apply in X.
			 * @return float
			 */
			[[nodiscard]]
			float
			inverseScaleX () const noexcept
			{
				return m_inverseScaleX;
			}

			/**
			 * @brief Returns the inverse scale to apply in Y.
			 * @return float
			 */
			[[nodiscard]]
			float
			inverseScaleY () const noexcept
			{
				return m_inverseScaleY;
			}

			/**
			 * @brief Returns the scaled resolution.
			 * @return const std::array< uint32_t, 2 > &
			 */
			[[nodiscard]]
			const std::array< uint32_t, 2 > &
			scaledResolution () const noexcept
			{
				return m_scaledResolution;
			}

			/**
			 * @brief Returns the scaled width according to X scale.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t
			scaledWidth () const noexcept
			{
				return m_scaledResolution[0];
			}

			/**
			 * @brief Returns the scaled height according to Y scale.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t
			scaledHeight () const noexcept
			{
				return m_scaledResolution[1];
			}

			/**
			 * @brief Returns a scaled version of the framebuffer dimensions.
			 * @tparam float_t The type of floating number. Default float.
			 * @param widthFactor The width factor.
			 * @param heightFactor The height factor.
			 * @param usePowerOfTwo Takes cares of having the dimensions as a power of two. Default true.
			 * @return std::array< uint32_t, 2 >
			 */
			template< typename float_t = float >
			[[nodiscard]]
			std::array< uint32_t, 2 >
			getScaledResolution (float_t widthFactor, float_t heightFactor, bool usePowerOfTwo = true) const noexcept requires (std::is_floating_point_v< float_t >)
			{
				/* NOTE: Do not simplify computation here ! */
				const auto width = static_cast< float_t >(m_scaledResolution[0]) * m_scaleX * std::abs(widthFactor);
				const auto height = static_cast< float_t >(m_scaledResolution[1]) * m_scaleY * std::abs(heightFactor);

				if ( usePowerOfTwo )
				{
					return {
						static_cast< uint32_t >(std::pow(static_cast< float_t >(2), std::ceil(std::log(width) / std::log(static_cast< float_t >(2))))),
						static_cast< uint32_t >(std::pow(static_cast< float_t >(2), std::ceil(std::log(height) / std::log(static_cast< float_t >(2)))))
					};
				}

				return {
					static_cast< uint32_t >(std::round(width)),
					static_cast< uint32_t >(std::round(height))
				};
			}

			/**
			 * @brief Returns a scaled version of the framebuffer dimensions.
			 * @tparam float_t The type of floating number. Default float.
			 * @param factor A reference to an array of floats.
			 * @param usePowerOfTwo Takes cares of having the dimensions as a power of two. Default true.
			 * @return std::array< uint32_t, 2 >
			 */
			template< typename float_t = float >
			[[nodiscard]]
			std::array< uint32_t, 2 >
			getScaledResolution (const std::array< float_t, 2 > & factor, bool usePowerOfTwo = true) const noexcept requires (std::is_floating_point_v< float_t >)
			{
				return this->getScaledResolution(factor[0], factor[1], usePowerOfTwo);
			}

			/**
			 * @brief Returns a scaled version of the framebuffer dimensions.
			 * @tparam float_t The type of floating number. Default float.
			 * @param rectangle A reference to a rectangle.
			 * @param usePowerOfTwo Takes cares of having the dimensions as a power of two. Default true.
			 * @return std::array< uint32_t, 2 >
			 */
			template< typename float_t = float >
			[[nodiscard]]
			std::array< uint32_t, 2 >
			getScaledResolution (const Libraries::Math::Rectangle< float_t > & rectangle, bool usePowerOfTwo = true) const noexcept requires (std::is_floating_point_v< float_t >)
			{
				return this->getScaledResolution(rectangle.width(), rectangle.height(), usePowerOfTwo);
			}

			/**
			 * @brief Updates the framebuffer properties.
			 * @param width The framebuffer width in pixel.
			 * @param height The framebuffer height in pixel.
			 * @param scaleX The scale in X.
			 * @param scaleY The scale in Y.
			 * @return void
			 */
			void
			updateProperties (uint32_t width, uint32_t height, float scaleX, float scaleY) noexcept
			{
				m_resolution[0] = width;
				m_resolution[1] = height;

				this->setScale(scaleX, scaleY);
			}

			/**
			 * @brief Updates the framebuffer properties.
			 * @param data A reference to an array of unsigned integer.
			 * @param scaleX The scale in X.
			 * @param scaleY The scale in Y.
			 * @return void
			 */
			void
			updateProperties (const std::array< uint32_t, 2 > & data, float scaleX, float scaleY) noexcept
			{
				m_resolution = data;

				this->setScale(scaleX, scaleY);
			}

			/**
			 * @brief Resets the framebuffer properties.
			 * @return void
			 */
			void reset () noexcept;

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const FramebufferProperties & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend std::string to_string (const FramebufferProperties & obj) noexcept;

		private:

			/**
			 * @brief Updates the scaled resolution with factors.
			 * @return void
			 */
			void updateScaledResolution () noexcept;

			std::array< uint32_t, 2 > m_resolution{0, 0};
			std::array< uint32_t, 2 > m_scaledResolution{0, 0};
			float m_scaleX{1.0F};
			float m_scaleY{1.0F};
			float m_inverseScaleX{1.0F};
			float m_inverseScaleY{1.0F};
	};
}
