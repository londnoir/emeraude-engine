#pragma once

/* STL inclusions. */
#include <string>
#include <map>
#include <memory>
#include <array>

/* Third-party inclusions. */
#include "GLFW/glfw3.h"

/* Local inclusions for usages. */
#include "Window.hpp"
#include "Graphics/ImageResource.hpp"
#include "Types.hpp"

namespace Emeraude
{
	/**
	 * @brief The cursor atlas holds all pointer representation for the application.
	 */
	class CursorAtlas final
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"CursorAtlas"};

			/** 
			 * @brief Constructs the cursor atlas.
			 */
			CursorAtlas () noexcept = default;

			/**
			 * @brief Changes the cursor representation on screen with a standard type.
			 * @param window A reference to the window where to change the cursor.
			 * @param cursorType The type of the cursor.
			 * @return void
			 */
			void setCursor (Window & window, CursorType cursorType) noexcept;

			/**
			 * @brief Changes the cursor representation on screen with a pixmap.
			 * @param window A reference to the window where to change the cursor.
			 * @param label A reference to a string.
			 * @param pixmap A reference to a pixmap.
			 * @param hotSpot A reference to an array of 2 integers. Default X:0, Y:0.
			 * @return void
			 */
			void setCursor (Window & window, const std::string & label, Libraries::PixelFactory::Pixmap< uint8_t > pixmap, const std::array< int, 2 > & hotSpot = {0, 0}) noexcept;

			/**
			 * @brief Changes the cursor representation on screen with a pixmap.
			 * @warning Raw mode to fit the GLFW basic needs. This is not the recommended version.
			 * @param window A reference to the window where to change the cursor.
			 * @param label A reference to a string.
			 * @param size A reference to an array of 2 integers.
			 * @param data A pointer to an uint8_t buffer. It must contain (width X height X 4) elements.
			 * @param hotSpot A reference to an array of 2 integers. Default X:0, Y:0.
			 * @return void
			 */
			void setCursor (Window & window, const std::string & label, const std::array< int, 2 > & size, unsigned char * data, const std::array< int, 2 > & hotSpot = {0, 0}) noexcept;

			/**
			 * @brief Changes the cursor representation on screen with an image resource.
			 * @param window A reference to the window where to change the cursor.
			 * @param imageResource A reference to an image resource smart pointer.
			 * @param hotSpot A reference to an array of 2 integers. Default X:0, Y:0.
			 * @return void
			 */
			void
			setCursor (Window & window, const std::shared_ptr< Graphics::ImageResource > & imageResource, const std::array< int, 2 > & hotSpot = {0, 0}) noexcept
			{
				if ( !imageResource->isLoaded() )
				{
					return;
				}

				this->setCursor(window, imageResource->name(), imageResource->data(), hotSpot);
			}

			/**
			 * @brief Reset back the cursor to default representation.
			 * @param window A reference to the window where to reset the cursor.
			 * @return void
			 */
			void resetCursor (Window & window) noexcept;

			/**
			 * @brief Removes all cursor from the atlas.
			 * @return void
			 */
			void clear () noexcept;

		private:

			std::map< CursorType, GLFWcursor * > m_standardCursors;
			std::map< std::string, GLFWcursor * > m_customCursors;
	};
}
