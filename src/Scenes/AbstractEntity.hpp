/*
 * Emeraude/Scenes/AbstractEntity.hpp
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
#include <array>
#include <unordered_set>
#include <memory>
#include <functional>

/* Local inclusions for inheritances. */
#include "AbstractOctreeElement.hpp"
#include "Physics/PhysicalInterface.hpp"
#include "Observable.hpp"
#include "Observer.hpp"

/* Local inclusions for usages. */
#include "Physics/PhysicalObjectProperties.hpp"
#include "OctreeSector.hpp"
/* Components lists */
#include "AbstractComponent.hpp"
#include "Camera.hpp"
#include "Microphone.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "SpotLight.hpp"
#include "SoundEmitter.hpp"
#include "VisualComponent.hpp"
#include "MultipleVisualsComponent.hpp"
#include "ParticlesEmitter.hpp"
#include "DirectionalPushModifier.hpp"
#include "SphericalPushModifier.hpp"
#include "Weight.hpp"

namespace Emeraude::Scenes
{
	/**
	 * @brief Defines the base of something in the 3D world composed with components.
	 * @extends std::enable_shared_from_this< AbstractEntity > To self replicate with smart pointer.
	 * @extends Emeraude::Scenes::AbstractOctreeElement An entity is insertable to the octree system.
	 * @extends Emeraude::Physics::PhysicalInterface A movable entity has physical properties to interact with other entities from the 3D world.
	 * @extends Libraries::Observer An entity listen to its components.
	 * @extends Libraries::Observable An entity is observable to notify its content modification easily.
	 */
	class AbstractEntity : public std::enable_shared_from_this< AbstractEntity >, public AbstractOctreeElement, virtual public Physics::PhysicalInterface, public Libraries::Observer, public Libraries::Observable
	{
		friend class OctreeSector;

		public:

			/** @brief Observable notification codes. */
			enum NotificationCode
			{
				/* Main notifications */
				ContentModified,
				ComponentCreated,
				ComponentDestroyed,
				ModifierCreated,
				ModifierDestroyed,
				/* Specific component notifications */
				CameraCreated,
				PrimaryCameraCreated,
				CameraDestroyed,
				MicrophoneCreated,
				PrimaryMicrophoneCreated,
				MicrophoneDestroyed,
				DirectionalLightCreated,
				DirectionalLightDestroyed,
				PointLightCreated,
				PointLightDestroyed,
				SpotLightCreated,
				SpotLightDestroyed,
				SoundEmitterCreated,
				SoundEmitterDestroyed,
				VisualComponentCreated,
				VisualComponentDestroyed,
				MultipleVisualsComponentCreated,
				MultipleVisualsComponentDestroyed,
				ParticlesEmitterCreated,
				ParticlesEmitterDestroyed,
				DirectionalPushModifierCreated,
				DirectionalPushModifierDestroyed,
				SphericalPushModifierCreated,
				SphericalPushModifierDestroyed,
				WeightCreated,
				WeightDestroyed,
				/* Enumeration boundary. */
				MaxEnum
			};

