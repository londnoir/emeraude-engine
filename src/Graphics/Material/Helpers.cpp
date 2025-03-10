/*
 * src/Graphics/Material/Helpers.cpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2025 - Sébastien Léon Claude Christian Bémelmans "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Emeraude-Engine; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Complete project and additional information can be found at :
 * https://github.com/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#include "Helpers.hpp"

/* STL inclusions. */
#include <algorithm>
#include <cstdint>
#include <array>

/* Local inclusions. */
#include "Graphics/Geometry/Interface.hpp"
#include "Graphics/Types.hpp"
#include "Interface.hpp"
#include "Libraries/PixelFactory/Color.hpp"
#include "Saphir/Generator/Abstract.hpp"
#include "Saphir/Code.hpp"
#include "Saphir/Keys.hpp"
#include "Tracer.hpp"

namespace Emeraude::Graphics::Material
{
	using namespace Libraries;
	using namespace Emeraude::Saphir;
	using namespace Emeraude::Saphir::Keys;

	static constexpr auto TracerTag{"MaterialHelpers"};

	bool
	checkPrimaryTextureCoordinates (Generator::Abstract & generator, VertexShader & vertexShader, const Interface & material, const Geometry::Interface & geometry) noexcept
	{
		/* NOTE: There is no need of primary texture coordinates. */
		if ( !material.usingPrimaryTextureCoordinates() )
		{
			return true;
		}

		/* NOTE: The texture coordinates will be generated by the shader. */
		if ( material.computesPrimaryTextureCoordinates() )
		{
			if ( material.primaryTextureCoordinatesUses3D() )
			{
				if ( !vertexShader.declare(Declaration::StageOutput{generator.getNextShaderVariableLocation(), GLSL::FloatVector3, ShaderVariable::Primary3DTextureCoordinates, GLSL::Smooth}) )
				{
					return false;
				}

				Code{vertexShader, Location::Output} << ShaderVariable::Primary3DTextureCoordinates << " = normalize(vec3(" << Attribute::Position << ".x, -" << Attribute::Position << ".y, " << Attribute::Position << ".z));";
			}
			else
			{
				if ( !vertexShader.declare(Declaration::StageOutput{generator.getNextShaderVariableLocation(), GLSL::FloatVector2, ShaderVariable::Primary2DTextureCoordinates, GLSL::Smooth}) )
				{
					return false;
				}

				Code{vertexShader, Location::Output} << ShaderVariable::Primary2DTextureCoordinates << " = normalize(" << Attribute::Position << ".x, -" << Attribute::Position << ".y);";
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
			if ( !geometry.primaryTextureCoordinates3DEnabled() )
			{
				TraceError{material.classLabel()} <<
					"The geometry '" << geometry.name() << "' has no 3D primary texture coordinates "
					"for basic material '" << material.name() << "' !";

				return false;
			}

			if ( !vertexShader.requestSynthesizeInstruction(ShaderVariable::Primary3DTextureCoordinates) )
			{
				return false;
			}
		}
		else
		{
			if ( !vertexShader.requestSynthesizeInstruction(ShaderVariable::Primary2DTextureCoordinates) )
			{
				return false;
			}
		}

		return true;
	}

	bool
	checkSecondaryTextureCoordinates (Generator::Abstract & generator, VertexShader & vertexShader, const Interface & material, const Geometry::Interface & geometry) noexcept
	{
		/* NOTE: There is no need of secondary texture coordinates. */
		if ( !material.usingSecondaryTextureCoordinates() )
		{
			return true;
		}

		/* NOTE: The texture coordinates will be generated by the shader. */
		if ( material.computesSecondaryTextureCoordinates() )
		{
			if ( material.secondaryTextureCoordinatesUses3D() )
			{
				if ( !vertexShader.declare(Declaration::StageOutput{generator.getNextShaderVariableLocation(), GLSL::FloatVector3, ShaderVariable::Secondary3DTextureCoordinates, GLSL::Smooth}) )
				{
					return false;
				}

				Code{vertexShader, Location::Output} << ShaderVariable::Secondary3DTextureCoordinates << " = normalize(" << Attribute::Position << ");";
			}
			else
			{
				if ( !vertexShader.declare(Declaration::StageOutput{generator.getNextShaderVariableLocation(), GLSL::FloatVector2, ShaderVariable::Secondary2DTextureCoordinates, GLSL::Smooth}) )
				{
					return false;
				}

				Code{vertexShader, Location::Output} << ShaderVariable::Secondary2DTextureCoordinates << " = normalize(" << Attribute::Position << ".xy);";
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

			if ( !vertexShader.requestSynthesizeInstruction(ShaderVariable::Secondary3DTextureCoordinates) )
			{
				return false;
			}
		}
		else
		{
			if ( !vertexShader.requestSynthesizeInstruction(ShaderVariable::Secondary2DTextureCoordinates) )
			{
				return false;
			}
		}

		return true;
	}

	bool
	parseComponentBase (const Json::Value & data, const char * componentName, FillingType & fillingType, Json::Value & componentData, bool optional) noexcept
	{
		if ( !data.isMember(componentName) )
		{
			fillingType = FillingType::None;

			return optional;
		}

		if ( !data[componentName].isObject() )
		{
			TraceError{TracerTag} << "The component '" << componentName << "' JSON structure is not an object !";

			return false;
		}

		const auto & component = data[componentName];

		if ( !component.isMember(JKType) || !component[JKType].isString() )
		{
			TraceError{TracerTag} << "The key '" << JKType << "' from component '" << componentName << "' JSON structure is not present or not a string !";

			return false;
		}

		fillingType = to_FillingType(component[JKType].asString());

		if ( fillingType == FillingType::None )
		{
			return optional;
		}

		if ( !component.isMember(JKData) )
		{
			TraceError{TracerTag} << "The key '" << JKData << "' from component '" << componentName << "' JSON structure is not present !";

			return false;
		}

		if ( !component[JKData].isObject() && !component[JKData].isArray() )
		{
			TraceError{TracerTag} << "The key '" << JKData << "' from component '" << componentName << "' must be an object or an array !";

			return false;
		}

		componentData = component[JKData];

		return true;
	}

	PixelFactory::Color< float >
	parseColorComponent (const Json::Value & data) noexcept
	{
		if ( !data.isArray() || data.size() < 3 )
		{
			Tracer::error(TracerTag, "Json value is not an array or invalid !");

			return {};
		}

		std::array< float, 4 > colorData{0.0F, 0.0F, 0.0F, 1.0F};

		for ( uint32_t index = 0; index < std::min(4U, data.size()); index++ )
		{
			const auto & colorComponent = data[index];

			if ( !colorComponent.isNumeric() )
			{
				TraceError{TracerTag} << "Json array #" << index << " value is not numeric !";

				break;
			}

			colorData.at(index) = colorComponent.asFloat();
		}

		return PixelFactory::Color{colorData};
	}

	float
	parseValueComponent (const Json::Value & data) noexcept
	{
		if ( !data.isNumeric() )
		{
			Tracer::error(TracerTag, "The Json value is not numeric !");

			return 0.0F;
		}

		return data.asFloat();
	}

	bool
	getComponentAsValue (const Json::Value & data, const char * componentType, float & value) noexcept
	{
		if ( !data.isMember(componentType) )
		{
			return false;
		}

		const auto & jsonNode = data[componentType];

		if  ( jsonNode.isObject() )
		{
			if ( !jsonNode.isMember(JKType) || !jsonNode[JKType].isString() )
			{
				return false;
			}

			if ( to_FillingType(jsonNode[JKType].asString()) != FillingType::Value )
			{
				return false;
			}

			if ( !jsonNode.isMember(JKData) || !jsonNode[JKData].isObject() )
			{
				return false;
			}

			value = jsonNode[JKData].asFloat();

			return true;
		}

		if ( !jsonNode.isNumeric() )
		{
			TraceError{"Interface"} << "The '" << componentType << "' key in Json structure is not numeric ! ";

			return false;
		}

		value = jsonNode.asFloat();

		return true;
	}
}
