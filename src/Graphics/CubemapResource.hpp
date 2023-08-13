/*
 * Emeraude/Graphics/CubemapResource.hpp
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
#include <array>
#include <cstdint>
#include <memory>
#include <string>

/* Local inclusions */
#include "PixelFactory/Pixmap.hpp"
#include "Resources/Container.hpp"
#include "Resources/ResourceTrait.hpp"

namespace Emeraude::Graphics
{
	/**
	 * @brief The cubemap resource class.
	 * @extends Emeraude::Resources::ResourceTrait This is a loadable resource.
	 */
	class CubemapResource final : public Resources::ResourceTrait
	{
		friend class Resources::Container< CubemapResource >;

		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"CubemapResource"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs a cubemap resource.
			 * @param name The name of the resource.
			 * @param resourceFlagBits The resource flag bits. Default none. (Unused yet)
			 */
			explicit CubemapResource (const std::string & name, uint32_t resourceFlagBits = 0) noexcept;

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
			 * @brief Loads a cubemap from a packed pixmap.
			 * @param pixmap A reference to the pixmap.
			 * @return bool
			 */
			bool load (const Libraries::PixelFactory::Pixmap< uint8_t > & pixmap) noexcept;

			/**
			 * @brief Loads a cubemap from a packed pixmap.
			 * @param pixmaps A reference to a fixed array of pixmaps.
			 * @return bool
			 */
			bool load (const std::array< Libraries::PixelFactory::Pixmap< uint8_t >, 6 > & pixmaps) noexcept;

			/**
			 * @brief Returns the pixmap.
			 * @param faceIndex The face number.
			 * @return const Libraries::PixelFactory::Pixmap< uint8_t > &
			 */
			[[nodiscard]]
			const Libraries::PixelFactory::Pixmap< uint8_t > & data (size_t faceIndex) const noexcept;

			/**
			 * @brief Returns faces of the cubemap.
			 * @return const std::array< Libraries::PixelFactory::Pixmap< uint8_t >, 6 > &
			 */
			[[nodiscard]]
			const std::array< Libraries::PixelFactory::Pixmap< uint8_t >, 6 > & faces () const noexcept;

			/**
			 * @brief Returns the size of the cubemap.
			 * @note Returns the width of the first face of the cubemap.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t size () const noexcept;

			/**
			 * @brief Returns whether pixmaps are all gray scale.
			 * @return bool
			 */
			[[nodiscard]]
			bool isGrayScale () const noexcept;

			/**
			 * @brief Returns the average color of the cubemap.
			 * @return Libraries::PixelFactory::Color< float >
			 */
			[[nodiscard]]
			Libraries::PixelFactory::Color< float > averageColor () const noexcept;

			/**
			 * @brief Returns a cubemap resource by its name.
			 * @param resourceName A reference to a string.
			 * @param directLoad Use the direct loading mode. Default false.
			 * @return std::shared_ptr< CubemapResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< CubemapResource > get (const std::string & resourceName, bool directLoad = false) noexcept;

			/**
			 * @brief Returns the default cubemap resource.
			 * @return std::shared_ptr< CubemapResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< CubemapResource > getDefault () noexcept;

		private:

			/** @copydoc Emeraude::Resources::ResourceTrait::onDependenciesLoaded() */
			[[nodiscard]]
			bool onDependenciesLoaded () noexcept override;

			/* JSON keys */
			static constexpr auto PackedKey = "Packed";
			static constexpr auto FileFormatKey = "FileFormat";
			static constexpr auto PositiveXKey = "PositiveX";
			static constexpr auto NegativeXKey = "NegativeX";
			static constexpr auto PositiveYKey = "PositiveY";
			static constexpr auto NegativeYKey = "NegativeY";
			static constexpr auto PositiveZKey = "PositiveZ";
			static constexpr auto NegativeZKey = "NegativeZ";

			static constexpr std::array< const char * const, 6 > s_texturesName = {{
				PositiveXKey, NegativeXKey,
				PositiveYKey, NegativeYKey,
				PositiveZKey, NegativeZKey
			}};

			std::array< Libraries::PixelFactory::Pixmap< uint8_t >, 6 > m_data{};
	};
}

/* Expose the resource manager as a convenient type. */
namespace Emeraude::Resources
{
	using Cubemaps = Container< Graphics::CubemapResource >;
}
