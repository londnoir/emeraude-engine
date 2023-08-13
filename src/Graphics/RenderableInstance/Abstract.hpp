/*
 * Emeraude/Graphics/RenderableInstance/Abstract.hpp
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
#include <map>
#include <memory>
#include <string>

/* Local inclusions for inheritances. */
#include "FlagTrait.hpp"
#include "Observable.hpp"
#include "Observer.hpp"

/* Local inclusions for usages. */
#include "Graphics/Renderable/Interface.hpp"
#include "RenderingOptions.hpp"

/* Forward declaration for RenderableInstance::render() function. */
namespace Emeraude
{
	namespace Graphics
	{
		namespace RenderTarget
		{
			class Abstract;
		}

		class Renderer;
	}

	namespace Vulkan
	{
		class PipelineLayout;
		class GraphicsPipeline;
		class CommandBuffer;
	}
}

namespace Emeraude::Graphics::RenderableInstance
{
	/** @brief Renderable instance interface flag bits. */
	enum RenderableInstanceFlagBits
	{
		/**
		 * @brief The RenderableInstance is ready for render.
		 * @warning != The renderable is ready to draw.
		 */
		IsReadyToRender = 1,
		/**
		 * @brief Returns whether the locations are up to date in video memory.
		 * @fixme Check the usefulness of this flag !
		 */
		IsPositionSynchronized = 2,
		/** @brief States the RenderableInstance can't be loaded in rendering system and must be removed. */
		BrokenState = 4,
		/** @brief The RenderableInstance is used in instance rendering with the usage of a VBO for locations. */
		EnableInstancing = 8,
		/** @brief The RenderableInstance will use the scene light set. */
		LightingEnabled = 16,
		/**
		 * @brief The RenderableInstance will be used in shadow calculations.
		 * @note A renderableInstance can use shadow without be part of shadow calculation.
		 */
		ShadowsCastingEnabled = 32,
		/**
		 * @brief The RenderableInstance will use computed shadow.
		 * @note A renderableInstance can be part of shadow calculation but not using it.
		 */
		ReceivingShadows = 64,
		/** @brief ??? */
		IsSubRenderingEnabled = 128,
		UseInfinityView = 256,
		DisableDepthTest = 512,
		DisableDepthWrite = 1024
	};

	/**
	 * @brief This is a renderable interface for the renderer to draw a renderable object.
	 * @extends Libraries::FlagTrait This object is flag-able.
	 * @extends Libraries::Observer This object observe the renderable loading.
	 * @extends Libraries::Observable This object is observable.
	 */
	class Abstract : public Libraries::FlagTrait< uint32_t >, public Libraries::Observer, public Libraries::Observable
	{
		public:

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/** @brief Observable notification codes. */
			enum NotificationCode
			{
				/* Declares the renderable unable to go on GPU for rendering. */
				Broken,
				/* Declares the renderable ready to go on GPU for rendering. */
				ReadyToSetupOnGPU,
				/* Enumeration boundary. */
				MaxEnum
			};

