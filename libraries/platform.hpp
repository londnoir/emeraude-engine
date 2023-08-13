/*
 * Libraries/platform.hpp
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

/*
 * NOTE: Cross-platform compilation warnings management.
 *  - COMPILATION_SILENCE_WARNINGS/COMPILATION_RESTORE_WARNINGS tells the compiler to silent every incoming warnings and restore it.
 *	This is useful for third-party libraries inclusions.
 *	!!! DO NOT USE THIS FOR THE PROJECT CODE !!!
 *  - COMPILATION_WARNING(WARNING_MSG) produce a compiler warning.
 */
#ifdef ENABLE_CROSS_PLATFORM_WARNINGS_MANAGEMENT
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
		#error "Unable to determine the compiler ! Disable ENABLE_CROSS_PLATFORM_WARNINGS_MANAGEMENT to get rid of this message."
	#endif
#else
	/* NOTE: These definitions will disable macro used in the code. */
	#define COMPILATION_WARNING(WARNING_MSG)
	#define COMPILATION_SILENCE_WARNINGS
	#define COMPILATION_RESTORE_WARNINGS
#endif

#if defined linux || defined __linux || defined __linux__
	/* Linux version */
	#define IS_LINUX 1
	#define IS_WINDOWS 0
	#define IS_MACOS 0
	#if defined __i386__
		#define IS_32BIT_PLATFORM 1
		#define IS_64BIT_PLATFORM 0
		#define IS_DESKTOP_PLATFORM 1
		#define IS_EMBEDDED_PLATFORM 0
		#define PLATFORM_TARGETED "linux-desktop-32bit"
		#define WEB_BROWSER_PLATFORM "X11; Linux i686"
	#elif defined __x86_64__
		#define IS_32BIT_PLATFORM 0
		#define IS_64BIT_PLATFORM 1
		#define IS_DESKTOP_PLATFORM 1
		#define IS_EMBEDDED_PLATFORM 0
		#define PLATFORM_TARGETED "linux-desktop-64bit"
		#define WEB_BROWSER_PLATFORM "X11; Linux x86_64"
	#elif defined __arm__
		#define IS_32BIT_PLATFORM 1
		#define IS_64BIT_PLATFORM 0
		#define IS_DESKTOP_PLATFORM 0
		#define IS_EMBEDDED_PLATFORM 1
		#define PLATFORM_TARGETED "linux-embedded-32bit"
		#define WEB_BROWSER_PLATFORM "Linux armv7l"
	#elif defined __aarch64__
		#define IS_32BIT_PLATFORM 0
		#define IS_64BIT_PLATFORM 1
		#define IS_DESKTOP_PLATFORM 0
		#define IS_EMBEDDED_PLATFORM 1
		#define PLATFORM_TARGETED "linux-embedded-64bit"
		#define WEB_BROWSER_PLATFORM "Linux aarch64" // ARM64 or ARMv8
	#else
		#error Unsupported architecture
	#endif
#elif defined _WIN32 || _WIN64
	/* Windows version */
	#define IS_LINUX 0
	#define IS_WINDOWS 1
	#define IS_MACOS 0
	#if defined __i386__
		#define IS_32BIT_PLATFORM 1
		#define IS_64BIT_PLATFORM 0
		#define IS_DESKTOP_PLATFORM 1
		#define IS_EMBEDDED_PLATFORM 0
		#define PLATFORM_TARGETED "windows-desktop-32bit"
		#define WEB_BROWSER_PLATFORM "Windows NT 0.0; Win32; x86"
	#elif defined __x86_64__
		#define IS_32BIT_PLATFORM 0
		#define IS_64BIT_PLATFORM 1
		#define IS_DESKTOP_PLATFORM 1
		#define IS_EMBEDDED_PLATFORM 0
		#define PLATFORM_TARGETED "windows-desktop-64bit"
		#define WEB_BROWSER_PLATFORM "Windows NT 0.0; Win64; x64"
	#else
		#error Unsupported architecture
	#endif
#elif defined __APPLE__
	/* Apple version */
	#define IS_LINUX 0
	#define IS_WINDOWS 0
	#define IS_MACOS 1
	#if defined __i386__
		#define IS_32BIT_PLATFORM 1
		#define IS_64BIT_PLATFORM 0
		#define IS_DESKTOP_PLATFORM 1
		#define IS_EMBEDDED_PLATFORM 0
		#define PLATFORM_TARGETED "macos-desktop-32bit"
		#define WEB_BROWSER_PLATFORM "Macintosh; Intel Mac OS X 0.0"
	#elif defined __x86_64__
		#define IS_32BIT_PLATFORM 0
		#define IS_64BIT_PLATFORM 1
		#define IS_DESKTOP_PLATFORM 1
		#define IS_EMBEDDED_PLATFORM 0
		#define PLATFORM_TARGETED "macos-desktop-64bit"
		#define WEB_BROWSER_PLATFORM "Macintosh; Intel Mac OS X 0.0"
	#else
		#error Unsupported architecture
	#endif
#endif

/* NOTE: Code will use the GCC macro for printing function signature. */
#ifndef __PRETTY_FUNCTION__
	#ifdef _MSC_VER
		#define __PRETTY_FUNCTION__ __FUNCSIG__
	#else
		#define __PRETTY_FUNCTION__ __FUNCTION__
	#endif
#endif
