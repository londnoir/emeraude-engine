/*
 * Emeraude/Graphics/MovieResource.hpp
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

/* C/C++ standard libraries */
#include <cstdint>
#include <string>
#include <vector>
#include <memory>

/* Local inclusions */
#include "PixelFactory/Pixmap.hpp"
#include "Resources/ResourceTrait.hpp"
#include "Resources/Container.hpp"
#include "Constants.hpp"

namespace Emeraude::Graphics
{
	/**
	 * @brief The movie resource class.
	 * @extends Emeraude::Resources::ResourceTrait This is a loadable resource.
	 */
	class MovieResource final : public Resources::ResourceTrait
	{
		friend class Resources::Container< MovieResource >;

		public:

			/** @brief A frame from the movie with duration in milliseconds. */
			using Frame = std::pair< Libraries::PixelFactory::Pixmap< uint8_t >, size_t >;

			/** @brief Class identifier. */
			static constexpr auto ClassId{"MovieResource"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs a movie resource.
			 * @param name The name of the resource.
			 * @param resourceFlagBits The resource flag bits. Default none. (Unused yet)
			 */
			explicit MovieResource (const std::string & name, uint32_t resourceFlagBits = 0) noexcept;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Libraries::Resources::ResourceTrait::classLabel() */
			[[nodiscard]]
			const char * classLabel () const noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load() */
			bool load () noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load(const Libraries::Path::File &) */
			bool load (const Libraries::Path::File & filepath) noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load(const Json::Value &) */
			bool load (const Json::Value & data) noexcept override;

			/**
			 * @brief Returns the pixmap.
			 * @param frameIndex The frame number.
			 * @return const Libraries::PixelFactory::Pixmap< uint8_t > &
			 */
			[[nodiscard]]
			const Libraries::PixelFactory::Pixmap< uint8_t > & data (size_t frameIndex) const noexcept;

			/**
			 * @brief Returns the frames from the movie.
			 * @return const std::vector< Frame > &
			 */
			[[nodiscard]]
			const std::vector< Frame > & frames () const noexcept;

			/**
			 * @brief Returns the width of the movie.
			 * @note Returns the width of the first frame.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t width () const noexcept;

			/**
			 * @brief Returns the height of the movie.
			 * @note Returns the height of the first frame.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t height () const noexcept;

			/**
			 * @brief Returns whether frames are all gray scale.
			 * @return bool
			 */
			[[nodiscard]]
			bool isGrayScale () const noexcept;

			/**
			 * @brief Returns the average color of the movie.
			 * @return Libraries::PixelFactory::Color< float >
			 */
			[[nodiscard]]
			Libraries::PixelFactory::Color< float > averageColor () const noexcept;

			/**
			 * @brief Returns the duration in milliseconds.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t duration () const noexcept;

			/**
			 * @brief Returns the number of frame.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t frameCount () const noexcept;

			/**
			 * @brief Returns the index of the frame at specific time.
			 * @param timepoint A time point in milliseconds.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t frameIndexAt (size_t timepoint) const noexcept;

			/**
			 * @brief Returns a movie resource by its name.
			 * @param resourceName A reference to a string.
			 * @param directLoad Use the direct loading mode. Default false.
			 * @return std::shared_ptr< MovieResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< MovieResource > get (const std::string & resourceName, bool directLoad = false) noexcept;

			/**
			 * @brief Returns the default movie resource.
			 * @return std::shared_ptr< MovieResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< MovieResource > getDefault () noexcept;

		private:

			/** @copydoc Emeraude::Resources::ResourceTrait::onDependenciesLoaded() */
			[[nodiscard]]
			bool onDependenciesLoaded () noexcept override;

			/**
			 * @brief Loads a movie based on a numerical sequence of files.
			 * @param data A reference to a Json value.
			 * @return bool
			 */
			bool loadParametric (const Json::Value & data) noexcept;

			/**
			 * @brief Loads a manual version of a movie.
			 * @param data A reference to a Json value.
			 * @return bool
			 */
			bool loadManual (const Json::Value & data) noexcept;

			/**
			 * @brief Updates the full duration of the movie.
			 * @return void
			 */
			void updateDuration () noexcept;

			/**
			 * @brief extractCountWidth
			 * @param basename
			 * @param replaceKey
			 * @return size_t
			 */
			static size_t extractCountWidth (const std::string & basename, std::string & replaceKey) noexcept;

			/* JSON key. */
			static constexpr auto BaseFrameNameKey = "BaseFrameName";
			static constexpr auto FrameCountKey = "FrameCount";
			static constexpr auto FrameRateKey = "FrameRate";
			static constexpr auto FrameDurationKey = "FrameDuration";
			static constexpr auto AnimationDurationKey = "AnimationDuration";
			static constexpr auto FramesKey = "Frames";
			static constexpr auto DurationKey = "Duration";
			static constexpr auto ImageKey = "Image";

			static constexpr auto DefaultFrameDuration = 1000 / EngineUpdateFrequency< size_t >;

			std::vector< Frame > m_data{};
			size_t m_duration{};
	};
}

/* Expose the resource manager as a convenient type. */
namespace Emeraude::Resources
{
	using Movies = Container< Graphics::MovieResource >;
}
