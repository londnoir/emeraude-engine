/*
 * Libraries/Path/File.cpp
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

#include "File.hpp"

/* C/C++ standard libraries. */
#include <algorithm>
#include <fstream>
#include <iostream>
#include <utility>

/* Local inclusions. */
#include "Path.hpp"
#include "String.hpp"
#include "platform.hpp"

/* Platform libraries. */
#if IS_LINUX
#include <sys/stat.h>
#include <unistd.h>
#endif

namespace Libraries::Path
{
	File::File (Directory directory, std::string filename) noexcept
		: m_directory(std::move(directory)), m_filename(std::move(filename))
	{

	}

	File::File (const std::string & path) noexcept
	{
		this->set(path);
	}

	bool
	File::empty () const noexcept
	{
		return m_filename.empty();
	}

	size_t
	File::length () const noexcept
	{
		return m_directory.length() + m_filename.length();
	}

	void
	File::set (const Directory & directory, const std::string & filename) noexcept
	{
		m_directory = directory;
		m_filename = filename;
	}

	void
	File::set (const std::string & path) noexcept
	{
		const auto pos = path.find_last_of(Separator);

		if ( pos != std::string::npos )
		{
			m_directory = Directory(path.substr(0, pos));
			m_filename = path.substr(pos + 1);
		}
	}

	bool
	File::hasExtension (const std::string & ext) const noexcept
	{
		const auto & str = to_string(*this);

		return str.find(ext) != std::string::npos || str.find(String::toUpper(ext)) != std::string::npos;
	}

	bool
	File::hasExtensions (const std::vector< std::string > & extensions) const noexcept
	{
		return std::ranges::any_of(extensions, [this] (const auto & extension) {
			return this->hasExtension(extension);
		});
	}

	bool
	File::hasExtensions (const std::vector< const char * > & extensions) const noexcept
	{
		return std::ranges::any_of(extensions, [this] (const char * extension) {
			return this->hasExtension(extension);
		});
	}

	bool
	File::hasExtensions (const char * const * extensions, size_t size) const noexcept
	{
		const auto & str = to_string(*this);

		for ( size_t index = 0; index < size; index++ )
		{
			if ( this->hasExtension({extensions[index]}) ) // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
			{
				return true;
			}
		}

		return false;
	}

	bool
	File::exists () const noexcept
	{
		return File::exists(to_string(*this));
	}

	bool
	File::exists (const std::string & path) noexcept
	{
		if ( path.empty() )
		{ 
			return false; 
		}

#if IS_LINUX

		/* POSIX way */
		struct stat statData{};

		return stat(path.c_str(), &statData) == 0;

#else

		std::ifstream file{path.c_str()};

		return file.good();

#endif
	}

	bool
	File::create () const noexcept
	{
		return File::create(to_string(*this));
	}

	bool
	File::create (const std::string & path) noexcept
	{
		if ( path.empty() )
		{ 
			return false; 
		}

		std::ofstream file(path);

		return file.is_open();
	}

	bool
	File::erase () const noexcept
	{
		return File::erase(to_string(*this));
	}

	bool
	File::erase (const std::string & path) noexcept
	{
		if ( path.empty() )
		{
			return false;
		}

		auto ret = unlink(path.c_str());

		if ( ret == 0 )
		{ 
			return true; 
		}

		switch ( ret )
		{
			case EACCES :
				std::cerr <<
					"Search permission is denied for a component of the path prefix, or write permission is denied on the directory containing the directory entry to be removed.\n"
					"The S_ISVTX flag is set on the directory containing the file referred to by the path argument and the caller is not the file owner, nor is the caller the directory owner, nor does the caller have appropriate privileges." "\n";
				break;

			case EBUSY :
				std::cerr <<
					"The file named by the path argument cannot be unlinked because it is being used by the system or another process and the implementation considers this an error.\n"
					"The file named by path is a named STREAM." "\n";
				break;

			case ELOOP :
				std::cerr << "Too many symbolic links were encountered in resolving path." "\n";
				break;

			case ENAMETOOLONG :
				std::cerr <<
					"The length of the path argument exceeds {PATH_MAX} or a pathname component is longer than {NAME_MAX}.\n"
					"Pathname resolution of a symbolic link produced an intermediate result whose length exceeds {PATH_MAX}." "\n";
				break;

			case ENOENT :
				std::cerr << "A component of path does not name an existing file or path is an empty string." "\n";
				break;

			case ENOTDIR :
				std::cerr << "A component of the path prefix is not a directory." "\n";
				break;

			case EPERM :
				std::cerr <<
					"The file named by path is a directory, and either the calling process does not have appropriate privileges, or the implementation prohibits using unlink() on directories.\n"
					"The S_ISVTX flag is set on the directory containing the file referred to by the path argument and the caller is not the file owner, nor is the caller the directory owner, nor does the caller have appropriate privileges." "\n";
				break;

			case EROFS :
				std::cerr << "The directory entry to be unlinked is part of a read-only file system." "\n";
				break;

			case ETXTBSY :
				std::cerr << "The entry to be unlinked is the last directory entry to a pure procedure (shared text) file that is being executed." "\n";
				break;

			default:
				break;
		}

		return false;
	}

	std::string
	File::cleanFilepath (const char * fullPath) noexcept
	{
		if ( fullPath == nullptr )
		{
			return {};
		}

		std::string cleanPath{};

		auto startCopying = false;

		auto words = String::explode(fullPath, Separator, false);

		for ( const auto & word : words )
		{
			if ( word == "src" )
			{
				cleanPath += word;

				startCopying = true;

				continue;
			}

			if ( startCopying )
			{
				cleanPath += '/' + word;
			}
		}

		if ( cleanPath.empty() )
		{
			return fullPath;
		}

		return cleanPath;
	}

	const std::string &
	File::getFilename () const noexcept
	{
		return m_filename;
	}

	std::ostream &
	operator<< (std::ostream & out, const File & obj)
	{
		return out << obj.m_directory << obj.m_filename;
	}

	std::string
	to_string (const File & obj) noexcept
	{
		return (std::stringstream{} << obj).str();
	}
}
