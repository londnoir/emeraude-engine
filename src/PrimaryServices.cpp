/*
 * src/PrimaryServices.cpp
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

#include "PrimaryServices.hpp"

/* STL inclusions. */
#include <iostream>
#include <sstream>
#include <ranges>

/* Local inclusions. */
#include "Libs/IO/IO.hpp"

namespace EmEn
{
	using namespace EmEn::Libs;

	PrimaryServices::PrimaryServices (int argc, char * * argv, const Identification & identification, bool childProcess) noexcept
		: m_arguments(argc, argv, childProcess),
		m_tracer(m_arguments, m_settings, childProcess),
		m_fileSystem(m_arguments, m_userInfo, identification, childProcess),
		m_settings(m_arguments, m_fileSystem, childProcess)
	{
		m_flags[ChildProcess] = childProcess;

		/* NOTE: This must be done immediately ! */
		if ( !m_arguments.initialize(m_primaryServicesEnabled) )
		{
			std::cerr << ClassId << ", " << m_arguments.name() << " service failed to execute !";
		}

		if ( !childProcess && m_arguments.get("--verbose").isPresent() )
		{
			m_flags[ShowInformation] = true;
		}
	}

#if IS_WINDOWS
	PrimaryServices::PrimaryServices (int argc, wchar_t * * wargv, const Identification & identification, bool childProcess) noexcept
		: m_arguments(argc, wargv, childProcess),
		m_tracer(m_arguments, m_settings, childProcess),
		m_fileSystem(m_arguments, m_userInfo, identification, childProcess),
		m_settings(m_arguments, m_fileSystem, childProcess)
	{
		m_flags[ChildProcess] = childProcess;

		/* NOTE: This must be done immediately ! */
		if ( !m_arguments.initialize(m_primaryServicesEnabled) )
		{
			std::cerr << ClassId << ", " << m_arguments.name() << " service failed to execute !";
		}

		if ( !childProcess && m_arguments.get("--verbose").isPresent() )
		{
			m_flags[ShowInformation] = true;
		}
	}
#endif

	bool
	PrimaryServices::initialize () noexcept
	{
		/* Initialize tracer. */
		if ( !m_tracer.initialize(m_primaryServicesEnabled) )
		{
			std::cerr << ClassId << ", " << m_tracer.name() << " service failed to execute !";

			return false;
		}

		/* Initialize the file system to reach every useful directories. */
		if ( m_fileSystem.initialize(m_primaryServicesEnabled) )
		{
			TraceSuccess{ClassId} << m_fileSystem.name() << " service up !";

			/* Creating some basic paths. */
			const auto directory = m_fileSystem.userDataDirectory("captures");

			if ( !IO::directoryExists(directory) )
			{
				if ( IO::createDirectory(directory) )
				{
					TraceSuccess{ClassId} << "Captures directory " << directory << " created.";
				}
				else
				{
					TraceWarning{ClassId} << "Unable to create captures directory " << directory << " !";
				}
			}
		}
		else
		{
			TraceFatal{ClassId} << m_fileSystem.name() << " service failed to execute !";

			return false;
		}

		/* Initialize core settings.
		 * NOTE : Settings class manages to write default file. */
		if ( m_settings.initialize(m_primaryServicesEnabled) )
		{
			TraceSuccess{ClassId} << m_settings.name() << " service up !";

			/* NOTE: Now the core settings is initialized, we can update the tracer service configuration. */
			m_tracer.readSettings();
		}
		else
		{
			TraceError{ClassId} <<
				m_fileSystem.name() << " service failed to execute !" "\n"
				"There is a problem to read or write the core settings file." "\n"
				"The engine will use the default configuration.";
		}

		return true;
	}

	void
	PrimaryServices::terminate () noexcept
	{
		/* Terminate primary services. */
		for ( auto * service : std::ranges::reverse_view(m_primaryServicesEnabled) )
		{
			if ( service->terminate() )
			{
				TraceSuccess{ClassId} << service->name() << " primary service terminated gracefully !";
			}
			else
			{
				TraceError{ClassId} << service->name() << " primary service failed to terminate properly !";
			}
		}
	}

	std::string
	PrimaryServices::information () const noexcept
	{
		std::stringstream output;

		output << "\n"
			" ================== GENERAL INFORMATION ==================" "\n"
			<< m_systemInfo << "\n"
			<< m_userInfo << "\n"
			<< m_arguments << "\n"
			<< m_fileSystem << "\n"
			<< m_settings << "\n"
			" ================ GENERAL INFORMATION EOF ================" "\n\n";

		return output.str();
	}
}
