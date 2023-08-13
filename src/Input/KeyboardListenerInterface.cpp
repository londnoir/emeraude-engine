/*
 * Emeraude/Input/KeyboardListenerInterface.cpp
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

#include "KeyboardListenerInterface.hpp"

/* Local inclusions */
#include "Manager.hpp"
#include "Tracer.hpp"

namespace Emeraude::Input
{
	constexpr auto TracerTag{"KeyboardListener"};

	KeyboardListenerInterface::KeyboardListenerInterface (bool isOpaque, bool enableTextMode, bool autoRegister) noexcept
		: AbstractInputListener(isOpaque)
	{
		/* Auto register this input listener to the manager. */
		if ( autoRegister )
		{
			this->enableKeyboardListening(true);

			Tracer::info(TracerTag, "Keyboard listener automatically registered to input manager !");
		}

		m_listenerFlags[TextMode] = enableTextMode;
	}

	bool
	KeyboardListenerInterface::onKeyPress (int /*key*/, int /*scanCode*/, int /*modifiers*/, bool /*repeat*/) noexcept
	{
		return false;
	}

	bool
	KeyboardListenerInterface::onKeyRelease (int /*key*/, int /*scanCode*/, int /*modifiers*/) noexcept
	{
		return false;
	}

	bool
	KeyboardListenerInterface::onCharacterType (unsigned int /*unicode*/, int /*modifiers*/) noexcept
	{
		Tracer::warning(TracerTag, "Text mode has been enabled on a listener which not overriding this method !");

		return false;
	}

	void
	KeyboardListenerInterface::enableTextMode (bool state) noexcept
	{
		m_listenerFlags[TextMode] = state;
	}

	bool
	KeyboardListenerInterface::isTextModeEnabled () const noexcept
	{
		return m_listenerFlags[TextMode];
	}

	void
	KeyboardListenerInterface::enableKeyboardListening (bool state) noexcept
	{
		if ( state )
		{
			Input::Manager::instance()->addKeyboardListener(this);
		}
		else
		{
			Input::Manager::instance()->removeKeyboardListener(this);
		}
	}
}
