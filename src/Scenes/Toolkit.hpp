/*
 * src/Scenes/Toolkit.hpp
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
#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

/* Local inclusions for usage. */
#include "AbstractEntity.hpp"
#include "BuiltEntity.hpp"
#include "Component/Abstract.hpp"
#include "Component/AbstractLightEmitter.hpp"
#include "Component/Camera.hpp"
#include "Component/DirectionalLight.hpp"
#include "Component/PointLight.hpp"
#include "Component/SphericalPushModifier.hpp"
#include "Component/SpotLight.hpp"
#include "Component/Visual.hpp"
#include "Constants.hpp"
#include "Graphics/Geometry/Interface.hpp"
#include "Graphics/Geometry/ResourceGenerator.hpp"
#include "Graphics/Material/Interface.hpp"
#include "Graphics/Renderable/MeshResource.hpp"
#include "Libraries/Math/Base.hpp"
#include "Libraries/Math/CartesianFrame.hpp"
#include "Libraries/Math/Vector.hpp"
#include "Node.hpp"
#include "Physics/Physics.hpp"
#include "Libraries/PixelFactory/Color.hpp"
#include "Resources/Manager.hpp"
#include "Scenes/Scene.hpp"
#include "StaticEntity.hpp"
#include "Libraries/VertexFactory/Shape.hpp"

namespace Emeraude::Scenes
{
	/**
	 * @brief Entity generation policy.
	 */
	enum class GenPolicy : uint8_t
	{
		/* Simple creation of entity. */
		Simple,
		/* The entity will be set for further component creation. */
		Reusable,
		/* The entity will be set to be the parent of future node creation.
		 * NOTE: This policy will be ignored for static entity. */
		Parent
	};

