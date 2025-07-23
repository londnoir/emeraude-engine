/*
 * src/Graphics/Renderable/BasicFloorResource.hpp
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
#include <cstdint>
#include <string>
#include <memory>

/* Local inclusions for inheritances. */
#include "SceneAreaInterface.hpp"

/* Local inclusions for usages. */
#include "Resources/Container.hpp"
#include "Graphics/Geometry/VertexGridResource.hpp"

namespace EmEn::Graphics::Renderable
{
	/**
	 * @brief The basic floor resource class.
	 * @extends EmEn::Graphics::Renderable::SceneAreaInterface This is a scene area.
	 */
	class BasicFloorResource final : public SceneAreaInterface
	{
		friend class Resources::Container< BasicFloorResource >;

		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"BasicFloorResource"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			static constexpr auto DefaultSize{1024.0F};
			static constexpr auto DefaultDivision{16};
			static constexpr uint32_t DefaultGeometryFlags{Geometry::EnableTangentSpace | Geometry::EnableVertexColor | Geometry::EnablePrimaryTextureCoordinates | Geometry::EnablePrimitiveRestart};

			/* JSON key. */
			static constexpr auto SizeKey{"Size"};
			static constexpr auto DivisionKey{"Division"};
			static constexpr auto HeightMapKey{"HeightMap"};
				static constexpr auto ImageNameKey{"ImageName"};
				static constexpr auto ScaleKey{"Scale"};
				static constexpr auto InverseKey{"Inverse"};
			static constexpr auto MaterialTypeKey{"MaterialType"};
			static constexpr auto MaterialNameKey{"MaterialName"};
			static constexpr auto UVMultiplierKey{"UVMultiplier"};

			/**
			 * @brief Constructs a basic floor resource.
			 * @param name A reference to a string for the resource name.
			 * @param resourceFlagBits The resource flag bits. Default none.
			 */
			explicit BasicFloorResource (const std::string & name, uint32_t resourceFlagBits = 0) noexcept;

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

			/** @copydoc EmEn::Resources::ResourceTrait::classLabel() const */
			[[nodiscard]]
			const char *
			classLabel () const noexcept override
			{
				return ClassId;
			}

			/** @copydoc EmEn::Resources::ResourceTrait::load() */
			bool load () noexcept override;

			/** @copydoc EmEn::Resources::ResourceTrait::load(const std::filesystem::path &) */
			bool load (const std::filesystem::path & filepath) noexcept override;

			/** @copydoc EmEn::Resources::ResourceTrait::load(const Json::Value &) */
			bool load (const Json::Value & data) noexcept override;

			/** @copydoc EmEn::Graphics::Renderable::Interface::layerCount() const */
			[[nodiscard]]
			uint32_t layerCount () const noexcept override
			{
				return 1;
			}

			/** @copydoc EmEn::Graphics::Renderable::Interface::isOpaque() const */
			[[nodiscard]]
			bool
			isOpaque (uint32_t /*layerIndex*/) const noexcept override
			{
				if ( m_material != nullptr )
				{
					return m_material->isOpaque();
				}

				return true;
			}

			/** @copydoc EmEn::Graphics::Renderable::Interface::geometry() const */
			[[nodiscard]]
			const Geometry::Interface *
			geometry () const noexcept override
			{
				return m_geometry.get();
			}

			/** @copydoc EmEn::Graphics::Renderable::Interface::material() const */
			[[nodiscard]]
			const Material::Interface *
			material (uint32_t /*layerIndex*/) const noexcept override
			{
				return m_material.get();
			}

			/** @copydoc EmEn::Graphics::Renderable::Interface::layerRasterizationOptions() const */
			[[nodiscard]]
			const RasterizationOptions *
			layerRasterizationOptions (uint32_t /*layerIndex*/) const noexcept override
			{
				return nullptr;
			}

