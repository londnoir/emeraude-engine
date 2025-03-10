/*
 * src/Libraries/Node.cpp
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

#include "Node.hpp"

/* STL inclusions. */
#include <stack>

namespace Libraries
{
	using namespace Math;

	Node::Node (const std::shared_ptr< Node > & parent, const CartesianFrame< float > & coordinates) noexcept
		: m_parent(parent), m_cartesianFrame(coordinates)
	{

	}

	size_t
	Node::getDepth () const noexcept
	{
		if ( this->isRoot() )
		{
			return 0;
		}

		size_t depth = 0;

		auto parent = m_parent.lock();

		while ( !parent->isRoot() )
		{
			depth++;

			parent = parent->m_parent.lock();
		}

		return depth;
	}

	std::shared_ptr< Node >
	Node::getRoot () noexcept
	{
		auto currentNode = this->shared_from_this();

		while ( !currentNode->isRoot() )
		{
			currentNode = currentNode->m_parent.lock();
		}

		return currentNode;
	}

	std::shared_ptr< const Node >
	Node::getRoot () const noexcept
	{
		auto currentNode = this->shared_from_this();

		while ( !currentNode->isRoot() )
		{
			currentNode = currentNode->m_parent.lock();
		}

		return currentNode;
	}

	std::shared_ptr< Node >
	Node::createChild (const std::string & name, const CartesianFrame< float > & coordinates) noexcept
	{
		if ( name == Root )
		{
			std::cerr << "The node name '" << Root << "' is reserved !" "\n";

			return nullptr;
		}

		if ( m_children.contains(name) )
		{
			std::cerr << "The node name '" << name << "' is already used at this level !" "\n";

			return nullptr;
		}

		return m_children.emplace(name, std::make_shared< Node >(this->shared_from_this(), coordinates)).first->second;
	}

	std::shared_ptr< Node >
	Node::findChild (const std::string & name) const noexcept
	{
		const auto nodeIt = m_children.find(name);

		return nodeIt != m_children.cend() ? nodeIt->second : nullptr;
	}

	bool
	Node::destroyChild (const std::string & name) noexcept
	{
		const auto nodeIt = m_children.find(name);

		if ( nodeIt == m_children.end() )
		{
			return false;
		}

		m_children.erase(nodeIt);

		return true;
	}

	CartesianFrame< float >
	Node::getWorldCartesianFrame () const noexcept
	{
		/* NOTE: As root, return the origin !
		 * If the parent is the root node, just return the frame. */
		if ( this->isRoot() || this->parent()->isRoot() )
		{
			return m_cartesianFrame;
		}

		/* Stack up a reversed tree for each cartesian frame. */
		std::stack< CartesianFrame< float > > reversedTree;

		{
			const auto * node = this;

			/* While parent is not root. */
			while ( node != nullptr )
			{
				reversedTree.emplace(node->m_cartesianFrame);

				node = node->m_parent.lock().get();
			}
		}

		Matrix< 4, float > matrix;
		Vector< 3, float > scalingVector{1.0F, 1.0F, 1.0F};

		while ( !reversedTree.empty() )
		{
			matrix *= reversedTree.top().getModelMatrix();
			scalingVector *= reversedTree.top().scalingFactor();

			reversedTree.pop();
		}

		return CartesianFrame< float >{matrix, scalingVector};
	}
}
