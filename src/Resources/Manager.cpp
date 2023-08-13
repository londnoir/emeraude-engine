/*
 * Emeraude/Resources/Manager.cpp
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

#include "Manager.hpp"

/* Local inclusions. */
#include "Tracer.hpp"
#include "Arguments.hpp"
#include "FileSystem.hpp"
#include "Settings.hpp"

namespace Emeraude::Resources
{
	using namespace Libraries;

	const size_t Manager::ClassUID{Observable::getClassUID()};
	Manager * Manager::s_instance{nullptr}; // NOLINT NOTE: Singleton behavior

	Manager::Manager (const Arguments & arguments, const FileSystem & fileSystem, Settings & coreSettings, NetworkManager & networkManager) noexcept
		: ServiceInterface(ClassId), m_arguments(arguments), m_fileSystem(fileSystem), m_coreSettings(coreSettings), m_networkManager(networkManager)
	{
		if ( s_instance != nullptr )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", constructor called twice !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

			std::terminate();
		}

		s_instance = this;
	}

	Manager::~Manager ()
	{
		s_instance = nullptr;
	}

	Manager *
	Manager::instance () noexcept
	{
		return s_instance;
	}

	bool
	Manager::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	Manager::usable () const noexcept
	{
		return m_stores.usable();
	}

	size_t
	Manager::unloadUnusedResources () noexcept
	{
		auto totalUnloadResources = 0UL;

		auto unloadedResources = std::numeric_limits< size_t >::max();

		while ( unloadedResources > 0 )
		{
			unloadedResources = 0;
			unloadedResources += m_sounds.unloadUnusedResources();
			unloadedResources += m_musics.unloadUnusedResources();
			unloadedResources += m_fonts.unloadUnusedResources();
			unloadedResources += m_images.unloadUnusedResources();
			unloadedResources += m_cubemaps.unloadUnusedResources();
			unloadedResources += m_movies.unloadUnusedResources();
			unloadedResources += m_texture1Ds.unloadUnusedResources();
			unloadedResources += m_texture2Ds.unloadUnusedResources();
			unloadedResources += m_texture3Ds.unloadUnusedResources();
			unloadedResources += m_textureCubemaps.unloadUnusedResources();
			unloadedResources += m_animatedTexture2Ds.unloadUnusedResources();
			unloadedResources += m_renderToTexture2Ds.unloadUnusedResources();
			unloadedResources += m_renderToCubemaps.unloadUnusedResources();
			unloadedResources += m_vertexGeometries.unloadUnusedResources();
			unloadedResources += m_indexedVertexGeometries.unloadUnusedResources();
			unloadedResources += m_vertexGridGeometries.unloadUnusedResources();
			unloadedResources += m_adaptiveVertexGridGeometries.unloadUnusedResources();
			unloadedResources += m_basicMaterials.unloadUnusedResources();
			unloadedResources += m_standardMaterials.unloadUnusedResources();
			unloadedResources += m_simpleMeshes.unloadUnusedResources();
			unloadedResources += m_meshes.unloadUnusedResources();
			unloadedResources += m_sprites.unloadUnusedResources();
			unloadedResources += m_skyboxes.unloadUnusedResources();
			unloadedResources += m_dynamicSkies.unloadUnusedResources();
			unloadedResources += m_basicFloors.unloadUnusedResources();
			unloadedResources += m_terrains.unloadUnusedResources();
			unloadedResources += m_waterLevels.unloadUnusedResources();
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
		}
		else
		{
			TraceError{ClassId} << m_stores.name() << " service failed to execute !";

			return false;
		}

		/* Initialize every resource managers. */
		{
			std::array< ServiceInterface *, 28 > resourceContainers{
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
				&m_skyboxes,
				&m_dynamicSkies,
				&m_basicFloors,
				&m_terrains,
				&m_waterLevels,
				&m_sceneDefinitions
			};

			for ( auto & resourceContainer : resourceContainers )
			{
				if ( resourceContainer->initialize(m_servicesEnabled) )
					TraceSuccess{ClassId} << resourceContainer->name() << " service up !";
				else
					TraceError{ClassId} << resourceContainer->name() << " service failed to execute !";
			}
		}

		return true;
	}

	bool
	Manager::onTerminate () noexcept
	{
		/* Terminate primary services. */
		for ( auto it = m_servicesEnabled.rbegin(); it != m_servicesEnabled.rend(); ++it)
		{
			auto service = *it;

			if ( service->terminate() )
				TraceSuccess{ClassId} << service->name() << " primary service terminated gracefully !";
			else
				TraceError{ClassId} << service->name() << " primary service failed to terminate properly !";
		}

		m_servicesEnabled.clear();

		return true;
	}

	Stores &
	Manager::stores () noexcept
	{
		return m_stores;
	}

	const Stores &
	Manager::stores () const noexcept
	{
		return m_stores;
	}

	Sounds &
	Manager::sounds () noexcept
	{
		return m_sounds;
	}

	const Sounds &
	Manager::sounds () const noexcept
	{
		return m_sounds;
	}

	Musics &
	Manager::musics () noexcept
	{
		return m_musics;
	}

	const Musics &
	Manager::musics () const noexcept
	{
		return m_musics;
	}

	Fonts &
	Manager::fonts () noexcept
	{
		return m_fonts;
	}

	const Fonts &
	Manager::fonts () const noexcept
	{
		return m_fonts;
	}

	Images &
	Manager::images () noexcept
	{
		return m_images;
	}

	const Images &
	Manager::images () const noexcept
	{
		return m_images;
	}

	Cubemaps &
	Manager::cubemaps () noexcept
	{
		return m_cubemaps;
	}

	const Cubemaps &
	Manager::cubemaps () const noexcept
	{
		return m_cubemaps;
	}


	Movies &
	Manager::movies () noexcept
	{
		return m_movies;
	}


	const Movies &
	Manager::movies () const noexcept
	{
		return m_movies;
	}


	Texture1Ds &
	Manager::texture1Ds () noexcept
	{
		return m_texture1Ds;
	}

	const Texture1Ds &
	Manager::texture1Ds () const noexcept
	{
		return m_texture1Ds;
	}

	Texture2Ds &
	Manager::texture2Ds () noexcept
	{
		return m_texture2Ds;
	}

	const Texture2Ds &
	Manager::texture2Ds () const noexcept
	{
		return m_texture2Ds;
	}

	Texture3Ds &
	Manager::texture3Ds () noexcept
	{
		return m_texture3Ds;
	}

	const Texture3Ds &
	Manager::texture3Ds () const noexcept
	{
		return m_texture3Ds;
	}

	TextureCubemaps &
	Manager::textureCubemaps () noexcept
	{
		return m_textureCubemaps;
	}

	const TextureCubemaps &
	Manager::textureCubemaps () const noexcept
	{
		return m_textureCubemaps;
	}

	AnimatedTexture2Ds &
	Manager::animatedTextures () noexcept
	{
		return m_animatedTexture2Ds;
	}

	const AnimatedTexture2Ds &
	Manager::animatedTextures () const noexcept
	{
		return m_animatedTexture2Ds;
	}

	RenderToTexture2Ds &
	Manager::renderToTexture2Ds () noexcept
	{
		return m_renderToTexture2Ds;
	}

	const RenderToTexture2Ds &
	Manager::renderToTexture2Ds () const noexcept
	{
		return m_renderToTexture2Ds;
	}

	RenderToCubemaps &
	Manager::renderToCubemaps () noexcept
	{
		return m_renderToCubemaps;
	}

	const RenderToCubemaps &
	Manager::renderToCubemaps () const noexcept
	{
		return m_renderToCubemaps;
	}

	VertexGeometries &
	Manager::vertexGeometries () noexcept
	{
		return m_vertexGeometries;
	}

	const VertexGeometries &
	Manager::vertexGeometries () const noexcept
	{
		return m_vertexGeometries;
	}

	IndexedVertexGeometries &
	Manager::indexedVertexGeometries () noexcept
	{
		return m_indexedVertexGeometries;
	}

	const IndexedVertexGeometries &
	Manager::indexedVertexGeometries () const noexcept
	{
		return m_indexedVertexGeometries;
	}

	VertexGridGeometries &
	Manager::vertexGridGeometries () noexcept
	{
		return m_vertexGridGeometries;
	}

	const VertexGridGeometries &
	Manager::vertexGridGeometries () const noexcept
	{
		return m_vertexGridGeometries;
	}

	AdaptiveVertexGridGeometries &
	Manager::adaptiveVertexGridGeometries () noexcept
	{
		return m_adaptiveVertexGridGeometries;
	}

	const AdaptiveVertexGridGeometries &
	Manager::adaptiveVertexGridGeometries () const noexcept
	{
		return m_adaptiveVertexGridGeometries;
	}

	BasicMaterials &
	Manager::basicMaterials () noexcept
	{
		return m_basicMaterials;
	}

	const BasicMaterials &
	Manager::basicMaterials () const noexcept
	{
		return m_basicMaterials;
	}

	StandardMaterials &
	Manager::standardMaterials () noexcept
	{
		return m_standardMaterials;
	}

	const StandardMaterials &
	Manager::standardMaterials () const noexcept
	{
		return m_standardMaterials;
	}

	SimpleMeshes &
	Manager::simpleMeshes () noexcept
	{
		return m_simpleMeshes;
	}

	const SimpleMeshes &
	Manager::simpleMeshes () const noexcept
	{
		return m_simpleMeshes;
	}

	Meshes &
	Manager::meshes () noexcept
	{
		return m_meshes;
	}

	const Meshes &
	Manager::meshes () const noexcept
	{
		return m_meshes;
	}

	Sprites &
	Manager::sprites () noexcept
	{
		return m_sprites;
	}

	const Sprites &
	Manager::sprites () const noexcept
	{
		return m_sprites;
	}

	Skyboxes &
	Manager::skyboxes () noexcept
	{
		return m_skyboxes;
	}

	const Skyboxes &
	Manager::skyboxes () const noexcept
	{
		return m_skyboxes;
	}

	DynamicSkies &
	Manager::dynamicSkies () noexcept
	{
		return m_dynamicSkies;
	}

	const DynamicSkies &
	Manager::dynamicSkies () const noexcept
	{
		return m_dynamicSkies;
	}

	BasicFloors &
	Manager::basicFloors () noexcept
	{
		return m_basicFloors;
	}

	const BasicFloors &
	Manager::basicFloors () const noexcept
	{
		return m_basicFloors;
	}

	Terrains &
	Manager::terrains () noexcept
	{
		return m_terrains;
	}

	const Terrains &
	Manager::terrains () const noexcept
	{
		return m_terrains;
	}

	WaterLevels &
	Manager::waterLevels () noexcept
	{
		return m_waterLevels;
	}

	const WaterLevels &
	Manager::waterLevels () const noexcept
	{
		return m_waterLevels;
	}

	SceneDefinitions &
	Manager::sceneDefinitions () noexcept
	{
		return m_sceneDefinitions;
	}

	const SceneDefinitions &
	Manager::sceneDefinitions () const noexcept
	{
		return m_sceneDefinitions;
	}
}
