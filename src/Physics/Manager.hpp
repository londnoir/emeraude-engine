/*
 * Emeraude/Physics/Manager.hpp
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
#include <vector>
#include <map>
#include <array>
#include <memory>

/* Local inclusions for inheritances. */
#include "ServiceInterface.hpp"

/* Forward declarations. */
namespace Emeraude
{
	namespace Vulkan
	{
		class Instance;
		class Device;
		class DescriptorPool;
		class DescriptorSet;
		class DescriptorSetLayout;
		class CommandPool;
		class CommandBuffer;
		class PipelineLayout;
		class ComputePipeline;
	}

	class Arguments;
	class Settings;
}

namespace Emeraude::Physics
{
	/**
	 * @brief The physics manager service class.
	 * @extends Emeraude::ServiceInterface This is a service.
	 */
	class Manager final : public ServiceInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"PhysicsManagerService"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/* Settings keys */
			static constexpr auto AccelerationEnabledKey = "Physics/AccelerationEnabled";
			static constexpr auto DefaultAccelerationEnabled = false;

			/**
			 * @brief Constructs the physics manager.
			 * @param arguments A reference to Arguments.
			 * @param coreSettings A reference to the core settings.
			 * @param instance A reference to the Vulkan instance.
			 */
			Manager (const Arguments & arguments, Settings & coreSettings, Vulkan::Instance & instance) noexcept;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::ServiceInterface::usable() */
			[[nodiscard]]
			bool usable () const noexcept override;

			/**
			 * @brief Returns the selected logical device used for compute.
			 * @return const std::shared_ptr< Vulkan::Device > &
			 */
			[[nodiscard]]
			const std::shared_ptr< Vulkan::Device > & device () const noexcept;

			/**
			 * @brief Returns the descriptor pool.
			 * @return const std::shared_ptr< Vulkan::DescriptorPool > &
			 */
			[[nodiscard]]
			const std::shared_ptr< Vulkan::DescriptorPool > & descriptorPool () const noexcept;

			/**
			 * @brief Returns or creates a pipeline layout according to requirements.
			 * @param descriptorSetLayouts A reference to a list of descriptor set layout.
			 * @return std::shared_ptr< Vulkan::PipelineLayout >
			 */
			[[nodiscard]]
			std::shared_ptr< Vulkan::PipelineLayout > getPipelineLayout (const std::vector< std::shared_ptr< Vulkan::DescriptorSetLayout > > & descriptorSetLayouts) noexcept;

			/**
			 * @brief Returns or creates a graphics pipeline according to requirements.
			 * @param pipelineLayout A reference to as pipeline layout smart pointer.
			 * @return std::shared_ptr< Vulkan::ComputePipeline >
			 */
			[[nodiscard]]
			std::shared_ptr< Vulkan::ComputePipeline > getPipeline (const std::shared_ptr< Vulkan::PipelineLayout > & pipelineLayout) noexcept;

			/**
			 * @brief Returns whether the physics acceleration was enabled at startup.
			 * @return bool
			 */
			[[nodiscard]]
			bool isPhysicsAccelerationAvailable () noexcept;

		private:

			/** @copydoc Emeraude::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc Emeraude::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

			/**
			 * @brief Clears primary command buffers.
			 */
			void clearCommandBuffers () noexcept;

			/* Flag names. */
			static constexpr auto Usable = 0UL;
			static constexpr auto AccelerationAvailable = 1UL;

			// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members) NOTE: Services inter-connexions.
			const Arguments & m_arguments;
			Settings & m_coreSettings;
			Vulkan::Instance & m_vulkanInstance;
			// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members) NOTE: Services inter-connexions.
			std::shared_ptr< Vulkan::Device > m_device{};
			std::shared_ptr< Vulkan::DescriptorPool > m_descriptorPool{};
			std::map< size_t , std::shared_ptr< Vulkan::DescriptorSetLayout > > m_descriptorSetLayouts{};
			std::shared_ptr< Vulkan::CommandPool > m_commandPool{};
			std::vector< std::shared_ptr< Vulkan::CommandBuffer > > m_commandBuffers{};
			std::map< size_t, std::shared_ptr< Vulkan::PipelineLayout > > m_pipelineLayouts{};
			std::map< size_t, std::shared_ptr< Vulkan::ComputePipeline > > m_pipelines{};
			std::array< bool, 8 > m_flags{ // NOLINT(*-magic-numbers)
				false/*Usable*/,
				false/*AccelerationAvailable*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
