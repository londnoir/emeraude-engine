/*
 * src/Graphics/TextureResource/Abstract.cpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2025 - Sébastien Léon Claude Christian Bémelmans "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Emeraude-Engine; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Complete project and additional information can be found at :
 * https://github.com/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#include "Abstract.hpp"

/* STL inclusions. */
#include <cstdint>
#include <string>

/* Local inclusions. */
#include "Libs/PixelFactory/Pixmap.hpp"
#include "Libs/PixelFactory/Processor.hpp"
#include "Resources/ResourceTrait.hpp"
#include "Tracer.hpp"
#include "Graphics/Renderer.hpp"
#include "Vulkan/Image.hpp"
#include "Vulkan/ImageView.hpp"
#include "Vulkan/Sampler.hpp"

namespace EmEn::Graphics::TextureResource
{
	using namespace EmEn::Libs;
	using namespace EmEn::Libs::PixelFactory;
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
		if ( !this->isCreated() && !this->createOnHardware(*Renderer::instance()) )
		{
			TraceError{TracerTag} << "Unable to load texture resource (" << this->classLabel() << ") '" << this->name() << "' !";

			return false;
		}

		return true;
	}

	bool
	Abstract::validatePixmap (const char * classId, const std::string & resourceName, Pixmap< uint8_t > & pixmap) noexcept
	{
		if ( !pixmap.isValid() )
		{
			TraceError{classId} << "The pixmap for resource '" << resourceName << "' is invalid !";

			return false;
		}

		/* TODO: Sometimes gray scale GPU resources is useful ! */
		if ( pixmap.colorCount() != 4 )
		{
			if ( !s_quietConversion )
			{
				TraceWarning{classId} << "The pixmap for resource '" << resourceName << "' color channel mismatch the system ! Converting to RGBA ...";
			}

			pixmap = Processor< uint8_t >::toRGBA(pixmap);
		}

		if ( !pixmap.isValid() )
		{
			TraceError{classId} << "The pixmap for resource '" << resourceName << "' became invalid after validation !";

			return false;
		}

		return true;
	}

	bool
	Abstract::validateTexture (const Pixmap< uint8_t > & pixmap, bool disablePowerOfTwoCheck) const noexcept
	{
		if ( !pixmap.isValid() )
		{
			TraceError{TracerTag} << "The pixmap for resource '" << this->name() << "' is invalid !";

			return false;
		}

		if ( !disablePowerOfTwoCheck && !pixmap.isPowerOfTwo() )
		{
			TraceError{TracerTag} << "The pixmap size for resource '" << this->name() << "' are not power of two (" << pixmap.width() << "X" << pixmap.height() << ") !";

			return false;
		}

		return true;
	}
}
