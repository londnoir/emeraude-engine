/*
 * Emeraude/Audio/Effects/PitchShifter.cpp
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

#include "PitchShifter.hpp"

/* Local inclusions */
#include "Tracer.hpp"
#include <Audio/OpenAL.EFX.hpp>
#include "Audio/Utility.hpp"

namespace Emeraude::Audio::Effects
{
	using namespace Libraries;

	PitchShifter::PitchShifter () noexcept
		: Abstract()
	{
		if ( this->identifier() == 0 )
			return;

		EFX::alEffecti(this->identifier(), AL_EFFECT_TYPE, AL_EFFECT_PITCH_SHIFTER);

		if ( alGetErrors("alEffecti()", __FILE__, __LINE__) )
			Tracer::error(ClassId, "Unable to generate OpenAL Pith Shifter effect !");
	}

	void
	PitchShifter::resetProperties () noexcept
	{
		if ( !EFX::isAvailable() )
			return;

		EFX::alEffecti(this->identifier(), AL_PITCH_SHIFTER_COARSE_TUNE, AL_PITCH_SHIFTER_DEFAULT_COARSE_TUNE);
		EFX::alEffecti(this->identifier(), AL_PITCH_SHIFTER_FINE_TUNE, AL_PITCH_SHIFTER_DEFAULT_FINE_TUNE);
	}

	void
	PitchShifter::setShifterCoarseTune (int value) noexcept
	{
		if ( !EFX::isAvailable() )
			return;

		if ( value < AL_PITCH_SHIFTER_MIN_COARSE_TUNE || value > AL_PITCH_SHIFTER_MAX_COARSE_TUNE )
		{
			Tracer::warning(ClassId, Blob() << "Coarse tune must be between " << AL_PITCH_SHIFTER_MIN_COARSE_TUNE << " and " << AL_PITCH_SHIFTER_MAX_COARSE_TUNE << ".");

			return;
		}

		EFX::alEffecti(this->identifier(), AL_PITCH_SHIFTER_COARSE_TUNE, value);
	}

	void
	PitchShifter::setShifterFineTune (int value) noexcept
	{
		if ( !EFX::isAvailable() )
			return;

		if ( value < AL_PITCH_SHIFTER_MIN_FINE_TUNE || value > AL_PITCH_SHIFTER_MAX_FINE_TUNE )
		{
			Tracer::warning(ClassId, Blob() << "Fine tune must be between " << AL_PITCH_SHIFTER_MIN_FINE_TUNE << " and " << AL_PITCH_SHIFTER_MAX_FINE_TUNE << ".");

			return;
		}

		EFX::alEffecti(this->identifier(), AL_PITCH_SHIFTER_FINE_TUNE, value);
	}

	int
	PitchShifter::shifterCoarseTune () const noexcept
	{
		if ( !EFX::isAvailable() )
			return 0;

		ALint value;

		EFX::alGetEffecti(this->identifier(), AL_PITCH_SHIFTER_COARSE_TUNE, &value);

		return value;
	}

	int
	PitchShifter::shifterFineTune () const noexcept
	{
		if ( !EFX::isAvailable() )
			return 0;

		ALint value;

		EFX::alGetEffecti(this->identifier(), AL_PITCH_SHIFTER_FINE_TUNE, &value);

		return value;
	}
}
