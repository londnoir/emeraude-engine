/*
 * Emeraude/Graphics/Renderable/SpriteResource.hpp
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
	 * @brief This class provide a high level object to describe a sprite (2D) in the 3D world.
	 * @extends Emeraude::Graphics::Renderable::Interface Adds the ability to be rendered in the 3D world.
	 */
	class SpriteResource final : public Interface
	{
		friend class Resources::Container< SpriteResource >;

		using ResourceTrait::load;

		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"SpriteResource"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Construct a Sprite resource.
			 * @param name A reference to a string for the resource name.
			 * @param resourceFlagBits The resource flag bits. Default none.
			 */
			explicit SpriteResource (const std::string & name, uint32_t resourceFlagBits = 0) noexcept;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::isReadyForInstantiation() */
			[[nodiscard]]
			bool isReadyForInstantiation () const noexcept override;

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

			/** @copydoc Emeraude::Graphics::Renderable::Interface::flags() */
			[[nodiscard]]
			int flags (size_t layerIndex) const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::prepareShaders() */
			[[nodiscard]]
			bool prepareShaders (const Geometry::Interface & geometry, const Material::Interface & material, RenderPassType renderPassType, bool enableInstancing, Vulkan::GraphicsShaderContainer & shaders) const noexcept override;

			/** @copydoc Libraries::Resources::ResourceTrait::classLabel() */
			[[nodiscard]]
			const char * classLabel () const noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load() */
			bool load () noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load(const Json::Value &) */
			bool load (const Json::Value & data) noexcept override;

			/**
			 * @brief setSize
			 * @param value
			 */
			void setSize (float value) noexcept;

			/**
			 * @brief size
			 * @return
			 */
			[[nodiscard]]
			float size () const noexcept;

			/**
			 * @brief Returns the number of frame.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t frameCount () const noexcept;

			/**
			 * @brief Returns the duration in milliseconds.
			 * @return float
			 */
			[[nodiscard]]
			float duration () const noexcept;

			/**
			 * @brief Returns a sprite resource by its name.
			 * @param resourceName A reference to a string.
			 * @param directLoad Use the direct loading mode. Default false.
			 * @return std::shared_ptr< SpriteResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< SpriteResource > get (const std::string & resourceName, bool directLoad = false) noexcept;

			/**
			 * @brief Returns the default sprite resource.
			 * @return std::shared_ptr< SpriteResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< SpriteResource > getDefault () noexcept;

		private:

			/** @copydoc Emeraude::Graphics::Renderable::Interface::setReadyForInstanciation() */
			void setReadyForInstanciation (bool state) noexcept override;

			/**
			 * @brief loadGeometry
			 * @param geometryName
			 * @return bool
			 */
			bool loadGeometry (const char * const geometryName) noexcept;

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

			/* JSON key. */
			static constexpr auto SizeKey = "Size";
			static constexpr auto CenterAtBottomKey = "CenterAtBottom";

			static constexpr auto CenteredQuadGeometryName = "CenteredQuadSprite";
			static constexpr auto BottomQuadGeometryName = "BottomQuadSprite";

			std::shared_ptr< Geometry::Interface > m_geometry{};
			std::shared_ptr< Material::Interface > m_material{};
			float m_size = 1.0F;
			int m_renderableFlags = 0;
	};
}

/* Expose the resource manager as a convenient type. */
namespace Emeraude::Resources
{
	using Sprites = Container< Graphics::Renderable::SpriteResource >;
}
