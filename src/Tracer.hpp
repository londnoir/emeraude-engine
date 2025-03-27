/*
 * src/Tracer.hpp
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

/* Project configuration. */
#include "emeraude_config.hpp"

/* STL inclusions. */
#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include "Libs/std_source_location.hpp"

/* Local inclusions for inheritances. */
#include "ServiceInterface.hpp"

/* Local inclusions for usages. */
#include "Libs/BlobTrait.hpp"
#include "TracerLogger.hpp"
#include "Types.hpp"

/* Forward declarations. */
namespace EmEn
{
	class Arguments;
	class Settings;
}

namespace EmEn
{
	/**
	 * @brief The tracer service class.
	 * @extends EmEn::ServiceInterface This is a service.
	 */
	class Tracer final : public ServiceInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"TracerService"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/* ANSI Escape Codes */
			static constexpr auto CSI{"\033["};

			enum class ANSIColorCode: uint8_t
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
			 * @param settings A reference to core settings. Warning this can't be used at this time.
			 * @param childProcess Declares a child process.
			 */
			Tracer (const Arguments & arguments, Settings & settings, bool childProcess) noexcept;

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

			/** @copydoc EmEn::Libs::ObservableTrait::classUID() const */
			[[nodiscard]]
			size_t classUID () const noexcept override;

			/** @copydoc EmEn::Libs::ObservableTrait::is() const */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc EmEn::ServiceInterface::usable() */
			[[nodiscard]]
			bool usable () const noexcept override;

			/**
			 * @brief Adds a term to only print out trace message containing it.
			 * @note This only affect the standard console output.
			 * @param filter The term to filter.
			 * @return void
			 */
			void
			addTagFilter (const std::string & filter) noexcept
			{
				m_filters.emplace_back(filter);
			}

			/**
			 * @brief Clears all filters.
			 * @return void
			 */
			void
			removeAllTagFilters () noexcept
			{
				m_filters.clear();
			}

			/**
			 * @brief Enables only the errors to be print in the standard console. By default, this is option is disabled.
			 * @note This won't affect the log file.
			 * @param state The state.
			 * @return void
			 */
			void
			enablePrintOnlyErrors (bool state) noexcept
			{
				m_flags[PrintOnlyErrors] = state;
			}

			/**
			 * @brief Returns whether only errors are print in the standard console.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			printOnlyErrors () const noexcept
			{
				return m_flags[PrintOnlyErrors];
			}

			/**
			 * @brief Enables the location "[file:number]" section in the standard console. By default, this options is enabled.
			 * @note This won't affect the log file.
			 * @param state The state.
			 * @return void
			 */
			void
			enableShowLocation (bool state) noexcept
			{
				m_flags[ShowLocation] = state;
			}

			/**
			 * @brief Returns it the location in the standard console is enabled.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			showLocation () const noexcept
			{
				return m_flags[ShowLocation];
			}

			/**
			 * @brief Enables the thread information section in the standard console. By default, this options is enabled.
			 * @note This won't affect the log file.
			 * @param state The state.
			 * @return void
			 */
			void
			enableShowThreadInfos (bool state) noexcept
			{
				m_flags[ShowThreadInfos] = state;
			}

			/**
			 * @brief Returns whether the thread information in the standard console is enabled.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			showThreadInfos () const noexcept
			{
				return m_flags[ShowThreadInfos];
			}

			/**
			 * @brief Turns ON/OFF the tracer.
			 * @param state The state.
			 * @return void
			 */
			void
			enableTracing (bool state) noexcept
			{
				m_flags[EnableTracing] = state;
			}

			/**
			 * @brief Returns whether the tracer is enabled.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isTracingEnabled () const noexcept
			{
				return m_flags[EnableTracing];
			}

			/**
			 * @brief Prepares the logger to write into a logfile.
			 * @param filepath A reference to a string for the filepath.
			 * @return bool
			 */
			bool enableLogger (const std::string & filepath) noexcept;

			/**
			 * @brief Removes the logger and closes the logfile.
			 * @return void
			 */
			void disableLogger () noexcept;