			/** @copydoc EmEn::Graphics::Renderable::Interface::boundingBox() const */
			[[nodiscard]]
			const Libs::Math::Space3D::AACuboid< float > &
			boundingBox () const noexcept override
			{
				if ( m_geometry == nullptr )
				{
					return NullBoundingBox;
				}

				return m_geometry->boundingBox();
			}

			/** @copydoc EmEn::Graphics::Renderable::Interface::boundingSphere() const */
			[[nodiscard]]
			const Libs::Math::Space3D::Sphere< float > &
			boundingSphere () const noexcept override
			{
				if ( m_geometry == nullptr )
				{
					return NullBoundingSphere;
				}

				return m_geometry->boundingSphere();
			}

			/** @copydoc EmEn::Graphics::Renderable::SceneAreaInterface::getLevelAt(const Libs::Math::Vector< 3, float > &) const */
			[[nodiscard]]
			float getLevelAt (const Libs::Math::Vector< 3, float > & worldPosition) const noexcept override;

			/** @copydoc EmEn::Graphics::Renderable::SceneAreaInterface::getLevelAt(float, float, float) const */
			[[nodiscard]]
			Libs::Math::Vector< 3, float > getLevelAt (float positionX, float positionZ, float deltaY) const noexcept override;

			/** @copydoc EmEn::Graphics::Renderable::SceneAreaInterface::getNormalAt() const */
			[[nodiscard]]
			Libs::Math::Vector< 3, float > getNormalAt (const Libs::Math::Vector< 3, float > & worldPosition) const noexcept override;

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
			bool load (float size, uint32_t division, const std::shared_ptr< Material::Interface > & materialResource, float UVMultiplier = 1.0F) noexcept;

			/**
			 * @brief Loads a basic floor by using parameters to generate the ground with diamond square and a material to paint it.
			 * @param size The size of the whole size of one dimension of the grid. i.e. If the size is 1024, the grid will be from +512 to -512.
			 * @param division How many cell in one dimension.
			 * @param factor Set diamond square factor parameter.
			 * @param roughness Set the diamond square roughness parameter. A value from 0.0 to 1.0
			 * @param seed Randomize generation.
			 * @param materialResource A reference to a material smart pointer.
			 * @param UVMultiplier Texture coordinates multiplier.
			 * @return bool
			 */
			bool loadDiamondSquare (float size, uint32_t division, float factor, float roughness, int32_t seed, const std::shared_ptr< Material::Interface > & materialResource, float UVMultiplier = 1.0F) noexcept;

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
			bool loadPerlinNoise (float size, uint32_t division, float noiseSize, float noiseFactor, const std::shared_ptr< Material::Interface > & materialResource, float UVMultiplier = 1.0F) noexcept;

			/**
			 * @brief Loads a basic floor by using parameters to generate the ground with displacement map and a material to paint it.
			 * @tparam pixmapData_t The type used within the pixmap.
			 * @param size The size of the whole size of one dimension of the grid. i.e. If the size is 1024, the grid will be from +512 to -512.
			 * @param division How many cell in one dimension.
			 * @param displacementMap A pixmap to use as a displacement map.
			 * @param displacementFactor Factor of displacement.
			 * @param materialResource A reference to a material smart pointer.
			 * @param UVMultiplier Texture coordinates multiplier. Default 1.0.
			 * @return bool
			 */
			template< typename pixmapData_t >
			bool
			load (float size, uint32_t division, const Libs::PixelFactory::Pixmap< pixmapData_t > & displacementMap, float displacementFactor, const std::shared_ptr< Material::Interface > & materialResource, float UVMultiplier = 1.0F) noexcept requires (std::is_arithmetic_v< pixmapData_t >)
			{
				const auto geometryResource = std::make_shared< Geometry::VertexGridResource >(this->name() + "GridGeometryDisplaced");

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

			std::shared_ptr< Geometry::VertexGridResource > m_geometry;
			std::shared_ptr< Material::Interface > m_material;
	};
}

/* Expose the resource manager as a convenient type. */
namespace EmEn::Resources
{
	using BasicFloors = Container< Graphics::Renderable::BasicFloorResource >;
}
