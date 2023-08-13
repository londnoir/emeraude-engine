/*
 * Emeraude/Audio/SoundResource.hpp
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

/* Local inclusions */
#include "Resources/ResourceTrait.hpp"
#include "PlayableInterface.hpp"
#include "Resources/Container.hpp"

namespace Emeraude::Audio
{
	class SoundResource final : public PlayableInterface, public Resources::ResourceTrait
	{
		friend class Resources::Container< SoundResource >;

		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"SoundResource"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs a sound resource.
			 * @param name The name of the resource.
			 * @param resourceFlagBits The resource flag bits. Default none. (Unused yet)
			 */
			explicit SoundResource (const std::string & name, uint32_t resourceFlagBits = 0) noexcept;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::Audio::PlayableInterface::streamable() */
			[[nodiscard]]
			size_t streamable () const noexcept override;

			/** @copydoc Emeraude::Audio::PlayableInterface::buffer() */
			[[nodiscard]]
			std::shared_ptr< const Buffer > buffer (size_t bufferIndex = 0) const noexcept override;

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
			 * @brief Returns the local data.
			 * @return const Libraries::WaveFactory::Wave< short int > &
			 */
			[[nodiscard]]
			const Libraries::WaveFactory::Wave< short int > & localData () const noexcept;

			/**
			 * @brief Returns the local data.
			 * @return Libraries::WaveFactory::Wave< short int > &
			 */
			Libraries::WaveFactory::Wave< short int > & localData () noexcept;

			/**
			 * @brief Returns a sound resource by its name.
			 * @param resourceName A reference to a string.
			 * @param directLoad Use the direct loading mode. Default false.
			 * @return std::shared_ptr< SoundResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< SoundResource > get (const std::string & resourceName, bool directLoad = false) noexcept;

			/**
			 * @brief Returns the default sound resource.
			 * @return std::shared_ptr< SoundResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< SoundResource > getDefault () noexcept;

		private:

			/** @copydoc Emeraude::Resources::ResourceTrait::onDependenciesLoaded() */
			[[nodiscard]]
			bool onDependenciesLoaded () noexcept override;

			std::shared_ptr< Buffer > m_buffer{};
			Libraries::WaveFactory::Wave< short int > m_localData{};
	};
}

/* Expose the resource manager as a convenient type. */
namespace Emeraude::Resources
{
	using Sounds = Container< Audio::SoundResource >;
}
