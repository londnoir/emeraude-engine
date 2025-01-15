#pragma once

/* Project configuration files. */
#include "platform.hpp"

/* STL inclusions. */
#include <string>
#include <filesystem>

namespace Emeraude::PlatformSpecific::Desktop
{
	/**
	 * @brief Tries to open a URL in an external web browser.
	 * @param url A reference to a string.
	 * @return void
	 */
	void openURL (const std::string & url) noexcept;

	/**
	 * @brief Tries to open a file in an external program.
	 * @param filepath A reference to a path.
	 * @return void
	 */
	void openPath (const std::filesystem::path & filepath) noexcept;

	/**
	 * @brief Tries to open the directory of a file in an external file browser.
	 * @param filepath A reference to a path.
	 * @return void
	 */
	void showInFolder (const std::filesystem::path & filepath) noexcept;
}
