/*
 * src/Graphics/RenderableInstance/Abstract.cpp
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
#include "Resources/ResourceTrait.hpp"
#include "Vulkan/GraphicsPipeline.hpp"
#include "Vulkan/CommandBuffer.hpp"
#include "Graphics/Renderer.hpp"
#include "Saphir/Program.hpp"
#include "Scenes/Component/AbstractLightEmitter.hpp"
#include "Tracer.hpp"

namespace Emeraude::Graphics::RenderableInstance
{
	using namespace Libraries;
	using namespace Emeraude::Vulkan;
	using namespace Saphir;
	using namespace Keys;

	static constexpr auto TracerTag{"RenderableInstance"};

	const size_t Abstract::ClassUID{getClassUID("AbstractRenderableInstance")};

	Abstract::Abstract (const std::shared_ptr< Renderable::Interface > & renderable, uint32_t flagBits) noexcept
		: FlagTrait(flagBits), m_renderable(renderable)
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

		return !renderTargetIt->second.empty();
	}

	void
	Abstract::disableForRender (const std::shared_ptr< RenderTarget::Abstract > & renderTarget) noexcept
	{
		const auto renderTargetIt = m_renderTargets.find(renderTarget);

		if ( renderTargetIt != m_renderTargets.cend() )
		{
			renderTargetIt->second.clear();
		}
	}

	void
	Abstract::setBroken (const std::string & errorMessage, const std::source_location & location) noexcept
	{
		this->enableFlag(BrokenState);

		Tracer::error(TracerTag, errorMessage, location);
	}

	void
	Abstract::setProgram (const std::shared_ptr< RenderTarget::Abstract > & renderTarget, RenderPassType renderPassType, size_t layerIndex, const std::shared_ptr<  Program > & program) noexcept
	{
		auto renderTargetIt = m_renderTargets.find(renderTarget);

		if ( renderTargetIt == m_renderTargets.end() )
		{
			renderTargetIt = m_renderTargets.try_emplace(renderTarget).first;
		}

		auto & renderPasses = renderTargetIt->second;

		auto renderPassIt = renderPasses.find(renderPassType);

		if ( renderPassIt == renderPasses.end() )
		{
			renderPassIt = renderPasses.try_emplace(renderPassType).first;
			renderPassIt->second.resize(m_renderable->layerCount());
		}

		renderPassIt->second[layerIndex] = program;
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

		for ( const auto & programs : std::ranges::views::values(renderTargetIt->second) )
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

		const auto & renderPasses = renderTargetIt->second;

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

		const auto * geometry = m_renderable->geometry();

		const auto renderTargetIt = m_renderTargets.find(renderTarget);

		if ( renderTargetIt == m_renderTargets.cend() )
		{
			TraceError{TracerTag} << "There is no program for render target '" << renderTarget->id() << "' registered in the renderable instance (Renderable:" << m_renderable->name() << ") !";

			return;
		}

		const auto renderPassTypeIt = renderTargetIt->second.find(renderPassType);

		if ( renderPassTypeIt == renderTargetIt->second.cend() )
		{
			TraceError{TracerTag} << "There is no program for render target '" << renderTarget->id() << "' and the render pass type '" << to_string(renderPassType) << "' registered in the renderable instance (Renderable:" << m_renderable->name() << ") !";

			return;
		}

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
					this->setBroken((std::stringstream{} <<
						"Unable to load the renderable '" << m_renderable->name() << "' ! "
						"Set the renderable instance as broken."
					).str());
					break;

				default:
					break;
			}

			return true;
		}

		return false;
	}
}
