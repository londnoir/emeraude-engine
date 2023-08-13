/*
 * Emeraude/Scenes/NodeController.cpp
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

#include "NodeController.hpp"

/* Local inclusions */
#include "Tracer.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Libraries::Math;

	NodeController::NodeController (const std::shared_ptr< Node > & node) noexcept
		: Input::KeyboardListenerInterface(true, false, false)
	{
		this->addNode(node);
	}

	void
	NodeController::getPreviousNode () noexcept
	{
		if ( m_selectables.empty() )
		{
			Tracer::info(ClassId, "No selectable Node !");

			return;
		}

		Tracer::info(ClassId, Blob() << m_selectables.size() << " selectable Nodes.");

		for ( auto it = m_selectables.begin(); it != m_selectables.end(); ++it )
		{
			if ( *it == m_selected )
			{
				if ( it == m_selectables.begin() )
					m_selected = m_selectables.back();
				else
					m_selected = (*--it);
				break;
			}
		}

		Tracer::info(ClassId, Blob() << "Node selected : " << m_selected->name());
	}

	void
	NodeController::nextNode () noexcept
	{
		if ( m_selectables.empty() )
		{
			Tracer::info(ClassId, "No selectable Node !");

			return;
		}

		Tracer::info(ClassId, Blob() << m_selectables.size() << " selectable Nodes.");

		for ( auto it = m_selectables.begin(); it != m_selectables.end(); ++it )
		{
			if ( *it == m_selected )
			{
				it++;

				if ( it == m_selectables.end() )
					m_selected = *m_selectables.begin();
				else
					m_selected = *it;

				break;
			}
		}

		Tracer::info(ClassId, Blob() << "Node selected : " << m_selected->name());
	}

	void
	NodeController::switchTransformSpace () noexcept
	{
		switch ( m_transformSpace )
		{
			case TransformSpace::Local :
				m_transformSpace = TransformSpace::Parent;

				Tracer::info(ClassId, "Transform space : Parent.");
				break;

			case TransformSpace::Parent :
				m_transformSpace = TransformSpace::World;

				Tracer::info(ClassId, "Transform space : World.");
				break;

			case TransformSpace::World :
				m_transformSpace = TransformSpace::Local;

				Tracer::info(ClassId, "Transform space : Local.");
				break;
		}
	}

	void
	NodeController::switchControlMode () noexcept
	{
		if ( m_nodeRotationMode )
		{
			m_transformSpace = TransformSpace::Parent;
			m_nodeRotationMode = false;

			Tracer::info(ClassId, "Translation mode (Parent transform space).");
		}
		else
		{
			m_transformSpace = TransformSpace::Local;
			m_nodeRotationMode = true;

			Tracer::info(ClassId, "Rotation mode (Local transform space).");
		}
	}

	void
	NodeController::addNode (const std::shared_ptr< Node > & node) noexcept
	{
		m_selectables.emplace_back(node);

		if ( m_selected == nullptr )
			m_selected = node;
	}

	void
	NodeController::removeNode (const std::shared_ptr< Node > & node) noexcept
	{
		for ( auto it = m_selectables.begin(); it != m_selectables.end(); ++it )
		{
			if ( *it == node )
			{
				m_selectables.erase(it);

				break;
			}
		}

		if ( m_selected == node )
			m_selected.reset();
	}

	bool
	NodeController::enableController (int id, float moveSpeed, float rotationSpeed) noexcept
	{
		m_controller.attachDeviceID(id);
		m_controllerMSpeed = moveSpeed;
		m_controllerRSpeed = rotationSpeed;

		return true;
	}

	bool
	NodeController::onKeyRelease (int key, int, int) noexcept
	{
		switch ( key )
		{
			case Input::KeyPad7 :
			case Input::KeyPad4 :
			case Input::KeyPad8 :
			case Input::KeyPad5 :
			case Input::KeyPad9 :
			case Input::KeyPad6 :
				if ( m_selected != nullptr )
				{
					const char * action = nullptr;

					if ( m_nodeRotationMode )
					{
						switch ( key )
						{
							/* Rotate targeted scene node on X axis. */
							case Input::KeyPad7 :
								m_selected->yaw(+Math::Radian(5.0F), m_transformSpace);

								action = "Yaw+";
								break;

							case Input::KeyPad4 :
								m_selected->yaw(-Math::Radian(5.0F), m_transformSpace);

								action = "Yaw-";
								break;

							/* Rotate targeted scene node on Y axis. */
							case Input::KeyPad8 :
								m_selected->pitch(+Math::Radian(5.0F), m_transformSpace);

								action = "Pitch+";
								break;

							case Input::KeyPad5 :
								m_selected->pitch(-Math::Radian(5.0F), m_transformSpace);

								action = "Pitch-";
								break;

							/* Rotate targeted scene node on Z axis. */
							case Input::KeyPad9 :
								m_selected->roll(+Math::Radian(5.0F), m_transformSpace);

								action = "Roll+";
								break;

							case Input::KeyPad6 :
								m_selected->roll(-Math::Radian(5.0F), m_transformSpace);

								action = "Roll-";
								break;
						}
					}
					else
					{
						switch ( key )
						{
							/* Move targeted scene node on X axis. */
							case Input::KeyPad7 :
								m_selected->moveOnXAxisBy(0.5F, m_transformSpace);

								action = "X+";
								break;

							case Input::KeyPad4 :
								m_selected->moveOnXAxisBy(-0.5F, m_transformSpace);

								action = "X-";
								break;

							/* Move targeted scene node on Y axis. */
							case Input::KeyPad8 :
								m_selected->moveOnYAxisBy(0.5F, m_transformSpace);

								action = "Y+";
								break;

							case Input::KeyPad5 :
								m_selected->moveOnYAxisBy(-0.5F, m_transformSpace);

								action = "Y-";
								break;

							/* Move targeted scene node on Z axis. */
							case Input::KeyPad9 :
								m_selected->moveOnZAxisBy(0.5F, m_transformSpace);

								action = "Z+";
								break;

							case Input::KeyPad6 :
								m_selected->moveOnZAxisBy(-0.5F, m_transformSpace);

								action = "Z-";
								break;
						}
					}

					switch ( m_transformSpace )
					{
						case TransformSpace::Local :
							Tracer::info(ClassId, Blob() << action << " in parent local.");
							break;

						case TransformSpace::Parent :
							Tracer::info(ClassId, Blob() << action << " in parent parent.");
							break;

						case TransformSpace::World :
							Tracer::info(ClassId, Blob() << action << " in parent world.");
							break;
					}
				}
				else
				{
					Tracer::info(ClassId, "No Node selected.");
				}
				return true;

			/* Select targeted scene node. */
			case Input::KeyPad1 :
				this->getPreviousNode();

				return true;

			case Input::KeyPad3 :
				this->nextNode();

				return true;

			/* Switch between Rotate and move. */
			case Input::KeyPad2 :
				this->switchControlMode();

				return true;

			/* Switch between transform space. */
			case Input::KeyPad0 :
				this->switchTransformSpace();

				return true;
		}

		return false;
	}

	void
	NodeController::update (size_t) noexcept
	{
		using namespace Input;

		if ( m_selected == nullptr )
			return;

		if ( m_controller.isConnected() )
		{
			if ( m_controller.isButtonPressed(ButtonX) )
			{
				if ( m_controller.isButtonPressed(ButtonDPadUp) )
					m_selected->moveOnYAxisBy(m_controllerMSpeed, TransformSpace::Local);

				if ( m_controller.isButtonPressed(ButtonDPadDown) )
					m_selected->moveOnYAxisBy(-m_controllerMSpeed, TransformSpace::Local);

				if ( m_controller.isButtonPressed(ButtonDPadLeft) )
					m_selected->moveOnXAxisBy(-m_controllerMSpeed, TransformSpace::Local);

				if ( m_controller.isButtonPressed(ButtonDPadRight) )
					m_selected->moveOnXAxisBy(m_controllerMSpeed, TransformSpace::Local);

				if ( m_controller.isButtonPressed(ButtonLeftBumper) )
					m_selected->roll(Math::Radian(m_controllerRSpeed));

				if ( m_controller.isButtonPressed(ButtonRightBumper) )
					m_selected->roll(-Math::Radian(m_controllerRSpeed));
			}
			else if ( m_controller.isButtonPressed(ButtonY) )
			{
				if ( m_controller.isButtonPressed(ButtonDPadUp) )
					m_selected->moveOnZAxisBy(-m_controllerMSpeed, TransformSpace::Local);

				if ( m_controller.isButtonPressed(ButtonDPadDown) )
					m_selected->moveOnZAxisBy(m_controllerMSpeed, TransformSpace::Local);

				if ( m_controller.isButtonPressed(ButtonDPadLeft) )
					m_selected->moveOnXAxisBy(-m_controllerMSpeed, TransformSpace::Local);

				if ( m_controller.isButtonPressed(ButtonDPadRight) )
					m_selected->moveOnXAxisBy(m_controllerMSpeed, TransformSpace::Local);

				if ( m_controller.isButtonPressed(ButtonLeftBumper) )
					m_selected->moveOnYAxisBy(m_controllerMSpeed, TransformSpace::Local);

				if ( m_controller.isButtonPressed(ButtonRightBumper) )
					m_selected->moveOnYAxisBy(-m_controllerMSpeed, TransformSpace::Local);
			}
			else
			{
				if ( m_controller.isButtonPressed(ButtonDPadUp) )
					m_selected->moveOnZAxisBy(-m_controllerMSpeed, TransformSpace::Local);

				if ( m_controller.isButtonPressed(ButtonDPadDown) )
					m_selected->moveOnZAxisBy(m_controllerMSpeed, TransformSpace::Local);

				if ( m_controller.isButtonPressed(ButtonDPadLeft) )
					m_selected->yaw(Math::Radian(m_controllerRSpeed), TransformSpace::World);

				if ( m_controller.isButtonPressed(ButtonDPadRight) )
					m_selected->yaw(-Math::Radian(m_controllerRSpeed), TransformSpace::World);

				if ( m_controller.isButtonPressed(ButtonLeftBumper) )
					m_selected->pitch(-Math::Radian(m_controllerRSpeed));

				if ( m_controller.isButtonPressed(ButtonRightBumper) )
					m_selected->pitch(Math::Radian(m_controllerRSpeed));
			}
		}
	}

	void
	NodeController::clear () noexcept
	{
		m_selected.reset();

		m_selectables.clear();
	}
}
