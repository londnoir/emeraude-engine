/*
 * Emeraude/Vulkan/Image.hpp
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

/* Local inclusions for inheritances. */
#include "AbstractDeviceDependentObject.hpp"
#include "DeviceMemory.hpp"

/* Local inclusions for usages. */
#include "PixelFactory/Pixmap.hpp"
#include "Vulkan/MemoryRegion.hpp"

namespace Emeraude::Graphics
{
	class ImageResource;
	class CubemapResource;
	class MovieResource;
}

namespace Emeraude::Vulkan
{
	class TransferManager;

	/**
	 * @brief The vulkan image specific buffer class.
	 * @extends std::enable_shared_from_this Adds to ability to self replicate the smart pointer.
	 * @extends Emeraude::Vulkan::AbstractDeviceDependentObject This object needs a device.
	 */
	class Image final : public AbstractDeviceDependentObject
	{
		public:

			/* Settings keys */
			static constexpr auto TextureMipmappingEnabledKey = "Video/Texture2Ds/MipmappingEnabled";
			static constexpr auto TextureDefaultMipmappingEnabled = false;
			static constexpr auto TextureInterpolateMinificationEnabledKey = "Video/Texture2Ds/InterpolateMinificationEnabled";
			static constexpr auto TextureDefaultInterpolateMinificationEnabled = false;
			static constexpr auto TextureInterpolateMagnificationEnabledKey = "Video/Texture2Ds/InterpolateMagnificationEnabled";
			static constexpr auto TextureDefaultInterpolateMagnificationEnabled = false;
			static constexpr auto TextureInterpolateMipmappingEnabledKey = "Video/Texture2Ds/InterpolateMipmappingEnabled";
			static constexpr auto TextureDefaultInterpolateMipmapping = false;
			static constexpr auto TextureAnisotropyLevelsKey = "Video/Texture2Ds/AnisotropyLevels";
			static constexpr auto TextureDefaultAnisotropyLevels = 1.0;

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VulkanImage"};

			/**
			 * @brief Constructs an image.
			 * @param device A reference to a device smart pointer.
			 * @param imageType The type of image.
			 * @param format The format of the image.
			 * @param extent A reference to an VkExtent3D for the image dimensions.
			 * @param usageFlags The usage purpose of the image.
			 * @param imageLayout The layout of the image.
			 * @param createFlags The create info flags. Default none.
			 * @param mipLevels The number of mip level. Default 1.
			 * @param arrayLayers The number of array levels. Default 1.
			 * @param sampleCount The number of sample (multisampling). Default VK_SAMPLE_COUNT_1_BIT.
			 * @param imageTiling The image tiling (memory layout). Default VK_IMAGE_TILING_OPTIMAL.
			 */
			Image (const std::shared_ptr< Device > & device, VkImageType imageType, VkFormat format, const VkExtent3D & extent, VkImageUsageFlags usageFlags, VkImageLayout imageLayout, VkImageCreateFlags createFlags = 0, uint32_t mipLevels = 1, uint32_t arrayLayers = 1, VkSampleCountFlagBits samples = VK_SAMPLE_COUNT_1_BIT, VkImageTiling imageTiling = VK_IMAGE_TILING_OPTIMAL) noexcept;

