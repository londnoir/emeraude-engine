/*
 * Emeraude/Graphics/Material/StandardResource.cpp
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

#include "StandardResource.hpp"

/* Local inclusions. */
#include "Component/Ambient.hpp"
#include "Component/AutoIllumination.hpp"
#include "Component/Diffuse.hpp"
#include "Component/Normal.hpp"
#include "Component/Opacity.hpp"
#include "Component/Reflection.hpp"
#include "Component/Specular.hpp"
#include "Component/TypeColor.hpp"
#include "Component/TypeValue.hpp"
#include "Graphics/Renderer.hpp"
#include "Resources/Manager.hpp"
#include "Tracer.hpp"
#include "Vulkan/DescriptorSet.hpp"
#include "Vulkan/DescriptorSetLayout.hpp"
#include "Vulkan/SharedUniformBuffer.hpp"

/* Defining the resource manager class id. */
template<>
const char * const Emeraude::Resources::Container< Emeraude::Graphics::Material::StandardResource >::ClassId{"StandardResourceContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t Emeraude::Resources::Container< Emeraude::Graphics::Material::StandardResource >::ClassUID{Observable::getClassUID()};

namespace Emeraude::Graphics::Material
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Libraries::PixelFactory;
	using namespace Saphir;
	using namespace Saphir::Keys;
	using namespace Component;

	const size_t StandardResource::ClassUID{Observable::getClassUID()};

	StandardResource::StandardResource (const std::string & name, int resourceFlagBits) noexcept
		: Interface(name, resourceFlagBits)
	{

	}

	StandardResource::~StandardResource ()
	{
		this->destroy();
	}

	bool
	StandardResource::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	const char *
	StandardResource::classLabel () const noexcept
	{
		return ClassId;
	}

	bool
	StandardResource::load () noexcept
	{
		if ( !this->beginLoading() )
		{
			return false;
		}

		//this->setColor(Magenta);

		return this->setLoadSuccess(true);
	}

	bool
	StandardResource::load (const Json::Value & data) noexcept
	{
		if ( !this->beginLoading() )
		{
			return false;
		}


		return this->setLoadSuccess(true);
	}

	bool
	StandardResource::create () noexcept
	{
		if ( this->isCreated() )
		{
			TraceWarning{ClassId} << "The material resource '" << this->name() << "' is already created !";

			return true;
		}

		if ( m_components.empty() )
		{
			TraceError{ClassId} << "The material resource '" << this->name() << "' has no component !";

			return false;
		}

		std::vector< std::shared_ptr< TextureResource::Abstract > > textures{};

		for ( auto & componentPair : m_components )
		{
			auto & component = componentPair.second->component();

			if ( !component.create() )
			{
				TraceError{ClassId} << "Unable to create component '" << to_cstring(componentPair.first) << "' of material resource '" << this->name() << "' !";

				return false;
			}

			if ( component.type() == Type::Texture )
			{
				textures.emplace_back(static_cast< const TypeTexture & >(component).texture());
			}
		}

		if ( !textures.empty() )
		{
			auto * renderer = Graphics::Renderer::instance();

			m_descriptorSetLayout = renderer->getMaterialDescriptorSetLayout(*this);

			m_descriptorSet = std::make_unique< Vulkan::DescriptorSet >(renderer->descriptorPool(), m_descriptorSetLayout);
			m_descriptorSet->setIdentifier("StandardResource-" + this->name() + "-DescriptorSet");

			if ( !m_descriptorSet->create() )
			{
				m_descriptorSet.reset();

				Tracer::error(ClassId, "Unable to create the descriptor set !");

				return false;
			}

			if ( !m_descriptorSet->writeCombinedImageSamplers(textures, 1) )
			{
				Tracer::error(ClassId, "Unable to setup the material descriptor set !");

				return false;
			}

			this->enableFlag(TexturingEnabled);
		}

		this->enableFlag(Created);

		return true;
	}

	void
	StandardResource::destroy () noexcept
	{
		m_descriptorSet.reset();
		m_descriptorSetLayout.reset();

		//m_physicalSurfaceProperties;
		m_components.clear();
		m_blendingMode = BlendingMode::None;

		/* Reset to defaults. */
		this->disableFlag(Created);
		this->disableFlag(BlendingEnabled);
		this->disableFlag(TexturingEnabled);
		this->disableFlag(Animated);
	}

	bool
	StandardResource::isCreated () const noexcept
	{
		return this->isFlagEnabled(Created);
	}

	const Physics::PhysicalSurfaceProperties &
	StandardResource::physicalSurfaceProperties () const noexcept
	{
		return m_physicalSurfaceProperties;
	}

	Physics::PhysicalSurfaceProperties &
	StandardResource::physicalSurfaceProperties () noexcept
	{
		return m_physicalSurfaceProperties;
	}

	size_t
	StandardResource::frameCount () const noexcept
	{
		if ( !this->isFlagEnabled(Animated) )
		{
			return 1;
		}

		// FIXME: Which component is animated ?

		return 1;
	}

	float
	StandardResource::duration () const noexcept
	{
		if ( !this->isFlagEnabled(Animated) )
		{
			return 0.0F;
		}

		// FIXME: Which component is animated ?

		return 0.0F;
	}

	bool
	StandardResource::isTranslucent () const noexcept
	{
		return this->isFlagEnabled(BlendingEnabled);
	}

	void
	StandardResource::enableBlending () noexcept
	{
		if ( this->isCreated() )
		{
			TraceWarning{ClassId} << "The resource '" << this->name() << "' is already created !";

			return;
		}

		this->enableFlag(BlendingEnabled);

		if ( m_blendingMode == BlendingMode::None )
		{
			m_blendingMode = BlendingMode::Normal;
		}
	}

	void
	StandardResource::setBlendingMode (BlendingMode mode) noexcept
	{
		if ( !this->isFlagEnabled(BlendingEnabled) )
		{
			TraceWarning{ClassId} << "The blending is not enabled with the material resource '" << this->name() << "' !";
		}

		m_blendingMode = mode;
	}

	BlendingMode
	StandardResource::blendingMode () const noexcept
	{
		if ( !this->isFlagEnabled(BlendingEnabled) )
		{
			TraceWarning{ClassId} << "The blending is not enabled with the material resource '" << this->name() << "' !";

			return BlendingMode::None;
		}

		return m_blendingMode;
	}

	std::shared_ptr< Vulkan::DescriptorSetLayout >
	StandardResource::descriptorSetLayout () const noexcept
	{
		return m_descriptorSetLayout;
	}

	const Vulkan::DescriptorSet *
	StandardResource::descriptorSet () const noexcept
	{
		return m_descriptorSet.get();
	}

	bool
	StandardResource::generateShaderCode (Saphir::ShaderGenerator & gen, const Geometry::Interface & geometry) const noexcept
	{
		if ( !this->isCreated() )
		{
			TraceWarning{ClassId} << "The resource '" << this->name() << "' is not created !";

			return false;
		}

		// TODO ...

		return true;
	}

	void
	StandardResource::setColor (const Color< float > & color, float shininess) noexcept
	{
		auto desaturatedColor{color};
		desaturatedColor.setSaturation(10.0F);

		this->setColor(color, desaturatedColor, shininess);
	}

	void
	StandardResource::setColor (const Color< float > & diffuseColor, const Color< float > & altColor, float shininess) noexcept
	{
		this->setAmbientComponent(altColor);
		this->setDiffuseComponent(diffuseColor);
		this->setSpecularComponent(altColor, shininess);
	}

	void
	StandardResource::setTexture (const std::shared_ptr< TextureResource::Abstract > & texture, float shininess) noexcept
	{
		this->setAmbientComponent(texture);
		this->setDiffuseComponent(texture);
		this->setSpecularComponent(texture, shininess);
	}

	void
	StandardResource::setTexture (const std::shared_ptr< TextureResource::Abstract > & diffuseTexture, const std::shared_ptr< TextureResource::Abstract > & altTexture, float shininess) noexcept
	{
		this->setAmbientComponent(altTexture);
		this->setDiffuseComponent(diffuseTexture);
		this->setSpecularComponent(altTexture, shininess);
	}

	void
	StandardResource::setTexture (const std::shared_ptr< TextureResource::Abstract > & diffuseTexture, const Color< float > & altColor, float shininess) noexcept
	{
		this->setAmbientComponent(altColor);
		this->setDiffuseComponent(diffuseTexture);
		this->setSpecularComponent(altColor, shininess);
	}

	void
	StandardResource::setAmbientComponent (const Color< float > & color) noexcept
	{
		if ( this->isCreated() )
		{
			TraceWarning{ClassId} <<
				"The resource '" << this->name() << "' is created ! "
				"Unable to create or change the ambient component.";

			return;
		}

		m_components[ComponentType::Ambient] = std::make_unique< Ambient< TypeColor > >(TypeColor{Uniforms::Ambient, color});
	}

	void
	StandardResource::setAmbientComponent (const std::shared_ptr< TextureResource::Abstract > & texture) noexcept
	{
		if ( this->isCreated() )
		{
			TraceWarning{ClassId} <<
				"The resource '" << this->name() << "' is created ! "
				"Unable to create or change the ambient component.";

			return;
		}

		m_components[ComponentType::Ambient] = std::make_unique< Ambient< TypeTexture > >(TypeTexture{Uniforms::Ambient, texture});
	}

	void
	StandardResource::setDiffuseComponent (const Color< float > & color) noexcept
	{
		if ( this->isCreated() )
		{
			TraceWarning{ClassId} <<
				"The resource '" << this->name() << "' is created ! "
				"Unable to create or change the diffuse component.";

			return;
		}

		m_components[ComponentType::Diffuse] = std::make_unique< Diffuse< TypeColor > >(TypeColor{Uniforms::Diffuse, color});
	}

	void
	StandardResource::setDiffuseComponent (const std::shared_ptr< TextureResource::Abstract > & texture) noexcept
	{
		if ( this->isCreated() )
		{
			TraceWarning{ClassId} <<
				"The resource '" << this->name() << "' is created ! "
				"Unable to create or change the diffuse component.";

			return;
		}

		m_components[ComponentType::Diffuse] = std::make_unique< Specular< TypeTexture > >(TypeTexture{Uniforms::Diffuse, texture});
	}

	void
	StandardResource::setSpecularComponent (const Color< float > & color, float shininess) noexcept
	{
		if ( this->isCreated() )
		{
			TraceWarning{ClassId} <<
				"The resource '" << this->name() << "' is created ! "
				"Unable to create or change the specular component.";

			return;
		}

		m_components[ComponentType::Specular] = std::make_unique< Specular< TypeColor > >(TypeColor{Uniforms::Specular, color}, shininess);
	}

	void
	StandardResource::setSpecularComponent (const std::shared_ptr< TextureResource::Abstract > & texture, float shininess) noexcept
	{
		if ( this->isCreated() )
		{
			TraceWarning{ClassId} <<
				"The resource '" << this->name() << "' is created ! "
				"Unable to create or change the specular component.";

			return;
		}

		m_components[ComponentType::Specular] = std::make_unique< Specular< TypeTexture > >(TypeTexture{Uniforms::Specular, texture}, shininess);
	}

	void
	StandardResource::setAutoIlluminationComponent (float value, float amount) noexcept
	{
		if ( this->isCreated() )
		{
			TraceWarning{ClassId} <<
				"The resource '" << this->name() << "' is created ! "
				"Unable to create or change the auto-illumination component.";

			return;
		}

		m_components[ComponentType::AutoIllumination] = std::make_unique< AutoIllumination< TypeValue > >(TypeValue{Uniforms::AutoIllumination, value}, amount);
	}

	void
	StandardResource::setAutoIlluminationComponent (const Color< float > & color, float amount) noexcept
	{
		if ( this->isCreated() )
		{
			TraceWarning{ClassId} <<
				"The resource '" << this->name() << "' is created ! "
				"Unable to create or change the auto-illumination component.";

			return;
		}

		m_components[ComponentType::AutoIllumination] = std::make_unique< AutoIllumination< TypeColor > >(TypeColor{Uniforms::AutoIllumination, color}, amount);
	}

	void
	StandardResource::setAutoIlluminationComponent (const std::shared_ptr< TextureResource::Abstract > & texture, float amount) noexcept
	{
		if ( this->isCreated() )
		{
			TraceWarning{ClassId} <<
				"The resource '" << this->name() << "' is created ! "
				"Unable to create or change the auto-illumination component.";

			return;
		}

		m_components[ComponentType::AutoIllumination] = std::make_unique< AutoIllumination< TypeTexture > >(TypeTexture{Uniforms::AutoIllumination, texture}, amount);
	}

	void
	StandardResource::setOpacityComponent (float value, float amount) noexcept
	{
		if ( this->isCreated() )
		{
			TraceWarning{ClassId} << "The resource '" << this->name() << "' is created ! Unable to modify it.";

			return;
		}

		m_components[ComponentType::Opacity] = std::make_unique< Opacity< TypeValue > >(TypeValue{Uniforms::Opacity, value}, amount);
	}

	void
	StandardResource::setOpacityComponent (const std::shared_ptr< TextureResource::Abstract > & texture, float amount) noexcept
	{
		if ( this->isCreated() )
		{
			TraceWarning{ClassId} << "The resource '" << this->name() << "' is created ! Unable to modify it.";

			return;
		}

		m_components[ComponentType::Opacity] = std::make_unique< Opacity< TypeTexture > >(TypeTexture{Uniforms::Opacity, texture}, amount);
	}

	void
	StandardResource::setNormalComponent (const std::shared_ptr< TextureResource::Abstract > & texture, float scale) noexcept
	{
		if ( this->isCreated() )
		{
			TraceWarning{ClassId} << "The resource '" << this->name() << "' is created ! Unable to modify it.";

			return;
		}

		m_components[ComponentType::Reflection] = std::make_unique< Normal< TypeTexture > >(TypeTexture{Uniforms::Normal, texture}, scale);
	}

	void
	StandardResource::setReflectionComponent (const std::shared_ptr< TextureResource::Abstract > & texture, float amount) noexcept
	{
		if ( this->isCreated() )
		{
			TraceWarning{ClassId} << "The resource '" << this->name() << "' is created ! Unable to modify it.";

			return;
		}

		m_components[ComponentType::Reflection] = std::make_unique< Reflection< TypeTexture > >(TypeTexture{Uniforms::Reflection, texture}, amount);
	}

	std::shared_ptr< StandardResource >
	StandardResource::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->standardMaterials().getResource(resourceName, directLoad);
	}

	std::shared_ptr< StandardResource >
	StandardResource::getDefault () noexcept
	{
		return Resources::Manager::instance()->standardMaterials().getDefaultResource();
	}
}
