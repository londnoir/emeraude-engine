/*
 * Emeraude/Saphir/ShaderCompiler.hpp
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
#include <string>
#include <memory>
#include <array>

/* Local inclusions for inheritances. */
#include "ServiceInterface.hpp"

/* Local inclusions for usages. */
#include "emeraude_config.hpp"
#include "Types.hpp"

/* Third-party libraries */
#include "Third-Party-Inclusion/glslang.hpp"
#include "DirStackFileIncluder.hpp"

/* Forward declarations. */
namespace Emeraude
{
	class Arguments;
	class Settings;
}

namespace Emeraude::Saphir
{
	class AbstractShader;

	/**
	 * @brief Wrapper class around the GLSLang compiler to compile a Saphir generated shader.
	 * @extends Emeraude::ServiceInterface This is a service.
	 */
	class ShaderCompiler final : public ServiceInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"ShaderCompilerService"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			static constexpr auto ShowGeneratedSourceCodeKey = "Video/Shader/Generator/ShowGeneratedSourceCode";
			static constexpr auto DefaultShowGeneratedSourceCode = BOOLEAN_FOLLOWING_DEBUG;
			static constexpr auto ShowPreprocessedSourceCodeKey = "Video/Shader/Generator/ShowPreprocessedSourceCode";
			static constexpr auto DefaultShowPreprocessedSourceCode = BOOLEAN_FOLLOWING_DEBUG;

			/**
			 * @brief Constructs the shader compiler.
			 * @param arguments A reference to Arguments.
			 * @param coreSettings A reference to the core settings.
			 */
			ShaderCompiler (const Arguments & arguments, Settings & coreSettings) noexcept;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::ServiceInterface::usable() */
			[[nodiscard]]
			bool usable () const noexcept override;

			/**
			 * @brief Compiles a shader.
			 * @param shader A reference to a shader smart pointer.
			 * @return bool
			 */
			[[nodiscard]]
			bool compile (const std::shared_ptr< AbstractShader > & shader) noexcept;

		private:

			/* Flag names. */
			static constexpr auto IsGLSLangInitialized = 0UL;
			static constexpr auto ForceDefaultVersionAndProfile = 1UL;
			static constexpr auto ForwardCompatible = 2UL;

			/** @copydoc Emeraude::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc Emeraude::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

			/**
			 * @brief Prints compilation errors.
			 * @param shaderIdentifier A reference to a string.
			 * @param sourceCode A reference to a string.
			 * @param infoLog A pointer to a string.
			 * @return void
			 */
			static void printCompilationErrors (const std::string & shaderIdentifier, const std::string & sourceCode, const char * infoLog) noexcept;

			/**
			 * @brief Converts shader type from saphir to GLSLang.
			 * @param shaderType The Saphir shader type.
			 * @return EShLanguage
			 */
			[[nodiscard]]
			static EShLanguage shaderType (ShaderType shaderType) noexcept;

			// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members) NOTE: Services inter-connexions.
			const Arguments & m_arguments;
			Settings & m_coreSettings;
			// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members) NOTE: Services inter-connexions.
			TBuiltInResource m_builtInResource{};
			DirStackFileIncluder m_includer{};
			EProfile m_profile{ECoreProfile}; // ENoProfile
			int m_defaultVersion{100};
			EShMessages m_messageFilter{static_cast< EShMessages >(EShMsgDefault | EShMsgSpvRules | EShMsgVulkanRules | EShMsgDebugInfo)};
			std::array< bool, 8 > m_flags{
				false/*IsGLSLangInitialized*/,
				false/*ForceDefaultVersionAndProfile*/,
				true/*ForwardCompatible*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
