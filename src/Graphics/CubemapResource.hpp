/*
 * src/Graphics/CubemapResource.hpp
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

#pragma once

/* STL inclusions. */
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>

/* Local inclusions for inheritances. */
#include "Resources/ResourceTrait.hpp"

/* Local inclusions for usages. */
#include "Libs/PixelFactory/Color.hpp"
#include "Libs/PixelFactory/Pixmap.hpp"
#include "Resources/Container.hpp"
#include "Types.hpp"

namespace EmEn::Graphics
{
	/**
	 * @brief The cubemap resource class.
	 * @extends EmEn::Resources::ResourceTrait This is a loadable resource.
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

			/** @copydoc EmEn::Libs::ObservableTrait::classUID() const */
			[[nodiscard]]
			size_t classUID () const noexcept override;

			/** @copydoc EmEn::Libs::ObservableTrait::is() const */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc EmEn::Resources::ResourceTrait::classLabel() const */
			[[nodiscard]]
			const char * classLabel () const noexcept override;

			/** @copydoc EmEn::Resources::ResourceTrait::load() */
			bool load () noexcept override;

			/** @copydoc EmEn::Resources::ResourceTrait::load(const std::filesystem::path &) */
			bool load (const std::filesystem::path & filepath) noexcept override;

			/** @copydoc EmEn::Resources::ResourceTrait::load(const Json::Value &) */
			bool load (const Json::Value & data) noexcept override;

			/**
			 * @brief Loads a cubemap from a packed pixmap.
			 * @param pixmap A reference to the pixmap.
			 * @return bool
			 */
			bool load (const Libs::PixelFactory::Pixmap< uint8_t > & pixmap) noexcept;

			/**
			 * @brief Loads a cubemap from a packed pixmap.
			 * @param pixmaps A reference to a fixed array of pixmaps.
			 * @return bool
			 */
			bool load (const CubemapPixmaps & pixmaps) noexcept;

			/**
			 * @brief Returns the pixmap.
			 * @param faceIndex The face number.
			 * @return const Libraries::PixelFactory::Pixmap< uint8_t > &
			 */
			[[nodiscard]]
			const Libs::PixelFactory::Pixmap< uint8_t > & data (size_t faceIndex) const noexcept;

			/**
			 * @brief Returns faces of the cubemap.
			 * @return const CubemapPixmaps &
			 */
			[[nodiscard]]
			const CubemapPixmaps & faces () const noexcept;

			/**
			 * @brief Returns the size of the cubemap.
			 * @note Returns the width of the first face of the cubemap.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t cubeSize () const noexcept;

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
			Libs::PixelFactory::Color< float > averageColor () const noexcept;

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

			/** @copydoc EmEn::Resources::ResourceTrait::onDependenciesLoaded() */
			[[nodiscard]]
			bool onDependenciesLoaded () noexcept override;

			/* JSON keys */
			static constexpr auto PackedKey{"Packed"};
			static constexpr auto FileFormatKey{"FileFormat"};

			CubemapPixmaps m_data{};
	};
}

/* Expose the resource manager as a convenient type. */
namespace EmEn::Resources
{
	using Cubemaps = Container< Graphics::CubemapResource >;
}
