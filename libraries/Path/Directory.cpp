/*
 * Libraries/Path/Directory.cpp
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

#include "Directory.hpp"

/* C/C++ standard libraries. */
#include <filesystem>
#include <iostream>
#include <numeric>

/* Local inclusions. */
#include "Path.hpp"
#include "String.hpp"
#include "platform.hpp"

/* Platform libraries. */
#if IS_LINUX
	#include <glob.h>
	#include <pwd.h>
	#include <sys/stat.h>
	#include <unistd.h>
#elif IS_WINDOWS
	#include <direct.h>
	#include <windows.h>
#endif

namespace Libraries::Path
{
	Directory::Directory (const std::string & path) noexcept
	{
		this->set(path);
	}

	Directory &
	Directory::append (const std::string & part) noexcept
	{
		if ( part.find(Separator) != std::string::npos )
		{
			auto chunks = String::explode(part, Separator, false);

			std::copy(chunks.cbegin(), chunks.cend(), std::back_inserter(m_parts));
		}
		else
		{
			m_parts.emplace_back(part);
		}

		return *this;
	}

	bool
	Directory::operator== (const Directory & operand) const noexcept
	{
		if ( this == &operand )
		{ 
			return true; 
		}

		return to_string(*this) == to_string(operand);
	}

	void
	Directory::set (const std::string & path) noexcept
	{
		std::vector< std::string > chunks{};

#if IS_LINUX

		if ( path.front() == '~' )
		{
			auto * userInfo = getpwuid(getuid());

			chunks = String::explode(std::string(userInfo->pw_dir) + path.substr(1), Separator, false);
		}
		else
		{
			chunks = String::explode(path, Separator, false);
		}

#else

		chunks = String::explode(path, Separator, false);

#endif

		auto chunkIt = chunks.begin();

		if ( chunkIt == chunks.end() )
		{ 
			return; 
		}

#if IS_WINDOWS

		/* NOTE: Workaround for the "[DRIVER_LETTER]:\" part. */
		if ( (*it).find(':') != std::string::npos  )
		{
			m_startPoint = (*it) + Slash;

			chunks.erase(it);
		}

#else

		if ( *chunkIt == "." || *chunkIt == ".." )
		{
			m_startPoint = *chunkIt;

			chunks.erase(chunkIt);
		}
		else if ( path.front() == Separator )
		{
			m_startPoint = Separator;
		}

#endif

		std::copy(chunks.cbegin(), chunks.cend(), std::back_inserter(m_parts));
	}

	bool
	Directory::empty () const noexcept
	{
		if ( !m_parts.empty() )
		{ 
			return false; 
		}

		if ( m_startPoint.empty() )
		{
			return false;
		}

		return true;
	}

	size_t
	Directory::length () const noexcept
	{
		size_t length = 0;

		/* ie: [..] + '/' = 3 */
		if ( !m_startPoint.empty() )
		{ 
			length += m_startPoint.length() + 1; 
		}

		/* id: [foo] + '/' + [bar] + '/' = 8 */
		if ( !m_parts.empty() )
		{
			length = std::accumulate(m_parts.cbegin(), m_parts.cend(), length, [] (auto sum, const auto & item) {
				return sum + item.length();
			});

			length += m_parts.size();
		}

		/* ie: 21 */
		return length;
	}

#if IS_LINUX

	bool
	Directory::exists (const std::string & path) noexcept
	{
		if ( path.empty() )
		{ 
			return false; 
		}

		struct stat statData{};

		if ( stat(path.c_str(), &statData) > 0 )
		{ 
			return false; 
		}

		return S_ISDIR(statData.st_mode);
	}

#elif IS_WINDOWS

	bool
	Directory::exists (const std::string & path) noexcept
	{
		if ( path.empty() )
			return false;

		DWORD dwAttrib = GetFileAttributes(path.c_str());

		return dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
	}

#elif IS_MACOS

	bool
	Directory::exists (const std::string & path) noexcept
	{
		#error "TODO: Check for this platform"

		return false;
	}

#endif

	bool
	Directory::writable (const std::string & path) noexcept
	{
		const auto permissions = std::filesystem::status(path).permissions();

		if ( (permissions & std::filesystem::perms::owner_write) != std::filesystem::perms::none )
		{ 
			return true; 
		}

		if ( (permissions & std::filesystem::perms::group_write) != std::filesystem::perms::none )
		{
			return true;
		}

		if ( (permissions & std::filesystem::perms::others_write) != std::filesystem::perms::none )
		{
			return true;
		}

		return false;
	}

	bool
	Directory::create (const std::string & path, bool lastPartIsFile) noexcept
	{
		if ( path.empty() )
		{ 
			return false; 
		}

		auto directories = String::explode(path, Separator, false);

		/* Removing file name */
		if ( lastPartIsFile )
		{ 
			directories.pop_back(); 
		}

		if ( directories.empty() )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", there is no directory to build !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

			return false;
		}

		/* Build the path folder by folder.  */
		std::string currentPath{};

#if IS_WINDOWS

		/* NOTE: Workaround for the "[DRIVER_LETTER]:\" part. */
		auto it = directories.begin();

		if ( it == directories.end() )
			return false;

		currentPath = (*it) + Slash;

		directories.erase(it);

#else
		currentPath += Separator;
#endif

