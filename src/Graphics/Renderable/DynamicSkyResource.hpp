/*
 * src/Graphics/Renderable/DynamicSkyResource.hpp
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

/* Local inclusions for inheritances. */
#include "AbstractBackground.hpp"

/* Local inclusions for usages. */
#include "Resources/Container.hpp"

namespace Emeraude::Graphics::Renderable
{
	/**
	 * @brief The DynamicSkyResource class
	 * @extends Emeraude::Graphics::Renderable::AbstractBackground The is a specialized background.
	 */
	class DynamicSkyResource final : public AbstractBackground
	{
		friend class Resources::Container< DynamicSkyResource >;

		using ResourceTrait::load;

		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"DynamicSkyResource"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs a dynamic skybox resource.
			 * @param name The name of the skybox.
			 * @param resourceFlagBits The resource flag bits. Default none.
			 */
			explicit DynamicSkyResource (const std::string & name, uint32_t resourceFlagBits = 0) noexcept;

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

			/** @copydoc Emeraude::Resources::ResourceTrait::classLabel() const */
			[[nodiscard]]
			const char * classLabel () const noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load() */
			bool load () noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load(const Json::Value &) */
			bool load (const Json::Value & data) noexcept override;

			/**
			 * @brief Returns a dynamic sky resource by its name.
			 * @param resourceName A reference to a string.
			 * @param directLoad Use the direct loading mode. Default false.
			 * @return std::shared_ptr< DynamicSkyResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< DynamicSkyResource > get (const std::string & resourceName, bool directLoad = false) noexcept;

			/**
			 * @brief Returns the default dynamic sky resource.
			 * @return std::shared_ptr< DynamicSkyResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< DynamicSkyResource > getDefault () noexcept;

		private:

			/**
			 * @brief setGeometry
			 * @param geometry
			 * @return bool
			 */
			bool setGeometry (const std::shared_ptr< Geometry::Interface > & geometry) noexcept;

			/**
			 * @brief setMaterial
			 * @param material
			 * @return bool
			 */
			bool setMaterial (const std::shared_ptr< Material::Interface > & material) noexcept;

			std::shared_ptr< Geometry::Interface > m_geometry;
			std::shared_ptr< Material::Interface > m_material;
	};
}

/* Expose the resource manager as a convenient type. */
namespace Emeraude::Resources
{
	using DynamicSkies = Container< Graphics::Renderable::DynamicSkyResource >;
}
