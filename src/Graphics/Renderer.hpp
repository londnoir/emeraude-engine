/*
 * Emeraude/Graphics/Renderer.hpp
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
#include <memory>
#include <vector>
#include <array>

/* Local inclusions for inheritances. */
#include "ServiceInterface.hpp"
#include "ConsoleControllable.hpp"
#include "Observer.hpp"

/* Local inclusions for usages. */
#include "PixelFactory/Color.hpp"
#include "Time/StatisticsTime.hpp"
#include "Types.hpp"
#include "RenderableInstance/VertexBufferFormatManager.hpp"

/* Third-Party inclusions. */
#include "Third-Party-Inclusion/vulkan.hpp"

/* Forward declarations. */
namespace Emeraude
{
	namespace Vulkan
	{
		class Instance;
		class SwapChain;
		class Device;
		class DescriptorPool;
		class DescriptorSetLayout;
		class CommandPool;
		class CommandBuffer;
		class PipelineLayout;
		class GraphicsPipeline;
		class Sampler;
		class GraphicsShaderContainer;
	}

	namespace Graphics
	{
		namespace Material
		{
			class Interface;
		}

		namespace Geometry
		{
			class Interface;
		}

		namespace RenderableInstance
		{
			class Abstract;
		}

		namespace RenderTarget
		{
			class Abstract;
		}
	}

	namespace Dev
	{
		class Manager;
	}

	namespace Overlay
	{
		class Manager;
	}

	namespace Saphir
	{
		class AbstractShader;
	}

	namespace Scenes
	{
		class Scene;
		class LightSet;
	}

	class Arguments;
	class Settings;
	class Window;
}

namespace Emeraude::Graphics
{
	/**
	 * @brief The graphics renderer service class.
	 * @extends Emeraude::ServiceInterface The renderer is a service.
	 * @extends Emeraude::ConsoleControllable The renderer can be controlled by the console.
	 * @extends Libraries::Observer The renderer needs to observe handle changes for instance.
	 */
	class Renderer final : public ServiceInterface, public ConsoleControllable, public Libraries::Observer
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"RendererService"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/* Settings keys */
			static constexpr auto EnabledKey = "Video/Enabled";
			static constexpr auto DefaultEnabled = true;
			static constexpr auto StereoEnabledKey = "Video/StereoEnabled";
			static constexpr auto DefaultStereoEnabled = false;
			static constexpr auto DoubleBufferEnabledKey = "Video/DoubleBufferEnabled";
			static constexpr auto DefaultDoubleBufferEnabled = true;

			/** @brief Observable notification codes. */
			enum NotificationCode
			{
				SwapChainCreated,
				SwapChainRecreated,
				SwapChainDestroyed,
				/* Enumeration boundary. */
				MaxEnum
			};

			/** @brief Defines the rendering mode for a current frame. */
			enum class SceneRenderingMode
			{
				Basic,
				Forward,
				Deferred
			};

