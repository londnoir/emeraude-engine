/*
 * src/Libraries/PixelFactory/Pixmap.hpp
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
#include <array>
#include <cmath>
#include <cstdint>
#include <cstdlib> // std::rand(), std::srand()
#include <cstring>
#include <ctime>
#include <functional>
#include <iostream>
#include <limits>
#include <string>
#include <type_traits>
#include <vector>

/* Local inclusions for usage. */
#include "Libraries/Algorithms/PerlinNoise.hpp"
#include "Libraries/Utility.hpp"
#include "Area.hpp"
#include "Color.hpp"
#include "Gradient.hpp"
#include "Types.hpp"

namespace Libraries::PixelFactory
{
	/** @brief RGB + alpha color mode. */
	static constexpr auto RGBA{4UL};
	/** @brief RGB color mode. */
	static constexpr auto RGB{3UL};
	/** @brief Grayscale + alpha color mode. */
	static constexpr auto GrayscaleAlpha{2UL};
	/** @brief Grayscale color mode. */
	static constexpr auto Grayscale{1UL};
	/** @brief 72dpi resolution. */
	static constexpr auto Resolution72DPI{2835UL};
	/** @brief 96dpi resolution. */
	static constexpr auto Resolution96DPI{3780UL};

	/**
	 * @brief Defines a structure to store pixels to make an image.
	 * @tparam precision_t The type of number for pixmap precision. Default uint8_t.
	 */
	template< typename precision_t = uint8_t >
	requires (std::is_arithmetic_v< precision_t >)
	class Pixmap
	{
		public:

			/**
			 * @brief The image compression format enumeration.
			 */
			enum class Format : uint8_t
			{
				None,
				Targa, /* No compression */
				PNG, /* Loss-less compression */
				Jpeg /* Destructive compression */
			};

			/**
			 * @brief Constructs a default pixmap.
			 * @note The channel mode will be set to RGB.
			 */
			Pixmap () noexcept = default;

			/**
			 * @brief Constructs a new pixmap.
			 * @param width The initial width of the pixmap.
			 * @param height The initial height of the pixmap.
			 * @param channelMode The number of color as a class constant. Default ChannelMode::RGB.
			 */
			Pixmap (size_t width, size_t height, ChannelMode channelMode = ChannelMode::RGB) noexcept
				: m_width(width), m_height(height), m_channelMode(channelMode)
			{
				m_data.resize(this->elementCount(), 0);

				if ( !this->initAlphaChannel() )
				{
					std::cerr << "Pixmap::Pixmap(" << width << ", " << height << ", " << static_cast< int >(channelMode) << ") : Unable to check alpha channel initialization !" "\n";
				}
			}

			/**
			 * @brief Constructs a new pixmap initialized with a designed color.
			 * @tparam color_data_t The color data type.
			 * @param width The initial width of the pixmap.
			 * @param height The initial height of the pixmap.
			 * @param channelMode The number of color as a class constant.
			 * @param color A reference to a color.
			 */
			template< typename color_data_t = float >
			Pixmap (size_t width, size_t height, ChannelMode channelMode, const Color< color_data_t > & color) noexcept requires (std::is_floating_point_v< color_data_t >)
				: m_width(width), m_height(height), m_channelMode(channelMode)
			{
				m_data.resize(this->elementCount(), 0);

				if ( !this->fill(color) )
				{
					std::cerr << "Pixmap::Pixmap(" << width << ", " << height << ", " << static_cast< int >(channelMode) << ", " << color << ") : Unable to initialize color !" "\n";
				}
			}

			/**
			 * @brief Initializes pixmap data.
			 * @param width The initial width of the pixmap.
			 * @param height The initial height of the pixmap.
			 * @param channelMode The number of color as a class constant. Default RGB.
			 * @return bool
			 */
			bool
			initialize (size_t width, size_t height, ChannelMode channelMode = ChannelMode::RGB) noexcept
			{
				if ( width == 0 || height == 0 )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", invalid pixmap dimensions !" "\n";

					return false;
				}

				m_width = width;
				m_height = height;
				m_channelMode = channelMode;
				m_data.resize(this->elementCount(), 0);

