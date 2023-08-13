/*
 * Emeraude/Overlay/Screen.cpp
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

#include "Screen.hpp"

/* Local inclusions */
#include "Tracer.hpp"
#include "Graphics/Renderer.hpp"

namespace Emeraude::Overlay
{
	using namespace Libraries;

	bool
	Screen::destroySurface (const std::string & surfaceName) noexcept
	{
		auto surfaceIt = m_surfaces.find(surfaceName);

		if ( surfaceIt != m_surfaces.end() )
		{
			m_surfaces.erase(surfaceIt);

			return true;
		}

		TraceWarning{ClassId} << "Unable to find '" << surfaceName << "' Screen to erase it !";

		return false;
	}

	std::shared_ptr< const Surface >
	Screen::surface (const std::string & surfaceName) const noexcept
	{
		auto surfaceIt = m_surfaces.find(surfaceName);

		if ( surfaceIt != m_surfaces.cend() )
			return surfaceIt->second;

		return nullptr;
	}

	std::shared_ptr< Surface >
	Screen::surface (const std::string & surfaceName) noexcept
	{
		auto surfaceIt = m_surfaces.find(surfaceName);

		if ( surfaceIt != m_surfaces.end() )
			return surfaceIt->second;

		return nullptr;
	}

	bool
	Screen::updateVideoMemory () noexcept
	{
		for ( auto & surface : m_surfaces )
			surface.second->updateVideoMemory();

		return true;
	}

	void
	Screen::render (Graphics::Renderer & renderer, const Graphics::Program & program) const noexcept
	{
		if ( m_surfaces.empty() )
			return;

		for ( auto & surfaceIt : m_surfaces )
			surfaceIt.second->render(renderer, program);
	}

	bool
	Screen::onKeyPress (int key, int scanCode, int modifiers, bool repeat) noexcept
	{
		/* If no surfaces or this screen doesn't need to look for keyboard event,
		 * we returns false directly. */
		if ( m_surfaces.empty() || !m_flags[RequestKeyboardEvents] )
			return false;

		auto somethingHappens = false;

		for ( auto & surfaceIt : m_surfaces )
		{
			auto & surface = surfaceIt.second;

			if ( !surface->isCapturingKeyboardEvents() || !surface->isFocused() )
				continue;

			surface->onKeyPress(key, scanCode, modifiers, repeat);

			somethingHappens = true;
		}

		return somethingHappens;
	}

	bool
	Screen::onKeyRelease (int key, int scanCode, int modifiers) noexcept
	{
		/* If no surfaces or this screen doesn't need to look for keyboard event,
		 * we returns false directly. */
		if ( m_surfaces.empty() || !m_flags[RequestKeyboardEvents] )
			return false;

		auto somethingHappens = false;

		for ( auto & surfaceIt : m_surfaces )
		{
			auto & surface = surfaceIt.second;

			if ( !surface->isCapturingKeyboardEvents() || !surface->isFocused() )
				continue;

			surface->onKeyRelease(key, scanCode, modifiers);

			somethingHappens = true;
		}

		return somethingHappens;
	}

	bool
	Screen::onCharacterType (unsigned int unicode, int modifiers) noexcept
	{
		/* If no surfaces or this screen doesn't need to look for keyboard event,
		 * we returns false directly. */
		if ( m_surfaces.empty() || !m_flags[RequestKeyboardEvents] )
			return false;

		auto somethingHappens = false;

		for ( auto & surfaceIt : m_surfaces )
		{
			auto & surface = surfaceIt.second;

			if ( !surface->isCapturingKeyboardEvents() || !surface->isFocused() )
				continue;

			surface->onCharacterType(unicode, modifiers);

			somethingHappens = true;
		}

		return somethingHappens;
	}

	bool
	Screen::onPointerMove (float x, float y) noexcept
	{
		/* If no surfaces or this screen doesn't need to look for pointer/mouse event,
		 * we returns false directly. */
		if ( m_surfaces.empty() || !m_flags[RequestPointerEvents] )
			return false;

		auto somethingHappens = false;

		for ( auto & surfaceIt : m_surfaces )
		{
			auto & surface = surfaceIt.second;

			if ( !surface->isCapturingPointerEvents() )
				continue;

			/* Checks if the pointer is over the surface. */
			if ( surface->isBelow(x, y) )
			{
				/* Checks the 'over' state and if requested,
				 * creates the 'entering' event. */
				if ( !surface->isPointerOver() )
				{
					surface->setPointerOverState(true);

					surface->onPointerEnter(x, y);
				}

				surface->onPointerMove(x, y);

				somethingHappens = true;
			}
			else
			{
				/* Checks the 'over' state and if requested,
				 * creates the 'leaving' event. */
				if ( surface->isPointerOver() )
				{
					surface->setPointerOverState(false);

					surface->onPointerLeave(x, y);

					somethingHappens = true;
				}
			}
		}

		return somethingHappens;
	}

	bool
	Screen::onButtonPress (float x, float y, int buttonNumber, int mods) noexcept
	{
		/* If no surfaces or this screen doesn't need to look for pointer/mouse event,
		 * we returns false directly. */
		if ( m_surfaces.empty() || !m_flags[RequestPointerEvents] )
			return false;

		auto somethingHappens = false;

		for ( auto & surfaceIt : m_surfaces )
		{
			auto & surface = surfaceIt.second;

			if ( !surface->isCapturingPointerEvents() )
				continue;

			if ( surface->isBelow(x, y) )
			{
				surface->setFocusedState(true);

				surface->onButtonPress(x, y, buttonNumber, mods);

				somethingHappens = true;
			}
			else
			{
				surface->setFocusedState(false);
			}
		}

		return somethingHappens;
	}

	bool
	Screen::onButtonRelease (float x, float y, int buttonNumber, int mods) noexcept
	{
		/* If no surfaces or this screen doesn't need to look for pointer/mouse event,
		 * we returns false directly. */
		if ( m_surfaces.empty() || !m_flags[RequestPointerEvents] )
			return false;

		auto somethingHappens = false;

		for ( auto & surfaceIt : m_surfaces )
		{
			auto & surface = surfaceIt.second;

			if ( !surface->isCapturingPointerEvents() )
				continue;

			if ( surface->isBelow(x, y) )
			{
				surface->onButtonRelease(x, y, buttonNumber, mods);

				somethingHappens = true;
			}
		}

		return somethingHappens;
	}

	bool
	Screen::onMouseWheel (float x, float y, float xOffset, float yOffset) noexcept
	{
		/* If no surfaces or this screen doesn't need to look for pointer/mouse event,
		 * we returns false directly. */
		if ( m_surfaces.empty() || !m_flags[RequestPointerEvents] )
			return false;

		auto somethingHappens = false;

		for ( auto & surfaceIt : m_surfaces )
		{
			auto & surface = surfaceIt.second;

			if ( !surface->isCapturingPointerEvents() )
				continue;

			if ( surface->isBelow(x, y) )
			{
				surface->onMouseWheel(x, y, xOffset, yOffset);

				somethingHappens = true;
			}
		}

		return somethingHappens;
	}

	bool
	Screen::checkSurfaceNameAvailability (const std::string & surfaceName) const noexcept
	{
		auto surfaceIt = m_surfaces.find(surfaceName);

		if ( surfaceIt != m_surfaces.cend() )
		{
			TraceWarning{ClassId} << "A surface named '" << surfaceName << "' already exists in the screen !";

			return false;
		}

		return true;
	}
}
