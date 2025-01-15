/*
 * src/Notifier.cpp
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

#include "Notifier.hpp"

/* STL inclusions. */

/* Local inclusions. */
#include "Resources/Manager.hpp"
#include "Tracer.hpp"

namespace Emeraude
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Libraries::PixelFactory;

	const size_t Notifier::ClassUID{getClassUID(ClassId)};

	Notifier::Notifier (Overlay::Manager & overlayManager) noexcept
		: ServiceInterface(ClassId), m_overlayManager(overlayManager)
	{

	}

	bool
	Notifier::onInitialize () noexcept
	{
		if ( !m_overlayManager.usable() )
		{
			Tracer::error(ClassId, "The overlay manager is not usable to build the notifier !");

			return false;
		}

		this->observe(&m_overlayManager);

		m_screen = m_overlayManager.createScreen(ScreenName, false, false);

		if ( m_screen == nullptr )
		{
			Tracer::error(ClassId, "Unable to get a screen to display the notifier !");

			return false;
		}

		m_pixelBuffer = m_screen->createSurface< Overlay::PixelBufferSurface >("Notifier", Math::Rectangle{0.0F, 0.9F, 1.0F, 0.1F}, 0.0F);
		m_pixelBuffer->pixmap().fill(Transparent);

		m_processor.setPixmap(m_pixelBuffer->pixmap());

		//auto font = Resources::Manager::instance()->fonts().getResource("old");

		const auto filepath = FileSystem::instance()->getFilepathFromDataDirectories("data-stores/Fonts", "Joystick.ttf");
		const auto font = std::make_shared< Font< uint8_t > >();

		if ( font->readFile(filepath, 24) )
		{
			m_processor.setFont(font);
			m_processor.setFontColor(White);
		}

		return m_overlayManager.enableScreen("NotifierScreen");
	}

	bool
	Notifier::onTerminate () noexcept
	{
		this->destroyTimers();

		m_screen.reset();
		m_pixelBuffer.reset();

		return true;
	}

	bool
	Notifier::push (const std::string & message, uint32_t duration) noexcept
	{
		if ( !this->usable() )
		{
			return false;
		}

		m_notifications.emplace_back(message, this->createTimer(
			[&] (Time::TimerID timerID){
				{
					const std::lock_guard< std::mutex > lock(m_lock);

					for ( auto notificationIt = m_notifications.begin(); notificationIt != m_notifications.cend(); ++notificationIt )
					{
						if ( notificationIt->second == timerID )
						{
							m_notifications.erase(notificationIt);

							break;
						}
					}
				}

				this->displayNotifications();

				return true;
			},
			duration,
			true, /* Only once. */
			true /* Start directly. */
		));

		this->displayNotifications();

		return true;
	}

	void
	Notifier::displayNotifications () noexcept
	{
		m_pixelBuffer->pixmap().fill(Transparent);

		if ( !m_notifications.empty() )
		{
			std::stringstream buffer;

			{
				const std::lock_guard< std::mutex > lock(m_lock);

				for ( auto rIt = m_notifications.crbegin(); rIt != m_notifications.crend(); ++rIt )
				{
					buffer << rIt->first << '\n';
				}
			}

			if ( !m_processor.write(buffer.str()) )
			{
				return;
			}
		}

		m_pixelBuffer->requestVideoMemoryUpdate();
	}

	void
	Notifier::clear () noexcept
	{
		/* NOTE: Removes all notifications. */
		{
			const std::lock_guard< std::mutex > lock(m_lock);

			this->destroyTimers();

			m_notifications.clear();
		}

		/* NOTE: Clean up the screen. */
		if ( m_pixelBuffer->pixmap().fill(Transparent) )
		{
			m_pixelBuffer->requestVideoMemoryUpdate();
		}
	}

	bool
	Notifier::onNotification (const ObservableTrait * observable, int notificationCode, const std::any & /*data*/) noexcept
	{
		if ( observable->is(Overlay::Manager::ClassUID) )
		{
			if ( notificationCode == Overlay::Manager::OverlayResized )
			{
				this->displayNotifications();
			}

			return true;
		}

		return false;
	}
}
