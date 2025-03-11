/*
 * src/Notifier.hpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2025 - Sébastien Léon Claude Christian Bémelmans "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Emeraude-Engine; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Complete project and additional information can be found at :
 * https://github.com/londnoir/emeraude-engine
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
#include "Libs/Time/EventTrait.hpp"

/* Local inclusions for usages */
#include "Libs/PixelFactory/TextProcessor.hpp"
#include "Overlay/Manager.hpp"
#include "Overlay/PixelBufferSurface.hpp"

namespace EmEn
{
	/**
	 * @brief The on-screen notifier service.
	 * @extends EmEn::ServiceInterface This is a service.
	 * @extends EmEn::Libs::ObserverTrait The notifier want to listen to overlay manager changes.
	 * @extends EmEn::Libs::Time::EventTrait The notifier use a timer to hide message.
	 */
	class Notifier final : public ServiceInterface, public Libs::ObserverTrait, public Libs::Time::EventTrait< uint32_t, std::milli >
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

			/** @copydoc EmEn::Libs::ObservableTrait::classUID() const */
			[[nodiscard]]
			size_t
			classUID () const noexcept override
			{
				return ClassUID;
			}

			/** @copydoc EmEn::Libs::ObservableTrait::is() const */
			[[nodiscard]]
			bool
			is (size_t classUID) const noexcept override
			{
				return classUID == ClassUID;
			}

			/** @copydoc EmEn::ServiceInterface::usable() */
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
			push (const Libs::BlobTrait & message, uint32_t duration = DefaultDuration) noexcept
			{
				return this->push(message.get(), duration);
			}

			/**
			 * @brief Clears the notify display.
			 * @return void
			 */
			void clear () noexcept;

		private:

			/** @copydoc EmEn::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc EmEn::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

			/** @copydoc EmEn::Libs::ObserverTrait::onNotification() */
			[[nodiscard]]
			bool onNotification (const Libs::ObservableTrait * observable, int notificationCode, const std::any & data) noexcept override;

			/**
			 * @brief Updates the notification area pixel buffer.
			 * @return void
			 */
			void displayNotifications () noexcept;

			Overlay::Manager & m_overlayManager;
			std::shared_ptr< Overlay::UIScreen > m_screen;
			std::shared_ptr< Overlay::PixelBufferSurface > m_pixelBuffer;
			Libs::PixelFactory::TextProcessor< uint8_t > m_processor;
			std::vector< std::pair< std::string, Libs::Time::TimerID > > m_notifications;
			mutable std::mutex m_lock;
	};
}
