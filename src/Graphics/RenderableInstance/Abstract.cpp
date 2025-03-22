/*
 * src/Graphics/RenderableInstance/Abstract.cpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2025 - Sébastien Léon Claude Christian Bémelmans "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Emeraude-Engine; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Complete project and additional information can be found at :
 * https://github.com/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#include "Abstract.hpp"

/* STL inclusions. */
#include <any>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <mutex>
#include <ranges>
#include <string>

/* Local inclusions. */
#include "Graphics/Renderer.hpp"
#include "Resources/ResourceTrait.hpp"
#include "Saphir/Generator/SceneRendering.hpp"
#include "Saphir/Program.hpp"
#include "Scenes/Component/AbstractLightEmitter.hpp"
#include "Tracer.hpp"
#include "Vulkan/CommandBuffer.hpp"
#include "Vulkan/GraphicsPipeline.hpp"

namespace EmEn::Graphics::RenderableInstance
{
	using namespace EmEn::Libs;
	using namespace EmEn::Vulkan;
	using namespace Saphir;
	using namespace Keys;

	static constexpr auto TracerTag{"RenderableInstance"};

	const size_t Abstract::ClassUID{getClassUID("AbstractRenderableInstance")};

	Abstract::Abstract (const std::shared_ptr< Renderable::Interface > & renderable, uint32_t flagBits) noexcept
		: FlagTrait(flagBits),
		m_renderable(renderable)
	{

	}

	bool
	Abstract::isReadyToRender (const std::shared_ptr< RenderTarget::Abstract > & renderTarget) const noexcept
	{
		const auto renderTargetIt = m_renderTargets.find(renderTarget);

		if ( renderTargetIt == m_renderTargets.cend() )
		{
			return false;
		}

		return renderTargetIt->second.isReadyToRender;
	}

	void
	Abstract::disableForRender (const std::shared_ptr< RenderTarget::Abstract > & renderTarget) noexcept
	{
		const auto renderTargetIt = m_renderTargets.find(renderTarget);

		if ( renderTargetIt != m_renderTargets.cend() )
		{
			renderTargetIt->second.isReadyToRender = false;
			renderTargetIt->second.renderPasses.clear();
		}
	}

