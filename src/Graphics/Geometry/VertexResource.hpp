/*
 * src/Graphics/Geometry/VertexResource.hpp
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
#include <vector>
#include <memory>

/* Local inclusions for inheritances. */
#include "Interface.hpp"

/* Local inclusions for usages. */
#include "Resources/Container.hpp"

namespace Emeraude::Graphics::Geometry
{
	/**
	 * @brief Defines an arbitrary geometry using a VBO.
	 * @extends Emeraude::Graphics::Geometry::Interface The common base for all geometry types.
	 */
	class VertexResource final : public Interface
	{
		friend class Resources::Container< VertexResource >;

		using ResourceTrait::load;

		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VertexResource"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs a basic geometry resource.
			 * @param name A reference to a string for the resource name.
			 * @param geometryFlagBits The geometry resource flag bits, See Emeraude::Graphics::Geometry::GeometryFlagBits. Default none.
			 */
			explicit VertexResource (const std::string & name, uint32_t geometryFlagBits = 0) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			VertexResource (const VertexResource & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			VertexResource (VertexResource && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			VertexResource & operator= (const VertexResource & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			VertexResource & operator= (VertexResource && copy) noexcept = delete;

			/**
			 * @brief Destructs the basic geometry resource.
			 */
			~VertexResource () override;

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

			/** @copydoc Emeraude::Graphics::Geometry::Interface::isCreated() */
			[[nodiscard]]
			bool
			isCreated () const noexcept override
			{
				return !static_cast< bool >(m_vertexBufferObject == nullptr || !m_vertexBufferObject->isCreated());
			}

			/** @copydoc Emeraude::Graphics::Geometry::Interface::topology() */
			[[nodiscard]]
			Topology
			topology () const noexcept override
			{
				return Topology::TriangleList;
			}

			/** @copydoc Emeraude::Graphics::Geometry::Interface::subGeometryCount() */
			[[nodiscard]]
			size_t
			subGeometryCount () const noexcept override
			{
				/* If sub-geometry mechanism is not used, we return 1. */
				if ( m_subGeometries.empty() )
				{
					return 1;
				}

				return m_subGeometries.size();
			}

			/** @copydoc Emeraude::Graphics::Geometry::Interface::subGeometryRange() */
			[[nodiscard]]
			std::array< uint32_t, 2 >
			subGeometryRange (size_t subGeometryIndex) const noexcept override
			{
				/* NOTE: If sub-geometry mechanism is not used, we return 0 as offset. */
				if ( m_subGeometries.empty() )
				{
					return {0, static_cast< uint32_t >(m_vertexBufferObject->vertexCount())};
				}

				if ( subGeometryIndex >= m_subGeometries.size() )
				{
					return m_subGeometries[0].range();
				}

				return m_subGeometries[subGeometryIndex].range();
			}

			/** @copydoc Emeraude::Graphics::Geometry::Interface::boundingBox() */
			[[nodiscard]]
			const Libraries::Math::Cuboid< float > &
			boundingBox () const noexcept override
			{
				return m_localData.boundingBox();
			}

			/** @copydoc Emeraude::Graphics::Geometry::Interface::boundingSphere() */
			[[nodiscard]]
			const Libraries::Math::Sphere< float > &
			boundingSphere () const noexcept override
			{
				return m_localData.boundingSphere();
			}

			/** @copydoc Emeraude::Graphics::Geometry::Interface::vertexBufferObject() */
			[[nodiscard]]
			const Vulkan::VertexBufferObject *
			vertexBufferObject () const noexcept override
			{
				return m_vertexBufferObject.get();
			}

			/** @copydoc Emeraude::Graphics::Geometry::Interface::indexBufferObject() */
			[[nodiscard]]
			const Vulkan::IndexBufferObject *
			indexBufferObject () const noexcept override
			{
				return nullptr;
			}

			/** @copydoc Emeraude::Graphics::Geometry::Interface::useIndexBuffer() */
			[[nodiscard]]
			bool
			useIndexBuffer () const noexcept override
			{
				return false;
			}

			/** @copydoc Emeraude::Graphics::Geometry::Interface::create() */
			bool create () noexcept override;

			/** @copydoc Emeraude::Graphics::Geometry::Interface::update() */
			bool update () noexcept override;

			/** @copydoc Emeraude::Graphics::Geometry::Interface::destroy() */
			void destroy (bool clearLocalData) noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::classLabel() const */
			[[nodiscard]]
			const char *
			classLabel () const noexcept override
			{
				return ClassId;
			}

			/** @copydoc Emeraude::Resources::ResourceTrait::load() */
			bool load () noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load(const std::filesystem::path &) */
			bool load (const std::filesystem::path & filepath) noexcept override;

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
			Libraries::VertexFactory::Shape< float > &
			localData () noexcept
			{
				return m_localData;
			}

			/**
			 * @brief Gives access to the local geometry data.
			 * @return const Libraries::VertexFactory::Shape< float > &
			 */
			[[nodiscard]]
			const Libraries::VertexFactory::Shape< float > &
			localData () const noexcept
			{
				return m_localData;
			}

			/**
			 * @brief Returns a vertex resource by its name.
			 * @param resourceName A reference to a string.
			 * @param directLoad Use the direct loading mode. Default false.
			 * @return std::shared_ptr< VertexResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< VertexResource > get (const std::string & resourceName, bool directLoad = false) noexcept;

			/**
			 * @brief Returns the default vertex resource.
			 * @return std::shared_ptr< VertexResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< VertexResource > getDefault () noexcept;

		private:

			/**
			 * @brief Creates an hardware buffer on the device.
			 * @param vertexAttributes A reference to a vertex attribute vector.
			 * @param vertexCount The number of vertices.
			 * @param vertexElementCount The number of elements composing a vertex.
			 * @return bool
			 */
			[[nodiscard]]
			bool createVideoMemoryBuffers (const std::vector< float > & vertexAttributes, size_t vertexCount, size_t vertexElementCount) noexcept;

			std::unique_ptr< Vulkan::VertexBufferObject > m_vertexBufferObject;
			Libraries::VertexFactory::Shape< float > m_localData;
			std::vector< SubGeometry > m_subGeometries;
	};
}

/* Expose the resource manager as a convenient type. */
namespace Emeraude::Resources
{
	using VertexGeometries = Container< Graphics::Geometry::VertexResource >;
}
