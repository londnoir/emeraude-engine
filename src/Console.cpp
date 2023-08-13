/*
 * Emeraude/Console.cpp
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

#include "Console.hpp"

/* C/C++ standard libraries. */
#include <chrono>
#include <future>
#include <iostream>

/* Local inclusions */
#include "Arguments.hpp"
#include "ConsoleControllable.hpp"
#include "FileSystem.hpp"
#include "Graphics/Geometry/IndexedVertexResource.hpp"
#include "Graphics/ImageResource.hpp"
#include "Input/KeyboardController.hpp"
#include "Input/Manager.hpp"
#include "Overlay/Elements/Picture.hpp"
#include "Overlay/Elements/Text.hpp"
#include "Overlay/Manager.hpp"
#include "Overlay/Screen.hpp"
#include "Settings.hpp"
#include "Tracer.hpp"

namespace Emeraude
{
	// NOLINTBEGIN(*-magic-numbers)
	using namespace Libraries;

	const size_t Console::ClassUID{Observable::getClassUID()};
	Console * Console::s_instance{nullptr}; // NOLINT NOTE: Singleton behavior

	Console::Console (const Arguments & arguments, const FileSystem & fileSystem, Settings & coreSettings, Input::Manager & inputManager, Overlay::Manager & overlayManager) noexcept
		: ServiceInterface(ClassId), KeyboardListenerInterface(true, true, false),
		  m_arguments(arguments), m_fileSystem(fileSystem), m_coreSettings(coreSettings), m_inputManager(inputManager), m_overlayManager(overlayManager)
	{
		if ( s_instance != nullptr )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", constructor called twice !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

			std::terminate();
		}

