/*
 * src/Notifier.hpp
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
#include <cstdint>
#include <memory>

/* Local inclusions for inheritances. */
#include "ServiceInterface.hpp"
#include "Libraries/Time/EventTrait.hpp"

/* Local inclusions for usages */
#include "Libraries/PixelFactory/TextProcessor.hpp"
#include "Overlay/Manager.hpp"
#include "Overlay/PixelBufferSurface.hpp"

namespace Emeraude
{
	/**
	 * @brief The on-screen notifier service.
	 * @extends Emeraude::ServiceInterface This is a service.
	 * @extends Libraries::ObserverTrait The notifier want to listen to overlay manager changes.
	 * @extends Libraries::Time::EventTrait The notifier use a timer to hide message.
	 */
	class Notifier final : public ServiceInterface, public Libraries::ObserverTrait, public Libraries::Time::EventTrait< uint32_t, std::milli >
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"NotifierService"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			static constexpr uint32_t DefaultDuration{3000};
			static constexpr auto ScreenName{"NotifierScreen"};

			/**
			 * @brief Constructs the notifier service.
			 * @param overlayManager A reference to the overlay manager.
			 */
			explicit Notifier (Overlay::Manager & overlayManager) noexcept;

			/** @copydoc Libraries::ObservableTrait::classUID() const */
			[[nodiscard]]
			size_t
			classUID () const noexcept override
			{
				return ClassUID;
			}

			/** @copydoc Libraries::ObservableTrait::is() const */
			[[nodiscard]]
			bool
			is (size_t classUID) const noexcept override
			{
				return classUID == ClassUID;
			}

			/** @copydoc Emeraude::ServiceInterface::usable() */
			[[nodiscard]]
			bool
			usable () const noexcept override
			{
				return m_pixelBuffer != nullptr;
			}

			/**
			 * @brief Notifies a message.
			 * @param message A reference to a string.
			 * @param duration The delay of the message staying on screen. Default 3 seconds.
			 * @return bool
			 */
			bool push (const std::string & message, uint32_t duration = DefaultDuration) noexcept;

			/**
			 * @brief Notifies a message.
			 * @param message A reference to a blob.
			 * @param duration The delay of the message staying on screen. Default 3 seconds.
			 * @return bool
			 */
			bool
			push (const Libraries::BlobTrait & message, uint32_t duration = DefaultDuration) noexcept
			{
				return this->push(message.get(), duration);
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

			/** @copydoc Libraries::ObserverTrait::onNotification() */
			[[nodiscard]]
			bool onNotification (const Libraries::ObservableTrait * observable, int notificationCode, const std::any & data) noexcept override;

			/**
			 * @brief Updates the notification area pixel buffer.
			 * @return void
			 */
			void displayNotifications () noexcept;

			Overlay::Manager & m_overlayManager;
			std::shared_ptr< Overlay::UIScreen > m_screen;
			std::shared_ptr< Overlay::PixelBufferSurface > m_pixelBuffer;
			Libraries::PixelFactory::TextProcessor< uint8_t > m_processor;
			std::vector< std::pair< std::string, Libraries::Time::TimerID > > m_notifications;
			mutable std::mutex m_lock;
	};
}
