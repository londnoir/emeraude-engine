/*
 * Emeraude/Graphics/Geometry/IndexedVertexResource.cpp
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

#include "IndexedVertexResource.hpp"

/* Local inclusions. */
#include "Tracer.hpp"
#include "Resources/Manager.hpp"
#include "Vulkan/TransferManager.hpp"
#include "Vulkan/CommandBuffer.hpp"
#include "VertexFactory/FileIO.hpp"
#include "VertexFactory/ShapeGenerator.hpp"

/* Defining the resource manager class id. */
template<>
const char * const Emeraude::Resources::Container< Emeraude::Graphics::Geometry::IndexedVertexResource >::ClassId{"IndexedVertexResourceContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t Emeraude::Resources::Container< Emeraude::Graphics::Geometry::IndexedVertexResource >::ClassUID{Observable::getClassUID()};

namespace Emeraude::Graphics::Geometry
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Libraries::VertexFactory;
	using namespace Libraries::PixelFactory;
	using namespace Libraries::VertexFactory;
	using namespace Vulkan;

	const size_t IndexedVertexResource::ClassUID{Observable::getClassUID()};

	IndexedVertexResource::IndexedVertexResource (const std::string & name, uint32_t resourceFlagBits) noexcept
		: Interface(name, resourceFlagBits)
	{

	}

	IndexedVertexResource::~IndexedVertexResource ()
	{
		this->destroy(true);
	}

	bool
	IndexedVertexResource::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	IndexedVertexResource::isCreated () const noexcept
	{
		if ( m_vertexBufferObject == nullptr || !m_vertexBufferObject->isCreated() )
			return false;

		if ( m_indexBufferObject == nullptr || !m_indexBufferObject->isCreated() )
			return false;

		return true;
	}

	Topology
	IndexedVertexResource::topology () const noexcept
	{
		return Topology::TriangleList;
	}

	size_t
	IndexedVertexResource::subGeometryCount () const noexcept
	{
		/* If sub-geometry mechanism is not used, we return 1. */
		if ( m_subGeometries.empty() )
			return 1;

		return m_subGeometries.size();
	}

	size_t
	IndexedVertexResource::subGeometryOffset (size_t subGeometryIndex) const noexcept
	{
		/* If sub-geometry mechanism is not used, we return 0 as offset. */
		if ( m_subGeometries.empty() )
			return 0;

		if ( subGeometryIndex >= m_subGeometries.size() )
		{
			TraceWarning{ClassId} << "Batch index " << subGeometryIndex << " overflow !";

			subGeometryIndex = 0;
		}

		return m_subGeometries[subGeometryIndex].offset();
	}

	size_t
	IndexedVertexResource::subGeometryLength (size_t subGeometryIndex) const noexcept
	{
		/* If sub-geometry mechanism is not used, we return the index count from IBO. */
		if ( m_subGeometries.empty() )
			return m_indexBufferObject->indexCount();

		if ( subGeometryIndex >= m_subGeometries.size() )
		{
			TraceWarning{ClassId} << "Batch index " << subGeometryIndex << " overflow !";

			subGeometryIndex = 0;
		}

		return m_subGeometries[subGeometryIndex].length();
	}

	const Math::Cuboid< float > &
	IndexedVertexResource::boundingBox () const noexcept
	{
		return m_localData.boundingBox();
	}

	const Math::Sphere< float > &
	IndexedVertexResource::boundingSphere () const noexcept
	{
		return m_localData.boundingSphere();
	}

	const Vulkan::VertexBufferObject *
	IndexedVertexResource::vertexBufferObject () const noexcept
	{
		return m_vertexBufferObject.get();
	}

	const Vulkan::IndexBufferObject *
	IndexedVertexResource::indexBufferObject () const noexcept
	{
		return m_indexBufferObject.get();
	}

	bool
	IndexedVertexResource::useIndexBuffer () const noexcept
	{
#ifdef DEBUG
		return m_indexBufferObject != nullptr;
#else
		return true;
#endif
	}

	bool
	IndexedVertexResource::create () noexcept
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

		if ( !Interface::buildSubGeometries(m_subGeometries, m_localData) )
		{
			TraceError{ClassId} << "Resource '" << this->name() << "' fails to build sub-geometries !";

			return false;
		}

		/* Create the vertex buffer local data. */
		std::vector< float > vertexAttributes{};

		const auto vertexElementCount = m_localData.createVerticesBuffer(
			vertexAttributes,
			attributeSize(VertexAttributeType::Position),
			this->normalEnabled() ? attributeSize(VertexAttributeType::Normal) : 0,
			this->tangentSpaceEnabled(),
			this->primaryTextureCoordinatesEnabled() ? attributeSize(VertexAttributeType::Primary2DTextureCoordinates) : 0,
			this->vertexColorEnabled() ? attributeSize(VertexAttributeType::VertexColor) : 0
		);

		/* Create the index buffer local data. */
		std::vector< uint32_t > indices{};

		if ( m_localData.createIndicesBuffer(indices) == 0 )
		{
			Tracer::error(ClassId, "Local data was unable to produce vertex indices to create an index buffer object (IBO) in video memory !");

			return false;
		}

		/* Create hardware buffers from local data. */
		if ( !this->createVideoMemoryBuffers(vertexAttributes, m_localData.vertexCount(), vertexElementCount, indices) )
			return false;

		/* Creates drawing sub geometries. */
		return true;
	}

	bool
	IndexedVertexResource::createVideoMemoryBuffers (const std::vector< float > & vertexAttributes, size_t vertexCount, size_t vertexElementCount, const std::vector< uint32_t > & indices) noexcept
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
	IndexedVertexResource::update () noexcept
	{
		if ( !this->isCreated() )
		{
			Tracer::warning(ClassId, "No buffer in video memory to update !");

			return false;
		}

		std::vector< float > vertexAttributes{};

		m_localData.createVerticesBuffer(
			vertexAttributes,
			attributeSize(VertexAttributeType::Position),
			this->normalEnabled() ? attributeSize(VertexAttributeType::Normal) : 0,
			this->tangentSpaceEnabled(),
			this->primaryTextureCoordinatesEnabled() ? attributeSize(VertexAttributeType::Primary2DTextureCoordinates) : 0,
			this->vertexColorEnabled() ? attributeSize(VertexAttributeType::VertexColor) : 0
		);

		Tracer::error(ClassId, "Updating geometry in video memory is not handled yet !");

		// TODO

		return false;
	}

	void
	IndexedVertexResource::destroy (bool clearLocalData) noexcept
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
			this->setFlagBits();
			m_localData.clear();
			m_subGeometries.clear();
		}
	}

	const char *
	IndexedVertexResource::classLabel () const noexcept
	{
		return ClassId;
	}

	bool
	IndexedVertexResource::load () noexcept
	{
		if ( !this->beginLoading() )
		{
			return false;
		}

		ShapeBuilderOptions< float > options{};
		options.enableGlobalVertexColor(PixelFactory::Red);

		m_localData = ShapeGenerator::generateCuboid(1.0F, 1.0F, 1.0F, options);

		return this->setLoadSuccess(true);
	}

	bool
	IndexedVertexResource::load (const Path::File & filepath) noexcept
	{
		if ( !this->beginLoading() )
			return false;

		if ( !FileIO::read(filepath, m_localData) )
		{
			TraceError{ClassId} << "Unable to load Geometry from '" << filepath << "' !";

			return this->setLoadSuccess(false);
		}

		/* FIXME: Should set that in reading step. */
		m_localData.flipYAxis();

		return this->setLoadSuccess(true);
	}

	bool
	IndexedVertexResource::load (const Json::Value &) noexcept
	{
		if ( !this->beginLoading() )
			return false;

		Tracer::warning(ClassId, "FIXME: This function is not available yet !");

		return this->setLoadSuccess(false);
	}

	bool
	IndexedVertexResource::load (const Shape< float > & shape) noexcept
	{
		if ( !this->beginLoading() )
			return false;

		if ( !shape.isValid() )
		{
			Tracer::error(ClassId, "The base geometry is not usable ! Abort loading ...");

			return this->setLoadSuccess(false);
		}

		m_localData = shape;

		return this->setLoadSuccess(true);
	}

	Shape< float > &
	IndexedVertexResource::localData () noexcept
	{
		return m_localData;
	}

	const Shape< float > &
	IndexedVertexResource::localData () const noexcept
	{
		return m_localData;
	}

	std::shared_ptr< IndexedVertexResource >
	IndexedVertexResource::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->indexedVertexGeometries().getResource(resourceName, directLoad);
	}

	std::shared_ptr< IndexedVertexResource >
	IndexedVertexResource::getDefault () noexcept
	{
		return Resources::Manager::instance()->indexedVertexGeometries().getDefaultResource();
	}
}
