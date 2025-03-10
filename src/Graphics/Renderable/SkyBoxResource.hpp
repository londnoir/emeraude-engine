/*
 * src/Graphics/Renderable/SkyBoxResource.hpp
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
#include "AbstractBackground.hpp"

/* Local inclusions for usages. */
#include "Resources/Container.hpp"

namespace Emeraude::Graphics::Renderable
{
	/**
	 * @brief The sky box resource class.
	 * @extends Emeraude::Graphics::Renderable::AbstractBackground The is a specialized background.
	 */
	class SkyBoxResource final : public AbstractBackground
	{
		friend class Resources::Container< SkyBoxResource >;

		using ResourceTrait::load;

		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"SkyBoxResource"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs a skybox resource.
			 * @param name A reference to a string for the resource name.
			 * @param resourceFlagBits The resource flag bits. Default none.
			 */
			explicit SkyBoxResource (const std::string & name, uint32_t resourceFlagBits = 0) noexcept;

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
			 * @brief Loads a skybox with a material resource.
			 * @param material A reference to a material smart pointer.
			 * @return bool
			 */
			bool load (const std::shared_ptr< Material::Interface > & material) noexcept;

			/**
			 * @brief Returns a skybox resource by its name.
			 * @param resourceName A reference to a string.
			 * @param directLoad Use the direct loading mode. Default false.
			 * @return std::shared_ptr< SkyBoxResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< SkyBoxResource > get (const std::string & resourceName, bool directLoad = false) noexcept;

			/**
			 * @brief Returns the default skybox resource.
			 * @return std::shared_ptr< SkyBoxResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< SkyBoxResource > getDefault () noexcept;

		private:

			/* JSON key. */
			static constexpr auto TextureKey{"Texture"};
			static constexpr auto LightPositionKey{"LightPosition"};
			static constexpr auto LightAmbientColorKey{"LightAmbientColor"};
			static constexpr auto LightDiffuseColorKey{"LightDiffuseColor"};
			static constexpr auto LightSpecularColorKey{"LightSpecularColor"};

			/**
			 * @brief Sets the geometry resource.
			 * @param geometry A reference to a geometry resource smart pointer.
			 * @return bool
			 */
			bool setGeometry (const std::shared_ptr< Geometry::Interface > & geometry) noexcept;

			/**
			 * @brief Sets the material resource.
			 * @param material A reference to a material resource smart pointer.
			 * @return bool
			 */
			bool setMaterial (const std::shared_ptr< Material::Interface > & material) noexcept;

			std::shared_ptr< Geometry::Interface > m_geometry{};
			std::shared_ptr< Material::Interface > m_material{};
	};
}

/* Expose the resource manager as a convenient type. */
namespace Emeraude::Resources
{
	using SkyBoxes = Container< Graphics::Renderable::SkyBoxResource >;
}
