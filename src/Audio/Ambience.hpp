/*
 * Emeraude/Audio/Ambience.hpp
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
#include <string>
#include <vector>

/* Local inclusions for usages. */
#include "Path/File.hpp"
#include "AmbienceChannel.hpp"
#include "AmbienceSound.hpp"

namespace Emeraude::Audio
{
	/**
	 * @brief The Ambience class
	 */
	class Ambience final
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"Ambience"};

			/**
			 * @brief Constructs an ambience.
			 */
			Ambience () noexcept = default;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Ambience (const Ambience & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Ambience (Ambience && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			Ambience & operator= (const Ambience & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			Ambience & operator= (Ambience && copy) noexcept = default;

			/**
			 * @brief Destructs the ambience.
			 */
			~Ambience ();

			/**
			 * @brief Returns whether the ambience sound set is playing.
			 * @return bool
			 */
			[[nodiscard]]
			bool isPlaying () const noexcept;

			/**
			 * @brief Sets the number of sound that can be played simultaneously.
			 * @param count The number of channel.
			 * @return void
			 */
			void setChannelCount (size_t count) noexcept;

			/**
			 * @brief Returns the number of sound that can be played simultaneously.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t channelCount () const noexcept;

			/**
			 * @brief Sets a distance around the listener where sound will be played randomly.
			 * @param radius A value in engine metric units.
			 * @return void
			 */
			void setRadius (float radius) noexcept;

			/**
			 * @brief Returns the distance around the listener where sound will be played randomly.
			 * @return float
			 */
			[[nodiscard]]
			float radius () const noexcept;

			/**
			 * @brief Sets a random delay range.
			 * @param delayA A delay in milliseconds.
			 * @param delayB Another delay.
			 * @return void
			 */
			void setRandomDelayRange (unsigned int delayA, unsigned int delayB) noexcept;

			/**
			 * @brief Sets the loop sound effect.
			 * @param soundResource A reference to a sound resource smart pointer.
			 * @param gain The loop channel gain. Default 0.75F.
			 * @return bool
			 */
			bool setLoopSound (const std::shared_ptr< SoundResource > & soundResource, float gain = 0.75F) noexcept;

			/**
			 * @brief Adds a sound effect to the ambience list.
			 * @param sound A reference to a sound effect.
			 * @return bool
			 */
			bool addSound (const AmbienceSound & sound) noexcept;

			/**
			 * @brief Adds a sound effect to the ambience list.
			 * @param sound A reference to a sound resource smart pointer.
			 * @param channelGain The channel gain. Default 0.75.
			 * @param relative The relative state of the channel to the listener. Default true.
			 * @param minPitch The minimum pitch value. Default 1.0.
			 * @param maxPitch The maximum pitch value. Default 1.0.
			 * @param velocity The radial velocity value. Default 0.0.
			 * @return bool
			 */
			bool addSound (const std::shared_ptr< SoundResource > & sound, float channelGain = 0.75F,  bool relative = true, float minPitch = 1.0F, float maxPitch = 1.0F, float velocity = 0.0F) noexcept;

			/**
			 * @brief Enables a direct filter.
			 * @warning This method only works with the EFX extension.
			 * @param filter A reference to a filter smart pointer.
			 * @return bool
			 */
			bool enableDirectFilter (const std::shared_ptr< Filters::Abstract > & filter) noexcept;

			/**
			 * @brief Disables the direct filter.
			 * @warning This method only works with the EFX extension.
			 * @return void
			 */
			void disableDirectFilter () noexcept;

			/**
			 * @brief Starts the ambience.
			 * @return void
			 */
			void start () noexcept;

			/**
			 * @brief Stops all sound from the ambience.
			 * @return void
			 */
			void stop () noexcept;

			/**
			 * @brief Updates the logics.
			 * @return void
			 */
			void update () noexcept;

			/**
			 * @brief Loads a sound set from a JSON file.
			 * @param filepath The path to the file.
			 * @return bool
			 */
			bool loadSoundSet (const Libraries::Path::File & filepath) noexcept;

			/**
			 * @brief Reset the current sound set.
			 * @return void
			 */
			void reset () noexcept;

		private:

			/**
			 * @brief Returns a random delay.
			 * @return unsigned int
			 */
			[[nodiscard]]
			unsigned int getRandomDelay () const noexcept;

			/**
			 * @brief Allocates all sources.
			 * @return bool
			 */
			bool allocateSources () noexcept;

			/**
			 * @brief Releases all sources.
			 * @return void
			 */
			void releaseSources () noexcept;

			/**
			 * @brief Picks a random sound from the ambience list.
			 * @return AmbienceSound &
			 */
			[[nodiscard]]
			AmbienceSound & getRandomSound () noexcept;

			/* JSON key. */
			static constexpr auto JKLoopSoundEffect = "LoopSoundEffect";
			static constexpr auto JKSoundEffectCollection = "SoundEffectCollection";
			static constexpr auto JKChannelCount = "ChannelCount";
			static constexpr auto JKRadius = "Radius";
			static constexpr auto JKResourceName = "ResourceName";
			static constexpr auto JKGain = "Gain";
			static constexpr auto JKRelative = "Relative";
			static constexpr auto JKMinimumPitch = "MinimumPitch";
			static constexpr auto JKMaximumPitch = "MaximumPitch";
			static constexpr auto JKRadialVelocity = "RadialVelocity";

			std::vector< AmbienceChannel > m_channels{};
			std::vector< AmbienceSound > m_sounds{};
			std::shared_ptr< Source > m_loopedSource{};
			std::shared_ptr< SoundResource > m_loopedSoundResource{};
			std::shared_ptr< Filters::Abstract > m_directFilter{};
			float m_loopedChannelGain{0.75F};
			size_t m_channelCount{4UL};
			float m_radius{1024.0F};
			unsigned int m_minDelay{500};
			unsigned int m_maxDelay{3000};
			bool m_active{false};
	};
}
