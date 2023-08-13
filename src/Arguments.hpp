/*
 * Emeraude/Arguments.hpp
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
#include <map>
#include <string>
#include <vector>

/* Local inclusions */
#include "ServiceInterface.hpp"
#include "Argument.hpp"

namespace Emeraude
{
	/**
	 * @brief The application arguments service.
	 * @extends Emeraude::ServiceInterface This is a service.
	 */
	class Arguments final : public ServiceInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"ArgumentsService"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs the application arguments service.
			 * @param argc The argument count from the standard C main function.
			 * @param argv The argument values from the standard C main function.
			 */
			explicit Arguments (int argc = 0, const char * argv[] = nullptr) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Arguments (const Arguments & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Arguments (Arguments && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			Arguments & operator= (const Arguments & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			Arguments & operator= (Arguments && copy) noexcept = delete;

			/**
			 * @brief Destructs the application arguments service.
			 */
			~Arguments () override;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::ServiceInterface::usable() */
			[[nodiscard]]
			bool usable () const noexcept override;

			/**
			 * @brief Returns the argument count from the standard C main function.
			 * @return int
			 */
			[[nodiscard]]
			int getArgc () const noexcept;

			/**
			 * @brief Returns the argument values from the standard C main function.
			 * @return const char * *
			 */
			[[nodiscard]]
			const char * * getArgv () const noexcept;

			/**
			 * @brief Returns the copy of the argument values from the standard C main function.
			 * @return char * *
			 */
			[[nodiscard]]
			char * * getArgvCopy () const noexcept;

			/**
			 * @brief Returns a parsed argument from the command line. Unique name version.
			 * @param name A reference to a string to define the argument name from the command line.
			 * @return Argument
			 */
			[[nodiscard]]
			Argument get (const std::string & name) const noexcept;

			/**
			 * @brief Returns a parsed argument from the command line. The name an is short version.
			 * @param name A reference to a string defining the argument name from the command line.
			 * @param name A reference to a string for an alternate name.
			 * @return Argument
			 */
			[[nodiscard]]
			Argument get (const std::string & name, const std::string & alternateName) const noexcept;

			/**
			 * @brief Returns a parsed argument from the command line. Multiple name version.
			 * @param name A reference to a vector of string defining all possible argument names from the command line.
			 * @return Argument
			 */
			[[nodiscard]]
			Argument get (const std::vector< std::string > & namesList) const noexcept;

			/**
			 * @brief Returns the application executable path.
			 * @return const string &
			 */
			[[nodiscard]]
			const std::string & getBinaryPath () const noexcept;

			/**
			 * @brief Returns the instance of the file system.
			 * @return Arguments *
			 */
			[[nodiscard]]
			static
			Arguments * instance () noexcept;

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const Arguments & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend std::string to_string (const Arguments & obj) noexcept;

		private:

			/** @copydoc Emeraude::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc Emeraude::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

			static Arguments * s_instance; // NOLINT NOTE: Singleton behavior

			std::map< std::string, Argument > m_arguments{};
			std::string m_binaryPath{};
			int m_argc{0};
			const char * * m_argv{nullptr};
			char * * m_argvCopy{nullptr};
	};
}
