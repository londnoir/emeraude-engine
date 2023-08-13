/*
 * Emeraude/Notifier.hpp
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

/* Local inclusions for inheritances. */
#include "ServiceInterface.hpp"
#include "Time/TimedEventsInterface.hpp"

/* Local inclusions for usages */
#include "Overlay/Elements/Text.hpp"

namespace Emeraude::Overlay
{
	class Manager;
}

namespace Emeraude
{
	class Settings;

	/**
	 * @brief The on-screen notifier service.
	 * @extends Emeraude::ServiceInterface This is a service.
	 * @extends Libraries::Time::TimedEventsInterface
	 */
	class Notifier final : public ServiceInterface, public Libraries::Time::TimedEventsInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"NotifierService"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs the notifier service.
			 * @param coreSettings A reference to the core settings.
			 * @param overlayManager A reference to the overlay manager.
			 */
			Notifier (Settings & coreSettings, Overlay::Manager & overlayManager) noexcept;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::ServiceInterface::usable() */
			[[nodiscard]]
			bool usable () const noexcept override;

			/**
			 * @brief Notifies a message.
			 * @param message A reference to a string.
			 * @param time The delay of the message staying on screen. Default 3 seconds.
			 * @return void
			 */
			void push (const std::string & message, double time = 3000.0) noexcept;

			/**
			 * @brief Notifies a message.
			 * @param message A reference to a blob.
			 * @param time The delay of the message staying on screen. Default 3 seconds.
			 * @return void
			 */
			inline
			void
			push (const Libraries::Blob & message, double time = 3000.0) noexcept
			{
				this->push(message.get(), time);
			}

			/**
			 * @brief Clears the notify display.
			 * @return void
			 */
			void clear () noexcept;

		private:

			/** @copydoc Emeraude::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc Emeraude::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

			/**
			 * @brief Delayed task to clear messages.
			 * @param milliseconds Sets the next time the task will occurs.
			 * @return void
			 */
			void clearTask (double milliseconds) noexcept;

			// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members) NOTE: Services inter-connexions.
			Settings & m_coreSettings;
			Overlay::Manager & m_overlayManager;
			// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members) NOTE: Services inter-connexions.
			std::shared_ptr< Overlay::Elements::Text > m_text{};
			Libraries::Time::TimerID m_autoClearTimerID{0};
	};
}