			/**
			 * @brief Destructs the abstract entity.
			 */
			~AbstractEntity () override = default;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractEntity (const AbstractEntity & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractEntity (AbstractEntity && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			AbstractEntity & operator= (const AbstractEntity & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			AbstractEntity & operator= (AbstractEntity && copy) noexcept = delete;

			/** @copydoc Emeraude::Scenes::LocatableInterface::localBoundingBox() const */
			[[nodiscard]]
			const Libraries::Math::Cuboid< float > & localBoundingBox () const noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::localBoundingSphere() const */
			[[nodiscard]]
			const Libraries::Math::Sphere< float > & localBoundingSphere () const noexcept override;

			/** @copydoc Emeraude::Physics::PhysicalInterface::physicalObjectProperties() const */
			const Physics::PhysicalObjectProperties & physicalObjectProperties () const noexcept override;

			/** @copydoc Emeraude::Physics::PhysicalInterface::physicalObjectProperties() */
			Physics::PhysicalObjectProperties & physicalObjectProperties () noexcept override;

			/**
			 * @brief Updates components when the holder is moving.
			 */
			virtual void move () noexcept final;

			/**
			 * @brief Returns the holding scene.
			 * @return Scene *
			 */
			[[nodiscard]]
			virtual Scene * parentScene () const noexcept final;

			/**
			 * @brief Returns whether a named component exists in the entity.
			 * @param name The name of the component.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool containsComponent (const std::string & name) const noexcept final;

			/**
			 * @brief Returns whether a component is part of this entity.
			 * @param component A reference to the component smart pointer.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool containsComponent (const std::shared_ptr< AbstractComponent > & component) const noexcept final;

			/**
			 * @brief Returns the component list of this entity.
			 * @return const std::map< std::string, std::shared_ptr< AbstractComponent > > &
			 */
			[[nodiscard]]
			virtual const std::map< std::string, std::shared_ptr< AbstractComponent > > & components () const noexcept final;

			/**
			 * @brief Returns the component list of this entity.
			 * @return std::map< std::string, std::shared_ptr< AbstractComponent > > &
			 */
			[[nodiscard]]
			virtual std::map< std::string, std::shared_ptr< AbstractComponent > > & components () noexcept final;

			/**
			 * @brief Returns a possible named component from the entity.
			 * @param name The name of the component.
			 * @return std::shared_ptr< AbstractComponent >
			 */
			[[nodiscard]]
			virtual std::shared_ptr< AbstractComponent > getComponent (const std::string & name) const noexcept final;

			/**
			 * @brief Removes a component by his name from this entity. Returns true whether the component existed.
			 * @param name The name of the component.
			 * @return bool
			 */
			virtual bool removeComponent (const std::string & name) noexcept final;

			/**
			 * @brief Removes a component by its pointer from this entity. Returns true whether the component existed.
			 * @param name The name of the component.
			 * @return bool
			 */
			virtual bool removeComponent (const std::shared_ptr< AbstractComponent > & component) noexcept final;

			/**
			 * @brief Removes all components.
			 * @return void
			 */
			virtual void clearComponents () noexcept final;

			/**
			 * @brief Reads something on each component of the entity.
			 * @param lambda A reference to a function using the signature "bool method (const AbstractComponent & component)".
			 * @return void
			 */
			virtual void forEachComponent (const std::function< bool (const AbstractComponent & component) > & lambda) const noexcept final;

			/**
			 * @brief Reads something on each component of the entity.
			 * @param lambda A reference to a function using the signature "bool method (const AbstractComponent & component, int index)".
			 * @return void
			 */
			virtual void forEachComponent (const std::function< bool (const AbstractComponent & component, size_t index) > & lambda) const noexcept final;

			/**
			 * @brief Modifies something on each component of the entity.
			 * @param lambda A reference to a function using the signature "bool method (const AbstractComponent & component)".
			 * @return void
			 */
			virtual void forEachComponent (const std::function< bool (AbstractComponent & component) > & lambda) noexcept final;

			/**
			 * @brief Modifies something on each component of the entity.
			 * @param lambda A reference to a function using the signature "bool method (const AbstractComponent & component, int index)".
			 * @return void
			 */
			virtual void forEachComponent (const std::function< bool (AbstractComponent & component, size_t index) > & lambda) noexcept final;

			/**
			 * @brief Creates a camera.
			 * @param componentName The name of the component. Default "Camera".
			 * @param primaryDevice Set this device as primary one. Default false.
			 * @param enableModel Enables a model to visualize the camera. Default false.
			 * @return std::shared_ptr< Camera >
			 */
			virtual std::shared_ptr< Camera > newCamera (const std::string & componentName = "Camera", bool primaryDevice = false, bool enableModel = false) noexcept final;

			/**
			 * @brief Creates an orthographic camera.
			 * @param componentName The name of the component. Default "OrthographicCamera".
			 * @param primaryDevice Set this device as primary one. Default false.
			 * @param enableModel Enables a model to visualize the camera. Default false.
			 * @return std::shared_ptr< Camera >
			 */
			virtual std::shared_ptr< Camera > newOrthographicCamera (const std::string & componentName = "OrthographicCamera", bool primaryDevice = false, bool enableModel = false) noexcept final;

			/**
			 * @brief Creates a microphone.
			 * @param componentName The name of the component. Default "Microphone".
			 * @param primaryDevice Set this device as primary one. Default false.
			 * @return std::shared_ptr< Microphone >
			 */
			virtual std::shared_ptr< Microphone > newMicrophone (const std::string & componentName = "Microphone", bool primaryDevice = false) noexcept final;

			/**
			 * @brief Creates a directional light emitter.
			 * @param componentName The name of the component. Default "DirectionalLight".
			 * @return std::shared_ptr< DirectionalLight >
			 */
			virtual std::shared_ptr< DirectionalLight > newDirectionalLight (const std::string & componentName = "DirectionalLight") noexcept final;

			/**
			 * @brief Creates a point light emitter.
			 * @param componentName The name of the component. Default "PointLight".
			 * @return std::shared_ptr< PointLight >
			 */
			virtual std::shared_ptr< PointLight > newPointLight (const std::string & componentName = "PointLight") noexcept final;

			/**
			 * @brief Creates a spot light emitter.
			 * @param componentName The name of the component. Default "SpotLight".
			 * @return std::shared_ptr< SpotLight >
			 */
			virtual std::shared_ptr< SpotLight > newSpotLight (const std::string & componentName = "SpotLight") noexcept final;

			/**
			 * @brief Creates a sound emitter.
			 * @param componentName The name of the component. Default "SoundEmitter".
			 * @return std::shared_ptr< SoundEmitter >
			 */
			virtual std::shared_ptr< SoundEmitter > newSoundEmitter (const std::string & componentName = "SoundEmitter") noexcept final;

			/**
			 * @brief Creates a sound emitter and provide a sound.
			 * @param resource A reference to a sound resource smart pointer to play.
			 * @param loop Set the loop state. Default true.
			 * @param componentName The name of the component. Default "SoundEmitter".
			 * @return std::shared_ptr< SoundEmitter >
			 */
			virtual std::shared_ptr< SoundEmitter > newSoundEmitter (const std::shared_ptr< Audio::SoundResource > & resource, bool loop = true, const std::string & componentName = "SoundEmitter") noexcept final;

			/**
			 * @brief Creates a mesh instance.
			 * @param resource a reference to a mesh resource smart pointer.
			 * @param componentName The name of the component. Default "VisualComponent".
			 * @return std::shared_ptr< VisualComponent >
			 */
			virtual std::shared_ptr< VisualComponent > newMeshInstance (const std::shared_ptr< Graphics::Renderable::MeshResource > & resource, const std::string & componentName = "VisualComponent") noexcept final;

			/**
			 * @brief Creates a sprite instance.
			 * @param resource a reference to a sprite resource smart pointer.
			 * @param componentName The name of the component. Default "VisualComponent".
			 * @return std::shared_ptr< VisualComponent >
			 */
			virtual std::shared_ptr< VisualComponent > newSpriteInstance (const std::shared_ptr< Graphics::Renderable::SpriteResource > & resource, const std::string & componentName = "VisualComponent") noexcept final;

			/**
			 * @brief Creates a multiple mesh instances.
			 * @param resource A reference to a mesh resource smart pointer.
			 * @param coordinates An array of coordinates to place instances.
			 * @param componentName The name of the component. Default "MultipleVisualsComponent".
			 * @return std::shared_ptr< MultipleVisualsComponent >
			 */
			virtual std::shared_ptr< MultipleVisualsComponent > newMeshInstance (const std::shared_ptr< Graphics::Renderable::MeshResource > & resource, const std::vector< Libraries::Math::Coordinates< float > > & coordinates, const std::string & componentName = "MultipleVisualsComponent") noexcept final;

			/**
			 * @brief Creates a multiple sprite instances.
			 * @param resource A reference to a sprite resource smart pointer.
			 * @param coordinates An array of coordinates to place instances.
			 * @param componentName The name of the component. Default "MultipleVisualsComponent".
			 * @return std::shared_ptr< MultipleVisualsComponent >
			 */
			virtual std::shared_ptr< MultipleVisualsComponent > newSpriteInstance (const std::shared_ptr< Graphics::Renderable::SpriteResource > & resource, const std::vector< Libraries::Math::Coordinates< float > > & coordinates, const std::string & componentName = "MultipleVisualsComponent") noexcept final;

			/**
			 * @brief Creates a particles emitter using a sprite resource.
			 * @param resource a reference to a sprite resource smart pointer.
			 * @param maxParticleCount The limit of particles allowed to be generated at once.
			 * @param componentName The name of the component. Default "ParticlesEmitter".
			 * @return std::shared_ptr< ParticlesEmitter >
			 */
			virtual std::shared_ptr< ParticlesEmitter > newParticlesEmitter (const std::shared_ptr< Graphics::Renderable::SpriteResource > & resource, size_t maxParticleCount, const std::string & componentName = "ParticlesEmitter") noexcept final;

			/**
			 * @brief Creates a particles emitter using a mesh resource.
			 * @param resource a reference to a mesh resource smart pointer.
			 * @param maxParticleCount The limit of particles allowed to be generated at once.
			 * @param componentName The name of the component. Default "ParticlesEmitter".
			 * @return std::shared_ptr< ParticlesEmitter >
			 */
			virtual std::shared_ptr< ParticlesEmitter > newParticlesEmitter (const std::shared_ptr< Graphics::Renderable::MeshResource > & resource, size_t maxParticleCount, const std::string & componentName = "ParticlesEmitter") noexcept final;

			/**
			 * @brief Creates a directional push modifier.
			 * @param componentName The name of the component. Default "DirectionalPushModifier".
			 * @return std::shared_ptr< DirectionalPushModifier >
			 */
			virtual std::shared_ptr< DirectionalPushModifier > newDirectionalPushModifier (const std::string & componentName = "DirectionalPushModifier") noexcept final;

			/**
			 * @brief Creates a spherical push modifier.
			 * @param componentName The name of the component. Default "SphericalPushModifier".
			 * @return std::shared_ptr< SphericalPushModifier >
			 */
			virtual std::shared_ptr< SphericalPushModifier > newSphericalPushModifier (const std::string & componentName = "SphericalPushModifier") noexcept final;

			/**
			 * @brief Creates a weight with default properties.
			 * @param componentName The name of the component. Default "Weight".
			 * @return std::shared_ptr< Weight >
			 */
			virtual std::shared_ptr< Weight > newWeight (const std::string & componentName = "Weight") noexcept final;

			/**
			 * @brief Creates a weight with customized properties.
			 * @param initialProperties A reference to a physical object properties.
			 * @param componentName The name of the component. Default "Weight".
			 * @return std::shared_ptr< Weight >
			 */
			virtual std::shared_ptr< Weight > newWeight (const Physics::PhysicalObjectProperties & initialProperties, const std::string & componentName = "Weight") noexcept final;

			/**
			 * @brief Updates components logics from engine cycle.
			 * @param scene A reference to the scene.
			 * @param cycle The engine cycle loop.
			 * @return bool
			 */
			virtual bool processLogics (const Scene & scene, size_t cycle) noexcept = 0;

		protected:

			/**
			 * @brief Constructs an abstract entity.
			 * @param name The name of the entity.
			 * @param parentScene A point of the scene holding this entity.
			 */
			AbstractEntity (const std::string & name, Scene * parentScene) noexcept;

			/**
			 * @brief Sets whether the entity is renderable.
			 * @param state The state of rendering ability.
			 * @return void
			 */
			virtual void setRenderingAbilityState (bool state) noexcept = 0;

			/**
			 * @brief Sets whether the entity has physical properties.
			 * @param state The state of physical ability.
			 * @return void
			 */
			virtual void setPhysicalObjectPropertiesState (bool state) noexcept = 0;

		private:

			/** @copydoc Libraries::Observer::onNotification() */
			[[nodiscard]]
			bool onNotification (const Observable * observable, int notificationCode, const std::any & data) noexcept final;

			/**
			 * @brief Called when a notification is not handled by the entity abstract level.
			 * @note If this function return false, the observer will be automatically detached.
			 * @return bool
			 */
			virtual bool onUnhandledNotification (const Libraries::Observable * observable, int notificationCode, const std::any & data) noexcept = 0;

			/**
			 * @brief This function is called to update entity properties with attached components.
			 * @return void
			 */
			virtual void updateGlobalPhysicalObjectProperties () noexcept final;

			/**
			 * @brief Before creating a new component, this function is called to know if the component name is available.
			 * @param name The name of the component.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool checkComponentNameAvailability (const std::string & name) const noexcept final;

			/**
			 * @brief Adds a component in the entity.
			 * @param name The name of the new component.
			 * @param component A reference to the component smart pointer.
			 * @return bool
			 */
			virtual bool addComponent (const std::string & name, const std::shared_ptr< AbstractComponent > & component) noexcept final;

			/**
			 * @brief Removes a component from the entity.
			 * @param componentIt An iterator from the component map.
			 * @return map< string, shared_ptr< AbstractComponent > >::iterator
			 */
			std::map< std::string, std::shared_ptr< AbstractComponent > >::iterator removeComponent (const std::map< std::string, std::shared_ptr< AbstractComponent > >::iterator & componentIt) noexcept;

			Scene * m_parentScene = nullptr;
			std::map< std::string, std::shared_ptr< AbstractComponent > > m_components{};
			Libraries::Math::Cuboid< float > m_boundingBox{};
			Libraries::Math::Sphere< float > m_boundingSphere{};
			Physics::PhysicalObjectProperties m_physicalObjectProperties{};
	};
}
