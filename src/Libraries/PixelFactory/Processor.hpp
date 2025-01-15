/*
 * src/Libraries/PixelFactory/Processor.hpp
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
#include <cmath>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <limits>
#include <type_traits>

/* Local inclusions. */
#include "Area.hpp"
#include "Color.hpp"
#include "Libraries/Math/Base.hpp"
#include "Libraries/Math/Circle.hpp"
#include "Libraries/Math/Line.hpp"
#include "Libraries/Math/Segment.hpp"
#include "Libraries/Math/Vector.hpp"
#include "Pixmap.hpp"
#include "Types.hpp"

namespace Libraries::PixelFactory
{
	/**
	 * @brief The pixmap processor is used to performs operations to a targeted pixmap.
	 * @TODO Use swap buffer to optimize some of operations.
	 * @tparam precision_t A numeric type to define the depth precision of pixel.
	 */
	template< typename precision_t = uint8_t >
	requires (std::is_arithmetic_v< precision_t >)
	class Processor final
	{
		public:

			/* https://github.com/podgorskiy/EnvMapTooL */
			/**
			 * @brief Constructs a processor on a pixmap.
			 * @param target A reference to a target pixmap.
			 * @param filteringMode Which filter mode to use when resizing occurs. Default FilteringMode::Linear.
			 */
			explicit
			Processor (Pixmap< precision_t > & target, FilteringMode filteringMode = FilteringMode::Linear) noexcept
				: m_target(target), m_filteringMode(filteringMode)
			{

			}

			/**
			 * @brief Multiplies the pixels value by a scalar.
			 * @tparam scale_t The type of scalar. Default float.
			 * @tparam color_data_t The color data type. Default float.
			 * @param scalar A scalar value.
			 * @return bool
			 */
			template< typename scale_t = float, typename color_data_t = float >
			bool
			scale (scale_t scalar) noexcept requires (std::is_floating_point_v< scale_t >)
			{
				if ( !this->checkPixmap() )
				{
					return false;
				}

				m_target.template forEachPixel< color_data_t >([scalar] (Color< color_data_t > & pixel) {
					pixel * scalar;

					return true;
				});

				m_target.setOverallUpdated();

				return true;
			}

			/**
			 * @brief Multiplies the value of sub-channel pixel by a scalar.
			 * @tparam scale_t The type of scalar. Default float.
			 * @tparam color_data_t The color data type. Default float.
			 * @param scalar A scalar value.
			 * @param channel The channel.
			 * @return bool
			 */
			template< typename scale_t = float, typename color_data_t = float >
			bool
			scale (scale_t scalar, Channel channel) noexcept requires (std::is_floating_point_v< scale_t >)
			{
				if ( !this->checkPixmap() )
				{
					return false;
				}

				m_target.template forEachPixel< color_data_t >([scalar, channel] (Color< color_data_t > & pixel) {
					switch ( channel )
					{
						case Channel::Red :
							pixel.setRed(pixel.red() * scalar);
							break;

						case Channel::Green :
							pixel.setGreen(pixel.green() * scalar);
							break;

						case Channel::Blue :
							pixel.setBlue(pixel.blue() * scalar);
							break;

						case Channel::Alpha :
							pixel.setAlpha(pixel.alpha() * scalar);
							break;
					}

					return true;
				});

				m_target.setOverallUpdated();

				return true;
			}

			/**
			 * @brief Draws a line between two point on the pixmap.
			 * @tparam vectorData_t The vector data type. Default int.
			 * @tparam dataColor_t The color data type. Default float.
			 * @param pointA A reference to a vector for the execute coordinates of the line.
			 * @param pointB A reference to a vector for the end coordinates of the line.
			 * @param color A reference to a color.
			 * @param mode The drawing mode. Default DrawPixelMode::Replace.
			 */
			template< typename vectorData_t = int, typename dataColor_t = float >
			bool
			drawSegment (Math::Vector< 2, vectorData_t > pointA, Math::Vector< 2, vectorData_t > pointB, const Color< dataColor_t > & color, DrawPixelMode mode = DrawPixelMode::Replace) noexcept requires (std::is_floating_point_v< dataColor_t >)
			{
				if ( !this->checkPixmap() )
				{
					return false;
				}

				const auto width = static_cast< vectorData_t >(m_target.width());
				const auto height = static_cast< vectorData_t >(m_target.height());

				/* Checks if segment are inside the Pixmap. */
				if
				(
					( pointA[Math::X] < 0 && pointB[Math::X] < 0 ) || ( pointA[Math::X] > width && pointB[Math::X] > width ) ||
					( pointA[Math::Y] < 0 && pointB[Math::Y] < 0 ) || ( pointA[Math::Y] > height && pointB[Math::Y] > height )
				)
				{
					std::cerr << __PRETTY_FUNCTION__ << ", the segment is completely outside the pixmap" "\n";

					return false;
				}

				if ( !this->clampSegmentPoint(pointA, pointB) )
				{
					return false;
				}

				if ( !this->clampSegmentPoint(pointB, pointA) )
				{
					return false;
				}

				const auto steep = std::abs(pointB[Math::Y] - pointA[Math::Y]) > std::abs(pointB[Math::X] - pointA[Math::X]);

				if ( steep )
				{
					pointA.swapAxis();
					pointB.swapAxis();
				}

				if ( pointA[Math::X] > pointB[Math::X] )
				{
					pointA.swap(pointB);
				}

				const auto deltaX = pointB[Math::X] - pointA[Math::X];
				const auto deltaY = std::abs(pointB[Math::Y] - pointA[Math::Y]);

				auto error = static_cast< float >(deltaX) / 2.0F;
				const auto yStep = (pointA[Math::Y] < pointB[Math::Y] ) ? 1 : -1;
				auto y = pointA[Math::Y];

				for( auto x = pointA[Math::X]; x <= pointB[Math::X]; ++x )
				{
					if ( steep )
					{
						m_target.blendPixel(static_cast< size_t >(y), static_cast< size_t >(x), color, mode);
					}
					else
					{
						m_target.blendPixel(static_cast< size_t >(x), static_cast< size_t >(y), color, mode);
					}

					error -= deltaY;

					if ( error < 0 )
					{
						y += yStep;
						error += deltaX;
					}
				}

				return true;
			}

			/**
			 * @brief Draws a line between two point on the pixmap.
			 * @tparam dataSegment_t The segment data type. Default int.
			 * @tparam dataColor_t The color data type. Default float.
			 * @param segment A reference to a segment.
			 * @param color A reference to a color.
			 * @param mode The drawing mode. Default DrawPixelMode::Replace.
			 */
			template< typename dataSegment_t = int, typename dataColor_t = float >
			bool
			drawSegment (const Math::Segment< dataSegment_t > & segment, const Color< dataColor_t > & color, DrawPixelMode mode = DrawPixelMode::Replace) noexcept requires (std::is_floating_point_v< dataSegment_t >)
			{
				return this->drawSegment(segment.start(), segment.end(), color, mode);
			}

