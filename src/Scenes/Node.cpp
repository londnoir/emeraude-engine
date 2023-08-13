/*
 * Emeraude/Scenes/Node.cpp
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

#include "Node.hpp"

/* Local inclusions */
#include "Math/OrientedCuboid.hpp"
#include "Scenes/Scene.hpp"
#include "Tracer.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Libraries::PixelFactory;
	using namespace Libraries::VertexFactory;
	using namespace Graphics;
	using namespace Physics;

	const size_t Node::ClassUID{Observable::getClassUID()};

	Node::Node (Scene * parentScene) noexcept
		: AbstractEntity(Node::Root, parentScene)
	{
		this->setMovingAbility(false);
	}

	Node::Node (const std::string & name, const std::shared_ptr< Node > & parent, const Coordinates< float > & coordinates) noexcept
		: AbstractEntity(name, parent->parentScene()), m_parentNode(parent), m_coordinates(coordinates)
	{

	}

	Node::~Node ()
	{
		if ( this->isRoot() )
		{
			this->notify(NodeDeleted, this);
		}
		else
		{
			m_parentNode->forget(this);
		}
	}

	bool
	Node::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	Node::isRenderable () const noexcept
	{
		return m_flags[IsRenderable];
	}

	bool
	Node::hasPhysicalObjectProperties () const noexcept
	{
		return m_flags[HasPhysicalObjectProperties];
	}

	const Coordinates< float > &
	Node::localCoordinates () const noexcept
	{
		return m_coordinates;
	}

	Coordinates< float > &
	Node::getWritableLocalCoordinates () noexcept
	{
		return m_coordinates;
	}

	Coordinates< float >
	Node::getWorldCoordinates () const noexcept
	{
		return Coordinates< float >{this->getModelMatrix()};
	}

	Cuboid< float >
	Node::getWorldBoundingBox () const noexcept
	{
		return OrientedCuboid< float >{this->localBoundingBox(), this->getWorldCoordinates()}.getAxisAlignedBox();
	}

	Sphere< float >
	Node::getWorldBoundingSphere () const noexcept
	{
		return {
			this->localBoundingSphere().radius(),
			this->getWorldCoordinates().position() + this->localBoundingSphere().position()
		};
	}

	void
	Node::enableSphereCollision (bool state) noexcept
	{
		m_flags[SphereCollisionEnabled] = state;
	}

	bool
	Node::sphereCollisionIsEnabled () const noexcept
	{
		return m_flags[SphereCollisionEnabled];
	}

	void
	Node::setLocalCoordinates (const Coordinates< float > & coordinates) noexcept
	{
		m_coordinates = coordinates;
	}

	std::shared_ptr< Node >
	Node::createSubNode (const std::string & name, const Coordinates< float > & coordinates) noexcept
	{
		if ( name == Root )
		{
			Tracer::error(ClassId, Blob() << "The node name '" << Root << "' is reserved !");

			return nullptr;
		}

		if ( m_subNodes.contains(name) )
		{
			Tracer::error(ClassId, Blob() << "The node name '" << name << "' is already used at this level !");

			return nullptr;
		}

		auto subNode = m_subNodes.emplace(name, std::make_shared< Node >(name, std::dynamic_pointer_cast< Node >(this->shared_from_this()), coordinates)).first->second;

		this->observe(subNode.get());

		this->notify(NodeCreated, subNode);

		return subNode;
	}

	void
	Node::onTransform () noexcept // NOLINT(misc-no-recursion)
	{
		/* Dispatch the movement to every component of the node. */
		this->move();

		/* Dispatch the movement to every node below this one. */
		for ( auto & nodePair : m_subNodes )
		{
			nodePair.second->onTransform();
		}
	}

	bool
	Node::processLogics (const Scene & scene, size_t cycle) noexcept
	{
		/* Updates the lifetime of the scene node. */
		m_lifetime += static_cast< unsigned long >(EngineUpdateCycleDuration< double > * 1000.0); // NOLINT(*-magic-numbers)

		/* Updates the position of the scene node. */
		auto moved = false;

		if ( this->isMovable() && this->hasPhysicalObjectProperties() )
		{
			/* Apply scene modifiers. */
			for ( const auto & modifier : scene.modifiers() )
			{
				/* NOTE: Avoid working on the same Node. */
				if ( this == &modifier->parentEntity() )
				{
					continue;
				}

				modifier->apply(*this);
			}

			const auto & velocity = this->updateVelocity(scene.physicalEnvironmentProperties());

			if ( !velocity.isNull() )
			{
				/* FIXME: Check if this is the right place to modulate physics with engine update frequency. */
				const auto newVelocity = velocity * EngineUpdateCycleDuration< float >;

				this->moveBy(newVelocity, TransformSpace::World);

				moved = true;
			}
		}

		/* Updates each animation attached to this node. */
		this->updateAnimations(cycle);

		/* Updates every entity at this Node. */
		for ( auto & pair : this->components() )
		{
			pair.second->processLogics(scene, cycle);
		}

		return moved;
	}

	float
	Node::getIntersectionOverlap (const Node & nodeA, const Node & nodeB) noexcept
	{
		if ( &nodeA == &nodeB )
		{
			return 0.0F;
		}

		return Sphere< float >::getIntersectionOverlap(nodeA.getWorldBoundingSphere(), nodeB.getWorldBoundingSphere());
	}

	float
	Node::getDistance (const Node & nodeA, const Node & nodeB) noexcept
	{
		if ( &nodeA == &nodeB )
		{
			return 0.0F;
		}

		return Vector< 3, float >::distance(nodeA.getWorldCoordinates().position(), nodeB.getWorldCoordinates().position());
	}

	bool
	Node::isVisible (const Frustum & frustum) const noexcept
	{
		if ( this->sphereCollisionIsEnabled() )
		{
			return frustum.isCollidingWith(this->getWorldBoundingSphere()) != Frustum::Result::Outside;
		}

		return frustum.isCollidingWith(this->getWorldBoundingBox()) != Frustum::Result::Outside;
	}

	std::shared_ptr< Node >
	Node::parentNode () noexcept
	{
		return m_parentNode;
	}

	std::shared_ptr< const Node >
	Node::parentNode () const noexcept
	{
		return m_parentNode;
	}

	std::shared_ptr< Node >
	Node::getRootNode () noexcept
	{
		auto currentNode = std::dynamic_pointer_cast< Node >(this->shared_from_this());

		while ( !currentNode->isRoot() )
		{
			currentNode = currentNode->m_parentNode;
		}

		return currentNode;
	}

	std::shared_ptr< const Node >
	Node::getRootNode () const noexcept
	{
		auto currentNode = std::dynamic_pointer_cast< const Node >(this->shared_from_this());

		while ( !currentNode->isRoot() )
		{
			currentNode = currentNode->m_parentNode;
		}

		return currentNode;
	}

	const std::map< std::string, std::shared_ptr< Node > > &
	Node::subNodes () const noexcept
	{
		return m_subNodes;
	}

	std::map< std::string, std::shared_ptr< Node > > &
	Node::subNodes () noexcept
	{
		return m_subNodes;
	}

	std::set< std::shared_ptr< Node > >
	Node::getNeighborNodes (float radius) const noexcept
	{
		std::set< std::shared_ptr< Node > > nearNodes{};

		const auto sectors = this->mainSector()->getSurroundingSectors(true);

		for ( const auto & sector : sectors )
		{
			for ( const auto & element : sector->elements() )
			{
				auto node = std::dynamic_pointer_cast< Node >(element);

				if ( node == nullptr )
				{
					continue;
				}

				if ( Node::getDistance(*this, *node) <= radius )
				{
					nearNodes.emplace(node);
				}
			}
		}

		return nearNodes;
	}

	std::shared_ptr< Node >
	Node::findSubNode (const std::string & nodeName) const noexcept
	{
		const auto nodeIt = m_subNodes.find(nodeName);

		return nodeIt != m_subNodes.cend() ? nodeIt->second : nullptr;
	}

	bool
	Node::destroySubNode (const std::string & nodeName) noexcept
	{
		auto nodeIt = m_subNodes.find(nodeName);

		if ( nodeIt == m_subNodes.end() )
		{
			return false;
		}

		m_subNodes.erase(nodeIt);

		return true;
	}

	void
	Node::destroyAllSubNode () noexcept
	{
		m_subNodes.clear();
	}

	void
	Node::discard () noexcept
	{
		if ( this->isRoot() )
		{
			Tracer::error(ClassId, "You cannot discard the root Node !");

			return;
		}

		/* Say i'm not longer usable. */
		m_flags[IsDiscardable] = true;
	}

	bool
	Node::isDiscardable () const noexcept
	{
		return m_flags[IsDiscardable];
	}

	void
	Node::destroy () noexcept
	{
		/* Removes every component attached to this Node. */
		this->clearComponents();

		/* Clear every sub Node. */
		this->destroyAllSubNode();
	}

	void
	Node::destroyTree () noexcept
	{
		if ( !this->isRoot() )
		{
			Tracer::error(ClassId, "Only the root Node can destroy the whole tree !");

			return;
		}

		/* Removes every component attached to this Node. */
		this->clearComponents();

		/* Clear every sub Node. */
		this->destroyAllSubNode();
	}

	void
	Node::cleanTree () noexcept // NOLINT(misc-no-recursion)
	{
		auto nodeIt = std::begin(m_subNodes);

		while ( nodeIt != std::end(m_subNodes) )
		{
			if ( nodeIt->second->isDiscardable() )
			{
				nodeIt = m_subNodes.erase(nodeIt);
			}
			else
			{
				nodeIt->second->cleanTree();

				++nodeIt;
			}
		}
	}

	bool
	Node::isRoot () const noexcept
	{
		return m_parentNode == nullptr;
	}

	bool
	Node::isLeaf() const noexcept
	{
		return m_subNodes.empty();
	}

	size_t
	Node::getDepth () const noexcept
	{
		if ( this->isRoot() )
		{
			return 0;
		}

		size_t depth = 0;

		auto parent = m_parentNode;

		while ( !parent->isRoot() )
		{
			depth++;

			parent = parent->m_parentNode;
		}

		return depth;
	}

	Matrix< 4, float >
	Node::getModelMatrix () const noexcept
	{
		if ( this->isRoot() )
		{
			return {};
		}

		/* NOTE: beyond this line, we have a parent Node. */
		std::stack< Matrix< 4, float > > reversedTree;

		/* Gets the tree node into a stack to reverse it. */
		{
			auto parent = std::dynamic_pointer_cast< const Node >(this->shared_from_this());

			/* While parent is not Root. */
			while ( parent != nullptr )
			{
				reversedTree.emplace(parent->localCoordinates().modelMatrix());

				parent = parent->m_parentNode;
			}
		}

		/* Compute the final matrix by getting back and multiply each matrix from the stack. */
		Matrix< 4, float > model;

		while ( !reversedTree.empty() )
		{
			model *= reversedTree.top();

			reversedTree.pop();
		}

		return model;
	}

	Matrix< 4, float >
	Node::getViewMatrix (bool rotateOnly) const noexcept
	{
		return this->getWorldCoordinates().viewMatrix(rotateOnly);
	}

	void
	Node::moveTo (const Vector< 3, float > & position, TransformSpace transformSpace) noexcept
	{
		if ( this->isRoot() )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", you can't move root ! " "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

			return;
		}

		switch ( transformSpace )
		{
			/* We are using the local coordinate system. */
			case TransformSpace::Local :
				this->getWritableLocalCoordinates().translateAlongLocalAxis(position);
				break;

			/* We are using the parent coordinates system. If the parent is the root, it's equivalent to world coordinates system. */
			case TransformSpace::Parent :
				this->getWritableLocalCoordinates().setPosition(position);
				break;

			/* We are using the world coordinate system. */
			case TransformSpace::World :
				/* If there is no parent or the parent is the root, simply set the new position. */
				if ( m_parentNode == nullptr || m_parentNode->isRoot() )
				{
					this->getWritableLocalCoordinates().setPosition(position);
				}
				/* We subtract the world coordinates of the parent node before setting the new position. */
				else
				{
					this->getWritableLocalCoordinates().setPosition(position - m_parentNode->getWorldCoordinates().position());
				}
				break;
		}

		this->onTransform();
	}

	void
	Node::moveOnXAxisTo (float xPosition, TransformSpace transformSpace) noexcept
	{
		if ( this->isRoot() )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", you can't move root !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

			return;
		}

		switch ( transformSpace )
		{
			case TransformSpace::Local :
				this->getWritableLocalCoordinates().translateAlongLocalXAxis(xPosition);
				break;

			case TransformSpace::Parent :
				this->getWritableLocalCoordinates().setXPosition(xPosition);
				break;

			case TransformSpace::World :
				if ( m_parentNode == nullptr || m_parentNode->isRoot() )
				{
					this->getWritableLocalCoordinates().setXPosition(xPosition);
				}
				else
				{
					auto delta = xPosition - m_parentNode->getWorldCoordinates().position()[X];

					this->getWritableLocalCoordinates().setXPosition(delta);
				}
				break;
		}

		this->onTransform();
	}

	void
	Node::moveOnYAxisTo (float yPosition, TransformSpace transformSpace) noexcept
	{
		if ( this->isRoot() )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", you can't move root !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

			return;
		}

		switch ( transformSpace )
		{
			case TransformSpace::Local :
				this->getWritableLocalCoordinates().translateAlongLocalYAxis(yPosition);
				break;

			case TransformSpace::Parent :
				this->getWritableLocalCoordinates().setYPosition(yPosition);
				break;

			case TransformSpace::World :
				if ( m_parentNode == nullptr || m_parentNode->isRoot() )
				{
					this->getWritableLocalCoordinates().setYPosition(yPosition);
				}
				else
				{
					auto delta = yPosition - m_parentNode->getWorldCoordinates().position()[Y];

					this->getWritableLocalCoordinates().setYPosition(delta);
				}
				break;
		}

		this->onTransform();
	}

	void
	Node::moveOnZAxisTo (float zPosition, TransformSpace transformSpace) noexcept
	{
		if ( this->isRoot() )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", you can't move root !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

			return;
		}

		switch ( transformSpace )
		{
			case TransformSpace::Local :
				this->getWritableLocalCoordinates().translateAlongLocalZAxis(zPosition);
				break;

			case TransformSpace::Parent :
				this->getWritableLocalCoordinates().setZPosition(zPosition);
				break;

			case TransformSpace::World :
				if ( m_parentNode == nullptr || m_parentNode->isRoot() )
				{
					this->getWritableLocalCoordinates().setZPosition(zPosition);
				}
				else
				{
					auto delta = zPosition - m_parentNode->getWorldCoordinates().position()[Z];

					this->getWritableLocalCoordinates().setZPosition(delta);
				}
				break;
		}

		this->onTransform();
	}

	void
	Node::moveBy (const Vector< 3, float > & distance, TransformSpace transformSpace) noexcept
	{
		if ( this->isRoot() )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", you can't move root !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

			return;
		}

		switch ( transformSpace )
		{
			case TransformSpace::Local :
				this->getWritableLocalCoordinates().translateAlongLocalAxis(distance);
				break;

			case TransformSpace::Parent :
				if ( !this->isRoot() )
				{
					this->getWritableLocalCoordinates().translateAlongCustomAxis(distance, m_parentNode->localCoordinates());
					break;
				}

				[[fallthrough]];

			case TransformSpace::World :
				this->getWritableLocalCoordinates().translateAlongWorldAxis(distance);
				break;
		}

		this->onTransform();
	}

	void
	Node::moveOnXAxisBy (float xShift, TransformSpace transformSpace) noexcept
	{
		if ( this->isRoot() )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", you can't move root !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

			return;
		}

		switch ( transformSpace )
		{
			case TransformSpace::Local :
				this->getWritableLocalCoordinates().translateAlongLocalXAxis(xShift);
				break;

			case TransformSpace::Parent :
				if ( !this->isRoot() )
				{
					this->getWritableLocalCoordinates().translateAlongCustomXAxis(xShift, m_parentNode->localCoordinates());
					break;
				}

				[[fallthrough]];

			case TransformSpace::World :
				this->getWritableLocalCoordinates().translateAlongWorldXAxis(xShift);
				break;
		}

		this->onTransform();
	}

	void
	Node::moveOnYAxisBy (float yShift, TransformSpace transformSpace) noexcept
	{
		if ( this->isRoot() )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", you can't move root !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

			return;
		}

		switch ( transformSpace )
		{
			case TransformSpace::Local :
				this->getWritableLocalCoordinates().translateAlongLocalYAxis(yShift);
				break;

			case TransformSpace::Parent :
				if ( !this->isRoot() )
				{
					this->getWritableLocalCoordinates().translateAlongCustomYAxis(yShift, m_parentNode->localCoordinates());
					break;
				}

				[[fallthrough]];

			case TransformSpace::World :
				this->getWritableLocalCoordinates().translateAlongWorldYAxis(yShift);
				break;
		}

		this->onTransform();
	}

	void
	Node::moveOnZAxisBy (float zShift, TransformSpace transformSpace) noexcept
	{
		if ( this->isRoot() )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", you can't move root !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

			return;
		}

		switch ( transformSpace )
		{
			case TransformSpace::Local :
				this->getWritableLocalCoordinates().translateAlongLocalZAxis(zShift);
				break;

			case TransformSpace::Parent :
				if ( !this->isRoot() )
				{
					this->getWritableLocalCoordinates().translateAlongCustomZAxis(zShift, m_parentNode->localCoordinates());
					break;
				}

				[[fallthrough]];

			case TransformSpace::World :
				this->getWritableLocalCoordinates().translateAlongWorldZAxis(zShift);
				break;
		}

		this->onTransform();
	}

	void
	Node::rotate (float radian, const Vector< 3, float > & axis, TransformSpace transformSpace) noexcept
	{
		if ( this->isRoot() )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", you cannot rotate the root node !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

			return;
		}

		switch ( transformSpace )
		{
			/* Rotation around the current node X axis. */
			case TransformSpace::Local :
				/* NOTE: special cases for straight axis. */
				if ( axis == Vector< 3, float >::positiveX() )
				{
					this->getWritableLocalCoordinates().pitch(radian);
				}
				else if ( axis == Vector< 3, float >::positiveY() )
				{
					this->getWritableLocalCoordinates().yaw(radian);
				}
				else if ( axis == Vector< 3, float >::positiveZ() )
				{
					this->getWritableLocalCoordinates().roll(radian);
				}
				else
				{
					/* NOTE: Avoid an identity matrix rotation. */
					if ( m_parentNode == nullptr || m_parentNode->isRoot() )
					{
						this->getWritableLocalCoordinates().rotate(radian, axis);
					}
					else
					{
						const auto rotation = (this->localCoordinates().modelMatrix() * Vector< 4, float >(axis,0.0F)).toVector3();

						this->getWritableLocalCoordinates().rotate(radian, rotation);
					}
				}
				break;

			/* Rotation around the parent node X axis. */
			case TransformSpace::Parent :
				this->getWritableLocalCoordinates().rotate(radian, axis);
				break;

			/* Rotation around the world X axis. */
			case TransformSpace::World :
				if ( !this->isRoot() && !m_parentNode->isRoot() )
				{
					auto mat = m_parentNode->getModelMatrix().inverse();

					this->getWritableLocalCoordinates().rotate(radian, (mat * Vector< 4, float >(axis, 0.0F)).toVector3());
				}
				else
				{
					this->getWritableLocalCoordinates().rotate(radian, axis);
				}
				break;
		}

		this->onTransform();
	}

	void
	Node::setMovingAbility (bool state) noexcept
	{
		m_flags[IsMovable] = state;
	}

	bool
	Node::isMovable () const noexcept
	{
		return m_flags[IsMovable];
	}

	void
	Node::pauseSimulation (bool state) noexcept
	{
		m_flags[SimulationPaused] = state;
	}

	bool
	Node::isSimulationPaused () const noexcept
	{
		return m_flags[SimulationPaused];
	}

	void
	Node::enableFreeFlyMode (bool state) noexcept
	{
		m_flags[FreeFlyModeEnabled] = state;
	}

	bool
	Node::isFreeFlyModeEnabled () const noexcept
	{
		return m_flags[FreeFlyModeEnabled];
	}

	void
	Node::enableNoClippingMode (bool state) noexcept
	{
		m_flags[NoClippingModeEnabled] = state;
	}

	bool
	Node::isNoClippingModeEnabled () const noexcept
	{
		return m_flags[NoClippingModeEnabled];
	}

	Vector< 3, float >
	Node::getWorldVelocity () const noexcept
	{
		auto velocity = this->velocity();

		auto parent = m_parentNode;

		while ( parent != nullptr )
		{
			velocity += parent->velocity();

			parent = parent->m_parentNode;
		}

		return velocity;
	}

	Vector< 3, float >
	Node::getWorldAcceleration () const noexcept
	{
		auto acceleration = this->acceleration();

		auto parent = m_parentNode;

		while ( parent != nullptr )
		{
			acceleration += parent->acceleration();

			parent = parent->m_parentNode;
		}

		return acceleration;
	}

	Vector< 3, float >
	Node::getWorldCenterOfMass () const noexcept
	{
		return this->getWorldCoordinates().position() + this->centerOfMass();
	}

	unsigned long
	Node::getLifeTime () const noexcept
	{
		return m_lifetime;
	}

	void
	Node::setRenderingAbilityState (bool state) noexcept
	{
		m_flags[IsRenderable] = state;
	}

	void
	Node::setPhysicalObjectPropertiesState (bool state) noexcept
	{
		m_flags[HasPhysicalObjectProperties] = state;
	}

	bool
	Node::onUnhandledNotification (const Observable * observable, int notificationCode, const std::any & data) noexcept
	{
		if ( observable->is(Node::ClassUID) )
		{
			if ( std::any_of(m_subNodes.cbegin(), m_subNodes.cend(), [observable] (const auto & subNode) {return subNode.second.get() == observable;}) )
			{
				this->notify(notificationCode, data);

				return true;
			}
		}

#ifdef DEBUG
		/* NOTE: Don't know what is it, goodbye ! */
		TraceInfo{ClassId} <<
			"Received an unhandled event from observable @" << observable << " (code:" << notificationCode << ") ! "
			"Forgetting it ...";
#endif

		return false;
	}

	bool
	Node::playAnimation (Animations::id_t identifier, const Variant & value) noexcept
	{
		switch ( identifier )
		{
			case LocalCoordinates :
				this->setLocalCoordinates(value.asCoordinatesFloat());
				return true;

			case LocalPosition :
				this->moveTo(value.asVector3Float(), TransformSpace::Local);
				return true;

			case LocalXPosition :
				this->moveOnXAxisTo(value.asFloat(), TransformSpace::Local);
				return true;

			case LocalYPosition :
				this->moveOnYAxisTo(value.asFloat(), TransformSpace::Local);
				return true;

			case LocalZPosition :
				this->moveOnZAxisTo(value.asFloat(), TransformSpace::Local);
				return true;

			case LocalTranslation :
				this->moveBy(value.asVector3Float(), TransformSpace::Local);
				return true;

			case LocalXTranslation :
				this->moveOnXAxisBy(value.asFloat(), TransformSpace::Local);
				return true;

			case LocalYTranslation :
				this->moveOnYAxisBy(value.asFloat(), TransformSpace::Local);
				return true;

			case LocalZTranslation :
				this->moveOnZAxisBy(value.asFloat(), TransformSpace::Local);
				return true;

			case LocalRotation :
				// ...
				return true;

			case LocalXRotation :
				this->pitch(value.asFloat(), TransformSpace::Local);
				return true;

			case LocalYRotation :
				this->yaw(value.asFloat(), TransformSpace::Local);
				return true;

			case LocalZRotation :
				this->roll(value.asFloat(), TransformSpace::Local);
				return true;

			case ParentPosition :
				this->moveTo(value.asVector3Float(), TransformSpace::Parent);
				return true;

			case ParentXPosition :
				this->moveOnXAxisTo(value.asFloat(), TransformSpace::Parent);
				return true;

			case ParentYPosition :
				this->moveOnYAxisTo(value.asFloat(), TransformSpace::Parent);
				return true;

			case ParentZPosition :
				this->moveOnZAxisTo(value.asFloat(), TransformSpace::Parent);
				return true;

			case ParentTranslation :
				this->moveBy(value.asVector3Float(), TransformSpace::Parent);
				return true;

			case ParentXTranslation :
				this->moveOnXAxisBy(value.asFloat(), TransformSpace::Parent);
				return true;

			case ParentYTranslation :
				this->moveOnYAxisBy(value.asFloat(), TransformSpace::Parent);
				return true;

			case ParentZTranslation :
				this->moveOnZAxisBy(value.asFloat(), TransformSpace::Parent);
				return true;

			case ParentRotation :
				// ...
				return true;

			case ParentXRotation :
				this->pitch(value.asFloat(), TransformSpace::Parent);
				return true;

			case ParentYRotation :
				this->yaw(value.asFloat(), TransformSpace::Parent);
				return true;

			case ParentZRotation :
				this->roll(value.asFloat(), TransformSpace::Parent);
				return true;

			case WorldPosition :
				this->moveTo(value.asVector3Float(), TransformSpace::World);
				return true;

			case WorldXPosition :
				this->moveOnXAxisTo(value.asFloat(), TransformSpace::World);
				return true;

			case WorldYPosition :
				this->moveOnYAxisTo(value.asFloat(), TransformSpace::World);
				return true;

			case WorldZPosition :
				this->moveOnZAxisTo(value.asFloat(), TransformSpace::World);
				return true;

			case WorldTranslation :
				this->moveBy(value.asVector3Float(), TransformSpace::World);
				return true;

			case WorldXTranslation :
				this->moveOnXAxisBy(value.asFloat(), TransformSpace::World);
				return true;

			case WorldYTranslation :
				this->moveOnYAxisBy(value.asFloat(), TransformSpace::World);
				return true;

			case WorldZTranslation :
				this->moveOnZAxisBy(value.asFloat(), TransformSpace::World);
				return true;

			case WorldRotation :
				// ...
				return true;

			case WorldXRotation :
				this->pitch(value.asFloat(), TransformSpace::World);
				return true;

			case WorldYRotation :
				this->yaw(value.asFloat(), TransformSpace::World);
				return true;

			case WorldZRotation :
				this->roll(value.asFloat(), TransformSpace::World);
				return true;

			default:
				break;
		}

		return false;
	}
}
