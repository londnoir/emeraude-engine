/*
 * Emeraude/Scenes/Node.hpp
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
#include <string>
#include <map>
#include <memory>

/* Local inclusions for inheritances. */
#include "AbstractEntity.hpp"
#include "Physics/MovableTrait.hpp"
#include "Animations/AnimatableInterface.hpp"

/* Local inclusions for usages. */
#include "Audio/SoundResource.hpp"
#include "Graphics/Frustum.hpp"

namespace Emeraude::Scenes
{
	/**
	 * @brief The Node class is the key component to build the scene node tree.
	 * @extends Emeraude::Scenes::AbstractEntity A node is an entity of the 3D world.
	 * @extends Emeraude::Physics::MovableTrait A node is a movable entity in the 3D world.
	 * @extends Emeraude::Animations::AnimatableInterface A node can be animated by the engine logics.
	 */
	class Node final : public AbstractEntity, public Physics::MovableTrait, public Animations::AnimatableInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"Node"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/** @brief Observable notification codes. */
			enum NotificationCode
			{
				NodeCreated = AbstractEntity::MaxEnum,
				NodeDeleted,
				/* Enumeration boundary. */
				MaxEnum
			};

			/* Animatable Interface key */
			static constexpr auto LocalCoordinates = 0;
			static constexpr auto LocalPosition = 1;
			static constexpr auto LocalXPosition = 2;
			static constexpr auto LocalYPosition = 3;
			static constexpr auto LocalZPosition = 4;
			static constexpr auto LocalTranslation = 5;
			static constexpr auto LocalXTranslation = 6;
			static constexpr auto LocalYTranslation = 7;
			static constexpr auto LocalZTranslation = 8;
			static constexpr auto LocalRotation = 9;
			static constexpr auto LocalXRotation = 10;
			static constexpr auto LocalYRotation = 11;
			static constexpr auto LocalZRotation = 12;

			static constexpr auto ParentPosition = 13;
			static constexpr auto ParentXPosition = 14;
			static constexpr auto ParentYPosition = 15;
			static constexpr auto ParentZPosition = 16;
			static constexpr auto ParentTranslation = 17;
			static constexpr auto ParentXTranslation = 18;
			static constexpr auto ParentYTranslation = 19;
			static constexpr auto ParentZTranslation = 20;
			static constexpr auto ParentRotation = 21;
			static constexpr auto ParentXRotation = 22;
			static constexpr auto ParentYRotation = 23;
			static constexpr auto ParentZRotation = 24;

			static constexpr auto WorldPosition = 25;
			static constexpr auto WorldXPosition = 26;
			static constexpr auto WorldYPosition = 27;
			static constexpr auto WorldZPosition = 28;
			static constexpr auto WorldTranslation = 29;
			static constexpr auto WorldXTranslation = 30;
			static constexpr auto WorldYTranslation = 31;
			static constexpr auto WorldZTranslation = 32;
			static constexpr auto WorldRotation = 33;
			static constexpr auto WorldXRotation = 34;
			static constexpr auto WorldYRotation = 35;
			static constexpr auto WorldZRotation = 36;

			static constexpr auto Root = "root";

			/**
			 * @brief Constructs the root node.
			 * @param parentScene A pointer to scene holding this node.
			 */
			explicit Node (Scene * parentScene) noexcept;

			/**
			 * @brief Constructs a child node.
			 * @param name The name of the sub child node.
			 * @param parent a reference to the smart pointer of the parent.
			 * @param coordinates A reference to a coordinates. Default Origin.
			 */
			Node (const std::string & name, const std::shared_ptr< Node > & parent, const Libraries::Math::Coordinates< float > & coordinates = {}) noexcept;

			/** @brief Deleted copy constructor. */
			Node (const Node & copy) = delete;

			/** @brief Deleted move constructor. */
			Node (Node && copy) = delete;

			/** @brief Destructor. */
			~Node () override;

			/** @brief Deleted assignment operator. */
			Node & operator= (const Node & other) = delete;

			/** @brief Deleted move assignment operator. */
			Node & operator= (Node && other) = delete;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::Scenes::AbstractEntity::isRenderable() */
			[[nodiscard]]
			bool isRenderable () const noexcept override;

