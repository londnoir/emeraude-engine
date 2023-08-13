/*
 * Emeraude/Scenes/Scene.cpp
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

#include "Scene.hpp"

/* C/C++ standard libraries. */
#include <thread>

/* Local inclusions. */
#include "Graphics/Renderer.hpp"
#include "NodeCrawler.hpp"
#include "OctreeSector.hpp"
#include "OctreeSectorCrawler.hpp"
#include "Tracer.hpp"
#include "Vulkan/SwapChain.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Libraries::PixelFactory;
	using namespace Graphics;
	using namespace Saphir;
	using namespace Physics;

	const size_t Scene::ClassUID{Observable::getClassUID()};
	const std::string Scene::DefaultOctreeName{"DefaultOctree"};

	Scene::Scene (const std::string & name, float boundary, const std::shared_ptr< Renderable::AbstractBackground > & background, const std::shared_ptr< Renderable::AbstractSceneArea > & sceneArea, const std::shared_ptr< Renderable::AbstractSeaLevel > & seaLevel) noexcept
		: NamedItem(name),
		  m_masterControlConsole(name),
		  m_rootNode(std::make_shared< Node >(this)),
		  m_background(background),
		  m_sceneArea(sceneArea),
		  m_seaLevel(seaLevel),
		  m_boundary(boundary)
	{
		this->observe(&m_masterControlConsole);
		this->observe(m_rootNode.get());

		this->buildOctree(DefaultOctreeName);

		TraceInfo{ClassId} << "The scene '" << this->name() << "' is constructed !";
	}

	Scene::~Scene ()
	{
		this->clear();

		m_lightSet.clear();
		m_masterControlConsole.clear();

		TraceInfo{ClassId} << "The scene '" << this->name() << "' is destructed !";
	}

	void
	Scene::registerSceneVisualComponents (Renderer & renderer) noexcept
	{
		m_sceneVisualComponents.clear();

		if ( m_background != nullptr )
		{
			auto result = m_sceneVisualComponents.emplace_back(std::make_shared< VisualComponent >("Background", *m_rootNode, m_background));

			/* NOTE: Disables lighting model on the background.
			 * FIXME: Check to disable at construct time */
			auto * renderableInstance = result->getRenderableInstance();
			renderableInstance->setReceivingLights(false);
			renderableInstance->setReceiveShadows(false);
			renderableInstance->setUseInfinityView(true);
			renderableInstance->disableDepthTest(true);
			renderableInstance->disableDepthWrite(true);

			this->checkRenderableInstance(renderer, renderableInstance);
		}

		if ( m_sceneArea != nullptr )
		{
			auto result = m_sceneVisualComponents.emplace_back(std::make_shared< VisualComponent >("SceneArea", *m_rootNode, m_sceneArea));

			auto * renderableInstance = result->getRenderableInstance();

			this->checkRenderableInstance(renderer, renderableInstance);
		}

		if ( m_seaLevel != nullptr )
		{
			auto result = m_sceneVisualComponents.emplace_back(std::make_shared< VisualComponent >("SeaLevel", *m_rootNode, m_seaLevel));

			auto * renderableInstance = result->getRenderableInstance();

			this->checkRenderableInstance(renderer, renderableInstance);
		}
	}

	bool
	Scene::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	void
	Scene::setBoundary (float boundary) noexcept
	{
		m_boundary = std::abs(boundary);

		/*if ( m_sceneArea != nullptr )
			m_sceneArea->setBoundary(m_boundary);*/

		this->rebuildAllOctrees(true);
	}

	float
	Scene::boundary () const noexcept
	{
		return m_boundary;
	}

	float
	Scene::size () const noexcept
	{
		return m_boundary * 2;
	}

	bool
	Scene::initializeBaseComponents () noexcept
	{
		auto hasCamera = false;
		auto hasMicrophone = false;

		{
			NodeCrawler< const Node > crawler(m_rootNode);

			std::shared_ptr< const Node > currentNode;

			while ( (currentNode = crawler.nextNode()) != nullptr )
			{
				for ( const auto & component : currentNode->components() )
				{
					if ( std::dynamic_pointer_cast< Camera >(component.second) != nullptr )
					{
						hasCamera = true;
					}
					else if ( std::dynamic_pointer_cast< Microphone >(component.second) != nullptr )
					{
						hasMicrophone = true;
					}
				}

				/* Stop looking in the node tree if at least
				 * one camera and one microphone are found. */
				if ( hasCamera && hasMicrophone )
				{
					return true;
				}
			}
		}

		if ( !hasCamera )
		{
			Tracer::warning(ClassId, "There is no camera in the scene ! Creating a default camera ...");

			const std::string name{"DefaultCamera"};

			if ( m_rootNode->createSubNode(name + "Node")->newCamera(name, true) == nullptr )
			{
				Tracer::error(ClassId, "Scene initialization error : Unable to create a default camera !");

				return false;
			}
		}

		if ( !hasMicrophone )
		{
			Tracer::warning(ClassId, "There is no microphone in the scene ! Creating a default microphone ...");

			const std::string name{"DefaultMicrophone"};

			if ( m_rootNode->createSubNode(name + "Node")->newMicrophone(name, true) == nullptr )
			{
				Tracer::error(ClassId, "Scene initialization error : Unable to create a default microphone !");

				return false;
			}
		}

		return true;
	}

	bool
	Scene::initialize (Settings & coreSettings, Renderer & renderer) noexcept
	{
		this->registerSceneVisualComponents(renderer);

		/* Create missing camera and/or microphone. */
		if ( !this->initializeBaseComponents() )
		{
			return false;
		}

		{
			Tracer::info(ClassId, "Initializing the scene master control ...");

			const auto & swapChain = renderer.swapChain();

			if ( swapChain != nullptr )
			{
				m_masterControlConsole.addVideoDevice(swapChain, true);
			}

			if ( !m_masterControlConsole.autoConnectPrimaryVideoDevices(coreSettings) )
			{
				TraceError{ClassId} <<
					"Unable to auto-connect primary video devices !" "\n" <<
					m_masterControlConsole.getConnexionStates();

				return false;
			}

			TraceSuccess{ClassId} <<
				"Initial device connexions :" "\n" <<
				m_masterControlConsole.getConnexionStates();
		}

		return true;
	}

	void
	Scene::shutdown () noexcept
	{
		/* Disconnect all audio/video devices from master control. */
		/* FIXME: Check for the main output. */
	}

	void
	Scene::setPhysicalEnvironmentProperties (const PhysicalEnvironmentProperties & properties) noexcept
	{
		m_physicalEnvironmentProperties = properties;
	}

	std::shared_ptr< StaticEntity >
	Scene::createStaticEntity (const std::string & name, const Coordinates< float > & coordinates) noexcept
	{
		auto staticEntity = std::make_shared< StaticEntity >(name, this, coordinates);

		m_staticEntities.emplace(name, staticEntity);

		/* Adds the entity to the default octree if enabled */
		{
			auto defaultOctree = this->getDefaultOctree();

			if ( defaultOctree != nullptr )
			{
				defaultOctree->addElement(staticEntity);
			}
		}

		this->notify(StaticCreated, staticEntity);

		this->observe(staticEntity.get());

		return staticEntity;
	}

	bool
	Scene::removeStaticEntity (const std::string & name) noexcept
	{
		/* Fist, check the presence of the entity in the list. */
		auto staticEntityIt = m_staticEntities.find(name);

		if ( staticEntityIt == m_staticEntities.end() )
		{
			return false;
		}

		auto staticEntity = staticEntityIt->second;

		this->forget(staticEntity.get());

		this->notify(StaticDeleting, staticEntity);

		/* Remove the entity from scene area, then from scene entity list. */
		{
			auto defaultOctree = this->getDefaultOctree();

			if ( defaultOctree != nullptr )
			{
				defaultOctree->removeElement(staticEntity);
			}
		}

		m_staticEntities.erase(staticEntityIt);

		this->notify(StaticDeleted);

		return true;
	}

	void
	Scene::addEnvironmentEffect (const std::shared_ptr< EffectInterface > & effect) noexcept
	{
		/* We don't want to notify an effect twice. */
		if ( m_environmentEffects.find(effect) != m_environmentEffects.cend() )
		{
			return;
		}

		m_environmentEffects.emplace(effect);
	}

	bool
	Scene::isEnvironmentEffectPresent (const std::shared_ptr< EffectInterface > & effect) const noexcept
	{
		return m_environmentEffects.find(effect) != m_environmentEffects.cend();
	}

	void
	Scene::clearEnvironmentEffects () noexcept
	{
		m_environmentEffects.clear();
	}

	void
	Scene::clear () noexcept
	{
		/* NOTE: Clean the master control console. */
		m_masterControlConsole.clear();

		/* First, clear properly the octree system before removing the scene content. */
		this->destroyAllOctrees();

		m_sceneVisualComponents.clear();
		m_environmentEffects.clear();
		m_modifiers.clear();
		m_staticEntities.clear();
		this->resetNodeTree();
		m_seaLevel.reset();
		m_background.reset();
		m_sceneArea.reset();
	}

	bool
	Scene::defaultOctreeEnabled () const noexcept
	{
		const std::lock_guard< std::mutex > lock{m_octreesMutex};

		return m_octrees.contains(DefaultOctreeName);
	}

	std::shared_ptr< OctreeSector >
	Scene::getDefaultOctree () noexcept
	{
		const std::lock_guard< std::mutex > lock{m_octreesMutex};

		auto octreeIt = m_octrees.find(DefaultOctreeName);

		if ( octreeIt == m_octrees.end() )
		{
			return nullptr;
		}

		return octreeIt->second;
	}

	std::shared_ptr< OctreeSector >
	Scene::getOctree (const std::string & octreeName) noexcept
	{
		const std::lock_guard< std::mutex > lock{m_octreesMutex};

		auto octreeIt = m_octrees.find(octreeName);

		if ( octreeIt == m_octrees.end() )
		{
			return nullptr;
		}

		return octreeIt->second;
	}

	std::shared_ptr< OctreeSector >
	Scene::createOctreeRootSector () const noexcept
	{
		if ( m_boundary <= 0.0F )
		{
			Tracer::error(ClassId, "The scene boundary is null ! Unable to create an octree root sector !");

			return nullptr;
		}

		return std::make_shared< OctreeSector >(
			Vector< 3, float >{m_boundary, m_boundary, m_boundary},
			Vector< 3, float >{-m_boundary, -m_boundary, -m_boundary}
		);
	}

	std::shared_ptr< OctreeSector >
	Scene::buildOctree (const std::string & octreeName) noexcept
	{
		const std::lock_guard< std::mutex > lock{m_octreesMutex};

		if ( m_octrees.contains(octreeName) )
		{
			TraceWarning{ClassId} << "An octree named '" << octreeName << "' already exists !";

			return nullptr;
		}

		/* Allocate the root sector using the scene boundary. */
		auto octree = this->createOctreeRootSector();

		if ( octree == nullptr )
		{
			return nullptr;
		}

		m_octrees.emplace(octreeName, octree);

		return octree;
	}

	bool
	Scene::destroyOctree (const std::string & octreeName) noexcept
	{
		const std::lock_guard< std::mutex > lock{m_octreesMutex};

		auto octreeIt = m_octrees.find(octreeName);

		if ( octreeIt == m_octrees.end() )
		{
			TraceWarning{ClassId} << "There is no octree named '" << octreeName << "' to destroy !";

			return false;
		}

		/* NOTE: Destroys the tree first. As each sector as parenting,
		 * so removing simply the shared_ptr from the map won't fire the tree destruction. */
		octreeIt->second->destroyTree();

		m_octrees.erase(octreeIt);

		return true;
	}

	void
	Scene::destroyAllOctrees () noexcept
	{
		const std::lock_guard< std::mutex > lock{m_octreesMutex};

		for ( const auto & octreeIt : m_octrees )
		{
			octreeIt.second->destroyTree();
		}

		m_octrees.clear();
	}

	bool
	Scene::rebuildOctree (const std::string & octreeName, bool keepElements) noexcept
	{
		const std::lock_guard< std::mutex > lock{m_octreesMutex};

		auto octreeIt = m_octrees.find(octreeName);

		if ( octreeIt == m_octrees.end() )
		{
			TraceWarning{ClassId} << "There is no sector layer named '" << octreeName << "' to rebuild !";

			return false;
		}

		return this->rebuildOctree(octreeIt, keepElements);
	}

	void
	Scene::rebuildAllOctrees (bool keepElements) noexcept
	{
		const std::lock_guard< std::mutex > lock{m_octreesMutex};

		for ( auto octreeLayerIt = m_octrees.begin(); octreeLayerIt != m_octrees.end(); ++octreeLayerIt )
		{
			this->rebuildOctree(octreeLayerIt, keepElements);
		}
	}

	bool
	Scene::rebuildOctree (const std::map< std::string, std::shared_ptr< Scenes::OctreeSector > >::iterator & octreeIt, bool keepElements) noexcept
	{
		/* Allocate a new octree. */
		auto octree = this->createOctreeRootSector();

		if ( octree == nullptr )
		{
			return false;
		}

		/* Transfer all elements from the previous octree (root sector) to the new one. */
		if ( keepElements )
		{
			for ( const auto & element : octreeIt->second->elements() )
			{
				octree->addElement(element);
			}
		}

		octreeIt->second.reset();
		octreeIt->second = octree;

		return true;
	}

	/* FIXME: Seems an old and useless function. */
	bool
	Scene::insertSceneElementsToOctree (const std::shared_ptr< Scenes::OctreeSector > & octree) noexcept
	{
		/* FIXME: Check for getting the root sector if useful. */
		if ( !octree->isRoot() )
		{
			Tracer::error(ClassId, "This sector is not the root of the octree !");

			return false;
		}

		/* Insert all existing nodes. */
		if ( m_rootNode != nullptr )
		{
			/* NOTE: Prevent scene node deletion from logic update thread to crash the rendering. */
			const std::lock_guard< std::mutex > lock{m_sceneNodesMutex};

			NodeCrawler< Node > crawler(m_rootNode);

			std::shared_ptr< Node > currentNode;

			while ( (currentNode = crawler.nextNode()) != nullptr )
			{
				/* Check whether the scene node contains something to render. */
				if ( !currentNode->isRenderable() )
				{
					continue;
				}

				octree->addElement(currentNode);
			}
		}

		/* Insert all existing static entities. */
		if ( !m_staticEntities.empty() )
		{
			const std::lock_guard< std::mutex > lock{m_staticEntitiesMutex};

			for ( auto & entityPair : m_staticEntities )
			{
				octree->addElement(entityPair.second);
			}
		}

		return true;
	}

	void
	Scene::resetNodeTree () noexcept
	{
		const std::lock_guard< std::mutex > lock{m_sceneNodesMutex};

		m_rootNode->destroyTree();
	}

	void
	Scene::processLogics (size_t cycle) noexcept
	{
		/* Update scene static entity logics. */
		{
			const std::lock_guard< std::mutex > lock{m_staticEntitiesMutex};

			for ( auto & staticEntity : m_staticEntities )
			{
				staticEntity.second->processLogics(*this, cycle);
			}
		}

		/* Update scene node logics. */
		{
			const std::lock_guard< std::mutex > lock{m_sceneNodesMutex};

			NodeCrawler< Node > crawler(m_rootNode);

			std::shared_ptr< Node > currentNode;

			auto defaultOctree = this->getDefaultOctree();

			while ( (currentNode = crawler.nextNode()) != nullptr )
			{
				if ( !currentNode->processLogics(*this, cycle) )
				{
					continue;
				}

				/* If the scene node moved, we check it with the scene area. */
				if ( defaultOctree != nullptr )
				{
					defaultOctree->checkElementOverlap(currentNode);
				}
			}

			/* Clean all dead nodes. */
			m_rootNode->cleanTree();
		}

		/* Launch the collision test step. */
		if ( m_octrees.empty() )
		{
			// TODO: Performs collisions without tree acceleration ...
		}
		else
		{
			for ( const auto & octreeItem : m_octrees )
			{
				std::array< size_t, 3 > stats{0UL, 0UL, 0UL};

				//unsigned long int time = 0;

				{
					//Time::ScopeElapsedTime stat(time);

					this->sectorCollisionTest(*octreeItem.second, stats);
				}

				//std::cout << "Resolutions (" << time << " µs): " << stats[2] << ", tests: " << stats[0] << ", sub-tests " << stats[1] << "." << std::endl;
			}
		}
	}

	void
	Scene::sectorCollisionTest (const OctreeSector & sector, std::array< size_t, 3 > & stats) noexcept // NOLINT(misc-no-recursion)
	{
		/* If no scene node here, we stop this branch. */
		if ( sector.elements().empty() )
		{
			return;
		}

		/* If sector is not a leaf, we test sub-sectors. */
		if ( !sector.isLeaf() )
		{
			//#pragma omp parallel for
			for ( const auto & subSector : sector.subSectors() )
			{
				this->sectorCollisionTest(*subSector, stats);
			}

			return;
		}

		/* We are in a leaf, we check scene nodes present here. */
		const auto & elements = sector.elements();

		for ( auto elementIt = elements.begin(); elementIt != elements.end(); ++elementIt )
		{
			const auto & elementA = *elementIt;

			if ( !elementA->hasPhysicalObjectProperties() )
			{
				continue;
			}

			auto nodeA = std::dynamic_pointer_cast< Node >(elementA);

			/* If not a node or the no clipping mode enabled or node is not moving. We skip the check. */
			if ( nodeA == nullptr || nodeA->isNoClippingModeEnabled() || !nodeA->isMoving() )
			{
				continue;
			}

			++stats[0];

			Collider collider{nodeA};

			/* First the scene node collision against the scene area (boundaries and ground).
			 * FIXME: Scene nodes in multiple sectors are calculated more than once against the scene area. */
			this->clip(nodeA, collider);

			/* Then test collisions against all other scene nodes present in the sector. */
			auto elementItCopy = elementIt;

			for ( ++elementItCopy; elementItCopy != elements.end(); ++elementItCopy )
			{
				const auto & elementB = *elementItCopy;

				if ( !elementB->hasPhysicalObjectProperties() )
				{
					continue;
				}

				auto nodeB = std::dynamic_pointer_cast< Node >(elementB);

				/* FIXME: For now we are totally ignoring static stuffs ! */
				if ( nodeB == nullptr || nodeB->isNoClippingModeEnabled() )
				{
					continue;
				}

				++stats[1];

				collider.checkCollision(nodeB.get());
			}

			if ( !collider.collisionManifold().hitSomething() )
			{
				continue;
			}

			collider.resolveCollisions();

			++stats[2];
		}
	}

	void
	Scene::clip (const std::shared_ptr< Node > & node, Collider & collider) const noexcept
	{
		auto & collisionManifold = collider.collisionManifold();

		if ( node->sphereCollisionIsEnabled() )
		{
			/* Gets the absolute position to test against the scene boundaries. */
			const auto worldPosition = node->getWorldCoordinates().position();

			if ( m_sceneArea != nullptr )
			{
				const auto groundLevel = m_sceneArea->getLevelAt(worldPosition) - node->getWorldBoundingSphere().radius() - CollisionCorrectionDistance;

				if ( worldPosition[Y] > groundLevel )
				{
					node->moveOnYAxisTo(groundLevel, TransformSpace::World);

					collisionManifold.addCollision(Collision::Type::SceneAreaGround, this, m_sceneArea->getNormalAt(worldPosition), 0.0F);
				}
			}

			/* Compute the max boundary. */
			const auto boundaryLimit = m_boundary - node->getWorldBoundingSphere().radius() - CollisionCorrectionDistance;

			/* X-Axis test. */
			if ( std::abs(worldPosition[X]) > boundaryLimit )
			{
				/* Reset position in scene boundaries. */
				if ( worldPosition[X] > boundaryLimit )
				{
					node->moveOnXAxisTo(boundaryLimit, TransformSpace::World);

					collisionManifold.addCollision(Collision::Type::SceneAreaBoundaries, this, Vector< 3, float >::negativeX(), 0.0F);
				}
				else
				{
					node->moveOnXAxisTo(-boundaryLimit, TransformSpace::World);

					collisionManifold.addCollision(Collision::Type::SceneAreaBoundaries, this, Vector< 3, float >::positiveX(), 0.0F);
				}
			}

			/* Y-Axis test. */
			if ( std::abs(worldPosition[Y]) > boundaryLimit )
			{
				if ( worldPosition[Y] > boundaryLimit )
				{
					node->moveOnYAxisTo(boundaryLimit, TransformSpace::World);

					collisionManifold.addCollision(Collision::Type::SceneAreaBoundaries, this, Vector< 3, float >::negativeY(), 0.0F);
				}
				else
				{
					node->moveOnYAxisTo(-boundaryLimit, TransformSpace::World);

					collisionManifold.addCollision(Collision::Type::SceneAreaBoundaries, this, Vector< 3, float >::positiveY(), 0.0F);
				}
			}

			/* Z-Axis test. */
			if ( std::abs(worldPosition[Z]) > boundaryLimit )
			{
				if ( worldPosition[Z] > boundaryLimit )
				{
					node->moveOnZAxisTo(boundaryLimit, TransformSpace::World);

					collisionManifold.addCollision(Collision::Type::SceneAreaBoundaries, this, Vector< 3, float >::negativeZ(), 0.0F);
				}
				else
				{
					node->moveOnZAxisTo(-boundaryLimit, TransformSpace::World);

					collisionManifold.addCollision(Collision::Type::SceneAreaBoundaries, this, Vector< 3, float >::positiveZ(), 0.0F);
				}
			}
		}
		else
		{
			const auto & AABB = node->getWorldBoundingBox();

			/* Running the subtest first. */
			if ( m_sceneArea != nullptr )
			{
				/* Gets the four points of the bottom of the box. */
				std::array< Vector< 3, float >, 4 > points{
					AABB.bottomSouthEast(),
					AABB.bottomSouthWest(),
					AABB.bottomNorthWest(),
					AABB.bottomNorthEast()
				};

				/* These will keep the deepest collision of the four points. */
				Vector< 3, float > * collisionPosition = nullptr;
				auto highestDistance = 0.0F;

				for ( auto & position : points )
				{
					const auto groundLevel = m_sceneArea == nullptr ? -m_boundary : m_sceneArea->getLevelAt(position);

					const auto distance = groundLevel - position[Y];

					if ( distance > highestDistance )
					{
						collisionPosition = &position;
						highestDistance = distance;
					}
				}

				if ( collisionPosition != nullptr )
				{
					node->moveOnYAxisBy(highestDistance + CollisionCorrectionDistance, TransformSpace::World);

					collisionManifold.addCollision(Collision::Type::SceneAreaGround, this, m_sceneArea->getNormalAt(*collisionPosition), 0.0F);
				}
			}

			/* X-Axis test */
			if ( AABB.maximum(X) > m_boundary )
			{
				auto delta = (AABB.maximum(X) - m_boundary) + CollisionCorrectionDistance;

				node->moveOnXAxisBy(-delta, TransformSpace::World);

				collisionManifold.addCollision(Collision::Type::SceneAreaBoundaries, this, Vector< 3, float >::negativeX(), 0.0F);
			}
			else if ( AABB.minimum(X) < -m_boundary )
			{
				auto delta = (std::abs(AABB.minimum(X)) - m_boundary) + CollisionCorrectionDistance;

				node->moveOnXAxisBy(delta, TransformSpace::World);

				collisionManifold.addCollision(Collision::Type::SceneAreaBoundaries, this, Vector< 3, float >::positiveX(), 0.0F);
			}

			/* Y-Axis test */
			if ( AABB.maximum(Y) > m_boundary )
			{
				auto delta = (AABB.maximum(Y) - m_boundary) + CollisionCorrectionDistance;

				node->moveOnYAxisBy(-delta, TransformSpace::World);

				collisionManifold.addCollision(Collision::Type::SceneAreaBoundaries, this, Vector< 3, float >::negativeY(), 0.0F);
			}
			else if ( AABB.minimum(Y) < -m_boundary )
			{
				auto delta = (std::abs(AABB.minimum(Y)) - m_boundary) + CollisionCorrectionDistance;

				node->moveOnYAxisBy(delta, TransformSpace::World);

				collisionManifold.addCollision(Collision::Type::SceneAreaBoundaries, this, Vector< 3, float >::positiveY(), 0.0F);
			}

			/* Z-Axis test */
			if ( AABB.maximum(Z) > m_boundary )
			{
				auto delta = (AABB.maximum(Z) - m_boundary) + CollisionCorrectionDistance;

				node->moveOnZAxisBy(-delta, TransformSpace::World);

				collisionManifold.addCollision(Collision::Type::SceneAreaBoundaries, this, Vector< 3, float >::negativeZ(), 0.0F);
			}
			else if ( AABB.minimum(Z) < -m_boundary )
			{
				auto delta = (std::abs(AABB.minimum(Z)) - m_boundary) + CollisionCorrectionDistance;

				node->moveOnZAxisBy(delta, TransformSpace::World);

				collisionManifold.addCollision(Collision::Type::SceneAreaBoundaries, this, Vector< 3, float >::positiveZ(), 0.0F);
			}
		}
	}

	bool
	Scene::getRenderLists (const std::shared_ptr< RenderTarget::Abstract > & renderTarget, RenderBatch::List & opaqueRenderList, RenderBatch::List & translucentRenderList) const noexcept
	{
		opaqueRenderList.clear();
		translucentRenderList.clear();

		/* NOTE: The camera position do not move from the whole process. */
		const auto & cameraPosition = renderTarget->viewMatrices().position();
		Vector< 3, float > entityPosition{};

		/* Lambda to read components. */
		auto insertComponentInSortList = [&cameraPosition, &entityPosition, &opaqueRenderList, &translucentRenderList] (const AbstractComponent & component) -> bool {
			/* Check whether the current component is renderable in this entity. */
			if ( !component.isRenderable() )
			{
				return false;
			}

			/* This is a raw pointer to the abstract renderable instance. */
			const auto * renderableInstance = component.getRenderableInstance();

#ifdef DEBUG
			if ( renderableInstance == nullptr )
			{
				Tracer::error(ClassId, "The abstract renderable instance pointer is a null !");

				return false;
			}
#endif

			/* Check whether the renderable instance is ready to render. */
			if ( !renderableInstance->isReadyToRender() )
			{
				return false;
			}

			/* This is a raw pointer to the renderable interface. */
			const auto * renderable = renderableInstance->renderable();

#ifdef DEBUG
			if ( renderable == nullptr )
			{
				Tracer::error(ClassId, "The renderable interface pointer is a null !");

				return false;
			}

			/* Check whether the renderable is ready to draw.
			 * Only done in debug mode, because a renderable instance ready to
			 * render implies the renderable is ready to draw. */
			if ( !renderable->isReadyForInstantiation() )
			{
				return false;
			}
#endif

			const auto distance = Vector< 3, float >::distance(cameraPosition, entityPosition);
			const auto layerCount = renderable->layerCount();

			for ( size_t layerIndex = 0; layerIndex < layerCount; layerIndex++ )
			{
				RenderBatch::create(
					renderable->isOpaque(layerIndex) ? opaqueRenderList : translucentRenderList,
					distance,
					renderableInstance,
					layerIndex
				);
			}

			return false;
		};

		/* Sorting global renderable objects from the scene. */
		for ( const auto & renderable : m_sceneVisualComponents )
		{
			insertComponentInSortList(*renderable);
		}

		/* Sorting renderable objects from scene static entities. */
		{
			const std::lock_guard< std::mutex > lock{m_staticEntitiesMutex};

			for ( const auto & pair : m_staticEntities )
			{
				const auto & staticEntity = pair.second;

				/* Check whether the static entity contains something to render. */
				if ( !staticEntity->isRenderable() )
				{
					continue;
				}

				/* Prepares the entity position (costly) for the lambda. */
				entityPosition = staticEntity->getWorldCoordinates().position();

				staticEntity->forEachComponent(insertComponentInSortList);
			}
		}

		/* Sorting renderable objects from the scene node tree. */
		{
			/* NOTE: Prevent scene node deletion from logic update thread to crash the rendering. */
			const std::lock_guard< std::mutex > lock{m_sceneNodesMutex};

			NodeCrawler< const Node > crawler{m_rootNode};

			std::shared_ptr< const Node > node{};

			while ( (node = crawler.nextNode()) != nullptr )
			{
				/* Check whether the scene node contains something to render. */
				if ( !node->isRenderable() )
				{
					continue;
				}

				/* Prepares the entity position (costly) for the lambda. */
				entityPosition = node->getWorldCoordinates().position();

				node->forEachComponent(insertComponentInSortList);
			}
		}

		/* Return if something can be rendered. */
		return !opaqueRenderList.empty() || !translucentRenderList.empty();
	}

	void
	Scene::updateVideoMemoryForRendering (const std::shared_ptr< Graphics::RenderTarget::Abstract > & renderTarget) const noexcept
	{
		/* Sorting global renderable objects from the scene. */
		for ( const auto & renderable : m_sceneVisualComponents )
		{
			if ( !renderable->isRenderable() )
			{
				continue;
			}

			renderable->getRenderableInstance()->updateVideoMemoryForRendering(renderTarget);
		}

		/* Sorting renderable objects from scene static entities. */
		{
			const std::lock_guard< std::mutex > lock{m_staticEntitiesMutex};

			for ( const auto & pair : m_staticEntities )
			{
				const auto & staticEntity = pair.second;

				/* Check whether the static entity contains something to render. */
				if ( !staticEntity->isRenderable() )
				{
					continue;
				}

				for ( const auto & component : staticEntity->components() )
				{
					if ( !component.second->isRenderable() )
					{
						continue;
					}

					component.second->getRenderableInstance()->updateVideoMemoryForRendering(renderTarget);
				}
			}
		}

		/* Sorting renderable objects from the scene node tree. */
		{
			/* NOTE: Prevent scene node deletion from logic update thread to crash the rendering. */
			const std::lock_guard< std::mutex > lock{m_sceneNodesMutex};

			NodeCrawler< const Node > crawler{m_rootNode};

			std::shared_ptr< const Node > node{};

			while ( (node = crawler.nextNode()) != nullptr )
			{
				/* Check whether the scene node contains something to render. */
				if ( !node->isRenderable() )
				{
					continue;
				}

				for ( const auto & component : node->components() )
				{
					if ( !component.second->isRenderable() )
					{
						continue;
					}

					component.second->getRenderableInstance()->updateVideoMemoryForRendering(renderTarget);
				}
			}
		}
	}

	void
	Scene::castShadows (const std::shared_ptr< RenderTarget::Abstract > & renderTarget, const Vulkan::CommandBuffer & commandBuffer) noexcept
	{

	}

	void
	Scene::render (const std::shared_ptr< RenderTarget::Abstract > & renderTarget, const Vulkan::CommandBuffer & commandBuffer) const noexcept
	{
		/* NOTE: Keep lists as static to benefit of amortized constant time complexity. */
		static RenderBatch::List depthOrderRenderList;
		static RenderBatch::List reverseDepthOrderRenderList;

		if ( this->getRenderLists(renderTarget, depthOrderRenderList, reverseDepthOrderRenderList) )
		{
			/* Launching the render from the two depth ordering lists. */
			for ( const auto & renderBatch : depthOrderRenderList )
			{
				renderBatch.second.renderableInstance()->render(renderTarget, RenderPassType::SimpleWithFakeLightPass, commandBuffer);
			}

			for ( const auto & renderBatch : reverseDepthOrderRenderList )
			{
				renderBatch.second.renderableInstance()->render(renderTarget, RenderPassType::SimpleWithFakeLightPass, commandBuffer);
			}
		}
	}

	bool
	Scene::checkMasterControlConsoleNotification (int notificationCode, const std::any & data) noexcept
	{
		switch ( notificationCode )
		{
			case MasterControl::Console::VideoDeviceAdded :
				TraceDebug{ClassId} << "A new video device is available.";
				return true;

			case MasterControl::Console::VideoDeviceRemoved :
				TraceDebug{ClassId} << "A video device has been removed.";
				return true;

			case MasterControl::Console::AudioDeviceAdded :
				TraceDebug{ClassId} << "A new audio device is available.";
				return true;

			case MasterControl::Console::AudioDeviceRemoved :
				TraceDebug{ClassId} << "An audio device has been removed.";
				return true;

			case MasterControl::Console::RenderToViewAdded :
			{
				TraceDebug{ClassId} <<
					"A new render to view is available ! "
					"Updating renderable instances from the scene ...";

				auto renderToView = std::any_cast< std::shared_ptr< RenderTarget::View::Abstract > >(data);

				this->updateRenderableInstancesForRendering(*Renderer::instance(), renderToView);
			}
				return true;

			case MasterControl::Console::RenderToTextureAdded :
			{
				TraceDebug{ClassId} <<
					"A new render to texture is available ! "
					"Updating renderable instances from the scene ...";

				auto renderToTexture = std::any_cast< std::shared_ptr< RenderTarget::Texture::Abstract > >(data);

				this->updateRenderableInstancesForRendering(*Renderer::instance(), renderToTexture);
			}
				return true;

			case MasterControl::Console::RenderToShadowMapAdded :
			{
				TraceDebug{ClassId} <<
				"A new render to shadow map is available ! "
				"Updating renderable instances from the scene ...";

				auto renderToShadowMap = std::any_cast< std::shared_ptr< RenderTarget::ShadowMap::Abstract > >(data);

				this->updateRenderableInstancesForRendering(*Renderer::instance(), renderToShadowMap);
			}
				return true;

			default :
				TraceDebug{ClassId} << "Event #" << notificationCode << " from a master control console ignored.";
				return false;
		}
	}

	bool
	Scene::checkNodeNotification (const Node * observableNode, int notificationCode, const std::any & data) noexcept
	{
		switch ( notificationCode )
		{
			/* A new scene node must be registered in sectors of the current scene area. */
			case Node::NodeCreated :
			{
				auto node = std::any_cast< std::shared_ptr< Node > >(data);

				/* Add the node to the default octree, if enabled */
				{
					auto defaultOctree = this->getDefaultOctree();

					if ( defaultOctree != nullptr )
					{
						defaultOctree->addElement(node);
					}
				}

				this->notify(NodeCreated, node);
			}
				return true;

			/* When a scene node is destroyed, we want to remove it from sectors of the current scene area. */
			case Node::NodeDeleted :
			{
				auto node = std::any_cast< std::shared_ptr< Node > >(data);

				this->notify(NodeDeleting, node);

				/* Remove the node from the default octree, if enabled */
				{
					auto defaultOctree = this->getDefaultOctree();

					if ( defaultOctree != nullptr )
					{
						defaultOctree->removeElement(node);
					}
				}

				this->notify(NodeDeleted);
			}
				return true;

			default:
				TraceDebug{ClassId} << "Event #" << notificationCode << " from '" << observableNode->name() << "' ignored.";
				return false;
		}
	}

	bool
	Scene::checkEntityNotification (const AbstractEntity * observableEntity, int notificationCode, const std::any & data) noexcept
	{
		switch ( notificationCode )
		{
			/* If an entity content has been modified in the scene, we want to check the overlap from the new bounding box. */
			case AbstractEntity::ContentModified :
			{
				auto defaultOctree = this->getDefaultOctree();

				if ( defaultOctree != nullptr )
				{
					auto entity = std::any_cast< std::shared_ptr< AbstractEntity > >(data);

					defaultOctree->checkElementOverlap(entity);
				}
			}
				return true;

			case AbstractEntity::ModifierCreated :
				m_modifiers.emplace(std::any_cast< std::shared_ptr< AbstractModifier > >(data));
				return true;

			case AbstractEntity::ModifierDestroyed :
				m_modifiers.erase(std::any_cast< std::shared_ptr< AbstractModifier > >(data));
				return true;

			case AbstractEntity::CameraCreated :
				m_masterControlConsole.addVideoDevice(std::any_cast< std::shared_ptr< Camera > >(data));
				return true;

			case AbstractEntity::PrimaryCameraCreated :
				m_masterControlConsole.addVideoDevice(std::any_cast< std::shared_ptr< Camera > >(data), true);
				return true;

			case AbstractEntity::CameraDestroyed :
				m_masterControlConsole.removeVideoDevice(std::any_cast< std::shared_ptr< Camera > >(data));
				return true;

			case AbstractEntity::MicrophoneCreated :
				m_masterControlConsole.addAudioDevice(std::any_cast< std::shared_ptr< Microphone > >(data));
				return true;

			case AbstractEntity::PrimaryMicrophoneCreated :
				m_masterControlConsole.addAudioDevice(std::any_cast< std::shared_ptr< Microphone > >(data), true);
				return true;

			case AbstractEntity::MicrophoneDestroyed :
				m_masterControlConsole.removeAudioDevice(std::any_cast< std::shared_ptr< Microphone > >(data));
				return true;

			case AbstractEntity::DirectionalLightCreated :
				m_lightSet.add(std::any_cast< std::shared_ptr< DirectionalLight > >(data));
				return true;

			case AbstractEntity::DirectionalLightDestroyed :
				m_lightSet.remove(std::any_cast< std::shared_ptr< DirectionalLight > >(data));
				return true;

			case AbstractEntity::PointLightCreated :
				m_lightSet.add(std::any_cast< std::shared_ptr< PointLight > >(data));
				return true;

			case AbstractEntity::PointLightDestroyed :
				m_lightSet.remove(std::any_cast< std::shared_ptr< PointLight > >(data));
				return true;

			case AbstractEntity::SpotLightCreated :
				m_lightSet.add(std::any_cast< std::shared_ptr< SpotLight > >(data));
				return true;

			case AbstractEntity::SpotLightDestroyed :
				m_lightSet.remove(std::any_cast< std::shared_ptr< SpotLight > >(data));
				return true;

			case AbstractEntity::VisualComponentCreated :
			{
				auto component = std::any_cast< std::shared_ptr< VisualComponent > >(data);

				this->checkRenderableInstance(*Renderer::instance(), component->getRenderableInstance());
			}
				return true;

			case AbstractEntity::VisualComponentDestroyed :
			{
				auto component = std::any_cast< std::shared_ptr< VisualComponent > >(data);

				this->forget(component->getRenderableInstance());
			}
				return true;

			case AbstractEntity::MultipleVisualsComponentCreated :
			{
				auto component = std::any_cast< std::shared_ptr< MultipleVisualsComponent > >(data);

				this->checkRenderableInstance(*Renderer::instance(), component->getRenderableInstance());
			}
				return true;

			case AbstractEntity::MultipleVisualsComponentDestroyed :
			{
				auto component = std::any_cast< std::shared_ptr< MultipleVisualsComponent > >(data);

				this->forget(component->getRenderableInstance());
			}
				return true;

			default:
				TraceDebug{ClassId} << "Event #" << notificationCode << " from '" << observableEntity->name() << "' ignored.";
				return false;
		}
	}

	bool
	Scene::onNotification (const Observable * observable, int notificationCode, const std::any & data) noexcept
	{
		if ( observable == &m_masterControlConsole )
		{
			if ( this->checkMasterControlConsoleNotification(notificationCode, data) )
			{
				return true;
			}

			return true;
		}

		if ( observable->is(StaticEntity::ClassUID) )
		{
			if ( this->checkEntityNotification(dynamic_cast< const AbstractEntity * >(observable), notificationCode, data) )
			{
				return true;
			}

			return true;
		}

		if ( observable->is(Node::ClassUID) )
		{
			if ( this->checkNodeNotification(dynamic_cast< const Node * >(observable), notificationCode, data) )
			{
				return true;
			}

			/* NOTE: A node is also an entity. */
			if ( this->checkEntityNotification(dynamic_cast< const AbstractEntity * >(observable), notificationCode, data) )
			{
				return true;
			}

			/* NOTE: We never want to stop listening from the root node. */
			return true;
		}

		if ( observable->is(RenderableInstance::Abstract::ClassUID) )
		{
			switch ( notificationCode )
			{
				case RenderableInstance::Abstract::Broken :
					Tracer::error(ClassId, "The renderable instance is broken !");

					return false;

				case RenderableInstance::Abstract::ReadyToSetupOnGPU :
				{
					auto * renderableInstance = std::any_cast< RenderableInstance::Abstract * >(data);

					this->updateRenderableInstanceForRendering(*Renderer::instance(), renderableInstance);
				}
					return false;

				default:
					TraceDebug{ClassId} << "Event #" << notificationCode << " from a scene renderable instance ignored.";
					break;
			}

			return true;
		}

#ifdef DEBUG
		/* NOTE: Don't know what is it, goodbye ! */
		TraceInfo{ClassId} <<
			"Received an unhandled event from observable @" << observable << " (code:" << notificationCode << ") ! "
			"Forgetting it ...";
#endif

		return false;
	}

	void
	Scene::checkRenderableInstance (Renderer & renderer, RenderableInstance::Abstract * renderableInstance) noexcept
	{
		if ( renderableInstance == nullptr )
		{
			Tracer::error(ClassId, "The renderable instance pointer is a null !");

			return;
		}

		/* NOTE: If the renderable instance is ready to render, we can stop here. */
		if ( renderableInstance->isReadyToRender() )
		{
			return;
		}

		const auto * renderable = renderableInstance->renderable();

		if ( renderable == nullptr )
		{
			Tracer::error(ClassId, "There is no renderable in the renderable instance !");

			return;
		}

		/* NOTE: If the renderable is ready for instantiation, we configure the rendering now ... */
		if ( renderable->isReadyForInstantiation() )
		{
			this->updateRenderableInstanceForRendering(renderer, renderableInstance);
		}
		else /* ... Or we delay the update later. */
		{
			this->observe(renderableInstance);
		}
	}

	void
	Scene::updateRenderableInstanceForRendering (Renderer & renderer, RenderableInstance::Abstract * renderableInstance) const noexcept
	{
		if ( renderableInstance == nullptr )
		{
			Tracer::error(ClassId, "The renderable instance pointer is null !");

			return;
		}

		for ( const auto & renderTarget : m_masterControlConsole.renderToViews() )
		{
			if ( !renderer.getRenderableInstanceReadyForRender(*renderableInstance, renderTarget, m_lightSet) )
			{
				Tracer::error(ClassId, "The renderable instance preparation for rendering has failed !");
			}
		}
	}

	void
	Scene::updateRenderableInstancesForRendering (Renderer & renderer, const std::shared_ptr< RenderTarget::Abstract > & renderTarget) const noexcept
	{
		TraceInfo{ClassId} << "Prepare renderable instance for render target '" << renderTarget->id() << "' ...";

		this->forEachRenderableInstance([this, &renderer, renderTarget] (RenderableInstance::Abstract & renderableInstance) {
			if ( !renderer.getRenderableInstanceReadyForRender(renderableInstance, renderTarget, m_lightSet) )
			{
				Tracer::error(ClassId, "The renderable instance preparation for rendering has failed !");
			}

			return true;
		});
	}

	void
	Scene::refreshRenderableInstances (const std::shared_ptr< RenderTarget::Abstract > & renderTarget) const noexcept
	{
		TraceInfo{ClassId} << "Refreshing renderable instance for render target '" << renderTarget->id() << "' ...";

		this->forEachRenderableInstance([renderTarget] (RenderableInstance::Abstract & renderableInstance) {
			if ( !renderableInstance.refreshGraphicsPipelines(renderTarget) )
			{
				Tracer::error(ClassId, "The renderable instance refresh for rendering has failed !");
			}

			return true;
		});
	}

	void
	Scene::forEachRenderableInstance (const std::function< bool (RenderableInstance::Abstract & renderableInstance) > & function) const noexcept
	{
		/* Check global renderable objects from the scene. */
		for ( const auto & sceneVisualComponent : m_sceneVisualComponents )
		{
			auto * renderableInstance = sceneVisualComponent->getRenderableInstance();

			if ( renderableInstance == nullptr )
			{
				Tracer::error(ClassId, "The scene visual renderable instance pointer is null !");

				continue;
			}

			if ( !function(*renderableInstance) )
			{
				return;
			}
		}

		/* Check renderable objects from scene static entities. */
		{
			const std::lock_guard< std::mutex > lock{m_staticEntitiesMutex};

			for ( const auto & pair : m_staticEntities )
			{
				const auto & staticEntity = pair.second;

				/* Check whether the static entity contains something to render. */
				if ( !staticEntity->isRenderable() )
				{
					continue;
				}

				/* Go through each entity component to update visuals. */
				for ( const auto & componentPair : staticEntity->components() )
				{
					const auto & component = componentPair.second;

					if ( !component->isRenderable() )
					{
						continue;
					}

					auto * renderableInstance = component->getRenderableInstance();

					if ( renderableInstance == nullptr )
					{
						TraceError{ClassId} << "The static entity '" << staticEntity->name() << "' component '" << componentPair.first << "' renderable instance pointer is null !";

						continue;
					}

					if ( !function(*renderableInstance) )
					{
						return;
					}
				}
			}
		}

		/* Check renderable objects from the scene node tree. */
		{
			/* NOTE: Prevent scene node deletion from logic update thread to crash the rendering. */
			const std::lock_guard< std::mutex > lock{m_sceneNodesMutex};

			NodeCrawler< const Node > crawler{m_rootNode};

			std::shared_ptr< const Node > node{};

			while ( (node = crawler.nextNode()) != nullptr )
			{
				/* Check whether the scene node contains something to render. */
				if ( !node->isRenderable() )
				{
					continue;
				}

				/* Go through each entity component to update visuals. */
				for ( const auto & componentPair : node->components() )
				{
					const auto & component = componentPair.second;

					if ( !component->isRenderable() )
					{
						continue;
					}

					auto * renderableInstance = component->getRenderableInstance();

					if ( renderableInstance == nullptr )
					{
						TraceError{ClassId} << "The scene node '" << node->name() << "' component '" << componentPair.first << "' renderable instance pointer is null !";

						continue;
					}

					if ( !function(*renderableInstance) )
					{
						return;
					}
				}
			}
		}
	}

	const MasterControl::Console &
	Scene::masterControlConsole () const noexcept
	{
		return m_masterControlConsole;
	}

	MasterControl::Console &
	Scene::masterControlConsole () noexcept
	{
		return m_masterControlConsole;
	}

	const LightSet &
	Scene::lightSet () const noexcept
	{
		return m_lightSet;
	}

	LightSet &
	Scene::lightSet () noexcept
	{
		return m_lightSet;
	}

	const PhysicalEnvironmentProperties &
	Scene::physicalEnvironmentProperties () const noexcept
	{
		return m_physicalEnvironmentProperties;
	}

	PhysicalEnvironmentProperties &
	Scene::physicalEnvironmentProperties () noexcept
	{
		return m_physicalEnvironmentProperties;
	}

	void
	Scene::setBackground (const std::shared_ptr< Renderable::AbstractBackground > & background) noexcept
	{
		m_background = background;

		this->registerSceneVisualComponents(*Renderer::instance());
	}

	const std::shared_ptr< Renderable::AbstractBackground > &
	Scene::background () const noexcept
	{
		return m_background;
	}

	void
	Scene::setSceneArea (const std::shared_ptr< Renderable::AbstractSceneArea > & sceneArea) noexcept
	{
		m_sceneArea = sceneArea;

		this->registerSceneVisualComponents(*Renderer::instance());
	}

	const std::shared_ptr< Renderable::AbstractSceneArea > &
	Scene::sceneArea () const noexcept
	{
		return m_sceneArea;
	}

	void
	Scene::setSeaLevel (const std::shared_ptr< Renderable::AbstractSeaLevel > & seaLevel) noexcept
	{
		m_seaLevel = seaLevel;

		this->registerSceneVisualComponents(*Renderer::instance());
	}

	const std::shared_ptr< Renderable::AbstractSeaLevel > &
	Scene::seaLevel () const noexcept
	{
		return m_seaLevel;
	}

	const std::shared_ptr< Node > &
	Scene::root () const noexcept
	{
		return m_rootNode;
	}

	std::shared_ptr< Node >
	Scene::findNode (const std::string & nodeName) const noexcept
	{
		std::shared_ptr< Node > currentNode = m_rootNode;

		NodeCrawler< Node > crawler(currentNode);

		while ( (currentNode = crawler.nextNode()) != nullptr )
		{
			if ( currentNode->name() == nodeName )
			{
				return currentNode;
			}
		}

		return nullptr;
	}

	const std::map< std::string , std::shared_ptr< StaticEntity > > &
	Scene::staticEntities () const noexcept
	{
		return m_staticEntities;
	}

	const std::set< std::shared_ptr< AbstractModifier > > &
	Scene::modifiers () const noexcept
	{
		return m_modifiers;
	}

	const EffectsList &
	Scene::environmentEffects () const noexcept
	{
		return m_environmentEffects;
	}

	std::array< size_t, 2 >
	Scene::getNodeStatistics () const noexcept
	{
		std::array< size_t, 2 > stats{0UL, 0UL};

		std::shared_ptr< const Node > currentNode = m_rootNode;

		NodeCrawler< const Node > crawler(currentNode);

		do
		{
			stats[0] += currentNode->subNodes().size();

			const auto depth = currentNode->getDepth();

			if ( stats[1] < depth )
			{
				stats[1] = depth;
			}
		}
		while ( (currentNode = crawler.nextNode()) != nullptr );

		return stats;
	}

	std::array< size_t, 2 >
	Scene::getSectorStatistics (const std::shared_ptr< Scenes::OctreeSector > & sector) noexcept
	{
		std::array< size_t, 2 > stats{1UL, 0UL};

		OctreeSectorCrawler< const OctreeSector > crawler(sector);

		std::shared_ptr< const OctreeSector > currentSector;

		while ( (currentSector = crawler.nextSector()) != nullptr )
		{
			stats[0]++;

			const auto depth = currentSector->getDepth();

			if ( depth > stats[1] )
			{
				stats[1] = depth;
			}
		}

		return stats;
	}

	bool
	Scene::contains (const Vector< 3, float > & worldPosition) const noexcept
	{
		/* Checks on X axis. */
		if ( worldPosition[X] > m_boundary || worldPosition[X] < -m_boundary )
		{
			return false;
		}

		/* Checks on Y axis. */
		if ( worldPosition[Y] > m_boundary || worldPosition[Y] < -m_boundary )
		{
			return false;
		}

		/* Checks on Z axis. */
		if ( worldPosition[Z] > m_boundary || worldPosition[Z] < -m_boundary )
		{
			return false;
		}

		return true;
	}

	Vector < 3, float>
	Scene::getRandomPosition () const noexcept
	{
		return {
			Utility::random(-m_boundary, m_boundary),
			Utility::random(-m_boundary, m_boundary),
			Utility::random(-m_boundary, m_boundary)
		};
	}

	void
	Scene::showSectors (bool state) noexcept
	{
		if ( m_flags[ShowSectors] == state )
		{
			return;
		}

		if ( state )
		{
			m_flags[ShowSectors] = true;
		}
		else
		{
			m_flags[ShowSectors] = false;
		}
	}

	void
	Scene::showGroundZero (bool /*state*/, float /*space*/) noexcept
	{
		/* FIXME: Old OpenGL behavior. */
	}

	void
	Scene::showBoundaries (bool /*state*/, float /*space*/) noexcept
	{
		/* FIXME: Old OpenGL behavior. */
	}

	std::string
	Scene::getStatisticsString (bool printNodeSystem, bool printStaticEntitySystem, bool printSectorSystem, bool printTrees) const noexcept
	{
		std::stringstream output{};

		output << "Scene '" << this->name() << "' content:" "\n";

		if ( printNodeSystem )
		{
			output << "Node system: " "\n";

			if ( m_rootNode != nullptr )
			{
				const auto stats = this->getNodeStatistics();

				output << "Node count: " << stats[0] << "\n"
					  "Node depth: " << stats[1] << '\n';

				if ( printTrees )
				{
					std::shared_ptr< const Node > currentNode = m_rootNode;

					NodeCrawler< const Node > crawler(currentNode);

					do
					{
						const std::string pad(currentNode->getDepth() * 2, ' ');

						output << pad << "[Node:" << currentNode->name() << "][Location: " << currentNode->getWorldCoordinates().position() << "] ";

						if ( !currentNode->components().empty() )
						{
							output << '\n';

							for ( const auto & component : currentNode->components() )
							{
								output << pad << "   {" << component.second->getComponentType() << ":" << component.second->name() << "}\n";
							}
						}
						else
						{
							output << "(Empty node)\n";
						}
					}
					while ( (currentNode = crawler.nextNode()) != nullptr );
				}
			}
			else
			{
				output << "No root node !" "\n";
			}
		}

		if ( printStaticEntitySystem )
		{
			output << "Static entity system: " "\n";

			if ( m_staticEntities.empty() )
			{
				output << "No static entity !" "\n";
			}
			else
			{
				output << "Static entity count: " << m_staticEntities.size() << "\n";

				if ( printTrees )
				{
					for ( auto staticEntityIt = m_staticEntities.cbegin(); staticEntityIt != m_staticEntities.cend(); ++staticEntityIt )
					{
						const auto & instance = staticEntityIt->second;

						output << "[Static entity #" << std::distance(m_staticEntities.cbegin(), staticEntityIt) << ":" << staticEntityIt->first << "][Location: " << instance->getWorldCoordinates().position() << "] ";

						if ( !instance->components().empty() )
						{
							output << '\n';

							for ( const auto & component : instance->components() )
							{
								output << "   {" << component.second->getComponentType() << ":" << component.second->name() << "}\n";
							}
						}
						else
						{
							output << "(Empty static entity)\n";
						}
					}
				}
			}
		}

		if ( printSectorSystem )
		{
			const std::lock_guard< std::mutex > lock{m_octreesMutex};

			if ( m_octrees.empty() )
			{
				output << "No octree enabled !" "\n";
			}
			else
			{
				for ( const auto & octreeItem : m_octrees )
				{
					output << "Octree '" << octreeItem.first << "':" "\n";

					const auto stats = this->getSectorStatistics(octreeItem.second);

					output <<
						   "Sector count: " << stats[0] << "\n"
						"Sector depth: " << stats[1] << '\n';

					if ( printTrees )
					{

					}
				}
			}
		}

		return output.str();
	}
}
