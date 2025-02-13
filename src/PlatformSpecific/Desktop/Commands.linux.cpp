#include "Commands.hpp"

#if IS_LINUX

/* STL inclusions. */
#include <cstdlib>
#include <sstream>

namespace Emeraude::PlatformSpecific::Desktop
{
	void
	runDesktopApplication (const std::string & argument) noexcept
	{
		if ( argument.empty() )
		{
			return;
		}

		std::stringstream commandStream;
		commandStream << "xdg-open \"" << argument << "\"";

		system(commandStream.str().c_str());
	}
}

#endif
