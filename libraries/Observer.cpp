/*
 * Libraries/Observer.cpp
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

#include "Observer.hpp"

/* C/C++ standard libraries. */
#ifdef DEBUG_OBSERVER_PATTERN
#include <iostream>
#endif

/* Local inclusions. */
#include "Observable.hpp"

namespace Libraries
{
	Observer::~Observer ()
	{
		/* NOTE: Only erase "this" observer to every attached observable.
		 * Do not use Observable::removeObserver(); */
		for ( auto * observable : m_observables )
		{
			observable->m_observers.erase(this);
		}
	}

	bool
	Observer::isObserving () const noexcept
	{
		return !m_observables.empty();
	}

	bool
	Observer::isObserving (Observable * observable) const noexcept
	{
		return m_observables.find(observable) != m_observables.cend();
	}

	const std::set< Observable * > &
	Observer::observables () const noexcept
	{
		return m_observables;
	}

	void
	Observer::observe (Observable * observable) noexcept
	{
		auto result = m_observables.emplace(observable);

		if ( !result.second )
		{
#ifdef DEBUG_OBSERVER_PATTERN
			std::cout << "observe() : (@" << this << ") already observing (@" << observable << ")." << std::endl;
#endif
			return;
		}

		observable->addObserver(this);
	}

	void
	Observer::forget (Observable * observable) noexcept
	{
		if ( m_observables.erase(observable) == 0 )
		{
#ifdef DEBUG_OBSERVER_PATTERN
			std::cout << "release() : (@" << this << ") wasn't observing (@" << observable << ")." << std::endl;
#endif
			return;
		}

		observable->removeObserver(this);
	}
}
