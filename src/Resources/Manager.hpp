/*
 * Emeraude/Resources/Manager.hpp
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

#pragma once

/* C/C++ standard libraries. */
#include <vector>

/* Local inclusions for inheritances. */
#include "ServiceInterface.hpp"

/* Local inclusions for usages. */
#include "Audio/SoundResource.hpp"
#include "Audio/MusicResource.hpp"
#include "Graphics/Geometry/AdaptiveVertexGridResource.hpp"
#include "Graphics/Geometry/IndexedVertexResource.hpp"
#include "Graphics/Geometry/VertexGridResource.hpp"
#include "Graphics/Geometry/VertexResource.hpp"
#include "Graphics/Material/BasicResource.hpp"
#include "Graphics/Material/StandardResource.hpp"
#include "Graphics/Renderable/BasicFloorResource.hpp"
#include "Graphics/Renderable/DynamicSkyResource.hpp"
#include "Graphics/Renderable/SimpleMeshResource.hpp"
#include "Graphics/Renderable/MeshResource.hpp"
#include "Graphics/Renderable/SkyboxResource.hpp"
#include "Graphics/Renderable/SpriteResource.hpp"
#include "Graphics/Renderable/TerrainResource.hpp"
#include "Graphics/Renderable/WaterLevelResource.hpp"
#include "Graphics/RenderTarget/Texture/Texture2D.hpp"
#include "Graphics/RenderTarget/Texture/Cubemap.hpp"
#include "Graphics/TextureResource/AnimatedTexture2D.hpp"
#include "Graphics/TextureResource/TextureCubemap.hpp"
#include "Graphics/TextureResource/Texture1D.hpp"
#include "Graphics/TextureResource/Texture2D.hpp"
#include "Graphics/TextureResource/Texture3D.hpp"
#include "Graphics/FontResource.hpp"
#include "Graphics/ImageResource.hpp"
#include "Graphics/CubemapResource.hpp"
#include "Graphics/MovieResource.hpp"
#include "Scenes/DefinitionResource.hpp"

/* Forward declarations. */
namespace Emeraude
{
	class Arguments;
	class FileSystem;
	class Settings;
	//class NetworkManager;
}

namespace Emeraude::Resources
{
	/**
	 * @brief The resource manager service class.
	 * @extends Emeraude::ServiceInterface The resource manager is a service.
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
			 * @param arguments A reference to Arguments.
			 * @param fileSystem The file system management object to deal with configuration files.
			 * @param coreSettings A reference to the core settings.
			 * @param networkManager A reference to the network manager.
			 */
			Manager (const Arguments & arguments, const FileSystem & fileSystem, Settings & coreSettings, NetworkManager & networkManager) noexcept;

			/**
			 * @brief Destructs the resource manager.
			 */
			~Manager ();

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::ServiceInterface::usable() */
			[[nodiscard]]
			bool usable () const noexcept override;

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
			Stores & stores () noexcept;

			/**
			 * @brief Returns the reference to the resource store service.
			 * @return const Stores &
			 */
			[[nodiscard]]
			const Stores & stores () const noexcept;

			/**
			 * @brief Returns the reference to the sound service.
			 * @return Sounds &
			 */
			[[nodiscard]]
			Sounds & sounds () noexcept;

			/**
			 * @brief Returns the reference to the sound service.
			 * @return const Sounds &
			 */
			[[nodiscard]]
			const Sounds & sounds () const noexcept;

			/**
			 * @brief Returns the reference to the music service.
			 * @return Musics &
			 */
			[[nodiscard]]
			Musics & musics () noexcept;

			/**
			 * @brief Returns the reference to the music service.
			 * @return const Musics &
			 */
			[[nodiscard]]
			const Musics & musics () const noexcept;

			/**
			 * @brief Returns the reference to the fonts service.
			 * @return Fonts &
			 */
			[[nodiscard]]
			Fonts & fonts () noexcept;

