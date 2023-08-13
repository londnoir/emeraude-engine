/*
 * Emeraude/Vulkan/Image.cpp
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

#include "Image.hpp"

/* Local inclusions. */
#include "Device.hpp"
#include "Graphics/CubemapResource.hpp"
#include "Graphics/ImageResource.hpp"
#include "Graphics/MovieResource.hpp"
#include "StagingBuffer.hpp"
#include "Tracer.hpp"
#include "TransferManager.hpp"
#include "Utility.hpp"

namespace Emeraude::Vulkan
{
	using namespace Libraries;

	Image::Image (const std::shared_ptr< Device > & device, VkImageType imageType, VkFormat format, const VkExtent3D & extent, VkImageUsageFlags usageFlags, VkImageLayout imageLayout, VkImageCreateFlags createFlags, uint32_t mipLevels, uint32_t arrayLayers, VkSampleCountFlagBits samples, VkImageTiling imageTiling) noexcept
		: AbstractDeviceDependentObject(device)
	{
		m_createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		m_createInfo.pNext = nullptr;
		m_createInfo.flags = createFlags;
		m_createInfo.imageType = imageType;
		m_createInfo.format = format;
		m_createInfo.extent = extent;
		m_createInfo.mipLevels = mipLevels;
		m_createInfo.arrayLayers = arrayLayers;
		m_createInfo.samples = samples;
		m_createInfo.tiling = imageTiling;
		m_createInfo.usage = usageFlags;
		m_createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		m_createInfo.queueFamilyIndexCount = 0;
		m_createInfo.pQueueFamilyIndices = nullptr;
		m_createInfo.initialLayout = imageLayout;
	}

	Image::Image (const std::shared_ptr< Device > & device, const VkImageCreateInfo & createInfo) noexcept
		: AbstractDeviceDependentObject(device), m_createInfo(createInfo)
	{

	}

	Image::~Image ()
	{
		this->destroyFromHardware();
	}

	std::shared_ptr< Image >
	Image::createFromSwapChain (const std::shared_ptr< Device > & device, VkImage handle, const VkSwapchainCreateInfoKHR & createInfo) noexcept
	{
		auto swapChainImage = std::make_shared< Image >(
			device,
			VK_IMAGE_TYPE_2D, // Image type
			createInfo.imageFormat, // Image format (bits description)
			VkExtent3D{createInfo.imageExtent.width, createInfo.imageExtent.height, 1}, // Image extent
			createInfo.imageUsage, // Image usage (color, depth, ...)
			VK_IMAGE_LAYOUT_UNDEFINED, // Layout
			0, // flags
			1, // Image mip levels
			createInfo.imageArrayLayers, // Image array layers
			VK_SAMPLE_COUNT_1_BIT, // Image multi sampling
			VK_IMAGE_TILING_OPTIMAL // Image tiling
		);

		/* NOTE: Set internal values manually and declare the image as created. */
		swapChainImage->m_handle = handle;
		swapChainImage->m_flags[IsSwapChainImage] = true;
		swapChainImage->setCreated();

		return swapChainImage;
	}

