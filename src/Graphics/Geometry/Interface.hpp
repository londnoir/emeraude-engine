/*
 * Emeraude/Graphics/Geometry/Interface.hpp
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

/* Local inclusions for inheritances. */
#include "Resources/ResourceTrait.hpp"

/* Local inclusions for usages. */
#include "Graphics/Types.hpp"
#include "SubGeometry.hpp"
#include "VertexFactory/Grid.hpp"
#include "VertexFactory/Shape.hpp"
#include "Vulkan/IndexBufferObject.hpp"
#include "Vulkan/VertexBufferObject.hpp"

namespace Emeraude::Graphics::Geometry
{
	/** @brief Geometry interface flag bits. */
	enum GeometryFlagBits
	{
		/* Vertex attributes present in local data. */
		EnableNormal = 1,
		EnableTangentSpace = 2, /* Overrides EnableNormal. */
		EnablePrimaryTextureCoordinates = 4,
		EnableSecondaryTextureCoordinates = 8,
		EnableVertexColor = 16,
		EnableWeight = 32,
		/* Vertex attribute options. */
		Enable3DPrimaryTextureCoordinates = 64, /* Will modify texture coordinates to be 3 components instead of 2. */
		Enable3DSecondaryTextureCoordinates = 128, /* Will modify texture coordinates to be 3 components instead of 2. */
		EnableDynamicVertexBuffer = 256,
		EnableAbsolutePosition = 512,
		EnablePrimitiveRestart = 1024
	};

	/**
	 * @brief Returns the number of element for a vertex definition using geometry flags.
	 * @param flatBits The geometry flags.
	 * @return uint32_t
	 */
	[[nodiscard]]
	uint32_t getElementCountFromFlags (int flatBits) noexcept;

	/**
	 * @brief Returns a printable debug flags string.
	 * @param flatBits The geometry flags.
	 * @return std::string
	 */
	[[nodiscard]]
	std::string getFlagsString (int flatBits) noexcept;

	/**
	 * @brief This is the base of all geometry compatible with the graphic engine.
	 * @extends Emeraude::Resources::ResourceTrait Every material is a resource.
	 */
	class Interface : public Resources::ResourceTrait
	{
		public:

			/**
			 * @brief Returns whether the tangent space is present in local data.
			 * @return bool
			 */
			[[nodiscard]]
			inline
			virtual
			bool
			tangentSpaceEnabled () const noexcept final
			{
				return this->isFlagEnabled(EnableTangentSpace);
			}

			/**
			 * @brief Returns whether normals are present in local data.
			 * @note If the tangent space is present, normals are available.
			 * @return bool
			 */
			[[nodiscard]]
			inline
			virtual
			bool
			normalEnabled () const noexcept final
			{
				if ( this->isFlagEnabled(EnableTangentSpace) )
				{
					return true;
				}

				return this->isFlagEnabled(EnableNormal);
			}

			/**
			 * @brief Returns whether the primary texture coordinates are present in local data.
			 * @return bool
			 */
			[[nodiscard]]
			inline
			virtual
			bool
			primaryTextureCoordinatesEnabled () const noexcept final
			{
				return this->isFlagEnabled(EnablePrimaryTextureCoordinates);
			}

			/**
			 * @brief Returns whether alternate texture coordinates are present in local data.
			 * @return bool
			 */
			[[nodiscard]]
			inline
			virtual
			bool
			secondaryTextureCoordinatesEnabled () const noexcept final
			{
				return this->isFlagEnabled(EnableSecondaryTextureCoordinates);
			}

			/**
			 * @brief Returns whether vertex colors are present in local data.
			 * @return bool
			 */
			[[nodiscard]]
			inline
			virtual
			bool
			vertexColorEnabled () const noexcept final
			{
				return this->isFlagEnabled(EnableVertexColor);
			}

			/**
			 * @brief Returns whether weights are present in local data.
			 * @return bool
			 */
			[[nodiscard]]
			inline
			virtual
			bool
			weightEnabled () const noexcept final
			{
				return this->isFlagEnabled(EnableWeight);
			}

			/**
			 * @brief Returns whether primary texture coordinates are 3D.
			 * @return bool
			 */
			[[nodiscard]]
			inline
			virtual
			bool
			primaryTextureCoordinates3DEnabled () const noexcept final
			{
				if ( !this->isFlagEnabled(EnablePrimaryTextureCoordinates) )
				{
					return false;
				}

				return this->isFlagEnabled(Enable3DPrimaryTextureCoordinates);
			}

