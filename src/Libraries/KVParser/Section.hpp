/*
 * src/Libraries/KVParser/Section.hpp
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
#include <map>
#include <string>

/* Local inclusions. */
#include "Variable.hpp"

namespace Libraries::KVParser
{
	class Section final
	{
		friend class Parser;

		public:

			using Variables = std::map< std::string, Variable >;

			Section () noexcept = default;

			void addVariable (const std::string & key, const Variable & variable) noexcept;

			[[nodiscard]]
			size_t getVariableCount () const noexcept;

			[[nodiscard]]
			Variable variable (const std::string & key) const noexcept;

		private:

			void write (std::ofstream & file) const noexcept;

			Variables m_variables{};
	};
}
