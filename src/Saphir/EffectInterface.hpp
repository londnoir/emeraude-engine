/*
 * Emeraude/Saphir/EffectInterface.hpp
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
#include <set>
#include <memory>

namespace Emeraude::Saphir
{
	/* Forward declarations. */
	class ShaderGenerator;

	/**
	 * @brief The effect interface.
	 */
	class EffectInterface
	{
		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			EffectInterface (const EffectInterface & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			EffectInterface (EffectInterface && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return EffectInterface &
			 */
			EffectInterface & operator= (const EffectInterface & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return EffectInterface &
			 */
			EffectInterface & operator= (EffectInterface && copy) noexcept = default;

			/**
			 * @brief Destructs the effect interface.
			 */
			virtual ~EffectInterface () = default;

			/**
			 * @brief Generates the source code for this effect.
			 * @param generator A reference to shader generator.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool generate (ShaderGenerator & generator) const noexcept = 0;

		protected:

			/**
			 * @brief Construct an effect interface.
			 */
			EffectInterface () noexcept = default;
	};

	using EffectsList = std::set< std::shared_ptr< EffectInterface > >;
}