				return this->initAlphaChannel();
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
			 * @brief Returns wheter the data is non-empty and dimension valid.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isValid () const noexcept
			{
				if ( m_width == 0 || m_height == 0 )
				{
					return false;
				}

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
			 * @brief Returns an area corresponding to the pixmap.
			 * @note Offset parameter is added to the size of the pixmap.
			 * @param offsetX Set an offset in X to the area. Default 0.
			 * @param offsetY Set an offset in Y to the area. Default 0.
			 * @return Area< size_t >
			 */
			[[nodiscard]]
			Area< size_t >
			area (size_t offsetX = 0, size_t offsetY = 0) const noexcept
			{
				return {offsetX, offsetY, m_width, m_height};
			}

			/**
			 * @brief Returns whether the pixmap dimensions are a power of two.
			 * @note Useful for GPU concerns.
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
			 * @note WIDTH * HEIGHT * COLOR COUNT
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
			 * @note WIDTH * HEIGHT * COLOR COUNT * PRECISION
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			bytes () const noexcept
			{
				return m_data.size() * sizeof(precision_t);
			}

			/**
			 * @brief Returns the size of a pixel in bytes.
			 * @note COLOR COUNT * PRECISION
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			bytePerPixel () const noexcept
			{
				return this->colorCount() * sizeof(precision_t);
			}

			/**
			 * @brief Returns the size of a pixel in bits.
			 * @note COLOR COUNT * PRECISION * 8
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
			 * @note WIDTH * COLOR COUNT * PRECISION
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			pitch () const noexcept
			{
				return m_width * this->colorCount() * sizeof(precision_t);
			}

			/**
			 * @brief Returns read-only access to raw data of the pixmap.
			 * @return const std::vector< data_t > &
			 */
			const std::vector< precision_t > &
			data () const noexcept
			{
				return m_data;
			}

			/**
			 * @brief Returns a write access to raw data of the pixmap.
			 * @return std::vector< data_t > &
			 */
			std::vector< precision_t > &
			data () noexcept
			{
				return m_data;
			}

			/**
			 * @brief Returns a read-only pointer of the first element of a row.
			 * @tparam enable_boundary_check_v Enable the boundary check and set a valid value. Default true.
			 * @param rowIndex The index of the row.
			 * @return const type_t *
			 */
			template< bool enable_boundary_check_v = true >
			[[nodiscard]]
			const precision_t *
			rowPointer (size_t rowIndex) const noexcept
			{
				if constexpr ( enable_boundary_check_v )
				{
					if ( rowIndex >= m_height )
					{
						std::cerr << __PRETTY_FUNCTION__ << ", row index overflow !" "\n";

						rowIndex = m_height - 1;
					}
				}

				return m_data.data() + (rowIndex * this->pitch());
			}

			/**
			 * @brief Returns the pointer of the first element of a row.
			 * @tparam enable_boundary_check_v Enable the boundary check and set a valid value. Default true.
			 * @param rowIndex The index of the row.
			 * @return type_t *
			 */
			template< bool enable_boundary_check_v = true >
			[[nodiscard]]
			precision_t *
			rowPointer (size_t rowIndex) noexcept
			{
				if constexpr ( enable_boundary_check_v )
				{
					if ( rowIndex >= m_height )
					{
						std::cerr << __PRETTY_FUNCTION__ << ", row index overflow !" "\n";

						rowIndex = m_height - 1;
					}
				}

				return m_data.data() + (rowIndex * this->pitch());
			}

			/**
			 * @brief Returns a raw pixel pointer.
			 * @tparam enable_boundary_check_v Enable the boundary check and set a valid value. Default true.
			 * @param pixelIndex The index of the pixel.
			 * @return const type_t *
			 */
			template< bool enable_boundary_check_v = true >
			[[nodiscard]]
			const precision_t *
			pixelPointer (size_t pixelIndex) const noexcept
			{
				if constexpr ( enable_boundary_check_v )
				{
					this->clampPixelIndex(pixelIndex);
				}

				return m_data.data() + (pixelIndex * this->colorCount());
			}

			/**
			 * @brief Returns a raw pixel pointer.
			 * @tparam enable_boundary_check_v Enable the boundary check and set a valid value. Default true.
			 * @param pixelIndex The index of the pixel.
			 * @return const type_t *
			 */
			template< bool enable_boundary_check_v = true >
			[[nodiscard]]
			precision_t *
			pixelPointer (size_t pixelIndex) noexcept
			{
				if constexpr ( enable_boundary_check_v )
				{
					this->clampPixelIndex(pixelIndex);
				}

				return m_data.data() + (pixelIndex * this->colorCount());
			}

			/**
			 * @brief Returns a raw pixel pointer.
			 * @tparam enable_boundary_check_v Enable the boundary check and set a valid value. Default true.
			 * @param coordX The X coordinate of the pixel.
			 * @param coordY The Y coordinate of the pixel.
			 * @return const type_t *
			 */
			template< bool enable_boundary_check_v = true >
			[[nodiscard]]
			const precision_t *
			pixelPointer (size_t coordX, size_t coordY) const noexcept
			{
				if constexpr ( enable_boundary_check_v )
				{
					this->clampPixelCoords(coordX, coordY);
				}

				/* NOTE: Boundary check already done. */
				return this->pixelPointer< false >(this->pixelIndex< false >(coordX, coordY));
			}

			/**
			 * @brief Returns a raw pixel pointer.
			 * @tparam enable_boundary_check_v Enable the boundary check and set a valid value. Default true.
			 * @param coordX The X coordinate of the pixel.
			 * @param coordY The Y coordinate of the pixel.
			 * @return const type_t *
			 */
			template< bool enable_boundary_check_v = true >
			[[nodiscard]]
			precision_t *
			pixelPointer (size_t coordX, size_t coordY) noexcept
			{
				if constexpr ( enable_boundary_check_v )
				{
					this->clampPixelCoords(coordX, coordY);
				}

				/* NOTE: Boundary check already done. */
				return this->pixelPointer< false >(this->pixelIndex< false >(coordX, coordY));
			}

			/**
			 * @brief Returns the X coordinates in the image from the array index.
			 * @tparam enable_boundary_check_v Enable the boundary check and set a valid value. Default true.
			 * @param pixelIndex The pixel index.
			 * @return size_t
			 */
			template< bool enable_boundary_check_v = true >
			[[nodiscard]]
			size_t
			x (size_t pixelIndex) const noexcept
			{
				if constexpr ( enable_boundary_check_v )
				{
					this->clampPixelIndex(pixelIndex);
				}

				return pixelIndex % m_width;
			}

			/**
			 * @brief Returns the Y coordinates in the image from the array index.
			 * @tparam enable_boundary_check_v Enable the boundary check and set a valid value. Default true.
			 * @param pixelIndex The pixel index.
			 * @return size_t
			 */
			template< bool enable_boundary_check_v = true >
			[[nodiscard]]
			size_t
			y (size_t pixelIndex) const noexcept
			{
				if constexpr ( enable_boundary_check_v )
				{
					this->clampPixelIndex(pixelIndex);
				}

				return static_cast< size_t >(std::floor(pixelIndex / m_width));
			}

			/**
			 * @brief Returns the U texture2Ds coordinates in the image from the array index.
			 * @tparam enable_boundary_check_v Enable the boundary check and set a valid value. Default true.
			 * @param pixelIndex The pixel index.
			 * @return float
			 */
			template< bool enable_boundary_check_v = true >
			[[nodiscard]]
			float
			u (size_t pixelIndex) const noexcept
			{
				if constexpr ( enable_boundary_check_v )
				{
					this->clampPixelIndex(pixelIndex);
				}

				/* NOTE: Boundary check already done. */
				return this->x< false >(pixelIndex) / static_cast< float >(m_width - 1);
			}

			/**
			 * @brief Returns the V texture2Ds coordinates in the image from the array index.
			 * @tparam enable_boundary_check_v Enable the boundary check and set a valid value. Default true.
			 * @param pixelIndex The pixel index.
			 * @return float
			 */
			template< bool enable_boundary_check_v = true >
			[[nodiscard]]
			float
			v (size_t pixelIndex) const noexcept
			{
				if constexpr ( enable_boundary_check_v )
				{
					this->clampPixelIndex(pixelIndex);
				}

				/* NOTE: Boundary check already done. */
				return this->y< false >(pixelIndex) / static_cast< float >(m_height - 1);
			}

			/**
			 * @brief Returns the pixel index at location X, Y.
			 * @warning This is the pixel index. If you want to use this index over the data vector, use Pixmap::dataIndex() instead.
			 * @tparam enable_boundary_check_v Enable the boundary check and set a valid value. Default true.
			 * @param coordX The X coordinate of the pixel.
			 * @param coordY The Y coordinate of the pixel.
			 * @return size_t
			 */
			template< bool enable_boundary_check_v = true >
			[[nodiscard]]
			size_t
			pixelIndex (size_t coordX, size_t coordY) const noexcept
			{
				if constexpr ( enable_boundary_check_v )
				{
					this->clampPixelCoords(coordX, coordY);
				}

				return (coordY * m_width) + coordX;
			}
		
			/**
			 * @brief Returns the data index at location X, Y.
			 * @tparam enable_boundary_check_v Enable the boundary check and set a valid value. Default true.
			 * @param coordX The X coordinate of the pixel.
			 * @param coordY The Y coordinate of the pixel.
			 * @return size_t
			 */
			template< bool enable_boundary_check_v = true >
			[[nodiscard]]
			size_t
			dataIndex (size_t coordX, size_t coordY) const noexcept
			{
				if constexpr ( enable_boundary_check_v )
				{
					this->clampPixelCoords(coordX, coordY);
				}

				/* NOTE: Boundary check already done. */
				return this->pixelIndex< false >(coordX, coordY) * this->colorCount();
			}

			/**
			 * @brief Sets a pixel.
			 * @tparam color_data_t The color data type. Default float.
			 * @tparam enable_boundary_check_v Enable the boundary check and set a valid value. Default true.
			 * @param pixelIndex The index of the pixel.
			 * @param color A reference to the color of the pixel.
			 * @return void
			 */
			template< typename color_data_t = float, bool enable_boundary_check_v = true >
			void
			setPixel (size_t pixelIndex, const Color< color_data_t > & color) noexcept requires (std::is_floating_point_v< color_data_t >)
			{
				if constexpr ( enable_boundary_check_v )
				{
					this->clampPixelIndex(pixelIndex);
				}

				const auto offset = pixelIndex * this->colorCount();

				if constexpr ( std::is_floating_point_v< precision_t > )
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
							m_data[offset] = color.template grayInteger< precision_t >();
							break;

						case ChannelMode::GrayscaleAlpha :
							m_data[offset] = color.template grayInteger< precision_t >();
							m_data[offset + 1] = color.template alphaInteger< precision_t >();
							break;

						case ChannelMode::RGB :
							m_data[offset] = color.template redInteger< precision_t >();
							m_data[offset + 1] = color.template greenInteger< precision_t >();
							m_data[offset + 2] = color.template blueInteger< precision_t >();
							break;

						case ChannelMode::RGBA :
							m_data[offset] = color.template redInteger< precision_t >();
							m_data[offset + 1] = color.template greenInteger< precision_t >();
							m_data[offset + 2] = color.template blueInteger< precision_t >();
							m_data[offset + 3] = color.template alphaInteger< precision_t >();
							break;
					}
				}

				if ( m_flags[UpdatedRegionMarkerEnabled] )
				{
					this->setPixelAsUpdated(
						this->x< false >(pixelIndex),
						this->y< false >(pixelIndex)
					);
				}
			}

			/**
			 * @brief Sets a pixel.
			 * @tparam color_data_t The color data type. Default float.
			 * @tparam enable_boundary_check_v Enable the boundary check and set a valid value. Default true.
			 * @param coordX The X coordinate of the pixel.
			 * @param coordY The Y coordinate of the pixel.
			 * @param color A reference to the color of the pixel.
			 * @return void
			 */
			template< typename color_data_t = float, bool enable_boundary_check_v = true >
			void
			setPixel (size_t coordX, size_t coordY, const Color< color_data_t > & color) noexcept requires (std::is_floating_point_v< color_data_t >)
			{
				if constexpr ( enable_boundary_check_v )
				{
					this->clampPixelCoords(coordX, coordY);
				}

				const auto pixelIndex = this->pixelIndex< false >(coordX, coordY);

				this->setPixel< color_data_t, false >(pixelIndex, color);
			}

