/*
 * Emeraude/Scenes/AbstractEntity.cpp
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

#include "AbstractEntity.hpp"

/* Local inclusions */
#include "Tracer.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Graphics;
	using namespace Physics;

	constexpr auto TracerTag{"AbstractEntity"};

	AbstractEntity::AbstractEntity (const std::string & name, Scene * parentScene) noexcept
		: AbstractOctreeElement(name), m_parentScene(parentScene)
	{

	}

	bool
	AbstractEntity::onNotification (const Observable * observable, int notificationCode, const std::any & data) noexcept
	{
		if ( observable->is(AbstractComponent::ClassUID) )
		{
			/* Checks components notifications. */
			for ( auto componentIt = m_components.begin(); componentIt != m_components.end(); ++componentIt )
			{
				/* Not the right component. */
				if ( componentIt->second.get() != observable )
				{
					continue;
				}

				switch ( notificationCode )
				{
					case AbstractComponent::PropertiesChanged :
						this->updateGlobalPhysicalObjectProperties();
						break;

					case AbstractComponent::RemoveBrokenComponent :
						TraceInfo{TracerTag} << "Removing the broken component '" << componentIt->first << "' !";

						m_components.erase(componentIt);
						break;

					default:
						break;
				}

				return true;
			}
		}

		/* Let child class look after the notification. */
		return this->onUnhandledNotification(observable, notificationCode, data);
	}

	const PhysicalObjectProperties &
	AbstractEntity::physicalObjectProperties () const noexcept
	{
		return m_physicalObjectProperties;
	}

	PhysicalObjectProperties &
	AbstractEntity::physicalObjectProperties () noexcept
	{
		return m_physicalObjectProperties;
	}

	Scene *
	AbstractEntity::parentScene () const noexcept
	{
		return m_parentScene;
	}

	void
	AbstractEntity::updateGlobalPhysicalObjectProperties () noexcept
	{
		auto physicalEntityCount = 0;

		/* Reset properties to node base properties. */
		auto surface = 0.0F;
		auto mass = 0.0F;
		auto dragCoefficient = 0.0F;
		auto bounciness = 0.0F;
		auto stickiness = 0.0F;

		this->setRenderingAbilityState(false);

		/* Reset the bounding box to make a valid
		 * bounding boxes merging from entities. */
		m_boundingBox.reset();
		m_boundingSphere.reset();

		for ( const auto & componentPair : m_components )
		{
			const auto & component = componentPair.second;
			const auto & physicalObjectProperties = component->physicalObjectProperties();

			/* Gets physical properties of a component only if it's a physical object. */
			if ( !physicalObjectProperties.isMassNull() )
			{
				surface += physicalObjectProperties.surface();
				mass += physicalObjectProperties.mass();

				dragCoefficient += physicalObjectProperties.dragCoefficient();
				bounciness += physicalObjectProperties.bounciness();
				stickiness += physicalObjectProperties.stickiness();

				physicalEntityCount++;
			}

			/* Checks render ability. */
			if ( component->isRenderable() )
			{
				this->setRenderingAbilityState(true);
			}

			/* Merge the component local bounding shapes to the scene node local bounding shapes. */
			m_boundingBox.merge(component->boundingBox());
			m_boundingSphere.merge(component->boundingSphere());
		}

		if ( physicalEntityCount > 0 )
		{
			const auto div = static_cast< float >(physicalEntityCount);

			m_physicalObjectProperties.setProperties(
				mass,
				surface,
				dragCoefficient / div,
				clampToUnit(bounciness / div),
				clampToUnit(stickiness / div)
			);

			this->setPhysicalObjectPropertiesState(true);
		}
		else
		{
			m_physicalObjectProperties.reset();

			this->setPhysicalObjectPropertiesState(false);
		}
	}

	void
	AbstractEntity::move () noexcept
	{
		/* NOTE: Dispatch the move to every component. */
		for ( auto & pair : m_components )
		{
			pair.second->move();
		}
	}

	const Cuboid< float > &
	AbstractEntity::localBoundingBox () const noexcept
	{
		return m_boundingBox;
	}

	const Sphere< float > &
	AbstractEntity::localBoundingSphere () const noexcept
	{
		return m_boundingSphere;
	}

	bool
	AbstractEntity::containsComponent (const std::string & name) const noexcept
	{
		return m_components.find(name) != m_components.cend();
	}

	bool
	AbstractEntity::containsComponent (const std::shared_ptr< AbstractComponent > & component) const noexcept
	{
		return std::any_of(m_components.cbegin(), m_components.cend(), [component] (const auto & pair) {
			return pair.second == component;
		});
	}

	bool
	AbstractEntity::checkComponentNameAvailability (const std::string & name) const noexcept
	{
		if ( m_components.contains(name) )
		{
			TraceWarning{TracerTag} <<
				"A component using the '" << name << "' is already present in this entity ! "
				"Creation cancelled.";

			return false;
		}

		return true;
	}

	bool
	AbstractEntity::addComponent (const std::string & name, const std::shared_ptr< AbstractComponent > & component) noexcept
	{
		auto result = m_components.emplace(name, component);

		if ( !result.second )
		{
			TraceError{TracerTag} << "Unable to create the component '" << name << "' !";

			return false;
		}

		this->updateGlobalPhysicalObjectProperties();

		this->observe(component.get());

		this->notify(ContentModified, this->shared_from_this());

		this->notify(ComponentCreated, component);

		return true;
	}

	std::map< std::string, std::shared_ptr< AbstractComponent > >::iterator
	AbstractEntity::removeComponent (const std::map< std::string, std::shared_ptr< AbstractComponent > >::iterator & componentIt) noexcept
	{
		const auto * pointer = componentIt->second.get();

		this->notify(ComponentDestroyed, componentIt->second);

		if ( typeid(*pointer) == typeid(Camera) )
		{
			this->notify(CameraDestroyed, std::static_pointer_cast< Camera >(componentIt->second));
		}
		else if ( typeid(*pointer) == typeid(Microphone) )
		{
			this->notify(MicrophoneDestroyed, std::static_pointer_cast< Microphone >(componentIt->second));
		}
		else if ( typeid(*pointer) == typeid(SphericalPushModifier) || typeid(*pointer) == typeid(DirectionalPushModifier) )
		{
			this->notify(ModifierDestroyed, std::static_pointer_cast< AbstractModifier >(componentIt->second));
		}
		else if ( typeid(*pointer) == typeid(DirectionalLight) )
		{
			this->notify(DirectionalLightDestroyed, std::static_pointer_cast< DirectionalLight >(componentIt->second));
		}
		else if ( typeid(*pointer) == typeid(PointLight) )
		{
			this->notify(PointLightDestroyed, std::static_pointer_cast< PointLight >(componentIt->second));
		}
		else if ( typeid(*pointer) == typeid(SpotLight) )
		{
			this->notify(SpotLightDestroyed, std::static_pointer_cast< SpotLight >(componentIt->second));
		}

		return m_components.erase(componentIt);
	}

	bool
	AbstractEntity::removeComponent (const std::string & name) noexcept
	{
		auto componentIt = m_components.find(name);

		if ( componentIt == m_components.end() )
		{
			TraceWarning{TracerTag} <<
				"No named component '" << name << "' exists. "
				"Deletion skipped.";

			return false;
		}

		this->removeComponent(componentIt);

		this->updateGlobalPhysicalObjectProperties();

		return true;
	}

	bool
	AbstractEntity::removeComponent (const std::shared_ptr< AbstractComponent > & component) noexcept
	{
		for ( auto componentIt = m_components.begin(); componentIt != m_components.end(); ++componentIt )
		{
			if ( componentIt->second != component )
			{
				continue;
			}

			this->removeComponent(componentIt);

			this->updateGlobalPhysicalObjectProperties();

			return true;
		}

		TraceWarning{TracerTag} <<
			"Component " << component.get() << " doesn't exist. "
			"Deletion skipped.";

		return false;
	}

	const std::map< std::string, std::shared_ptr< AbstractComponent > > &
	AbstractEntity::components () const noexcept
	{
		return m_components;
	}

	std::map< std::string, std::shared_ptr< AbstractComponent > > &
	AbstractEntity::components () noexcept
	{
		return m_components;
	}

	std::shared_ptr< AbstractComponent >
	AbstractEntity::getComponent (const std::string & name) const noexcept
	{
		const auto componentIt = m_components.find(name);

		return componentIt != m_components.cend() ? componentIt->second : nullptr;
	}

	void
	AbstractEntity::clearComponents () noexcept
	{
		auto componentIt = std::begin(m_components);

		while ( componentIt != std::end(m_components) )
		{
			componentIt = this->removeComponent(componentIt);
		}

		this->updateGlobalPhysicalObjectProperties();
	}

	void
	AbstractEntity::forEachComponent (const std::function< bool (const AbstractComponent & component) > & lambda) const noexcept
	{
		for ( const auto & item : m_components )
		{
			if ( lambda(*item.second))
			{
				break;
			}
		}
	}

	void
	AbstractEntity::forEachComponent (const std::function< bool (const AbstractComponent & component, size_t index) > & lambda) const noexcept
	{
		for ( auto componentIt = m_components.cbegin(); componentIt != m_components.cend(); ++componentIt )
		{
			const auto index = std::distance(m_components.cbegin(), componentIt);

			if ( !lambda(*componentIt->second, index) )
			{
				break;
			}
		}
	}

	void
	AbstractEntity::forEachComponent (const std::function< bool (AbstractComponent & component) > & lambda) noexcept
	{
		for ( auto & item : m_components )
		{
			if ( lambda(*item.second))
			{
				break;
			}
		}
	}

	void
	AbstractEntity::forEachComponent (const std::function< bool (AbstractComponent & component, size_t index) > & lambda) noexcept
	{
		for ( auto componentIt = m_components.begin(); componentIt != m_components.end(); ++componentIt )
		{
			const auto index = std::distance(m_components.begin(), componentIt);

			if ( !lambda(*componentIt->second, index) )
			{
				break;
			}
		}
	}

	std::shared_ptr< Camera >
	AbstractEntity::newCamera (const std::string & componentName, bool primaryDevice, bool enableModel) noexcept
	{
		if ( !this->checkComponentNameAvailability(componentName) )
		{
			return nullptr;
		}

		auto component = std::make_shared< Camera >(componentName, *this, true);

		/* Registering the smart pointer. */
		if ( !this->addComponent(componentName, component) )
		{
			return nullptr;
		}

		/* Notify the camera creation. */
		this->notify(primaryDevice ? PrimaryCameraCreated : CameraCreated, component);

		if ( enableModel )
		{
			this->newMeshInstance(Renderable::MeshResource::get("camera"), componentName + "Gizmo");
		}

		return component;
	}

	std::shared_ptr< Camera >
	AbstractEntity::newOrthographicCamera (const std::string & componentName, bool primaryDevice, bool enableModel) noexcept
	{
		if ( !this->checkComponentNameAvailability(componentName) )
		{
			return nullptr;
		}

		auto component = std::make_shared< Camera >(componentName, *this, false);

		/* Registering the smart pointer. */
		if ( !this->addComponent(componentName, component) )
		{
			return nullptr;
		}

		/* Notify the creation. */
		this->notify(primaryDevice ? PrimaryCameraCreated : CameraCreated, component);

		if ( enableModel )
		{
			this->newMeshInstance(Renderable::MeshResource::get("camera"), componentName + "Gizmo");
		}

		return component;
	}

	std::shared_ptr< Microphone >
	AbstractEntity::newMicrophone (const std::string & componentName, bool primaryDevice) noexcept
	{
		if ( !this->checkComponentNameAvailability(componentName) )
		{
			return nullptr;
		}

		auto component = std::make_shared< Microphone >(componentName, *this);

		/* Registering the smart pointer. */
		if ( !this->addComponent(componentName, component) )
		{
			return nullptr;
		}

		/* Notify the creation. */
		this->notify(primaryDevice ? PrimaryMicrophoneCreated : MicrophoneCreated, component);

		return component;
	}

	std::shared_ptr< DirectionalLight >
	AbstractEntity::newDirectionalLight (const std::string & componentName) noexcept
	{
		if ( !this->checkComponentNameAvailability(componentName) )
		{
			return nullptr;
		}

		auto component = std::make_shared< DirectionalLight >(componentName, *this);

		/* Registering the smart pointer. */
		if ( !this->addComponent(componentName, component) )
		{
			return nullptr;
		}

		/* Notify the creation. */
		this->notify(DirectionalLightCreated, component);

		return component;
	}

	std::shared_ptr< PointLight >
	AbstractEntity::newPointLight (const std::string & componentName) noexcept
	{
		if ( !this->checkComponentNameAvailability(componentName) )
		{
			return nullptr;
		}

		auto component = std::make_shared< PointLight >(componentName, *this);

		/* Registering the smart pointer. */
		if ( !this->addComponent(componentName, component) )
		{
			return nullptr;
		}

		/* Notify the creation. */
		this->notify(PointLightCreated, component);

		return component;
	}

	std::shared_ptr< SpotLight >
	AbstractEntity::newSpotLight (const std::string & componentName) noexcept
	{
		if ( !this->checkComponentNameAvailability(componentName) )
		{
			return nullptr;
		}

		auto component = std::make_shared< SpotLight >(componentName, *this);

		/* Registering the smart pointer. */
		if ( !this->addComponent(componentName, component) )
		{
			return nullptr;
		}

		/* Notify the creation. */
		this->notify(SpotLightCreated, component);

		return component;
	}

	std::shared_ptr< SoundEmitter >
	AbstractEntity::newSoundEmitter (const std::string & componentName) noexcept
	{
		if ( !this->checkComponentNameAvailability(componentName) )
		{
			return nullptr;
		}

		auto component = std::make_shared< SoundEmitter >(componentName, *this);

		/* Registering the smart pointer. */
		if ( !this->addComponent(componentName, component) )
		{
			return nullptr;
		}

		/* Notify the creation. */
		this->notify(SoundEmitterCreated, component);

		return component;
	}

	std::shared_ptr< SoundEmitter >
	AbstractEntity::newSoundEmitter (const std::shared_ptr< Audio::SoundResource > & resource, bool loop, const std::string & componentName) noexcept
	{
		auto component = this->newSoundEmitter(componentName);

		component->play(resource, loop);

		return component;
	}

	std::shared_ptr< VisualComponent >
	AbstractEntity::newMeshInstance (const std::shared_ptr< Renderable::MeshResource > & resource, const std::string & componentName) noexcept
	{
		/* If no name were passed, we use the mesh name. */
		const auto name = componentName.empty() ? resource->name() : componentName;

		if ( !this->checkComponentNameAvailability(name) )
		{
			return nullptr;
		}

		auto component = std::make_shared< VisualComponent >(name, *this, resource);

		/* Registering the smart pointer. */
		if ( !this->addComponent(name, component) )
		{
			return nullptr;
		}

		/* Notify the creation. */
		this->notify(VisualComponentCreated, component);

		return component;
	}

	std::shared_ptr< VisualComponent >
	AbstractEntity::newSpriteInstance (const std::shared_ptr< Renderable::SpriteResource > & resource, const std::string & componentName) noexcept
	{
		/* If no name were passed, we use the resource name. */
		const auto name = componentName.empty() ? resource->name() : componentName;

		if ( !this->checkComponentNameAvailability(name) )
		{
			return nullptr;
		}

		auto component = std::make_shared< VisualComponent >(name, *this, resource);

		/* Registering the smart pointer. */
		if ( !this->addComponent(name, component) )
		{
			return nullptr;
		}

		/* Notify the creation. */
		this->notify(VisualComponentCreated, component);

		return component;
	}

	std::shared_ptr< MultipleVisualsComponent >
	AbstractEntity::newMeshInstance (const std::shared_ptr< Renderable::MeshResource > & resource, const std::vector< Coordinates< float > > & coordinates, const std::string & componentName) noexcept
	{
		/* If no name were passed, we use the mesh name. */
		const auto name = componentName.empty() ? resource->name() : componentName;

		if ( !this->checkComponentNameAvailability(name) )
		{
			return nullptr;
		}

		auto component = std::make_shared< MultipleVisualsComponent >(name, *this, resource, coordinates);

		/* Registering the smart pointer. */
		if ( !this->addComponent(name, component) )
		{
			return nullptr;
		}

		/* Notify the creation. */
		this->notify(MultipleVisualsComponentCreated, component);

		return component;
	}

	std::shared_ptr< MultipleVisualsComponent >
	AbstractEntity::newSpriteInstance (const std::shared_ptr< Renderable::SpriteResource > & resource, const std::vector< Coordinates< float > > & coordinates, const std::string & componentName) noexcept
	{
		/* If no name were passed, we use the resource name. */
		const auto name = componentName.empty() ? resource->name() : componentName;

		if ( !this->checkComponentNameAvailability(name) )
		{
			return nullptr;
		}

		auto component = std::make_shared< MultipleVisualsComponent >(name, *this, resource, coordinates);

		/* Registering the smart pointer. */
		if ( !this->addComponent(name, component) )
		{
			return nullptr;
		}

		/* Notify the creation. */
		this->notify(MultipleVisualsComponentCreated, component);

		return component;
	}

	std::shared_ptr< ParticlesEmitter >
	AbstractEntity::newParticlesEmitter (const std::shared_ptr< Renderable::SpriteResource > & resource, size_t maxParticleCount, const std::string & componentName) noexcept
	{
		/* If no name were passed, we use the resource name. */
		const auto name = componentName.empty() ? resource->name() : componentName;

		if ( !this->checkComponentNameAvailability(name) )
		{
			return nullptr;
		}

		auto component = std::make_shared< ParticlesEmitter >(name, *this, resource, maxParticleCount);

		/* Registering the smart pointer. */
		if ( !this->addComponent(name, component) )
		{
			return nullptr;
		}

		/* Notify the creation. */
		this->notify(ParticlesEmitterCreated, component);

		return component;
	}

	std::shared_ptr< ParticlesEmitter >
	AbstractEntity::newParticlesEmitter (const std::shared_ptr< Renderable::MeshResource > & resource, size_t maxParticleCount, const std::string & componentName) noexcept
	{
		/* If no name were passed, we use the resource name. */
		const auto name = componentName.empty() ? resource->name() : componentName;

		if ( !this->checkComponentNameAvailability(name) )
		{
			return nullptr;
		}

		auto component = std::make_shared< ParticlesEmitter >(name, *this, resource, maxParticleCount);

		/* Registering the smart pointer. */
		if ( !this->addComponent(name, component) )
		{
			return nullptr;
		}

		/* Notify the creation. */
		this->notify(ParticlesEmitterCreated, component);

		return component;
	}

	std::shared_ptr< DirectionalPushModifier >
	AbstractEntity::newDirectionalPushModifier (const std::string & componentName) noexcept
	{
		if ( !this->checkComponentNameAvailability(componentName) )
		{
			return nullptr;
		}

		auto component = std::make_shared< DirectionalPushModifier >(componentName, *this);

		/* Registering the smart pointer. */
		if ( !this->addComponent(componentName, component) )
		{
			return nullptr;
		}

		/* Notify the creation. */
		this->notify(ModifierCreated, std::static_pointer_cast< AbstractModifier >(component));
		this->notify(DirectionalPushModifierCreated, component);

		return component;
	}

	std::shared_ptr< SphericalPushModifier >
	AbstractEntity::newSphericalPushModifier (const std::string & componentName) noexcept
	{
		if ( !this->checkComponentNameAvailability(componentName) )
		{
			return nullptr;
		}

		auto component = std::make_shared< SphericalPushModifier >(componentName, *this);

		/* Registering the smart pointer. */
		if ( !this->addComponent(componentName, component) )
		{
			return nullptr;
		}

		/* Notify the creation. */
		this->notify(ModifierCreated, std::static_pointer_cast< AbstractModifier >(component));
		this->notify(SphericalPushModifierCreated, component);

		return component;
	}

	std::shared_ptr< Weight >
	AbstractEntity::newWeight (const std::string & componentName) noexcept
	{
		if ( !this->checkComponentNameAvailability(componentName) )
		{
			return nullptr;
		}

		auto component = std::make_shared< Weight >(componentName, *this);

		/* Registering the smart pointer. */
		if ( !this->addComponent(componentName, component) )
		{
			return nullptr;
		}

		/* Notify the creation. */
		this->notify(WeightCreated, component);

		return component;
	}

	std::shared_ptr< Weight >
	AbstractEntity::newWeight (const PhysicalObjectProperties & initialProperties, const std::string & componentName) noexcept
	{
		if ( !this->checkComponentNameAvailability(componentName) )
		{
			return nullptr;
		}

		auto component = std::make_shared< Weight >(componentName, *this, initialProperties);

		/* Registering the smart pointer. */
		if ( !this->addComponent(componentName, component) )
		{
			return nullptr;
		}

		/* Notify the creation. */
		this->notify(WeightCreated, component);

		return component;
	}
}
