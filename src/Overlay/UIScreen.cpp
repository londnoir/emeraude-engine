/*
 * src/Overlay/UIScreen.cpp
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

#include "UIScreen.hpp"

/* STL inclusions. */
#include <array>
#include <cstddef>
#include <map>
#include <memory>
#include <string>
#include <ranges>

/* Local inclusions. */
#include "FramebufferProperties.hpp"
#include "Graphics/TextureResource/Abstract.hpp"
#include "Libs/NameableTrait.hpp"
#include "Surface.hpp"
#include "Tracer.hpp"

namespace EmEn::Overlay
{
	using namespace EmEn::Libs;
	using namespace Graphics;

	UIScreen::UIScreen (const std::string & name, const FramebufferProperties & framebufferProperties, Renderer & graphicsRenderer, bool enableKeyboardListener, bool enablePointerListener) noexcept
		: NameableTrait(name),
		m_graphicsRenderer(graphicsRenderer),
		m_framebufferProperties(framebufferProperties)
	{
		m_flags[IsListeningKeyboard] = enableKeyboardListener;
		m_flags[IsListeningPointer] = enablePointerListener;
	}

	bool
	UIScreen::updateVideoMemory (bool windowResized) noexcept
	{
		if ( this->empty() )
		{
			return true;
		}

		size_t errors = 0;

		for ( const auto & surface : m_surfaces | std::views::values )
		{
			if ( windowResized )
			{
				surface->invalidate();
			}

			if ( !surface->updateVideoMemory(m_graphicsRenderer) )
			{
				errors++;
			}
		}

		return errors == 0;
	}

	bool
	UIScreen::destroySurface (const std::string & name) noexcept
	{
		const auto surfaceIt = m_surfaces.find(name);

		if ( surfaceIt == m_surfaces.cend() )
		{
			TraceWarning{ClassId} << "There is no surface named '" << name << "' in the screen to erase !";

			return false;
		}

		surfaceIt->second->destroyFromHardware();

		m_surfaces.erase(surfaceIt);

		return true;
	}

	std::shared_ptr< const Surface >
	UIScreen::getSurface (const std::string & name) const noexcept
	{
		const auto surfaceIt = m_surfaces.find(name);

		if ( surfaceIt == m_surfaces.cend() )
		{
			TraceWarning{ClassId} << "There is no surface named " << name << "' in the screen !";

			return nullptr;
		}

		return surfaceIt->second;
	}

	std::shared_ptr< Surface >
	UIScreen::getSurface (const std::string & name) noexcept
	{
		const auto surfaceIt = m_surfaces.find(name);

		if ( surfaceIt == m_surfaces.cend() )
		{
			TraceWarning{ClassId} << "There is no surface named " << name << "' in the screen !";

			return nullptr;
		}

		return surfaceIt->second;
	}

	bool
	UIScreen::setInputExclusiveSurface (const std::string & name) noexcept
	{
		const auto surface = this->getSurface(name);

		if ( surface == nullptr )
		{
			return false;
		}

		m_inputExclusiveSurface = surface;

		return true;
	}

	bool
	UIScreen::onKeyPress (int32_t key, int32_t scancode, int32_t modifiers, bool repeat) noexcept
	{
		const auto dispatchEvent = [key, scancode, modifiers, repeat] (const std::shared_ptr< Surface > & surface) -> bool
		{
			if ( !surface->isListeningKeyboard() || !surface->isFocused() )
			{
				return false;
			}

			return surface->onKeyPress(key, scancode, modifiers, repeat);
		};

		if ( m_inputExclusiveSurface != nullptr )
		{
			return dispatchEvent(m_inputExclusiveSurface);
		}

		auto somethingHappens = false;

		for ( const auto & [surfaceName, surface] : m_surfaces )
		{
			somethingHappens = dispatchEvent(surface);
		}

		return somethingHappens;
	}

	bool
	UIScreen::onKeyRelease (int32_t key, int32_t scancode, int32_t modifiers) noexcept
	{
		const auto dispatchEvent = [key, scancode, modifiers] (const std::shared_ptr< Surface > & surface) -> bool
		{
			if ( !surface->isListeningKeyboard() || !surface->isFocused() )
			{
				return false;
			}

			return surface->onKeyRelease(key, scancode, modifiers);
		};

		if ( m_inputExclusiveSurface != nullptr )
		{
			return dispatchEvent(m_inputExclusiveSurface);
		}

		auto somethingHappens = false;

		for ( const auto & [surfaceName, surface] : m_surfaces )
		{
			somethingHappens = dispatchEvent(surface);
		}

		return somethingHappens;
	}

