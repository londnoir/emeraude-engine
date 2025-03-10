/*
 * src/Animations/RandomValue.hpp
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

/* Local inclusions for inheritances. */
#include "AnimationInterface.hpp"

/* Local inclusions for usages. */
#include "Libraries/Variant.hpp"

namespace Emeraude::Animations
{
	/**
	 * @brief Animation using a simple random value.
	 * @note ie, This can be used to randomize something each logic cycle.
	 * @extends Emeraude::Animations::AnimationInterface This is an animation.
	 */
	class RandomValue final : public AnimationInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"RandomValue"};

			/**
			 * @brief Constructs a random value.
			 */
			RandomValue () noexcept = default;

			/**
			 * @brief Constructs a random value.
			 * @param minimum A reference to a minimum value.
			 * @param maximum A reference to a maximum value.
			 */
			RandomValue (const Libraries::Variant & minimum, const Libraries::Variant & maximum) noexcept;

			/** @copydoc Emeraude::Animations::AnimationInterface::getNextValue() */
			Libraries::Variant getNextValue () noexcept override;

			/** @copydoc Emeraude::Animations::AnimationInterface::isPlaying() */
			[[nodiscard]]
			bool
			isPlaying () const noexcept override
			{
				return true;
			}

			/** @copydoc Emeraude::Animations::AnimationInterface::isPaused() */
			[[nodiscard]]
			bool
			isPaused () const noexcept override
			{
				return false;
			}

			/** @copydoc Emeraude::Animations::AnimationInterface::isFinished() */
			[[nodiscard]]
			bool
			isFinished () const noexcept override
			{
				return false;
			}

			/** @copydoc Emeraude::Animations::AnimationInterface::play() */
			bool
			play () noexcept override
			{
				return true;
			}

			/** @copydoc Emeraude::Animations::AnimationInterface::pause() */
			bool
			pause () noexcept override
			{
				return false;
			}

			/**
			 * @brief Sets the new random value.
			 * @param minimum A reference to a minimum value.
			 * @param maximum A reference to a maximum value.
			 */
			void setValue (const Libraries::Variant & minimum, const Libraries::Variant & maximum) noexcept;

		private:

			Libraries::Variant m_minimumValue{};
			Libraries::Variant m_maximumValue{};
	};
}
