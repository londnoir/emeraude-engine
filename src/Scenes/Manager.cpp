/*
 * src/Scenes/Manager.cpp
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

#include "Manager.hpp"

/* STL inclusions. */
#include <algorithm>
#include <array>
#include <cstddef>
#include <map>
#include <memory>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

/* Local inclusions. */
#include "DefinitionResource.hpp"
#include "Graphics/Renderable/AbstractBackground.hpp"
#include "Graphics/Renderable/SceneAreaInterface.hpp"
#include "Graphics/Renderable/SeaLevelInterface.hpp"
#include "Graphics/Renderer.hpp"
#include "Resources/Manager.hpp"
#include "PrimaryServices.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Graphics;

	const size_t Manager::ClassUID{getClassUID(ClassId)};

	Manager::Manager (PrimaryServices & primaryServices, Resources::Manager & resourceManager, Renderer & graphicsRenderer, Audio::Manager & audioManager) noexcept
		: ServiceInterface(ClassId),
		m_primaryServices(primaryServices),
		m_resourceManager(resourceManager),
		m_graphicsRenderer(graphicsRenderer),
		m_audioManager(audioManager)
	{

	}

	bool
	Manager::onInitialize () noexcept
	{
		m_flags[ServiceInitialized] = true;

		return true;
	}

	bool
	Manager::onTerminate () noexcept
	{
		m_flags[ServiceInitialized] = false;

		this->deleteAllScenes();

		return true;
	}

	std::shared_ptr< Scene >
	Manager::newScene (const std::string & sceneName, float boundary, const std::shared_ptr< Renderable::AbstractBackground > & background, const std::shared_ptr< Renderable::SceneAreaInterface > & sceneArea, const std::shared_ptr< Renderable::SeaLevelInterface > & seaLevel) noexcept
	{
		if ( this->hasSceneNamed(sceneName) )
		{
			TraceError{ClassId} << "A scene named '" << sceneName << "' already exists ! Delete it first or enable it.";

			return nullptr;
		}

		auto newScene = std::make_shared< Scene >(m_graphicsRenderer, m_audioManager, sceneName, boundary, background, sceneArea, seaLevel);

		this->notify(SceneCreated, newScene);

		return m_scenes.emplace(sceneName, newScene).first->second;
	}

	Manager::SceneLoading
	Manager::loadScene (const std::string & resourceName) noexcept
	{
		/* Loads the scene definition from store (direct loading) */
		const auto sceneDefinition = m_resourceManager.sceneDefinitions().getResource(resourceName, false);

		if ( sceneDefinition == nullptr )
		{
			TraceError{ClassId} << "There is no scene named '" << resourceName << "' in store ! Loading cancelled ...";

			return {nullptr, nullptr};
		}

		/* If everything ok, let the scene definition load method continuing the job. */
		return this->loadScene(sceneDefinition);
	}

	Manager::SceneLoading
	Manager::loadScene (const std::filesystem::path & filepath) noexcept
	{
		/* Creates a new resource for the scene definition. */
		auto sceneDefinition = m_resourceManager
			.sceneDefinitions()
			.createResource(filepath.stem().string());

		if ( sceneDefinition == nullptr )
		{
			TraceError{ClassId} << "Unable to create the new scene '" << filepath.stem() << "' ! Loading cancelled ...";

			return {nullptr, nullptr};
		}

		/* Loads the scene definition from the file. */
		if ( !sceneDefinition->load(filepath) )
		{
			TraceError{ClassId} << "Unable to load Definition from '" << filepath << "' file ! Loading cancelled ...";

			return {nullptr, sceneDefinition};
		}

		/* If everything ok, let the scene definition load method continuing the job. */
		return this->loadScene(sceneDefinition);
	}

	Manager::SceneLoading
	Manager::loadScene (const std::shared_ptr< DefinitionResource > & sceneDefinition) noexcept
	{
		const auto sceneName = sceneDefinition->getSceneName();

		/* Creating a new scene in the manager and build with the definition. */
		auto scene = this->newScene(sceneName, DefaultSceneBoundary);

		if ( scene == nullptr )
		{
			TraceError{ClassId} << "Unable to create scene '" << sceneName << "' !";

			return {nullptr, sceneDefinition};
		}

		/* Load the standard scene definition. */
		if ( !sceneDefinition->buildScene(*scene) )
		{
			TraceError{ClassId} << "Unable to build scene '" << sceneName << "' from definition ! Loading cancelled ...";

			return {nullptr, sceneDefinition};
		}

		this->notify(SceneLoaded, scene);

		return {scene, sceneDefinition};
	}

	void
	Manager::refreshScenes () const noexcept
	{
		for ( const auto & scene : std::ranges::views::values(m_scenes) )
		{
			TraceInfo{ClassId} << "Refreshing scene '" << scene->name() << "' ...";

			for ( const auto & renderTarget : scene->masterControlConsole().renderToViews() )
			{
				scene->refreshRenderableInstances(renderTarget);
			}
		}
	}

	bool
	Manager::deleteScene (const std::string & sceneName) noexcept
	{
		const auto sceneIt = m_scenes.find(sceneName);

		if ( sceneIt == m_scenes.end() )
		{
			TraceError{ClassId} << "Scene '" << sceneName << "' doesn't exist and so can't be deleted !";

			return false;
		}

		/* NOTE: Disable the scene, if this is the one being deleted. */
		if ( m_activeScene == sceneIt->second )
		{
			this->disableActiveScene();
		}

		m_scenes.erase(sceneIt);

		this->notify(SceneDestroyed);

		return true;
	}

	void
	Manager::deleteAllScenes () noexcept
	{
		if ( m_scenes.empty() )
		{
			return;
		}

		/* First, disable the possible current active scene. */
		this->disableActiveScene();

		for ( auto sceneIt = m_scenes.cbegin(); sceneIt != m_scenes.cend(); )
		{
			if ( sceneIt->second.use_count() > 1 )
			{
				TraceError{ClassId} << "The scene '" << sceneIt->first << "' smart pointer still have " << sceneIt->second.use_count() << " uses ! Force a call to Scene::destroy().";

				sceneIt->second->destroy();
			}
			else
			{
				TraceSuccess{ClassId} << "Removing scene '" << sceneIt->first << "' ...";
			}

			m_scenes.erase(sceneIt++);
		}

		this->notify(SceneDestroyed);
	}

	bool
	Manager::enableScene (const std::shared_ptr< Scene > & scene) noexcept
	{
		if ( m_activeScene != nullptr )
		{
			TraceWarning{ClassId} << "The scene '" << m_activeScene->name() << "' is still active. Disable it before !";

			return false;
		}

		/* NOTE: Be sure the active is not currently used within the rendering or the logics update tasks. */
		const std::unique_lock< std::shared_mutex > activeSceneLock{m_activeSceneAccess};

		if ( scene == nullptr )
		{
			Tracer::error(ClassId, "The scene pointer is null !");

			return false;
		}

		/* Checks whether the scene is usable and tries to complete it otherwise. */
		if ( !scene->initialize(m_primaryServices.settings()) )
		{
			TraceError{ClassId} << "Unable to initialize the scene '" << scene->name() << "' !";

			return false;
		}

		m_activeScene = scene;

		/* Send out a message that scene has been activated. */
		this->notify(SceneActivated, m_activeScene);

		TraceSuccess{ClassId} << "Scene '" << m_activeScene->name() << "' loaded !";

		return true;
	}

	bool
	Manager::disableActiveScene () noexcept
	{
		if ( m_activeScene == nullptr )
		{
			return false;
		}

		/* NOTE: Be sure the active is not currently used within the rendering or the logics update tasks. */
		const std::unique_lock< std::shared_mutex > activeSceneLock{m_activeSceneAccess};

		m_activeScene->shutdown();

		/* Send out a message that scene has been deactivated. */
		this->notify(SceneDeactivated, m_activeScene);

		m_activeScene.reset();

		return true;
	}

	std::vector< std::string >
	Manager::getSceneNameList () const noexcept
	{
		if ( m_scenes.empty() )
		{
			return {};
		}

		std::vector< std::string > names;

		std::ranges::transform(m_scenes, std::back_inserter(names), [] (const auto & sceneIt) -> std::string {
			return sceneIt.first;
		});

		return names;
	}

	std::shared_ptr< Scene >
	Manager::getScene (const std::string & sceneName) noexcept
	{
		const auto sceneIt = m_scenes.find(sceneName);

		if ( sceneIt == m_scenes.end() )
		{
			return nullptr;
		}

		return sceneIt->second;
	}

	std::shared_ptr< const Scene >
	Manager::getScene (const std::string & sceneName) const noexcept
	{
		const auto sceneIt = m_scenes.find(sceneName);

		if ( sceneIt == m_scenes.cend() )
		{
			return nullptr;
		}

		return sceneIt->second;
	}
}
