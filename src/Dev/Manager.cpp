/*
 * Emeraude/Dev/Manager.cpp
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

#include "Manager.hpp"

/* Local inclusions */
#include "Argument.hpp"
#include "ControlsWidgetInterface.hpp"
#include "Graphics/Geometry/ResourceGenerator.hpp"
#include "Graphics/Renderer.hpp"
#include "Resources/Manager.hpp"
#include "Saphir/ShaderGenerator.hpp"
#include "Scenes/Scene.hpp"
#include "Settings.hpp"
#include "Tracer.hpp"
#include "Window.hpp"

namespace Emeraude::Dev
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Libraries::PixelFactory;
	using namespace Graphics;
	using namespace Saphir;
	using namespace Saphir::Keys;
	using namespace Vulkan;

	const size_t Manager::ClassUID{Observable::getClassUID()};

	Manager::Manager (const FileSystem & fileSystem, Settings & coreSettings, Resources::Manager & resourceManager, const Window & window, const Renderer & renderer) noexcept
		: ServiceInterface("Dev manager"), m_fileSystem(fileSystem), m_coreSettings(coreSettings), m_resourceManager(resourceManager), m_window(window), m_renderer(renderer)
	{

	}

	bool
	Manager::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	Manager::onInitialize () noexcept
	{
		/* Prepare the rasterization mode for the surface */
		m_rasterizationMode.setDepthBufferStates(false, false);

		const auto framebufferSize = m_window.getFramebufferSize();

		this->updateOrthographicProjection(
		static_cast< float >(framebufferSize[0]),
		static_cast< float >(framebufferSize[1])
		);

#ifdef IMGUI_ENABLED
		if ( !this->initializeImGui() )
		{
			Tracer::error(ClassId, "Unable to load up the ImGUI library !");

			return false;
		}
#endif

		m_flags[Usable] = true;

		return true;
	}

	bool
	Manager::onTerminate () noexcept
	{
		this->clearAllGizmos();

		m_activeGizmos.clear();

#ifdef IMGUI_ENABLED
		this->destroyImGui();
#endif

		return true;
	}

	bool
	Manager::onNotification (const Observable * observable, int notificationCode, const std::any & /*data*/) noexcept
	{
		if ( observable->is(Window::ClassUID) )
		{
			//const auto windowSize = std::any_cast< std::array< size_t, 2 > >(data);
			//this->updateOrthographicProjection(static_cast< float >(windowSize[X]), static_cast< float >(windowSize[Y]));

			switch ( notificationCode )
			{
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
				case Window::OSNotifiesFramebufferResized :
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
	Manager::usable () const noexcept
	{
		if ( !m_renderer.usable() )
		{
			return false;
		}

		return m_flags[Usable];
	}

	bool
	Manager::updateVideoMemory () noexcept
	{


		return false;
	}

	void
	Manager::addControlsWidget (const ControlsWidgetInterface * controlsWidget) noexcept
	{
		m_controlsWidgets.emplace(controlsWidget);
	}

	void
	Manager::removeControlsWidget (const ControlsWidgetInterface * controlsWidget) noexcept
	{
		m_controlsWidgets.erase(controlsWidget);
	}

	void
	Manager::clearControlsWidget () noexcept
	{
		m_controlsWidgets.clear();
	}

	void
	Manager::render (const std::shared_ptr< CommandBuffer > & /*commandBuffer*/) const noexcept
	{
		if ( !this->usable() )
		{
			return;
		}

#ifdef IMGUI_ENABLED
		this->renderImGui(commandBuffer);
#endif
	}

	void
	Manager::enableAutoClear (bool state) noexcept
	{
		m_flags[AutomaticClearEnabled] = state;
	}

	void
	Manager::enableScene (Scenes::Scene & scene) noexcept
	{
		auto sceneIt = m_enabledScenes.find(&scene);

		if ( sceneIt == m_enabledScenes.end() )
		{
			m_enabledScenes.emplace(&scene, std::vector<std::shared_ptr<Scenes::Node> >());
		}
	}

	void
	Manager::createGizmoNode (const Scenes::Scene & scene, const Coordinates< float > & atLocation, const std::shared_ptr< Renderable::SimpleMeshResource > & gizmo) noexcept
	{
		/* Gets the registered scene. */
		auto * registeredScene = this->getRegisteredScene(scene);

		if ( registeredScene == nullptr )
		{
			Tracer::error(ClassId, "The scene is not registered for debugging ! Use Dev::Manager::enableScene().");

			return;
		}

		/* Creates the node into the scene. */
		auto node = registeredScene->root()->createSubNode(String::incrementalLabel("GizmoNode", m_generatedNode), atLocation);
		/* FIXME : Rework the gizmo layer */
		//node->addGizmoInstance(gizmo->name().c_str(), gizmo);

		/* Save the node here to track it. */
		m_enabledScenes[registeredScene].emplace_back(node);

		/* Start a timer or re-up it to clean the gizmo after a while. */
		if ( m_flags[AutomaticClearEnabled] )
		{
			if ( m_autoClearTimerID > 0UL )
			{
				this->setTimerGranularity(m_autoClearTimerID, 5000.0);
			}
			else
			{
				m_autoClearTimerID = this->createTimer(std::bind(&Manager::clearTask, this, std::placeholders::_1), 5000.0, true, true);
			}
		}
	}

	void
	Manager::createGizmo (const Scenes::Scene & scene, const Libraries::Math::Coordinates< float > & atLocation, ShapeType shape, float size) noexcept
	{
		switch ( shape )
		{
			case ShapeType::Cube :
				this->createGizmoNode(scene, atLocation, this->getCubeGizmo(size));
				break;

			case ShapeType::Sphere :
				this->createGizmoNode(scene, atLocation, this->getSphereGizmo(size));
				break;

			case ShapeType::Arrow :
				this->createGizmoNode(scene, atLocation, this->getArrowGizmo(size));
				break;

			case ShapeType::Axis :
				this->createGizmoNode(scene, atLocation, this->getAxisGizmo(size));
				break;

			default :
				Tracer::warning(ClassId, "This shape type is not allowed here !");
				break;
		}
	}

	void
	Manager::createGizmo (const Scenes::Scene & scene, const Libraries::Math::Coordinates< float > & atLocation, ShapeType shape, float size, const Libraries::PixelFactory::Color< float > & color) noexcept
	{
		switch ( shape )
		{
			case ShapeType::Cube :
				this->createGizmoNode(scene, atLocation, this->getCubeGizmo(size, color));
				break;

			case ShapeType::Sphere :
				this->createGizmoNode(scene, atLocation, this->getSphereGizmo(size, color));
				break;

			case ShapeType::Arrow :
				this->createGizmoNode(scene, atLocation, this->getArrowGizmo(size, color));
				break;

			case ShapeType::Axis :
				this->createGizmoNode(scene, atLocation, this->getAxisGizmo(size));
				break;

			default :
				Tracer::warning(ClassId, "This shape type is not allowed here !");
				break;
		}
	}

	void
	Manager::clearGizmos (const Scenes::Scene & scene) noexcept
	{
		for ( auto & sceneIt : m_enabledScenes )
		{
			if ( sceneIt.first->name() == scene.name() )
			{
				/* Ask for scene to delete the gizmo node. */
				for ( const auto & gizmoNode : sceneIt.second )
				{
					sceneIt.first->root()->destroySubNode(gizmoNode->name());
				}

				/* Clear the gizmo nodes vector. */
				sceneIt.first->clear();

				return;
			}
		}
	}

	void
	Manager::clearAllGizmos () noexcept
	{
		for ( auto & sceneIt : m_enabledScenes )
		{
			/* Ask for scene to delete the gizmo node. */
			for ( const auto & gizmoNode : sceneIt.second )
			{
				sceneIt.first->root()->destroySubNode(gizmoNode->name());
			}

			/* Clear the gizmo nodes vector. */
			sceneIt.second.clear();
		}
	}

	std::shared_ptr< Renderable::SimpleMeshResource >
	Manager::getCubeGizmo (float size, const Color< float > & color) noexcept
	{
		const auto resourceName = (std::stringstream{} << "CubeGizmo(" << size << ',' << color << ')').str();

		auto gizmo = m_resourceManager.simpleMeshes().getOrCreateResource(resourceName);

		if ( gizmo->isUnloaded() )
		{
			Geometry::ResourceGenerator generator{Geometry::EnableTangentSpace | Geometry::EnableVertexColor};
			generator.parameters().setGlobalVertexColor(color);

			if ( !gizmo->load(generator.cube(size), Material::BasicResource::getDefault()) )
			{
				return nullptr;
			}
		}

		m_activeGizmos.emplace(gizmo);

		return gizmo;
	}

	std::shared_ptr< Renderable::SimpleMeshResource >
	Manager::getCuboidGizmo (float width, float height, float depth, const Color< float > & color) noexcept
	{
		const auto resourceName = (std::stringstream{} << "CuboidGizmo(" << width << ',' << height << ',' << depth << ',' << color << ')').str();

		auto gizmo = m_resourceManager.simpleMeshes().getOrCreateResource(resourceName);

		if ( gizmo->isUnloaded() )
		{
			Geometry::ResourceGenerator generator{Geometry::EnableTangentSpace | Geometry::EnableVertexColor};
			generator.parameters().setGlobalVertexColor(color);

			if ( !gizmo->load(generator.cuboid(width, height, depth), Material::BasicResource::getDefault()) )
			{
				return nullptr;
			}
		}

		m_activeGizmos.emplace(gizmo);

		return gizmo;
	}

	std::shared_ptr< Renderable::SimpleMeshResource >
	Manager::getUniformAreaGizmo (float size, const Color< float > & color) noexcept
	{
		const auto resourceName = (std::stringstream{} << "UniformAreaGizmo(" << size << ',' << color << ')').str();

		auto gizmo = m_resourceManager.simpleMeshes().getOrCreateResource(resourceName);

		if ( gizmo->isUnloaded() )
		{
			Geometry::ResourceGenerator generator{Geometry::EnableTangentSpace | Geometry::EnableVertexColor};
			generator.parameters().setGlobalVertexColor(color);

			if ( !gizmo->load(generator.uniformArea(size), Material::BasicResource::getDefault()) )
			{
				return nullptr;
			}
		}

		m_activeGizmos.emplace(gizmo);

		return gizmo;
	}

	std::shared_ptr< Renderable::SimpleMeshResource >
	Manager::getSphereGizmo (float size, const Color< float > & color) noexcept
	{
		const auto resourceName = (std::stringstream{} << "SphereGizmo(" << size << ',' << color << ')').str();

		auto gizmo = m_resourceManager.simpleMeshes().getOrCreateResource(resourceName);

		if ( gizmo->isUnloaded() )
		{
			Geometry::ResourceGenerator generator{Geometry::EnableTangentSpace | Geometry::EnableVertexColor};
			generator.parameters().setGlobalVertexColor(color);

			if ( !gizmo->load(generator.sphere(size, 8UL, 8UL), Material::BasicResource::getDefault()) )
			{
				return nullptr;
			}
		}

		m_activeGizmos.emplace(gizmo);

		return gizmo;
	}

	std::shared_ptr< Renderable::SimpleMeshResource >
	Manager::getArrowGizmo (float size, const Color< float > & color, PointTo pointTo) noexcept
	{
		const auto resourceName = (std::stringstream{} << "ArrowGizmo(" << size << ',' << color << ')').str();

		auto gizmo = m_resourceManager.simpleMeshes().getOrCreateResource(resourceName);

		if ( gizmo->isUnloaded() )
		{
			Geometry::ResourceGenerator generator{Geometry::EnableTangentSpace | Geometry::EnableVertexColor};
			generator.parameters().setGlobalVertexColor(color);

			if ( !gizmo->load(generator.arrow(size, pointTo), Material::BasicResource::getDefault()) )
			{
				return nullptr;
			}
		}

		m_activeGizmos.emplace(gizmo);

		return gizmo;
	}

	std::shared_ptr< Renderable::SimpleMeshResource >
	Manager::getAxisGizmo (float size) noexcept
	{
		const auto resourceName = (std::stringstream{} << "AxisGizmo(" << size << ')').str();

		auto gizmo = m_resourceManager.simpleMeshes().getOrCreateResource(resourceName);

		if ( gizmo->isUnloaded() )
		{
			Geometry::ResourceGenerator generator{Geometry::EnableTangentSpace | Geometry::EnableVertexColor};

			if ( !gizmo->load(generator.axis(size), Material::BasicResource::getDefault()) )
			{
				return nullptr;
			}
		}

		m_activeGizmos.emplace(gizmo);

		return gizmo;
	}

	std::shared_ptr< Renderable::SimpleMeshResource >
	Manager::getCustomGizmo (const std::string & name, const std::shared_ptr< Geometry::Interface > & geometry, std::shared_ptr< Material::Interface > material) noexcept
	{
		auto & manager = m_resourceManager.simpleMeshes();

		/* Checks for existing mesh. */
		if ( manager.isResourceAvailable(name) )
		{
			return manager.getResource(name);
		}

		/* Checks the shape. */
		if ( geometry == nullptr )
		{
			Tracer::error(ClassId, "Geometry is a null pointer !");

			return nullptr;
		}

		if ( material == nullptr )
		{
			material = Material::BasicResource::getDefault();
		}

		/* Assembling the gizmo. */
		auto gizmo = manager.createResource(name);

		if ( !gizmo->load(geometry, material) )
		{
			Tracer::error(ClassId, "Unable to generate the gizmo !");

			return nullptr;
		}

		m_activeGizmos.emplace(gizmo);

		return gizmo;
	}

	Scenes::Scene *
	Manager::getRegisteredScene (const Scenes::Scene & searchedScene) noexcept
	{
		for ( auto & sceneIt : m_enabledScenes )
		{
			if (sceneIt.first->name() == searchedScene.name())
			{
				return sceneIt.first;
			}
		}

		return nullptr;
	}

	void
	Manager::clearTask (double /* time */) noexcept
	{
		this->clearAllGizmos();

		m_autoClearTimerID = 0;
	}

	void
	Manager::updateOrthographicProjection (float width, float height) noexcept
	{
		const auto aspectRatio = width / height;

		m_projection = Matrix< 4, float >::orthographicProjection(-aspectRatio, aspectRatio, -1.0F, 1.0F, -1.0F, 1.0F);
	}

#ifdef IMGUI_ENABLED
	bool
	Manager::initializeImGui () noexcept
	{
		if ( !IMGUI_CHECKVERSION() )
		{
			Tracer::error(ClassId, "Unable to use ImGUI !");

			return false;
		}

		m_ImGuiContext = ImGui::CreateContext();

		if ( m_ImGuiContext == nullptr )
		{
			Tracer::error(ClassId, "Unable to create ImGUI context !");

			return false;
		}

		ImGuiIO & io = ImGui::GetIO(); (void) io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;	 // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;	  // Enable Gamepad Controls

		/* Sets ImGUI ini file path. */
		//m_ImGUIConfigFile = to_string(Path::File(m_fileSystem.configDirectory(), "imgui.ini"));
		//ImGui::GetIO().IniFilename = m_ImGUIConfigFile.c_str();

		/* Setup Dear ImGui style. */
		auto style = m_coreSettings.get(ImGUIStyleKey, DefaultImGUIStyle);

		if ( style.compare("Dark") == 0 )
			ImGui::StyleColorsDark();
		else if ( style.compare("Light") == 0 )
			ImGui::StyleColorsLight();
		else
			ImGui::StyleColorsClassic();

		/* NOTE : Initialize ImGui with GLFW. */
		if ( !ImGui_ImplGlfw_InitForVulkan(Core::instance()->window().window(), true) )
		{
			Tracer::error(ClassId, "Unable to init ImGUI with GLFW !");

			return false;
		}

		/* NOTE : Initialize ImGui with Vulkan. */
		{
			auto & device = m_renderer.device();

			if ( !this->createImGuiDescriptorPool(device) )
			{
				Tracer::error(ClassId, "Unable to create Dear ImGui descriptor pool !");

				return false;
			}

			if ( !this->createImGuiRenderPass(device) )
			{
				Tracer::error(ClassId, "Unable to create Dear ImGui render pass !");

				return false;
			}

			auto queue = device->getGraphicsQueue();
			auto imageCount = m_renderer.swapChain()->imageCount();

			ImGui_ImplVulkan_InitInfo initInfo = {};
			initInfo.Instance = m_renderer.vulkanInstance().handle();
			initInfo.PhysicalDevice = device->physicalDevice()->handle();
			initInfo.Device = device->handle();
			initInfo.QueueFamily = queue->familyQueueIndex();
			initInfo.Queue = queue->handle();
			initInfo.PipelineCache = VK_NULL_HANDLE;
			initInfo.DescriptorPool = m_ImGuiDescriptorPool->handle();
			initInfo.Subpass = 0;
			initInfo.MinImageCount = imageCount; // >= 2
			initInfo.ImageCount = imageCount; // >= MinImageCount
			initInfo.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
			initInfo.Allocator = nullptr;
			initInfo.CheckVkResultFn = nullptr;

			if ( !ImGui_ImplVulkan_Init(&initInfo, m_renderPass) )
			{
				Tracer::error(ClassId, "Unable to init Dear ImGUI with Vulkan !");

				return false;
			}

			/* Uploading fonts to the GPU */
			if ( !this->createImGuiFonts(device) )
			{
				Tracer::error(ClassId, "Unable to create Dear ImGui fonts !");

				return false;
			}
		}

		return true;
	}

	bool
	Manager::createImGuiDescriptorPool (const std::shared_ptr< Device > & device) noexcept
	{
		m_ImGuiDescriptorPool = std::make_shared< DescriptorPool >(device, std::vector< VkDescriptorPoolSize >{
			{VK_DESCRIPTOR_TYPE_SAMPLER, 1000},
			{VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000},
			{VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000},
			{VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000},
			{VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000},
			{VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000},
			{VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000},
			{VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000},
			{VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000},
			{VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000},
			{VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000}
		}, 1000, VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT);
		m_ImGuiDescriptorPool->setIdentifier("DevManager-Main-DescriptorPool");

		return m_ImGuiDescriptorPool->create();
	}

	bool
	Manager::createImGuiRenderPass (const std::shared_ptr< Device > & device) noexcept
	{
		VkAttachmentDescription attachment = {};
		attachment.format = m_renderer.swapChain()->createInfo().imageFormat;
		attachment.samples = VK_SAMPLE_COUNT_1_BIT;
		attachment.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
		attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		attachment.initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		VkAttachmentReference color_attachment = {};
		color_attachment.attachment = 0;
		color_attachment.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subpass = {};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &color_attachment;

		VkSubpassDependency dependency = {};
		dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		dependency.dstSubpass = 0;
		dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.srcAccessMask = 0;  // or VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

		VkRenderPassCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		createInfo.attachmentCount = 1;
		createInfo.pAttachments = &attachment;
		createInfo.subpassCount = 1;
		createInfo.pSubpasses = &subpass;
		createInfo.dependencyCount = 1;
		createInfo.pDependencies = &dependency;

		const auto result = vkCreateRenderPass(device->handle(), &createInfo, nullptr, &m_renderPass);

		if ( result != VK_SUCCESS )
		{
			Tracer::error(ClassId, Blob() << "Unable to create Dear ImGui's render pass : " << vkResultToCString(result) << " !");

			return false;
		}

		return true;
	}

	bool
	Manager::createImGuiFonts (const std::shared_ptr< Device > & device) noexcept
	{
		auto commandPool = device->transferCommandPool();

		auto commandBuffer = std::make_shared< CommandBuffer >(commandPool, true);

		if ( !commandBuffer->isCreated() )
		{
			Tracer::error(classId, "Unable to create a transfer command buffer !");

			return false;
		}

		if ( !commandBuffer->begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT) )
			return false;

		ImGui_ImplVulkan_CreateFontsTexture(commandBuffer->handle());

		if ( !commandBuffer->end() )
			return false;

		if ( !commandBuffer->submitTransfer() )
			return false;

		return true;
	}

	void
	Manager::updateImGui () const noexcept
	{
		/*auto & device = m_renderer.device();
		auto imageCount = m_renderer.swapChain()->imageCount();

		ImGui_ImplVulkan_SetMinImageCount(imageCount);
		ImGui_ImplVulkanH_CreateWindow(
			*m_renderer.vulkanInstance().handle(),
			device->physicalDevice()->handle(),
			device->handle(),
			nullptr, //&g_MainWindowData,
			device->getGraphicsQueue()->familyQueueIndex(),
			nullptr, // g_Allocator
			800,
			600,
			imageCount
		);*/
	}

	void
	Manager::renderImGui (const std::shared_ptr< CommandBuffer > & commandBuffer) const noexcept
	{
		ImGui_ImplVulkan_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		/*if ( !io.WantCaptureMouse )
		{
			// your input functions here
		}*/

		/* Rendering */
		{
			ImGui::Begin("DemoWindow");
			ImGui::ShowDemoWindow();
			ImGui::End();

			for ( auto controller : m_controlsWidgets )
				controller->renderWidget();
		}

		ImGui::Render();
		ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), commandBuffer->handle());
	}

	void
	Manager::destroyImGui () noexcept
	{
		if ( m_ImGuiDescriptorPool != nullptr )
		{
			auto device = m_ImGuiDescriptorPool->device();

			if ( m_renderPass != VK_NULL_HANDLE )
			{
				device->waitIdle();

				vkDestroyRenderPass(device->handle(), m_renderPass, nullptr);

				m_renderPass = VK_NULL_HANDLE;
			}

			if ( m_ImGuiDescriptorPool != nullptr )
			{
				m_ImGuiDescriptorPool->destroyFromHardware();
				m_ImGuiDescriptorPool.reset();
			}
		}

		ImGui_ImplVulkan_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
#endif
}
