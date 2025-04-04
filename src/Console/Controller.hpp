/*
 * src/Console/Controller.hpp
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
#include <cstddef>
#include <array>
#include <vector>
#include <map>
#include <string>

/* Local inclusions for inheritances. */
#include "ServiceInterface.hpp"
#include "Libs/Time/EventTrait.hpp"

/* Local usages */
#include "Output.hpp"

/* Forward declarations */
namespace EmEn
{
	class PrimaryServices;

	namespace Console
	{
		class Controllable;
		class Expression;
	}
}

namespace EmEn::Console
{
	/**
	 * @brief The console service class.
	 * @extends EmEn::ServiceInterface This is a service.
	 * @extends EmEn::Libs::Time::EventTrait This service needs to delay some behavior.
	 */
	class Controller final : public ServiceInterface, private Libs::Time::EventTrait< uint32_t, std::milli >
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"ConsoleControllerService"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs the console controller.
			 * @param primaryServices A reference to primary services.
			 */
			Controller (PrimaryServices & primaryServices) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Controller (const Controller & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Controller (Controller && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return Controller &
			 */
			Controller & operator= (const Controller & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return Controller &
			 */
			Controller & operator= (Controller && copy) noexcept = delete;

			/**
			 * @brief Destructs the console controller.
			 */
			~Controller () override;

			/** @copydoc EmEn::Libs::ObservableTrait::classUID() const */
			[[nodiscard]]
			size_t
			classUID () const noexcept override
			{
				return ClassUID;
			}

			/** @copydoc EmEn::Libs::ObservableTrait::is() const */
			[[nodiscard]]
			bool
			is (size_t classUID) const noexcept override
			{
				return classUID == ClassUID;
			}

			/** @copydoc EmEn::ServiceInterface::usable() */
			[[nodiscard]]
			bool usable () const noexcept override;

			/**
			 * @brief Adds a controllable object to the console.
			 * @param controllable A reference to the controllable object to add.
			 * @return bool
			 */
			bool add (Controllable & controllable) noexcept;

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
			bool remove (const Controllable & pointer) noexcept;

			/**
			 * @brief Tries to guess the next term in the console input.
			 * @param input A writable reference to a string.
			 * @return void
			 */
			void complete (std::string & input) const noexcept;

			/**
			 * @brief Executes a command.
			 * @param command A reference to a string holding the raw command.
			 * @param outputs A writable reference to a vector of console outputs.
			 * @return bool
			 */
			bool executeCommand (const std::string & command, Outputs & outputs) noexcept;

			/**
			 * @brief Returns the instance of the console controller.
			 * @return Controller *
			 */
			[[nodiscard]]
			static
			Controller *
			instance () noexcept
			{
				return s_instance;
			}

			/**
			 * @brief Loop over object names.
			 * FIXME Checks this method, this should be non-static.
			 * @param objects The list of register objects to the console.
			 * @param expression A writable reference to a console expression.
			 * @param identifier A writable reference to a string.
			 * @param suggestions A writable reference to a string list to set found suggestions.
			 * @return bool
			 */
			static bool loopOverObjectsName (const std::map< std::string, Controllable * > & objects, Expression & expression, std::string & identifier, std::vector< std::string > & suggestions) noexcept;

		private:

			/** @copydoc EmEn::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc EmEn::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

			/**
			 * @brief Checks and execute built-in console commands such as "help".
			 * @param command A reference to a string holding the raw command.
			 * @param outputs A writable reference to a vector of console outputs.
			 * @return bool
			 */
			[[nodiscard]]
			bool executeBuiltInCommand (const std::string & command, Outputs & outputs) noexcept;

			static constexpr auto InputTextName{"Input"};
			static constexpr auto OutputTextName{"Output"};

			/* Flag names. */
			static constexpr auto ServiceInitialized{0UL};
			static constexpr auto DirectInputWasEnabled{1UL};
			static constexpr auto PointerWasLocked{2UL};

			static Controller * s_instance;

			PrimaryServices & m_primaryServices;
			std::map< std::string, Controllable * > m_consoleObjects;
			std::vector< std::string > m_history;
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
