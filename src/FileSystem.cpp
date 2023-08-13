/*
 * Emeraude/FileSystem.cpp
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

#include "FileSystem.hpp"

/* C/C++ standard libraries. */
#include <filesystem>
#include <iostream>

/* Local inclusion */
#include "Arguments.hpp"
#include "Path/Path.hpp"
#include "Tracer.hpp"

/* Used for get the home directory. */
#if IS_LINUX
	#include <pwd.h>
	#include <unistd.h>
#elif IS_WINDOWS
	#include <Shlobj.h>
#elif IS_MACOS
	/* TODO ... */
#endif

namespace Emeraude
{
	using namespace Libraries;

	const size_t FileSystem::ClassUID{Observable::getClassUID()};
	FileSystem * FileSystem::s_instance{nullptr}; // NOLINT NOTE: Singleton behavior

	FileSystem::FileSystem (const Arguments & arguments, std::string applicationName) noexcept
		: ServiceInterface(ClassId), m_arguments(arguments), m_applicationName(std::move(applicationName))
	{
		if ( s_instance != nullptr )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", constructor called twice !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

			std::terminate();
		}

		s_instance = this;
	}

	FileSystem::~FileSystem ()
	{
		s_instance = nullptr;
	}

	FileSystem *
	FileSystem::instance () noexcept
	{
		return s_instance;
	}

	bool
	FileSystem::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	FileSystem::usable () const noexcept
	{
		return m_usable;
	}

	Path::Directory
	FileSystem::userDataDirectory (const std::string & append) const noexcept
	{
		/* FIXME: Check the whole method ! */
#if IS_LINUX
		Path::Directory directory{to_string(m_userDirectory) + ".local" + Path::Separator + "share" + Path::Separator + m_applicationName + Path::Separator};
#elif IS_MACOS
		#error "TODO: Check for this platform"
#elif IS_WINDOWS
		#error "TODO: Check for this platform"
#endif

		return append.empty() ? directory : directory.append(append);
	}

	bool
	FileSystem::onInitialize () noexcept
	{
		/* 1. Check for binary name and directory. */
		const auto binaryPath = m_arguments.getBinaryPath();

#if IS_WINDOWS
		std::replace(binaryPath.begin(), binaryPath.end(), '\\', Path::Separator);
#endif

		const auto position = binaryPath.find_last_of(Path::Separator);

		/* FIXME: Gives incorrect results when called from PATH ! */
		m_binaryDirectory = Path::Directory::getCurrentWorkingDirectory();
		m_binaryName = position == std::string::npos ? binaryPath : binaryPath.substr(position + 1);

		/* 2. Check home user directory. */
		if ( !this->checkUserDirectory() )
		{
			Tracer::fatal(ClassId, "Unable to use the user directory !");

			return false;
		}

		/* 3. Check config directories. */
		if ( !this->checkConfigDirectories() )
		{
			Tracer::error(ClassId, "Unable to reach a valid config data directory ! You can provide a custom path with argument '--config-directory'.");

			return false;
		}

		/* 4. Check data directories. */
		if ( !this->checkDataDirectories() )
		{
			Tracer::error(ClassId, "Unable to reach a valid data directory ! You can provide a custom path with argument '--data-directory'.");

			return false;
		}

		/* 5. Check cache directories. */
		if ( !this->checkCacheDirectories() )
		{
			Tracer::error(ClassId, "Unable to reach a valid cache directory ! You can provide a custom path with argument '--cache-directory'.");

			return false;
		}

#ifdef DEBUG
		std::cout << *this << '\n';
#endif

		m_usable = true;

		return true;
	}

	bool
	FileSystem::onTerminate () noexcept
	{
		return true;
	}

	bool
	FileSystem::checkUserDirectory () noexcept
	{
#if IS_LINUX
		const auto * userInfo = getpwuid(getuid());

		m_userDirectory.set(userInfo->pw_dir);
#elif IS_WINDOWS
		std::array< WCHAR, MAX_PATH > path;

		if ( SHGetFolderPathW(nullptr, CSIDL_PROFILE, nullptr, 0, path.data()) < 0 )
			return false;

		std::string userDirectory{};

		for ( auto chr : path )
		{
			if ( chr == 0 )
				break;

			userDirectory += static_cast< char >(chr);
		}

		std::replace(userDirectory.begin(), userDirectory.end(), '\\', Path::Separator);

		m_userDirectory.set(userDirectory);
#elif IS_MACOS
		#error "TODO: Check for this platform"
#endif

		return !m_userDirectory.empty();
	}

	bool
	FileSystem::checkConfigDirectories () noexcept
	{
		std::vector< std::string > directoryStrings{};

		/* Check for a forced config directory from command line arguments. */
		const auto forcedDirectory = m_arguments.get("--forced-config-directory").value();

		if ( !forcedDirectory.empty() )
		{
			directoryStrings.emplace_back(forcedDirectory);
		}
		else
		{
			/* Check for a custom config directory from command line arguments. */
			const auto customDirectory = m_arguments.get("--config-directory").value();

			if ( !customDirectory.empty() )
			{
				directoryStrings.emplace_back(customDirectory);
			}

			/* Check for standard OS config directories (User space or system space). */
#if IS_LINUX
			/* NOTE: "/etc/Emeraude/" */
			directoryStrings.emplace_back((std::stringstream{} <<
				Path::Separator << "etc" << Path::Separator << m_applicationName << Path::Separator
			).str());

			/* NOTE: "/usr/local/etc/Emeraude/" */
			directoryStrings.emplace_back((std::stringstream{} <<
				Path::Separator << "usr" << Path::Separator << "local" << Path::Separator << "etc" << Path::Separator << m_applicationName << Path::Separator
			).str());

			/* Check for a config directory next to binary. */
			directoryStrings.emplace_back(to_string(m_binaryDirectory) + "config" + Path::Separator);

			/* NOTE: "$HOME/.config/Emeraude/" [DEFAULT] */
			directoryStrings.emplace_back((std::stringstream{} <<
				m_userDirectory << ".config" << Path::Separator << m_applicationName << Path::Separator
			).str());
#elif IS_MACOS
			#error "TODO: Check for this platform"
#elif IS_WINDOWS
			#error "TODO: Check for this platform"
#endif
		}

		return FileSystem::registerDirectories(directoryStrings, true, true, m_configDirectories);
	}

	bool
	FileSystem::checkDataDirectories () noexcept
	{
		std::vector< std::string > directoryStrings{};

		/* Check for a forced data directory from command line arguments. */
		const auto forcedDirectory = m_arguments.get("--forced-data-directory").value();

		if ( !forcedDirectory.empty() )
		{
			directoryStrings.emplace_back(forcedDirectory);
		}
		else
		{
			/* Check for a custom data directory from command line arguments. */
			const auto customDirectory = m_arguments.get("--data-directory").value();

			if ( !customDirectory.empty() )
			{
				directoryStrings.emplace_back(customDirectory);
			}

			/* Check for standard OS data directories (User space or system space). */
#if IS_LINUX
			/* NOTE: "/usr/share/games/Emeraude/" */
			directoryStrings.emplace_back((std::stringstream{} <<
				Path::Separator << "usr" << Path::Separator << "share" << Path::Separator << "games" << Path::Separator << m_applicationName << Path::Separator
			).str());

			/* NOTE: "/usr/local/share/games/Emeraude/" */
			directoryStrings.emplace_back((std::stringstream{} <<
				Path::Separator << "usr" << Path::Separator << "local" << Path::Separator << "share" << Path::Separator << "games" << Path::Separator << m_applicationName << Path::Separator
			).str());

			/* Check for a data directory next to binary. */
			directoryStrings.emplace_back(to_string(m_binaryDirectory) + "data" + Path::Separator);

			/* NOTE: "$HOME/.local/share/Emeraude/" */
			directoryStrings.emplace_back((std::stringstream{} <<
				m_userDirectory << ".local" << Path::Separator << "share" << Path::Separator << m_applicationName << Path::Separator
			).str());
#elif IS_MACOS
			#error "TODO: Check for this platform"
#elif IS_WINDOWS
			#error "TODO: Check for this platform"
#endif
		}

		return FileSystem::registerDirectories(directoryStrings, false, false, m_dataDirectories);
	}

	bool
	FileSystem::checkCacheDirectories () noexcept
	{
		std::vector< std::string > directoryStrings{};

		/* Check for a forced cache directory from command line arguments. */
		const auto forcedDirectory = m_arguments.get("--forced-cache-directory").value();

		if ( !forcedDirectory.empty() )
		{
			directoryStrings.emplace_back(forcedDirectory);
		}
		else
		{
			/* Check for a custom cache directory from command line arguments. */
			const auto customDirectory = m_arguments.get("--cache-directory").value();

			if ( !customDirectory.empty() )
			{
				directoryStrings.emplace_back(customDirectory);
			}

			/* Check for standard OS cache directories (User space or system space). */
#if IS_LINUX
			/* NOTE: "/var/cache/Emeraude/" */
			directoryStrings.emplace_back((std::stringstream{} <<
				Path::Separator << "var" << Path::Separator << "cache" << Path::Separator << m_applicationName << Path::Separator
			).str());

			/* Check for a cache directory next to binary */
			directoryStrings.emplace_back(to_string(m_binaryDirectory) + "cache" + Path::Separator);

			/* NOTE: "$HOME/.cache/Emeraude/" [DEFAULT] */
			directoryStrings.emplace_back((std::stringstream{} <<
				m_userDirectory << ".cache" << Path::Separator << m_applicationName << Path::Separator
			).str());
#elif IS_MACOS
			#error "TODO: Check for this platform"
#elif IS_WINDOWS
			#error "TODO: Check for this platform"
#endif
		}

		return FileSystem::registerDirectories(directoryStrings, true, true, m_cacheDirectories);
	}

	bool
	FileSystem::registerDirectories (const std::vector< std::string > & directoryStrings, bool createLastDirectory, bool writableRequested, std::vector< Path::Directory > & directories) noexcept
	{
		for ( const auto & directoryString : directoryStrings )
		{
#if IS_WINDOWS
			std::replace(directoryString.begin(), directoryString.end(), '\\', Path::Separator);
#endif

			const Path::Directory directory{directoryString};

			/* If the directory doesn't exist, we skip it. */
			if ( !directory.exists() )
			{
				TraceInfo{ClassId} << "'" << directoryString << "' doesn't exist !";

				continue;
			}

			/* If the directory exists, but we need permission to write to it,
			 * we test and if the permission is revoked we skip it. */
			if ( writableRequested && !directory.writable() )
			{
				TraceWarning{ClassId} << "'" << directoryString << "' exists, but is not writable !";

				continue;
			}

			/* If all is ok, we keep it. */
			directories.emplace_back(directory);

			TraceSuccess{ClassId} << "Directory '" << directory << "' added !";
		}

		/* NOTE: If no directory was found, we try to create the default one. */
		if ( directories.empty() && createLastDirectory )
		{
			const auto defaultDirectory = Path::Directory{directoryStrings.back()};

			/* If we can't write the directory, we set an error ! */
			if ( !defaultDirectory.create() )
			{
				TraceError{ClassId} << "Default directory '" << defaultDirectory << "' is not writable !";

				return false;
			}

			directories.emplace_back(defaultDirectory);
		}

		return true;
	}

	const Path::Directory &
	FileSystem::userDirectory () const noexcept
	{
		return m_userDirectory;
	}

	const Path::Directory &
	FileSystem::binaryDirectory () const noexcept
	{
		return m_binaryDirectory;
	}

	const std::string &
	FileSystem::binaryName () const noexcept
	{
		return m_binaryName;
	}

	const std::vector< Path::Directory > &
	FileSystem::configDirectoriesList () const noexcept
	{
		return m_configDirectories;
	}

	const std::vector< Path::Directory > &
	FileSystem::dataDirectoriesList () const noexcept
	{
		return m_dataDirectories;
	}

	const std::vector< Path::Directory > &
	FileSystem::cacheDirectoriesList() const noexcept
	{
		return m_cacheDirectories;
	}

	Path::Directory
	FileSystem::configDirectory (const std::string & append) const noexcept
	{
		if ( m_configDirectories.empty() )
		{
			Tracer::error(ClassId, "No config directory available !");

			return {};
		}

		auto directory = m_configDirectories[0];

		return append.empty() ? directory : directory.append(append);
	}

	Path::Directory
	FileSystem::dataDirectory (const std::string & append) const noexcept
	{
		if ( m_dataDirectories.empty() )
		{
			Tracer::error(ClassId, "No data directory available !");

			return {};
		}

		auto directory = m_dataDirectories[0];

		return append.empty() ? directory : directory.append(append);
	}

	Path::Directory
	FileSystem::cacheDirectory (const std::string & append) const noexcept
	{
		if ( m_cacheDirectories.empty() )
		{
			Tracer::error(ClassId, "No cache directory available !");

			return {};
		}

		auto directory = m_cacheDirectories[0];

		return append.empty() ? directory : directory.append(append);
	}

	std::ostream &
	operator<< (std::ostream & out, const FileSystem & obj)
	{
		out <<
			"\n"
			"[Core] Engine working directories :" "\n" <<
			" - Current user home directory : " << obj.m_userDirectory << "\n"
			" - Binary directory : " << obj.m_binaryDirectory << "\n"
			" - Binary name : " << obj.m_binaryName << "\n"

			" - Config directories :" "\n";

		for ( const auto & directory : obj.m_configDirectories )
		{
			out << '\t' << directory << '\n';
		}

		out << " - Data directories :" "\n";

		for ( const auto & directory : obj.m_dataDirectories )
		{
			out << '\t' << directory << '\n';
		}

		out << " - Cache directories :" "\n";

		for ( const auto & directory : obj.m_cacheDirectories )
		{
			out << '\t' << directory << '\n';
		}

		return out;
	}

	std::string
	to_string (const FileSystem & obj) noexcept
	{
		return (std::stringstream{} << obj).str();
	}
}
