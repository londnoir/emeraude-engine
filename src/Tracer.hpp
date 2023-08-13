/*
 * Emeraude/Tracer.hpp
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
#include <array>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#if defined(__clang__) && __clang_major__ < 16
#include <experimental/source_location>

namespace std_glue = std::experimental;
#else
#include <source_location>

namespace std_glue = std;
#endif

/* Local inclusions for inheritances. */
#include "ServiceInterface.hpp"

/* Local inclusions for usages. */
#include "Blob.hpp"
#include "TracerLogger.hpp"
#include "Types.hpp"
#include "emeraude_config.hpp"

#define STRINGIFY_DETAIL(V) #V
#define STRINGIFY(V)  STRINGIFY_DETAIL(V)
#define LOCATION __FILE__ ":"  STRINGIFY(__LINE__)

namespace Emeraude
{
	class Arguments;
	class Settings;

	/**
	 * @brief The tracer service class.
	 * @extends Emeraude::ServiceInterface This is a service.
	 */
	class Tracer final : public ServiceInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"TracerService"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/* Settings keys */
			static constexpr auto PrintOnlyErrorsKey = "Tracer/PrintOnlyErrors";
			static constexpr auto DefaultPrintOnlyErrors = false;
			static constexpr auto ShowLocationKey = "Tracer/ShowLocation";
			static constexpr auto DefaultShowLocation = BOOLEAN_FOLLOWING_DEBUG;
			static constexpr auto ShowThreadInfosKey = "Tracer/ShowThreadInfos";
			static constexpr auto DefaultShowThreadInfos = BOOLEAN_FOLLOWING_DEBUG;

			/* ANSI Escape Codes */
			static constexpr auto CSI = "\033[";

			enum class ANSIColorCode: int
			{
				Black = 30,
				Red = 31,
				Green = 32,
				Yellow = 33,
				Blue = 34,
				Magenta = 35,
				Cyan = 36,
				White = 37,
				BrightBlack = 90,
				BrightRed = 91,
				BrightGreen = 92,
				BrightYellow = 93,
				BrightBlue = 94,
				BrightMagenta = 95,
				BrightCyan = 96,
				BrightWhite = 97
			};

