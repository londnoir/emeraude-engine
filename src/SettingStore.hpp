/*
 * Emeraude/SettingStore.hpp
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
#include <map>
#include <string>
#include <vector>

namespace Emeraude
{
	/**
	 * @brief The SettingStore class
	 */
	class SettingStore final
	{
		friend class Settings;

		public:

			/**
			 * @brief Constructs a setting store.
			 */
			SettingStore () noexcept = default;

			/**
			 * @brief Sets a new variable in store.
			 * @param name A reference to a string for the variable name.
			 * @param value The variable value.
			 */
			void set (const std::string & name, const std::string & value) noexcept;

			/**
			 * @brief Sets a new variable in store.
			 * @param name A reference to a string for the variable name.
			 * @param value The variable value.
			 */
			inline
			void
			set (const std::string & name, const char * value) noexcept
			{
				this->set(name, std::string{value});
			}

			/**
			 * @brief Sets a new variable in store.
			 * @param name A reference to a string for the variable name.
			 * @param value The variable value.
			 */
			template< typename type_t >
			inline
			void
			set (const std::string & name, type_t value) noexcept
			{
				this->set(name, std::to_string(value));
			}

			/**
			 * @brief Sets a new variable in an array of the store.
			 * @param name A reference to a string for the array name.
			 * @param value The variable value.
			 */
			void setInArray (const std::string & name, const std::string & value) noexcept;

			/**
			 * @brief Sets a new variable in an array of the store.
			 * @param name A reference to a string for the array name.
			 * @param value The variable value.
			 */
			inline
			void
			setInArray (const std::string & name, const char * value) noexcept
			{
				this->setInArray(name, std::string{value});
			}

			/**
			 * @brief Sets a new variable in an array of the store.
			 * @param name A reference to a string for the array name.
			 * @param value The variable value.
			 */
			template< typename type_t >
			inline
			void
			setInArray (const std::string & name, type_t value) noexcept
			{
				this->setInArray(name, std::to_string(value));
			}

			/**
			 * @brief Checks whether a variable is present in the store.
			 * @param name A reference to a string for the variable name.
			 * @return bool
			 */
			[[nodiscard]]
			bool variableExists (const std::string & name) const noexcept;

			/**
			 * @brief Checks whether an array is present in the store.
			 * @param name A reference to a string for the array name.
			 * @return bool
			 */
			[[nodiscard]]
			bool arrayExists (const std::string & name) const noexcept;

			/**
			 * @brief Checks if a sub-store is present in the store.
			 * @param storeName The name of the store.
			 * @return bool
			 */
			[[nodiscard]]
			bool subStoreExists (const std::string & storeName) const noexcept;

			/**
			 * @brief Gets a sub-store. If doesn't exist, it will be created.
			 * @param storeName The name of the store.
			 * @return SettingStore &
			 */
			[[nodiscard]]
			SettingStore & getSubStore (const std::string & storeName) noexcept;

			/**
			 * @brief Returns a sub-store pointer.
			 * @param storeName The name of the store.
			 * @return const SettingStore *
			 */
			[[nodiscard]]
			const SettingStore * getSubStorePointer (const std::string & storeName) const noexcept;

			/**
			 * @brief Returns a sub-store pointer.
			 * @param storeName The name of the store.
			 * @param createIfNotExists Enabled, this will create the sub-store if it doesn't exist.
			 * @return SettingStore *
			 */
			[[nodiscard]]
			SettingStore * getSubStorePointer (const std::string & storeName, bool createIfNotExists = true) noexcept;

			/**
			 * @brief Gets the value of a variable.
			 * @param name A reference to a string for the variable name.
			 * @return string
			 */
			[[nodiscard]]
			std::string get (const std::string & name) const noexcept;

			/**
			 * @brief Gets the value of a variable. If the variable doesn't exist, it will be set.
			 * @param name A reference to a string for the variable name.
			 * @param defaultValue A reference to a string for the default value.
			 * @return string
			 */
			[[nodiscard]]
			std::string getOrSet (const std::string & name, const std::string & defaultValue) noexcept;

			/**
			 * @brief Returns a const access to an array of variable.
			 * @param name A reference to a string for the array name.
			 * @return const std::vector< std::string > *
			 */
			[[nodiscard]]
			const std::vector< std::string > * getArray (const std::string & name) const noexcept;

			/**
			 * @brief Returns a access to an array of variable.
			 * @param name A reference to a string for the array name.
			 * @return std::vector< std::string > *
			 */
			[[nodiscard]]
			std::vector< std::string > * getArray (const std::string & name) noexcept;

			/** @brief Clears the store. */
			void clear () noexcept;

			/** @brief Clears variable from this store. */
			void clearData () noexcept;

			/** @brief Clears sub-stores from this store. */
			void clearSubStores () noexcept;

			/**
			 * @brief Returns variables.
			 * @return const std::map< std::string, std::string > &
			 */
			[[nodiscard]]
			const std::map< std::string, std::string > & variables () const noexcept;

			/**
			 * @brief Returns arrays variables.
			 * @return const std::map< std::string, std::vector< std::string > > &
			 */
			[[nodiscard]]
			const std::map< std::string, std::vector< std::string > > & arrays () const noexcept;

			/**
			 * @brief Returns sub-stores.
			 * @return const std::map< std::string, SettingStore > &
			 */
			[[nodiscard]]
			const std::map< std::string, SettingStore > & subStores () const noexcept;

		private:

			std::map< std::string, std::string > m_variables{};
			std::map< std::string, std::vector< std::string > > m_arrays{};
			std::map< std::string, SettingStore > m_subStores{};
	};
}
