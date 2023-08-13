/*
 * Emeraude/Graphics/Geometry/VertexGridResource.cpp
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

#include "VertexGridResource.hpp"

/* Local inclusions. */
#include "Resources/Manager.hpp"
#include "Tracer.hpp"
#include "Vulkan/CommandBuffer.hpp"
#include "Vulkan/TransferManager.hpp"

/* Defining the resource manager class id. */
template<>
const char * const Emeraude::Resources::Container< Emeraude::Graphics::Geometry::VertexGridResource >::ClassId{"VertexGridContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t Emeraude::Resources::Container< Emeraude::Graphics::Geometry::VertexGridResource >::ClassUID{Observable::getClassUID()};

namespace Emeraude::Graphics::Geometry
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Libraries::VertexFactory;
	using namespace Libraries::PixelFactory;
	using namespace Vulkan;

	const size_t VertexGridResource::ClassUID{Observable::getClassUID()};

	VertexGridResource::VertexGridResource (const std::string & name, uint32_t resourceFlagBits) noexcept
		: Interface(name, resourceFlagBits)
	{

	}

	VertexGridResource::~VertexGridResource ()
	{
		this->destroy(true);
	}

	bool
	VertexGridResource::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	VertexGridResource::isCreated () const noexcept
	{
		if ( m_vertexBufferObject == nullptr || !m_vertexBufferObject->isCreated() )
			return false;

		if ( m_indexBufferObject == nullptr || !m_indexBufferObject->isCreated() )
			return false;

		return true;
	}

	Topology
	VertexGridResource::topology () const noexcept
	{
		return Topology::TriangleStrip;
	}

	size_t
	VertexGridResource::subGeometryCount () const noexcept
	{
		return 1;
	}

	size_t
	VertexGridResource::subGeometryOffset (size_t) const noexcept
	{
		return 0;
	}

	size_t
	VertexGridResource::subGeometryLength (size_t) const noexcept
	{
		return m_indexBufferObject->indexCount();
	}

	const Math::Cuboid< float > &
	VertexGridResource::boundingBox () const noexcept
	{
		return m_localData.boundingBox();
	}

	const Math::Sphere< float > &
	VertexGridResource::boundingSphere () const noexcept
	{
		return m_localData.boundingSphere();
	}

	const Vulkan::VertexBufferObject *
	VertexGridResource::vertexBufferObject () const noexcept
	{
		return m_vertexBufferObject.get();
	}

	const Vulkan::IndexBufferObject *
	VertexGridResource::indexBufferObject () const noexcept
	{
		return m_indexBufferObject.get();
	}

	bool
	VertexGridResource::useIndexBuffer () const noexcept
	{
#ifdef DEBUG
		return m_indexBufferObject != nullptr;
#else
		return true;
#endif
	}

	bool
	VertexGridResource::create () noexcept
	{
		if ( this->isCreated() )
		{
			Tracer::warning(ClassId, "The buffers are already in video memory ! Use update() instead.");

			return true;
		}

		/* Checking local data ... */
		if ( !m_localData.isValid() )
		{
			TraceError{ClassId} <<
				"Resource '" << this->name() << "' has invalid local data ! "
				"Loading into video memory cancelled.";

			return false;
		}

		/* NOTE: Example for a 4 divisions square. */

		/* Create the vertex buffer and the index buffer local data. */
		const auto vertexElementCount = Geometry::getElementCountFromFlags(this->flagBits());
		const auto rowCount = m_localData.squaredQuadCount(); /* 4 */
		/* This holds the number of indices requested to draw a
		 * full row of quads including the primitive restart. */
		const auto indexPerRowCount = (m_localData.squaredPointCount() * 2) + 1; /* 11 */
		const auto indexCount = indexPerRowCount * rowCount; /* 44 */

		std::vector< float > vertexAttributes{};
		vertexAttributes.reserve(m_localData.pointCount() * vertexElementCount); /* 25 * element count per vertex */

		std::vector< uint32_t > indices{};
		indices.reserve(indexCount);

		for ( auto quadYIndex = 0U; quadYIndex < rowCount; quadYIndex++ )
		{
			const auto sharedIndexesOffset = quadYIndex > 1 ? (quadYIndex * indexPerRowCount) - indexPerRowCount : 0;

			for ( auto quadXIndex = 0U; quadXIndex < rowCount; quadXIndex++ )
			{
				const auto currentQuad = m_localData.quad(quadXIndex, quadYIndex);

				/* NOTE : Only once by row of quads at execute
				 * because of GL_TRIANGLE_STRIP technic. */
				if ( quadXIndex == 0 )
				{
					/* NOTE: Shared index if above row 0. */
					if ( quadYIndex == 0 )
					{
						/* Top left vertex. */
						indices.emplace_back(this->addVertexToBuffer(currentQuad.topLeftIndex(), vertexAttributes, vertexElementCount));
					}
					else
					{
						/* Adds a previously registered vertex index. */
						indices.emplace_back(indices[sharedIndexesOffset + 1]);
					}

					/* Bottom left vertex. */
					indices.emplace_back(this->addVertexToBuffer(currentQuad.bottomLeftIndex(), vertexAttributes, vertexElementCount));
				}

				/* NOTE : Shared index if above row 0. */
				if ( quadYIndex == 0 )
				{
					/* Top right vertex. */
					indices.emplace_back(this->addVertexToBuffer(currentQuad.topRightIndex(), vertexAttributes, vertexElementCount));
				}
				else
				{
					/* Adds a previously registered vertex index. */
					indices.emplace_back(indices[sharedIndexesOffset + ((quadXIndex + 1) * 2) + 1]);
				}

				/* Bottom right vertex. */
				indices.emplace_back(this->addVertexToBuffer(currentQuad.bottomRightIndex(), vertexAttributes, vertexElementCount));
			}

			/* Add a primitive restart hint. This will break the triangle strip. */
			indices.emplace_back(std::numeric_limits< uint32_t >::max());
		}

		/* Create hardware buffers from local data. */
		if ( !this->createVideoMemoryBuffers(vertexAttributes, m_localData.pointCount(), vertexElementCount, indices) )
			return false;

		return true;
	}

	bool
	VertexGridResource::createVideoMemoryBuffers (const std::vector< float > & vertexAttributes, size_t vertexCount, size_t vertexElementCount, const std::vector< uint32_t > & indices) noexcept
	{
		const std::lock_guard< std::mutex > lock{m_GPUAccessMutex};

		auto * transferManager = Vulkan::TransferManager::instance(TransferType::Graphics);

		m_vertexBufferObject = std::make_unique< VertexBufferObject >(transferManager->device(), vertexCount, vertexElementCount);
		m_vertexBufferObject->setIdentifier(this->name() + "-VBO-VertexBufferObject");

		if ( !m_vertexBufferObject->create(*transferManager, vertexAttributes) )
		{
			Tracer::error(ClassId, "Unable to create the vertex buffer object (VBO) !");

			m_vertexBufferObject.reset();

			return false;
		}

		m_indexBufferObject = std::make_unique< IndexBufferObject >(transferManager->device(), indices.size());
		m_indexBufferObject->setIdentifier(this->name() + "-IBO-IndexBufferObject");

		if ( !m_indexBufferObject->create(*transferManager, indices) )
		{
			Tracer::error(ClassId, "Unable to get an index buffer object (IBO) !");

			m_indexBufferObject.reset();

			return false;
		}

		return true;
	}

	bool
	VertexGridResource::update () noexcept
	{
		if ( !this->isCreated() )
		{
			Tracer::warning(ClassId, "No buffer in video memory to update !");

			return false;
		}

		// TODO

		Tracer::error(ClassId, "Updating geometry in video memory is not handled yet !");

		return false;
	}

	void
	VertexGridResource::destroy (bool clearLocalData) noexcept
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
		}
	}

	const char *
	VertexGridResource::classLabel () const noexcept
	{
		return ClassId;
	}

	bool
	VertexGridResource::load () noexcept
	{
		return this->load(1024.0F, 32, 32.0F);
	}

	bool
	VertexGridResource::load (const Json::Value & data) noexcept
	{
		return this->load(
			FastJSON::getFloat(data, JKSize, 1024.0F),
			FastJSON::getUnsignedInteger(data, JKDivision, 32),
			FastJSON::getFloat(data, JKUVMultiplier, 32.0F)
		);
	}

	bool
	VertexGridResource::load (float size, size_t division, float UVMultiplier) noexcept
	{
		if ( !this->beginLoading() )
			return false;

		if ( size < 0.0F )
		{
			Tracer::error(ClassId, "Size parameter must be positive !");

			return this->setLoadSuccess(false);
		}

		if ( division < 1 )
		{
			Tracer::error(ClassId, "Division parameter must be a least 1 !");

			return this->setLoadSuccess(false);
		}

		if ( !m_localData.initializeData(size, division) )
		{
			Tracer::error(ClassId, "Unable to initialize local data !");

			return this->setLoadSuccess(false);
		}

		m_localData.setUVMultiplier(UVMultiplier);

		return this->setLoadSuccess(true);
	}

	bool
	VertexGridResource::load (const Grid< float > & grid) noexcept
	{
		if ( !this->beginLoading() )
			return false;

		if ( !grid.isValid() )
		{
			Tracer::error(ClassId, "The base geometry is not usable !");

			return this->setLoadSuccess(false);
		}

		m_localData = grid;

		return this->setLoadSuccess(true);
	}

	Grid< float > &
	VertexGridResource::localData () noexcept
	{
		return m_localData;
	}

	const Grid< float > &
	VertexGridResource::localData () const noexcept
	{
		return m_localData;
	}

	std::shared_ptr< VertexGridResource >
	VertexGridResource::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->vertexGridGeometries().getResource(resourceName, directLoad);
	}

	std::shared_ptr< VertexGridResource >
	VertexGridResource::getDefault () noexcept
	{
		return Resources::Manager::instance()->vertexGridGeometries().getDefaultResource();
	}
}
