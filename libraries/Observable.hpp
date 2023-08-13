/*
 * Libraries/Observable.hpp
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
#include <any>
#include <mutex>
#include <set>
#include <cstddef>

/* Local inclusions. */
#include "libraries_config.hpp"

namespace Libraries
{
	/* Forward declaration */
	class Observer;

	/**
	 * @brief This class is the observable interface of the observer design pattern.
	 */
	class Observable
	{
		/* NOTE: This simplifies looped-back operations between Observable/Observer classes. */
		friend class Observer;

		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Observable (const Observable & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Observable (Observable && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return Observable &
			 */
			Observable & operator= (const Observable & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return Observable &
			 */
			Observable & operator= (Observable && copy) noexcept = delete;

			/**
			 * @brief Destructs the observable object
			 * @note Takes cares of detaching observers.
			 */
			virtual ~Observable ();

			/**
			 * @brief Returns whether the object is currently observed.
			 * @return bool
			 */
			[[maybe_unused]]
			[[nodiscard]]
			virtual bool isObserved () const noexcept final;

			/**
			 * @brief Returns whether the object is observed by a specific observer.
			 * @param observer The pointer of the observer.
			 * @return bool
			 */
			[[maybe_unused]]
			[[nodiscard]]
			virtual bool isObserved (Observer * observer) const noexcept final;

			/**
			 * @brief Returns the list of observers.
			 * @return const std::set< Observer * > &
			 */
			[[maybe_unused]]
			[[nodiscard]]
			virtual const std::set< Observer * > & observers () const noexcept final;

			/**
			 * @brief Returns whether the observable unique identifier matches.
			 * @note The ID should be asked once per class with Observable::generateUniqueIdentifier() and stored as a static.
			 * @param classUID A number to identify a kind of class.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool is (size_t classUID) const noexcept = 0;

		protected:

			/**
			 * @brief Constructs an observable object.
			 */
			Observable () noexcept = default;

			/**
			 * @brief Sends a notification to every observers.
			 * @param notificationCode Code of notification.
			 * @return void
			 */
			virtual void notify (int notificationCode) noexcept final;

			/**
			 * @brief Sends a notification to every observers.
			 * @param notificationCode Code of notification.
			 * @param data Pointer to possible data.
			 * @return void
			 */
			virtual void notify (int notificationCode, const std::any & data) noexcept final;

			/**
			 * @brief Returns an unique identifier for observable. [Thread-safe]
			 * @return size_t
			 */
			[[nodiscard]]
			static size_t getClassUID () noexcept;

		private:

			/**
			 * @brief Adds an observer to this object.
			 * @param observer The pointer of the observer.
			 * @return void
			 */
			virtual void addObserver (Observer * observer) noexcept final;

			/**
			 * @brief Removes an observer from this object.
			 * @param observer The pointer of the observer.
			 * @return void
			 */
			virtual void removeObserver (Observer * observer) noexcept final;

			// NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
			static std::mutex s_UIDMutex;
			static size_t s_nextClassUID;
			// NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)

			std::set< Observer * > m_observers{};
			mutable std::mutex m_mutex{};
	};
}
