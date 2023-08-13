/*
 * Libraries/VertexFactory/Grid.hpp
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
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/* Local inclusions */
#include "PixelFactory/Pixmap.hpp"
#include "DiamondSquare.hpp"
#include "GridQuad.hpp"
#include "Math/Cuboid.hpp"
#include "Math/Sphere.hpp"
#include "PerlinNoise.hpp"

namespace Libraries::VertexFactory
{
	// NOLINTBEGIN(readability-identifier-length, *-magic-numbers)

	/** @brief Mode of applying a transformation on the grid data. */
	enum class Mode
	{
		Replace,
		Add,
		Subtract,
		Multiply,
		Divide
	};

	/**
	 * @brief The grid geometry class.
	 * @tparam type_t The precision of the data.
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	class Grid final
	{
		public:

			/**
			 * @brief Constructs a grid.
			 */
			Grid () noexcept = default;

			/**
			 * @brief Reserves data for a new grid.
			 * @note All parameter is for one dimension, because a Grid is always a square.
			 * @param size The size of the grid or a cell grid depending of the third parameter.
			 * @param division The number of cell per dimension (square).
			 * @param isSizeForCell Tells if the size parameter is the size of a cell or the whole grid.
			 * @return bool
			 */
			bool
			initializeData (type_t size, size_t division, bool isSizeForCell = false) noexcept
			{
				if ( division == 0 )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", division parameter must be at least 1 !" "\n";

					return false;
				}

				if ( size < 0 )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", size parameter must be positive !" "\n";

					return false;
				}

				/* To be sure. */
				this->clear();

				m_squaredQuadCount = division;
				m_squaredPointCount = division + 1;
				m_pointHeights.resize(this->pointCount(), 0);

#ifdef VERTEXFACTORY_DEBUG
				/* Shows memory usage */
				auto memoryAllocated = m_heights.size() * sizeof(type_t);

				std::cout << "[DEBUG] " << __PRETTY_FUNCTION__ << ", " << ( static_cast< type_t >(memoryAllocated) / 1048576 ) << " Mib allocated." "\n";
