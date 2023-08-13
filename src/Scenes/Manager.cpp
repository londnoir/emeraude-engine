/*
 * Emeraude/Scenes/Manager.cpp
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

#include "Manager.hpp"

/* Local inclusions. */
#include "Tracer.hpp"
#include "Argument.hpp"
#include "Settings.hpp"
#include "Resources/Manager.hpp"
#include "Graphics/Renderer.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Graphics;

	const size_t Manager::ClassUID{Observable::getClassUID()};

	Manager::Manager (const Arguments & arguments, Settings & coreSettings, Settings & applicationSettings, Resources::Manager & resourceManager, Graphics::Renderer & renderer) noexcept
		: ServiceInterface(ClassId), m_arguments(arguments), m_coreSettings(coreSettings), m_applicationSettings(applicationSettings), m_resourceManager(resourceManager), m_renderer(renderer)
	{

	}

	bool
	Manager::onInitialize () noexcept
	{
		OctreeSector::enableAutoExpand(m_coreSettings.getAs< bool >(AutoExpandEnabledKey, DefaultAutoExpandEnabled));
		OctreeSector::setAutoExpandAt(m_coreSettings.getAs< uint32_t >(AutoExpandAtKey, DefaultAutoExpandAt));

		return true;
	}

	bool
	Manager::onTerminate () noexcept
	{
		this->deleteAllScenes();

		return true;
	}

	bool
	Manager::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	Manager::usable () const noexcept
	{
		return true;
	}

	bool
	Manager::hasSceneNamed (const std::string & sceneName) const noexcept
	{
		return m_scenes.contains(sceneName);
	}

	std::shared_ptr< Scene >
	Manager::newScene (const std::string & sceneName, float boundary, const std::shared_ptr< Renderable::AbstractBackground > & background, const std::shared_ptr< Renderable::AbstractSceneArea > & sceneArea, const std::shared_ptr< Renderable::AbstractSeaLevel > & seaLevel) noexcept
	{
		if ( this->hasSceneNamed(sceneName) )
		{
			TraceError{ClassId} << "A scene named '" << sceneName << "' already exists ! Delete it first or enable it.";

			return nullptr;
		}

		auto newScene = std::make_shared< Scene >(sceneName, boundary, background, sceneArea, seaLevel);

		this->notify(SceneCreated, newScene);

		return m_scenes.emplace(sceneName, newScene).first->second;
	}

	Manager::SceneLoading
	Manager::loadScene (const std::string & resourceName) noexcept
	{
		/* Loads the scene definition from store (direct loading) */
		auto sceneDefinition = m_resourceManager.sceneDefinitions().getResource(resourceName, true);

		if ( sceneDefinition == nullptr )
		{
			TraceError{ClassId} << "There is no scene named '" << resourceName << "' in store ! Loading cancelled ...";

			return {nullptr, nullptr};
		}

		/* If everything ok, let the scene definition load method continuing the job. */
		return this->loadScene(sceneDefinition);
	}

	Manager::SceneLoading
	Manager::loadScene (const Path::File & filepath) noexcept
	{
		/* Creates a new resource for the scene definition. */
		auto sceneDefinition = m_resourceManager
			.sceneDefinitions()
			.createResource(filepath.getFilename());

		if ( sceneDefinition == nullptr )
		{
			TraceError{ClassId} << "Unable to create the new scene '" << filepath.getFilename() << "' ! Loading cancelled ...";

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
		auto sceneName = sceneDefinition->getSceneName();

		/* Creating a new scene in the manager and build with the definition. */
		auto scene = this->newScene(sceneName, 1024.0F);

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

	bool
	Manager::refreshScenes () const noexcept
	{
		if ( m_scenes.empty() )
		{
			Tracer::warning(ClassId, "There is no scene to refresh !");

			return false;
		}

		for ( const auto & scenePair : m_scenes )
		{
			const auto & scene = scenePair.second;

			TraceInfo{ClassId} << "Refreshing scene '" << scene->name() << "' ...";

			//scene->masterControlConsole().

			for ( const auto & renderTarget : scene->masterControlConsole().renderToViews() )
				scene->refreshRenderableInstances(renderTarget);
		}

		return true;
	}

	bool
	Manager::deleteScene (const std::string & sceneName) noexcept
	{
		auto sceneIt = m_scenes.find(sceneName);

		if ( sceneIt == m_scenes.end() )
		{
			TraceError{ClassId} << "Scene '" << sceneName << "' doesn't exist and so can't be deleted !";

			return false;
		}

		/* NOTE: Disable the scene, if this is the one being deleted. */
		if ( m_activeScene == sceneIt->second )
			this->disableScene();

		m_scenes.erase(sceneIt);

		this->notify(SceneDestroyed);

		return true;
	}

	void
	Manager::deleteAllScenes () noexcept
	{
		Tracer::info(ClassId, "Deleting all scenes !");

		this->disableScene();

		if ( m_activeScene != nullptr )
			Tracer::error(ClassId, "An active scene still pointed by the manager ! Something goes wrong when disabling the active scene.");

		for ( const auto & scene : m_scenes )
		{
			const auto useCount = scene.second.use_count();

			if ( useCount > 1 )
			{
				TraceError{ClassId} << "The scene '" << scene.first << "' smart pointer still have " << useCount << " uses !";
			}
		}

		m_scenes.clear();

		this->notify(SceneDestroyed);
	}

	bool
	Manager::enableScene (const std::shared_ptr< Scene > & scene) noexcept
	{
		if ( scene == nullptr )
		{
			Tracer::error(ClassId, "The scene pointer is null !");

			return false;
		}

		/* Disable the previous active scene. */
		if ( !this->disableScene() )
			Tracer::info(ClassId, "No previous scene was active.");

		/* Checks whether the scene is usable and tries to complete it otherwise. */
		if ( !scene->initialize(m_coreSettings, m_renderer) )
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
	Manager::disableScene () noexcept
	{
		if ( m_activeScene == nullptr )
			return false;

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
			return {};

		std::vector< std::string > names{};

		std::transform(m_scenes.cbegin(), m_scenes.cend(), std::back_inserter(names), [] (const auto & sceneIt) -> std::string {
			return sceneIt.first;
		});

		return names;
	}

	std::shared_ptr< Scene >
	Manager::getScene (const std::string & sceneName) noexcept
	{
		const auto sceneIt = m_scenes.find(sceneName);

		if ( sceneIt == m_scenes.end() )
			return nullptr;

		return sceneIt->second;
	}

	std::shared_ptr< const Scene >
	Manager::getScene (const std::string & sceneName) const noexcept
	{
		const auto sceneIt = m_scenes.find(sceneName);

		if ( sceneIt == m_scenes.cend() )
			return nullptr;

		return sceneIt->second;
	}

	std::shared_ptr< Scene >
	Manager::activeScene () noexcept
	{
		return m_activeScene;
	}

	bool
	Manager::hasActiveScene () const noexcept
	{
		return m_activeScene != nullptr;
	}
}
