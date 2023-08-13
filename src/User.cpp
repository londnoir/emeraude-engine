/*
 * Emeraude/User.cpp
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

#include "User.hpp"

/* Local inclusions. */
#include "Settings.hpp"
#include "Tracer.hpp"

namespace Emeraude
{
	const size_t User::ClassUID{Observable::getClassUID()};

	User::User (Settings & applicationSettings) noexcept
		: ServiceInterface(ClassId), m_applicationSettings(applicationSettings)
	{

	}

	bool
	User::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	User::usable () const noexcept
	{
		return true;
	}

	void
	User::setUserID (uint64_t identifier) noexcept
	{
		m_userID = identifier;
	}

	void
	User::setUsername (const std::string & username) noexcept
	{
		m_username = username;
	}

	uint64_t
	User::userID () const noexcept
	{
		return m_userID;
	}

	const std::string &
	User::username () const noexcept
	{
		return m_username;
	}

	bool
	User::onInitialize () noexcept
	{
		return true;
	}

	bool
	User::onTerminate () noexcept
	{
		return true;
	}
}
