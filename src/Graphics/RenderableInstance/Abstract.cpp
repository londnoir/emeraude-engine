/*
 * Emeraude/Graphics/RenderableInstance/Abstract.cpp
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

#include "Abstract.hpp"

/* Local inclusions. */
#include "Graphics/Renderer.hpp"
#include "Graphics/ViewMatricesInterface.hpp"
#include "Tracer.hpp"
#include "Vulkan/CommandBuffer.hpp"
#include "Vulkan/GraphicsPipeline.hpp"
#include "Vulkan/PipelineLayout.hpp"

namespace Emeraude::Graphics::RenderableInstance
{
	using namespace Libraries;
	using namespace Emeraude::Vulkan;
	using namespace Saphir;
	using namespace Saphir::Keys;

	constexpr auto TracerTag{"RenderableInstance"};

	const size_t Abstract::ClassUID{Observable::getClassUID()};

	Abstract::Abstract (const std::shared_ptr< Renderable::Interface > & renderable, int initialInstanceFlagBits) noexcept
		: FlagTrait(initialInstanceFlagBits), m_renderable(renderable)
	{

	}

	bool
	Abstract::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(TracerTag, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	void
	Abstract::setBroken () noexcept
	{
		this->enableFlag(BrokenState);

		this->notify(Broken, this);
	}

	void
	Abstract::setBroken (const std::string & errorMessage, const std_glue::source_location & location) noexcept
	{
		this->enableFlag(BrokenState);

		Tracer::error(TracerTag, errorMessage, location);

		this->notify(Broken, this);
	}

	const Renderable::Interface *
	Abstract::renderable () const noexcept
	{
		return m_renderable.get();
	}

	void
	Abstract::setGraphicsPipeline (const std::shared_ptr< RenderTarget::Abstract > & renderTarget, RenderPassType renderPassType, size_t layerIndex, const std::shared_ptr< Vulkan::GraphicsPipeline > & pipeline) noexcept
	{
		auto renderTargetIt = m_graphicsPipelines.find(renderTarget);

		if ( renderTargetIt == m_graphicsPipelines.end() )
		{
			renderTargetIt = m_graphicsPipelines.try_emplace(renderTarget).first;
		}

		auto & renderPasses = renderTargetIt->second;

		auto renderPassIt = renderPasses.find(renderPassType);

		if ( renderPassIt == renderPasses.end() )
		{
			renderPassIt = renderPasses.try_emplace(renderPassType).first;
			renderPassIt->second.resize(m_renderable->layerCount());
		}

		renderPassIt->second[layerIndex] = pipeline;
	}

	bool
	Abstract::refreshGraphicsPipelines (const std::shared_ptr< RenderTarget::Abstract > & renderTarget) noexcept
	{
		const std::lock_guard< std::mutex > lock{m_GPUMemoryAccess};

		auto renderTargetIt = m_graphicsPipelines.find(renderTarget);

		if ( renderTargetIt == m_graphicsPipelines.end() )
		{
			return false;
		}

		size_t error = 0;

		for ( const auto & renderPassPair : renderTargetIt->second )
		{
			for ( const auto & graphicsPipeline : renderPassPair.second )
			{
				if ( !graphicsPipeline->recreate(*renderTarget, *this) )
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

		m_graphicsPipelines.erase(renderTarget);

		if ( !this->validate() )
		{
			Tracer::warning(TracerTag, "The renderable instance is no more renderable !");
		}
	}

	bool
	Abstract::validate () noexcept
	{
		this->disableFlag(IsReadyToRender);

		if ( m_graphicsPipelines.empty() )
		{
			return false;
		}

		for ( const auto & renderTargetIt : m_graphicsPipelines )
		{
			if ( renderTargetIt.second.empty() )
			{
				return false;
			}

			for ( const auto & renderPass : renderTargetIt.second )
			{
				if ( renderPass.second.empty() )
				{
					return false;
				}

				for ( const auto & graphicsPipeline : renderPass.second )
				{
					if ( graphicsPipeline == nullptr )
					{
						return false;
					}
				}
			}
		}

		this->enableFlag(IsReadyToRender);

		return true;
	}

	void
	Abstract::render (const std::shared_ptr< RenderTarget::Abstract > & renderTarget, RenderPassType renderPassType, const CommandBuffer & commandBuffer) const noexcept
	{
		const std::lock_guard< std::mutex > lock{m_GPUMemoryAccess};

		const auto * geometry = this->renderable()->geometry();

		/* FIXME: Create a loop-less version and create persistence with bindings to avoid multiple commands. */
		auto renderTargetIt = m_graphicsPipelines.find(renderTarget);

		if ( renderTargetIt == m_graphicsPipelines.cend() )
		{
			return;
		}

		auto renderPassTypeIt = renderTargetIt->second.find(renderPassType);

		if ( renderPassTypeIt == renderTargetIt->second.cend() )
		{
			return;
		}

		for ( size_t layerIndex = 0; layerIndex < renderPassTypeIt->second.size(); layerIndex++ )
		{
			const auto & pipeline = renderPassTypeIt->second[layerIndex];

			if ( pipeline == nullptr )
			{
				continue;
			}

			const auto pipelineLayout = pipeline->pipelineLayout();

			/* Bind the graphic pipeline (ex glUseProgram()). */
			commandBuffer.bind(*pipeline);

			uint32_t setOffset = 0;

			/* Bind view UBO (Must be set #0). */
			commandBuffer.bind(
				*renderTarget->viewMatrices().descriptorSet(this->isUsingInfinityView()),
				*pipelineLayout,
				VK_PIPELINE_BIND_POINT_GRAPHICS,
				setOffset++
			);

			/* Bind renderable instance. */
			this->bindInstanceLayer(commandBuffer, *pipelineLayout, layerIndex, setOffset);

			/* Draw the geometry (ex glDraw())*/
			commandBuffer.draw(*geometry, layerIndex, this->instanceCount());
		}
	}

	bool
	Abstract::onNotification (const Observable * observable, int notificationCode, const std::any & /*data*/) noexcept
	{
		if ( observable == m_renderable.get() )
		{
			switch ( notificationCode )
			{
				case Resources::ResourceTrait::LoadFinished :
					TraceSuccess{TracerTag} << "Renderable '" << m_renderable->name() << "' is ready for instance.";

					this->notify(ReadyToSetupOnGPU, this);
					break;

				case Resources::ResourceTrait::LoadFailed :
					this->setBroken((std::stringstream{} << "Unable to load the renderable '" << m_renderable->name() << "' ! Set the renderable instance as broken.").str());
					break;

				default:
					break;
			}

			return true;
		}

		return false;
	}
}
