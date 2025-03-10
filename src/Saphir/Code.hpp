/*
 * src/Saphir/Code.hpp
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

/* STL inclusions. */
#include <sstream>

/* Local inclusions for usages. */
#include "Libraries/Math/Vector.hpp"
#include "Libraries/PixelFactory/Color.hpp"
#include "CodeGeneratorInterface.hpp"

namespace Emeraude::Saphir
{
	/** @brief Code location type. */
	enum class Location
	{
		Top,
		Main,
		Output
	};

	/** @brief Line ending enumeration. */
	enum class Line
	{
		End,
		Blank
	};

	/**
	 * @brief The code instruction class.
	 * @note A '\n' character is automatically put at the end of each generated code.
	 * Use Line::end when writing multiple line of code to automatically follow the indentation.
	 */
	class Code final
	{
		public:

			/** 
			 * @brief Constructs a code.
			 * @param generator A reference to the shader generator.
			 * @param type The code location type. Default main instruction.
			 * @param depth The indentation depth. Default 1.
			 */
			explicit Code (CodeGeneratorInterface & generator, Location type = Location::Main, size_t depth = 1) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Code (const Code & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Code (Code && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			Code & operator= (const Code & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			Code & operator= (Code && copy) noexcept = delete;

			/**
			 * @brief Destructs the code.
			 * @note This will generates the code inside the generator.
			 */
			~Code ();

			/**
			 * @brief Adds a line control token.
			 * @param value The token.
			 * @return Code &
			 */
			Code & operator<< (const Line & value) noexcept;

			/**
			 * @brief Adds a vector 2 to the code content.
			 * @param value A reference to a vector.
			 * @return std::string
			 */
			Code &
			operator<< (const Libraries::Math::Vector< 2, float > & value) noexcept
			{
				m_code << "vec2(" << value.x() << ", " << value.y() << ")";

				return *this;
			}

			/**
			 * @brief Adds a vector 3 to the code content.
			 * @param value A reference to a vector.
			 * @return std::string
			 */
			Code &
			operator<< (const Libraries::Math::Vector< 3, float > & value) noexcept
			{
				m_code << "vec3(" << value.x() << ", " << value.y() << ", " << value.z() << ")";

				return *this;
			}

			/**
			 * @brief Adds a vector 4 to the code content.
			 * @param value A reference to a vector.
			 * @return std::string
			 */
			Code &
			operator<< (const Libraries::Math::Vector< 4, float > & value) noexcept
			{
				m_code << "vec4(" << value.x() << ", " << value.y() << ", " << value.z() << ", " << value.w() << ")";

				return *this;
			}

			/**
			 * @brief Adds a vector 4 to the code content.
			 * @param value A reference to a vector.
			 * @return std::string
			 */
			Code &
			operator<< (const Libraries::PixelFactory::Color< float > & value) noexcept
			{
				m_code << "vec4(" << value.red() << ", " << value.green() << ", " << value.blue() << ", " << value.alpha() << ")";

				return *this;
			}

			/**
			 * @brief Adds a generic type to the code content.
			 * @tparam data_t The type of the data.
			 * @param value A reference to the data.
			 * @return Code &
			 */
			template< typename data_t >
			Code &
			operator<< (const data_t & value) noexcept
			{
				m_code << value;

				return *this;
			}

		private:

			CodeGeneratorInterface & m_generator;
			Location m_type;
			std::string m_indent;
			std::stringstream m_code{};
	};
}
