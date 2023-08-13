/*
 * Emeraude/Overlay/Surface.hpp
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
#include <array>

/* Local inclusions for usages. */
#include "Math/Vector.hpp"
#include "Math/Rectangle.hpp"
#include "PixelFactory/Pixmap.hpp"
#include "Layouts/Main.hpp"

/* Forward declaration */
namespace Emeraude
{
	namespace Graphics
	{
		namespace Geometry
		{
			class IndexedVertexResource;
		}

		class Program;
		class Renderer;
		class ImageResource;
	}

	namespace Vulkan
	{
		class Image;
	}
}

namespace Emeraude::Overlay
{
	/**
	 * @brief The base class of all overlay surfaces.
	 */
	class Surface
	{
		friend class Screen;

		public:

			enum class Position
			{
				Center,
				Bottom,
				Top,
				Left,
				Right,
				BottomLeft,
				BottomRight,
				TopLeft,
				TopRight
			};

			/** @brief Class identifier. */
			static constexpr auto ClassId{"UISurface"};

			/**
			 * @brief Constructs a surface.
			 * @param textureWidthProportion Texture coordinates multiplier for the width. Default 1.
			 * @param textureHeightProportion Texture coordinates multiplier for the height. Default 1.
			 */
			explicit Surface (float textureWidthProportion = 1.0F, float textureHeightProportion = 1.0F) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Surface (const Surface & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Surface (Surface && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return Surface &
			 */
			Surface & operator= (const Surface & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return Surface &
			 */
			Surface & operator= (Surface && copy) noexcept = delete;
			
			/**
			 * @brief Destructs the surface.
			 */
			virtual ~Surface () = default;

			/**
			 * @brief Sets the dimension of the surface.
			 * @note This implies a call to Surface::resize().
			 * @param width
			 * @param height
			 */
			virtual void setGeometry (float width, float height) noexcept final;

			/**
			 * @brief Integer version of the function that set the dimensions of the surface in pixels.
			 * @note This implies a call to Surface::resize().
			 * @param width
			 * @param height
			 */
			virtual void setGeometry (unsigned int width, unsigned int height) noexcept final;

			/**
			 * @brief Sets the lower left point of the surface on screen.
			 * @param x
			 * @param y
			 */
			virtual void setPosition (float x, float y) noexcept final;

			/**
			 * @brief Integer version of the function that set the lower left point of the surface on screen in pixels.
			 * @param x
			 * @param y
			 */
			virtual void setPosition (int x, int y) noexcept final;

			/**
			 * @brief Sets a predefined position for the surface on the screen.
			 * @param position
			 */
			virtual void setPosition (Position position) noexcept final;

			/**
			 * @brief rootLayout
			 * @return Layouts::Main &
			 */
			[[nodiscard]]
			virtual Layouts::Main & rootLayout () noexcept final;

			/**
			 * @brief rootLayout
			 * @return const Layouts::Main &
			 */
			[[nodiscard]]
			virtual const Layouts::Main & rootLayout () const noexcept final;

			/**
			 * @brief Returns a const reference to the pixmap of the surface.
			 * @return const Libraries::PixelFactory::Pixmap< uint8_t > &
			 */
			[[nodiscard]]
			virtual const Libraries::PixelFactory::Pixmap< uint8_t > & pixmap () const noexcept final;

			/**
			 * @brief Returns a reference to the pixmap of the surface.
			 * @return Libraries::PixelFactory::Pixmap< uint8_t > &
			 */
			[[nodiscard]]
			virtual Libraries::PixelFactory::Pixmap< uint8_t > & pixmap () noexcept final;

			/**
			 * @brief Marks the surface ready for a video memory update.
			 */
			virtual void drawFinished () noexcept final;

			/**
			 * @brief Returns the width in graphics API metrics of the surface.
			 * @return float
			 */
			[[nodiscard]]
			virtual float realWidth () const noexcept final;

			/**
			 * @brief Returns the height in graphics API metrics of the surface.
			 * @return float
			 */
			[[nodiscard]]
			virtual float realHeight () const noexcept final;

			/**
			 * @brief Returns the position of the left border of the surface in graphics API metrics on the screen.
			 * @return float
			 */
			[[nodiscard]]
			virtual float xOffset () const noexcept final;

			/**
			 * @brief Returns the position of the bottom border of the surface in graphics API metrics on the screen.
			 * @return float
			 */
			[[nodiscard]]
			virtual float yOffset () const noexcept final;

			/**
			 * @brief textureOffset
			 * @return const Libraries::Math::Vector< 2, float > &
			 */
			[[nodiscard]]
			virtual const Libraries::Math::Vector< 2, float > & textureOffset () const noexcept;

			/**
			 * @brief Checks if coordinates intersect the surface.
			 * @param x
			 * @param y
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isBelow (float x, float y) const noexcept final;

			/**
			 * @brief isCapturingPointerEvents
			 * @return bool
			 */
			[[nodiscard]]
			virtual
			inline
			bool
			isCapturingPointerEvents () const noexcept final
			{
				return m_flags[CapturePointerEvents];
			}

			/**
			 * @brief isCapturingKeyboardEvents
			 * @return bool
			 */
			[[nodiscard]]
			virtual
			inline
			bool
			isCapturingKeyboardEvents () const noexcept final
			{
				return m_flags[CaptureKeyboardEvents];
			}

			/**
			 * @brief isPointerOver
			 * @return bool
			 */
			[[nodiscard]]
			virtual
			inline
			bool
			isPointerOver () const noexcept final
			{
				return m_flags[IsPointerOver];
			}

			/**
			 * @brief isFocused
			 * @return bool
			 */
			[[nodiscard]]
			virtual
			inline
			bool
			isFocused () const noexcept final
			{
				return m_flags[IsFocused];
			}

			/**
			 * @brief Updates the video memory from the surface data
			 * @return bool
			 */
			virtual bool updateVideoMemory () noexcept final;

			/**
			 * @brief render
			 * @param renderer
			 * @param program
			 */
			virtual void render (Graphics::Renderer & renderer, const Graphics::Program & program) const noexcept final;

			/**
			 * @brief On key press event handler.
			 * @param key The keyboard universal key code.
			 * @param scanCode The system-dependent key code.
			 * @param modifiers The modifier keys mask.
			 * @param repeat Repeat state.
			 * @return void
			 */
			virtual void onKeyPress (int key, int scanCode, int modifiers, bool repeat) noexcept;

			/**
			 * @brief On key release event handler.
			 * @param key The keyboard universal key code.
			 * @param scanCode The system-dependent key code.
			 * @param modifiers The modifier keys mask.
			 * @return void
			 */
			virtual void onKeyRelease (int key, int scanCode, int modifiers) noexcept;

			/**
			 * @brief On character typing event handler.
			 * @param unicode The character unicode value.
			 * @param modifiers The modification keys state.
			 * @return void
			 */
			virtual void onCharacterType (unsigned int unicode, int modifiers) noexcept;

			/**
			 * @brief Method fired when pointer is entering the surface.
			 * @param x
			 * @param y
			 */
			virtual void onPointerEnter (float x, float y) noexcept;

			/**
			 * @brief Method fired when pointer is leaving the surface.
			 * @param x
			 * @param y
			 */
			virtual void onPointerLeave (float x, float y) noexcept;

			/**
			 * @brief Method fired when pointer is moving on the surface.
			 * @param x
			 * @param y
			 */
			virtual void onPointerMove (float x, float y) noexcept;

			/**
			 * @brief Method fired when a button of the pointer is pressed on the surface.
			 * @param x
			 * @param y
			 * @param buttonNumber
			 * @param mods
			 */
			virtual void onButtonPress (float x, float y, int buttonNumber, int mods) noexcept;

			/**
			 * @brief Method fired when a button of the pointer is released on the surface.
			 * @param x
			 * @param y
			 * @param buttonNumber
			 * @param mods
			 */
			virtual void onButtonRelease (float x, float y, int buttonNumber, int mods) noexcept;

			/**
			 * @brief Method fired when the mouse wheel is activated on the surface.
			 * @param x
			 * @param y
			 * @param xOffset
			 * @param yOffset
			 */
			virtual void onMouseWheel (float x, float y, float xOffset, float yOffset) noexcept;

		protected:

			/**
			 * @brief setCapturePointerEventsState
			 * @param state
			 */
			virtual
			inline
			void
			setCapturePointerEventsState (bool state) noexcept final
			{
				m_flags[CapturePointerEvents] = state;
			}

			/**
			 * @brief setCaptureKeyboardEventsState
			 * @param state
			 */
			virtual
			inline
			void
			setCaptureKeyboardEventsState (bool state) noexcept final
			{
				m_flags[CaptureKeyboardEvents] = state;
			}

			/**
			 * @brief setPointerOverState
			 * @param state
			 */
			virtual
			inline
			void
			setPointerOverState (bool state) noexcept final
			{
				m_flags[IsPointerOver] = state;
			}

			/**
			 * @brief setFocusedState
			 * @param state
			 */
			virtual
			inline
			void
			setFocusedState (bool state) noexcept final
			{
				m_flags[IsFocused] = state;
			}

			/**
			 * @brief setTextureOffsetX
			 * @param x
			 */
			virtual void setTextureOffsetX (float x) noexcept final;

			/**
			 * @brief setTextureOffsetY
			 * @param y
			 */
			virtual void setTextureOffsetY (float y) noexcept final;

			/**
			 * @brief setTextureOffset
			 * @param offset
			 */
			virtual void setTextureOffset (const Libraries::Math::Vector< 2, float > & offset) noexcept final;

			/**
			 * @brief This method it's called on first surface initialization and every time the geometry changes.
			 * @param pixmap
			 * @return bool
			 */
			virtual bool onResize (const Libraries::PixelFactory::Pixmap< uint8_t > & pixmap) noexcept;

			/**
			 * @brief Callback before Surface::drawFinished() function is executed.
			 * @note If returns false, the main function will abort.
			 * @param pixmap
			 * @return bool
			 */
			virtual bool onDrawFinished (Libraries::PixelFactory::Pixmap< uint8_t > & pixmap) noexcept;

		private:

			/**
			 * @brief Creates or update the vertex data of the surface.
			 * @return bool
			 */
			virtual bool updateGeometry () noexcept final;

			/**
			 * @brief Creates or update the texture of the surface.
			 * @param windowWidth
			 * @param windowHeight
			 * @return bool
			 */
			virtual bool updateTexture (float windowWidth, float windowHeight) noexcept final;

			/**
			 * @brief resize
			 * @param windowWidth
			 * @param windowHeight
			 * @return bool
			 */
			virtual bool resize (float windowWidth, float windowHeight) noexcept final;

			/* Flag names. */
			static constexpr auto CapturePointerEvents = 0UL;
			static constexpr auto CaptureKeyboardEvents = 1UL;
			static constexpr auto IsPointerOver = 2UL;
			static constexpr auto IsFocused = 3UL;

			Layouts::Main m_rootLayout{};
			Libraries::Math::Rectangle< float > m_rectangle{0.0F, 0.0F, 1.0F, 1.0F};
			std::unique_ptr< Graphics::Geometry::IndexedVertexResource > m_geometry{};
			std::shared_ptr< Vulkan::Image > m_texture{};
			Libraries::PixelFactory::Pixmap< uint8_t > m_data{};
			Libraries::Math::Vector< 2, float > m_textureProportion{1.0F, 1.0F};
			Libraries::Math::Vector< 2, float > m_textureOffset{};
			std::array< bool, 8 > m_flags{ // NOLINT(*-magic-numbers)
				false/*CapturePointerEvents*/,
				false/*CaptureKeyboardEvents*/,
				false/*IsPointerOver*/,
				false/*IsFocused*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
