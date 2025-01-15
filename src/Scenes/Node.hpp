/*
 * src/Scenes/Node.hpp
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
#include <any>
#include <map>
#include <memory>
#include <string>

/* Local inclusions for inheritances. */
#include "AbstractEntity.hpp"
#include "Physics/MovableTrait.hpp"
#include "Animations/AnimatableInterface.hpp"

/* Local inclusions for usages. */
#include "Libraries/Variant.hpp"
#include "Graphics/Frustum.hpp"

namespace Emeraude::Scenes
{
	/**
	 * @brief The Node class is the key component to build the scene node tree.
	 * @extends std::enable_shared_from_this A node need to self replicate its smart pointer.
	 * @extends Emeraude::Scenes::AbstractEntity A node is an entity of the 3D world.
	 * @extends Emeraude::Physics::MovableTrait A node is a movable entity in the 3D world.
	 * @extends Emeraude::Animations::AnimatableInterface A node can be animated by the engine logics.
	 */
	class Node final : public std::enable_shared_from_this< Node >, public AbstractEntity, public Physics::MovableTrait, public Animations::AnimatableInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"Node"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/** @brief Observable notification codes. */
			enum NotificationCode
			{
				SubNodeCreating = AbstractEntity::MaxEnum,
				SubNodeCreated,
				SubNodeDeleting,
				SubNodeDeleted,
				NodeCollision,
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

			static constexpr auto Root{"root"};

			/**
			 * @brief Constructs the root node.
			 */
			Node () noexcept;