			/** @copydoc Emeraude::Scenes::AbstractEntity::hasPhysicalObjectProperties() */
			[[nodiscard]]
			bool hasPhysicalObjectProperties () const noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::setLocalCoordinates() */
			void setLocalCoordinates (const Libraries::Math::Coordinates< float > & coordinates) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::localCoordinates() const */
			[[nodiscard]]
			const Libraries::Math::Coordinates< float > & localCoordinates () const noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::getWritableLocalCoordinates() */
			[[nodiscard]]
			Libraries::Math::Coordinates< float > & getWritableLocalCoordinates () noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::getWorldCoordinates() const */
			[[nodiscard]]
			Libraries::Math::Coordinates< float > getWorldCoordinates () const noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::getWorldBoundingBox() const */
			[[nodiscard]]
			Libraries::Math::Cuboid< float > getWorldBoundingBox () const noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::getWorldBoundingSphere() const */
			[[nodiscard]]
			Libraries::Math::Sphere< float > getWorldBoundingSphere () const noexcept override;

			/** @copydoc Emeraude::Physics::PhysicalInterface::enableSphereCollision() const */
			void enableSphereCollision (bool state) noexcept override;

			/** @copydoc Emeraude::Physics::PhysicalInterface::sphereCollisionIsEnabled() */
			[[nodiscard]]
			bool sphereCollisionIsEnabled () const noexcept override;

			/** @copydoc Emeraude::Scenes::MovableTrait::setMovingAbility() */
			void setMovingAbility (bool state) noexcept override;

			/** @copydoc Emeraude::Scenes::MovableTrait::isMovable() */
			[[nodiscard]]
			bool isMovable () const noexcept override;

			/** @copydoc Emeraude::Scenes::MovableTrait::pauseSimulation() */
			void pauseSimulation (bool state) noexcept override;

			/** @copydoc Emeraude::Scenes::MovableTrait::isSimulationPaused() */
			[[nodiscard]]
			bool isSimulationPaused () const noexcept override;

			/** @copydoc Emeraude::Scenes::MovableTrait::enableFreeFlyMode() */
			void enableFreeFlyMode (bool state) noexcept override;

			/** @copydoc Emeraude::Scenes::MovableTrait::isFreeFlyModeEnabled() */
			[[nodiscard]]
			bool isFreeFlyModeEnabled () const noexcept override;

			/** @copydoc Emeraude::Scenes::MovableTrait::enableNoClippingMode() */
			void enableNoClippingMode (bool state) noexcept override;

			/** @copydoc Emeraude::Scenes::MovableTrait::isNoClippingModeEnabled() */
			[[nodiscard]]
			bool isNoClippingModeEnabled () const noexcept override;

			/** @copydoc Emeraude::Scenes::MovableTrait::getWorldVelocity() */
			[[nodiscard]]
			Libraries::Math::Vector< 3, float > getWorldVelocity () const noexcept override;

			/** @copydoc Emeraude::Scenes::MovableTrait::getWorldAcceleration() */
			[[nodiscard]]
			Libraries::Math::Vector< 3, float > getWorldAcceleration () const noexcept override;

			/** @copydoc Emeraude::Scenes::MovableTrait::getWorldCenterOfMass() */
			[[nodiscard]]
			Libraries::Math::Vector< 3, float > getWorldCenterOfMass () const noexcept override;

			/** @copydoc Emeraude::Scenes::isSimulationPaused::moveTo() */
			void moveTo (const Libraries::Math::Vector< 3, float > & position, Libraries::Math::TransformSpace transformSpace = Libraries::Math::TransformSpace::Parent) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::moveOnXAxisTo() */
			void moveOnXAxisTo (float xPosition, Libraries::Math::TransformSpace transformSpace = Libraries::Math::TransformSpace::Parent) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::moveOnYAxisTo() */
			void moveOnYAxisTo (float yPosition, Libraries::Math::TransformSpace transformSpace = Libraries::Math::TransformSpace::Parent) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::moveOnZAxisTo() */
			void moveOnZAxisTo (float zPosition, Libraries::Math::TransformSpace transformSpace = Libraries::Math::TransformSpace::Parent) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::moveBy() */
			void moveBy (const Libraries::Math::Vector< 3, float > & distance, Libraries::Math::TransformSpace transformSpace = Libraries::Math::TransformSpace::Parent) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::moveOnXAxisBy() */
			void moveOnXAxisBy (float xShift, Libraries::Math::TransformSpace transformSpace = Libraries::Math::TransformSpace::Parent) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::moveOnYAxisBy() */
			void moveOnYAxisBy (float yShift, Libraries::Math::TransformSpace transformSpace = Libraries::Math::TransformSpace::Parent) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::moveOnZAxisBy() */
			void moveOnZAxisBy (float zShift, Libraries::Math::TransformSpace transformSpace = Libraries::Math::TransformSpace::Parent) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::rotate() */
			void rotate (float radian, const Libraries::Math::Vector< 3, float > & axis, Libraries::Math::TransformSpace transformSpace = Libraries::Math::TransformSpace::Local) noexcept override;