			/**
			 * @brief Returns the reference to the fonts service.
			 * @return const Fonts &
			 */
			[[nodiscard]]
			const Fonts & fonts () const noexcept;

			/**
			 * @brief Returns the reference to the image service.
			 * @return Images &
			 */
			[[nodiscard]]
			Images & images () noexcept;

			/**
			 * @brief Returns the reference to the image service.
			 * @return const Images &
			 */
			[[nodiscard]]
			const Images & images () const noexcept;

			/**
			 * @brief Returns the reference to the cubemap service.
			 * @return Cubemaps &
			 */
			[[nodiscard]]
			Cubemaps & cubemaps () noexcept;

			/**
			 * @brief Returns the reference to the cubemap service.
			 * @return const Cubemaps &
			 */
			[[nodiscard]]
			const Cubemaps & cubemaps () const noexcept;

			/**
			 * @brief Returns the reference to the movie service.
			 * @return Movies &
			 */
			[[nodiscard]]
			Movies & movies () noexcept;

			/**
			 * @brief Returns the reference to the movie service.
			 * @return const Movies &
			 */
			[[nodiscard]]
			const Movies & movies () const noexcept;

			/**
			 * @brief Returns the reference to the texture 1D service.
			 * @return Texture1Ds &
			 */
			[[nodiscard]]
			Texture1Ds & texture1Ds () noexcept;

			/**
			 * @brief Returns the reference to the texture 1D service.
			 * @return const Texture1Ds &
			 */
			[[nodiscard]]
			const Texture1Ds & texture1Ds () const noexcept;

			/**
			 * @brief Returns the reference to the texture 2D service.
			 * @return Texture2Ds &
			 */
			[[nodiscard]]
			Texture2Ds & texture2Ds () noexcept;

			/**
			 * @brief Returns the reference to the texture 2D service.
			 * @return const Texture2Ds &
			 */
			[[nodiscard]]
			const Texture2Ds & texture2Ds () const noexcept;

			/**
			 * @brief Returns the reference to the texture 3D service.
			 * @return Texture3Ds &
			 */
			[[nodiscard]]
			Texture3Ds & texture3Ds () noexcept;

			/**
			 * @brief Returns the reference to the texture 3D service.
			 * @return const Texture3Ds &
			 */
			[[nodiscard]]
			const Texture3Ds & texture3Ds () const noexcept;

			/**
			 * @brief Returns the reference to the texture cubemap service.
			 * @return TextureCubemaps &
			 */
			[[nodiscard]]
			TextureCubemaps & textureCubemaps () noexcept;

			/**
			 * @brief Returns the reference to the texture cubemap service.
			 * @return const TextureCubemaps &
			 */
			[[nodiscard]]
			const TextureCubemaps & textureCubemaps () const noexcept;

			/**
			 * @brief Returns the reference to the animated texture 2D service.
			 * @return AnimatedTexture2Ds &
			 */
			[[nodiscard]]
			AnimatedTexture2Ds & animatedTextures () noexcept;

			/**
			 * @brief Returns the reference to the animated texture 2D service.
			 * @return const AnimatedTexture2Ds &
			 */
			[[nodiscard]]
			const AnimatedTexture2Ds & animatedTextures () const noexcept;

			/**
			 * @brief Returns the reference to the render to texture service.
			 * @return RenderToTexture2Ds &
			 */
			[[nodiscard]]
			RenderToTexture2Ds & renderToTexture2Ds () noexcept;

			/**
			 * @brief Returns the reference to the render to texture service.
			 * @return const RenderToTexture2Ds &
			 */
			[[nodiscard]]
			const RenderToTexture2Ds & renderToTexture2Ds () const noexcept;

			/**
			 * @brief Returns the reference to the render to cubemap service.
			 * @return RenderToCubemaps &
			 */
			[[nodiscard]]
			RenderToCubemaps & renderToCubemaps () noexcept;

