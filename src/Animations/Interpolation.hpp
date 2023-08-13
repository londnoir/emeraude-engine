/*
 * Emeraude/Animations/Interpolation.hpp
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
#include <map>
#include <sstream>
#include <string>

/* Local inclusions for inheritances. */
#include "AnimationInterface.hpp"

/* Local inclusions for usages. */
#include "Constants.hpp"
#include "KeyFrame.hpp"

namespace Emeraude::Animations
{
	/**
	 * @brief This class describing the Interpolation of a state during a finite scale of time [0.0 -> 1.0].
	 * @extends Emeraude::Animations::AnimationInterface This is an animation.
	 */
	class Interpolation final : public AnimationInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"Interpolation"};

			/**
			 * @brief Constructs a default interpolation.
			 */
			Interpolation () noexcept = default;

			/** @copydoc Emeraude::Animations::AnimationInterface::getNextValue() */
			Libraries::Variant getNextValue () noexcept override;

			/** @copydoc Emeraude::Animations::AnimationInterface::isPlaying() */
			[[nodiscard]]
			bool isPlaying () const noexcept override;

			/** @copydoc Emeraude::Animations::AnimationInterface::isPaused() */
			[[nodiscard]]
			bool isPaused () const noexcept override;

			/** @copydoc Emeraude::Animations::AnimationInterface::isFinished() */
			[[nodiscard]]
			bool isFinished () const noexcept override;

			/** @copydoc Emeraude::Animations::AnimationInterface::play() */
			bool play () noexcept override;

			/** @copydoc Emeraude::Animations::AnimationInterface::pause() */
			bool pause () noexcept override;

			/**
			 * @brief Sets the number of time the animation should loop.
			 * @note -1 is an infinite loop.
			 * @param getNextValue ???
			 * @return void
			 */
			void setRepeatness (int getNextValue) noexcept;

			/**
			 * @brief Sets the animation duration in seconds.
			 * @param time The duration. 1.0 is 1 second.
			 * @return void
			 */
			void setDuration (float time) noexcept;

			/**
			 * @brief Sets the number of time the animation should be updated per second.
			 * @param time
			 * @return void
			 */
			void setDurationInHertz (unsigned int time) noexcept;

			/**
			 * @brief Sets noise parameter.
			 * @param noise
			 * @return void
			 */
			void setNoise (float noise) noexcept;

			/**
			 * @brief Adds a key frame.
			 * @param offset
			 * @param value
			 * @param interpolation
			 * @return void
			 */
			void addKeyFrame (float offset, const Libraries::Variant & value, Libraries::Math::InterpolationType interpolation = Libraries::Math::InterpolationType::Linear) noexcept;

			/**
			 * @brief Sets the current animation range time.
			 * @param time The current animation time between 0.0 and 1.0.
			 * @return void
			 */
			void setCurrentTime (float time) noexcept;

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const Interpolation & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend std::string to_string (const Interpolation & obj) noexcept;

		private:

			/**
			 * @brief Performs a linear interpolation.
			 * @param itStart
			 * @param itEnd
			 * @param factor
			 * @return Libraries::Variant
			 */
			static Libraries::Variant linearInterpolate (const KeyFrames::const_iterator & itStart, const KeyFrames::const_iterator & itEnd, float factor) noexcept;

			/**
			 * @brief Performs a cosine interpolation.
			 * @param itStart
			 * @param itEnd
			 * @param factor
			 * @return Libraries::Variant
			 */
			static Libraries::Variant cosineInterpolate (const KeyFrames::const_iterator & itStart, const KeyFrames::const_iterator & itEnd, float factor) noexcept;

			/**
			 * @brief Performs a cubic interpolation.
			 * @param itStart
			 * @param itEnd
			 * @param factor
			 * @return Libraries::Variant
			 */
			static Libraries::Variant cubeInterpolate (const KeyFrames::const_iterator & itStart, const KeyFrames::const_iterator & itEnd, float factor) noexcept;

			/* Flag names. */
			static constexpr auto IsPlaying = 0UL;

			KeyFrames m_keyFrames{};
			/* Position in the animation */
			float m_currentTime{0.0F};
			/* The value added to current time until it reaches 1.0.
			 * By default, an animation will be completed in 1 second. */
			float m_step{EngineUpdateCycleDuration< float >};
			int m_repeat{-1};
			float m_noise{0.0F};
			std::array< bool, 8 > m_flags{ // NOLINT(*-magic-numbers)
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
