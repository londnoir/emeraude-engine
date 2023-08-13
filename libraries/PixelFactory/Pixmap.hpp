/*
 * Libraries/PixelFactory/Pixmap.hpp
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

/* C/C++ standard libraries */
#include <array>
#include <cmath>
#include <cstring>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/* Local inclusions */
#include "libraries_config.hpp"
#include "Area.hpp"
#include "Color.hpp"
#include "Gradient.hpp"
#include "Math/Vector.hpp"
#include "PerlinNoise.hpp"
#include "Types.hpp"
#include "Utility.hpp"

namespace Libraries::PixelFactory
{
	/**
	 * @brief Defines a structure to store pixels to make an image.
	 * @tparam data_t The type of pixel sub-element, the type must be numeric. Default uint8_t.
	 */
	template< typename data_t = uint8_t, std::enable_if_t< std::is_arithmetic_v< data_t >, bool > = false >
	class Pixmap
	{
		public:

			/* Mode list */
			static constexpr auto RGBA = 4UL;
			static constexpr auto RGB = 3UL;
			static constexpr auto GrayscaleAlpha = 2UL;
			static constexpr auto Grayscale = 1UL;

			static constexpr auto Resolution72DPI = 2835UL;
			static constexpr auto Resolution96DPI = 3780UL;

			/**
			 * @brief The Format enum
			 */
			enum class Format
			{
				None,
				Targa, /* No compression */
				PNG, /* Loss-less compression */
				Jpeg /* Destructive compression */
			};

			/**
			 * @brief Default constructor.
			 * @note The channel mode will be set to RGB.
			 */
			Pixmap () noexcept = default;

			/**
			 * @brief Constructs a new pixmap.
			 * @param width The initial width of the pixmap.
			 * @param height The initial height of the pixmap.
			 * @param channelMode The number of color as a class constant. Default ChannelMode::RGB.
			 */
			explicit Pixmap (size_t width, size_t height, ChannelMode channelMode = ChannelMode::RGB) noexcept
				: m_width(width), m_height(height), m_channelMode(channelMode)
			{
				m_data.resize(this->elementCount(), 0);

				this->initAlphaChannel();
			}

			/**
			 * @brief Constructs a new pixmap initialized with a designed color.
			 * @tparam colorData_t The color data type.
			 * @param width The initial width of the pixmap.
			 * @param height The initial height of the pixmap.
			 * @param channelMode The number of color as a class constant.
			 * @param color A reference to a color.
			 */
			template< typename colorData_t = float, std::enable_if_t< std::is_floating_point_v< colorData_t >, bool > = false >
			Pixmap (size_t width, size_t height, ChannelMode channelMode, const Color< colorData_t > & color) noexcept
				: m_width(width), m_height(height), m_channelMode(channelMode)
			{
				m_data.resize(this->elementCount(), 0);

				this->fill(color);
			}

			/**
			 * @brief Initializes pixmap data.
			 * @param width The initial width of the pixmap.
			 * @param width The initial height of the pixmap.
			 * @param channelMode The number of color as a class constant. Default ChannelMode::RGB.
			 * @return bool
			 */
			bool
			initialize (size_t width, size_t height, ChannelMode channelMode = ChannelMode::RGB) noexcept
			{
				if ( width == 0 || height == 0 )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", invalid pixmap dimensions !" << std::endl;

					return false;
				}

				m_width = width;
				m_height = height;
				m_channelMode = channelMode;
				m_data.resize(this->elementCount(), 0);

				this->initAlphaChannel();

				return true;
			}

			/**
			 * @brief Clears the pixmap data.
			 * @note Width and height will be reset to zero and the channel mode to RGB.
			 * @return void
			 */
			void
			clear () noexcept
			{
				m_width = 0;
				m_height = 0;
				m_channelMode = ChannelMode::RGB;
				m_data.clear();
			}

			/**
			 * @brief Returns data is initialized.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isValid () const noexcept
			{
				return !m_data.empty();
			}

			/**
			 * @brief Returns the pixmap width in pixels.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			width () const noexcept
			{
				return m_width;
			}

			/**
			 * @brief Returns the pixmap half width in pixels.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			halfWidth () const noexcept
			{
				return static_cast< size_t >(std::floor(static_cast< float >(m_width) * 0.5F));
			}

			/**
			 * @brief Returns the pixmap height in pixels.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			height () const noexcept
			{
				return m_height;
			}

			/**
			 * @brief Returns the pixmap half height in pixels.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			halfHeight () const noexcept
			{
				return static_cast< size_t >(std::floor(static_cast< float >(m_height) * 0.5F));
			}

			/**
			 * @brief Returns whether the pixmap is a square.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isSquare () const noexcept
			{
				return m_width == m_height;
			}

			/**
			 * @brief Returns an area surrounding the pixmap.
			 * @param x The offset in X to initialize the Area. Default 0.
			 * @param y The offset in Y to initialize the Area. Default 0.
			 * @return Area< size_t >
			 */
			Area< size_t >
			area (size_t x = 0, size_t y = 0) const noexcept
			{
				return {x, y, m_width, m_height};
			}

			/**
			 * @brief Returns the number of pixel of the pixmap.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isPowerOfTwo () const noexcept
			{
				if ( m_width % 2 > 0 )
				{
					return false;
				}

				if ( m_height % 2 > 0 )
				{
					return false;
				}

				return true;
			}

			/**
			 * @brief Returns the number of pixel of the pixmap.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			pixelCount () const noexcept
			{
				return m_width * m_height;
			}

			/**
			 * @brief Returns the channel mode.
			 * @return ChannelMode
			 */
			[[nodiscard]]
			ChannelMode
			channelMode () const noexcept
			{
				return m_channelMode;
			}

			/**
			 * @brief Returns the number of color.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			colorCount () const noexcept
			{
				return static_cast< size_t >(m_channelMode);
			}

			/**
			 * @brief Returns the number of elements of the pixmap.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			elementCount () const noexcept
			{
				return m_width * m_height * this->colorCount();
			}

			/**
			 * @brief Returns the size of the Pixmap in bytes.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			bytes () const noexcept
			{
				return m_data.size() * sizeof(data_t);
			}

			/**
			 * @brief Returns the size of a pixel in bytes.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			bytePerPixel () const noexcept
			{
				return this->colorCount() * sizeof(data_t);
			}

			/**
			 * @brief Returns the pixel bit requested. (8, 16, 24 or 32bit).
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			bitPerPixel () const noexcept
			{
				return this->bytePerPixel() * 8;
			}

			/**
			 * @brief Returns the size in bytes for one row of pixel.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			pitch () const noexcept
			{
				return m_width * this->colorCount() * sizeof(data_t);
			}

			/**
			 * @brief Returns the underlaying data of the pixmap.
			 * @return const std::vector< data_t > &
			 */
			const std::vector< data_t > &
			data () const noexcept
			{
				return m_data;
			}

			/**
			 * @brief Returns the underlaying data of the pixmap.
			 * @return std::vector< data_t > &
			 */
			std::vector< data_t > &
			data () noexcept
			{
				return m_data;
			}

			/**
			 * @brief Returns the pointer of the first element of a row.
			 * @param rowIndex The index of the row.
			 * @return type_t *
			 */
			[[nodiscard]]
			data_t *
			rowPointer (size_t rowIndex) noexcept
			{
#ifdef DEBUG_PIXEL_FACTORY
				if ( rowIndex >= m_height )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", row index overflow !" << std::endl;

					return nullptr;
				}
#endif
				return m_data.data() + (rowIndex * this->pitch());
			}

			/**
			 * @brief Returns the pointer of the first element of a row.
			 * @param rowIndex The index of the row.
			 * @return const type_t *
			 */
			[[nodiscard]]
			const data_t *
			rowPointer (size_t rowIndex) const noexcept
			{
#ifdef DEBUG_PIXEL_FACTORY
				if ( rowIndex >= m_height )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", row index overflow !" << std::endl;

					return nullptr;
				}
