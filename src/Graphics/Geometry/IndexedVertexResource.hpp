/*
 * Emeraude/Graphics/Geometry/IndexedVertexResource.hpp
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

/* C/C++ standards libraries. */
#include <memory>
#include <mutex>
#include <string>
#include <vector>

/* Local inclusions for inheritances. */
#include "Interface.hpp"

/* Local inclusions for usages. */
#include "Resources/Container.hpp"
#include "VertexFactory/Shape.hpp"

namespace Emeraude::Graphics::Geometry
{
	/**
	 * @brief Defines an arbitrary geometry using a VBO and an IBO.
	 * @extends Emeraude::Graphics::Geometry::Interface The common base for all geometry types.
	 */
	class IndexedVertexResource final : public Interface
	{
		friend class Resources::Container< IndexedVertexResource >;

		using ResourceTrait::load;

		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"IndexedVertexResource"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs a vertex indexed geometry resource.
			 * @param name A reference to a string for the resource name.
			 * @param resourceFlagBits The resource flag bits. Default none.
			 */
			explicit IndexedVertexResource (const std::string & name, uint32_t resourceFlagBits = 0) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			IndexedVertexResource (const IndexedVertexResource & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			IndexedVertexResource (IndexedVertexResource && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			IndexedVertexResource & operator= (const IndexedVertexResource & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			IndexedVertexResource & operator= (IndexedVertexResource && copy) noexcept = delete;

			/**
			 * @brief Destructs the vertex indexed geometry resource.
			 */
			~IndexedVertexResource () override;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::Graphics::Geometry::Interface::isCreated() */
			[[nodiscard]]
			bool isCreated () const noexcept override;

			/** @copydoc Emeraude::Graphics::Geometry::Interface::topology() */
			[[nodiscard]]
			Topology topology () const noexcept override;

			/** @copydoc Emeraude::Graphics::Geometry::Interface::subGeometryCount() */
			[[nodiscard]]
			size_t subGeometryCount () const noexcept override;

			/** @copydoc Emeraude::Graphics::Geometry::Interface::subGeometryOffset() */
			[[nodiscard]]
			size_t subGeometryOffset (size_t subGeometryIndex) const noexcept override;

			/** @copydoc Emeraude::Graphics::Geometry::Interface::subGeometryLength() */
			[[nodiscard]]
			size_t subGeometryLength (size_t subGeometryIndex) const noexcept override;

			/** @copydoc Emeraude::Graphics::Geometry::Interface::boundingBox() */
			[[nodiscard]]
			const Libraries::Math::Cuboid< float > & boundingBox () const noexcept override;

			/** @copydoc Emeraude::Graphics::Geometry::Interface::boundingSphere() */
			[[nodiscard]]
			const Libraries::Math::Sphere< float > & boundingSphere () const noexcept override;

			/** @copydoc Emeraude::Graphics::Geometry::Interface::vertexBufferObject() */
			[[nodiscard]]
			const Vulkan::VertexBufferObject * vertexBufferObject () const noexcept override;

			/** @copydoc Emeraude::Graphics::Geometry::Interface::indexBufferObject() */
			[[nodiscard]]
			const Vulkan::IndexBufferObject * indexBufferObject () const noexcept override;

			/** @copydoc Emeraude::Graphics::Geometry::Interface::useIndexBuffer() */
			[[nodiscard]]
			bool useIndexBuffer () const noexcept override;

			/** @copydoc Emeraude::Graphics::Geometry::Interface::create() */
			bool create () noexcept override;

			/** @copydoc Emeraude::Graphics::Geometry::Interface::update() */
			bool update () noexcept override;

			/** @copydoc Emeraude::Graphics::Geometry::Interface::destroy() */
			void destroy (bool clearLocalData) noexcept override;

			/** @copydoc Libraries::Resources::ResourceTrait::classLabel() */
			[[nodiscard]]
			const char * classLabel () const noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load() */
			bool load () noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load(const Libraries::Path::File &) */
			bool load (const Libraries::Path::File & filepath) noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load(const Json::Value &) */
			bool load (const Json::Value & data) noexcept override;

			/**
			 * @brief This load a geometry from a parametric object.
			 * @note This only local data and not pushing it to the video RAM.
			 * @param shape A reference to a geometry from vertexFactory library.
			 * @return bool
			 */
			bool load (const Libraries::VertexFactory::Shape< float > & shape) noexcept;

			/**
			 * @brief Gives access to the local geometry data.
			 * @return Libraries::VertexFactory::Shape< float > &
			 */
			Libraries::VertexFactory::Shape< float > & localData () noexcept;

			/**
			 * @brief Gives access to the local geometry data.
			 * @return const Libraries::VertexFactory::Shape< float > &
			 */
			[[nodiscard]]
			const Libraries::VertexFactory::Shape< float > & localData () const noexcept;

			/**
			 * @brief Returns an indexed vertex resource by its name.
			 * @param resourceName A reference to a string.
			 * @param directLoad Use the direct loading mode. Default false.
			 * @return std::shared_ptr< IndexedVertexResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< IndexedVertexResource > get (const std::string & resourceName, bool directLoad = false) noexcept;

			/**
			 * @brief Returns the default indexed vertex resource.
			 * @return std::shared_ptr< IndexedVertexResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< IndexedVertexResource > getDefault () noexcept;

		private:

			/**
			 * @brief Creates an hardware buffer on the device.
			 * @param vertexAttributes A reference to a vertex attribute vector.
			 * @param vertexCount The number of vertices.
			 * @param vertexElementCount The number of elements composing a vertex.
			 * @param indices A reference to a index vector.
			 * @return bool
			 */
			[[nodiscard]]
			bool createVideoMemoryBuffers (const std::vector< float > & vertexAttributes, size_t vertexCount, size_t vertexElementCount, const std::vector< uint32_t > & indices) noexcept;

			std::unique_ptr< Vulkan::VertexBufferObject > m_vertexBufferObject{};
			std::unique_ptr< Vulkan::IndexBufferObject > m_indexBufferObject{};
			Libraries::VertexFactory::Shape< float > m_localData{};
			std::vector< SubGeometry > m_subGeometries{};
			mutable std::mutex m_GPUAccessMutex{};
	};
}

/* Expose the resource manager as a convenient type. */
namespace Emeraude::Resources
{
	using IndexedVertexGeometries = Container< Graphics::Geometry::IndexedVertexResource >;
}
