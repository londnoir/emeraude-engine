/*
 * Emeraude/Graphics/Renderable/SimpleMeshResource.hpp
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
#include <string>
#include <memory>

/* Local inclusions for inheritances. */
#include "Interface.hpp"

namespace Emeraude::Graphics::Renderable
{
	/**
	 * @brief Simple mesh renderable with only one layer.
	 * @extends Emeraude::Graphics::AbstractHelper
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

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Libraries::Resources::ResourceTrait::classLabel() */
			[[nodiscard]]
			const char * classLabel () const noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load() */
			bool load () noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load(const Json::Value &) */
			bool load (const Json::Value & data) noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::isReadyForInstantiation() */
			bool isReadyForInstantiation() const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::layerCount() */
			size_t layerCount() const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::isOpaque() */
			bool isOpaque (size_t layerIndex) const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::geometry() */
			const Geometry::Interface * geometry () const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::material() */
			const Material::Interface * material (size_t layerIndex) const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::boundingBox() */
			const Libraries::Math::Cuboid< float > & boundingBox () const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::boundingSphere() */
			const Libraries::Math::Sphere< float > & boundingSphere () const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::flags() */
			int flags (size_t layerIndex) const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::prepareShaders() */
			[[nodiscard]]
			bool prepareShaders (const Geometry::Interface & geometry, const Material::Interface & material, RenderPassType renderPassType, bool enableInstancing, Vulkan::GraphicsShaderContainer & shaders) const noexcept override;

			/**
			 * @brief Loads a simple mesh.
			 * @param geometry A reference to a geometry smart pointer.
			 * @param material A reference to a material smart pointer.
			 * @return bool
			 */
			bool load (const std::shared_ptr< Geometry::Interface > & geometry, const std::shared_ptr< Material::Interface > & material = nullptr) noexcept;

			/**
			 * @brief Returns a gizmo resource by its name.
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

		private:

			/** @copydoc Emeraude::Graphics::Renderable::Interface::setReadyForInstanciation() */
			void setReadyForInstanciation (bool state) noexcept override;

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

			/* Flag names. */
			static constexpr auto IsReadyToSetupGPU = 0UL;
			static constexpr auto IsBroken = 1UL;

			std::shared_ptr< Geometry::Interface > m_geometry{};
			std::shared_ptr< Material::Interface > m_material{};
			int m_renderableFlags = 0;
	};
}

/* Expose the resource manager as a convenient type. */
namespace Emeraude::Resources
{
	using SimpleMeshes = Container< Graphics::Renderable::SimpleMeshResource >;
}
