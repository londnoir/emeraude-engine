/*
 * Emeraude/Audio/Effects/Distortion.hpp
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
	 * @brief Distortion effect.
	 * @extends Emeraude::Audio::Effects::Abstract This is an effect.
	 */
	class Distortion final : public Abstract
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"Distortion"};

			/**
			 * @brief Constructs a distortion effect.
			 */
			Distortion () noexcept;

			/** @copydoc Emeraude::Audio::Effects::Abstract::resetProperties() */
			void resetProperties () noexcept override;

			/**
			 * @brief Sets the edge.
			 * @param value A value between 0 and 1.
			 */
			void setEdge (float value) noexcept;

			/**
			 * @brief Sets the gain.
			 * @param value A value between 0.01 and 1.
			 */
			void setGain (float value) noexcept;

			/**
			 * @brief Sets the low pass cut-off.
			 * @param value A value between 80 and 24000.
			 */
			void setLowPassCutOff (float value) noexcept;

			/**
			 * @brief Sets the equalizer center.
			 * @param value A value between 80 and 24000.
			 */
			void setEQCenter (float value) noexcept;

			/**
			 * @brief Sets the equalizer bandwidth.
			 * @param value A value between 80 and 24000.
			 */
			void setEQBandWidth (float value) noexcept;

			/**
			 * @brief Returns the edge value.
			 * @return float
			 */
			[[nodiscard]]
			float edge () const noexcept;

			/**
			 * @brief Returns the gain value.
			 * @return float
			 */
			[[nodiscard]]
			float gain () const noexcept;

			/**
			 * @brief Returns the low pass cut-off value.
			 * @return float
			 */
			[[nodiscard]]
			float lowPassCutOff () const noexcept;

			/**
			 * @brief Returns the equalizer center value.
			 * @return float
			 */
			[[nodiscard]]
			float EQCenter () const noexcept;

			/**
			 * @brief Returns the equalizer bandwidth value.
			 * @return float
			 */
			[[nodiscard]]
			float EQBandWidth () const noexcept;
	};
}
