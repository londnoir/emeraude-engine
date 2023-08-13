/*
 * Emeraude/Graphics/Material/Helpers.cpp
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

#include "Helpers.hpp"

/* Local inclusions. */
#include "Tracer.hpp"
#include "Saphir/ShaderGenerator.hpp"
#include "Saphir/Keys.hpp"
#include "Graphics/Geometry/Interface.hpp"
#include "Interface.hpp"

namespace Emeraude::Graphics::Material
{
	using namespace Libraries;
	using namespace Emeraude::Saphir;
	using namespace Emeraude::Saphir::Keys;

	bool
	checkPrimaryTextureCoordinates (ShaderGenerator & gen, const Interface & material, const Geometry::Interface & geometry) noexcept
	{
		/* NOTE: There is no need of primary texture coordinates. */
		if ( !material.usingPrimaryTextureCoordinates() )
		{
			Tracer::debug(material.classLabel(), "Is not using primary texture coordinates !");

			return true;
		}

		/* NOTE: The texture coordinates will be generated by the shader. */
		if ( material.computesPrimaryTextureCoordinates() )
		{
			if ( material.primaryTextureCoordinatesUses3D() )
			{
				Tracer::debug(material.classLabel(), "Is computing the 3D primary texture coordinates !");

				gen.declare(Declaration::StageOutput{ShaderVariables::Primary3DTextureCoordinates, GLSL::Smooth});

				Code{gen, Location::Output} <<
											ShaderVariables::Primary3DTextureCoordinates << " = normalize(vec3(" << Attributes::Position << ".x, -" << Attributes::Position << ".y, " << Attributes::Position << ".z));";
			}
			else
			{
				Tracer::debug(material.classLabel(), "Is computing the 2D primary texture coordinates !");

				gen.declare(Declaration::StageOutput{ShaderVariables::Primary2DTextureCoordinates, GLSL::Smooth});

				Code{gen, Location::Output} <<
											ShaderVariables::Primary2DTextureCoordinates << " = normalize(vec2(" << Attributes::Position << ".x, -" << Attributes::Position << ".y));";
			}

			return true;
		}

		if ( !geometry.primaryTextureCoordinatesEnabled() )
		{
			TraceError{material.classLabel()} <<
				"The geometry '" << geometry.name() << "' has no 2D primary texture coordinates "
				"for basic material '" << material.name() << "' !";

			return false;
		}

		if ( material.primaryTextureCoordinatesUses3D() )
		{
			Tracer::debug(material.classLabel(), "Is using 3D primary texture coordinates !");

			if ( !geometry.primaryTextureCoordinates3DEnabled() )
			{
				TraceError{material.classLabel()} <<
					"The geometry '" << geometry.name() << "' has no 3D primary texture coordinates "
					"for basic material '" << material.name() << "' !";

				return false;
			}

			gen.requestVertexShaderSynthesizeInstruction(ShaderVariables::Primary3DTextureCoordinates);
		}
		else
		{
			Tracer::debug(material.classLabel(), "Is using 2D primary texture coordinates !");

			gen.requestVertexShaderSynthesizeInstruction(ShaderVariables::Primary2DTextureCoordinates);
		}

		return true;
	}

	bool
	checkSecondaryTextureCoordinates (ShaderGenerator & gen, const Interface & material, const Geometry::Interface & geometry) noexcept
	{
		/* NOTE: There is no need of secondary texture coordinates. */
		if ( !material.usingSecondaryTextureCoordinates() )
			return true;

		/* NOTE: The texture coordinates will be generated by the shader. */
		if ( material.computesSecondaryTextureCoordinates() )
		{
			if ( material.secondaryTextureCoordinatesUses3D() )
			{
				gen.declare(Declaration::StageOutput{ShaderVariables::Secondary3DTextureCoordinates, GLSL::Smooth});

				Code{gen, Location::Output} <<
											ShaderVariables::Secondary3DTextureCoordinates << " = normalize(vec3(" << Attributes::Position << ".x, -" << Attributes::Position << ".y, " << Attributes::Position << ".z));";
			}
			else
			{
				gen.declare(Declaration::StageOutput{ShaderVariables::Secondary2DTextureCoordinates, GLSL::Smooth});

				Code{gen, Location::Output} <<
											ShaderVariables::Secondary2DTextureCoordinates << " = normalize(vec2(" << Attributes::Position << ".x, -" << Attributes::Position << ".y));";
			}

			return true;
		}

		if ( !geometry.secondaryTextureCoordinatesEnabled() )
		{
			TraceError{material.classLabel()} <<
				"The geometry '" << geometry.name() << "' has no 2D secondary texture coordinates "
				"for basic material '" << material.name() << "' !";

			return false;
		}

		if ( material.secondaryTextureCoordinatesUses3D() )
		{
			if ( !geometry.secondaryTextureCoordinates3DEnabled() )
			{
				TraceError{material.classLabel()} <<
					"The geometry '" << geometry.name() << "' has no 3D secondary texture coordinates "
					"for basic material '" << material.name() << "' !";

				return false;
			}

			gen.requestVertexShaderSynthesizeInstruction(ShaderVariables::Secondary3DTextureCoordinates);
		}
		else
		{
			gen.requestVertexShaderSynthesizeInstruction(ShaderVariables::Secondary2DTextureCoordinates);
		}

		return true;
	}
}
