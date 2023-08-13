/*
 * Emeraude/Vulkan/Utility.hpp
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
#include <string>
#include <vector>

/* Third-party libraries */
#include "Third-Party-Inclusion/vulkan.hpp"

namespace Emeraude::Vulkan
{
	/**
	 * @brief Returns a Vulkan result code to a C-String.
	 * @param code The vulkan code.
	 * @return const char *
	 */
	[[nodiscard]]
	const char * vkResultToCString (VkResult code) noexcept;

	/**
	 * @brief Prints validation layers available from Vulkan.
	 * @param validationLayers A reference to a validation layer list.
	 * @return void
	 */
	void printItemList (const std::vector< VkLayerProperties > & validationLayers) noexcept;

	/**
	 * @brief Prints extensions available from Vulkan.
	 * @param type Which type of extensions.
	 * @param extensions A reference to a extension list.
	 * @return void
	 */
	void printItemList (const char * type, const std::vector< VkExtensionProperties > & extensions) noexcept;
}
