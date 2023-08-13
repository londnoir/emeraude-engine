/*
 * Emeraude/Input/PointerListenerInterface.cpp
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

#include "PointerListenerInterface.hpp"

/* Local inclusions */
#include "Manager.hpp"
#include "Tracer.hpp"

namespace Emeraude::Input
{
	constexpr auto TracerTag{"PointerListener"};

	PointerListenerInterface::PointerListenerInterface (bool isOpaque, bool isAbsoluteMode, bool autoRegister) noexcept
		: AbstractInputListener(isOpaque)
	{
		/* Auto register this input listener to the manager. */
		if ( autoRegister )
		{
			this->enablePointerListening(true);

			Tracer::info(TracerTag, "Pointer listener automatically registered to input manager !");
		}

		m_listenerFlags[IsAbsoluteMode] = isAbsoluteMode;
	}

	void
	PointerListenerInterface::setAbsoluteMode (bool state) noexcept
	{
		m_listenerFlags[IsAbsoluteMode] = state;
	}

	bool
	PointerListenerInterface::isAbsoluteModeEnabled () const noexcept
	{
		return m_listenerFlags[IsAbsoluteMode];
	}

	void
	PointerListenerInterface::enablePointerListening (bool state) noexcept
	{
		if ( state )
		{
			Input::Manager::instance()->addPointerListener(this);
		}
		else
		{
			Input::Manager::instance()->removePointerListener(this);
		}
	}

	bool
	PointerListenerInterface::onPointerEnter (float /*x*/, float /*y*/) noexcept
	{
		return false;
	}

	bool
	PointerListenerInterface::onPointerLeave (float /*x*/, float /*y*/) noexcept
	{
		return false;
	}

	bool
	PointerListenerInterface::onPointerMove (float /*x*/, float /*y*/) noexcept
	{
		return false;
	}

	bool
	PointerListenerInterface::onButtonPress (float /*x*/, float /*y*/, int /*buttonNumber*/, int /*modifiers*/) noexcept
	{
		return false;
	}

	bool
	PointerListenerInterface::onButtonRelease (float /*x*/, float /*y*/, int /*buttonNumber*/, int /*modifiers*/) noexcept
	{
		return false;
	}

	bool
	PointerListenerInterface::onMouseWheel (float /*x*/, float /*y*/, float /*xOffset*/, float /*yOffset*/) noexcept
	{
		return false;
	}
}
