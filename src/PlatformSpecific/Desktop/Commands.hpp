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
	 * @return bool
	 */
	bool openURL (const std::string & url) noexcept;

	/**
	 * @brief Tries to open a file in an external program.
	 * @param filepath A reference to a path.
	 * @return bool
	 */
	bool openFile (const std::filesystem::path & filepath) noexcept;

	/**
	 * @brief Tries to open a folder in an external program.
	 * @param filepath A reference to a path.
	 * @return bool
	 */
	bool openFolder (const std::filesystem::path & filepath) noexcept;

	/**
	 * @brief Tries to open the directory of a file in an external file browser.
	 * @param filepath A reference to a path.
	 * @return bool
	 */
	bool showInFolder (const std::filesystem::path & filepath) noexcept;

	/**
	 * @brief Tries to open the directory of a file in an external file browser.
	 * @param argument A reference to a string.
	 * @return void
	 */
	void runDesktopApplication (const std::string & argument) noexcept;
}
