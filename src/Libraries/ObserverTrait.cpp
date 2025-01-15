/*
 * src/Libraries/ObserverTrait.cpp
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

#include "ObserverTrait.hpp"

/* STL inclusions. */
#ifdef EMERAUDE_DEBUG_OBSERVER_PATTERN
#include <iostream>
#endif

/* Local inclusions. */
#include "Libraries/ObservableTrait.hpp"

namespace Libraries
{
	ObserverTrait::~ObserverTrait ()
	{
		/* NOTE: Only erase "this" observer to every attached observable.
		 * Do not use Observable::removeObserver(); */
		for ( auto * observable : m_observables )
		{
			observable->m_observers.erase(this);
		}
	}

	void
	ObserverTrait::observe (ObservableTrait * observable) noexcept
	{
		const auto result = m_observables.emplace(observable);

		if ( !result.second )
		{
#ifdef EMERAUDE_DEBUG_OBSERVER_PATTERN
			std::cout << "observe() : (@" << this << ") already observing ('" << observable->classUID() << "')." "\n";
#endif
			return;
		}

		observable->addObserver(this);
	}

	void
	ObserverTrait::forget (ObservableTrait * observable) noexcept
	{
		if ( m_observables.erase(observable) == 0 )
		{
#ifdef EMERAUDE_DEBUG_OBSERVER_PATTERN
			std::cout << "release() : (@" << this << ") wasn't observing ('" << observable->classUID() << "')." "\n";
#endif
			return;
		}

		observable->removeObserver(this);
	}
}
