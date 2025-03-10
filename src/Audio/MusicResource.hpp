/*
 * src/Audio/MusicResource.hpp
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
#include <vector>

/* Local inclusions for inheritances. */
#include "PlayableInterface.hpp"
#include "Resources/ResourceTrait.hpp"

/* Local inclusions. */
#include "Resources/Container.hpp"

namespace Emeraude::Audio
{
	/**
	 * @brief The music resource class.
	 * @extends Emeraude::Audio::PlayableInterface
	 * @extends Emeraude::Resources::ResourceTrait This is a loadable resource.
	 */
	class MusicResource final : public PlayableInterface, public Resources::ResourceTrait
	{
		friend class Resources::Container< MusicResource >;

		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"MusicResource"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs a music resource.
			 * @param name The name of the resource.
			 * @param resourceFlagBits The resource flag bits. Default none. (Unused yet)
			 */
			explicit MusicResource (const std::string & name, uint32_t resourceFlagBits = 0) noexcept;

			/** @copydoc Libraries::ObservableTrait::classUID() const */
			[[nodiscard]]
			size_t
			classUID () const noexcept override
			{
				return ClassUID;
			}

			/** @copydoc Libraries::ObservableTrait::is() const */
			[[nodiscard]]
			bool
			is (size_t classUID) const noexcept override
			{
				return classUID == ClassUID;
			}

			/** @copydoc Emeraude::Audio::PlayableInterface::streamable() */
			[[nodiscard]]
			size_t
			streamable () const noexcept override
			{
				return m_buffers.size();
			}

			/** @copydoc Emeraude::Audio::PlayableInterface::buffer() */
			[[nodiscard]]
			std::shared_ptr< const Buffer >
			buffer (size_t bufferIndex = 0) const noexcept override
			{
				return m_buffers.at(bufferIndex);
			}

			/** @copydoc Emeraude::Resources::ResourceTrait::classLabel() const */
			[[nodiscard]]
			const char *
			classLabel () const noexcept override
			{
				return ClassId;
			}

			/** @copydoc Emeraude::Resources::ResourceTrait::load() */
			bool load () noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load(const std::filesystem::path &) */
			bool load (const std::filesystem::path & filepath) noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load(const Json::Value &) */
			bool load (const Json::Value & data) noexcept override;

			/**
			 * @brief Returns the local data.
			 * @return const Libraries::WaveFactory::Wave< int16_t > &
			 */
			[[nodiscard]]
			const Libraries::WaveFactory::Wave< int16_t > &
			localData () const noexcept
			{
				return m_localData;
			}

			/**
			 * @brief Returns the local data.
			 * @return Libraries::WaveFactory::Wave< int16_t > &
			 */
			Libraries::WaveFactory::Wave< int16_t > &
			localData () noexcept
			{
				return m_localData;
			}

			/**
			 * @brief Returns the title of the music.
			 * @return const std::string &
			 */
			[[nodiscard]]
			const std::string &
			title () const noexcept
			{
				return m_title;
			}

			/**
			 * @brief Returns the artist of the music.
			 * @return const std::string &
			 */
			[[nodiscard]]
			const std::string &
			artist () const noexcept
			{
				return m_artist;
			}

			/**
			 * @brief Returns a music resource by its name.
			 * @param resourceName A reference to a string.
			 * @param directLoad Use the direct loading mode. Default false.
			 * @return std::shared_ptr< MusicResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< MusicResource > get (const std::string & resourceName, bool directLoad = false) noexcept;

			/**
			 * @brief Returns the default music resource.
			 * @return std::shared_ptr< MusicResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< MusicResource > getDefault () noexcept;

		private:

			/** @copydoc Emeraude::Resources::ResourceTrait::onDependenciesLoaded() */
			[[nodiscard]]
			bool onDependenciesLoaded () noexcept override;

			/**
			 * @brief Reads the music file metadata.
			 * @param filepath A reference to a filesystem path.
			 */
			void readMetaData (const std::filesystem::path & filepath) noexcept;

			static constexpr auto DefaultInfo{"Unknown"};

			std::vector< std::shared_ptr< Buffer > > m_buffers;
			Libraries::WaveFactory::Wave< int16_t > m_localData;
			std::string m_title{DefaultInfo};
			std::string m_artist{DefaultInfo};
	};
}

/* Expose the resource manager as a convenient type. */
namespace Emeraude::Resources
{
	using Musics = Container< Audio::MusicResource >;
}
