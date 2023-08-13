/*
 * Emeraude/Graphics/Geometry/AdaptiveVertexGridResource.cpp
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

#include "AdaptiveVertexGridResource.hpp"

/* Local inclusions. */
#include "Tracer.hpp"
#include "Resources/Manager.hpp"
#include "Vulkan/TransferManager.hpp"
#include "Vulkan/CommandBuffer.hpp"

/* Defining the resource manager class id. */
template<>
const char * const Emeraude::Resources::Container< Emeraude::Graphics::Geometry::AdaptiveVertexGridResource >::ClassId{"AdaptiveVertexGridContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t Emeraude::Resources::Container< Emeraude::Graphics::Geometry::AdaptiveVertexGridResource >::ClassUID{Observable::getClassUID()};

namespace Emeraude::Graphics::Geometry
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Libraries::VertexFactory;
	using namespace Libraries::PixelFactory;
	using namespace Vulkan;

	const size_t AdaptiveVertexGridResource::ClassUID{Observable::getClassUID()};

	AdaptiveVertexGridResource::AdaptiveVertexGridResource (const std::string & name, uint32_t resourceFlagBits) noexcept
		: Interface(name, resourceFlagBits)
	{

	}

	AdaptiveVertexGridResource::~AdaptiveVertexGridResource ()
	{
		this->destroy(true);
	}

	bool
	AdaptiveVertexGridResource::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	AdaptiveVertexGridResource::isCreated () const noexcept
	{
		if ( m_vertexBufferObject == nullptr || !m_vertexBufferObject->isCreated() )
			return false;

		if ( m_indexBufferObject == nullptr || !m_indexBufferObject->isCreated() )
			return false;

		return true;
	}

	Topology
	AdaptiveVertexGridResource::topology () const noexcept
	{
		return Topology::TriangleStrip;
	}

	size_t
	AdaptiveVertexGridResource::subGeometryCount () const noexcept
	{
		return 1;
	}

	size_t
	AdaptiveVertexGridResource::subGeometryOffset (size_t) const noexcept
	{
		return 0;
	}

	size_t
	AdaptiveVertexGridResource::subGeometryLength (size_t) const noexcept
	{
		return m_indexBufferObject->indexCount();
	}

	const Math::Cuboid< float > &
	AdaptiveVertexGridResource::boundingBox () const noexcept
	{
		return m_boundingBox;
	}

	const Math::Sphere< float > &
	AdaptiveVertexGridResource::boundingSphere () const noexcept
	{
		return m_boundingSphere;
	}

	const Vulkan::VertexBufferObject *
	AdaptiveVertexGridResource::vertexBufferObject () const noexcept
	{
		return m_vertexBufferObject.get();
	}

	const Vulkan::IndexBufferObject *
	AdaptiveVertexGridResource::indexBufferObject () const noexcept
	{
		return m_indexBufferObject.get();
	}

	bool
	AdaptiveVertexGridResource::useIndexBuffer () const noexcept
	{
#ifdef DEBUG
		return m_indexBufferObject != nullptr;
#else
		return true;
#endif
	}

	bool
	AdaptiveVertexGridResource::create () noexcept
	{
		const std::lock_guard< std::mutex > lock{m_GPUAccessMutex};

		if ( this->isCreated() )
		{
			Tracer::warning(ClassId, "The buffers are already in video memory ! Use update() instead.");

			return true;
		}

		/* Checking local data ... */
		if ( m_localData.empty() || m_indices.empty() )
		{
			TraceError{ClassId} <<
				"Resource '" << this->name() << "' has invalid local data ! "
				"Loading into video memory cancelled.";

			return false;
		}

		/* NOTE: Requesting a VBO using data. */
		const auto vertexElementCount = Geometry::getElementCountFromFlags(this->flagBits());

		auto * transferManager = Vulkan::TransferManager::instance(TransferType::Graphics);

		m_vertexBufferObject = std::make_unique< VertexBufferObject >(transferManager->device(), m_localData.size(), vertexElementCount);
		m_vertexBufferObject->setIdentifier(this->name() + "-VBO-VertexBufferObject");

		if ( !m_vertexBufferObject->create(*transferManager, m_localData) )
		{
			Tracer::error(ClassId, "Unable to create the vertex buffer object (VBO) !");

			m_vertexBufferObject.reset();

			return false;
		}

		/* NOTE: Requesting an IBO using data. */
		m_indexBufferObject = std::make_unique< IndexBufferObject >(transferManager->device(), m_indices.size());
		m_indexBufferObject->setIdentifier(this->name() + "-IBO-IndexBufferObject");

		if ( !m_indexBufferObject->create(*transferManager, m_indices) )
		{
			Tracer::error(ClassId, "Unable to get an index buffer object (IBO) !");

			m_indexBufferObject.reset();

			return false;
		}

		/* Creates drawing batches. */
		return true;
	}

	bool
	AdaptiveVertexGridResource::update () noexcept
	{
		if ( !this->isCreated() )
		{
			Tracer::warning(ClassId, "No buffer in video memory to update !");

			return false;
		}

		// TODO

		return false;
	}

	void
	AdaptiveVertexGridResource::destroy (bool clearLocalData) noexcept
	{
		if ( m_vertexBufferObject != nullptr )
		{
			m_vertexBufferObject->destroyFromHardware();
			m_vertexBufferObject.reset();
		}

		if ( m_indexBufferObject != nullptr )
		{
			m_indexBufferObject->destroyFromHardware();
			m_indexBufferObject.reset();
		}

		if ( clearLocalData )
		{
			this->setFlagBits(EnablePrimitiveRestart);
			m_localData.clear();
			m_indices.clear();

			m_minimalUpdateDistance = 1024.0F;
			m_squareQuadCount = 0;
			m_quadCount = 0;
			m_squarePointCount = 0;
			m_pointCount = 0;
			m_vertexColorMap.reset();
		}
	}

	const char *
	AdaptiveVertexGridResource::classLabel () const noexcept
	{
		return ClassId;
	}

	bool
	AdaptiveVertexGridResource::load () noexcept
	{
		if ( !this->beginLoading() )
			return false;

		Tracer::warning(ClassId, "FIXME: This function is not available yet !");

		return this->setLoadSuccess(false);
	}

	bool
	AdaptiveVertexGridResource::load (const Json::Value &) noexcept
	{
		if ( !this->beginLoading() )
			return false;

		Tracer::warning(ClassId, "FIXME: This function is not available yet !");

		return this->setLoadSuccess(false);
	}

	bool
	AdaptiveVertexGridResource::load (const Grid< float > & baseGrid, size_t quadCount, const Vector< 3, float > & position) noexcept
	{
		if ( !this->beginLoading() )
			return false;

		if ( !baseGrid.isValid() )
		{
			Tracer::warning(ClassId, "Grid data is not yet loaded, so it can't be moved to video memory.");

			return this->setLoadSuccess(false);
		}

		if ( quadCount >= baseGrid.quadCount() )
		{
			TraceError{ClassId} << "Grid data must be smaller than AdaptiveGridGeometry !";

			return this->setLoadSuccess(false);
		}

		m_squareQuadCount = quadCount;
		m_quadCount = m_squareQuadCount * m_squareQuadCount;
		m_squarePointCount = m_squareQuadCount + 1;
		m_pointCount = m_squarePointCount * m_squarePointCount;
		m_minimalUpdateDistance = baseGrid.quadSize() * m_squareQuadCount * 0.5F;

		/* Generate vertices buffer. */
		if ( !this->updateLocalData(baseGrid, position) )
			return this->setLoadSuccess(false);

		/* Generate indices buffer. */
		if ( !this->generateIndicesBuffer() )
			return this->setLoadSuccess(false);

		return this->setLoadSuccess(true);
	}

	size_t
	AdaptiveVertexGridResource::findStartingOffset (const Grid< float > & baseGrid, const Vector< 3, float > & position) const noexcept
	{
		/* Convert from 3D to 2D coordinates and shift the position
		 * to the bottom-left position of the future adaptive grid
		 * to get the right first quad. */
		auto x = position[X] - m_minimalUpdateDistance;
		auto y = position[Z] - m_minimalUpdateDistance;

		auto offset = baseGrid.nearestQuad(x, y).topLeftIndex();
		auto max = baseGrid.pointCount() - m_pointCount;

		if ( offset >= max )
			return max - 1;

		return offset;
	}

	bool
	AdaptiveVertexGridResource::generateIndicesBuffer () noexcept
	{
		for ( auto y = 0U; y < m_squareQuadCount; y++ )
		{
			auto rowOffset = y * m_squarePointCount;

			for ( auto x = 0U; x < m_squareQuadCount; x++ )
			{
				/* Top left vertex. */
				auto tl = rowOffset + x;
				/* Bottom left vertex. */
				auto bl = tl + m_squarePointCount;
				/* Top right vertex. */
				auto tr = tl + 1;
				/* Bottom right vertex. */
				auto br = bl + 1;

				if ( x == 0 )
				{
					m_indices.emplace_back(tl);
					m_indices.emplace_back(bl);
				}

				m_indices.emplace_back(tr);
				m_indices.emplace_back(br);
			}

			/* Primitive restart. This will break the triangle strip. */
			m_indices.emplace_back(std::numeric_limits< uint32_t >::max());
		}

		return !m_indices.empty();
	}

	bool
	AdaptiveVertexGridResource::updateLocalData (const Grid< float > & baseGrid, const Vector< 3, float > & position) noexcept
	{
		if ( !baseGrid.isValid() )
		{
			Tracer::warning(ClassId, "Grid data is no more valid... Unable to use it for updating the adaptive grid.");

			return false;
		}

		m_localData.clear();

		auto startingOffset = this->findStartingOffset(baseGrid, position);

		for ( size_t y = 0; y < m_squarePointCount; y++ )
		{
			auto rowOffset = startingOffset + (y * baseGrid.squaredPointCount());

			for ( size_t x = 0; x < m_squarePointCount; x++ )
			{
				auto index = rowOffset + x;

				addGridPointToVertexAttributes(baseGrid, index, this->flagBits(), m_localData);

			}
		}

		return true;
	}

	void
	AdaptiveVertexGridResource::updateVisibility (const Coordinates< float > & /*view*/) noexcept
	{
		/* FIXME: Empty function. */
	}

	float
	AdaptiveVertexGridResource::getMinimalUpdateDistance () const noexcept
	{
		return m_minimalUpdateDistance;
	}

	void
	AdaptiveVertexGridResource::enableVertexColor (const std::shared_ptr< ImageResource > & vertexColorMap) noexcept
	{
		if ( this->isCreated() )
		{
			Tracer::error(ClassId, "Vertex color must be enabled before loading the data !");

			return;
		}

		m_vertexColorMap = vertexColorMap;
	}

	bool
	AdaptiveVertexGridResource::isVertexColorEnabled () const noexcept
	{
		return m_vertexColorMap != nullptr;
	}

	std::shared_ptr< AdaptiveVertexGridResource >
	AdaptiveVertexGridResource::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->adaptiveVertexGridGeometries().getResource(resourceName, directLoad);
	}

	std::shared_ptr< AdaptiveVertexGridResource >
	AdaptiveVertexGridResource::getDefault () noexcept
	{
		return Resources::Manager::instance()->adaptiveVertexGridGeometries().getDefaultResource();
	}
}