	bool
	Abstract::getReadyForRender (const Scenes::Scene & scene, const std::shared_ptr< RenderTarget::Abstract > & renderTarget, const std::vector< RenderPassType > & renderPassTypes, Renderer & renderer) noexcept
	{
		/* NOTE : Checking the renderable interface.
		 * This is the shared part between all renderable instances. */
		/* TODO: Check for renderable interface already in video memory to reduce renderable instance preparation time. */
		if ( m_renderable == nullptr )
		{
			this->setBroken("The renderable instance has no renderable associated !");

			return false;
		}

		/* NOTE : Check whether the renderable interface is ready for instantiation.
		 * If not, this is no big deal, a loading event exists to relaunch the whole process. */
		if ( !m_renderable->isReadyForInstantiation() )
		{
			return true;
		}

		const auto layerCount = m_renderable->layerCount();

#ifdef DEBUG
		/* NOTE : This test only exists in debug mode because it is already performed beyond isReadyForInstantiation(). */
		if ( layerCount == 0 )
		{
			std::stringstream errorMessage;
			errorMessage <<
				"The renderable interface has no layer ! It must have at least one. "
				"Unable to setup the renderable instance '" << m_renderable->name() << "' for rendering.";

			this->setBroken(errorMessage.str());

			return false;
		}

		/* NOTE : The geometry interface is the same for every layer of the renderable interface. */
		const auto * geometry = m_renderable->geometry();

		/* NOTE : This test only exists in debug mode because it is already performed beyond isReadyForInstantiation(). */
		if ( geometry == nullptr )
		{
			std::stringstream errorMessage;
			errorMessage <<
				"The renderable interface has no geometry interface ! "
				"Unable to setup the renderable instance '" << m_renderable->name() << "' for rendering.";

			this->setBroken(errorMessage.str());

			return false;
		}
#endif

		auto renderTargetIt = m_renderTargets.find(renderTarget);

		if ( renderTargetIt == m_renderTargets.end() )
		{
			renderTargetIt = m_renderTargets.try_emplace(renderTarget).first;
		}

		for ( const auto renderPassType : renderPassTypes )
		{
			auto & renderTargets = renderTargetIt->second;

			auto renderPassIt = renderTargets.renderPasses.find(renderPassType);

			if ( renderPassIt == renderTargets.renderPasses.end() )
			{
				renderPassIt = renderTargets.renderPasses.try_emplace(renderPassType).first;
				renderPassIt->second.resize(layerCount);
			}

			for ( size_t layerIndex = 0; layerIndex < layerCount; layerIndex++ )
			{
				std::stringstream name;
				name << "RenderableInstance" << to_string(renderPassType);

				/* The first step is to generate the shaders source code from every resource involved. */
				Generator::SceneRendering generator{
					renderer.primaryServices().settings(),
					name.str(),
					renderTarget,
					this->shared_from_this(),
					layerIndex,
					renderPassType,
					scene
				};

				if ( renderer.shaderManager().showGeneratedSourceCode() )
				{
					generator.enableDebugging();
				}

				/* The vertex buffer format, responsible for the specific VBO is handled with the shaders. */
				if ( !generator.generateProgram(renderer.vertexBufferFormatManager()) )
				{
					std::stringstream errorMessage;
					errorMessage <<
						"Unable to generate the renderable instance '" << m_renderable->name() << "' "
						"(RenderPass:'" << to_string(renderPassType) << "', layer:" << layerIndex << ") program !";

					this->setBroken(errorMessage.str());

					return false;
				}

				/* The second step is to check every resource needed by shaders (UBO, Samples, etc.).
				 * NOTE: VBO is an exception done before. */
				if ( !generator.generateProgramLayout(renderer) )
				{
					std::stringstream errorMessage;
					errorMessage <<
						"Unable to get the program layout for layer #" << layerIndex << " "
						"of the renderable instance '" << m_renderable->name() << "' "
						"and the render pass type '" << to_string(renderPassType) << "' !";

					this->setBroken(errorMessage.str());

					return false;
				}

				/* The third step is to check if separate shaders already exists to avoid an extra compilation.
				 * Retrieve the graphics pipeline for the combination of the current renderable instance layer and the render pass. */
				if ( !generator.createGraphicsPipeline(renderer) )
				{
					std::stringstream errorMessage;
					errorMessage <<
						"Unable to get a program for layer #" << layerIndex << " "
						"of the renderable instance '" << m_renderable->name() << "' "
						"and the render pass type '" << to_string(renderPassType) << "' !";

					this->setBroken(errorMessage.str());

					return false;
				}

				renderPassIt->second[layerIndex] = generator.program();
			}
		}

		renderTargetIt->second.isReadyToRender = true;

		/* FIXME: Bad idea ! */
		//this->setShadowProgram(m_graphicsRenderer.getShadowProgram(renderTarget, this->shared_from_this()));

		if ( this->isDisplayTBNSpaceEnabled() )
		{
			this->setTBNSpaceProgram(renderer.getTBNSpaceProgram(renderTarget, this->shared_from_this()));
		}

		return this->validate(renderTarget);
	}

	void
	Abstract::setBroken (const std::string & errorMessage, const std::source_location & location) noexcept
	{
		this->enableFlag(BrokenState);

		Tracer::error(TracerTag, errorMessage, location);
	}

