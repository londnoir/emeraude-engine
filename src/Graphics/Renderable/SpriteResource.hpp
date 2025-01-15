/*
 * src/Graphics/Renderable/SpriteResource.hpp
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
#include <mutex>

/* Local inclusions for inheritances. */
#include "Interface.hpp"

/* Local inclusions for usages. */
#include "Resources/Container.hpp"

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

			/** @copydoc Libraries::ObservableTrait::classUID() const */
			[[nodiscard]]
			size_t
			classUID () const noexcept override
			{
				return ClassUID;
			}

			/** @copydoc Libraries::ObservableTrait::is() const */
			[[nodiscard]]
			bool
			is (size_t classUID) const noexcept override
			{
				return classUID == ClassUID;
			}

			/** @copydoc Emeraude::Graphics::Renderable::Interface::layerCount() const */
			[[nodiscard]]
			size_t
			layerCount () const noexcept override
			{
				return 1;
			}

			/** @copydoc Emeraude::Graphics::Renderable::Interface::isOpaque() const */
			[[nodiscard]]
			bool
			isOpaque (size_t layerIndex = 0) const noexcept override
			{
				if ( m_material != nullptr )
				{
					return m_material->isOpaque();
				}

				return true;
			}

			/** @copydoc Emeraude::Graphics::Renderable::Interface::geometry() const */
			[[nodiscard]]
			const Geometry::Interface *
			geometry () const noexcept override
			{
				return m_geometry.get();
			}

			/** @copydoc Emeraude::Graphics::Renderable::Interface::material() const */
			[[nodiscard]]
			const Material::Interface *
			material (size_t layerIndex = 0) const noexcept override
			{
				return m_material.get();
			}

			/** @copydoc Emeraude::Graphics::Renderable::Interface::layerRasterizationOptions() const */
			[[nodiscard]]
			const RasterizationOptions *
			layerRasterizationOptions (size_t layerIndex = 0) const noexcept override
			{
				return nullptr;
			}

			/** @copydoc Emeraude::Graphics::Renderable::Interface::boundingBox() const */
			[[nodiscard]]
			const Libraries::Math::Cuboid< float > &
			boundingBox () const noexcept override
			{
				if ( m_geometry == nullptr )
				{
					return NullBoundingBox;
				}

				return m_geometry->boundingBox();
			}

			/** @copydoc Emeraude::Graphics::Renderable::Interface::boundingSphere() const */
			[[nodiscard]]
			const Libraries::Math::Sphere< float > &
			boundingSphere () const noexcept override
			{
				if ( m_geometry == nullptr )
				{
					return NullBoundingSphere;
				}

				return m_geometry->boundingSphere();
			}

			/** @copydoc Emeraude::Resources::ResourceTrait::classLabel() const */
			[[nodiscard]]
			const char *
			classLabel () const noexcept override
			{
				return ClassId;
			}

			/** @copydoc Emeraude::Resources::ResourceTrait::load() */
			bool load () noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load(const Json::Value &) */
			bool load (const Json::Value & data) noexcept override;

			/**
			 * @brief Loads a sprite resource from a material.
			 * @param material A reference to a material resource smart pointer.
			 * @param centerAtBottom Set the sprite center to the bottom of the quad. Default false.
			 * @param flip Flip the sprite picture. Default false.
			 * @param rasterizationOptions A reference to a rasterization options. Defaults.
			 * @return bool
			 */
			bool load (const std::shared_ptr< Material::Interface > & material, bool centerAtBottom = false, bool flip = false, const RasterizationOptions & rasterizationOptions = {}) noexcept;

			/**
			 * @brief Sets the site of the sprite.
			 * @param value
			 */
			void
			setSize (float value) noexcept
			{
				m_size = std::abs(value);
			}

			/**
			 * @brief Returns the size of the sprite.
			 * @return float
			 */
			[[nodiscard]]
			float
			size () const noexcept
			{
				return m_size;
			}

			/**
			 * @brief Returns the number of frame from the material.
			 * @note Will return 1 if no material is associated.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			frameCount () const noexcept
			{
				if ( m_material == nullptr )
				{
					Tracer::warning(ClassId, "Material is not yet loaded ! Unable to get the Sprite frame count.");

					return 1;
				}

				return m_material->frameCount();
			}

			/**
			 * @brief Returns the duration in milliseconds from the material.
			 * @note Will return 0 if no material is associated.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t
			duration () const noexcept
			{
				if ( m_material == nullptr )
				{
					Tracer::warning(ClassId, "Material is not yet loaded ! Unable to get the Sprite duration.");

					return 0;
				}

				return m_material->duration();
			}

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

			/** @copydoc Emeraude::Resources::ResourceTrait::onDependenciesLoaded() */
			[[nodiscard]]
			bool onDependenciesLoaded () noexcept override;

			/**
			 * @brief Prepares the geometry resource for the sprite.
			 * @note This geometry resource will be shared between all sprites.
			 * @param isAnimated Set texture coordinates to 3D if so.
			 * @param centerAtBottom Set the geometry center at bottom for specific sprites.
			 * @param flip Flip the UV on X axis.
			 * @return bool
			 */
			bool prepareGeometry (bool isAnimated, bool centerAtBottom, bool flip) noexcept;

			/**
			 * @brief Attaches the material resource.
			 * @param materialResource A reference to a material resource smart pointer.
			 * @return bool
			 */
			bool setMaterial (const std::shared_ptr< Material::Interface > & materialResource) noexcept;

			/* JSON key. */
			static constexpr auto JKSizeKey{"Size"};
			static constexpr auto JKCenterAtBottomKey{"CenterAtBottom"};
			static constexpr auto JKFlipKey{"Flip"};

			static constexpr size_t MaxFrames{120};
			static std::mutex s_lockGeometryLoading;

			std::shared_ptr< Geometry::Interface > m_geometry;
			std::shared_ptr< Material::Interface > m_material;
			float m_size{1.0F};
	};
}

/* Expose the resource manager as a convenient type. */
namespace Emeraude::Resources
{
	using Sprites = Container< Graphics::Renderable::SpriteResource >;
}
