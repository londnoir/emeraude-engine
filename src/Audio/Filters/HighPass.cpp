/*
 * src/Audio/Filters/HighPass.cpp
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

#include "HighPass.hpp"

/* Local inclusions. */
#include "Tracer.hpp"
#include <Audio/OpenAL.EFX.hpp>
#include "Audio/Utility.hpp"

namespace Emeraude::Audio::Filters
{
	using namespace Libraries;

	HighPass::HighPass () noexcept
		: Abstract()
	{
		if ( this->identifier() == 0 )
			return;

		EFX::alFilteri(this->identifier(), AL_FILTER_TYPE, AL_FILTER_HIGHPASS);

		if ( alGetErrors("alFilteri()", __FILE__, __LINE__) )
			Tracer::error(ClassId, "Unable to generate OpenAL High-Pass filter !");
	}

	void
	HighPass::resetProperties () noexcept
	{
		if ( !EFX::isAvailable() )
			return;

		EFX::alFilterf(this->identifier(), AL_HIGHPASS_GAIN, AL_HIGHPASS_DEFAULT_GAIN);
		EFX::alFilterf(this->identifier(), AL_HIGHPASS_GAINLF, AL_HIGHPASS_DEFAULT_GAINLF);
	}

	void
	HighPass::setGain (float value) noexcept
	{
		if ( !EFX::isAvailable() )
			return;

		if ( value < AL_HIGHPASS_MIN_GAIN || value > AL_HIGHPASS_MAX_GAIN )
		{
			Tracer::warning(ClassId, BlobTrait() << "Gain must be between " << AL_HIGHPASS_MIN_GAIN << " and " << AL_HIGHPASS_MAX_GAIN << ".");

			return;
		}

		EFX::alFilterf(this->identifier(), AL_HIGHPASS_GAIN, value);
	}

	void
	HighPass::setGainLF (float value) noexcept
	{
		if ( !EFX::isAvailable() )
			return;

		if ( value < AL_HIGHPASS_MIN_GAINLF || value > AL_HIGHPASS_MAX_GAINLF )
		{
			Tracer::warning(ClassId, BlobTrait() << "Gain must be between " << AL_HIGHPASS_MIN_GAINLF << " and " << AL_HIGHPASS_MAX_GAINLF << ".");

			return;
		}

		EFX::alFilterf(this->identifier(), AL_HIGHPASS_GAINLF, value);
	}

	float
	HighPass::gain () const noexcept
	{
		if ( !EFX::isAvailable() )
			return 0.0F;

		ALfloat value;

		EFX::alGetFilterf(this->identifier(), AL_HIGHPASS_GAIN, &value);

		return value;
	}

	float
	HighPass::gainLF () const noexcept
	{
		if ( !EFX::isAvailable() )
			return 0.0F;

		ALfloat value;

		EFX::alGetFilterf(this->identifier(), AL_HIGHPASS_GAINLF, &value);

		return value;
	}
}
