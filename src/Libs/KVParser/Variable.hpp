/*
 * src/Libs/KVParser/Variable.hpp
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
#include <string>

namespace EmEn::Libs::KVParser
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
