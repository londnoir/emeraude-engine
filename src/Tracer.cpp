/*
 * src/Tracer.cpp
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

#include "Tracer.hpp"

/* STL inclusions. */
#include <algorithm>
#include <cstring>
#include <exception>
#include <iostream>
#include <memory>
#include <sstream>
#include <thread>

/* Local inclusions. */
#include "Libraries/BlobTrait.hpp"
#include "Libraries/String.hpp"
#include "Arguments.hpp"
#include "ServiceInterface.hpp"
#include "Settings.hpp"
#include "SettingKeys.hpp"
#include "TracerLogger.hpp"
#include "Types.hpp"
#if IS_WINDOWS
#include "PlatformSpecific/Helpers.hpp"
#endif

/* System inclusions. */
#if IS_LINUX || IS_MACOS
#include <unistd.h>
#endif

namespace Emeraude
{
	using namespace Libraries;

	const size_t Tracer::ClassUID{getClassUID(ClassId)};

	Tracer * Tracer::s_instance{nullptr};

	Tracer::Tracer (const Arguments & arguments, Settings & settings) noexcept
		: ServiceInterface(ClassId), m_arguments(arguments), m_settings(settings)
	{
		if ( s_instance != nullptr )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", constructor called twice !" "\n";

			std::terminate();
		}