	bool
	Image::createOnHardware () noexcept
	{
		/* NOTE: Special case for swap chain images. */
		if ( m_flags[IsSwapChainImage] )
		{
			Tracer::error(ClassId, "This is an image provided by the swap chain ! No need to create it.");

			return true;
		}

		if ( !this->hasDevice() )
		{
			Tracer::error(ClassId, "No device to create this image !");

			return false;
		}

		/* 1. Create the hardware image. */
		auto result = vkCreateImage(
			this->device()->handle(),
			&m_createInfo,
			VK_NULL_HANDLE,
			&m_handle
		);

		if ( result != VK_SUCCESS )
		{
			TraceError{ClassId} << "Unable to create an image : " << vkResultToCString(result) << " !";

			return false;
		}

		/* 2. Allocate device memory for the image. */
		VkMemoryRequirements memoryRequirement{};

		vkGetImageMemoryRequirements(
			this->device()->handle(),
			m_handle,
			&memoryRequirement
		);

		m_deviceMemory = std::make_unique< DeviceMemory >(this->device(), memoryRequirement, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		m_deviceMemory->setIdentifier(this->identifier() + "-Main-DeviceMemory");

		if ( !m_deviceMemory->createOnHardware() )
		{
			TraceError{ClassId} << "Unable to create a device memory for the image " << m_handle << " !";

			this->destroyFromHardware();

			return false;
		}

		/* 3. Bind the image to the device memory. */
		result = vkBindImageMemory(
			this->device()->handle(),
			m_handle,
			m_deviceMemory->handle(),
			0// offset
		);

		if ( result != VK_SUCCESS )
		{
			TraceError{ClassId} <<
				"Unable to bind the image " << m_handle << " to the device memory " << m_deviceMemory->handle() <<
				" : " << vkResultToCString(result) << " !";

			this->destroyFromHardware();

			return false;
		}

		this->setCreated();

		TraceSuccess{ClassId} <<
			"The image " << m_handle << " (" << this->identifier() << ") is successfully created !" "\n"
			"Device memory size : " << m_deviceMemory->bytes() << " bytes" "\n"
			"Create info size : " << this->bytes() << " bytes";

		return true;
	}

	bool
	Image::create (TransferManager & transferManager, const std::shared_ptr< Graphics::ImageResource > & imageResource) noexcept
	{
		if ( !this->createOnHardware() )
		{
			return false;
		}

		const auto & pixmap = imageResource->data();

		/* Get an available staging buffer to prepare the transfer */
		auto stagingBuffer = transferManager.getStagingBuffer(pixmap.bytes());

		if ( stagingBuffer == nullptr )
		{
			return false;
		}

		/* NOTE: Already locked, but gives the ability to unlock the staging buffer automatically at function exit. */
		const std::lock_guard< StagingBuffer > lock{*stagingBuffer};

		if ( !stagingBuffer->writeData({pixmap.data().data(), pixmap.bytes()}) )
		{
			TraceError{ClassId} << "Unable to write " << pixmap.bytes() << " bytes of data in the staging buffer !";

			return false;
		}

		TraceSuccess{ClassId} << pixmap.bytes() << " bytes successfully written in the staging buffer !";

		/* Transfer the image data from host memory to device memory. */
		return transferManager.transfer(*stagingBuffer, *this);
	}

	bool
	Image::create (TransferManager & transferManager, const std::shared_ptr< Graphics::CubemapResource > & cubemapResource) noexcept
	{
		if ( !this->createOnHardware() )
		{
			return false;
		}

		const auto & pixmaps = cubemapResource->faces();

		/* Get the total bytes requested for the 6 faces. */
		const size_t totalBytes = std::accumulate(pixmaps.cbegin(), pixmaps.cend(), 0, [] (auto sum, const auto & pixmap) {
			return sum + pixmap.bytes();
		});

		/* Get an available staging buffer to prepare the transfer */
		auto stagingBuffer = transferManager.getStagingBuffer(totalBytes);

		if ( stagingBuffer == nullptr )
		{
			return false;
		}

		/* NOTE: Already locked, but gives the ability to unlock the staging buffer automatically at function exit. */
		const std::lock_guard< StagingBuffer > lock{*stagingBuffer};

		/* NOTE: We will write all 6 pixmaps next to each others in the staging buffer. */
		size_t offset = 0;

		for ( const auto & pixmap : pixmaps )
		{
			if ( !stagingBuffer->writeData({pixmap.data().data(), pixmap.bytes(), offset}) )
			{
				TraceError{ClassId} << "Unable to write " << pixmap.bytes() << " bytes of data in the staging buffer !";

				return false;
			}

			offset += pixmap.bytes();
		}

		TraceSuccess{ClassId} << totalBytes << " bytes successfully written in the staging buffer !";

		/* Transfer the image data from host memory to device memory. */
		return transferManager.transfer(*stagingBuffer, *this);
	}

	bool
	Image::create (TransferManager & transferManager, const std::shared_ptr< Graphics::MovieResource > & movieResource) noexcept
	{
		if ( !this->createOnHardware() )
		{
			return false;
		}

		const auto & frames = movieResource->frames();

		const size_t totalBytes = std::accumulate(frames.cbegin(), frames.cend(), 0, [] (auto sum, const auto & frame) {
			return sum + frame.first.bytes();
		});

		/* Get an available staging buffer to prepare the transfer */
		auto stagingBuffer = transferManager.getStagingBuffer(totalBytes);

		if ( stagingBuffer == nullptr )
		{
			return false;
		}

		/* NOTE: Already locked, but gives the ability to unlock the staging buffer automatically at function exit. */
		const std::lock_guard< StagingBuffer > lock{*stagingBuffer};

		size_t offset = 0;

		for ( const auto & frame : frames )
		{
			const auto & pixmap = frame.first;

			if ( !stagingBuffer->writeData({pixmap.data().data(), pixmap.bytes(), offset}) )
			{
				TraceError{ClassId} << "Unable to write " << pixmap.bytes() << " bytes of data in the staging buffer !";

				return false;
			}

			offset += pixmap.bytes();
		}

		TraceSuccess{ClassId} << totalBytes << " bytes successfully written in the staging buffer !";

		/* Transfer the image data from host memory to device memory. */
		return transferManager.transfer(*stagingBuffer, *this);
	}

	bool
	Image::writeData (TransferManager & transferManager, const MemoryRegion & memoryRegion) noexcept
	{
		if ( !this->isCreated() )
		{
			Tracer::error(ClassId, "The image is not created ! Use one of the Image::create() methods first.");

			return false;
		}

		/* Get an available staging buffer to prepare the transfer */
		auto stagingBuffer = transferManager.getStagingBuffer(memoryRegion.bytes());

		if ( stagingBuffer == nullptr )
		{
			return false;
		}

		/* NOTE: Already locked, but gives the ability to unlock the staging buffer automatically at function exit. */
		const std::lock_guard< StagingBuffer > lock{*stagingBuffer};

		if ( !stagingBuffer->writeData(memoryRegion) )
		{
			TraceError{ClassId} << "Unable to write " << memoryRegion.bytes() << " bytes of data in the staging buffer !";

			return false;
		}

		TraceSuccess{ClassId} << memoryRegion.bytes() << " bytes successfully written in the staging buffer !";

		/* Transfer the image data from host memory to device memory. */
		return transferManager.transfer(*stagingBuffer, *this);
	}

	bool
	Image::destroyFromHardware () noexcept
	{
		/* NOTE: Special case for swap chain images. */
		if ( m_flags[IsSwapChainImage] )
		{
			m_handle = VK_NULL_HANDLE;

			this->setDestroyed();

			return true;
		}

		if ( !this->hasDevice() )
		{
			TraceError{ClassId} << "No device to destroy the image " << m_handle << " (" << this->identifier() << ") !";

			return false;
		}

		if ( m_deviceMemory != nullptr )
		{
			m_deviceMemory->destroyFromHardware();
			m_deviceMemory.reset();
		}

		if ( m_handle != VK_NULL_HANDLE )
		{
			this->device()->waitIdle();

			vkDestroyImage(
				this->device()->handle(),
				m_handle,
				VK_NULL_HANDLE
			);

			TraceSuccess{ClassId} << "The image " << m_handle << " (" << this->identifier() << ") is gracefully destroyed !";

			m_handle = VK_NULL_HANDLE;
		}

		this->setDestroyed();

		return true;
	}

	VkImage
	Image::handle () const noexcept
	{
		return m_handle;
	}

	const VkImageCreateInfo &
	Image::createInfo () const noexcept
	{
		return m_createInfo;
	}

	void
	Image::setCurrentImageLayout (VkImageLayout imageLayout) noexcept
	{
		m_currentImageLayout = imageLayout;
	}

	VkImageLayout
	Image::currentImageLayout () const noexcept
	{
		return m_currentImageLayout;
	}

	uint32_t
	Image::width () const noexcept
	{
		return m_createInfo.extent.width;
	}

	uint32_t
	Image::height () const noexcept
	{
		return m_createInfo.extent.height;
	}

	uint32_t
	Image::depth () const noexcept
	{
		return m_createInfo.extent.depth;
	}

	uint32_t
	Image::colorCount () const noexcept
	{
		switch ( m_createInfo.format )
		{
			/* FIXME: Declares each used format ... */
			default:
				return 4;
		}
	}

	VkDeviceSize
	Image::bytes () const noexcept
	{
		/* FIXME: incorrect, this only count pixel elements ! */
		return this->width() * this->height() * this->depth() * this->colorCount() /** sizeof(???)*/;
	}
}