			/**
			 * @brief Turns ON/OFF the tracer writing into the logfile.
			 * @param state The state.
			 * @return void
			 */
			void
			enableLogging (bool state) noexcept
			{
				if ( m_logger == nullptr )
				{
					return;
				}

				m_flags[EnableLogging] = state;
			}

			/**
			 * @brief Returns whether the tracer is writing into the logfile.
			 * @note Returns always false, if the logger is disabled.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isLoggingEnabled () const noexcept
			{
				return m_flags[EnableLogging];
			}

			/**
			 * @brief Reads the application settings.
			 * @warning This can't be done at startup because the Tracer service is the first to be setup.
			 * @return void
			 */
			void readSettings () noexcept;

			/**
			 * @brief Creates a log.
			 * @param severity The type of log.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a string for the log content.
			 * @param location A pointer to a C-string to describe the location. Use LOCATION for default behavior.
			 * @return void
			 */
			void trace (Severity severity, const char * tag, const std::string & message, const char * location) const noexcept;

			/**
			 * @brief Creates a log with the Blob class.
			 * @param severity The type of log.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a string for the log content.
			 * @param location A pointer to a C-string to describe the location. Use LOCATION for default behavior.
			 * @return void
			 */
			void
			trace (Severity severity, const char * tag, const Libs::BlobTrait & message, const char * location) const noexcept
			{
				this->trace(severity, tag, message.get(), location);
			}

			/**
			 * @brief Creates a log.
			 * @param severity The type of log.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a string for the log content.
			 * @param location A reference to a source_location. Default constructed in place.
			 * @return void
			 */
			void trace (Severity severity, const char * tag, const std::string & message, const std::source_location & location = std::source_location::current()) const noexcept;

			/**
			 * @brief Creates a log with the Blob class.
			 * @param severity The type of log.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a string for the log content.
			 * @param location A reference to a source_location. Default constructed in place.
			 * @return void
			 */
			void
			trace (Severity severity, const char * tag, const Libs::BlobTrait & message, const std::source_location & location = std::source_location::current()) const noexcept
			{
				this->trace(severity, tag, message.get(), location);
			}

			/**
			 * @brief Creates a log for a specific API.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param functionName A pointer on a c-string for the API function.
			 * @param message A reference to a string for the message. Default none.
			 * @param location A reference to a source_location. Default constructed in place.
			 * @return void
			 */
			void traceAPI (const char * tag, const char * functionName, const std::string & message = {}, const std::source_location & location = std::source_location::current()) const noexcept;

			/**
			 * @brief Returns the instance of tracer.
			 * @return Tracer *
			 */
			[[nodiscard]]
			static
			Tracer *
			instance () noexcept
			{
				return s_instance;
			}

			/**
			 * @brief Creates a quick log with Info as severity.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a string for the log content.
			 * @param location A reference to a source_location. Default constructed in place.
			 * @return void
			 */
			static
			void
			info (const char * tag, const std::string & message, const std::source_location & location = std::source_location::current()) noexcept
			{
				s_instance->trace(Severity::Info, tag, message, location);
			}

			/**
			 * @brief Creates a quick log with Info as severity.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a blob for the log content.
			 * @param location A reference to a source_location. Default constructed in place.
			 * @return void
			 */
			static
			void
			info (const char * tag, const Libs::BlobTrait & message, const std::source_location & location = std::source_location::current()) noexcept
			{
				s_instance->trace(Severity::Info, tag, message.get(), location);
			}

			/**
			 * @brief Creates a quick log with Success as severity.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a string for the log content.
			 * @param location A reference to a source_location. Default constructed in place.
			 * @return void
			 */
			static
			void
			success (const char * tag, const std::string & message, const std::source_location & location = std::source_location::current()) noexcept
			{
				s_instance->trace(Severity::Success, tag, message, location);
			}

			/**
			 * @brief Creates a quick log with Success as severity.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a blob for the log content.
			 * @param location A reference to a source_location. Default constructed in place.
			 * @return void
			 */
			static
			void
			success (const char * tag, const Libs::BlobTrait & message, const std::source_location & location = std::source_location::current()) noexcept
			{
				s_instance->trace(Severity::Success, tag, message.get(), location);
			}

