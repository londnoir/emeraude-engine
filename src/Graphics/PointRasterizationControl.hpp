/*
 * Emeraude/Graphics/PointRasterizationControl.hpp
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

namespace Emeraude::Graphics
{
	/**
	 * @brief The point rasterization control class
	 */
	class PointRasterizationControl final
	{
		public:

			/** @brief Default constructor. */
			PointRasterizationControl () noexcept = default;

			/**
			 * @brief Enables or disable the point size used by shading programs.
			 * @note When the state is effectively changed, the point size parameter get back to 1.0.
			 * @param state The state.
			 */
			void enableUseProgram (bool state) noexcept;

			/**
			 * @brief Says if the point size is used by shading programs.
			 * @return bool
			 */
			bool isUseProgramEnabled () const noexcept;

			/**
			 * @brief Sets the size of a point. This method can fails for several hardware reasons.
			 * @param size The size requested. May fails.
			 * @return bool
			 */
			bool setSize (float size) noexcept;

			/**
			 * @brief Returns the actual point size.
			 * @return float
			 */
			float size () const noexcept;

			/**
			 * @brief Sets the fade threshold size.
			 * @param size
			 */
			void setFadeThresholdSize (float size) noexcept;

			/**
			 * @brief Returns the fade threshold size.
			 * @return float
			 */
			float fadeThresholdSize () const noexcept;

			/**
			 * @brief Sets the point sprite coord to upper left or lower left.
			 * @param state True for upper left and false for lower left.
			 */
			void setPointSpriteCoord (bool state) noexcept;

			/**
			 * @brief Returns whether the point sprite coord is upper left else it's lower left.
			 * @return bool
			 */
			bool isPointSpriteCoordIsUpperLeft () noexcept;
	};
}
