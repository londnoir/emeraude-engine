/*
 * Emeraude/Notifier.cpp
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

#include "Notifier.hpp"

/* Local inclusions */
#include "Graphics/Geometry/IndexedVertexResource.hpp"
#include "Overlay/Manager.hpp"
#include "Overlay/Screen.hpp"
#include "Settings.hpp"
#include "Tracer.hpp"

namespace Emeraude
{
	using namespace Libraries;

	const size_t Notifier::ClassUID{Observable::getClassUID()};

	Notifier::Notifier (Settings & coreSettings, Overlay::Manager & overlayManager) noexcept
		: ServiceInterface(ClassId), m_coreSettings(coreSettings), m_overlayManager(overlayManager)
	{

	}

	bool
	Notifier::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	Notifier::onInitialize () noexcept
	{
		if ( !m_overlayManager.usable() )
		{
			Tracer::error(ClassId, "Unable to create the notifier interface. Overlay manager is not usable !");

			return false;
		}

		const std::string screenName{"CoreDefault"};

		auto screen = m_overlayManager.createScreen(screenName);

		if ( screen == nullptr )
		{
			Tracer::error(ClassId, "Unable to get a screen to display the notifier !");

			return false;
		}

		m_text = screen->create< Overlay::Elements::Text >("Notifier", 1.0F, 0.1F);
		m_text->setPosition(Overlay::Surface::Position::Top);
		m_text->setClearColor(PixelFactory::Color{0.5F, 0.5F, 0.5F, 0.33F});

		auto & writer = m_text->textWriter();
		writer.setFont(Graphics::FontResource::get("old", true));
		writer.setColor(PixelFactory::White);
		writer.setSpacing(-8);

		return m_overlayManager.enableScreen(screenName);
	}

	bool
	Notifier::onTerminate () noexcept
	{
		if ( m_autoClearTimerID > 0 )
		{
			this->destroyTimer(m_autoClearTimerID);

			m_autoClearTimerID = 0;
		}

		m_text.reset();

		return true;
	}

	bool
	Notifier::usable () const noexcept
	{
		return m_text != nullptr;
	}

	void
	Notifier::push (const std::string & message, double time) noexcept
	{
		Tracer::info(ClassId, message);

		if ( !this->usable() )
		{
			return;
		}

		m_text->write(message, false);

		/* Start a timer or reset it to clean the message after a while. */
		if ( m_autoClearTimerID > 0 )
		{
			this->setTimerGranularity(m_autoClearTimerID, time);
		}
		else
		{
			m_autoClearTimerID = this->createTimer(
				std::bind(&Notifier::clearTask, this, std::placeholders::_1),
				time,
				true, /* Only once. */
				true /* Start directly. */
			);
		}
	}

	void
	Notifier::clear () noexcept
	{
		m_text->clear();
	}

	void
	Notifier::clearTask (double /*milliseconds*/) noexcept
	{
		this->clear();

		m_autoClearTimerID = 0;
	}
}
