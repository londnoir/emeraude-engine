/*
 * Emeraude/Graphics/Geometry/Interface.cpp
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

#include "Interface.hpp"

/* Local inclusions. */
#include "Tracer.hpp"

namespace Emeraude::Graphics::Geometry
{
	using namespace Libraries;
	using namespace Libraries::VertexFactory;

	constexpr auto TracerTag{"GeometryInterface"};

	Interface::Interface (const std::string & name, uint32_t resourceFlagBits) noexcept
		: Resources::ResourceTrait(name, resourceFlagBits)
	{

	}

	bool
	Interface::buildSubGeometries (std::vector< SubGeometry > & subGeometries, size_t length) noexcept
	{
		if ( length == 0 )
		{
			return false;
		}

		subGeometries.clear();
		subGeometries.emplace_back(0UL, length);

		return true;
	}

	bool
	Interface::buildSubGeometries (std::vector< SubGeometry > & subGeometries, const Shape< float > & shape) noexcept
	{
		if ( shape.empty() )
		{
			return false;
		}

		subGeometries.clear();

		if ( shape.hasGroups() )
		{
			TraceInfo{TracerTag} << "Shape has " << shape.groupCount() << " groups ! Creating sub geometries ...";

			/* FIXME: Check topology/primitive */
			std::transform(shape.groups().cbegin(), shape.groups().cend(), std::back_inserter(subGeometries), [&] (const auto & group) -> SubGeometry {
				return SubGeometry{group.first * 3, group.second * 3};
			});
		}
		else
		{
			Tracer::info(TracerTag, "No batch needed for this geometry.");
		}

		return true;
	}

	bool
	Interface::buildSubGeometries (std::vector< SubGeometry > & subGeometries, const Grid< float > & grid) noexcept
	{
		if ( grid.empty() )
		{
			return false;
		}

		subGeometries.clear();

		// TODO ...

		return true;
	}

	// NOLINTBEGIN(*-magic-numbers)
	uint32_t
	getElementCountFromFlags (int flatBits) noexcept
	{
		/* NOTE: Position are always present ! */
		uint32_t elementCount = 3;

		if ( (flatBits & EnableTangentSpace) != 0 )
		{
			elementCount += 9;
		}
		else if ( (flatBits & EnableNormal) != 0 )
		{
			elementCount += 3;
		}

		if ( (flatBits & EnablePrimaryTextureCoordinates) != 0 )
		{
			elementCount += (flatBits & Enable3DPrimaryTextureCoordinates) != 0 ? 3 : 2;
		}

		if ( (flatBits & EnableSecondaryTextureCoordinates) != 0 )
		{
			elementCount += (flatBits & Enable3DSecondaryTextureCoordinates) != 0 ? 3 : 2;
		}

		if ( (flatBits & EnableVertexColor) != 0 )
		{
			elementCount += 4;
		}

		if ( (flatBits & EnableWeight) != 0 )
		{
			elementCount += 4;
		}

		return elementCount;
	}
	// NOLINTEND(*-magic-numbers)

	std::string
	getFlagsString (int flatBits) noexcept
	{
		std::stringstream output{};

		output <<
			  /* Vertex attributes presence in local data. */
			  "EnableNormal : " << ( (flatBits & EnableNormal) != 0 ? "yes" : "no" ) << "\n"
			  "EnableTangentSpace : " << ( (flatBits & EnableTangentSpace) != 0 ? "yes" : "no" ) << "\n"
			  "EnablePrimaryTextureCoordinates : " << ( (flatBits & EnablePrimaryTextureCoordinates) != 0 ? "yes" : "no" ) << "\n"
			  "EnableSecondaryTextureCoordinates : " << ( (flatBits & EnableSecondaryTextureCoordinates) != 0 ? "yes" : "no" ) << "\n"
			  "EnableVertexColor : " << ( (flatBits & EnableVertexColor) != 0 ? "yes" : "no" ) << "\n"
			  "EnableWeight : " << ( (flatBits & EnableWeight) != 0 ? "yes" : "no" ) << "\n"
			  /* Vertex attribute options. */
			  "Enable3DPrimaryTextureCoordinates : " << ( (flatBits & Enable3DPrimaryTextureCoordinates) != 0 ? "yes" : "no" ) << "\n"
			  "Enable3DSecondaryTextureCoordinates : " << ( (flatBits & Enable3DSecondaryTextureCoordinates) != 0 ? "yes" : "no" ) << "\n"
			  "EnableDynamicVertexBuffer : " << ( (flatBits & EnableDynamicVertexBuffer) != 0 ? "yes" : "no" ) << "\n"
			  "EnableAbsolutePosition : " << ( (flatBits & EnableAbsolutePosition) != 0 ? "yes" : "no" ) << "\n"
			  "EnablePrimitiveRestart : " << ( (flatBits & EnablePrimitiveRestart) != 0 ? "yes" : "no" ) << "\n";

		return output.str();
	}

	bool
	Interface::onDependenciesLoaded () noexcept
	{
		/* NOTE: Ensure the texture is on the video memory. */
		if ( !this->isCreated() && !this->create() )
		{
			TraceError{TracerTag} << "Unable to send the geometry resource '" << this->name() << "' (" << this->classLabel() << ") into the video memory !";

			return false;
		}

		return true;
	}
}
