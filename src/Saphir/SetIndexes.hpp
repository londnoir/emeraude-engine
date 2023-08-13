/*
 * Emeraude/Saphir/SetIndexes.hpp
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
#include <vector>
#include <cstdint>

namespace Emeraude::Saphir
{
	/** @brief The set type. */
	enum class SetType
	{
		/* Everything used by the whole frame. */
		PerView,
		/* Everything used by a whole model. */
		PerModel,
		/* Everything used by an object layer. */
		PerObjectLayer
	};

	/**
	 * @brief The set indexes class. This ensure the order of set when generating the GLSL source code.
	 * @note This should be only used in the shader generation. The Vulkan set order is known by the rendering code.
	 */
	class SetIndexes final
	{
		public:

			/**
			 * @brief Constructs a set indexes.
			 */
			SetIndexes () noexcept = default;

			/**
			 * @brief Enables a set type.
			 * @param setType The type of set.
			 * @return void
			 */
			void enableSet (SetType setType) noexcept;

			/**
			 * @brief Returns whether a set is enabled.
			 * @param setType The type of set.
			 * @return bool
			 */
			[[nodiscard]]
			bool isSetEnabled (SetType setType) const noexcept;

			/**
			 * @brief Returns the index of a set.
			 * @param descriptorSetType The type of set.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t set (SetType setType) const noexcept;

		private:

			std::vector< SetType > m_setTypes{};
	};
}
