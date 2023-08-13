/*
 * Emeraude/Saphir/AbstractShader.cpp
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

#include "AbstractShader.hpp"

/* C/C++ standard libraries. */
#include <functional>

/* Local inclusions */
#include "Tracer.hpp"
#include "Utility.hpp"

namespace Emeraude::Saphir
{
	using namespace Libraries;
	
	constexpr auto TracerTag{"Shader"};

	AbstractShader::AbstractShader (const std::string & name) noexcept
		: NamedItem(name)
	{

	}

	void
	AbstractShader::setSourceCode (const std::string & sourceCode) noexcept
	{
		m_sourceCode = sourceCode;

		this->generateHash();
	}

	bool
	AbstractShader::loadSourceCode (const Path::File & filepath) noexcept
	{
		const auto * extension = getShaderFileExtension(this->type());

		if ( !filepath.hasExtension(extension) )
		{
			TraceError{TracerTag} << "The shader source file extension must be '" << extension << "' !";

			return false;
		}

		if ( !Utility::fileGetContents(filepath, m_sourceCode) )
		{
			TraceError{TracerTag} << "Unable to read the shader source code from file '" << filepath << "' !";

			return false;
		}

		this->generateHash();

		return true;
	}

	bool
	AbstractShader::writeSourceCode (const Path::File & filepath) const noexcept
	{
		if ( !Utility::filePutContents(filepath, m_sourceCode) )
		{
			TraceError{TracerTag} << "Unable to write the shader source code to file '" << filepath << "' !";

			return false;
		}

		return true;
	}

	const std::string &
	AbstractShader::sourceCode () const noexcept
	{
		return m_sourceCode;
	}

	size_t
	AbstractShader::hash () const noexcept
	{
		return m_sourceCodeHash;
	}

	bool
	AbstractShader::isGenerated () const noexcept
	{
		return !m_sourceCode.empty();
	}

	void
	AbstractShader::setBinaryCode (const ShaderBinary & binary) noexcept
	{
		m_binaryCode = binary;
	}

	bool
	AbstractShader::loadBinaryCode (const Path::File & filepath) noexcept
	{
		if ( !Utility::fileGetContents(filepath, m_binaryCode) )
		{
			TraceError{TracerTag} << "Unable to read the shader binary code from file '" << filepath << "' !";

			return false;
		}

		/* FIXME: Check binary shader type */

		return true;
	}

	bool
	AbstractShader::writeBinaryCode (const Path::File & filepath) const noexcept
	{
		if ( !Utility::filePutContents(filepath, m_binaryCode) )
		{
			TraceError{TracerTag} << "Unable to write the shader binary code to file '" << filepath << "' !";

			return false;
		}

		return true;
	}

	bool
	AbstractShader::isCompiled () const noexcept
	{
		return !m_binaryCode.empty();
	}

	const ShaderBinary &
	AbstractShader::binary () const noexcept
	{
		return m_binaryCode;
	}

	void
	AbstractShader::clearBinary () noexcept
	{
		m_binaryCode.clear();
	}

	const std::set< std::string > &
	AbstractShader::uniforms () const noexcept
	{
		return m_uniforms;
	}

	const std::set< std::string > &
	AbstractShader::uniformBlocks () const noexcept
	{
		return m_uniformBlocks;
	}

	const std::set< std::string > &
	AbstractShader::shaderStorageBlocks () const noexcept
	{
		return m_shaderStorageBlocks;
	}

	void
	AbstractShader::declareUniform (const std::string & name) noexcept
	{
		m_uniforms.emplace(name);
	}

	void
	AbstractShader::declareUniformBlock (const std::string & name) noexcept
	{
		m_uniformBlocks.emplace(name);
	}

	void
	AbstractShader::declareShaderStorageBlock (const std::string & name) noexcept
	{
		m_shaderStorageBlocks.emplace(name);
	}

	void
	AbstractShader::generateHash () noexcept
	{
		if ( m_sourceCode.empty() )
		{
			m_sourceCodeHash = 0;
		}
		else
		{
			const std::hash< std::string > hashString{};

			m_sourceCodeHash = hashString(m_sourceCode);
		}
	}
}
