/*
 * Emeraude/Graphics/Geometry/VertexResource.cpp
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

#include "VertexResource.hpp"

/* Local inclusions. */
#include "Resources/Manager.hpp"
#include "Tracer.hpp"
#include "VertexFactory/FileIO.hpp"
#include "VertexFactory/ShapeGenerator.hpp"
#include "Vulkan/CommandBuffer.hpp"
#include "Vulkan/TransferManager.hpp"

/* Defining the resource manager class id. */
template<>
const char * const Emeraude::Resources::Container< Emeraude::Graphics::Geometry::VertexResource >::ClassId{"VertexContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t Emeraude::Resources::Container< Emeraude::Graphics::Geometry::VertexResource >::ClassUID{Observable::getClassUID()};

namespace Emeraude::Graphics::Geometry
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Libraries::VertexFactory;
	using namespace Libraries::PixelFactory;
	using namespace Vulkan;

	const size_t VertexResource::ClassUID{Observable::getClassUID()};

	VertexResource::VertexResource (const std::string & name, uint32_t resourceFlagBits) noexcept
		: Interface(name, resourceFlagBits)
	{

	}

	VertexResource::~VertexResource ()
	{
		this->destroy(true);
	}

	bool
	VertexResource::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	VertexResource::isCreated () const noexcept
	{
		if ( m_vertexBufferObject == nullptr || !m_vertexBufferObject->isCreated() )
			return false;

		return true;
	}

	Topology
	VertexResource::topology () const noexcept
	{
		return Topology::TriangleList;
	}

	size_t
	VertexResource::subGeometryCount () const noexcept
	{
		/* If sub-geometry mechanism is not used, we return 1. */
		if ( m_subGeometries.empty() )
			return 1;

		return m_subGeometries.size();
	}

	size_t
	VertexResource::subGeometryOffset (size_t subGeometryIndex) const noexcept
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
	VertexResource::subGeometryLength (size_t subGeometryIndex) const noexcept
	{
		/* If sub-geometry mechanism is not used, we return the vertex count from VBO. */
		if ( m_subGeometries.empty() )
			return m_vertexBufferObject->vertexCount();

		if ( subGeometryIndex >= m_subGeometries.size() )
		{
			TraceWarning{ClassId} << "Batch index " << subGeometryIndex << " overflow !";

			subGeometryIndex = 0;
		}

		return m_subGeometries[subGeometryIndex].length();
	}

	const Math::Cuboid< float > &
	VertexResource::boundingBox () const noexcept
	{
		return m_localData.boundingBox();
	}

	const Math::Sphere< float > &
	VertexResource::boundingSphere () const noexcept
	{
		return m_localData.boundingSphere();
	}

	const Vulkan::VertexBufferObject *
	VertexResource::vertexBufferObject () const noexcept
	{
		return m_vertexBufferObject.get();
	}

	const Vulkan::IndexBufferObject *
	VertexResource::indexBufferObject () const noexcept
	{
		return nullptr;
	}

	bool
	VertexResource::useIndexBuffer () const noexcept
	{
		return false;
	}

	bool
	VertexResource::create () noexcept
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

		/* Create hardware buffers from local data. */
		if ( !this->createVideoMemoryBuffers(vertexAttributes, m_localData.vertexCount(), vertexElementCount) )
			return false;

		/* Creates drawing sub geometries. */
		return true;
	}

	bool
	VertexResource::createVideoMemoryBuffers (const std::vector< float > & vertexAttributes, size_t vertexCount, size_t vertexElementCount) noexcept
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

		return true;
	}

	bool
	VertexResource::update () noexcept
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
	VertexResource::destroy (bool clearLocalData) noexcept
	{
		if ( m_vertexBufferObject != nullptr )
		{
			m_vertexBufferObject->destroyFromHardware();
			m_vertexBufferObject.reset();
		}

		if ( clearLocalData )
		{
			this->setFlagBits();
			m_localData.clear();
			m_subGeometries.clear();
		}
	}

	const char *
	VertexResource::classLabel () const noexcept
	{
		return ClassId;
	}

	bool
	VertexResource::load () noexcept
	{
		if ( !this->beginLoading() )
			return false;

		ShapeBuilderOptions< float > options{};
		options.enableGlobalVertexColor(PixelFactory::Red);

		m_localData = ShapeGenerator::generateCuboid(1.0F, 1.0F, 1.0F, options);

		return this->setLoadSuccess(true);
	}

	bool
	VertexResource::load (const Libraries::Path::File & filepath) noexcept
	{
		if ( !this->beginLoading() )
			return false;

		if ( !FileIO::read(filepath, m_localData) )
		{
			TraceError{ClassId} << "Unable to load Geometry from '" << filepath << "' !";

			return this->setLoadSuccess(false);
		}

		/* FIXME: Should set that at reading step. */
		m_localData.flipYAxis();

		return this->setLoadSuccess(true);
	}

	bool
	VertexResource::load (const Json::Value & data) noexcept
	{
		if ( !this->beginLoading() )
			return false;

		Tracer::warning(ClassId, "FIXME: This function is not available yet !");

		return this->setLoadSuccess(false);
	}

	bool
	VertexResource::load (const Shape< float > & shape) noexcept
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
	VertexResource::localData () noexcept
	{
		return m_localData;
	}

	const Shape< float > &
	VertexResource::localData () const noexcept
	{
		return m_localData;
	}

	std::shared_ptr< VertexResource >
	VertexResource::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->vertexGeometries().getResource(resourceName, directLoad);
	}

	std::shared_ptr< VertexResource >
	VertexResource::getDefault () noexcept
	{
		return Resources::Manager::instance()->vertexGeometries().getDefaultResource();
	}
}