	bool
	UIScreen::onCharacterType (uint32_t unicode) noexcept
	{
		const auto dispatchEvent = [unicode] (const std::shared_ptr< Surface > & surface) -> bool
		{
			if ( !surface->isListeningKeyboard() || !surface->isFocused() )
			{
				return false;
			}

			return surface->onCharacterType(unicode);
		};

		if ( m_inputExclusiveSurface != nullptr )
		{
			return dispatchEvent(m_inputExclusiveSurface);
		}

		auto somethingHappens = false;

		for ( const auto & [surfaceName, surface] : m_surfaces )
		{
			somethingHappens = dispatchEvent(surface);
		}

		return somethingHappens;
	}

	bool
	UIScreen::onPointerMove (float positionX, float positionY) noexcept
	{
		const auto dispatchEvent = [positionX, positionY] (const std::shared_ptr< Surface > & surface) -> bool
		{
			/* NOTE: Always check if the pointer is over the surface. */
			const auto pointerOver = surface->isBelowPoint(positionX, positionY);

			if ( !surface->isListeningPointer() )
			{
				surface->setPointerOverState(pointerOver);

				return false;
			}

			if ( pointerOver )
			{
				/* NOTE: If pointer wasn't over the surface before, generate an entering event. */
				if ( !surface->isPointerWasOver() )
				{
					surface->setPointerOverState(true);

					surface->onPointerEnter(positionX, positionY);
				}

				return surface->onPointerMove(positionX, positionY);
			}

			/* NOTE: If pointer was over the surface before, generate a leaving event. */
			if ( surface->isPointerWasOver() )
			{
				surface->setPointerOverState(false);

				surface->onPointerLeave(positionX, positionY);
			}

			return false;
		};

		if ( m_inputExclusiveSurface != nullptr )
		{
			return dispatchEvent(m_inputExclusiveSurface);
		}

		auto somethingHappens = false;

		for ( const auto & surface: m_surfaces | std::views::values )
		{
			somethingHappens = dispatchEvent(surface);
		}

		return somethingHappens;
	}

	bool
	UIScreen::onButtonPress (float positionX, float positionY, int32_t buttonNumber, int32_t modifiers) noexcept
	{
		const auto dispatchEvent = [positionX, positionY, buttonNumber, modifiers] (const std::shared_ptr< Surface > & surface) -> bool
		{
			if ( surface->isListeningPointer() && surface->isBelowPoint(positionX, positionY) )
			{
				surface->setFocusedState(true);

				return surface->onButtonPress(positionX, positionY, buttonNumber, modifiers);
			}

			surface->setFocusedState(false);

			return false;
		};

		if ( m_inputExclusiveSurface != nullptr )
		{
			return dispatchEvent(m_inputExclusiveSurface);
		}

		auto somethingHappens = false;

		for ( const auto & surface: m_surfaces | std::views::values )
		{
			somethingHappens = dispatchEvent(surface);
		}

		return somethingHappens;
	}

	bool
	UIScreen::onButtonRelease (float positionX, float positionY, int32_t buttonNumber, int32_t modifiers) noexcept
	{
		const auto dispatchEvent = [positionX, positionY, buttonNumber, modifiers] (const std::shared_ptr< Surface > & surface) -> bool
		{
			if ( surface->isListeningPointer() && surface->isBelowPoint(positionX, positionY) )
			{
				return surface->onButtonRelease(positionX, positionY, buttonNumber, modifiers);
			}

			return false;
		};

		if ( m_inputExclusiveSurface != nullptr )
		{
			return dispatchEvent(m_inputExclusiveSurface);
		}

		auto somethingHappens = false;

		for ( const auto & surface: m_surfaces | std::views::values )
		{
			somethingHappens = dispatchEvent(surface);
		}

		return somethingHappens;
	}

	bool
	UIScreen::onMouseWheel (float positionX, float positionY, float xOffset, float yOffset) noexcept
	{
		const auto dispatchEvent = [positionX, positionY, xOffset, yOffset] (const std::shared_ptr< Surface > & surface) -> bool
		{
			if ( surface->isListeningPointer() && surface->isBelowPoint(positionX, positionY) )
			{
				return surface->onMouseWheel(positionX, positionY, xOffset, yOffset);
			}

			return false;
		};

		if ( m_inputExclusiveSurface != nullptr )
		{
			return dispatchEvent(m_inputExclusiveSurface);
		}

		auto somethingHappens = false;

		for ( const auto & surface: m_surfaces | std::views::values )
		{
			somethingHappens = dispatchEvent(surface);
		}

		return somethingHappens;
	}
}
