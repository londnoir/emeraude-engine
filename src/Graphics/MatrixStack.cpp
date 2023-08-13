/*
 * Emeraude/Graphics/MatrixStack.cpp
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

#include "MatrixStack.hpp"

namespace Emeraude::Graphics
{
	using namespace Libraries;

	const Math::Matrix< 4, float > MatrixStack::Identity;

	void
	MatrixStack::add (const Math::Matrix< 4, float > & matrix) noexcept
	{
		if ( m_matrices.empty() )
			m_matrices.emplace(matrix);
		else
			m_matrices.emplace(m_matrices.top() * matrix);
	}

	void
	MatrixStack::replace (const Math::Matrix< 4, float > & matrix) noexcept
	{
		if ( m_matrices.empty() )
			m_matrices.emplace(matrix);
		else
			m_matrices.top() = matrix;
	}

	void
	MatrixStack::pop () noexcept
	{
		if ( m_matrices.empty() )
			return;

		m_matrices.pop();
	}

	void
	MatrixStack::clear () noexcept
	{
		std::stack< Math::Matrix< 4, float > > empty;

		std::swap(m_matrices, empty);
	}

	const Math::Matrix< 4, float > &
	MatrixStack::top () const noexcept
	{
		if ( m_matrices.empty() )
			return Identity;

		return m_matrices.top();
	}
}
