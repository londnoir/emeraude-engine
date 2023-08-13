/*
 * Emeraude/Audio/Effects/Compressor.hpp
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

/* Local inclusions for ineritances. */
#include "Abstract.hpp"

namespace Emeraude::Audio::Effects
{
	/**
	 * @brief Compressor effect.
	 * @extends Emeraude::Audio::Effects::Abstract This is an effect.
	 */
	class Compressor final : public Abstract
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"Compressor"};

			/**
			 * @brief Constructs a compressor effect.
			 */
			Compressor () noexcept;

			/** @copydoc Emeraude::Audio::Effects::Abstract::resetProperties() */
			void resetProperties () noexcept override;

			/**
			 * @brief Enables or disable the compressor effect.
			 * @param state The state.
			 */
			void enable (bool state) noexcept;

			/**
			 * @brief Returns whether the effect is enabled.
			 * @return bool
			 */
			[[nodiscard]]
			bool isEnabled () const noexcept;
	};
}
