/*
 * Libraries/KVParser/Variable.hpp
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
#include <string>

namespace Libraries::KVParser
{
	class Variable final
	{
		friend class Section;

		public:

			Variable () noexcept = default;

			explicit Variable (std::string value) noexcept;

			explicit Variable (bool value) noexcept;

			explicit Variable (int value) noexcept;

			explicit Variable (float value) noexcept;

			explicit Variable (double value) noexcept;

			[[nodiscard]]
			bool isUndefined () const noexcept;

			[[nodiscard]]
			bool asBoolean () const noexcept;

			[[nodiscard]]
			int asInteger () const noexcept;

			[[nodiscard]]
			float asFloat () const noexcept;

			[[nodiscard]]
			double asDouble () const noexcept;

			[[nodiscard]]
			const std::string & asString () const noexcept;

		private:

			std::string m_value{};
			bool m_undefined = true;
	};
}
