/*
 * src/Scenes/DefinitionResource.hpp
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

/* Local inclusions. */
#include "Resources/Container.hpp"

namespace Emeraude::Scenes
{
	class Scene;

	/**
	 * @brief The scene definition class.
	 * @extends Emeraude::Resources::ResourceTrait This is a resource
	 */
	class DefinitionResource final : public Resources::ResourceTrait
	{
		friend class Resources::Container< DefinitionResource >;

		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"DefinitionResource"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/* JSON key. */
			static constexpr auto BackgroundKey{"Background"};
			static constexpr auto SceneAreaKey{"SceneArea"};
			static constexpr auto ExtraDataKey{"ExtraData"};
			static constexpr auto SurfaceGravityKey{"SurfaceGravity"};
			static constexpr auto AtmosphericDensityKey{"AtmosphericDensity"};
			static constexpr auto PlanetRadiusKey{"PlanetRadius"};
			static constexpr auto WaterDensityKey{"WaterDensity"};
			static constexpr auto NodesKey{"Nodes"};
			static constexpr auto ComponentsKey{"Components"};

			/**
			 * @brief Constructs a definition resource.
			 * @param name The name of the resource.
			 * @param resourceFlagBits The resource flag bits. Default none. (Unused yet)
			 */
			explicit DefinitionResource (const std::string & name, uint32_t resourceFlagBits = 0) noexcept;

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

			/** @brief Gives the name of the scene. */
			[[nodiscard]]
			std::string getSceneName () const noexcept;

			/** @brief Build the scene from JSON definition. */
			bool buildScene (Scene & scene) noexcept;

			/** @brief Gets the extra data from the scene definition */
			[[nodiscard]]
			Json::Value getExtraData () const noexcept;

			/**
			 * @brief Returns a definition resource by its name.
			 * @param resourceName A reference to a string.
			 * @param directLoad Use the direct loading mode. Default false.
			 * @return std::shared_ptr< DefinitionResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< DefinitionResource > get (const std::string & resourceName, bool directLoad = false) noexcept;

			/**
			 * @brief Returns the default definition resource.
			 * @return std::shared_ptr< DefinitionResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< DefinitionResource > getDefault () noexcept;

		private:

			/** @copydoc Emeraude::Resources::ResourceTrait::onDependenciesLoaded() */
			[[nodiscard]]
			bool onDependenciesLoaded () noexcept override;

			/**
			 * @brief readProperties
			 * @param scene A reference to the scene.
			 * @return bool
			 */
			bool readProperties (Scene & scene) noexcept;

			/**
			 * @brief readBackground
			 * @param scene A reference to the scene.
			 * @return bool
			 */
			bool readBackground (Scene & scene) noexcept;

			/**
			 * @brief readSceneArea
			 * @param scene A reference to the scene.
			 * @return bool
			 */
			bool readSceneArea (Scene & scene) noexcept;

			Json::Value m_root{};
	};
}

/* Expose the resource manager as a convenient type. */
namespace Emeraude::Resources
{
	using SceneDefinitions = Container< Scenes::DefinitionResource >;
}
