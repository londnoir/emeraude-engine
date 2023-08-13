/*
 * Emeraude/Graphics/ViewMatrices2DUBO.cpp
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

#include "ViewMatrices2DUBO.hpp"

/* C/C++ standard libraries. */
#include <cstring>

/* Local inclusions */
#include "Tracer.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/RenderTarget/Abstract.hpp"
#include "Vulkan/TransferManager.hpp"
#include "Vulkan/UniformBufferObject.hpp"
#include "Vulkan/DescriptorSet.hpp"

namespace Emeraude::Graphics
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Vulkan;

	ViewMatrices2DUBO::ViewMatrices2DUBO (bool enableCloseView, bool enableInfinityView) noexcept
		: ViewMatricesInterface(enableCloseView, enableInfinityView)
	{

	}

	const Matrix< 4, float > &
	ViewMatrices2DUBO::projectionMatrix () const noexcept
	{
		return m_projection;
	}

	const Matrix< 4, float > &
	ViewMatrices2DUBO::viewMatrix (size_t /*index*/) const noexcept
	{
		return m_view;
	}

	const Matrix< 4, float > &
	ViewMatrices2DUBO::infinityViewMatrix (size_t /*index*/) const noexcept
	{
		return m_infinityView;
	}

	const Matrix< 4, float > &
	ViewMatrices2DUBO::viewProjectionMatrix (size_t /*index*/) const noexcept
	{
		return m_viewProjection;
	}

	const Matrix< 4, float > &
	ViewMatrices2DUBO::infinityViewProjectionMatrix (size_t /*index*/) const noexcept
	{
		return m_infinityViewProjection;
	}

	const Vector< 3, float > &
	ViewMatrices2DUBO::position () const noexcept
	{
		return m_position;
	}

	const Vector< 3, float > &
	ViewMatrices2DUBO::velocity () const noexcept
	{
		return m_velocity;
	}

	const Vector< 4, float > &
	ViewMatrices2DUBO::viewProperties () const noexcept
	{
		return m_viewProperties;
	}

	const Frustum &
	ViewMatrices2DUBO::frustum (size_t /*index*/) const noexcept
	{
		return m_frustum;
	}

	float
	ViewMatrices2DUBO::getAspectRatio () const noexcept
	{
		if ( m_viewProperties[Y] <= 0.0F )
		{
			Tracer::error(ClassId, "View properties for width and height are invalid ! Unable to compute the aspect ratio.");

			return 1.0F;
		}

		return m_viewProperties[X] / m_viewProperties[Y];
	}

	float
	ViewMatrices2DUBO::fieldOfView () const noexcept
	{
		const auto Rad2Deg = 180.0F / Pi< float >;

		return std::atan(1.0F / m_projection[M4x4Col1Row1]) * 2.0F * Rad2Deg; // NOLINT(*-magic-numbers)
	}

	void
	ViewMatrices2DUBO::updatePerspectiveViewProperties (float width, float height, float distance, float fov) noexcept
	{
		TraceInfo{ClassId} <<
			"Updating perspective view matrices with " << width << "X" << height << ", "
			"distance: " << distance << " and FOV: " << fov << " ...";

		m_viewProperties[X] = width;
		m_viewProperties[Y] = height;
		m_viewProperties[W] = distance;

		/* Formula : nearPlane = nearestObject / sqrt(1 + tan(fov/2)² · (getAspectRatio² + 1))) */
		const auto aspectRatio = this->getAspectRatio();
		const auto powA = std::pow(std::tan(Radian(fov) * 0.5F), 2.0F);
		const auto powB = std::pow(aspectRatio, 2.0F) + 1.0F;

		m_viewProperties[Z] = 0.1F / std::sqrt(1.0F + powA * powB); // NOLINT(*-magic-numbers)

		/* Configures the 3D projection matrix. */
		m_projection = Matrix< 4, float >::perspectiveProjection(fov, aspectRatio, m_viewProperties[Z], m_viewProperties[W]);

		this->updateVideoMemory();
	}

	void
	ViewMatrices2DUBO::updateOrthographicViewProperties (float width, float height, float distance, float near) noexcept
	{
		TraceInfo{ClassId} <<
			"Updating orthographic view matrices with " << width << "X" << height << ", "
			"distance: " << distance << " and near: " << near << " ...";

		m_viewProperties[X] = width;
		m_viewProperties[Y] = height;
		m_viewProperties[Z] = near;
		m_viewProperties[W] = distance;

		const auto side = m_viewProperties[W] * this->getAspectRatio();

		m_projection = Matrix< 4, float >::orthographicProjection(-side, side, -m_viewProperties[W], m_viewProperties[W], m_viewProperties[Z], m_viewProperties[W]);

		this->updateVideoMemory();
	}

	void
	ViewMatrices2DUBO::updateViewCoordinates (const Coordinates< float > & coordinates, const Vector< 3, float > & velocity) noexcept
	{
		/* Sets the camera world position and velocity. */
		m_position = coordinates.position();
		m_velocity = velocity;

		/* Use the camera position as the point of view. */
		if ( this->closeViewEnabled() )
		{
			m_view = coordinates.viewMatrix();
			m_viewProjection = m_projection * m_view;

			/* Updates the view frustum (Only in close view). */
			m_frustum.update(m_viewProjection);
		}

		/* Same but update matrices for far objects. */
		if ( this->infinityViewEnabled() )
		{
			m_infinityView = coordinates.viewMatrix(true);
			m_infinityViewProjection = m_projection * m_infinityView;
		}

		this->updateVideoMemory();
	}

	bool
	ViewMatrices2DUBO::create (const RenderTarget::Abstract & renderTarget) noexcept
	{
		const std::lock_guard< std::mutex > lock{m_memoryAccess};

		auto * renderer = Graphics::Renderer::instance();

		auto * transferManager = TransferManager::instance(TransferType::Graphics);

		auto descriptorSetLayout = renderer->getViewDescriptorSetLayout(renderTarget);

		/* Prepare the close view UBO and descriptor set. */
		if ( this->closeViewEnabled() )
		{
			m_uniformBufferObject = std::make_unique< UniformBufferObject >(transferManager->device(), ViewUBOSize);
			m_uniformBufferObject->setIdentifier("ViewMatrices2D-" + renderTarget.id() + "-UniformBufferObject");

			if ( !m_uniformBufferObject->createOnHardware() )
			{
				Tracer::error(ClassId, "Unable to get an uniform buffer object for close view !");

				m_uniformBufferObject.reset();

				return false;
			}

			m_descriptorSet = std::make_unique< DescriptorSet >(renderer->descriptorPool(), descriptorSetLayout);
			m_descriptorSet->setIdentifier("ViewMatrices2D-" + renderTarget.id() + "-DescriptorSet");

			if ( !m_descriptorSet->create() )
			{
				m_descriptorSet.reset();

				Tracer::error(ClassId, "Unable to create the close view descriptor set !");

				return false;
			}

			if ( !m_descriptorSet->writeUniformBufferObject(*m_uniformBufferObject, 0) )
			{
				Tracer::error(ClassId, "Unable to setup the close view descriptor set !");

				return false;
			}
		}

		/* Prepare the infinite view UBO and descriptor set. */
		if ( this->infinityViewEnabled() )
		{
			m_infinityUniformBufferObject = std::make_unique< UniformBufferObject >(transferManager->device(), ViewUBOSize);
			m_infinityUniformBufferObject->setIdentifier("ViewMatrices2D-" + renderTarget.id() + "Infinity-UniformBufferObject");

			if ( !m_infinityUniformBufferObject->createOnHardware() )
			{
				Tracer::error(ClassId, "Unable to get an uniform buffer object for infinite view !");

				m_infinityUniformBufferObject.reset();

				return false;
			}

			m_infinityDescriptorSet = std::make_unique< DescriptorSet >(renderer->descriptorPool(), descriptorSetLayout);
			m_infinityDescriptorSet->setIdentifier("ViewMatrices2D-" + renderTarget.id() + "Infinity-DescriptorSet");

			if ( !m_infinityDescriptorSet->create() )
			{
				m_infinityDescriptorSet.reset();

				Tracer::error(ClassId, "Unable to create the infinity view descriptor set !");

				return false;
			}

			if ( !m_infinityDescriptorSet->writeUniformBufferObject(*m_infinityUniformBufferObject, 0) )
			{
				Tracer::error(ClassId, "Unable to setup the infinity view descriptor set !");

				return false;
			}
		}

		return true;
	}

	bool
	ViewMatrices2DUBO::updateVideoMemory (UpdateSet set) const noexcept
	{
		const std::lock_guard< std::mutex > lock{m_memoryAccess};

		if ( this->closeViewEnabled() && (set == UpdateSet::Both || set == UpdateSet::Regular) )
		{
#ifdef DEBUG
			if ( m_uniformBufferObject == nullptr )
			{
				Tracer::error(ClassId, "The view uniform buffer object is not initialized !");

				return false;
			}
#endif

			auto * pointer = m_uniformBufferObject->mapMemory< float >();

			if ( pointer == nullptr )
			{ 
				return false; 
			}

			size_t offset = 0;

			// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)

			std::memcpy(&pointer[offset], m_view.data(), MatrixAlignment * sizeof(float));
			offset += MatrixAlignment;

			std::memcpy(&pointer[offset], m_projection.data(), MatrixAlignment * sizeof(float));
			offset += MatrixAlignment;

			std::memcpy(&pointer[offset], m_viewProjection.data(), MatrixAlignment * sizeof(float));
			offset += MatrixAlignment;

			std::memcpy(&pointer[offset], m_position.data(), VectorAlignment * sizeof(float));
			offset += VectorAlignment;

			std::memcpy(&pointer[offset], m_velocity.data(), VectorAlignment * sizeof(float));
			offset += VectorAlignment;

			std::memcpy(&pointer[offset], m_viewProperties.data(), VectorAlignment * sizeof(float));
			//offset += VectorAlignment;

			// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)

			m_uniformBufferObject->unmapMemory();
		}

		if ( this->infinityViewEnabled() && (set == UpdateSet::Both || set == UpdateSet::Infinity) )
		{
#ifdef DEBUG
			if ( m_infinityUniformBufferObject == nullptr )
			{
				Tracer::error(ClassId, "The infinity view uniform buffer object is not initialized !");

				return false;
			}
#endif

			auto * pointer = m_infinityUniformBufferObject->mapMemory< float >();

			if ( pointer == nullptr )
			{
				return false;
			}

			size_t offset = 0;

			// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)

			std::memcpy(&pointer[offset], m_infinityView.data(), MatrixAlignment * sizeof(float));
			offset += MatrixAlignment;

			std::memcpy(&pointer[offset], m_projection.data(), MatrixAlignment * sizeof(float));
			offset += MatrixAlignment;

			std::memcpy(&pointer[offset], m_infinityViewProjection.data(), MatrixAlignment * sizeof(float));
			offset += MatrixAlignment;

			std::memcpy(&pointer[offset], m_position.data(), VectorAlignment * sizeof(float));
			offset += VectorAlignment;

			std::memcpy(&pointer[offset], m_velocity.data(), VectorAlignment * sizeof(float));
			offset += VectorAlignment;

			std::memcpy(&pointer[offset], m_viewProperties.data(), VectorAlignment * sizeof(float));
			//offset += VectorAlignment;

			// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)

			m_infinityUniformBufferObject->unmapMemory();
		}

		return true;
	}

	void
	ViewMatrices2DUBO::destroy () noexcept
	{
		const std::lock_guard< std::mutex > lock{m_memoryAccess};

		m_descriptorSet.reset();
		m_infinityDescriptorSet.reset();

		if ( m_uniformBufferObject != nullptr )
		{
			m_uniformBufferObject->destroyFromHardware();
			m_uniformBufferObject.reset();
		}

		if ( m_infinityUniformBufferObject != nullptr )
		{
			m_infinityUniformBufferObject->destroyFromHardware();
			m_infinityUniformBufferObject.reset();
		}
	}

	const Vulkan::UniformBufferObject *
	ViewMatrices2DUBO::viewUBO (size_t /*index*/) const noexcept
	{
		return m_uniformBufferObject.get();
	}

	const Vulkan::UniformBufferObject *
	ViewMatrices2DUBO::viewInfinityUBO (size_t /*index*/) const noexcept
	{
		return m_infinityUniformBufferObject.get();
	}

	const Vulkan::DescriptorSet *
	ViewMatrices2DUBO::descriptorSet (bool infinity) const noexcept
	{
		if ( infinity )
		{
			return m_infinityDescriptorSet.get();
		}

		return m_descriptorSet.get();
	}
}
