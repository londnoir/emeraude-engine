/*
 * Emeraude/Graphics/Renderer.cpp
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

#include "Renderer.hpp"

/* Local inclusions */
#include "Core.hpp"
#include "Tracer.hpp"
#include "Arguments.hpp"
#include "Settings.hpp"
#include "Window.hpp"
#include "Vulkan/Instance.hpp"
#include "Vulkan/SwapChain.hpp"
#include "Vulkan/Sampler.hpp"
#include "Scenes/Scene.hpp"
#include "Saphir/ShaderGenerator.hpp"
#include "Saphir/LightGenerator.hpp"

namespace Emeraude::Graphics
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Libraries::PixelFactory;
	using namespace Vulkan;
	using namespace Saphir;

	const size_t Renderer::ClassUID{Observable::getClassUID()};
	Renderer * Renderer::s_instance{nullptr}; // NOLINT NOTE: Singleton behavior

	Renderer::Renderer (const Arguments & arguments, Settings & coreSettings, Instance & instance, Window & window, RenderableInstance::VertexBufferFormatManager & vertexBufferFormatManager) noexcept
		: ServiceInterface(ClassId), ConsoleControllable(ClassId),
		  m_arguments(arguments), m_coreSettings(coreSettings), m_vulkanInstance(instance), m_window(window), m_vertexBufferFormatManager(vertexBufferFormatManager)
	{
		if ( s_instance != nullptr )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", constructor called twice !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

			std::terminate();
		}

		s_instance = this;

		m_flags[DebugMode] = m_vulkanInstance.isDebugModeEnabled();

		/* Framebuffer clear color value. */
		this->setClearColor({1.0F / 3, 1.0F / 3, 1.0F / 3});

		/* Framebuffer clear depth/stencil values. */
		this->setClearDepthStencilValues(1.0F, 0);

		this->observe(&m_window);
	}

	Renderer::~Renderer ()
	{
		s_instance = nullptr;
	}

	Renderer *
	Renderer::instance () noexcept
	{
		return s_instance;
	}

	void
	Renderer::setClearColor (const Color< float > & clearColor) noexcept
	{
		m_clearColors[0].color.float32[0] = clearColor.red();
		m_clearColors[0].color.float32[1] = clearColor.green();
		m_clearColors[0].color.float32[2] = clearColor.blue();
		m_clearColors[0].color.float32[3] = clearColor.alpha();
	}

	void
	Renderer::setClearDepthStencilValues (float depth, uint32_t stencil) noexcept
	{
		m_clearColors[1].depthStencil.depth = depth;
		m_clearColors[1].depthStencil.stencil = stencil;
	}

	Color< float >
	Renderer::getClearColor () const noexcept
	{
		return {
			m_clearColors[0].color.float32[0],
			m_clearColors[0].color.float32[1],
			m_clearColors[0].color.float32[2],
			m_clearColors[0].color.float32[3]
		};
	}

	float
	Renderer::getClearDepthValue () const noexcept
	{
		return m_clearColors[1].depthStencil.depth;
	}

	uint32_t
	Renderer::getClearStencilValue () const noexcept
	{
		return m_clearColors[1].depthStencil.stencil;
	}

	bool
	Renderer::onInitialize () noexcept
	{
		if ( m_arguments.get("--disable-video").isPresent() || !m_coreSettings.getAs< bool >(EnabledKey, DefaultEnabled) )
		{
			Tracer::warning(ClassId, "Graphics renderer disabled at startup.");

			return true;
		}

		if ( !m_vulkanInstance.usable() )
		{
			Tracer::fatal(ClassId, "The Vulkan instance is not usable !");

			return false;
		}

		/* Graphics device selection. */
		m_device = m_vulkanInstance.getGraphicsDevice(m_window);

		if ( m_device == nullptr )
		{
			Tracer::fatal(ClassId, "Unable to find a suitable graphics device !");

			return false;
		}

		/* Create a descriptor pool (FIXME: maybe not the right place !) */
		const auto sizes = std::vector< VkDescriptorPoolSize >{
				{VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 16}
		};

		m_descriptorPool = std::make_shared< DescriptorPool >(m_device, sizes, 64, VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT);
		m_descriptorPool->setIdentifier("Renderer-Main-DescriptorPool");

		if ( !m_descriptorPool->createOnHardware() )
		{
			Tracer::fatal(ClassId, "Unable to create the descriptor pool !");

			return false;
		}

		/* Create the swap chain for presenting images to screen. */
		m_swapChain = std::make_shared< SwapChain >(m_device, m_window);
		m_swapChain->setIdentifier("Renderer-Main-SwapChain");

		if ( m_swapChain->createOnHardware() )
		{
			this->notify(SwapChainCreated, m_swapChain);
		}
		else
		{
			Tracer::fatal(ClassId, "Unable to create the swap chain !");

			return false;
		}

		/* Create a command pools and command buffers following the swap-chain images. */
		if ( !this->createCommandSystem() )
		{
			Tracer::fatal(ClassId, "Unable to create a test command buffers !");

			return false;
		}

		m_flags[Usable] = true;

		return true;
	}

	bool
	Renderer::onTerminate () noexcept
	{
		m_flags[Usable] = false;

		m_samplers.clear();

		m_pipelines.clear();
		m_pipelineLayouts.clear();

		m_descriptorSetLayouts.clear();
		m_descriptorPool.reset();

		this->destroyCommandSystem();

		m_swapChain.reset();

		/* Release the pointer on the device. */
		m_device.reset();

		return true;
	}

	bool
	Renderer::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	Renderer::usable () const noexcept
	{
		return m_flags[Usable];
	}

	const std::shared_ptr< Device > &
	Renderer::device () const noexcept
	{
		return m_device;
	}

	const std::shared_ptr< DescriptorPool > &
	Renderer::descriptorPool () const noexcept
	{
		return m_descriptorPool;
	}

	const std::shared_ptr< SwapChain > &
	Renderer::swapChain () const noexcept
	{
		return m_swapChain;
	}

	const Time::StatisticsTime< std::chrono::high_resolution_clock > &
	Renderer::statistics () const noexcept
	{
		return m_statistics;
	}

	std::shared_ptr< DescriptorSetLayout >
	Renderer::getViewDescriptorSetLayout (const RenderTarget::Abstract & renderTarget, int flags) noexcept
	{
		auto descriptorSetLayout = std::make_shared< DescriptorSetLayout >(m_device, flags);
		descriptorSetLayout->setIdentifier((std::stringstream{} << "Renderer-" << renderTarget.id() << "-DescriptorSetLayout").str());
		descriptorSetLayout->declareUniformBuffer(0, VK_SHADER_STAGE_VERTEX_BIT);

		const auto hash = descriptorSetLayout->hash();

		const auto descriptorSetLayoutIt = m_descriptorSetLayouts.find(hash);

		if ( descriptorSetLayoutIt != m_descriptorSetLayouts.cend() )
		{
			descriptorSetLayout->destroyFromHardware();

			return descriptorSetLayoutIt->second;
		}

		if ( !descriptorSetLayout->createOnHardware() )
		{
			Tracer::error(ClassId, "Unable to create a view descriptor set layout !");

			return {};
		}

		auto result = m_descriptorSetLayouts.emplace(hash, descriptorSetLayout);

#ifdef DEBUG
		if ( !result.second )
		{
			Tracer::fatal(ClassId, "Unable to insert result into map !");

			return {};
		}
#endif

		return result.first->second;
	}

	std::shared_ptr< DescriptorSetLayout >
	Renderer::getModelDescriptorSetLayout (const RenderableInstance::Abstract & renderableInstance, int flags) noexcept
	{
		auto descriptorSetLayout = std::make_shared< DescriptorSetLayout >(m_device, flags);
		descriptorSetLayout->setIdentifier("Renderer-" + renderableInstance.renderable()->name() + "-DescriptorSetLayout");
		descriptorSetLayout->declareUniformBuffer(0, VK_SHADER_STAGE_VERTEX_BIT);

		const auto hash = descriptorSetLayout->hash();

		const auto descriptorSetLayoutIt = m_descriptorSetLayouts.find(hash);

		if ( descriptorSetLayoutIt != m_descriptorSetLayouts.cend() )
		{
			descriptorSetLayout->destroyFromHardware();

			return descriptorSetLayoutIt->second;
		}

		if ( !descriptorSetLayout->createOnHardware() )
		{
			Tracer::error(ClassId, "Unable to create a geometry descriptor set layout !");

			return {};
		}

		auto result = m_descriptorSetLayouts.emplace(hash, descriptorSetLayout);

#ifdef DEBUG
		if ( !result.second )
		{
			Tracer::fatal(ClassId, "Unable to insert result into map !");

			return {};
		}
#endif

		return result.first->second;
	}

	std::shared_ptr< DescriptorSetLayout >
	Renderer::getMaterialDescriptorSetLayout (const Material::Interface & material, int flags) noexcept
	{
		auto descriptorSetLayout = std::make_shared< DescriptorSetLayout >(m_device, flags);
		descriptorSetLayout->setIdentifier("Renderer-" + material.name() + "-DescriptorSetLayout");
		// FIXME : Check bits against what's is in use in the material and light.
		descriptorSetLayout->declareUniformBuffer(0, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT);

		if ( material.usingTexture() )
		{
			descriptorSetLayout->declareCombinedImageSampler(1, VK_SHADER_STAGE_FRAGMENT_BIT);
		}

		const auto hash = descriptorSetLayout->hash();

		const auto descriptorSetLayoutIt = m_descriptorSetLayouts.find(hash);

		if ( descriptorSetLayoutIt != m_descriptorSetLayouts.cend() )
		{
			descriptorSetLayout->destroyFromHardware();

			return descriptorSetLayoutIt->second;
		}

		if ( !descriptorSetLayout->createOnHardware() )
		{
			Tracer::error(ClassId, "Unable to create a material descriptor set layout !");

			return {};
		}

		auto result = m_descriptorSetLayouts.emplace(hash, descriptorSetLayout);

#ifdef DEBUG
		if ( !result.second )
		{
			Tracer::fatal(ClassId, "Unable to insert result into map !");

			return {};
		}
#endif

		return result.first->second;
	}

	std::shared_ptr< PipelineLayout >
	Renderer::getPipelineLayout (const std::vector< std::shared_ptr< DescriptorSetLayout > > & descriptorSetLayouts) noexcept
	{
		const auto hash = PipelineLayout::getHash(descriptorSetLayouts, {}, 0);

		const auto pipelineLayoutIt = m_pipelineLayouts.find(hash);

		if ( pipelineLayoutIt != m_pipelineLayouts.cend() )
		{
			return pipelineLayoutIt->second;
		}

		auto pipelineLayout = std::make_shared< PipelineLayout >(m_device, descriptorSetLayouts);
		pipelineLayout->setIdentifier("Renderer-Main-PipelineLayout");

		if ( !pipelineLayout->createOnHardware() )
		{
			Tracer::error(ClassId, "Unable to create the pipeline layout !");

			return {};
		}

		auto result = m_pipelineLayouts.emplace(hash, pipelineLayout);

#ifdef DEBUG
		if ( !result.second )
		{
			Tracer::fatal(ClassId, "Unable to insert result into map !");

			return {};
		}
#endif

		return result.first->second;
	}

	std::shared_ptr< Sampler >
	Renderer::getSampler (size_t type, VkSamplerCreateFlags createFlags) noexcept
	{
		const auto samplerIt = m_samplers.find(type);

		if ( samplerIt != m_samplers.cend() )
		{
			return samplerIt->second;
		}

		auto sampler = std::make_shared< Sampler >(m_device, createFlags);
		sampler->setIdentifier("Renderer-Main-Sampler");

		if ( !sampler->createOnHardware() )
		{
			Tracer::error(ClassId, "Unable to create a sampler !");

			return {};
		}

		auto result = m_samplers.emplace(type, sampler);

#ifdef DEBUG
		if ( !result.second )
		{
			Tracer::fatal(ClassId, "Unable to insert the sampler into map !");

			return {};
		}
#endif

		return result.first->second;
	}

	bool
	Renderer::getRenderableInstanceReadyForRender (RenderableInstance::Abstract & renderableInstance, const std::shared_ptr< RenderTarget::Abstract > & renderTarget, const Scenes::LightSet & lightSet) noexcept
	{
		Tracer::debug(ClassId, "[GPU-instance-upload] Get a renderer instance ready for rendering ...");

		/* If the object is ready to render, there is nothing more to do ! */
		if ( renderableInstance.isReadyToRender() )
		{
			return true;
		}

		/* A previous try to set up the renderable instance for rendering has failed ... */
		if ( renderableInstance.isBroken() )
		{
			return false;
		}

		/* NOTE: Checking the renderable interface.
		 * This is the shared part between all renderable instances. */
		/* TODO: Check for renderable interface already in video memory
		 * to reduce renderable instance preparation time. */
		const auto * renderable = renderableInstance.renderable();

		if ( renderable == nullptr )
		{
#ifdef DEBUG
			renderableInstance.setBroken("The renderable instance has no renderable interface !");
#else
			renderableInstance.setBroken();
#endif

			return false;
		}

		/* NOTE: Check whether the renderable interface is ready for instantiation.
		 * If not, this is no big deal, a loading event exists to relaunch the whole process. */
		if ( !renderable->isReadyForInstantiation() )
		{
			return true;
		}

		/* NOTE: The geometry interface is the same for every layer of the renderable interface. */
		const auto * geometry = renderable->geometry();
		const auto layerCount = renderable->layerCount();
		const auto enableInstancing = renderableInstance.isFlagEnabled(RenderableInstance::EnableInstancing);

		/* FIXME/TODO: Determine here the number of render pass types
		 * requested from the renderable instance. */
		const std::vector< RenderPassType > renderPassTypes{
			RenderPassType::SimpleWithFakeLightPass,
			//RenderPassType::AmbientPass,
			//RenderPassType::DirectionalLightPass
		};

#ifdef DEBUG

		/* NOTE: These tests only exists in debug mode,
		 * they are already done beyond isReadyForInstantiation(). */
		if ( geometry == nullptr )
		{
			renderableInstance.setBroken((std::stringstream{} <<
				"The renderable interface has no geometry interface ! "
				"Unable to setup the renderable instance '" << renderable->name() << "' for rendering."
			).str());

			return false;
		}

		if ( layerCount == 0 )
		{
			renderableInstance.setBroken((std::stringstream{} <<
				"The renderable interface has no layer ! It must have at least one. "
				"Unable to setup the renderable instance '" << renderable->name() << "' for rendering."
			).str());

			return false;
		}

#endif

		for ( size_t layerIndex = 0; layerIndex < layerCount; layerIndex++ )
		{
			TraceDebug{ClassId} << "[GPU-instance-upload] With layer #" << layerIndex << " ...";

			/* NOTE: The material interface is unique per layer. */
			const auto * material = renderable->material(layerIndex);

			for ( auto renderPassType : renderPassTypes )
			{
				TraceDebug{ClassId} << "[GPU-instance-upload] With render pass #" << to_string(renderPassType) << " ...";

				/* 1. Preparing every shader and vertex buffer format. */
				GraphicsShaderContainer shaders{};

				if ( !renderable->prepareShaders(*geometry, *material, renderPassType, enableInstancing, shaders) )
				{
#ifdef DEBUG
					renderableInstance.setBroken((std::stringstream{} <<
						"Unable to prepare shader source code and "
						"the vertex buffer format for layer #" << layerIndex << " "
						"of the renderable instance '" << renderable->name() << "' "
						"and the render pass type '" << to_string(renderPassType) << "' !"
					).str());
#else
					renderableInstance.setBroken();
#endif

					return false;
				}

				auto vertexBufferFormat = m_vertexBufferFormatManager.getVertexBufferFormat(*geometry, *shaders.vertexShader());

				if ( vertexBufferFormat == nullptr )
				{
					TraceError{ClassId} <<
						"Unable to configure the geometry '" << geometry->name() << "' and "
						"the material '" << material->name() << "' to get vertex buffer format !";

					return false;
				}

				/* 2. Preparing all descriptor set layouts to get the proper pipeline layout. */
				std::vector< std::shared_ptr< DescriptorSetLayout > > descriptorSetLayouts{};

				if ( !this->prepareDescriptorSetLayouts(*renderTarget, renderableInstance, *material, enableInstancing, descriptorSetLayouts) )
				{
#ifdef DEBUG
					renderableInstance.setBroken((std::stringstream{} <<
						"Unable to gather descriptor set layouts for layer #" << layerIndex << " "
						"of the renderable instance '" << renderable->name() << "' "
						"and the render pass type '" << to_string(renderPassType) << "' !"
					).str());
#else
					renderableInstance.setBroken();
#endif

					return false;
				}

				/* 3. Get the proper pipeline layout according to all descriptor set layouts to build the graphics pipeline. */
				const auto pipelineLayout = this->getPipelineLayout(descriptorSetLayouts);

				if ( pipelineLayout == nullptr )
				{
#ifdef DEBUG
					renderableInstance.setBroken((std::stringstream{} <<
						"Unable to get a pipeline layout for layer #" << layerIndex << " "
						"of the renderable instance '" << renderable->name() << "' "
						"and the render pass type '" << to_string(renderPassType) << "' !"
					).str());
#else
					renderableInstance.setBroken();
#endif

					return false;
				}

				/* 4. Retrieve the graphics pipeline for the combination of the current renderable instance layer and the render pass. */
				const auto graphicsPipeline = this->getGraphicsPipeline(*renderTarget, renderableInstance, pipelineLayout, vertexBufferFormat, shaders);

				if ( graphicsPipeline == nullptr )
				{
#ifdef DEBUG
					renderableInstance.setBroken((std::stringstream{} <<
						"Unable to get a graphics pipeline for layer #" << layerIndex << " "
						"of the renderable instance '" << renderable->name() << "' "
						"and the render pass type '" << to_string(renderPassType) << "' !"
					).str());
#else
					renderableInstance.setBroken();
#endif

					return false;
				}

				renderableInstance.setGraphicsPipeline(renderTarget, renderPassType, layerIndex, graphicsPipeline);
			}
		}

		return renderableInstance.validate();
	}

	bool
	Renderer::refreshRenderableInstance (RenderableInstance::Abstract & renderableInstance, const std::shared_ptr< RenderTarget::Abstract > & renderTarget, const Scenes::LightSet & lightSet) noexcept
	{
		renderableInstance.disableForRender();

		/* A previous try to set up the renderable instance for rendering has failed ... */
		if ( renderableInstance.isBroken() )
		{
			return false;
		}

		/*const auto renderable = renderableInstance.renderable();

		const auto layerCount = renderable->layerCount();

		std::vector< RenderPassType > renderPassTypes{
			RenderPassType::SimpleWithFakeLightPass
		};

		for ( size_t layerIndex = 0; layerIndex < layerCount; layerIndex++ )
		{

		}*/

		return renderableInstance.validate();
	}

	bool
	Renderer::prepareDescriptorSetLayouts (const RenderTarget::Abstract & renderTarget, const RenderableInstance::Abstract & renderableInstance, const Material::Interface & material, bool enableInstance, std::vector< std::shared_ptr< DescriptorSetLayout > > & descriptorSetLayouts) noexcept
	{
		/* The descriptor set layout for the view. */
		{
			auto descriptorSetLayout = this->getViewDescriptorSetLayout(renderTarget);

			if ( descriptorSetLayout == nullptr )
			{
				Tracer::error(ClassId, "Unable to get the view descriptor set layout !");

				return false;
			}

			descriptorSetLayouts.emplace_back(descriptorSetLayout);
		}

		/* The descriptor set layout for the model. */
		if ( !enableInstance )
		{
			auto descriptorSetLayout = this->getModelDescriptorSetLayout(renderableInstance);

			if ( descriptorSetLayout == nullptr )
			{
				Tracer::error(ClassId, "Unable to get the model descriptor set layout !");

				return false;
			}

			descriptorSetLayouts.emplace_back(descriptorSetLayout);
		}

		{
			auto descriptorSetLayout = material.descriptorSetLayout();

			if ( descriptorSetLayout == nullptr )
			{
				Tracer::error(ClassId, "Unable to get the material descriptor set layout !");

				return false;
			}

			descriptorSetLayouts.emplace_back(descriptorSetLayout);
		}

		return true;
	}

	std::shared_ptr< Vulkan::GraphicsPipeline >
	Renderer::getGraphicsPipeline (const RenderTarget::Abstract & renderTarget, const RenderableInstance::Abstract & renderableInstance, const std::shared_ptr< Vulkan::PipelineLayout > & pipelineLayout, const std::shared_ptr< RenderableInstance::VertexBufferFormat > & vertexBufferFormat, const GraphicsShaderContainer & shaders) noexcept
	{
		/* FIXME: Fake hash ! */
		const auto hash = GraphicsPipeline::getHash();

		const auto pipelineIt = m_pipelines.find(hash);

		if ( pipelineIt != m_pipelines.cend() )
		{
			return pipelineIt->second;
		}

		auto pipeline = std::make_shared< GraphicsPipeline >(pipelineLayout, vertexBufferFormat, shaders);
		pipeline->setIdentifier((std::stringstream{} << "Renderer-" << renderableInstance.renderable()->name() << "-GraphicsPipeline").str());

		if ( !pipeline->create(renderTarget, renderableInstance) )
		{
			Tracer::error(ClassId, "Unable to create a graphics pipeline !");

			return {};
		}

		auto result = m_pipelines.emplace(hash, pipeline);

#ifdef DEBUG
		if ( !result.second )
		{
			Tracer::fatal(ClassId, "Unable to insert the graphics pipeline into map !");

			return {};
		}
#endif

		return result.first->second;
	}

	std::shared_ptr< Vulkan::GraphicsPipeline >
	Renderer::getTBNSpaceDisplayPipeline () noexcept
	{
		using namespace Keys;

		if ( m_TBNSpaceDisplay != nullptr )
		{
			return m_TBNSpaceDisplay;
		}

		GraphicsShaderContainer shaders{};
		SetIndexes indexes{};
		indexes.enableSet(SetType::PerView);
		/*if ( !enableInstancing )
		{
			indexes.enableSet(SetType::PerModel);
		}*/
		indexes.enableSet(SetType::PerObjectLayer);


		{ 
			auto shader = shaders.initVertexShader("TBNSpaceDisplayVertexShader");
			
			ShaderGenerator gen{shader};
			gen.setIndexes(indexes);

			/* Input declarations. */
			gen.declare(Declaration::InputAttribute{VertexAttributeType::Position});
			gen.declare(Declaration::InputAttribute{VertexAttributeType::Tangent});
			gen.declare(Declaration::InputAttribute{VertexAttributeType::Binormal});
			gen.declare(Declaration::InputAttribute{VertexAttributeType::Normal});

			if ( gen.modelMatricesType() == ModelMatrixType::VertexBufferObject )
			{
				gen.declare(RenderTarget::View::Texture2D::getViewUniformBlock(indexes.set(SetType::PerView)));
				gen.declare(Declaration::InputAttribute{VertexAttributeType::ModelMatrixR0});
				gen.declare(Declaration::StageOutput{0, GLSL::Matrix4, "MVP", GLSL::Flat});

				Code{gen, Location::Output} <<
					"MVP = " << ShaderGenerator::viewUniform(UniformBlocks::Component::ViewProjectionMatrix) << " * " << Attributes::ModelMatrix << ';';
			}

			/* Output declarations. */
			gen.declare(Declaration::StageOutput{GLSL::FloatVector4, ShaderVariables::TangentWorldSpace});
			gen.declare(Declaration::StageOutput{GLSL::FloatVector4, ShaderVariables::BinormalWorldSpace});
			gen.declare(Declaration::StageOutput{GLSL::FloatVector4, ShaderVariables::NormalWorldSpace});

			/* Instructions. */
			Code{gen, Location::Top} <<
				"const float length = 10.0";

			Code{gen, Location::Output} <<
				"gl_Position = vec4(" << Attributes::Position << ", 1.0);" << Line::End <<
				ShaderVariables::TangentWorldSpace << " = vec4(" << Attributes::Tangent << ", 0.0) * length;" << Line::End <<
				ShaderVariables::BinormalWorldSpace << " = vec4(" << Attributes::Binormal << ", 0.0) * length;" << Line::End <<
				ShaderVariables::NormalWorldSpace << " = vec4(" << Attributes::Normal << ", 0.0) * length;";
			
			if ( !gen.writeShader() )
			{
				Tracer::error(ClassId, "Unable to generate the TBN space display vertex shader !");

				return {};
			}
		}

		{
			auto shader = shaders.initVertexShader("TBNSpaceDisplayGeometryShader");

			ShaderGenerator gen{shader};
			gen.setIndexes(indexes);

			/* Input declarations. */
			gen.declare(Declaration::InputPrimitive{GLSL::Geometry::In::Primitive::Triangles});

			gen.declare(Declaration::StageInput{GLSL::FloatVector4, ShaderVariables::TangentWorldSpace});
			gen.declare(Declaration::StageInput{GLSL::FloatVector4, ShaderVariables::BinormalWorldSpace});
			gen.declare(Declaration::StageInput{GLSL::FloatVector4, ShaderVariables::NormalWorldSpace});

			std::string modelViewProjectionMatrix;

			switch ( gen.modelMatricesType() )
			{
				case ModelMatrixType::UniformBufferObject :
					gen.declare(RenderableInstance::Unique::getModelUniformBlock(gen.indexes().set(SetType::PerModel)));

					modelViewProjectionMatrix = ShaderGenerator::modelUniform(UniformBlocks::Component::ModelViewProjectionMatrix);
					break;

				case ModelMatrixType::VertexBufferObject :
					gen.declare(Declaration::StageInput{0, GLSL::Matrix4, "MVP", GLSL::Flat});

					modelViewProjectionMatrix.assign("MVP[index]");
					break;
					
				default:
					break;
			}

			/* Output declarations. */
			gen.declare(Declaration::OutputPrimitive{GLSL::Geometry::Out::Primitive::LineStrip, 18});
			gen.declare(Declaration::StageOutput{ShaderVariables::Color, GLSL::Smooth});

			/* Instructions. */
			{
				std::stringstream code;

				code <<
					"\t" "const vec4 White = vec4(1.0, 1.0, 1.0, 1.0);" "\n"
					"\t" "const vec4 Red = vec4(1.0, 0.0, 0.0, 1.0);" "\n"
					"\t" "const vec4 Green = vec4(0.0, 1.0, 0.0, 1.0);" "\n"
					"\t" "const vec4 Blue = vec4(0.0, 0.0, 1.0, 1.0);" "\n"
					"\t" "const float VectorLength = 4.0;" "\n\n"
					
					"\t" "for ( int index = 0; index < gl_in.length(); index++ )" "\n"
					"\t" "{" "\n"
					/* Tangent (X-Axis -> R) */
					"\t\t" << ShaderVariables::Color << " = White;" "\n"
					"\t\t" << "gl_Position = " << modelViewProjectionMatrix << " * gl_in[index].gl_Position;" "\n"
					"\t\t" << "EmitVertex();" "\n\n"
					
					"\t\t" << ShaderVariables::Color << " = Red;" "\n"
					"\t\t" << "gl_Position = " << modelViewProjectionMatrix << " * (gl_in[index].gl_Position + " << ShaderVariables::TangentWorldSpace << "[index]) * VectorLength;" "\n"
					"\t\t" << "EmitVertex();" "\n\n"
					
					"\t\t" << "EndPrimitive();" "\n\n"
					
					/* Binormal (Y-Axis -> G) */
					"\t\t" << ShaderVariables::Color << " = White;" "\n"
					"\t\t" << "gl_Position = " << modelViewProjectionMatrix << " * gl_in[index].gl_Position;" << '\n' <<
					"\t\t" << "EmitVertex();" "\n\n"
					
					"\t\t" << ShaderVariables::Color << " = Green;" "\n"
					"\t\t" << "gl_Position = " << modelViewProjectionMatrix << " * (gl_in[index].gl_Position + " << ShaderVariables::BinormalWorldSpace << "[index]) * VectorLength;" "\n"
					"\t\t" << "EmitVertex();" "\n\n"
					
					"\t\t" << "EndPrimitive();" "\n\n"
					
					/* Normal (Z-Axis -> B) */
					"\t\t" << ShaderVariables::Color << " = White;" "\n"
					"\t\t" << "gl_Position = " << modelViewProjectionMatrix << " * gl_in[index].gl_Position;" << '\n' <<
					"\t\t" << "EmitVertex();" "\n\n"
					
					"\t\t" << ShaderVariables::Color << " = Blue;" "\n"
					"\t\t" << "gl_Position = " << modelViewProjectionMatrix << " * (gl_in[index].gl_Position + " << ShaderVariables::NormalWorldSpace << "[index]) * VectorLength;" "\n"
					"\t\t" << "EmitVertex();" "\n\n"
					
					"\t\t" << "EndPrimitive();" "\n"
					"\t" "}" "\n";

				gen.addInstruction(code.str());
			}

			if ( !gen.writeShader() )
			{
				Tracer::error(ClassId, "Unable to generate the TBN space display geometry shader !");

				return {};
			}
		}

		{
			auto shader = shaders.initVertexShader("TBNSpaceDisplayFragmentShader");

			ShaderGenerator gen{shader};
			gen.setIndexes(indexes);

			/* Input declarations. */
			gen.declare(Declaration::StageInput{ShaderVariables::Color, GLSL::Smooth});

			/* Output declarations. */
			gen.declareDefaultOutputFragment();

			/* Instructions. */
			Code{gen, Location::Output} <<
				ShaderVariables::OutputFragment << " = " << ShaderVariables::Color << ';';

			if ( !gen.writeShader() )
			{
				Tracer::error(ClassId, "Unable to generate the TBN space display fragment shader !");

				return {};
			}
		}

		/*m_TBNSpaceDisplay = std::make_shared< GraphicsPipeline >(pipelineLayout, vertexBufferFormat, shaders);
		m_TBNSpaceDisplay->setIdentifier((std::stringstream{} << "Renderer-TBNSpaceDisplay-GraphicsPipeline").str());

		if ( !m_TBNSpaceDisplay->create(renderTarget, renderableInstance) )
		{
			Tracer::error(ClassId, "Unable to create the TBN space display graphics pipeline !");

			return {};
		}*/

		return m_TBNSpaceDisplay;
	}

	void
	Renderer::renderFrame (const std::shared_ptr< const Scenes::Scene > & scene, const Overlay::Manager & overlayManager, const Dev::Manager & devManager, unsigned long lifetime) noexcept
	{
		if ( !this->usable() )
		{
			return;
		}

		if ( m_swapChain->isDegraded() )
		{
			TraceInfo{ClassId} << "The swap-chain is degraded !";

			if ( !this->recreateSwapChain() )
			{
				Core::instance()->stop();
			}
		}

		m_statistics.start();

		/* First we get an image ready to render into it. */
		uint32_t imageIndex = 0;

		if ( !m_swapChain->acquireNextImage(imageIndex) )
		{
			return;
		}

		/* Then we need the command buffer linked to this image by its index. */
		auto commandBuffer = m_commandBuffers[imageIndex];

		if ( !commandBuffer->begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT) )
		{
			return;
		}

		const auto & extent = m_swapChain->extent();

		VkRect2D renderArea{};
		renderArea.offset = {0, 0};
		renderArea.extent = {extent.width, extent.height};

		commandBuffer->beginRenderPass(*m_swapChain->renderPass(), *m_swapChain->framebuffer(), renderArea, m_clearColors, VK_SUBPASS_CONTENTS_INLINE);

		/* Render the scene */
		if ( scene != nullptr )
		{
			scene->updateVideoMemoryForRendering(m_swapChain);

			scene->render(m_swapChain, *commandBuffer);

			//devManager.render(commandBuffer);

			/*switch ( m_sceneRenderingMode )
			{
				case SceneRenderingMode::Basic :
				{

				}
					break;

				case SceneRenderingMode::Forward :
				{

				}
					break;

				case SceneRenderingMode::Deferred :
				{

				}
					break;
			}*/
		}

		/* Render the UI */
		{

		}

		commandBuffer->endRenderPass();

		if ( !commandBuffer->end() )
		{
			return;
		}

		if ( !m_swapChain->submitCommandBuffer(commandBuffer, imageIndex) )
		{
			return;
		}

		m_statistics.stop();
	}

	void
	Renderer::renderShadowMaps (const Scenes::Scene & scene) noexcept
	{
		if ( !m_flags[ShadowMapsEnabled] )
		{
			return;
		}

		for ( const auto & shadowMap : scene.masterControlConsole().renderToShadowMaps() )
		{

		}
	}

	void
	Renderer::renderRenderToTextures (const Scenes::Scene & scene) noexcept
	{
		if ( !m_flags[RenderToTexturesEnabled] )
		{
			return;
		}

		for ( const auto & renderToTexture : scene.masterControlConsole().renderToTextures() )
		{

		}
	}

	void
	Renderer::renderViews (const Scenes::Scene & scene) noexcept
	{
		for ( const auto & renderToView : scene.masterControlConsole().renderToViews() )
		{

		}
	}

	void
	Renderer::renderFinal () noexcept
	{

	}

	bool
	Renderer::onNotification (const Libraries::Observable * observable, int notificationCode, const std::any & /*data*/) noexcept
	{
		if ( observable->is(Window::ClassUID) )
		{
			switch ( notificationCode )
			{
				/* Updates the handle surface information. */
				case Window::OSNotifiesFramebufferResized :
					if ( m_window.surface()->update(this->device()->physicalDevice()) )
					{
						Tracer::success(ClassId, "Framebuffer resized. Window surface info updated.");
					}
					else
					{
						Tracer::error(ClassId, "Unable to update the handle surface from a framebuffer resized !");
					}
					break;

				case Window::Created :
				case Window::Destroyed :
				case Window::Centered :
				case Window::OSNotifiesWindowGetFocus :
				case Window::OSNotifiesWindowLostFocus :
				case Window::OSNotifiesWindowMovedTo :
				case Window::OSNotifiesWindowVisible :
				case Window::OSNotifiesWindowHidden :
				case Window::OSNotifiesWindowSizeMaximized :
				case Window::OSNotifiesWindowSizeMinimized :
				case Window::OSNotifiesWindowResized :
				case Window::OSRequestsToRescaleContentBy :
				case Window::OSRequestsToRefreshContent :
				case Window::OSRequestsToTerminate :
				default :
					TraceDebug{ClassId} << "Event #" << notificationCode << " from the window ignored.";
					break;
			}

			return true;
		}

#ifdef DEBUG
		/* NOTE: Don't know what is it, goodbye ! */
		TraceInfo{ClassId} <<
			"Received an unhandled event from observable @" << observable << " (code:" << notificationCode << ") ! "
			"Forgetting it ...";
#endif

		return false;
	}

	bool
	Renderer::createCommandSystem () noexcept
	{
		const auto imageCount = m_swapChain->imageCount();

		m_commandPools.resize(imageCount);
		m_commandBuffers.resize(imageCount);

		for ( size_t index = 0; index < imageCount; index++ )
		{
			auto & commandPool = m_commandPools[index];
			auto & commandBuffer = m_commandBuffers[index];

			commandPool = std::make_shared< CommandPool >(
				m_device,
				m_device->getGraphicsFamilyIndex(),
				VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT
			);
			commandPool->setIdentifier((std::stringstream{} << "Renderer-Frame" << index << "-CommandPool").str());

			if ( !commandPool->createOnHardware() )
			{
				TraceError{ClassId} << "Unable to create the command pool #" << index << " !";

				return false;
			}

			commandBuffer = std::make_shared< CommandBuffer >(commandPool);
			commandBuffer->setIdentifier((std::stringstream{} << "Renderer-Frame" << index << "-CommandBuffer").str());

			if ( !commandBuffer->isCreated() )
			{
				TraceError{ClassId} << "Unable to create the command buffer #" << index << " !";

				return false;
			}
		}

		return true;
	}

	void
	Renderer::destroyCommandSystem () noexcept
	{
		m_device->waitIdle();

		m_commandBuffers.clear();
		m_commandPools.clear();
	}

	bool
	Renderer::recreateSwapChain () noexcept
	{
		//this->destroyCommandSystem();

		/* NOTE: Wait for a valid framebuffer dimensions in case of handle minimisation. */
		if ( !m_window.waitValidWindowSize() )
		{
			Tracer::fatal(ClassId, "Unable to get a back a valid handle !");

			return false;
		}

		if ( !m_swapChain->recreate() )
		{
			Tracer::fatal(ClassId, "Unable to rebuild the swap chain !");

			return false;
		}

		/*if ( !this->createCommandSystem() )
		{
			Tracer::fatal(ClassId, "Unable to rebuild the command system !");

			return false;
		}*/

		this->notify(SwapChainRecreated, m_swapChain);

		return true;
	}
}
