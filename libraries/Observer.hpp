/*
 * Libraries/Observer.hpp
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
#include <set>

namespace Libraries
{
	/* Forward declaration */
	class Observable;

	/**
	 * @brief This class is the observer interface of the observer design pattern.
	 */
	class Observer
	{
		/* NOTE: This simplifies looped-back operations between Observable/Observer classes. */
		friend class Observable;

		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Observer (const Observer & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Observer (Observer && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return Observer &
			 */
			Observer & operator= (const Observer & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return Observer &
			 */
			Observer & operator= (Observer && copy) noexcept = delete;

			/**
			 * @brief Destructor.
			 * @note Takes cares of detach observables.
			 */
			virtual ~Observer ();

			/**
			 * @brief Says if something is currently observed.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isObserving () const noexcept final;

			/**
			 * @brief Returns whether a specific object is observed.
			 * @param observable The pointer of the observable.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isObserving (Observable * observable) const noexcept final;

			/**
			 * @brief Returns the list of observables.
			 * @return const std::set< Observable * > &
			 */
			[[nodiscard]]
			virtual const std::set< Observable * > & observables () const noexcept final;

			/**
			 * @brief Observes an observable.
			 * @param observable The pointer of the observable.
			 * @return void
			 */
			virtual void observe (Observable * observable) noexcept final;

			/**
			 * @brief Removes an observable.
			 * @param observable The pointer of the observable.
			 * @return void
			 */
			virtual void forget (Observable * observable) noexcept final;

		protected:

			/**
			 * @brief Constructs an observer.
			 */
			Observer () noexcept = default;

			/**
			 * @brief Consumes the event from the observable.
			 * @note Returning false will detach the observable.
			 * @param observable The observable responsible of the notification.
			 * @param notificationCode Code of notification.
			 * @param data Pointer to possible data.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool onNotification (const Observable * observable, int notificationCode, const std::any & data) noexcept = 0;

		private:

			std::set< Observable * > m_observables{};
	};
}
