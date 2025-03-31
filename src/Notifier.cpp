/*
 * src/Notifier.cpp
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

#include "Notifier.hpp"

/* Local inclusions. */
#include "Graphics/FontResource.hpp"
#include "Resources/Manager.hpp"
#include "Tracer.hpp"

namespace EmEn
{
	using namespace EmEn::Libs;
	using namespace EmEn::Libs::Math;
	using namespace EmEn::Libs::PixelFactory;

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
			Tracer::error(ClassId, "Unable to create a screen !");

			return false;
		}

		m_surface = m_screen->createSurface< Overlay::Surface >("Notifier", Math::Rectangle{0.0F, 0.9F, 1.0F, 0.1F}, 0.0F);

		if ( m_surface == nullptr )
		{
			Tracer::error(ClassId, "Unable to create a surface !");

			return false;
		}

		m_surface->pixmap().fill(Transparent);

		{
			//m_font = Resources::Manager::instance()->fonts().getResource("old", false);
			m_font = Resources::Manager::instance()->fonts().getDefaultResource();

			m_processor.setPixmap(m_surface->pixmap());
			m_processor.setFont(m_font->font(), 16U);
			m_processor.setFontColor(White);
		}

		return m_overlayManager.enableScreen("NotifierScreen");
	}

	bool
	Notifier::onTerminate () noexcept
	{
		this->destroyTimers();

		m_font.reset();

		m_screen.reset();
		m_surface.reset();

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
		m_surface->pixmap().fill(Transparent);

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

		m_surface->setVideoMemoryOutdated();
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
		if ( m_surface->pixmap().fill(Transparent) )
		{
			m_surface->setVideoMemoryOutdated();
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