			/**
			 * @brief Returns the reference to the render to cubemap service.
			 * @return const RenderToCubemaps &
			 */
			[[nodiscard]]
			const RenderToCubemaps & renderToCubemaps () const noexcept;

			/**
			 * @brief Returns the reference to the vertex geometry service.
			 * @return VertexGeometries &
			 */
			[[nodiscard]]
			VertexGeometries & vertexGeometries () noexcept;

			/**
			 * @brief Returns the reference to the vertex geometry service.
			 * @return const VertexGeometries &
			 */
			[[nodiscard]]
			const VertexGeometries & vertexGeometries () const noexcept;

			/**
			 * @brief Returns the reference to the indexed vertex geometry service.
			 * @return IndexedVertexGeometries &
			 */
			[[nodiscard]]
			IndexedVertexGeometries & indexedVertexGeometries () noexcept;

			/**
			 * @brief Returns the reference to the indexed vertex geometry service.
			 * @return const IndexedVertexGeometries &
			 */
			[[nodiscard]]
			const IndexedVertexGeometries & indexedVertexGeometries () const noexcept;

			/**
			 * @brief Returns the reference to the vertex grid geometry service.
			 * @return VertexGridGeometries &
			 */
			[[nodiscard]]
			VertexGridGeometries & vertexGridGeometries () noexcept;

			/**
			 * @brief Returns the reference to the vertex grid geometry service.
			 * @return const VertexGridGeometries &
			 */
			[[nodiscard]]
			const VertexGridGeometries & vertexGridGeometries () const noexcept;

			/**
			 * @brief Returns the reference to the adaptive vertex grid geometry service.
			 * @return AdaptiveVertexGridGeometries &
			 */
			[[nodiscard]]
			AdaptiveVertexGridGeometries & adaptiveVertexGridGeometries () noexcept;

			/**
			 * @brief Returns the reference to the adaptive vertex grid geometry service.
			 * @return const AdaptiveVertexGridGeometries &
			 */
			[[nodiscard]]
			const AdaptiveVertexGridGeometries & adaptiveVertexGridGeometries () const noexcept;

			/**
			 * @brief Returns the reference to the basic material service.
			 * @return BasicMaterials &
			 */
			[[nodiscard]]
			BasicMaterials & basicMaterials () noexcept;

			/**
			 * @brief Returns the reference to the basic material service.
			 * @return const BasicMaterials &
			 */
			[[nodiscard]]
			const BasicMaterials & basicMaterials () const noexcept;

			/**
			 * @brief Returns the reference to the standard material service.
			 * @return StandardMaterials &
			 */
			[[nodiscard]]
			StandardMaterials & standardMaterials () noexcept;

			/**
			 * @brief Returns the reference to the standard material service.
			 * @return const StandardMaterials &
			 */
			[[nodiscard]]
			const StandardMaterials & standardMaterials () const noexcept;

			/**
			 * @brief Returns the reference to the simple mesh service.
			 * @return SimpleMeshes &
			 */
			[[nodiscard]]
			SimpleMeshes & simpleMeshes () noexcept;

			/**
			 * @brief Returns the reference to the simple mesh service.
			 * @return const SimpleMeshes &
			 */
			[[nodiscard]]
			const SimpleMeshes & simpleMeshes () const noexcept;

			/**
			 * @brief Returns the reference to the meshes service.
			 * @return Meshes &
			 */
			[[nodiscard]]
			Meshes & meshes () noexcept;

			/**
			 * @brief Returns the reference to the meshes service.
			 * @return const Meshes &
			 */
			[[nodiscard]]
			const Meshes & meshes () const noexcept;

			/**
			 * @brief Returns the reference to the sprites service.
			 * @return Sprites &
			 */
			[[nodiscard]]
			Sprites & sprites () noexcept;

			/**
			 * @brief Returns the reference to the sprites service.
			 * @return const Sprites &
			 */
			[[nodiscard]]
			const Sprites & sprites () const noexcept;

