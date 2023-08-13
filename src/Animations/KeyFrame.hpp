/*
 * Emeraude/Animations/KeyFrame.hpp
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

/* Local inclusions for usages. */
#include "Variant.hpp"
#include "Math/Base.hpp"

namespace Emeraude::Animations
{
	/**
	 * @brief The Keyframe definition.
	 */
	class KeyFrame final
	{
		public:

			/**
			 * @brief Construct a new key with a valued type.
			 * @param value The value at this keyframe [std::move].
			 * @param interpolation The type of interpolation.
			 */
			KeyFrame (Libraries::Variant value, Libraries::Math::InterpolationType interpolation) noexcept;

			/**
			 * @brief Returns the value.
			 * @return const Libraries::Variant &
			 */
			[[nodiscard]]
			const Libraries::Variant & value () const noexcept;

			/**
			 * @brief Returns the interpolation type.
			 * @return const Libraries::Math::InterpolationType &
			 */
			[[nodiscard]]
			const Libraries::Math::InterpolationType & interpolation () const noexcept;

		private:

			Libraries::Variant m_value;
			Libraries::Math::InterpolationType m_interpolation;
	};

	/**
	 * @brief KeyFrame list using a std::map.
	 */
	using KeyFrames = std::map< float, KeyFrame >;
}