			/**
			 * @brief Destructs the renderable instance.
			 */
			~Abstract () override = default;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Abstract (const Abstract & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Abstract (Abstract && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			Abstract & operator= (const Abstract & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			Abstract & operator= (Abstract && copy) noexcept = delete;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/**
			 * @brief Returns whether this instance is ready for rendering.
			 * @return bool
			 */
			[[nodiscard]]
			virtual
			inline
			bool
			isReadyToRender () const noexcept final
			{
				return this->isFlagEnabled(IsReadyToRender);
			}

			/**
			 * @brief Disables the renderable instance for rendering.
			 * @return void
			 */
			virtual
			inline
			void
			disableForRender () noexcept final
			{
				this->disableFlag(IsReadyToRender);
			}

			/**
			 * @brief Returns whether this instance is unable to get ready for rendering.
			 * @return bool
			 */
			[[nodiscard]]
			virtual
			inline
			bool
			isBroken () const noexcept final
			{
				return this->isFlagEnabled(BrokenState);
			}

			/**
			 * @brief Sets if this object will affected by the scene light.
			 * If no, the material will be fully bright.
			 * @param state The state of the lighting.
			 * @return void
			 */
			virtual
			inline
			void
			setReceivingLights (bool state) noexcept final
			{
				if ( state )
				{
					this->enableFlag(LightingEnabled);
				}
				else
				{
					this->disableFlag(LightingEnabled);
				}
			}

			/**
			 * @brief Returns whether this object is affected by the scene light or not.
			 * @return bool
			 */
			[[nodiscard]]
			virtual
			inline
			bool
			isReceivingLights () const noexcept final
			{
				return this->isFlagEnabled(LightingEnabled);
			}

			/**
			 * @brief Sets if the object should cast shadows or not on the scene.
			 * @param state The state of shadow generation from this renderable object.
			 * @return void
			 */
			virtual
			inline
			void
			enableShadowsCasting (bool state) noexcept final
			{
				if ( state )
				{
					this->enableFlag(ShadowsCastingEnabled);
				}
				else
				{
					this->disableFlag(ShadowsCastingEnabled);
				}
			}

			/**
			 * @brief Returns whether the object casts shadows on the scene.
			 * @return bool
			 */
			[[nodiscard]]
			virtual
			inline
			bool
			isShadowsCastingEnabled () const noexcept final
			{
				return this->isFlagEnabled(ShadowsCastingEnabled);
			}

			/**
			 * @brief Sets if the object should apply shadows map coming from the scene or not.
			 * @param state The state of shadow receiving on this renderable object.
			 * @return void
			 */
			virtual
			inline
			void
			setReceiveShadows (bool state) noexcept final
			{
				if ( state )
				{
					this->enableFlag(ReceivingShadows);
				}
				else
				{
					this->disableFlag(ReceivingShadows);
				}
			}

			/**
			 * @brief Returns whether the object apply shadows map coming from the scene.
			 * @return bool
			 */
			[[nodiscard]]
			virtual
			inline
			bool
			isReceivingShadows () const noexcept final
			{
				return this->isFlagEnabled(ReceivingShadows);
			}

			/**
			 * @brief Sets if the instance should be rendered with the infinity view.
			 * @param state The state.
			 * @return void
			 */
			virtual
			inline
			void
			setUseInfinityView (bool state) noexcept final
			{
				if ( state )
				{
					this->enableFlag(UseInfinityView);
				}
				else
				{
					this->disableFlag(UseInfinityView);
				}
			}

			/**
			 * @brief Returns whether the object use the infinity view to be rendered.
			 * @return bool
			 */
			[[nodiscard]]
			virtual
			inline
			bool
			isUsingInfinityView () const noexcept final
			{
				return this->isFlagEnabled(UseInfinityView);
			}

			/**
			 * @brief Disables the depth test with this instance.
			 * @param state The state.
			 * @return void
			 */
			virtual
			inline
			void
			disableDepthTest (bool state) noexcept final
			{
				if ( state )
				{
					this->enableFlag(DisableDepthTest);
				}
				else
				{
					this->disableFlag(DisableDepthTest);
				}
			}

			/**
			 * @brief Returns whether the depth test is disabled with this instance.
			 * @return bool
			 */
			[[nodiscard]]
			virtual
			inline
			bool
			isDepthTestDisabled () const noexcept final
			{
				return this->isFlagEnabled(DisableDepthTest);
			}

			/**
			 * @brief Disables the depth write with this instance.
			 * @param state The state.
			 * @return void
			 */
			virtual
			inline
			void
			disableDepthWrite (bool state) noexcept final
			{
				if ( state )
				{
					this->enableFlag(DisableDepthWrite);
				}
				else
				{
					this->disableFlag(DisableDepthWrite);
				}
			}

			/**
			 * @brief Returns whether the depth write is disabled with this instance.
			 * @return bool
			 */
			[[nodiscard]]
			virtual
			inline
			bool
			isDepthWriteDisabled () const noexcept final
			{
				return this->isFlagEnabled(DisableDepthWrite);
			}

			/**
			 * @brief Returns the renderable pointer.
			 * @return const Renderable::Interface *
			 */
			[[nodiscard]]
			virtual const Renderable::Interface * renderable () const noexcept final;

			/**
			 * @brief Sets the renderable instance broken from a child class.
			 * @note This is the release version.
			 * @return void
			 */
			virtual void setBroken () noexcept final;

			/**
			 * @brief Sets the renderable instance broken from a child class.
			 * @note This is the debug version.
			 * @param errorMessage Trace an error message.
			 * @param location If a message has to be traced, this pass the location. Default auto-generated by the mighty C++ STL.
			 * @return void
			 */
			virtual void setBroken (const std::string & errorMessage, const std_glue::source_location & location = std_glue::source_location::current()) noexcept final;

			/**
			 * @brief Sets a graphics pipeline for a combination of layer and render-pass.
			 * @param renderTarget A reference to the render target smart pointer.
			 * @param renderPassType The render pass type.
			 * @param layerIndex The index of the renderable instance layer.
			 * @param pipeline A reference to a graphics pipeline smart pointer.
			 */
			virtual void setGraphicsPipeline (const std::shared_ptr< RenderTarget::Abstract > & renderTarget, RenderPassType renderPassType, size_t layerIndex, const std::shared_ptr< Vulkan::GraphicsPipeline > & pipeline) noexcept;

			/**
			 * @brief Refresh graphics pipelines for a specific render target.
			 * @param renderTarget A reference to the render target smart pointer.
			 * @return bool
			 */
			virtual bool refreshGraphicsPipelines (const std::shared_ptr< RenderTarget::Abstract > & renderTarget) noexcept final;

			/**
			 * @brief Destroys graphics pipelines from the renderable instance for a specific render target.
			 * @param renderTarget A reference to the render target smart pointer.
			 * @return void
			 */
			virtual void destroyGraphicsPipelines (const std::shared_ptr< RenderTarget::Abstract > & renderTarget) noexcept final;

			/**
			 * @brief Validates the renderable instance by checking graphics pipeline.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool validate () noexcept;

			/**
			 * @brief Update the renderable instance for rendering.
			 * @param renderTarget A reference to the render target smart pointer.
			 * @return bool
			 */
			virtual bool updateVideoMemoryForRendering (const std::shared_ptr< Graphics::RenderTarget::Abstract > & renderTarget) noexcept = 0;

			/**
			 * @brief Draws the instance in a render target.
			 * @param renderTarget A reference to the render target smart pointer.
			 * @param renderPassType The render pass type into the render target.
			 * @param commandBuffer A reference to a command buffer.
			 * @return void
			 */
			virtual void render (const std::shared_ptr< RenderTarget::Abstract > & renderTarget, RenderPassType renderPassType, const Vulkan::CommandBuffer & commandBuffer) const noexcept final;

		protected:

			/**
			 * @brief Constructs a renderable instance.
			 * @param renderable A reference to renderable interface smart pointer.
			 * @param initialInstanceFlagBits The renderable instance level flags.
			 */
			explicit Abstract (const std::shared_ptr< Renderable::Interface > & renderable, int initialInstanceFlagBits) noexcept;

			/**
			 * @brief Returns the number of instance to draw.
			 * @note This is a more convenient named method than get the vertex count from the VBO.
			 * @return size_t
			 */
			[[nodiscard]]
			virtual size_t instanceCount () const noexcept = 0;

			/**
			 * @brief Returns whether model matrices are created in video memory.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isModelMatricesCreated () const noexcept = 0;

			/**
			 * @brief Returns whether the instance use an uniform buffer object for the model matrices.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool useModelUniformBufferObject () const noexcept = 0;

			/**
			 * @brief Returns whether the instance use a vertex buffer object for the model matrices.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool useModelVertexBufferObject () const noexcept = 0;

			/**
			 * @brief Prepares the model matrices into video memory.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool createModelMatrices () noexcept = 0;

			/**
			 * @brief Resets model matrices in video memory.
			 * @return bool
			 */
			virtual bool resetModelMatrices () noexcept = 0;

			/**
			 * @brief Binds the renderable instance resources to a command buffer.
			 * @param commandBuffer A reference to a command buffer.
			 * @param pipelineLayout A reference to a pipeline layout.
			 * @param layerIndex The current layer to bind.
			 * @param setOffset The next set value.
			 * @return void
			 */
			virtual void bindInstanceLayer (const Vulkan::CommandBuffer & commandBuffer, const Vulkan::PipelineLayout & pipelineLayout, size_t layerIndex, uint32_t & setOffset) const noexcept = 0;

			mutable std::mutex m_GPUMemoryAccess{}; // NOLINT

		private:

			/** @copydoc Libraries::Observer::onNotification() */
			[[nodiscard]]
			bool onNotification (const Observable * observable, int notificationCode, const std::any & data) noexcept override;

			std::shared_ptr< Renderable::Interface > m_renderable{};
			std::vector< RenderingOptions > m_layerRenderingOptions{};
			std::map<
				std::shared_ptr< RenderTarget::Abstract >,
				std::map<
					RenderPassType,
					std::vector< std::shared_ptr< Vulkan::GraphicsPipeline > >
				>
			> m_graphicsPipelines{};
	};
}
