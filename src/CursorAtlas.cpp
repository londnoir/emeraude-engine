#include "CursorAtlas.hpp"

/* Local inclusions. */
#include "Tracer.hpp"

namespace Emeraude
{
	using namespace Libraries;
	
	void
	CursorAtlas::setCursor (Window & window, CursorType cursorType) noexcept
	{
		auto cursorIt = m_standardCursors.find(cursorType);

		if ( cursorIt == m_standardCursors.end() )
		{
			switch ( cursorType )
			{
				case CursorType::Arrow :
					cursorIt = m_standardCursors.emplace(cursorType, glfwCreateStandardCursor(GLFW_ARROW_CURSOR)).first;
					break;

				case CursorType::TextInput :
					cursorIt = m_standardCursors.emplace(cursorType, glfwCreateStandardCursor(GLFW_IBEAM_CURSOR)).first;
					break;

				case CursorType::Crosshair :
					cursorIt = m_standardCursors.emplace(cursorType, glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR)).first;
					break;

				case CursorType::Hand :
					cursorIt = m_standardCursors.emplace(cursorType, glfwCreateStandardCursor(GLFW_HAND_CURSOR)).first;
					break;

				case CursorType::HorizontalResize :
					cursorIt = m_standardCursors.emplace(cursorType, glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR)).first;
					break;

				case CursorType::VerticalResize :
					cursorIt = m_standardCursors.emplace(cursorType, glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR)).first;
					break;
			}
		}

		glfwSetCursor(window.handle(), cursorIt->second);
	}

	void
	CursorAtlas::setCursor (Window & window, const std::string & label, const std::array< int, 2 > & size, unsigned char * data, const std::array< int, 2 > & hotSpot) noexcept
	{
		auto cursorIt = m_customCursors.find(label);

		if ( cursorIt == m_customCursors.end() )
		{
			const GLFWimage cursorImage{
				.width = size[0],
				.height = size[1],
				.pixels = data
			};

			cursorIt = m_customCursors.emplace(label, glfwCreateCursor(&cursorImage, hotSpot[0], hotSpot[1])).first;
		}

		glfwSetCursor(window.handle(), cursorIt->second);
	}

	void
	CursorAtlas::setCursor (Window & window, const std::string & label, PixelFactory::Pixmap< uint8_t > pixmap, const std::array< int, 2 > & hotSpot) noexcept
	{
		if ( pixmap.colorCount() != 4 )
		{
			TraceError{ClassId} << "A cursor needs a 4 channels image !";

			return;
		}

		auto cursorIt = m_customCursors.find(label);

		if ( cursorIt == m_customCursors.end() )
		{
			const GLFWimage cursorImage{
				.width = static_cast< int >(pixmap.width()),
				.height = static_cast< int >(pixmap.height()),
				.pixels = pixmap.pixelPointer(0)
			};

			cursorIt = m_customCursors.emplace(label, glfwCreateCursor(&cursorImage, hotSpot[0], hotSpot[1])).first;
		}

		glfwSetCursor(window.handle(), cursorIt->second);
	}

	void
	CursorAtlas::resetCursor (Window & window) noexcept
	{
		glfwSetCursor(window.handle(), nullptr);
	}

	void
	CursorAtlas::clear () noexcept
	{
		for ( const auto & cursorPair : m_standardCursors )
		{
			glfwDestroyCursor(cursorPair.second);
		}

		m_standardCursors.clear();

		for ( const auto & cursorPair : m_customCursors )
		{
			glfwDestroyCursor(cursorPair.second);
		}

		m_customCursors.clear();
	}
}
