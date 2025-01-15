/*
 * src/Audio/Filters/BandPass.hpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2024 - "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emeraude-Engine; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Complete project and additional information can be found at :
 * https://bitbucket.org/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#pragma once

/* STL inclusions. */
#include <memory>

/* Local inclusions for inheritances. */
#include "Abstract.hpp"

namespace Emeraude::Audio::Filters
{
	/**
	 * @brief The band pass filter.
	 * @extends Emeraude::Audio::Abstract This is a filter.
	 */
	class BandPass final : public Abstract
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"BandPass"};

			/**
			 * @brief Constructs a band pass filter.
			 */
			BandPass () noexcept;

			/** @copydoc Emeraude::Audio::Filters::Abstract::resetProperties() */
			void resetProperties () noexcept override;

			/**
			 * @brief Sets the gain.
			 * @param value A value between 0 and 1.
			 */
			void setGain (float value) noexcept;

			/**
			 * @brief Sets the gain at high frequency.
			 * @param value A value between 0 and 1.
			 */
			void setGainHF (float value) noexcept;

			/**
			 * @brief Sets the gain at low frequency.
			 * @param value A value between 0 and 1.
			 */
			void setGainLF (float value) noexcept;

			/**
			 * @brief Returns the gain value.
			 * @return float
			 */
			[[nodiscard]]
			float gain () const noexcept;

			/**
			 * @brief Returns the gain at high frequency value.
			 * @return float
			 */
			[[nodiscard]]
			float gainHF () const noexcept;

			/**
			 * @brief Returns the gain at low frequency value.
			 * @return float
			 */
			[[nodiscard]]
			float gainLF () const noexcept;
	};
}