#endif

				/* If we specify the size about the division. */
				if ( isSizeForCell )
				{
					m_quadSquaredSize = size;
					m_halfSquaredSize = (m_quadSquaredSize * m_squaredQuadCount) * static_cast< type_t >(0.5);
				}
				else
				{
					m_quadSquaredSize = size / m_squaredQuadCount;
					m_halfSquaredSize = size * static_cast< type_t >(0.5);
				}

				/* Initialize the bounding box for a flat ground. */
				m_boundingBox.set({m_halfSquaredSize, 0, m_halfSquaredSize}, {-m_halfSquaredSize, 0, -m_halfSquaredSize});
				m_boundingSphere.setRadius(m_boundingBox.highestLength() * 0.5);

				return true;
			}

			/**
			 * @brief Applies a pixmap as a height map to the geometry.
			 * @param map A reference to a pixmap.
			 * @param factor The factor of displacement.
			 * @param mode The mode for moving vertices high. Default Replace.
			 * @return void
			 */
			void
			applyDisplacementMapping (const PixelFactory::Pixmap< uint8_t > & map, type_t factor, Mode mode = Mode::Replace) noexcept
			{
				if ( !map.isValid() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", Pixmap is not usable !" "\n";

					return;
				}

				switch ( mode )
				{
					case Mode::Replace :
						this->applyTransformation([this, &map, factor](size_t x, size_t y, type_t u, type_t v) {
							m_pointHeights[this->index(x, y)] = map.cosineSample(u, v).gray() * factor;

							return true;
						});
						break;

					case Mode::Add :
						this->applyTransformation([this, &map, factor](size_t x, size_t y, type_t u, type_t v) {
							m_pointHeights[this->index(x, y)] += map.cosineSample(u, v).gray() * factor;

							return true;
						});
						break;

					case Mode::Subtract :
						this->applyTransformation([this, &map, factor](size_t x, size_t y, type_t u, type_t v) {
							m_pointHeights[this->index(x, y)] -= map.cosineSample(u, v).gray() * factor;

							return true;
						});
						break;

					case Mode::Multiply :
						this->applyTransformation([this, &map, factor](size_t x, size_t y, type_t u, type_t v) {
							m_pointHeights[this->index(x, y)] *= map.cosineSample(u, v).gray() * factor;

							return true;
						});
						break;

					case Mode::Divide :
						this->applyTransformation([this, &map, factor](size_t x, size_t y, type_t u, type_t v) {
							m_pointHeights[this->index(x, y)] /= map.cosineSample(u, v).gray() * factor;

							return true;
						});
						break;
				}
			}

			/**
			 * @brief Applies the perlin noise algorithm on the grid.
			 * @param size The size of the perlin algorithm.
			 * @param factor The factor of displacement.
			 * @param mode The mode for moving vertices high. Default Replace.
			 * @return void
			 */
			void
			applyPerlinNoise (type_t size, type_t factor, Mode mode = Mode::Replace) noexcept
			{
				PerlinNoise< type_t > generator{};

				switch ( mode )
				{
					case Mode::Replace :
						this->applyTransformation([this, size, factor, &generator](size_t x, size_t y, type_t u, type_t v) {
							const auto index = this->index(x, y);

							m_pointHeights[index] = generator.generate(u * size, v * size, 0) * factor;
							m_boundingBox.mergeY(m_pointHeights[index]);

							return true;
						});
						break;

					case Mode::Add :
						this->applyTransformation([this, size, factor, &generator](size_t x, size_t y, type_t u, type_t v) {
							const auto index = this->index(x, y);

							m_pointHeights[index] += generator.generate(u * size, v * size, 0) * factor;
							m_boundingBox.mergeY(m_pointHeights[index]);

							return true;
						});
						break;

					case Mode::Subtract :
						this->applyTransformation([this, size, factor, &generator](size_t x, size_t y, type_t u, type_t v) {
							const auto index = this->index(x, y);

							m_pointHeights[index] -= generator.generate(u * size, v * size, 0) * factor;
							m_boundingBox.mergeY(m_pointHeights[index]);

							return true;
						});
						break;

					case Mode::Multiply :
						this->applyTransformation([this, size, factor, &generator](size_t x, size_t y, type_t u, type_t v) {
							const auto index = this->index(x, y);

							m_pointHeights[index] *= generator.generate(u * size, v * size, 0) * factor;
							m_boundingBox.mergeY(m_pointHeights[index]);

							return true;
						});
						break;

					case Mode::Divide :
						this->applyTransformation([this, size, factor, &generator](size_t x, size_t y, type_t u, type_t v) {
							const auto index = this->index(x, y);

							m_pointHeights[index] /= generator.generate(u * size, v * size, 0) * factor;
							m_boundingBox.mergeY(m_pointHeights[index]);

							return true;
						});
						break;
				}
			}

			/**
			 * @brief Applies the diamond square algorithm on the grid.
			 * @param factor Noise strength.
			 * @param seed Randomize the generation. Default 1.
			 * @param mode The mode for moving vertices high. Default Replace.
			 * @return void
			 */
			void
			applyDiamondSquare (type_t factor, unsigned int seed = 1, Mode mode = Mode::Replace) noexcept
			{
				DiamondSquare< type_t > map{m_squaredPointCount};

				if ( map.generate(seed) )
				{
					switch ( mode )
					{
						case Mode::Replace :
							this->applyTransformation([this, factor, &map](size_t x, size_t y) {
								const auto index = this->index(x, y);

								m_pointHeights[index] = map.value(x, y) * factor;
								m_boundingBox.mergeY(m_pointHeights[index]);

								return true;
							});
							break;

						case Mode::Add :
							this->applyTransformation([this, factor, &map](size_t x, size_t y) {
								const auto index = this->index(x, y);

								m_pointHeights[index] += map.value(x, y) * factor;
								m_boundingBox.mergeY(m_pointHeights[index]);

								return true;
							});
							break;

						case Mode::Subtract :
							this->applyTransformation([this, factor, &map](size_t x, size_t y) {
								const auto index = this->index(x, y);

								m_pointHeights[index] -= map.value(x, y) * factor;
								m_boundingBox.mergeY(m_pointHeights[index]);

								return true;
							});
							break;

						case Mode::Multiply :
							this->applyTransformation([this, factor, &map](size_t x, size_t y) {
								const auto index = this->index(x, y);

								m_pointHeights[index] *= map.value(x, y) * factor;
								m_boundingBox.mergeY(m_pointHeights[index]);

								return true;
							});
							break;

						case Mode::Divide :
							this->applyTransformation([this, factor, &map](size_t x, size_t y) {
								const auto index = this->index(x, y);

								m_pointHeights[index] /= map.value(x, y) * factor;
								m_boundingBox.mergeY(m_pointHeights[index]);

								return true;
							});
							break;
					}
				}
			}

			/**
			 * @brief Multiplies uniformly the heights of the grid.
			 * @param value The scale value.
			 * @return void
			 */
			void
			scale (type_t value) noexcept
			{
				std::transform(m_pointHeights.begin(), m_pointHeights.end(), m_pointHeights.begin(), [value] (auto height) -> type_t {
					return height * value;
				});

				auto maximum = m_boundingBox.maximum();
				auto minimum = m_boundingBox.minimum();

				maximum[Math::Y] *= value;
				minimum[Math::Y] *= value;

				m_boundingBox.set(maximum, minimum);
				m_boundingSphere.setRadius(m_boundingBox.highestLength() * 0.5F);
			}

			/**
			 * @brief Clears the grid data.
			 * @return void
			 */
			void
			clear () noexcept
			{
				m_pointHeights.clear();

				m_squaredQuadCount = 0;
				m_squaredPointCount = 0;

				m_boundingBox.reset();
				m_boundingSphere.reset();
			}

			/**
			 * @brief Sets a multiplier to texture coordinates.
			 * @param UVMultiplier The multiplier in both direction for the texture coordinates.
			 * @return void
			 */
			void
			setUVMultiplier (type_t UVMultiplier) noexcept
			{
				if ( UVMultiplier > 0 )
				{
					m_UMultiplier = UVMultiplier;
					m_VMultiplier = UVMultiplier;
				}
			}

			/**
			 * @brief Sets a multiplier to texture coordinates.
			 * @param UMultiplier The multiplier in X direction for the texture coordinates.
			 * @param VMultiplier The multiplier in Y direction for the texture coordinates.
			 * @return void
			 */
			void
			setUVMultiplier (type_t UMultiplier, type_t VMultiplier) noexcept
			{
				if ( UMultiplier > 0 )
				{
					m_UMultiplier = UMultiplier;
				}

				if ( VMultiplier > 0 )
				{
					m_VMultiplier = VMultiplier;
				}
			}

			/**
			 * @brief Returns the multiplier to the U component of texture coordinates.
			 * @return type_t
			 */
			[[nodiscard]]
			type_t
			UMultiplier () const noexcept
			{
				return m_UMultiplier;
			}

			/**
			 * @brief Returns the multiplier to the V component of texture coordinates.
			 * @return type_t
			 */
			[[nodiscard]]
			type_t
			VMultiplier () const noexcept
			{
				return m_VMultiplier;
			}

			/**
			 * @brief Checks the validity of the data.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isValid () const noexcept
			{
				return !m_pointHeights.empty();
			}

			/**
			 * @brief Checks if the grid data is empty.
			 * @note Inverse of Grid::isValid(). Provided to satisfy C++ conventions.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			empty () const noexcept
			{
				return m_pointHeights.empty();
			}

			/**
			 * @brief Returns a bounding box enclosing the whole grid.
			 * @return const AxisAlignedBoundingBox< type_t > &
			 */
			[[nodiscard]]
			const Math::Cuboid< type_t > &
			boundingBox () const noexcept
			{
				return m_boundingBox;
			}

			/**
			 * @brief Returns the bounding radius.
			 * @return const Sphere< type_t > &
			 */
			[[nodiscard]]
			const Math::Sphere< type_t > &
			boundingSphere () const noexcept
			{
				return m_boundingSphere;
			}

			/**
			 * @brief Returns the squared dimension of the grid.
			 * @return type_t
			 */
			[[nodiscard]]
			type_t
			squaredSize () const noexcept
			{
				return m_halfSquaredSize + m_halfSquaredSize;
			}

			/**
			 * @brief Returns the half squared dimension of the grid.
			 * @note Useful when using coordinates thinking the origin of the grid is at his center.
			 * @return type_t
			 */
			[[nodiscard]]
			type_t
			halfSquaredSize () const noexcept
			{
				return m_halfSquaredSize;
			}

			/**
			 * @brief Returns the size of a grid cell.
			 * @return type_t
			 */
			[[nodiscard]]
			type_t
			quadSize () const noexcept
			{
				return m_quadSquaredSize;
			}

			/**
			 * @brief Returns the height at cell coordinates.
			 * @param x The grid quad index on X axis.
			 * @param y The grid quad index on Y axis.
			 * @return type_t
			 */
			[[nodiscard]]
			type_t
			getHeightAt (size_t x, size_t y) const noexcept
			{
				return m_pointHeights[this->index(x, y)];
			}

			/**
			 * @brief Returns the height at specific coordinates.
			 * @param coordX The coordinate on X axis.
			 * @param coordY The coordinate on Y axis.
			 * @return type_t
			 */
			[[nodiscard]]
			type_t
			getHeightAt (type_t coordX, type_t coordY) const noexcept
			{
				/* If coordinates are outside the grid, we return zero. */
				if ( coordX <= -m_halfSquaredSize || coordX >= m_halfSquaredSize || coordY <= -m_halfSquaredSize || coordY >= m_halfSquaredSize )
				{
					return 0;
				}

				const auto realX = (coordX + m_halfSquaredSize) / m_quadSquaredSize;
				const auto factorX = realX - std::floor(realX);

				const auto realY = (coordY + m_halfSquaredSize) / m_quadSquaredSize;
				const auto factorY = realY - std::floor(realY);

				const auto currentQuad = this->quad(static_cast< size_t >(std::floor(realX)), static_cast< size_t >(std::floor(realY)));

				/* Interpolate height from each corner of the quad. First X axis... */
				const auto top = Math::linearInterpolation(m_pointHeights[currentQuad.topLeftIndex()], m_pointHeights[currentQuad.topRightIndex()], factorX);
				const auto bottom = Math::linearInterpolation(m_pointHeights[currentQuad.bottomLeftIndex()], m_pointHeights[currentQuad.bottomRightIndex()], factorX);

				/* ... then Y axis. */
				return Math::linearInterpolation(top, bottom, factorY);
			}

			/**
			 * @brief Returns the normal vector at cell coordinates.
			 * @param coordX The coordinate on X axis.
			 * @param coordY The coordinate on Y axis.
			 * @return Math::Vector< 3, type_t >
			 */
			[[nodiscard]]
			Math::Vector< 3, type_t >
			getNormalAt (type_t coordX, type_t coordY) const noexcept
			{
				/* If coordinates are outside the grid, we return zero. */
				if ( coordX <= -m_halfSquaredSize || coordX >= m_halfSquaredSize || coordY <= -m_halfSquaredSize || coordY >= m_halfSquaredSize )
				{
					return Math::Vector< 3, type_t>::positiveY();
				}

				const auto realX = (coordX + m_halfSquaredSize) / m_quadSquaredSize;
				const auto factorX = realX - std::floor(realX);

				const auto realY = (coordY + m_halfSquaredSize) / m_quadSquaredSize;
				const auto factorY = realY - std::floor(realY);

				const auto coordQuad = this->quad(static_cast< size_t >(std::floor(realX)), static_cast< size_t >(std::floor(realY)));

				/* Interpolate height from each corner of the quad. First X axis... */
				const auto top = Math::linearInterpolation(this->normal(coordQuad.topLeftIndex()), this->normal(coordQuad.topRightIndex()), factorX);
				const auto bottom = Math::linearInterpolation(this->normal(coordQuad.bottomLeftIndex()), this->normal(coordQuad.bottomRightIndex()), factorX);

				/* ... then Y axis. */
				return Math::linearInterpolation(top, bottom, factorY);
			}

			/**
			 * @brief Returns the point count.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			pointCount () const noexcept
			{
				return m_squaredPointCount * m_squaredPointCount;
			}

			/**
			 * @brief Returns the point count in one dimension.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			squaredPointCount () const noexcept
			{
				return m_squaredPointCount;
			}

			/**
			 * @brief Returns the number of grid cell.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			quadCount () const noexcept
			{
				return m_squaredQuadCount * m_squaredQuadCount;
			}

			/**
			 * @brief Returns the number of grid cell in one dimension.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			squaredQuadCount () const noexcept
			{
				return m_squaredQuadCount;
			}

			/**
			 * @brief Convert XY indexes to buffer index.
			 * @param x The grid quad index on X axis.
			 * @param y The grid quad index on Y axis.
			 * @return size_t
			 */
			[[nodiscard]]
			inline
			size_t
			index (size_t x, size_t y) const noexcept
			{
				return x + (y * m_squaredPointCount);
			}

			/**
			 * @brief Returns the X grid coordinates from grid index.
			 * @param index The grid index.
			 * @return size_t
			 */
			[[nodiscard]]
			inline
			size_t
			x (size_t index) const noexcept
			{
				return index % m_squaredPointCount;
			}
			/**
			 * @brief Returns the Y grid coordinates from grid index.
			 * @param index The grid index.
			 * @return size_t
			 */
			[[nodiscard]]
			inline
			size_t
			y (size_t index) const noexcept
			{
				return static_cast< size_t >(std::floor(index / m_squaredPointCount));
			}

			/**
			 * @brief Returns the quad at grid coordinates.
			 * @param x The grid quad index on X axis.
			 * @param y The grid quad index on Y axis.
			 * @return GridQuad
			 */
			[[nodiscard]]
			GridQuad
			quad (size_t x, size_t y) const noexcept
			{
				if ( x >= m_squaredQuadCount || y >= m_squaredQuadCount )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", quad indexes X:" << x << ", Y:" << y << " overflows " << m_squaredQuadCount << " !" "\n";

					return {};
				}

				/* NOTE: We add y at the end to correspond to vertex indices,
				 * because quads are composed of 4 vertices. */
				const auto base = x + (y * m_squaredQuadCount) + y;

				return {
					base,
					base + m_squaredPointCount,
					/* NOTE: this is only left plus one. */
					base + 1,
					base + m_squaredPointCount + 1
				};
			}

			/**
			 * @brief Returns the nearest quad at coordinates.
			 * @param x
			 * @param y
			 * @return GridQuad
			 */
			[[nodiscard]]
			GridQuad
			nearestQuad (type_t coordX, type_t coordY) const noexcept
			{
				const auto realX = std::floor((coordX + m_halfSquaredSize) / m_quadSquaredSize);
				const auto realY = std::floor((coordY + m_halfSquaredSize) / m_quadSquaredSize);

				return this->quad(static_cast< size_t >(realX), static_cast< size_t >(realY));
			}

			/**
			 * @brief Builds position vectors.
			 * @return std::vector< type_t >
			 */
			std::vector< type_t >
			buildPositionVector () const noexcept
			{
				std::vector< type_t > vector{m_squaredPointCount * m_squaredPointCount * 3};

				#pragma omp simd
				for ( size_t xIndex = 0; xIndex < m_squaredPointCount; xIndex++ )
				{
					for ( size_t yIndex = 0; yIndex < m_squaredPointCount; yIndex++ )
					{
						vector.push_back((xIndex * m_quadSquaredSize) - m_halfSquaredSize);
						vector.push_back(m_pointHeights[this->index(xIndex, yIndex)]);
						vector.push_back((yIndex * m_quadSquaredSize) - m_halfSquaredSize);
					}
				}

				return vector;
			}

			/**
			 * @brief Returns the position vector at grid coordinates.
			 * @param x The grid quad index on X axis.
			 * @param y The grid quad index on Y axis.
			 * @return Math::Vector< 3, type_t >
			 */
			[[nodiscard]]
			inline
			Math::Vector< 3, type_t >
			position (size_t x, size_t y) const noexcept
			{
				return {
					(x * m_quadSquaredSize) - m_halfSquaredSize,
					m_pointHeights[this->index(x, y)],
					(y * m_quadSquaredSize) - m_halfSquaredSize
				};
			}

			/**
			 * @brief Returns the position vector at grid cell index.
			 * @param index The grid cell index.
			 * @return Math::Vector< 3, type_t >
			 */
			[[nodiscard]]
			inline
			Math::Vector< 3, type_t >
			position (size_t index) const noexcept
			{
				return this->position(this->x(index), this->y(index));
			}

			/**
			 * @brief Returns the normal vector at grid coordinates.
			 * @param x The grid quad index on X axis.
			 * @param y The grid quad index on Y axis.
			 * @param thisPosition The reference to the position at this same spot.
			 * @return Math::Vector< 3, type_t >
			 */
			[[nodiscard]]
			Math::Vector< 3, type_t >
			normal (size_t x, size_t y, const Math::Vector< 3, type_t > & thisPosition) const noexcept
			{
				Math::Vector< 3, type_t > normal{};

				/* Checks the two quads top to this position.
				 * NOTE: y:0 = top. */
				if ( y > 0 )
				{
					const auto top = this->position(x, y - 1);

					/* Top-Left quad. */
					if ( x > 0 )
					{
						normal += Math::Vector< 3, type_t >::normal(thisPosition, top, this->position(x - 1, y));
					}

					/* Top-Right quad. */
					if ( x < (m_squaredPointCount - 1) )
					{
						normal += Math::Vector< 3, type_t >::normal(thisPosition, this->position(x + 1, y), top);
					}
				}

				/* Checks the two quads bottom to this position. */
				if ( y < (m_squaredPointCount - 1) )
				{
					const auto bottom = this->position(x, y + 1);

					/* Bottom-Left quad. */
					if ( x > 0 )
					{
						normal += Math::Vector< 3, type_t >::normal(thisPosition, this->position(x - 1, y), bottom);
					}

					/* Bottom-Right quad. */
					if ( x < (m_squaredPointCount - 1) )
					{
						normal += Math::Vector< 3, type_t >::normal(thisPosition, bottom, this->position(x + 1, y));
					}
				}

				return normal.normalize();
			}

			/**
			 * @brief Returns the normal vector at grid coordinates.
			 * @param x The grid quad index on X axis.
			 * @param y The grid quad index on Y axis.
			 * @return Math::Vector< 3, type_t >
			 */
			[[nodiscard]]
			inline
			Math::Vector< 3, type_t >
			normal (size_t x, size_t y) const noexcept
			{
				return this->normal(x, y, this->position(x, y));
			}

			/**
			 * @brief Returns the normal vector at grid index.
			 * @param index The grid quad index.
			 * @param thisPosition The reference to the position at this same spot.
			 * @return Math::Vector< 3, type_t >
			 */
			[[nodiscard]]
			inline
			Math::Vector< 3, type_t >
			normal (size_t index, const Math::Vector< 3, type_t > & thisPosition) const noexcept
			{
				return this->normal(this->x(index), this->y(index), thisPosition);
			}

			/**
			 * @brief Returns the normal vector at grid index.
			 * @param index The grid quad index.
			 * @return Math::Vector< 3, type_t >
			 */
			[[nodiscard]]
			Math::Vector< 3, type_t >
			normal (size_t index) const noexcept
			{
				const auto xIndex = this->x(index);
				const auto yIndex = this->y(index);

				return this->normal(xIndex, yIndex, this->position(xIndex, yIndex));
			}

			/**
			 * @brief Returns the tangent vector at grid coordinates.
			 * @param x The grid quad index on X axis.
			 * @param y The grid quad index on Y axis.
			 * @param thisPosition The reference to the position at this same spot.
			 * @param thisUV The reference to the texture coordinates at this same spot.
			 * @return Math::Vector< 3, type_t >
			 */
			[[nodiscard]]
			Math::Vector< 3, type_t >
			tangent (size_t x, size_t y, const Math::Vector< 3, type_t > & thisPosition, const Math::Vector< 2, type_t > & thisUV) const
			{
				Math::Vector< 3, type_t > tangent{};

				/* Checks the two quads top to this position.
				 * NOTE: y:0 = top. */
				if ( y > 0 )
				{
					const auto topPosition = this->position(x, y - 1);
					const auto topUV = this->textureCoordinates2D(x, y - 1);

					/* Top-Left quad. */
					if ( x > 0 )
					{
						tangent += Math::Vector< 3, type_t >::tangent(
							thisPosition,
							thisUV,
							this->position(x - 1, y),
							this->textureCoordinates2D(x - 1, y),
							topPosition,
							topUV
						);
					}

					/* Top-Right quad. */
					if ( x < (m_squaredPointCount - 1) )
					{
						tangent += Math::Vector< 3, type_t >::tangent(
							thisPosition,
							thisUV,
							topPosition,
							topUV,
							this->position(x + 1, y),
							this->textureCoordinates2D(x + 1, y)
						);
					}
				}

				/* Checks the two quads bottom to this position. */
				if ( y < (m_squaredPointCount - 1) )
				{
					const auto bottomPosition = this->position(x, y + 1);
					const auto bottomUV = this->textureCoordinates2D(x, y + 1);

					/* Bottom-Left quad. */
					if ( x > 0 )
					{
						tangent += Math::Vector< 3, type_t >::tangent(
							thisPosition,
							thisUV,
							bottomPosition,
							bottomUV,
							this->position(x - 1, y),
							this->textureCoordinates2D(x - 1, y)
						);
					}

					/* Bottom-Right quad. */
					if ( x < (m_squaredPointCount - 1) )
					{
						tangent += Math::Vector< 3, type_t >::tangent(
							thisPosition,
							thisUV,
							this->position(x + 1, y),
							this->textureCoordinates2D(x + 1, y),
							bottomPosition,
							bottomUV
						);
					}
				}

				return tangent.normalize();
			}

			/**
			 * @brief Returns the tangent vector at grid coordinates.
			 * @param x The grid quad index on X axis.
			 * @param y The grid quad index on Y axis.
			 * @return Math::Vector< 3, type_t >
			 */
			[[nodiscard]]
			inline
			Math::Vector< 3, type_t >
			tangent (size_t x, size_t y) const noexcept
			{
				return this->tangent(x, y, this->position(x, y), this->textureCoordinates2D(x, y));
			}

			/**
			 * @brief Returns the tangent vector at grid index.
			 * @param index The grid quad index.
			 * @return Math::Vector< 3, type_t >
			 */
			[[nodiscard]]
			Math::Vector< 3, type_t >
			tangent (size_t index) const noexcept
			{
				const auto xIndex = this->x(index);
				const auto yIndex = this->y(index);

				return this->tangent(xIndex, yIndex, this->position(xIndex, yIndex), this->textureCoordinates2D(xIndex, yIndex));
			}

			/**
			 * @brief Returns the tangent vector at grid index.
			 * @param index The grid quad index.
			 * @param thisPosition The reference to the position at this same spot.
			 * @param thisUV The reference to the texture coordinates at this same spot.
			 * @return Math::Vector< 3, type_t >
			 */
			[[nodiscard]]
			inline
			Math::Vector< 3, type_t >
			tangent (size_t index, const Math::Vector< 3, type_t > & thisPosition, const Math::Vector< 2, type_t > & thisUV) const noexcept
			{
				return this->tangent(this->x(index), this->y(index), thisPosition, thisUV);
			}

			/**
			 * @brief Returns a 2D texture coordinates at grid coordinates.
			 * @param x The grid quad index on X axis.
			 * @param y The grid quad index on Y axis.
			 * @return Math::Vector< 2, type_t >
			 */
			[[nodiscard]]
			Math::Vector< 2, type_t >
			textureCoordinates2D (size_t x, size_t y) const noexcept
			{
				const auto div = static_cast< type_t >(m_squaredQuadCount);

				return {
					(static_cast< type_t >(x) / div) * m_UMultiplier,
					(1 - (static_cast< type_t >(y) / div)) * m_VMultiplier
				};
			}

			/**
			 * @brief Returns a 2D texture coordinates at grid index.
			 * @param index The grid quad index.
			 * @return Math::Vector< 2, type_t >
			 */
			[[nodiscard]]
			inline
			Math::Vector< 2, type_t >
			textureCoordinates2D (size_t index) const noexcept
			{
				return this->textureCoordinates2D(this->x(index), this->y(index));
			}

			/**
			 * @brief Returns a 3D texture coordinates at grid coordinates.
			 * @param x The grid quad index on X axis.
			 * @param y The grid quad index on Y axis.
			 * @return Math::Vector< 2, type_t >
			 */
			[[nodiscard]]
			Math::Vector< 3, type_t >
			textureCoordinates3D (size_t x, size_t y) const noexcept
			{
				const auto div = static_cast< type_t >(m_squaredQuadCount);

				return {
					(static_cast< type_t >(x) / div) * m_UMultiplier,
					(1 - (static_cast< type_t >(y) / div)) * m_VMultiplier,
					(m_pointHeights[this->index(x, y)] - m_boundingBox.minimum()[Math::Y]) / m_boundingBox.height()
				};
			}

			/**
			 * @brief Returns a 3D texture coordinates at grid index.
			 * @param index The grid quad index.
			 * @return Math::Vector< 3, type_t >
			 */
			[[nodiscard]]
			inline
			Math::Vector< 3, type_t >
			textureCoordinates3D (size_t index) const noexcept
			{
				return this->textureCoordinates3D(this->x(index), this->y(index));
			}

			/**
			 * @brief Returns a vertex color at grid index.
			 * @param index The grid quad index.
			 * @param pixmap A reference to a pixmap.
			 * @return PixelFactory::Color< float >
			 */
			[[nodiscard]]
			PixelFactory::Color< float >
			vertexColor (size_t index, const PixelFactory::Pixmap< uint8_t > & pixmap) const noexcept
			{
				const auto u = static_cast< type_t >(this->x(index)) / static_cast< type_t >(m_squaredPointCount);
				const auto v = static_cast< type_t >(this->y(index)) / static_cast< type_t >(m_squaredPointCount);

				return pixmap.linearSample(u, v);
			}

			/**
			 * @brief Returns the list of heights;
			 * @return const std::vector< type_t > &
			 */
			const std::vector< type_t > &
			heights () const noexcept
			{
				return m_pointHeights;
			}

			/**
			 * @brief Returns the mode in enum.
			 * @param string A reference to a string.
			 * @return Mode
			 */
			static
			Mode
			getMode (const std::string & string) noexcept
			{
				if ( string == "Add" )
				{
					return Mode::Add;
				}

				if ( string == "Subtract" )
				{
					return Mode::Subtract;
				}

				if ( string == "Multiply" )
				{
					return Mode::Multiply;
				}

				if ( string == "Divide" )
				{
					return Mode::Divide;
				}
				return Mode::Replace;
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return ostream &
			 */
			friend
			std::ostream &
			operator<< (std::ostream & out, const Grid & obj) noexcept
			{
				return out << "Grid data :\n"
					"Quad count : " << obj.quadCount() << "(Squared: " << obj.m_squaredQuadCount << ")\n"
					"Point count : " << obj.pointCount() << "(Squared: " << obj.m_squaredPointCount << ")\n"
					"Vector< type_t >::size() : " << obj.m_pointHeights.size() << "\n"
					"UV multiplier : " << obj.m_UMultiplier << ", " << obj.m_VMultiplier << "\n"
					"Quad size (squared) : " << obj.m_quadSquaredSize << "\n"
					"Grid size (squared) : " << ( obj.m_halfSquaredSize + obj.m_halfSquaredSize ) << "\n"
					"BoundingBox : " << obj.m_boundingBox << "\n"
					"BoundingRadius : " << obj.m_boundingSphere << '\n';
			}

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend
			std::string
			to_string (const Grid & obj) noexcept
			{
				return (std::stringstream{} << obj).str();
			}

		private:

			/**
			 * @brief Applies a transformation on grid data.
			 * @param transform A reference to a lambda.
			 * @return void
			 */
			void
			applyTransformation (const std::function< bool (size_t, size_t, type_t, type_t) > & transform) noexcept
			{
				const auto square = static_cast< type_t >(m_squaredQuadCount);

				/* Loop over Y axis and get the V coordinates. */
				for ( size_t yIndex = 0; yIndex < m_squaredPointCount; yIndex++ )
				{
					const auto v = static_cast< type_t >(yIndex) / square;

					/* Loop over X axis and get the U coordinates. */
					for ( size_t xIndex = 0; xIndex < m_squaredPointCount; xIndex++ )
					{
						const auto u = static_cast< type_t >(xIndex) / square;

						/* Send data to transformation function. */
						if ( !transform(xIndex, yIndex, u, v) )
						{
							std::cerr << __PRETTY_FUNCTION__ << ", transform method failed !" "\n";

							return;
						}
					}
				}
			}

			/**
			 * @brief Applies a transformation on grid data.
			 * @param transform A reference to a lambda.
			 * @return void
			 */
			void
			applyTransformation (const std::function< bool (size_t, size_t) > & transform) noexcept
			{
				/* Loop over Y axis and get the V coordinates. */
				for ( size_t yIndex = 0; yIndex < m_squaredPointCount; yIndex++ )
				{
					/* Loop over X axis and get the U coordinates. */
					for ( size_t xIndex = 0; xIndex < m_squaredPointCount; xIndex++ )
					{
						/* Send data to transformation function. */
						if ( !transform(xIndex, yIndex) )
						{
							std::cerr << __PRETTY_FUNCTION__ << ", transform method failed !" "\n";

							return;
						}
					}
				}
			}

			/**
			 * @brief Updates the bounding box with new data.
			 * @return void
			 */
			void
			updateBoundingBox () noexcept
			{
				m_boundingBox.reset();

				for ( auto height : m_pointHeights )
				{
					m_boundingBox.merge({0.0F, height, 0.0F});
				}
			}

			size_t m_squaredQuadCount = 0;
			/* NOTE: m_squareQuads + 1 */
			size_t m_squaredPointCount = 0;
			std::vector< type_t > m_pointHeights{};
			type_t m_quadSquaredSize = 2;
			type_t m_halfSquaredSize = 1;
			type_t m_UMultiplier = 1;
			type_t m_VMultiplier = 1;
			Math::Cuboid< type_t > m_boundingBox{};
			Math::Sphere< type_t > m_boundingSphere{};
	};

	// NOLINTEND(readability-identifier-length, *-magic-numbers)
}
