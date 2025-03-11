/*
 * src/Overlay/AbstractSurface.hpp
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
#include <array>
#include <string>

/* Local inclusions for inheritance. */
#include "Graphics/TextureResource/Abstract.hpp"
#include "Libs/NameableTrait.hpp"

/* Local inclusions for usages. */
#include "FramebufferProperties.hpp"
#include "Libs/Math/Matrix.hpp"
#include "Libs/Math/Rectangle.hpp"

namespace EmEn::Vulkan
{
	class LayoutManager;
	class DescriptorSet;
}

namespace EmEn::Overlay
{
	/**
	 * @brief The base class for all overlay surfaces.
	 * @exception Libraries::NameableTrait A surface have a name.
	 */
	class AbstractSurface : public Libs::NameableTrait
	{
		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractSurface (const AbstractSurface & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractSurface (AbstractSurface && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return SurfaceInterface &
			 */
			AbstractSurface & operator= (const AbstractSurface & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return SurfaceInterface &
			 */
			AbstractSurface & operator= (AbstractSurface && copy) noexcept = delete;

			/**
			 * @brief Destructs the surface.
			 */
			~AbstractSurface () noexcept override = default;

			/**
			 * @brief Returns the framebuffer properties from the overlay.
			 * @return const FramebufferProperties &
			 */
			[[nodiscard]]
			const FramebufferProperties &
			framebufferProperties () const noexcept
			{
				return m_framebufferProperties;
			}

			/**
			 * @brief Returns the surface geometry.
			 * @return const Libraries::Math::Rectangle< float > &
			 */
			[[nodiscard]]
			const Libs::Math::Rectangle< float > &
			geometry () const noexcept
			{
				return m_rectangle;
			}

			/**
			 * @brief Returns the surface depth on screen.
			 * @return float
			 */
			[[nodiscard]]
			float
			depth () const noexcept
			{
				return m_depth;
			}

			/**
			 * @brief Returns the transformation matrix to place the surface on screen.
			 * @return const Libraries::Math::Matrix< 4, float > &
			 */
			[[nodiscard]]
			const Libs::Math::Matrix< 4, float > &
			transformationMatrix () const noexcept
			{
				return m_transformationMatrix;
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
			 * @brief Sets the surface "pointer-over" state.
			 * @param state The state.
			 * @return void
			 */
			void
			setPointerOverState (bool state) noexcept
			{
				m_flags[IsPointerWasOver] = state;
			}

			/**
			 * @brief Returns whether the pointer was on the surface in the last move event check.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isPointerWasOver () const noexcept
			{
				return m_flags[IsPointerWasOver];
			}

			/**
			 * @brief Sets the surface "focus" state.
			 * @param state The state.
			 * @return void
			 */
			void
			setFocusedState (bool state) noexcept
			{
				m_flags[IsFocused] = state;
			}

			/**
			 * @brief Returns whether the surface is focused.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isFocused () const noexcept
			{
				return m_flags[IsFocused];
			}

			/**
			 * @brief Checks whether the pointer coordinates intersects with the surface.
			 * @param positionX The pointer coordinate on X screen axis.
			 * @param positionY The pointer coordinate on Y screen axis.
			 * @return bool
			 */
			[[nodiscard]]
			bool isBelowPoint (float positionX, float positionY) const noexcept;

			/**
			 * @brief Updates the physical properties of a surface.
			 * @note This occurs when the application window is resized.
			 * @param renderer A reference to the graphics renderer.
			 * @return bool
			 */
			bool updatePhysicalRepresentation (Graphics::Renderer & renderer) noexcept;

			/**
			 * @brief Declares to update surface on the GPU.
			 * @return void
			 */
			void
			requestVideoMemoryUpdate () noexcept
			{
				m_flags[VideoMemoryUpdateRequested] = true;
			}

			/**
			 * @brief Updates the local data changes to the GPU.
			 * @note The AbstractSurface::requestVideoMemoryUpdate() method must be called first for it to actually do anything.
			 * @param renderer A reference to the graphics renderer.
			 * @return bool
			 */
			bool updateVideoMemory (Graphics::Renderer & renderer) noexcept;

			/**
			 * @brief On key press event handler.
			 * @note Override this method to react on the input event.
			 * @param key The keyboard universal key code. I.e, QWERTY keyboard 'A' key gives the ASCII code '65' on all platform.
			 * @param scancode The OS dependent scancode.
			 * @param modifiers The modifier keys mask.
			 * @param repeat Repeat state.
			 * @return bool
			 */
			virtual bool onKeyPress (int32_t key, int32_t scancode, int32_t modifiers, bool repeat) noexcept
			{
				return false;
			}

			/**
			 * @brief On key release event handler.
			 * @note Override this method to react on the input event.
			 * @param key The keyboard universal key code. I.e, QWERTY keyboard 'A' key gives the ASCII code '65' on all platform.
			 * @param scancode The OS dependent scancode.
			 * @param modifiers The modifier keys mask.
			 * @return bool
			 */
			virtual bool onKeyRelease (int32_t key, int32_t scancode, int32_t modifiers) noexcept
			{
				return false;
			}

			/**
			 * @brief On character typing event handler.
			 * @note Override this method to react on the input event.
			 * @param unicode The character Unicode value.
			 * @return bool
			 */
			virtual bool onCharacterType (uint32_t unicode) noexcept
			{
				return false;
			}

			/**
			 * @brief Method fired when pointer is entering the surface.
			 * @note Override this method to react on the input event.
			 * @param positionX The pointer X position.
			 * @param positionY The pointer Y position.
			 * @return bool
			 */
			virtual void onPointerEnter (float positionX, float positionY) noexcept
			{

			}

			/**
			 * @brief Method fired when pointer is leaving the surface.
			 * @note Override this method to react on the input event.
			 * @param positionX The pointer X position.
			 * @param positionY The pointer Y position.
			 * @return bool
			 */
			virtual void onPointerLeave (float positionX, float positionY) noexcept
			{

			}

			/**
			 * @brief Method fired when pointer is moving on the surface.
			 * @note Override this method to react on the input event.
			 * @param positionX The pointer X position.
			 * @param positionY The pointer Y position.
			 * @return bool
			 */
			virtual bool onPointerMove (float positionX, float positionY) noexcept
			{
				return m_flags[IsOpaque];
			}

			/**
			 * @brief Method fired when a button of the pointer is pressed on the surface.
			 * @note Override this method to react on the input event.
			 * @param positionX The pointer X position.
			 * @param positionY The pointer Y position.
			 * @param buttonNumber The pointer button number pressed.
			 * @param modifiers The keyboard modifiers held when the button has been pressed.
			 * @return bool
			 */
			virtual bool onButtonPress (float positionX, float positionY, int32_t buttonNumber, int32_t modifiers) noexcept
			{
				return m_flags[IsOpaque];
			}

			/**
			 * @brief Method fired when a button of the pointer is released on the surface.
			 * @note Override this method to react on the input event.
			 * @param positionX The pointer X position.
			 * @param positionY The pointer Y position.
			 * @param buttonNumber The pointer button number released.
			 * @param modifiers The keyboard modifiers held when the button has been released.
			 * @return bool
			 */
			virtual bool onButtonRelease (float positionX, float positionY, int buttonNumber, int modifiers) noexcept
			{
				return m_flags[IsOpaque];
			}

			/**
			 * @brief Method fired when the mouse wheel is activated on the surface.
			 * @note Override this method to react on the input event.
			 * @param positionX The pointer X position when the mouse wheel occurred.
			 * @param positionY The pointer Y modifiers the mouse wheel occurred.
			 * @param xOffset The scroll distance on the X axis.
			 * @param yOffset The scroll distance on the Y axis.
			 * @return bool
			 */
			virtual bool onMouseWheel (float positionX, float positionY, float xOffset, float yOffset) noexcept
			{
				return m_flags[IsOpaque];
			}

			/**
			 * @brief Returns the surface descriptor set.
			 * @return const Vulkan::DescriptorSet *
			 */
			[[nodiscard]]
			virtual const Vulkan::DescriptorSet * descriptorSet () const noexcept = 0;

			/**
			 * @brief Creates the surface on the GPU.
			 * @param renderer A reference to the graphics renderer.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool createOnHardware (Graphics::Renderer & renderer) noexcept = 0;

			/**
			 * @brief Destroys the surface from the GPU.
			 * @return bool
			 */
			virtual bool destroyFromHardware () noexcept = 0;

		protected:

			/**
			 * @brief Constructs a surface.
			 * @param framebufferProperties A reference to the overlay framebuffer properties.
			 * @param name A reference to a string.
			 * @param geometry A reference to a rectangle for the surface geometry on screen. Default the whole screen.
			 * @param depth A depth value to order surface on the screen. Default 0.0.
			 */
			AbstractSurface (const FramebufferProperties & framebufferProperties, const std::string & name, const Libs::Math::Rectangle< float > & geometry = {}, float depth = 0.0F) noexcept;

			/**
			 * @brief Updates the transformation matrix to place the surface on screen.
			 * @return void
			 */
			void setTransformationMatrix () noexcept;

			/**
			 * @brief Creates the descriptor set for this surface.
			 * @param renderer A reference to the graphics renderer.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool createDescriptorSet (Graphics::Renderer & renderer) noexcept = 0;

		private:

			/**
			 * @brief Event when the physical data is updating.
			 * @param renderer A reference to the graphics renderer.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool onPhysicalRepresentationUpdate (Graphics::Renderer & renderer) noexcept = 0;

			/**
			 * @brief Event when the video memory is updating.
			 * @param renderer A reference to the graphics renderer.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool onVideoMemoryUpdate (Graphics::Renderer & renderer) noexcept = 0;

			/* Flag names */
			static constexpr auto VideoMemoryUpdateRequested{0UL};
			static constexpr auto IsListeningKeyboard{1UL};
			static constexpr auto IsListeningPointer{2UL};
			static constexpr auto LockPointerMoveEvents{3UL};
			static constexpr auto IsPointerWasOver{4UL};
			static constexpr auto IsFocused{5UL};
			static constexpr auto IsOpaque{6UL};

			const FramebufferProperties & m_framebufferProperties;
			Libs::Math::Rectangle< float > m_rectangle;
			Libs::Math::Matrix< 4, float > m_transformationMatrix;
			float m_depth;
			std::array< bool, 8 > m_flags{
				true/*VideoMemoryUpdateRequested*/,
				false/*IsListeningKeyboard*/,
				false/*IsListeningPointer*/,
				false/*LockPointerMoveEvents*/,
				false/*IsPointerWasOver*/,
				false/*IsFocused*/,
				false/*IsOpaque*/,
				false/*IsAlphaTestEnabled*/
			};
	};
}
