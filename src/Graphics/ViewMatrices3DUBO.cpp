/*
 * Emeraude/Graphics/ViewMatrices3DUBO.cpp
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

#include "ViewMatrices3DUBO.hpp"

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
	// NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index)

	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Vulkan;

	ViewMatrices3DUBO::ViewMatrices3DUBO (bool enableCloseView, bool enableInfinityView) noexcept
		: ViewMatricesInterface(enableCloseView, enableInfinityView)
	{

	}

	const std::array< Matrix< 4, float >, Graphics::CubemapFaceIndexes.size() > ViewMatrices3DUBO::CubemapOrientation = {
		Matrix< 4, float >::lookAt(Vector< 3, float >{0.0F, 0.0F, 0.0F}, Vector< 3, float >{ 1.0F,  0.0F,  0.0F}, Vector< 3, float >{ 0.0F, -1.0F,  0.0F}), // X+
		Matrix< 4, float >::lookAt(Vector< 3, float >{0.0F, 0.0F, 0.0F}, Vector< 3, float >{-1.0F,  0.0F,  0.0F}, Vector< 3, float >{ 0.0F, -1.0F,  0.0F}), // X-
		Matrix< 4, float >::lookAt(Vector< 3, float >{0.0F, 0.0F, 0.0F}, Vector< 3, float >{ 0.0F, -1.0F,  0.0F}, Vector< 3, float >{ 0.0F,  0.0F, -1.0F}), // Y+
		Matrix< 4, float >::lookAt(Vector< 3, float >{0.0F, 0.0F, 0.0F}, Vector< 3, float >{ 0.0F,  1.0F,  0.0F}, Vector< 3, float >{ 0.0F,  0.0F,  1.0F}), // Y-
		Matrix< 4, float >::lookAt(Vector< 3, float >{0.0F, 0.0F, 0.0F}, Vector< 3, float >{ 0.0F,  0.0F,  1.0F}, Vector< 3, float >{ 0.0F, -1.0F,  0.0F}), // Z+
		Matrix< 4, float >::lookAt(Vector< 3, float >{0.0F, 0.0F, 0.0F}, Vector< 3, float >{ 0.0F,  0.0F, -1.0F}, Vector< 3, float >{ 0.0F, -1.0F,  0.0F}) // Z-
	};

	const std::array< Matrix< 4, float >, Graphics::CubemapFaceIndexes.size() > ViewMatrices3DUBO::ShadowCubemapOrientation = {
		Matrix< 4, float >::lookAt(Vector< 3, float >{0.0F, 0.0F, 0.0F}, Vector< 3, float >{-1.0F,  0.0F,  0.0F}, Vector< 3, float >{ 0.0F,  1.0F,  0.0F}), // X+
		Matrix< 4, float >::lookAt(Vector< 3, float >{0.0F, 0.0F, 0.0F}, Vector< 3, float >{ 1.0F,  0.0F,  0.0F}, Vector< 3, float >{ 0.0F,  1.0F,  0.0F}), // X-
		Matrix< 4, float >::lookAt(Vector< 3, float >{0.0F, 0.0F, 0.0F}, Vector< 3, float >{ 0.0F,  1.0F,  0.0F}, Vector< 3, float >{ 0.0F,  0.0F,  1.0F}), // Y+
		Matrix< 4, float >::lookAt(Vector< 3, float >{0.0F, 0.0F, 0.0F}, Vector< 3, float >{ 0.0F, -1.0F,  0.0F}, Vector< 3, float >{ 0.0F,  0.0F, -1.0F}), // Y-
		Matrix< 4, float >::lookAt(Vector< 3, float >{0.0F, 0.0F, 0.0F}, Vector< 3, float >{ 0.0F,  0.0F, -1.0F}, Vector< 3, float >{ 0.0F,  1.0F,  0.0F}), // Z+
		Matrix< 4, float >::lookAt(Vector< 3, float >{0.0F, 0.0F, 0.0F}, Vector< 3, float >{ 0.0F,  0.0F,  1.0F}, Vector< 3, float >{ 0.0F,  1.0F,  0.0F}) // Z-
	};

	const Matrix< 4, float > &
	ViewMatrices3DUBO::projectionMatrix () const noexcept
	{
		return m_projection;
	}

	const Matrix< 4, float > &
	ViewMatrices3DUBO::viewMatrix (size_t index) const noexcept
	{
		if ( index >= CubemapFaceIndexes.size() )
		{
			Tracer::error(ClassId, "Index overflow !");

			index = 0;
		}

		return m_views[index];
	}

	const Matrix< 4, float > &
	ViewMatrices3DUBO::infinityViewMatrix (size_t index) const noexcept
	{
		if ( index >= CubemapFaceIndexes.size() )
		{
			Tracer::error(ClassId, "Index overflow !");

			index = 0;
		}

		return m_infinityViews[index];
	}

	const Matrix< 4, float > &
	ViewMatrices3DUBO::viewProjectionMatrix (size_t index) const noexcept
	{
		if ( index >= CubemapFaceIndexes.size() )
		{
			Tracer::error(ClassId, "Index overflow !");

			index = 0;
		}

		return m_viewProjections[index];
	}

	const Matrix< 4, float > &
	ViewMatrices3DUBO::infinityViewProjectionMatrix (size_t index) const noexcept
	{
		if ( index >= CubemapFaceIndexes.size() )
		{
			Tracer::error(ClassId, "Index overflow !");

			index = 0;
		}

		return m_infinityViewProjections[index];
	}

	const Vector< 3, float > &
	ViewMatrices3DUBO::position () const noexcept
	{
		return m_position;
	}

	const Vector< 3, float > &
	ViewMatrices3DUBO::velocity () const noexcept
	{
		return m_velocity;
	}

	const Vector< 4, float > &
	ViewMatrices3DUBO::viewProperties () const noexcept
	{
		return m_viewProperties;
	}

	const Frustum &
	ViewMatrices3DUBO::frustum (size_t index) const noexcept
	{
		if ( index >= CubemapFaceIndexes.size() )
		{
			Tracer::error(ClassId, "Index overflow !");

			index = 0;
		}

		return m_frustums[index];
	}

	float
	ViewMatrices3DUBO::getAspectRatio () const noexcept
	{
		return 1.0F;
	}

	float
	ViewMatrices3DUBO::fieldOfView () const noexcept
	{
		const auto Rad2Deg = 180.0F / Pi< float >;

		return std::atan(1.0F / m_projection[M4x4Col1Row1]) * 2.0F * Rad2Deg; // NOLINT(*-magic-numbers)
	}

	void
	ViewMatrices3DUBO::updatePerspectiveViewProperties (float width, float height, float distance, float /*fov*/) noexcept
	{
		Tracer::info(ClassId, Blob() << "Updating perspective view matrices with " << width << "X" << height << ", distance: " << distance << " ...");

		m_viewProperties[X] = width;
		m_viewProperties[Y] = height;
		m_viewProperties[W] = distance;

		const auto powA = std::pow(std::tan(Radian(90.0F) * 0.5F), 2.0F);
		m_viewProperties[Z] = 0.1F / std::sqrt(1.0F + powA * 2.0F); // NOLINT(*-magic-numbers)

		m_projection = Matrix< 4, float >::perspectiveProjection(90.0F, 1.0F, m_viewProperties[Z], m_viewProperties[W]); // NOLINT(*-magic-numbers)

		this->updateVideoMemory();
	}

	void
	ViewMatrices3DUBO::updateOrthographicViewProperties (float width, float height, float distance, float near) noexcept
	{
		Tracer::info(ClassId, Blob() << "Updating orthographic view matrices with " << width << "X" << height << ", distance: " << distance << " and near: " << near << " ...");

		m_viewProperties[X] = width;
		m_viewProperties[Y] = height;
		m_viewProperties[Z] = near;
		m_viewProperties[W] = distance;

		const auto side = m_viewProperties[W] * this->getAspectRatio();

		m_projection = Matrix< 4, float >::orthographicProjection(-side, side, -m_viewProperties[W], m_viewProperties[W], m_viewProperties[Z], m_viewProperties[W]);

		this->updateVideoMemory();
	}

	void
	ViewMatrices3DUBO::updateViewCoordinates (const Coordinates< float > & coordinates, const Vector< 3, float > & velocity) noexcept
	{
		/* Sets the camera world position and velocity. */
		m_position = coordinates.position();
		m_velocity = velocity;

		for ( auto face : CubemapFaceIndexes )
		{
			const auto faceIndex = static_cast< size_t >(face);

			/* Use the camera position as the point of view. */
			if ( this->closeViewEnabled() )
			{
				m_views[faceIndex] = CubemapOrientation[faceIndex] * Matrix< 4, float >::translation(-m_position);
				m_viewProjections[faceIndex] = m_projection * m_views[faceIndex];

				/* Updates the view frustum. */
				m_frustums[faceIndex].update(m_viewProjections[faceIndex]);
			}

			/* Same but update matrices for far objects. */
			if ( this->infinityViewEnabled() )
			{
				m_infinityViews[faceIndex] = CubemapOrientation[faceIndex] * Matrix< 4, float >::translation(-m_position);
				m_infinityViewProjections[faceIndex] = m_projection * m_infinityViews[faceIndex];
			}
		}

		this->updateVideoMemory();
	}

	bool
	ViewMatrices3DUBO::create (const RenderTarget::Abstract & renderTarget) noexcept
	{
		const std::lock_guard< std::mutex > lock{m_GPUAccessMutex};

		auto * renderer = Graphics::Renderer::instance();

		auto * transferManager = TransferManager::instance(TransferType::Graphics);

		auto descriptorSetLayout = renderer->getViewDescriptorSetLayout(renderTarget);

		/* Prepare the close view UBO and descriptor set. */
		if ( this->closeViewEnabled() )
		{
			for ( auto face : CubemapFaceIndexes )
			{
				const auto faceIndex = static_cast< size_t >(face);

				m_viewUBOs[faceIndex] = std::make_unique< UniformBufferObject >(transferManager->device(), ViewUBOSize);
				m_viewUBOs[faceIndex]->setIdentifier((std::stringstream{} << "ViewMatrices3D-" << renderTarget.id() << "#" << faceIndex << "-UniformBufferObject").str());

				if ( !m_viewUBOs[faceIndex]->createOnHardware() )
				{
					TraceError{ClassId} << "Unable to get an uniform buffer object for face #" << faceIndex << " of the close view !";

					m_viewUBOs[faceIndex].reset();

					return false;
				}
			}

			m_descriptorSet = std::make_unique< DescriptorSet >(renderer->descriptorPool(), descriptorSetLayout);
			m_descriptorSet->setIdentifier("ViewMatrices3D-" + renderTarget.id() + "-DescriptorSet");

			if ( !m_descriptorSet->create() )
			{
				m_descriptorSet.reset();

				Tracer::error(ClassId, "Unable to create the close view descriptor set !");

				return false;
			}

			if ( !m_descriptorSet->writeUniformBufferObject(*m_viewUBOs[0], 0) )
			{
				Tracer::error(ClassId, "Unable to setup the close view descriptor set !");

				return false;
			}
		}

		/* Prepare the infinite view UBO and descriptor set. */
		if ( this->infinityViewEnabled() )
		{
			for ( auto face : CubemapFaceIndexes )
			{
				const auto faceIndex = static_cast< size_t >(face);

				m_viewInfinityUBOs[faceIndex] = std::make_unique< UniformBufferObject >(transferManager->device(), ViewUBOSize);
				m_viewInfinityUBOs[faceIndex]->setIdentifier((std::stringstream{} << "ViewMatrices3D-" << renderTarget.id() << "Infinity#" << faceIndex << "-UniformBufferObject").str());

				if ( !m_viewInfinityUBOs[faceIndex]->createOnHardware() )
				{
					TraceError{ClassId} << "Unable to get an uniform buffer object for face #" << faceIndex << " of the close view !";

					m_viewInfinityUBOs[faceIndex].reset();

					return false;
				}
			}

			m_infinityDescriptorSet = std::make_unique< DescriptorSet >(renderer->descriptorPool(), descriptorSetLayout);
			m_infinityDescriptorSet->setIdentifier("ViewMatrices3D-" + renderTarget.id() + "Infinity-DescriptorSet");

			if ( !m_infinityDescriptorSet->create() )
			{
				m_infinityDescriptorSet.reset();

				Tracer::error(ClassId, "Unable to create the infinity view descriptor set !");

				return false;
			}

			if ( !m_infinityDescriptorSet->writeUniformBufferObject(*m_viewInfinityUBOs[0], 0) )
			{
				Tracer::error(ClassId, "Unable to setup the infinity view descriptor set !");

				return false;
			}
		}

		return true;
	}

	bool
	ViewMatrices3DUBO::updateVideoMemory (UpdateSet set) const noexcept
	{
		const std::lock_guard< std::mutex > lock{m_GPUAccessMutex};

		for ( auto face : CubemapFaceIndexes )
		{
			const auto faceIndex = static_cast< size_t >(face);

			if ( this->closeViewEnabled() && (set == UpdateSet::Both || set == UpdateSet::Regular) )
			{
#ifdef DEBUG
				if ( m_viewUBOs[faceIndex] == nullptr )
				{
					Tracer::error(ClassId, "The uniform buffer object is uninitialized !");

					return false;
				}
#endif

				auto * pointer = m_viewUBOs[faceIndex]->mapMemory< float >();

				if ( pointer == nullptr )
				{
					return false;
				}

				size_t offset = 0;

				// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)

				std::memcpy(&pointer[offset], m_views[faceIndex].data(), MatrixAlignment * sizeof(float));
				offset += MatrixAlignment;

				std::memcpy(&pointer[offset], m_projection.data(), MatrixAlignment * sizeof(float));
				offset += MatrixAlignment;

				std::memcpy(&pointer[offset], m_viewProjections[faceIndex].data(), MatrixAlignment * sizeof(float));
				offset += MatrixAlignment;

				std::memcpy(&pointer[offset], m_position.data(), VectorAlignment * sizeof(float));
				offset += VectorAlignment;

				std::memcpy(&pointer[offset], m_velocity.data(), VectorAlignment * sizeof(float));
				offset += VectorAlignment;

				std::memcpy(&pointer[offset], m_viewProperties.data(), VectorAlignment * sizeof(float));
				//offset += VectorAlignment;

				// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)

				m_viewUBOs[faceIndex]->unmapMemory();
			}

			if ( this->infinityViewEnabled() && (set == UpdateSet::Both || set == UpdateSet::Infinity) )
			{
#ifdef DEBUG
				if ( m_viewInfinityUBOs[faceIndex] == nullptr )
				{
					Tracer::error(ClassId, "The uniform buffer object is uninitialized !");

					return false;
				}
#endif

				auto * pointer = m_viewInfinityUBOs[faceIndex]->mapMemory< float >();

				if ( pointer == nullptr )
				{
					return false;
				}

				size_t offset = 0;

				// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)

				std::memcpy(&pointer[offset], m_infinityViews[faceIndex].data(), MatrixAlignment * sizeof(float));
				offset += MatrixAlignment;

				std::memcpy(&pointer[offset], m_projection.data(), MatrixAlignment * sizeof(float));
				offset += MatrixAlignment;

				std::memcpy(&pointer[offset], m_infinityViewProjections[faceIndex].data(), MatrixAlignment * sizeof(float));
				offset += MatrixAlignment;

				std::memcpy(&pointer[offset], m_position.data(), VectorAlignment * sizeof(float));
				offset += VectorAlignment;

				std::memcpy(&pointer[offset], m_velocity.data(), VectorAlignment * sizeof(float));
				offset += VectorAlignment;

				std::memcpy(&pointer[offset], m_viewProperties.data(), VectorAlignment * sizeof(float));
				//offset += VectorAlignment;

				// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)

				m_viewInfinityUBOs[faceIndex]->unmapMemory();
			}
		}

		return true;
	}

	void
	ViewMatrices3DUBO::destroy () noexcept
	{
		const std::lock_guard< std::mutex > lock{m_GPUAccessMutex};

		m_descriptorSet.reset();
		m_infinityDescriptorSet.reset();

		for ( auto face : CubemapFaceIndexes )
		{
			const auto faceIndex = static_cast< size_t >(face);

			if ( m_viewUBOs[faceIndex] != nullptr )
			{
				m_viewUBOs[faceIndex]->destroyFromHardware();
				m_viewUBOs[faceIndex].reset();
			}

			if ( m_viewInfinityUBOs[faceIndex] != nullptr )
			{
				m_viewInfinityUBOs[faceIndex]->destroyFromHardware();
				m_viewInfinityUBOs[faceIndex].reset();
			}
		}
	}

	const Vulkan::UniformBufferObject *
	ViewMatrices3DUBO::viewUBO (size_t index) const noexcept
	{
		return m_viewUBOs[index].get();
	}

	const Vulkan::UniformBufferObject *
	ViewMatrices3DUBO::viewInfinityUBO (size_t index) const noexcept
	{
		return m_viewInfinityUBOs[index].get();
	}

	const Vulkan::DescriptorSet *
	ViewMatrices3DUBO::descriptorSet (bool infinity) const noexcept
	{
		if ( infinity )
		{
			return m_infinityDescriptorSet.get();
		}

		return m_descriptorSet.get();
	}
	// NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index)
}