			/**
			 * @brief Draws a circle on the pixmap.
			 * @tparam dataColor_t The color data type. Default float.
			 * @param center The center of the circle.
			 * @param radius The radius of the circle.
			 * @param color A reference to a color.
			 * @param mode The drawing mode. Default DrawPixelMode::Replace.
			 */
			template< typename dataColor_t = float >
			bool
			drawCircle (const Math::Vector< 2, int > & center, size_t radius, const Color< dataColor_t > & color, DrawPixelMode mode = DrawPixelMode::Replace) noexcept requires (std::is_floating_point_v< dataColor_t >)
			{
				if ( !this->checkPixmap() )
				{
					return false;
				}

				auto x = 0UL;
				auto y = radius;
				auto delta = radius - 1;

				while ( y >= x )
				{
					const auto signedX = static_cast< int >(x);
					const auto signedY = static_cast< int >(y);

					/* Quadrant 1 */
					m_target.blendPixel(signedX + center.x(), signedY + center.y(), color, mode);
					m_target.blendPixel(signedY + center.x(), signedX + center.y(), color, mode);

					/* Quadrant 2 */
					m_target.blendPixel(-signedX + center.x(), signedY + center.y(), color, mode);
					m_target.blendPixel(-signedY + center.x(), signedX + center.y(), color, mode);

					/* Quadrant 3 */
					m_target.blendPixel(signedX + center.x(), -signedY + center.y(), color, mode);
					m_target.blendPixel(signedY + center.x(), -signedX + center.y(), color, mode);

					/* Quadrant 4 */
					m_target.blendPixel(-signedX + center.x(), -signedY + center.y(), color, mode);
					m_target.blendPixel(-signedY + center.x(), -signedX + center.y(), color, mode);

					if ( delta >= 2 * x )
					{
						delta -= (2 * x) - 1;

						x++;
					}
					else if ( delta <= 2 * (radius - y) )
					{
						delta += (2 * y) - 1;

						y--;
					}
					else
					{
						delta += 2 * (y - x - 1);

						y--;
						x++;
					}
				}

				return true;
			}

			/**
			 * @brief Draws a circle on the pixmap.
			 * @tparam dataColor_t The color data type. Default float.
			 * @param circle A reference to a circle.
			 * @param color A reference to a color.
			 * @param mode The drawing mode. Default DrawPixelMode::Replace.
			 */
			template< typename dataColor_t = float >
			bool
			drawCircle (const Math::Circle< float > & circle, const Color< dataColor_t > & color, DrawPixelMode mode = DrawPixelMode::Replace) noexcept requires (std::is_floating_point_v< dataColor_t >)
			{
				return this->drawCircle(circle.position(), static_cast< size_t >(circle.radius()), color, mode);
			}

			/**
			 * @brief Draws a square on the pixmap.
			 * @tparam dataColor_t The color data type. Default float.
			 * @param area A reference to a area.
			 * @param color A reference to a color.
			 * @param mode The drawing mode. Default DrawPixelMode::Replace.
			 */
			template< typename dataColor_t = float >
			bool
			drawSquare (const Area< size_t > & area, const Color< dataColor_t > & color, DrawPixelMode mode = DrawPixelMode::Replace) noexcept requires (std::is_floating_point_v< dataColor_t >)
			{
				if ( !this->checkPixmapClipping(m_target, area) )
				{
					return false;
				}

				this->drawSegment(area.bottomLeft< int >(), area.bottomRight< int >(), color, mode);
				this->drawSegment(area.bottomRight< int >(), area.topRight< int >(), color, mode);
				this->drawSegment(area.topLeft< int >(), area.topRight< int >(), color, mode);
				this->drawSegment(area.topLeft< int >(), area.bottomLeft< int >(), color, mode);

				return true;
			}

			/**
			 * @brief Draws a cross on the pixmap.
			 * @tparam dataColor_t The color data type. Default float.
			 * @param area A reference to a area.
			 * @param color A reference to a color.
			 * @param mode The drawing mode. Default DrawPixelMode::Replace.
			 */
			template< typename dataColor_t = float >
			bool
			drawCross (const Area< size_t > & area, const Color< dataColor_t > & color, DrawPixelMode mode = DrawPixelMode::Replace) noexcept requires (std::is_floating_point_v< dataColor_t >)
			{
				if ( !this->checkPixmapClipping(m_target, area) )
				{
					return false;
				}

				this->drawSegment(area.topLeft< int >(), area.bottomRight< int >(), color, mode);
				this->drawSegment(area.bottomLeft< int >(), area.topRight< int >(), color, mode);

				return true;
			}

			/**
			 * @brief Draws a straight cross on the pixmap.
			 * @tparam dataColor_t The color data type. Default float.
			 * @param area A reference to a area.
			 * @param color A reference to a color.
			 * @param mode The drawing mode. Default DrawPixelMode::Replace.
			 */
			template< typename dataColor_t = float >
			bool
			drawStraightCross (const Area< size_t > & area, const Color< dataColor_t > & color, DrawPixelMode mode = DrawPixelMode::Replace) noexcept requires (std::is_floating_point_v< dataColor_t >)
			{
				if ( !this->checkPixmapClipping(m_target, area) )
				{
					return false;
				}

				const auto midX = static_cast< int >(area.offsetX() + (area.width() / 2));
				const auto midY = static_cast< int >(area.offsetY() + (area.height() / 2));

				this->drawSegment({midX, static_cast< int >(area.offsetY())}, {midX, static_cast< int >(area.offsetYb())}, color, mode);
				this->drawSegment({static_cast< int >(area.offsetX()), midY}, {static_cast< int >(area.offsetXb()), midY}, color, mode);

				return true;
			}

			/**
			 * @brief Moves pixels into a direction.
			 * @note Positive X value will move pixel to the left while positive Y value will move pixel upward.
			 * @param xDirection An integer to move pixels in X-Axis.
			 * @param yDirection An integer to move pixels in Y-Axis.
			 * @return bool
			 */
			bool
			move (int xDirection, int yDirection) noexcept
			{
				if ( !this->checkPixmap() )
				{
					return false;
				}

				/* NOTE: No movement at all ! */
				if ( xDirection == 0 && yDirection == 0 )
				{
					return false;
				}

				this->prepareSwapBuffer();

				/* NOTE: The shift is completely moving the pixmap outside the canvas in X-Axis or Y-axis. */
				if ( std::abs(xDirection) < m_target.width() && std::abs(yDirection) < m_target.height() )
				{
					const auto rowSize = m_target.pitch();
					const auto xShift = xDirection * static_cast< int >(m_target.colorCount());

					/* NOTE : Defines chunk sizes to move. */
					const auto xLimit = rowSize - std::abs(xShift);
					const auto yLimit = m_target.height() - std::abs(yDirection);

					size_t src = 0;
					size_t dst = 0;

					for ( size_t rowIndex = 0; rowIndex < yLimit; rowIndex++ )
					{
						if ( yDirection > 0 )
						{
							src = rowIndex;
							dst = (rowIndex + yDirection) * rowSize;
						}
						else
						{
							src = rowIndex - yDirection;
							dst = rowIndex  * rowSize;
						}

						if ( xShift > 0 )
						{
							std::memcpy(m_swapBuffer.data() + dst + xShift, m_target.rowPointer(src), xLimit);
						}
						else
						{
							std::memcpy(m_swapBuffer.data() + dst, m_target.rowPointer(src) - xShift, xLimit);
						}
					}
				}

				m_target.setOverallUpdated();

				return this->swapBuffers();
			}

			/**
			 * @brief Moves pixels into a direction.
			 * @note Positive X value will move pixel to the left while positive Y value will move pixel upward.
			 * @param direction A reference to a 2D vector.
			 * @return bool
			 */
			bool
			move (const Math::Vector< 2, int > & direction) noexcept
			{
				return this->move(direction[Math::X], direction[Math::Y]);
			}

			/**
			 * @brief Shift pixmap into a direction. Same as Processor::move() with pixels wrapping.
			 * @note Positive X value will move pixel to the left while positive Y value will move pixel upward.
			 * @param xDirection An integer to move pixels in X-Axis.
			 * @param yDirection An integer to move pixels in Y-Axis.
			 * @return bool
			 */
			bool
			shift (int xDirection, int yDirection) noexcept
			{
				if ( !this->checkPixmap() )
				{
					return false;
				}

				/* NOTE: No movement at all ! */
				if ( xDirection == 0 && yDirection == 0 )
				{
					return true;
				}

				/* NOTE: Remove the shifting round trip. */
				xDirection =
					xDirection < 0 ?
					xDirection % -m_target.width() :
					xDirection % m_target.width();
				yDirection =
					yDirection < 0 ?
					yDirection % -m_target.height() :
					yDirection % m_target.height();

				/* NOTE: Complete shift in both direction. */
				if ( xDirection == 0 && yDirection == 0 )
				{
					return true;
				}

				this->prepareSwapBuffer();

				const auto rowSize = m_target.pitch();
				const auto xShift = xDirection * m_target.colorCount();

				/* NOTE : Defines chunk sizes to move. */
				const auto rowCopySizeA = rowSize - xShift;
				const auto rowCopySizeB = rowSize - rowCopySizeA;

				size_t dstRowIndex = std::abs(yDirection);

				for ( size_t rowIndex = 0; rowIndex < m_target.height(); rowIndex++ )
				{
					auto dst = dstRowIndex * rowSize;

					std::memcpy(m_swapBuffer.data() + dst, m_target.rowPointer(rowIndex) + rowCopySizeA, rowCopySizeB);

					dst += rowCopySizeB;

					std::memcpy(m_swapBuffer.data() + dst, m_target.rowPointer(rowIndex), rowCopySizeA);

					/* NOTE: Next row on the destination and loop if requested. */
					dstRowIndex++;

					if ( dstRowIndex >= m_target.height() )
					{
						dstRowIndex = 0;
					}
				}

				m_target.setOverallUpdated();

				return this->swapBuffers();
			}

