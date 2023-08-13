/*
 * Emeraude/Settings.hpp
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

/* C/C++ standard libraries */
#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/* Local inclusion for inheritances. */
#include "ServiceInterface.hpp"

/* Local inclusion for usages. */
#include "Path/File.hpp"
#include "SettingStore.hpp"
#include "String.hpp"

namespace Json
{
	class Value;
}

namespace Emeraude
{
	class Arguments;

	/**
	 * @brief The settings instance type enum
	 */
	enum class SettingsType : size_t
	{
		Core = 0,
		Application = 1
	};

	/**
	 * @brief The settings service class.
	 * @extends Emeraude::ServiceInterface This is a service.
	 */
	class Settings final : public ServiceInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"SettingsService"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			static constexpr auto VersionKey = "WrittenByAppVersion";
			static constexpr auto DateKey = "WrittenAtDate";

			/**
			 * @brief Constructs a settings manager.
			 * @param arguments A reference to Arguments.
			 * @param type The settings instance type.
			 * @param serviceInstanceName The name of the service to differentiate the settings main store.
			 */
			Settings (const Arguments & arguments, SettingsType type, const char * serviceInstanceName = ClassId) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Settings (const Settings & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Settings (Settings && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			Settings & operator= (const Settings & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			Settings & operator= (Settings && copy) noexcept = delete;

			/**
			 * @brief Destructs the settings manager.
			 */
			~Settings () override;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::ServiceInterface::usable() */
			[[nodiscard]]
			bool usable () const noexcept override;

			/**
			 * @brief Sets the file path for this settings.
			 * @param filepath A reference to file path.
			 */
			void setFilepath (const Libraries::Path::File & filepath) noexcept;

			/**
			 * @brief Prevents config file creation.
			 * @warning This must be called after initialize() to prevent auto file creation.
			 */
			void doNotCreateConfigFile () noexcept;

			/**
			 * @brief Checks the present of a variable in the settings.
			 * @param key The key in settings to check.
			 * @return bool
			 */
			[[nodiscard]]
			bool variableExists (const std::string & key) const noexcept;

			/**
			 * @brief Checks the present of an array in the settings.
			 * @param key The key in settings to check.
			 * @return bool
			 */
			[[nodiscard]]
			bool arrayExists (const std::string & key) const noexcept;

			/**
			 * @brief Checks the present of a store in the settings.
			 * @param key The store name in settings to check.
			 * @return bool
			 */
			[[nodiscard]]
			bool storeExists (const std::string & key) const noexcept;

			/**
			 * @brief Returns a variable from settings.
			 * @param key The name of the configuration key.
			 * @return string
			 */
			[[nodiscard]]
			std::string get (const std::string & key) const noexcept;

			/**
			 * @brief Returns a variable from settings and set the default value if not exits.
			 * @note If the variable and/or Store doesn't exist, it will be create with the default value.
			 * @param key The name of the configuration key.
			 * @param defaultValue The default value if key don't exists.
			 * @return string
			 */
			std::string get (const std::string & key, const std::string & defaultValue) noexcept;

			/**
			 * @brief Returns a variable and convert the type to the template parameter.
			 * @tparam type_t
			 * @param key A reference to a string for the variable name.
			 * @return integer_t
			 */
			template< typename type_t, std::enable_if_t< std::is_arithmetic_v< type_t >, bool > = false >
			[[nodiscard]]
			type_t
			getAs (const std::string & key) const noexcept
			{
				const auto stringValue = this->get(key);

				if constexpr ( std::is_same_v< type_t, bool > )
				{
					return Libraries::String::toBool(stringValue);
				}

				if constexpr ( std::is_arithmetic_v< type_t > )
				{
					return Libraries::String::toNumber< type_t >(stringValue);
				}

				return 0;
			}

			/**
			 * @brief Returns a variable and convert the type to the template parameter and set the default value if not exits.
			 * @tparam type_t
			 * @param key A reference to a string for the variable name.
			 * @param defaultValue The default value.
			 * @return integer_t
			 */
			template< typename type_t, std::enable_if_t< std::is_arithmetic_v< type_t >, bool > = false >
			[[nodiscard]]
			type_t
			getAs (const std::string & key, type_t defaultValue) noexcept
			{
				const auto stringValue = this->get(key, Libraries::String::to_string(defaultValue));

				if constexpr ( std::is_same_v< type_t, bool > )
				{
					return Libraries::String::toBool(stringValue);
				}

				if constexpr ( std::is_arithmetic_v< type_t > )
				{
					return Libraries::String::toNumber< type_t >(stringValue);
				}

				return 0;
			}

			/**
			 * @brief Saves the settings in the file.
			 * @return bool
			 */
			[[nodiscard]]
			bool save () const noexcept;

			/**
			 * @brief Clears the settings.
			 * @return void
			 */
			void clear () noexcept;

			/**
			 * @brief Sets a value in the store.
			 * @param key A reference to a string for the variable name.
			 * @param value
			 */
			template< typename type_t >
			inline
			void
			set (const std::string & key, const type_t & value) noexcept
			{
				/* This will keep the variable name. */
				std::string variableName{};

				this->getStorePointer(key, variableName)->set(variableName, value);
			}

			/**
			 * @brief Sets a value in an array of the store.
			 * @param key A reference to a string for the array name.
			 * @param value A reference to a value.
			 */
			template< typename type_t >
			inline
			void
			setInArray (const std::string & key, const type_t & value) noexcept
			{
				/* This will keep the variable name. */
				std::string variableName{};

				this->getStorePointer(key, variableName)->setInArray(variableName, value);
			}

			/**
			 * @brief Returns a variable as a copy of string list.
			 * @param key A reference to a string for the variable name.
			 * @return std::vector< std::string >
			 */
			[[nodiscard]]
			std::vector< std::string > asStringList (const std::string & key) const noexcept;

			/**
			 * @brief Returns whether a variable as an array is empty.
			 * @param key A reference to a string for the variable name.
			 * @return bool
			 */
			[[nodiscard]]
			bool isArrayEmpty (const std::string & key) const noexcept;

			/**
			 * @brief Returns the instance of the settings manager.
			 * @param type The settings instance type.
			 * @return Settings *
			 */
			[[nodiscard]]
			static
			Settings * instance (SettingsType type) noexcept;

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const Settings & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend std::string to_string (const Settings & obj) noexcept;

		private:

			/** @copydoc Emeraude::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc Emeraude::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

			/**
			 * @brief readLevel
			 * @param data
			 * @param store
			 * @return bool
			 */
			bool readLevel (const Json::Value & data, SettingStore & store) noexcept;

			/**
			 * @brief readFile
			 * @param filepath
			 * @return bool
			 */
			bool readFile (const Libraries::Path::File & filepath) noexcept;

			[[nodiscard]]
			bool writeLevel (const SettingStore & store, Json::Value & data) const noexcept;

			/**
			 * @brief writeFile
			 * @param filepath
			 * @return bool
			 */
			[[nodiscard]]
			bool writeFile (const Libraries::Path::File & filepath) const noexcept;

			/**
			 * @brief getStorePointer
			 * @param key
			 * @param variableName
			 * @return SettingStore *
			 */
			[[nodiscard]]
			SettingStore * getStorePointer (const std::string & key, std::string & variableName) noexcept;

			/**
			 * @brief getStorePointer
			 * @param key
			 * @param variableName
			 * @return const SettingStore
			 */
			[[nodiscard]]
			const SettingStore * getStorePointer (const std::string & key, std::string & variableName) const noexcept;

			/* Flag names. */
			static constexpr auto SaveAtExit = 0UL;

			static std::array< Settings *, 2 > s_instances; // NOLINT NOTE: Singleton behavior

			const Arguments & m_arguments; // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
			SettingsType m_type;
			SettingStore m_store{};
			Libraries::Path::File m_filepath{};
			std::array< bool, 8 > m_flags{ // NOLINT(*-magic-numbers)
				true/*SaveAtExit*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
