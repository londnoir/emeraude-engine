/*
 * Emeraude/Graphics/Renderable/Interface.hpp
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

/* C/C++ standard libraries. */
#include <string>
#include <cstdint>

/* Local inclusions for inheritances. */
#include "Resources/Container.hpp"

/* Local inclusions for usages. */
#include "Math/Cuboid.hpp"
#include "Math/Sphere.hpp"
#include "Graphics/Geometry/Interface.hpp"
#include "Graphics/Material/Interface.hpp"

/* Forward declarations. */
namespace Emeraude
{
	namespace Graphics::RenderableInstance
	{
		class VertexBufferFormat;
	}

	namespace Vulkan
	{
		class GraphicsShaderContainer;
	}
}

namespace Emeraude::Graphics::Renderable
{
	/** @brief Renderable interface flag bits. */
	enum RenderableFlagBits
	{
		IsReadyForInstanciation = 1,
	};

	/**
	 * @brief Defines a contract to render an object in the 3D world.
	 * @note This holds only what to draw.
	 * @extends Emeraude::Resources::ResourceTrait Every renderable is a resource.
	 */
	class Interface : public Resources::ResourceTrait
	{
		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Interface (const Interface & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Interface (Interface && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return Interface &
			 */
			Interface & operator= (const Interface & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return Interface &
			 */
			Interface & operator= (Interface && copy) noexcept = delete;

			/**
			 * @brief Destructs the renderable object.
			 */
			~Interface () override = default;

			/**
			 * @brief Returns whether the renderable is ready to prepare an instance on GPU for rendering.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isReadyForInstantiation () const noexcept = 0;

			/**
			 * @brief Returns the number of layout to render the whole object.
			 * @return size_t
			 */
			[[nodiscard]]
			virtual size_t layerCount () const noexcept = 0;

			/**
			 * @brief Returns whether the renderable is opaque to get the way to order it with the render lists.
			 * @param layerIndex The index of the layer.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isOpaque (size_t layerIndex) const noexcept = 0;

			/**
			 * @brief Returns the geometry of the renderable.
			 * @return const Geometry::Interface *
			 */
			[[nodiscard]]
			virtual const Geometry::Interface * geometry () const noexcept = 0;

			/**
			 * @brief Returns the material of the renderable.
			 * @note This can be nullptr.
			 * @param layerIndex The index of the layer.
			 * @return const Material::Interface *
			 */
			[[nodiscard]]
			virtual const Material::Interface * material (size_t layerIndex) const noexcept = 0;

			/**
			 * @brief Returns the bounding box surrounding the renderable.
			 * @return const Libraries::Math::Cuboid< float > &
			 */
			[[nodiscard]]
			virtual const Libraries::Math::Cuboid< float > & boundingBox () const noexcept = 0;

			/**
			 * @brief Returns the bounding sphere surrounding the renderable.
			 * @return const Libraries::Math::Sphere< float > &
			 */
			[[nodiscard]]
			virtual const Libraries::Math::Sphere< float > & boundingSphere () const noexcept = 0;

			/**
			 * @brief Returns renderable level flags.
			 * @param layerIndex The index of the layer.
			 * @return int
			 */
			[[nodiscard]]
			virtual int flags (size_t layerIndex) const noexcept = 0;

			/**
			 * @brief Prepares shaders for a renderable instance layer.
			 * @param geometry A reference to the geometry of the renderable instance.
			 * @param material A reference to the material of the renderable instance layer.
			 * @param renderPassType The render pass type.
			 * @param enableInstancing Hint for instancing.
			 * @param shaders A reference to the vector of generated shaders for the renderable instance.
			 * @param vertexShader A pointer to the vertex shader to generate the vertex buffer format.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool prepareShaders (const Geometry::Interface & geometry, const Material::Interface & material, RenderPassType renderPassType, bool enableInstancing, Vulkan::GraphicsShaderContainer & shaders) const noexcept = 0;

		protected:

			static const Libraries::Math::Cuboid< float > NullBoundingBox;
			static const Libraries::Math::Sphere< float > NullBoundingSphere;

			/**
			 * @brief Constructs a renderable object.
			 * @param name A reference to a string for the resource name.
			 * @param resourceFlagBits The resource flag bits.
			 */
			explicit Interface (const std::string & name, uint32_t resourceFlagBits) noexcept;
			
			/**
			 * @brief Sets the renderable ready to prepare an instance on GPU.
			 * @param state The state.
			 * @return void
			 */
			virtual void setReadyForInstanciation (bool state) noexcept = 0;

		private:

			/** @copydoc Emeraude::Resources::ResourceTrait::onDependenciesLoaded() */
			[[nodiscard]]
			bool onDependenciesLoaded () noexcept override;
	};
}