			/**
			 * @brief Shift pixmap into a direction. Same as Processor::move() with pixels wrapping.
			 * @note Positive X value will move pixel to the left while positive Y value will move pixel upward.
			 * @param direction A reference to a 2D vector.
			 * @return bool
			 */
			bool
			shift (const Math::Vector< 2, int > & direction) noexcept
			{
				return this->shift(direction[Math::X], direction[Math::Y]);
			}

			/**
			 * @brief Moves pixels upward or downward for a console-like text area.
			 * @param distance The distance of moving in pixel.
			 * @return bool
			 */
			bool
			shiftTextArea (int distance) noexcept
			{
				if ( !this->checkPixmap() )
				{
					return false;
				}

				/* NOTE : Not moving at all ! */
				if ( distance == 0 )
				{
					return true;
				}

				this->prepareSwapBuffer();

				const auto rowSize = m_target.pitch();
				const auto bufferSize = (m_target.height() - std::abs(distance)) * rowSize;

				if ( distance > 0 )
				{
					std::memcpy(m_swapBuffer.data() + (distance * rowSize), m_target.rowPointer(0UL), bufferSize);
				}
				else
				{
					std::memcpy(m_swapBuffer.data(), m_target.rowPointer(std::abs(distance)), bufferSize);
				}

				m_target.setOverallUpdated();

				return this->swapBuffers();
			}

			/**
			 * @brief Returns a resized version of the Pixmap.
			 * @param source A reference to a pixmap to resize.
			 * @param width The new width.
			 * @param height The new height.
			 * @param filteringMode The filtering mode to apply during the resize. Default FilteringMode::Linear.
			 * @return Pixmap< data_t >
			 */
			[[nodiscard]]
			static
			Pixmap< precision_t >
			resize (const Pixmap< precision_t > & source, size_t width, size_t height, FilteringMode filteringMode = FilteringMode::Linear) noexcept
			{
				if ( !source.isValid() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", source Pixmap is invalid !" "\n";

					return {};
				}

				/* Simple copy if same size. */
				if ( width == source.width() && height == source.height() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", resize target the same Pixmap sizes..." "\n";

					return source;
				}

				Pixmap< precision_t > output{width, height, source.channelMode()};

				const auto colorCount = source.colorCount();
				const auto xRatio = static_cast< float >(source.width() - 1) / static_cast< float >(width);
				const auto yRatio = static_cast< float >(source.height() - 1) / static_cast< float >(height);
				const auto & pixels = source.data();
				auto & data = output.data();

				switch ( filteringMode )
				{
					case FilteringMode::Cubic :
						std::cerr << __PRETTY_FUNCTION__ << ", the cubic sampling is not yet implemented ! Using linear filtering instead." "\n";

						[[fallthrough]];

					case FilteringMode::Linear :
					{
						size_t dstIndex = 0;

						/* Y (row) on the destination */
						for ( size_t y = 0; y < height; y++ )
						{
							const auto realY = yRatio * static_cast< float >(y);

							const auto yFloor = static_cast< size_t >(std::floor(realY));
							const auto yCeil = static_cast< size_t >(std::ceil(realY));

							/* Source row of pixels */
							const auto srcRowA = yFloor * source.width();
							const auto srcRowB = yCeil * source.width();

							const auto yFactor = realY - static_cast< float >(yFloor);

							/* X (column) on the destination */
							for ( size_t x = 0; x < width; x++ )
							{
								const auto realX = static_cast< float >(x) * xRatio;

								const auto xFloor = static_cast< size_t >(std::floor(realX));
								const auto xCeil = static_cast< size_t >(std::ceil(realX));

								/* Source pixel */
								const auto srcIndexA = (srcRowA + xFloor) * colorCount;
								const auto srcIndexB = (srcRowA + xCeil) * colorCount;
								const auto srcIndexC = (srcRowB + xFloor) * colorCount;
								const auto srcIndexD = (srcRowB + xCeil) * colorCount;

								const auto xFactor = realX - static_cast< float >(xFloor);

								/* FIXME: provoke "invalid read of size 1" */
								switch ( source.channelMode() )
								{
									case ChannelMode::Grayscale :
										data[dstIndex++] = Processor::bilinearFiltering(pixels[srcIndexA], pixels[srcIndexB], pixels[srcIndexC], pixels[srcIndexD], xFactor, yFactor);
										break;

									case ChannelMode::GrayscaleAlpha :
										data[dstIndex++] = Processor::bilinearFiltering(pixels[srcIndexA], pixels[srcIndexB], pixels[srcIndexC], pixels[srcIndexD], xFactor, yFactor);
										data[dstIndex++] = Processor::bilinearFiltering(pixels[srcIndexA+1], pixels[srcIndexB+1], pixels[srcIndexC+1], pixels[srcIndexD+1], xFactor, yFactor);
										break;

									case ChannelMode::RGB :
										data[dstIndex++] = Processor::bilinearFiltering(pixels[srcIndexA], pixels[srcIndexB], pixels[srcIndexC], pixels[srcIndexD], xFactor, yFactor);
										data[dstIndex++] = Processor::bilinearFiltering(pixels[srcIndexA+1], pixels[srcIndexB+1], pixels[srcIndexC+1], pixels[srcIndexD+1], xFactor, yFactor);
										data[dstIndex++] = Processor::bilinearFiltering(pixels[srcIndexA+2], pixels[srcIndexB+2], pixels[srcIndexC+2], pixels[srcIndexD+2], xFactor, yFactor);
										break;

									case ChannelMode::RGBA :
										data[dstIndex++] = Processor::bilinearFiltering(pixels[srcIndexA], pixels[srcIndexB], pixels[srcIndexC], pixels[srcIndexD], xFactor, yFactor);
										data[dstIndex++] = Processor::bilinearFiltering(pixels[srcIndexA+1], pixels[srcIndexB+1], pixels[srcIndexC+1], pixels[srcIndexD+1], xFactor, yFactor);
										data[dstIndex++] = Processor::bilinearFiltering(pixels[srcIndexA+2], pixels[srcIndexB+2], pixels[srcIndexC+2], pixels[srcIndexD+2], xFactor, yFactor);
										data[dstIndex++] = Processor::bilinearFiltering(pixels[srcIndexA+3], pixels[srcIndexB+3], pixels[srcIndexC+3], pixels[srcIndexD+3], xFactor, yFactor);
										break;

									default:
										break;
								}
							}
						}
					}
						break;

					case FilteringMode::Nearest :
					{
						size_t destinationIndex = 0;

						/* Y (row) on the destination */
						for ( size_t destinationY = 0; destinationY < height; destinationY++ )
						{
							const auto sourceY = static_cast< size_t >(std::round(yRatio * static_cast< float >(destinationY)));
							const auto sourceRowIndex = sourceY * source.width() * colorCount;

							/* X (column) on the destination */
							for ( size_t destinationX = 0; destinationX < width; destinationX++ )
							{
								const auto sourceX = static_cast< size_t >(std::round(xRatio * static_cast< float >(destinationX)));
								const auto sourceIndex = sourceRowIndex + (sourceX * colorCount);

								switch ( source.channelMode() )
								{
									case ChannelMode::Grayscale :
										data[destinationIndex++] = pixels[sourceIndex];
										break;

									case ChannelMode::GrayscaleAlpha :
										data[destinationIndex++] = pixels[sourceIndex];
										data[destinationIndex++] = pixels[sourceIndex+1];
										break;

									case ChannelMode::RGB :
										data[destinationIndex++] = pixels[sourceIndex];
										data[destinationIndex++] = pixels[sourceIndex+1];
										data[destinationIndex++] = pixels[sourceIndex+2];
										break;

									case ChannelMode::RGBA :
										data[destinationIndex++] = pixels[sourceIndex];
										data[destinationIndex++] = pixels[sourceIndex+1];
										data[destinationIndex++] = pixels[sourceIndex+2];
										data[destinationIndex++] = pixels[sourceIndex+3];
										break;

									default:
										break;
								}
							}
						}
					}
						break;
				}

				return output;
			}

