/*
 * Emeraude/Scenes/NodeController.hpp
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
#include <vector>
#include <memory>

/* Local inclusions for inheritances. */
#include "Input/KeyboardListenerInterface.hpp"

/* Local inclusions for usages. */
#include "Input/GamepadController.hpp"
#include "Node.hpp"

namespace Emeraude::Scenes
{
	/**
	 * @brief The NodeController class
	 * @extends Emeraude::Input::KeyboardListenerInterface
	 */
	class NodeController final : public Input::KeyboardListenerInterface
	{
		public:

			static constexpr auto ClassId{"NodeController"};

			/**
			 * @brief Constructor.
			 * @param node The initial node.
			 */
			explicit NodeController (const std::shared_ptr< Node > & node = {}) noexcept;

			/**
			 * @brief Adds a new scene node to the list of controllable scene nodes.
			 * @param node The scene node.
			 */
			void addNode (const std::shared_ptr< Node > & node) noexcept;

			/**
			 * @brief Removes a scene node from the list of controllable scene nodes.
			 * @param node The scene node.
			 */
			void removeNode (const std::shared_ptr< Node > & node) noexcept;

			/**
			 * @brief Enables a gamepad controller over this node.
			 * @param id The ID of the device. The first is 0.
			 * @param moveSpeed Set a step value to move the node.
			 * @param rotationSpeed Set the rate of speed to rotate the node.
			 * @return bool
			 */
			bool enableController (int id, float moveSpeed = 6.0F, float rotationSpeed = 1.0F) noexcept;

			/**
			 * @brief Checks the controller buttons. This should be called in logic process loop.
			 * @param cycle The current logic cycle.
			 */
			void update (size_t cycle) noexcept;

			/** @brief Clears every registered scene nodes. */
			void clear () noexcept;

		private:

			/**
			 * @brief On key release event handler.
			 * @param key The keyboard universal key code.
			 * @param scanCode The system-dependent key code.
			 * @param modifiers The modifier keys mask.
			 * @return bool
			 */
			bool onKeyRelease (int key, int scanCode, int modifiers) noexcept override;

			/**
			 * @brief getPreviousNode
			 */
			void getPreviousNode () noexcept;

			/**
			 * @brief nextNode
			 */
			void nextNode () noexcept;

			/**
			 * @brief switchTransformSpace
			 */
			void switchTransformSpace () noexcept;

			/**
			 * @brief switchControlMode
			 */
			void switchControlMode () noexcept;

			std::vector< std::shared_ptr< Node > > m_selectables{};
			std::shared_ptr< Node > m_selected{};
			Libraries::Math::TransformSpace m_transformSpace = Libraries::Math::TransformSpace::Parent;
			Input::GamepadController m_controller{};
			float m_controllerMSpeed = 6.0F;
			float m_controllerRSpeed = 1.0F;
			bool m_nodeRotationMode = false;
	};
}
