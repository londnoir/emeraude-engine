/*
 * Libraries/Observable.cpp
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

#include "Observable.hpp"

/* C/C++ standard libraries. */
#ifdef DEBUG_OBSERVER_PATTERN
#include <iostream>
#endif

/* Local inclusions */
#include "Observer.hpp"

namespace Libraries
{
	// NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
	std::mutex Observable::s_UIDMutex{};
	size_t Observable::s_nextClassUID{1UL};
	// NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)

	Observable::~Observable ()
	{
		const std::lock_guard< std::mutex > lock {m_mutex};

		/* NOTE: Only erase "this" observable to every looking observer.
		 * Do not use Observer::release(); */
		for ( auto * observer : m_observers )
		{
			observer->m_observables.erase(this);
		}
	}

	bool
	Observable::isObserved () const noexcept
	{
		return !m_observers.empty();
	}

	bool
	Observable::isObserved (Observer * observer) const noexcept
	{
		return m_observers.find(observer) != m_observers.cend();
	}

	const std::set< Observer * > &
	Observable::observers () const noexcept
	{
		return m_observers;
	}

	void
	Observable::addObserver (Observer * observer) noexcept
	{
		auto result = m_observers.emplace(observer);

		if ( !result.second )
		{
#ifdef DEBUG_OBSERVER_PATTERN
			std::cout << "addObserver() @" << observer << " already observing @" << this << "." << std::endl;
#endif
			return;
		}
	}

	void
	Observable::removeObserver (Observer * observer) noexcept
	{
		if ( m_observers.erase(observer) == 0 )
		{
#ifdef DEBUG_OBSERVER_PATTERN
			std::cout << "removeObserver() : @" << observer << " wasn't observing @" << this << "." << std::endl;
#endif
			return;
		}
	}

	void
	Observable::notify (int notificationCode, const std::any & data) noexcept
	{
		const std::lock_guard< std::mutex > lock{m_mutex};

#ifdef DEBUG_OBSERVER_PATTERN
		if ( m_observers.size() == 0 )
		{
			std::cout << "Observable @" << this << " tries to notify the code '" << notificationCode << "', but no one was listening !" << std::endl;

			return;
		}
#endif

		/* [ERASE IN LOOP] */
		auto observerIt = m_observers.begin();

		while ( observerIt != m_observers.end() )
		{
			auto * observer = *observerIt;

			/* If onNotification() returns false, we automatically remove the observer. */
			if ( !observer->onNotification(this, notificationCode, data) )
			{
				observer->m_observables.erase(this);

				/* NOTE: set::erase() gives the next iterator. */
				observerIt = m_observers.erase(observerIt);
			}
			else
			{
				++observerIt;
			}
		}
	}

	void
	Observable::notify (int notificationCode) noexcept
	{
		this->notify(notificationCode, {});
	}

	size_t
	Observable::getClassUID () noexcept
	{
		const std::lock_guard< std::mutex > lock{s_UIDMutex};

		/* NOTE: Return the current identifier and increment for the next one. */
		return s_nextClassUID++;
	}
}
