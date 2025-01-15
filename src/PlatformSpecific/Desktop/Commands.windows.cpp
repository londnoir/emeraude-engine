#include "Commands.hpp"

#if IS_WINDOWS

/* STL inclusions. */
#include <iostream>

namespace Emeraude::PlatformSpecific::Desktop
{
	void
	openURL (const std::string & url) noexcept
	{
		std::cout << "TODO: Should open the URL " << url << " externally." << "\n";
	}

	void
	openPath (const std::filesystem::path & filepath) noexcept
	{
		std::cout << "TODO: Should open the file " << filepath << " externally." << "\n";
	}

	void
	showInFolder (const std::filesystem::path & filepath) noexcept
	{
		std::cout << "TODO: Should open the directory of the file " << filepath << " in an external file browser." << "\n";
	}
}

#endif
