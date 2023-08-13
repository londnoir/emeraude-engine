/*
 * Emeraude/Graphics/Geometry/GenerationParameters.hpp
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

/* Local inclusions for inheritances. */
#include "FlagTrait.hpp"

/* Local inclusions for usages. */
#include "PixelFactory/Color.hpp"
#include "Math/Matrix.hpp"
#include "Math/Vector.hpp"
#include "VertexFactory/ShapeBuilderOptions.hpp"

namespace Emeraude::Graphics::Geometry
{
	/**
	 * @brief Defines parameters to generate a geometry with the resource generator.
	 * @extends Libraries::FlagTrait Needs FlagTrait to pass it to generated geometries.
	 */
	class GenerationParameters final : public Libraries::FlagTrait< uint32_t >
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"GenerationParameters"};

			/**
			 * @brief Constructs a generation parameters object.
			 * @param geometryResourceFlagBits Flags value from GeometryFlagBits. Default 0.
			 */
			GenerationParameters (uint32_t geometryResourceFlagBits = 0) noexcept;

			/**
			 * @brief Set the global vertex color for mesh generation.
			 * @note Vertex color attribute must be enabled, this method only change the color.
			 * @param globalVertexColor A reference to a PixelFactory color.
			 * @return void
			 */
			void setGlobalVertexColor (const Libraries::PixelFactory::Color< float > & globalVertexColor) noexcept;

			/**
			 * @brief Applies a transform matrix on the generated resource.
			 * @param transformMatrix A reference to a 4x4 matrix.
			 * @return void
			 */
			void setTransformMatrix (const Libraries::Math::Matrix< 4, float > & transformMatrix) noexcept;

			/**
			 * @brief Sets texture coordinates multipliers.
			 * @param xMultiplier The multiplication factor on the X axis.
			 * @param yMultiplier The multiplication factor on the Y axis. Default same as X.
			 * @param zMultiplier The multiplication factor on the Z axis. Default same as Z.
			 * @return void
			 */
			void setTextureCoordinatesMultiplier (float xMultiplier, float yMultiplier = 0.0F, float zMultiplier = 0.0F) noexcept;

			/**
			 * @brief Sets the geometry flags.
			 * @param geometryResourceFlagBits Flags value from GeometryFlagBits.
			 * @return void
			 */
			void setGeometryFlags (uint32_t geometryResourceFlagBits) noexcept;

			/**
			 * @brief Sets the center of the geometry at bottom.
			 * @param state The state.
			 * @return void
			 */
			void setCenterAtBottom (bool state) noexcept;

			/**
			 * @brief Sets the geometry surface flipping state.
			 * @param state The state.
			 * @return void
			 */
			void setFlipGeometry (bool state) noexcept;

			/**
			 * @brief Returns the global vertex color.
			 * @return const Libraries::PixelFactory::Color< float > &
			 */
			[[nodiscard]]
			const Libraries::PixelFactory::Color< float > & globalVertexColor () const noexcept;

			/**
			 * @brief Returns the transform matrix.
			 * @return const Libraries::Math::Matrix< 4, float > &
			 */
			[[nodiscard]]
			const Libraries::Math::Matrix< 4, float > & transformMatrix () const noexcept;

			/**
			 * @brief Returns the texture coordinate multipliers vector.
			 * @return const Libraries::Math::Vector< 3, float > &
			 */
			[[nodiscard]]
			const Libraries::Math::Vector< 3, float > & textureCoordinatesMultiplier () const noexcept;

			/**
			 * @brief Returns the geometry flags.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t geometryFlags () const noexcept;

			/**
			 * @brief Returns whether the center at bottom option is enabled.
			 * @return bool
			 */
			[[nodiscard]]
			bool isCenteredAtBottom () const noexcept;

			/**
			 * @brief Returns whether the geometry surface flipping is enabled.
			 * @return bool
			 */
			[[nodiscard]]
			bool flipGeometry () const noexcept;

			/**
			 * @brief Returns an unique identifier for these parameters to complete a generated resource name.
			 * @return std::string
			 */
			[[nodiscard]]
			std::string uniqueIdentifier () const noexcept;

			/**
			 * @brief getShapeBuilderOption
			 * @return Libraries::VertexFactory::ShapeBuilderOptions< float >
			 */
			[[nodiscard]]
			Libraries::VertexFactory::ShapeBuilderOptions< float > getShapeBuilderOptions () const noexcept;

		private:

			/* Flag names. */
			static constexpr auto CenterAtBottom = 0UL;
			static constexpr auto FlipGeometry = 1UL;
			static constexpr auto GlobalVertexColorSet = 2UL;

			Libraries::PixelFactory::Color< float > m_globalVertexColor{Libraries::PixelFactory::Magenta};
			Libraries::Math::Matrix< 4, float > m_transformMatrix{};
			Libraries::Math::Vector< 3, float > m_textureCoordinatesMultiplier{1.0F, 1.0F, 1.0F};
			std::array< bool, 8 > m_flags{
				false/*CenterAtBottom*/,
				false/*FlipGeometry*/,
				false/*GlobalVertexColorSet*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
