/*
 * Emeraude/Graphics/ViewMatrices3DUBO.hpp
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
#include <memory>
#include <mutex>

/* Local inclusions for inheritances. */
#include "ViewMatricesInterface.hpp"

/* Local inclusions for usages. */
#include "Vulkan/UniformBufferObject.hpp"
#include "Vulkan/DescriptorSet.hpp"

namespace Emeraude::Graphics
{
	/**
	 * @brief Specialization of view matrices for cubemap rendering.
	 * @extends Emeraude::Graphics::ViewMatricesInterface
	 */
	class ViewMatrices3DUBO final : public ViewMatricesInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"ViewMatrices3DUBO"};

			/**
			 * @brief Creates 3D view matrices.
			 * @param enableCloseView Enable the matrices for close view. Default true.
			 * @param enableInfinityView Enable the matrices for infinity view. Default true.
			 */
			explicit ViewMatrices3DUBO (bool enableCloseView = true, bool enableInfinityView = true) noexcept;

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::projectionMatrix() */
			[[nodiscard]]
			const Libraries::Math::Matrix< 4, float > & projectionMatrix () const noexcept override;

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::viewMatrix() */
			[[nodiscard]]
			const Libraries::Math::Matrix< 4, float > & viewMatrix (size_t index = 0) const noexcept override;

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::infinityViewMatrix() */
			[[nodiscard]]
			const Libraries::Math::Matrix< 4, float > & infinityViewMatrix (size_t index = 0) const noexcept override;

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::viewProjectionMatrix() */
			[[nodiscard]]
			const Libraries::Math::Matrix< 4, float > & viewProjectionMatrix (size_t index = 0) const noexcept override;

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::infinityViewProjectionMatrix() */
			[[nodiscard]]
			const Libraries::Math::Matrix< 4, float > & infinityViewProjectionMatrix (size_t index = 0) const noexcept override;

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::position() */
			[[nodiscard]]
			const Libraries::Math::Vector< 3, float > & position () const noexcept override;

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::velocity() */
			[[nodiscard]]
			const Libraries::Math::Vector< 3, float > & velocity () const noexcept override;

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::viewProperties() */
			[[nodiscard]]
			const Libraries::Math::Vector< 4, float > & viewProperties () const noexcept override;

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::frustum() */
			[[nodiscard]]
			const Frustum & frustum (size_t index = 0UL) const noexcept override;

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::getAspectRatio() */
			[[nodiscard]]
			float getAspectRatio () const noexcept override;

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::fieldOfView() */
			[[nodiscard]]
			float fieldOfView () const noexcept override;

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::updatePerspectiveViewProperties() */
			void updatePerspectiveViewProperties (float width, float height, float distance, float /*fov*/) noexcept override;

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::updateOrthographicViewProperties() */
			void updateOrthographicViewProperties (float width, float height, float distance, float near = 0.0F) noexcept override;

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::updateViewCoordinates() */
			void updateViewCoordinates (const Libraries::Math::Coordinates< float > & coordinates, const Libraries::Math::Vector< 3, float > & velocity) noexcept override;

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::create() */
			bool create (const RenderTarget::Abstract & renderTarget) noexcept override;

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::updateVideoMemoryForRendering() */
			bool updateVideoMemory (UpdateSet set = UpdateSet::Both) const noexcept override;

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::destroy() */
			void destroy () noexcept override;

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::viewUBO() */
			[[nodiscard]]
			const Vulkan::UniformBufferObject * viewUBO (size_t index = 0) const noexcept override;

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::viewInfinityUBO() */
			[[nodiscard]]
			const Vulkan::UniformBufferObject * viewInfinityUBO (size_t index = 0) const noexcept override;

			/** @copydoc Emeraude::Graphics::ViewMatricesInterface::descriptorSet() */
			[[nodiscard]]
			const Vulkan::DescriptorSet * descriptorSet (bool infinity) const noexcept override;

		private:

			static const std::array< Libraries::Math::Matrix< 4, float >, Graphics::CubemapFaceIndexes.size() > CubemapOrientation;
			static const std::array< Libraries::Math::Matrix< 4, float >, Graphics::CubemapFaceIndexes.size() > ShadowCubemapOrientation;

			Libraries::Math::Matrix< 4, float > m_projection{};
			std::array< Libraries::Math::Matrix< 4, float >, Graphics::CubemapFaceIndexes.size() > m_views{};
			std::array< Libraries::Math::Matrix< 4, float >, Graphics::CubemapFaceIndexes.size() > m_infinityViews{};
			std::array< Libraries::Math::Matrix< 4, float >, Graphics::CubemapFaceIndexes.size() > m_viewProjections{};
			std::array< Libraries::Math::Matrix< 4, float >, Graphics::CubemapFaceIndexes.size() > m_infinityViewProjections{};
			Libraries::Math::Vector< 3, float > m_position{};
			Libraries::Math::Vector< 3, float > m_velocity{};
			Libraries::Math::Vector< 4, float > m_viewProperties{};
			std::array< Frustum, Graphics::CubemapFaceIndexes.size() > m_frustums{};
			/* FIXME: Should be a single UBO. */
			std::array< std::unique_ptr< Vulkan::UniformBufferObject >, Graphics::CubemapFaceIndexes.size() > m_viewUBOs{};
			std::unique_ptr< Vulkan::DescriptorSet > m_descriptorSet{};
			/* FIXME: Should be a single UBO. */
			std::array< std::unique_ptr< Vulkan::UniformBufferObject >, Graphics::CubemapFaceIndexes.size() > m_viewInfinityUBOs{};
			std::unique_ptr< Vulkan::DescriptorSet > m_infinityDescriptorSet{};
			mutable std::mutex m_GPUAccessMutex{};
	};
}
