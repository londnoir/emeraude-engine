/*
 * Emeraude/Audio/Effects/Compressor.cpp
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

#include "Compressor.hpp"

/* Local inclusions */
#include "Tracer.hpp"
#include <Audio/OpenAL.EFX.hpp>
#include "Audio/Utility.hpp"

namespace Emeraude::Audio::Effects
{
	using namespace Libraries;

	Compressor::Compressor () noexcept
		: Abstract()
	{
		if ( this->identifier() == 0 )
			return;

		EFX::alEffecti(this->identifier(), AL_EFFECT_TYPE, AL_EFFECT_COMPRESSOR);

		if ( alGetErrors("alEffecti()", __FILE__, __LINE__) )
			Tracer::error(ClassId, "Unable to generate OpenAL Compressor effect !");
	}

	void
	Compressor::resetProperties () noexcept
	{
		if ( !EFX::isAvailable() )
			return;

		EFX::alEffecti(this->identifier(), AL_COMPRESSOR_ONOFF, AL_COMPRESSOR_DEFAULT_ONOFF);
	}

	void
	Compressor::enable (bool state) noexcept
	{
		if ( !EFX::isAvailable() )
			return;

		EFX::alEffecti(this->identifier(), AL_COMPRESSOR_ONOFF, state ? AL_TRUE : AL_FALSE);
	}

	bool
	Compressor::isEnabled () const noexcept
	{
		if ( !EFX::isAvailable() )
			return false;

		ALint value;

		EFX::alGetEffecti(this->identifier(), AL_COMPRESSOR_ONOFF, &value);

		return value > 0;
	}
}
