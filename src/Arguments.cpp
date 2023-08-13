/*
 * Emeraude/Arguments.cpp
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

#include "Arguments.hpp"

/* C/C++ standard libraries. */
#include <iostream>
#include <cstring>
#include <sstream>

/* Local inclusions */
#include "String.hpp"
#include "Tracer.hpp"

namespace Emeraude
{
	using namespace Libraries;

	const size_t Arguments::ClassUID{Observable::getClassUID()};
	Arguments * Arguments::s_instance{nullptr}; // NOLINT NOTE: Singleton behavior

	Arguments::Arguments (int argc, const char * argv[]) noexcept
		: ServiceInterface(ClassId), m_argc(argc), m_argv(argv)
	{
		if ( s_instance != nullptr )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", constructor called twice !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

			std::terminate();
		}

		s_instance = this;

		if ( argc > 0 && m_argv != nullptr )
		{
			m_argvCopy = new char * [static_cast< size_t >(argc)];

			for ( auto i = 0; i < argc; i++ )
			{
				const auto length = std::strlen(argv[i]) + 1;

				m_argvCopy[i] = new char[length];

				//strcpy(m_argvCopy[i], argv[i]); // Standard C way, but unsecure.
				//strlcpy(m_argvCopy[i], argv[i], length); // Secure way, but not standard
				strncpy(m_argvCopy[i], argv[i], length);
			}
		}
	}

	Arguments::~Arguments ()
	{
		if ( m_argvCopy != nullptr )
		{
			for ( auto i = 0; i < m_argc; i++ )
			{
				delete[] m_argvCopy[i];

				m_argvCopy[i] = nullptr;
			}

			delete[] m_argvCopy;

			m_argvCopy = nullptr;
		}

		s_instance = nullptr;
	}

	Arguments *
	Arguments::instance () noexcept
	{
		return s_instance;
	}

	bool
	Arguments::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	Arguments::usable () const noexcept
	{
		return m_argc > 0;
	}

	int
	Arguments::getArgc () const noexcept
	{
		return m_argc;
	}

	const char * *
	Arguments::getArgv () const noexcept
	{
		return m_argv;
	}

	char * *
	Arguments::getArgvCopy () const noexcept
	{
		return m_argvCopy;
	}

	Argument
	Arguments::get (const std::string & name) const noexcept
	{
		const auto argIt = m_arguments.find(name);

		if ( argIt != m_arguments.cend() )
		{
			return argIt->second;
		}

		return {};
	}

	Argument
	Arguments::get (const std::string & name, const std::string & alternateName) const noexcept
	{
		auto argIt = m_arguments.find(name);

		if ( argIt != m_arguments.cend() )
		{
			return argIt->second;
		}

		argIt = m_arguments.find(alternateName);

		if ( argIt != m_arguments.cend() )
		{
			return argIt->second;
		}

		return {};
	}

	Argument
	Arguments::get (const std::vector< std::string > & namesList) const noexcept
	{
		for ( const auto & name : namesList )
		{
			const auto argIt = m_arguments.find(name);

			if ( argIt != m_arguments.cend() )
			{
				return argIt->second;
			}
		}

		return {};
	}

	const std::string &
	Arguments::getBinaryPath () const noexcept
	{
		return m_binaryPath;
	}

	bool
	Arguments::onInitialize () noexcept
	{
		m_binaryPath = m_argv[0];

		/* NOTE : We execute at 1 because we don't
		 * care about the binary name. */
		for ( auto arg = 1; arg < m_argc; arg++ )
		{
			const auto nextArg = arg + 1;

			std::string value{m_argv[arg]};

			if ( value[0] != '-' )
			{
				std::cerr << "Invalid argument : " << value << '\n';

				continue;
			}

			/* Checks the form --xxx=yyy */
			if ( value.find_first_of('=') != std::string::npos )
			{
				auto chunks = String::explode(value, '=', false);

				m_arguments.emplace(std::piecewise_construct, std::forward_as_tuple(chunks[0]), std::forward_as_tuple(chunks[1]));

				continue;
			}

			/* Checks the form --xxx yyy */
			if ( nextArg < m_argc && m_argv[nextArg][0] != '-' )
			{
				/* We assume the arg is the parameter value. */
				m_arguments.emplace(std::piecewise_construct, std::forward_as_tuple(value), std::forward_as_tuple(m_argv[nextArg]));

				arg++;

				continue;
			}

			/* NOTE: we put "1" to makes argument returning true
			 * when calling ArgumentValue::isPresent(). */
			m_arguments.emplace(std::piecewise_construct, std::forward_as_tuple(value), std::forward_as_tuple("1"));
		}

		return true;
	}

	bool
	Arguments::onTerminate () noexcept
	{
		m_arguments.clear();

		return true;
	}

	std::ostream &
	operator<< (std::ostream & out, const Arguments & obj)
	{
		if ( obj.m_arguments.empty() )
		{ return out << "Arguments : NONE" "\n"; }

		out << "Arguments :\n";

		for ( const auto & argument : obj.m_arguments )
		{
			out << argument.first << " = " << argument.second << '\n';
		}

		return out;
	}

	std::string
	to_string (const Arguments & obj) noexcept
	{
		return (std::stringstream{} << obj).str();
	}
}
