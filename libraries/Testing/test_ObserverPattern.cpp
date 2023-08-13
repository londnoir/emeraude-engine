/*
 * Libraries/Testing/test_ObserverPattern.cpp
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

#include <gtest/gtest.h>

/* Local inclusions. */
#include "Observer.hpp"
#include "Observable.hpp"

using namespace Libraries;

class Noise final : public Observable
{
	public:

		Noise () = default;

		[[nodiscard]]
		bool
		is (size_t uniqueIdentifier) const noexcept
		{
			if ( s_identifier == 0 )
				return false;

			return s_identifier == uniqueIdentifier;
		}

		void
		doSomething () noexcept
		{
			this->notify(0);
		}

		[[nodiscard]]
		static
		size_t
		uniqueIdentifier () noexcept
		{
			return s_identifier;
		}

	private:

		static size_t s_identifier;
};

class Dummy final : public Observable
{
	public:

		Dummy () = default;

		[[nodiscard]]
		bool
		is (size_t uniqueIdentifier) const noexcept
		{
			if ( s_identifier == 0 )
				return false;

			return s_identifier == uniqueIdentifier;
		}

		void
		doSomething () noexcept
		{
			this->notify(0);
		}

		[[nodiscard]]
		static
		size_t
		uniqueIdentifier () noexcept
		{
			return s_identifier;
		}

	private:

		static size_t s_identifier;
};

size_t Noise::s_identifier{Observable::getClassUID()};
size_t Dummy::s_identifier{Observable::getClassUID()};

class Watcher final : public Observer
{
	public:

		Watcher () = default;

		[[nodiscard]]
		bool
		noiseEventIntercepted () const noexcept
		{
			return m_noiseEventIntercepted;
		}

		[[nodiscard]]
		bool
		dummyEventIntercepted () const noexcept
		{
			return m_dummyEventIntercepted;
		}

	private:

		bool
		onNotification (const Observable * observable, int notificationCode, const std::any & data) noexcept override
		{
			if ( observable->is(Noise::uniqueIdentifier()) )
			{
				m_noiseEventIntercepted = true;

				return true;
			}

			if ( observable->is(Dummy::uniqueIdentifier()) )
			{
				m_dummyEventIntercepted = true;

				return true;
			}

			return false;
		}

		bool m_noiseEventIntercepted{false};
		bool m_dummyEventIntercepted{false};
};

TEST(Observer, uniqueIdentifier)
{
	Noise noisyInstance{};

	Dummy instanceA{};

	const auto expectedDummyClassIdentifier = 2UL;

	EXPECT_EQ(instanceA.is(expectedDummyClassIdentifier), true);

	Dummy instanceB{};

	EXPECT_EQ(instanceB.is(expectedDummyClassIdentifier), true);
}

TEST(Observer, watch)
{
	Noise noisyInstance{};

	Watcher watcher{};

	Dummy instance{};

	watcher.observe(&instance);
	watcher.observe(&noisyInstance);

	EXPECT_EQ(watcher.noiseEventIntercepted(), false);
	EXPECT_EQ(watcher.dummyEventIntercepted(), false);

	instance.doSomething();

	EXPECT_EQ(watcher.noiseEventIntercepted(), false);
	EXPECT_EQ(watcher.dummyEventIntercepted(), true);

	noisyInstance.doSomething();

	EXPECT_EQ(watcher.noiseEventIntercepted(), true);
	EXPECT_EQ(watcher.dummyEventIntercepted(), true);
}
