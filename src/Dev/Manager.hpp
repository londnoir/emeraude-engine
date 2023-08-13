/*
 * Emeraude/Dev/Manager.hpp
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
#include <vector>

/* Local inclusions for inheritances. */
#include "ServiceInterface.hpp"
#include "Observer.hpp"
#include "Time/TimedEventsInterface.hpp"

/* Local inclusions for usages. */
#include "Graphics/RasterizationMode.hpp"
#include "Graphics/Renderable/SimpleMeshResource.hpp"
#include "Graphics/Types.hpp"
#include "Math/Coordinates.hpp"
#include "PixelFactory/Color.hpp"

/* Third-party libraries */
//#include "Third-Party-Inclusion/imgui.hpp"

/* Forward declarations. */
namespace Emeraude
{
	namespace Vulkan
	{
		class CommandBuffer;
	}

	namespace Resources
	{
		class Manager;
	}

	namespace Graphics
	{
		class Renderer;
	}

	namespace Scenes
	{
		class Scene;
		class Node;
	}

	namespace Dev
	{
		class ControlsWidgetInterface;
	}

	class FileSystem;
	class Settings;
	class Window;
}

namespace Emeraude::Dev
{
	/**
	 * @brief This class is used to bring a debug layer in the engine.
	 * @extends Emeraude::ServiceInterface This is a service.
	 * @extends Libraries::Time::TimedEventsInterface
	 * @extends Libraries::Observer
	 */
	class Manager final : public ServiceInterface, public Libraries::Time::TimedEventsInterface, public Libraries::Observer
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"DevManager"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/* Settings keys */
			static constexpr auto ImGUIStyleKey = "Dev/ImGUIStyle";
			static constexpr auto DefaultImGUIStyle = "Dev/Classic";

			/**
			 * @brief Constructs the dev manager.
			 * @param fileSystem A reference to the file system.
			 * @param coreSettings A reference to the core settings.
			 * @param resourceManager A reference to the resource manager.
			 * @param window A reference to the window.
			 * @param renderer A reference to the graphics renderer.
			 */
			Manager (const FileSystem & fileSystem, Settings & coreSettings, Resources::Manager & resourceManager, const Window & window, const Graphics::Renderer & renderer) noexcept;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::ServiceInterface::usable() */
			[[nodiscard]]
			bool usable () const noexcept override;

			/**
			 * @brief Sends everything needed for a render to video memory.
			 * @return bool
			 */
			bool updateVideoMemory () noexcept;

			/**
			 * @brief Adds a controls widget to render.
			 * @param controlsWidget A pointer to a controls widget.
			 * @return void
			 */
			void addControlsWidget (const ControlsWidgetInterface * controlsWidget) noexcept;

			/**
			 * @brief Removes a controls widget to render.
			 * @param controlsWidget A pointer to a controls widget.
			 * @return void
			 */
			void removeControlsWidget (const ControlsWidgetInterface * controlsWidget) noexcept;

			/**
			 * @brief Removes all controls widget.
			 * @return void
			 */
			void clearControlsWidget () noexcept;

			/**
			 * @brief This will render the ImGUI controllers on top of the current frame and built-in OSD widgets.
			 * @param commandBuffer A reference to a command buffer smart pointer.
			 * @return void
			 */
			void render (const std::shared_ptr< Vulkan::CommandBuffer > & commandBuffer) const noexcept;

			/**
			 * @brief enableAutoClear
			 * @param state
			 * @return void
			 */
			void enableAutoClear (bool state) noexcept;

			/**
			 * @brief enableScene
			 * @param scene
			 * @return void
			 */
			void enableScene (Scenes::Scene & scene) noexcept;

			/**
			 * @brief Adds a gizmo to a scene by creating a temporary scene node.
			 * @param scene A reference to the scene.
			 * @param atLocation A coordinates where in the scene the gizmo should appears.
			 * @param gizmo A smart pointer to the gizmo.
			 * @return void
			 */
			void createGizmoNode (const Scenes::Scene & scene, const Libraries::Math::Coordinates< float > & atLocation, const std::shared_ptr< Graphics::Renderable::SimpleMeshResource > & gizmo) noexcept;

			/**
			 * @brief Adds a parametric gizmo to a scene by creating a temporary scene node.
			 * @param scene A reference to the scene.
			 * @param atLocation A coordinates where in the scene the gizmo should appears.
			 * @param shape The gizmo shape.
			 * @param size The size of the shape.
			 * @return void
			 */
			void createGizmo (const Scenes::Scene & scene, const Libraries::Math::Coordinates< float > & atLocation, Graphics::ShapeType shape, float size = 1.0F) noexcept;