			/**
			 * @brief Creates a quick log with Warning as severity.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a string for the log content.
			 * @param location A reference to a source_location. Default constructed in place.
			 * @return void
			 */
			static
			void
			warning (const char * tag, const std::string & message, const std::source_location & location = std::source_location::current()) noexcept
			{
				s_instance->trace(Severity::Warning, tag, message, location);
			}

			/**
			 * @brief Creates a quick log with Warning as severity.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a blob for the log content.
			 * @param location A reference to a source_location. Default constructed in place.
			 * @return void
			 */
			static
			void
			warning (const char * tag, const Libs::BlobTrait & message, const std::source_location & location = std::source_location::current()) noexcept
			{
				s_instance->trace(Severity::Warning, tag, message.get(), location);
			}

			/**
			 * @brief Creates a quick log with Error as severity.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a string for the log content.
			 * @param location A reference to a source_location. Default constructed in place.
			 * @return void
			 */
			static
			void
			error (const char * tag, const std::string & message, const std::source_location & location = std::source_location::current()) noexcept
			{
				s_instance->trace(Severity::Error, tag, message, location);
			}

			/**
			 * @brief Creates a quick log with Error as severity.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a blob for the log content.
			 * @param location A reference to a source_location. Default constructed in place.
			 * @return void
			 */
			static
			void
			error (const char * tag, const Libs::BlobTrait & message, const std::source_location & location = std::source_location::current()) noexcept
			{
				s_instance->trace(Severity::Error, tag, message.get(), location);
			}

			/**
			 * @brief Creates a quick log with Fatal as severity.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a string for the log content.
			 * @param location A reference to a source_location. Default constructed in place.
			 * @return void
			 */
			static
			void
			fatal (const char * tag, const std::string & message, const std::source_location & location = std::source_location::current()) noexcept
			{
				s_instance->trace(Severity::Fatal, tag, message, location);
			}

			/**
			 * @brief Creates a quick log with Fatal as severity.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a blob for the log content.
			 * @param location A reference to a source_location. Default constructed in place.
			 * @return void
			 */
			static
			void
			fatal (const char * tag, const Libs::BlobTrait & message, const std::source_location & location = std::source_location::current()) noexcept
			{
				s_instance->trace(Severity::Fatal, tag, message.get(), location);
			}

			/**
			 * @brief Creates a quick log with Debug as severity.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param message A reference to a string for the log content.
			 * @param location A reference to a source_location. Default constructed in place.
			 * @return void
			 */
			static
			void
			debug (const char * tag, const std::string & message, const std::source_location & location = std::source_location::current()) noexcept
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
			 * @return void
			 */
			static
			void
			debug (const char * tag, const Libs::BlobTrait & message, const std::source_location & location = std::source_location::current()) noexcept
			{
				#ifdef DEBUG
				s_instance->trace(Severity::Debug, tag, message.get(), location);
				#endif
			}

			/**
			 * @brief Creates a quick log for API usage.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param functionName A pointer on a c-string for the API function.
			 * @param message A reference to a string for the log content. Default none.
			 * @param location A reference to a source_location. Default constructed in place.
			 * @return void
			 */
			static
			void
			API (const char * tag, const char * functionName, const std::string & message = {}, const std::source_location & location = std::source_location::current())
			{
				s_instance->traceAPI(tag, functionName, message, location);
			}

			/**
			 * @brief Creates a quick log for API usage.
			 * @param tag A pointer on a c-string for identify and sort logs.
			 * @param functionName A pointer on a c-string for the API function.
			 * @param message A reference to a blob for the log content.
			 * @param location A reference to a source_location. Default constructed in place.
			 * @return void
			 */
			static
			void
			API (const char * tag, const char * functionName, const Libs::BlobTrait & message, const std::source_location & location = std::source_location::current())
			{
				s_instance->traceAPI(tag, functionName, message.get(), location);
			}

			/**
			 * @brief Converts GLFW log facility to trace()
			 * @param error The error number from GLFW library.
			 * @param description The message associated to the error code.
			 * @return void
			 */
			static void traceGLFW (int error, const char * description) noexcept;

		private:

