/*
 * Libraries/VertexFactory/TreeGenerator.hpp
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

/* Local inclusions for usages. */
#include "ShapeAssembler.hpp"

namespace Libraries::VertexFactory
{
	/**
	 * @brief The TreeGenerator class
	 */
	class [[maybe_unused]] TreeGenerator final
	{
		public:

			/**
			 * @brief Constructs a default tree generator.
			 */
			TreeGenerator () noexcept = default;

			/**
			 * @brief Returns the base size.
			 * @return float
			 */
			[[nodiscard]]
			float baseSize () const noexcept;

			/**
			 * @brief Sets the base size of generation.
			 * @param baseSize The radius of the trunk.
			 * @return void
			 */
			void setBaseSize (float baseSize) noexcept;

			/**
			 * @brief Returns the base size of generation.
			 * @return float
			 */
			[[nodiscard]]
			float baseHeight () const noexcept;

			/**
			 * @brief Sets the base height of generation.
			 * @param baseHeight The height of the trunk.
			 * @return void
			 */
			void setBaseHeight (float baseHeight) noexcept;

			/**
			 * @brief reduceFactor
			 * @return float
			 */
			[[nodiscard]]
			float reduceFactor () const noexcept;

			/**
			 * @brief setReduceFactor
			 * @param reduceFactor
			 * @return void
			 */
			void setReduceFactor (float reduceFactor) noexcept;

			/**
			 * @brief maxSpreadingAngle
			 * @return float
			 */
			[[nodiscard]]
			float maxSpreadingAngle () const noexcept;

			/**
			 * @brief setMaxSpreadingAngle
			 * @param maxSpreadingAngle
			 * @return void
			 */
			void setMaxSpreadingAngle (float maxSpreadingAngle) noexcept;

			/**
			 * @brief chaos
			 * @return float
			 */
			[[nodiscard]]
			float chaos () const noexcept;

			/**
			 * @brief setChaos
			 * @param chaos
			 * @return void
			 */
			void setChaos (float chaos) noexcept;

			/**
			 * @brief depth
			 * @return size_t
			 */
			[[nodiscard]]
			size_t depth () const noexcept;

			/**
			 * @brief setDepth
			 * @param depth
			 * @return void
			 */
			void setDepth (size_t depth) noexcept;

			/**
			 * @brief Executes the generation of the tree as a shape.
			 * @param seed The generation seed. Default 0.
			 * @return Shape< float >
			 */
			[[nodiscard]]
			Shape< float > generate (size_t seed = 0) noexcept;

		private:

			/**
			 * @brief generateBranch
			 * @param assembler
			 * @param size
			 * @param height
			 * @param origin
			 * @param currentDepth
			 * @param generateSubBranches
			 * @return void
			 */
			void generateBranch (ShapeAssembler< float > & assembler, float size, float height, const Math::Coordinates< float > & origin, size_t currentDepth, bool generateSubBranches) noexcept;

			// NOLINTBEGIN(*-magic-numbers)
			float m_baseSize{1.0F};
			float m_baseHeight{4.0F};
			float m_reduceFactor{0.75F};
			float m_maxSpreadingAngle{15.0F};
			float m_chaos{0.1F};
			size_t m_depth{3};
			// NOLINTEND(*-magic-numbers)
		};
}