			/**
			 * @brief Adds a parametric gizmo to a scene by creating a temporary scene node.
			 * @param scene A reference to the scene.
			 * @param atLocation A coordinates where in the scene the gizmo should appears.
			 * @param shape The gizmo shape.
			 * @param size The size of the shape.
			 * @param color A specific color for the gizmo.
			 * @return void
			 */
			void createGizmo (const Scenes::Scene & scene, const Libraries::Math::Coordinates< float > & atLocation, Graphics::ShapeType shape, float size, const Libraries::PixelFactory::Color< float > & color) noexcept;

			/**
			 * @brief Gets a parametric cube gizmo.
			 * @param size The size of the cube.
			 * @param color The color of the cube.
			 * @return std::shared_ptr< Graphics::Renderable::SimpleMeshResource >
			 */
			[[nodiscard]]
			std::shared_ptr< Graphics::Renderable::SimpleMeshResource > getCubeGizmo (float size = 1.0F, const Libraries::PixelFactory::Color< float > & color = Libraries::PixelFactory::Red) noexcept;

			/**
			 * @brief Gets a parametric cuboid gizmo.
			 * @param width The width of the cuboid.
			 * @param height The height of the cuboid.
			 * @param depth The depth of the cuboid.
			 * @param color The color of the cube.
			 * @return std::shared_ptr< Graphics::Renderable::SimpleMeshResource >
			 */
			[[nodiscard]]
			std::shared_ptr< Graphics::Renderable::SimpleMeshResource > getCuboidGizmo (float width, float height, float depth, const Libraries::PixelFactory::Color< float > & color = Libraries::PixelFactory::Red) noexcept;

			/**
			 * @brief Gets a parametric cuboid gizmo.
			 * @param size Dimensions in X,Y and Z of the cuboid.
			 * @param color The color of the cube.
			 * @return std::shared_ptr< Graphics::Renderable::SimpleMeshResource >
			 */
			[[nodiscard]]
			inline
			std::shared_ptr< Graphics::Renderable::SimpleMeshResource >
			getCuboidGizmo (const Libraries::Math::Vector< 3, float > & size, const Libraries::PixelFactory::Color< float > & color = Libraries::PixelFactory::Red)
			{
				return this->getCuboidGizmo(size[Libraries::Math::X], size[Libraries::Math::Y], size[Libraries::Math::Z], color);
			}

			/**
			 * @brief Gets a parametric area gizmo.
			 * @param size The size of the area.
			 * @param color The color of the area.
			 * @return std::shared_ptr< Graphics::Renderable::SimpleMeshResource >
			 */
			[[nodiscard]]
			std::shared_ptr< Graphics::Renderable::SimpleMeshResource > getUniformAreaGizmo (float size = 1.0F, const Libraries::PixelFactory::Color< float > & color = Libraries::PixelFactory::Green) noexcept;

			/**
			 * @brief Gets a parametric sphere gizmo.
			 * @param size The size of the sphere.
			 * @param color The color of the sphere.
			 * @return std::shared_ptr< Graphics::Renderable::SimpleMeshResource >
			 */
			[[nodiscard]]
			std::shared_ptr< Graphics::Renderable::SimpleMeshResource > getSphereGizmo (float size = 1.0F, const Libraries::PixelFactory::Color< float > & color = Libraries::PixelFactory::Blue) noexcept;

			/**
			 * @brief Gets a parametric arrow gizmo.
			 * @param size The size of the arrow.
			 * @param color The color of the arrow.
			 * @return std::shared_ptr< Graphics::Renderable::SimpleMeshResource >
			 */
			[[nodiscard]]
			std::shared_ptr< Graphics::Renderable::SimpleMeshResource > getArrowGizmo (float size = 1.0F, const Libraries::PixelFactory::Color< float > & color = Libraries::PixelFactory::Magenta, Graphics::PointTo pointTo = Graphics::PointTo::PositiveZ) noexcept;

			/**
			 * @brief Gets a parametric axis gizmo.
			 * @note RGB color will be use for XYZ axis.
			 * @param size The size of the axis.
			 * @return std::shared_ptr< Graphics::Renderable::SimpleMeshResource >
			 */
			[[nodiscard]]
			std::shared_ptr< Graphics::Renderable::SimpleMeshResource > getAxisGizmo (float size = 1.0F) noexcept;

