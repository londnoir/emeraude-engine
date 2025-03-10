/*
 * src/Libraries/Node.hpp
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
#include <map>
#include <memory>
#include <string>

/* Local inclusions for usages. */
#include "Math/CartesianFrame.hpp"

namespace Libraries
{
	/**
	 * @brief Node class to define a skin.
	 * @extends std::enable_shared_from_this< Node >
	 */
	class Node : public std::enable_shared_from_this< Node >
	{
		public:

			static constexpr auto Root{"Root"};

			/**
			 * @brief Constructs the root node.
			 */
			Node () noexcept = default;

			/**
			 * @brief Constructs a child node.
			 * @param parent a reference to the smart pointer of the parent.
			 * @param coordinates A reference to a coordinates. Default Origin.
			 */
			explicit Node (const std::shared_ptr< Node > & parent, const Math::CartesianFrame< float > & coordinates = {}) noexcept;

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
			 * @return node &
			 */
			Node & operator= (const Node & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return node &
			 */
			Node & operator= (Node && copy) noexcept = delete;

			/**
			 * @brief Destructs the node.
			 */
			virtual ~Node () = default;

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
			 * @param coordinates Set the coordinates of the new node. Default Origin.
			 * @return std::shared_ptr< Node >
			 */
			[[nodiscard]]
			std::shared_ptr< Node > createChild (const std::string & name, const Math::CartesianFrame< float > & coordinates = {}) noexcept;

			/**
			 * @brief Creates a sub node at a given position.
			 * @warning If the node already exists, the method will return a null pointer.
			 * @param name A reference to a string.
			 * @param position Set the position of the new node.
			 * @return std::shared_ptr< Node >
			 */
			[[nodiscard]]
			std::shared_ptr< Node >
			createChild (const std::string & name, const Math::Vector< 3, float > & position) noexcept
			{
				return this->createChild(name, Math::CartesianFrame< float >{position});
			}

			/**
			 * @brief Returns a child by its name.
			 * @warning Can be nullptr !
			 * @param name A reference to a string.
			 * @return std::shared_ptr< Node >
			 */
			[[nodiscard]]
			std::shared_ptr< Node > findChild (const std::string & name) const noexcept;

			/**
			 * @brief Destroys a child by its name and returns true if the child existed.
			 * @param name A reference to a string.
			 * @return bool
			 */
			bool destroyChild (const std::string & name) noexcept;

			/**
			 * @brief Destroys children.
			 * @return void
			 */
			void
			destroyChildren () noexcept
			{
				m_children.clear();
			}

			/**
			* @brief Returns the cartesian frame in local space.
			* @return const Math::CartesianFrame< float > &
			*/
			[[nodiscard]]
			const Math::CartesianFrame< float > &
			cartesianFrame () const noexcept
			{
				return m_cartesianFrame;
			}

			/**
			 * @brief Returns the cartesian frame in local space.
			 * @return Math::CartesianFrame< float > &
			 */
			[[nodiscard]]
			Math::CartesianFrame< float > &
			cartesianFrame () noexcept
			{
				return m_cartesianFrame;
			}

			/**
			 * @brief Returns the cartesian frame in world space.
			 * @return Math::CartesianFrame< float >
			 */
			[[nodiscard]]
			Math::CartesianFrame< float > getWorldCartesianFrame () const noexcept;

		private:

			/* NOTE : If nullptr, this node is the root. */
			std::weak_ptr< Node > m_parent;
			std::map< std::string, std::shared_ptr< Node > > m_children;
			Math::CartesianFrame< float > m_cartesianFrame;
	};
}
