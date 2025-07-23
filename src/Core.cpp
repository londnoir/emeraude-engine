/*
 * src/Core.cpp
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

#include "Core.hpp"

/* STL inclusions. */
#include <sstream>
#include <iostream>
#include <ranges>
#include <thread>

/* Third-party inclusions. */
#include "GLFW/glfw3.h"

/* Local inclusions. */
#include "Constants.hpp"
#include "Input/Types.hpp"
#include "Libs/Time/Elapsed/PrintScopeRealTime.hpp"
#include "Libs/Time/Time.hpp"
#include "Libs/Version.hpp"
#include "PlatformSpecific/Desktop/Dialog/Message.hpp"
#include "PlatformSpecific/Desktop/Dialog/OpenFile.hpp"
#include "PlatformSpecific/Desktop/Commands.hpp"
#include "Tool/GeometryDataPrinter.hpp"
#include "Tool/ShowVulkanInformation.hpp"

namespace EmEn
{
	using namespace EmEn::Libs;
	using namespace Vulkan;
	using namespace Graphics;
	using namespace Scenes;
	using namespace Input;
	using namespace Resources;

	Core * Core::s_instance{nullptr};

	Core::Core (int argc, char * * argv, const char * applicationName, const Version & applicationVersion, const char * applicationOrganization, const char * applicationDomain) noexcept
		: KeyboardListenerInterface(false, false),
		Controllable(ClassId),
		m_identification(applicationName, applicationVersion, applicationOrganization, applicationDomain),
		m_primaryServices(argc, argv, m_identification)
	{
		if ( s_instance != nullptr )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", constructor called twice !" "\n";

#if IS_MACOS // clang 15 failure (try to use __apple_build_version__)
			std::terminate();
#else
			std::quick_exit(1);
#endif
		}

		s_instance = this;

		if ( !this->initializeBaseLevel() )
		{
#if IS_MACOS // clang 15 failure (try to use __apple_build_version__)
			std::terminate();
#else
			std::quick_exit(2);
#endif
		}
	}

#if IS_WINDOWS
	Core::Core (int argc, wchar_t * * wargv, const char * applicationName, const Version & applicationVersion, const char * applicationOrganization, const char * applicationDomain) noexcept
		: KeyboardListenerInterface(false, false),
		Controllable(ClassId),
		m_identification(applicationName, applicationVersion, applicationOrganization, applicationDomain),
		m_primaryServices(argc, wargv, m_identification)
	{
		if ( s_instance != nullptr )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", constructor called twice !" "\n";

			std::quick_exit(1);
		}

		s_instance = this;

		if ( !this->initializeBaseLevel() )
		{
			std::quick_exit(2);
		}
	}