			/**
			 * @brief Sets a pixel. It will be ignored if it's fall outside the pixmap.
			 * @tparam color_data_t The color data type. Default float.
			 * @param coordX The X coordinate of the pixel.
			 * @param coordY The Y coordinate of the pixel.
			 * @param color A reference to the color of the pixel.
			 * @return void
			 */
			template< typename color_data_t = float >
			void
			setFreePixel (int64_t coordX, int64_t coordY, const Color< color_data_t > & color) noexcept requires (std::is_floating_point_v< color_data_t >)
			{
				if ( coordX < 0 || coordX >= m_width || coordY < 0 || coordY >= m_height )
				{
					return;
				}

				const auto pixelIndex = this->pixelIndex< false >(static_cast< size_t >(coordX), static_cast< size_t >(coordY));

				this->setPixel< color_data_t, false >(pixelIndex, color);
			}

			/**
			 * @brief Mixes a color to an existing pixel with a scalar value.
			 * @tparam color_data_t The color data type. Default float.
			 * @tparam enable_boundary_check_v Enable the boundary check and set a valid value. Default true.
			 * @param pixelIndex The index of the pixel.
			 * @param color A reference to a color.
			 * @param mix The mix scale.
			 * @return void
			 */
			template< typename color_data_t = float, bool enable_boundary_check_v = true >
			void
			mixPixel (size_t pixelIndex, const Color< color_data_t > & color, float mix) noexcept requires (std::is_floating_point_v< color_data_t >)
			{
				if constexpr ( enable_boundary_check_v )
				{
					this->clampPixelIndex(pixelIndex);
				}

				const auto previousColor = this->pixel< color_data_t, false >(pixelIndex);

				this->template setPixel< color_data_t, false >(pixelIndex, Color< color_data_t >::mix(previousColor, color, mix));
			}

			/**
			 * @brief Mixes a color to an existing pixel with a scalar value.
			 * @tparam color_data_t The color data type. Default float.
			 * @tparam enable_boundary_check_v Enable the boundary check and set a valid value. Default true.
			 * @param coordX The X coordinate of the pixel.
			 * @param coordY The Y coordinate of the pixel.
			 * @param color A reference to a color.
			 * @param mix The blending technics.
			 * @return void
			 */
			template< typename color_data_t = float, bool enable_boundary_check_v = true >
			void
			mixPixel (size_t coordX, size_t coordY, const Color< color_data_t > & color, float mix) noexcept requires (std::is_floating_point_v< color_data_t >)
			{
				if constexpr ( enable_boundary_check_v )
				{
					this->clampPixelCoords(coordX, coordY);
				}

				const auto pixelIndex = this->pixelIndex< false >(coordX, coordY);

				const auto previousColor = this->pixel< color_data_t, false >(pixelIndex);

				this->template setPixel< color_data_t, false >(pixelIndex, Color< color_data_t >::mix(previousColor, color, mix));
			}

			/**
			 * @brief Mixes a color to an existing pixel with a scalar value. It will be ignored if it's fall outside the pixmap.
			 * @tparam color_data_t The color data type. Default float.
			 * @param coordX The X coordinate of the pixel.
			 * @param coordY The Y coordinate of the pixel.
			 * @param color A reference to a color.
			 * @param mix The blending technics.
			 * @return void
			 */
			template< typename color_data_t = float >
			void
			mixFreePixel (int64_t coordX, int64_t coordY, const Color< color_data_t > & color, float mix) noexcept requires (std::is_floating_point_v< color_data_t >)
			{
				if ( coordX < 0 || coordX >= m_width || coordY < 0 || coordY >= m_height )
				{
					return;
				}

				const auto pixelIndex = this->pixelIndex< false >(static_cast< size_t >(coordX), static_cast< size_t >(coordY));

				const auto previousColor = this->pixel< color_data_t, false >(pixelIndex);

				this->template setPixel< color_data_t, false >(pixelIndex, Color< color_data_t >::mix(previousColor, color, mix));
			}

			/**
			 * @brief Blends a color to an existing pixel.
			 * @tparam color_data_t The color data type. Default float.
			 * @tparam enable_boundary_check_v Enable the boundary check and set a valid value. Default true.
			 * @param pixelIndex The index of the pixel.
			 * @param color A reference to a color.
			 * @param mode The blending technics.
			 * @param opacity A global opacity (Ignored with Replace). Default 1.0.
			 * @return void
			 */
			template< typename color_data_t = float, bool enable_boundary_check_v = true >
			void
			blendPixel (size_t pixelIndex, const Color< color_data_t > & color, DrawPixelMode mode, float opacity = 1.0F) noexcept requires (std::is_floating_point_v< color_data_t >)
			{
				if constexpr ( enable_boundary_check_v )
				{
					this->clampPixelIndex(pixelIndex);
				}

				if ( mode == DrawPixelMode::Replace )
				{
					this->setPixel< color_data_t, false >(pixelIndex, color);
				}
				else
				{
					const auto previousColor = this->pixel< color_data_t, false >(pixelIndex);

					this->template setPixel< color_data_t, false >(pixelIndex, Color< color_data_t >::blend(previousColor, color, mode, opacity));
				}
			}

			/**
			 * @brief Blends a color to an existing pixel.
			 * @tparam color_data_t The color data type. Default float.
			 * @tparam enable_boundary_check_v Enable the boundary check and set a valid value. Default true.
			 * @param coordX The X coordinate of the pixel.
			 * @param coordY The Y coordinate of the pixel.
			 * @param color A reference to a color.
			 * @param mode The blending technics.
			 * @param opacity A global opacity (Ignored with Replace). Default 1.0.
			 * @return void
			 */
			template< typename color_data_t = float, bool enable_boundary_check_v = true >
			void
			blendPixel (size_t coordX, size_t coordY, const Color< color_data_t > & color, DrawPixelMode mode, float opacity = 1.0F) noexcept requires (std::is_floating_point_v< color_data_t >)
			{
				if constexpr ( enable_boundary_check_v )
				{
					this->clampPixelCoords(coordX, coordY);
				}

				const auto pixelIndex = this->pixelIndex< false >(coordX, coordY);

				if ( mode == DrawPixelMode::Replace )
				{
					this->setPixel< color_data_t, false >(pixelIndex, color);
				}
				else
				{
					const auto previousColor = this->pixel< color_data_t, false >(pixelIndex);

					this->template setPixel< color_data_t, false >(pixelIndex, Color< color_data_t >::blend(previousColor, color, mode, opacity));
				}
			}

			/**
			 * @brief Blends a color to an existing pixel. It will be ignored if it's fall outside the pixmap.
			 * @tparam color_data_t The color data type. Default float.
			 * @param coordX The X coordinate of the pixel.
			 * @param coordY The Y coordinate of the pixel.
			 * @param color A reference to a color.
			 * @param mode The blending technics.
			 * @param opacity A global opacity (Ignored with Replace). Default 1.0.
			 * @return void
			 */
			template< typename color_data_t = float >
			void
			blendFreePixel (int64_t coordX, int64_t coordY, const Color< color_data_t > & color, DrawPixelMode mode, float opacity = 1.0F) noexcept requires (std::is_floating_point_v< color_data_t >)
			{
				if ( coordX < 0 || coordX >= m_width || coordY < 0 || coordY >= m_height )
				{
					return;
				}

				const auto pixelIndex = this->pixelIndex< false >(coordX, coordY);

				if ( mode == DrawPixelMode::Replace )
				{
					this->setPixel< color_data_t, false >(pixelIndex, color);
				}
				else
				{
					const auto previousColor = this->pixel< color_data_t, false >(pixelIndex);

					this->template setPixel< color_data_t, false >(pixelIndex, Color< color_data_t >::blend(previousColor, color, mode, opacity));
				}
			}

