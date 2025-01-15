/*
 * src/Libraries/Version.hpp
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
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

namespace Libraries
{
	/**
	 * @brief Utility to create a parametric versioning.
	 * @TODO Create a templated version to have multiple depth.
	 */
	class Version final
	{
		public:

			/**
			 * @brief Constructs a default version.
			 */
			Version () noexcept = default;

			/**
			 * @brief Constructs a version.
			 * @param major The major number.
			 * @param minor The minor number.
			 * @param revision The revision number.
			 */
			constexpr Version (int major, int minor, int revision) noexcept
				: m_major(major), m_minor(minor), m_revision(revision)
			{

			}

			/**
			 * @brief Constructs a version from a string.
			 * @param raw A string that hold a version like "1.0.0".
			 */
			explicit Version (const std::string & raw) noexcept;

			/**
			 * @brief Constructs a version from a number.
			 * @param bitmask An unsigned integer of 32 bits.
			 */
			explicit Version (uint32_t bitmask) noexcept;

			/**
			 * @brief Overloads the equality operator.
			 * @param operand A reference to a version.
			 * @return bool
			 */
			bool operator== (const Version & operand) const noexcept;

			/**
			 * @brief Overloads the inequality operator.
			 * @param operand A reference to a version.
			 * @return bool
			 */
			bool operator!= (const Version & operand) const noexcept;

			/**
			 * @brief Overloads the greater than operator.
			 * @param operand A reference to a version.
			 * @return bool
			 */
			bool operator> (const Version & operand) const noexcept;

			/**
			 * @brief Overloads the greater or equal than operator.
			 * @param operand A reference to a version.
			 * @return bool
			 */
			bool operator>= (const Version & operand) const noexcept;

			/**
			 * @brief Overloads the lesser than operator.
			 * @param operand A reference to a version.
			 * @return bool
			 */
			bool operator< (const Version & operand) const noexcept;

			/**
			 * @brief Overloads the lesser or equal than operator.
			 * @param operand A reference to a version.
			 * @return bool
			 */
			bool operator<= (const Version & operand) const noexcept;

			/**
			 * @brief Sets the version.
			 * @param major The major number.
			 * @param minor The minor number.
			 * @param revision The revision number.
			 * @return void
			 */
			void
			set (int major, int minor, int revision) noexcept
			{
				m_major = major;
				m_minor = minor;
				m_revision = revision;
			}

			/**
			 * @brief Parses a string a set the version.
			 * @param raw A reference to a string to parse.
			 * @return bool
			 */
			bool set (const std::string & raw) noexcept;

			/**
			 * @brief Sets the major number of the version.
			 * @param value
			 * @return void
			 */
			void
			setMajor (int value) noexcept
			{
				m_major = value;
			}

			/**
			 * @brief Sets the minor number of the version.
			 * @param value
			 * @return void
			 */
			void
			setMinor (int value) noexcept
			{
				m_minor = value;
			}

			/**
			 * @brief Sets the revision number of the version.
			 * @param value
			 * @return void
			 */
			void
			setRevision (int value) noexcept
			{
				m_revision = value;
			}

			/**
			 * @brief Returns the major number of the version.
			 * @return int
			 */
			[[nodiscard]]
			int
			major () const noexcept
			{
				return m_major;
			}

			/**
			 * @brief Returns the minor number of the version.
			 * @return int
			 */
			[[nodiscard]]
			int
			minor () const noexcept
			{
				return m_minor;
			}

			/**
			 * @brief Returns the revision number of the version.
			 * @return int
			 */
			[[nodiscard]]
			int
			revision () const noexcept
			{
				return m_revision;
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const Version & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend std::string to_string (const Version & obj) noexcept;

		private:

			int m_major{0};
			int m_minor{0};
			int m_revision{0};
	};
}