#endif
				return m_data.data() + (rowIndex * this->pitch());
			}

			/**
			 * @brief Returns a raw pixel pointer.
			 * @param pixelIndex The index of the pixel.
			 * @return const type_t *
			 */
			[[nodiscard]]
			const data_t *
			pixelPointer (size_t pixelIndex) const noexcept
			{
				return m_data.data() + (pixelIndex * this->colorCount());
			}

			/**
			 * @brief Returns a raw pixel pointer.
			 * @param x The X coordinate of the pixel.
			 * @param y The Y coordinate of the pixel.
			 * @return const type_t *
			 */
			[[nodiscard]]
			const data_t *
			pixelPointer (size_t x, size_t y) const noexcept
			{
				return this->pixelPointer(this->pixelIndex(x, y));
			}

			/**
			 * @brief Returns a raw pixel pointer.
			 * @param pixelIndex The index of the pixel.
			 * @return const type_t *
			 */
			[[nodiscard]]
			data_t *
			pixelPointer (size_t pixelIndex) noexcept
			{
				return m_data.data() + (pixelIndex * this->colorCount());
			}

			/**
			 * @brief Returns a raw pixel pointer.
			 * @param x The X coordinate of the pixel.
			 * @param y The Y coordinate of the pixel.
			 * @return const type_t *
			 */
			[[nodiscard]]
			data_t *
			pixelPointer (size_t x, size_t y) noexcept
			{
				return this->pixelPointer(this->pixelIndex(x, y));
			}

			/**
			 * @brief Returns the X coordinates in the image from the array index.
			 * @param pixelIndex The pixel index.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			x (size_t pixelIndex) const noexcept
			{
#ifdef DEBUG_PIXEL_FACTORY
				if ( pixelIndex >= this->pixelCount() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", pixel index overflow (" << pixelIndex << " >= " << this->pixelCount() << ") !" << std::endl;

					return 0;
				}
#endif
				return pixelIndex % m_width;
			}

			/**
			 * @brief Returns the Y coordinates in the image from the array index.
			 * @param pixelIndex The pixel index.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			y (size_t pixelIndex) const noexcept
			{
#ifdef DEBUG_PIXEL_FACTORY
				if ( pixelIndex >= this->pixelCount() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", pixel index overflow (" << pixelIndex << " >= " << this->pixelCount() << ") !" << std::endl;

					return 0;
				}
#endif
				return static_cast< size_t >(std::floor(pixelIndex / m_width));
			}

			/**
			 * @brief Returns the U texture2Ds coordinates in the image from the array index.
			 * @param pixelIndex The pixel index.
			 * @return float
			 */
			[[nodiscard]]
			float
			u (size_t pixelIndex) const noexcept
			{
#ifdef DEBUG_PIXEL_FACTORY
				if ( pixelIndex >= this->pixelCount() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", pixel index overflow (" << pixelIndex << " >= " << this->pixelCount() << ") !" << std::endl;

					return 0;
				}
#endif
				return this->x(pixelIndex) / static_cast< float >(m_width - 1);
			}

			/**
			 * @brief Returns the V texture2Ds coordinates in the image from the array index.
			 * @param pixelIndex The pixel index.
			 * @return float
			 */
			[[nodiscard]]
			float
			v (size_t pixelIndex) const noexcept
			{
#ifdef DEBUG_PIXEL_FACTORY
				if ( pixelIndex >= this->pixelCount() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", pixel index overflow (" << pixelIndex << " >= " << this->pixelCount() << ") !" << std::endl;

					return 0;
				}
#endif
				return this->y(pixelIndex) / static_cast< float >(m_height - 1);
			}

			/**
			 * @brief Returns the pixel index at location X, Y.
			 * @warning This is the pixel index. If you want to use this index over the data vector, use Pixmap::dataIndex() instead.
			 * @param x The X position of the pixel.
			 * @param y The Y position of the pixel.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			pixelIndex (size_t x, size_t y) const noexcept
			{
#ifdef DEBUG_PIXEL_FACTORY
				if ( x >= m_width || y >= m_height )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", pixel overflow at X:" << x << ", Y: " << y << " !" << std::endl;

					return 0;
				}
#endif
				return static_cast< size_t >((y * m_width) + x);
			}

			/**
			 * @brief Returns the data index at location X, Y.
			 * @param x The X position of the pixel.
			 * @param y The Y position of the pixel.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			dataIndex (size_t x, size_t y) const noexcept
			{
				return this->pixelIndex(x, y) * this->colorCount();
			}

			/**
			 * @brief Sets a pixel.
			 * @tparam colorData_t The color data type.
			 * @param pixelIndex The index of the pixel.
			 * @param color A reference to the color of the pixel.
			 * @return void
			 */
			template< typename colorData_t = float, std::enable_if_t< std::is_floating_point_v< colorData_t >, bool > = false >
			void
			setPixel (size_t pixelIndex, const Color< colorData_t > & color) noexcept
			{
				const auto offset = pixelIndex * this->colorCount();

				if constexpr ( std::is_floating_point_v< data_t > )
				{
					switch ( m_channelMode )
					{
						case ChannelMode::Grayscale :
							m_data[offset] = color.gray();
							break;

						case ChannelMode::GrayscaleAlpha :
							m_data[offset] = color.gray();
							m_data[offset + 1] = color.alpha();
							break;

						case ChannelMode::RGB :
							m_data[offset] = color.red();
							m_data[offset + 1] = color.green();
							m_data[offset + 2] = color.blue();
							break;

						case ChannelMode::RGBA :
							m_data[offset] = color.red();
							m_data[offset + 1] = color.green();
							m_data[offset + 2] = color.blue();
							m_data[offset + 3] = color.alpha();
							break;
					}
				}
				else
				{
					switch ( m_channelMode )
					{
						case ChannelMode::Grayscale :
							m_data[offset] = color.template grayInteger< data_t >();
							break;

						case ChannelMode::GrayscaleAlpha :
							m_data[offset] = color.template grayInteger< data_t >();
							m_data[offset + 1] = color.template alphaInteger< data_t >();
							break;

						case ChannelMode::RGB :
							m_data[offset] = color.template redInteger< data_t >();
							m_data[offset + 1] = color.template greenInteger< data_t >();
							m_data[offset + 2] = color.template blueInteger< data_t >();
							break;

						case ChannelMode::RGBA :
							m_data[offset] = color.template redInteger< data_t >();
							m_data[offset + 1] = color.template greenInteger< data_t >();
							m_data[offset + 2] = color.template blueInteger< data_t >();
							m_data[offset + 3] = color.template alphaInteger< data_t >();
							break;
					}
				}
			}

			/**
			 * @brief Sets a pixel.
			 * @tparam colorData_t The color data type.
			 * @param x The X coordinate of the pixel.
			 * @param y The Y coordinate of the pixel.
			 * @param color A reference to the color of the pixel.
			 */
			template< typename colorData_t = float, std::enable_if_t< std::is_floating_point_v< colorData_t >, bool > = false >
			void
			setPixel (size_t x, size_t y, const Color< colorData_t > & color) noexcept
			{
				this->setPixel(this->pixelIndex(x, y), color);

				this->setPixelAsUpdated(x, y);
			}

			/**
			 * @brief Mixes a color to an existing pixel with a scalar value.
			 * @tparam colorData_t The color data type.
			 * @param pixelIndex The index of the pixel.
			 * @param color A reference to a color.
			 * @param mix The mix scale.
			 */
			template< typename colorData_t = float, std::enable_if_t< std::is_floating_point_v< colorData_t >, bool > = false >
			void
			mixPixel (size_t pixelIndex, const Color< colorData_t > & color, float mix) noexcept
			{
				this->setPixel(pixelIndex, Color< colorData_t >::mix(this->pixel(pixelIndex), color, mix));
			}

			/**
			 * @brief Mixes a color to an existing pixel with a scalar value.
			 * @tparam colorData_t The color data type.
			 * @param x The X coordinate of the pixel.
			 * @param y The Y coordinate of the pixel.
			 * @param color A reference to a color.
			 * @param mode The blending technics.
			 */
			template< typename colorData_t = float, std::enable_if_t< std::is_floating_point_v< colorData_t >, bool > = false >
			void
			mixPixel (size_t x, size_t y, const Color< colorData_t > & color, float mix) noexcept
			{
				this->mixPixel(this->pixelIndex(x, y), color, mix);

				this->setPixelAsUpdated(x, y);
			}

			/**
			 * @brief Blends a color to an existing pixel.
			 * @tparam colorData_t The color data type.
			 * @param pixelIndex The index of the pixel.
			 * @param color A reference to a color.
			 * @param mode The blending technics.
			 * @param opacity A global opacity (Ignored with Replace). Default 1.0.
			 */
			template< typename colorData_t = float, std::enable_if_t< std::is_floating_point_v< colorData_t >, bool > = false >
			void
			blendPixel (size_t pixelIndex, const Color< colorData_t > & color, DrawPixelMode mode, float opacity = 1.0F) noexcept
			{
				if ( mode == DrawPixelMode::Replace )
					this->setPixel(pixelIndex, color);
				else
					this->setPixel(pixelIndex, Color< colorData_t >::blend(this->pixel(pixelIndex), color, mode, opacity));
			}

			/**
			 * @brief Blends a color to an existing pixel.
			 * @tparam colorData_t The color data type.
			 * @param x The X coordinate of the pixel.
			 * @param y The Y coordinate of the pixel.
			 * @param color A reference to a color.
			 * @param mode The blending technics.
			 * @param opacity A global opacity (Ignored with Replace). Default 1.0.
			 */
			template< typename colorData_t = float, std::enable_if_t< std::is_floating_point_v< colorData_t >, bool > = false >
			void
			blendPixel (size_t x, size_t y, const Color< colorData_t > & color, DrawPixelMode mode, float opacity = 1.0F) noexcept
			{
				this->blendPixel(this->pixelIndex(x, y), color, mode, opacity);

				this->setPixelAsUpdated(x, y);
			}

			/**
			 * @brief Returns a pixel as a color.
			 * @tparam colorData_t The color data type. Should be a floating point number.
			 * @param pixelIndex The index of the pixel.
			 * @return Color< colorData_t >
			 */
			template< typename colorData_t = float, std::enable_if_t< std::is_floating_point_v< colorData_t >, bool > = false >
			[[nodiscard]]
			Color< colorData_t >
			pixel (size_t pixelIndex) const noexcept
			{
				const auto offset = pixelIndex * this->colorCount();

				if constexpr ( std::is_floating_point_v< data_t > )
				{
					switch ( m_channelMode )
					{
						case ChannelMode::Grayscale :
							return {m_data[offset], m_data[offset], m_data[offset], 1};

						case ChannelMode::GrayscaleAlpha :
							return {m_data[offset], m_data[offset], m_data[offset], m_data[offset+1]};

						case ChannelMode::RGB :
							return {m_data[offset], m_data[offset+1], m_data[offset+2], 1};

						case ChannelMode::RGBA :
							return {m_data[offset], m_data[offset+1], m_data[offset+2], m_data[offset+3]};
					}
				}
				else
				{
					switch ( m_channelMode )
					{
						case ChannelMode::Grayscale :
							return ColorFromInteger(m_data[offset], m_data[offset], m_data[offset], Pixmap::one());

						case ChannelMode::GrayscaleAlpha :
							return ColorFromInteger(m_data[offset], m_data[offset], m_data[offset], m_data[offset+1]);

						case ChannelMode::RGB :
							return ColorFromInteger(m_data[offset], m_data[offset+1], m_data[offset+2], Pixmap::one());

						case ChannelMode::RGBA :
							return ColorFromInteger(m_data[offset], m_data[offset+1], m_data[offset+2], m_data[offset+3]);
					}
				}

				return {};
			}

			/**
			 * @brief Returns a pixel.
			 * @tparam colorData_t The color data type.
			 * @param x The X coordinate of the pixel.
			 * @param y The Y coordinate of the pixel.
			 * @return Color< colorData_t >
			 */
			template< typename colorData_t = float, std::enable_if_t< std::is_floating_point_v< colorData_t >, bool > = false >
			[[nodiscard]]
			Color< colorData_t >
			pixel (size_t x, size_t y) const noexcept
			{
				return this->pixel(this->pixelIndex(x, y));
			}

			/**
			 * @brief Returns the closest pixel to boundary at coordinates.
			 * @tparam colorData_t The color data type.
			 * @param x The X coordinate of the pixel.
			 * @param y The Y coordinate of the pixel.
			 * @return Color< colorData_t >
			 */
			template< typename colorData_t = float, std::enable_if_t< std::is_floating_point_v< colorData_t >, bool > = false >
			[[nodiscard]]
			Color< colorData_t >
			closestPixel (int x, int y) const noexcept
			{
				if ( x < 0 )
					x = 0;
				else if ( x >= m_width )
					x = m_width - 1;

				if ( y < 0 )
					y = 0;
				else if ( y >= m_height )
					y = m_height - 1;

				return this->pixel(x, y);
			}

			/**
			 * @brief Returns a sampled pixel using the nearest algorithm.
			 * @tparam colorData_t The color data type.
			 * @param u The X coordinate of the pixel.
			 * @param v The Y coordinate of the pixel.
			 * @return Color< colorData_t >
			 */
			template< typename colorData_t = float, std::enable_if_t< std::is_floating_point_v< colorData_t >, bool > = false >
			[[nodiscard]]
			Color< colorData_t >
			nearestSample (float u, float v) const noexcept
			{
				if ( m_flags[UVWrappingEnabled] )
				{
					if ( u < 0.0F || u > 1.0F )
						u = std::fmod(std::abs(u), 1.0F);

					if ( v < 0.0F || v > 1.0F )
						v = std::fmod(std::abs(v), 1.0F);
				}
				else if ( u < 0.0F || u > 1.0F || v < 0.0F || v > 1.0F )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", incorrect parameters (U:" << u << ", V:" << v << ") !" << std::endl;

					return {};
				}

				/* Prepare variable for X axis. */
				auto realX = static_cast< float >(m_width - 1) * u;

				/* Prepare variable for Y axis. */
				auto realY = static_cast< float >(m_height - 1) * v;

				return this->pixel(static_cast< size_t >(std::round(realX)), static_cast< size_t >(std::round(realY)));
			}

			/**
			 * @brief Returns a sampled pixel using the linear algorithm.
			 * @tparam colorData_t The color data type.
			 * @param u The X coordinate of the pixel.
			 * @param v The Y coordinate of the pixel.
			 * @return Color< colorData_t >
			 */
			template< typename colorData_t = float, std::enable_if_t< std::is_floating_point_v< colorData_t >, bool > = false >
			[[nodiscard]]
			Color< colorData_t >
			linearSample (float u, float v) const noexcept
			{
				if ( m_flags[UVWrappingEnabled] )
				{
					if ( u < 0.0F || u > 1.0F )
						u = std::fmod(std::abs(u), 1.0F);

					if ( v < 0.0F || v > 1.0F )
						v = std::fmod(std::abs(v), 1.0F);
				}
				else if ( u < 0.0F || u > 1.0F || v < 0.0F || v > 1.0F )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", incorrect parameters (U:" << u << ", V:" << v << ") !" << std::endl;

					return {};
				}

				/* Prepare variable for X axis. */
				auto realX = static_cast< float >(m_width - 1) * u;
				auto loX = static_cast< size_t >(std::floor(realX));
				auto hiX = static_cast< size_t >(std::ceil(realX));
				auto factorX = realX - loX;

				/* Prepare variable for Y axis. */
				auto realY = static_cast< float >(m_height - 1) * v;
				auto loY = static_cast< size_t >(std::floor(realY));
				auto hiY = static_cast< size_t >(std::ceil(realY));
				auto factorY = realY - loY;

				/* Gets involved pixels. */
				auto bottomLeftPixel = this->pixel(loX, loY);
				auto bottomRightPixel = this->pixel(hiX, loY);
				auto topLeftPixel = this->pixel(loX, hiY);
				auto topRightPixel = this->pixel(hiX, hiY);

				return Color< colorData_t >::bilinearInterpolation(bottomLeftPixel, bottomRightPixel, topLeftPixel, topRightPixel, factorX, factorY);
			}

			/**
			 * @brief Returns a sampled pixel using the cosine algorithm.
			 * @tparam colorData_t The color data type.
			 * @param u The X coordinate of the pixel.
			 * @param v The Y coordinate of the pixel.
			 * @return Color< colorData_t >
			 */
			template< typename colorData_t = float, std::enable_if_t< std::is_floating_point_v< colorData_t >, bool > = false >
			[[nodiscard]]
			Color< colorData_t >
			cosineSample (float u, float v) const noexcept
			{
				if ( m_flags[UVWrappingEnabled] )
				{
					if ( u < 0.0F || u > 1.0F )
						u = std::fmod(std::abs(u), 1.0F);

					if ( v < 0.0F || v > 1.0F )
						v = std::fmod(std::abs(v), 1.0F);
				}
				else if ( u < 0.0F || u > 1.0F || v < 0.0F || v > 1.0F )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", incorrect parameters (U:" << u << ", V:" << v << ") !" << std::endl;

					return {};
				}

				/* Prepare variable for X axis. */
				auto realX = static_cast< float >(m_width - 1) * u;
				auto loX = static_cast< size_t >(std::floor(realX));
				auto hiX = static_cast< size_t >(std::ceil(realX));
				auto factorX = realX - loX;

				/* Prepare variable for Y axis. */
				auto realY = static_cast< float >(m_height - 1) * v;
				auto loY = static_cast< size_t >(std::floor(realY));
				auto hiY = static_cast< size_t >(std::ceil(realY));
				auto factorY = realY - loY;

				/* Gets involved pixels. */
				auto bottomLeftPixel = this->pixel(loX, loY);
				auto bottomRightPixel = this->pixel(hiX, loY);
				auto topLeftPixel = this->pixel(loX, hiY);
				auto topRightPixel = this->pixel(hiX, hiY);

				return Color< colorData_t >::bicosineInterpolation(bottomLeftPixel, bottomRightPixel, topLeftPixel, topRightPixel, factorX, factorY);
			}

			/**
			 * @brief Returns a sampled pixel using the cubic algorithm.
			 * @tparam colorData_t The color data type.
			 * @param u The X coordinate of the pixel.
			 * @param v The Y coordinate of the pixel.
			 * @return Color< colorData_t >
			 */
			template< typename colorData_t = float, std::enable_if_t< std::is_floating_point_v< colorData_t >, bool > = false >
			[[nodiscard]]
			Color< colorData_t >
			cubicSample (float u, float v) const noexcept
			{
				if ( m_flags[UVWrappingEnabled] )
				{
					if ( u < 0.0F || u > 1.0F )
						u = std::fmod(std::abs(u), 1.0F);

					if ( v < 0.0F || v > 1.0F )
						v = std::fmod(std::abs(v), 1.0F);
				}
				else if ( u < 0.0F || u > 1.0F || v < 0.0F || v > 1.0F )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", incorrect parameters (U:" << u << ", V:" << v << ") !" << std::endl;

					return {};
				}

				/* Prepare variable for X axis */
				auto realX = static_cast< float >(m_width - 1) * u;
				auto loX = static_cast< size_t >(std::floor(realX));
				auto factorX = realX - loX;

				/* Prepare variable for Y axis */
				auto realY = static_cast< float >(m_height - 1) * v;
				auto loY = static_cast< size_t >(std::floor(realY));
				auto factorY = realY - loY;

				/* Gets involved pixels */
				auto p00 = this->clampedPixel(loX - 1, loY - 1);
				auto p10 = this->clampedPixel(loX + 0, loY - 1);
				auto p20 = this->clampedPixel(loX + 1, loY - 1);
				auto p30 = this->clampedPixel(loX + 2, loY - 1);

				auto p01 = this->clampedPixel(loX - 1, loY + 0);
				auto p11 = this->clampedPixel(loX + 0, loY + 0);
				auto p21 = this->clampedPixel(loX + 1, loY + 0);
				auto p31 = this->clampedPixel(loX + 2, loY + 0);

				auto p02 = this->clampedPixel(loX - 1, loY + 1);
				auto p12 = this->clampedPixel(loX + 0, loY + 1);
				auto p22 = this->clampedPixel(loX + 1, loY + 1);
				auto p32 = this->clampedPixel(loX + 2, loY + 1);

				auto p03 = this->clampedPixel(loX - 1, loY + 2);
				auto p13 = this->clampedPixel(loX + 0, loY + 2);
				auto p23 = this->clampedPixel(loX + 1, loY + 2);
				auto p33 = this->clampedPixel(loX + 2, loY + 2);

				/* Red component */
				auto red = Math::cubicInterpolation(
					Math::cubicInterpolation(p00.red(), p10.red(), p20.red(), p30.red(), factorX),
					Math::cubicInterpolation(p01.red(), p11.red(), p21.red(), p31.red(), factorX),
					Math::cubicInterpolation(p02.red(), p12.red(), p22.red(), p32.red(), factorX),
					Math::cubicInterpolation(p03.red(), p13.red(), p23.red(), p33.red(), factorX),
					factorY
				);

				/* Green component */
				auto green = Math::cubicInterpolation(
					Math::cubicInterpolation(p00.green(), p10.green(), p20.green(), p30.green(), factorX),
					Math::cubicInterpolation(p01.green(), p11.green(), p21.green(), p31.green(), factorX),
					Math::cubicInterpolation(p02.green(), p12.green(), p22.green(), p32.green(), factorX),
					Math::cubicInterpolation(p03.green(), p13.green(), p23.green(), p33.green(), factorX),
					factorY
				);

				/* Blue component */
				auto blue = Math::cubicInterpolation(
					Math::cubicInterpolation(p00.blue(), p10.blue(), p20.blue(), p30.blue(), factorX),
					Math::cubicInterpolation(p01.blue(), p11.blue(), p21.blue(), p31.blue(), factorX),
					Math::cubicInterpolation(p02.blue(), p12.blue(), p22.blue(), p32.blue(), factorX),
					Math::cubicInterpolation(p03.blue(), p13.blue(), p23.blue(), p33.blue(), factorX),
					factorY
				);

				/* Alpha component */
				auto alpha = Math::cubicInterpolation(
					Math::cubicInterpolation(p00.alpha(), p10.alpha(), p20.alpha(), p30.alpha(), factorX),
					Math::cubicInterpolation(p01.alpha(), p11.alpha(), p21.alpha(), p31.alpha(), factorX),
					Math::cubicInterpolation(p02.alpha(), p12.alpha(), p22.alpha(), p32.alpha(), factorX),
					Math::cubicInterpolation(p03.alpha(), p13.alpha(), p23.alpha(), p33.alpha(), factorX),
					factorY
				);

				return {red, green, blue, alpha};
			}

			/**
			 * @brief Sets a pixel sub-element.
			 * @param x The X coordinate of the pixel.
			 * @param y The Y coordinate of the pixel.
			 * @param channel The pixmap channel targeted.
			 * @param value The new value.
			 */
			void
			setPixelElement (size_t x, size_t y, Channel channel, data_t value) noexcept
			{
				auto index = this->getBufferIndex(x, y) + static_cast< size_t >(channel);

				if ( index >= m_data.size() )
					return;

				m_data[index] = value;

				this->setPixelAsUpdated(x, y);
			}

			/**
			 * @brief Returns a pixel sub-element.
			 * @param x The X coordinate of the pixel.
			 * @param y The Y coordinate of the pixel.
			 * @param channel The pixmap channel targeted.
			 * @return type_t
			 */
			[[nodiscard]]
			data_t
			pixelElement (size_t x, size_t y, Channel channel) const noexcept
			{
				auto index = this->getBufferIndex(x, y) + static_cast< size_t >(channel);

				if ( index >= m_data.size() )
					return 0;

				return m_data[index];
			}

			/**
			 * @brief Returns whether the pixmap is gray scale.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isGrayScale () const noexcept
			{
				return m_channelMode == ChannelMode::Grayscale;
			}

			/**
			 * @brief Returns whether the pixmap has a alpha channel.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			hasAlphaChannel () const noexcept
			{
				if ( m_channelMode == ChannelMode::GrayscaleAlpha )
					return true;

				if ( m_channelMode == ChannelMode::RGBA )
					return true;

				return false;
			}

			/**
			 * @brief Returns the average color of the pixmap.
			 * @tparam colorData_t The color data type.
			 * @return Color< colorData_t >
			 */
			template< typename colorData_t = float, std::enable_if_t< std::is_floating_point_v< colorData_t >, bool > = false >
			[[nodiscard]]
			Color< colorData_t >
			averageColor () const noexcept
			{
				if ( !this->isValid() )
					return {};

				const auto limit = this->pixelCount();
				const auto stride = this->colorCount();
				const auto dataLimit = m_data.size();

				switch ( m_channelMode )
				{
					case ChannelMode::Grayscale :
					case ChannelMode::GrayscaleAlpha :
						if constexpr ( std::is_floating_point_v< data_t > )
						{
							data_t maxValue = 0;

							for ( size_t index = 0; index < dataLimit; index += stride )
								maxValue += m_data[index];

							const auto value = static_cast< colorData_t >(maxValue / limit);

							return {value, value, value};
						}
						else
						{
							size_t maxValue = 0;

							for ( size_t index = 0; index < dataLimit; index += stride )
								maxValue += m_data[index];

							const auto value = static_cast< data_t >(std::floor(maxValue / limit));

							return ColorFromInteger(value, value, value);
						}
						break;

					case ChannelMode::RGB :
					case ChannelMode::RGBA :
						if constexpr ( std::is_floating_point_v< data_t > )
						{
							data_t maxR = 0;
							data_t maxG = 0;
							data_t maxB = 0;

							for ( size_t index = 0; index < dataLimit; index += stride )
							{
								maxR += m_data[index];
								maxG += m_data[index+1];
								maxB += m_data[index+2];
							}

							return {
								static_cast< colorData_t >(maxR / limit),
								static_cast< colorData_t >(maxG / limit),
								static_cast< colorData_t >(maxB / limit)
							};
						}
						else
						{
							size_t maxR = 0;
							size_t maxG = 0;
							size_t maxB = 0;

							for ( size_t index = 0; index < dataLimit; index += stride )
							{
								maxR += m_data[index];
								maxG += m_data[index+1];
								maxB += m_data[index+2];
							}

							return ColorFromInteger(
								static_cast< data_t >(std::floor(maxR / limit)),
								static_cast< data_t >(std::floor(maxG / limit)),
								static_cast< data_t >(std::floor(maxB / limit))
							);
						}
						break;
				}

				return {};
			}

			/**
			 * @brief Enables the updated region marker. This feature will keep an Area object that hold every update made to the pixmap.
			 * @param state The state.
			 */
			void
			enableUpdatedRegion (bool state) noexcept
			{
				m_flags[UpdatedRegionMarkerEnabled] = state;
			}

			/**
			 * @brief Returns whether the updated region marker is active.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			updatedRegionEnabled () const noexcept
			{
				return m_flags[UpdatedRegionMarkerEnabled];
			}

			/**
			 * @brief Returns the Area where every modification were lastly done on the Pixmap.
			 * @return const Area &
			 */
			[[nodiscard]]
			const Area< size_t > &
			updatedRegion () const noexcept
			{
				return m_lastUpdatedRegion;
			}

			/**
			 * @brief Marks a pixel updated in the pixmap.
			 * @param x The X coordinate of the pixel.
			 * @param y The Y coordinate of the pixel.
			 */
			void
			setPixelAsUpdated (size_t x, size_t y) noexcept
			{
				if ( !m_flags[UpdatedRegionMarkerEnabled] )
					return;

				if ( m_lastUpdatedRegion.isValid() )
				{
					/* Checks on X axis */
					if ( x < m_lastUpdatedRegion.offsetX() )
					{
						m_lastUpdatedRegion.setOffsetX(x);
						m_lastUpdatedRegion.modifyWidthBy(m_lastUpdatedRegion.offsetX() - x);
					}

					if ( x > m_lastUpdatedRegion.offsetXb() )
						m_lastUpdatedRegion.setWidth((x - m_lastUpdatedRegion.offsetX()) + 1);

					/* Checks on Y axis */
					if ( y < m_lastUpdatedRegion.offsetY() )
					{
						m_lastUpdatedRegion.setOffsetY(y);
						m_lastUpdatedRegion.modifyHeightBy(m_lastUpdatedRegion.offsetY() - y);
					}

					if ( y > m_lastUpdatedRegion.offsetYb() )
						m_lastUpdatedRegion.setHeight((y - m_lastUpdatedRegion.offsetY()) + 1);
				}
				else
				{
					m_lastUpdatedRegion = {x, y, 1U, 1U};
				}
			}

			/**
			 * @brief Marks a region updated in the pixmap.
			 * @param area A reference to the region.
			 * @return void
			 */
			void
			setRegionAsUpdated (const Area< size_t > & area) noexcept
			{
				if ( !m_flags[UpdatedRegionMarkerEnabled] )
					return;

				m_lastUpdatedRegion = Area< size_t >::merge(m_lastUpdatedRegion, area);
			}

			/**
			 * @brief Sets the whole pixmap as updated.
			 * @return void
			 */
			void
			setOverallUpdated () noexcept
			{
				if ( !m_flags[UpdatedRegionMarkerEnabled] )
					return;

				m_lastUpdatedRegion.setOffsetX(0);
				m_lastUpdatedRegion.setOffsetY(0);
				m_lastUpdatedRegion.setWidth(m_width);
				m_lastUpdatedRegion.setHeight(m_height);
			}

			/**
			 * @brief Reset the Area marker for updated region.
			 * @return void
			 */
			void
			resetUpdatedRegion () noexcept
			{
				m_lastUpdatedRegion.reset();
			}

			/**
			 * @brief Draws the updated region on the pixmap.
			 * @note This is mostly for debug purposes.
			 * @tparam colorData_t The color data type.
			 * @param color A reference to the color of the updated region.
			 * @return void
			 */
			template< typename colorData_t = float, std::enable_if_t< std::is_floating_point_v< colorData_t >, bool > = false >
			void
			showUpdatedRegion (const Color< colorData_t > & color) noexcept
			{
				/* Retain old marker state */
				const auto oldState = m_flags[UpdatedRegionMarkerEnabled];

				/* Disables it */
				this->enableUpdatedRegion(false);

				/* Draw the square on the region */
				this->drawSquare(m_lastUpdatedRegion, color, DrawPixelMode::Replace);

				/* Sets the old state */
				this->enableUpdatedRegion(oldState);
			}

			/**
			 * @brief Adds alpha channel.
			 * @param alphaValue The initial alpha value.
			 * @param modifyUpdatedRegion Set the updated region. Default true.
			 * @return bool
			 */
			bool
			addAlphaChannel (data_t alphaValue, bool modifyUpdatedRegion = true) noexcept
			{
				if ( !this->isValid() )
					return false;

				switch ( m_channelMode )
				{
					case ChannelMode::GrayscaleAlpha :
					case ChannelMode::RGBA :
						return true;

					case ChannelMode::Grayscale :
					{
						const auto copy = m_data;

						if ( !this->initialize(m_width, m_height, ChannelMode::GrayscaleAlpha) )
							return false;

						const auto limit = this->pixelCount();

						size_t dstIndex = 0;

						for ( size_t index = 0; index < limit; index++ )
						{
							m_data[dstIndex++] = copy[index];
							m_data[dstIndex++] = alphaValue;
						}
					}

					case ChannelMode::RGB :
					{
						const auto copy = m_data;

						if ( !this->initialize(m_width, m_height, ChannelMode::RGBA) )
							return false;

						const auto limit = this->pixelCount();

						size_t srcIndex = 0;
						size_t dstIndex = 0;

						for ( size_t index = 0; index < limit; index++ )
						{
							m_data[dstIndex++] = copy[srcIndex++];
							m_data[dstIndex++] = copy[srcIndex++];
							m_data[dstIndex++] = copy[srcIndex++];
							m_data[dstIndex++] = alphaValue;
						}
					}
				}

				if ( modifyUpdatedRegion )
					this->setOverallUpdated();

				return true;
			}

			/**
			 * @brief Fills the pixmap with a single value.
			 * @note This will ignore the alpha value.
			 * @param value The value.
			 * @return bool
			 */
			bool
			fill (data_t value) noexcept
			{
				if ( !this->isValid() )
					return false;

				switch ( m_channelMode )
				{
					case ChannelMode::Grayscale :
					case ChannelMode::RGB :
						std::memset(m_data.data(), value, m_data.size() * sizeof(data_t));
						break;

					case ChannelMode::GrayscaleAlpha :
					{
						const auto limit = this->elementCount();

						for ( size_t index = 0; index < limit; index += 2 )
							m_data[index] = value;
					}
						break;

					case ChannelMode::RGBA :
					{
						const auto limit = this->elementCount();

						for ( size_t index = 0; index < limit; index += 4 )
						{
							m_data[index] = value;
							m_data[index+1] = value;
							m_data[index+2] = value;
						}
					}
						break;
				}

				this->setOverallUpdated();

				return true;
			}

			/**
			 * @brief Fills the pixmap with raw data.
			 * @note This will ignore the alpha value.
			 * @param data A raw pointer to data.
			 * @param size The size of the data.
			 * @return bool
			 */
			bool
			fill (const data_t * data, size_t size) noexcept
			{
				if ( !this->isValid() )
					return false;

				switch ( m_channelMode )
				{
					case ChannelMode::Grayscale :
					case ChannelMode::RGB :
						if ( size >= m_data.size() )
						{
							std::memcpy(m_data.data(), data, m_data.size());
						}
						else
						{
							const auto loopLimit = std::ceil(m_data.size() / size);
							const auto remain = m_data.size() % size;

							for ( size_t loopIndex = 0; loopIndex < loopLimit; loopIndex++ )
							{
								const auto shift = loopIndex * size;

								std::memcpy(m_data.data() + shift, data + shift, loopIndex + 1 == loopLimit ? remain : size);
							}
						}
						break;

					case ChannelMode::GrayscaleAlpha :
					{
						const auto limit = this->elementCount();

						size_t offset = 0;

						for ( size_t index = 0; index < limit; index += 2 )
						{
							m_data[index] = data[offset++];

							if ( offset >= size )
								offset = 0;
						}
					}
						break;

					case ChannelMode::RGBA :
					{
						const auto limit = this->elementCount();

						size_t offset = 0;

						for ( size_t index = 0; index < limit; index += 4 )
						{
							m_data[index] = data[offset++];

							if ( offset >= size )
								offset = 0;

							m_data[index+1] = data[offset++];

							if ( offset >= size )
								offset = 0;

							m_data[index+2] = data[offset++];

							if ( offset >= size )
								offset = 0;
						}
					}
						break;
				}

				this->setOverallUpdated();

				return true;
			}

			/**
			 * @brief Fills the pixmap with a pattern of data.
			 * @note This will ignore the alpha value.
			 * @param vector A reference to a vector.
			 * @return bool
			 */
			bool
			fill (const std::vector< data_t > & vector) noexcept
			{
				return this->fill(vector.data(), vector.size());
			}

			/**
			 * @brief Fills the pixmap with a color.
			 * @tparam colorData_t The color data type.
			 * @param color A reference to a color.
			 * @return bool
			 */
			template< typename colorData_t = float, std::enable_if_t< std::is_floating_point_v< colorData_t >, bool > = false >
			bool
			fill (const Color< colorData_t > & color) noexcept
			{
				if ( !this->isValid() )
					return false;

				const auto limit = this->pixelCount();

				for ( size_t index = 0; index < limit; index++ )
					this->setPixel(index, color);

				this->setOverallUpdated();

				return true;
			}

			/**
			 * @brief Fills the pixmap with a pattern.
			 * @param pattern A reference to a pixmap.
			 * @return bool
			 */
			bool
			fill (const Pixmap & pattern) noexcept
			{
				if ( !this->isValid() )
					return false;

				/* FIXME: Complete the method... */

				this->setOverallUpdated();

				return true;
			}

			/**
			 * @brief Fills the pixmap with a gradient.
			 * @tparam colorData_t The color data type.
			 * @param gradient A reference to a gradient.
			 * @param starts A reference to a vector to starts the gradient.
			 * @param ends A reference to a vector to ends the gradient.
			 * @return bool
			 */
			template< typename colorData_t = float, std::enable_if_t< std::is_floating_point_v< colorData_t >, bool > = false >
			bool
			fill (const Gradient< colorData_t , colorData_t > & gradient, const Math::Vector< 2, int > & starts, const Math::Vector< 2, int > & ends) noexcept
			{
				if ( !this->isValid() )
					return false;

				/* FIXME: Complete the method... */

				this->setOverallUpdated();

				return true;
			}

			/**
			 * @brief Fills the pixmap channel with a single value.
			 * @param channel The targeted channel of the pixmap.
			 * @param value The value.
			 * @return bool
			 */
			bool
			fillChannel (Channel channel, data_t value) noexcept
			{
				if ( !this->isValid() )
					return false;

				const auto channelIndex = static_cast< size_t >(channel);

				if ( channelIndex >= this->colorCount() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", bad channel index !" << std::endl;

					return false;
				}

				if ( m_channelMode == ChannelMode::Grayscale )
				{
					std::memset(m_data.data(), value, m_data.size() * sizeof(data_t));

					return true;
				}

				const auto stride = this->elementCount();
				const auto limit = this->colorCount();

				for ( size_t index = 0; index < limit; index += stride )
					m_data[index + channelIndex] = value;

				this->setOverallUpdated();

				return true;
			}

			/**
			 * @brief Fills the pixmap channel with a pattern of data.
			 * @param channel The targeted channel of the pixmap.
			 * @param data A raw pointer to data.
			 * @param size The size of the data.
			 * @return bool
			 */
			bool
			fillChannel (Channel channel, const data_t * data, size_t size) noexcept
			{
				if ( !this->isValid() )
					return false;

				const auto channelIndex = static_cast< size_t >(channel);

				if ( channelIndex >= this->colorCount() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", bad channel index !" << std::endl;

					return false;
				}

				if ( m_channelMode == ChannelMode::Grayscale )
					return this->fill(data, size);

				const auto limit = this->elementCount();
				const auto stride = this->colorCount();

				size_t offset = 0;

				for ( size_t index = 0; index < limit; index += stride )
				{
					m_data[index + channelIndex] = data[offset++];

					if ( offset >= size )
						offset = 0;
				}

				this->setOverallUpdated();

				return true;
			}

			/**
			 * @brief Fills the pixmap channel with a pattern of data.
			 * @param channel The targeted channel of the pixmap.
			 * @param vector A reference to a vector.
			 * @return bool
			 */
			bool
			fillChannel (Channel channel, const std::vector< data_t > & vector) noexcept
			{
				return this->fillChannel(channel, vector.data(), vector.size());
			}

			/**
			 * @brief Fills the pixmap channel with a pattern.
			 * @param channel The targeted channel of the pixmap.
			 * @param pattern A reference to a pixmap.
			 * @return bool
			 */
			bool
			fillChannel (Channel channel, const Pixmap & pattern) noexcept
			{
				if ( !this->isValid() )
					return false;

				const auto channelIndex = static_cast< size_t >(channel);

				if ( channelIndex >= this->colorCount() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", bad channel index !" << std::endl;

					return false;
				}

				/* FIXME: Complet the method. */

				this->setOverallUpdated();

				return true;
			}

			/**
			 * @brief Fills the pixmap channel with a gradient.
			 * @tparam colorData_t The color data type.
			 * @param channel The targeted channel of the pixmap.
			 * @param gradient A reference to a gradient.
			 * @param starts A reference to a vector to starts the gradient.
			 * @param ends A reference to a vector to ends the gradient.
			 * @return bool
			 */
			template< typename colorData_t = float, std::enable_if_t< std::is_floating_point_v< colorData_t >, bool > = false >
			bool
			fillChannel (Channel channel, const Gradient< colorData_t, colorData_t > & gradient, const Math::Vector< 2, int > & starts, const Math::Vector< 2, int > & ends) noexcept
			{
				if ( !this->isValid() )
					return false;

				/* FIXME: Complete the method... */

				this->setOverallUpdated();

				return true;
			}

			/**
			 * @brief Sets data to zero.
			 * @return void
			 */
			void
			zeroFill () noexcept
			{
				if ( !this->isValid() )
					return;

				/* NOTE : C++ std::fill(myarray, myarray+N, 0); */
				//std::fill(m_data.begin(), m_data.end(), 0);
				std::memset(m_data.data(), 0, m_data.size() * sizeof(data_t));

				this->setOverallUpdated();
			}

			/**
			 * @brief Fills the pixmap with a basic noise.
			 * @return bool
			 */
			bool
			noise () noexcept
			{
				if ( !this->isValid() )
					return false;

				std::srand(unsigned(std::time(nullptr)));

				std::vector< data_t > pixelData;

				switch ( m_channelMode )
				{
					case ChannelMode::Grayscale :
					case ChannelMode::GrayscaleAlpha :
						pixelData.resize(m_width * m_height);
						break;

					case ChannelMode::RGB :
					case ChannelMode::RGBA :
						pixelData.resize(m_width * m_height * 3);
						break;
				}

				std::generate(pixelData.begin(), pixelData.end(), std::rand);

				return this->fill(pixelData);
			}

			/**
			 * @brief Fills the pixmap with a basic noise.
			 * @param scale The perlin noise scale factore.
			 * @param grayNoise Generatore only gray. Default false.
			 * @return bool
			 */
			bool
			perlinNoise (float scale, bool grayNoise = false) noexcept
			{
				if ( !this->isValid() )
					return false;

				const auto limit = this->pixelCount();
				const auto stride = this->colorCount();

				switch ( m_channelMode )
				{
					case ChannelMode::Grayscale :
					case ChannelMode::GrayscaleAlpha :
					{
						PerlinNoise< float > generator{Utility::trueRandom(0U, std::numeric_limits< unsigned int >::max())};

						for ( size_t index = 0; index < limit; ++index )
						{
							const auto offset = index * stride;

							m_data[offset] = generator.generate8bits(this->u(index) * scale, this->v(index) * scale);
						}
					}
						break;

					case ChannelMode::RGB :
					case ChannelMode::RGBA :
						if ( grayNoise )
						{
							PerlinNoise< float > generator{Utility::trueRandom(0U, std::numeric_limits< unsigned int >::max())};

							for ( size_t index = 0; index < limit; ++index )
							{
								const auto offset = index * stride;
								const auto value = generator.generate8bits(this->u(index) * scale, this->v(index) * scale);

								m_data[offset] = value;
								m_data[offset+1] = value;
								m_data[offset+2] = value;
							}
						}
						else
						{
							PerlinNoise< float > redGenerator{Utility::trueRandom(0U, std::numeric_limits< unsigned int >::max())};
							PerlinNoise< float > greenGenerator{Utility::trueRandom(0U, std::numeric_limits< unsigned int >::max())};
							PerlinNoise< float > blueGenerator{Utility::trueRandom(0U, std::numeric_limits< unsigned int >::max())};

							for ( size_t index = 0; index < limit; ++index )
							{
								const auto offset = index * stride;
								const auto uCoord = this->u(index) * scale;
								const auto vCoord = this->v(index) * scale;

								m_data[offset] = redGenerator.generate8bits(uCoord, vCoord);
								m_data[offset+1] = greenGenerator.generate8bits(uCoord, vCoord);
								m_data[offset+2] = blueGenerator.generate8bits(uCoord, vCoord);
							}
						}
						break;
				}

				this->setOverallUpdated();

				return true;
			}

			/**
			 * @brief Applies a function on every pixel.
			 * @tparam colorData_t The color data type.
			 * @param method A reference to a function to modify the pixel.
			 * @return void
			 */
			template< typename colorData_t = float, std::enable_if_t< std::is_floating_point_v< colorData_t >, bool > = false >
			void
			forEachPixel (const std::function< Color< colorData_t > (Color< colorData_t >) > & method) noexcept
			{
				const auto limit = this->pixelCount();

				for ( size_t index = 0; index < limit; index++ )
					this->setPixel(index, method(this->pixel(index)));
			}

			/**
			 * @brief Performs Floyd–Steinberg dithering.
			 * @warning Faulty !
			 * @tparam colorData_t The color data type.
			 * @param colorCount The desired color count.
			 * @return void
			 */
			template< typename colorData_t = float, std::enable_if_t< std::is_floating_point_v< colorData_t >, bool > = false >
			void
			dither (unsigned int colorCount) noexcept
			{
				for ( size_t indexY = 0; indexY < m_height; indexY++ )
				{
					for ( size_t indexX = 0; indexX < m_width; indexX++ )
					{
						auto index = this->pixelIndex(indexX, indexY);

						const auto red = m_data[index];
						const auto green = m_data[index+1];
						const auto blue = m_data[index+2];

						m_data[index] = Color< colorData_t >::clamp(red / colorCount);
						m_data[index+1] = Color< colorData_t >::clamp(green / colorCount);
						m_data[index+2] = Color< colorData_t >::clamp(blue / colorCount);

						const auto redError = red - m_data[index];
						const auto greenError = green - m_data[index+1];
						const auto blueError = blue - m_data[index+2];

						if ( indexX + 1 < m_width )
						{
							index = this->pixelIndex(indexX + 1, indexY);

							m_data[index] += Color< colorData_t >::clamp((redError * 7) / 16);
							m_data[index+1] += Color< colorData_t >::clamp((greenError * 7) / 16);
							m_data[index+2] += Color< colorData_t >::clamp((blueError * 7) / 16);
						}

						if ( indexX > 0 && indexY + 1 < m_height )
						{
							index = this->pixelIndex(indexX - 1, indexY + 1);

							m_data[index] += Color< colorData_t >::clamp((redError * 3) / 16);
							m_data[index+1] += Color< colorData_t >::clamp((greenError * 3) / 16);
							m_data[index+2] += Color< colorData_t >::clamp((blueError * 3) / 16);
						}

						if ( indexY + 1 < m_height )
						{
							index = this->pixelIndex(indexX, indexY + 1);

							m_data[index] += Color< colorData_t >::clamp((redError * 5) / 16);
							m_data[index+1] += Color< colorData_t >::clamp((greenError * 5) / 16);
							m_data[index+2] += Color< colorData_t >::clamp((blueError * 5) / 16);
						}

						if ( indexX + 1 < m_width && indexY + 1 < m_height )
						{
							index = this->pixelIndex(indexX + 1, indexY + 1);

							m_data[index] += Color< colorData_t >::clamp((redError * 1) / 16);
							m_data[index+1] += Color< colorData_t >::clamp((greenError * 1) / 16);
							m_data[index+2] += Color< colorData_t >::clamp((blueError * 1) / 16);
						}
					}
				}

				this->setOverallUpdated();
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return ostream &
			 */
			friend
			std::ostream &
			operator<< (std::ostream & out, const Pixmap & obj)
			{
				out <<
					"Pixmap data :\n"
					"Width : " << obj.m_width << "\n"
					"Height : " << obj.m_height << '\n';

				switch ( obj.colorCount() )
				{
					case 1 :
						out << "Channels count : 1 (Grayscale)\n";
						break;

					case 2 :
						out << "Channels count : 2 (GrayscaleAlpha)\n";
						break;

					case 3 :
						out << "Channels count : 3 (RGB)\n";
						break;

					case 4 :
						out << "Channels count : 4 (RGBA)\n";
						break;
				}

				out <<
					"Pixel count : " << obj.pixelCount() << "\n"
					"Pixel size : " << obj.bytePerPixel() << " bytes (" << obj.bitPerPixel() << " bit)\n"
					"Element count : " << obj.elementCount() << "\n"
					"Data size : " << obj.bytes() << " bytes\n";

				return out;
			}

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend
			std::string
			to_string (const Pixmap & obj) noexcept
			{
				return (std::stringstream{} << obj).str();
			}

		private:

			/* Flag names. */
			static constexpr auto UVWrappingEnabled = 0UL;
			static constexpr auto UpdatedRegionMarkerEnabled = 1UL;

			/**
			 * @brief Returns the zero value for this pixmap component.
			 * @return type_t
			 */
			[[nodiscard]]
			static
			data_t
			zero () noexcept
			{
				return 0;
			}

			/**
			 * @brief Returns the one value for this pixmap component.
			 * @return type_t
			 */
			[[nodiscard]]
			static
			data_t
			one () noexcept
			{
				if constexpr ( std::is_floating_point_v< data_t > )
					return 1;
				else
					return std::numeric_limits< data_t >::max();
			}

			/**
			 * @brief Takes care of initialize alpha channel to 1.
			 * @return void
			 */
			void
			initAlphaChannel () noexcept
			{
				switch ( m_channelMode )
				{
					case ChannelMode::RGBA :
						this->fillChannel(Channel::Alpha, Pixmap::one());
						break;

					case ChannelMode::GrayscaleAlpha :
						this->fillChannel(Channel::Green, Pixmap::one());
						break;

					default:
						break;
				}
			}

			size_t m_width{0};
			size_t m_height{0};
			ChannelMode m_channelMode{ChannelMode::RGB};
			std::vector< data_t > m_data{};
			Area< size_t > m_lastUpdatedRegion{};
			std::array< bool, 8 > m_flags{
				true/*UVWrappingEnabled*/,
				true/*UpdatedRegionMarkerEnabled*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};

	/**
	 * @brief dataConversion
	 * @param input A reference to input pixmap.
	 * @return Pixmap< output_t >
	 */
	template<
		typename output_t,
		typename input_t,
		std::enable_if_t< std::is_arithmetic_v< output_t >, bool > = false,
		std::enable_if_t< std::is_arithmetic_v< input_t >, bool > = false
	>
	[[nodiscard]]
	Pixmap< output_t >
	dataConversion (const Pixmap< input_t > & input) noexcept
	{
		Pixmap< output_t > output{input.width(), input.height(), input.channelMode()};

#ifdef DEBUG_PIXEL_FACTORY
		std::cout << "Pixmap data conversion : " << typeid(input_t).name() << " (" << sizeof(input_t) << " bytes) to " << typeid(output_t).name() << " (" << sizeof(output_t) << " bytes) !" << std::endl;
#endif

		const auto & inputData = input.data();
		auto & outputData = output.data();

		for ( size_t index = 0; index < inputData.size(); index++ )
		{
			if constexpr ( std::is_floating_point_v< input_t > )
			{
				/* float -> float */
				if constexpr ( std::is_floating_point_v< output_t > )
				{
					outputData[index] = static_cast< output_t >(inputData[index]);
				}
				/* float -> integer */
				else
				{
					outputData[index] = static_cast< output_t >(std::round(inputData[index] * std::numeric_limits< output_t >::max()));
				}
			}
			else
			{
				/* integer -> float */
				if constexpr ( std::is_floating_point_v< output_t > )
				{
					outputData[index] = static_cast< output_t >(inputData[index]) / static_cast< output_t >(std::numeric_limits< input_t >::max());
				}
				/* integer -> integer */
				else
				{
					const auto ratio = static_cast< float >(std::numeric_limits< output_t >::max()) / static_cast< float >(std::numeric_limits< input_t >::max());

					outputData[index] = static_cast< output_t >(std::round(ratio * inputData[index]));
				}
			}
		}

		return output;
	}
}
