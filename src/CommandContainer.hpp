/*
 * src/CommandContainer.hpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2024 - "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emeraude-Engine; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Complete project and additional information can be found at :
 * https://bitbucket.org/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#pragma once

/* STL inclusions. */
#include <functional>
#include <string>

namespace Emeraude
{
	/** @brief Typedef of a function used by the console. */
	using ConsoleCommand = std::function< int (const std::vector< std::string > &) >;

	/**
	 * @brief Container for a specific command.
	 */
	class CommandContainer final
	{
		public:

			/**
			 * @brief Constructs a command container.
			 * @param command The command to execute in the container [std::move].
			 * @param help A way to explain that command [std::move].
			 */
			CommandContainer (ConsoleCommand command, std::string help) noexcept;

			/**
			 * @brief Returns the command to type.
			 * @return const ConsoleCommand &
			 */
			[[nodiscard]]
			const ConsoleCommand &
			command () const noexcept
			{
				return m_command;
			}

			/**
			 * @brief Returns the command usage instructions.
			 * @return const std::string &
			 */
			[[nodiscard]]
			const std::string &
			help () const noexcept
			{
				return m_help;
			}

		private:

			ConsoleCommand m_command;
			std::string m_help;
	};
}
