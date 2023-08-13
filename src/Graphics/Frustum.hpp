/*
 * Emeraude/Graphics/Frustum.hpp
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
#include <array>
#include <sstream>
#include <string>

/* Local inclusions for usages. */
#include "Math/Matrix.hpp"
#include "Math/Cuboid.hpp"
#include "Math/Plane.hpp"
#include "Math/Sphere.hpp"

namespace Emeraude::Graphics
{
	/**
	 * @brief The Frustum class
	 */
	class Frustum final
	{
		public:

			enum class Result
			{
				Outside,
				Intersect,
				Inside
			};

			static constexpr auto Right = 0;
			static constexpr auto Left = 1;
			static constexpr auto Bottom = 2;
			static constexpr auto Top = 3;
			static constexpr auto Far = 4;
			static constexpr auto Near = 5;

			/** @brief Default constructor. */
			Frustum () noexcept = default;

			/**
			 * @brief Declares the far distance of the frustum.
			 * @note Lazy way of keeping the far distance.
			 * @param farDistance The distance of the camera.
			 * @return void
			 */
			void updateProperties (float farDistance) noexcept;

			/**
			 * @brief Updates the frustum geometry when the camera move.
			 * @param viewProjectionMatrix
			 */
			void update (const Libraries::Math::Matrix< 4, float > & viewProjectionMatrix) noexcept;

			/**
			 * @brief update
			 * @param projection
			 * @param view
			 */
			inline
			void
			update (const Libraries::Math::Matrix< 4, float > & projection, const Libraries::Math::Matrix< 4, float > & view) noexcept
			{
				this->update(projection * view);
			}

			/**
			 * @brief Checks a point against the Frustum.
			 * @param point
			 * @return Result
			 */
			[[nodiscard]]
			Result isCollidingWith (const Libraries::Math::Vector< 3, float > & point) const noexcept;

			/**
			 * @brief Checks a sphere against the Frustum.
			 * @param sphere
			 * @return Result
			 */
			[[nodiscard]]
			Result isCollidingWith (const Libraries::Math::Sphere< float > & sphere) const noexcept;

			/**
			 * @brief Checks an axis aligned bounding box against the Frustum.
			 * @todo FIXME: may be it could be useful to separate Intersect and Inside case ! ² Not perfect...
			 * @param box A reference to an axis aligned bounding box.
			 * @return Result
			 */
			[[nodiscard]]
			Result isCollidingWith (const Libraries::Math::Cuboid< float > & box) const noexcept;

			/**
			 * @brief Checks a ??? against the Frustum.
			 * @param x
			 * @param y
			 * @param z
			 * @param size
			 * @return Result
			 */
			[[nodiscard]]
			Result isCollidingWith (float x, float y, float z, float size) const noexcept;

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const Frustum & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend std::string to_string (const Frustum & obj) noexcept;

			/**
			 * @brief setTestState
			 * @param state
			 */
			static void setTestState (bool state) noexcept;

			/**
			 * @brief isTestEnabled
			 * @return bool
			 */
			static bool isTestEnabled () noexcept;

			/**
			 * @brief toggleTestState
			 * @return bool
			 */
			static bool toggleTestState () noexcept;

		private:

			static bool s_enableFrustumTest;

			std::array< Libraries::Math::Plane< float >, 6 > m_planes{};
	};
}
