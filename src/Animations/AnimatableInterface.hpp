/*
 * src/Animations/AnimatableInterface.hpp
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
#include <cstddef>
#include <map>
#include <memory>

/* Local inclusions for usages. */
#include "Libraries/Variant.hpp"
#include "AnimationInterface.hpp"
#include "Types.hpp"

namespace Emeraude::Animations
{
	/**
	 * @brief The AnimatableInterface class
	 */
	class AnimatableInterface
	{
		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			AnimatableInterface (const AnimatableInterface & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			AnimatableInterface (AnimatableInterface && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return AnimatableInterface &
			 */
			AnimatableInterface & operator= (const AnimatableInterface & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return AnimatableInterface &
			 */
			AnimatableInterface & operator= (AnimatableInterface && copy) noexcept = default;

			/**
			 * @brief Destructs the animatable interface.
			 */
			virtual ~AnimatableInterface () = default;

			/**
			 * @brief Adds an animatable interfaced object where the animation is modified by an interpolation.
			 * @param animationID
			 * @param animation
			 * @return bool
			 */
			bool
			addAnimation (id_t animationID, const std::shared_ptr< AnimationInterface > & animation) noexcept
			{
				return m_animations.emplace(animationID, animation).second;
			}

			/**
			 * @brief Removes an animatable interfaced object.
			 * @param animationID The ID of the animation.
			 * @return bool
			 */
			bool
			removeAnimation (id_t animationID) noexcept
			{
				return m_animations.erase(animationID) > 0;
			}

			/**
			 * @brief This method is called within the logic loop to update every registered animation.
			 * @param cycle The current engine cycle.
			 * @return void
			 */
			void updateAnimations (size_t cycle) noexcept;

			/**
			 * @brief Clears every animation.
			 * @return void
			 */
			void
			clearAnimations () noexcept
			{
				m_animations.clear();
			}

		protected:

			/**
			 * @brief Constructs a default animatable interface.
			 */
			AnimatableInterface () noexcept = default;

		private:

			/**
			 * @brief Plays the identified animations.
			 * @param identifier The animation ID.
			 * @param value A reference to a variable.
			 * @return bool
			 */
			virtual bool playAnimation (id_t identifier, const Libraries::Variant & value) noexcept = 0;

			/* FIXME: Use std::any instead maybe, but it implies RTTI ! */
			std::map< id_t, std::shared_ptr< AnimationInterface > > m_animations;
	};
}
