/*
 * Emeraude/Graphics/Renderable/TerrainResource.hpp
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

/* C/C++ standard libraries */
#include <cstddef>
#include <string>
#include <memory>

/* Local inclusions for inheritances. */
#include "AbstractSceneArea.hpp"

/* Local inclusions for usages. */
#include "Graphics/Geometry/AdaptiveVertexGridResource.hpp"

namespace Emeraude::Graphics::Renderable
{
	/**
	 * @brief The TerrainResource class
	 * @extends Emeraude::Graphics::AbstractSceneArea The is a specialized scene area.
	 */
	class TerrainResource final : public AbstractSceneArea
	{
		friend class Resources::Container< TerrainResource >;

		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"TerrainResource"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/* JSON key. */
			static constexpr auto HeightMapKey = "HeightMap";
				static constexpr auto ImageNameKey = "ImageName";
				static constexpr auto InverseKey = "Inverse";
			static constexpr auto MaterialTypeKey = "MaterialType";
			static constexpr auto MaterialNameKey = "MaterialName";
			static constexpr auto PerlinNoiseKey = "PerlinNoise";
			static constexpr auto VertexColorKey = "VertexColor";

			static constexpr auto DefaultSize = 4096.0F;
			static constexpr auto DefaultDivision = 4096;

			/**
			 * @brief Constructs a terrain resource.
			 * @param name A reference to a string for the resource name.
			 * @param resourceFlagBits The resource flag bits. Default none.
			 */
			explicit TerrainResource (const std::string & name, uint32_t resourceFlagBits = 0) noexcept;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::layerCount() */
			[[nodiscard]]
			size_t layerCount () const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::isOpaque() */
			[[nodiscard]]
			bool isOpaque (size_t layerIndex = 0UL) const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::geometry() */
			[[nodiscard]]
			const Geometry::Interface * geometry () const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::material() */
			[[nodiscard]]
			const Material::Interface * material (size_t layerIndex = 0UL) const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::boundingBox() */
			[[nodiscard]]
			const Libraries::Math::Cuboid< float > & boundingBox () const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::boundingSphere() */
			[[nodiscard]]
			const Libraries::Math::Sphere< float > & boundingSphere () const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::prepareShaders() */
			[[nodiscard]]
			bool prepareShaders (const Geometry::Interface & geometry, const Material::Interface & material, RenderPassType renderPassType, bool enableInstancing, Vulkan::GraphicsShaderContainer & shaders) const noexcept override;

			/** @copydoc Libraries::Resources::ResourceTrait::classLabel() */
			[[nodiscard]]
			const char * classLabel () const noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load() */
			bool load () noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load(const Libraries::Path::File &) */
			bool load (const Libraries::Path::File & filepath) noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load(const Json::Value &) */
			bool load (const Json::Value & data) noexcept override;

			/**
			 * @brief getLevelAt
			 * @param worldPosition
			 * @return float
			 */
			[[nodiscard]]
			float getLevelAt (const Libraries::Math::Vector< 3, float > & worldPosition) const noexcept override;

			/**
			 * @brief getLevelAt
			 * @param x
			 * @param z
			 * @param delta
			 * @return Libraries::Math::Vector< 3, float > getLevelAt
			 */
			[[nodiscard]]
			Libraries::Math::Vector< 3, float > getLevelAt (float x, float z, float delta = 0.0F) const noexcept override;

			/**
			 * @brief getNormalAt
			 * @param worldPosition
			 * @return Libraries::Math::Vector< 3, float >
			 */
			[[nodiscard]]
			Libraries::Math::Vector< 3, float > getNormalAt (const Libraries::Math::Vector< 3, float > & worldPosition) const noexcept override;

			/**
			 * @brief isOnGround
			 * @param node
			 * @return bool
			 */
			bool isOnGround (Scenes::Node & node) const noexcept override;

			/**
			 * @brief Loads a parametric terrain with a material.
			 * @param material A pointer to a material resource.
			 * @return bool
			 */
			bool load (float size, size_t division, const std::shared_ptr< Material::Interface > & material) noexcept;

			/**
			 * @brief Returns a terrain resource by its name.
			 * @param resourceName A reference to a string.
			 * @param directLoad Use the direct loading mode. Default false.
			 * @return std::shared_ptr< TerrainResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< TerrainResource > get (const std::string & resourceName, bool directLoad = false) noexcept;

			/**
			 * @brief Returns the default terrain resource.
			 * @return std::shared_ptr< TerrainResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< TerrainResource > getDefault () noexcept;

		private:

			/**
			 * @brief Prepares all about geometry of the terrain.
			 * @param size The size of the terrain.
			 * @param division The number of division.
			 * @return bool
			 */
			bool prepareGeometry (float size, size_t division) noexcept;

			/**
			 * @brief Sets a grid geometry.
			 * @param geometryResource A reference to a material smart pointer.
			 * @return bool
			 */
			bool setGeometry (const std::shared_ptr< Geometry::AdaptiveVertexGridResource > & geometryResource) noexcept;

			/**
			 * @brief Sets a material.
			 * @param materialResource A reference to a material smart pointer.
			 * @return bool
			 */
			bool setMaterial (const std::shared_ptr< Material::Interface > & materialResource) noexcept;

			/**
			 * @brief updateActiveGeometryProcess
			 */
			void updateActiveGeometryProcess () noexcept;

			/* Contains the graphical sub-data. */
			std::shared_ptr< Geometry::AdaptiveVertexGridResource > m_geometry{};
			std::shared_ptr< Geometry::VertexGridResource > m_farGeometry{};
			std::shared_ptr< Material::Interface > m_material{};
			/* Contains the whole data. */
			Libraries::VertexFactory::Grid< float > m_localData{};
			Libraries::Math::Vector< 3, float > m_lastUpdatePosition{};
			bool m_updatingActiveGeometryProcess = false;
	};
}

/* Expose the resource manager as a convenient type. */
namespace Emeraude::Resources
{
	using Terrains = Container< Graphics::Renderable::TerrainResource >;
}