		s_instance = this;
	}

	Console::~Console ()
	{
		s_instance = nullptr;
	}

	Console *
	Console::instance () noexcept
	{
		return s_instance;
	}

	bool
	Console::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	Console::usable () const noexcept
	{
		return !m_consoleObjects.empty();
	}

	bool
	Console::onInitialize () noexcept
	{
		return true;
	}

	bool
	Console::onTerminate () noexcept
	{
		m_consoleObjects.clear();

		return true;
	}

	bool
	Console::buildGUI () noexcept
	{
		using namespace PixelFactory;

		if ( m_inputText != nullptr && m_outputText != nullptr )
		{
			return true;
		}

		auto screen = m_overlayManager.createScreen(ScreenName);

		{
			auto background = screen->create< Overlay::Elements::Picture >("Background", 1.0F, 1.0F);
			background->setImage(Graphics::ImageResource::get("UI/Console", true));
			background->setOpacity(0.75F);
			background->drawFinished();
		}

		auto font = Graphics::FontResource::get("old", true);

		{
			m_inputText = screen->create< Overlay::Elements::Text >(InputTextName, 1.0F, 0.1F);
			m_inputText->setPosition(Overlay::Surface::Position::Bottom);

			auto & writer = m_inputText->textWriter();
			writer.setFont(font);
			writer.setColor(White);
			writer.setSpacing(-8);

			m_inputText->drawFinished();
		}

		{
			m_outputText = screen->create< Overlay::Elements::Text >(OutputTextName, 1.0F, 0.9F);
			m_outputText->setPosition(Overlay::Surface::Position::Top);

			auto & writer = m_outputText->textWriter();
			writer.setFont(font);
			writer.setColor(White);
			writer.setSpacing(-8);

			m_outputText->drawFinished();
		}

		return true;
	}

	void
	Console::enable () noexcept
	{
		Tracer::info(ClassId, "Enabling console ...");

		m_inputManager.addKeyboardListener(this);

		/* If the direct querying state of the keyboard is enabled.
		 * Disables it to stop it during the console session. */
		if ( m_inputManager.isDirectQueryEnabled() )
		{
			m_inputManager.enableDirectQuery(false);

			m_flags[DirectInputWasEnabled] = true;
		}
		else
		{
			m_flags[DirectInputWasEnabled] = false;
		}

		/* If the pointer is locked to control the view, unlock it. */
		if ( m_inputManager.isPointerLocked() )
		{
			m_inputManager.unlockPointer();

			m_flags[PointerWasLocked] = true;
		}
		else
		{
			m_flags[PointerWasLocked] = false;
		}

		m_overlayManager.enableScreen(ScreenName);
	}

	void
	Console::disable () noexcept
	{
		Tracer::info(ClassId, "Disabling console ...");

		/* Disables keyboard listener for the console. */
		m_inputManager.removeKeyboardListener(this);

		/* Restore the direct querying state of the keyboard behavior, if it was enabled. */
		if ( m_flags[DirectInputWasEnabled] )
		{
			m_inputManager.enableDirectQuery(true);
		}

		/* If the pointer was locked to control the view, re-lock it. */
		if ( m_flags[PointerWasLocked] )
		{
			m_inputManager.lockPointer();
		}

		m_overlayManager.disableScreen(ScreenName);
	}

	bool
	Console::add (ConsoleControllable & controllable) noexcept
	{
		if ( m_consoleObjects.find(controllable.identifier()) != m_consoleObjects.cend() )
		{
			Tracer::error(ClassId, Blob() << "Console object named '" << controllable.identifier() << "' already exists !");

			return false;
		}

		auto result = m_consoleObjects.emplace(controllable.identifier(), &controllable);

		return result.second;
	}

	bool
	Console::remove (const std::string & identifier) noexcept
	{
		auto objectIt = m_consoleObjects.find(identifier);

		if ( objectIt != m_consoleObjects.end() )
		{
			m_consoleObjects.erase(objectIt);

			return true;
		}

		return false;
	}


	bool
	Console::remove (ConsoleControllable & pointer) noexcept
	{
		for ( auto it = m_consoleObjects.begin(); it != m_consoleObjects.end(); ++it )
		{
			if ( it->second == &pointer )
			{
				m_consoleObjects.erase(it);

				return true;
			}
		}

		return false;
	}

	bool
	Console::execute (const std::string & command) noexcept
	{
		m_inputText->clear();

		/* Checks for built-in command first ! */
		if ( command.find('.') == std::string::npos )
		{
			if ( !this->executeBuiltIn(command) )
			{
				Tracer::warning(ClassId, Blob() << "Command '" << command << "' with no effect !");

				return false;
			}

			return true;
		}

		/* Parse the command expression. */
		ConsoleExpression expression(command);

		if ( !expression.isValid() )
		{
			Tracer::warning(ClassId, Blob() << "Command '" << command << "' is invalid !");

			return false;
		}

		/* Gets the first identifier.
		 * NOTE: It is useless to check if it's empty here. */
		auto identifier = expression.nextIdentifier();

		/* Retrieve the base object. */
		auto objectIt = m_consoleObjects.find(identifier);

		if ( objectIt == m_consoleObjects.cend() )
		{
			Tracer::error(ClassId, Blob() << "Console object '" << identifier << "' not found !");

			return false;
		}

		/* Send the command to this object. */
		if ( !objectIt->second->execute(expression) )
		{
			Tracer::error(ClassId, Blob() << "Command '" << command << "' failed !");

			return false;
		}

		return true;
	}

	void
	Console::write (const std::string & message, Severity severity) noexcept
	{
		if ( m_outputText == nullptr )
		{
			return;
		}

		switch ( severity )
		{
			case Severity::Debug :
				m_outputText->textWriter().setColor({0.0F, 0.5F, 0.0F});
				break;

			case Severity::Success :
				m_outputText->textWriter().setColor({78U, 154U, 6U});
				break;

			case Severity::Info :
				m_outputText->textWriter().setColor({1.0F, 1.0F, 1.0F});
				break;

			case Severity::Warning :
				m_outputText->textWriter().setColor({206U, 92U, 0U});
				break;

			case Severity::Error :
			case Severity::Fatal :
				m_outputText->textWriter().setColor({1.0F, 0.0F, 0.0F});
				break;
		}

		m_outputText->write(message);
	}

	bool
	Console::loopOverObjectsName (const std::map< std::string, ConsoleControllable * > & objects, ConsoleExpression & expression, std::string & identifier, std::vector< std::string > & suggestions) noexcept
	{
		for ( const auto & objectIt : objects )
		{
			/* Object name is smaller than input, skip it. */
			if ( identifier.length() > objectIt.first.length() )
			{
				continue;
			}

			/* Perfect match. */
			if ( identifier == objectIt.first )
			{
				/* As we check a new depth, we don't want old suggestions */
				suggestions.clear();

				objectIt.second->complete(expression, identifier, suggestions);

				return true;
			}

			/* Checks for mismatching. */
			auto mismatch = false;

			for ( size_t chr = 0; chr < identifier.length(); chr++ )
			{
				/* Object name mismatch characters from input. */
				if ( objectIt.first[chr] != identifier[chr] )
				{
					mismatch = true;

					break;
				}
			}

			if ( !mismatch )
			{
				suggestions.emplace_back(objectIt.first);
			}
		}

		return false;
	}

	void
	Console::updateInput () const noexcept
	{
		if ( m_inputText != nullptr )
		{
			m_inputText->write(m_input, true);
		}
		else
		{
			std::cout << m_input << '\n';
		}
	}

	void
	Console::executeInput () noexcept
	{
		if ( m_input.empty() )
		{
			return;
		}

		/* Checks for multiple commands. */
		auto commandsList = String::explode(m_input, ';', false);

		auto success = std::all_of(commandsList.cbegin(), commandsList.cend(), [this](const auto & command) {
			return this->execute(command);
		});

		if ( !success )
		{
			auto msg = (Blob() << "'" << m_input << "' command has failed !").get();

			if ( m_outputText == nullptr )
			{
				Tracer::error(ClassId, msg);

				return;
			}

			m_outputText->write(msg);
		}
	}

	void
	Console::completeInput () noexcept
	{
		if ( m_input.empty() )
		{
			return;
		}

		/* Checks form multiple commands. */
		auto commandsList = String::explode(m_input, ';', false);

		/* We only check the last term. */
		ConsoleExpression expression(*commandsList.crbegin());

		if ( expression.isValid() )
		{
			return;
		}

		auto identifier = expression.nextIdentifier();

		std::vector< std::string > terms;

		/* For each register object in the console. */
		Console::loopOverObjectsName(m_consoleObjects, expression, identifier, terms);

		/* Shows the result */
		switch ( terms.size() )
		{
			case 1 :
				m_input += String::right(*terms.begin(), identifier);

				break;

			case 0 :

				Tracer::warning(ClassId, "No match found !");

				break;

			default:

				for ( auto & term : terms )
				{
					Tracer::info(ClassId, term);
				}

				break;
		}

		this->updateInput();
	}

	bool
	Console::executeBuiltIn (const std::string & command) noexcept
	{
		if ( command == "help" || command == "lsfunc()" )
		{
			this->write("Help command invoked !", Severity::Info);

			return true;
		}

		if ( command == "listObjects" || command == "lsobj()" )
		{
			for ( const auto & objectIt : m_consoleObjects )
			{
				this->write(Blob() << "'" << objectIt.first << "'", Severity::Info);
			}

			return true;
		}

		if ( command == "exit" || command == "quit" || command == "shutdown" )
		{
			this->write("Goodbye !", Severity::Info);

			/* FIXME: Launch a notification */
			/*this->fire([] (double) {
				Core::instance()->stop();
			}, 3000.0);*/

			return true;
		}

		if ( command == "hardExit" )
		{
			this->write("Wild exit command invoked !", Severity::Info);

			this->fire([] (double) {
				std::terminate();
			}, 3000.0);

			return true;
		}

		return false;
	}

	bool
	Console::onKeyPress (int /*key*/, int /*scanCode*/, int /*modifiers*/, bool /*repeat*/) noexcept
	{
		return this->isOpaque();
	}

	bool
	Console::onKeyRelease (int key, int /*scancode*/, int modifiers) noexcept
	{
		switch ( key )
		{
			/* Process the current command. */
			case Input::KeyEnter :
			case Input::KeyPadEnter :
				/* Save the command to history. */
				m_commandsHistory.emplace_back(m_input);

				/* Parse the command and execute it. */
				this->executeInput();

				/* Clean the input. */
				m_input.clear();

				m_historyOffset = m_commandsHistory.size();

				return true;

			case Input::KeyUp :
				if ( !m_commandsHistory.empty() && m_historyOffset != 0 )
				{
					m_historyOffset--;

					m_input = m_commandsHistory.at(m_historyOffset);

					this->updateInput();
				}
				return true;

			case Input::KeyDown :
				if ( !m_commandsHistory.empty() && m_historyOffset < (m_commandsHistory.size() - 1) )
				{
					m_historyOffset++;

					m_input = m_commandsHistory.at(m_historyOffset);

					this->updateInput();
				}
				return true;

			/* Removes character */
			case Input::KeyBackspace :

				if ( !m_input.empty() )
				{
					m_input.pop_back();

					this->updateInput();
				}

				return true;

			case Input::KeyTab :

				this->completeInput();

				return true;

			case Input::KeyEscape :

				this->disable();

				/* CTRL+ESC let ESC get to engine level. */
				return !Input::KeyboardController::isModifierKeyPressed(Input::ModKeyControl, modifiers);

			default:
				break;
		}

		return this->isOpaque();
	}

	bool
	Console::onCharacterType (unsigned int unicode, int /*modifiers*/) noexcept
	{
		if ( unicode < 127 )
		{
			m_input += static_cast< char >(unicode);
		}
		/*else
		{
			m_input += Libraries::String::unicodeToUTF8(unicode);
		}*/

		this->updateInput();

		return true;
	}

	// NOLINTEND(*-magic-numbers)
}
