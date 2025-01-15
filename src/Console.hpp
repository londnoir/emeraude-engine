/*
 * src/Console.hpp
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
#include <cstddef>
#include <map>
#include <memory>
#include <string>
#include <vector>

/* Local inclusions for inheritances. */
#include "Input/KeyboardListenerInterface.hpp"
#include "ServiceInterface.hpp"
#include "Libraries/Time/EventTrait.hpp"

/* Local inclusions for usages. */
#include "Libraries/BlobTrait.hpp"
#include "Types.hpp"

/* Forward declarations */
namespace Emeraude
{
	namespace Input
	{
		class Manager;
	}

	namespace Overlay
	{
		namespace Elements
		{
			class Text;
		}

		class Manager;
	}

	class PrimaryServices;
	class ConsoleControllable;
	class ConsoleExpression;
}

namespace Emeraude
{
	/**
	 * @brief The console service class.
	 * @extends Emeraude::ServiceInterface This is a service.
	 * @extends Emeraude::Input::KeyboardListenerInterface The console needs to check keyboard input.
	 * @extends Libraries::Time::EventTrait The console can create timer to delay some action.
	 */
	class Console final : public ServiceInterface, public Input::KeyboardListenerInterface, private Libraries::Time::EventTrait< uint32_t, std::milli >
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"ConsoleService"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs the console.
			 * @param primaryServices A reference to primary services.
			 * @param inputManager A reference to the input manager.
			 * @param overlayManager A reference to the overlay manager.
			 */
			Console (PrimaryServices & primaryServices, Input::Manager & inputManager, Overlay::Manager & overlayManager) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Console (const Console & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Console (Console && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return Console &
			 */
			Console & operator= (const Console & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return Console &
			 */
			Console & operator= (Console && copy) noexcept = delete;

			/**
			 * @brief Destructs the console.
			 */
			~Console () override;

			/** @copydoc Libraries::ObservableTrait::classUID() const */
			[[nodiscard]]
			size_t classUID () const noexcept override;

			/** @copydoc Libraries::ObservableTrait::is() const */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::ServiceInterface::usable() */
			[[nodiscard]]
			bool usable () const noexcept override;

			/**
			 * @brief Creates the graphical console.
			 * @return bool
			 */
			bool buildGUI () noexcept;

			/**
			 * @brief Enables the console.
			 */
			void enable () noexcept;

			/**
			 * @brief Disables the console.
			 */
			void disable () noexcept;

			/**
			 * @brief Adds a controllable object to the console.
			 * @param controllable A reference to the controllable object to add.
			 * @return bool
			 */
			bool add (ConsoleControllable & controllable) noexcept;

			/**
			 * @brief Removes a controllable object from the console using the identifier.
			 * @param identifier The identifier of the controllable object.
			 * @return bool
			 */
			bool remove (const std::string & identifier) noexcept;

			/**
			 * @brief Removes a controllable object from the console.
			 * @param pointer A reference to the controllable object to remove.
			 * @return bool
			 */
			bool remove (const ConsoleControllable & pointer) noexcept;

			/**
			 * @brief Executes a single command.
			 * @param command A reference to a string holding the raw command.
			 * @return bool
			 */
			[[nodiscard]]
			bool execute (const std::string & command) noexcept;

			/**
			 * @brief Writes to the console.
			 * @param message The message to write to the console.
			 * @param severity Changes the color of the text by using Tracer severity enum.
			 */
			void write (const std::string & message, Severity severity) const noexcept;

			/**
			 * @brief Writes to the console.
			 * @param message The message to write to the console using a blob.
			 * @param severity Changes the color of the text by using Tracer severity enum.
			 * @return void
			 */
			void
			write (const Libraries::BlobTrait & message, Severity severity = Severity::Info) noexcept
			{
				this->write(message.get(), severity);
			}

			/**
			 * @brief Returns the instance of the console.
			 * @return Console *
			 */
			[[nodiscard]]
			static
			Console * instance () noexcept;

			/**
			 * @brief Loop over object names.
			 * FIXME Checks this method, this should be non static.
			 * @param objects The list of register objects to the console.
			 * @param expression
			 * @param identifier
			 * @param suggestions A reference to a string list to set found suggestions.
			 * @return bool
			 */
			static bool loopOverObjectsName (const std::map< std::string, ConsoleControllable * > & objects, ConsoleExpression & expression, std::string & identifier, std::vector< std::string > & suggestions) noexcept;

		private:

			/** @copydoc Emeraude::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc Emeraude::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

			/** @copydoc Emeraude::Input::KeyboardListenerInterface::onKeyPress() */
			bool onKeyPress (int32_t key, int32_t scancode, int32_t modifiers, bool repeat) noexcept override;

			/** @copydoc Emeraude::Input::KeyboardListenerInterface::onKeyRelease() */
			bool onKeyRelease (int32_t key, int32_t scancode, int32_t modifiers) noexcept override;

			/** @copydoc Emeraude::Input::KeyboardListenerInterface::onCharacterType() */
			bool onCharacterType (uint32_t unicode) noexcept override;

			/** @brief Updates the input text after adding/removing char... */
			void updateInput () const noexcept;

			/** @brief Parses and executes the current console input. */
			void executeInput () noexcept;

			/** @brief Tries to guess the next term in the console input. */
			void completeInput () noexcept;

			/**
			 * @brief Checks and execute built-in console commands such as "help".
			 * @param command A reference to a string holding the raw command.
			 * @return bool
			 */
			[[nodiscard]]
			bool executeBuiltIn (const std::string & command) noexcept;

			static constexpr auto InputTextName = "Input";
			static constexpr auto OutputTextName = "Output";

			/* Flag names. */
			static constexpr auto ServiceInitialized{0UL};
			static constexpr auto DirectInputWasEnabled{1UL};
			static constexpr auto PointerWasLocked{2UL};

			static Console * s_instance;

			PrimaryServices & m_primaryServices;
			Input::Manager & m_inputManager;
			Overlay::Manager & m_overlayManager;
			std::map< std::string, ConsoleControllable * > m_consoleObjects;
			std::vector< std::string > m_commandsHistory;
			size_t m_historyOffset{0};
			std::string m_input;
			std::shared_ptr< Overlay::Elements::Text > m_inputText;
			std::shared_ptr< Overlay::Elements::Text > m_outputText;
			std::array< bool, 8 > m_flags{
				false/*ServiceInitialized*/,
				false/*DirectInputWasEnabled*/,
				false/*PointerWasLocked*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
