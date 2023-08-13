/*
 * Emeraude/Graphics/MatrixStack.hpp
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
#include <stack>

/* Local inclusions */
#include "Math/Matrix.hpp"

namespace Emeraude::Graphics
{
	/** @brief Controls the current object being displayed respectively in the scene hierarchy. */
	class MatrixStack final
	{
		public:

			static const Libraries::Math::Matrix< 4, float > Identity;

			/**
			 * @brief Default constructor.
			 */
			MatrixStack () = default;

			/**
			 * @brief Multiplies the matrix with the last on on the stack and add it to the top.
			 * @param matrix A reference to a transform matrix.
			 */
			void add (const Libraries::Math::Matrix< 4, float > & matrix) noexcept;

			/**
			 * @brief Replaces the top matrix with the new one.
			 * @param matrix A reference to a transform matrix.
			 */
			void replace (const Libraries::Math::Matrix< 4, float > & matrix) noexcept;

			/**
			 * @brief Removes the top matrix.
			 */
			void pop () noexcept;

			/**
			 * @brief Empty the stack.
			 */
			void clear () noexcept;

			/**
			 * @brief Returns the top matrix or Identity if the stack is empty.
			 * @return const Libraries::Math::Matrix< 4, float > &
			 */
			[[nodiscard]]
			const Libraries::Math::Matrix< 4, float > & top () const noexcept;

		private:

			std::stack< Libraries::Math::Matrix< 4, float > > m_matrices{};
	};
}
