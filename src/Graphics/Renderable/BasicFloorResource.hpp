/*
 * Emeraude/Graphics/Renderable/BasicFloorResource.hpp
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

namespace Emeraude::Graphics::Renderable
{
	/**
	 * @brief The basic floor resource class.
	 * @extends Emeraude::Graphics::AbstractSceneArea The is a specialized scene area.
	 */
	class BasicFloorResource final : public AbstractSceneArea
	{
		friend class Resources::Container< BasicFloorResource >;

		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"BasicFloorResource"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			static constexpr auto CellSize = 100.0F;
			static constexpr auto DefaultSize = 1024.0F;
			static constexpr auto DefaultDivision = 16;

			/* JSON key. */
			static constexpr auto SizeKey = "Size";
			static constexpr auto DivisionKey = "Division";
			static constexpr auto HeightMapKey = "HeightMap";
				static constexpr auto ImageNameKey = "ImageName";
				static constexpr auto ScaleKey = "Scale";
				static constexpr auto InverseKey = "Inverse";
			static constexpr auto MaterialTypeKey = "MaterialType";
			static constexpr auto MaterialNameKey = "MaterialName";
			static constexpr auto UVMultiplierKey = "UVMultiplier";

			/**
			 * @brief Constructs a basic floor resource.
			 * @param name A reference to a string for the resource name.
			 * @param resourceFlagBits The resource flag bits. Default none.
			 */
			explicit BasicFloorResource (const std::string & name, uint32_t resourceFlagBits = 0) noexcept;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Libraries::Resources::ResourceTrait::classLabel() */
			[[nodiscard]]
			const char * classLabel () const noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load() */
			bool load () noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load(const Libraries::Path::File &) */
			bool load (const Libraries::Path::File & filepath) noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load(const Json::Value &) */
			bool load (const Json::Value & data) noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::layerCount() */
			[[nodiscard]]
			size_t layerCount () const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::isOpaque() */
			[[nodiscard]]
			bool isOpaque (size_t layerIndex = 0) const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::geometry() */
			[[nodiscard]]
			const Geometry::Interface * geometry () const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::material() */
			[[nodiscard]]
			const Material::Interface * material (size_t layerIndex = 0) const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::boundingBox() */
			[[nodiscard]]
			const Libraries::Math::Cuboid< float > & boundingBox () const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::boundingSphere() */
			[[nodiscard]]
			const Libraries::Math::Sphere< float > & boundingSphere () const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::prepareShaders() */
			[[nodiscard]]
			bool prepareShaders (const Geometry::Interface & geometry, const Material::Interface & material, RenderPassType renderPassType, bool enableInstancing, Vulkan::GraphicsShaderContainer & shaders) const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::AbstractSceneArea::getLevelAt(const Libraries::Math::Vector< 3, float > &) */
			[[nodiscard]]
			float getLevelAt (const Libraries::Math::Vector< 3, float > & worldPosition) const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::AbstractSceneArea::getLevelAt(float, float, float) */
			[[nodiscard]]
			Libraries::Math::Vector< 3, float > getLevelAt (float x, float z, float delta = 0) const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::AbstractSceneArea::getNormalAt() */
			[[nodiscard]]
			Libraries::Math::Vector< 3, float > getNormalAt (const Libraries::Math::Vector< 3, float > & worldPosition) const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::AbstractSceneArea::isOnGround() */
			bool isOnGround (Scenes::Node & node) const noexcept override;

			/**
			 * @brief Loads a basic floor by providing a vertex grid geometry for the ground and a material to paint it.
			 * @param geometry A vertex grid geometry.
			 * @param material A material.
			 * @return bool
			 */
			bool load (const std::shared_ptr< Geometry::VertexGridResource > & geometry, const std::shared_ptr< Material::Interface > & material) noexcept;

			/**
			 * @brief Loads a basic floor by using parameters to generate the ground and a material to paint it.
			 * @param size The size of the whole size of one dimension of the grid. i.e. If the size is 1024, the grid will be from +512 to -512.
			 * @param division How many cell in one dimension.
			 * @param materialResource A reference to a material smart pointer.
			 * @param UVMultiplier Texture coordinates multiplier.
			 * @return bool
			 */
			bool load (float size, size_t division, const std::shared_ptr< Material::Interface > & materialResource, float UVMultiplier = 1.0F) noexcept;

			/**
			 * @brief Loads a basic floor by using parameters to generate the ground with diamond square and a material to paint it.
			 * @param size The size of the whole size of one dimension of the grid. i.e. If the size is 1024, the grid will be from +512 to -512.
			 * @param division How many cell in one dimension.
			 * @param factor Set diamond square factor parameter.
			 * @param seed Randomize generation.
			 * @param materialResource A reference to a material smart pointer.
			 * @param UVMultiplier Texture coordinates multiplier.
			 * @return bool
			 */
			bool loadDiamondSquare (float size, size_t division, float factor, unsigned int seed, const std::shared_ptr< Material::Interface > & materialResource, float UVMultiplier = 1.0F) noexcept;

			/**
			 * @brief Loads a basic floor by using parameters to generate the ground with diamond square and a material to paint it.
			 * @param size The size of the whole size of one dimension of the grid. i.e. If the size is 1024, the grid will be from +512 to -512.
			 * @param division How many cell in one dimension.
			 * @param noiseSize Set perlin noise size parameter.
			 * @param noiseFactor Set perlin noise factor parameter.
			 * @param materialResource A reference to a material smart pointer.
			 * @param UVMultiplier Texture coordinates multiplier.
			 * @return bool
			 */
			bool loadPerlinNoise (float size, size_t division, float noiseSize, float noiseFactor, const std::shared_ptr< Material::Interface > & materialResource, float UVMultiplier = 1.0F) noexcept;

			/**
			 * @brief Loads a basic floor by using parameters to generate the ground with displacement map and a material to paint it.
			 * @tparam pixmapData_t The type used within the pixmap.
			 * @param size The size of the whole size of one dimension of the grid. i.e. If the size is 1024, the grid will be from +512 to -512.
			 * @param division How many cell in one dimension.
			 * @param displacementMap A pixmap to use as a displacement map.
			 * @param displacementFactor Factor of displacement.
			 * @param materialResource A reference to a material smart pointer.
			 * @param UVMultiplier Texture coordinates multiplier.
			 * @return bool
			 */
			template< typename pixmapData_t, std::enable_if_t< std::is_arithmetic_v< pixmapData_t > > = false >
			bool
			load (float size, size_t division, const Libraries::PixelFactory::Pixmap< pixmapData_t > & displacementMap, float displacementFactor, const std::shared_ptr< Material::Interface > & materialResource, float UVMultiplier = 1.0F) noexcept
			{
				auto geometryResource = std::make_shared< Geometry::VertexGridResource >(this->name() + "GridGeometryDisplaced");

				if ( !geometryResource->load(size, division, UVMultiplier) )
				{
					Tracer::error(ClassId, "Unable to generate a basic floor geometry !");

					return false;
				}

				geometryResource->localData().applyDisplacementMapping(displacementMap, displacementFactor);

				return this->load(geometryResource, materialResource);
			}

			/**
			 * @brief Returns a basic floor resource by its name.
			 * @param resourceName A reference to a string.
			 * @param directLoad Use the direct loading mode. Default false.
			 * @return std::shared_ptr< BasicFloorResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< BasicFloorResource > get (const std::string & resourceName, bool directLoad = false) noexcept;

			/**
			 * @brief Returns the default basic floor resource.
			 * @return std::shared_ptr< BasicFloorResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< BasicFloorResource > getDefault () noexcept;

		private:

			/**
			 * @brief Sets the geometry resource.
			 * @param geometryResource A reference to a geometry resource smart pointer.
			 * @return bool
			 */
			bool setGeometry (const std::shared_ptr< Geometry::VertexGridResource > & geometryResource) noexcept;

			/**
			 * @brief Sets the material resource.
			 * @param materialResource A reference to a material resource smart pointer.
			 * @return bool
			 */
			bool setMaterial (const std::shared_ptr< Material::Interface > & materialResource) noexcept;

			std::shared_ptr< Geometry::VertexGridResource > m_geometry{};
			std::shared_ptr< Material::Interface > m_material{};
	};
}

/* Expose the resource manager as a convenient type. */
namespace Emeraude::Resources
{
	using BasicFloors = Container< Graphics::Renderable::BasicFloorResource >;
}
