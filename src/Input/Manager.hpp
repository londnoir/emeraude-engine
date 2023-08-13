/*
 * Emeraude/Input/Manager.hpp
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
#include <vector>
#include <array>

/* Third-Party */
#include "Third-Party-Inclusion/glfw.hpp"

/* Local inclusions for inheritances. */
#include "ServiceInterface.hpp"
#include "Observer.hpp"

/* Local inclusions for usage */
#include "KeyboardListenerInterface.hpp"
#include "PointerListenerInterface.hpp"

/* Forward declarations. */
namespace Emeraude
{
	class Arguments;
	class FileSystem;
	class Settings;
	class Window;
}

namespace Emeraude::Input
{
	/**
	 * @brief The input manager service class.
	 * @extends Emeraude::ServiceInterface This is a service.
	 * @extends Libraries::Observer
	 */
	class Manager final : public ServiceInterface, public Libraries::Observer
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"InputManagerService"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/** @brief Observable notification codes. */
			enum NotificationCode
			{
				DroppedFiles,
				/* Enumeration boundary. */
				MaxEnum
			};

			/**
			 * @brief Constructs the input manager.
			 * @param arguments A reference to Arguments.
			 * @param fileSystem A reference to the file system.
			 * @param coreSettings A reference to the core settings.
			 * @param window A reference to the handle.
			 */
			Manager (const Arguments & arguments, const FileSystem & fileSystem, Settings & coreSettings, Window & window) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Manager (const Manager & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Manager (Manager && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			Manager & operator= (const Manager & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			Manager & operator= (Manager && copy) noexcept = delete;

			/**
			 * @brief Destructs the resource manager.
			 */
			~Manager () override;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::ServiceInterface::usable() */
			[[nodiscard]]
			bool usable () const noexcept override;

			/**
			 * @brief Enables/Disables the keyboard.
			 * @param state The state of the keyboard.
			 * @return void
			 */
			void enableKeyboard (bool state) noexcept;

			/**
			 * @brief Toggles the state of the keyboard.
			 * @return void
			 */
			void toggleKeyboardState () noexcept;

			/**
			 * @brief Returns whether the manager is listening to keyboard input
			 * @return bool
			 */
			[[nodiscard]]
			bool isKeyboardEnabled () const noexcept;

			/**
			 * @brief Enables/Disables the pointer.
			 * @param state The state of the pointer.
			 * @return void
			 */
			void enablePointer (bool state) noexcept;

			/**
			 * @brief Toggles the state of the pointer.
			 * @return void
			 */
			void togglePointerState () noexcept;

			/**
			 * @brief Returns whether the manager is listening to pointer input.
			 * @return bool
			 */
			[[nodiscard]]
			bool isPointerEnabled () const noexcept;

			/**
			 * @brief Hides mouse cursor and manager will serve only PointerListeners in relative mode.
			 * @return void
			 */
			void lockPointer () noexcept;

			/**
			 * @brief Shows mouse cursor and manager will serve only PointerListeners in absolute mode.
			 * @return void
			 */
			void unlockPointer () noexcept;

			/**
			 * @brief Returns whether the pointer is locked on screen (FPS mode).
			 * @return bool
			 */
			[[nodiscard]]
			bool isPointerLocked () const noexcept;

			/**
			 * @brief Enables the GLFW text function with modifiers.
			 * @param state The state.
			 * @return void
			 */
			void enableModifiersWithText (bool state) noexcept;

			/**
			 * @brief Returns whether the modifiers are enabled with text function.
			 * @return bool
			 */
			[[nodiscard]]
			bool isModifiersWithTextEnabled () const noexcept;

			/**
			 * @brief Gets events from the system.
			 * @return void
			 */
			void pollSystemEvents () noexcept;

			/**
			 * @brief Waits for a system event.
			 * @param until Sets a duration until the cancellation of the waiting.
			 * @return void
			 */
			void waitSystemEvents (double until = 0.0) noexcept;

			/**
			 * @brief Adds an object the keyboard can control, like a player.
			 * @param listener A pointer to a keyboard listener interfaced object.
			 * @return void
			 */
			void addKeyboardListener (KeyboardListenerInterface * listener) noexcept;

			/**
			 * @brief Removes an object of keyboard listeners.
			 * @param listener A pointer to a keyboard listener interfaced object.
			 * @return void
			 */
			void removeKeyboardListener (KeyboardListenerInterface * listener) noexcept;

			/**
			 * @brief Clears all keyboard listeners.
			 * @return void
			 */
			void removeAllKeyboardListeners () noexcept;

			/**
			 * @brief Adds an object the pointer can control, like a player.
			 * @param listener A pointer to a pointer listener interfaced object.
			 * @return void
			 */
			void addPointerListener (PointerListenerInterface * listener) noexcept;

			/**
			 * @brief Removes an object of pointer listeners.
			 * @param listener A pointer to a pointer listener interfaced object.
			 * @return void
			 */
			void removePointerListener (PointerListenerInterface * listener) noexcept;

			/**
			 * @brief Clears all pointer listeners.
			 * @return void
			 */
			void removeAllPointerListeners () noexcept;

			/**
			 * @brief Updates every input devices state by copying their states.
			 * @return void
			 */
			void getInputsState () noexcept;

			/**
			 * @brief Enables or disable direct input state queries.
			 * @param state The state of direct query.
			 * @return void
			 */
			void enableDirectQuery (bool state) noexcept;

			/**
			 * @brief Returns whether the direct query is enabled or not.
			 * @return bool
			 */
			[[nodiscard]]
			bool isDirectQueryEnabled () const noexcept;

			/**
			 * @brief Returns the instance of the input manager.
			 * @return Manager *
			 */
			[[nodiscard]]
			static
			Manager * instance () noexcept;

		private:

			/** @copydoc Emeraude::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc Emeraude::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

			/** @copydoc Libraries::Observer::onNotification() */
			[[nodiscard]]
			bool onNotification (const Libraries::Observable * observable, int notificationCode, const std::any & data) noexcept override;

			/**
			 * @brief Main method to attach all events callback from a glfw handle.
			 * @param window The glfw handle handle.
			 * @param state The state of link.
			 * @return void
			 */
			void setWindowLink (GLFWwindow * window, bool state) noexcept;

			/**
			 * @brief The callback for the glfw API to handle key inputs.
			 * @param window The glfw handle handle.
			 * @param key The keyboard universal key code.
			 * @param scanCode The system-dependent key code.
			 * @param action The key event.
			 * @param modifiers The modifier keys mask.
			 * @return void
			 */
			static void keyCallback (GLFWwindow * window, int key, int scancode, int action, int modifiers) noexcept;

			/**
			 * @brief The callback for the glfw API to handle character inputs.
			 * @param window The glfw handle handle.
			 * @param codepoint The unicode value of the character.
			 * @return void
			 */
			static void charCallback (GLFWwindow * window, unsigned int codepoint) noexcept;

			/**
			 * @brief The callback for the glfw API to handle character modification inputs.
			 * @param window The glfw handle handle.
			 * @param codepoint The unicode value of the character.
			 * @param modifiers The modifier keys mask.
			 * @return void
			 */
			static void charModsCallback (GLFWwindow * window, unsigned int codepoint, int modifiers) noexcept;

			/**
			 * @brief The callback for the glfw API to handle cursor position changes.
			 * @param window The glfw handle handle.
			 * @param xPosition The X position of the cursor.
			 * @param yPosition The Y position of the cursor.
			 * @return void
			 */
			static void cursorPositionCallback (GLFWwindow * window, double xPosition, double yPosition) noexcept;

			/**
			 * @brief The callback for the glfw API to handle cursor enter the handle.
			 * @param window The glfw handle handle.
			 * @param entered The state of the cursor.
			 * @return void
			 */
			static void cursorEnterCallback (GLFWwindow * window, int entered) noexcept;

			/**
			 * @brief The callback for the glfw API to handle cursor button inputs.
			 * @param window The glfw handle handle.
			 * @param button
			 * @param action
			 * @param modifiers The modifier keys mask.
			 * @return void
			 */
			static void mouseButtonCallback (GLFWwindow * window, int button, int action, int modifiers) noexcept;

			/**
			 * @brief The callback for the glfw API to handle scroll state changes.
			 * @param window The glfw handle handle.
			 * @param xOffset
			 * @param yOffset
			 * @return void
			 */
			static void scrollCallback (GLFWwindow * window, double xOffset, double yOffset) noexcept;

			/**
			 * @brief The callback for the glfw API to handle file dropped in the handle.
			 * @param window The glfw handle handle.
			 * @param count
			 * @param paths
			 * @return void
			 */
			static void dropCallback (GLFWwindow * window, int count, const char * * paths) noexcept;

			/**
			 * @brief The callback for the glfw API to handle joystick inputs.
			 * @param jid The joystick id.
			 * @param event
			 * @return void
			 */
			static void joystickCallback (int jid, int event) noexcept;

			/* Flag names. */
			static constexpr auto WindowLinked = 0UL;
			static constexpr auto KeyboardEnabled = 1UL;
			static constexpr auto PointerEnabled = 2UL;
			static constexpr auto PointerLocked = 3UL;
			static constexpr auto EnableModifiersWithText = 4UL;
			static constexpr auto DirectQueryEnabled = 5UL;

			static constexpr auto GameControllersFile = "gamecontrollerdb.txt";

			static Manager * s_instance; // NOLINT NOTE: Singleton behavior

			// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members) NOTE: Services inter-connexions.
			const Arguments & m_arguments;
			const FileSystem & m_fileSystem;
			Settings & m_coreSettings;
			Window & m_window;
			// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members) NOTE: Services inter-connexions.
			std::vector< KeyboardListenerInterface * > m_keyboardListeners{};
			std::vector< PointerListenerInterface * > m_pointerListeners{};
			std::set< int > m_joystickID{};
			std::set< int > m_gamepadID{};
			std::array< bool, 8 > m_flags{ // NOLINT(*-magic-numbers)
				false/*WindowLinked*/,
				true/*KeyboardEnabled*/,
				true/*PointerEnabled*/,
				false/*PointerLocked*/,
				true/*EnableModifiersWithText*/,
				true/*DirectQueryEnabled*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