			/**
			 * @brief Returns a pixel as a color.
			 * @tparam color_data_t The color data type. Default float.
			 * @tparam enable_boundary_check_v Enable the boundary check and set a valid value. Default true.
			 * @param pixelIndex The index of the pixel.
			 * @return Color< color_data_t >
			 */
			template< typename color_data_t = float, bool enable_boundary_check_v = true >
			[[nodiscard]]
			Color< color_data_t >
			pixel (size_t pixelIndex) const noexcept requires (std::is_floating_point_v< color_data_t >)
			{
				if constexpr ( enable_boundary_check_v )
				{
					this->clampPixelIndex(pixelIndex);
				}

				const auto offset = pixelIndex * this->colorCount();

				if constexpr ( std::is_floating_point_v< precision_t > )
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
			 * @tparam color_data_t The color data type. Default float.
			 * @tparam enable_boundary_check_v Enable the boundary check and set a valid value. Default true.
			 * @param coordX The X coordinate of the pixel.
			 * @param coordY The Y coordinate of the pixel.
			 * @return Color< color_data_t >
			 */
			template< typename color_data_t = float, bool enable_boundary_check_v = true >
			[[nodiscard]]
			Color< color_data_t >
			pixel (size_t coordX, size_t coordY) const noexcept requires (std::is_floating_point_v< color_data_t >)
			{
				if constexpr ( enable_boundary_check_v )
				{
					this->clampPixelCoords(coordX, coordY);
				}

				const auto pixelIndex = this->pixelIndex< false >(coordX, coordY);

				return this->pixel< color_data_t, false >(pixelIndex);
			}

			/**
			 * @brief Returns the closest pixel to boundary at coordinates.
			 * @tparam color_data_t The color data type.
			 * @param coordX The X coordinate of the pixel.
			 * @param coordY The Y coordinate of the pixel.
			 * @return Color< color_data_t >
			 */
			template< typename color_data_t = float >
			[[nodiscard]]
			Color< color_data_t >
			closestPixel (int64_t coordX, int64_t coordY) const noexcept requires (std::is_floating_point_v< color_data_t >)
			{
				if ( coordX < 0 )
				{
					coordX = 0;
				}
				else if ( coordX >= m_width )
				{
					coordX = m_width - 1;
				}

				if ( coordY < 0 )
				{
					coordY = 0;
				}
				else if ( coordY >= m_height )
				{
					coordY = m_height - 1;
				}

				return this->pixel< color_data_t, false >(coordX, coordY);
			}

			/**
			 * @brief Returns a sampled pixel using the nearest algorithm.
			 * @tparam color_data_t The color data type.
			 * @param texCoordU The X coordinate of the pixel.
			 * @param texCoordV The Y coordinate of the pixel.
			 * @return Color< color_data_t >
			 */
			template< typename color_data_t = float >
			[[nodiscard]]
			Color< color_data_t >
			nearestSample (float texCoordU, float texCoordV) const noexcept requires (std::is_floating_point_v< color_data_t >)
			{
				if ( m_flags[UVWrappingEnabled] )
				{
					if ( texCoordU < 0.0F || texCoordU > 1.0F )
					{
						texCoordU = std::fmod(std::abs(texCoordU), 1.0F);
					}

					if ( texCoordV < 0.0F || texCoordV > 1.0F )
					{
						texCoordV = std::fmod(std::abs(texCoordV), 1.0F);
					}
				}
				else if ( texCoordU < 0.0F || texCoordU > 1.0F || texCoordV < 0.0F || texCoordV > 1.0F )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", incorrect parameters (U:" << texCoordU << ", V:" << texCoordV << ") !" "\n";

					return {};
				}

				/* Prepare variable for X axis. */
				const auto realX = static_cast< float >(m_width - 1) * texCoordU;

				/* Prepare variable for Y axis. */
				const auto realY = static_cast< float >(m_height - 1) * texCoordV;

				return this->pixel< color_data_t, false >(static_cast< size_t >(std::round(realX)), static_cast< size_t >(std::round(realY)));
			}

			/**
			 * @brief Returns a sampled pixel using the linear algorithm.
			 * @tparam color_data_t The color data type.
			 * @param texCoordU The X coordinate of the pixel.
			 * @param texCoordV The Y coordinate of the pixel.
			 * @return Color< color_data_t >
			 */
			template< typename color_data_t = float>
			[[nodiscard]]
			Color< color_data_t >
			linearSample (float texCoordU, float texCoordV) const noexcept requires (std::is_floating_point_v< color_data_t >)
			{
				if ( m_flags[UVWrappingEnabled] )
				{
					if ( texCoordU < 0.0F || texCoordU > 1.0F )
					{
						texCoordU = std::fmod(std::abs(texCoordU), 1.0F);
					}

					if ( texCoordV < 0.0F || texCoordV > 1.0F )
					{
						texCoordV = std::fmod(std::abs(texCoordV), 1.0F);
					}
				}
				else if ( texCoordU < 0.0F || texCoordU > 1.0F || texCoordV < 0.0F || texCoordV > 1.0F )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", incorrect parameters (U:" << texCoordU << ", V:" << texCoordV << ") !" "\n";

					return {};
				}

				/* Prepare variable for X axis. */
				const auto realX = static_cast< float >(m_width - 1) * texCoordU;
				const auto loX = static_cast< size_t >(std::floor(realX));
				const auto hiX = static_cast< size_t >(std::ceil(realX));
				const auto factorX = realX - static_cast< float >(loX);

				/* Prepare variable for Y axis. */
				const auto realY = static_cast< float >(m_height - 1) * texCoordV;
				const auto loY = static_cast< size_t >(std::floor(realY));
				const auto hiY = static_cast< size_t >(std::ceil(realY));
				const auto factorY = realY - static_cast< float >(loY);

				/* Gets involved pixels. */
				auto bottomLeftPixel = this->pixel< color_data_t, false >(loX, loY);
				auto bottomRightPixel = this->pixel< color_data_t, false >(hiX, loY);
				auto topLeftPixel = this->pixel< color_data_t, false >(loX, hiY);
				auto topRightPixel = this->pixel< color_data_t, false >(hiX, hiY);

