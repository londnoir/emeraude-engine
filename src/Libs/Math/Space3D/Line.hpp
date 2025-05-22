/*
* src/Libs/Math/Space3D/Line.hpp
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
#include <sstream>
#include <string>
#include <array>

/* Local inclusions. */
#include "Point.hpp"

namespace EmEn::Libs::Math::Space3D
{
	/**
	 * @brief Class for a line in 3D space.
	 * @tparam precision_t The data precision. Default float.
	 */
	template< typename precision_t = float >
	requires (std::is_floating_point_v< precision_t >)
	class Line final
	{
		public:

			/**
			 * @brief Constructs a default line.
			 */
			Line () noexcept = default;

			/**
			 * @brief Reset the line to null value.
			 * @return void
			 */
			void
			reset () noexcept
			{

			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend
			std::ostream &
			operator<< (std::ostream & out, const Line & obj) noexcept
			{
				return out << "Line (3D) data :\n";
			}

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend
			std::string
			to_string (const Line & obj) noexcept
			{
				std::stringstream output;

				output << obj;

				return output.str();
			}

		private:


	};
}
