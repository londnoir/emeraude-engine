/*
 * src/Resources/Manager.hpp
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

#pragma once

/* STL inclusions. */
#include <cstddef>
#include <vector>

/* Local inclusions for inheritances. */
#include "ServiceInterface.hpp"

/* Local inclusions for usages. */
#include "Audio/MusicResource.hpp"
#include "Audio/SoundResource.hpp"
#include "Graphics/CubemapResource.hpp"
#include "Graphics/FontResource.hpp"
#include "Graphics/Geometry/AdaptiveVertexGridResource.hpp"
#include "Graphics/Geometry/IndexedVertexResource.hpp"
#include "Graphics/Geometry/VertexGridResource.hpp"
#include "Graphics/Geometry/VertexResource.hpp"
#include "Graphics/ImageResource.hpp"
#include "Graphics/Material/BasicResource.hpp"
#include "Graphics/Material/StandardResource.hpp"
#include "Graphics/MovieResource.hpp"
#include "Graphics/Renderable/BasicFloorResource.hpp"
#include "Graphics/Renderable/DynamicSkyResource.hpp"
#include "Graphics/Renderable/MeshResource.hpp"
#include "Graphics/Renderable/SimpleMeshResource.hpp"
#include "Graphics/Renderable/SkyBoxResource.hpp"
#include "Graphics/Renderable/SpriteResource.hpp"
#include "Graphics/Renderable/TerrainResource.hpp"
#include "Graphics/Renderable/WaterLevelResource.hpp"
#include "Graphics/TextureResource/AnimatedTexture2D.hpp"
#include "Graphics/TextureResource/Texture1D.hpp"
#include "Graphics/TextureResource/Texture2D.hpp"
#include "Graphics/TextureResource/Texture3D.hpp"
#include "Graphics/TextureResource/TextureCubemap.hpp"
#include "Scenes/DefinitionResource.hpp"
#include "Stores.hpp"

/* Forward declarations. */
namespace EmEn
{
	class PrimaryServices;
	class NetworkManager;
}

