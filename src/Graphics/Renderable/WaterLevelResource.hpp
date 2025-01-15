/*
 * src/Graphics/Renderable/WaterLevelResource.hpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2024 - "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emeraude-Engine; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Complete project and additional information can be found at :
 * https://bitbucket.org/londnoir/emeraude-engine
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
#include "SeaLevelInterface.hpp"

/* Local inclusions for usages. */
#include "Resources/Container.hpp"
#include "Graphics/Geometry/VertexGridResource.hpp"

namespace Emeraude::Graphics::Renderable
{
	/**
	 * @brief The water level resource class.
	 * @extends Emeraude::Graphics::Renderable::SeaLevelInterface This is a sea level.
	 */
	class WaterLevelResource : public SeaLevelInterface
	{
		friend class Resources::Container< WaterLevelResource >;

		using ResourceTrait::load;

		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"WaterLevelResource"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			static constexpr auto CellSize{100.0F};
			static constexpr auto DefaultSize{1024.0F};
			static constexpr auto DefaultDivision{16};

			/**
			 * @brief Constructs a water level resource.
			 * @param name A reference to a string for the resource name.
			 * @param resourceFlagBits The resource flag bits. Default none.
			 */
			explicit WaterLevelResource (const std::string & name, uint32_t resourceFlagBits = 0) noexcept;

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
			 * @brief Loads a water level from geometry and material resources.
			 * @param geometryResource A reference to a geometry resource smart pointer.
			 * @param materialResource A reference to a material resource smart pointer.
			 * @return bool
			 */
			bool load (const std::shared_ptr< Geometry::VertexGridResource > & geometryResource, const std::shared_ptr< Material::Interface > & materialResource) noexcept;

			/**
			 * @brief Returns a water level resource by its name.
			 * @param resourceName A reference to a string.
			 * @param directLoad Use the direct loading mode. Default false.
			 * @return std::shared_ptr< WaterLevelResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< WaterLevelResource > get (const std::string & resourceName, bool directLoad = false) noexcept;

			/**
			 * @brief Returns the default water level resource.
			 * @return std::shared_ptr< WaterLevelResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< WaterLevelResource > getDefault () noexcept;

		private:

			/**
			 * @brief Attaches the geometry resource.
			 * @param geometryResource A reference to a geometry resource smart pointer.
			 * @return bool
			 */
			bool setGeometry (const std::shared_ptr< Geometry::VertexGridResource > & geometryResource) noexcept;

			/**
			 * @brief Attaches the material resource.
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
	using WaterLevels = Container< Graphics::Renderable::WaterLevelResource >;
}
