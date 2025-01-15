/*
 * src/Graphics/ViewMatrices2DUBO.hpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2024 - "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emeraude-Engine; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Complete project and additional information can be found at :
 * https://bitbucket.org/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#pragma once

/* STL inclusions. */
#include <cstddef>
#include <array>
#include <memory>
#include <mutex>

/* Local inclusions for inheritances. */
#include "ViewMatricesInterface.hpp"

/* Local inclusions for usages. */
#include "Vulkan/UniformBufferObject.hpp"
#include "Tracer.hpp"

namespace Emeraude::Graphics
{
	/**
	 * @brief Specialization of view matrices for 2D surface rendering.
	 * @extends Emeraude::Graphics::ViewMatricesInterface
	 */
	class ViewMatrices2DUBO final : public ViewMatricesInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"ViewMatrices2DUBO"};

			/**
			 * @brief Creates 2D view matrices.
			 */
			ViewMatrices2DUBO () noexcept = default;

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::projectionMatrix() */
			[[nodiscard]]
			const Libraries::Math::Matrix< 4, float > &
			projectionMatrix () const noexcept override
			{
				return m_projection;
			}

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::viewMatrix() */
			[[nodiscard]]
			const Libraries::Math::Matrix< 4, float > &
			viewMatrix (bool infinity, size_t /*index*/) const noexcept override
			{
				return infinity ? m_infinityView : m_view;
			}

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::position() */
			[[nodiscard]]
			const Libraries::Math::Vector< 3, float > &
			position () const noexcept override
			{
				return m_position;
			}

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::frustum() */
			[[nodiscard]]
			const Frustum &
			frustum (size_t /*index*/) const noexcept override
			{
				return m_frustum;
			}

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::getAspectRatio() */
			[[nodiscard]]
			float
			getAspectRatio () const noexcept override
			{
				if ( m_bufferData[ViewWidthOffset] * m_bufferData[ViewHeightOffset] <= 0.0F )
				{
					Tracer::error(ClassId, "View properties for width and height are invalid ! Unable to compute the aspect ratio.");

					return 1.0F;
				}

				return m_bufferData[ViewWidthOffset] / m_bufferData[ViewHeightOffset];
			}

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::fieldOfView() */
			[[nodiscard]]
			float
			fieldOfView () const noexcept override
			{
				using namespace Libraries::Math;

				constexpr auto Rad2Deg = HalfRevolution< float > / Pi< float >;

				return std::atan(1.0F / m_projection[M4x4Col1Row1]) * 2.0F * Rad2Deg;
			}

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::updatePerspectiveViewProperties() */
			void updatePerspectiveViewProperties (float width, float height, float distance, float fov) noexcept override;

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::updateOrthographicViewProperties() */
			void updateOrthographicViewProperties (float width, float height, float distance, float near) noexcept override;

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::updateViewCoordinates() */
			void updateViewCoordinates (const Libraries::Math::CartesianFrame< float > & coordinates, const Libraries::Math::Vector< 3, float > & velocity) noexcept override;

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::updateAmbientLightProperties() */
			void updateAmbientLightProperties (const Libraries::PixelFactory::Color< float > & color, float intensity) noexcept override;

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::create() */
			bool create (Renderer & renderer, const std::string & instanceID) noexcept override;

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::updateVideoMemory() */
			bool updateVideoMemory () const noexcept override;

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::destroy() */
			void
			destroy () noexcept override
			{
				/* NOTE: Lock between updateVideoMemory() and destroy(). */
				const std::lock_guard< std::mutex > lockGuard{m_GPUBufferAccessLock};

				m_descriptorSet.reset();
				m_uniformBufferObject.reset();
			}

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::descriptorSet() */
			[[nodiscard]]
			const Vulkan::DescriptorSet *
			descriptorSet () const noexcept override
			{
				return m_descriptorSet.get();
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const ViewMatrices2DUBO & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend std::string to_string (const ViewMatrices2DUBO & obj) noexcept;

		private:

			static constexpr auto ViewUBOElementCount = Matrix4Alignment + (5 * VectorAlignment);
			static constexpr auto ViewUBOSize = ViewUBOElementCount * sizeof(float);

			static constexpr auto ProjectionMatrixOffset{0UL};
			static constexpr auto WorldPositionOffset{16UL};
			static constexpr auto VelocityVectorOffset{20UL};
			static constexpr auto ViewPropertiesOffset{24UL};
			static constexpr auto ViewWidthOffset{24UL};
			static constexpr auto ViewHeightOffset{25UL};
			static constexpr auto ViewNearOffset{26UL};
			static constexpr auto ViewDistanceOffset{27UL};
			static constexpr auto AmbientLightColorOffset{28UL};
			static constexpr auto AmbientLightIntensityOffset{32UL};

			Libraries::Math::Matrix< 4, float > m_projection;
			Libraries::Math::Matrix< 4, float > m_view;
			Libraries::Math::Matrix< 4, float > m_infinityView;
			Libraries::Math::Vector< 3, float > m_position;
			Frustum m_frustum;
			std::array< float, ViewUBOElementCount > m_bufferData{
				/* Projection matrix. */
				1.0F, 0.0F, 0.0F, 0.0F,
				0.0F, 1.0F, 0.0F, 0.0F,
				0.0F, 0.0F, 1.0F, 0.0F,
				0.0F, 0.0F, 0.0F, 1.0F,
				/* World position. */
				0.0F, 0.0F, 0.0F, 1.0F,
				/* Velocity vector. */
				0.0F, 0.0F, 0.0F, 0.0F,
				/* View properties. */
				1.0F, 1.0F, 1.0F, 1.0F,
				/* Light ambient color. */
				0.0F, 0.0F, 0.0F, 1.0F,
				/* Light ambient intensity. */
				0.0F, 0.0F, 0.0F, 0.0F
			};
			std::unique_ptr< Vulkan::UniformBufferObject > m_uniformBufferObject;
			std::unique_ptr< Vulkan::DescriptorSet > m_descriptorSet;
			mutable std::mutex m_GPUBufferAccessLock;
	};
}
