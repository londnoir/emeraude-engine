/*
 * src/Audio/Effects/Compressor.hpp
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

/* Local inclusions for ineritances. */
#include "Abstract.hpp"

namespace EmEn::Audio::Effects
{
	/**
	 * @brief Compressor effect.
	 * @extends EmEn::Audio::Effects::Abstract This is an effect.
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

			/** @copydoc EmEn::Audio::Effects::Abstract::resetProperties() */
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