			/**
			 * @brief Returns the reference to the skyboxs service.
			 * @return Skyboxes &
			 */
			[[nodiscard]]
			Skyboxes & skyboxes () noexcept;

			/**
			 * @brief Returns the reference to the skyboxs service.
			 * @return const Skyboxes &
			 */
			[[nodiscard]]
			const Skyboxes & skyboxes () const noexcept;

			/**
			 * @brief Returns the reference to the dynamic skies service.
			 * @return DynamicSkies &
			 */
			[[nodiscard]]
			DynamicSkies & dynamicSkies () noexcept;

			/**
			 * @brief Returns the reference to the dynamic skies service.
			 * @return const DynamicSkies &
			 */
			[[nodiscard]]
			const DynamicSkies & dynamicSkies () const noexcept;

			/**
			 * @brief Returns the reference to the basic floors service.
			 * @return BasicFloors &
			 */
			[[nodiscard]]
			BasicFloors & basicFloors () noexcept;

			/**
			 * @brief Returns the reference to the basic floors service.
			 * @return const BasicFloors &
			 */
			[[nodiscard]]
			const BasicFloors & basicFloors () const noexcept;

			/**
			 * @brief Returns the reference to the terrains service.
			 * @return Terrains &
			 */
			[[nodiscard]]
			Terrains & terrains () noexcept;

			/**
			 * @brief Returns the reference to the terrains service.
			 * @return const Terrains &
			 */
			[[nodiscard]]
			const Terrains & terrains () const noexcept;

			/**
			 * @brief Returns the reference to the water levels service.
			 * @return WaterLevels &
			 */
			[[nodiscard]]
			WaterLevels & waterLevels () noexcept;

			/**
			 * @brief Returns the reference to the water levels service.
			 * @return const WaterLevels &
			 */
			[[nodiscard]]
			const WaterLevels & waterLevels () const noexcept;

			/**
			 * @brief Returns the reference to the scene definitions service.
			 * @return SceneDefinitions &
			 */
			[[nodiscard]]
			SceneDefinitions & sceneDefinitions () noexcept;

			/**
			 * @brief Returns the reference to the scene definitions service.
			 * @return const SceneDefinitions &
			 */
			[[nodiscard]]
			const SceneDefinitions & sceneDefinitions () const noexcept;

			/**
			 * @brief Returns the instance of the resource manager.
			 * @return Manager *
			 */
			[[nodiscard]]
			static
			Manager * instance () noexcept;

		private:

			/** @copydoc Emeraude::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc Emeraude::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

			static Manager * s_instance; // NOLINT NOTE: Singleton behavior

			const Arguments & m_arguments;
			const FileSystem & m_fileSystem;
			Settings & m_coreSettings;
			NetworkManager & m_networkManager;
			std::vector< ServiceInterface * > m_servicesEnabled{};
			Stores m_stores{m_arguments, m_fileSystem, m_coreSettings};
			Sounds m_sounds{m_arguments, m_fileSystem, m_coreSettings, m_networkManager, m_stores, "Sound manager", "Sounds"};
			Musics m_musics{m_arguments, m_fileSystem, m_coreSettings, m_networkManager, m_stores, "Music manager", "Musics"};
			Fonts m_fonts{m_arguments, m_fileSystem, m_coreSettings, m_networkManager, m_stores, "Font manager", "Fonts"};
			Images m_images{m_arguments, m_fileSystem, m_coreSettings, m_networkManager, m_stores, "Image manager", "Images"};
			Cubemaps m_cubemaps{m_arguments, m_fileSystem, m_coreSettings, m_networkManager, m_stores, "Cubemap manager", "Cubemaps"};
			Movies m_movies{m_arguments, m_fileSystem, m_coreSettings, m_networkManager, m_stores, "Movie manager", "Movies"};
			Texture1Ds m_texture1Ds{m_arguments, m_fileSystem, m_coreSettings, m_networkManager, m_stores, "Texture 1D manager", "Images"};
			Texture2Ds m_texture2Ds{m_arguments, m_fileSystem, m_coreSettings, m_networkManager, m_stores, "Texture 2D manager", "Images"};
			Texture3Ds m_texture3Ds{m_arguments, m_fileSystem, m_coreSettings, m_networkManager, m_stores, "Texture 3D manager", "Images"};
			TextureCubemaps m_textureCubemaps{m_arguments, m_fileSystem, m_coreSettings, m_networkManager, m_stores, "Texture cubemap manager", "Cubemaps"};
			AnimatedTexture2Ds m_animatedTexture2Ds{m_arguments, m_fileSystem, m_coreSettings, m_networkManager, m_stores, "Animated texture 2D manager", "Movies"};
			RenderToTexture2Ds m_renderToTexture2Ds{m_arguments, m_fileSystem, m_coreSettings, m_networkManager, m_stores, "Texture cubemap (RTT) manager"};
			RenderToCubemaps m_renderToCubemaps{m_arguments, m_fileSystem, m_coreSettings, m_networkManager, m_stores, "Texture 2D (RTT) manager"};
			VertexGeometries m_vertexGeometries{m_arguments, m_fileSystem, m_coreSettings, m_networkManager, m_stores, "Geometry manager", "Geometries"};
			IndexedVertexGeometries m_indexedVertexGeometries{m_arguments, m_fileSystem, m_coreSettings, m_networkManager, m_stores, "Indexed geometry manager", "Geometries"};
			VertexGridGeometries m_vertexGridGeometries{m_arguments, m_fileSystem, m_coreSettings, m_networkManager, m_stores, "Grid geometry manager", "Geometries"};
			AdaptiveVertexGridGeometries m_adaptiveVertexGridGeometries{m_arguments, m_fileSystem, m_coreSettings, m_networkManager, m_stores, "Adaptive grid geometry manager", "Geometries"};
			BasicMaterials m_basicMaterials{m_arguments, m_fileSystem, m_coreSettings, m_networkManager, m_stores, "Basic material manager", "Materials"};
			StandardMaterials m_standardMaterials{m_arguments, m_fileSystem, m_coreSettings, m_networkManager, m_stores, "Standard material manager", "Materials"};
			SimpleMeshes m_simpleMeshes{m_arguments, m_fileSystem, m_coreSettings, m_networkManager, m_stores, "Simple mesh manager", "Meshes"};
			Meshes m_meshes{m_arguments, m_fileSystem, m_coreSettings, m_networkManager, m_stores, "Mesh manager", "Meshes"};
			Sprites m_sprites{m_arguments, m_fileSystem, m_coreSettings, m_networkManager, m_stores, "Sprite manager", "Sprites"};
			Skyboxes m_skyboxes{m_arguments, m_fileSystem, m_coreSettings, m_networkManager, m_stores, "Skybox manager", "Backgrounds"};
			DynamicSkies m_dynamicSkies{m_arguments, m_fileSystem, m_coreSettings, m_networkManager, m_stores, "Dynamic sky manager", "Backgrounds"};
			BasicFloors m_basicFloors{m_arguments, m_fileSystem, m_coreSettings, m_networkManager, m_stores, "BasicFloor manager", "SceneAreas"};
			Terrains m_terrains{m_arguments, m_fileSystem, m_coreSettings, m_networkManager, m_stores, "Terrain manager", "SceneAreas"};
			WaterLevels m_waterLevels{m_arguments, m_fileSystem, m_coreSettings, m_networkManager, m_stores, "Water level manager", "SeaLevels"};
			SceneDefinitions m_sceneDefinitions{m_arguments, m_fileSystem, m_coreSettings, m_networkManager, m_stores, "Scene definition manager", "Scenes"};
	};
}