	/**
	 * @brief This class ease the build of a scene.
	 */
	class Toolkit final
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"ScenesToolkit"};

			/**
			 * @brief Constructs the toolkit to help at building a scene.
			 * @param scene A reference to a scene smart pointer.
			 */
			explicit Toolkit (const std::shared_ptr< Scene > & scene = {}) noexcept;

			/**
			 * @brief Enables or disable the debug mode. This will force debugging over all created things.
			 * @param state The state.
			 * @return Toolkit &
			 */
			Toolkit &
			enableDebug (bool state) noexcept
			{
				m_flags[Debug] = state;

				return *this;
			}

			/**
			 * @brief Returns whether the toolkit has debug mode enabled.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isDebugEnabled () const noexcept
			{
				return m_flags[Debug];
			}

			/**
			 * @brief Sets a scene for the toolkit.
			 * @return Toolkit &
			 */
			Toolkit &
			setScene (const std::shared_ptr< Scene > & scene) noexcept
			{
				m_scene = scene;

				return *this;
			}

			/**
			 * @brief Gives back the access to the current scene.
			 * @return shared_ptr< Scene >
			 */
			[[nodiscard]]
			std::shared_ptr< Scene >
			scene () const noexcept
			{
				return m_scene;
			}

			/**
			 * @brief Sets the cursor position of the builder at world location.
			 * @param xPosition The position on X axis.
			 * @param yPosition The position on Y axis.
			 * @param zPosition The position on Z axis.
			 * @return Toolkit &
			 */
			Toolkit &
			setCursor (float xPosition, float yPosition, float zPosition) noexcept
			{
				m_cursorFrame.reset();
				m_cursorFrame.setPosition(xPosition, yPosition, zPosition);

				return *this;
			}

			/**
			 * @brief Sets the cursor position of the builder at world location using a vector.
			 * @param position A vector to define the position.
			 * @return Toolkit &
			 */
			Toolkit &
			setCursor (const Libraries::Math::Vector< 3, float > & position) noexcept
			{
				m_cursorFrame.reset();
				m_cursorFrame.setPosition(position);

				return *this;
			}

			/**
			 * @brief Sets the cursor position of the builder at world location using coordinates.
			 * @param coordinates A coordinates to extract the position from.
			 * @return Toolkit &
			 */
			Toolkit &
			setCursor (const Libraries::Math::CartesianFrame< float > & coordinates) noexcept
			{
				m_cursorFrame = coordinates;

				return *this;
			}

			/**
			 * @brief Returns the cursor frame.
			 * @return Coordinates &
			 */
			[[nodiscard]]
			const Libraries::Math::CartesianFrame< float > &
			cursor () const noexcept
			{
				return m_cursorFrame;
			}

			/**
			 * @brief Sets a node which will be responsible for being the parent of the next node created.
			 * @note The cursor will use parent node coordinates system.
			 * @param node A reference to a scene node smart pointer.
			 * @return Toolkit &
			 */
			Toolkit & setParentNode (const std::shared_ptr< Node > & node) noexcept
			{
				m_nodeGenerationPolicy = GenPolicy::Parent;
				m_previousNode = node;

				return *this;
			}

			/**
			 * @brief Sets a node where next entity component will be generated instead of creating a new one.
			 * @param node A reference to a scene node smart pointer.
			 * @return Toolkit &
			 */
			Toolkit &
			setReusableNode (const std::shared_ptr< Node > & node) noexcept
			{
				m_nodeGenerationPolicy = GenPolicy::Reusable;
				m_previousNode = node;

				return *this;
			}

			/**
			 * @brief Sets a static entity where the next entity component will be generated instead of creating a new one.
			 * @param staticEntity A reference to a static entity smart pointer.
			 * @return Toolkit &
			 */
			Toolkit &
			setReusableStaticEntity (const std::shared_ptr< StaticEntity > & staticEntity) noexcept
			{
				m_staticEntityGenerationPolicy = GenPolicy::Reusable;
				m_previousStaticEntity = staticEntity;

				return *this;
			}

			/**
			 * @brief Reset the entity generation state of toolkit to default.
			 * @return Toolkit &
			 */
			Toolkit &
			clearGenerationParameters () noexcept
			{
				m_nodeGenerationPolicy = GenPolicy::Simple;
				m_previousNode.reset();
				m_staticEntityGenerationPolicy = GenPolicy::Simple;
				m_previousStaticEntity.reset();

				m_cursorFrame.reset();

				return *this;
			}

			/**
			 * @brief Creates a new scene node at cursor and by using the selected parent node or root otherwise.
			 * @param entityName A reference to a string for the entity entityName. Default auto-generated.
			 * @param movable Set the movable property of the node. Default true.
			 * @param genPolicy Set the entity generation policy. Default simple.
			 * @return std::shared_ptr< Node >
			 */
			[[nodiscard]]
			std::shared_ptr< Node > generateNode (const std::string & entityName = {}, bool movable = true, GenPolicy genPolicy = GenPolicy::Simple) noexcept;

			/**
			 * @brief Creates a new scene node at cursor and by using the selected parent node or root otherwise.
			 * The new node will point his Z+ vector toward the designed position.
			 * @param entityName A reference to a string for the entity name. Default auto-generated.
			 * @param pointTo The position where the node point to.
			 * @param movable Set the movable property of the node. Default true.
			 * @param genPolicy Set the entity generation policy. Default simple.
			 * @return std::shared_ptr< Node >
			 */
			[[nodiscard]]
			std::shared_ptr< Node > generateNode (const Libraries::Math::Vector< 3, float > & pointTo, const std::string & entityName = {}, bool movable = true, GenPolicy genPolicy = GenPolicy::Simple) noexcept;

			/**
			 * @brief Creates a new static entity at cursor.
			 * @param entityName A reference to a string for the entity name. Default auto-generated.
			 * @param genPolicy Set the entity generation policy. Default simple.
			 * @return std::shared_ptr< StaticEntity >
			 */
			[[nodiscard]]
			std::shared_ptr< StaticEntity > generateStaticEntity (const std::string & entityName = {}, GenPolicy genPolicy = GenPolicy::Simple) noexcept;

			/**
			 * @brief Creates a new scene node at cursor and by using the selected parent node or root otherwise.
			 * The new node will point his Z+ vector toward the designed position.
			 * @param entityName A reference to a string for the entity name. Default auto-generated.
			 * @param pointTo The position where the node point to.
			 * @param genPolicy Set the entity generation policy. Default simple.
			 * @return std::shared_ptr< StaticEntity >
			 */
			[[nodiscard]]
			std::shared_ptr< StaticEntity > generateStaticEntity (const Libraries::Math::Vector< 3, float > & pointTo, const std::string & entityName = {}, GenPolicy genPolicy = GenPolicy::Simple) noexcept;

			/**
			 * @brief Creates an entity.
			 * @tparam entity_t The type of entity, a scene node or a static entity. Default StaticEntity.
			 * @param entityName A reference to a string for the entity name. Default auto-generated.
			 * @return std::shared_ptr< entity_t >
			 */
			template< typename entity_t = StaticEntity >
			[[nodiscard]]
			std::shared_ptr< entity_t >
			generateEntity (const std::string & entityName = {}) noexcept requires (std::is_base_of_v< AbstractEntity, entity_t >)
			{
				if constexpr ( std::is_same_v< entity_t, Node > )
				{
					return this->generateNode(entityName);
				}

				if constexpr ( std::is_same_v< entity_t, StaticEntity > )
				{
					return this->generateStaticEntity(entityName);
				}

				return nullptr;
			}

			/**
			 * @brief Creates an entity which look at a specified position.
			 * @tparam entity_t The type of entity, a scene node or a static entity. Default StaticEntity.
			 * @param pointTo The position where the entity point to.
			 * @param entityName A reference to a string for the entity name. Default auto-generated.
			 * @return std::shared_ptr< entity_t >
			 */
			template< typename entity_t = StaticEntity >
			[[nodiscard]]
			std::shared_ptr< entity_t >
			generateEntity (const Libraries::Math::Vector< 3, float > & pointTo, const std::string & entityName = {}) noexcept requires (std::is_base_of_v< AbstractEntity, entity_t >)
			{
				if constexpr ( std::is_same_v< entity_t, Node > )
				{
					return this->generateNode(pointTo, entityName);
				}

				if constexpr ( std::is_same_v< entity_t, StaticEntity > )
				{
					return this->generateStaticEntity(pointTo, entityName);
				}

				return nullptr;
			}

			/**
			 * @brief Generates a camera using the perspective projection.
			 * @tparam entity_t The type of entity, a scene node or a static entity. Default StaticEntity.
			 * @param entityName The used for the node and the camera component.
			 * @param fov The camera field of view expressed in degrees. Default 85.0.
			 * @param pointTo A position where the camera should initially look at. Default origin.
			 * @param primaryDevice Set the camera as the primary device. Default false.
			 * @param showModel Enables a model to visualize the camera. Default false.
			 * @return BuiltEntity< entity_t, Component::Camera >
			 */
			template< typename entity_t = StaticEntity >
			BuiltEntity< entity_t, Component::Camera >
			generatePerspectiveCamera (const std::string & entityName, float fov = DefaultGraphicsFieldOfView, const Libraries::Math::Vector< 3, float > & pointTo = {}, bool primaryDevice = false, bool showModel = false) noexcept requires (std::is_base_of_v< AbstractEntity, entity_t >)
			{
				/* Create the entity. */
				auto entity = this->generateEntity< entity_t >(pointTo, entityName);

				if ( entity == nullptr )
				{
					return {};
				}

				/* Create the camera component. */
				auto component = entity->newCamera(true, primaryDevice, entityName);
				component->setPerspectiveProjection(fov);

				if ( showModel )
				{
					entity->enableVisualDebug(VisualDebugType::Camera);
				}

				return {entity, component};
			}

			/**
			 * @brief Generates a camera using the orthographic projection.
			 * @tparam entity_t The type of entity, a scene node or a static entity. Default StaticEntity.
			 * @param entityName The used for the node and the camera component.
			 * @param size The square size of the capture. Default 1.0.
			 * @param pointTo A position where the camera should initially look at. Default origin.
			 * @param primaryDevice Declare this camera as the primary video device. Default false.
			 * @param showModel Display a model to visualize the camera. Default false.
			 * @return BuiltEntity< Node, Component::Camera >
			 */
			template< typename entity_t = StaticEntity >
			BuiltEntity< entity_t, Component::Camera >
			generateOrthographicCamera (const std::string & entityName, float size = 1.0F, const Libraries::Math::Vector< 3, float > & pointTo = {}, bool primaryDevice = false, bool showModel = false) noexcept requires (std::is_base_of_v< AbstractEntity, entity_t >)
			{
				/* Create the entity. */
				auto entity = this->generateEntity< entity_t >(pointTo, entityName);

				if ( entity == nullptr )
				{
					return {};
				}

				/* Create the camera component. */
				auto component = entity->newCamera(false, primaryDevice, entityName);
				component->setOrthographicProjection(size);

				if ( showModel )
				{
					entity->enableVisualDebug(VisualDebugType::Camera);
				}

				return {entity, component};
			}

			/**
			 * @brief Generates a camera prepared for rendering an environment for use in a reflection or a skybox.
			 * @tparam entity_t The type of entity, a scene node or a static entity. Default StaticEntity.
			 * @param entityName The used for the node and the camera component.
			 * @param primaryDevice Declare this camera as the primary video device. Default false.
			 * @param showModel Display a model to visualize the camera. Default false.
			 * @return BuiltEntity< entity_t, Component::Camera >
			 */
			template< typename entity_t = StaticEntity >
			BuiltEntity< entity_t, Component::Camera >
			generateCubemapCamera (const std::string & entityName, bool primaryDevice = false, bool showModel = false) noexcept requires (std::is_base_of_v< AbstractEntity, entity_t >)
			{
				/* Create the entity. */
				auto entity = this->generateEntity< entity_t >(entityName);

				if ( entity == nullptr )
				{
					return {};
				}

				/* Create the camera component. */
				auto component = entity->newCamera(true, primaryDevice, entityName);
				component->setPerspectiveProjection(Libraries::Math::QuartRevolution< float >);

				if ( showModel )
				{
					entity->enableVisualDebug(VisualDebugType::Camera);
				}

				return {entity, component};
			}

			/**
			 * @brief Generates a directional light. Like the sun.
			 * @tparam entity_t The type of entity, a scene node or a static entity. Default StaticEntity.
			 * @param entityName The used for the node and the light emitter component.
			 * @param pointTo Set where the ray should point.
			 * @param color The color of the light. White by default.
			 * @param intensity The light intensity. Default 1.
			 * @param shadowMapResolution The shadow map resolution. Default disabled.
			 * @return BuiltEntity< entity_t, Component::DirectionalLight >
			 */
			template< typename entity_t = StaticEntity >
			BuiltEntity< entity_t, Component::DirectionalLight >
			generateDirectionalLight (const std::string & entityName, const Libraries::Math::Vector< 3, float > & pointTo, const Libraries::PixelFactory::Color< float > & color = Libraries::PixelFactory::White, float intensity = Component::AbstractLightEmitter::DefaultIntensity, uint32_t shadowMapResolution = 0) noexcept requires (std::is_base_of_v< AbstractEntity, entity_t >)
			{
				/* Create the entity. */
				auto entity = this->generateEntity< entity_t >(pointTo, entityName);

				if ( entity == nullptr )
				{
					return {};
				}

				/* Create the light component. */
				auto component = entity->newDirectionalLight(shadowMapResolution, entityName);
				component->setColor(color);
				component->setIntensity(intensity);

				return {entity, component};
			}

			/**
			 * @brief Generates a point light. Like a bulb.
			 * @tparam entity_t The type of entity, a scene node or a static entity. Default StaticEntity.
			 * @param entityName The used for the node and the light emitter component.
			 * @param color The color of the light. White by default.
			 * @param radius The radius of the light. Infinite by default.
			 * @param intensity The light intensity. Default 1.
			 * @param shadowMapResolution The shadow map resolution. Default disabled.
			 * @return BuiltEntity< entity_t, Component::PointLight >
			 */
			template< typename entity_t = StaticEntity >
			BuiltEntity< entity_t, Component::PointLight >
			generatePointLight (const std::string & entityName, const Libraries::PixelFactory::Color< float > & color = Libraries::PixelFactory::White, float radius = Component::AbstractLightEmitter::DefaultRadius, float intensity = Component::AbstractLightEmitter::DefaultIntensity, uint32_t shadowMapResolution = 0) noexcept requires (std::is_base_of_v< AbstractEntity, entity_t >)
			{
				/* Create the entity. */
				auto entity = this->generateEntity< entity_t >(entityName);

				if ( entity == nullptr )
				{
					return {};
				}

				/* Create the light component. */
				auto component = entity->newPointLight(shadowMapResolution, entityName);
				component->setColor(color);
				component->setRadius(radius);
				component->setIntensity(intensity);

				return {entity, component};
			}

			/**
			 * @brief Generates a spotlight. Like a ... spotlight ;).
			 * @tparam entity_t The type of entity, a scene node or a static entity. Default StaticEntity.
			 * @param entityName The used for the node and the light emitter component.
			 * @param pointTo Set where the light should point.
			 * @param innerAngle Define the inner border of the light cone where the light will be emitted at 100% inside. Default 35°.
			 * @param outerAngle Define the outer border of the light cone where no more light will be emitted outside this range. Default 40°.
			 * @param color The color of the light. White by default.
			 * @param radius The radius of the light. Infinite by default.
			 * @param intensity The light intensity. Default 1.
			 * @param shadowMapResolution The shadow map resolution. Default disabled.
			 * @return BuiltEntity< entity_t, Component::SpotLight >
			 */
			template< typename entity_t = StaticEntity >
			BuiltEntity< entity_t, Component::SpotLight >
			generateSpotLight (const std::string & entityName, const Libraries::Math::Vector< 3, float > & pointTo, float innerAngle = Component::AbstractLightEmitter::DefaultInnerAngle, float outerAngle = Component::AbstractLightEmitter::DefaultOuterAngle, const Libraries::PixelFactory::Color< float > & color = Libraries::PixelFactory::White, float radius = Component::AbstractLightEmitter::DefaultRadius, float intensity = Component::AbstractLightEmitter::DefaultIntensity, uint32_t shadowMapResolution = 0) noexcept requires (std::is_base_of_v< AbstractEntity, entity_t >)
			{
				/* Create the entity. */
				auto entity = this->generateEntity< entity_t >(pointTo, entityName);

				if ( entity == nullptr )
				{
					return {};
				}

				/* Create the light component. */
				auto component = entity->newSpotLight(shadowMapResolution, entityName);
				component->setColor(color);
				component->setConeAngles(innerAngle, outerAngle);
				component->setRadius(radius);
				component->setIntensity(intensity);

				return {entity, component};
			}

			/**
			 * @brief Generates a mesh instance in the scene.
			 * @tparam entity_t The type of entity, a scene node or a static entity. Default StaticEntity.
			 * @param entityName A reference to a string.
			 * @param geometryResource A geometry smart pointer. Default nullptr.
			 * @param materialResource A material smart pointer. Default nullptr.
			 * @param enableLighting Enable the lighting. Default false.
			 * @return BuiltEntity< entity_t, Component::Visual >
			 */
			template< typename entity_t = StaticEntity >
			BuiltEntity< entity_t, Component::Visual >
			generateMeshInstance (const std::string & entityName, std::shared_ptr< Graphics::Geometry::Interface > geometryResource = nullptr, std::shared_ptr< Graphics::Material::Interface > materialResource = nullptr, bool enableLighting = false) noexcept requires (std::is_base_of_v< AbstractEntity, entity_t >)
			{
				/* Create the entity. */
				auto entity = this->generateEntity< entity_t >(entityName);

				if ( entity == nullptr )
				{
					return {};
				}

				/* Check geometry. */
				if ( geometryResource == nullptr )
				{
					geometryResource = Resources::Manager::instance()->indexedVertexGeometries().getDefaultResource();
				}

				/* Get the default basic material resource. */
				if ( materialResource == nullptr )
				{
					materialResource = Resources::Manager::instance()->basicMaterials().getDefaultResource();
				}

				/* Create a mesh resource by assembling the geometry and the material resource. */
				const auto meshResource = Graphics::Renderable::MeshResource::getOrCreate(geometryResource, materialResource);

				if ( meshResource == nullptr )
				{
					return {};
				}

				/* Create the visual component. */
				auto component = entity->newVisual(meshResource, true, enableLighting, entityName);

				return {entity, component};
			}

			/**
			 * @brief Generates a mesh instance in the scene from a shape.
			 * @note Shortcut to Toolkit::generateMeshInstance().
			 * @tparam entity_t The type of entity, a scene node or a static entity. Default StaticEntity.
			 * @param entityName A reference to a string.
			 * @param shape A reference to a vertex factory shape.
			 * @param materialResource A reference to a material smart pointer. Default nullptr.
			 * @param enableLighting Enable the lighting. Default false.
			 * @return BuiltEntity< entity_t, Component::Visual >
			 */
			template< typename entity_t = StaticEntity >
			BuiltEntity< entity_t, Component::Visual >
			generateShapeInstance (const std::string & entityName, const Libraries::VertexFactory::Shape< float > & shape, const std::shared_ptr< Graphics::Material::Interface > & materialResource = nullptr, bool enableLighting = false) noexcept requires (std::is_base_of_v< AbstractEntity, entity_t >)
			{
				using namespace Graphics;

				const Geometry::ResourceGenerator generator{*Resources::Manager::instance(), Geometry::EnableTangentSpace | Geometry::EnablePrimaryTextureCoordinates};

				const auto geometryResource = generator.shape(shape, entityName);

				if ( geometryResource == nullptr )
				{
					return {};
				}

				return this->generateMeshInstance< entity_t >(entityName, geometryResource, materialResource, enableLighting);
			}

			/**
			 * @brief Generates a cuboid mesh instance with computed physics properties.
			 * @note Shortcut to Toolkit::generateMeshInstance(). The TBN space and one texture coordinates will be enabled.
			 * @tparam entity_t The type of entity, a scene node or a static entity. Default StaticEntity.
			 * @param entityName A reference to a string.
			 * @param size The dimension of the cuboid.
			 * @param materialResource A material resource. Default random.
			 * @param enableLighting Enable the lighting. Default false.
			 * @param generatePhysicsProperties Set physical properties based on shade a material. Default false.
			 * @return BuiltEntity< entity_t, Component::Visual >
			 */
			template< typename entity_t = StaticEntity >
			BuiltEntity< entity_t, Component::Visual >
			generateCuboidInstance (const std::string & entityName, const Libraries::Math::Vector< 3, float > & size, const std::shared_ptr< Graphics::Material::Interface > & materialResource = nullptr, bool enableLighting = false, bool generatePhysicsProperties = false) noexcept requires (std::is_base_of_v< AbstractEntity, entity_t >)
			{
				using namespace Libraries;
				using namespace Libraries::Math;
				using namespace Graphics;
				using namespace Physics;

				const Geometry::ResourceGenerator generator{*Resources::Manager::instance(), Geometry::EnableTangentSpace | Geometry::EnablePrimaryTextureCoordinates};

				const auto geometryResource = generator.cuboid(size, entityName);

				if ( geometryResource == nullptr )
				{
					return {};
				}

				const auto entity = this->generateMeshInstance< entity_t >(entityName, geometryResource, materialResource, enableLighting);

				if ( entity.isValid() && generatePhysicsProperties )
				{
					entity.component()->physicalObjectProperties().setProperties(
						size[X] * size[Y] * size[Z] * materialResource->physicalSurfaceProperties().density() * SI::Kilogram< float >,
						size[X] * size[Y],
						DragCoefficient::Cube< float >,
						Half< float >,
						Half< float >
					);
				}

				return entity;
			}

			/**
			 * @brief Generates a cube mesh instance with computed physics properties.
			 * @note Shortcut to Toolkit::generateMeshInstance(). The TBN space and one texture coordinates will be enabled.
			 * @tparam entity_t The type of entity, a scene node or a static entity. Default StaticEntity.
			 * @param entityName A reference to a string.
			 * @param size The uniform size of the cube.
			 * @param materialResource A material resource. Default random.
			 * @param enableLighting Enable the lighting. Default false.
			 * @param generatePhysicsProperties Set physical properties based on shade a material. Default false.
			 * @return BuiltEntity< entity_t, Component::Visual >
			 */
			template< typename entity_t = StaticEntity >
			BuiltEntity< entity_t, Component::Visual >
			generateCuboidInstance (const std::string & entityName, float size, const std::shared_ptr< Graphics::Material::Interface > & materialResource = nullptr, bool enableLighting = false, bool generatePhysicsProperties = false) noexcept requires (std::is_base_of_v< AbstractEntity, entity_t >)
			{
				return generateCuboidInstance< entity_t >(entityName, {size, size, size}, materialResource, enableLighting, generatePhysicsProperties);
			}

			/**
			 * @brief Generates a sphere mesh instance with computed physics properties.
			 * @note Shortcut to Toolkit::generateMeshInstance(). The TBN space and one texture coordinates will be enabled.
			 * @tparam entity_t The type of entity, a scene node or a static entity. Default StaticEntity.
			 * @param entityName A reference to a string.
			 * @param radius The radius of the sphere.
			 * @param materialResource A reference to a material smart pointer. Default nullptr.
			 * @param useGeodesic Use geodesic sphere instead classical. Default false.
			 * @param enableLighting Enable the lighting. Default false.
			 * @param generatePhysicsProperties Set physical properties based on shade a material. Default false.
			 * @return BuiltEntity< entity_t, Component::Visual >
			 */
			template< typename entity_t = StaticEntity >
			BuiltEntity< entity_t, Component::Visual >
			generateSphereInstance (const std::string & entityName, float radius, const std::shared_ptr< Graphics::Material::Interface > & materialResource = nullptr, bool useGeodesic = false, bool enableLighting = false, bool generatePhysicsProperties = false) noexcept requires (std::is_base_of_v< AbstractEntity, entity_t >)
			{
				using namespace Libraries;
				using namespace Libraries::Math;
				using namespace Graphics;
				using namespace Physics;

				const Geometry::ResourceGenerator generator{*Resources::Manager::instance(), Geometry::EnableTangentSpace | Geometry::EnablePrimaryTextureCoordinates};

				const auto geometryResource = useGeodesic ?
					generator.geodesicSphere(radius, 2, entityName) :
					generator.sphere(radius, 16, 16, entityName);

				if ( geometryResource == nullptr )
				{
					return {};
				}

				auto entity = this->generateMeshInstance< entity_t >(entityName, geometryResource, materialResource, enableLighting);

				if ( entity.isValid() && generatePhysicsProperties )
				{
					entity.entity()->enableSphereCollision(true);

					const auto density = materialResource == nullptr ? 1.0F : materialResource->physicalSurfaceProperties().density();

					entity.component()->physicalObjectProperties().setProperties(
						sphereVolume(radius) * density * SI::Kilogram< float >,
						circleArea(radius) * SI::Meter< float >,
						DragCoefficient::Sphere< float >,
						Half< float >,
						Half< float >
					);
				}

				return entity;
			}

			/**
			 * @brief Generates a spherical push modifier in the scene.
			 * @tparam entity_t The type of entity, a scene node or a static entity. Default StaticEntity.
			 * @param entityName A reference to a string.
			 * @param magnitude The push magnitude.
			 * @return BuiltEntity< entity_t, Component::SphericalPushModifier >
			 */
			template< typename entity_t = StaticEntity >
			BuiltEntity< entity_t, Component::SphericalPushModifier >
			generateSphericalPushModifier (const std::string & entityName, float magnitude) noexcept requires (std::is_base_of_v< AbstractEntity, entity_t >)
			{
				using namespace Libraries;
				using namespace Libraries::Math;

				/* Create the entity. */
				auto entity = this->generateEntity< entity_t >(entityName);

				if ( entity == nullptr )
				{
					return {};
				}

				/* Create the modifier component. */
				auto component = entity->newSphericalPushModifier(entityName);
				component->setMagnitude(magnitude);

				return {entity, component};
			}

			/**
			 * @brief Generates a list of random coordinates.
			 * @param count The number of coordinates desired.
			 * @param min The minimum number to use for random in X, Y and Z axis.
			 * @param max The maximum number to use for random in X, Y and Z axis.
			 * @return std::vector< Libraries::Math::Coordinates< float > >
			 */
			[[nodiscard]]
			static std::vector< Libraries::Math::CartesianFrame< float > > generateRandomCoordinates (size_t count, float min, float max) noexcept;

		private:

			/* Flag names. */
			static constexpr auto Debug{0UL};

			static size_t s_autoEntityCount;

			std::shared_ptr< Scene > m_scene;
			GenPolicy m_nodeGenerationPolicy{GenPolicy::Simple};
			std::shared_ptr< Node > m_previousNode{};
			GenPolicy m_staticEntityGenerationPolicy{GenPolicy::Simple};
			std::shared_ptr< StaticEntity > m_previousStaticEntity{};
			Libraries::Math::CartesianFrame< float > m_cursorFrame{};
			std::array< bool, 8 > m_flags{
				false/*Debug*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
