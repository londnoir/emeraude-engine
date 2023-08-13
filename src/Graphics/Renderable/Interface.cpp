/*
 * Emeraude/Graphics/Renderable/Interface.cpp
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

namespace Emeraude::Graphics::Renderable
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Resources;

	constexpr auto TracerTag{"RenderableInterface"};

	const Cuboid< float > Interface::NullBoundingBox{};
	const Sphere< float > Interface::NullBoundingSphere{};

	Interface::Interface (const std::string & name, uint32_t resourceFlagBits) noexcept
		: ResourceTrait(name, resourceFlagBits)
	{

	}

	bool
	Interface::onDependenciesLoaded () noexcept
	{
		/* NOTE: Check for sub-geometries and layer count coherence. */
		if ( this->geometry()->subGeometryCount() != this->layerCount() )
		{
			TraceError{TracerTag} <<
				"Resource '" << this->name() << "' (" << this->classLabel() << ") structure ill-formed ! "
				"There is " << this->geometry()->subGeometryCount() << " sub geometries () and " <<  this->layerCount() << " rendering layers !";

			return false;
		}

#ifdef DEBUG
		/* NOTE: Check the geometry resource. */
		if ( !this->geometry()->isLoaded() )
		{

			TraceError{TracerTag} <<
				"Resource '" << this->name() << "' (" << this->classLabel() << ") structure ill-formed ! "
				"The geometry is not created !";

			return false;
		}

		/* NOTE: Check material resources. */
		for ( size_t layerIndex = 0; layerIndex < this->layerCount(); layerIndex++ )
		{
			if ( !this->material(layerIndex)->isCreated() )
			{
				TraceError{TracerTag} <<
					"Resource '" << this->name() << "' (" << this->classLabel() << ") structure ill-formed ! "
					"The material #" << layerIndex << " is not created !";

				return false;
			}
		}
#endif

		this->setReadyForInstanciation(true);

		return true;
	}
}
