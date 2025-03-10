/*
 * src/Resources/Manager.cpp
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

#include "Manager.hpp"

/* STL inclusions. */
#include <exception>
#include <iostream>
#include <cstddef>
#include <limits>
#include <ranges>

/* Local inclusions. */
#include "PrimaryServices.hpp"

namespace Emeraude::Resources
{
	using namespace Libraries;

	const size_t Manager::ClassUID{getClassUID(ClassId)};

	Manager * Manager::s_instance{nullptr};

	Manager::Manager (PrimaryServices & primaryServices, NetworkManager & networkManager) noexcept
		: ServiceInterface(ClassId), m_primaryServices(primaryServices), m_networkManager(networkManager)
	{
		if ( s_instance != nullptr )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", constructor called twice !" "\n";

			std::terminate();
		}

		s_instance = this;
	}

	size_t
	Manager::unloadUnusedResources () noexcept
	{
		size_t totalUnloadResources = 0;

		auto unloadedResources = std::numeric_limits< size_t >::max();

		while ( unloadedResources > 0 )
		{
			unloadedResources = 0;

			/* Complex dependencies */
			unloadedResources += m_simpleMeshes.unloadUnusedResources();
			unloadedResources += m_meshes.unloadUnusedResources();
			unloadedResources += m_sprites.unloadUnusedResources();
			unloadedResources += m_skyBoxes.unloadUnusedResources();
			unloadedResources += m_dynamicSkies.unloadUnusedResources();
			unloadedResources += m_basicFloors.unloadUnusedResources();
			unloadedResources += m_terrains.unloadUnusedResources();
			unloadedResources += m_waterLevels.unloadUnusedResources();

			/* On or more dependencies. */
			unloadedResources += m_basicMaterials.unloadUnusedResources();
			unloadedResources += m_standardMaterials.unloadUnusedResources();

			/* One dependencies. */
			unloadedResources += m_texture1Ds.unloadUnusedResources();
			unloadedResources += m_texture2Ds.unloadUnusedResources();
			unloadedResources += m_texture3Ds.unloadUnusedResources();
			unloadedResources += m_textureCubemaps.unloadUnusedResources();
			unloadedResources += m_animatedTexture2Ds.unloadUnusedResources();
			unloadedResources += m_vertexGeometries.unloadUnusedResources();
			unloadedResources += m_indexedVertexGeometries.unloadUnusedResources();
			unloadedResources += m_vertexGridGeometries.unloadUnusedResources();
			unloadedResources += m_adaptiveVertexGridGeometries.unloadUnusedResources();

			/* No dependencies last. */
			unloadedResources += m_cubemaps.unloadUnusedResources();
			unloadedResources += m_movies.unloadUnusedResources();
			unloadedResources += m_sounds.unloadUnusedResources();
			unloadedResources += m_musics.unloadUnusedResources();
			unloadedResources += m_fonts.unloadUnusedResources();
			unloadedResources += m_images.unloadUnusedResources();
			unloadedResources += m_renderToTexture2Ds.unloadUnusedResources();
			unloadedResources += m_renderToCubemaps.unloadUnusedResources();
			unloadedResources += m_sceneDefinitions.unloadUnusedResources();

			/* Sum up for output. */
			totalUnloadResources += unloadedResources;
		}

		return totalUnloadResources;
	}

	bool
	Manager::onInitialize () noexcept
	{
		/* Initialize store services. */
		if ( m_stores.initialize(m_servicesEnabled) )
		{
			TraceSuccess{ClassId} << m_stores.name() << " service up !";

			if ( m_primaryServices.settings().get< bool >(ResourcesShowInformationKey, BOOLEAN_FOLLOWING_DEBUG) )
			{
				TraceInfo{ClassId} << m_stores;
			}
		}
		else
		{
			TraceError{ClassId} << m_stores.name() << " service failed to execute !";

			return false;
		}

		/* Initialize every resource managers. */
		{
			const std::array< ServiceInterface *, 28 > resourceContainers{
				&m_sounds,
				&m_musics,
				&m_fonts,
				&m_images,
				&m_cubemaps,
				&m_movies,
				&m_texture1Ds,
				&m_texture2Ds,
				&m_texture3Ds,
				&m_textureCubemaps,
				&m_animatedTexture2Ds,
				&m_renderToTexture2Ds,
				&m_renderToCubemaps,
				&m_vertexGeometries,
				&m_indexedVertexGeometries,
				&m_vertexGridGeometries,
				&m_adaptiveVertexGridGeometries,
				&m_basicMaterials,
				&m_standardMaterials,
				&m_simpleMeshes,
				&m_meshes,
				&m_sprites,
				&m_skyBoxes,
				&m_dynamicSkies,
				&m_basicFloors,
				&m_terrains,
				&m_waterLevels,
				&m_sceneDefinitions
			};

			for ( const auto & resourceContainer : resourceContainers )
			{
				if ( resourceContainer->initialize(m_servicesEnabled) )
				{
					TraceSuccess{ClassId} << resourceContainer->name() << " service up !";
				}
				else
				{
					TraceError{ClassId} << resourceContainer->name() << " service failed to execute !";
				}
			}
		}

		return true;
	}

	bool
	Manager::onTerminate () noexcept
	{
		/* Terminate primary services. */
		for ( auto * resourceContainer : std::ranges::reverse_view(m_servicesEnabled) )
		{
			if ( resourceContainer->terminate() )
			{
				TraceSuccess{ClassId} << resourceContainer->name() << " primary service terminated gracefully !";
			}
			else
			{
				TraceError{ClassId} << resourceContainer->name() << " primary service failed to terminate properly !";
			}
		}

		m_servicesEnabled.clear();

		return true;
	}
}
