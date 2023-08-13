/*
 * Libraries/PixelFactory/Gradient.hpp
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
#include <map>

/* Local inclusions */
#include "Math/Base.hpp"
#include "Color.hpp"

namespace Libraries::PixelFactory
{
	/**
	 * @brief The gradient pixmap class.
	 * @tparam data_t
	 * @tparam colorData_t
	 */
	template<
		typename data_t = float,
		typename colorData_t = float,
		std::enable_if_t< std::is_arithmetic_v< data_t >, bool > = false,
		std::enable_if_t< std::is_floating_point_v< colorData_t >, bool > = false
	>
	class Gradient final
	{
		public:

			/**
			 * @brief Constructs a default gradient.
			 */
			Gradient () noexcept = default;

			/**
			 * @brief Constructs a gradient from two colors.
			 * @param colorAtZero A reference to a color for the execute point.
			 * @param colorAtOne A reference to a color for the end point.
			 */
			Gradient (const Color< colorData_t > & colorAtZero, const Color< colorData_t > & colorAtOne) noexcept
			{
				this->addColorAt(static_cast< data_t >(0), colorAtZero);
				this->addColorAt(static_cast< data_t >(1), colorAtOne);
			}

			/**
			 * @brief Adds a new color to the existing gradient.
			 * @param position A scalar value to place the color in the gradient.
			 * @param color A reference to a color.
			 */
			void
			addColorAt (data_t position, const Color< colorData_t > & color) noexcept
			{
				if ( position < 0 )
				{
					position = 0;
				}
				else if ( position > 1 )
				{
					position = 1;
				}

				m_data.emplace(position, color);
			}

			[[nodiscard]]
			Color< colorData_t >
			colorAt (data_t position) const noexcept
			{
				if ( position < 0 )
				{
					position = 0;
				}
				else if ( position > 1 )
				{
					position = 1;
				}

				auto previousColor = m_data.cbegin();
				auto nextColor = m_data.cbegin();

				for ( auto it = m_data.cbegin(); it != m_data.cend(); ++it )
				{
					if ( position > it->first && position > previousColor->first )
					{
						previousColor = it;
					}

					if ( position < it->first && position < nextColor->first )
					{
						nextColor = it;
					}
				}

				auto newScale = nextColor->first - previousColor->first;
				auto realPosition = (position - previousColor->first) * (static_cast< data_t >(1) / newScale);

				return Color< colorData_t >::interpolate(previousColor->second, nextColor->second, realPosition);
			}

		private:

			std::map< data_t, Color< colorData_t > > m_data{};
	};
}
