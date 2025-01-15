/*
 * src/Animations/Sequence.hpp
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
#include <cstdint>
#include <array>
#include <map>
#include <string>

/* Local inclusions for inheritances. */
#include "AnimationInterface.hpp"

/* Local inclusions for usages. */
#include "KeyFrame.hpp"

namespace Emeraude::Animations
{
	/**
	 * @brief Define an animation sequence with key frames during a specific time measured in milliseconds.
	 * @extends Emeraude::Animations::AnimationInterface This is an animation.
	 */
	class Sequence final : public AnimationInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"Sequence"};

			/**
			 * @brief Constructs a sequence.
			 * @param duration The sequence duration in milliseconds.
			 * @param repeat The number of sequence repetition, -1 is infinite. Default infinite.
			 */
			explicit Sequence (uint32_t duration, int32_t repeat = -1) noexcept;

			/** @copydoc Emeraude::Animations::AnimationInterface::getNextValue() */
			Libraries::Variant getNextValue () noexcept override;

			/** @copydoc Emeraude::Animations::AnimationInterface::isPlaying() */
			[[nodiscard]]
			bool
			isPlaying () const noexcept override
			{
				return m_flags[IsPlaying];
			}

			/** @copydoc Emeraude::Animations::AnimationInterface::isPaused() */
			[[nodiscard]]
			bool
			isPaused () const noexcept override
			{
				return !m_flags[IsPlaying];
			}

			/** @copydoc Emeraude::Animations::AnimationInterface::isFinished() */
			[[nodiscard]]
			bool
			isFinished () const noexcept override
			{
				return m_repeat == 0 && m_elapsedTime >= m_duration;
			}

			/** @copydoc Emeraude::Animations::AnimationInterface::play() */
			bool play () noexcept override;

			/** @copydoc Emeraude::Animations::AnimationInterface::pause() */
			bool pause () noexcept override;

			/**
			 * @brief Sets noise parameter.
			 * @param noise A value noise to add to interpolation value.
			 * @return void
			 */
			void
			setNoise (float noise) noexcept
			{
				m_noise = noise;
			}

			/**
			* @brief Adds a key frame using a time code.
			* @note A key frame out of the timeline will be ignored.
			* @param timeCode A value in milliseconds.
			* @param value The value at this time point.
			* @param interpolation The type of interpolation. Default linear.
			* @return void
			*/
			void addKeyFrame (uint32_t timeCode, const Libraries::Variant & value, Libraries::Math::InterpolationType interpolation = Libraries::Math::InterpolationType::Linear) noexcept;

			/**
			 * @brief Adds a key frame with a position relative to the sequence.
			 * @param position A value between 0.0 to 1.0 to set a frame.
			 * @param value The value at this time point.
			 * @param interpolation The type of interpolation. Default linear.
			 * @return void
			 */
			void addKeyFrame (float position, const Libraries::Variant & value, Libraries::Math::InterpolationType interpolation = Libraries::Math::InterpolationType::Linear) noexcept;

			/**
			 * @brief Sets the current animation range time.
			 * @note A value out of the timeline will be ignored.
			 * @param timeCode A value in milliseconds.
			 * @return void
			 */
			void setCurrentTime (uint32_t timeCode) noexcept;

			/**
			 * @brief Sets the current animation range time.
			 * @param position The current animation time between 0.0 and 1.0.
			 * @return void
			 */
			void setCurrentTime (float position) noexcept;

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const Sequence & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend std::string to_string (const Sequence & obj) noexcept;

		private:

			/**
			 * @brief Advances the animation sequence time.
			 * @return void
			 */
			void advanceTime () noexcept;

			/**
			 * @brief Performs a linear interpolation.
			 * @param itStart A reference to the starting frame iterator.
			 * @param itEnd A reference to the ending frame iterator.
			 * @param factor The interpolation factor between the two frames.
			 * @return Libraries::Variant
			 */
			static Libraries::Variant getLinearInterpolation (const KeyFrames::const_iterator & itStart, const KeyFrames::const_iterator & itEnd, float factor) noexcept;

			/**
			 * @brief Performs a cosine interpolation.
			 * @param itStart A reference to the starting frame iterator.
			 * @param itEnd A reference to the ending frame iterator.
			 * @param factor The interpolation factor between the two frames.
			 * @return Libraries::Variant
			 */
			static Libraries::Variant getCosineInterpolation (const KeyFrames::const_iterator & itStart, const KeyFrames::const_iterator & itEnd, float factor) noexcept;

			/**
			 * @brief Performs a cubic interpolation.
			 * @param itStart A reference to the starting frame iterator.
			 * @param itEnd A reference to the ending frame iterator.
			 * @param factor The interpolation factor between the two frames.
			 * @return Libraries::Variant
			 */
			static Libraries::Variant getCubicInterpolation (const KeyFrames::const_iterator & itStart, const KeyFrames::const_iterator & itEnd, float factor) noexcept;

			/* Flag names. */
			static constexpr auto IsPlaying{0UL};

			uint32_t m_duration;
			int32_t m_repeat;
			uint32_t m_elapsedTime{0};
			float m_noise{0.0F};
			KeyFrames m_keyFrames;
			std::array< bool, 8 > m_flags{
				false/*IsPlaying*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