				return Color< color_data_t >::bilinearInterpolation(bottomLeftPixel, bottomRightPixel, topLeftPixel, topRightPixel, factorX, factorY);
			}

			/**
			 * @brief Returns a sampled pixel using the cosine algorithm.
			 * @tparam color_data_t The color data type.
			 * @param texCoordU The X coordinate of the pixel.
			 * @param texCoordV The Y coordinate of the pixel.
			 * @return Color< color_data_t >
			 */
			template< typename color_data_t = float >
			[[nodiscard]]
			Color< color_data_t >
			cosineSample (float texCoordU, float texCoordV) const noexcept requires (std::is_floating_point_v< color_data_t >)
			{
				if ( m_flags[UVWrappingEnabled] )
				{
					if ( texCoordU < 0.0F || texCoordU > 1.0F )
					{
						texCoordU = std::fmod(std::abs(texCoordU), 1.0F);
					}

					if ( texCoordV < 0.0F || texCoordV > 1.0F )
					{
						texCoordV = std::fmod(std::abs(texCoordV), 1.0F);
					}
				}
				else if ( texCoordU < 0.0F || texCoordU > 1.0F || texCoordV < 0.0F || texCoordV > 1.0F )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", incorrect parameters (U:" << texCoordU << ", V:" << texCoordV << ") !" "\n";

					return {};
				}

				/* Prepare variable for X axis. */
				const auto realX = static_cast< float >(m_width - 1) * texCoordU;
				const auto loX = static_cast< size_t >(std::floor(realX));
				const auto hiX = static_cast< size_t >(std::ceil(realX));
				const auto factorX = realX - static_cast< float >(loX);

				/* Prepare variable for Y axis. */
				const auto realY = static_cast< float >(m_height - 1) * texCoordV;
				const auto loY = static_cast< size_t >(std::floor(realY));
				const auto hiY = static_cast< size_t >(std::ceil(realY));
				const auto factorY = realY - static_cast< float >(loY);

				/* Gets involved pixels. */
				const auto bottomLeftPixel = this->pixel< color_data_t, false >(loX, loY);
				const auto bottomRightPixel = this->pixel< color_data_t, false >(hiX, loY);
				const auto topLeftPixel = this->pixel< color_data_t, false >(loX, hiY);
				const auto topRightPixel = this->pixel< color_data_t, false >(hiX, hiY);

				return Color< color_data_t >::bicosineInterpolation(bottomLeftPixel, bottomRightPixel, topLeftPixel, topRightPixel, factorX, factorY);
			}

			/**
			 * @brief Returns a sampled pixel using the cubic algorithm.
			 * @tparam color_data_t The color data type.
			 * @param texCoordU The X coordinate of the pixel.
			 * @param texCoordV The Y coordinate of the pixel.
			 * @return Color< color_data_t >
			 */
			template< typename color_data_t = float >
			[[nodiscard]]
			Color< color_data_t >
			cubicSample (float texCoordU, float texCoordV) const noexcept requires (std::is_floating_point_v< color_data_t >)
			{
				if ( m_flags[UVWrappingEnabled] )
				{
					if ( texCoordU < 0.0F || texCoordU > 1.0F )
					{
						texCoordU = std::fmod(std::abs(texCoordU), 1.0F);
					}

					if ( texCoordV < 0.0F || texCoordV > 1.0F )
					{
						texCoordV = std::fmod(std::abs(texCoordV), 1.0F);
					}
				}
				else if ( texCoordU < 0.0F || texCoordU > 1.0F || texCoordV < 0.0F || texCoordV > 1.0F )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", incorrect parameters (U:" << texCoordU << ", V:" << texCoordV << ") !" "\n";

					return {};
				}

				/* Prepare variable for X axis */
				const auto realX = static_cast< float >(m_width - 1) * texCoordU;
				const auto loX = static_cast< size_t >(std::floor(realX));
				const auto factorX = realX - static_cast< float >(loX);

				/* Prepare variable for Y axis */
				const auto realY = static_cast< float >(m_height - 1) * texCoordV;
				const auto loY = static_cast< size_t >(std::floor(realY));
				const auto factorY = realY - static_cast< float >(loY);

				/* Gets involved pixels */
				const auto p00 = this->pixel< color_data_t, true >(loX - 1, loY - 1);
				const auto p10 = this->pixel< color_data_t, true >(loX + 0, loY - 1);
				const auto p20 = this->pixel< color_data_t, true >(loX + 1, loY - 1);
				const auto p30 = this->pixel< color_data_t, true >(loX + 2, loY - 1);

				const auto p01 = this->pixel< color_data_t, true >(loX - 1, loY + 0);
				const auto p11 = this->pixel< color_data_t, true >(loX + 0, loY + 0);
				const auto p21 = this->pixel< color_data_t, true >(loX + 1, loY + 0);
				const auto p31 = this->pixel< color_data_t, true >(loX + 2, loY + 0);

				const auto p02 = this->pixel< color_data_t, true >(loX - 1, loY + 1);
				const auto p12 = this->pixel< color_data_t, true >(loX + 0, loY + 1);
				const auto p22 = this->pixel< color_data_t, true >(loX + 1, loY + 1);
				const auto p32 = this->pixel< color_data_t, true >(loX + 2, loY + 1);

				const auto p03 = this->pixel< color_data_t, true >(loX - 1, loY + 2);
				const auto p13 = this->pixel< color_data_t, true >(loX + 0, loY + 2);
				const auto p23 = this->pixel< color_data_t, true >(loX + 1, loY + 2);
				const auto p33 = this->pixel< color_data_t, true >(loX + 2, loY + 2);

				/* Red component */
				const auto red = Math::cubicInterpolation(
					Math::cubicInterpolation(p00.red(), p10.red(), p20.red(), p30.red(), factorX),
					Math::cubicInterpolation(p01.red(), p11.red(), p21.red(), p31.red(), factorX),
					Math::cubicInterpolation(p02.red(), p12.red(), p22.red(), p32.red(), factorX),
					Math::cubicInterpolation(p03.red(), p13.red(), p23.red(), p33.red(), factorX),
					factorY
				);

				/* Green component */
				const auto green = Math::cubicInterpolation(
					Math::cubicInterpolation(p00.green(), p10.green(), p20.green(), p30.green(), factorX),
					Math::cubicInterpolation(p01.green(), p11.green(), p21.green(), p31.green(), factorX),
					Math::cubicInterpolation(p02.green(), p12.green(), p22.green(), p32.green(), factorX),
					Math::cubicInterpolation(p03.green(), p13.green(), p23.green(), p33.green(), factorX),
					factorY
				);

				/* Blue component */
				const auto blue = Math::cubicInterpolation(
					Math::cubicInterpolation(p00.blue(), p10.blue(), p20.blue(), p30.blue(), factorX),
					Math::cubicInterpolation(p01.blue(), p11.blue(), p21.blue(), p31.blue(), factorX),
					Math::cubicInterpolation(p02.blue(), p12.blue(), p22.blue(), p32.blue(), factorX),
					Math::cubicInterpolation(p03.blue(), p13.blue(), p23.blue(), p33.blue(), factorX),
					factorY
				);

				/* Alpha component */
				const auto alpha = Math::cubicInterpolation(
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
			 * @tparam enable_boundary_check_v Enable the boundary check and set a valid value. Default true.
			 * @param coordX The X coordinate of the pixel.
			 * @param coordY The Y coordinate of the pixel.
			 * @param channel The pixmap channel targeted.
			 * @param value The new value.
			 */
			template< bool enable_boundary_check_v = true >
			void
			setPixelElement (size_t coordX, size_t coordY, Channel channel, precision_t value) noexcept
			{
				if constexpr ( enable_boundary_check_v )
				{
					this->clampPixelCoords(coordX, coordY);
				}

				const auto index = this->dataIndex< false >(coordX, coordY) + static_cast< size_t >(channel);

				m_data[index] = value;

				if ( m_flags[UpdatedRegionMarkerEnabled] )
				{
					this->setPixelAsUpdated(coordX, coordY);
				}
			}

			/**
			 * @brief Returns a pixel sub-element.
			 * @tparam enable_boundary_check_v Enable the boundary check and set a valid value. Default true.
			 * @param coordX The X coordinate of the pixel.
			 * @param coordY The Y coordinate of the pixel.
			 * @param channel The pixmap channel targeted.
			 * @return type_t
			 */
			template< bool enable_boundary_check_v = true >
			[[nodiscard]]
			precision_t
			pixelElement (size_t coordX, size_t coordY, Channel channel) const noexcept
			{
				if constexpr ( enable_boundary_check_v )
				{
					this->clampPixelCoords(coordX, coordY);
				}

				const auto index = this->dataIndex< false >(coordX, coordY) + static_cast< size_t >(channel);

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
				return m_channelMode == ChannelMode::GrayscaleAlpha || m_channelMode == ChannelMode::RGBA;
			}

			/**
			 * @brief Returns the average color of the pixmap.
			 * @tparam color_data_t The color data type.
			 * @return Color< color_data_t >
			 */
			template< typename color_data_t = float >
			[[nodiscard]]
			Color< color_data_t >
			averageColor () const noexcept requires (std::is_floating_point_v< color_data_t >)
			{
				if ( !this->isValid() )
				{
					return {};
				}

				const auto limit = this->pixelCount();
				const auto stride = this->colorCount();
				const auto dataLimit = m_data.size();

				switch ( m_channelMode )
				{
					case ChannelMode::Grayscale :
					case ChannelMode::GrayscaleAlpha :
						if constexpr ( std::is_floating_point_v< precision_t > )
						{
							precision_t maxValue = 0;

							for ( size_t index = 0; index < dataLimit; index += stride )
							{
								maxValue += m_data[index];
							}

							const auto value = static_cast< color_data_t >(maxValue / limit);

							return {value, value, value};
						}
						else
						{
							size_t maxValue = 0;

							for ( size_t index = 0; index < dataLimit; index += stride )
							{
								maxValue += m_data[index];
							}

							const auto value = static_cast< precision_t >(std::floor(maxValue / limit));

							return ColorFromInteger(value, value, value);
						}

					case ChannelMode::RGB :
					case ChannelMode::RGBA :
						if constexpr ( std::is_floating_point_v< precision_t > )
						{
							precision_t maxR = 0;
							precision_t maxG = 0;
							precision_t maxB = 0;

							for ( size_t index = 0; index < dataLimit; index += stride )
							{
								maxR += m_data[index];
								maxG += m_data[index+1];
								maxB += m_data[index+2];
							}

							return {
								static_cast< color_data_t >(maxR / limit),
								static_cast< color_data_t >(maxG / limit),
								static_cast< color_data_t >(maxB / limit)
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
								static_cast< precision_t >(std::floor(maxR / limit)),
								static_cast< precision_t >(std::floor(maxG / limit)),
								static_cast< precision_t >(std::floor(maxB / limit))
							);
						}

					default:
						return {};
				}
			}

			/**
			 * @brief Enables the updated region marker. This feature will keep an Area object that hold every processLogics made to the pixmap.
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
			 * @param coordX The X coordinate of the pixel.
			 * @param coordY The Y coordinate of the pixel.
			 * @return void
			 */
			void
			setPixelAsUpdated (size_t coordX, size_t coordY) noexcept
			{
				if ( m_lastUpdatedRegion.isValid() )
				{
					/* Checks on X axis */
					if ( coordX < m_lastUpdatedRegion.offsetX() )
					{
						m_lastUpdatedRegion.setOffsetX(coordX);
						m_lastUpdatedRegion.modifyWidthBy(m_lastUpdatedRegion.offsetX() - coordX);
					}

					if ( coordX > m_lastUpdatedRegion.offsetXb() )
					{
						m_lastUpdatedRegion.setWidth((coordX - m_lastUpdatedRegion.offsetX()) + 1);
					}

					/* Checks on Y axis */
					if ( coordY < m_lastUpdatedRegion.offsetY() )
					{
						m_lastUpdatedRegion.setOffsetY(coordY);
						m_lastUpdatedRegion.modifyHeightBy(m_lastUpdatedRegion.offsetY() - coordY);
					}

					if ( coordY > m_lastUpdatedRegion.offsetYb() )
					{
						m_lastUpdatedRegion.setHeight((coordY - m_lastUpdatedRegion.offsetY()) + 1);
					}
				}
				else
				{
					m_lastUpdatedRegion = {coordX, coordY, 1U, 1U};
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
				{
					return;
				}

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
				{
					return;
				}

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
			 * @brief Adds alpha channel.
			 * @param alphaValue The initial alpha value.
			 * @param modifyUpdatedRegion Set the updated region. Default true.
			 * @return bool
			 */
			bool
			addAlphaChannel (precision_t alphaValue, bool modifyUpdatedRegion = true) noexcept
			{
				if ( !this->isValid() )
				{
					return false;
				}

				switch ( m_channelMode )
				{
					case ChannelMode::GrayscaleAlpha :
					case ChannelMode::RGBA :
						return true;

					case ChannelMode::Grayscale :
					{
						const auto copy = m_data;

						if ( !this->initialize(m_width, m_height, ChannelMode::GrayscaleAlpha) )
						{
							return false;
						}

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
						{
							return false;
						}

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
				{
					this->setOverallUpdated();
				}

				return true;
			}

			/**
			 * @brief Fills the pixmap with a single value.
			 * @note This will ignore the alpha value.
			 * @param value The value.
			 * @return bool
			 */
			bool
			fill (precision_t value) noexcept
			{
				if ( !this->isValid() )
				{
					return false;
				}

				switch ( m_channelMode )
				{
					case ChannelMode::Grayscale :
					case ChannelMode::RGB :
						std::memset(m_data.data(), value, m_data.size() * sizeof(precision_t));
						break;

					case ChannelMode::GrayscaleAlpha :
					{
						const auto limit = this->elementCount();

						for ( size_t index = 0; index < limit; index += 2 )
						{
							m_data[index] = value;
						}
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
			 * @brief Fills the pixmap with a sequence of data.
			 * @note This will ignore the alpha value.
			 * @param data A raw pointer to data.
			 * @param size The size of the data.
			 * @return bool
			 */
			bool
			fill (const precision_t * data, size_t size) noexcept
			{
				if ( !this->isValid() )
				{
					return false;
				}

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
							{
								offset = 0;
							}
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
							{
								offset = 0;
							}

							m_data[index+1] = data[offset++];

							if ( offset >= size )
							{
								offset = 0;
							}

							m_data[index+2] = data[offset++];

							if ( offset >= size )
							{
								offset = 0;
							}
						}
					}
						break;
				}

				this->setOverallUpdated();

				return true;
			}

			/**
			 * @brief Fills the pixmap with a sequence of data.
			 * @note This will ignore the alpha value.
			 * @param vector A reference to a vector.
			 * @return bool
			 */
			bool
			fill (const std::vector< precision_t > & vector) noexcept
			{
				return this->fill(vector.data(), vector.size());
			}

			/**
			 * @brief Fills the pixmap with a color.
			 * @tparam color_data_t The color data type.
			 * @param color A reference to a color.
			 * @return bool
			 */
			template< typename color_data_t = float >
			bool
			fill (const Color< color_data_t > & color) noexcept requires (std::is_floating_point_v< color_data_t >)
			{
				if ( !this->isValid() )
				{
					return false;
				}

				const auto limit = this->pixelCount();

				for ( size_t index = 0; index < limit; index++ )
				{
					this->setPixel< color_data_t, false >(index, color);
				}

				this->setOverallUpdated();

				return true;
			}

			/**
			 * @brief Fills the pixmap with a pattern.
			 * @note This may be a naive approach. But this library is not intended to be Photoshop.
			 * @param pattern A reference to a pixmap.
			 * @return bool
			 */
			bool
			fill (const Pixmap & pattern) noexcept
			{
				if ( !this->isValid() )
				{
					return false;
				}

				if ( this->colorCount() != pattern.colorCount() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", the pixmap and the pattern do not have the same channel mode !" "\n";

					return false;
				}

				size_t patternRowIndex = 0;

				for ( size_t rowIndex = 0; rowIndex < m_height; rowIndex++ )
				{
					auto * rowData = this->rowPointer(rowIndex);
					auto * patternRowData = pattern.rowPointer(patternRowIndex);

					auto bytesLeft = this->pitch();

					while ( bytesLeft > 0 )
					{
						const auto chunkBytes = pattern.pitch() > bytesLeft ? bytesLeft : pattern.pitch();

						std::memcpy(rowData, patternRowData, chunkBytes);

						rowData += chunkBytes;
						bytesLeft -= chunkBytes;
					}

					/* NOTE: Advance in the pattern rows, and reset at the bottom of the pattern image. */
					patternRowIndex++;

					if ( patternRowIndex >= pattern.height() )
					{
						patternRowIndex = 0;
					}
				}

				this->setOverallUpdated();

				return true;
			}

			/**
			 * @brief Fills the pixmap with an horizontal gradient.
			 * @tparam scale_data_t The scale data type. Default float.
			 * @tparam color_data_t The color data type. Default float.
			 * @param gradient A reference to a gradient.
			 * @return bool
			 */
			template< typename scale_data_t = float, typename color_data_t = float >
			bool
			fillHorizontal (const Gradient< scale_data_t, color_data_t > & gradient) noexcept
			{
				if ( !this->isValid() )
				{
					return false;
				}

				for ( size_t rowIndex = 0; rowIndex < m_height; rowIndex++ )
				{
					const auto position = static_cast< scale_data_t >(rowIndex) / static_cast< scale_data_t >(m_height);

					const auto color = gradient.colorAt(position);

					for ( size_t colIndex = 0; colIndex < m_width; colIndex++ )
					{
						this->template setPixel< color_data_t, false >(colIndex, rowIndex, color);
					}
				}

				this->setOverallUpdated();

				return true;
			}

			/**
			 * @brief Fills the pixmap with a vertical gradient.
			 * @tparam scale_data_t The scale data type. Default float.
			 * @tparam color_data_t The color data type. Default float.
			 * @param gradient A reference to a gradient.
			 * @return bool
			 */
			template< typename scale_data_t = float, typename color_data_t = float >
			bool
			fillVertical (const Gradient< scale_data_t, color_data_t > & gradient) noexcept
			{
				if ( !this->isValid() )
				{
					return false;
				}

				for ( size_t colIndex = 0; colIndex < m_width; colIndex++ )
				{
					const auto position = static_cast< scale_data_t >(colIndex) / static_cast< scale_data_t >(m_width);

					const auto color = gradient.colorAt(position);

					for ( size_t rowIndex = 0; rowIndex < m_height; rowIndex++ )
					{
						this->template setPixel< color_data_t, false >(colIndex, rowIndex, color);
					}
				}

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
			fillChannel (Channel channel, precision_t value) noexcept
			{
				if ( !this->isValid() )
				{
					return false;
				}

				const auto channelIndex = static_cast< size_t >(channel);

				if ( channelIndex >= this->colorCount() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", bad channel index !" "\n";

					return false;
				}

				if ( m_channelMode == ChannelMode::Grayscale )
				{
					std::memset(m_data.data(), value, m_data.size() * sizeof(precision_t));

					return true;
				}

				const auto limit = this->elementCount();
				const auto stride = this->colorCount();

				for ( size_t index = 0; index < limit; index += stride )
				{
					m_data[index + channelIndex] = value;
				}

				this->setOverallUpdated();

				return true;
			}

			/**
			 * @brief Fills the pixmap channel with a sequence of data.
			 * @param channel The targeted channel of the pixmap.
			 * @param data A raw pointer to data.
			 * @param size The size of the data.
			 * @return bool
			 */
			bool
			fillChannel (Channel channel, const precision_t * data, size_t size) noexcept
			{
				if ( !this->isValid() )
				{
					return false;
				}

				const auto channelIndex = static_cast< size_t >(channel);

				if ( channelIndex >= this->colorCount() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", bad channel index !" "\n";

					return false;
				}

				if ( m_channelMode == ChannelMode::Grayscale )
				{
					return this->fill(data, size);
				}

				const auto limit = this->elementCount();
				const auto stride = this->colorCount();

				size_t offset = 0;

				for ( size_t index = 0; index < limit; index += stride )
				{
					m_data[index + channelIndex] = data[offset++];

					if ( offset >= size )
					{
						offset = 0;
					}
				}

				this->setOverallUpdated();

				return true;
			}

			/**
			 * @brief Fills the pixmap channel with a sequence of data.
			 * @param channel The targeted channel of the pixmap.
			 * @param vector A reference to a vector.
			 * @return bool
			 */
			bool
			fillChannel (Channel channel, const std::vector< precision_t > & vector) noexcept
			{
				return this->fillChannel(channel, vector.data(), vector.size());
			}

			/**
			 * @brief Fills the pixmap channel with a pattern.
			 * @note The pattern pixmap will be used as a grayscale.
			 * @param channel The targeted channel of the pixmap.
			 * @param pattern A reference to a pixmap.
			 * @param mode The conversion mode. Default LumaRec709.
			 * @param option Additional parameter for specific mode. Default 0.
			 * @return bool
			 */
			bool
			fillChannel (Channel channel, const Pixmap & pattern, GrayscaleConversionMode mode = GrayscaleConversionMode::LumaRec709, int option = 0) noexcept
			{
				if ( !this->isValid() )
				{
					return false;
				}

				const auto channelIndex = static_cast< size_t >(channel);

				if ( channelIndex >= this->colorCount() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", bad channel index !" "\n";

					return false;
				}

				size_t patternRowIndex = 0;
				size_t patternColIndex = 0;

				for ( size_t rowIndex = 0; rowIndex < m_height; rowIndex++ )
				{
					for ( size_t colIndex = 0; colIndex < m_width; colIndex++ )
					{
						if constexpr ( std::is_floating_point_v< precision_t > )
						{
							this->setPixelElement(colIndex, rowIndex, channel, pattern.pixel(patternColIndex, patternRowIndex).luminance(mode, option));
						}
						else
						{
							this->setPixelElement(colIndex, rowIndex, channel, pattern.pixel(patternColIndex, patternRowIndex).luminanceInteger(mode, option));
						}

						/* NOTE: Advance in the pattern columns, and reset at the right of the pattern image. */
						patternColIndex++;

						if ( patternColIndex >= pattern.width() )
						{
							patternColIndex = 0;
						}
					}

					/* NOTE: Advance in the pattern rows, and reset at the bottom of the pattern image. */
					patternRowIndex++;
					patternColIndex = 0;

					if ( patternRowIndex >= pattern.height() )
					{
						patternRowIndex = 0;
					}
				}

				this->setOverallUpdated();

				return true;
			}

			/**
			 * @brief Fills the pixmap channel with an horizontal gradient.
			 * @note The gradient will be used as a grayscale.
			 * @tparam color_data_t The color data type.
			 * @param channel The targeted channel of the pixmap.
			 * @param gradient A reference to a gradient.
			 * @param mode The conversion mode. Default LumaRec709.
			 * @param option Additional parameter for specific mode. Default 0.
			 * @return bool
			 */
			template< typename scale_data_t = float, typename color_data_t = float >
			bool
			fillHorizontalChannel (Channel channel, const Gradient< color_data_t, color_data_t > & gradient, GrayscaleConversionMode mode = GrayscaleConversionMode::LumaRec709, int option = 0) noexcept requires (std::is_floating_point_v< color_data_t >)
			{
				if ( !this->isValid() )
				{
					return false;
				}

				const auto channelIndex = static_cast< size_t >(channel);

				if ( channelIndex >= this->colorCount() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", bad channel index !" "\n";

					return false;
				}

				for ( size_t rowIndex = 0; rowIndex < m_height; rowIndex++ )
				{
					const auto position = static_cast< scale_data_t >(rowIndex) / static_cast< scale_data_t >(m_height);

					precision_t value;

					if constexpr ( std::is_floating_point_v< precision_t > )
					{
						value = gradient.colorAt(position).luminance(mode, option);
					}
					else
					{
						value = gradient.colorAt(position).luminanceInteger(mode, option);
					}

					for ( size_t colIndex = 0; colIndex < m_width; colIndex++ )
					{
						this->setPixelElement(colIndex, rowIndex, channel, value);
					}
				}

				this->setOverallUpdated();

				return true;
			}

			/**
			 * @brief Fills the pixmap channel with a vertical gradient.
			 * @note The gradient will be used as a grayscale.
			 * @tparam color_data_t The color data type.
			 * @param channel The targeted channel of the pixmap.
			 * @param gradient A reference to a gradient.
			 * @param mode The conversion mode. Default LumaRec709.
			 * @param option Additional parameter for specific mode. Default 0.
			 * @return bool
			 */
			template< typename scale_data_t = float, typename color_data_t = float >
			bool
			fillVerticalChannel (Channel channel, const Gradient< color_data_t, color_data_t > & gradient, GrayscaleConversionMode mode = GrayscaleConversionMode::LumaRec709, int option = 0) noexcept requires (std::is_floating_point_v< color_data_t >)
			{
				if ( !this->isValid() )
				{
					return false;
				}

				const auto channelIndex = static_cast< size_t >(channel);

				if ( channelIndex >= this->colorCount() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", bad channel index !" "\n";

					return false;
				}

				for ( size_t colIndex = 0; colIndex < m_width; colIndex++ )
				{
					const auto position = static_cast< scale_data_t >(colIndex) / static_cast< scale_data_t >(m_width);

					precision_t value;

					if constexpr ( std::is_floating_point_v< precision_t > )
					{
						value = gradient.colorAt(position).luminance(mode, option);
					}
					else
					{
						value = gradient.colorAt(position).luminanceInteger(mode, option);
					}

					for ( size_t rowIndex = 0; rowIndex < m_height; rowIndex++ )
					{
						this->setPixelElement(colIndex, rowIndex, channel, value);
					}
				}

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
				{
					return;
				}

				/* NOTE : C++ std::fill(myArray, myArray+N, 0); */
				//std::fill(m_data.begin(), m_data.end(), 0);
				std::memset(m_data.data(), 0, m_data.size() * sizeof(precision_t));

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
				{
					return false;
				}

				std::srand(static_cast< unsigned >(std::time(nullptr)));

				std::vector< precision_t > pixelData{};

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
			 * @param scale The perlin noise scale factor.
			 * @param grayNoise Generate only gray. Default false.
			 * @return bool
			 */
			bool
			perlinNoise (float scale, bool grayNoise = false) noexcept
			{
				if ( !this->isValid() )
				{
					return false;
				}

				const auto limit = this->pixelCount();
				const auto stride = this->colorCount();

				switch ( m_channelMode )
				{
					case ChannelMode::Grayscale :
					case ChannelMode::GrayscaleAlpha :
					{
						Algorithms::PerlinNoise< float > generator{Utility::random(0U, std::numeric_limits< unsigned int >::max())};

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
							Algorithms::PerlinNoise< float > generator{Utility::random(0U, std::numeric_limits< unsigned int >::max())};

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
							Algorithms::PerlinNoise< float > redGenerator{Utility::random(0U, std::numeric_limits< unsigned int >::max())};
							Algorithms::PerlinNoise< float > greenGenerator{Utility::random(0U, std::numeric_limits< unsigned int >::max())};
							Algorithms::PerlinNoise< float > blueGenerator{Utility::random(0U, std::numeric_limits< unsigned int >::max())};

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
			 * @brief Applies a function on every pixel in rows order (Single loop).
			 * @note Returning false will skip the pixel.
			 * @warning This method is slow.
			 * @param updatePixel A reference to a function to modify the pixel. Signature : function(Color & pixel) -> bool
			 * @return void
			 */
			template< typename color_data_t = float >
			void
			forEachPixel (const std::function< bool (Color< color_data_t > &) > & updatePixel) noexcept requires (std::is_floating_point_v< color_data_t >)
			{
				const auto limit = this->pixelCount();

				for ( size_t index = 0; index < limit; index++ )
				{
					auto pixel = this->pixel< color_data_t, false >(index);

					if ( !updatePixel(pixel) )
					{
						continue;
					}

					this->setPixel< color_data_t, false >(index, pixel);
				}
			}

			/**
			 * @brief Applies a function on every pixel in rows order (Single loop).
			 * @note Returning false will skip the pixel.
			 * @warning This method is slow.
			 * @tparam color_data_t The color data type.
			 * @param updatePixel A reference to a function to modify the pixel. Signature : function(Color & pixel, size_t coordX, size_t coordY) -> bool
			 * @return void
			 */
			template< typename color_data_t = float >
			void
			forEachPixelRowMajor (const std::function< bool (Color< color_data_t > &, size_t, size_t) > & updatePixel) noexcept requires (std::is_floating_point_v< color_data_t >)
			{
				const auto limit = this->pixelCount();

				for ( size_t index = 0; index < limit; index++ )
				{
					auto pixel = this->pixel< color_data_t, false >(index);

					if ( !updatePixel(pixel, this->x< false >(index), this->y< false >(index)) )
					{
						continue;
					}

					this->setPixel< color_data_t, false >(index, pixel);
				}
			}

			/**
			 * @brief Applies a function on every pixel in columns order (X^Y loops).
			 * @note Returning false will skip the pixel.
			 * @warning This method is slow.
			 * @tparam color_data_t The color data type.
			 * @param updatePixel A reference to a function to modify the pixel. Signature : function(Color & pixel, size_t, size_t) -> bool
			 * @return void
			 */
			template< typename color_data_t = float >
			void
			forEachPixelColMajor (const std::function< bool (Color< color_data_t > &, size_t, size_t) > & updatePixel) noexcept requires (std::is_floating_point_v< color_data_t >)
			{
				for ( size_t colIndex = 0; colIndex < m_width; colIndex++ )
				{
					for ( size_t rowIndex = 0; rowIndex < m_height; rowIndex++ )
					{
						const auto pixelIndex = this->pixelIndex< false >(colIndex, rowIndex);

						auto pixel = this->pixel< color_data_t, false >(pixelIndex);

						if ( !updatePixel(pixel, colIndex, rowIndex) )
						{
							continue;
						}

						this->setPixel< color_data_t, false >(pixelIndex, pixel);
					}
				}
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
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
						out << "Channels count : 1 (Grayscale)" "\n";
						break;

					case 2 :
						out << "Channels count : 2 (GrayscaleAlpha)" "\n";
						break;

					case 3 :
						out << "Channels count : 3 (RGB)" "\n";
						break;

					case 4 :
						out << "Channels count : 4 (RGBA)" "\n";
						break;

					default:
						out << "Channels count : ERROR !" "\n";
						break;
				}

				out <<
					"Pixel count : " << obj.pixelCount() << "\n"
					"Pixel size : " << obj.bytePerPixel() << " bytes (" << obj.bitPerPixel() << " bit)\n"
					"Element count : " << obj.elementCount() << "\n"
					"Data size : " << obj.bytes() << " bytes" "\n";

				return out;
			}

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend
			std::string
			to_string (const Pixmap & obj) noexcept
			{
				std::stringstream output;

				output << obj;

				return output.str();
			}

		private:

			/**
			 * @brief Clamps a pixel index to pixmap valid area.
			 * @param pixelIndex A pixel index.
			 * @return void
			 */
			void
			clampPixelIndex (size_t & pixelIndex) const noexcept
			{
				const auto pixelCount = this->pixelCount();

				if ( pixelIndex >= pixelCount )
				{
#ifdef EMERAUDE_DEBUG_PIXEL_FACTORY
					std::cerr << __PRETTY_FUNCTION__ << ", pixel index overflow !" "\n";
#endif
					pixelIndex = pixelCount - 1;
				}
			}

			/**
			 * @brief Clamps a pixel coordinates to pixmap valid area.
			 * @param coordX The pixel position in X.
			 * @param coordY The pixel position in Y.
			 * @return void
			 */
			void
			clampPixelCoords (size_t & coordX, size_t & coordY) const noexcept
			{
				if ( coordX >= m_width )
				{
#ifdef EMERAUDE_DEBUG_PIXEL_FACTORY
					std::cerr << __PRETTY_FUNCTION__ << ", pixel X coordinate overflow !" "\n";
#endif

					coordX = m_width - 1;
				}

				if ( coordY >= m_height )
				{
#ifdef EMERAUDE_DEBUG_PIXEL_FACTORY
					std::cerr << __PRETTY_FUNCTION__ << ", pixel Y coordinate overflow !" "\n";
#endif

					coordY = m_height - 1;
				}
			}

			/**
			 * @brief Returns the zero value for this pixmap component.
			 * @return type_t
			 */
			[[nodiscard]]
			static
			precision_t
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
			precision_t
			one () noexcept
			{
				if constexpr ( std::is_floating_point_v< precision_t > )
				{
					return 1;
				}
				else
				{
					return std::numeric_limits< precision_t >::max();
				}
			}

			/**
			 * @brief Takes care of initialize alpha channel to 1.
			 * @return bool
			 */
			bool
			initAlphaChannel () noexcept
			{
				switch ( m_channelMode )
				{
					case ChannelMode::RGBA :
						return this->fillChannel(Channel::Alpha, Pixmap::one());

					case ChannelMode::GrayscaleAlpha :
						return this->fillChannel(Channel::Green, Pixmap::one());

					default:
						return true;
				}
			}

			/* Flag names. */
			static constexpr auto UVWrappingEnabled{0UL};
			static constexpr auto UpdatedRegionMarkerEnabled{1UL};

			size_t m_width{0};
			size_t m_height{0};
			ChannelMode m_channelMode{ChannelMode::RGB};
			std::vector< precision_t > m_data{};
			Area< size_t > m_lastUpdatedRegion;
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
	template< typename input_t, typename output_t >
	[[nodiscard]]
	Pixmap< output_t >
	dataConversion (const Pixmap< input_t > & input) noexcept requires (std::is_arithmetic_v< input_t >, std::is_arithmetic_v< output_t >)
	{
		Pixmap< output_t > output{input.width(), input.height(), input.channelMode()};

#ifdef EMERAUDE_DEBUG_PIXEL_FACTORY
		std::cout << "Pixmap data conversion : " << typeid(input_t).name() << " (" << sizeof(input_t) << " bytes) to " << typeid(output_t).name() << " (" << sizeof(output_t) << " bytes) !" "\n";
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