			/**
			 * @brief Constructs an image with a create info.
			 * @param device A reference to a smart pointer of the device.
			 * @param createInfo A reference to the create info.
			 */
			Image (const std::shared_ptr< Device > & device, const VkImageCreateInfo & createInfo) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Image (const Image & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Image (Image && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			Image & operator= (const Image & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			Image & operator= (Image && copy) noexcept = delete;

			/**
			 * @brief Destructs the image.
			 */
			~Image () override;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::createOnHardware() */
			bool createOnHardware () noexcept override;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::destroyFromHardware() */
			bool destroyFromHardware () noexcept override;

			/**
			 * @brief Returns the image vulkan handle.
			 * @return VkImage
			 */
			[[nodiscard]]
			VkImage handle () const noexcept;

			/**
			 * @brief Returns the image create info.
			 * @return const VkImageCreateInfo &
			 */
			[[nodiscard]]
			const VkImageCreateInfo & createInfo () const noexcept;

			/**
			 * @brief Sets the current image layout.
			 * @warning This should be call after image manipulation on GPU.
			 * @param imageLayout The Vulkan image layout.
			 * @return void
			 */
			void setCurrentImageLayout (VkImageLayout imageLayout) noexcept;

			/**
			 * @brief Returns the current image layout.
			 * @return VkImageLayout
			 */
			[[nodiscard]]
			VkImageLayout currentImageLayout () const noexcept;

			/**
			 * @brief Returns the image width.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t width () const noexcept;

			/**
			 * @brief Returns the image height.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t height () const noexcept;

			/**
			 * @brief Returns the image depth.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t depth () const noexcept;

			/**
			 * @brief Returns the number of color.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t colorCount () const noexcept;

			/**
			 * @brief Returns the image size in bytes.
			 * @warning This information come from the create info with no mipmap, not the device memory.
			 * @return VkDeviceSize
			 */
			[[nodiscard]]
			VkDeviceSize bytes () const noexcept;

			/**
			 * @brief Creates, allocates and returns an usable image.
			 * @param transferManager A reference to a transfer manager.
			 * @param imageResource A reference to an image resource smart pointer.
			 * @return bool
			 */
			[[nodiscard]]
			bool create (TransferManager & transferManager, const std::shared_ptr< Graphics::ImageResource > & imageResource) noexcept;

			/**
			 * @brief Creates, allocates and returns an usable image.
			 * @param transferManager A reference to a transfer manager.
			 * @param cubemapResource A reference to a cubemap resource smart pointer.
			 * @return bool
			 */
			[[nodiscard]]
			bool create (TransferManager & transferManager, const std::shared_ptr< Graphics::CubemapResource > & cubemapResource) noexcept;

			/**
			 * @brief Creates, allocates and returns an usable image.
			 * @param transferManager A reference to a transfer manager.
			 * @param movieResource A reference to a movie resource smart pointer.
			 * @return bool
			 */
			[[nodiscard]]
			bool create (TransferManager & transferManager, const std::shared_ptr< Graphics::MovieResource > & movieResource) noexcept;

			/**
			 * @brief Writes raw data to this image using a staging buffer.
			 * @param transferManager A reference to a transfer manager.
			 * @param memoryRegion A reference to a memory region structure.
			 * @return bool
			 */
			bool writeData (TransferManager & transferManager, const MemoryRegion & memoryRegion) noexcept;

			/**
			 * @brief Creates an image object from a vulkan handle form the swap chain.
			 * @param device A reference to a device smart pointer.
			 * @param handle The handle provided by the swap chain.
			 * @param createInfo A reference to the create info used to create the swap chain.
			 * @return std::shared_ptr< Image >
			 */
			[[nodiscard]]
			static std::shared_ptr< Image > createFromSwapChain (const std::shared_ptr< Device > & device, VkImage handle, const VkSwapchainCreateInfoKHR & createInfo) noexcept;

			/**
			 * @brief Returns the vulkan image format suitable for this pixmap.
			 * @tparam data_t The type of pixmap.
			 * @param pixmap A reference to a pixmap.
			 * @return VkFormat
			 */
			template< typename data_t >
			[[nodiscard]]
			static
			VkFormat
			getFormat (const Libraries::PixelFactory::Pixmap< data_t > & pixmap) noexcept
			{
				// NOLINTBEGIN(*-magic-numbers)
				/* Reminder :
				 * [Numeric format][SPIR-V Sampled Type][Description]
				 * UNORM, OpTypeFloat, The components are unsigned normalized values in the range [0,1]
				 * SNORM, OpTypeFloat, The components are signed normalized values in the range [-1,1]
				 * USCALED, OpTypeFloat, The components are unsigned integer values that get converted to floating-point in the range [0,2n-1]
				 * SSCALED, OpTypeFloat, The components are signed integer values that get converted to floating-point in the range [-2n-1,2n-1-1]
				 * UINT, OpTypeInt, The components are unsigned integer values in the range [0,2n-1]
				 * SINT, OpTypeInt, The components are signed integer values in the range [-2n-1,2n-1-1]
				 * UFLOAT, OpTypeFloat, The components are unsigned floating-point numbers (used by packed, shared exponent, and some compressed formats)
				 * SFLOAT, OpTypeFloat, The components are signed floating-point numbers
				 * SRGB, OpTypeFloat, The R, G, and B components are unsigned normalized values that represent values using sRGB nonlinear encoding, while the A component (if one exists) is a regular unsigned normalized value
				 *	n is the number of bits in the component.
				 */

				/* NOTE: Floating point value. */
				if constexpr ( std::is_floating_point_v< data_t > )
				{
					/* NOTE : float (4 bytes) */
					if constexpr ( sizeof(data_t) == 4 )
					{
						switch ( pixmap.colorCount() )
						{
							case 4 :
								return VK_FORMAT_R32G32B32A32_SFLOAT;

							case 3 :
								return VK_FORMAT_R32G32B32_SFLOAT;

							case 2 :
								return VK_FORMAT_R32G32_SFLOAT;

							case 1 :
								return VK_FORMAT_R32_SFLOAT;
						}
					}
					/* NOTE : double (8 bytes) */
					else if constexpr ( sizeof(data_t) == 8 )
					{
						switch ( pixmap.colorCount() )
						{
							case 4 :
								return VK_FORMAT_R64G64B64A64_SFLOAT;

							case 3 :
								return VK_FORMAT_R64G64B64_SFLOAT;

							case 2 :
								return VK_FORMAT_R64G64_SFLOAT;

							case 1 :
								return VK_FORMAT_R64_SFLOAT;
						}
					}
				}

				/* NOTE: Integer value. */
				if constexpr ( std::is_integral_v< data_t > )
				{
					/* FIXME: Check for non 8bits format ! */

					/* NOTE: uint8_t (1 byte). */
					if constexpr ( std::is_unsigned_v< data_t > )
					{
						switch ( pixmap.colorCount() )
						{
							case 4 :
								return VK_FORMAT_R8G8B8A8_UNORM;

							case 3 :
								return VK_FORMAT_R8G8B8_UNORM;

							case 2 :
								return VK_FORMAT_R8G8_UNORM;

							case 1 :
								return VK_FORMAT_R8_UNORM;
						}
					}
					/* NOTE: int8_t (1 byte). */
					else
					{
						switch ( pixmap.colorCount() )
						{
							case 4 :
								return VK_FORMAT_R8G8B8A8_SNORM;

							case 3 :
								return VK_FORMAT_R8G8B8_SNORM;

							case 2 :
								return VK_FORMAT_R8G8_SNORM;

							case 1 :
								return VK_FORMAT_R8_SNORM;
						}
					}
				}

				return VK_FORMAT_UNDEFINED;
				// NOLINTEND(*-magic-numbers)
			}

		private:

			/* Flag names. */
			static constexpr auto IsSwapChainImage = 0UL;

			VkImage m_handle{VK_NULL_HANDLE};
			VkImageCreateInfo m_createInfo{};
			std::unique_ptr< DeviceMemory > m_deviceMemory{};
			VkImageLayout m_currentImageLayout{VK_IMAGE_LAYOUT_UNDEFINED};
			std::array< bool, 8 > m_flags{ // NOLINT(*-magic-numbers)
				false/*IsSwapChainImage*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