			/**
			 * @brief Returns a resized version of the Pixmap using a ratio.
			 * @param source A reference to a pixmap to resize.
			 * @param ratio The scale ratio.
			 * @param filteringMode The filtering mode to apply during the resize. Default FilteringMode::Linear.
			 * @return Pixmap< data_t >
			 */
			[[nodiscard]]
			static
			Pixmap< precision_t >
			resize (const Pixmap< precision_t > & source, float ratio, FilteringMode filteringMode = FilteringMode::Linear) noexcept
			{
				return Processor::resize(source, static_cast< size_t >(source.width() * ratio), static_cast< size_t >(source.height() * ratio), filteringMode);
			}

			/**
			 * @brief Returns a cropped version of the Pixmap.
			 * @param source A reference to a pixmap to resize.
			 * @param area A reference to an area.
			 * @return Pixmap< data_t >
			 */
			[[nodiscard]]
			static
			Pixmap< precision_t >
			crop (const Pixmap< precision_t > & source, const Area< size_t > & area) noexcept
			{
				if ( !source.isValid() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", the pixmap is invalid !" "\n";

					return {};
				}

				if ( !area.isValid() || !area.isIntersect(source.width(), source.height()) )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", the area is invalid or do not intersect the pixmap !" "\n";

					return {};
				}

				Pixmap< precision_t > output{area.width(), area.height(), source.channelMode()};

				const auto rowBytes = output.pitch();
				const auto pixelBytes = source.colorCount() * sizeof(precision_t);

				for ( size_t rowIndex = 0; rowIndex < area.height(); rowIndex++ )
				{
					const auto baseY = rowIndex + area.offsetY();
					const auto destinationIndex = rowIndex * rowBytes;
					const auto sourceIndex = (baseY * source.width() + area.offsetX()) * pixelBytes;

					std::memcpy(output.data().data() + destinationIndex, source.data().data() + sourceIndex, rowBytes);
				}

				return output;
			}

			/**
			 * @brief Returns one channel of the pixmap as a new grayscale pixmap.
			 * @param source A reference to a pixmap.
			 * @param channel The desired channel to extract.
			 * @return Pixmap< data_t >
			 */
			[[nodiscard]]
			static
			Pixmap< precision_t >
			extractChannel (const Pixmap< precision_t > & source, Channel channel) noexcept
			{
				if ( !source.isValid() )
				{
					return {};
				}

				size_t channelIndex = 0;

				switch ( source.channelMode() )
				{
					case ChannelMode::Grayscale :
						if ( channel == Channel::Alpha )
						{
							return {source.width(), source.height(), ChannelMode::Grayscale, White};
						}

						return source;

					case ChannelMode::GrayscaleAlpha :
						if ( channel == Channel::Alpha )
						{
							channelIndex = 1UL;
						}
						break;

					case ChannelMode::RGB :
						if ( channel == Channel::Alpha )
						{
							return {source.width(), source.height(), ChannelMode::Grayscale, White};
						}

						channelIndex = static_cast< size_t >(channel);
						break;

					case ChannelMode::RGBA :
						channelIndex = static_cast< size_t >(channel);
						break;

					default:
						break;
				}

				Pixmap< precision_t > output{source.width(), source.height(), ChannelMode::Grayscale};

				const auto pixelCount = source.pixelCount();

				for ( size_t pixelIndex = 0; pixelIndex < pixelCount; pixelIndex++ )
				{
					*output.pixelPointer(pixelIndex) = *(source.pixelPointer(pixelIndex) + channelIndex);
				}

				return output;
			}

			/**
			 * @brief Returns a pixmap in grayscale mode.
			 * @param source A reference to a pixmap.
			 * @param mode The conversion mode. Default LumaRec709.
			 * @param option Additional parameter for specific mode. Default 0.
			 * @return Pixmap< data_t >
			 */
			[[nodiscard]]
			static
			Pixmap< precision_t >
			toGrayscale (const Pixmap< precision_t > & source, GrayscaleConversionMode mode = GrayscaleConversionMode::Average, int option = 0) noexcept
			{
				if ( !source.isValid() )
				{
					return {};
				}

				if ( source.channelMode() == ChannelMode::Grayscale || source.channelMode() == ChannelMode::GrayscaleAlpha )
				{
					return source;
				}

				Pixmap< precision_t > output{source.width(), source.height(), ChannelMode::Grayscale};

				const auto pixelCount = source.pixelCount();

				for ( size_t pixelIndex = 0; pixelIndex < pixelCount; pixelIndex++ )
				{
					if constexpr ( std::is_floating_point_v< precision_t > )
					{
						*output.pixelPointer(pixelIndex) = source.pixel(pixelIndex).luminance(mode, option);
					}
					else
					{
						*output.pixelPointer(pixelIndex) = source.pixel(pixelIndex).template luminanceInteger<precision_t>(mode, option);
					}
				}

				return output;
			}

			/**
			 * @brief Returns a pixmap in RGB mode.
			 * @param source A reference to a pixmap.
			 * @return Pixmap< data_t >
			 */
			[[nodiscard]]
			static
			Pixmap< precision_t >
			toRGB (const Pixmap< precision_t > & source) noexcept
			{
				if ( !source.isValid() )
				{
					return {};
				}

				if ( source.channelMode() == ChannelMode::RGB )
				{
					return source;
				}

				Pixmap< precision_t > output{source.width(), source.height(), ChannelMode::RGB};

				const auto pixelCount = source.pixelCount();

				for ( size_t pixelIndex = 0; pixelIndex < pixelCount; pixelIndex++ )
				{
					output.setPixel(pixelIndex, source.pixel(pixelIndex));
				}

				return output;
			}

			/**
			 * @brief Returns a pixmap in RGBA mode.
			 * @param source A reference to a pixmap.
			 * @param opacity Alpha default value. Default 1.0.
			 * @return Pixmap< data_t >
			 */
			[[nodiscard]]
			static
			Pixmap< precision_t >
			toRGBA (const Pixmap< precision_t > & source, float opacity = 1.0F) noexcept
			{
				if ( !source.isValid() )
				{
					return {};
				}

				if ( source.channelMode() == ChannelMode::RGBA )
				{
					return source;
				}

				Pixmap< precision_t > output{source.width(), source.height(), ChannelMode::RGBA};

				const auto pixelCount = source.pixelCount();

				for ( size_t pixelIndex = 0; pixelIndex < pixelCount; pixelIndex++ )
				{
					auto color = source.pixel(pixelIndex);
					color.setAlpha(opacity);

					output.setPixel(pixelIndex, color);
				}

				return output;
			}