	bool
	Abstract::refreshGraphicsPipelines (const std::shared_ptr< RenderTarget::Abstract > & renderTarget) noexcept
	{
		const std::lock_guard< std::mutex > lock{m_GPUMemoryAccess};

		const auto renderTargetIt = m_renderTargets.find(renderTarget);

		if ( renderTargetIt == m_renderTargets.end() )
		{
			return false;
		}

		size_t error = 0;

		for ( const auto & programs : std::ranges::views::values(renderTargetIt->second.renderPasses) )
		{
			for ( const auto & program : programs )
			{
				if ( !program->graphicsPipeline()->recreateOnHardware(*renderTarget, *this) )
				{
					error++;
				}
			}
		}

		return error == 0;
	}

	void
	Abstract::destroyGraphicsPipelines (const std::shared_ptr< RenderTarget::Abstract > & renderTarget) noexcept
	{
		const std::lock_guard< std::mutex > lock{m_GPUMemoryAccess};

		m_renderTargets.erase(renderTarget);
	}

	bool
	Abstract::validate (const std::shared_ptr< RenderTarget::Abstract > & renderTarget) noexcept
	{
		const auto renderTargetIt = m_renderTargets.find(renderTarget);

		if ( renderTargetIt == m_renderTargets.cend() )
		{
			return false;
		}

		const auto & renderPasses = renderTargetIt->second.renderPasses;

		if ( renderPasses.empty() )
		{
			return false;
		}

		for ( const auto & graphicsPipelines : std::ranges::views::values(renderPasses) )
		{
			if ( graphicsPipelines.empty() )
			{
				return false;
			}

			for ( const auto & graphicsPipeline : graphicsPipelines )
			{
				if ( graphicsPipeline == nullptr )
				{
					return false;
				}
			}
		}

		return true;
	}

	void
	Abstract::castShadows (const std::shared_ptr< RenderTarget::Abstract > & renderTarget, const CommandBuffer & commandBuffer) const noexcept
	{
		if ( m_shadowProgram == nullptr )
		{
			//Tracer::error(TracerTag, "No shadow program available !");

			return;
		}

		const auto pipelineLayout = m_shadowProgram->pipelineLayout();

		commandBuffer.bind(*m_shadowProgram->graphicsPipeline());

		/* Bind view UBO. */
		if ( this->isFlagEnabled(EnableInstancing) )
		{
			commandBuffer.bind(
				*renderTarget->viewMatrices().descriptorSet(),
				*pipelineLayout,
				VK_PIPELINE_BIND_POINT_GRAPHICS,
				0
			);
		}

		for ( size_t layerIndex = 0; layerIndex < m_renderable->layerCount(); layerIndex++ )
		{
			this->bindInstanceModelLayer(commandBuffer, layerIndex);

			this->pushMatrices(commandBuffer, *pipelineLayout, renderTarget->viewMatrices(), *m_shadowProgram);

			commandBuffer.draw(*m_renderable->geometry(), layerIndex, static_cast< uint32_t >(this->instanceCount()));
		}
	}