			/**
			 * @brief Returns whether the node is the top tree one. Parent pointer is nullptr.
			 * @return bool.
			 */
			[[nodiscard]]
			bool isRoot () const noexcept;

			/**
			 * @brief Returns true if the node have no child.
			 * @return bool
			 */
			[[nodiscard]]
			bool isLeaf () const noexcept;

			/**
			 * @brief Returns the level below the root of this node.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t getDepth () const noexcept;

			/**
			 * @brief Returns the parent node or nullptr is the current one is root.
			 * @return shared_ptr< Node >.
			 */
			[[nodiscard]]
			std::shared_ptr< Node > parentNode () noexcept;

			/**
			 * @brief Returns the parent node or nullptr is the current one is root.
			 * @return shared_ptr< const Node >.
			 */
			[[nodiscard]]
			std::shared_ptr< const Node > parentNode () const noexcept;

			/**
			 * @brief Returns the root node.
			 * @return shared_ptr< Node >.
			 */
			[[nodiscard]]
			std::shared_ptr< Node > getRootNode () noexcept;

			/**
			 * @brief Returns the root node.
			 * @return shared_ptr< const Node >.
			 */
			[[nodiscard]]
			std::shared_ptr< const Node > getRootNode () const noexcept;

			/**
			 * @brief Returns the children nodes.
			 * @return const map< string, shared_ptr< Node > > &
			 */
			[[nodiscard]]
			const std::map< std::string, std::shared_ptr< Node > > & subNodes () const noexcept;

			/**
			 * @brief Returns the children nodes.
			 * @return map< string, shared_ptr< Node > > &
			 */
			[[nodiscard]]
			std::map< std::string, std::shared_ptr< Node > > & subNodes () noexcept;

			/**
			 * @brief Returns the neighbor nodes.
			 * @return set< shared_ptr< Node > >
			 */
			[[nodiscard]]
			std::set< std::shared_ptr< Node > > getNeighborNodes (float radius) const noexcept;

			/**
			 * @brief Creates a sub node at a given coordinates.
			 * @warning  If the node already exists, the coordinates will be ignored.
			 * @param name The name of the new node.
			 * @param coordinates Set the coordinates of the new node. Default Origin.
			 * @return shared_ptr< Node >
			 */
			[[nodiscard]]
			std::shared_ptr< Node > createSubNode (const std::string & name, const Libraries::Math::Coordinates< float > & coordinates = {}) noexcept;

			/**
			 * @brief Creates a sub node at a given position.
			 * @warning  If the node already exists the position will be ignored.
			 * @param name The name of the new node.
			 * @param position Set the position of the new node.
			 * @return shared_ptr< Node >
			 */
			[[nodiscard]]
			inline
			std::shared_ptr< Node >
			createSubNode (const std::string & name, const Libraries::Math::Vector< 3, float > & position) noexcept
			{
				return this->createSubNode(name, Libraries::Math::Coordinates< float >{position});
			}

			/**
			 * @brief Search for a named sub node.
			 * @warning Can be nullptr !
			 * @param nodeName The name of the node.
			 * @return shared_ptr< Node >.
			 */
			[[nodiscard]]
			std::shared_ptr< Node > findSubNode (const std::string & nodeName) const noexcept;

			/**
			 * @brief Destroys a sub node by his name.
			 * @param nodeName The name of the node.
			 * @return bool
			 */
			bool destroySubNode (const std::string & nodeName) noexcept;

			/** @brief Destroys every sub node and their content. */
			void destroyAllSubNode () noexcept;

			/**
			 * @brief Short-hand for Coordinates class, but use the tree to get the right model matrix.
			 * @todo This is the expensive function of the engine. The multiplication operation of matrices.
			 * @return Matrix< 4, float >
			 */
			[[nodiscard]]
			Libraries::Math::Matrix< 4, float > getModelMatrix () const noexcept;

