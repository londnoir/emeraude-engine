/*
 * Emeraude/Vulkan/Device.cpp
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

#include "Device.hpp"

/* Local inclusions. */
#include "QueueFamily.hpp"
#include "QueueFamilySQ.hpp"
#include "Settings.hpp"
#include "Tracer.hpp"
#include "Utility.hpp"

namespace Emeraude::Vulkan
{
	using namespace Libraries;
	using namespace Graphics;

	Device::Device (const std::shared_ptr< PhysicalDevice > & physicalDevice) noexcept
		: NamedItem(physicalDevice->properties().deviceName), m_physicalDevice(physicalDevice)
	{
		m_flags[DebugMode] = Settings::instance(SettingsType::Core)->getAs< bool >(EnableDeviceDebugKey, BOOLEAN_FOLLOWING_DEBUG);
	}

	Device::~Device ()
	{
		this->destroy();
	}

	bool
	Device::create (const DeviceRequirements & requirements, const std::vector< const char * > & extensions) noexcept
	{
		if ( Settings::instance(SettingsType::Core)->getAs< bool >(ShowAvailableDeviceExtensionsKey, BOOLEAN_FOLLOWING_DEBUG) )
		{
			printItemList("Device", m_physicalDevice->getExtensions(nullptr));
		}

		/* Queue creation definitions. */
		std::vector< VkDeviceQueueCreateInfo > queueCreateInfos{};

		/* Check queues availabilities and possibilities against requirements. */
		if ( !this->prepareQueues(requirements, queueCreateInfos) )
		{
			Tracer::error(ClassId, "Unable to have a suitable queue configuration for the device !");

			return false;
		}

		if ( m_flags[DebugMode] )
		{
			TraceInfo info{ClassId};

			info << "Device configuration : " "\n";

			for ( const auto & queueFamily : m_queueFamilies )
			{
				info << "Queue family #" << queueFamily->index() << " enabled !" "\n";
			}

			for ( const auto & pair : m_queueFamilyPerJob )
			{
				info << "'" << to_cstring(pair.first) << "' job will be performed on queue family #" << pair.second->index() << "." "\n";
			}
		}

		/* Logical device creation. */
		if ( !this->createDevice(requirements, queueCreateInfos, extensions) )
		{
			Tracer::error(ClassId, "Logical device creation failed !");

			return false;
		}

		/* Retrieve every created queues. */
		auto device = this->shared_from_this();

		for ( auto & queueFamily : m_queueFamilies )
		{
			if ( !queueFamily->retrieveQueuesFromDevice(device) )
			{
				TraceError{ClassId} <<
					"Unable to retrieve queue for queue family #" << queueFamily->index() << " of "
					"the device " << m_handle << " (" << this->identifier() << ") is successfully created !";

				return false;
			}
		}

		TraceSuccess{ClassId} << "The device " << m_handle << " (" << this->identifier() << ") is successfully created !";

		this->setCreated();

		return true;
	}

	void
	Device::destroy () noexcept
	{
		if ( m_handle == VK_NULL_HANDLE )
		{
			return;
		}

		this->waitIdle();

		m_queueFamilyPerJob.clear();
		m_queueFamilies.clear();

		vkDestroyDevice(m_handle, nullptr);

		TraceSuccess{ClassId} << "The device " << m_handle << " is gracefully destroyed !";

		m_handle = VK_NULL_HANDLE;

		m_physicalDevice.reset();

		this->setDestroyed();
	}

