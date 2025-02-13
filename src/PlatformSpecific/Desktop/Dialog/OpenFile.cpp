#include "OpenFile.hpp"

namespace Emeraude::PlatformSpecific::Desktop::Dialog
{
	OpenFile::OpenFile (const std::string & title, bool selectFolder, bool multiSelect)
		: Abstract(title)
	{
		m_flags[SelectFolder] = selectFolder;
		m_flags[MultiSelect] = multiSelect;
	}
}
