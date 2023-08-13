/*
 * Emeraude/Resources/BaseInformation.hpp
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
#include <string>

/* Local inclusions for usages. */
#include "Path/File.hpp"
#include "Types.hpp"

/* Third-party libraries */
#include "Third-Party-Inclusion/json.hpp"

namespace Emeraude::Resources
{
	/** @brief This structure represent a resource definition in a store. It hold the way to load it. */
	class BaseInformation final
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"ResourcesBaseInformation"};

			/**
			 * @brief Default constructor.
			 */
			BaseInformation () = default;

			/**
			 * @brief Returns false if the source is Undefined.
			 * @return bool
			 */
			[[nodiscard]]
			bool isValid () const noexcept;

			/**
			 * @brief Returns the name of the resource.
			 * @return const std::string &
			 */
			[[nodiscard]]
			const std::string & name () const noexcept;

			/**
			 * @brief Returns where the resource come from.
			 * @return SourceType
			 */
			[[nodiscard]]
			SourceType sourceType () const noexcept;

			/**
			 * @brief Returns the resource data as JSON.
			 * @return const Json::Value &
			 */
			[[nodiscard]]
			const Json::Value & data () const noexcept;

			/**
			 * @brief Updates resource information from a downloaded file.
			 * @param file A reference to as file.
			 */
			void updateFromDownload (const Libraries::Path::File & file) noexcept;

			/**
			 * @brief Parses a JSON node to extract resource information.
			 * @param resourceDefinition A reference to a JSON node.
			 * @return bool
			 */
			bool parse (const Json::Value & resourceDefinition) noexcept;

		private:

			/**
			 * @brief Gets the resource name from the JSON node.
			 * @param resourceDefinition A reference to a JSON node.
			 * @return bool
			 */
			bool parseName (const Json::Value & resourceDefinition) noexcept;

			/**
			 * @brief Gets the resource source type from the JSON node.
			 * @param resourceDefinition A reference to a JSON node.
			 * @return bool
			 */
			bool parseSource (const Json::Value & resourceDefinition) noexcept;

			/**
			 * @brief Gets the resource data from the JSON node.
			 * @param resourceDefinition A reference to a JSON node.
			 * @return bool
			 */
			bool parseData (const Json::Value & resourceDefinition) noexcept;

			/* JSON keys */
			static constexpr auto NameKey = "Name";
			static constexpr auto SourceKey = "Source";
			static constexpr auto DataKey = "Data";

			std::string m_name{};
			SourceType m_source = SourceType::Undefined;
			Json::Value m_data{};
	};
}