	void
	Abstract::render (const std::shared_ptr< RenderTarget::Abstract > & renderTarget, const Scenes::Component::AbstractLightEmitter * lightEmitter, RenderPassType renderPassType, const CommandBuffer & commandBuffer) const noexcept
	{
		const std::lock_guard< std::mutex > lock{m_GPUMemoryAccess};

		/* NOTE: Select the render target. */
		const auto renderTargetIt = m_renderTargets.find(renderTarget);

		if ( renderTargetIt == m_renderTargets.cend() )
		{
			TraceError{TracerTag} << "There is no program for render target '" << renderTarget->id() << "' registered in the renderable instance (Renderable:" << m_renderable->name() << ") !";

			return;
		}

		/* NOTE: Select the render pass type. */
		const auto & renderPasses = renderTargetIt->second.renderPasses;

		const auto renderPassTypeIt = renderPasses.find(renderPassType);

		if ( renderPassTypeIt == renderPasses.cend() )
		{
			TraceError{TracerTag} << "There is no program for render target '" << renderTarget->id() << "' and the render pass type '" << to_string(renderPassType) << "' registered in the renderable instance (Renderable:" << m_renderable->name() << ") !";

			return;
		}

		const auto * geometry = m_renderable->geometry();
		const auto & programs = renderPassTypeIt->second;

		for ( size_t layerIndex = 0; layerIndex < programs.size(); layerIndex++ )
		{
			const auto & program = programs[layerIndex];

			if ( program == nullptr )
			{
				continue;
			}

			const auto pipelineLayout = program->pipelineLayout();

			/* Bind the graphics pipeline. */
			commandBuffer.bind(*program->graphicsPipeline());

			/* Bind renderable instance VBO/IBO. */
			this->bindInstanceModelLayer(commandBuffer, layerIndex);

			/* Configure the push constants. */
			this->pushMatrices(commandBuffer, *pipelineLayout, renderTarget->viewMatrices(), *program);

			uint32_t setOffset = 0;

			/* Bind view UBO. */
			commandBuffer.bind(
				*renderTarget->viewMatrices().descriptorSet(),
				*pipelineLayout,
				VK_PIPELINE_BIND_POINT_GRAPHICS,
				setOffset++
			);

			/* Bind light UBO. */
			if ( lightEmitter != nullptr && lightEmitter->isCreated() )
			{
				commandBuffer.bind(
					*lightEmitter->descriptorSet(),
					*pipelineLayout,
					VK_PIPELINE_BIND_POINT_GRAPHICS,
					setOffset++,
					lightEmitter->UBOOffset()
				);
			}

			/* Bind material UBO and samplers. */
			const auto * material = m_renderable->material(layerIndex);

			commandBuffer.bind(
				*material->descriptorSet(),
				*pipelineLayout,
				VK_PIPELINE_BIND_POINT_GRAPHICS,
				setOffset++
			);

			if ( material->isAnimated() )
			{
				commandBuffer.draw(*geometry, m_frameIndex, static_cast< uint32_t >(this->instanceCount()));
			}
			else
			{
				commandBuffer.draw(*geometry, layerIndex, static_cast< uint32_t >(this->instanceCount()));
			}
		}
	}

	void
	Abstract::renderTBNSpace (const std::shared_ptr< RenderTarget::Abstract > & renderTarget, const CommandBuffer & commandBuffer) const noexcept
	{
		if ( m_TBNSpaceProgram == nullptr )
		{
			Tracer::error(TracerTag, "No TBN space program available !");

			return;
		}

		const auto pipelineLayout = m_TBNSpaceProgram->pipelineLayout();

		commandBuffer.bind(*m_TBNSpaceProgram->graphicsPipeline());

		/* Bind view UBO. */
		if ( this->isFlagEnabled(EnableInstancing) )
		{
			commandBuffer.bind(
				*renderTarget->viewMatrices().descriptorSet(),
				*pipelineLayout,
				VK_PIPELINE_BIND_POINT_GRAPHICS,
				0
			);
		}

		for ( size_t layerIndex = 0; layerIndex < m_renderable->layerCount(); layerIndex++ )
		{
			this->bindInstanceModelLayer(commandBuffer, layerIndex);

			this->pushMatrices(commandBuffer, *pipelineLayout, renderTarget->viewMatrices(), *m_TBNSpaceProgram);

			commandBuffer.draw(*m_renderable->geometry(), layerIndex, static_cast< uint32_t >(this->instanceCount()));
		}
	}

	bool
	Abstract::onNotification (const ObservableTrait * observable, int notificationCode, const std::any & /*data*/) noexcept
	{
		if ( observable == m_renderable.get() )
		{
			switch ( notificationCode )
			{
				case Resources::ResourceTrait::LoadFinished :
					this->notify(ReadyToSetupOnGPU, this->shared_from_this());
					break;

				case Resources::ResourceTrait::LoadFailed :
				{
					std::stringstream errorMessage;
					errorMessage <<
						"Unable to load the renderable '" << m_renderable->name() << "' ! "
						"Set the renderable instance as broken.";

					this->setBroken(errorMessage.str());
				}
					break;

				default:
					break;
			}

			return true;
		}

		return false;
	}
}