			/**
			 * @brief Constructs the tracer.
			 * @param arguments A reference to Arguments.
			 * @param coreSettings A reference to core settings. Warning this can't be used at this time.
			 */
			Tracer (const Arguments & arguments, Settings & coreSettings) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Tracer (const Tracer & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Tracer (Tracer && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			Tracer & operator= (const Tracer & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			Tracer & operator= (Tracer && copy) noexcept = delete;

			/**
			 * @brief Destructs the tracer.
			 */
			~Tracer () override;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::ServiceInterface::usable() */
			[[nodiscard]]
			bool usable () const noexcept override;

			/**
			 * @brief Adds a term to only print out trace message containing it.
			 * @note This only affect the standard console output.
			 * @param filter The term to filter.
			 */
			void addTagFilter (const std::string & filter) noexcept;

			/** @brief Clears all filters. */
			void removeAllTagFilters () noexcept;

			/**
			 * @brief Enables only the errors to be print in the standard console. By default, this is option is disabled.
			 * @note This won't affect the log file.
			 * @param state The state.
			 */
			void enablePrintOnlyErrors (bool state) noexcept;

			/**
			 * @brief Returns whether only errors are print in the standard console.
			 * @return bool
			 */
			[[nodiscard]]
			bool printOnlyErrors () const noexcept;

			/**
			 * @brief Enables the location "[file:number]" section in the standard console. By default, this options is enabled.
			 * @note This won't affect the log file.
			 * @param state The state.
			 */
			void enableShowLocation (bool state) noexcept;

			/**
			 * @brief Returns it the location in the standard console is enabled.
			 * @return bool
			 */
			[[nodiscard]]
			bool showLocation () const noexcept;

			/**
			 * @brief Enables the thread information section in the standard console. By default, this options is enabled.
			 * @note This won't affect the log file.
			 * @param state The state.
			 */
			void enableShowThreadInfos (bool state) noexcept;

			/**
			 * @brief Returns whether the thread information in the standard console is enabled.
			 * @return bool
			 */
			[[nodiscard]]
			bool showThreadInfos () const noexcept;

			/**
			 * @brief Turns ON/OFF the tracer.
			 * @param state The state.
			 */
			void enableTracing (bool state) noexcept;

			/**
			 * @brief Returns whether the tracer is enabled.
			 * @return bool
			 */
			[[nodiscard]]
			bool isTracingEnabled () const noexcept;

			/**
			 * @brief Prepares the logger to write into a logfile.
			 * @param filepath A reference to a string for the filepath.
			 * @return bool
			 */
			bool enableLogger (const std::string & filepath) noexcept;

			/**
			 * @brief Removes the logger and closes the logfile.
			 */
			void disableLogger () noexcept;

			/**
			 * @brief Turns ON/OFF the tracer writing into the logfile.
			 * @param state The state.
			 */
			void enableLogging (bool state) noexcept;

			/**
			 * @brief Returns whether the tracer is writing into the logfile.
			 * @note Returns always false, if the logger is disabled.
			 * @return bool
			 */
			[[nodiscard]]
			bool isLoggingEnabled () const noexcept;

			/**
			 * @brief Reads the core settings.
			 * @warning This can't be done at startup because the Tracer service is the first to be setup.
			 */
			void readCoreSettings () noexcept;

			/**
			 * @brief Creates a log.
			 * @param severity The type of log.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a string for the log content.
			 * @param location A pointer to a C-string to describe the location. Use LOCATION for default behavior.
			 */
			void trace (Severity severity, const char * tag, const std::string & message, const char * location) noexcept;

			/**
			 * @brief Creates a log with the Blob class.
			 * @param severity The type of log.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a string for the log content.
			 * @param location A pointer to a C-string to describe the location. Use LOCATION for default behavior.
			 */
			inline
			void
			trace (Severity severity, const char * tag, const Libraries::Blob & message, const char * location) noexcept
			{
				this->trace(severity, tag, message.get(), location);
			}

			/**
			 * @brief Creates a log.
			 * @param severity The type of log.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a string for the log content.
			 * @param location A reference to a source_location. Default constructed in place.
			 */
			void trace (Severity severity, const char * tag, const std::string & message, const std_glue::source_location & location = std_glue::source_location::current()) noexcept;

			/**
			 * @brief Creates a log with the Blob class.
			 * @param severity The type of log.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a string for the log content.
			 * @param location A reference to a source_location. Default constructed in place.
			 */
			inline
			void
			trace (Severity severity, const char * tag, const Libraries::Blob & message, const std_glue::source_location & location = std_glue::source_location::current()) noexcept
			{
				this->trace(severity, tag, message.get(), location);
			}

			/**
			 * @brief Returns the instance of tracer.
			 * @return Tracer *
			 */
			[[nodiscard]]
			static
			Tracer * instance () noexcept;

			/**
			 * @brief Creates a quick log with Info as severity.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a string for the log content.
			 * @param location A reference to a source_location. Default constructed in place.
			 */
			static
			inline
			void
			info (const char * tag, const std::string & message, const std_glue::source_location & location = std_glue::source_location::current()) noexcept
			{
				s_instance->trace(Severity::Info, tag, message, location);
			}

			/**
			 * @brief Creates a quick log with Info as severity.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a blob for the log content.
			 * @param location A reference to a source_location. Default constructed in place.
			 */
			static
			inline
			void
			info (const char * tag, const Libraries::Blob & message, const std_glue::source_location & location = std_glue::source_location::current()) noexcept
			{
				s_instance->trace(Severity::Info, tag, message.get(), location);
			}

			/**
			 * @brief Creates a quick log with Success as severity.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a string for the log content.
			 * @param location A reference to a source_location. Default constructed in place.
			 */
			static
			inline
			void
			success (const char * tag, const std::string & message, const std_glue::source_location & location = std_glue::source_location::current()) noexcept
			{
				s_instance->trace(Severity::Success, tag, message, location);
			}

			/**
			 * @brief Creates a quick log with Success as severity.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a blob for the log content.
			 * @param location A reference to a source_location. Default constructed in place.
			 */
			static
			inline
			void
			success (const char * tag, const Libraries::Blob & message, const std_glue::source_location & location = std_glue::source_location::current()) noexcept
			{
				s_instance->trace(Severity::Success, tag, message.get(), location);
			}

			/**
			 * @brief Creates a quick log with Warning as severity.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a string for the log content.
			 * @param location A reference to a source_location. Default constructed in place.
			 */
			static
			inline
			void
			warning (const char * tag, const std::string & message, const std_glue::source_location & location = std_glue::source_location::current()) noexcept
			{
				s_instance->trace(Severity::Warning, tag, message, location);
			}

			/**
			 * @brief Creates a quick log with Warning as severity.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a blob for the log content.
			 * @param location A reference to a source_location. Default constructed in place.
			 */
			static
			inline
			void
			warning (const char * tag, const Libraries::Blob & message, const std_glue::source_location & location = std_glue::source_location::current()) noexcept
			{
				s_instance->trace(Severity::Warning, tag, message.get(), location);
			}

			/**
			 * @brief Creates a quick log with Error as severity.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a string for the log content.
			 * @param location A reference to a source_location. Default constructed in place.
			 */
			static
			inline
			void
			error (const char * tag, const std::string & message, const std_glue::source_location & location = std_glue::source_location::current()) noexcept
			{
				s_instance->trace(Severity::Error, tag, message, location);
			}

			/**
			 * @brief Creates a quick log with Error as severity.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a blob for the log content.
			 * @param location A reference to a source_location. Default constructed in place.
			 */
			static
			inline
			void
			error (const char * tag, const Libraries::Blob & message, const std_glue::source_location & location = std_glue::source_location::current()) noexcept
			{
				s_instance->trace(Severity::Error, tag, message.get(), location);
			}

			/**
			 * @brief Creates a quick log with Fatal as severity.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a string for the log content.
			 * @param location A reference to a source_location. Default constructed in place.
			 */
			static
			inline
			void
			fatal (const char * tag, const std::string & message, const std_glue::source_location & location = std_glue::source_location::current()) noexcept
			{
				s_instance->trace(Severity::Fatal, tag, message, location);
			}

			/**
			 * @brief Creates a quick log with Fatal as severity.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a blob for the log content.
			 * @param location A reference to a source_location. Default constructed in place.
			 */
			static
			inline
			void
			fatal (const char * tag, const Libraries::Blob & message, const std_glue::source_location & location = std_glue::source_location::current()) noexcept
			{
				s_instance->trace(Severity::Fatal, tag, message.get(), location);
			}

			/**
			 * @brief Creates a quick log with Debug as severity.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a string for the log content.
			 * @param location A reference to a source_location. Default constructed in place.
			 */
			static
			inline
			void
			debug (const char * tag, const std::string & message, const std_glue::source_location & location = std_glue::source_location::current()) noexcept
			{
				#ifdef DEBUG
				s_instance->trace(Severity::Debug, tag, message, location);
				#endif
			}

			/**
			 * @brief Creates a quick log with Debug as severity.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a blob for the log content.
			 * @param location A reference to a source_location. Default constructed in place.
			 */
			static
			inline
			void
			debug (const char * tag, const Libraries::Blob & message, const std_glue::source_location & location = std_glue::source_location::current()) noexcept
			{
				#ifdef DEBUG
				s_instance->trace(Severity::Debug, tag, message.get(), location);
				#endif
			}

			/**
			 * @brief Converts GLFW log facility to trace()
			 * @warning FIXME: This should now belong to Renderer or Window object.
			 * @param error The error number from GLFW library.
			 * @param description The message associated to the error code.
			 */
			static void traceGLFW (int error, const char * description) noexcept;

		private:

			/** @copydoc Emeraude::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc Emeraude::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

			/**
			 * @brief Filters the current tag. If the method return true, the message with the tag is allowed to be displayed.
			 * @param tag The tag to filter.
			 * @return bool
			 */
			bool filterTag (const char * tag) const noexcept;

			/* Flag names. */
			static constexpr auto PrintOnlyErrors = 0UL;
			static constexpr auto ShowLocation = 1UL;
			static constexpr auto ShowThreadInfos = 2UL;
			static constexpr auto EnableTracing = 3UL;
			static constexpr auto EnableLogging = 4UL;

			static Tracer * s_instance; // NOLINT NOTE: Singleton behavior
			static std::thread::id s_mainThreadId;

			// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members) NOTE: Services inter-connexions.
			const Arguments & m_arguments;
			Settings & m_coreSettings;
			// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members) NOTE: Services inter-connexions.
			std::vector< std::string > m_filters;
			std::unique_ptr< TracerLogger > m_logger;
			std::thread m_loggerProcess;
			std::array< bool, 8 > m_flags{ // NOLINT(*-magic-numbers)
				DefaultPrintOnlyErrors/*PrintOnlyErrors*/,
				DefaultShowLocation/*ShowLocation*/,
				DefaultShowThreadInfos/*ShowThreadInfos*/,
				true/*EnableTracing*/,
				false/*EnableLogging*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};

	/**
	 * @brief The TraceDebug class.
	 * @extends Libraries::Blob
	 */
	class TraceDebug final : public Libraries::Blob
	{
		public:

			/**
			 * @brief Constructs a trace.
			 * @param tag A pointer to a C-string for the tag.
			 * @param location A reference to a source location structure.
			 */
			explicit
			TraceDebug (const char * tag, const std_glue::source_location & location = std_glue::source_location::current()) noexcept
				: m_tag(tag), m_location(location)
			{

			}

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			TraceDebug (const TraceDebug & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			TraceDebug (TraceDebug && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			TraceDebug & operator= (const TraceDebug & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			TraceDebug & operator= (TraceDebug && copy) noexcept = delete;

			/**
			 * @brief Destructs the trace and calls the real tracer service.
			 */
			~TraceDebug ()
			{
				Tracer::instance()->trace(Severity::Debug, m_tag, this->get(), m_location);
			}

		private:

			const char * m_tag;
			std_glue::source_location m_location;
	};

	/**
	 * @brief The TraceSuccess class.
	 * @extends Libraries::Blob
	 */
	class TraceSuccess final : public Libraries::Blob
	{
		public:

			/**
			 * @brief Constructs a trace.
			 * @param tag A pointer to a C-string for the tag.
			 * @param location A reference to a source location structure.
			 */
			explicit
			TraceSuccess (const char * tag, const std_glue::source_location & location = std_glue::source_location::current()) noexcept
				: m_tag(tag), m_location(location)
			{

			}

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			TraceSuccess (const TraceSuccess & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			TraceSuccess (TraceSuccess && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			TraceSuccess & operator= (const TraceSuccess & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			TraceSuccess & operator= (TraceSuccess && copy) noexcept = delete;

			/**
			 * @brief Destructs the trace and calls the real tracer service.
			 */
			~TraceSuccess ()
			{
				Tracer::instance()->trace(Severity::Success, m_tag, this->get(), m_location);
			}

		private:

			const char * m_tag;
			std_glue::source_location m_location;
	};

	/**
	 * @brief The TraceInfo class.
	 * @extends Libraries::Blob
	 */
	class TraceInfo final : public Libraries::Blob
	{
		public:

			/**
			 * @brief Constructs a trace.
			 * @param tag A pointer to a C-string for the tag.
			 * @param location A reference to a source location structure.
			 */
			explicit
			TraceInfo (const char * tag, const std_glue::source_location & location = std_glue::source_location::current()) noexcept
				: m_tag(tag), m_location(location)
			{

			}

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			TraceInfo (const TraceInfo & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			TraceInfo (TraceInfo && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			TraceInfo & operator= (const TraceInfo & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			TraceInfo & operator= (TraceInfo && copy) noexcept = delete;

			/**
			 * @brief Destructs the trace and calls the real tracer service.
			 */
			~TraceInfo ()
			{
				Tracer::instance()->trace(Severity::Info, m_tag, this->get(), m_location);
			}

		private:

			const char * m_tag;
			std_glue::source_location m_location;
	};

	/**
	 * @brief The TraceWarning class.
	 * @extends Libraries::Blob
	 */
	class TraceWarning final : public Libraries::Blob
	{
		public:

			/**
			 * @brief Constructs a trace.
			 * @param tag A pointer to a C-string for the tag.
			 * @param location A reference to a source location structure.
			 */
			explicit
			TraceWarning (const char * tag, const std_glue::source_location & location = std_glue::source_location::current()) noexcept
				: m_tag(tag), m_location(location)
			{

			}

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			TraceWarning (const TraceWarning & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			TraceWarning (TraceWarning && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			TraceWarning & operator= (const TraceWarning & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			TraceWarning & operator= (TraceWarning && copy) noexcept = delete;

			/**
			 * @brief Destructs the trace and calls the real tracer service.
			 */
			~TraceWarning ()
			{
				Tracer::instance()->trace(Severity::Warning, m_tag, this->get(), m_location);
			}

		private:

			const char * m_tag;
			std_glue::source_location m_location;
	};

	/**
	 * @brief The TraceError class.
	 * @extends Libraries::Blob
	 */
	class TraceError final : public Libraries::Blob
	{
		public:

			/**
			 * @brief Constructs a trace.
			 * @param tag A pointer to a C-string for the tag.
			 * @param location A reference to a source location structure.
			 */
			explicit
			TraceError (const char * tag, const std_glue::source_location & location = std_glue::source_location::current()) noexcept
				: m_tag(tag), m_location(location)
			{

			}

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			TraceError (const TraceError & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			TraceError (TraceError && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			TraceError & operator= (const TraceError & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			TraceError & operator= (TraceError && copy) noexcept = delete;

			/**
			 * @brief Destructs the trace and calls the real tracer service.
			 */
			~TraceError ()
			{
				Tracer::instance()->trace(Severity::Error, m_tag, this->get(), m_location);
			}

		private:

			const char * m_tag;
			std_glue::source_location m_location;
	};

	/**
	 * @brief The TraceFatal class.
	 * @extends Libraries::Blob
	 */
	class TraceFatal final : public Libraries::Blob
	{
		public:

			/**
			 * @brief Constructs a trace.
			 * @param tag A pointer to a C-string for the tag.
			 * @param location A reference to a source location structure.
			 */
			explicit
			TraceFatal (const char * tag, const std_glue::source_location & location = std_glue::source_location::current()) noexcept
				: m_tag(tag), m_location(location)
			{

			}

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			TraceFatal (const TraceFatal & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			TraceFatal (TraceFatal && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return TraceFatal &
			 */
			TraceFatal & operator= (const TraceFatal & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return TraceFatal &
			 */
			TraceFatal & operator= (TraceFatal && copy) noexcept = delete;

			/**
			 * @brief Destructs the trace and calls the real tracer service.
			 */
			~TraceFatal ()
			{
				Tracer::instance()->trace(Severity::Fatal, m_tag, this->get(), m_location);
			}

		private:

			const char * m_tag;
			std_glue::source_location m_location;
	};
}
