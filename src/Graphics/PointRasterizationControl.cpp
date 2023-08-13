/*
 * Emeraude/Graphics/PointRasterizationControl.cpp
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

#include "PointRasterizationControl.hpp"

/* C/C++ standard libraries. */
#include <array>
#include <cmath>

/* Local inclusions */
#include "Tracer.hpp"

namespace Emeraude::Graphics
{
	using namespace Libraries;

	void
	PointRasterizationControl::enableUseProgram (bool state) noexcept
	{
		/*if ( this->isUseProgramEnabled() == state )
			return;

		if ( state )
			glEnable(GL_PROGRAM_POINT_SIZE);
		else
			glDisable(GL_PROGRAM_POINT_SIZE);

		glPointSize(1.0F);*/
	}

	bool
	PointRasterizationControl::isUseProgramEnabled () const noexcept
	{
		//return glIsEnabled(GL_PROGRAM_POINT_SIZE) ? true : false;
		return false;
	}

	bool
	PointRasterizationControl::setSize (float size) noexcept
	{
		return false;
		/*if ( size <= 0.0F )
			return false;

		const auto useProgram = this->isUseProgramEnabled();

		/ * Checks the granularity. * /
		GLfloat granularity;

		glGetFloatv(GL_POINT_SIZE_GRANULARITY, &granularity);

		if ( std::fmod(size, granularity) == 0.0F )
		{
			Tracer::error(ClassId, Blob() << "The " << ( useProgram ? "program" : "regular" ) << " point granularity is " << granularity << " !");

			return false;
		}

		/ * Checks the limit. * /
		std::array< GLfloat, 2 > range;

		if ( useProgram )
			glGetFloatv(GL_PROGRAM_POINT_SIZE, range.data());
		else
			glGetFloatv(GL_POINT_SIZE_RANGE, range.data());

		if ( size < range[0] || size > range[1] )
		{
			Tracer::error(ClassId, Blob() << "The " << ( useProgram ? "program" : "regular" ) << " point width must be between " << range[0] << " and " << range[1] << " !");

			return false;
		}

		glPointSize(size);

		return true;*/
	}

	float
	PointRasterizationControl::size () const noexcept
	{
		/*GLfloat value;

		glGetFloatv(GL_POINT_SIZE, &value);

		return value;*/
		return 0.0F;
	}

	void
	PointRasterizationControl::setFadeThresholdSize (float size) noexcept
	{
		/*if ( size < 0.0F )
			return;

		glPointParameterf(GL_POINT_FADE_THRESHOLD_SIZE, size);*/
	}

	float
	PointRasterizationControl::fadeThresholdSize () const noexcept
	{
		/*GLfloat value;

		glGetFloatv(GL_POINT_FADE_THRESHOLD_SIZE, &value);

		return value;*/
		return 0.0F;
	}

	void
	PointRasterizationControl::setPointSpriteCoord (bool state) noexcept
	{
		//glPointParameterf(GL_POINT_SPRITE_COORD_ORIGIN, state ? GL_UPPER_LEFT : GL_LOWER_LEFT);
	}

	bool
	PointRasterizationControl::isPointSpriteCoordIsUpperLeft() noexcept
	{
		/*GLint value;

		glGetIntegerv(GL_POINT_SPRITE_COORD_ORIGIN, &value);

		return value == static_cast< GLenum >(GL_UPPER_LEFT);*/
		return false;
	}
}
