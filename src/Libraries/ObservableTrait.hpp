/*
 * src/Libraries/ObservableTrait.hpp
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
#include <any>
#include <cstddef>
#include <iostream>
#include <map>
#include <mutex>
#include <set>
#include <string>
#ifdef EMERAUDE_DEBUG_OBSERVER_PATTERN
#include <iostream>
#endif
#ifdef DEBUG
#include <memory>
#endif

/* Forward declarations. */
namespace Libraries
{
	class ObserverTrait;
}

namespace Libraries
{
	/**
	 * @brief This class is the observable interface of the observer design pattern.
	 */
	class ObservableTrait
	{
		/* NOTE: This simplifies looped-back operations between Observable/Observer classes. */
		friend class ObserverTrait;

		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			ObservableTrait (const ObservableTrait & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			ObservableTrait (ObservableTrait && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return ObservableTrait &
			 */
			ObservableTrait & operator= (const ObservableTrait & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return Observable &
			 */
			ObservableTrait & operator= (ObservableTrait && copy) noexcept = delete;

			/**
			 * @brief Destructs the observable.
			 * @note Takes cares of detaching observers.
			 */
			virtual ~ObservableTrait ();

			/**
			 * @brief Returns whether the object is currently observed.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isObserved () const noexcept
			{
				return !m_observers.empty();
			}

			/**
			 * @brief Returns whether the object is observed by a specific observer.
			 * @param observer The pointer of the observer.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isObserved (ObserverTrait * observer) const noexcept
			{
#if __cplusplus >= 202002L /* C++20 feature */
				return m_observers.contains(observer);
#else
				return m_observers.find(observer) != m_observers.cend();
#endif
			}

			/**
			 * @brief Returns the list of observers.
			 * @return const std::set< Observer * > &
			 */
			[[nodiscard]]
			const std::set< ObserverTrait * > &
			observers () const noexcept
			{
				return m_observers;
			}

			/**
			 * @brief Returns the observable unique identifier set by Observable::getClassUID().
			 * @return size_t
			 */
			[[nodiscard]]
			virtual size_t classUID () const noexcept = 0;

			/**
			 * @brief Returns whether the observable unique identifier matches.
			 * @note The ID should be asked once per class with Observable::getClassUID() and stored as a static.
			 * @param classUID A number to identify a kind of class.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool is (size_t classUID) const noexcept = 0;


			/**
			 * @brief Returns the label registered when generation the UID to use to debug the Observer::onNotification().
			 * @note This debugging method will return :
			 *  - "DEBUG_FEATURE" if the binary is in release mode.
			 *  - "UNALLOCATED_MAP" if the function is called before any observable creation.
			 *  - "UNREGISTERED_ITEM" if the UID doesn't exist.
			 * @param UID An observable UID.
			 * @return const char *
			 */
#ifdef NDEBUG
			[[deprecated("This method is useless in release mode ! Surround the call with DEBUG macro.")]]
#endif
			[[nodiscard]]
			static
			const char *
			whoIs (size_t UID) noexcept
			{
#ifdef DEBUG
				if ( s_classUIDs == nullptr )
				{
					return "UNALLOCATED_MAP";
				}

				const auto item = s_classUIDs->find(UID);

				if ( item != s_classUIDs->cend() )
				{
					return item->second;
				}

				return "UNREGISTERED_ITEM";
#else
				return "DEBUG_FEATURE";
#endif
			}

		protected:

			/**
			 * @brief Constructs an observable object.
			 */
			ObservableTrait () noexcept = default;

			/**
			 * @brief Sends a notification to every observer.
			 * @param notificationCode Code of notification.
			 * @param data A reference to any. Default no data.
			 * @return void
			 */
			void notify (int notificationCode, const std::any & data = {}) noexcept;

			/**
			 * @brief Returns a unique identifier for observable and register a label with it [Thread-safe].
			 * @param label A pointer to a C-string.
			 * @return size_t
			 */
			[[nodiscard]]
			static
			size_t
			getClassUID (const char * label) noexcept
			{
				/* NOTE: Lock the call to this function to be sure having a unique class identifier. */
				const std::lock_guard< std::mutex > lock{s_UIDMutex};

#ifdef DEBUG
				const auto UID = s_nextClassUID++;

				if ( s_classUIDs == nullptr )
				{
					s_classUIDs = std::make_unique< std::map< size_t, const char * > >();

					/* NOTE: As a special engine debug feature, we register the
					 * release of memory allocation at application exit. */
					atexit([] () {
				        s_classUIDs.reset();
					});
				}

#ifdef EMERAUDE_DEBUG_OBSERVER_PATTERN
				std::cout << "Linking UID: " << UID << " to item '" << label << "'" "\n";
#endif

				s_classUIDs->emplace(UID, label);

				return UID;
#else
				return s_nextClassUID++;
#endif
			}

		private:

			/**
			 * @brief Adds an observer to this object.
			 * @param observer The pointer of the observer.
			 * @return void
			 */
			void
			addObserver (ObserverTrait * observer) noexcept
			{
				m_observers.emplace(observer);
			}

			/**
			 * @brief Removes an observer from this object.
			 * @param observer The pointer of the observer.
			 * @return void
			 */
			void
			removeObserver (ObserverTrait * observer) noexcept
			{
				m_observers.erase(observer);
			}

			static std::mutex s_UIDMutex;
			static size_t s_nextClassUID;
#ifdef DEBUG
			static std::unique_ptr< std::map< size_t, const char * > > s_classUIDs;
#endif

			std::set< ObserverTrait * > m_observers;
			mutable std::mutex m_notificationMutex;
	};
}
