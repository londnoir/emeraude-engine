/*
 * Emeraude/Scenes/AbstractComponent.hpp
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
#include <memory>

/* Local inclusions for inheritances. */
#include "NamedItem.hpp"
#include "Observable.hpp"
#include "Animations/AnimatableInterface.hpp"

/* Local inclusions for usages. */
#include "Physics/PhysicalObjectProperties.hpp"
#include "Math/Vector.hpp"
#include "Math/Cuboid.hpp"
#include "Math/Sphere.hpp"

/* Third-party libraries */
#include "Third-Party-Inclusion/json.hpp"

/* Forward declarations. */
namespace Emeraude
{
	namespace Graphics::RenderableInstance
	{
		class Abstract;
	}

	namespace Scenes
	{
		class Scene;
		class AbstractEntity;
	}
}

namespace Emeraude::Scenes
{
	/**
	 * @brief Class that hold the base of every component that can be attached to a entity.
	 * @extends Libraries::NamedItem Each component is named.
	 * @extends Libraries::Observable To transfer physical properties changes.
	 * @extends Animations::AnimatableInterface Component are animatable.
	 */
	class AbstractComponent : public Libraries::NamedItem, public Libraries::Observable, public Animations::AnimatableInterface
	{
		public:

			/** @brief Observable notification codes. */
			enum NotificationCode
			{
				PropertiesChanged,
				RemoveBrokenComponent,
				/* Enumeration boundary. */
				MaxEnum
			};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Destructs the abstract entity component.
			 */
			~AbstractComponent () override = default;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractComponent (const AbstractComponent & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractComponent (AbstractComponent && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			AbstractComponent & operator= (const AbstractComponent & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			AbstractComponent & operator= (AbstractComponent && copy) noexcept = delete;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/**
			 * @brief Returns the entity where this entity is attached.
			 * @return const AbstractEntity &
			 */
			[[nodiscard]]
			virtual const AbstractEntity & parentEntity () const noexcept final;

			/**
			 * @brief Returns whether the parent entity has the movable trait.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isParentEntityMovable () const noexcept final;

			/**
			 * @brief Initializes that entity from JSON rules.
			 * @param jsonData A native json value from project JsonCpp.
			 * @return bool
			 */
			virtual bool initialize (const Json::Value & jsonData) noexcept;

			/**
			 * @brief Returns true if the component is renderable.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isRenderable () const noexcept final;

			/**
			 * @brief Returns to the renderable instance, if component is visual.
			 * @warning Can be null !
			 * @return const Graphics::RenderableInstance::Abstract *
			 */
			[[nodiscard]]
			virtual const Graphics::RenderableInstance::Abstract * getRenderableInstance () const noexcept;

			/**
			 * @brief Returns to the renderable instance, if component is visual.
			 * @warning Can be null !
			 * @return Graphics::RenderableInstance::Abstract *
			 */
			[[nodiscard]]
			virtual Graphics::RenderableInstance::Abstract * getRenderableInstance () noexcept;

			/**
			 * @brief Returns the local bounding box of this component.
			 * @note Can be invalid.
			 * @return const Cuboid< float > &
			 */
			[[nodiscard]]
			virtual const Libraries::Math::Cuboid< float > & boundingBox () const noexcept final;

			/**
			 * @brief Returns the local bounding box of this component.
			 * @note Can be invalid.
			 * @return const Cuboid< float > &
			 */
			[[nodiscard]]
			virtual Libraries::Math::Cuboid< float > & boundingBox () noexcept final;

			/**
			 * @brief Returns the local bounding sphere of this component.
			 * @note Can be invalid.
			 * @return const Sphere< float > &
			 */
			[[nodiscard]]
			virtual const Libraries::Math::Sphere< float > & boundingSphere () const noexcept final;

			/**
			 * @brief Returns the local bounding sphere of this component.
			 * @note Can be invalid.
			 * @return const Sphere< float > &
			 */
			[[nodiscard]]
			virtual Libraries::Math::Sphere< float > & boundingSphere () noexcept final;

			/**
			 * @brief Returns physical properties of the component.
			 * @return const Properties &
			 */
			[[nodiscard]]
			virtual const Physics::PhysicalObjectProperties & physicalObjectProperties () const noexcept final;

			/**
			 * @brief Returns physical properties of the component.
			 * @return const Properties &
			 */
			[[nodiscard]]
			virtual Physics::PhysicalObjectProperties & physicalObjectProperties () noexcept final;

			/**
			 * @brief Returns the absolute coordinates of this component using parent node.
			 * @return Libraries::Math::Coordinates< float >
			 */
			[[nodiscard]]
			virtual Libraries::Math::Coordinates< float > getWorldCoordinates () const noexcept final;

			/**
			 * @brief Returns the absolute velocity of this component using parent node.
			 * @return Libraries::Math::Vector< 3, float >
			 */
			[[nodiscard]]
			virtual Libraries::Math::Vector< 3, float > getWorldVelocity () const noexcept final;

			/**
			 * @brief Returns the type of component.
			 * @return const char *
			 */
			[[nodiscard]]
			virtual const char * getComponentType () const noexcept = 0;

			/**
			 * @brief This method is called when the entity is moved in the scene.
			 */
			virtual void move () noexcept = 0;

			/**
			 * @brief This method is called when the entity is updated by the core logic every cycle.
			 * @param scene A reference to the scene.
			 * @param cycle The engine cycle number.
			 */
			virtual void processLogics (const Scene & scene, size_t cycle) noexcept = 0;

		protected:

			/**
			 * @brief Constructs an abstract entity component.
			 * @param name The name of the component.
			 * @param parentEntity A reference to the parent entity.
			 */
			AbstractComponent (const std::string & name, const AbstractEntity & parentEntity) noexcept;

		private:

			const AbstractEntity & m_parentEntity;
			Libraries::Math::Cuboid< float > m_boundingBox{};
			Libraries::Math::Sphere< float > m_boundingSphere{};
			Physics::PhysicalObjectProperties m_physicalObjectProperties{};
	};
}
