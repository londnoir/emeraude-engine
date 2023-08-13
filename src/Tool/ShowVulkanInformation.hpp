/*
 * Emeraude/Tool/ShowVulkanInformation.hpp
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

/* Local inclusions for inheritances. */
#include "ToolInterface.hpp"

namespace Emeraude::Vulkan
{
	class Instance;
}

namespace Emeraude::Tool
{
	/**
	 * @brief The vulkan information class.
	 * @extends Emeraude::Tool::ToolInterface This is tool interface.
	 */
	class ShowVulkanInformation final : public ToolInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"ShowVulkanInformation"};

			/**
			 * @brief Constructs the tool.
			 * @param arguments A reference to the arguments.
			 * @param vulkanInstance A reference to the vulkan instance.
			 */
			explicit ShowVulkanInformation (const Arguments & arguments, const Vulkan::Instance & vulkanInstance) noexcept;

			/** @copydoc Emeraude::Tool::ToolInterface::execute() */
			[[nodiscard]]
			bool execute () noexcept override;

		private:

			const Arguments & m_arguments;
			const Vulkan::Instance & m_vulkanInstance;
	};
}
