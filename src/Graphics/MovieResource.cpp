/*
 * src/Graphics/MovieResource.cpp
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

#include "MovieResource.hpp"

/* STL inclusions. */
#include <cstdint>
#include <cstddef>
#include <vector>
#include <array>
#include <string>
#include <memory>
#include <algorithm>
#include <numeric>
#include <ranges>

/* Third-Party inclusions. */
#include "json/json.h"

/* Local inclusions. */
#include "Libraries/PixelFactory/Pixmap.hpp"
#include "Libraries/PixelFactory/Types.hpp"
#include "Libraries/PixelFactory/Color.hpp"
#include "Libraries/ObservableTrait.hpp"
#include "Libraries/FastJSON.hpp"
#include "Libraries/String.hpp"
#include "Resources/Container.hpp"
#include "Resources/Manager.hpp"
#include "Resources/ResourceTrait.hpp"
#include "Tracer.hpp"

/* Defining the resource manager class id. */
template<>
const char * const Emeraude::Resources::Container< Emeraude::Graphics::MovieResource >::ClassId{"MovieContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t Emeraude::Resources::Container< Emeraude::Graphics::MovieResource >::ClassUID{getClassUID(ClassId)};

namespace Emeraude::Graphics
{
	using namespace Libraries;

	const size_t MovieResource::ClassUID{getClassUID(ClassId)};

	/* JSON key. */
	constexpr auto JKBaseFrameName{"BaseFrameName"};
	constexpr auto JKFrameCount{"FrameCount"};
	constexpr auto JKFrameRate{"FrameRate"};
	constexpr auto JKFrameDuration{"FrameDuration"};
	constexpr auto JKIsLooping{"IsLooping"};
	constexpr auto JKAnimationDuration{"AnimationDuration"};
	constexpr auto JKFrames{"Frames"};
	constexpr auto JKDuration{"Duration"};
	constexpr auto JKImage{"Image"};

	MovieResource::MovieResource (const std::string & name, uint32_t resourceFlagBits) noexcept
		: ResourceTrait(name, resourceFlagBits)
	{

	}

	bool
	MovieResource::load () noexcept
	{
		if ( !this->beginLoading() )
		{
			return false;
		}

		constexpr size_t imageCount{3};
		constexpr size_t size{32};

		constexpr std::array< PixelFactory::Color< float >, imageCount > colors{
			PixelFactory::Red,
			PixelFactory::Green,
			PixelFactory::Blue
		};

		m_frames.resize(3);

		for ( size_t frameIndex = 0; frameIndex < imageCount; frameIndex++ )
		{
			if ( !m_frames[frameIndex].first.initialize(size, size, PixelFactory::ChannelMode::RGB) )
			{
				TraceError{ClassId} << "Unable to load the default pixmap for frame #" << frameIndex << " !";

				return this->setLoadSuccess(false);
			}

			if ( !m_frames[frameIndex].first.fill(colors.at(frameIndex)) )
			{
				TraceError{ClassId} << "Unable to fill the default pixmap for frame #" << frameIndex << " !";

				return this->setLoadSuccess(false);
			}

			m_frames[frameIndex].second = DefaultFrameDuration;
		}

		return this->setLoadSuccess(true);
	}

	bool
	MovieResource::load (const std::filesystem::path & filepath) noexcept
	{
		/* Check for a JSON file. */
		if ( IO::getFileExtension(filepath) == "json" )
		{
			return Resources::ResourceTrait::load(filepath);
		}

		/* Tries to read a movie (mp4, mpg, avi, ...) file. */
		Tracer::debug(ClassId, "Reading movie file is not available yet !");

		if ( !this->beginLoading() )
		{
			return false;
		}

		return this->setLoadSuccess(false);
	}

	bool
	MovieResource::load (const Json::Value & data) noexcept
	{
		if ( !this->beginLoading() )
		{
			return false;
		}

		/* Checks the load with the parametric way. */
		if ( data.isMember(JKBaseFrameName) )
		{
			if ( !this->loadParametric(data) )
			{
				TraceError{ClassId} << "Unable to load the animated texture with parametric key '" << JKBaseFrameName << "' !";

				return this->setLoadSuccess(false);
			}
		}
		/* Checks the load with the manual way. */
		else if ( data.isMember(JKFrames) )
		{
			if ( !this->loadManual(data) )
			{
				TraceError{ClassId} << "Unable to load the animated texture with manual key '" << JKFrames << "' !";

				return this->setLoadSuccess(false);
			}
		}
		else
		{
			TraceError{ClassId} << "There is no '" << JKBaseFrameName << "' or '" << JKFrames << "' key in animated texture definition !";

			return this->setLoadSuccess(false);
		}

		/* Checks if there is at least one frame registered. */
		if ( m_frames.empty() )
		{
			TraceError{ClassId} << "There is no valid frame for this movie !";

			return this->setLoadSuccess(false);
		}

		return this->setLoadSuccess(true);
	}

	size_t
	MovieResource::extractFrameDuration (const Json::Value & data, size_t frameCount) noexcept
	{
		const auto fps = FastJSON::getNumber< uint32_t >(data, JKFrameRate, 0);

		if ( fps > 0 )
		{
			/* NOTE: Compute by using an FPS definition. */
			return BaseTime / fps;
		}

		const auto animationDuration = FastJSON::getNumber< uint32_t >(data, JKAnimationDuration, 0);

		if ( animationDuration > 0 )
		{
			/* NOTE: Using the duration of the whole movie. */
			return animationDuration / frameCount;
		}

		/* NOTE: Using a defined frame duration. */
		return FastJSON::getNumber< uint32_t >(data, JKFrameDuration, DefaultFrameDuration);
	}

	bool
	MovieResource::loadParametric (const Json::Value & data) noexcept
	{
		/* Checks the base name of animation files. */
		const auto basename = FastJSON::getString(data, JKBaseFrameName);

		if ( basename.empty() )
		{
			return false;
		}

		std::string replaceKey{};

		const auto nWidth = MovieResource::extractCountWidth(basename, replaceKey);

		if ( nWidth == 0 )
		{
			TraceError{ClassId} << "Invalid basename '" << basename << "' !";

			return false;
		}

		/* Gets the frame count. */
		const auto frameCount = FastJSON::getNumber< uint32_t >(data, JKFrameCount, 0);

		if ( frameCount == 0 )
		{
			Tracer::error(ClassId, "Invalid number of frame !");

			return false;
		}

		/* Gets the frame duration. */
		const auto frameDuration = MovieResource::extractFrameDuration(data, frameCount);

		if ( frameDuration == 0 )
		{
			Tracer::error(ClassId, "Invalid frame duration !");

			return false;
		}

		m_looping = FastJSON::getBoolean(data, JKIsLooping, true);

		/* Gets all frames images. */
		auto & images = Resources::Manager::instance()->images();

		for ( size_t frameIndex = 0; frameIndex < frameCount; frameIndex++ )
		{
			/* Sets the number as a string. */
			const auto filename = String::replace(replaceKey, pad(std::to_string(frameIndex + 1), nWidth, '0', String::Side::Left), basename);

			const auto imageResource = images.getResource(filename, false);

			if ( imageResource == nullptr )
			{
				TraceError{ClassId} << "Unable to get Image '" << filename << "' or the default one.";

				return false;
			}

			/* Save frame data. */
			m_frames.emplace_back(imageResource->data(), frameDuration);
		}

		return true;
	}

	bool
	MovieResource::loadManual (const Json::Value & data) noexcept
	{
		if ( !data.isMember(JKFrames) || !data[JKFrames].isArray() )
		{
			TraceError{ClassId} << "The '" << JKFrames << "' key  is not present or not an array in movie definition !";

			return false;
		}

		auto & images = Resources::Manager::instance()->images();

		for ( const auto & frame : data[JKFrames] )
		{
			const auto imageName = FastJSON::getString(frame, JKImage);

			if ( imageName.empty() )
			{
				TraceError{ClassId} <<
					"The '" << JKImage << "' key is not present or not a string in movie frame definition ! "
					"Skipping that frame...";

				continue;
			}

			/* NOTE: The image must be loaded synchronously here. */
			const auto imageResource = images.getResource(imageName, false);

			m_frames.emplace_back(imageResource->data(), FastJSON::getNumber< uint32_t >(frame, JKDuration, DefaultFrameDuration));
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
		m_duration = std::accumulate(m_frames.cbegin(), m_frames.cend(), 0, [] (auto duration, const auto & frame) {
			return duration + frame.second;
		});
	}

	std::shared_ptr< MovieResource >
	MovieResource::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->movies().getResource(resourceName, !directLoad);
	}

	std::shared_ptr< MovieResource >
	MovieResource::getDefault () noexcept
	{
		return Resources::Manager::instance()->movies().getDefaultResource();
	}

	const PixelFactory::Pixmap< uint8_t > &
	MovieResource::data (size_t frameIndex) const noexcept
	{
		if ( frameIndex >= m_frames.size() )
		{
			Tracer::error(ClassId, "Frame index overflow !");

			frameIndex = 0;
		}

		return m_frames[frameIndex].first;
	}

	bool
	MovieResource::isGrayScale () const noexcept
	{
		return std::ranges::all_of(m_frames, [] (const auto & frame) {
			if ( !frame.first.isValid() )
			{
				return false;
			}

			return frame.first.isGrayScale();
		});
	}

	PixelFactory::Color< float >
	MovieResource::averageColor () const noexcept
	{
		if ( !this->isLoaded() )
		{
			return {};
		}

		const auto ratio = 1.0F / static_cast< float >(m_frames.size());

		auto red = 0.0F;
		auto green = 0.0F;
		auto blue = 0.0F;

		for ( const auto & frame : std::ranges::views::keys(m_frames) )
		{
			const auto average = frame.averageColor();

			red += average.red() * ratio;
			green += average.green() * ratio;
			blue += average.blue() * ratio;
		}

		return {red, green, blue, 1.0F};
	}

	size_t
	MovieResource::frameIndexAt (uint32_t timePoint) const noexcept
	{
		if ( m_duration > 0 )
		{
			auto time = timePoint % m_duration;

			if ( !m_looping && timePoint >= m_duration )
			{
				return m_frames.size() - 1;
			}

			for ( size_t index = 0; index < m_frames.size(); index++ )
			{
				if ( m_frames[index].second >= time )
				{
					return index;
				}

				time -= static_cast< uint32_t >(m_frames[index].second);
			}
		}

		return 0;
	}

	size_t
	MovieResource::extractCountWidth (const std::string & basename, std::string & replaceKey) noexcept
	{
		const auto params = String::extractTags(basename, {'{', '}'}, true);

		if ( params.empty() )
		{
			return 0;
		}

		replaceKey = '{' + params[0] + '}';

		return std::stoul(params[0]);
	}
}
