/*
 * Emeraude/Animations/AnimatableInterface.cpp
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

#include "AnimatableInterface.hpp"

/* Local inclusions */
#include "Tracer.hpp"

namespace Emeraude::Animations
{
	using namespace Libraries;

	bool
	AnimatableInterface::addAnimation (id_t animationID, const std::shared_ptr< AnimationInterface > & animation) noexcept
	{
		return m_animations.emplace(animationID, animation).second;
	}

	bool
	AnimatableInterface::removeAnimation (id_t animationID) noexcept
	{
		auto animationIt = m_animations.find(animationID);

		if ( animationIt != m_animations.end() )
		{
			m_animations.erase(animationIt);

			return true;
		}

		return false;
	}

	void
	AnimatableInterface::updateAnimations (size_t /* cycle */) noexcept
	{
		for ( auto & animationPair : m_animations )
		{
			auto & animation = *animationPair.second;

			if ( animation.isPaused() || animation.isFinished() )
			{
				continue;
			}

			auto value = animation.getNextValue();

			if ( value.isNull() )
			{
				continue;
			}

			if ( !this->playAnimation(animationPair.first, value) )
			{
				TraceError{"AnimatableInterface"} << "Unable to play animation " << animationPair.first << " !";
			}
		}
	}

	void
	AnimatableInterface::clearAnimations () noexcept
	{
		m_animations.clear();
	}
}
