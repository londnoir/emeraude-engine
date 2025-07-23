/*
 * src/Graphics/Geometry/VertexGridResource.hpp
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

namespace EmEn::Graphics::Geometry
{
	/**
	 * @brief Defines a geometry using a VBO and an IBO to produce a grid.
	 * @extends EmEn::Graphics::Geometry::Interface The common base for all geometry types.
	 */
	class VertexGridResource final : public Interface
	{
		friend class Resources::Container< VertexGridResource >;

		using ResourceTrait::load;

		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VertexGridResource"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Construct a vertex grid geometry resource.
			 * @param name A reference to a string for the resource name.
			 * @param geometryFlagBits The geometry resource flag bits, See EmEn::Graphics::Geometry::GeometryFlagBits. Default EnablePrimitiveRestart.
			 */
			explicit VertexGridResource (const std::string & name, uint32_t geometryFlagBits = EnablePrimitiveRestart) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			VertexGridResource (const VertexGridResource & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			VertexGridResource (VertexGridResource && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			VertexGridResource & operator= (const VertexGridResource & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			VertexGridResource & operator= (VertexGridResource && copy) noexcept = delete;

			/**
			 * @brief Destructs the vertex grid geometry resource.
			 */
			~VertexGridResource () override;

			/** @copydoc EmEn::Libs::ObservableTrait::classUID() const */
			[[nodiscard]]
			size_t
			classUID () const noexcept override
			{
				return ClassUID;
			}

			/** @copydoc EmEn::Libs::ObservableTrait::is() const */
			[[nodiscard]]
			bool
			is (size_t classUID) const noexcept override
			{
				return classUID == ClassUID;
			}

			/** @copydoc EmEn::Graphics::Geometry::Interface::isCreated() */
			[[nodiscard]]
			bool
			isCreated () const noexcept override
			{
				if ( m_vertexBufferObject == nullptr || !m_vertexBufferObject->isCreated() )
				{
					return false;
				}

				if ( m_indexBufferObject == nullptr || !m_indexBufferObject->isCreated() )
				{
					return false;
				}

				return true;
			}

			/** @copydoc EmEn::Graphics::Geometry::Interface::topology() */
			[[nodiscard]]
			Topology
			topology () const noexcept override
			{
				return Topology::TriangleStrip;
			}

			/** @copydoc EmEn::Graphics::Geometry::Interface::subGeometryCount() */
			[[nodiscard]]
			uint32_t
			subGeometryCount () const noexcept override
			{
				return 1;
			}

			/** @copydoc EmEn::Graphics::Geometry::Interface::subGeometryRange() */
			[[nodiscard]]
			std::array< uint32_t, 2 >
			subGeometryRange (uint32_t /*subGeometryIndex*/ = 0) const noexcept override
			{
				return {0, static_cast< uint32_t >(m_indexBufferObject->indexCount())};
			}

			/** @copydoc EmEn::Graphics::Geometry::Interface::boundingBox() */
			[[nodiscard]]
			const Libs::Math::Space3D::AACuboid< float > &
			boundingBox () const noexcept override
			{
				return m_localData.boundingBox();
			}

			/** @copydoc EmEn::Graphics::Geometry::Interface::boundingSphere() */
			[[nodiscard]]
			const Libs::Math::Space3D::Sphere< float > &
			boundingSphere () const noexcept override
			{
				return m_localData.boundingSphere();
			}

			/** @copydoc EmEn::Graphics::Geometry::Interface::vertexBufferObject() */
			[[nodiscard]]
			const Vulkan::VertexBufferObject *
			vertexBufferObject () const noexcept override
			{
				return m_vertexBufferObject.get();
			}

			/** @copydoc EmEn::Graphics::Geometry::Interface::indexBufferObject() */
			[[nodiscard]]
			const Vulkan::IndexBufferObject *
			indexBufferObject () const noexcept override
			{
				return m_indexBufferObject.get();
			}

			/** @copydoc EmEn::Graphics::Geometry::Interface::useIndexBuffer() */
			[[nodiscard]]
			bool
			useIndexBuffer () const noexcept override
			{
				if constexpr ( IsDebug )
				{
					return m_indexBufferObject != nullptr;
				}

				return true;
			}

			/** @copydoc EmEn::Graphics::Geometry::Interface::create() */
			bool create () noexcept override;

			/** @copydoc EmEn::Graphics::Geometry::Interface::update() */
			bool update () noexcept override;

			/** @copydoc EmEn::Graphics::Geometry::Interface::destroy() */
			void destroy (bool clearLocalData) noexcept override;

			/** @copydoc EmEn::Resources::ResourceTrait::classLabel() const */
			[[nodiscard]]
			const char *
			classLabel () const noexcept override
			{
				return ClassId;
			}

			/** @copydoc EmEn::Resources::ResourceTrait::load() */
			bool load () noexcept override;

			/** @copydoc EmEn::Resources::ResourceTrait::load(const Json::Value &) */
			bool load (const Json::Value & data) noexcept override;

			/**
			 * @brief Loads a flat squared grid.
			 * @param size The size of the whole size of one dimension of the grid. i.e. If the size is 1024, the grid will be from +512 to -512.
			 * @param division How many cell in one dimension.
			 * @param UVMultiplier Texture coordinates multiplier. Default, 1.0.
			 * @param vertexColorGenMode Set the vertex color generation mode. Default random.
			 * @param globalVertexColor A reference to a color. Default black.
			 * @return bool
			 */
			bool load (float size, uint32_t division, float UVMultiplier = 1.0F, const VertexColorGenMode & vertexColorGenMode = VertexColorGenMode::UseRandom, const Libs::PixelFactory::Color< float > & globalVertexColor = Libs::PixelFactory::Black) noexcept;

			/**
			 * @brief This load a geometry from a parametric object.
			 * @note This only local data and not pushing it to the video RAM.
			 * @param grid A reference to a geometry from vertex factory library.
			 * @param vertexColorGenMode Set the vertex color generation mode. Default random.
			 * @param globalVertexColor A reference to a color. Default black.
			 * @return bool
			 */
			bool load (const Libs::VertexFactory::Grid< float > & grid, const VertexColorGenMode & vertexColorGenMode = VertexColorGenMode::UseRandom, const Libs::PixelFactory::Color< float > & globalVertexColor = Libs::PixelFactory::Black) noexcept;

			/**
			 * @brief Gives access to the local geometry data.
			 * @return Libraries::VertexFactory::Grid< float > &
			 */
			Libs::VertexFactory::Grid< float > &
			localData () noexcept
			{
				return m_localData;
			}

			/**
			 * @brief Gives access to the local geometry data.
			 * @return const Libraries::VertexFactory::Grid< float > &
			 */
			[[nodiscard]]
			const Libs::VertexFactory::Grid< float > &
			localData () const noexcept
			{
				return m_localData;
			}

			/**
			 * @brief Returns a vertex grid resource by its name.
			 * @param resourceName A reference to a string.
			 * @param directLoad Use the direct loading mode. Default false.
			 * @return std::shared_ptr< VertexGridResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< VertexGridResource > get (const std::string & resourceName, bool directLoad = false) noexcept;

			/**
			 * @brief Returns the default vertex grid resource.
			 * @return std::shared_ptr< VertexGridResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< VertexGridResource > getDefault () noexcept;

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
			bool createVideoMemoryBuffers (const std::vector< float > & vertexAttributes, uint32_t vertexCount, uint32_t vertexElementCount, const std::vector< uint32_t > & indices) noexcept;

			/**
			 * @brief Adds a vertex to the local buffer.
			 * @param index The point index in the local grid.
			 * @param buffer A reference to the vertex attribute buffer.
			 * @param vertexElementCount The number of element for a vertex count.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t addVertexToBuffer (uint32_t index, std::vector< float > & buffer, uint32_t vertexElementCount) const noexcept;

			/* JSON key. */
			static constexpr auto JKSize{"Size"};
			static constexpr auto JKDivision{"Division"};
			static constexpr auto JKUVMultiplier{"UVMultiplier"};

			static constexpr auto DefaultSize{1024.0F};
			static constexpr auto DefaultDivision{32UL};
			static constexpr auto DefaultUVMultiplier{32.0F};

			std::unique_ptr< Vulkan::VertexBufferObject > m_vertexBufferObject;
			std::unique_ptr< Vulkan::IndexBufferObject > m_indexBufferObject;
			Libs::VertexFactory::Grid< float > m_localData;
			VertexColorGenMode m_vertexColorGenMode{VertexColorGenMode::UseRandom};
			Libs::PixelFactory::Color< float > m_globalVertexColor;
	};
}

/* Expose the resource manager as a convenient type. */
namespace EmEn::Resources
{
	using VertexGridGeometries = Container< Graphics::Geometry::VertexGridResource >;
}
