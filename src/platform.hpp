/*
 * src/platform.hpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2024 - "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emeraude-Engine; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Complete project and additional information can be found at :
 * https://bitbucket.org/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#pragma once

/*
 * NOTE: Cross-platform compilation warnings management.
 *  - COMPILATION_SILENCE_WARNINGS/COMPILATION_RESTORE_WARNINGS tells the compiler to silent every incoming warnings and restore it.
 *	This is useful for third-party libraries inclusions.
 *	!!! DO NOT USE THIS FOR THE PROJECT CODE !!!
 *  - COMPILATION_WARNING(WARNING_MSG) produce a compiler warning.
 */
#ifdef EMERAUDE_ENABLE_CROSS_PLATFORM_WARNINGS_MANAGEMENT
	/* NOTE: Trick to get a macro expanded into a string for use in another macro. */
	#define CWM_STRINGIFY(a) #a

	#if defined(__GNUC__) || defined(__clang__)
		/* Silence and restore warning macros.
		 * NOTE: GCC/Clang compiler forces to explicitly set every item to ignore.
		 * Add here every annoying warning coming from third-party libraries. */
		#define COMPILATION_SILENCE_WARNINGS _Pragma("GCC diagnostic push") \
			_Pragma("GCC diagnostic ignored \"-Wall\"") \
			_Pragma("GCC diagnostic ignored \"-Wextra\"") \
			_Pragma("GCC diagnostic ignored \"-Wpedantic\"") \
			_Pragma("GCC diagnostic ignored \"-Wpadded\"") \
			_Pragma("GCC diagnostic ignored \"-Weffc++\"") \
			_Pragma("GCC diagnostic ignored \"-Wpragmas\"") \
			_Pragma("GCC diagnostic ignored \"-Wdocumentation\"") \
			_Pragma("GCC diagnostic ignored \"-Wdocumentation-unknown-command\"") \
			_Pragma("GCC diagnostic ignored \"-Wold-style-cast\"") \
			_Pragma("GCC diagnostic ignored \"-Wreserved-id-macro\"") \
			_Pragma("GCC diagnostic ignored \"-Wunused\"")
		#define COMPILATION_RESTORE_WARNINGS _Pragma("GCC diagnostic pop")

		/* Cross-platform warning function macro. */
		#define COMPILATION_WARNING(WARNING_MSG) _Pragma(CWM_STRINGIFY(GCC warning WARNING_MSG))
	#elif defined(_MSC_VER)
		/* Silence and restore warning macros. */
		#define COMPILATION_SILENCE_WARNINGS _Pragma("warning( push, 0 )")
		#define COMPILATION_RESTORE_WARNINGS _Pragma("warning( pop )")

		/* Cross-platform warning function macro. */
		#define COMPILATION_WARNING(WARNING_MSG) _Pragma(CWM_STRINGIFY(message(WARNING_MSG)))
	#else
		#error "Unable to determine the compiler ! Disable EMERAUDE_ENABLE_CROSS_PLATFORM_WARNINGS_MANAGEMENT to get rid of this message."
	#endif
#else
	/* NOTE: These definitions will disable macro used in the code. */
	#define COMPILATION_WARNING(WARNING_MSG)
	#define COMPILATION_SILENCE_WARNINGS
	#define COMPILATION_RESTORE_WARNINGS
#endif

#if defined(__i386__) || defined(_M_IX86) // Major detection of x86 32bit architecture.
	#define IS_X86_ARCH 1
	#define IS_ARM_ARCH 0
	#define IS_32BIT_PLATFORM 1
	#define IS_64BIT_PLATFORM 0
	#define PLATFORM_PRECISION "32bit"
	#define PLATFORM_ARCH "x86_32"
	#define PLATFORM_ARCH_NICENAME "Intel x86"
#elif defined(__x86_64__) || defined(__amd64__) || defined(_M_AMD64) || defined(_WIN64) // Major detection of x86 64bit architecture.
	#define IS_X86_ARCH 1
	#define IS_ARM_ARCH 0
	#define IS_32BIT_PLATFORM 0
	#define IS_64BIT_PLATFORM 1
	#define PLATFORM_PRECISION "64bit"
	#define PLATFORM_ARCH "x86_64"
	#define PLATFORM_ARCH_NICENAME "AMD64"
#elif defined(__arm__) // Major detection of ARM 32bit architecture.
	#define IS_X86_ARCH 0
	#define IS_ARM_ARCH 1
	#define IS_32BIT_PLATFORM 1
	#define IS_64BIT_PLATFORM 0
	#define PLATFORM_PRECISION "32bit"
	#define PLATFORM_ARCH "arm"
	#define PLATFORM_ARCH_NICENAME "ARMv7" // Should be the ARMv7
#elif defined(__aarch64__) || defined(__arm64__) // Major detection of ARM 64bit architecture.
	#define IS_X86_ARCH 0
	#define IS_ARM_ARCH 1
	#define IS_32BIT_PLATFORM 0
	#define IS_64BIT_PLATFORM 1
	#define PLATFORM_PRECISION "64bit"
	#define PLATFORM_ARCH "arm64"
	#define PLATFORM_ARCH_NICENAME "AArch64"
#else
	#error "Unsupported architecture !"
#endif

#if defined(linux) || defined(__linux) || defined(__linux__) // Major detection of Linux OS
	#define IS_LINUX 1
	#define IS_WINDOWS 0
	#define IS_MACOS 0
	#define OS_NAME "linux"
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_WIN64) // Major detection of Windows OS
	#define IS_LINUX 0
	#define IS_WINDOWS 1
	#define IS_MACOS 0
	#define OS_NAME "windows"
#elif defined(__APPLE__) // Major detection of Apple OS
	#define IS_LINUX 0
	#define IS_WINDOWS 0
	#define IS_MACOS 1
	#define OS_NAME "macos"
#else
	#error "Unsupported OS !"
#endif

#define PLATFORM_TARGETED OS_NAME "-" PLATFORM_PRECISION "-" PLATFORM_ARCH

/* NOTE: Code will use the GCC macro for printing function signature. */
#ifndef __PRETTY_FUNCTION__ // NOLINT(bugprone-reserved-identifier)
	#ifdef _MSC_VER
		#define __PRETTY_FUNCTION__ __FUNCSIG__
	#else
		#define __PRETTY_FUNCTION__ __FUNCTION__
	#endif
#endif
