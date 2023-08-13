/*
 * Emeraude/Saphir/ShaderManager.cpp
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

#include "ShaderManager.hpp"

/* Local inclusions */
#include "Tracer.hpp"
#include "Arguments.hpp"
#include "Settings.hpp"
#include "FileSystem.hpp"
#include "ShaderCompiler.hpp"
#include "SourceCodeParser.hpp"
#include "Vulkan/ShaderModule.hpp"

namespace Emeraude::Saphir
{
	using namespace Libraries;
	using namespace Vulkan;

	const size_t ShaderManager::ClassUID{Observable::getClassUID()};
	ShaderManager * ShaderManager::s_instance{nullptr}; // NOLINT NOTE: Singleton behavior

	ShaderManager::ShaderManager (const Arguments & arguments, const FileSystem & fileSystem, Settings & coreSettings, ShaderCompiler & shaderCompiler) noexcept
		: ServiceInterface(ClassId), m_arguments(arguments), m_fileSystem(fileSystem), m_coreSettings(coreSettings), m_shaderCompiler(shaderCompiler)
	{
		if ( s_instance != nullptr )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", constructor called twice !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

			std::terminate();
		}

		s_instance = this;
	}

	ShaderManager::~ShaderManager ()
	{
		s_instance = nullptr;
	}

	ShaderManager *
	ShaderManager::instance () noexcept
	{
		return s_instance;
	}

	bool
	ShaderManager::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	ShaderManager::usable () const noexcept
	{
		return m_flags[Usable];
	}

	bool
	ShaderManager::onInitialize () noexcept
	{
		/* Read core settings. */
		m_flags[ShowLoadedSourceCode] = m_coreSettings.getAs< bool >(ShowLoadedSourceCodeKey, DefaultShowLoadedSourceCode);
		m_flags[SourceCodeCacheEnabled] = m_coreSettings.getAs< bool >(SourceCodeCacheEnabledKey, DefaultSourceCodeCacheEnabled);
		m_flags[BinaryCacheEnabled] = m_coreSettings.getAs< bool >(BinaryCacheEnabledKey, DefaultBinaryCacheEnabled);

		/* Shader source cache directory. */
		m_shadersSourcesDirectory = m_fileSystem.cacheDirectory(ShaderSourcesDirectoryName);

		if ( !m_shadersSourcesDirectory.create() )
		{
			TraceError{ClassId} << "Unable to create '" << m_shadersSourcesDirectory << "' directory !";

			return false;
		}

		/* Shader binaries cache directory. */
		m_shadersBinariesDirectory = m_fileSystem.cacheDirectory(ShaderBinariesDirectoryName);

		if ( !m_shadersBinariesDirectory.create() )
		{
			TraceError{ClassId} << "Unable to create '" << m_shadersBinariesDirectory << "' directory !";

			return false;
		}

		/* Checks shader cache. */
		if ( m_arguments.get("--clear-shader-cache").isPresent() )
		{
			this->clearCache();
		}
		else
		{
			this->readCache();
		}

		m_flags[Usable] = true;

		return true;
	}

	bool
	ShaderManager::onTerminate () noexcept
	{
		m_flags[Usable] = false;

		m_cachedShaderBinaries.clear();
		m_cachedShaderSourceCodes.clear();
		m_shaders.clear();

		return true;
	}

	bool
	ShaderManager::cacheShaderSourceCode (const AbstractShader & shader) noexcept
	{
		if ( !m_flags[SourceCodeCacheEnabled] )
		{
			return true;
		}

		const auto cacheFilepath = this->generateShaderSourceCacheFilepath(shader);

		if ( cacheFilepath.empty() )
		{
			TraceError{ClassId} << "Unable to get a proper source cache path for shader '" << shader.name() << "' !";

			return false;
		}

		if ( !shader.writeSourceCode(cacheFilepath) )
		{
			TraceError{ClassId} << "Unable to write the source cache file '" << cacheFilepath << "' for shader '" << shader.name() << "' !";

			return false;
		}

		return true;
	}

	bool
	ShaderManager::cacheShaderBinary (const AbstractShader & shader) noexcept
	{
		if ( !m_flags[BinaryCacheEnabled] )
		{
			return true;
		}

		const auto cacheFilepath = this->generateShaderBinaryCacheFilepath(shader);

		if ( cacheFilepath.empty() )
		{
			TraceError{ClassId} << "Unable to get a proper binary cache path for shader '" << shader.name() << "' !";

			return false;
		}

		if ( !shader.writeBinaryCode(cacheFilepath) )
		{
			TraceError{ClassId} << "Unable to write the binary cache file '" << cacheFilepath << "' for shader '" << shader.name() << "' !";

			return false;
		}

		return true;
	}

	bool
	ShaderManager::checkBinaryFromCache (AbstractShader & shader) noexcept
	{
		if ( !m_flags[BinaryCacheEnabled] )
		{
			return false;
		}

		auto binaryIt = m_cachedShaderBinaries.find(shader.hash());

		if ( binaryIt == m_cachedShaderBinaries.cend() )
		{
			return false;
		}

		/* Load the binary from cache. */
		shader.loadBinaryCode(binaryIt->second);

		return true;
	}

	std::shared_ptr< ShaderModule >
	ShaderManager::getShaderModuleFromGeneratedShader (const std::shared_ptr< Vulkan::Device > & device, const std::shared_ptr< AbstractShader > & shader) noexcept
	{
		if ( !this->usable() )
		{
			Tracer::error(ClassId, "There is no device to load create the shader module !");

			return {};
		}

		/* The shader must have a source code before anything else.
		 * The hash depend on it. */
		if ( !shader->isGenerated() )
		{
			TraceError{ClassId} << "The shader '" << shader->name() << "' is empty ! Generate it first.";

			return {};
		}

		if ( m_flags[ShowLoadedSourceCode] )
		{
			const SourceCodeParser parser{shader->sourceCode()};

			TraceInfo{ClassId} << "\n"
				"****** START OF LOADED GLSL SHADER CODE ******" "\n" <<
				parser.getParsedSourceCode() <<
				"******  END OF LOADED GLSL SHADER CODE  ******" "\n";
		}

		const auto shaderHash = shader->hash();

		/* Checks in loaded shader list with the hash. */
		const auto shaderIt = m_shaders.find(shaderHash);

		if ( shaderIt != m_shaders.cend() )
		{
			TraceSuccess{ClassId} << "The shader '" << shader->name() << "' already loaded !";

			return shaderIt->second;
		}

		/* Checks in cached binaries to prevent a compilation. */
		if ( this->checkBinaryFromCache(*shader) )
		{
			TraceSuccess{ClassId} << "The shader '" << shader->name() << "' loaded from binary cache !";
		}
		else
		{
			/* Checks whether the shader is already compiled. */
			if ( !shader->isCompiled() )
			{
				this->cacheShaderSourceCode(*shader);

				/* If not, we compile it. */
				if ( m_shaderCompiler.compile(shader) )
				{
					TraceSuccess{ClassId} << "The shader '" << shader->name() << "' is successfully compiled !";

					this->cacheShaderBinary(*shader);
				}
				else
				{
					TraceError{ClassId} << "Unable to compile shader '" << shader->name() << "' !";

					return {};
				}
			}
		}

		auto shaderModule = std::make_shared< ShaderModule >(device, shader);
		shaderModule->setIdentifier((std::stringstream{} << "ShaderManager-" << shader->name() << "-ShaderModule").str());

		if ( !shaderModule->createOnHardware() )
		{
			Tracer::error(ClassId, "Unable to create a shader module !");

			return {};
		}

		/* Save a copy into loaded shaders with the associated vulkan shader module. */
		auto result = m_shaders.emplace(shaderHash, shaderModule);

		return result.first->second;
	}

	void
	ShaderManager::readCache () noexcept
	{
		for ( const auto & entry : m_shadersSourcesDirectory.entries() )
		{
			const Path::File filepath{entry};

			if ( !filepath.hasExtensions(ShaderFileExtensions.data(), ShaderFileExtensions.size()) )
			{
				continue;
			}

			auto hash = ShaderManager::extractHashFromFilepath(filepath);

			if ( hash == 0 )
			{
				TraceError{ClassId} << "The hash from shader source file '" << entry << "' is invalid !";

				continue;
			}

			m_cachedShaderSourceCodes.emplace(hash, filepath);
		}

		for ( const auto & entry : m_shadersBinariesDirectory.entries() )
		{
			const Path::File filepath{entry};

			if ( !filepath.hasExtension("bin") )
			{
				continue;
			}

			auto hash = ShaderManager::extractHashFromFilepath(filepath);

			if ( hash == 0 )
			{
				TraceError{ClassId} << "The hash from shader binary file '" << entry << "' is invalid !";

				continue;
			}

			m_cachedShaderBinaries.emplace(hash, filepath);
		}
	}

	void
	ShaderManager::clearCache () noexcept
	{
		for ( const auto & entry : m_shadersSourcesDirectory.entries() )
		{
			const Path::File filepath{entry};

			if ( !filepath.hasExtensions(ShaderFileExtensions.data(), ShaderFileExtensions.size()) )
			{
				continue;
			}

			if ( !Path::File::erase(entry) )
			{
				TraceError{ClassId} << "Unable to erase '" << entry << "' !";
			}
		}

		m_cachedShaderSourceCodes.clear();

		for ( const auto & entry : m_shadersBinariesDirectory.entries() )
		{
			const Path::File filepath{entry};

			if ( !filepath.hasExtension("bin") )
			{
				continue;
			}

			if ( !Path::File::erase(entry) )
			{
				TraceError{ClassId} << "Unable to erase '" << entry << "' !";
			}
		}

		m_cachedShaderBinaries.clear();
	}

	Path::File
	ShaderManager::generateShaderSourceCacheFilepath (const AbstractShader & shader) const noexcept
	{
		return {m_shadersSourcesDirectory, (std::stringstream{} << shader.name() << '_' << shader.hash() << '.' << getShaderFileExtension(shader.type())).str()};
	}

	Path::File
	ShaderManager::generateShaderBinaryCacheFilepath (const AbstractShader & shader) const noexcept
	{
		return {m_shadersBinariesDirectory, (std::stringstream{} << shader.name() << '_' << shader.hash() << ".bin").str()};
	}

	size_t
	ShaderManager::extractHashFromFilepath (const Path::File & filepath) noexcept
	{
		const auto & filename = filepath.getFilename();

		auto tmpA = String::explode(filename, '_');

		if ( tmpA.size() != 2 )
		{
			return 0;
		}

		auto tmpB = String::explode(tmpA[1], '.');

		if ( tmpB.size() != 2 )
		{
			return 0;
		}

		return std::stoull(tmpB[0]);
	}
}
