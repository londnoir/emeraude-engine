/*
 * Emeraude/Tool/GeometryDataPrinter.hpp
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

/* Local inclusions for inheritances. */
#include "ToolInterface.hpp"

/* Local inclusions for usages. */
#include "Graphics/Types.hpp"
#include "VertexFactory/Shape.hpp"

namespace Emeraude::Tool
{
	/**
	 * @brief The geometry data printer tool.
	 * @extends Emeraude::Tool::ToolInterface This is tool interface.
	 */
	class GeometryDataPrinter final : public ToolInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"GeometryDataPrinter"};

			/**
			 * @brief Constructs the geometry data printer.
			 * @param arguments A reference to the arguments.
			 */
			explicit GeometryDataPrinter (const Arguments & arguments) noexcept;

			/** @copydoc Emeraude::Tool::ToolInterface::execute() */
			[[nodiscard]]
			bool execute () noexcept override;

		private:

			/**
			 * @brief Print vertices array.
			 * @return std::string
			 */
			[[nodiscard]]
			std::string printVertices () const noexcept;

			/**
			 * @brief Print indices array.
			 * @return std::string
			 */
			[[nodiscard]]
			std::string printIndices () const noexcept;

			/* Flag names */
			static constexpr auto EnableNormals = 0UL;
			static constexpr auto EnableTangentSpace = 1UL;
			static constexpr auto EnableTexCoords = 2UL;
			static constexpr auto Enable3DTexCoords = 3UL;

			const Arguments & m_arguments;
			std::string m_outputFile{};
			Libraries::VertexFactory::Shape< float > m_shape{};
			Graphics::ShapeType m_shapeType{Graphics::ShapeType::Cube};
			float m_baseSize{1.0F};
			float m_baseLength{4.0F};
			size_t m_quality{8};
			std::array< bool, 8 > m_flags{
				false/*EnableNormals*/,
				false/*EnableTangentSpace*/,
				false/*EnableTexCoords*/,
				false/*Enable3DTexCoords*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
