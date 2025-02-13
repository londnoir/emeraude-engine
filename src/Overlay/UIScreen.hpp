/*
 * src/Overlay/UIScreen.hpp
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
#include <array>
#include <map>
#include <memory>
#include <string>

/* Local inclusions for inheritances. */
#include "Libraries/NameableTrait.hpp"

/* Local inclusions for usages. */
#include "AbstractSurface.hpp"
#include "FramebufferProperties.hpp"
#include "Graphics/Renderer.hpp"
#include "Tracer.hpp"

namespace Emeraude::Overlay
{
	/**
	 * @brief Defines an overlaying screen object.
	 * @details There is no physical properties. This is just a group of surfaces and dispatch input event to it.
	 * @exception Libraries::NameableTrait A UI screen have a name.
	 */
	class UIScreen final : public Libraries::NameableTrait
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"UIScreen"};

			/**
			 * @brief Constructs a default UI screen.
			 * @param name A reference to a string.
			 * @param framebufferProperties A reference to an array [width, height].
			 * @param graphicsRenderer A reference to the graphics renderer.
			 * @param enableKeyboardListener Enables the keyboard listener at creation.
			 * @param enablePointerListener Enables the pointer listener at creation.
			 */
			UIScreen (const std::string & name, const FramebufferProperties & framebufferProperties, Graphics::Renderer & graphicsRenderer, bool enableKeyboardListener, bool enablePointerListener) noexcept;

			/**
			 * @brief Returns whether the UI screen has surfaces declared.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			empty () const noexcept
			{
				return m_surfaces.empty();
			}

			/**
			 * @brief Sets the UI screen visibility.
			 * @param state The state
			 * @return void
			 */
			void
			setVisibility (bool state) noexcept
			{
				m_flags[IsVisible] = state;
			}

			/**
			 * @brief Returns whether the UI screen is visible.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isVisible () const noexcept
			{
				return m_flags[IsVisible];
			}

			/**
			 * @brief Enables the listening of keyboard events.
			 * @param state The state.
			 * @return void
			 */
			void
			enableKeyboardListening (bool state) noexcept
			{
				m_flags[IsListeningKeyboard] = state;
			}

			/**
			 * @brief Returns whether the keyboard is listened.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isListeningKeyboard () const noexcept
			{
				return m_flags[IsListeningKeyboard];
			}

			/**
			 * @brief Enables the listening of pointer events.
			 * @param state The state.
			 * @return void
			 */
			void
			enablePointerListening (bool state) noexcept
			{
				m_flags[IsListeningPointer] = state;
			}

			/**
			 * @brief Returns whether the pointer is listened.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isListeningPointer () const noexcept
			{
				return m_flags[IsListeningPointer];
			}

			/**
			 * @brief Creates a specialized surface.
			 * @tparam surface_t The type of screen.
			 * @tparam ctor_args The type of screen constructor optional arguments.
			 * @param name A reference to a string.
			 * @param args Additional arguments to pass to specific surface constructor. Default none.
			 * @return std::shared_ptr< surface_t >
			 */
			template< typename surface_t, typename... ctor_args >
			std::shared_ptr< surface_t >
			createSurface (const std::string & name, ctor_args... args) noexcept requires (std::is_base_of_v< AbstractSurface, surface_t >)
			{
#ifdef DEBUG
				if ( !m_framebufferProperties.isValid() )
				{
					TraceError{ClassId} << "The screen size are not initialized !";

					return nullptr;
				}
#endif

				if ( m_surfaces.contains(name) )
				{
					TraceError{ClassId} << "The UI screen '" << this->name() << "' contains already a surface named '" << name << "' !";

					return nullptr;
				}

				const auto surface = std::make_shared< surface_t >(name, std::forward< ctor_args >(args)...);

				if ( !surface->createOnHardware(m_graphicsRenderer, m_framebufferProperties) )
				{
					TraceError{ClassId} << "Unable to create the surface '" << name << "' on the GPU !";

					return nullptr;
				}

				m_surfaces[name] = surface;

				return surface;
			}

			/**
			 * @brief Deletes all surfaces.
			 * @return void
			 */
			void
			clearSurfaces () noexcept
			{
				m_surfaces.clear();
			}

			/**
			 * @brief Resizes the surface textures resolution according to the new window size.
			 * @param renderer A reference to the graphics renderer.
			 * @param framebufferProperties A reference to the framebuffer properties.
			 * @return bool
			 */
			[[nodiscard]]
			bool updatePhysicalRepresentation (Graphics::Renderer & renderer, const FramebufferProperties & framebufferProperties) noexcept;

			/**
			 * @brief Updates necessary data in video memory.
			 * @param renderer A reference to the graphics renderer.
			 * @return bool
			 */
			bool updateVideoMemory (Graphics::Renderer & renderer) noexcept;

			/**
			 * @brief Destroys a surface by its name.
			 * @param name A reference to a string.
			 * @return bool
			 */
			bool destroySurface (const std::string & name) noexcept;

			/**
			 * @brief Returns the screen surfaces list.
			 * @return const std::map< std::string, std::shared_ptr< AbstractSurface > > &
			 */
			[[nodiscard]]
			const std::map< std::string, std::shared_ptr< AbstractSurface > > &
			surfaces () const noexcept
			{
				return m_surfaces;
			}

			/**
			 * @brief Returns a pointer to a named surface or nullptr.
			 * @param name The name of the surface.
			 * @return std::shared_ptr< const AbstractSurface >
			 */
			[[nodiscard]]
			std::shared_ptr< const AbstractSurface > getSurface (const std::string & name) const noexcept;

			/**
			 * @brief Returns a pointer to a named surface or nullptr.
			 * @param name The name of the surface.
			 * @return std::shared_ptr< AbstractSurface >
			 */
			[[nodiscard]]
			std::shared_ptr< AbstractSurface > getSurface (const std::string & name) noexcept;

			/**
			 * @brief Sets an exclusive surface to receive inputs.
			 * @param name A reference to a string.
			 * @return bool
			 */
			[[nodiscard]]
			bool setInputExclusiveSurface (const std::string & name) noexcept;

			/**
			 * @brief Disables a previous input exclusive surface.
			 * @return void
			 */
			void
			disableInputExclusiveSurface () noexcept
			{
				m_inputExclusiveSurface.reset();
			}

			/**
			 * @bries Returns whether an input exclusive surface has been set.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isInputExclusiveSurfaceEnabled () const noexcept
			{
				return m_inputExclusiveSurface != nullptr;
			}

			/**
			 * @brief Returns the surface set as input exclusive.
			 * @warning This can be nullptr.
			 * @return std::shared_ptr< AbstractSurface >
			 */
			[[nodiscard]]
			std::shared_ptr< AbstractSurface >
			inputExclusiveSurface () const noexcept
			{
				return m_inputExclusiveSurface;
			}

			/**
			 * @brief Transfers the key press event to surfaces.
			 * @param key The keyboard universal key code. I.e, QWERTY keyboard 'A' key gives the ASCII code '65' on all platform.
			 * @param scancode The OS dependent scancode.
			 * @param modifiers The modifier keys mask.
			 * @param repeat Repeat state.
			 * @return bool
			 */
			bool onKeyPress (int32_t key, int32_t scancode, int32_t modifiers, bool repeat) noexcept;

			/**
			 * @brief Transfers the key release event to surfaces.
			 * @param key The keyboard universal key code. I.e, QWERTY keyboard 'A' key gives the ASCII code '65' on all platform.
			 * @param scancode The OS dependent scancode..
			 * @param modifiers The modifier keys mask.
			 * @return bool
			 */
			bool onKeyRelease (int32_t key, int32_t scancode, int32_t modifiers) noexcept;

			/**
			 * @brief Transfers the character typed event to surfaces.
			 * @param unicode The Unicode number.
			 * @return bool
			 */
			bool onCharacterType (uint32_t unicode) noexcept;

			/**
			 * @brief Transfers the pointer movement event to surfaces.
			 * @param framebufferProperties A reference to the framebuffer properties.
			 * @param positionX The x position of the cursor.
			 * @param positionY The Y position of the cursor.
			 * @return bool
			 */
			bool onPointerMove (const FramebufferProperties & framebufferProperties, float positionX, float positionY) noexcept;

			/**
			 * @brief Transfers the pointer press event to surfaces.
			 * @param framebufferProperties A reference to the framebuffer properties.
			 * @param positionX The x position of the cursor.
			 * @param positionY The Y position of the cursor.
			 * @param buttonNumber The mouse button.
			 * @param modifiers Modification keys held.
			 * @return bool
			 */
			bool onButtonPress (const FramebufferProperties & framebufferProperties, float positionX, float positionY, int32_t buttonNumber, int32_t modifiers) noexcept;

			/**
			 * @brief Transfers the pointer release event to surfaces.
			 * @param framebufferProperties A reference to the framebuffer properties.
			 * @param positionX The x position of the cursor.
			 * @param positionY The Y position of the cursor.
			 * @param buttonNumber The mouse button.
			 * @param modifiers Modification keys held.
			 * @return bool
			 */
			bool onButtonRelease (const FramebufferProperties & framebufferProperties, float positionX, float positionY, int32_t buttonNumber, int32_t modifiers) noexcept;

			/**
			 * @brief Transfers the mouse wheel event to surfaces.
			 * @param framebufferProperties A reference to the framebuffer properties.
			 * @param positionX The x position of the cursor.
			 * @param positionY The Y position of the cursor.
			 * @param xOffset The mouse wheel x offset.
			 * @param yOffset The mouse wheel y offset.
			 * @return bool
			 */
			bool onMouseWheel (const FramebufferProperties & framebufferProperties, float positionX, float positionY, float xOffset, float yOffset) noexcept;

		private:

			/* Flag names. */
			static constexpr auto IsVisible{0UL};
			static constexpr auto IsListeningKeyboard{1UL};
			static constexpr auto IsListeningPointer{2UL};

			Graphics::Renderer & m_graphicsRenderer;
			FramebufferProperties m_framebufferProperties;
			std::map< std::string, std::shared_ptr< AbstractSurface > > m_surfaces;
			std::shared_ptr< AbstractSurface > m_inputExclusiveSurface;
			std::array< bool, 8 > m_flags{
				false/*IsVisible*/,
				false/*IsListeningKeyboard*/,
				false/*IsListeningPointer*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
