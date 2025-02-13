#include "Commands.hpp"

/* Local inclusions. */
#include "Libraries/Network/URL.hpp"
#include "Tracer.hpp"

namespace Emeraude::PlatformSpecific::Desktop
{
	using namespace Libraries::Network;

	static constexpr auto TracerTag{"DesktopCommand"};

	bool
	openURL (const std::string & url) noexcept
	{
		if ( !URL::isURL(url) )
		{
			TraceWarning{TracerTag} << "The URL '" << url << "' is invalid !";

			return false;
		}

		runDesktopApplication(url);

		return true;
	}

	bool
	openFile (const std::filesystem::path & filepath) noexcept
	{
		if ( !std::filesystem::is_regular_file(filepath) )
		{
			TraceWarning{TracerTag} << "The file '" << filepath.string() << "' does not exist !";

			return false;
		}

		runDesktopApplication(filepath.string());

		return true;
	}

	bool
	openFolder (const std::filesystem::path & filepath) noexcept
	{
		if ( !std::filesystem::is_directory(filepath) )
		{
			TraceWarning{TracerTag} << "The file '" << filepath.string() << "' does not exist !";

			return false;
		}

		runDesktopApplication(filepath.string());

		return true;
	}

	bool
	showInFolder (const std::filesystem::path & filepath) noexcept
	{
		if ( !std::filesystem::is_regular_file(filepath) )
		{
			TraceWarning{TracerTag} << "The file '" << filepath.string() << "' does not exist !";

			return false;
		}

		runDesktopApplication(filepath.parent_path().string());

		return true;
	}
}
