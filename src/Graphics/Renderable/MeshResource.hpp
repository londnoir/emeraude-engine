/*
 * src/Graphics/Renderable/MeshResource.hpp
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
#include <cstdint>
#include <string>
#include <vector>
#include <memory>

/* Local inclusions for inheritances. */
#include "Interface.hpp"

/* Local inclusions for usages. */
#include "Resources/Container.hpp"
#include "MeshLayer.hpp"

namespace Emeraude::Graphics::Renderable
{
	/**
	 * @brief This class provide a high level object to describe a physical object in the 3D world.
	 * @extends Emeraude::Graphics::Renderable::Interface Adds the ability to be rendered in the 3D world.
	 */
	class MeshResource final : public Interface
	{
		friend class Resources::Container< MeshResource >;

		using ResourceTrait::load;

		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"MeshResource"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Construct a Mesh resource.
			 * @param name A reference to a string for the resource name.
			 * @param resourceFlagBits The resource flag bits. Default none.
			 */
			explicit MeshResource (const std::string & name, uint32_t resourceFlagBits = 0) noexcept;

			/** @copydoc Libraries::ObservableTrait::classUID() const */
			[[nodiscard]]
			size_t classUID () const noexcept override;

			/** @copydoc Libraries::ObservableTrait::is() const */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::layerCount() const */
			[[nodiscard]]
			size_t layerCount () const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::isOpaque() const */
			[[nodiscard]]
			bool isOpaque (size_t layerIndex = 0) const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::geometry() const */
			[[nodiscard]]
			const Geometry::Interface * geometry () const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::material() const */
			[[nodiscard]]
			const Material::Interface * material (size_t layerIndex = 0) const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::layerRasterizationOptions() const */
			[[nodiscard]]
			const RasterizationOptions * layerRasterizationOptions (size_t layerIndex = 0) const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::boundingBox() const */
			[[nodiscard]]
			const Libraries::Math::Cuboid< float > & boundingBox () const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::boundingSphere() const */
			[[nodiscard]]
			const Libraries::Math::Sphere< float > & boundingSphere () const noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::classLabel() const */
			[[nodiscard]]
			const char * classLabel () const noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load() */
			bool load () noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load(const Json::Value &) */
			bool load (const Json::Value & data) noexcept override;

			/**
			 * @brief Loads a mesh resource from a geometry and a material. This will produce a single layer mesh.
			 * @param geometry A reference to a geometry resource smart pointer.
			 * @param material A reference to a material resource smart pointer.
			 * @param rasterizationOptions A reference to a rasterization options. Defaults.
			 * @return bool
			 */
			bool load (const std::shared_ptr< Geometry::Interface > & geometry, const std::shared_ptr< Material::Interface > & material, const RasterizationOptions & rasterizationOptions = {}) noexcept;

			/**
			 * @brief Loads a mesh resource from a geometry and a materials list. This will produce a multiple layers mesh.
			 * @param geometry A reference to a geometry resource smart pointer.
			 * @param materialList A reference to a list of material resource smart pointer.
			 * @param rasterizationOptions A reference to a list of rasterization options. Defaults.
			 * @return bool
			 */
			bool load (const std::shared_ptr< Geometry::Interface > & geometry, const std::vector< std::shared_ptr< Material::Interface > > & materialList, const std::vector< RasterizationOptions > & rasterizationOptions = {}) noexcept;

			/**
			 * @brief Gives a hint for the mesh size. This is not effective by itself, you can use it for scale a scene node.
			 * @return float
			 */
			[[nodiscard]]
			float baseSize () const noexcept;