			/**
			 * @brief Returns whether secondary texture coordinates are 3D.
			 * @return bool
			 */
			[[nodiscard]]
			inline
			virtual
			bool
			secondaryTextureCoordinates3DEnabled () const noexcept final
			{
				if ( !this->isFlagEnabled(EnableSecondaryTextureCoordinates) )
				{
					return false;
				}

				return this->isFlagEnabled(Enable3DSecondaryTextureCoordinates);
			}

			/**
			 * @brief Returns whether the geometry needs dynamic VBO.
			 * @return bool
			 */
			[[nodiscard]]
			inline
			virtual
			bool
			useDynamicVertexBuffer () const noexcept final
			{
				return this->isFlagEnabled(EnableDynamicVertexBuffer);
			}

			/**
			 * @brief Returns whether the geometry defines absolute positions.
			 * @return bool
			 */
			[[nodiscard]]
			inline
			virtual
			bool
			useAbsolutePosition () const noexcept final
			{
				return this->isFlagEnabled(EnableAbsolutePosition);
			}

			/**
			 * @brief Returns whether the geometry use primitive restart index.
			 * @return bool
			 */
			[[nodiscard]]
			inline
			virtual
			bool
			usePrimitiveRestart () const noexcept final
			{
				return this->isFlagEnabled(EnablePrimitiveRestart);
			}

			/**
			 * @brief Returns whether the geometry is ready.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isCreated () const noexcept = 0;

			/**
			 * @brief Returns the topology to draw this geometry.
			 * @return Topology
			 */
			[[nodiscard]]
			virtual Topology topology () const noexcept = 0;

			/**
			 * @brief subGeometryCount
			 * @return size_t
			 */
			[[nodiscard]]
			virtual size_t subGeometryCount () const noexcept = 0;

			/**
			 * @brief subGeometryOffset
			 * @param subGeometryIndex The sub-geometry index.
			 * @return size_t
			 */
			[[nodiscard]]
			virtual size_t subGeometryOffset (size_t subGeometryIndex) const noexcept = 0;

			/**
			 * @brief subGeometryLength
			 * @param subGeometryIndex The sub-geometry index.
			 * @return size_t
			 */
			[[nodiscard]]
			virtual size_t subGeometryLength (size_t subGeometryIndex) const noexcept = 0;

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
			 * @brief Returns the vertex buffer object.
			 * @return const Vulkan::VertexBufferObject *
			 */
			[[nodiscard]]
			virtual const Vulkan::VertexBufferObject * vertexBufferObject () const noexcept = 0;

			/**
			 * @brief Returns the index buffer object.
			 * @return const Vulkan::IndexBufferObject *
			 */
			[[nodiscard]]
			virtual const Vulkan::IndexBufferObject * indexBufferObject () const noexcept = 0;

			/**
			 * @brief Returns whether the geometry use an index buffer object for drawing.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool useIndexBuffer () const noexcept = 0;

			/**
			 * @brief Creates the geometry in the video memory from the local data.
			 * @return bool
			 */
			virtual bool create () noexcept = 0;

			/**
			 * @brief Updates the geometry in the video memory from the local data.
			 * @note The geometry must have been previously created in video memory.
			 * @return bool
			 */
			virtual bool update () noexcept = 0;

			/**
			 * @brief Destroys resource.
			 * @param clearLocalData Erase local data too.
			 */
			virtual void destroy (bool clearLocalData) noexcept = 0;

		protected:

			/**
			 * @brief Constructs an abstract geometry.
			 * @param name A reference to a string for the resource name.
			 * @param resourceFlagBits The resource flag bits.
			 */
			Interface (const std::string & name, uint32_t resourceFlagBits) noexcept;

			/**
			 * @brief Builds a simple geometry batch by specifying only the vertex count.
			 * @param length The vertex count.
			 * @param subGeometries A reference to a sub geometry list.
			 * @return bool
			 */
			static bool buildSubGeometries (std::vector< SubGeometry > & subGeometries, size_t length) noexcept;

			/**
			 * @brief Builds geometry batches from shape.
			 * @param shape A reference to a shape.
			 * @param subGeometries A reference to a sub geometry list.
			 * @return bool
			 */
			static bool buildSubGeometries (std::vector< SubGeometry > & subGeometries, const Libraries::VertexFactory::Shape< float > & shape) noexcept;

			/**
			 * @brief Builds geometry batches from grid.
			 * @param grid A reference to a grid.
			 * @param subGeometries A reference to a sub geometry list.
			 * @return bool
			 */
			static bool buildSubGeometries (std::vector< SubGeometry > & subGeometries, const Libraries::VertexFactory::Grid< float > & grid) noexcept;

		private:

			/** @copydoc Emeraude::Resources::ResourceTrait::onDependenciesLoaded() */
			[[nodiscard]]
			bool onDependenciesLoaded () noexcept override;
	};
}