			/**
			 * @brief Gets a custom gizmo.
			 * @param name The name of the gizmo
			 * @param geometry A pointer to an helper geometry resource.
			 * @param material A pointer to an helper material resource. Optional.
			 * @return std::shared_ptr< Graphics::Renderable::SimpleMeshResource >
			 */
			[[nodiscard]]
			std::shared_ptr< Graphics::Renderable::SimpleMeshResource > getCustomGizmo (const std::string & name, const std::shared_ptr< Graphics::Geometry::Interface > & geometry, std::shared_ptr< Graphics::Material::Interface > material = nullptr) noexcept;

			/**
			 * @brief clearGizmos
			 * @param scene
			 * @return void
			 */
			void clearGizmos (const Scenes::Scene & scene) noexcept;

			/**
			 * @brief clearAllGizmos
			 * @return void
			 */
			void clearAllGizmos () noexcept;

		private:

			/* Flag names. */
			static constexpr auto Usable = 0UL;
			static constexpr auto AutomaticClearEnabled = 1UL;

			/** @copydoc Emeraude::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc Emeraude::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

			/** @copydoc Libraries::Observer::onNotification() */
			[[nodiscard]]
			bool onNotification (const Libraries::Observable * observable, int notificationCode, const std::any & data) noexcept override;

			/**
			 * @brief getRegisteredScene
			 * @param searchedScene
			 * @return Scenes::Scene *
			 */
			Scenes::Scene * getRegisteredScene (const Scenes::Scene & searchedScene) noexcept;

			/**
			 * @brief clearTask
			 * @param milliseconds
			 * @return void
			 */
			void clearTask (double milliseconds) noexcept;

			/**
			 * @brief updateOrthographicProjection
			 * @param width
			 * @param height
			 * @return void
			 */
			void updateOrthographicProjection (float width, float height) noexcept;

#ifdef IMGUI_ENABLED
			/**
			 * @brief Initializes the ImGui library.
			 * @return bool
			 */
			bool initializeImGui () noexcept;

			/**
			 * @brief Initializes the ImGui library descriptor pool.
			 * @param device A reference to a device smart pointer.
			 * @return bool
			 */
			bool createImGuiDescriptorPool (const std::shared_ptr< Vulkan::Device > & device) noexcept;

			/**
			 * @brief Initializes the ImGui library render pass.
			 * @param device A reference to a device smart pointer.
			 * @return bool
			 */
			bool createImGuiRenderPass (const std::shared_ptr< Vulkan::Device > & device) noexcept;

			/**
			 * @brief Initializes the ImGui library fonts.
			 * @param device A reference to a device smart pointer.
			 * @return bool
			 */
			bool createImGuiFonts (const std::shared_ptr< Vulkan::Device > & device) noexcept;

			void updateImGui () const noexcept;

			/**
			 * @brief Render the ImGui library.
			 * @param commandBuffer A reference to a command buffer smart pointer.
			 * @return void
			 */
			void renderImGui (const std::shared_ptr< Vulkan::CommandBuffer > & commandBuffer) const noexcept;

			/**
			 * @brief Destroys ImGui the ImGui library.
			 * @return void
			 */
			void destroyImGui () noexcept;
#endif

			// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members) NOTE: Services inter-connexions.
			const FileSystem & m_fileSystem;
			Settings & m_coreSettings;
			Resources::Manager & m_resourceManager;
			const Window & m_window;
			const Graphics::Renderer & m_renderer;
			// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
			std::set< const ControlsWidgetInterface * > m_controlsWidgets{};
			std::set< std::shared_ptr< Graphics::Renderable::SimpleMeshResource > > m_activeGizmos{};
			std::map< Scenes::Scene *, std::vector< std::shared_ptr< Scenes::Node > > > m_enabledScenes{};
			size_t m_generatedNode{0};
			Libraries::Math::Matrix< 4, float > m_projection{};
			Libraries::Time::TimerID m_autoClearTimerID{0};
			Graphics::RasterizationMode m_rasterizationMode{};
#ifdef IMGUI_ENABLED
			ImGuiContext * m_ImGuiContext = nullptr;
			std::string m_ImGUIConfigFile{};
			std::shared_ptr< Vulkan::DescriptorPool > m_ImGuiDescriptorPool{};
			VkRenderPass m_renderPass = VK_NULL_HANDLE;
#endif
			std::array< bool, 8 > m_flags{ // NOLINT(*-magic-numbers)
				false/*Usable*/,
				false/*AutomaticClearEnabled*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
