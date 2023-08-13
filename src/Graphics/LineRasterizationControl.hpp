/*
 * Emeraude/Graphics/LineRasterizationControl.hpp
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
	 * @brief The LineRasterizationControl class
	 */
	class LineRasterizationControl final
	{
		public:

			/** @brief Default constructor. */
			LineRasterizationControl () noexcept = default;

			/**
			 * @brief Enables or disable the line smoothing.
			 * @note When the state is effectively changed, the line width parameter get back to 1.0.
			 * @param state The state.
			 */
			void enableSmoothing (bool state) noexcept;

			/**
			 * @brief Says if the line smoothing is enabled.
			 * @return bool
			 */
			bool isSmoothingEnabled () const noexcept;

			/**
			 * @brief Sets the width of a line. This method can fails for several hardware reasons.
			 * @param width The line width requested. May fails.
			 * @return bool
			 */
			bool setWidth (float width) noexcept;

			/**
			 * @brief Returns the actual line width.
			 * @return float
			 */
			[[nodiscard]]
			float width () const noexcept;
	};
}
