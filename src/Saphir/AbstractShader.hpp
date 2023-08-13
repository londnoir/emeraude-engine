/*
 * Emeraude/Saphir/AbstractShader.hpp
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

#pragma once

/* C/C++ standard libraries. */
#include <set>
#include <string>

/* Local inclusions for inheritances. */
#include "NamedItem.hpp"

/* Local inclusions for usages. */
#include "Path/File.hpp"
#include "Types.hpp"

namespace Emeraude::Saphir
{
	/**
	 * @brief Defines a shader that can be filled with source code and compiled. Or directly filled with binary code.
	 * @extends Libraries::NamedItem
	 */
	class AbstractShader : public Libraries::NamedItem
	{
		friend class ShaderGenerator;
		friend class ShaderCompiler;

		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractShader (const AbstractShader & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractShader (AbstractShader && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return AbstractShader &
			 */
			AbstractShader & operator= (const AbstractShader & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return AbstractShader &
			 */
			AbstractShader & operator= (AbstractShader && copy) noexcept = delete;

			/**
			 * @brief Destructs an abstract shader.
			 */
			~AbstractShader () override = default;

			/**
			 * @brief Sets the source code for this shader.
			 * @param sourceCode The source code.
			 * @return void
			 */
			virtual void setSourceCode (const std::string & sourceCode) noexcept final;

			/**
			 * @brief Loads source code from a file.
			 * @param filepath A reference to a filepath.
			 * @return bool
			 */
			virtual bool loadSourceCode (const Libraries::Path::File & filepath) noexcept final;

			/**
			 * @brief Writes the source code to a file.
			 * @param filepath A reference to a filepath.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool writeSourceCode (const Libraries::Path::File & filepath) const noexcept final;

			/**
			 * @brief Returns the source code.
			 * @return const std::string &
			 */
			[[nodiscard]]
			virtual const std::string & sourceCode () const noexcept final;

			/**
			 * @brief Returns the hash of the source code.
			 * @return size_t
			 */
			[[nodiscard]]
			virtual size_t hash () const noexcept final;

			/**
			 * @brief Returns whether a source code is present.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isGenerated () const noexcept final;

			/**
			 * @brief Sets the binary for this shader.
			 * @note This should be done by Saphir::ShaderCompiler.
			 * @param binary The source code.
			 * @return void
			 */
			virtual void setBinaryCode (const ShaderBinary & binary) noexcept final;

			/**
			 * @brief Loads binary from a file.
			 * @param filepath A reference to a filepath.
			 * @return bool
			 */
			virtual bool loadBinaryCode (const Libraries::Path::File & filepath) noexcept final;

			/**
			 * @brief Writes the binary code to a file.
			 * @param filepath A reference to a filepath.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool writeBinaryCode (const Libraries::Path::File & filepath) const noexcept final;

			/**
			 * @brief Returns whether a binary code is present.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isCompiled () const noexcept final;

			/**
			 * @brief Returns the binary of the shader.
			 * @return const ShaderBinary &
			 */
			[[nodiscard]]
			virtual const ShaderBinary & binary () const noexcept final;

			/**
			 * @brief Erases the binary data.
			 * @return void
			 */
			virtual void clearBinary () noexcept final;

			/**
			 * @brief Returns a list of available uniform symbols in the shader.
			 * @return const std::set< std::string > &
			 */
			[[nodiscard]]
			virtual const std::set< std::string > & uniforms () const noexcept final;

			/**
			 * @brief Returns a list of available uniform block symbols in the shader.
			 * @return const std::set< std::string > &
			 */
			[[nodiscard]]
			virtual const std::set< std::string > & uniformBlocks () const noexcept final;

			/**
			 * @brief Returns a list of available shader storage block symbols in the shader.
			 * @return const std::set< std::string > &
			 */
			[[nodiscard]]
			virtual const std::set< std::string > & shaderStorageBlocks () const noexcept final;

			/**
			 * @brief Declares the use of an uniform symbol.
			 * @param name The name of the variable in the source code.
			 * @return void
			 */
			virtual void declareUniform (const std::string & name) noexcept final;

			/**
			 * @brief Declares the use of an uniform block symbol.
			 * @param name The name of the variable in the source code.
			 * @return void
			 */
			virtual void declareUniformBlock (const std::string & name) noexcept final;

			/**
			 * @brief Declares the use of a shader storage block symbol.
			 * @param name The name of the variable in the source code.
			 * @return void
			 */
			virtual void declareShaderStorageBlock (const std::string & name) noexcept final;

			/**
			 * @brief Returns the shader type.
			 * @return ShaderType
			 */
			[[nodiscard]]
			virtual ShaderType type () const noexcept = 0;

		protected:

			/**
			 * @brief Constructs an abstract shader.
			 * @param name The name of the shader for identification.
			 */
			explicit AbstractShader (const std::string & name) noexcept;

		private:

			/**
			 * @brief Generates a hash from the source code.
			 * @return void
			 */
			virtual void generateHash () noexcept;

			std::string m_sourceCode{};
			size_t m_sourceCodeHash{0};
			ShaderBinary m_binaryCode{};
			std::set< std::string > m_uniforms{};
			std::set< std::string > m_uniformBlocks{};
			std::set< std::string > m_shaderStorageBlocks{};
	};
}