			/**
			 * @brief Constructs the graphics renderer.
			 * @param arguments A reference to the core arguments.
			 * @param coreSettings A reference to the core settings.
			 * @param instance A reference to the Vulkan instance.
			 * @param window A reference to a handle.
			 * @param vertexBufferFormatManager A reference to the vertex buffer format manager.
			 */
			Renderer (const Arguments & arguments, Settings & coreSettings, Vulkan::Instance & instance, Window & window, RenderableInstance::VertexBufferFormatManager & vertexBufferFormatManager) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Renderer (const Renderer & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Renderer (Renderer && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			Renderer & operator= (const Renderer & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			Renderer & operator= (Renderer && copy) noexcept = delete;

			/**
			 * @brief Destructs the graphics renderer.
			 */
			~Renderer () override;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::ServiceInterface::usable() */
			[[nodiscard]]
			bool usable () const noexcept override;

			/**
			 * @brief Sets the clear value for the color buffer for the next rendering.
			 * @param clearColor A reference to a color.
			 * @return void
			 */
			void setClearColor (const Libraries::PixelFactory::Color< float > & clearColor) noexcept;

			/**
			 * @brief Sets the clear values for the depth/stencil buffers for the next rendering.
			 * @param depth The depth value.
			 * @param stencil The stencil value.
			 * @return void
			 */
			void setClearDepthStencilValues (float depth, uint32_t stencil) noexcept;

			/**
			 * @brief Returns the clear color.
			 * @return Libraries::PixelFactory::Color< float >
			 */
			[[nodiscard]]
			Libraries::PixelFactory::Color< float > getClearColor () const noexcept;

			/**
			 * @brief Returns the depth clear value.
			 * @return float
			 */
			[[nodiscard]]
			float getClearDepthValue () const noexcept;

			/**
			 * @brief Returns the stencil clear value.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t getClearStencilValue () const noexcept;

			/**
			 * @brief Returns the selected logical device used for graphics.
			 * @return const std::shared_ptr< Vulkan::Device > &
			 */
			[[nodiscard]]
			const std::shared_ptr< Vulkan::Device > & device () const noexcept;

			/**
			 * @brief Returns the descriptor pool.
			 * @return const std::shared_ptr< Vulkan::DescriptorPool > &
			 */
			[[nodiscard]]
			const std::shared_ptr< Vulkan::DescriptorPool > & descriptorPool () const noexcept;

			/**
			 * @brief Returns the swap chain.
			 * @return const std::shared_ptr< Vulkan::SwapChain > &
			 */
			[[nodiscard]]
			const std::shared_ptr< Vulkan::SwapChain > & swapChain () const noexcept;

			/**
			 * @brief Returns rendering statistics.
			 * @return const Libraries::Time::StatisticsTime< std::chrono::high_resolution_clock > &
			 */
			[[nodiscard]]
			const Libraries::Time::StatisticsTime< std::chrono::high_resolution_clock > & statistics () const noexcept;

			/**
			 * @brief Gets or creates a descriptor set layout for a render target (View UBO).
			 * @param renderTarget A pointer to the render target.
			 * @param flags Flags for create info. Default 0.
			 * @return std::shared_ptr< Vulkan::DescriptorSetLayout >
			 */
			[[nodiscard]]
			std::shared_ptr< Vulkan::DescriptorSetLayout > getViewDescriptorSetLayout (const RenderTarget::Abstract & renderTarget, int flags = 0) noexcept;

			/**
			 * @brief Gets or creates a descriptor set layout for a renderable instance (Model UBO + ModelView UBO).
			 * @param renderableInstance A pointer to the renderable instance.
			 * @param flags Flags for create info. Default 0.
			 * @return std::shared_ptr< Vulkan::DescriptorSetLayout >
			 */
			[[nodiscard]]
			std::shared_ptr< Vulkan::DescriptorSetLayout > getModelDescriptorSetLayout (const RenderableInstance::Abstract & renderableInstance, int flags = 0) noexcept;

			/**
			 * @brief Gets or creates a descriptor set layout for a material.
			 * @param material A pointer to the material.
			 * @param flags Flags for create info. Default 0.
			 * @return std::shared_ptr< Vulkan::DescriptorSetLayout >
			 */
			[[nodiscard]]
			std::shared_ptr< Vulkan::DescriptorSetLayout > getMaterialDescriptorSetLayout (const Material::Interface & material, int flags = 0) noexcept;

			/**
			 * @brief Returns or creates a pipeline layout according to requirements.
			 * @param descriptorSetLayouts A reference to a list of descriptor set layout.
			 * @return std::shared_ptr< Vulkan::PipelineLayout >
			 */
			[[nodiscard]]
			std::shared_ptr< Vulkan::PipelineLayout > getPipelineLayout (const std::vector< std::shared_ptr< Vulkan::DescriptorSetLayout > > & descriptorSetLayouts) noexcept;

			/**
			 * @brief Gets a graphics pipeline for a renderable instance.
			 * @param renderTarget A reference to a render target.
			 * @param renderableInstance A reference to the renderable instance.
			 * @param pipelineLayout A reference to the pipeline layout smart pointer.
			 * @param vertexBufferFormat A reference to the vertex format.
			 * @param shaders A reference to a list of shaders being used to render the renderable instance.
			 * @return std::shared_ptr< Vulkan::GraphicsPipeline >
			 */
			[[nodiscard]]
			std::shared_ptr< Vulkan::GraphicsPipeline > getGraphicsPipeline (const RenderTarget::Abstract & renderTarget, const RenderableInstance::Abstract & renderableInstance, const std::shared_ptr< Vulkan::PipelineLayout > & pipelineLayout, const std::shared_ptr< RenderableInstance::VertexBufferFormat > & vertexBufferFormat, const Vulkan::GraphicsShaderContainer & shaders) noexcept;

			/**
			 * @brief Gets a specific graphics pipeline for displaying the vertex TBN spaces.
			 * @param renderTarget A reference to a render target.
			 * @param renderableInstance A reference to the renderable instance.
			 * @param pipelineLayout A reference to the pipeline layout smart pointer.
			 * @param vertexBufferFormat A reference to the vertex format.
			 * @param shaders A reference to a list of shaders being used to render the renderable instance.
			 * @return std::shared_ptr< Vulkan::GraphicsPipeline >
			 */
			[[nodiscard]]
			std::shared_ptr< Vulkan::GraphicsPipeline > getTBNSpaceDisplayPipeline () noexcept;

			/**
			 * @brief Returns or creates a sampler.
			 * @param type
			 * @param createFlags The create info flags. Default none.
			 * @return std::shared_ptr< Vulkan::Sampler >
			 */
			[[nodiscard]]
			std::shared_ptr< Vulkan::Sampler > getSampler (size_t type, VkSamplerCreateFlags createFlags = 0) noexcept;

			/**
			 * @brief Prepares a renderable instance for a specific rendering.
			 * @note The function return false only if the instance cannot be prepared. 'true' can post pose the preparation.
			 * @param renderableInstance A reference to the renderable instance.
			 * @param renderTarget A reference to a render target smart pointer where the renderable instance must get ready.
			 * @param lightSet A reference to the light set.
			 * @return bool
			 */
			[[nodiscard]]
			bool getRenderableInstanceReadyForRender (RenderableInstance::Abstract & renderableInstance, const std::shared_ptr< RenderTarget::Abstract > & renderTarget, const Scenes::LightSet & lightSet) noexcept;

			/**
			 * @brief Refreshes a renderable instance. This will recreate the graphics pipelines.
			 * @param renderableInstance A reference to the renderable instance.
			 * @param renderTarget A reference to a render target smart pointer where the renderable instance must get ready.
			 * @param lightSet A reference to the light set.
			 * @return bool
			 */
			[[nodiscard]]
			bool refreshRenderableInstance (RenderableInstance::Abstract & renderableInstance, const std::shared_ptr< RenderTarget::Abstract > & renderTarget, const Scenes::LightSet & lightSet) noexcept;

			/**
			 * @brief Render a new frame for the active scene.
			 * @param scene A reference to the scene smart pointer.
			 * @param overlayManager A reference to the overlay manager.
			 * @param devManager A reference to the dev manager.
			 * @param lifetime The current engine lifetime in milliseconds.
			 * @return void
			 */
			void renderFrame (const std::shared_ptr< const Scenes::Scene > & scene, const Overlay::Manager & overlayManager, const Dev::Manager & devManager, unsigned long lifetime) noexcept;

			/**
			 * @brief Returns the instance of the graphics renderer.
			 * @return Renderer *
			 */
			[[nodiscard]]
			static
			Renderer * instance () noexcept;

		private:

			/** @copydoc Emeraude::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc Emeraude::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

			/** @copydoc Libraries::Observer::onNotification() */
			[[nodiscard]]
			bool onNotification (const Libraries::Observable * observable, int notificationCode, const std::any & data) noexcept override;

			/**
			 * @brief Prepares descriptor set layouts for a renderable instance layer.
			 * @param renderTarget A reference to the render target (View UBO).
			 * @param renderableInstance A reference to the renderable instance (Model UBO).
			 * @param material A reference to the material of the renderable instance layer (Material UBO).
			 * @param enableInstance Hint for instancing.
			 * @param descriptorSetLayouts A reference to the vector of generated descriptor set layouts for the renderable instance.
			 * @return bool
			 */
			[[nodiscard]]
			bool prepareDescriptorSetLayouts (const RenderTarget::Abstract & renderTarget, const RenderableInstance::Abstract & renderableInstance, const Material::Interface & material, bool enableInstance, std::vector< std::shared_ptr< Vulkan::DescriptorSetLayout > > & descriptorSetLayouts) noexcept;

			/**
			 * @brief Updates every shadow maps from the scene.
			 * @param A reference to the active scene.
			 */
			void renderShadowMaps (const Scenes::Scene & scene) noexcept;

			/**
			 * @brief Updates every dynamic texture2Ds from the scene.
			 * @param A reference to the active scene.
			 */
			void renderRenderToTextures (const Scenes::Scene & scene) noexcept;

			/**
			 * @brief Updates every off-screen views from the scene.
			 * @param A reference to the active scene.
			 */
			void renderViews (const Scenes::Scene & scene) noexcept;

			/**
			 * @brief Render the final image for the screen.
			 */
			void renderFinal () noexcept;

			/**
			 * @brief Creates command pools and buffers according to the swap chain image count.
			 * @return bool
			 */
			bool createCommandSystem () noexcept;

			/**
			 * @brief Destroys command pools and buffers.
			 * @return void
			 */
			void destroyCommandSystem () noexcept;

			/**
			 * @brief Recreates the swap-chain.
			 * @return bool
			 */
			[[nodiscard]]
			bool recreateSwapChain () noexcept;

			/* Flag names. */
			static constexpr auto Usable = 0UL;
			static constexpr auto DebugMode = 1UL;
			static constexpr auto ShadowMapsEnabled = 2UL;
			static constexpr auto RenderToTexturesEnabled = 3UL;

			static Renderer * s_instance; // NOLINT NOTE: Singleton behavior

			// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members) NOTE: Services inter-connexions.
			const Arguments & m_arguments;
			Settings & m_coreSettings;
			Vulkan::Instance & m_vulkanInstance;
			Window & m_window;
			RenderableInstance::VertexBufferFormatManager & m_vertexBufferFormatManager;
			// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members) NOTE: Services inter-connexions.
			std::shared_ptr< Vulkan::Device > m_device{};
			std::shared_ptr< Vulkan::DescriptorPool > m_descriptorPool{};
			std::map< size_t , std::shared_ptr< Vulkan::DescriptorSetLayout > > m_descriptorSetLayouts{};
			std::vector< std::shared_ptr< Vulkan::CommandPool > > m_commandPools{};
			std::vector< std::shared_ptr< Vulkan::CommandBuffer > > m_commandBuffers{};
			std::shared_ptr< Vulkan::SwapChain > m_swapChain{};
			std::map< size_t, std::shared_ptr< Vulkan::PipelineLayout > > m_pipelineLayouts{};
			std::map< size_t, std::shared_ptr< Vulkan::GraphicsPipeline > > m_pipelines{};
			std::map< size_t, std::shared_ptr< Vulkan::Sampler > > m_samplers{};
			std::shared_ptr< Vulkan::GraphicsPipeline > m_TBNSpaceDisplay{};
			SceneRenderingMode m_sceneRenderingMode = SceneRenderingMode::Basic;
			Libraries::Time::StatisticsTime< std::chrono::high_resolution_clock > m_statistics{30}; // NOLINT(*-magic-numbers)
			std::array< VkClearValue, 2 > m_clearColors{};
			std::array< bool, 8 > m_flags{ // NOLINT(*-magic-numbers)
				false/*Usable*/,
				false/*DebugMode*/,
				true/*ShadowMapsEnabled*/,
				true/*RenderToTexturesEnabled*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
