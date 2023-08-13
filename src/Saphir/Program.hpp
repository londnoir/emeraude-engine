/*
 * Emeraude/Saphir/Program.hpp
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
#include <memory>

/* Local inclusions */
#include "VertexShader.hpp"
#include "TesselationControlShader.hpp"
#include "TesselationEvaluationShader.hpp"
#include "GeometryShader.hpp"
#include "FragmentShader.hpp"

namespace Emeraude::Saphir
{
	/**
	 * @brief Class act like an old OpenGL program to group shaders.
	 */
	class Program final
	{
		public:

			/**
			 * @brief Constructs a program.
			 */
			Program () noexcept = default;

			/**
			 * @brief Returns whether the program is complete.
			 * @return bool
			 */
			[[nodiscard]]
			bool isComplete () const noexcept;

		private:

			std::shared_ptr< VertexShader > m_vertexShader{};
			std::shared_ptr< TesselationControlShader > m_tesselationControlShader{};
			std::shared_ptr< TesselationEvaluationShader > m_tesselationEvaluationShader{};
			std::shared_ptr< GeometryShader > m_geometryShader{};
			std::shared_ptr< FragmentShader > m_fragmentShader{};
	};
}