			/**
			 * @brief Constructs a child node.
			 * @param name The name of the sub child node.
			 * @param parent a reference to the smart pointer of the parent.
			 * @param sceneTimeMS The scene current time in milliseconds.
			 * @param coordinates A reference to a coordinates. Default Origin.
			 */
			Node (const std::string & name, const std::shared_ptr< Node > & parent, uint32_t sceneTimeMS, const Libraries::Math::CartesianFrame< float > & coordinates = {}) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Node (const Node & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Node (Node && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return Node &
			 */
			Node & operator= (const Node & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return Node &
			 */
			Node & operator= (Node && copy) noexcept = delete;

			/**
			 * @brief Destructs the node.
			 */
			~Node () override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::setPosition(const Libraries::Math::Vector< 3, float > &, Libraries::Math::TransformSpace) */
			void setPosition (const Libraries::Math::Vector< 3, float > & position, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::setXPosition(float, Libraries::Math::TransformSpace) */
			void setXPosition (float position, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::setYPosition(float, Libraries::Math::TransformSpace) */
			void setYPosition (float position, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::setZPosition(float, Libraries::Math::TransformSpace) */
			void setZPosition (float position, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::move(const Libraries::Math::Vector< 3, float > &, Libraries::Math::TransformSpace) */
			void move (const Libraries::Math::Vector< 3, float > & distance, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::moveX(float, Libraries::Math::TransformSpace) */
			void moveX (float distance, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::moveY(float, Libraries::Math::TransformSpace) */
			void moveY (float distance, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::moveZ(float, Libraries::Math::TransformSpace) */
			void moveZ (float distance, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::rotate(float, const Libraries::Math::Vector< 3, float > &, Libraries::Math::TransformSpace) */
			void rotate (float radian, const Libraries::Math::Vector< 3, float > & axis, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::pitch(float, Libraries::Math::TransformSpace) */
			void pitch (float radian, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::yaw(float, Libraries::Math::TransformSpace) */
			void yaw (float radian, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::roll(float, Libraries::Math::TransformSpace) */
			void roll (float radian, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::scale(const Libraries::Math::Vector< 3, float > &, Libraries::Math::TransformSpace) */
			void scale (const Libraries::Math::Vector< 3, float > & factor, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::scale(float, Libraries::Math::TransformSpace) */
			void scale (float factor, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::scaleX(float, Libraries::Math::TransformSpace) */
			void scaleX (float factor, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::scaleY(float, Libraries::Math::TransformSpace) */
			void scaleY (float factor, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::scaleZ(float, Libraries::Math::TransformSpace) */
			void scaleZ (float factor, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::lookAt(const Libraries::Math::Vector< 3, float > &, bool) */
			void
			lookAt (const Libraries::Math::Vector< 3, float > & target, bool flipZAxis) noexcept override
			{
				m_cartesianFrame.lookAt(target, flipZAxis);

				this->onLocationDataUpdate();
			}

			/** @copydoc Emeraude::Scenes::LocatableInterface::setLocalCoordinates(const Libraries::Math::CartesianFrame< float > &) */
			void
			setLocalCoordinates (const Libraries::Math::CartesianFrame< float > & coordinates) noexcept override
			{
				m_cartesianFrame = coordinates;
			}

			/** @copydoc Emeraude::Scenes::LocatableInterface::localCoordinates() const */
			[[nodiscard]]
			const Libraries::Math::CartesianFrame< float > &
			localCoordinates () const noexcept override
			{
				return m_cartesianFrame;
			}

			/** @copydoc Emeraude::Scenes::LocatableInterface::localCoordinates() */
			[[nodiscard]]
			Libraries::Math::CartesianFrame< float > &
			localCoordinates () noexcept override
			{
				return m_cartesianFrame;
			}

			/** @copydoc Emeraude::Scenes::LocatableInterface::getWorldCoordinates() const */
			[[nodiscard]]
			Libraries::Math::CartesianFrame< float > getWorldCoordinates () const noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::getWorldBoundingBox() const */
			[[nodiscard]]
			Libraries::Math::Cuboid< float > getWorldBoundingBox () const noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::getWorldBoundingSphere() const */
			[[nodiscard]]
			Libraries::Math::Sphere< float > getWorldBoundingSphere () const noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::enableSphereCollision(bool) */
			void
			enableSphereCollision (bool state) noexcept override
			{
				this->setFlag(SphereCollisionEnabled, state);
			}

			/** @copydoc Emeraude::Scenes::LocatableInterface::sphereCollisionIsEnabled() const */
			[[nodiscard]]
			bool
			sphereCollisionIsEnabled () const noexcept override
			{
				return this->isFlagEnabled(SphereCollisionEnabled);
			}

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

			/** @copydoc Emeraude::Scenes::AbstractEntity::hasMovableAbility() const */
			[[nodiscard]]
			bool
			hasMovableAbility () const noexcept override
			{
				return true;
			}

			/** @copydoc Emeraude::Scenes::AbstractEntity::isMoving() const */
			[[nodiscard]]
			bool
			isMoving () const noexcept override
			{
				return this->hasVelocity();
			}

			/** @copydoc Emeraude::Scenes::AbstractEntity::getMovableTrait() */
			[[nodiscard]]
			MovableTrait *
			getMovableTrait () noexcept override
			{
				return this;
			}

			/** @copydoc Emeraude::Physics::MovableTrait::getWorldVelocity() const */
			[[nodiscard]]
			Libraries::Math::Vector< 3, float > getWorldVelocity () const noexcept override;

			/** @copydoc Emeraude::Physics::MovableTrait::getWorldCenterOfMass() const */
			[[nodiscard]]
			Libraries::Math::Vector< 3, float > getWorldCenterOfMass () const noexcept override;

			/** @copydoc Emeraude::Physics::MovableTrait::onHit() */
			void
			onHit (float impactForce) noexcept override
			{
				this->notify(NodeCollision, impactForce);
			}

			/** @copydoc Emeraude::Physics::MovableTrait::onImpulse() */
			void
			onImpulse () noexcept override
			{
				this->pauseSimulation(false);
			}

			/**
			 * @brief Returns whether the node is the top tree one. Parent pointer is nullptr.
			 * @return bool.
			 */
			[[nodiscard]]
			bool
			isRoot () const noexcept
			{
				return m_parent.expired();
			}

			/**
			 * @brief Returns true if the node have no child.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isLeaf () const noexcept
			{
				return m_children.empty();
			}

			/**
			 * @brief Returns the level below the root of this node.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t getDepth () const noexcept;

			/**
			 * @brief Returns the parent node smart pointer.
			 * @warning If the node is root, it will be nullptr.
			 * @return std::shared_ptr< Node >
			 */
			[[nodiscard]]
			std::shared_ptr< Node >
			parent () noexcept
			{
				return m_parent.lock();
			}

			/**
			 * @brief Returns the parent node smart pointer.
			 * @warning If the node is root, it will be nullptr.
			 * @return std::shared_ptr< const Node >
			 */
			[[nodiscard]]
			std::shared_ptr< const Node >
			parent () const noexcept
			{
				return m_parent.lock();
			}

			/**
			 * @brief Returns the children nodes.
			 * @return const std::map< std::string, std::shared_ptr< Node > > &
			 */
			[[nodiscard]]
			const std::map< std::string, std::shared_ptr< Node > > &
			children () const noexcept
			{
				return m_children;
			}

			/**
			 * @brief Returns the children nodes.
			 * @return std::map< std::string, std::shared_ptr< Node > > &
			 */
			[[nodiscard]]
			std::map< std::string, std::shared_ptr< Node > > &
			children () noexcept
			{
				return m_children;
			}

			/**
			 * @brief Returns the root node.
			 * @return std::shared_ptr< Node >
			 */
			[[nodiscard]]
			std::shared_ptr< Node > getRoot () noexcept;

			/**
			 * @brief Returns the root node.
			 * @return std::shared_ptr< const Node >
			 */
			[[nodiscard]]
			std::shared_ptr< const Node > getRoot () const noexcept;

			/**
			 * @brief Creates a sub node at a given coordinates.
			 * @warning If the node already exists, the method will return a null pointer.
			 * @param name A reference to a string.
			 * @param sceneTimeMS The scene current time in milliseconds.
			 * @param coordinates Set the coordinates of the new node. Default Origin.
			 * @return std::shared_ptr< Node >
			 */
			[[nodiscard]]
			std::shared_ptr< Node > createChild (const std::string & name, uint32_t sceneTimeMS, const Libraries::Math::CartesianFrame< float > & coordinates = {}) noexcept;

			/**
			 * @brief Creates a sub node at a given position.
			 * @warning If the node already exists, the method will return a null pointer.
			 * @param name A reference to a string.
			 * @param sceneTimeMS The scene current time in milliseconds.
			 * @param position Set the position of the new node.
			 * @return std::shared_ptr< Node >
			 */
			[[nodiscard]]
			std::shared_ptr< Node >
			createChild (const std::string & name, uint32_t sceneTimeMS, const Libraries::Math::Vector< 3, float > & position) noexcept
			{
				return this->createChild(name, sceneTimeMS, Libraries::Math::CartesianFrame< float >{position});
			}

			/**
			 * @brief Returns a sub node by its name.
			 * @warning Can be nullptr !
			 * @param name A reference to a string.
			 * @return std::shared_ptr< Node >
			 */
			[[nodiscard]]
			std::shared_ptr< Node > findChild (const std::string & name) const noexcept;

			/**
			 * @brief Destroys a sub node by its name and returns true if the sub node existed.
			 * @param name A reference to a string.
			 * @return bool
			 */
			bool destroyChild (const std::string & name) noexcept;

			/**
			 * @brief Destroys every sub node and their content.
			 * @return void
			 */
			void
			destroyChildren () noexcept
			{
				m_children.clear();
			}

			/**
			 * @brief Returns for how long this node exists in microseconds.
			 * @return uint64_t
			 */
			[[nodiscard]]
			uint64_t
			lifeTime () const noexcept
			{
				return m_lifetime;
			}

			/**
			 * @brief Plans a destruction for this Node. Thread-safe.
			 * @return void
			 */
			void discard () noexcept;

			/**
			 * @brief Returns whether the Node will be destroyed in the next cycle processLogics.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isDiscardable () const noexcept
			{
				return this->isFlagEnabled(IsDiscardable);
			}

			/**
			 * @brief Removes directly all sub node below this node.
			 * @return void
			 */
			void destroyTree () noexcept;

			/**
			 * @brief Check all sub node below this node for discarded marked ones.
			 * @return void
			 */
			void trimTree () noexcept;

			/**
			 * @brief Checks is this node is visible to frustum.
			 * @param frustum The frustum where the node is tested.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isVisible (const Graphics::Frustum & frustum) const noexcept
			{
				if ( this->sphereCollisionIsEnabled() )
				{
					return frustum.isCollidingWith(this->getWorldBoundingSphere()) != Graphics::Frustum::Result::Outside;
				}

				return frustum.isCollidingWith(this->getWorldBoundingBox()) != Graphics::Frustum::Result::Outside;
			}

			/**
			 * @brief Accelerates the node forward. This is a shortcut.
			 * @param power The power of acceleration. This can be negative to decelerate.
			 * @return void
			 */
			void accelerate (float power) noexcept;

			/**
			 * @brief Returns the overlap from the intersection with another node.
			 * @param nodeA A reference to a node.
			 * @param nodeB A reference to a node.
			 * @return float
			 */
			[[nodiscard]]
			static
			float
			getIntersectionOverlap (const Node & nodeA, const Node & nodeB) noexcept
			{
				if ( &nodeA == &nodeB )
				{
					return 0.0F;
				}

				return Libraries::Math::Sphere< float >::getIntersectionOverlap(nodeA.getWorldBoundingSphere(), nodeB.getWorldBoundingSphere());
			}

			/**
			 * @brief Returns the distance between two nodes.
			 * @param nodeA A reference to a node.
			 * @param nodeB A reference to a node.
			 * @return float
			 */
			[[nodiscard]]
			static
			float
			getDistance (const Node & nodeA, const Node & nodeB) noexcept
			{
				if ( &nodeA == &nodeB )
				{
					return 0.0F;
				}

				return Libraries::Math::Vector< 3, float >::distance(nodeA.getWorldCoordinates().position(), nodeB.getWorldCoordinates().position());
			}

		private:

			/** @copydoc Emeraude::Physics::MovableTrait::getObjectProperties() */
			[[nodiscard]]
			const Physics::PhysicalObjectProperties &
			getObjectProperties () const noexcept override
			{
				return this->physicalObjectProperties();
			}

			/** @copydoc Emeraude::Physics::MovableTrait::getWorldPosition() */
			[[nodiscard]]
			Libraries::Math::Vector< 3, float >
			getWorldPosition () const noexcept override
			{
				return this->getWorldCoordinates().position();
			}

			/** @copydoc Emeraude::Physics::MovableTrait::simulatedMove() */
			void
			simulatedMove (const Libraries::Math::Vector< 3, float > & worldPosition) noexcept override
			{
				this->move(worldPosition, Libraries::Math::TransformSpace::World);
			}

			/** @copydoc Emeraude::Physics::MovableTrait::simulatedRotation() */
			void
			simulatedRotation (float radianAngle, const Libraries::Math::Vector< 3, float > & worldDirection) noexcept override
			{
				this->rotate(Libraries::Math::Degree(radianAngle), worldDirection, Libraries::Math::TransformSpace::Local);
			}

			/** @copydoc Emeraude::Scenes::AbstractEntity::onUnhandledNotification() */
			bool onUnhandledNotification (const ObservableTrait * observable, int notificationCode, const std::any & data) noexcept override;

			/** @copydoc Emeraude::Animations::AnimatableInterface::playAnimation() */
			bool playAnimation (Animations::id_t identifier, const Libraries::Variant & value) noexcept override;

			/** @copydoc Emeraude::Scenes::AbstractEntity::onLocationDataUpdate() */
			void onLocationDataUpdate () noexcept override;

			/** @copydoc Emeraude::Scenes::AbstractEntity::onProcessLogics() */
			bool onProcessLogics (const Scene & scene) noexcept override;

			/* Flag names. */
			static constexpr auto IsDiscardable{NextFlag + 0UL};

			/* NOTE : If nullptr, this node is the root. */
			std::weak_ptr< Node > m_parent;
			std::map< std::string, std::shared_ptr< Node > > m_children;
			Libraries::Math::CartesianFrame< float > m_cartesianFrame;
			uint64_t m_lifetime{0};
	};
}
