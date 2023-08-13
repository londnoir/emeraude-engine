/*
 * Emeraude/Scenes/Toolkit.cpp
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

#include "Toolkit.hpp"

/* Local inclusions */
#include "Tracer.hpp"
#include "Resources/Manager.hpp"
#include "Graphics/Geometry/ResourceGenerator.hpp"
#include "Animations/ConstantValue.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Libraries::PixelFactory;
	using namespace Libraries::VertexFactory;
	using namespace Graphics;

	Toolkit::Toolkit (const std::shared_ptr< Scene > & scene) noexcept
		: m_scene(scene)
	{

	}

	void
	Toolkit::enableDebug (bool state) noexcept
	{
		m_flags[Debug] = state;
	}

	bool
	Toolkit::isDebugEnabled () const noexcept
	{
		return m_flags[Debug];
	}

	void
	Toolkit::setScene (const std::shared_ptr< Scene > & scene) noexcept
	{
		m_scene = scene;
	}

	std::shared_ptr< Scene >
	Toolkit::scene () const noexcept
	{
		return m_scene;
	}

	void
	Toolkit::setParentNode (const std::shared_ptr< Node > & parentNode) noexcept
	{
		m_parentNode = parentNode;
	}

	void
	Toolkit::setReusableNode (const std::shared_ptr< Node > & node) noexcept
	{
		m_reusableNode = node;
	}

	void
	Toolkit::setCursor (const Vector< 3, float > & position) noexcept
	{
		m_cursor.clear();
		m_cursor.setPosition(position);
	}

	void
	Toolkit::setCursor (const Coordinates< float > & coordinates) noexcept
	{
		m_cursor = coordinates;
	}

	void
	Toolkit::setNextNodeMovingAbility (bool state) noexcept
	{
		m_flags[NextNodeMovable] = state;
	}

	const Coordinates< float > &
	Toolkit::cursor () const noexcept
	{
		return m_cursor;
	}

	std::shared_ptr< Node >
	Toolkit::generateNode (const std::string & name, bool movable, bool setAsReusable) noexcept
	{
		if ( m_reusableNode != nullptr )
		{
			TraceInfo{ClassId} << "Reusing a previous scene node (" << m_reusableNode->name() << ") ...";

			return m_reusableNode;
		}

		if ( m_scene == nullptr )
		{
			Tracer::error(ClassId, "There is no scene ! Unable to create a scene node.");

			return {};
		}

		auto parentNode = m_parentNode != nullptr ? m_parentNode : m_scene->root();

		auto node = parentNode->createSubNode(name + "Node", m_cursor);
		node->setMovingAbility(movable);

		if ( setAsReusable )
			this->setReusableNode(node);

		return node;
	}

	std::shared_ptr< Node >
	Toolkit::generateNodeLookAt (const std::string & name, const Vector< 3, float > & lookAt, bool movable) noexcept
	{
		auto node = this->generateNode(name, movable);

		if ( node == nullptr )
			return node;

		node->lookAt(lookAt);

		return node;
	}

	std::shared_ptr< Node >
	Toolkit::generateNodePointTo (const std::string & name, const Vector< 3, float > & pointTo, bool movable) noexcept
	{
		auto node = this->generateNode(name, movable);

		if ( node == nullptr )
			return node;

		node->pointTo(pointTo);

		return node;
	}

	Toolkit::BuiltNode< Camera >
	Toolkit::generateCamera (const std::string & name, const Vector< 3, float > & lookAt, float fov) noexcept
	{
		auto node = this->generateNodeLookAt(name, lookAt, m_flags[NextNodeMovable]);

		auto component = node->newCamera(name, m_flags[Debug]);
		component->setPerspectiveProjection(fov);

		return {node, component};
	}

	Toolkit::BuiltNode< Camera >
	Toolkit::generateOrthographicCamera (const std::string & name, const Vector< 3, float > & lookAt, float size) noexcept
	{
		auto node = this->generateNodeLookAt(name, lookAt, m_flags[NextNodeMovable]);

		auto component = node->newCamera(name, m_flags[Debug]);
		component->setOrthographicProjection(size);

		return {node, component};
	}

	Toolkit::BuiltNode< Camera >
	Toolkit::generateCubemapCamera (const std::string & name, bool movable) noexcept
	{
		auto node = this->generateNode(name, movable);

		auto component = node->newCamera(name, m_flags[Debug]);
		component->setPerspectiveProjection(90.0F);

		return {node, component};
	}

	Toolkit::BuiltNode< DirectionalLight >
	Toolkit::generateDirectionalLight (const std::string & name, const Vector< 3, float > & lookAt, const Color< float > & color) noexcept
	{
		auto node = this->generateNodeLookAt(name, lookAt, m_flags[NextNodeMovable]);

		auto component = node->newDirectionalLight(name);
		component->setColor(color);

		return {node, component};
	}

	Toolkit::BuiltNode< PointLight >
	Toolkit::generatePointLight (const std::string & name, const Color< float > & color, float radius) noexcept
	{
		auto node = this->generateNode(name, m_flags[NextNodeMovable]);

		auto component = node->newPointLight(name);
		component->setColor(color);
		component->setRadius(radius);

		return {node, component};
	}

	Toolkit::BuiltNode< SpotLight >
	Toolkit::generateSpotLight (const std::string & name, const Vector< 3, float > & lookAt, float outerAngle, float innerAngle, const Color< float > & color, float radius) noexcept
	{
		auto node = this->generateNodeLookAt(name, lookAt, m_flags[NextNodeMovable]);

		auto component = node->newSpotLight(name);
		component->setColor(color);
		component->setConeAngles(Radian(innerAngle), Radian(outerAngle));
		component->setRadius(radius);

		return {node, component};
	}

	Toolkit::BuiltNode< SpotLight >
	Toolkit::generateSpinningSpotLight (const std::string & name, float outerAngle, float innerAngle, const Color< float > & color, float radius) noexcept
	{
		auto node = this->generateNode(name, m_flags[NextNodeMovable]);

		auto component = node->newSpotLight(name);
		component->setColor(color);
		component->setConeAngles(Radian(innerAngle), Radian(outerAngle));
		component->setRadius(radius);

		node->addAnimation(Node::WorldYRotation, std::make_shared< Animations::ConstantValue >(Variant{Radian(5.0F)}));

		return {node, component};
	}

	std::shared_ptr< TextureResource::Abstract >
	Toolkit::getDynamicEnvironmentMap (const std::string & name, uint32_t resolution) noexcept
	{
		/* Create a render to texture. */
		auto environmentMap = m_scene->masterControlConsole().createRenderToCubemap(name + "EnvironmentMap", resolution);

		if ( environmentMap == nullptr )
			return {};

		auto node = this->generateNode(name, m_flags[NextNodeMovable]);

		/* Create a camera. */
		auto camera = node->newCamera(name, m_flags[Debug]);
		camera->setFieldOfView(90.0F);
		camera->connect(environmentMap);

		return environmentMap;
	}

	void
	Toolkit::generateRandomNodes (size_t depth, const Scene & scene, const std::shared_ptr< Node > & parent, const std::string & name) noexcept
	{
		const auto newDepth = depth + 1UL;

		const auto limit =  Utility::random(0UL, 48UL / newDepth);

		for ( size_t index = 0; index < limit; ++index )
		{
			this->setParentNode(parent);
			this->setCursor(scene.getRandomPosition());

			auto node = this->generateNode(String::numericLabel(name, index), false, false);

			if ( depth < 2 )
			{
				this->generateRandomNodes(newDepth, scene, node);
			}
		}
	}

	Toolkit::BuiltNode< VisualComponent >
	Toolkit::generateMeshInstance (const std::string & baseName, const std::shared_ptr< Graphics::Geometry::IndexedVertexResource > & geometryResource, std::shared_ptr< Graphics::Material::Interface > materialResource) noexcept
	{
		/* Generate the material resource. */
		if ( materialResource == nullptr )
			materialResource = Resources::Manager::instance()->standardMaterials().getRandomResource();

		/* Check resources */
		if ( geometryResource == nullptr || materialResource == nullptr )
			return {};

		/* Create the mesh resource. */
		auto meshResource = Renderable::MeshResource::getOrCreate(geometryResource, materialResource);

		if ( meshResource == nullptr )
			return {};

		/* Create the node. */
		auto node = this->generateNode(String::incrementalLabel(baseName, m_generatedObjectCount), m_flags[NextNodeMovable]);

		/* Create the mesh instance. */
		auto component = node->newMeshInstance(meshResource, baseName);

		return {node, component};
	}

	Toolkit::BuiltNode< VisualComponent >
	Toolkit::generateShapeInstance (const std::string & baseName, const Shape< float > & shape, const std::shared_ptr< Material::Interface > & materialResource) noexcept
	{
		/* Create the geometry resource from the shape. */
		Geometry::ResourceGenerator generator{Geometry::EnableTangentSpace | Geometry::EnablePrimaryTextureCoordinates};

		auto geometryResource = generator.shape(shape, baseName);

		return this->generateMeshInstance(baseName, geometryResource, materialResource);
	}

	Toolkit::BuiltNode< VisualComponent >
	Toolkit::generateCuboidInstance (const std::string & baseName, const Vector< 3, float > & size, const std::shared_ptr< Material::Interface > & materialResource) noexcept
	{
		/* Generate the geometry resource. */
		Geometry::ResourceGenerator generator{Geometry::EnableTangentSpace | Geometry::EnablePrimaryTextureCoordinates};
		generator.parameters().setGeometryFlags(true);

		auto builtNode = this->generateMeshInstance(baseName, generator.cuboid(size, baseName), materialResource);
		builtNode.second->physicalObjectProperties().setProperties(
			(size[X] * size[Y] * size[Z]) * materialResource->physicalSurfaceProperties().density() * Physics::SI::Kilogram< float >,
			(size[X] * size[Y]),
			Physics::DragCoefficient::Cube< float >,
			0.5F,
			0.5F
		);

		return builtNode;
	}

	Toolkit::BuiltNode< VisualComponent >
	Toolkit::generateSphereInstance (const std::string & baseName, float radius, const std::shared_ptr< Material::Interface > & materialResource, bool useGeodesic) noexcept
	{
		//Geometry::ResourceGenerator generator{Geometry::EnableTangentSpace | Geometry::EnablePrimaryTextureCoordinates};
		Geometry::ResourceGenerator generator{Geometry::EnableNormal | Geometry::EnableVertexColor};

		auto geometryResource = useGeodesic ?
			generator.geodesicSphere(radius, 2, baseName) :
			generator.sphere(radius, 16, 16, baseName);

		auto builtNode = this->generateMeshInstance(baseName, geometryResource, materialResource);
		builtNode.second->physicalObjectProperties().setProperties(
			sphereVolume(radius) * materialResource->physicalSurfaceProperties().density() * Physics::SI::Kilogram< float >,
			circleArea(radius),
			Physics::DragCoefficient::Sphere< float >,
			0.5F,
			0.5F
		);

		return builtNode;
	}

	Toolkit::BuiltNode< VisualComponent >
	Toolkit::generateOutputScreen (const std::string & name, Camera & camera, float screenSize) noexcept
	{
		/* 1. Building geometry */
		Geometry::ResourceGenerator generator{Geometry::EnableTangentSpace | Geometry::EnablePrimaryTextureCoordinates};

		auto geometryResource = generator.cuboid(screenSize, screenSize, 2.0F, name);

		/* 2. Check material */
		auto texture = m_scene->masterControlConsole().createRenderToTexture2D(name + "Stream", 1024, 1024);

		if ( texture == nullptr )
		{
			TraceWarning{ClassId} << "Can't get texture '" << name << "Stream' !";

			return {};
		}

		camera.connect(texture);

		auto resources = Resources::Manager::instance();

		auto materialResource = resources->standardMaterials().createResource(name + "Material", 0, true);
		materialResource->setAmbientComponent(texture);
		materialResource->setDiffuseComponent(texture);
		materialResource->setSpecularComponent({1.0F, 1.0F, 1.0F, 1.0F}, 120.0F);
		materialResource->setAutoIlluminationComponent(1.0F, 1.0F);
		if ( !materialResource->setManualLoadSuccess(true) )
			return {};

		/* 3. Building mesh */
		auto meshResource = resources->meshes().createResource(name + "Mesh");

		if ( !meshResource->load(geometryResource, materialResource) )
		{
			TraceWarning{ClassId} << "Can't get mesh '" << name << "Mesh' !";

			return {};
		}

		/* Creates the scene node. */
		auto node = this->generateNode(String::incrementalLabel(name, m_generatedObjectCount), m_flags[NextNodeMovable]);

		return {node, node->newMeshInstance(meshResource, name)};
	}

	std::vector< Coordinates< float > >
	Toolkit::generateRandomCoordinates (size_t limit, float min, float max) noexcept
	{
		std::vector< Coordinates< float > > coordinates{};

		coordinates.reserve(limit);

		for ( size_t index = 0; index < limit; index++ )
		{
			coordinates.emplace_back(Vector< 3, float >::random(min, max));
		}

		return coordinates;
	}
}
