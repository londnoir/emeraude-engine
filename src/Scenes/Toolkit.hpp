/*
 * Emeraude/Scenes/Toolkit.hpp
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

/* C/C++ standard libraries */
#include <string>
#include <memory>
#include <array>

/* Local inclusions */
#include "Math/Coordinates.hpp"
#include "Scenes/Scene.hpp"

namespace Emeraude::Scenes
{
	/** @brief This class ease the build of a scene. */
	class Toolkit final
	{
		public:

			template< typename component_t >
			using BuiltNode = std::pair< std::shared_ptr< Node >, std::shared_ptr< component_t > >;

			static constexpr auto ClassId{"ScenesToolkit"};

			/**
			 * @brief Constructs the toolkit to help at building a scene.
			 * @param scene A reference to a scene smart pointer.
			 */
			explicit Toolkit (const std::shared_ptr< Scene > & scene = {}) noexcept;

			/**
			 * @brief Enables or disable the debug mode. This will force debugging over all created things.
			 * @param state The state.
			 */
			void enableDebug (bool state) noexcept;

			/**
			 * @brief Returns whether the toolkit has debug mode enabled.
			 * @return bool
			 */
			[[nodiscard]]
			bool isDebugEnabled () const noexcept;

			/**
			 * @brief Sets a scene for the toolkit.
			 * @return const shared_ptr< Scene > &
			 */
			void setScene (const std::shared_ptr< Scene > & scene) noexcept;

			/**
			 * @brief Gives back the access to the current scene.
			 * @return shared_ptr< Scene >
			 */
			[[nodiscard]]
			std::shared_ptr< Scene > scene () const noexcept;

			/**
			 * @brief Sets the node which will be responsible for being the parent of the next node created.
			 * @param parentNode The parent node.
			 */
			void setParentNode (const std::shared_ptr< Node > & parentNode) noexcept;

			/**
			 * @brief Sets the node where the next object will be generated instead of creating a new one.
			 * @param node The scene node.
			 */
			void setReusableNode (const std::shared_ptr< Node > & node) noexcept;

			/**
			 * @brief Sets a full coordinates for the cursor of the builder.
			 * @param position A vector to define the position.
			 */
			void setCursor (const Libraries::Math::Vector< 3, float > & position) noexcept;

			/**
			 * @brief Sets position of the builder.
			 * @param coordinates A coordinates to extract the position from.
			 */
			void setCursor (const Libraries::Math::Coordinates< float > & coordinates) noexcept;

			/**
			 * @brief Sets every next new scene node movable.
			 * @param state The state.
			 */
			void setNextNodeMovingAbility (bool state) noexcept;

			/**
			 * @brief Returns the current cursor.
			 * @return Coordinates &
			 */
			[[nodiscard]]
			const Libraries::Math::Coordinates< float > & cursor () const noexcept;

			/**
			 * @brief Creates a new scene node at cursor and by using the selected parent node or root otherwise.
			 * @param name The name of the new node.
			 * @param movable Set the movable property of the node.
			 * @param setAsReusable Set the new node as reusable.
			 * @return shared_ptr< Node >
			 */
			[[nodiscard]]
			std::shared_ptr< Node > generateNode (const std::string & name, bool movable = true, bool setAsReusable = false) noexcept;

			/**
			 * @brief Creates a new scene node at cursor and by using the selected parent node or root otherwise.
			 * The new node will point his Z- vector toward the designed position.
			 * @param name The name of the new node.
			 * @param lookAt The position where the node should look at.
			 * @param movable Set the movable property of the node.
			 * @return shared_ptr< Node >
			 */
			[[nodiscard]]
			std::shared_ptr< Node > generateNodeLookAt (const std::string & name, const Libraries::Math::Vector< 3, float > & lookAt, bool movable = true) noexcept;

			/**
			 * @brief Creates a new scene node at cursor and by using the selected parent node or root otherwise.
			 * The new node will point his Z+ vector toward the designed position.
			 * @param name The name of the new node.
			 * @param pointTo The position where the node point to.
			 * @param movable Set the movable property of the node.
			 * @return shared_ptr< Node >
			 */
			[[nodiscard]]
			std::shared_ptr< Node > generateNodePointTo (const std::string & name, const Libraries::Math::Vector< 3, float > & pointTo, bool movable = true) noexcept;