		s_instance = this;
	}

	Tracer::~Tracer ()
	{
		s_instance = nullptr;
	}

	size_t
	Tracer::classUID () const noexcept
	{
		return ClassUID;
	}

	bool
	Tracer::is (size_t classUID) const noexcept
	{
		return classUID == ClassUID;
	}

	bool
	Tracer::onInitialize () noexcept
	{
		/* NOTE: Register once PPID and PID for this tracer. */
#if IS_LINUX || IS_MACOS
		m_parentProcessID = getppid();
		m_processID = getpid();
#elif IS_WINDOWS
		const auto PID = GetCurrentProcessId();

		m_parentProcessID = PlatformSpecific::getParentProcessId(PID);
		m_processID = static_cast< int >(PID);
#endif

		auto argument = m_arguments.get("--filter-tags");

		if ( argument.isPresent() )
		{
			for ( const auto & term : String::explode(argument.value(), ',', false) )
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

		m_flags[ServiceInitialized] = true;

		return true;
	}

	bool
	Tracer::onTerminate () noexcept
	{
		m_flags[ServiceInitialized] = false;

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
		return m_flags[ServiceInitialized];
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

			this->trace(Severity::Error, "Tracer", BlobTrait() << "Unable to enable the logger with the file '" << filepath << "' !");

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
	Tracer::readSettings () noexcept
	{
		this->enablePrintOnlyErrors(m_settings.get< bool >(TracerPrintOnlyErrorsKey, DefaultPrintOnlyErrors));
		this->enableShowLocation(m_settings.get< bool >(TracerShowLocationKey, DefaultShowLocation));
		this->enableShowThreadInfos(m_settings.get< bool >(TracerShowThreadInfosKey, DefaultShowThreadInfos));
	}

	void
	Tracer::trace (Severity severity, const char * tag, const std::string & message, const char * location) const noexcept
	{
		if ( !this->isTracingEnabled() || !this->filterTag(tag) )
		{
			return;
		}

		std::stringstream trace{};

		trace << '[' << to_string(severity) << "][" << tag << ']';

		Tracer::colorizeMessage(trace, severity, message);

		if ( m_flags[ShowLocation] && location != nullptr )
		{
			trace << "\n\t" "[" << location << ']';
		}

		if ( m_flags[ShowThreadInfos] )
		{
			this->injectProcessInfo(trace);
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
	Tracer::trace (Severity severity, const char * tag, const std::string & message, const std::source_location & location) const noexcept
	{
		if ( !this->isTracingEnabled() || !this->filterTag(tag) )
		{
			return;
		}

		std::stringstream trace{};

		trace << '[' << to_string(severity) << "][" << tag << ']';

		Tracer::colorizeMessage(trace, severity, message);

		if ( m_flags[ShowLocation] )
		{
			trace << "\n\t" "[" << location.file_name() << ':' << location.line() << ':' << location.column() << " `" << location.function_name() << "`]";
		}

		if ( m_flags[ShowThreadInfos] )
		{
			this->injectProcessInfo(trace);
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
	Tracer::traceAPI (const char * tag, const char * functionName, const std::string & message, const std::source_location & location) const noexcept
	{
		std::stringstream trace{};

		trace << "[" << tag << "] ";

		if ( message.empty() )
		{
			trace << "\033[1;93m" << functionName << "() called !" << "\033[0m ";
		}
		else
		{
			trace << "\033[1;93m" << functionName << "(), " << message << "\033[0m ";
		}

		if ( m_flags[ShowLocation] )
		{
			trace << "\n\t" "[" << location.file_name() << ':' << location.line() << ':' << location.column() << " `" << location.function_name() << "`]";
		}

		if ( m_flags[ShowThreadInfos] )
		{
			this->injectProcessInfo(trace);
		}

		std::cout << trace.str() << "\n";

		if ( m_logger != nullptr )
		{
			std::stringstream logMessage{};
			logMessage << functionName << "() : " << message;

			m_logger->push(Severity::Info, tag, logMessage.str(), location);
		}
	}

	void
	Tracer::injectProcessInfo (std::stringstream & stream) const noexcept
	{
#if IS_LINUX
		const auto tid = gettid();
#elif IS_MACOS
		const auto tid = -1;
#elif IS_WINDOWS
		const auto tid = GetCurrentThreadId();
#else
		const auto tid = -1;
#endif

		stream << "[PPID:" << m_parentProcessID << "][PID:" << m_processID << "][TID:" << tid << ']';
	}

	void
	Tracer::traceGLFW (int error, const char * description) noexcept
	{
		s_instance->trace(Severity::Error, "GLFW", (std::stringstream{} << description << " (errno:" << error << ')').str(), nullptr);
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

	TraceDebug::TraceDebug (const char * tag, const std::source_location & location) noexcept
		: m_tag(tag), m_location(location)
	{

	}

	TraceDebug::TraceDebug (const char * tag, const char * initialMessage, const std::source_location & location) noexcept
		: BlobTrait(initialMessage), m_tag(tag), m_location(location)
	{

	}

	TraceDebug::TraceDebug (const char * tag, const std::string & initialMessage, const std::source_location & location) noexcept
		: BlobTrait(initialMessage), m_tag(tag), m_location(location)
	{

	}

	TraceDebug::~TraceDebug ()
	{
		Tracer::instance()->trace(Severity::Debug, m_tag, this->get(), m_location);
	}

	TraceSuccess::TraceSuccess (const char * tag, const std::source_location & location) noexcept
		: m_tag(tag), m_location(location)
	{

	}

	TraceSuccess::TraceSuccess (const char * tag, const char * initialMessage, const std::source_location & location) noexcept
		: BlobTrait(initialMessage), m_tag(tag), m_location(location)
	{

	}

	TraceSuccess::TraceSuccess (const char * tag, const std::string & initialMessage, const std::source_location & location) noexcept
		: BlobTrait(initialMessage), m_tag(tag), m_location(location)
	{

	}

	TraceSuccess::~TraceSuccess ()
	{
		Tracer::instance()->trace(Severity::Success, m_tag, this->get(), m_location);
	}

	TraceInfo::TraceInfo (const char * tag, const std::source_location & location) noexcept
		: m_tag(tag), m_location(location)
	{

	}

	TraceInfo::TraceInfo (const char * tag, const char * initialMessage, const std::source_location & location) noexcept
		: BlobTrait(initialMessage), m_tag(tag), m_location(location)
	{

	}

	TraceInfo::TraceInfo (const char * tag, const std::string & initialMessage, const std::source_location & location) noexcept
		: BlobTrait(initialMessage), m_tag(tag), m_location(location)
	{

	}

	TraceInfo::~TraceInfo ()
	{
		Tracer::instance()->trace(Severity::Info, m_tag, this->get(), m_location);
	}

	TraceWarning::TraceWarning (const char * tag, const std::source_location & location) noexcept
		: m_tag(tag), m_location(location)
	{

	}

	TraceWarning::TraceWarning (const char * tag, const char * initialMessage, const std::source_location & location) noexcept
		: BlobTrait(initialMessage), m_tag(tag), m_location(location)
	{

	}

	TraceWarning::TraceWarning (const char * tag, const std::string & initialMessage, const std::source_location & location) noexcept
		: BlobTrait(initialMessage), m_tag(tag), m_location(location)
	{

	}

	TraceWarning::~TraceWarning ()
	{
		Tracer::instance()->trace(Severity::Warning, m_tag, this->get(), m_location);
	}

	TraceError::TraceError (const char * tag, const std::source_location & location) noexcept
		: m_tag(tag), m_location(location)
	{

	}

	TraceError::TraceError (const char * tag, const char * initialMessage, const std::source_location & location) noexcept
		: BlobTrait(initialMessage), m_tag(tag), m_location(location)
	{

	}

	TraceError::TraceError (const char * tag, const std::string & initialMessage, const std::source_location & location) noexcept
		: BlobTrait(initialMessage), m_tag(tag), m_location(location)
	{

	}

	TraceError::~TraceError ()
	{
		Tracer::instance()->trace(Severity::Error, m_tag, this->get(), m_location);
	}

	TraceFatal::TraceFatal (const char * tag, bool terminate, const std::source_location & location) noexcept
		: m_tag(tag), m_location(location), m_terminate(terminate)
	{

	}

	TraceFatal::TraceFatal (const char * tag, const char * initialMessage, bool terminate, const std::source_location & location) noexcept
		: BlobTrait(initialMessage), m_tag(tag), m_location(location), m_terminate(terminate)
	{

	}

	TraceFatal::TraceFatal (const char * tag, const std::string & initialMessage, bool terminate, const std::source_location & location) noexcept
		: BlobTrait(initialMessage), m_tag(tag), m_location(location), m_terminate(terminate)
	{

	}

	TraceFatal::~TraceFatal ()
	{
		Tracer::instance()->trace(Severity::Fatal, m_tag, this->get(), m_location);

		if ( m_terminate )
		{
			std::terminate();
		}
	}

	TraceAPI::TraceAPI (const char * tag, const char * functionName, bool terminate, const std::source_location & location) noexcept
		: m_tag(tag), m_functionName(functionName), m_location(location), m_terminate(terminate)
	{

	}

	TraceAPI::TraceAPI (const char * tag, const char * functionName, const char * initialMessage, bool terminate, const std::source_location & location) noexcept
		: BlobTrait(initialMessage), m_tag(tag), m_functionName(functionName), m_location(location), m_terminate(terminate)
	{

	}

	TraceAPI::TraceAPI (const char * tag, const char * functionName, const std::string & initialMessage, bool terminate, const std::source_location & location) noexcept
		: BlobTrait(initialMessage), m_tag(tag), m_functionName(functionName), m_location(location), m_terminate(terminate)
	{

	}

	TraceAPI::~TraceAPI ()
	{
		Tracer::instance()->traceAPI(m_tag, m_functionName, this->get(), m_location);

		if ( m_terminate )
		{
			std::terminate();
		}
	}
}
