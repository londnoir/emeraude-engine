/*
 * Emeraude/Graphics/Geometry/AdaptiveVertexGridResource.hpp
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
#include "Graphics/ImageResource.hpp"
#include "Math/Coordinates.hpp"
#include "Resources/Container.hpp"
#include "VertexFactory/Grid.hpp"

namespace Emeraude::Graphics::Geometry
{
	/**
	 * @brief Defines a geometry using a VBO and an IBO to produce a grid with LOD adapted to the point of view.
	 * @extends Emeraude::Graphics::Geometry::Interface The common base for all geometry types.
	 */
	class AdaptiveVertexGridResource final : public Interface
	{
		friend class Resources::Container< AdaptiveVertexGridResource >;

		using ResourceTrait::load;

		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"AdaptiveVertexGridResource"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs an adaptive grid geometry resource.
			 * @param name A reference to a string for the resource name.
			 * @param resourceFlagBits The resource flag bits. Default EnablePrimitiveRestart.
			 */
			explicit AdaptiveVertexGridResource (const std::string & name, uint32_t resourceFlagBits = EnablePrimitiveRestart) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			AdaptiveVertexGridResource (const AdaptiveVertexGridResource & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			AdaptiveVertexGridResource (AdaptiveVertexGridResource && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			AdaptiveVertexGridResource & operator= (const AdaptiveVertexGridResource & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			AdaptiveVertexGridResource & operator= (AdaptiveVertexGridResource && copy) noexcept = delete;

			/**
			 * @brief Destructs the adaptive grid geometry resource.
			 */
			~AdaptiveVertexGridResource () override;

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
			size_t subGeometryOffset (size_t subGeometryIndex = 0) const noexcept override;

			/** @copydoc Emeraude::Graphics::Geometry::Interface::subGeometryLength() */
			[[nodiscard]]
			size_t subGeometryLength (size_t subGeometryIndex = 0) const noexcept override;

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

			/** @copydoc Emeraude::Resources::ResourceTrait::load(const Json::Value &) */
			bool load (const Json::Value & data) noexcept override;

			/**
			 * @brief Prepares a grid ready to go on video memory with create() method from a position and a number of quads (lesser the the whole grid).
			 * @param baseGrid
			 * @param quadCount
			 * @param position
			 * @return bool
			 */
			bool load (const Libraries::VertexFactory::Grid< float > & baseGrid, size_t quadCount, const Libraries::Math::Vector< 3, float > & position) noexcept;

			/**
			 * @brief This will rewrite the vertices buffer from the grid and the new position.
			 * @param baseGrid
			 * @param position
			 * @return bool
			 */
			bool updateLocalData (const Libraries::VertexFactory::Grid< float > & baseGrid, const Libraries::Math::Vector< 3, float > & position) noexcept;

			/**
			 * @brief This will modify the render from the position of the camera using LOD with the existing data.
			 * @param view
			 */
			void updateVisibility (const Libraries::Math::Coordinates< float > & view) noexcept;

			/**
			 * @brief Gets the minimal distance to fire an update.
			 * @return float
			 */
			[[nodiscard]]
			float getMinimalUpdateDistance () const noexcept;

			/**
			 * @brief Enables the use of vertex color.
			 * @param vertexColorMap A reference to a image smart pointer.
			 */
			void enableVertexColor (const std::shared_ptr< ImageResource > & vertexColorMap) noexcept;

			/**
			 * @brief Returns whether the use of vertex color is enabled or not.
			 * @return bool
			 */
			[[nodiscard]]
			bool isVertexColorEnabled () const noexcept;

			/**
			 * @brief Returns an adaptive vertex grid resource by its name.
			 * @param resourceName A reference to a string.
			 * @param directLoad Use the direct loading mode. Default false.
			 * @return std::shared_ptr< AdaptiveVertexGridResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< AdaptiveVertexGridResource > get (const std::string & resourceName, bool directLoad = false) noexcept;

			/**
			 * @brief Returns the default adaptive vertex grid resource.
			 * @return std::shared_ptr< AdaptiveVertexGridResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< AdaptiveVertexGridResource > getDefault () noexcept;

		private:

			/**
			 * @brief Returns The first offset from base grid to build the adaptive grid.
			 * @param baseGrid A reference to the base grid.
			 * @param position A reference to a vector for the position.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t findStartingOffset (const Libraries::VertexFactory::Grid< float > & baseGrid, const Libraries::Math::Vector< 3, float > & position) const noexcept;

			/**
			 * @brief Generates the indices buffer once for all.
			 * @return bool
			 */
			bool generateIndicesBuffer () noexcept;

			std::unique_ptr< Vulkan::VertexBufferObject > m_vertexBufferObject{};
			std::unique_ptr< Vulkan::IndexBufferObject > m_indexBufferObject{};
			std::vector< float > m_localData{};
			std::vector< unsigned int > m_indices{};
			Libraries::Math::Cuboid< float > m_boundingBox{};
			Libraries::Math::Sphere< float > m_boundingSphere{};
			float m_minimalUpdateDistance{1024.0F}; // NOLINT(*-magic-numbers)
			/* Contains the number of quads in on dimension. Grids are always square. */
			size_t m_squareQuadCount{0};
			size_t m_quadCount{0};
			/* NOTE: m_squareQuads + 1 */
			size_t m_squarePointCount{0};
			size_t m_pointCount{0};
			std::shared_ptr< ImageResource > m_vertexColorMap{};
			mutable std::mutex m_GPUAccessMutex{};
	};
}

/* Expose the resource manager as a convenient type. */
namespace Emeraude::Resources
{
	using AdaptiveVertexGridGeometries = Container< Graphics::Geometry::AdaptiveVertexGridResource >;
}
