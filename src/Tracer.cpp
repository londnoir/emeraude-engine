/*
 * Emeraude/Tracer.cpp
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

#include "Tracer.hpp"

/* C/C++ standard libraries. */
#include <algorithm>
#include <cstring>
#include <iostream>

/* Local inclusions */
#include "Arguments.hpp"
#include "Settings.hpp"

namespace Emeraude
{
	using namespace Libraries;

	const size_t Tracer::ClassUID{Observable::getClassUID()};
	Tracer * Tracer::s_instance{nullptr}; // NOLINT NOTE: Singleton behavior
	std::thread::id Tracer::s_mainThreadId{};

	Tracer::Tracer (const Arguments & arguments, Settings & coreSettings) noexcept
		: ServiceInterface(ClassId), m_arguments(arguments), m_coreSettings(coreSettings)
	{
		if ( s_instance != nullptr )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", constructor called twice !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

			std::terminate();
		}

		s_instance = this;
	}

	Tracer::~Tracer ()
	{
		s_instance = nullptr;
	}

	Tracer *
	Tracer::instance () noexcept
	{
		return s_instance;
	}

	bool
	Tracer::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	Tracer::onInitialize () noexcept
	{
		auto argument = m_arguments.get("--filter-tags");

		if ( argument.isPresent() )
		{
			const auto terms = String::explode(argument.value(), ',', false);

			for ( const auto & term : terms )
			{
				this->addTagFilter(String::trim(term));
			}
		}

		argument = m_arguments.get("-q", "--disable-tracing");

		if ( argument.isPresent() )
		{
			std::cout << "Tracer disabled on startup !" "\n";

			m_flags[EnableTracing] = false;
		}

		argument = m_arguments.get("-l", "--enable-log");

		if ( argument.isPresent() )
		{
			m_logger = std::make_unique< TracerLogger >(argument.value());

			m_flags[EnableLogging] = true;

			m_loggerProcess = std::thread{&TracerLogger::task, m_logger.get()};
		}

		s_mainThreadId = std::this_thread::get_id();

		return true;
	}

	bool
	Tracer::onTerminate () noexcept
	{
		if ( m_logger != nullptr )
		{
			m_logger->stop();

			if ( m_loggerProcess.joinable() )
			{
				m_loggerProcess.join();
			}

			m_logger.reset();
		}

		return true;
	}

	bool
	Tracer::usable () const noexcept
	{
		return true;
	}

	void
	Tracer::addTagFilter (const std::string & filter) noexcept
	{
		m_filters.emplace_back(filter);
	}

	void
	Tracer::removeAllTagFilters () noexcept
	{
		m_filters.clear();
	}

	void
	Tracer::enablePrintOnlyErrors (bool state) noexcept
	{
		m_flags[PrintOnlyErrors] = state;
	}

	bool
	Tracer::printOnlyErrors () const noexcept
	{
		return m_flags[PrintOnlyErrors];
	}

	void
	Tracer::enableShowLocation (bool state) noexcept
	{
		m_flags[ShowLocation] = state;
	}

	bool
	Tracer::showLocation () const noexcept
	{
		return m_flags[ShowLocation];
	}

	void
	Tracer::enableShowThreadInfos (bool state) noexcept
	{
		m_flags[ShowThreadInfos] = state;
	}

	bool
	Tracer::showThreadInfos () const noexcept
	{
		return m_flags[ShowThreadInfos];
	}

	void
	Tracer::enableTracing (bool state) noexcept
	{
		m_flags[EnableTracing] = state;
	}

	bool
	Tracer::isTracingEnabled () const noexcept
	{
		return m_flags[EnableTracing];
	}

	bool
	Tracer::enableLogger (const std::string & filepath) noexcept
	{
		if ( m_logger != nullptr )
		{
			return true;
		}

		m_logger = std::make_unique< TracerLogger >(filepath);

		if ( !m_logger->usable() )
		{
			m_logger.reset();

			this->trace(Severity::Error, "Tracer", Blob() << "Unable to enable the logger with the file '" << filepath << "' !");

			return false;
		}

		m_loggerProcess = std::thread{&TracerLogger::task, m_logger.get()};

		m_flags[EnableLogging] = true;

		return true;
	}

	void
	Tracer::disableLogger () noexcept
	{
		/* FIXME: Detach ?! */
		if ( m_logger != nullptr )
		{
			m_logger->stop();

			if ( m_loggerProcess.joinable() )
			{
				m_loggerProcess.join();
			}

			m_logger.reset();
		}
	}

	void
	Tracer::enableLogging (bool state) noexcept
	{
		if ( m_logger == nullptr )
		{
			return;
		}

		m_flags[EnableLogging] = state;
	}

	bool
	Tracer::isLoggingEnabled () const noexcept
	{
		return m_flags[EnableLogging];
	}

	void
	Tracer::readCoreSettings () noexcept
	{
		this->enablePrintOnlyErrors(m_coreSettings.getAs< bool >(PrintOnlyErrorsKey, DefaultPrintOnlyErrors));
		this->enableShowLocation(m_coreSettings.getAs< bool >(ShowLocationKey, DefaultShowLocation));
		this->enableShowThreadInfos(m_coreSettings.getAs< bool >(ShowThreadInfosKey, DefaultShowThreadInfos));

		this->trace(Severity::Info, "Tracer", "Core settings available, Tracer configuration updated !");
	}

	void
	Tracer::trace (Severity severity, const char * tag, const std::string & message, const char * location) noexcept
	{
		if ( !this->isTracingEnabled() || !this->filterTag(tag) )
		{
			return;
		}

		std::stringstream trace{};

		trace << '[' << to_string(severity) << ']' << '[' << tag << ']';

		switch ( severity )
		{
			case Severity::Debug :
				trace << " \033[1;36m" << message << " \033[0m";
				break;

			case Severity::Info :
				trace << ' ' << message << ' ';
				break;

			case Severity::Success :
				trace << " \033[1;32m" << message << " \033[0m";
				break;

			case Severity::Warning :
				trace << " \033[1;35m" << message << " \033[0m";
				break;

			case Severity::Error :
			case Severity::Fatal :
				trace << " \033[1;31m" << message << " \033[0m";
				break;
		}

		if ( m_flags[ShowLocation] && location != nullptr )
		{
			trace << '\n' << '\t' << '[' << location << ']';
		}

		if ( m_flags[ShowThreadInfos] )
		{
			trace << "[Thread:" << std::this_thread::get_id() << ']';
		}

		switch ( severity )
		{
			case Severity::Debug :
			case Severity::Info :
			case Severity::Success :
				if ( !m_flags[PrintOnlyErrors] )
				{
					std::cout << trace.str() << '\n';
				}
				break;

			case Severity::Warning :
			case Severity::Error :
			case Severity::Fatal :
				std::cerr << trace.str() << '\n';
				break;
		}
	}

	void
	Tracer::trace (Severity severity, const char * tag, const std::string & message, const std_glue::source_location & location) noexcept
	{
		if ( !this->isTracingEnabled() || !this->filterTag(tag) )
		{
			return;
		}

		std::stringstream trace{};

		trace << '[' << to_string(severity) << ']' << '[' << tag << ']';

		switch ( severity )
		{
			case Severity::Debug :
				trace << " \033[1;36m" << message << " \033[0m";
				break;

			case Severity::Info :
				trace << ' ' << message << ' ';
				break;

			case Severity::Success :
				trace << " \033[1;32m" << message << " \033[0m";
				break;

			case Severity::Warning :
				trace << " \033[1;35m" << message << " \033[0m";
				break;

			case Severity::Error :
			case Severity::Fatal :
				trace << " \033[1;31m" << message << " \033[0m";
				break;
		}

		if ( m_flags[ShowLocation] )
		{
			trace << '\n' << '\t' << '[' << location.file_name() << ':' << location.line() << ':' << location.column() << " `" << location.function_name() << '`' << ']';
		}

		if ( m_flags[ShowThreadInfos] )
		{
			if ( std::this_thread::get_id() == s_mainThreadId )
			{
				trace << "[MainThread:" << std::this_thread::get_id() << ']';
			}
			else
			{
				trace << "[Thread:" << std::this_thread::get_id() << ']';
			}
		}

		switch ( severity )
		{
			case Severity::Debug :
			case Severity::Info :
			case Severity::Success :
				if ( !m_flags[PrintOnlyErrors] )
				{
					std::cout << trace.str() << '\n';
				}
				break;

			case Severity::Warning :
			case Severity::Error :
			case Severity::Fatal :
				std::cerr << trace.str() << '\n';
				break;
		}

		if ( m_logger != nullptr )
		{
			m_logger->push(severity, tag, message, location);
		}
	}

	void
	Tracer::traceGLFW (int error, const char * description) noexcept
	{
		s_instance->trace(Severity::Error, nullptr, (std::stringstream{} << description << " (errno:" << error << ')').str(), nullptr);
	}

	bool
	Tracer::filterTag (const char * tag) const noexcept
	{
		/* There is no tag filtering at all. */
		if ( m_filters.empty() )
		{
			return true;
		}

		/* Checks if a term match the filter. */
		return std::ranges::any_of(m_filters, [tag](const auto & filteredTag) {
			return std::strcmp(tag, filteredTag.c_str()) == 0;
		});
	}
}