namespace EmEn::Resources
{
	/**
	 * @brief The resource manager service class.
	 * @extends EmEn::ServiceInterface The resource manager is a service.
	 */
	class Manager final : public ServiceInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"ResourcesManagerService"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs the resource manager.
			 * @param primaryServices A reference to primary services.
			 * @param networkManager A reference to the network manager.
			 */
			Manager (PrimaryServices & primaryServices, NetworkManager & networkManager) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Manager (const Manager & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Manager (Manager && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return Manager &
			 */
			Manager & operator= (const Manager & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return Manager &
			 */
			Manager & operator= (Manager && copy) noexcept = delete;

			/**
			 * @brief Destructs the resource manager.
			 */
			~Manager () override
			{
				s_instance = nullptr;
			}

			/** @copydoc EmEn::Libs::ObservableTrait::classUID() const */
			[[nodiscard]]
			size_t
			classUID () const noexcept override
			{
				return ClassUID;
			}

			/** @copydoc EmEn::Libs::ObservableTrait::is() const */
			[[nodiscard]]
			bool
			is (size_t classUID) const noexcept override
			{
				return classUID == ClassUID;
			}

			/** @copydoc EmEn::ServiceInterface::usable() */
			[[nodiscard]]
			bool
			usable () const noexcept override
			{
				return m_stores.usable();
			}

			/**
			 * @brief Clean up every unused resources.
			 * @return size_t
			 */
			size_t unloadUnusedResources () noexcept;

			/**
			 * @brief Returns the reference to the resource store service.
			 * @return Stores &
			 */
			[[nodiscard]]
			Stores &
			stores () noexcept
			{
				return m_stores;
			}

			/**
			 * @brief Returns the reference to the resource store service.
			 * @return const Stores &
			 */
			[[nodiscard]]
			const Stores &
			stores () const noexcept
			{
				return m_stores;
			}

			/**
			 * @brief Returns the reference to the sound service.
			 * @return Sounds &
			 */
			[[nodiscard]]
			Sounds &
			sounds () noexcept
			{
				return m_sounds;
			}

			/**
			 * @brief Returns the reference to the sound service.
			 * @return const Sounds &
			 */
			[[nodiscard]]
			const Sounds &
			sounds () const noexcept
			{
				return m_sounds;
			}

			/**
			 * @brief Returns the reference to the music service.
			 * @return Musics &
			 */
			[[nodiscard]]
			Musics &
			musics () noexcept
			{
				return m_musics;
			}

			/**
			 * @brief Returns the reference to the music service.
			 * @return const Musics &
			 */
			[[nodiscard]]
			const Musics &
			musics () const noexcept
			{
				return m_musics;
			}

			/**
			 * @brief Returns the reference to the fonts service.
			 * @return Fonts &
			 */
			[[nodiscard]]
			Fonts &
			fonts () noexcept
			{
				return m_fonts;
			}

			/**
			 * @brief Returns the reference to the fonts service.
			 * @return const Fonts &
			 */
			[[nodiscard]]
			const Fonts &
			fonts () const noexcept
			{
				return m_fonts;
			}

			/**
			 * @brief Returns the reference to the image service.
			 * @return Images &
			 */
			[[nodiscard]]
			Images &
			images () noexcept
			{
				return m_images;
			}

			/**
			 * @brief Returns the reference to the image service.
			 * @return const Images &
			 */
			[[nodiscard]]
			const Images &
			images () const noexcept
			{
				return m_images;
			}

			/**
			 * @brief Returns the reference to the cubemap service.
			 * @return Cubemaps &
			 */
			[[nodiscard]]
			Cubemaps &
			cubemaps () noexcept
			{
				return m_cubemaps;
			}

			/**
			 * @brief Returns the reference to the cubemap service.
			 * @return const Cubemaps &
			 */
			[[nodiscard]]
			const Cubemaps &
			cubemaps () const noexcept
			{
				return m_cubemaps;
			}

			/**
			 * @brief Returns the reference to the movie service.
			 * @return Movies &
			 */
			[[nodiscard]]
			Movies &
			movies () noexcept
			{
				return m_movies;
			}

			/**
			 * @brief Returns the reference to the movie service.
			 * @return const Movies &
			 */
			[[nodiscard]]
			const Movies &
			movies () const noexcept
			{
				return m_movies;
			}

			/**
			 * @brief Returns the reference to the texture 1D service.
			 * @return Texture1Ds &
			 */
			[[nodiscard]]
			Texture1Ds &
			texture1Ds () noexcept
			{
				return m_texture1Ds;
			}

			/**
			 * @brief Returns the reference to the texture 1D service.
			 * @return const Texture1Ds &
			 */
			[[nodiscard]]
			const Texture1Ds &
			texture1Ds () const noexcept
			{
				return m_texture1Ds;
			}

			/**
			 * @brief Returns the reference to the texture 2D service.
			 * @return Texture2Ds &
			 */
			[[nodiscard]]
			Texture2Ds &
			texture2Ds () noexcept
			{
				return m_texture2Ds;
			}

			/**
			 * @brief Returns the reference to the texture 2D service.
			 * @return const Texture2Ds &
			 */
			[[nodiscard]]
			const Texture2Ds &
			texture2Ds () const noexcept
			{
				return m_texture2Ds;
			}

			/**
			 * @brief Returns the reference to the texture 3D service.
			 * @return Texture3Ds &
			 */
			[[nodiscard]]
			Texture3Ds &
			texture3Ds () noexcept
			{
				return m_texture3Ds;
			}

			/**
			 * @brief Returns the reference to the texture 3D service.
			 * @return const Texture3Ds &
			 */
			[[nodiscard]]
			const Texture3Ds &
			texture3Ds () const noexcept
			{
				return m_texture3Ds;
			}

			/**
			 * @brief Returns the reference to the texture cubemap service.
			 * @return TextureCubemaps &
			 */
			[[nodiscard]]
			TextureCubemaps &
			textureCubemaps () noexcept
			{
				return m_textureCubemaps;
			}

			/**
			 * @brief Returns the reference to the texture cubemap service.
			 * @return const TextureCubemaps &
			 */
			[[nodiscard]]
			const TextureCubemaps &
			textureCubemaps () const noexcept
			{
				return m_textureCubemaps;
			}

			/**
			 * @brief Returns the reference to the animated texture 2D service.
			 * @return AnimatedTexture2Ds &
			 */
			[[nodiscard]]
			AnimatedTexture2Ds &
			animatedTextures () noexcept
			{
				return m_animatedTexture2Ds;
			}

			/**
			 * @brief Returns the reference to the animated texture 2D service.
			 * @return const AnimatedTexture2Ds &
			 */
			[[nodiscard]]
			const AnimatedTexture2Ds & animatedTextures () const noexcept
			{
				return m_animatedTexture2Ds;
			}

			/**
			 * @brief Returns the reference to the vertex geometry service.
			 * @return VertexGeometries &
			 */
			[[nodiscard]]
			VertexGeometries &
			vertexGeometries () noexcept
			{
				return m_vertexGeometries;
			}

			/**
			 * @brief Returns the reference to the vertex geometry service.
			 * @return const VertexGeometries &
			 */
			[[nodiscard]]
			const VertexGeometries &
			vertexGeometries () const noexcept
			{
				return m_vertexGeometries;
			}

			/**
			 * @brief Returns the reference to the indexed vertex geometry service.
			 * @return IndexedVertexGeometries &
			 */
			[[nodiscard]]
			IndexedVertexGeometries &
			indexedVertexGeometries () noexcept
			{
				return m_indexedVertexGeometries;
			}

			/**
			 * @brief Returns the reference to the indexed vertex geometry service.
			 * @return const IndexedVertexGeometries &
			 */
			[[nodiscard]]
			const IndexedVertexGeometries &
			indexedVertexGeometries () const noexcept
			{
				return m_indexedVertexGeometries;
			}

			/**
			 * @brief Returns the reference to the vertex grid geometry service.
			 * @return VertexGridGeometries &
			 */
			[[nodiscard]]
			VertexGridGeometries &
			vertexGridGeometries () noexcept
			{
				return m_vertexGridGeometries;
			}

			/**
			 * @brief Returns the reference to the vertex grid geometry service.
			 * @return const VertexGridGeometries &
			 */
			[[nodiscard]]
			const VertexGridGeometries &
			vertexGridGeometries () const noexcept
			{
				return m_vertexGridGeometries;
			}

			/**
			 * @brief Returns the reference to the adaptive vertex grid geometry service.
			 * @return AdaptiveVertexGridGeometries &
			 */
			[[nodiscard]]
			AdaptiveVertexGridGeometries &
			adaptiveVertexGridGeometries () noexcept
			{
				return m_adaptiveVertexGridGeometries;
			}

			/**
			 * @brief Returns the reference to the adaptive vertex grid geometry service.
			 * @return const AdaptiveVertexGridGeometries &
			 */
			[[nodiscard]]
			const AdaptiveVertexGridGeometries &
			adaptiveVertexGridGeometries () const noexcept
			{
				return m_adaptiveVertexGridGeometries;
			}

			/**
			 * @brief Returns the reference to the basic material service.
			 * @return BasicMaterials &
			 */
			[[nodiscard]]
			BasicMaterials &
			basicMaterials () noexcept
			{
				return m_basicMaterials;
			}

			/**
			 * @brief Returns the reference to the basic material service.
			 * @return const BasicMaterials &
			 */
			[[nodiscard]]
			const BasicMaterials &
			basicMaterials () const noexcept
			{
				return m_basicMaterials;
			}

			/**
			 * @brief Returns the reference to the standard material service.
			 * @return StandardMaterials &
			 */
			[[nodiscard]]
			StandardMaterials &
			standardMaterials () noexcept
			{
				return m_standardMaterials;
			}

			/**
			 * @brief Returns the reference to the standard material service.
			 * @return const StandardMaterials &
			 */
			[[nodiscard]]
			const StandardMaterials &
			standardMaterials () const noexcept
			{
				return m_standardMaterials;
			}

			/**
			 * @brief Returns the reference to the simple mesh service.
			 * @return SimpleMeshes &
			 */
			[[nodiscard]]
			SimpleMeshes &
			simpleMeshes () noexcept
			{
				return m_simpleMeshes;
			}

			/**
			 * @brief Returns the reference to the simple mesh service.
			 * @return const SimpleMeshes &
			 */
			[[nodiscard]]
			const SimpleMeshes &
			simpleMeshes () const noexcept
			{
				return m_simpleMeshes;
			}

			/**
			 * @brief Returns the reference to the meshes service.
			 * @return Meshes &
			 */
			[[nodiscard]]
			Meshes &
			meshes () noexcept
			{
				return m_meshes;
			}

			/**
			 * @brief Returns the reference to the meshes service.
			 * @return const Meshes &
			 */
			[[nodiscard]]
			const Meshes &
			meshes () const noexcept
			{
				return m_meshes;
			}

			/**
			 * @brief Returns the reference to the sprites service.
			 * @return Sprites &
			 */
			[[nodiscard]]
			Sprites &
			sprites () noexcept
			{
				return m_sprites;
			}

			/**
			 * @brief Returns the reference to the sprites service.
			 * @return const Sprites &
			 */
			[[nodiscard]]
			const Sprites &
			sprites () const noexcept
			{
				return m_sprites;
			}

			/**
			 * @brief Returns the reference to the sky boxes service.
			 * @return SkyBoxes &
			 */
			[[nodiscard]]
			SkyBoxes &
			skyBoxes () noexcept
			{
				return m_skyBoxes;
			}

			/**
			 * @brief Returns the reference to the sky boxes service.
			 * @return const SkyBoxes &
			 */
			[[nodiscard]]
			const SkyBoxes &
			skyBoxes () const noexcept
			{
				return m_skyBoxes;
			}

			/**
			 * @brief Returns the reference to the dynamic skies service.
			 * @return DynamicSkies &
			 */
			[[nodiscard]]
			DynamicSkies &
			dynamicSkies () noexcept
			{
				return m_dynamicSkies;
			}

			/**
			 * @brief Returns the reference to the dynamic skies service.
			 * @return const DynamicSkies &
			 */
			[[nodiscard]]
			const DynamicSkies &
			dynamicSkies () const noexcept
			{
				return m_dynamicSkies;
			}

			/**
			 * @brief Returns the reference to the basic floors service.
			 * @return BasicFloors &
			 */
			[[nodiscard]]
			BasicFloors &
			basicFloors () noexcept
			{
				return m_basicFloors;
			}

			/**
			 * @brief Returns the reference to the basic floors service.
			 * @return const BasicFloors &
			 */
			[[nodiscard]]
			const BasicFloors &
			basicFloors () const noexcept
			{
				return m_basicFloors;
			}

			/**
			 * @brief Returns the reference to the terrains service.
			 * @return Terrains &
			 */
			[[nodiscard]]
			Terrains &
			terrains () noexcept
			{
				return m_terrains;
			}

			/**
			 * @brief Returns the reference to the terrains service.
			 * @return const Terrains &
			 */
			[[nodiscard]]
			const Terrains &
			terrains () const noexcept
			{
				return m_terrains;
			}

			/**
			 * @brief Returns the reference to the water levels service.
			 * @return WaterLevels &
			 */
			[[nodiscard]]
			WaterLevels &
			waterLevels () noexcept
			{
				return m_waterLevels;
			}

			/**
			 * @brief Returns the reference to the water levels service.
			 * @return const WaterLevels &
			 */
			[[nodiscard]]
			const WaterLevels &
			waterLevels () const noexcept
			{
				return m_waterLevels;
			}

			/**
			 * @brief Returns the reference to the scene definitions service.
			 * @return SceneDefinitions &
			 */
			[[nodiscard]]
			SceneDefinitions &
			sceneDefinitions () noexcept
			{
				return m_sceneDefinitions;
			}

			/**
			 * @brief Returns the reference to the scene definitions service.
			 * @return const SceneDefinitions &
			 */
			[[nodiscard]]
			const SceneDefinitions &
			sceneDefinitions () const noexcept
			{
				return m_sceneDefinitions;
			}

			/**
			 * @brief Returns the instance of the resource manager.
			 * @return Manager *
			 */
			[[nodiscard]]
			static
			Manager *
			instance () noexcept
			{
				return s_instance;
			}

		private:

			/** @copydoc EmEn::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc EmEn::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

			static Manager * s_instance;

			PrimaryServices & m_primaryServices;
			NetworkManager & m_networkManager;
			std::vector< ServiceInterface * > m_servicesEnabled;
			Stores m_stores{m_primaryServices};
			Sounds m_sounds{m_primaryServices, m_networkManager, m_stores, "Sound manager", "Sounds"};
			Musics m_musics{m_primaryServices, m_networkManager, m_stores, "Music manager", "Musics"};
			Fonts m_fonts{m_primaryServices, m_networkManager, m_stores, "Font manager", "Fonts"};
			Images m_images{m_primaryServices, m_networkManager, m_stores, "Image manager", "Images"};
			Cubemaps m_cubemaps{m_primaryServices, m_networkManager, m_stores, "Cubemap manager", "Cubemaps"};
			Movies m_movies{m_primaryServices, m_networkManager, m_stores, "Movie manager", "Movies"};
			Texture1Ds m_texture1Ds{m_primaryServices, m_networkManager, m_stores, "Texture 1D manager", "Images"};
			Texture2Ds m_texture2Ds{m_primaryServices, m_networkManager, m_stores, "Texture 2D manager", "Images"};
			Texture3Ds m_texture3Ds{m_primaryServices, m_networkManager, m_stores, "Texture 3D manager", "Images"};
			TextureCubemaps m_textureCubemaps{m_primaryServices, m_networkManager, m_stores, "Texture cubemap manager", "Cubemaps"};
			AnimatedTexture2Ds m_animatedTexture2Ds{m_primaryServices, m_networkManager, m_stores, "Animated texture 2D manager", "Movies"};
			VertexGeometries m_vertexGeometries{m_primaryServices, m_networkManager, m_stores, "Geometry manager", "Geometries"};
			IndexedVertexGeometries m_indexedVertexGeometries{m_primaryServices, m_networkManager, m_stores, "Indexed geometry manager", "Geometries"};
			VertexGridGeometries m_vertexGridGeometries{m_primaryServices, m_networkManager, m_stores, "Grid geometry manager", "Geometries"};
			AdaptiveVertexGridGeometries m_adaptiveVertexGridGeometries{m_primaryServices, m_networkManager, m_stores, "Adaptive grid geometry manager", "Geometries"};
			BasicMaterials m_basicMaterials{m_primaryServices, m_networkManager, m_stores, "Basic material manager", "Materials"};
			StandardMaterials m_standardMaterials{m_primaryServices, m_networkManager, m_stores, "Standard material manager", "Materials"};
			SimpleMeshes m_simpleMeshes{m_primaryServices, m_networkManager, m_stores, "Simple mesh manager", "Meshes"};
			Meshes m_meshes{m_primaryServices, m_networkManager, m_stores, "Mesh manager", "Meshes"};
			Sprites m_sprites{m_primaryServices, m_networkManager, m_stores, "Sprite manager", "Sprites"};
			SkyBoxes m_skyBoxes{m_primaryServices, m_networkManager, m_stores, "Skybox manager", "Backgrounds"};
			DynamicSkies m_dynamicSkies{m_primaryServices, m_networkManager, m_stores, "Dynamic sky manager", "Backgrounds"};
			BasicFloors m_basicFloors{m_primaryServices, m_networkManager, m_stores, "BasicFloor manager", "SceneAreas"};
			Terrains m_terrains{m_primaryServices, m_networkManager, m_stores, "Terrain manager", "SceneAreas"};
			WaterLevels m_waterLevels{m_primaryServices, m_networkManager, m_stores, "Water level manager", "SeaLevels"};
			SceneDefinitions m_sceneDefinitions{m_primaryServices, m_networkManager, m_stores, "Scene definition manager", "Scenes"};
	};
}
