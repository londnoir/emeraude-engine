/*
 * Emeraude/Graphics/ViewMatricesInterface.hpp
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

/* C/C++ standard libraries. */
#include <array>

/* Local inclusions for usages. */
#include "Math/Vector.hpp"
#include "Math/Matrix.hpp"
#include "Math/Coordinates.hpp"
#include "Frustum.hpp"
#include "Types.hpp"

/* Forward declarations. */
namespace Emeraude
{
	namespace Graphics::RenderTarget
	{
		class Abstract;
	}

	namespace Vulkan
	{
		class UniformBufferObject;
		class DescriptorSet;
	}
}

namespace Emeraude::Graphics
{
	/** 
	 * @brief Defines an abstract way to describes a view with coordinates and matrices to use with Vulkan.
	 */
	class ViewMatricesInterface
	{
		public:

			enum class UpdateSet
			{
				Regular,
				Infinity,
				Both
			};

			/* View properties UBO layout :
			 * mat4: view matrix. (64 bytes)
			 * mat4: projection matrix. (64 bytes)
			 * mat4: (viewInfinity/view)Projection matrix. (64 bytes)
			 * vec4: world position. (16 bytes)
			 * vec4: velocity. (16 bytes)
			 * vec4: view information [width, height, near, far]. (16 bytes)
			 */
			static constexpr auto ViewUBOElementCount = (3 * Graphics::MatrixAlignment) + (3 * Graphics::VectorAlignment);
			static constexpr auto ViewUBOSize = ViewUBOElementCount * sizeof(float);

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			ViewMatricesInterface (const ViewMatricesInterface & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			ViewMatricesInterface (ViewMatricesInterface && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return ViewMatricesInterface &
			 */
			ViewMatricesInterface & operator= (const ViewMatricesInterface & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return ViewMatricesInterface &
			 */
			ViewMatricesInterface & operator= (ViewMatricesInterface && copy) noexcept = delete;
			
			/**
			 * @brief Destructs the view matrices interface.
			 */
			virtual ~ViewMatricesInterface () = default;
			
			/**
			 * @brief Returns the projection matrix.
			 * @return const Matrix< 4, float > &
			 */
			[[nodiscard]]
			virtual const Libraries::Math::Matrix< 4, float > & projectionMatrix () const noexcept = 0;

			/**
			 * @brief Returns the view matrix.
			 * @param index The index of the matrix for the cubemap view. Default 0.
			 * @return const Matrix< 4, float > &
			 */
			[[nodiscard]]
			virtual const Libraries::Math::Matrix< 4, float > & viewMatrix (size_t index) const noexcept = 0;

			/**
			 * @brief Returns the infinity view matrix.
			 * @param index The index of the matrix for the cubemap view. Default 0.
			 * @return const Matrix< 4, float > &
			 */
			[[nodiscard]]
			virtual const Libraries::Math::Matrix< 4, float > & infinityViewMatrix (size_t index) const noexcept = 0;

			/**
			 * @brief Returns the view projection matrix.
			 * @param index The index of the matrix for the cubemap view. Default 0.
			 * @return const Matrix< 4, float > &
			 */
			[[nodiscard]]
			virtual const Libraries::Math::Matrix< 4, float > & viewProjectionMatrix (size_t index) const noexcept = 0;

			/**
			 * @brief Returns the infinity view projection matrix.
			 * @param index The index of the matrix for the cubemap view. Default 0.
			 * @return const Matrix< 4, float > &
			 */
			[[nodiscard]]
			virtual const Libraries::Math::Matrix< 4, float > & infinityViewProjectionMatrix (size_t index) const noexcept = 0;

			/**
			 * @brief Returns the position of the point of view.
			 * @todo Should be the coordinates instead of the only position.
			 * @return const Vector< 3, float > &
			 */
			[[nodiscard]]
			virtual const Libraries::Math::Vector< 3, float > & position () const noexcept = 0;

			/**
			 * @brief Returns the velocity of the point of view.
			 * @return const Vector< 3, float > &
			 */
			[[nodiscard]]
			virtual const Libraries::Math::Vector< 3, float > & velocity () const noexcept = 0;

			/**
			 * @brief Returns the view properties
			 * @return const Vector< 4, float > &
			 */
			[[nodiscard]]
			virtual const Libraries::Math::Vector< 4, float > & viewProperties () const noexcept = 0;

			/**
			 * @brief Returns the const access to the frustum for object clipping.
			 * @param index The index of the frustum for the cubemap view. Default 0.
			 * @return Frustum
			 */
			[[nodiscard]]
			virtual const Frustum & frustum (size_t index) const noexcept = 0;

			/**
			 * @brief Returns the aspect ratio of the view.
			 * @return float
			 */
			[[nodiscard]]
			virtual float getAspectRatio () const noexcept = 0;

			/**
			 * @brief Returns the field of view of the perspective projection matrix.
			 * @return float
			 */
			[[nodiscard]]
			virtual float fieldOfView () const noexcept = 0;

			/**
			 * @brief Updates view properties with a perspective projection.
			 * @note This should be called when the viewport change.
			 * @param width The width of the viewport.
			 * @param height The height of the viewport.
			 * @param distance The maximal distance of the viewport for perspective calculation.
			 * @param fov The field of view in degrees.
			 * @return void
			 */
			virtual void updatePerspectiveViewProperties (float width, float height, float distance, float fov) noexcept = 0;

			/**
			 * @brief Updates view properties with an orthographic projection.
			 * @note This should be called when the viewport change.
			 * @param width The width of the viewport.
			 * @param height The height of the viewport.
			 * @param distance The maximal distance of the viewport for perspective calculation.
			 * @param near The minimal distance of the viewport for orthographic calculation.
			 * @return void
			 */
			virtual void updateOrthographicViewProperties (float width, float height, float distance, float near) noexcept = 0;

			/**
			 * @brief This should be called everytime the point of view moves.
			 * @param coordinates The absolute coordinates of the camera responsible for this view.
			 * @param velocity A vector representing a velocity applied to the camera for special effect.
			 * @return void
			 */
			virtual void updateViewCoordinates (const Libraries::Math::Coordinates< float > & coordinates, const Libraries::Math::Vector< 3, float > & velocity) noexcept = 0;

			/**
			 * @brief Creates buffer in the video memory.
			 * @param renderTarget A reference to a render target.
			 * @return bool
			 */
			virtual bool create (const RenderTarget::Abstract & renderTarget) noexcept = 0;

			/**
			 * @brief Updates the video memory.
			 * @param set Which set of matrices should we update. Default UpdateSet::Both.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool updateVideoMemory (UpdateSet set) const noexcept = 0;

			/**
			 * @brief Destroys buffer in the video memory.
			 * @return void
			 */
			virtual void destroy () noexcept = 0;

			/**
			 * @brief Returns the raw pointer on the view uniform buffer object.
			 * @return const Vulkan::UniformBufferObject *
			 */
			[[nodiscard]]
			virtual const Vulkan::UniformBufferObject * viewUBO (size_t index) const noexcept = 0;

			/**
			 * @brief Returns the raw pointer on the view infinity uniform buffer object.
			 * @return const Vulkan::UniformBufferObject *
			 */
			[[nodiscard]]
			virtual const Vulkan::UniformBufferObject * viewInfinityUBO (size_t index) const noexcept = 0;

			/**
			 * @brief Returns the view descriptor set.
			 * @param bool infinity Set for the infinite view.
			 * @return const Vulkan::DescriptorSet *
			 */
			[[nodiscard]]
			virtual const Vulkan::DescriptorSet * descriptorSet (bool infinity) const noexcept = 0;

		protected:

			/**
			 * @brief Constructs a view matrices interface.
			 * @param enableCloseView Enable the matrices for close view.
			 * @param enableInfinityView Enable the matrices for infinity view.
			 */
			ViewMatricesInterface (bool enableCloseView, bool enableInfinityView) noexcept;

			/**
			 * @return Returns whether the close view is enabled.
			 * @return bool
			 */
			[[nodiscard]]
			bool closeViewEnabled () const noexcept;

			/**
			 * @return Returns whether the infinity view is enabled.
			 * @return bool
			 */
			[[nodiscard]]
			bool infinityViewEnabled () const noexcept;

		private:

			/* Flag names. */
			static constexpr auto EnableCloseView = 0UL;
			static constexpr auto EnableInfinityView = 1UL;
			
			std::array< bool, 8 > m_flags{ // NOLINT(*-magic-numbers)
				true/*EnableCloseView*/,
				true/*EnableInfinityView*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