			/**
			 * @brief Mirrors the pixmap on X axis, Y axis or both axis.
			 * @param mode The mirror mode desired.
			 * @return bool
			 */
			bool
			mirror (MirrorMode mode) noexcept
			{
				if ( !m_target.isValid() )
				{
					return false;
				}

				/* Gets a copy. */
				Pixmap< precision_t > pixmap{m_target};

				switch ( mode )
				{
					case MirrorMode::X :
						Processor::mirrorX(pixmap, m_target);
						break;

					case MirrorMode::Y :
						if ( !Processor::mirrorY(pixmap, m_target) )
						{
							return false;
						}
						break;

					case MirrorMode::Both :
						if ( !Processor::mirrorBoth(pixmap, m_target) )
						{
							return false;
						}
						break;
				}

				return true;
			}

			/**
			 * @brief Mirrors the pixmap on X axis, Y axis or both axis.
			 * @param base A reference to a pixmap.
			 * @param mode The mirror mode desired.
			 * @return Pixmap< data_t >
			 */
			[[nodiscard]]
			static
			Pixmap< precision_t >
			mirror (const Pixmap< precision_t > & base, MirrorMode mode) noexcept
			{
				if ( !base.isValid() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", base Pixmap is invalid !" "\n";

					return {};
				}

				Pixmap< precision_t > output{base.width(), base.height(), base.channelMode()};

				switch ( mode )
				{
					case MirrorMode::X :
						Processor::mirrorX(base, output);
						break;

					case MirrorMode::Y :
						if ( !Processor::mirrorY(base, output) )
						{
							return {};
						}
						break;

					case MirrorMode::Both :
						if ( !Processor::mirrorBoth(base, output) )
						{
							return {};
						}
						break;
				}

				return output;
			}

			/**
			 * @brief Inverses the colors.
			 * @note This leave the alpha channel untouched.
			 * @param source A reference to a pixmap.
			 * @return Pixmap< data_t >
			 */
			[[nodiscard]]
			static
			Pixmap< precision_t >
			inverseColors (const Pixmap< precision_t > & source) noexcept
			{
				if ( !source.isValid() )
				{
					return {};
				}

				if ( source.channelMode() == ChannelMode::Grayscale || source.channelMode() == ChannelMode::GrayscaleAlpha )
				{
					return source;
				}

				Pixmap< precision_t > output{source.width(), source.height(), source.channelMode()};

				const auto pixelCount = source.pixelCount();

				for ( size_t pixelIndex = 0; pixelIndex < pixelCount; pixelIndex++ )
				{
					const auto * pixelSrc = source.pixelPointer(pixelIndex);
					auto pixelDst = output.pixelPointer(pixelIndex);

					pixelDst[0] = std::numeric_limits< precision_t >::max() - pixelSrc[0];
					pixelDst[1] = std::numeric_limits< precision_t >::max() - pixelSrc[1];
					pixelDst[2] = std::numeric_limits< precision_t >::max() - pixelSrc[2];
				}

				return output;
			}

			/**
			 * @brief This reverse the order of color components in each pixel. E.g. RGB -> BGR. RGBA -> BGRA.
			 * @note If swapAlpha is active, ARGB -> BGRA.
			 * @param source A reference to a pixmap.
			 * @param swapAlpha Set to swap alpha channel too.
			 * @return Pixmap< data_t >
			 */
			[[nodiscard]]
			static
			Pixmap< precision_t >
			swapChannels (const Pixmap< precision_t > & source, bool swapAlpha = false) noexcept
			{
				if ( !source.isValid() )
				{
					return {};
				}

				if ( source.channelMode() == ChannelMode::Grayscale || source.channelMode() == ChannelMode::GrayscaleAlpha )
				{
					return source;
				}

				Pixmap< precision_t > output{source.width(), source.height(), source.channelMode()};

				const auto elementCount = source.elementCount();
				const auto stride = source.colorCount();

				const auto & dataSrc = source.data();
				auto & dataDst = output.data();

				switch ( source.channelMode() )
				{
					case ChannelMode::RGB :
						for ( size_t index = 0; index < elementCount; index += stride )
						{
							/* RGB -> BGR */
							dataDst[index] = dataSrc[index+2];
							dataDst[index+1] = dataSrc[index+1];
							dataDst[index+2] = dataSrc[index];
						}
						break;

					case ChannelMode::RGBA :
						if ( swapAlpha )
						{
							for ( size_t index = 0; index < elementCount; index += stride )
							{
								/* RGBA -> ABGR */
								dataDst[index] = dataSrc[index+3];
								dataDst[index+1] = dataSrc[index+2];
								dataDst[index+2] = dataSrc[index+1];
								dataDst[index+3] = dataSrc[index];
							}
						}
						else
						{
							for ( size_t index = 0; index < elementCount; index += stride )
							{
								/* RGB -> BGR */
								dataDst[index] = dataSrc[index+2];
								dataDst[index+1] = dataSrc[index+1];
								dataDst[index+2] = dataSrc[index];

								/* Keeping alpha. */
								dataDst[index+3] = dataSrc[index+3];
							}
						}
						break;

					case ChannelMode::Grayscale :
					case ChannelMode::GrayscaleAlpha :
						/* NOTE: should never happen */
						return source;

					default:
						return {};
				}

				return output;
			}

			/**
			 * @brief Copies a clipped area of the source pixmap to a clipped area of the target pixmap.
			 * @warning Pixmaps involved must have the same color count.
			 * @param source A reference to a source pixmap.
			 * @param sourceClip A reference to an area on source pixmap.
			 * @param destinationClip A reference to an area on target pixmap.
			 * @return bool
			 */
			bool
			blit (const Pixmap< precision_t > & source, const Area< size_t > & sourceClip, const Area< size_t > & destinationClip) const noexcept
			{
				if ( !Processor::checkPixmapClipping(source, sourceClip) && !Processor::checkPixmapClipping(m_target, destinationClip) )
				{
					return false;
				}

				/* NOTE: If both pixmap have the same channel mode, we can perform the blit operation ! */
				if ( source.channelMode() != m_target.channelMode() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", the pixmaps must have the same channel mode in order to make a blit operation !" "\n";

					return false;
				}

				const auto pixelSize = m_target.colorCount() * sizeof(precision_t);
				const auto rowSize = destinationClip.width() * pixelSize;

				for ( size_t destinationY = 0; destinationY < destinationClip.height(); destinationY++ )
				{
					const auto sourceIndex = ((sourceClip.offsetY() + destinationY) * source.width() + sourceClip.offsetX()) * pixelSize;
					const auto destinationIndex = ((destinationClip.offsetY() + destinationY) * m_target.width() + destinationClip.offsetX()) * pixelSize;

					std::memcpy(m_target.data().data() + destinationIndex, source.data().data() + sourceIndex, rowSize);
				}

				m_target.setRegionAsUpdated(destinationClip);

				return true;
			}

			/**
			 * @brief Copies the source pixmap to the target pixmap.
			 * @param source A reference to a source pixmap.
			 */
			bool
			blit (const Pixmap< precision_t > & source) const noexcept
			{
				const auto sourceArea = source.area();

				return this->blit(source, sourceArea, sourceArea);
			}

			/**
			 * @brief Copies the source pixmap to a clipped area of the target pixmap.
			 * @warning Pixmaps involved must have the same color count.
			 * @param source A reference to a source pixmap.
			 * @param destinationClip A reference to an area on target pixmap.
			 * @return bool
			 */
			bool
			blit (const Pixmap< precision_t > & source, const Area< size_t > & destinationClip) const noexcept
			{
				return this->blit(source, {source.width(), source.height()}, destinationClip);
			}

			/**
			 * @brief Copies raw data to a clipped area of the target pixmap.
			 * @warning Be sure to have enough data in the pointer.
			 * @param rawData A reference to a structure of raw data.
			 * @param sourceClip A reference to an area on source pixmap.
			 * @param destinationClip A reference to an area on target pixmap.
			 * @return bool
			 */
			bool
			blit (const RawPixmapData< precision_t > & rawData, const Area< size_t > & sourceClip, const Area< size_t > & destinationClip) const noexcept
			{
				if ( sourceClip.isOutside(rawData.width, rawData.height) )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", the clipping area is outside the pixmap !" "\n";

					return false;
				}