			/** @copydoc EmEn::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc EmEn::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

			/**
			 * @brief Colorizes a message from the severity type.
			 * @param stream A reference to a stream.
			 * @param severity The severity.
			 * @param message A reference to a string.
			 * @return void
			 */
			static
			void
			colorizeMessage (std::stringstream & stream, Severity severity, const std::string & message) noexcept
			{
				switch ( severity )
				{
					case Severity::Debug :
						stream << " \033[1;36m" << message << "\033[0m ";
						break;

					case Severity::Success :
						stream << " \033[1;92m" << message << " \033[0m ";
						break;

					case Severity::Warning :
						stream << " \033[1;35m" << message << " \033[0m ";
						break;

					case Severity::Error :
						stream << " \033[1;91m" << message << " \033[0m ";
						break;

					case Severity::Fatal :
						stream << " \033[1;41m" << message << " \033[0m ";
						break;

					case Severity::Info :
					default :
						stream << ' ' << message << ' ';
						break;
				}
			}

			/**
			 * @brief Injects process and thread info.
			 * @param stream A reference to a stream.
			 * @return void
			 */
			void injectProcessInfo (std::stringstream & stream) const noexcept;

			/**
			 * @brief Filters the current tag. If the method return true, the message with the tag is allowed to be displayed.
			 * @param tag The tag to filter.
			 * @return bool
			 */
			bool filterTag (const char * tag) const noexcept;

			/* Flag names. */
			static constexpr auto ServiceInitialized{0UL};
			static constexpr auto ChildProcess{1UL};
			static constexpr auto PrintOnlyErrors{2UL};
			static constexpr auto ShowLocation{3UL};
			static constexpr auto ShowThreadInfos{4UL};
			static constexpr auto EnableTracing{5UL};
			static constexpr auto EnableLogging{6UL};

			static Tracer * s_instance;

