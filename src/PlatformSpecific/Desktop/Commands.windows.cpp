#include "Commands.hpp"

#if IS_WINDOWS

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
		commandStream << "start " << argument;

		system(commandStream.str().c_str());
	}
}

#endif
