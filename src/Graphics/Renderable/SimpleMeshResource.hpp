/*
 * src/Graphics/Renderable/SimpleMeshResource.hpp
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
#include <memory>

/* Local inclusions for inheritances. */
#include "Interface.hpp"

/* Local inclusions for usages. */
#include "Resources/Container.hpp"

namespace Emeraude::Graphics::Renderable
{
	/**
	 * @brief Simple mesh renderable with only one layer.
	 * @extends Emeraude::Graphics::Renderable::Interface
	 */
	class SimpleMeshResource final : public Interface
	{
		friend class Resources::Container< SimpleMeshResource >;

		using ResourceTrait::load;

		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"SimpleMeshResource"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs a gizmo.
			 * @param name The resource name.
			 */
			explicit SimpleMeshResource (const std::string & name, uint32_t resourceFlagBits = 0) noexcept;

			/** @copydoc Libraries::ObservableTrait::classUID() const */
			[[nodiscard]]
			size_t classUID () const noexcept override;

			/** @copydoc Libraries::ObservableTrait::is() const */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::classLabel() const */
			[[nodiscard]]
			const char * classLabel () const noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load() */
			bool load () noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load(const Json::Value &) */
			bool load (const Json::Value & data) noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::layerCount() const */
			[[nodiscard]]
			size_t layerCount () const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::isOpaque() const */
			[[nodiscard]]
			bool isOpaque (size_t layerIndex) const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::geometry() const */
			[[nodiscard]]
			const Geometry::Interface * geometry () const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::material() const */
			[[nodiscard]]
			const Material::Interface * material (size_t layerIndex) const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::layerRasterizationOptions() const */
			[[nodiscard]]
			const RasterizationOptions * layerRasterizationOptions (size_t layerIndex) const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::boundingBox() const */
			[[nodiscard]]
			const Libraries::Math::Cuboid< float > & boundingBox () const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::boundingSphere() const */
			[[nodiscard]]
			const Libraries::Math::Sphere< float > & boundingSphere () const noexcept override;

			/**
			 * @brief Loads a simple mesh.
			 * @param geometry A reference to a geometry smart pointer.
			 * @param material A reference to a material smart pointer.
			 * @return bool
			 */
			bool load (const std::shared_ptr< Geometry::Interface > & geometry, const std::shared_ptr< Material::Interface > & material = nullptr) noexcept;

			/**
			 * @brief Returns a simple mesh resource by its name.
			 * @param resourceName A reference to a string.
			 * @param directLoad Use the direct loading mode. Default false.
			 * @return std::shared_ptr< SimpleMeshResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< SimpleMeshResource > get (const std::string & resourceName, bool directLoad = false) noexcept;

			/**
			 * @brief Returns the default simple mesh resource.
			 * @return std::shared_ptr< SimpleMeshResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< SimpleMeshResource > getDefault () noexcept;

			/**
			 * @brief Creates a unique simple mesh or returns the existing one with same parameters.
			 * The resource name will be based on sub-resource names.
			 * @param geometryResource A reference to a geometry resource smart pointer.
			 * @param materialResource A reference to a material resource smart pointer.
			 * @param resourceName A string. Default auto generated name.
			 * @return std::shared_ptr< SimpleMeshResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< SimpleMeshResource > getOrCreate (const std::shared_ptr< Geometry::Interface > & geometryResource, const std::shared_ptr< Material::Interface > & materialResource, std::string resourceName = {}) noexcept;

		private:

			/**
			 * @brief Attaches the geometry resource.
			 * @param geometryResource A reference to a geometry resource smart pointer.
			 * @return bool
			 */
			bool setGeometry (const std::shared_ptr< Geometry::Interface > & geometryResource) noexcept;

			/**
			 * @brief Attaches the material resource.
			 * @param materialResource A reference to a material resource smart pointer.
			 * @return bool
			 */
			bool setMaterial (const std::shared_ptr< Material::Interface > & materialResource) noexcept;

			std::shared_ptr< Geometry::Interface > m_geometry{};
			std::shared_ptr< Material::Interface > m_material{};
	};
}

/* Expose the resource manager as a convenient type. */
namespace Emeraude::Resources
{
	using SimpleMeshes = Container< Graphics::Renderable::SimpleMeshResource >;
}
