/*
 * Emeraude/Overlay/Screen.hpp
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

/* C/C++ standard libraries. */
#include <memory>
#include <string>
#include <map>

/* Local inclusions for usages. */
#include "Surface.hpp"
#include "Elements.hpp"

/* Forward declaration */
namespace Emeraude::Graphics
{
	class Program;
	class Renderer;
}

namespace Emeraude::Overlay
{
	/**
	 * @brief This class define a screen or a page of the overlaying. It's a group of surfaces.
	 */
	class Screen final
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"UIScreen"};

			/**
			 * @brief Constructs a screen.
			 */
			Screen () noexcept = default;

			/**
			 * @brief Creates a new empty surface.
			 * @param surfaceName The name of the surface.
			 * @return shared_ptr< _T1 >
			 */
			template< class surface_t >
			std::shared_ptr< surface_t >
			create (const std::string & surfaceName) noexcept
			{
				if ( !this->checkSurfaceNameAvailability(surfaceName) )
					return nullptr;

				auto newSurface = std::make_shared< surface_t >();

				/* NOTE: pointer cast to Surface subtype. */
				m_surfaces[surfaceName] = newSurface;

				return newSurface;
			}

			/**
			 * @brief Creates a new surface.
			 * @param surfaceName The name of the surface.
			 * @param width The width of the surface.
			 * @param height The height of the surface.
			 * @return shared_ptr< _T1 >
			 */
			template< class surface_t >
			std::shared_ptr< surface_t >
			create (const std::string & surfaceName, float width, float height) noexcept
			{
				auto newSurface = this->create< surface_t >(surfaceName);

				if ( newSurface == nullptr )
					return nullptr;

				newSurface->setGeometry(width, height);

				return newSurface;
			}

			/**
			 * @brief Creates a new surface.
			 * @param surfaceName The name of the surface.
			 * @param width The width of the surface.
			 * @param height The height of the surface.
			 * @return shared_ptr< _T1 >
			 */
			template< class surface_t >
			std::shared_ptr< surface_t >
			create (const std::string & surfaceName, unsigned int width, unsigned int height) noexcept
			{
				auto newSurface = this->create< surface_t >(surfaceName);

				if ( newSurface == nullptr )
					return nullptr;

				newSurface->setGeometry(width, height);

				return newSurface;
			}

			/**
			 * @brief Destroys a surface by the name.
			 * @param surfaceName The name of the surface.
			 * @return bool
			 */
			bool destroySurface (const std::string & surfaceName) noexcept;

			/**
			 * @brief Returns a pointer to a named surface or nullptr.
			 * @param surfaceName The name of the surface.
			 * @return shared_ptr< const Surface >
			 */
			[[nodiscard]]
			std::shared_ptr< const Surface > surface (const std::string & surfaceName) const noexcept;

			/**
			 * @brief Returns a pointer to a named surface or nullptr.
			 * @param surfaceName The name of the surface.
			 * @return shared_ptr< Surface >
			 */
			std::shared_ptr< Surface > surface (const std::string & surfaceName) noexcept;

			/**
			 * @brief Updates necessary data in video memory. This is the screen level call.
			 * @return bool
			 */
			bool updateVideoMemory () noexcept;

			/**
			 * @brief Renders the screen.
			 * @param renderer A reference to the graphic renderer.
			 * @param program A reference to the overlay program.
			 */
			void render (Graphics::Renderer & renderer, const Graphics::Program & program) const noexcept;

			/**
			 * @brief Transfers the key press event to surfaces.
			 * @param key The keyboard universal key code.
			 * @param scanCode The system-dependent key code.
			 * @param modifiers The modifier keys mask.
			 * @param repeat Repeat state.
			 * @return bool
			 */
			bool onKeyPress (int key, int scanCode, int modifiers, bool repeat) noexcept;

			/**
			 * @brief Transfers the key release event to surfaces.
			 * @param key The keyboard universal key code.
			 * @param scanCode The system-dependent key code.
			 * @param modifiers The modifier keys mask.
			 * @return bool
			 */
			bool onKeyRelease (int key, int scanCode, int modifiers) noexcept;

			/**
			 * @brief Transferts the character typed event to surfaces.
			 * @param unicode The unicode number.
			 * @param modifiers Modification keys holded.
			 * @return bool
			 */
			bool onCharacterType (unsigned int unicode, int modifiers) noexcept;

			/**
			 * @brief Transferts the pointer movemement event to surfaces.
			 * @param x The x position of the cursor.
			 * @param y The Y position of the cursor.
			 * @return bool
			 */
			bool onPointerMove (float x, float y) noexcept;

			/**
			 * @brief Transferts the pointer press event to surfaces.
			 * @param x The x position of the cursor.
			 * @param y The Y position of the cursor.
			 * @param buttonNumber The mouse button.
			 * @param mods Modification keys holded.
			 * @return bool
			 */
			bool onButtonPress (float x, float y, int buttonNumber, int mods) noexcept;

			/**
			 * @brief Transferts the pointer release event to surfaces.
			 * @param x The x position of the cursor.
			 * @param y The Y position of the cursor.
			 * @param buttonNumber The mouse button.
			 * @param mods Modification keys holded.
			 * @return bool
			 */
			bool onButtonRelease (float x, float y, int buttonNumber, int mods) noexcept;

			/**
			 * @brief Transferts the mouse wheel event to surfaces.
			 * @param x The x position of the cursor.
			 * @param y The Y position of the cursor.
			 * @param xOffset The mouse wheel x offset.
			 * @param yOffset The mouse wheel y offset.
			 * @return bool
			 */
			bool onMouseWheel (float x, float y, float xOffset, float yOffset) noexcept;

		private:

			/* Flag names. */
			static constexpr auto RequestPointerEvents = 0UL;
			static constexpr auto RequestKeyboardEvents = 1UL;

			/**
			 * @brief checkSurfaceNameAvailability
			 * @param surfaceName
			 * @return
			 */
			[[nodiscard]]
			bool checkSurfaceNameAvailability (const std::string & surfaceName) const noexcept;

			std::map< std::string, std::shared_ptr< Surface > > m_surfaces{};
			std::array< bool, 8 > m_flags{
				true/*RequestPointerEvents*/,
				true/*RequestKeyboardEvents*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