			/**
			 * @brief Returns a mesh resource by its name.
			 * @param resourceName A reference to a string.
			 * @param directLoad Use the direct loading mode. Default false.
			 * @return std::shared_ptr< MeshResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< MeshResource > get (const std::string & resourceName, bool directLoad = false) noexcept;

			/**
			 * @brief Returns the default mesh resource.
			 * @return std::shared_ptr< DynamicSkyResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< MeshResource > getDefault () noexcept;

			/**
			 * @brief Creates a unique mesh or returns the existing one with same parameters.
			 * The resource name will be based on sub-resource names.
			 * @param geometryResource A reference to a geometry resource smart pointer.
			 * @param materialResource A reference to a material resource smart pointer.
			 * @param resourceName A string. Default auto generated name.
			 * @return std::shared_ptr< MeshResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< MeshResource > getOrCreate (const std::shared_ptr< Geometry::Interface > & geometryResource, const std::shared_ptr< Material::Interface > & materialResource, std::string resourceName = {}) noexcept;

			/**
			 * @brief Creates a unique mesh or returns the existing one with same parameters.
			 * The resource name will be based on sub-resource names.
			 * @param geometryResource A reference to a geometry resource smart pointer.
			 * @param materialResources A reference to a material resource smart pointer list.
			 * @param resourceName A string. Default auto generated name.
			 * @return std::shared_ptr< MeshResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< MeshResource > getOrCreate (const std::shared_ptr< Geometry::Interface > & geometryResource, const std::vector< std::shared_ptr< Material::Interface > > & materialResources, std::string resourceName = {}) noexcept;

		private:

			/**
			 * @brief Sets the geometry resource.
			 * @param geometry A reference to a geometry resource smart pointer.
			 * @return bool
			 */
			bool setGeometry (const std::shared_ptr< Geometry::Interface > & geometry) noexcept;

			/**
			 * @brief Sets the material resource.
			 * @param material A reference to a material resource smart pointer.
			 * @param options A reference to a rasterization options.
			 * @param flags The renderable level flags.
			 * @return bool
			 */
			bool
			setMaterial (const std::shared_ptr< Material::Interface > & material, const RasterizationOptions & options, int flags) noexcept
			{
				m_layers.clear();

				return this->addMaterial(material, options, flags);
			}

			/**
			 * @brief Adds a layer with a material and rasterization options.
			 * @param material A reference to a material resource smart pointer.
			 * @param options A reference to a rasterization options.
			 * @param flags The renderable level flags.
			 * @return bool
			 */
			bool addMaterial (const std::shared_ptr< Material::Interface > & material, const RasterizationOptions & options, int flags) noexcept;

			/**
			 * @brief Parses a JSON stream to get the geometry information.
			 * @param data A reference to a JSON node.
			 * @return std::shared_ptr< Geometry::Interface >
			 */
			std::shared_ptr< Geometry::Interface > parseGeometry (const Json::Value & data) noexcept;

			/**
			 * @brief Parses a JSON stream to get the material information.
			 * @param data A reference to a JSON node.
			 * @return std::shared_ptr< Material::Interface >
			 */
			static std::shared_ptr< Material::Interface > parseLayer (const Json::Value & data) noexcept;

			/**
			 * @brief Parses a JSON stream to get the mesh options.
			 * @param data A reference to a JSON node.
			 * @return RasterizationOptions
			 */
			static RasterizationOptions parseLayerOptions (const Json::Value & data) noexcept;

			/* Flag names. */
			static constexpr auto IsReadyToSetupGPU{0UL};
			static constexpr auto IsBroken{1UL};

			/* JSON key. */
			static constexpr auto LayersKey{"Layers"};
			static constexpr auto GeometryTypeKey{"GeometryType"};
			static constexpr auto GeometryNameKey{"GeometryName"};
			static constexpr auto MaterialTypeKey{"MaterialType"};
			static constexpr auto MaterialNameKey{"MaterialName"};
			static constexpr auto BaseSizeKey{"BaseSize"};
			static constexpr auto EnableDoubleSidedFaceKey{"EnableDoubleSidedFace"};
			static constexpr auto DrawingModeKey{"DrawingMode"};

			std::shared_ptr< Geometry::Interface > m_geometry;
			std::vector< MeshLayer > m_layers;
			float m_baseSize{1.0F};
	};
}

/* Expose the resource manager as a convenient type. */
namespace Emeraude::Resources
{
	using Meshes = Container< Graphics::Renderable::MeshResource >;
}
