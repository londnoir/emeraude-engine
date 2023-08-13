/*
 * Emeraude/Third-Party-Inclusion/openal.hpp
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

#include "emeraude_config.hpp"

#ifdef OPENAL_ENABLED
	COMPILATION_SILENCE_WARNINGS
	
	#if IS_WINDOWS
		#include <al.h>
		#include <alc.h>
		#include <alut.h>
		#include <alext.h>
		/* EFX extension */
		#include <efx.h>
		#include <efx-presets.h>
	#else
		#include <AL/al.h>
		#include <AL/alc.h>
		#include <AL/alut.h>
		#include <AL/alext.h>
		/* EFX extension */
		#include <AL/efx.h>
		#include <AL/efx-presets.h>
	#endif

	COMPILATION_RESTORE_WARNINGS
#else
	#ifdef DEBUG
		#pragma GCC warning "OpenAL disabled. Set EM_ENABLE_OPENAL=1 in CMake configuration."
	#endif
#endif