			/**
			 * @brief Generates a camera using the perspective projection (The classical one).
			 * @param name The used for the node and the camera component.
			 * @param lookAt A position where the camera should initially look at.
			 * @param fov A angle in degrees to set the field of view of the camera.
			 * @return BuiltNode< Camera >
			 */
			BuiltNode< Camera > generateCamera (const std::string & name, const Libraries::Math::Vector< 3, float > & lookAt, float fov) noexcept;

			/**
			 * @brief Generates a camera using the orthographic projection.
			 * @param name The used for the node and the camera component.
			 * @param lookAt A position where the camera should initially look at.
			 * @param size The size of the capture.
			 * @return BuiltNode< Camera >
			 */
			BuiltNode< Camera > generateOrthographicCamera (const std::string & name, const Libraries::Math::Vector< 3, float > & lookAt, float size) noexcept;

			/**
			 * @brief Generates a camera prepared for rendering an environment for use in a reflection or a skybox.
			 * @param name The used for the node and the camera component.
			 * @param movable Set the movable property of the node.
			 * @return BuiltNode< Camera >
			 */
			BuiltNode< Camera > generateCubemapCamera (const std::string & name, bool movable = false) noexcept;

			/**
			 * @brief Generates a directional light. Like the sun.
			 * @param name The used for the node and the light emitter component.
			 * @param lookAt Set where the ray should point.
			 * @param color The color of the light. White by default.
			 * @return BuiltNode< DirectionalLight >
			 */
			BuiltNode< DirectionalLight > generateDirectionalLight (const std::string & name, const Libraries::Math::Vector< 3, float > & lookAt, const Libraries::PixelFactory::Color< float > & color = Libraries::PixelFactory::White) noexcept;

			/**
			 * @brief Generates a point light. Like a bulb.
			 * @param name The used for the node and the light emitter component.
			 * @param color The color of the light. White by default.
			 * @param radius The radius of the light. Infinite by default.
			 * @return BuiltNode< PointLight >
			 */
			BuiltNode< PointLight > generatePointLight (const std::string & name, const Libraries::PixelFactory::Color< float > & color = Libraries::PixelFactory::White, float radius = 0.0F) noexcept;

			/**
			 * Generates a spot light. Like a ... spot light ;).
			 * @param name The used for the node and the light emitter component.
			 * @param lookAt Set where the light should point.
			 * @param outerRadius Define the outer border of the light cone where no more light will be emitted outside this range.
			 * @param innerRadius Define the inner border of the light cone where the light will be emitted at 100% inside.
			 * @param color The color of the light. White by default.
			 * @param radius The radius of the light. Infinite by default.
			 * @return BuiltNode< SpotLight >
			 */
			BuiltNode< SpotLight > generateSpotLight (const std::string & name, const Libraries::Math::Vector< 3, float > & lookAt, float outerRadius = 35.0F, float innerRadius = 0.0F, const Libraries::PixelFactory::Color< float > & color = Libraries::PixelFactory::White, float radius = 0.0F) noexcept;

			/**
			 * @brief Generates a mesh instance in the scene.
			 * @param baseName A reference to a string.
			 * @param geometryResource A reference to a geometry smart pointer.
			 * @param materialResource A reference to a material smart pointer. Default nullptr.
			 * @return BuiltNode< VisualComponent >
			 */
			BuiltNode< VisualComponent > generateMeshInstance (const std::string & baseName, const std::shared_ptr< Graphics::Geometry::IndexedVertexResource > & geometryResource, std::shared_ptr< Graphics::Material::Interface > materialResource = nullptr) noexcept;

			/**
			 * @brief Generates a mesh instance in the scene from a shape.
			 * @param baseName A reference to a string.
			 * @param shape A reference to a shape.
			 * @param materialResource A reference to a material smart pointer. Default nullptr.
			 * @return BuiltNode< VisualComponent >
			 */
			BuiltNode< VisualComponent > generateShapeInstance (const std::string & baseName, const Libraries::VertexFactory::Shape< float > & shape, const std::shared_ptr< Graphics::Material::Interface > & materialResource = nullptr) noexcept;

