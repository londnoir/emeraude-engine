/*
 * src/Graphics/MatrixStack.hpp
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
#include <stack>

/* Local inclusions. */
#include "Libs/Math/Matrix.hpp"

namespace EmEn::Graphics
{
	/**
	 * @brief Controls the current object being displayed respectively in the scene hierarchy.
	 */
	class MatrixStack final
	{
		public:

			/**
			 * @brief Constructs a default matrix stack.
			 */
			MatrixStack () = default;

			/**
			 * @brief Multiplies the matrix with the last on on the stack and add it to the top.
			 * @param matrix A reference to a transform matrix.
			 * @return void
			 */
			void
			add (const Libs::Math::Matrix< 4, float > & matrix) noexcept
			{
				if ( m_matrices.empty() )
				{
					m_matrices.emplace(matrix);
				}
				else
				{
					m_matrices.emplace(m_matrices.top() * matrix);
				}
			}

			/**
			 * @brief Replaces the top matrix with the new one.
			 * @param matrix A reference to a transform matrix.
			 * @return void
			 */
			void
			replace (const Libs::Math::Matrix< 4, float > & matrix) noexcept
			{
				if ( m_matrices.empty() )
				{
					m_matrices.emplace(matrix);
				}
				else
				{
					m_matrices.top() = matrix;
				}
			}

			/**
			 * @brief Removes the top matrix.
			 * @return void
			 */
			void
			pop () noexcept
			{
				if ( m_matrices.empty() )
				{
					return;
				}

				m_matrices.pop();
			}

			/**
			 * @brief Empty the stack.
			 * @return void
			 */
			void
			clear () noexcept
			{
				std::stack< Libs::Math::Matrix< 4, float > > empty;

				std::swap(m_matrices, empty);
			}

			/**
			 * @brief Returns the top matrix or Identity if the stack is empty.
			 * @return const Libs::Math::Matrix< 4, float > &
			 */
			[[nodiscard]]
			const Libs::Math::Matrix< 4, float > &
			top () const noexcept
			{
				if ( m_matrices.empty() )
				{
					return s_identity;
				}

				return m_matrices.top();
			}

		private:

			static const Libs::Math::Matrix< 4, float > s_identity;

			std::stack< Libs::Math::Matrix< 4, float > > m_matrices;
	};
}
