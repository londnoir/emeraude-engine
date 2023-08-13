/*
 * Emeraude/Graphics/RenderableInstance/RenderingOptions.hpp
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
#include <array>

/* Local inclusions for usages. */
#include "Graphics/Types.hpp"

namespace Emeraude::Graphics::RenderableInstance
{
	/**
	 * @brief Defines options to render the instance.
	 * @note These options are dynamic to gain control over the rendering of multiple instance of the same renderable object.
	 */
	class RenderingOptions final
	{
		public:

			/**
			 * @brief Constructs Class.
			 */
			RenderingOptions () noexcept = default;

			/**
			 * @brief Sets how triangles will be rasterized on screen.
			 * @note This affect only triangle primitive.
			 * @param mode Mode of drawing the triangles.
			 */
			void setPolygonMode (PolygonMode mode) noexcept;

			/**
			 * @brief Returns how triangles will be rasterized on screen.
			 * @return PolygonMode
			 */
			[[nodiscard]]
			PolygonMode polygonMode () const noexcept;

		private:

			PolygonMode m_polygonMode = PolygonMode::Fill;
			CullingMode m_cullingMode = CullingMode::Back;
			float m_polygonOffsetFactor = 0.0F;
			float m_polygonOffsetUnits = 0.0F;
			std::array< bool, 8 > m_flags {
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