			/**
			 * @brief Generates a cuboid mesh instance with computed physics properties.
			 * @param baseName A reference to a string.
			 * @param size The dimension of the block.
			 * @param material A material resource. Default random.
			 * @return BuiltNode< RenderableInstance >
			 */
			BuiltNode< VisualComponent > generateCuboidInstance (const std::string & name, const Libraries::Math::Vector< 3, float > & size, const std::shared_ptr< Graphics::Material::Interface > & material = nullptr) noexcept;

			/**
			 * @brief Generates a sphere mesh instance with computed physics properties.
			 * @param baseName A reference to a string.
			 * @param radius The radius of the sphere.
			 * @param materialResource A reference to a material smart pointer. Default nullptr.
			 * @param useGeodesic Use geodesic sphere instead classical. Default false.
			 * @return BuiltNode< RenderableInstance >
			 */
			BuiltNode< VisualComponent > generateSphereInstance (const std::string & name, float radius, const std::shared_ptr< Graphics::Material::Interface > & materialResource = nullptr, bool useGeodesic = false) noexcept;

			/**
			 * @brief Generates an output screen in the scene.
			 * @param name A name. The uniqueness of the name is managed by this method.
			 * @param camera A reference to a scene camera.
			 * @param size The size of the screen in meters.
			 * @return BuiltNode< VisualComponent >
			 */
			BuiltNode< VisualComponent > generateOutputScreen (const std::string & name, Camera & camera, float size) noexcept;

			/**
			 * @brief Generates random nodes.
			 * @note Debug purposes only
			 * @param depth The depth of node tree.
			 * @param sceneArea A reference to a scene area.
			 * @param parent A reference to the parent scene node.
			 * @param name The base name for all nodes.
			 */
			void generateRandomNodes (size_t depth, const Scene & scene, const std::shared_ptr< Node > & parent, const std::string & name = "test") noexcept;

			/**
			 * @brief Generates an environment map.
			 * @param name A name. The uniqueness of the name is managed by this method.
			 * @param resolution The texture resolution. Default 256.
			 * @return std::shared_ptr< Graphics::TextureResource::Abstract >
			 */
			[[deprecated("This is an old debug method.")]]
			std::shared_ptr< Graphics::TextureResource::Abstract > getDynamicEnvironmentMap (const std::string & name, uint32_t resolution = 256) noexcept;

			/**
			 * @brief Generates a spinning spot light.
			 * @deprecated This is a old debug method.
			 * @param name
			 * @param outerRadius
			 * @param innerRadius
			 * @param color
			 * @param radius
			 * @return BuiltNode< SpotLight >
			 */
			[[deprecated("This is an old debug method.")]]
			BuiltNode< SpotLight > generateSpinningSpotLight (const std::string & name, float outerRadius = 35.0F, float innerRadius = 0.0F, const Libraries::PixelFactory::Color< float > & color = Libraries::PixelFactory::White, float radius = 0.0F) noexcept;

			/**
			 * @brief Generates a list of random coordinates.
			 * @param limit The number of coordinates desired.
			 * @param min The minimum number to use for random in X, Y and Z axis.
			 * @param max The maximum number to use for random in X, Y and Z axis.
			 * @return std::vector< Libraries::Math::Coordinates< float > >
			 */
			[[nodiscard]]
			static std::vector< Libraries::Math::Coordinates< float > > generateRandomCoordinates (size_t limit, float min, float max) noexcept;

		private:

			/* Flag names. */
			static constexpr auto Debug = 0UL;
			static constexpr auto NextNodeMovable = 1UL;

			std::shared_ptr< Scene > m_scene;
			std::shared_ptr< Node > m_parentNode{};
			std::shared_ptr< Node > m_reusableNode{};
			Libraries::Math::Coordinates< float > m_cursor{};
			size_t m_generatedObjectCount = 0;
			std::array< bool, 8 > m_flags{
				false/*Debug*/,
				false/*NextNodeMovable*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