				if ( !Processor::checkPixmapClipping(m_target, destinationClip) )
				{
					return false;
				}

				/* NOTE: If both pixmap have the same channel mode, we can perform the blit operation ! */
				if ( rawData.colorCount != m_target.colorCount() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", the pixmaps must have the same channel mode in order to make a blit operation !" "\n";

					return false;
				}

				const auto pixelSize = m_target.colorCount() * sizeof(precision_t);
				const auto rowSize = destinationClip.width() * pixelSize;

				for ( size_t destinationY = 0; destinationY < destinationClip.height(); destinationY++ )
				{
					const auto sourceIndex = ((sourceClip.offsetY() + destinationY) * rawData.width + sourceClip.offsetX()) * pixelSize;
					const auto destinationIndex = ((destinationClip.offsetY() + destinationY) * m_target.width() + destinationClip.offsetX()) * pixelSize;

					std::memcpy(m_target.data().data() + destinationIndex, rawData.pointer + sourceIndex, rowSize);
				}

				m_target.setRegionAsUpdated(destinationClip);

				return true;
			}

			/**
			 * @brief Copies raw data to a clipped area of the target pixmap.
			 * @warning Be sure to have enough data in the pointer.
			 * @param rawData A reference to a structure of raw data.
			 * @param clip A reference to an area on target pixmap. This will be used as the source clip and the destination clip.
			 * @return bool
			 */
			bool
			blit (const RawPixmapData< precision_t > & rawData, const Area< size_t > & clip) const noexcept
			{
				return this->blit(rawData, clip, clip);
			}

			/**
			 * @brief Copies a clipped area of the source pixmap to a clipped area of the target pixmap.
			 * @param source A reference to a source pixmap.
			 * @param sourceClip A reference to an area on source pixmap.
			 * @param destinationClip A reference to an area on target pixmap.
			 * @param mode Set the copy technic. Default: Replace.
			 * @param opacity A global opacity. Default 1.0.
			 * @return bool
			 */
			bool
			copy (const Pixmap< precision_t > & source, Area< size_t > sourceClip, Area< size_t > destinationClip, DrawPixelMode mode = DrawPixelMode::Replace, float opacity = 1.0F) const noexcept
			{
				/* NOTE: Check if we can replace the copy operation by a blit operation (much faster). */
				if (
					mode == DrawPixelMode::Replace &&
					source.channelMode() != m_target.channelMode() &&
					sourceClip.width() != destinationClip.width() &&
					sourceClip.height() != destinationClip.height()
				)
				{
					return this->blit(source, sourceClip, destinationClip);
				}

				if ( !Processor::checkPixmapClipping(source, sourceClip) && !Processor::checkPixmapClipping(m_target, destinationClip) )
				{
					return false;
				}

				for ( size_t y = 0; y < destinationClip.height(); y++ )
				{
					const auto sourceY = sourceClip.offsetY() + y;
					const auto destinationY = destinationClip.offsetY() + y;

					for ( size_t x = 0; x < destinationClip.width(); x++ )
					{
						const auto sourceX = sourceClip.offsetX() + x;
						const auto destinationX = destinationClip.offsetX() + x;

						m_target.blendPixel(destinationX, destinationY, source.pixel(sourceX, sourceY), mode, opacity);
					}
				}

				m_target.setRegionAsUpdated(destinationClip);

				return true;
			}

			/**
			 * @brief Copies the source pixmap to a clipped area of the target pixmap.
			 * @note The source pixmap will be used from top-left corner.
			 * @param source A reference to a source pixmap.
			 * @param mode Set the copy technic. Default: Replace.
			 * @param opacity A global opacity. Default 1.0.
			 * @return bool
			 */
			bool
			copy (const Pixmap< precision_t > & source, DrawPixelMode mode = DrawPixelMode::Replace, float opacity = 1.0F) const noexcept
			{
				const auto sourceArea = source.area();

				return this->copy(source, sourceArea, sourceArea, mode, opacity);
			}

			/**
			 * @brief Copies the source pixmap to a clipped area of the target pixmap.
			 * @note The source pixmap will be used from top-left corner.
			 * @param source A reference to a source pixmap.
			 * @param destinationClip A reference to an area on target pixmap.
			 * @param mode Set the copy technic. Default: Replace.
			 * @param opacity A global opacity. Default 1.0.
			 * @return bool
			 */
			bool
			copy (const Pixmap< precision_t > & source, const Area< size_t > & destinationClip, DrawPixelMode mode = DrawPixelMode::Replace, float opacity = 1.0F) const noexcept
			{
				return this->copy(source, source.area(), destinationClip, mode, opacity);
			}

			/**
			 * @brief Copies the source pixmap to a clipped area of the target pixmap.
			 * @note The source pixmap will be used from top-left corner.
			 * @param source A reference to a source pixmap.
			 * @param xPosition The position in X where to execute the copy.
			 * @param yPosition The position in Y where to execute the copy.
			 * @param mode Set the copy technic. Default: Replace.
			 * @param opacity A global opacity. Default 1.0.
			 * @return bool
			 */
			bool
			copy (const Pixmap< precision_t > & source, int xPosition, int yPosition, DrawPixelMode mode = DrawPixelMode::Replace, float opacity = 1.0F) const noexcept
			{
				Area< size_t > sourceClip;
				Area< size_t > destinationClip;

				if ( xPosition < 0 )
				{
					const auto shiftSize = static_cast< size_t >(std::abs(xPosition));

					if ( shiftSize >= source.width() )
					{
						std::cerr << __PRETTY_FUNCTION__ << ", the source pixmap do not lie in target pixmap on X axis !" "\n";

						return false;
					}

					const auto newWidth = source.width() - shiftSize;

					sourceClip.setOffsetX(shiftSize);
					sourceClip.setWidth(newWidth);

					destinationClip.setWidth(newWidth);
				}
				else
				{
					sourceClip.setWidth(source.width());

					destinationClip.setOffsetX(static_cast< size_t >(xPosition));
					destinationClip.setWidth(source.width());
				}

				if ( yPosition < 0 )
				{
					const auto shiftSize = static_cast< size_t >(std::abs(yPosition));

					if ( shiftSize >= source.height() )
					{
						std::cerr << __PRETTY_FUNCTION__ << ", the source pixmap do not lie in target pixmap on Y axis !" "\n";

						return false;
					}

					const auto newHeight = source.height() - shiftSize;

					sourceClip.setOffsetY(shiftSize);
					sourceClip.setHeight(newHeight);

					destinationClip.setHeight(newHeight);
				}
				else
				{
					sourceClip.setHeight(source.height());

					destinationClip.setOffsetY(static_cast< size_t >(yPosition));
					destinationClip.setHeight(source.height());
				}

				return this->copy(source, sourceClip, destinationClip, mode, opacity);
			}

			/**
			 * @brief Copies the source pixmap to a clipped area of the target pixmap.
			 * @note The source pixmap will be used from top-left corner.
			 * @param source A reference to a source pixmap.
			 * @param position A reference to a vector.
			 * @param mode Set the copy technic. Default: Replace.
			 * @param opacity A global opacity. Default 1.0.
			 * @return bool
			 */
			bool
			copy (const Pixmap< precision_t > & source, const Math::Vector< 2, int > & position, DrawPixelMode mode = DrawPixelMode::Replace, float opacity = 1.0F) const noexcept
			{
				return this->copy(source, source.area(), position.x(), position.y(), mode, opacity);
			}

			/**
			 * @brief Copies a colored area to the target pixmap.
			 * @tparam colorData_t The color data type. Default float.
			 * @param color A reference to a color.
			 * @param clip A reference to an area.
			 * @param mode Set the copy technic. Default: Replace.
			 * @param opacity A global opacity. Default 1.0.
			 * @return bool
			 */
			template< typename colorData_t = float >
			bool
			copy (const Color< colorData_t > & color, const Area< size_t > & clip, DrawPixelMode mode = DrawPixelMode::Replace, float opacity = 1.0F) const noexcept
			{
				if ( !Processor::checkPixmapClipping(m_target, clip) )
				{
					return false;
				}

				for ( size_t y = 0; y < clip.height(); y++ )
				{
					const auto destinationY = clip.offsetY() + y;

					for ( size_t x = 0; x < clip.width(); x++ )
					{
						const auto destinationX = clip.offsetX() + x;

						m_target.blendPixel(destinationX, destinationY, color, mode, opacity);
					}
				}

				m_target.setRegionAsUpdated(clip);

				return true;
			}

			/**
			 * @brief Copies with a stencil mask a clipped area of the source pixmap to a clipped area of the target pixmap.
			 * @note The source pixmap will be used from top-left corner.
			 * @warning The mask pixmap must be a grayscale.
			 * @param source A reference to a source pixmap.
			 * @param sourceClip A reference to an area on source pixmap.
			 * @param destinationClip A reference to an area on target pixmap.
			 * @param mask A reference to a pixmap to act as the stencil mask.
			 * @param mode Set the copy technic. Default: Replace.
			 * @return bool
			 */
			bool
			stencil (const Pixmap< precision_t > & source, Area< size_t > sourceClip, Area< size_t > destinationClip, const Pixmap< precision_t > & mask, DrawPixelMode mode = DrawPixelMode::Replace) const noexcept
			{
				if ( !Processor::checkPixmapClipping(source, sourceClip) && !Processor::checkPixmapClipping(m_target, destinationClip) )
				{
					return false;
				}

				if ( !mask.isValid() || !mask.isGrayScale() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", mask pixmap is invalid !" "\n";

					return false;
				}

				const auto rowPixelCount = destinationClip.width();

				for ( size_t row = 0; row < destinationClip.height(); row++ )
				{
					const auto sourceIndex = (((sourceClip.offsetY() + row) * source.width()) + sourceClip.offsetX());
					const auto destinationIndex = (((destinationClip.offsetY() + row) * m_target.width()) + destinationClip.offsetX());

					/* FIXME: Check the value of the mask. */
					for ( size_t pixel = 0; pixel < rowPixelCount; ++pixel )
					{
						m_target.blendPixel(destinationIndex + pixel, row, source.pixel(sourceIndex + pixel, row), mode);
					}
				}

				m_target.setRegionAsUpdated(destinationClip);

				return true;
			}

			/**
			 * @brief Copies with a stencil mask the source pixmap to a clipped area of the target pixmap.
			 * @note The source pixmap will be used from top-left corner.
			 * @warning The mask pixmap must be a grayscale.
			 * @param source A reference to a source pixmap.
			 * @param clip A reference to an area on target pixmap.
			 * @param mask A reference to a pixmap to act as the stencil mask.
			 * @param mode Set the copy technic. Default: Replace.
			 * @param opacity A global opacity. Default 1.0.
			 * @return bool
			 */
			bool
			stencil (const Pixmap< precision_t > & source, const Area< size_t > & clip, const Pixmap< precision_t > & mask, DrawPixelMode mode = DrawPixelMode::Replace, float opacity = 1.0F) const noexcept
			{
				return this->stencil(source, {source.width(), source.height()}, clip, mask, mode, opacity);
			}

			/**
			 * @brief Copies a colored area with a stencil mask to the target pixmap.
			 * @tparam colorData_t The color data type. Default float.
			 * @param color A reference to a color.
			 * @param clip A reference to an area.
			 * @param mode Set the copy technic. Default: Replace.
			 * @param mask A reference to a pixmap to act as the stencil mask.
			 * @param opacity A global opacity. Default 1.0.
			 * @return bool
			 */
			template< typename colorData_t = float >
			bool
			stencil (const Color< colorData_t > & /*color*/, const Area< size_t > & /*clip*/, const Pixmap< precision_t > & /*mask*/, DrawPixelMode /*mode*/ = DrawPixelMode::Replace, float /*opacity*/ = 1.0F) const noexcept
			{
				// FIXME: TODO ...

				return false;
			}

		private:

			/**
			 * @brief Checks whether the targeted Pixmap in the processor is present and valid.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			checkPixmap () const noexcept
			{
				if ( !m_target.isValid() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", target pixmap is invalid !" "\n";

					return false;
				}

				return true;
			}

			/**
			 * @brief Checks the clipping area within a pixmap.
			 * @param pixmap A reference to a pixmap.
			 * @param clip A reference to an area.
			 * @return bool
			 */
			[[nodiscard]]
			static
			bool
			checkPixmapClipping (const Pixmap< precision_t > & pixmap, const Area< size_t > & clip) noexcept
			{
				if ( !pixmap.isValid() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", the pixmap is invalid !" "\n";

					return false;
				}

				if ( !clip.isValid() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", the clipping area is invalid !" "\n";

					return false;
				}

				if ( clip.isOutside(pixmap.width(), pixmap.height()) )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", the clipping area is outside the pixmap !" "\n";

					return false;
				}

				return true;
			}

			/**
			 * @brief Checks the clipping area within a pixmap and clamps it on overlapping.
			 * @param pixmap A reference to a pixmap.
			 * @param clip A reference to an area.
			 * @return bool
			 */
			[[nodiscard]]
			static
			bool
			checkPixmapClipping (const Pixmap< precision_t > & pixmap, Area< size_t > & clip) noexcept
			{
				if ( !Processor::checkPixmapClipping(pixmap, static_cast< const Area< size_t > & >(clip)) )
				{
					return false;
				}

				/* NOTE: Crop the width and height if overflow the source pixmap. */
				if ( clip.cropOnOverflow(pixmap.width(), pixmap.height()) )
				{
					std::cout << __PRETTY_FUNCTION__ << ", source area overflow fixed to " << clip << " !" "\n";
				}

				return true;
			}

			/**
			 * @brief Clamps segment point to the pixmap boundaries.
			 * @param pointA A reference to the first point of the segment.
			 * @param pointB A reference to the second point of the segment.
			 * @return bool
			 */
			bool
			clampSegmentPoint (Math::Vector< 2, int > & pointA, const Math::Vector< 2, int > & pointB) const noexcept
			{
				const auto width = static_cast< int >(m_target.width());
				const auto height = static_cast< int >(m_target.height());

				if ( pointA[Math::X] < 0 || pointA[Math::Y] < 0 )
				{
					auto intersection = Math::Line< float >::findIntersection(
						0.0F, 0.0F,
						0.0F, height - 1.0F,
						static_cast< float >(pointA[Math::X]), static_cast< float >(pointA[Math::Y]),
						static_cast< float >(pointB[Math::X]), static_cast< float >(pointB[Math::Y])
					);

					auto x = static_cast< int >(std::roundf(intersection[Math::X]));
					auto y = static_cast< int >(std::roundf(intersection[Math::Y]));

					if ( x >= 0 && y >= 0 && x < width && y < height )
					{
						pointA[Math::X] = x;
						pointA[Math::Y] = y;

						return true;
					}

					intersection = Math::Line< float >::findIntersection(
						0.0F, 0.0F,
						width - 1.0F, 0.0F,
						static_cast< float >(pointA[Math::X]), static_cast< float >(pointA[Math::Y]),
						static_cast< float >(pointB[Math::X]), static_cast< float >(pointB[Math::Y])
					);

					x = static_cast< int >(std::roundf(intersection[Math::X]));
					y = static_cast< int >(std::roundf(intersection[Math::Y]));

					if ( x >= 0 && y >= 0 && x < width && y < height )
					{
						pointA[Math::X] = x;
						pointA[Math::Y] = y;

						return true;
					}

					return false;
				}

				if ( pointA[Math::X] > width || pointA[Math::Y] > height )
				{
					auto intersection = Math::Line< float >::findIntersection(
						0.0F, height - 1.0F,
						width - 1.0F, height - 1.0F,
						static_cast< float >(pointA[Math::X]), static_cast< float >(pointA[Math::Y]),
						static_cast< float >(pointB[Math::X]), static_cast< float >(pointB[Math::Y])
					);

					auto x = static_cast< int >(std::roundf(intersection[Math::X]));
					auto y = static_cast< int >(std::roundf(intersection[Math::Y]));

					if ( x >= 0 && y >= 0 && x < width && y < height )
					{
						pointA[Math::X] = x;
						pointA[Math::Y] = y;

						return true;
					}

					intersection = Math::Line< float >::findIntersection(
						width - 1.0F, 0.0F,
						width - 1.0F, height - 1.0F,
						static_cast< float >(pointA[Math::X]), static_cast< float >(pointA[Math::Y]),
						static_cast< float >(pointB[Math::X]), static_cast< float >(pointB[Math::Y])
					);

					x = static_cast< int >(std::roundf(intersection[Math::X]));
					y = static_cast< int >(std::roundf(intersection[Math::Y]));

					if ( x >= 0 && y >= 0 && x < width && y < height )
					{
						pointA[Math::X] = x;
						pointA[Math::Y] = y;

						return true;
					}

					return false;
				}

				return true;
			}

			/** @brief Prepares the swap buffer for copy operations. */
			void
			prepareSwapBuffer () noexcept
			{
				const auto size = m_target.bytes();

				if ( m_swapBuffer.size() != size )
				{
					m_swapBuffer.resize(size);
				}
			}

			/**
			 * @brief Swaps between processor buffer data and pixmap data to save results.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			swapBuffers () noexcept
			{
				if ( m_swapBuffer.empty() )
				{
					return false;
				}

				if ( m_swapBuffer.size() != m_target.bytes() )
				{
					return false;
				}

				m_swapBuffer.swap(m_target.data());

				return true;
			}

			/**
			 * @brief Used during linear resize.
			 * @param bottomLeft
			 * @param bottomRight
			 * @param topLeft
			 * @param topRight
			 * @param xFactor
			 * @param yFactor
			 * @return uint8_t
			 */
			[[nodiscard]]
			static
			uint8_t
			bilinearFiltering (uint8_t bottomLeft, uint8_t bottomRight, uint8_t topLeft, uint8_t topRight, float xFactor, float yFactor) noexcept
			{
				return static_cast< uint8_t >(Math::linearInterpolation(
					Math::linearInterpolation(static_cast< float >(bottomLeft), static_cast< float >(bottomRight), xFactor),
					Math::linearInterpolation(static_cast< float >(topLeft), static_cast< float >(topRight), xFactor),
					yFactor
				));
			}

			/**
			 * @brief Mirrors the pixmap in X-Axis.
			 * @param source A reference to the input pixmap.
			 * @param output A reference to the output pixmap.
			 * @return void
			 */
			static
			void
			mirrorX (const Pixmap< precision_t > & source, Pixmap< precision_t > & output) noexcept
			{
				const auto rowElementCount = source.pitch();
				const auto rowCount = source.height();

				/* Copy rows in reversed order to new pixmap. */
				for ( size_t row = 0; row < rowCount; row++ )
				{
					const auto invertedRow = rowCount - (row + 1);

					std::memcpy(output.data().data() + (invertedRow * rowElementCount), source.data().data() + (row * rowElementCount), rowElementCount);
				}
			}

			/**
			 * @brief Mirrors the pixmap in Y-Axis.
			 * @param source A reference to the input pixmap.
			 * @param output A reference to the output pixmap.
			 * @return bool
			 */
			[[nodiscard]]
			static
			bool
			mirrorY (const Pixmap< precision_t > & source, Pixmap< precision_t > & output) noexcept
			{
				const auto rowCount = source.height();
				const auto width = source.width();
				const auto stride = source.colorCount();

				auto & data = output.data();
				const auto & baseData = source.data();

				switch ( source.channelMode() )
				{
					case ChannelMode::Grayscale :
						for ( auto row = 0U; row < rowCount; row++ )
						{
							const auto rowOffset = row * width;

							for ( size_t rowPixel = 0; rowPixel < width; rowPixel++ )
							{
								const auto pixel = rowOffset + rowPixel;
								const auto invertedPixel = rowOffset + (width - (rowPixel + 1));

								data[pixel] = baseData[invertedPixel];
							}
						}
						break;

					case ChannelMode::GrayscaleAlpha :
						for ( auto row = 0U; row < rowCount; row++ )
						{
							const auto rowOffset = row * width * stride;

							for ( size_t rowPixel = 0; rowPixel < width; rowPixel++ )
							{
								const auto pixel = rowOffset + (rowPixel * stride);
								const auto invertedPixel = rowOffset + ((width - (rowPixel + 1)) * stride);

								data[pixel] = baseData[invertedPixel];
								data[pixel+1] = baseData[invertedPixel+1];
							}
						}
						break;

					case ChannelMode::RGB :
						for ( auto row = 0U; row < rowCount; row++ )
						{
							const auto rowOffset = row * width * stride;

							for ( size_t rowPixel = 0; rowPixel < width; rowPixel++ )
							{
								const auto pixel = rowOffset + (rowPixel * stride);
								const auto invertedPixel = rowOffset + ((width - (rowPixel + 1)) * stride);

								data[pixel] = baseData[invertedPixel];
								data[pixel+1] = baseData[invertedPixel+1];
								data[pixel+2] = baseData[invertedPixel+2];
							}
						}
						break;

					case ChannelMode::RGBA :
						for ( auto row = 0U; row < rowCount; row++ )
						{
							const auto rowOffset = row * width * stride;

							for ( size_t rowPixel = 0; rowPixel < width; rowPixel++ )
							{
								const auto pixel = rowOffset + (rowPixel * stride);
								const auto invertedPixel = rowOffset + ((width - (rowPixel + 1)) * stride);

								data[pixel] = baseData[invertedPixel];
								data[pixel+1] = baseData[invertedPixel+1];
								data[pixel+2] = baseData[invertedPixel+2];
								data[pixel+3] = baseData[invertedPixel+3];
							}
						}
						break;

					default:
						return false;
				}

				return true;
			}

			/**
			 * @brief Mirrors the pixmap in both X-Axis and Y-Axis.
			 * @param source A reference to the input pixmap.
			 * @param output A reference to the output pixmap.
			 * @return bool
			 */
			[[nodiscard]]
			static
			bool
			mirrorBoth (const Pixmap< precision_t > & source, Pixmap< precision_t > & output) noexcept
			{
				const auto componentCount = source.elementCount();
				const auto stride = source.colorCount();

				auto & data = output.data();
				const auto & baseData = source.data();

				switch ( source.channelMode() )
				{
					case ChannelMode::Grayscale :
						for ( size_t component = 0; component < componentCount; component++ )
						{
							auto invertedComponent = componentCount - (component + 1);

							data[component] = baseData[invertedComponent];
						}
						break;

					case ChannelMode::GrayscaleAlpha :
						for ( size_t component = 0; component < componentCount; component += stride )
						{
							auto invertedComponent = componentCount - (component + stride);

							data[component] = baseData[invertedComponent];
							data[component+1] = baseData[invertedComponent+1];
						}
						break;

					case ChannelMode::RGB :
						for ( size_t component = 0; component < componentCount; component += stride )
						{
							auto invertedComponent = componentCount - (component + stride);

							data[component] = baseData[invertedComponent];
							data[component+1] = baseData[invertedComponent+1];
							data[component+2] = baseData[invertedComponent+2];
						}
						break;

					case ChannelMode::RGBA :
						for ( size_t component = 0; component < componentCount; component += stride )
						{
							auto invertedComponent = componentCount - (component + stride);

							data[component] = baseData[invertedComponent];
							data[component+1] = baseData[invertedComponent+1];
							data[component+2] = baseData[invertedComponent+2];
							data[component+3] = baseData[invertedComponent+3];
						}
						break;

					default:
						return false;
				}

				return true;
			}

			Pixmap< precision_t > & m_target;
			std::vector< precision_t > m_swapBuffer{};
			FilteringMode m_filteringMode;
	};
}