#endif

	Core::~Core ()
	{
		/* Terminate primary services. */
		for ( auto * service : std::ranges::reverse_view(m_primaryServicesEnabled) )
		{
			if ( service->terminate() )
			{
				TraceSuccess{ClassId} << service->name() << " primary service terminated gracefully !";
			}
			else
			{
				TraceError{ClassId} << service->name() << " primary service failed to terminate properly !";
			}
		}

		m_resourceManager.unloadUnusedResources();

		m_primaryServices.terminate();

		m_primaryServicesEnabled.clear();

		Tracer::success(ClassId, "*** Core level terminated ***");

		s_instance = nullptr;
	}

	void
	Core::logicsTask () noexcept
	{
		const std::chrono::duration< uint64_t, std::micro > logicsUpdateFrequency{EngineUpdateCycleDurationUS< uint64_t >};

		while ( m_flags[IsLogicsLoopRunning] )
		{
			if ( m_flags[Paused] )
			{
				std::this_thread::sleep_for(std::chrono::milliseconds{100});

				continue;
			}

			const auto top = std::chrono::steady_clock::now();

			{
				/* NOTE: Prevent an active scene deletion/switch during the logic update task without blocking the rendering task. */
				const std::shared_lock< std::shared_mutex > activeSceneLock{m_sceneManager.activeSceneAccess()};

				const Time::Elapsed::PrintScopeRealTimeThreshold stat{"logicsTask", 1000.0 / 60.0};

				m_lifetime += EngineUpdateCycleDurationUS< uint64_t >;

				/* Call the application method to update its logics first. */
				this->onProcessLogics(m_cycle);

				const auto activeScene = m_sceneManager.activeScene();

				if ( activeScene != nullptr )
				{
					activeScene->processLogics(m_cycle);
				}

				m_cycle++;
			}

			const auto duration = std::chrono::steady_clock::now() - top;

			/* NOTE: Let sleep the thread until the next update. */
			if ( duration < logicsUpdateFrequency )
			{
				std::this_thread::sleep_for(logicsUpdateFrequency - duration);
			}
		}

		TraceSuccess{ClassId} << "Logics loop ended !";
	}

	void
	Core::renderingTask () noexcept
	{
		uint64_t frames = 0;

		while ( m_flags[IsRenderingLoopRunning] )
		{
			if ( m_flags[Paused] )
			{
				std::this_thread::sleep_for(std::chrono::milliseconds{100});

				continue;
			}

			{
				/* NOTE: Prevent an active scene deletion/switch during the rendering task without blocking the logic update task. */
				const std::shared_lock< std::shared_mutex > activeSceneLock{m_sceneManager.activeSceneAccess()};

				const Time::Elapsed::PrintScopeRealTimeThreshold stat{"renderingTask", 1000.0 / 30.0};

				const auto & activeScene = m_sceneManager.activeScene();

				if ( activeScene != nullptr )
				{
					activeScene->updateVideoMemory();
				}

				m_overlayManager.updateVideoMemory();

				m_graphicsRenderer.renderFrame(activeScene, m_overlayManager);

				frames++;
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}

		TraceSuccess{ClassId} << "Rendering loop ended with " << frames << " frames rendered !";
	}

	bool
	Core::run () noexcept
	{
		switch ( m_startupMode )
		{
			case StartupMode::Error :
				Tracer::fatal(ClassId, "Engine startup has been aborted by the core constructor !");

				return false;

			case StartupMode::ToolsMode :
				return this->executeToolsMode();

			case StartupMode::Continue :
				/* NOTE: Let the application stop the run. */
				if ( this->onBeforeSecondaryServicesInitialization() )
				{
					return this->terminate() == 0;
				}

				/* NOTE: Finish the core initialization with secondary services. */
				if ( !this->initializeCoreLevel() )
				{
					return false;
				}

				Tracer::success(ClassId, "Engine at application level initialized !");

				m_flags[IsMainLoopRunning] = true;

				break;
		}

		/* NOTE: Create the logic loop and the rendering loop into threads
		 * automatically joined at the end of this function.
		 * TODO: Use std::jthread instead to auto join threads at the end. */
		std::thread logicsThread{[this] {
			this->logicsTask();
		}};

		std::thread renderingThread{[this] {
			this->renderingTask();
		}};

		Tracer::success(ClassId, "Core level execution started !");

		/* Launch the application level. */
		if ( this->onStart() )
		{
			Tracer::success(ClassId, "The application successfully started.");

			this->notify(ExecutionStarted);
		}
		else
		{
			Tracer::fatal(ClassId, "The application failed to start ! Exiting ...");

			this->stop();
		}

		/* NOTE: This is the engine main loop. */
		while ( m_flags[IsMainLoopRunning] )
		{
			const Time::Elapsed::PrintScopeRealTimeThreshold stat{"MainLoop", 1000.0 / 60};

			/* EventInput: Update user events.
			 * DirectInput: Copy the state of every input
			 * device to use it in the engine cycle. */
			m_inputManager.pollSystemEvents();

			/* Let the child class get the call event from the main loop. */
			this->onMainLoopCycle();

			/* NOTE: Checks whether the engine is running or paused.
			 * If not, we wait for a wake-up event with a blocking function. */
			if ( m_flags[Paused] )
			{
				/* Stop all timers of an active scene. */
				if ( m_sceneManager.hasActiveScene() )
				{
					m_sceneManager.activeScene()->pauseTimers();
				}

				/* Wait until an event release the pause state. */
				while ( m_flags[Paused] )
				{
					/* Let the child class get the call event from the main loop. */
					this->onMainLoopCycle();

					m_inputManager.waitSystemEvents(0.16);
				}

				/* Restart all timers of the active scene. */
				if ( m_sceneManager.hasActiveScene() )
				{
					m_sceneManager.activeScene()->resumeTimers();
				}
			}

			if constexpr ( IsDebug )
			{
				if ( !m_messages.empty() )
				{
					this->checkForDialogMessages();
				}
			}

			/* TODO: Create a policy to throttle the main loop according to the engine usage. */
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}

		if ( renderingThread.joinable() )
		{
			Tracer::info(ClassId, "Waiting for rendering thread to be joined ...");

			renderingThread.join();
		}

		if ( logicsThread.joinable() )
		{
			Tracer::info(ClassId, "Waiting for core logics thread to be joined ...");

			logicsThread.join();
		}

		return this->terminate() == 0;
	}

	void
	Core::checkForDialogMessages () noexcept
	{
		using namespace PlatformSpecific::Desktop::Dialog;

		const auto error = m_messages.front();

		Message dialog{
			"Internal engine message !",
			error,
			ButtonLayout::OK,
			MessageType::Info
		};

		m_messages.pop();

		this->pause();

		dialog.execute(&this->window());

		this->resume();
	}

	void
	Core::onMainLoopCycle () noexcept
	{
		/* Makes nothing special here. */
	}

	bool
	Core::initializeBaseLevel () noexcept
	{
		std::cout << "\n"
			"Engine      : " << m_identification.engineId() << "\n"
			"Application : " << m_identification.applicationId() << "\n"
			"Reverse ID  : " << m_identification.applicationReverseId() << "\n\n";

		/* Registering core help. */
		{
			m_coreHelp.registerArgument("Show this help.", "help", 'h');
			m_coreHelp.registerArgument("Disable audio layer.", "disable-audio");
			m_coreHelp.registerArgument("Display only logs which tags appears. TAG is a list of words separated by comma.", "filter-tag", 't', {"TAG"});
			m_coreHelp.registerArgument("Set a custom core settings file. FILE_PATH is where to get the settings file and should be writable.", "settings-filepath", 0, {"FILE_PATH"});
			m_coreHelp.registerArgument("Disable the generation or the saving of settings files.", "disable-settings-autosave");
			m_coreHelp.registerArgument("Enable log writing.", "enable-log", 'l', {"FILE_PATH"});
			m_coreHelp.registerArgument("Add a custom data directory.", "add-data-directory", 0, {"DIRECTORY_PATH"});
			m_coreHelp.registerArgument("Force the use of a cache directory overriding every others.", "cache-directory", 0, {"DIRECTORY_PATH"});
			m_coreHelp.registerArgument("Force the use of a config directory overriding every others.", "config-directory", 0, {"DIRECTORY_PATH"});
			m_coreHelp.registerArgument("Force the use of a data directory overriding every others.", "data-directory", 0, {"DIRECTORY_PATH"});
			m_coreHelp.registerArgument("Execute a specific tool.", "tools-mode", 't');

			m_coreHelp.registerShortcut("Quit the application.", KeyEscape, ModKeyShift);
			m_coreHelp.registerShortcut("Print the active scene content in console.", KeyF1, ModKeyShift);
			m_coreHelp.registerShortcut("Refreshes scenes (Experimental).", KeyF2, ModKeyShift);
			m_coreHelp.registerShortcut("Test dialog (Experimental).", KeyF3, ModKeyShift);
			m_coreHelp.registerShortcut("Reset the window size to defaults.", KeyF4, ModKeyShift);
			m_coreHelp.registerShortcut("Open settings file in text editor.", KeyF5, ModKeyShift);
			m_coreHelp.registerShortcut("Open file explorer to application configuration directory.", KeyF6, ModKeyShift);
			m_coreHelp.registerShortcut("Open file explorer to application cache directory.", KeyF7, ModKeyShift);
			m_coreHelp.registerShortcut("Open file explorer to application user data directory.", KeyF8, ModKeyShift);
			m_coreHelp.registerShortcut("Clean up unused resources from managers.", KeyF9, ModKeyShift);
			m_coreHelp.registerShortcut("Suspend core thread execution for 3 seconds.", KeyF10, ModKeyShift);
			m_coreHelp.registerShortcut("Toggle the window fullscreen mode.", KeyF11, ModKeyShift);
			m_coreHelp.registerShortcut("Unused yet. Reserved by the core.", KeyF12, ModKeyShift);
		}

		if ( m_primaryServices.initialize() )
		{
			Tracer::success(ClassId, "Primary services up !");
		}
		else
		{
			Tracer::fatal(ClassId, "Unable to initialize primary services !");

			m_startupMode = StartupMode::Error;

			return false;
		}

		if ( m_primaryServices.arguments().get("-h", "--help").isPresent() )
		{
			m_flags[ShowHelp] = true;

			return false;
		}

		/* Initialize the console. */
		if ( m_consoleController.initialize(m_primaryServicesEnabled) )
		{
			TraceSuccess{ClassId} << m_consoleController.name() << " service up !";

			this->registerToConsole();
		}
		else
		{
			TraceFatal{ClassId} << m_consoleController.name() << " service failed to execute !";

			m_startupMode = StartupMode::Error;

			return false;
		}

		/* Initialize download manager. */
		if ( m_networkManager.initialize(m_primaryServicesEnabled) )
		{
			TraceSuccess{ClassId} << m_networkManager.name() << " service up !";

			/* We want to know at core level, when something is downloading! */
			this->observe(&m_networkManager);
		}
		else
		{
			TraceError{ClassId} << m_networkManager.name() << " service failed to execute !";
		}

		/* Initialize resource manager services. */
		if ( m_resourceManager.initialize(m_primaryServicesEnabled) )
		{
			TraceSuccess{ClassId} << m_resourceManager.name() << " service up !";
		}
		else
		{
			TraceError{ClassId} << m_resourceManager.name() << " service failed to execute !";
		}

		/* Initialize user service. */
		if ( m_user.initialize(m_primaryServicesEnabled) )
		{
			TraceSuccess{ClassId} << m_user.name() << " service up !";
		}
		else
		{
			TraceError{ClassId} << m_user.name() << " service failed to execute !";
		}

		/* Print startup general information. */
		if ( m_primaryServices.settings().get< bool >(CoreShowInformationKey, DefaultCoreShowInformation) )
		{
			Tracer::info(ClassId, m_primaryServices.information());
		}

		/* Checks if we need to execute the engine in tool mode. */
		if ( m_primaryServices.arguments().get(ToolsArg, ToolsLongArg).isPresent() )
		{
			m_startupMode = StartupMode::ToolsMode;
		}

		Tracer::success(ClassId, "*** Core level created ***");

		return true;
	}

	bool
	Core::initializeCoreLevel () noexcept
	{
		/* Initialize platform service (GLFW). */
		if ( m_platformManager.initialize(m_secondaryServicesEnabled) )
		{
			TraceSuccess{ClassId} << m_platformManager.name() << " service up !";
		}
		else
		{
			TraceFatal{ClassId} << m_platformManager.name() << " service failed to execute !";

			return false;
		}

		/* Initialize the vulkan API. */
		if ( m_vulkanInstance.initialize(m_secondaryServicesEnabled) )
		{
			TraceSuccess{ClassId} << m_vulkanInstance.name() << " service up !";
		}
		else
		{
			TraceFatal{ClassId} << m_vulkanInstance.name() << " service failed to execute !";

			return false;
		}

		/* Initialize the handle. */
		if ( m_window.initialize(m_secondaryServicesEnabled) )
		{
			this->observe(&m_window);

			TraceSuccess{ClassId} << m_window.name() << " service up !";
		}
		else
		{
			TraceFatal{ClassId} << m_window.name() << " service failed to execute !";

			return false;
		}

		/* Initialization of the input manager. */
		if ( m_inputManager.initialize(m_secondaryServicesEnabled) )
		{
			TraceSuccess{ClassId} << m_inputManager.name() << " service up !";

			/* Configure the input manager. */
			m_inputManager.enableKeyboardListening(true);
			m_inputManager.enablePointerListening(true);
			m_inputManager.enableCopyKeyboardState(true);
			m_inputManager.enableCopyPointerState(true);

			/* Adds Core keyboard listener to the input manager. */
			m_inputManager.addKeyboardListener(this);

#if IS_MACOS
			m_inputManager.enablePointerScaling(
				m_window.state().contentXScale,
				m_window.state().contentYScale
			);
#endif

			this->observe(&m_inputManager);
		}
		else
		{
			TraceFatal{ClassId} << m_inputManager.name() << " service failed to execute !";

			return false;
		}

		/* Initialize graphics renderer. */
		if ( m_graphicsRenderer.initialize(m_secondaryServicesEnabled) )
		{
			TraceSuccess{ClassId} << m_graphicsRenderer.name() << " service up !";

			m_graphicsRenderer.registerToObject(*this);

			this->observe(&m_graphicsRenderer);
			this->observe(&m_graphicsRenderer.shaderManager());
		}
		else
		{
			TraceFatal{ClassId} << m_graphicsRenderer.name() << " service failed to execute !";

			return false;
		}

		/* Initialize video input. */
		if ( m_graphicsRenderer.usable() && m_videoExternalInput.initialize(m_secondaryServicesEnabled) )
		{
			TraceSuccess{ClassId} << m_videoExternalInput.name() << " service up !";
		}
		else
		{
			TraceWarning{ClassId} <<
				m_audioExternalInput.name() << " service failed to execute !" "\n"
				"No video input available !";
		}

		/* Initialize physics manager. */
		if ( m_physicsManager.initialize(m_secondaryServicesEnabled) )
		{
			TraceSuccess{ClassId} << m_physicsManager.name() << " service up !";
		}
		else
		{
			TraceWarning{ClassId} <<
				m_physicsManager.name() << " service failed to execute !" "\n"
				"No physics acceleration available !";
		}

		/* Initialize audio manager. */
		if ( m_audioManager.initialize(m_secondaryServicesEnabled) )
		{
			if ( m_audioManager.isAudioEnabled() )
			{
				TraceSuccess{ClassId} << m_audioManager.name() << " service up !";

				m_audioManager.registerToObject(*this);

				/* Initialize the track mixer. */
				if ( m_trackMixer.initialize(m_secondaryServicesEnabled) )
				{
					TraceSuccess{ClassId} << m_trackMixer.name() << " service up !";

					this->observe(&m_trackMixer);
				}
				else
				{
					TraceWarning{ClassId} <<
						m_trackMixer.name() << " service failed to execute." "\n"
						"No music available !";
				}

				/* Initialize the audio external input. */
				if ( m_audioExternalInput.initialize(m_secondaryServicesEnabled) )
				{
					TraceSuccess{ClassId} << m_audioExternalInput.name() << " service up !";
				}
				else
				{
					TraceWarning{ClassId} <<
						m_audioExternalInput.name() << " service failed to execute !" "\n"
						"No audio input available !";
				}
			}
		}
		else
		{
			TraceWarning{ClassId} <<
				m_audioManager.name() << " service failed to execute !" "\n"
				"No audio available !";
		}

		/* Initialization of the overlay manager. */
		if ( m_overlayManager.initialize(m_secondaryServicesEnabled) )
		{
			TraceSuccess{ClassId} << m_overlayManager.name() << " service up !";

			m_overlayManager.enable(m_inputManager, true);

			/* Initialization of the notifier. */
			if ( m_notifier.initialize(m_secondaryServicesEnabled) )
			{
				TraceSuccess{ClassId} << m_notifier.name() << " service up !";
			}
			else
			{
				TraceError{ClassId} << m_notifier.name() << " service failed to execute !";
			}

			/* Initialization of the core screen. */
			if ( !this->initializeCoreScreen() )
			{
				Tracer::warning(ClassId, "Unable to create Core screens for information's and basic functions !");
			}
		}
		else
		{
			TraceFatal{ClassId} << m_overlayManager.name() << " service failed to execute !";

			return false;
		}

		/* Initialize scene manager. */
		if ( m_sceneManager.initialize(m_secondaryServicesEnabled) )
		{
			this->observe(&m_sceneManager);

			TraceSuccess{ClassId} << m_sceneManager.name() << " service up !";
		}
		else
		{
			TraceError{ClassId} << m_sceneManager.name() << " service failed to execute !";

			return false;
		}

		Tracer::success(ClassId, "Engine at core level initialized ! Now initialization at the application level ...");

		return true;
	}

	bool
	Core::enableUserService (ServiceInterface * userService) noexcept
	{
		if ( !userService->initialize(m_userServiceEnabled) )
		{
			TraceError{ClassId} << userService->name() << " user service failed to execute !";

			return false;
		}

		TraceSuccess{ClassId} << userService->name() << " user service up !";

		return true;
	}

	void
	Core::onRegisterToConsole () noexcept
	{
		this->bindCommand("exit,quit,shutdown", [this] (const Console::Arguments & /*arguments*/, Console::Outputs & outputs) {
			outputs.emplace_back(Severity::Info, "Shutdown procedure called from console ...");

			this->stop();

			return 0;
		}, "Quit the application.");
	}

	bool
	Core::initializeCoreScreen () noexcept
	{
#ifdef IMGUI_ENABLED
		const auto screen = m_overlayManager.createImGUIScreen("CoreScreen", [] () {
			bool show = true;
			ImGui::ShowDemoWindow(&show);
		});

		screen->setVisibility(false);
#else
		const auto screen = m_overlayManager.createScreen("CoreScreen", false, false);
#endif

		return screen != nullptr;
	}

	void
	Core::pause () noexcept
	{
		if ( m_flags[Paused]  )
		{
			return;
		}

		/* Dispatch the pause event,
		 * first by sending the event,
		 * then directly to the sub application. */
		this->notify(ExecutionPaused);

		this->onPause();

		/* Pause the core engine last. */
		m_flags[Paused] = true;
	}

	void
	Core::resume () noexcept
	{
		if ( !m_flags[Paused] )
		{
			return;
		}

		/* Pause the core engine first. */
		m_flags[Paused] = false;

		/* Dispatch the resume event,
		 * first by sending the event,
		 * then directly to the sub application. */
		this->notify(ExecutionResumed);

		this->onResume();
	}

	void
	Core::stop () noexcept
	{
		std::cout << "\n"
			"*******************************" "\n"
			"   Engine is about to stop !   " "\n"
			"*******************************" "\n\n";

		/* Dispatch the stop event,
		 * first by sending the event,
		 * then directly to the sub application. */
		this->notify(ExecutionStopped);

		this->onStop();

		/* FIXME: Check the right order for stopping the engine! */
		m_sceneManager.deleteAllScenes();

		/* Stopping the logics and rendering loops. */
		m_flags[IsLogicsLoopRunning] = false;
		m_flags[IsRenderingLoopRunning] = false;

		/* Stopping the main loop. */
		m_flags[IsMainLoopRunning] = false;
	}

	unsigned int
	Core::terminate () noexcept
	{
		unsigned int error = 0;

		/* Terminate user services. */
		for ( auto * userService : std::ranges::reverse_view(m_userServiceEnabled) )
		{
			if ( userService->terminate() )
			{
				TraceSuccess{ClassId} << userService->name() << " user service terminated gracefully !";
			}
			else
			{
				error++;

				TraceError{ClassId} << userService->name() << " user service failed to terminate properly !";
			}
		}

		m_userServiceEnabled.clear();

		/* Terminate secondary services. */
		for ( auto * service : std::ranges::reverse_view(m_secondaryServicesEnabled) )
		{
			if ( service->terminate() )
			{
				TraceSuccess{ClassId} << service->name() << " secondary service terminated gracefully !";
			}
			else
			{
				error++;

				TraceError{ClassId} << service->name() << " secondary service failed to terminate properly !";
			}
		}

		m_resourceManager.unloadUnusedResources();

		m_secondaryServicesEnabled.clear();

		if constexpr ( VulkanTrackingDebugEnabled )
		{
			const auto vkAliveObjectCount = AbstractObject::s_tracking.size();

			if ( vkAliveObjectCount > 0 )
			{
				std::cerr << "[DEBUG:VK_TRACKING] There is " << vkAliveObjectCount << " Vulkan objects not properly destructed !" "\n";

				for ( auto & alloc : AbstractObject::s_tracking )
				{
					std::cerr << "[DEBUG:VK_TRACKING] The Vulkan object @" << alloc.first << " '" << alloc.second << "' still alive !" << "\n";
				}
			}
			else
			{
				std::cout << "[DEBUG:VK_TRACKING] All Vulkan objects has been released !" << "\n";
			}
		}

		return error;
	}

	void
	Core::openFiles (const std::vector< std::filesystem::path > & filepaths) noexcept
	{
		std::vector< std::filesystem::path > verifiedFilepaths;
		verifiedFilepaths.reserve(filepaths.size());

		for ( const auto & filepath : filepaths )
		{
			TraceInfo{ClassId} << "Check file : " << filepath;

			// TODO : Filter files for the application.

			// TODO : If the file is a resource file, read it to complete the resource store.

			verifiedFilepaths.emplace_back(filepath);
		}

		if ( verifiedFilepaths.empty() )
		{
			return;
		}

		this->onOpenFiles(verifiedFilepaths);
	}

	void
	Core::hangExecution (const std::string & command) noexcept
	{
		std::cout << "\n\n\n"
			"******************************************************************\n"
			"	 Execution has been hung ! Press SPACE-BAR to continue ...	\n"
			"******************************************************************\n"
			"\n\n\n";

		/* Execute a command (Only in debug) */
		if constexpr ( IsDebug )
		{
			system(command.c_str());
		}

		while ( glfwGetKey(m_window.handle(), GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			glfwPollEvents();
		}

		while ( true )
		{
			glfwWaitEvents();

			if ( glfwGetKey(m_window.handle(), GLFW_KEY_SPACE) == GLFW_PRESS )
			{
				break;
			}
		}
	}

	bool
	Core::onKeyPress (int32_t key, int32_t scancode, int32_t modifiers, bool repeat) noexcept
	{
		/* NOTE: Pause the engine. */
		if ( !repeat && key == KeyPause )
		{
			if ( m_flags[Paused] )
			{
				this->resume();
			}
			else
			{
				this->pause();
			}

			return true;
		}

		/* NOTE: Let the user application consume the event. */
		return this->onAppKeyPress(key, scancode, modifiers, repeat);
	}

	bool
	Core::onKeyRelease (int32_t key, int32_t scancode, int32_t modifiers) noexcept
	{
		/* NOTE: When the shift modifiers are pressed,
		 * the core level has the priority to check the key released. */
		if ( isKeyboardModifierPressed(ModKeyShift, modifiers) )
		{
			switch ( key )
			{
				case KeyEscape :
				{
					Tracer::info(ClassId, "Force quit !");

					this->stop();
				}
					return true;

				/* Direct keys reserved by core. */
				case KeyF1 :
				{
					m_audioManager.play("switch_on");

					if ( m_sceneManager.hasActiveScene())
					{
						const auto scene = m_sceneManager.activeScene();

						TraceInfo{ClassId} <<
							"Scene '" << scene->name() << "' content:" "\n" <<
							"Octree System : " "\n" << scene->getSectorSystemStatistics(true) <<
							"Static entities : " "\n" << scene->getStaticEntitySystemStatistics(true) <<
							"Node entities : " "\n" << scene->getNodeSystemStatistics(true) <<
							"Light set : " "\n" << scene->lightSet();
					}
					else
					{
						Tracer::info(ClassId, "No active scene !");
					}
				}
					return true;

				case KeyF2 :
				{
					m_audioManager.play("switch_on");

					m_sceneManager.refreshScenes();
				}
					return true;

				case KeyF3 :
					this->notifyUser("Core reserved SHIFT+F3 shortcut hit.");

					return true;

				case KeyF4 :
					if ( !m_window.isFullscreenMode() )
					{
						TraceInfo{ClassId} << "Reset window size to default " << DefaultVideoWindowWidth << "X" << DefaultVideoWindowHeight;

						if ( m_window.resize(DefaultVideoWindowWidth, DefaultVideoWindowHeight) )
						{
							m_window.centerPosition();
						}
					}
					return true;

				case KeyF5 :
				{
					this->notifyUser("Opening settings file ...");

					auto & settings = this->primaryServices().settings();

					settings.saveAtExit(false);

					PlatformSpecific::Desktop::openFile(settings.filepath());
				}
					return true;

				case KeyF6 :
				{
					this->notifyUser("Showing application configuration directory ...");

					PlatformSpecific::Desktop::openFolder(this->primaryServices().fileSystem().configDirectory());
				}
					return true;

				case KeyF7 :
				{
					this->notifyUser("Showing application cache directory ...");

					PlatformSpecific::Desktop::openFolder(this->primaryServices().fileSystem().cacheDirectory());
				}
					return true;

				case KeyF8 :
				{
					this->notifyUser("Showing application user data directory ...");

					PlatformSpecific::Desktop::openFolder(this->primaryServices().fileSystem().userDataDirectory());
				}
					return true;

				case KeyF9 :
				{
					this->notifyUser("Cleaning unused resources ...");

					m_audioManager.play("switch_on");

					const auto count = m_resourceManager.unloadUnusedResources();

					TraceInfo{ClassId} << count << " resources cleaned !";
				}
					return true;

				case KeyF10 :
				{
					this->notifyUser("Core engine paused for 3 seconds ...");

					std::this_thread::sleep_for(std::chrono::seconds(3));

					this->notifyUser("Core engine wake-up.");
				}
					return true;

				case KeyF11 :
				{
					this->notifyUser("Toggling fullscreen mode ...");

					if ( m_window.isFullscreenMode() )
					{
						m_window.switchToWindowedMode();
					}
					else
					{
						m_window.switchToFullscreenMode();
					}
				}

					return true;

				case KeyF12 :
					this->notifyUser("Core reserved SHIFT+F12 shortcut hit.");

					return true;

				case KeyPad1 :
					m_window.setGamma(0.8F);
					return true;

				case KeyPad2 :
					m_window.setGamma(1.0F);
					return true;

				case KeyPad3 :
					m_window.setGamma(1.2F);
					return true;

				default:
					break;
			}
		}

		/* NOTE: Let the child application looks for the key pressed. */
		if ( this->onAppKeyRelease(key, scancode, modifiers) )
		{
			return true;
		}

		/* NOTE: If the application does not catch any key, we let the core having a default behavior. */
		if ( m_flags[PreventDefaultKeyBehaviors] )
		{
			return false;
		}

		switch ( key )
		{
			case KeyGraveAccent :
				// TODO: Re-enable this method
				//m_console.enable();

				return true;

			case KeyEscape :
				this->stop();

				return true;

			default:
				return false;
		}
	}

	bool
	Core::onCharacterType (uint32_t unicode) noexcept
	{
		/* NOTE: Let the user application consume the event. */
		return this->onAppCharacterType(unicode);
	}

	bool
	Core::screenshot (bool /*depth*/, bool /*stencil*/) noexcept
	{
		/* Gets the capture directory. */
		const auto captures = m_primaryServices.fileSystem().userDataDirectory("Captures");

		if ( !IO::writable(captures) )
		{
			TraceError{ClassId} << "Unable to write in captures directory '" << captures << "' !";

			return false;
		}

		/* FIXME: TODO with vulkan */

		return true;
	}

	bool
	Core::dumpFramebuffer () const noexcept
	{
		/* Framebuffer dumping directory. */
		const auto directory = m_primaryServices.fileSystem().userDataDirectory("framebuffer-snapshots");

		if ( !IO::directoryExists(directory) )
		{
			if ( !IO::createDirectory(directory) )
			{
				TraceError{ClassId} << "Unable to create the directory '" << directory << "' !";

				return false;
			}
		}
		else
		{
			if ( !IO::writable(directory) )
			{
				TraceError{ClassId} << "Unable to write into directory '" << directory << "' !";

				return false;
			}
		}

		return true;
	}

	bool
	Core::onNotification (const ObservableTrait * observable, int notificationCode, const std::any & data) noexcept
	{
		if ( observable == &m_networkManager )
		{
			TraceDebug{ClassId} << "Receiving an event from '" << NetworkManager::ClassId << "' (code:" << notificationCode << ") ...";

			return true;
		}

		if ( observable == &m_window )
		{
			switch ( notificationCode )
			{
				case Window::OSNotifiesWindowGetFocus :
				case Window::OSNotifiesWindowVisible :
					this->resume();
					break;

				case Window::OSNotifiesWindowLostFocus :
				case Window::OSNotifiesWindowHidden :
					if ( m_flags[Pausable] )
					{
						this->pause();
					}
					break;

				case Window::OSRequestsToTerminate :
					this->stop();
					break;

				default :
					if constexpr ( ObserverDebugEnabled )
					{
						TraceDebug{ClassId} << "Event #" << notificationCode << " from '" << Window::ClassId << "' ignored.";
					}
					break;
			}

			return true;
		}

		if ( observable == &m_inputManager )
		{
			TraceDebug{ClassId} << "Receiving an event from '" << Input::Manager::ClassId << "' (code:" << notificationCode << ") ...";

			return true;
		}

		if ( observable == &m_graphicsRenderer )
		{
			switch ( notificationCode )
			{
				case Renderer::SwapChainRecreated :
					m_sceneManager.refreshScenes();
					break;

				case Renderer::SwapChainCreated :
				case Renderer::SwapChainDestroyed :
				default:
					TraceDebug{ClassId} << "Receiving an event from '" << Renderer::ClassId << "' (code:" << notificationCode << ") ...";
					break;
			}

			return true;
		}

		if ( observable == &m_graphicsRenderer.shaderManager() )
		{
			switch ( notificationCode )
			{
				case Saphir::ShaderManager::ShaderCompilationSucceed :
					this->notifyUser(BlobTrait{} << "Shader '" << std::any_cast< std::string >(data) << "' compilation succeeded !");
					break;

				case Saphir::ShaderManager::ShaderCompilationFailed :
				{
					const auto shaderDetails = std::any_cast< std::pair< std::string, std::string > >(data);

					this->onShaderCompilationFailed(shaderDetails.first, shaderDetails.second);
				}
					break;

				default:
					break;
			}

			return true;
		}

		if ( observable == &m_trackMixer )
		{
			TraceDebug{ClassId} << "Receiving an event from '" << Audio::TrackMixer::ClassId << "' (code:" << notificationCode << ") ...";

			switch ( notificationCode )
			{
				case Audio::TrackMixer::MusicPlaying :
				case Audio::TrackMixer::MusicSwitching :
					this->notifyUser(std::any_cast< std::string >(data));
					break;

				case Audio::TrackMixer::MusicPaused :
					this->notifyUser("Music paused !");
					break;

				case Audio::TrackMixer::MusicResumed :
					this->notifyUser("Music resumed !");
					break;

				case Audio::TrackMixer::MusicStopped :
					this->notifyUser("Music stopped !");
					break;

				default:
					break;
			}

			return true;
		}

		if ( observable == &m_sceneManager )
		{
			switch ( notificationCode )
			{
				case Scenes::Manager::SceneDestroyed :
					m_resourceManager.unloadUnusedResources();
					break;

				case Scenes::Manager::SceneCreated :
				case Scenes::Manager::SceneLoaded :
				case Scenes::Manager::SceneActivated :
				case Scenes::Manager::SceneDeactivated :
				default :
					TraceDebug{ClassId} << "Receiving an event from '" << Scenes::Manager::ClassId << "' (code:" << notificationCode << ") ...";
					break;
			}

			return true;
		}

		return this->onAppNotification(observable, notificationCode, data);
	}

	bool
	Core::executeToolsMode () noexcept
	{
		Tracer::info(ClassId, "Executing in tools mode ...");

		const auto tools = m_primaryServices.arguments().get(ToolsArg, ToolsLongArg).value();

		if ( tools == VulkanInformationToolName )
		{
			Tool::ShowVulkanInformation tool{m_primaryServices.arguments(), m_vulkanInstance};

			return tool.execute();
		}

		if ( tools == PrintGeometryToolName )
		{
			Tool::GeometryDataPrinter tool{m_primaryServices.arguments()};

			return tool.execute();
		}

		if ( tools == ConvertGeometryToolName )
		{
			TraceDebug{ClassId} << "FIXME: ...";

			return true;
		}

		TraceWarning{ClassId} << "Unrecognized tools '" << tools << "' !";

		return false;
	}

	void
	Core::showStatistics (double /*elapsedTime*/) const noexcept
	{
		const auto & rendererStatistics = m_graphicsRenderer.statistics();

		std::stringstream text;

		text <<
			"Clock : " << Time::elapsedSeconds() << " seconds elapsed ..." "\n" <<
			"FPS : " << rendererStatistics.executionsPerSecond() << " [" << rendererStatistics.duration() << " ms]" "\n" <<
			"FPS (avg) : " << rendererStatistics.averageExecutionsPerSecond() << " [" << rendererStatistics.averageDuration() << " ms]";

		/* VULKAN_DEV */
		/*if ( m_statisticsDisplay != nullptr )
		{
			m_statisticsDisplay->write(text.str(), true);
		}
		else*/
		{
			std::cout << text.str() << '\n';
		}
	}
}