		for ( const auto & directory : directories )
		{
			currentPath += directory + Separator;

			if ( !Directory::mkdir(currentPath) )
			{ 
				return false; 
			}
		}

		return true;
	}

	bool
	Directory::remove (const std::string & path) noexcept
	{
		if ( path.empty() )
		{
			return false;
		}

		const auto ret = rmdir(path.c_str());

		if ( ret == 0 )
		{ 
			return true; 
		}

		switch ( ret )
		{
			case EACCES :
				std::cerr <<
					"Search permission is denied on a component of the path prefix, or write permission is denied on the parent directory of the directory to be removed.\n"
					"The S_ISVTX flag is set on the parent directory of the directory to be removed and the caller is not the owner of the directory to be removed, nor is the caller the owner of the parent directory, nor does the caller have the appropriate privileges." "\n";
				break;

			case EBUSY :
				std::cerr << "The directory to be removed is currently in use by the system or some process and the implementation considers this to be an error." "\n";
				break;

			case EEXIST :
			case ENOTEMPTY :
				std::cerr << "The path argument names a directory that is not an empty directory, or there are hard links to the directory other than dot or a single entry in dot-dot." "\n";
				break;

			case EINVAL :
				std::cerr << "The path argument contains a last component that is dot." "\n";
				break;

			case EIO :
				std::cerr << "A physical I/O error has occurred." "\n";
				break;

			case ELOOP :
				std::cerr << "A loop exists in symbolic links encountered during resolution of the path argument." "\n";
				break;

			case ENAMETOOLONG :
				std::cerr <<
					"The length of the path argument exceeds {PATH_MAX} or a pathname component is longer than {NAME_MAX}.\n"
					"Pathname resolution of a symbolic link produced an intermediate result whose length exceeds {PATH_MAX}." "\n";
				break;

			case ENOENT :
				std::cerr << "A component of path does not name an existing file, or the path argument names a nonexistent directory or points to an empty string." "\n";
				break;

			case ENOTDIR :
				std::cerr << "A component of path is not a directory." "\n";
				break;

			case EPERM :
				std::cerr << "The S_ISVTX flag is set on the parent directory of the directory to be removed and the caller is not the owner of the directory to be removed, nor is the caller the owner of the parent directory, nor does the caller have the appropriate privileges." "\n";
				break;

			case EROFS :
				std::cerr << "The directory entry to be removed resides on a read-only file system." "\n";
				break;

			default:
				break;
		}

		return false;
	}

	std::vector< std::string >
	Directory::entries () const noexcept
	{
		if ( this->empty() )
		{
			return {};
		}

		std::vector< std::string > entries{};

#if IS_LINUX

		const auto pattern = to_string(*this) + "*";

		glob_t files{};

		glob(pattern.c_str(), GLOB_TILDE, nullptr, &files);

		for ( unsigned long index = 0; index < files.gl_pathc; ++index )
		{
			entries.emplace_back(files.gl_pathv[index]); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
		}

		globfree(&files);

#elif IS_WINDOWS

#elif IS_MACOS

#endif

		return entries;
	}

	Directory
	Directory::getCurrentWorkingDirectory () noexcept
	{
		return Directory{std::filesystem::current_path()};
	}

	bool
	Directory::mkdir (const std::string & path) noexcept
	{
		/* 1. Check if the directory exists. */
		Directory const directory{path};

		if ( directory.exists() )
		{
			return true;
		}

		/* 2. Creates the directory. */
#if IS_LINUX

		auto ret = ::mkdir(path.c_str(), 0755); // NOLINT(*-magic-numbers)

#elif IS_WINDOWS

		auto ret = ::mkdir(path.c_str());

#elif IS_MACOS

		auto ret = 0;

#endif

		if ( ret == 0 )
		{
			return true;
		}

		switch ( ret )
		{
			case EACCES :
				std::cerr << "Search permission is denied on a component of the path prefix, or write permission is denied on the parent directory of the directory to be created." "\n";
				break;

			case EEXIST :
				std::cerr << "The named file exists." "\n";
				break;

			case ELOOP :
				std::cerr << "Too many symbolic links were encountered in resolving path." "\n";
				break;

			case EMLINK :
				std::cerr << "The link count of the parent directory would exceed {LINK_MAX}." "\n";
				break;

			case ENAMETOOLONG :
				std::cerr <<
					"The length of the path argument exceeds {PATH_MAX} or a pathname component is longer than {NAME_MAX}\n."
					"Pathname resolution of a symbolic link produced an intermediate result whose length exceeds {PATH_MAX}." "\n";
				break;

			case ENOENT :
				std::cerr << "A component of the path prefix specified by path does not name an existing directory or path is an empty string." "\n";
				break;

			case ENOSPC :
				std::cerr << "The file system does not contain enough space to hold the contents of the new directory or to extend the parent directory of the new directory." "\n";
				break;

			case ENOTDIR :
				std::cerr << "A component of the path prefix is not a directory." "\n";
				break;

			case EROFS :
				std::cerr << "The parent directory resides on a read-only file system." "\n";
				break;

			default:
				break;
		}

		return false;
	}

	std::ostream &
	operator<< (std::ostream & out, const Directory & obj)
	{
		out << obj.m_startPoint;

		for ( const auto & part : obj.m_parts )
		{
			out << part << Separator;
		}

		return out;
	}

	std::string
	to_string (const Directory & obj) noexcept
	{
		return (std::stringstream{} << obj).str();
	}
}