			/**
			 * @brief Short-hand for Coordinates class, but use the tree to get the right view matrix.
			 * @param rotateOnly Don't set translation in final matrices.
			 * @return Matrix< 4, float >
			 */
			[[nodiscard]]
			Libraries::Math::Matrix< 4, float > getViewMatrix (bool rotateOnly = false) const noexcept;

			/**
			 * @brief Returns for how long this node exists in milliseconds.
			 * @return unsigned long
			 */
			[[nodiscard]]
			unsigned long getLifeTime () const noexcept;

			/**
			 * @brief This function is called from Core::processLogics() to update the logic of the node and return if it has been moved.
			 * @param scene The scene where the node is present.
			 * @param cycle The engine cycle number to use with time dependent effects.
			 * @return bool
			 */
			bool processLogics (const Scene & scene, size_t cycle) noexcept override;

			/** @brief Plans a destruction for this Node. Thread-safe. */
			void discard () noexcept;

			/**
			 * @brief Returns whether the Node will be destroyed in the next cycle update.
			 * @return bool
			 */
			bool isDiscardable () const noexcept;

			/**
			 * @brief RootNode destroy method.
			 * @note This is only callable from root node.
			 */
			void destroyTree () noexcept;

			/** @brief Cleans the tree from dead nodes. */
			void cleanTree () noexcept;

			/**
			 * @brief Checks is this node is visible to frustum.
			 * @param frustum The frustum where the node is tested.
			 * @return bool
			 */
			[[nodiscard]]
			bool isVisible (const Graphics::Frustum & frustum) const noexcept;

			/**
			 * @brief Returns the overlap from the intersection with an other node.
			 * @param nodeA A reference to a node.
			 * @param nodeB A reference to a node.
			 * @return float
			 */
			[[nodiscard]]
			static float getIntersectionOverlap (const Node & nodeA, const Node & nodeB) noexcept;

			/**
			 * @brief Returns the distance between two nodes.
			 * @param nodeA A reference to a node.
			 * @param nodeB A reference to a node.
			 * @return float
			 */
			[[nodiscard]]
			static float getDistance (const Node & nodeA, const Node & nodeB) noexcept;

		private:

			/** @copydoc Emeraude::Scenes::AbstractEntity::setRenderingAbilityState() */
			void setRenderingAbilityState (bool state) noexcept override;

			/** @copydoc Emeraude::Scenes::AbstractEntity::setPhysicalObjectPropertiesState() */
			void setPhysicalObjectPropertiesState (bool state) noexcept override;

			/** @copydoc Emeraude::Scenes::AbstractEntity::onAppNotification() */
			bool onUnhandledNotification (const Observable * observable, int notificationCode, const std::any & data) noexcept override;

			/** @copydoc Emeraude::Animations::AnimatableInterface::playAnimation() */
			bool playAnimation (Animations::id_t identifier, const Libraries::Variant & value) noexcept override;

			/**
			 * @brief Updates data on transformation on the current node.
			 * @return void
			 */
			void onTransform () noexcept;

			/**
			 * @brief This will clean the Node from the Node tree.
			 * @return void
			 */
			void destroy () noexcept;

			/* Flag names. */
			static constexpr auto IsRenderable = 0UL;
			static constexpr auto HasPhysicalObjectProperties = 1UL;
			static constexpr auto IsDiscardable = 2UL;
			static constexpr auto SphereCollisionEnabled = 3UL;
			static constexpr auto IsMovable = 4UL;
			static constexpr auto SimulationPaused = 5UL;
			static constexpr auto FreeFlyModeEnabled = 6UL;
			static constexpr auto NoClippingModeEnabled = 7UL;

			/* NOTE : If nullptr, this node is the root. */
			std::shared_ptr< Node > m_parentNode{};
			std::map< std::string, std::shared_ptr< Node > > m_subNodes{};
			Libraries::Math::Coordinates< float > m_coordinates{};
			unsigned long m_lifetime{0};
			std::array< bool, 8 > m_flags{ // NOLINT(*-magic-numbers)
				false/*IsRenderable*/,
				false/*HasPhysicalObjectProperties*/,
				false/*IsDiscardable*/,
				false/*SphereCollisionEnabled*/,
				true/*IsMovable*/,
				false/*SimulationPaused*/,
				false/*FreeFlyModeEnabled*/,
				false/*NoClippingModeEnabled*/
			};
	};
}
