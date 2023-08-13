/*
 * Emeraude/Graphics/MovieResource.cpp
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

#include "MovieResource.hpp"

/* Local inclusions */
#include "Tracer.hpp"
#include "String.hpp"
#include "Resources/Manager.hpp"
#include "PixelFactory/FileIO.hpp"

/* Defining the resource manager class id. */
template<>
const char * const Emeraude::Resources::Container< Emeraude::Graphics::MovieResource >::ClassId{"MovieContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t Emeraude::Resources::Container< Emeraude::Graphics::MovieResource >::ClassUID{Observable::getClassUID()};

namespace Emeraude::Graphics
{
	using namespace Libraries;

	const size_t MovieResource::ClassUID{Observable::getClassUID()};

	MovieResource::MovieResource (const std::string & name, uint32_t resourceFlagBits) noexcept
		: ResourceTrait(name, resourceFlagBits)
	{

	}

	bool
	MovieResource::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	const char *
	MovieResource::classLabel () const noexcept
	{
		return ClassId;
	}

	bool
	MovieResource::load () noexcept
	{
		if ( !this->beginLoading() )
			return false;

		constexpr size_t imageCount = 3;
		constexpr size_t size = 32;

		const std::array< PixelFactory::Color< float >, imageCount > colors{
			PixelFactory::Red,
			PixelFactory::Green,
			PixelFactory::Blue
		};

		m_data.resize(3);

		for ( size_t frameIndex = 0; frameIndex < imageCount; frameIndex++ )
		{
			if ( !m_data[frameIndex].first.initialize(size, size, PixelFactory::ChannelMode::RGB) )
			{
				TraceError{ClassId} << "Unable to load the default pixmap for frame #" << frameIndex << " !";

				return this->setLoadSuccess(false);
			}

			if ( !m_data[frameIndex].first.fill(colors[frameIndex]) )
			{
				TraceError{ClassId} << "Unable to fill the default pixmap for frame #" << frameIndex << " !";

				return this->setLoadSuccess(false);
			}

			m_data[frameIndex].second = 300;
		}

		return this->setLoadSuccess(true);
	}

	bool
	MovieResource::load (const Path::File & filepath) noexcept
	{
		/* Check for a JSON file. */
		if ( filepath.hasExtension("json") )
			return Resources::ResourceTrait::load(filepath);

		/* Tries to read a movie file. */
		if ( !this->beginLoading() )
			return false;

		Tracer::warning(ClassId, "FIXME: This function is not available yet !");

		return this->setLoadSuccess(false);
	}

	bool
	MovieResource::load (const Json::Value & data) noexcept
	{
		if ( !this->beginLoading() )
			return false;

		/* Checks the load with the parametric way. */
		if ( data.isMember(BaseFrameNameKey) )
		{
			if ( !this->loadParametric(data) )
			{
				TraceError{ClassId} << "Unable to load the AnimatedTexture with parametric key '" << BaseFrameNameKey << "' !";

				return this->setLoadSuccess(false);
			}
		}
		/* Checks the load with the manual way. */
		else if ( data.isMember(FramesKey) )
		{
			if ( !this->loadManual(data) )
			{
				TraceError{ClassId} << "Unable to load the AnimatedTexture with manual key '" << FramesKey << "' !";

				return this->setLoadSuccess(false);
			}
		}
		else
		{
			TraceError{ClassId} << "There is no '" << BaseFrameNameKey << "' or '" << FramesKey << "' key in AnimatedTexture definition !";

			return this->setLoadSuccess(false);
		}

		/* Checks if there is at least one frame registered. */
		if ( m_data.empty() )
		{
			TraceError{ClassId} << "There is no valid frame for this movie !";

			return this->setLoadSuccess(false);
		}

		return this->setLoadSuccess(false);
	}

	bool
	MovieResource::loadParametric (const Json::Value & data) noexcept
	{
		/* Checks the base name of animation files. */
		const auto basename = FastJSON::getString(data, BaseFrameNameKey);

		std::string replaceKey{};

		const auto nWidth = MovieResource::extractCountWidth(basename, replaceKey);

		if ( nWidth == 0 )
		{
			TraceError{ClassId} << "Invalid basename '" << basename << "' !";

			return false;
		}

		/* Gets the frame count. */
		const auto frameCount = FastJSON::getUnsignedInteger(data, FrameCountKey);

		if ( frameCount == 0 )
		{
			Tracer::error(ClassId, "Invalid number of frame !");

			return false;
		}

		/* Gets the default duration. */
		size_t frameDuration = 0;

		auto fps = FastJSON::getUnsignedInteger(data, FrameRateKey);

		if ( fps > 0 )
		{
			frameDuration = 1000 / fps;
		}
		else
		{
			/* NOTE: The duration of the whole movie. */
			auto animationDuration = FastJSON::getUnsignedInteger(data, AnimationDurationKey);

			if ( animationDuration > 0 )
				frameDuration = animationDuration / frameCount;
			else
				frameDuration = FastJSON::getUnsignedInteger(data, FrameDurationKey, DefaultFrameDuration);
		}

		if ( frameDuration == 0 )
		{
			Tracer::error(ClassId, "Invalid frame duration !");

			return false;
		}

		/* Gets all frames images. */
		auto & images = Resources::Manager::instance()->images();

		for ( size_t frameIndex = 0; frameIndex < frameCount; frameIndex++ )
		{
			/* Sets the number as a string. */
			const auto filename = String::replace(replaceKey, String::pad(std::to_string(frameIndex + 1), nWidth, '0', String::Side::Left), basename);

			const auto imageResource = images.getResource(filename, true);

			if ( imageResource == nullptr )
			{
				TraceError{ClassId} << "Unable to get Image '" << filename << "' or the default one.";

				return false;
			}

			/* Save frame data. */
			m_data.emplace_back(imageResource->data(), frameDuration);
		}

		return true;
	}

	bool
	MovieResource::loadManual (const Json::Value & data) noexcept
	{
		if ( !data.isMember(FramesKey) || !data[FramesKey].isArray() )
		{
			TraceError{ClassId} << "The '" << FramesKey << "' key  is not present or not an array in movie definition !";

			return false;
		}

		auto & images = Resources::Manager::instance()->images();

		for ( const auto & frame : data[FramesKey] )
		{
			/* Parse the image name. */
			if ( !frame.isMember(ImageKey) || !frame[ImageKey].isString() )
			{
				TraceError{ClassId} <<
					"The '" << ImageKey << "' key is not present or not a string in movie frame definition ! "
					"Skipping that frame...";

				continue;
			}

			const auto imageName = frame[ImageKey].asString();

			/* Retrieve the image from the store. */
			const auto imageResource = images.getResource(imageName, true);

			if ( imageResource == nullptr )
			{
				TraceError{ClassId} << "Unable to get Image '" << imageName << "' or the default one.";

				return false;
			}

			/* Get the frame duration. */
			auto frameDuration = DefaultFrameDuration;

			if ( frame.isMember(DurationKey) && frame[DurationKey].isUInt() )
			{
				frameDuration = frame[DurationKey].asUInt();
			}
			else
			{
				TraceWarning{ClassId} <<
					"The '" << DurationKey << "' key is not present or not a number in movie frame definition ! "
					"Duration set to " << frameDuration << " ms.";
			}

			/* Save frame data. */
			m_data.emplace_back(imageResource->data(), frameDuration);
		}

		return true;
	}

	bool
	MovieResource::onDependenciesLoaded () noexcept
	{
		this->updateDuration();

		return true;
	}

	void
	MovieResource::updateDuration () noexcept
	{
		m_duration = std::accumulate(m_data.cbegin(), m_data.cend(), 0, [] (auto duration, const auto & frame) {
			return duration + frame.second;
		});
	}

	std::shared_ptr< MovieResource >
	MovieResource::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->movies().getResource(resourceName, directLoad);
	}

	std::shared_ptr< MovieResource >
	MovieResource::getDefault () noexcept
	{
		return Resources::Manager::instance()->movies().getDefaultResource();
	}

	const Libraries::PixelFactory::Pixmap< uint8_t > &
	MovieResource::data (size_t frameIndex) const noexcept
	{
		if ( frameIndex >= m_data.size() )
		{
			Tracer::error(ClassId, "Frame index overflow !");

			frameIndex = 0;
		}

		return m_data[frameIndex].first;
	}

	const std::vector< MovieResource::Frame > &
	MovieResource::frames () const noexcept
	{
		return m_data;
	}

	size_t
	MovieResource::width () const noexcept
	{
		if ( m_data.empty() )
			return 0;

		return m_data[0].first.width();
	}

	size_t
	MovieResource::height () const noexcept
	{
		if ( m_data.empty() )
			return 0;

		return m_data[0].first.height();
	}

	bool
	MovieResource::isGrayScale () const noexcept
	{
		return std::all_of(m_data.cbegin(), m_data.cend(), [] (const auto & frame) {
			if ( !frame.first.isValid() )
				return false;

			return frame.first.isGrayScale();
		});
	}

	PixelFactory::Color< float >
	MovieResource::averageColor () const noexcept
	{
		if ( !this->isLoaded() )
			return {};

		const auto ratio = 1.0F / m_data.size();

		auto red = 0.0F;
		auto green = 0.0F;
		auto blue = 0.0F;

		for ( const auto & frame : m_data )
		{
			const auto average = frame.first.averageColor();

			red += average.red() * ratio;
			green += average.green() * ratio;
			blue += average.blue() * ratio;
		}

		return {red, green, blue, 1.0F};
	}

	size_t
	MovieResource::duration () const noexcept
	{
		return m_duration;
	}

	size_t
	MovieResource::frameCount () const noexcept
	{
		return m_data.size();
	}

	size_t
	MovieResource::frameIndexAt (size_t timepoint) const noexcept
	{
		if ( m_duration )
		{
			auto time = timepoint % m_duration;

			for ( size_t index = 0; index < m_data.size(); index++ )
			{
				if ( m_data[index].second >= time )
					return index;

				time -= m_data[index].second;
			}
		}

		return 0;
	}

	size_t
	MovieResource::extractCountWidth (const std::string & basename, std::string & replaceKey) noexcept
	{
		auto params = String::extractTags(basename, {'{', '}'});

		if ( params.empty() )
			return 0U;

		replaceKey = '{' + params[0] + '}';

		return std::stoul(params[0]);
	}
}