			const Arguments & m_arguments;
			Settings & m_settings;
			std::vector< std::string > m_filters;
			std::unique_ptr< TracerLogger > m_logger;
			std::thread m_loggerProcess;
			int m_parentProcessID{-1};
			int m_processID{-1};
			std::array< bool, 8 > m_flags{
				false/*ServiceInitialized*/,
				false/*ChildProcess*/,
				false/*PrintOnlyErrors*/,
				false/*ShowLocation*/,
				true/*ShowThreadInfos*/,
				true/*EnableTracing*/,
				false/*EnableLogging*/,
				false/*UNUSED*/
			};
	};

	/**
	 * @brief This utils class create a debug trace object.
	 * @extends EmEn::Libs::BlobTrait
	 */
	class TraceDebug final : public Libs::BlobTrait
	{
		public:

			/**
			 * @brief Constructs a debug trace.
			 * @param tag A pointer to a C-string for the tag.
			 * @param location A reference to a source location structure.
			 */
			explicit TraceDebug (const char * tag, const std::source_location & location = std::source_location::current()) noexcept;

			/**
			 * @brief Constructs a debug trace with an initial message.
			 * @param tag A pointer to a C-string for the tag.
			 * @param initialMessage A pointer to a C-string.
			 * @param location A reference to a source location structure.
			 */
			TraceDebug (const char * tag, const char * initialMessage, const std::source_location & location = std::source_location::current()) noexcept;

			/**
			 * @brief Constructs a debug trace with an initial message.
			 * @param tag A pointer to a C-string for the tag.
			 * @param initialMessage A reference to a string.
			 * @param location A reference to a source location structure.
			 */
			TraceDebug (const char * tag, const std::string & initialMessage, const std::source_location & location = std::source_location::current()) noexcept;

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
			~TraceDebug ();

		private:

			const char * m_tag;
			std::source_location m_location;
	};

	/**
	 * @brief This utils class create a success trace object.
	 * @extends EmEn::Libs::BlobTrait
	 */
	class TraceSuccess final : public Libs::BlobTrait
	{
		public:

			/**
			 * @brief Constructs a success trace.
			 * @param tag A pointer to a C-string for the tag.
			 * @param location A reference to a source location structure.
			 */
			explicit TraceSuccess (const char * tag, const std::source_location & location = std::source_location::current()) noexcept;

			/**
			 * @brief Constructs a success trace with an initial message.
			 * @param tag A pointer to a C-string for the tag.
			 * @param initialMessage A pointer to a C-string.
			 * @param location A reference to a source location structure.
			 */
			TraceSuccess (const char * tag, const char * initialMessage, const std::source_location & location = std::source_location::current()) noexcept;

			/**
			 * @brief Constructs a success trace with an initial message.
			 * @param tag A pointer to a C-string for the tag.
			 * @param initialMessage A reference to a string.
			 * @param location A reference to a source location structure.
			 */
			TraceSuccess (const char * tag, const std::string & initialMessage, const std::source_location & location = std::source_location::current()) noexcept;

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
			~TraceSuccess ();

		private:

			const char * m_tag;
			std::source_location m_location;
	};

	/**
	 * @brief This utils class create an info trace object.
	 * @extends EmEn::Libs::BlobTrait
	 */
	class TraceInfo final : public Libs::BlobTrait
	{
		public:

			/**
			 * @brief Constructs an info trace.
			 * @param tag A pointer to a C-string for the tag.
			 * @param location A reference to a source location structure.
			 */
			explicit TraceInfo (const char * tag, const std::source_location & location = std::source_location::current()) noexcept;

			/**
			 * @brief Constructs an info trace with an initial message.
			 * @param tag A pointer to a C-string for the tag.
			 * @param initialMessage A pointer to a C-string.
			 * @param location A reference to a source location structure.
			 */
			TraceInfo (const char * tag, const char * initialMessage, const std::source_location & location = std::source_location::current()) noexcept;

			/**
			 * @brief Constructs an info trace with an initial message.
			 * @param tag A pointer to a C-string for the tag.
			 * @param initialMessage A reference to a string.
			 * @param location A reference to a source location structure.
			 */
			TraceInfo (const char * tag, const std::string & initialMessage, const std::source_location & location = std::source_location::current()) noexcept;

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
			~TraceInfo ();

		private:

			const char * m_tag;
			std::source_location m_location;
	};

	/**
	 * @brief This utils class create a warning trace object.
	 * @extends EmEn::Libs::BlobTrait
	 */
	class TraceWarning final : public Libs::BlobTrait
	{
		public:

			/**
			 * @brief Constructs a warning trace.
			 * @param tag A pointer to a C-string for the tag.
			 * @param location A reference to a source location structure.
			 */
			explicit TraceWarning (const char * tag, const std::source_location & location = std::source_location::current()) noexcept;

			/**
			 * @brief Constructs a warning trace with an initial message.
			 * @param tag A pointer to a C-string for the tag.
			 * @param initialMessage A pointer to a C-string.
			 * @param location A reference to a source location structure.
			 */
			TraceWarning (const char * tag, const char * initialMessage, const std::source_location & location = std::source_location::current()) noexcept;

			/**
			 * @brief Constructs a warning trace with an initial message.
			 * @param tag A pointer to a C-string for the tag.
			 * @param initialMessage A reference to a string.
			 * @param location A reference to a source location structure.
			 */
			TraceWarning (const char * tag, const std::string & initialMessage, const std::source_location & location = std::source_location::current()) noexcept;

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
			~TraceWarning ();

		private:

			const char * m_tag;
			std::source_location m_location;
	};

	/**
	 * @brief TThis utils class create an error trace object.
	 * @extends EmEn::Libs::BlobTrait
	 */
	class TraceError final : public Libs::BlobTrait
	{
		public:

			/**
			 * @brief Constructs an error trace.
			 * @param tag A pointer to a C-string for the tag.
			 * @param location A reference to a source location structure.
			 */
			explicit TraceError (const char * tag, const std::source_location & location = std::source_location::current()) noexcept;

			/**
			 * @brief Constructs an error trace with an initial message.
			 * @param tag A pointer to a C-string for the tag.
			 * @param initialMessage A pointer to a C-string.
			 * @param location A reference to a source location structure.
			 */
			TraceError (const char * tag, const char * initialMessage, const std::source_location & location = std::source_location::current()) noexcept;

			/**
			 * @brief Constructs an error trace with an initial message.
			 * @param tag A pointer to a C-string for the tag.
			 * @param initialMessage A reference to a string.
			 * @param location A reference to a source location structure.
			 */
			TraceError (const char * tag, const std::string & initialMessage, const std::source_location & location = std::source_location::current()) noexcept;

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
			~TraceError ();

		private:

			const char * m_tag;
			std::source_location m_location;
	};

	/**
	 * @brief This utils class create a fatal trace object.
	 * @extends EmEn::Libs::BlobTrait
	 */
	class TraceFatal final : public Libs::BlobTrait
	{
		public:

			/**
			 * @brief Constructs a fatal trace.
			 * @param tag A pointer to a C-string for the tag.
			 * @param terminate Call std::terminate() at this object destructor. Default false.
			 * @param location A reference to a source location structure.
			 */
			explicit TraceFatal (const char * tag, bool terminate = false, const std::source_location & location = std::source_location::current()) noexcept;

			/**
			 * @brief Constructs a fatal trace with an initial message.
			 * @param tag A pointer to a C-string for the tag.
			 * @param initialMessage A pointer to a C-string.
			 * @param terminate Call std::terminate() at this object destructor. Default false.
			 * @param location A reference to a source location structure.
			 */
			TraceFatal (const char * tag, const char * initialMessage, bool terminate = false, const std::source_location & location = std::source_location::current()) noexcept;

			/**
			 * @brief Constructs a fatal trace with an initial message.
			 * @param tag A pointer to a C-string for the tag.
			 * @param initialMessage A reference to a string.
			 * @param terminate Call std::terminate() at this object destructor. Default false.
			 * @param location A reference to a source location structure.
			 */
			TraceFatal (const char * tag, const std::string & initialMessage, bool terminate = false, const std::source_location & location = std::source_location::current()) noexcept;

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
			~TraceFatal ();

		private:

			const char * m_tag;
			std::source_location m_location;
			bool m_terminate;
	};

	/**
	 * @brief This utils class create an API trace object.
	 * @extends EmEn::Libs::BlobTrait
	 */
	class TraceAPI final : public Libs::BlobTrait
	{
		public:

			/**
			 * @brief Constructs an API trace.
			 * @param tag A pointer to a C-string for the tag.
			 * @param functionName A pointer on a c-string for the API function.
			 * @param terminate Call std::terminate() at this object destructor. Default false.
			 * @param location A reference to a source location structure.
			 */
			explicit TraceAPI (const char * tag, const char * functionName, bool terminate = false, const std::source_location & location = std::source_location::current()) noexcept;

			/**
			 * @brief Constructs a fatal trace with an initial message.
			 * @param tag A pointer to a C-string for the tag.
			 * @param functionName A pointer on a c-string for the API function.
			 * @param initialMessage A pointer to a C-string.
			 * @param terminate Call std::terminate() at this object destructor. Default false.
			 * @param location A reference to a source location structure.
			 */
			TraceAPI (const char * tag, const char * functionName, const char * initialMessage, bool terminate = false, const std::source_location & location = std::source_location::current()) noexcept;

			/**
			 * @brief Constructs a fatal trace with an initial message.
			 * @param tag A pointer to a C-string for the tag.
			 * @param functionName A pointer on a c-string for the API function.
			 * @param initialMessage A reference to a string.
			 * @param terminate Call std::terminate() at this object destructor. Default false.
			 * @param location A reference to a source location structure.
			 */
			TraceAPI (const char * tag, const char * functionName, const std::string & initialMessage, bool terminate = false, const std::source_location & location = std::source_location::current()) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			TraceAPI (const TraceAPI & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			TraceAPI (TraceAPI && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return TraceFatal &
			 */
			TraceAPI & operator= (const TraceAPI & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return TraceFatal &
			 */
			TraceAPI & operator= (TraceAPI && copy) noexcept = delete;

			/**
			 * @brief Destructs the trace and calls the real tracer service.
			 */
			~TraceAPI ();

		private:

			const char * m_tag;
			const char * m_functionName;
			std::source_location m_location;
			bool m_terminate;
	};
}
