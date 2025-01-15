#pragma once

/* Project configuration. */
#include "emeraude_config.hpp"

/* STL inclusions. */
#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>

namespace Libraries::IO
{
#if IS_WINDOWS
	constexpr char Separator = '\\';
#else
	constexpr char Separator = '/';
#endif

	/**
	 * @brief Checks if the directory exists on disk.
	 * @param filepath A reference to a filesystem path.
	 * @return bool
	 */
	[[nodiscard]]
	bool fileExists (const std::filesystem::path & filepath) noexcept;

	/**
	 * @brief Return the file size in bytes.
	 * @param filepath A reference to a filesystem path.
	 * @return size_t
	 */
	[[nodiscard]]
	size_t filesize (const std::filesystem::path & filepath) noexcept;

	/**
	 * @brief Creates an empty file at pointed location.
	 * @param filepath A reference to a filesystem path.
	 * @return bool
	 */
	bool createFile (const std::filesystem::path & filepath) noexcept;

	/**
	 * @brief Deletes a file.
	 * @warning This is a destructive function.
	 * @param filepath A reference to a filesystem path.
	 * @return bool
	 */
	bool eraseFile (const std::filesystem::path & filepath) noexcept;

	/**
	 * @brief Checks if the directory exists on disk.
	 * @param path A reference to a filesystem path.
	 * @return bool
	 */
	[[nodiscard]]
	bool directoryExists (const std::filesystem::path & path) noexcept;

	/**
	 * @brief Returns whether a directory content is empty.
	 * @param path A reference to a filesystem path.
	 * @return size_t
	 */
	[[nodiscard]]
	bool isDirectoryContentEmpty (const std::filesystem::path & path) noexcept;
	
	/**
	 * @brief Returns the content list of a directory.
	 * @param path A reference to a filesystem path.
	 * @return std::vector< std::filesystem::path >
	 */
	[[nodiscard]]
	std::vector< std::filesystem::path > directoryEntries (const std::filesystem::path & path) noexcept;

	/**
	 * @brief Creates a directory.
	 * @param path A reference to a filesystem path.
	 * @param removeFileSection Ignore the last part of the path. Default false.
	 * @return bool
	 */
	bool createDirectory (const std::filesystem::path & path, bool removeFileSection = false) noexcept;

	/**
	 * @brief Deletes a directory.
	 * @warning This is a destructive function.
	 * @param path A reference to a filesystem path.
	 * @param recursive Will deletes everything in the directory. Default false.
	 * @return bool
	 */
	bool eraseDirectory (const std::filesystem::path & path, bool recursive = false) noexcept;

	/**
	 * @brief Returns the current working directory.
	 * @return std::filesystem::path
	 */
	[[nodiscard]]
	std::filesystem::path getCurrentWorkingDirectory () noexcept;

	/**
	 * @brief Checks if the directory exists on disk.
	 * @param path A reference to a filesystem path.
	 * @return bool
	*/
	[[nodiscard]]
	bool exists (const std::filesystem::path & path) noexcept;

	/**
	 * @brief Checks whether the path has give the read permission to the application.
	 * @param path A reference to a filesystem path.
	 * @return bool
	 */
	[[nodiscard]]
	bool readable (const std::filesystem::path & path) noexcept;

	/**
	 * @brief Checks whether the path has give the write permission to the application.
	 * @param path A reference to a filesystem path.
	 * @return bool
	 */
	[[nodiscard]]
	bool writable (const std::filesystem::path & path) noexcept;

	/**
	 * @brief Checks whether the path has give the execute permission to the application.
	 * @param path A reference to a filesystem path.
	 * @return bool
	 */
	[[nodiscard]]
	bool executable (const std::filesystem::path & path) noexcept;

	/**
	 * @brief Extracts the file extension from a path.
	 * @param filepath A reference to a filesystem path.
	 * @param forceToLower Force to get the extension to lower case. Default false.
	 * @return
	 */
	[[nodiscard]]
	std::string getFileExtension (const std::filesystem::path & filepath, bool forceToLower = false) noexcept;

	/**
	 * @brief Reads a file and returns the content into a string.
	 * @param filepath A reference to a filesystem path.
	 * @param content A reference to a string.
	 * @return bool
	 */
	bool fileGetContents (const std::filesystem::path & filepath, std::string & content) noexcept;

	/**
	 * @brief Writes a string to a file.
	 * @param filepath A reference to a filesystem path.
	 * @param content A reference to a string.
	 * @return bool
	 */
	bool filePutContents (const std::filesystem::path & filepath, const std::string & content) noexcept;

	/**
	 * @brief Reads a file and returns the binary content into a std::vector.
	 * @tparam data_t The type of data.
	 * @param filepath A reference to a filesystem path.
	 * @param content A reference to an unsigned int vector.
	 * @return bool
	 */
	template< typename data_t >
	bool
	fileGetContents (const std::filesystem::path & filepath, std::vector< data_t > & content) noexcept
	{
		std::ifstream file{filepath, std::ios::binary};

		if ( !file.is_open() )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", unable to read '" << filepath << "' file." "\n";

			return false;
		}

		/* NOTE: Read the file size. */
		const auto size = file.tellg();
		file.seekg(0);

		content.resize(size / sizeof(data_t) + (size % (sizeof(data_t) ? 1U : 0U)));

		file.read(reinterpret_cast< char * >(content.data()), size);
		file.close();

		return true;
	}

	/**
	 * @brief Writes binary data to a file.
	 * @tparam data_t The type of data.
	 * @param filepath A reference to a filesystem path.
	 * @param content A reference to an unsigned int vector.
	 * @return bool
	 */
	template< typename data_t >
	bool
	filePutContents (const std::filesystem::path & filepath, const std::vector< data_t > & content) noexcept
	{
		std::ofstream file{filepath, std::ios::binary | std::ios::trunc};

		if ( !file.is_open() )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", unable to write into '" << filepath << "' file." "\n";

			return false;
		}

		file.write(reinterpret_cast< const char * >(content.data()), content.size() * sizeof(data_t));

		file.close();

		return true;
	}

	/**
	 * @brief Checks the directory is ready to be used and writable.
	 * @note This is useful for cache directory.
	 * @return bool
	 */
	[[nodiscard]]
	inline
	bool
	isDirectoryUsable (const std::filesystem::path & path) noexcept
	{
		if ( directoryExists(path) )
		{
			return writable(path);
		}

		return createDirectory(path);
	}
}
