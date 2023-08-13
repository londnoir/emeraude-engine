/*
 * Emeraude/Audio/Filters/BandPass.cpp
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

#include "BandPass.hpp"

/* Local inclusions */
#include "Tracer.hpp"
#include <Audio/OpenAL.EFX.hpp>
#include "Audio/Utility.hpp"

namespace Emeraude::Audio::Filters
{
	using namespace Libraries;

	BandPass::BandPass () noexcept
		: Abstract()
	{
		if ( this->identifier() == 0 )
			return;

		EFX::alFilteri(this->identifier(), AL_FILTER_TYPE, AL_FILTER_BANDPASS);

		if ( alGetErrors("alFilteri()", __FILE__, __LINE__) )
			Tracer::error(ClassId, "Unable to generate OpenAL Band-Pass filter !");
	}

	void
	BandPass::resetProperties () noexcept
	{
		if ( !EFX::isAvailable() )
			return;

		EFX::alFilterf(this->identifier(), AL_BANDPASS_GAIN, AL_BANDPASS_DEFAULT_GAIN);
		EFX::alFilterf(this->identifier(), AL_BANDPASS_GAINHF, AL_BANDPASS_DEFAULT_GAINHF);
		EFX::alFilterf(this->identifier(), AL_BANDPASS_GAINLF, AL_BANDPASS_DEFAULT_GAINLF);
	}

	void
	BandPass::setGain (float value) noexcept
	{
		if ( !EFX::isAvailable() )
			return;

		if ( value < AL_BANDPASS_MIN_GAIN || value > AL_BANDPASS_MAX_GAIN )
		{
			Tracer::warning(ClassId, Blob() << "Gain must be between " << AL_BANDPASS_MIN_GAIN << " and " << AL_BANDPASS_MAX_GAIN << ".");

			return;
		}

		EFX::alFilterf(this->identifier(), AL_BANDPASS_GAIN, value);
	}

	void
	BandPass::setGainHF (float value) noexcept
	{
		if ( !EFX::isAvailable() )
			return;

		if ( value < AL_BANDPASS_MIN_GAINHF || value > AL_BANDPASS_MAX_GAINHF )
		{
			Tracer::warning(ClassId, Blob() << "Gain must be between " << AL_BANDPASS_MIN_GAINHF << " and " << AL_BANDPASS_MAX_GAINHF << ".");

			return;
		}

		EFX::alFilterf(this->identifier(), AL_BANDPASS_GAINHF, value);
	}

	void
	BandPass::setGainLF (float value) noexcept
	{
		if ( !EFX::isAvailable() )
			return;

		if ( value < AL_BANDPASS_MIN_GAINLF || value > AL_BANDPASS_MAX_GAINLF )
		{
			Tracer::warning(ClassId, Blob() << "Gain must be between " << AL_BANDPASS_MIN_GAINLF << " and " << AL_BANDPASS_MAX_GAINLF << ".");

			return;
		}

		EFX::alFilterf(this->identifier(), AL_BANDPASS_GAINLF, value);
	}

	float
	BandPass::gain () const noexcept
	{
		if ( !EFX::isAvailable() )
			return 0.0F;

		ALfloat value;

		EFX::alGetFilterf(this->identifier(), AL_BANDPASS_GAIN, &value);

		return value;
	}

	float
	BandPass::gainHF () const noexcept
	{
		if ( !EFX::isAvailable() )
			return 0.0F;

		ALfloat value;

		EFX::alGetFilterf(this->identifier(), AL_BANDPASS_GAINHF, &value);

		return value;
	}

	float
	BandPass::gainLF () const noexcept
	{
		if ( !EFX::isAvailable() )
			return 0.0F;

		ALfloat value;

		EFX::alGetFilterf(this->identifier(), AL_BANDPASS_GAINLF, &value);

		return value;
	}
}
