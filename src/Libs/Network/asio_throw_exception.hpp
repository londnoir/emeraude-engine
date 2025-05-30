/*
 * src/Libs/Network/asio_throw_exception.hpp
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

/* Application configuration */
#include "platform.hpp"

/* STL inclusions. */
#include <iostream>

namespace asio::detail
{
	/**
	 * @brief Overrides the asio::detail::throw_exception() method to use the library without C++ exception mechanism.
	 * @param exception A reference to the ASIO exception template.
	 * @return void
	 */
	template < typename exception_t >
	void
	throw_exception (const exception_t & exception)
	{
		std::cerr << __PRETTY_FUNCTION__ << '\n' << "ASIO stack message : " << exception.what() << '\n';

		//std::terminate();
	}
};
