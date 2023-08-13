/*
 * Emeraude/Audio/AmbienceChannel.hpp
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
#include <memory>

/* Local inclusions. */
#include "Source.hpp"
#include "AmbienceSound.hpp"

namespace Emeraude::Audio
{
	/**
	 * @brief The ambience channel class.
	 */
	class AmbienceChannel final
	{
		public:

			/**
			 * @brief Constructs an ambience channel.
			 * @param source A reference to an audio source smart pointer.
			 */
			explicit AmbienceChannel (const std::shared_ptr< Source > & source) noexcept;

			/**
			 * @brief Gets the channel source.
			 * @return std::shared_ptr< Source >
			 */
			[[nodiscard]]
			std::shared_ptr< Source > getSource () const noexcept;

			/**
			 * @brief Sets time before the next sound play from this channel.
			 * @note This will reset the current time to 0.
			 * @param time The delay in milliseconds.
			 * @return void
			 */
			void setTimeBeforeNextPlay (unsigned int time) noexcept;

			/**
			 * @brief Initializes the channel to play an ambience sound.
			 * @param sound A reference to an ambience sound.
			 * @param radius The radius of playing.
			 * @return unsigned int
			 */
			[[nodiscard]]
			unsigned int play (const AmbienceSound & sound, float radius) noexcept;

			/**
			 * @brief Updates the current time.
			 * @param time The new current time in milliseconds.
			 * @return void
			 */
			void update (unsigned int time) noexcept;

			/**
			 * @brief Returns whether is time to play the channel or not.
			 * @return bool
			 */
			[[nodiscard]]
			bool isTimeToPlay () const noexcept;

			/**
			 * @brief Sets the position.
			 * @param position A reference to a vector.
			 * @return void
			 */
			void setPosition (const Libraries::Math::Vector< 3, float > & position) noexcept;

			/**
			 * @brief Sets a velocity vector to fake a movement.
			 * @param velocity A reference to a vector.
			 * @return void
			 */
			void setVelocity (const Libraries::Math::Vector< 3, float > & velocity) noexcept;

			/**
			 * @brief Disable the channel velocity.
			 * @return void
			 */
			void disableVelocity () noexcept;

		private:

			std::shared_ptr< Source > m_source{};
			unsigned int m_timeBeforeNextPlay = 0U;
			unsigned int m_time = 0U;
			Libraries::Math::Vector< 3, float > m_position{};
			Libraries::Math::Vector< 3, float > m_velocity{};
	};
}
