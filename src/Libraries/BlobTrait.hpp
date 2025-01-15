/*
 * src/Libraries/BlobTrait.hpp
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
#include <sstream>
#include <string>

namespace Libraries
{
	/**
	 * @brief Class to ease the creation of a std::string using the std::cout syntax.
	 */
	class BlobTrait
	{
		public:

			/**
			 * @brief Constructs a blob.
			 */
			BlobTrait () = default;

			/**
			 * @brief Constructs a blob with an initial string.
			 * @param initialString A pointer to a C-string.
			 */
			explicit BlobTrait (const char * initialString);

			/**
			 * @brief Constructs a blob with an initial string.
			 * @param initialString A reference to a string.
			 */
			explicit BlobTrait (const std::string & initialString);

			/**
			 * @brief Deleted copy constructor.
			 * @param other A reference to a blob.
			 */
			BlobTrait (const BlobTrait & other) = delete;

			/**
			 * @brief Deleted assignment operator.
			 * @param other A reference to a blob.
			 * @return BlobTrait &
			 */
			BlobTrait & operator= (const BlobTrait & other) = delete;

			/**
			 * @brief Deleted move constructor.
			 * @param other A reference to a blob.
			 */
			BlobTrait (BlobTrait && other) noexcept = delete;

			/**
			 * @brief Deleted move assignment operator.
			 * @param other A reference to a blob.
			 * @return BlobTrait &
			 */
			BlobTrait & operator= (BlobTrait && other) noexcept = delete;

			/**
			 * @brief Destructs the blob.
			 */
			~BlobTrait () = default;

			/**
			 * @brief Adds a value to the blob content.
			 * @tparam data_t The type of the data.
			 * @param value A reference to the data.
			 * @return BlobTrait &
			 */
			template< typename data_t >
			BlobTrait &
			operator<< (const data_t & value) noexcept
			{
				m_stream << value;

				return *this;
			}

			/**
			 * @brief Adds a boolean value to the blob content.
			 * @param value The value of the boolean.
			 * @return BlobTrait &
			 */
			BlobTrait &
			operator<< (bool value) noexcept
			{
				m_stream << ( value ? "True" : "False" );

				return *this;
			}

			/**
			 * @brief Adds a raw pointer value to the blob content.
			 * @param value The value of the pointer.
			 * @return BlobTrait &
			 */
			BlobTrait &
			operator<< (void * value) noexcept
			{
				m_stream << '@' << value;

				return *this;
			}

			/**
			 * @brief Adds a raw pointer value to the blob content.
			 * @param value The value of the pointer.
			 * @return BlobTrait &
			 */
			BlobTrait &
			operator<< (const void * value) noexcept
			{
				m_stream << '@' << value;

				return *this;
			}

			/**
			 * @brief Adds a stream to the blob content.
			 * @param value The value of the pointer.
			 * @return BlobTrait &
			 */
			BlobTrait &
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

			std::stringstream m_stream;
	};
}
