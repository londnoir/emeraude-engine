/*
 * Emeraude/Graphics/LineRasterizationControl.cpp
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

#include "LineRasterizationControl.hpp"

/* C/C++ standard libraries. */
#include <array>
#include <cmath>

/* Local inclusions */
#include "Tracer.hpp"

namespace Emeraude::Graphics
{
	using namespace Libraries;

	void
	LineRasterizationControl::enableSmoothing (bool state) noexcept
	{
		/*if ( this->isSmoothingEnabled() == state )
			return;

		if ( state )
			glEnable(GL_LINE_SMOOTH);
		else
			glDisable(GL_LINE_SMOOTH);

		glLineWidth(1.0F);*/
	}

	bool
	LineRasterizationControl::isSmoothingEnabled () const noexcept
	{
		//return glIsEnabled(GL_LINE_SMOOTH) ? true : false;
		return false;
	}

	bool
	LineRasterizationControl::setWidth (float width) noexcept
	{
		return false;
		/*if ( width <= 0.0F )
			return false;

		const auto smooth = this->isSmoothingEnabled();

		/ * Checks the granularity. * /
		GLfloat granularity;

		glGetFloatv(GL_SMOOTH_LINE_WIDTH_GRANULARITY, &granularity);

		if ( std::fmod(width, granularity) == 0.0F )
		{
			Tracer::error(ClassId, Blob() << "The " << ( smooth ? "smooth" : "aliased" ) << " line granularity is " << granularity << " !");

			return false;
		}

		/ * Checks the limit. * /
		std::array< GLfloat, 2 > range;

		if ( smooth )
			glGetFloatv(GL_SMOOTH_LINE_WIDTH_RANGE, range.data());
		else
			glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, range.data());

		if ( width < range[0] || width > range[1] )
		{
			Tracer::error(ClassId, Blob() << "The " << ( smooth ? "smooth" : "aliased" ) << " line width must be between " << range[0] << " and " << range[1] << " !");

			return false;
		}

		glLineWidth(width);

		return true;*/
	}

	float
	LineRasterizationControl::width () const noexcept
	{
		/*GLfloat value;

		glGetFloatv(GL_LINE_WIDTH, &value);

		return value;*/
		return 0.0F;
	}
}
