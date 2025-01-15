/*
 * src/Graphics/TextureResource/Abstract.cpp
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

#include "Abstract.hpp"

/* STL inclusions. */
#include <cstdint>
#include <string>

/* Local inclusions. */
#include "Libraries/PixelFactory/Pixmap.hpp"
#include "Libraries/PixelFactory/Processor.hpp"
#include "Resources/ResourceTrait.hpp"
#include "Tracer.hpp"
#include "Graphics/Renderer.hpp"
#include "Vulkan/Image.hpp"
#include "Vulkan/ImageView.hpp"
#include "Vulkan/Sampler.hpp"

namespace Emeraude::Graphics::TextureResource
{
	using namespace Libraries;
	using namespace Libraries::PixelFactory;
	using namespace Vulkan;

	static constexpr auto TracerTag{"AbstractTextureResource"};

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
		if ( !this->isCreated() && !this->createOnHardware(*Renderer::instance()) )
		{
			TraceError{TracerTag} << "Unable to load texture resource (" << this->classLabel() << ") '" << this->name() << "' !";

			return false;
		}

		return true;
	}

	bool
	Abstract::validatePixmap (const char * classId, Pixmap< uint8_t > & pixmap, bool disablePowerOfTwoCheck) noexcept
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

		/* TODO: Sometimes gray scale GPU resources is useful ! */
		if ( pixmap.colorCount() != 4 )
		{
			Tracer::warning(classId, "The pixmap color channel mismatch the system ! Converting to RGBA ...");

			pixmap = Processor< uint8_t >::toRGBA(pixmap);
		}

		if ( !pixmap.isValid() )
		{
			Tracer::error(classId, "The pixmap became invalid after validation !");

			return false;
		}

		return true;
	}
}
