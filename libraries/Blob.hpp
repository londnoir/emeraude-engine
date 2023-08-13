/*
 * Libraries/Blob.hpp
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
#include <sstream>
#include <string>

namespace Libraries
{
	/**
	 * @brief Class to ease the creation of a std::string using std::cout syntax.
	 */
	class Blob
	{
		public:

			/**
			 * @brief Constructor a blob.
			 */
			Blob () = default;

			/**
			 * @brief Deleted copy constructor.
			 * @param other A reference to a blob.
			 */
			Blob (const Blob & other) = delete;

			/**
			 * @brief Destructs the blob.
			 */
			~Blob () = default;

			/**
			 * @brief Deleted assignment operator.
			 * @param other A reference to a blob.
			 */
			Blob & operator= (const Blob & other) = delete;

			/**
			 * @brief Deleted move constructor.
			 * @param other A reference to a blob.
			 */
			Blob (Blob && other) noexcept = delete;

			/**
			 * @brief Deleted move assignment operator.
			 * @param other A reference to a blob.
			 */
			Blob & operator= (Blob && other) noexcept = delete;

			/**
			 * @brief Adds a value to the blob content.
			 * @tparam data_t The type of the data.
			 * @param value A reference to the data.
			 * @return Blob &
			 */
			template< typename data_t >
			Blob &
			operator<< (const data_t & value) noexcept
			{
				m_stream << value;

				return *this;
			}

			/**
			 * @brief Adds a boolean value to the blob content.
			 * @param value The value of the boolean.
			 * @return Blob &
			 */
			inline
			Blob &
			operator<< (bool value) noexcept
			{
				m_stream << ( value ? "True" : "False" );

				return *this;
			}

			/**
			 * @brief Adds a raw pointer value to the blob content.
			 * @param value The value of the pointer.
			 * @return Blob &
			 */
			inline
			Blob &
			operator<< (void * value) noexcept
			{
				m_stream << '@' << value;

				return *this;
			}

			/**
			 * @brief Adds a raw pointer value to the blob content.
			 * @param value The value of the pointer.
			 * @return Blob &
			 */
			inline
			Blob &
			operator<< (const void * value) noexcept
			{
				m_stream << '@' << value;

				return *this;
			}

			/**
			 * @brief Adds a stream to the blob content.
			 * @param value The value of the pointer.
			 * @return Blob &
			 */
			inline
			Blob &
			operator<< (const std::stringstream & value) noexcept
			{
				m_stream << value.str();

				return *this;
			}

			/**
			 * @brief Returns the blob content in a string.
			 * @return std::string
			 */
			std::string
			get () const noexcept
			{
				return m_stream.str();
			}

		private:

			std::stringstream m_stream{};
	};
}
