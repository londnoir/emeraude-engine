/*
 * Emeraude/Graphics/TextureResource/Abstract.cpp
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

#include "Abstract.hpp"

/* Local inclusions. */
#include "Tracer.hpp"
#include "Vulkan/Image.hpp"
#include "Vulkan/ImageView.hpp"
#include "Vulkan/Sampler.hpp"
#include "PixelFactory/Processor.hpp"

namespace Emeraude::Graphics::TextureResource
{
	using namespace Libraries;
	using namespace Vulkan;

	constexpr auto TracerTag{"AbstractTextureResource"};

	Abstract::Abstract (const std::string & name, uint32_t resourceFlagBits) noexcept
		: ResourceTrait(name, resourceFlagBits)
	{

	}

	VkDescriptorImageInfo
	Abstract::getDescriptorInfo () const noexcept
	{
		VkDescriptorImageInfo descriptorInfo{};

		const auto & textureSampler = this->sampler();

		if ( textureSampler == nullptr )
		{
			Tracer::error(TracerTag, "The texture has no sampler !");

			descriptorInfo.sampler = VK_NULL_HANDLE;
		}
		else
		{
			descriptorInfo.sampler = textureSampler->handle();
		}

		const auto & textureImageView = this->imageView();

		if ( textureImageView == nullptr )
		{
			Tracer::error(TracerTag, "The texture has no image view !");

			descriptorInfo.imageView = VK_NULL_HANDLE;
		}
		else
		{
			descriptorInfo.imageView = textureImageView->handle();
		}

		const auto & textureImage = this->image();

		if ( textureImage == nullptr )
		{
			Tracer::error(TracerTag, "The texture has no image !");

			descriptorInfo.imageLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		}
		else
		{
			descriptorInfo.imageLayout = textureImage->currentImageLayout();
		}

		return descriptorInfo;
	}

	bool
	Abstract::onDependenciesLoaded () noexcept
	{
		/* NOTE: Ensure the texture is on the video memory. */
		if ( !this->isCreated() && !this->createOnHardware() )
		{
			TraceError{TracerTag} << "Unable to load texture resource (" << this->classLabel() << ") '" << this->name() << "' !";

			return false;
		}

		return true;
	}

	bool
	Abstract::validatePixmap (const char * classId, PixelFactory::Pixmap< uint8_t > & pixmap, bool disablePowerOfTwoCheck) noexcept
	{
		if ( !pixmap.isValid() )
		{
			Tracer::error(classId, "The pixmap is invalid !");

			return false;
		}

		if ( !disablePowerOfTwoCheck && !pixmap.isPowerOfTwo() )
		{
			Tracer::error(classId, "The pixmap size are not power of two !");

			return false;
		}

		if ( pixmap.colorCount() == 3 )
		{
			PixelFactory::Processor processor{pixmap};

			Tracer::warning(classId, "The pixmap color channel mismatch the system ! Converting to RGBA ...");

			pixmap = processor.toRGBA();
		}

		if ( !pixmap.isValid() )
		{
			Tracer::error(classId, "The pixmap became invalid after validation !");

			return false;
		}

		return true;
	}
}
