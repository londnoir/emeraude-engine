/*
 * Emeraude/Input/Manager.cpp
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

#include "Manager.hpp"

/* C/C++ standard libraries. */
#include <iostream>
#include <algorithm>

/* Local inclusions */
#include "Tracer.hpp"
#include "Arguments.hpp"
#include "FileSystem.hpp"
#include "Settings.hpp"
#include "Window.hpp"
#include "Path/File.hpp"
#include "KeyboardController.hpp"
#include "PointerController.hpp"
#include "JoystickController.hpp"
#include "GamepadController.hpp"

namespace Emeraude::Input
{
	using namespace Libraries;
	using namespace Vulkan;

	const size_t Manager::ClassUID{Observable::getClassUID()};
	Manager * Manager::s_instance{nullptr}; // NOLINT NOTE: Singleton behavior

	Manager::Manager (const Arguments & arguments, const FileSystem & fileSystem, Settings & coreSettings, Window & window) noexcept
		: ServiceInterface(ClassId), m_arguments(arguments), m_fileSystem(fileSystem), m_coreSettings(coreSettings), m_window(window)
	{
		if ( s_instance != nullptr )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", constructor called twice !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

			std::terminate();
		}

		s_instance = this;

		this->observe(&m_window);
	}

	Manager::~Manager ()
	{
		s_instance = nullptr;
	}

	Manager *
	Manager::instance () noexcept
	{
		return s_instance;
	}

	bool
	Manager::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	void
	Manager::enableDirectQuery (bool state) noexcept
	{
		m_flags[DirectQueryEnabled] = state;
	}

	bool
	Manager::isDirectQueryEnabled () const noexcept
	{
		return m_flags[DirectQueryEnabled];
	}

	void
	Manager::keyCallback (GLFWwindow * /*handle*/, int key, int scancode, int action, int modifiers) noexcept
	{
#ifdef DEBUG_INPUT_LAYER
		std::cout << "Keyboard input detected ! Key:" << key << ", ScanCode:" << scancode << ", action: " << action << ", modifiers:" << modifiers << "\n";
#endif

		if ( !s_instance->isKeyboardEnabled() )
		{
			return;
		}

		for ( auto & listener : s_instance->m_keyboardListeners )
		{
			auto processed = false;

			switch ( action )
			{
				case GLFW_PRESS :
					processed = listener->onKeyPress(key, scancode, modifiers, false);
					break;

				case GLFW_REPEAT :
					processed = listener->onKeyPress(key, scancode, modifiers, true);
					break;

				case GLFW_RELEASE :
					processed = listener->onKeyRelease(key, scancode, modifiers);
					break;

				default:
					break;
			}

			/* If this listener captures events, we stop the loop. */
			if ( processed && listener->isOpaque() )
			{
				break;
			}
		}
	}

	void
	Manager::charCallback (GLFWwindow * /*handle*/, unsigned int codepoint) noexcept
	{
#ifdef DEBUG_INPUT_LAYER
		std::cout << "Unicode input detected ! Unicode:" << codepoint << "\n";
#endif

		if ( !s_instance->isKeyboardEnabled() )
		{
			return;
		}

		for ( auto & listener : s_instance->m_keyboardListeners )
		{
			if ( !listener->isTextModeEnabled() )
			{
				continue;
			}

			/* If this listener captures events, we stop the loop. */
			if ( listener->onCharacterType(codepoint, 0) && listener->isOpaque() )
			{
				break;
			}
		}
	}

	void
	Manager::charModsCallback (GLFWwindow * /*handle*/, unsigned int codepoint, int modifiers) noexcept
	{
#ifdef DEBUG_INPUT_LAYER
		std::cout << "Unicode input detected ! Unicode:" << codepoint << ", modifiers:" << modifiers << "\n";
#endif

		if ( !s_instance->isKeyboardEnabled() )
		{
			return;
		}

		for ( auto & listener : s_instance->m_keyboardListeners )
		{
			if ( !listener->isTextModeEnabled() )
			{
				continue;
			}

			/* If this listener captures events, we stop the loop. */
			if ( listener->onCharacterType(codepoint, modifiers) && listener->isOpaque() )
			{
				break;
			}
		}
	}

	void
	Manager::cursorPositionCallback (GLFWwindow * window, double xPosition, double yPosition) noexcept
	{
		if ( !s_instance->isPointerEnabled() )
		{
			return;
		}

		const auto pointerX = static_cast< float >(xPosition);
		const auto pointerY = static_cast< float >(yPosition);

		/* If the mouse is used to look in 3D world. */
		if ( s_instance->isPointerLocked() )
		{
			int width = 0;
			int height = 0;

			/* FIXME: check with https://www.glfw.org/docs/latest/input_guide.html#cursor_mode */
			glfwGetWindowSize(window, &width, &height);

			const auto halfWidth = static_cast< float >(width) * 0.5F;
			const auto halfHeight = static_cast< float >(height) * 0.5F;

			for ( auto & listener : s_instance->m_pointerListeners )
			{
				if ( listener->isAbsoluteModeEnabled() )
				{
					continue;
				}

				/* If this listener captures events, we stop the loop. */
				if ( listener->onPointerMove(pointerX - halfWidth, pointerY - halfHeight) && listener->isOpaque() )
				{
					break;
				}
			}

			/* Recenter the pointer in the middle of the screen. */
			{
				/* We don't want process any pointer move during the centering. */
				auto previousPointerState = s_instance->isPointerEnabled();

				s_instance->enablePointer(false);

				glfwSetCursorPos(window, static_cast< double >(halfWidth),static_cast< double >(halfHeight));

				/* Gets back the pointer to previous state. */
				s_instance->enablePointer(previousPointerState);
			}
		}
		else
		{
			for ( auto & listener : s_instance->m_pointerListeners )
			{
				if ( !listener->isAbsoluteModeEnabled() )
				{
					continue;
				}

				/* If this listener captures events, we stop the loop. */
				if ( listener->onPointerMove(pointerX, pointerY) && listener->isOpaque() )
				{
					break;
				}
			}
		}
	}

	void
	Manager::cursorEnterCallback (GLFWwindow * window, int entered) noexcept
	{
#ifdef DEBUG_INPUT_LAYER
		std::cout << "Mouse " << ( entered ? "entering" : "leaving" ) << " the handle !" << "\n";
#endif

		if ( !s_instance->isPointerEnabled() )
		{
			return;
		}

		double xPosition = 0.0;
		double yPosition = 0.0;

		glfwGetCursorPos(window, &xPosition, &yPosition);

		const auto pointerX = static_cast< float >(xPosition);
		const auto pointerY = static_cast< float >(yPosition);

		for ( auto & listener : s_instance->m_pointerListeners )
		{
			auto isProcessed = ( entered == GLFW_TRUE ) ?
				listener->onPointerEnter(pointerX, pointerY) :
				listener->onPointerLeave(pointerX, pointerY);

			/* If this listener captures events, we stop the loop. */
			if ( isProcessed && listener->isOpaque() )
			{
				break;
			}
		}
	}

	void
	Manager::mouseButtonCallback (GLFWwindow * window, int button, int action, int modifiers) noexcept
	{
#ifdef DEBUG_INPUT_LAYER
		std::cout << "Mouse input detected ! Button:" << button << ", Action:" << action << ", modifiers:" << modifiers << "\n";
#endif

		if ( !s_instance->isPointerEnabled() )
		{
			return;
		}

		double xPosition = 0.0;
		double yPosition = 0.0;

		glfwGetCursorPos(window, &xPosition, &yPosition);

		const auto pointerX = static_cast< float >(xPosition);
		const auto pointerY = static_cast< float >(yPosition);

		for ( auto & listener : s_instance->m_pointerListeners )
		{
			auto isProcessed = ( action == GLFW_PRESS ) ?
					listener->onButtonPress(pointerX, pointerY, button, modifiers) :
					listener->onButtonRelease(pointerX, pointerY, button, modifiers);

			/* If this listener captures events, we stop the loop. */
			if ( isProcessed && listener->isOpaque() )
			{
				break;
			}
		}
	}

	void
	Manager::scrollCallback (GLFWwindow * window, double xOffset, double yOffset) noexcept
	{
#ifdef DEBUG_INPUT_LAYER
		std::cout << "Mouse scrolling detected ! X:" << xOffset << ", Y:" << yOffset << "\n";
#endif

		if ( !s_instance->isPointerEnabled() )
		{
			return;
		}

		double xPosition = 0.0;
		double yPosition = 0.0;

		glfwGetCursorPos(window, &xPosition, &yPosition);

		const auto pointerX = static_cast< float >(xPosition);
		const auto pointerY = static_cast< float >(yPosition);

		const auto sXOffset = static_cast< float >(xOffset);
		const auto sYOffset = static_cast< float >(yOffset);

		for ( auto & listener : s_instance->m_pointerListeners )
		{
			/* If this listener captures events, we stop the loop. */
			if ( listener->onMouseWheel(pointerX, pointerY, sXOffset, sYOffset) && listener->isOpaque() )
			{
				return;
			}
		}
	}

	void
	Manager::dropCallback (GLFWwindow * /*handle*/, int count, const char * * paths) noexcept
	{
		std::vector< Path::File > filePaths{};
		filePaths.reserve(count);

		for ( auto i = 0; i < count; i++ )
		{
			const std::string path{paths[i]}; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
			const Path::File filepath{path};

			if ( !filepath.exists() )
			{
				TraceError{ClassId} << "File '" << path << "' doesn't exists !";

				continue;
			}

			filePaths.emplace_back(filepath);
		}

		s_instance->notify(DroppedFiles, filePaths);
	}

	void
	Manager::joystickCallback (int jid, int event) noexcept
	{
		switch ( event )
		{
			case GLFW_CONNECTED :
				if ( glfwJoystickIsGamepad(jid) == GLFW_TRUE )
				{
					TraceInfo{ClassId} << "Gamepad '" << glfwGetGamepadName(jid) << "' (GUID:" <<  glfwGetJoystickGUID(jid) << ") connected at slot #" << jid << " !";

					s_instance->m_gamepadID.emplace(jid);
				}
				else
				{
					TraceInfo{ClassId} << "Joystick '" << glfwGetJoystickName(jid) << "' (GUID:" <<  glfwGetJoystickGUID(jid) << ") connected at slot #" << jid << " !";

					s_instance->m_joystickID.emplace(jid);
				}
				break;

			case GLFW_DISCONNECTED :
			{
				TraceInfo{ClassId} << "Game device #" << jid << " disconnected !";

				/* NOTE: Here we don't know if it's a joystick or a gamepad.
				 * But we don't care a bit because ID are shared between gamepads and joysticks. */

				/* First we reset the device last state. */
				JoystickController::clearDeviceState(jid);
				GamepadController::clearDeviceState(jid);

				/* We remove the ID from both ID set. */
				s_instance->m_joystickID.erase(jid);
				s_instance->m_gamepadID.erase(jid);
			}
				break;

			default :
				break;
		}
	}

	void
	Manager::setWindowLink (GLFWwindow * window, bool state) noexcept
	{
		glfwSetKeyCallback(window, state ? keyCallback : nullptr);
		if ( m_flags[EnableModifiersWithText] )
		{
			glfwSetCharModsCallback(window, state ? charModsCallback : nullptr);
		}
		else
		{
			glfwSetCharCallback(window, state ? charCallback : nullptr);
		}
		glfwSetMouseButtonCallback(window, state ? mouseButtonCallback : nullptr);
		glfwSetCursorPosCallback(window, state ? cursorPositionCallback : nullptr);
		glfwSetCursorEnterCallback(window, state ? cursorEnterCallback : nullptr);
		glfwSetScrollCallback(window, state ? scrollCallback : nullptr);
		glfwSetDropCallback(window, state ? dropCallback : nullptr);
		glfwSetJoystickCallback(state ? joystickCallback : nullptr);

		m_flags[WindowLinked] = state;

		glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
		glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
	}

	bool
	Manager::onNotification (const Observable * observable, int notificationCode, const std::any & /*data*/) noexcept
	{
		if ( observable == &m_window )
		{
			switch ( notificationCode )
			{
				case Window::Created :
					if ( m_window.usable() )
					{
						Tracer::success(ClassId, "InputManager linked to the current Window for events callbacks !");

						this->setWindowLink(m_window.handle(), true);
					}
					else
					{
						Tracer::error(ClassId, "Try to link InputManager linked to a nullptr Window !");
					}
					break;

				case Window::Destroyed :
				case Window::Centered :
				case Window::OSNotifiesWindowGetFocus :
				case Window::OSNotifiesWindowLostFocus :
				case Window::OSNotifiesWindowMovedTo :
				case Window::OSNotifiesWindowVisible :
				case Window::OSNotifiesWindowHidden :
				case Window::OSNotifiesWindowSizeMaximized :
				case Window::OSNotifiesWindowSizeMinimized :
				case Window::OSNotifiesWindowResized :
				case Window::OSNotifiesFramebufferResized :
				case Window::OSRequestsToRescaleContentBy :
				case Window::OSRequestsToRefreshContent :
				case Window::OSRequestsToTerminate :
				default :
					TraceDebug{ClassId} << "Event #" << notificationCode << " from the window ignored.";
					break;
			}

			return true;
		}

#ifdef DEBUG
		/* NOTE: Don't know what is it, goodbye ! */
		TraceInfo{ClassId} <<
			"Received an unhandled event from observable @" << observable << " (code:" << notificationCode << ") ! "
			"Forgetting it ...";
#endif

		return false;
	}

	void
	Manager::enableKeyboard (bool state) noexcept
	{
		m_flags[KeyboardEnabled] = state;
	}

	void
	Manager::toggleKeyboardState () noexcept
	{
		m_flags[KeyboardEnabled] = !m_flags[KeyboardEnabled];
	}

	bool
	Manager::isKeyboardEnabled () const noexcept
	{
		return m_flags[KeyboardEnabled];
	}


	void
	Manager::enablePointer (bool state) noexcept
	{
		m_flags[PointerEnabled] = state;
	}

	bool
	Manager::isPointerEnabled () const noexcept
	{
		return m_flags[PointerEnabled];
	}

	void
	Manager::togglePointerState () noexcept
	{
		m_flags[PointerEnabled] = !m_flags[PointerEnabled];
	}

	bool
	Manager::usable () const noexcept
	{
		return m_window.usable();
	}

	bool
	Manager::isPointerLocked () const noexcept
	{
		return m_flags[PointerLocked];
	}

	bool
	Manager::onInitialize () noexcept
	{
		if ( !m_window.usable() )
		{
			Tracer::error(ClassId, "No handle available, cannot link input listeners !");

			return false;
		}

		this->setWindowLink(m_window.handle(), true);

		/* Update gamepad database. */
		std::string devicesDatabase{};

		const auto & list = m_fileSystem.dataDirectoriesList();

		for ( const auto & path : list )
		{
			const auto filepath = Path::File{path, GameControllersFile};

			if ( !filepath.exists() )
			{
				TraceInfo{ClassId} << "The file '" << filepath << "' is not present !";

				continue;
			}

			if ( !Utility::fileGetContents(filepath, devicesDatabase) )
			{
				TraceError{ClassId} << "Unable to read '" << filepath << "' !";

				continue;
			}

			if ( glfwUpdateGamepadMappings(devicesDatabase.c_str()) == GLFW_FALSE )
			{
				TraceError{ClassId} << "Update input devices from '" << filepath << "' failed !";

				continue;
			}

			TraceSuccess{ClassId} << "Update input devices from '" << filepath << "' succeed !";
		}

		if ( devicesDatabase.empty() )
		{
			TraceWarning{ClassId} << "There was no '" << GameControllersFile << "' file available !";
		}

		/* Checks every device connected. */
		for ( int jid = 0; jid <= GLFW_JOYSTICK_LAST; jid++ )
		{
			/* Checks if a device is present. */
			if ( glfwJoystickPresent(jid) == GLFW_FALSE )
			{
				continue;
			}

			/* If present, determine if it's a gamepad or a joystick. */
			if ( glfwJoystickIsGamepad(jid) == GLFW_TRUE )
			{
				m_gamepadID.emplace(jid);

				TraceSuccess{ClassId} << "Gamepad '" << glfwGetGamepadName(jid) << "' (GUID:" <<  glfwGetJoystickGUID(jid) << ") available at slot #" << jid;
			}
			else
			{
				m_joystickID.emplace(jid);

				TraceSuccess{ClassId} << "Joystick '" << glfwGetJoystickName(jid) << "' (GUID:" <<  glfwGetJoystickGUID(jid) << ") available at slot #" << jid;
			}
		}

		return true;
	}

	bool
	Manager::onTerminate () noexcept
	{
		if ( m_window.usable() )
		{
			/* Disables every callback. */
			this->setWindowLink(m_window.handle(), false);
		}
		else
		{
			Tracer::warning(ClassId, "No handle was available !");

			return false;
		}

		return true;
	}

	void
	Manager::pollSystemEvents () noexcept // NOLINT(*-convert-member-functions-to-static)
	{
		glfwPollEvents();
	}

	void
	Manager::waitSystemEvents (double until) noexcept // NOLINT(*-convert-member-functions-to-static)
	{
		/* This function is blocking the
		 * process by waiting an event from system. */
		if ( until > 0.0 )
		{
			glfwWaitEventsTimeout(until);
		}
		else
		{
			glfwWaitEvents();
		}
	}

	void
	Manager::addKeyboardListener (KeyboardListenerInterface * listener) noexcept
	{
		if ( std::binary_search(m_keyboardListeners.cbegin(), m_keyboardListeners.cend(), listener) )
		{
			TraceInfo{ClassId} << "Listener @" << listener << " already added !";

			return;
		}

		Tracer::info(ClassId, "Keyboard input listener registered.");

		m_keyboardListeners.emplace(m_keyboardListeners.begin(), listener);
	}

	void
	Manager::removeKeyboardListener (KeyboardListenerInterface * listener) noexcept
	{
		m_keyboardListeners.erase(std::remove(m_keyboardListeners.begin(), m_keyboardListeners.end(), listener), m_keyboardListeners.end());
	}

	void
	Manager::removeAllKeyboardListeners () noexcept
	{
		m_keyboardListeners.clear();
	}

	void
	Manager::addPointerListener (PointerListenerInterface * listener) noexcept
	{
		if ( std::binary_search(m_pointerListeners.cbegin(), m_pointerListeners.cend(), listener) )
		{
			TraceInfo{ClassId} << "Listener @" << listener << " already added !";

			return;
		}

		Tracer::info(ClassId, "Pointer input listener registered.");

		m_pointerListeners.emplace(m_pointerListeners.begin(), listener);
	}

	void
	Manager::removePointerListener (PointerListenerInterface * listener) noexcept
	{
		m_pointerListeners.erase(std::remove(m_pointerListeners.begin(), m_pointerListeners.end(), listener), m_pointerListeners.end());
	}

	void
	Manager::removeAllPointerListeners () noexcept
	{
		m_pointerListeners.clear();
	}

	void
	Manager::getInputsState () noexcept
	{
		if ( !m_flags[DirectQueryEnabled] )
		{
			return;
		}

		auto * window = m_window.handle();

		KeyboardController::readDeviceState(window);

		PointerController::readDeviceState(window);

		for ( const auto & joystickID : m_joystickID )
		{
			JoystickController::readDeviceState(window, joystickID);
		}
		for ( const auto & joystickID : m_gamepadID )
		{
			GamepadController::readDeviceState(window, joystickID);
		}
	}

	void
	Manager::lockPointer () noexcept
	{
		auto * window = m_window.handle();

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		if ( glfwRawMouseMotionSupported() == GLFW_TRUE )
		{
			glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		}

		m_flags[PointerLocked] = true;
	}

	void
	Manager::unlockPointer () noexcept
	{
		auto * window = m_window.handle();

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		if ( glfwRawMouseMotionSupported() == GLFW_TRUE )
		{
			glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
		}

		m_flags[PointerLocked] = false;
	}

	void
	Manager::enableModifiersWithText (bool state) noexcept
	{
		m_flags[EnableModifiersWithText] = state;

		if ( m_flags[WindowLinked] )
		{
			auto * window = m_window.handle();

			if ( this->isModifiersWithTextEnabled() )
			{
				glfwSetCharCallback(window, nullptr);
				glfwSetCharModsCallback(window, charModsCallback);

			}
			else
			{
				glfwSetCharCallback(window, charCallback);
				glfwSetCharModsCallback(window, nullptr);
			}
		}
	}

	bool
	Manager::isModifiersWithTextEnabled () const noexcept
	{
		return m_flags[EnableModifiersWithText];
	}
}
