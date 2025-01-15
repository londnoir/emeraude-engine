/*
 * src/Graphics/ImageResource.hpp
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

#pragma once

/* STL inclusions. */
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>

/* Local inclusions for inheritances. */
#include "Resources/ResourceTrait.hpp"

/* Local inclusions for usages. */
#include "Libraries/PixelFactory/Color.hpp"
#include "Libraries/PixelFactory/Pixmap.hpp"
#include "Resources/Container.hpp"

namespace Emeraude::Graphics
{
	/**
	 * @brief The image resource class.
	 * @extends Emeraude::Resources::ResourceTrait This is a loadable resource.
	 */
	class ImageResource final : public Resources::ResourceTrait
	{
		friend class Resources::Container< ImageResource >;

		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"ImageResource"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs an image resource.
			 * @param name The name of the resource.
			 * @param resourceFlagBits The resource flag bits. Default none. (Unused yet)
			 */
			explicit ImageResource (const std::string & name, uint32_t resourceFlagBits = 0) noexcept;

			/** @copydoc Libraries::ObservableTrait::classUID() const */
			[[nodiscard]]
			size_t classUID () const noexcept override;

			/** @copydoc Libraries::ObservableTrait::is() const */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::classLabel() const */
			[[nodiscard]]
			const char * classLabel () const noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load() */
			bool load () noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load(const std::filesystem::path &) */
			bool load (const std::filesystem::path & filepath) noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load(const Json::Value &) */
			bool load (const Json::Value & data) noexcept override;

			/**
			 * @brief Returns the pixmap.
			 * @return const Libraries::PixelFactory::Pixmap< uint8_t > &
			 */
			[[nodiscard]]
			const Libraries::PixelFactory::Pixmap< uint8_t > & data () const noexcept;

			/**
			 * @brief Returns the width of the image.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t width () const noexcept;

			/**
			 * @brief Returns the height of the image.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t height () const noexcept;

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
			 * @brief Returns a image resource by its name.
			 * @param resourceName A reference to a string.
			 * @param directLoad Use the direct loading mode. Default false.
			 * @return std::shared_ptr< ImageResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< ImageResource > get (const std::string & resourceName, bool directLoad = false) noexcept;

			/**
			 * @brief Returns the default image resource.
			 * @return std::shared_ptr< ImageResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< ImageResource > getDefault () noexcept;

		private:

			/** @copydoc Emeraude::Resources::ResourceTrait::onDependenciesLoaded() */
			[[nodiscard]]
			bool onDependenciesLoaded () noexcept override;

			Libraries::PixelFactory::Pixmap< uint8_t > m_data{};
	};
}

/* Expose the resource manager as a convenient type. */
namespace Emeraude::Resources
{
	using Images = Container< Graphics::ImageResource >;
}