	bool
	Device::declareQueuesFromSingleQueueFamily (const DeviceRequirements & requirements, const VkQueueFamilyProperties & queueFamilyProperty) noexcept
	{
		auto queueFamily = queueFamilyProperty.queueCount > 1 ?
			m_queueFamilies.emplace_back(std::make_shared< QueueFamily >(0, queueFamilyProperty.queueCount)) :
			m_queueFamilies.emplace_back(std::make_shared< QueueFamilySQ >(0));

		m_flags[HasBasicSupport] = true;

		/* NOTE: Without transfer nothing is possible ! This should never happen ! */
		if ( (queueFamilyProperty.queueFlags & VK_QUEUE_TRANSFER_BIT) == 0 )
		{
			TraceFatal{ClassId} << "The physical device '" << this->name() << "' has no queue for transfer !";

			return false;
		}

		m_queueFamilyPerJob[QueueJob::Transfer] = queueFamily;

		if ( requirements.needsGraphics() )
		{
			if ( (queueFamilyProperty.queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0 )
			{
				TraceError{ClassId} << "The physical device '" << this->name() << "' has no queue for graphics !";

				return false;
			}

			m_queueFamilyPerJob[QueueJob::Graphics] = queueFamily;
			m_queueFamilyPerJob[QueueJob::GraphicsTransfer] = queueFamily;

			if ( requirements.needsPresentation() )
			{
				if ( !m_physicalDevice->getSurfaceSupport(requirements.surface(), 0) )
				{
					TraceFatal{ClassId} << "The physical device '" << this->name() << "' has no queue for presentation !";

					return false;
				}

				m_queueFamilyPerJob[QueueJob::Presentation] = queueFamily;
			}
		}

		if ( requirements.needsCompute() )
		{
			if ( (queueFamilyProperty.queueFlags & VK_QUEUE_COMPUTE_BIT) == 0 )
			{
				TraceError{ClassId} << "The physical device '" << this->name() << "' has no queue for compute !";

				return false;
			}

			m_queueFamilyPerJob[QueueJob::Compute] = queueFamily;
			m_queueFamilyPerJob[QueueJob::ComputeTransfer] = queueFamily;
		}

		return true;
	}

	bool
	Device::declareQueuesFromMultipleQueueFamilies (const DeviceRequirements & requirements, const std::vector< VkQueueFamilyProperties > & queueFamilyProperties) noexcept
	{
		/* Loop over all existing queue family in the physical device. */
		for ( uint32_t queueFamilyIndex = 0; queueFamilyIndex < queueFamilyProperties.size(); queueFamilyIndex++ )
		{
			const auto & flag = queueFamilyProperties[queueFamilyIndex].queueFlags;

			const auto maxQueueCount = queueFamilyProperties[queueFamilyIndex].queueCount;

			auto queueFamily = maxQueueCount > 1 ?
				m_queueFamilies.emplace_back(std::make_shared< QueueFamily >(queueFamilyIndex, maxQueueCount)) :
				m_queueFamilies.emplace_back(std::make_shared< QueueFamilySQ >(queueFamilyIndex));

			if ( flag & VK_QUEUE_GRAPHICS_BIT )
			{
				if ( requirements.needsGraphics() )
				{
					/* If no graphic queue has been registered or if the queue family is exclusive to graphics. */
					if ( !m_queueFamilyPerJob.contains(QueueJob::Graphics) || (flag & VK_QUEUE_COMPUTE_BIT) == 0 )
					{
						m_queueFamilyPerJob[QueueJob::Graphics] = queueFamily;

						if ( flag & VK_QUEUE_TRANSFER_BIT )
						{
							m_queueFamilyPerJob[QueueJob::GraphicsTransfer] = queueFamily;
						}
					}
				}

				if ( !requirements.tryPresentationSeparateFromGraphics() && requirements.needsPresentation() && m_physicalDevice->getSurfaceSupport(requirements.surface(), queueFamilyIndex) )
				{
					m_queueFamilyPerJob[QueueJob::Presentation] = queueFamily;
				}
			}
			else if ( requirements.tryPresentationSeparateFromGraphics() && requirements.needsPresentation() && m_physicalDevice->getSurfaceSupport(requirements.surface(), queueFamilyIndex) )
			{
				m_queueFamilyPerJob[QueueJob::Presentation] = queueFamily;
			}

			if ( requirements.needsCompute() && flag & VK_QUEUE_COMPUTE_BIT )
			{
				/* If no compute queue has been registered or if the queue family is exclusive to compute. */
				if ( !m_queueFamilyPerJob.contains(QueueJob::Compute) || (flag & VK_QUEUE_GRAPHICS_BIT) == 0 )
				{
					m_queueFamilyPerJob[QueueJob::Compute] = queueFamily;

					if ( flag & VK_QUEUE_TRANSFER_BIT )
					{
						m_queueFamilyPerJob[QueueJob::ComputeTransfer] = queueFamily;
					}
				}
			}

			if ( requirements.needsTransfer() && flag & VK_QUEUE_TRANSFER_BIT && (flag & VK_QUEUE_GRAPHICS_BIT) == 0 && (flag & VK_QUEUE_COMPUTE_BIT) == 0 )
			{
				m_queueFamilyPerJob[QueueJob::Transfer] = queueFamily;
			}
		}

		/* Check if every need are met. */
		if ( requirements.needsGraphics() && !m_queueFamilyPerJob.contains(QueueJob::Graphics) )
		{
			TraceError{ClassId} << "The physical device '" << this->name() << "' has no queue for graphics !";

			return false;
		}

		if ( requirements.needsPresentation() && !m_queueFamilyPerJob.contains(QueueJob::Presentation) )
		{
			TraceError{ClassId} << "The physical device '" << this->name() << "' has no queue for presentation !";

			return false;
		}

		if ( requirements.needsCompute() && !m_queueFamilyPerJob.contains(QueueJob::Compute) )
		{
			TraceError{ClassId} << "The physical device '" << this->name() << "' has no queue for compute !";

			return false;
		}

		if ( requirements.needsTransfer() && !m_queueFamilyPerJob.contains(QueueJob::Transfer) )
		{
			switch ( requirements.jobHint() )
			{
				case DeviceJobHint::General :
					TraceError{ClassId} << "The physical device '" << this->name() << "' has no queue for separate transfer !";

					return false;

				case DeviceJobHint::Graphics :
					m_queueFamilyPerJob[QueueJob::Transfer] = m_queueFamilyPerJob[QueueJob::Graphics];
					break;

				case DeviceJobHint::Compute :
					m_queueFamilyPerJob[QueueJob::Transfer] = m_queueFamilyPerJob[QueueJob::Compute];
					break;
			}
		}

		return true;
	}

	bool
	Device::prepareQueues (const DeviceRequirements & requirements, std::vector< VkDeviceQueueCreateInfo > & queueCreateInfos) noexcept
	{
		if ( m_flags[DebugMode] )
		{
			TraceInfo{ClassId} << requirements;
		}

		const auto & queueFamilyProperties = m_physicalDevice->queueFamilyProperties();

		if ( queueFamilyProperties.empty() )
		{
			TraceError{ClassId} << "The physical device '" << this->name() << "' has no family queue !";

			return false;
		}

		/* Check queue family requirements. */
		if ( queueFamilyProperties.size() == 1 )
		{
			TraceInfo{ClassId} <<
				"The physical device '" << this->name() << "' has a basic support. "
				"There will be only one queue family and maybe only one queue at all.";

			if ( !this->declareQueuesFromSingleQueueFamily(requirements, queueFamilyProperties[0]) )
			{
				return false;
			}
		}
		else
		{
			TraceInfo{ClassId} << "The physical device '" << this->name() << "' has an advanced support.";

			if ( !this->declareQueuesFromMultipleQueueFamilies(requirements, queueFamilyProperties) )
			{
				return false;
			}
		}

		/* Check queue count requirements. */
		for ( auto & queueFamily : m_queueFamilies )
		{
			if ( !queueFamily->hasSingleQueue() )
			{
				std::vector< std::pair< QueueJob, float > > structure{};

				for ( const auto & job : m_queueFamilyPerJob )
				{
					if ( job.second != queueFamily )
					{
						continue;
					}

					switch ( job.first )
					{
						case QueueJob::Graphics :
							for ( auto priority : requirements.graphicsQueuePriorities() )
							{
								structure.emplace_back(job.first, priority);
							}
							break;

						case QueueJob::GraphicsTransfer :
							for ( auto priority : requirements.graphicsTransferQueuePriorities() )
							{
								structure.emplace_back(job.first, priority);
							}
							break;

						case QueueJob::Presentation :
							for ( auto priority : requirements.presentationQueuePriorities() )
							{
								structure.emplace_back(job.first, priority);
							}
							break;

						case QueueJob::Compute :
							for ( auto priority : requirements.computeQueuePriorities() )
							{
								structure.emplace_back(job.first, priority);
							}
							break;

						case QueueJob::ComputeTransfer :
							for ( auto priority : requirements.computeTransferQueuePriorities() )
							{
								structure.emplace_back(job.first, priority);
							}
							break;

						case QueueJob::Transfer :
							for ( auto priority : requirements.transferQueuePriorities() )
							{
								structure.emplace_back(job.first, priority);
							}
							break;
					}
				}

				if ( structure.empty() )
				{
					TraceInfo{ClassId} << "There is no queue required for queue family #" << queueFamily->index() << " !";

					continue;
				}

				if ( !queueFamily->declareQueueStructure(structure) )
				{
					return false;
				}
			}

			queueCreateInfos.emplace_back(queueFamily->getCreateInfo(0));
		}

		return true;
	}

	bool
	Device::createDevice (const DeviceRequirements & requirements, const std::vector< VkDeviceQueueCreateInfo > & queueCreateInfos, const std::vector< const char * > & extensions) noexcept
	{
		/* Creates the logical device from the physical device information. */
		VkDeviceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pNext = nullptr;
		createInfo.flags = 0;
		createInfo.queueCreateInfoCount = static_cast< uint32_t >(queueCreateInfos.size());
		createInfo.pQueueCreateInfos = queueCreateInfos.data();
		createInfo.enabledLayerCount = 0; // IGNORED (Device layer deprecation)
		createInfo.ppEnabledLayerNames = nullptr; // IGNORED (Device layer deprecation)
		createInfo.enabledExtensionCount = static_cast< uint32_t >(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();
		createInfo.pEnabledFeatures = &(requirements.features());

		const auto result = vkCreateDevice(m_physicalDevice->handle(), &createInfo, nullptr, &m_handle);

		if ( result != VK_SUCCESS )
		{
			TraceFatal{ClassId} << "Unable to create a logical device : " << vkResultToCString(result) << " !";

			return false;
		}

		return true;
	}

	const std::shared_ptr< PhysicalDevice > &
	Device::physicalDevice () const noexcept
	{
		return m_physicalDevice;
	}

	VkDevice
	Device::handle () const noexcept
	{
		return m_handle;
	}

	bool
	Device::isDebugModeEnabled () const noexcept
	{
		return m_flags[DebugMode];
	}

	void
	Device::enableDebugMode (bool state) noexcept
	{
		m_flags[DebugMode] = state;
	}

	bool
	Device::hasBasicSupport () const noexcept
	{
		return m_flags[HasBasicSupport];
	}

	bool
	Device::hasGraphicsQueues () const noexcept
	{
		return m_queueFamilyPerJob.contains(QueueJob::Graphics);
	}

	uint32_t
	Device::getGraphicsFamilyIndex () const noexcept
	{
		auto queueFamilyIt = m_queueFamilyPerJob.find(QueueJob::Graphics);

		if ( queueFamilyIt == m_queueFamilyPerJob.cend() )
		{
			return 0;
		}

		return queueFamilyIt->second->index();
	}

	bool
	Device::hasComputeQueues () const noexcept
	{
		return m_queueFamilyPerJob.contains(QueueJob::Compute);
	}

	uint32_t
	Device::getComputeFamilyIndex () const noexcept
	{
		auto queueFamilyIt = m_queueFamilyPerJob.find(QueueJob::Compute);

		if ( queueFamilyIt == m_queueFamilyPerJob.cend() )
		{
			return 0;
		}

		return queueFamilyIt->second->index();
	}

	bool
	Device::hasTransferQueues () const noexcept
	{
		return m_queueFamilyPerJob.contains(QueueJob::Transfer);
	}

	uint32_t
	Device::getTransferFamilyIndex () const noexcept
	{
		auto queueFamilyIt = m_queueFamilyPerJob.find(QueueJob::Transfer);

		if ( queueFamilyIt == m_queueFamilyPerJob.cend() )
		{
			return 0;
		}

		return queueFamilyIt->second->index();
	}

	Queue *
	Device::getQueue (QueueJob deviceJobType, QueuePriority priority) const noexcept
	{
		auto queueFamilyIt = m_queueFamilyPerJob.find(deviceJobType);

		if ( queueFamilyIt == m_queueFamilyPerJob.cend() )
		{
			return nullptr;
		}

		return queueFamilyIt->second->queue(deviceJobType, priority);
	}

	bool
	Device::waitIdle () const noexcept
	{
		const std::lock_guard< std::mutex > lock{m_mutex};

		auto result = vkDeviceWaitIdle(m_handle);

		if ( result != VK_SUCCESS )
		{
			TraceError{ClassId} << "Unable wait device " << m_handle << " : " << vkResultToCString(result) << " !";

			return false;
		}

		return true;
	}

	uint32_t
	Device::findMemoryType (uint32_t memoryTypeFilter, VkMemoryPropertyFlags propertyFlags) const noexcept
	{
		const auto & memoryProperties = m_physicalDevice->memoryProperties();

		for ( auto memoryTypeIndex = 0U; memoryTypeIndex < memoryProperties.memoryTypeCount; memoryTypeIndex++ )
		{
			if ( (memoryTypeFilter & (1 << memoryTypeIndex)) && (memoryProperties.memoryTypes[memoryTypeIndex].propertyFlags & propertyFlags) == propertyFlags )
			{
				return memoryTypeIndex;
			}
		}

		return 0U;
	}

	VkFormat
	Device::findSupportedFormat (const std::vector< VkFormat > & formats, VkImageTiling tiling, VkFormatFeatureFlags featureFlags) const noexcept
	{
		for ( const auto & format : formats )
		{
			auto formatProperties = m_physicalDevice->getFormatProperties(format);

			switch ( tiling )
			{
				case VK_IMAGE_TILING_OPTIMAL :
					if ( (formatProperties.optimalTilingFeatures & featureFlags) == featureFlags)
					{
						return format;
					}
					break;

				case VK_IMAGE_TILING_LINEAR :
					if ( (formatProperties.linearTilingFeatures & featureFlags) == featureFlags)
					{
						return format;
					}
					break;

				/* FIXME: Check this tiling mode. */
				case VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT :
					if ( (formatProperties.optimalTilingFeatures & featureFlags) == featureFlags || (formatProperties.linearTilingFeatures & featureFlags) )
					{
						return format;
					}
					break;

				case VK_IMAGE_TILING_MAX_ENUM :
				default:
					break;
			}
		}

		return VK_FORMAT_UNDEFINED;
	}
}
