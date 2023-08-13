/*
 * Emeraude/Core.cpp
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

#include "Core.hpp"

/* C/C++ standard libraries. */
#include <iostream> // DEV
#include <ranges>
#include <thread>

/* Local inclusions */
#include "Constants.hpp"
#include "Input/KeyboardController.hpp"
#include "Time/Time.hpp"
#include "Tool/GeometryDataPrinter.hpp"
#include "Tool/ShowVulkanInformation.hpp"

namespace Emeraude
{
	// NOLINTBEGIN(*-magic-numbers)
	using namespace Libraries;
	using namespace Vulkan;
	using namespace Graphics;
	using namespace Scenes;
	using namespace Input;
	using namespace Resources;

	Core * Core::s_instance{nullptr}; // NOLINT NOTE: Singleton behavior

	Core::Core (int argc, const char * argv[], const char * applicationName, const Libraries::Version & applicationVersion, const char * applicationOrganization, const char * applicationDomain) noexcept
		: KeyboardListenerInterface(true, false, false), ConsoleControllable(ClassId),
		  m_applicationName(applicationName),
		  m_applicationVersion(applicationVersion),
		  m_applicationOrganization(applicationOrganization),
		  m_applicationDomain(applicationDomain),
		  m_arguments(argc, argv)
	{
		/* NOTE: Avoid to double construct the engine. */
		if ( s_instance != nullptr )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", constructor called twice !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

			std::terminate();
		}

		s_instance = this;

		/* Identification. */
		{
			auto date = String::explode(LibraryCompilationDate, ' ');

			TraceInfo{ClassId} << LibraryName << ' ' << LibraryVersion << " (" << LibraryPlatform << ") - " << LibraryOrganizationName << ' ' << date[2];
		}

		/* Initialize arguments. */
		if ( m_arguments.initialize(m_primaryServicesEnabled) )
		{
			TraceSuccess{ClassId} << m_arguments.name() << " service up !";

			/* Initialize core help. */
			if ( m_coreHelp.initialize(m_primaryServicesEnabled) )
			{
				/* Registering core help. */
				m_coreHelp.registerArgument("Show this help.", "help", 'h');
				m_coreHelp.registerArgument("Disable audio layer.", "disable-audio");
				m_coreHelp.registerArgument("Display only logs which tags appears. TAG is a list of words separated by comma.", "filter-tag", 't', {"TAG"});
				m_coreHelp.registerArgument("Set a custom core settings file. FILE_PATH is where to get the settings file and should be writable.", "settings-core-filepath", 0, {"FILE_PATH"});
				m_coreHelp.registerArgument("Set a custom application settings file. FILE_PATH is where to get the settings file and should be writable.", "settings-application-filepath", 0, {"FILE_PATH"});
				m_coreHelp.registerArgument("Disable the generation or the saving of settings files.", "disable-settings-autosave");
				m_coreHelp.registerArgument("Enable log writing.", "enable-log", 'l', {"FILE_PATH"});
				m_coreHelp.registerArgument("Add a custom cache directory.", "cache-directory", 0, {"DIRECTORY_PATH"});
				m_coreHelp.registerArgument("Add a custom config directory.", "config-directory", 0, {"DIRECTORY_PATH"});
				m_coreHelp.registerArgument("Add a custom data directory.", "data-directory", 0, {"DIRECTORY_PATH"});
				m_coreHelp.registerArgument("Force the use of a cache directory overriding every others.", "force-cache-directory", 0, {"DIRECTORY_PATH"});
				m_coreHelp.registerArgument("Force the use of a config directory overriding every others.", "force-config-directory", 0, {"DIRECTORY_PATH"});
				m_coreHelp.registerArgument("Force the use of a data directory overriding every others.", "force-data-directory", 0, {"DIRECTORY_PATH"});
				m_coreHelp.registerArgument("Execute a specific tool.", "tools-mode", 't');

				m_coreHelp.registerShortcut("Print the active scene content in console.", Input::Key::KeyF1, Input::ModKeyShift);
				m_coreHelp.registerShortcut("Unused yet. Reserved by the core.", Input::Key::KeyF2, Input::ModKeyShift);
				m_coreHelp.registerShortcut("Unused yet. Reserved by the core.", Input::Key::KeyF3, Input::ModKeyShift);
				m_coreHelp.registerShortcut("Unused yet. Reserved by the core.", Input::Key::KeyF4, Input::ModKeyShift);
				m_coreHelp.registerShortcut("Unused yet. Reserved by the core.", Input::Key::KeyF5, Input::ModKeyShift);
				m_coreHelp.registerShortcut("Unused yet. Reserved by the core.", Input::Key::KeyF6, Input::ModKeyShift);
				m_coreHelp.registerShortcut("Unused yet. Reserved by the core.", Input::Key::KeyF7, Input::ModKeyShift);
				m_coreHelp.registerShortcut("Unused yet. Reserved by the core.", Input::Key::KeyF8, Input::ModKeyShift);
				m_coreHelp.registerShortcut("Clean up unused resources from managers.", Input::Key::KeyF9, Input::ModKeyShift);
				m_coreHelp.registerShortcut("Suspend core thread execution for 3 seconds.", Input::Key::KeyF10, Input::ModKeyShift);
				m_coreHelp.registerShortcut("Unused yet. Reserved by the core.", Input::Key::KeyF11, Input::ModKeyShift);
				m_coreHelp.registerShortcut("Unused yet. Reserved by the core.", Input::Key::KeyF12, Input::ModKeyShift);

				TraceSuccess{ClassId} << m_coreHelp.name() << " service up !";
			}
			else
			{
				TraceWarning{ClassId} << m_coreHelp.name() << " service failed to execute !";
			}

			/* Initialize application help. */
			if ( m_applicationHelp.initialize(m_primaryServicesEnabled) )
			{
				TraceSuccess{ClassId} << m_applicationHelp.name() << " service up !";
			}
			else
			{
				TraceWarning{ClassId} << m_applicationHelp.name() << " service failed to execute !";
			}

			if ( m_arguments.get("-h", "--help").isPresent() )
			{
				m_startupMode = StartupMode::ShowHelp;

				return;
			}
		}
		else
		{
			TraceFatal{ClassId} << m_arguments.name() << " service failed to execute !";

			m_startupMode = StartupMode::Error;

			return;
		}

		/* Initialize tracer. */
		if ( m_tracer.initialize(m_primaryServicesEnabled) )
		{
			TraceSuccess{ClassId} << m_tracer.name() << " service up !";
		}
		else
		{
			TraceFatal{ClassId} << m_tracer.name() << " service failed to execute !";

			m_startupMode = StartupMode::Error;

			return;
		}

		/* Initialize the file system to reach every useful directories. */
		if ( m_fileSystem.initialize(m_primaryServicesEnabled) )
		{
			TraceSuccess{ClassId} << m_fileSystem.name() << " service up !";

			/* Creating some basic paths */
			const auto directory = m_fileSystem.userDataDirectory("captures");

			if ( !directory.exists() )
			{
				if ( directory.create() )
				{
					Tracer::success(ClassId, "Captures directory created.");
				}
				else
				{
					Tracer::warning(ClassId, "Unable to create captures directory.");
				}
			}
		}
		else
		{
			TraceFatal{ClassId} << m_fileSystem.name() << " service failed to execute !";

			m_startupMode = StartupMode::Error;

			return;
		}

		/* Initialize core settings.
		 * NOTE : Settings class manages to write default file. */
		{
			const auto filepath = this->getSettingFile(CoreSettingsFilename, "--settings-core-filepath");

			TraceInfo{ClassId} << "Loading core settings file from '" << filepath << "' ...";

			m_coreSettings.setFilepath(filepath);

			if ( m_coreSettings.initialize(m_primaryServicesEnabled) )
			{
				TraceSuccess{ClassId} << m_coreSettings.name() << " service up !";

				/* NOTE: Now the core settings is initialized, we can update Tracer service configuration. */
				m_tracer.readCoreSettings();
			}
			else
			{
				Tracer::error(ClassId, "There is a problem to read or write the core settings file. The engine will use the default configuration.");
			}

			if ( m_arguments.get("--disable-settings-autosave").isPresent() )
			{
				m_coreSettings.doNotCreateConfigFile();
			}
		}

		/* Initialize user settings.
		 * NOTE : Settings class manages to write default file. */
		{
			const auto filepath = this->getSettingFile(ApplicationSettingsFilename, "--settings-application-filepath");

			TraceInfo{ClassId} << "Loading user settings file from '" << filepath << "' ...";

			m_applicationSettings.setFilepath(filepath);

			if ( m_applicationSettings.initialize(m_primaryServicesEnabled) )
			{
				TraceSuccess{ClassId} << m_applicationSettings.name() << " service up !";
			}
			else
			{
				Tracer::error(ClassId, "There is a problem to read or write the application settings file. The engine will use the default configuration.");
			}

			if ( m_arguments.get("--disable-settings-autosave").isPresent() )
			{
				m_applicationSettings.doNotCreateConfigFile();
			}
		}

		/* Initialize the console. */
		if ( m_console.initialize(m_primaryServicesEnabled) )
		{
			TraceSuccess{ClassId} << m_console.name() << " service up !";

			/* Console commands bindings. */
			this->bindCommand("exit,quit,shutdown", std::bind(&Core::CFQuit, this, std::placeholders::_1), "Quit the application.");

			this->registerToConsole();
		}
		else
		{
			TraceFatal{ClassId} << m_console.name() << " service failed to execute !";

			m_startupMode = StartupMode::Error;

			return;
		}

		/* Initialize download manager. */
		if ( m_networkManager.initialize(m_primaryServicesEnabled) )
		{
			TraceSuccess{ClassId} << m_networkManager.name() << " service up !";

			/* We want to know at core level, when something is downloading ! */
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

		/* Checks if we need to execute the engine in tool mode. */
		if ( m_arguments.get(ToolsArg, ToolsLongArg).isPresent() )
		{
			m_startupMode = StartupMode::ToolsMode;
		}

#ifdef DEBUG
		std::cout << "*** Core level created ***" "\n";
#endif
	}

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

			m_resourceManager.unloadUnusedResources();
		}

		m_primaryServicesEnabled.clear();

#ifdef DEBUG
		std::cout << "*** Core level terminated ***" "\n";
#endif

		s_instance = nullptr;
	}

	Path::File
	Core::getSettingFile (const std::string & filename, const std::string & argumentName) noexcept
	{
		const auto arg = m_arguments.get(argumentName);

		if ( arg.isPresent() )
		{
			TraceInfo{ClassId} << "Loading an alternate settings file in '" << arg.value() << "'...";

			return Path::File{arg.value()};
		}

		for ( const auto & configDirectory : m_fileSystem.configDirectoriesList() )
		{
			Path::File filepath{configDirectory, filename};

			if ( !filepath.exists() )
			{
				continue;
			}

			TraceInfo{ClassId} << "Settings file '" << filepath << "' found !";

			return filepath;
		}

		return Path::File{m_fileSystem.configDirectory(), filename};
	}

	void
	Core::processLogicsTask (double milliseconds) noexcept
	{
		const std::lock_guard< std::mutex > lock{m_processLogicsMutex};

		/* NOTE: If option is false, the lifetime will be estimated. */
		m_lifetime += m_flags[LifetimeUsesRealTime] ? milliseconds : EngineUpdateCycleDuration< double > * 1000.0;

		/* Updates the active scene node position and velocities. */
		auto activeScene = m_sceneManager.activeScene();

		if ( activeScene != nullptr )
		{
			activeScene->processLogics(m_cycle);
		}

		/* Call child method ... */
		this->onProcessLogics(m_cycle);

		m_cycle++;
	}

	bool
	Core::run () noexcept
	{
		switch ( m_startupMode )
		{
			case StartupMode::Error :
				Tracer::fatal(ClassId, "Engine startup has been aborted by the Core constructor !");

				return false;

			case StartupMode::ToolsMode :
				return this->executeToolsMode();

			case StartupMode::ShowHelp :
				std::cout <<
					"\n\n" "Emeraude Engine help." "\n" <<
					m_coreHelp.argumentDocsString() << '\n' <<
					m_coreHelp.shortcutDocsString() << '\n' <<
					m_applicationHelp.argumentDocsString() << '\n' <<
					m_applicationHelp.shortcutDocsString() << "\n\n";

				return this->terminate() == 0;

			case StartupMode::Continue :
				if ( this->readArgumentsBeforeInitialization(m_arguments) )
				{
					return this->terminate() == 0;
				}

				if ( !this->initializeCoreLevel() )
				{
					return false;
				}

				if ( !this->onInitialize() )
				{
					Tracer::fatal(ClassId, "An application level error occurred during initialization !");

					return false;
				}

				Tracer::success(ClassId, "Engine at application level initialized !");

				m_flags[IsRunning] = true;
				break;
		}

		if ( this->onStart() )
		{
			Tracer::info(ClassId, "Core execution started !");

			this->notify(ExecutionStarted);
		}
		else
		{
			Tracer::fatal(ClassId, "Inherited Core::onStart() method returned an error ! Exiting ...");

			m_flags[IsRunning] = false;
		}

		Tracer::info(ClassId, "Launching the logics loop in a thread ...");

		/* Create the logics management thread. */
		m_logicsUpdateTimerID = this->createTimer(
			std::bind(&Core::processLogicsTask, this, std::placeholders::_1),
			EngineUpdateCycleDuration< double > * 1000.0,
			false, /* We want to loop forever... And ever... And ev.. */
			true, /* We want to start it right now. */
			true /* We want a precise time. */
		);

		Tracer::info(ClassId, "Launching the main loop ...");

		while ( m_flags[IsRunning] )
		{
			/* [DirectInput] Copy the state of every input device
			 * to use it to this engine cycle. */
			m_inputManager.getInputsState();

			/* Asks the graphics renderer a new frame. */
			m_graphicsRenderer.renderFrame(m_sceneManager.activeScene(), m_overlayManager, m_devManager, m_lifetime);

			/* NOTE: Checks whether the engine is running or paused.
			 * If not, we wait a wake-up event with a blocking function. */
			if ( m_flags[Paused] )
			{
				/* Stop all timers. */
				this->pauseTimers();

				/* Stop all timers of active scene. */
				if ( m_sceneManager.hasActiveScene() )
				{
					m_sceneManager.activeScene()->pauseTimers();
				}

				/* Wait until an event release the pause state. */
				while ( m_flags[Paused] )
				{
					m_inputManager.waitSystemEvents();
				}

				/* Restart all timers. */
				this->resumeTimers();

				/* Restart all timers of active scene. */
				if ( m_sceneManager.hasActiveScene() )
				{
					m_sceneManager.activeScene()->resumeTimers();
				}

				continue;
			}

			/* [EventInput] Update user events. */
			m_inputManager.pollSystemEvents();
		}

		return this->terminate() == 0;
	}

	bool
	Core::initializeCoreLevel () noexcept
	{
		Tracer::info(ClassId, "Core engine initialization...");

		/* Initialize platform service (GLFW). */
		if ( m_platformManager.initialize(m_secondaryServicesEnabled) )
		{
			TraceSuccess{ClassId} << m_fileSystem.name() << " service up !";
		}
		else
		{
			TraceFatal{ClassId} << m_fileSystem.name() << " service failed to execute !";

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

			/* Adds Core keyboard listener to input manager. */
			m_inputManager.addKeyboardListener(this);

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

			/* Initialize graphics transfer manager. */
			if ( m_graphicsRenderer.usable() )
			{
				m_graphicsTransferManager.setDevice(m_graphicsRenderer.device());

				if ( m_graphicsTransferManager.initialize(m_secondaryServicesEnabled) )
				{
					TraceSuccess{ClassId} << m_graphicsTransferManager.name() << " service up !";
				}
				else
				{
					TraceFatal{ClassId} << m_graphicsTransferManager.name() << " service failed to execute !";

					return false;
				}
			}
		}
		else
		{
			TraceFatal{ClassId} << m_graphicsRenderer.name() << " service failed to execute !";

			return false;
		}

		/* Initialize vertex buffer format manager. */
		if ( m_vertexBufferFormatManager.initialize(m_secondaryServicesEnabled) )
		{
			TraceSuccess{ClassId} << m_vertexBufferFormatManager.name() << " service up !";
		}
		else
		{
			TraceFatal{ClassId} << m_vertexBufferFormatManager.name() << " service failed to execute !";

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

			/* Initialize physics transfer manager. */
			if ( m_physicsManager.isPhysicsAccelerationAvailable() )
			{
				m_physicsTransferManager.setDevice(m_physicsManager.device());

				if ( m_physicsTransferManager.initialize(m_secondaryServicesEnabled) )
				{
					TraceSuccess{ClassId} << m_physicsTransferManager.name() << " service up !";
				}
				else
				{
					TraceFatal{ClassId} << m_physicsTransferManager.name() << " service failed to execute !";

					return false;
				}
			}
		}
		else
		{
			TraceWarning{ClassId} <<
				m_physicsTransferManager.name() << " service failed to execute !" "\n"
				"No physics acceleration available !";
		}

		/* Shader compiler. */
		if ( m_shaderCompiler.initialize(m_secondaryServicesEnabled) )
		{
			TraceSuccess{ClassId} << m_shaderCompiler.name() << " service up !";
		}
		else
		{
			TraceFatal{ClassId} << m_shaderCompiler.name() << " service failed to execute !";

			return false;
		}

		/* Shader manager. */
		if ( m_shaderManager.initialize(m_secondaryServicesEnabled) )
		{
			TraceSuccess{ClassId} << m_shaderManager.name() << " service up !";
		}
		else
		{
			TraceFatal{ClassId} << m_shaderManager.name() << " service failed to execute !";

			return false;
		}

		/* Initialize audio manager. */
		if ( m_audioManager.initialize(m_secondaryServicesEnabled) )
		{
			TraceSuccess{ClassId} << m_audioManager.name() << " service up !";

			Tracer::info(ClassId, m_audioManager.getAPIInformation());

			m_audioManager.registerToObject(*this);

			/* Initialize the track mixer. */
			if ( m_trackMixer.initialize(m_secondaryServicesEnabled) )
			{
				TraceSuccess{ClassId} << m_trackMixer.name() << " service up !";

				this->observe(&m_trackMixer);

				m_trackMixer.registerToObject(*this);
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

			/* Preloading engine internal sounds. */
			auto & sounds = m_resourceManager.sounds();

			m_switchOnSound = sounds.getResource("switch_on");
			m_switchOffSound = sounds.getResource("switch_off");
			m_captureSound = sounds.getResource("capture");
		}
		else
		{
			TraceWarning{ClassId} <<
				m_audioExternalInput.name() << " service failed to execute !" "\n"
				"No audio available !";
		}

		/* Initialization of the overlay manager. */
		if ( m_overlayManager.initialize(m_secondaryServicesEnabled) )
		{
			TraceSuccess{ClassId} << m_overlayManager.name() << " service up !";

			/* NOTE: Overlay manager could have been disabled at startup. */
			if ( m_overlayManager.usable() )
			{
				/* Initialization of the notifier. */
				if ( m_notifier.initialize(m_secondaryServicesEnabled) )
				{
					TraceSuccess{ClassId} << m_notifier.name() << " service up !";
				}
				else
				{
					TraceError{ClassId} << m_notifier.name() << " service failed to execute !";
				}

				/* Call the console to build the graphical display. */
				if ( !m_console.buildGUI() )
				{
					Tracer::error(ClassId, "Unable to create the graphical console !");
				}

				/* Initialization of the core screen. */
				if ( !this->initializeCoreScreen() )
				{
					Tracer::warning(ClassId, "Unable to create Core screens for information's and basic functions !");
				}
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

		/* Initialize dev manager. */
		if ( m_devManager.initialize(m_secondaryServicesEnabled) )
		{
			m_devManager.observe(&m_window);

			TraceSuccess{ClassId} << m_devManager.name() << " service up !";
		}
		else
		{
			TraceError{ClassId} << m_devManager.name() << " service failed to execute !";
		}

		Tracer::success(ClassId, "Engine at core level initialized ! Now initialization at the application level ...");

		return true;
	}

	bool
	Core::initializeCoreScreen () noexcept
	{
		Tracer::info(ClassId, "Initializing core screen ...");

		return true;
	}

	void
	Core::pause () noexcept
	{
		if ( m_flags[Paused]  )
		{
			return;
		}

		m_flags[Paused] = true;

		/* Dispatch the pause event,
		 * first by sending the event
		 * then directly to the sub application. */
		this->notify(ExecutionPaused);

		this->onPause();
	}

	void
	Core::resume () noexcept
	{
		if ( !m_flags[Paused] )
		{
			return;
		}

		m_flags[Paused] = false;

		/* Dispatch the resume event,
		 * first by sending the event
		 * then directly to the sub application. */
		this->notify(ExecutionResumed);

		this->onResume();
	}

	void
	Core::stop () noexcept
	{
		/* Wait for the logic processing to finish the update. */
		const std::lock_guard< std::mutex > lock{m_processLogicsMutex};

		m_flags[IsRunning] = false;

		/* Stop the update interval. */
		this->stopTimer(m_logicsUpdateTimerID);

		/* Dispatch the stop event,
		 * first by sending the event
		 * then directly to the sub application. */
		this->notify(ExecutionStopped);

		this->onStop();
	}

	unsigned int
	Core::terminate () noexcept
	{
		this->onTermination();

		/* Destroy timers. */
		{
			this->destroyTimers();

			m_logicsUpdateTimerID = 0UL;
		}

		/* Removes all loaded scenes. */
		m_sceneManager.deleteAllScenes();

		m_switchOnSound.reset();
		m_switchOffSound.reset();
		m_captureSound.reset();

		/* Terminate secondary services. */
		auto error = 0U;

		for ( auto it = m_secondaryServicesEnabled.rbegin(); it != m_secondaryServicesEnabled.rend(); ++it)
		{
			auto * service = *it;

			if ( service->terminate() )
			{
				TraceSuccess{ClassId} << service->name() << " secondary service terminated gracefully !";
			}
			else
			{
				error++;

				TraceError{ClassId} << service->name() << " secondary service failed to terminate properly !";
			}

			m_resourceManager.unloadUnusedResources();
		}

		m_secondaryServicesEnabled.clear();

#ifdef VK_TRACKING

		auto vkAliveObjectCount = Vulkan::AbstractObject::s_tracking.size();

		if ( vkAliveObjectCount > 0 )
		{
			std::cerr << "[VK_TRACKING] There is " << vkAliveObjectCount << " Vulkan objects not properly destructed !" "\n";

			for ( auto & alloc : Vulkan::AbstractObject::s_tracking )
			{
				std::cerr << "[VK_TRACKING] The Vulkan object @" << alloc.first << " '" << alloc.second << "' still alive !" << "\n";
			}
		}
		else
		{
			std::cout << "[VK_TRACKING] All Vulkan objects has been released !" << "\n";
		}

#endif

		return error;
	}

	void
	Core::openFiles (const std::vector< Path::File > & filePaths) noexcept
	{
		std::vector< Path::File > appFilePaths;
		appFilePaths.reserve(filePaths.size());

		for ( const auto & filepath : filePaths )
		{
			TraceInfo{ClassId} << "Check file : " << filepath;

			// TODO : Filter files for the application.

			// TODO : If the file is a resource file, read it to complete the resource store.

			appFilePaths.emplace_back(filepath);
		}

		if ( appFilePaths.empty() )
		{
			return;
		}

		this->onOpenFiles(appFilePaths);
	}

	void
	Core::hangExecution (const std::string & cmd) noexcept
	{
		std::cout << "\n\n\n"
			"******************************************************************\n"
			"	 Execution has been hung ! Press SPACE-BAR to continue ...	\n"
			"******************************************************************\n"
			"\n\n\n";

#ifdef DEBUG
		/* Execute a command (Only in debug) */
		if ( !cmd.empty() )
		{
			system(cmd.c_str());
		}
#endif

		auto hang = true;

		while ( hang )
		{
			m_inputManager.pollSystemEvents();

			if ( glfwGetKey(m_window.handle(), GLFW_KEY_SPACE) == GLFW_PRESS )
			{
				hang = false;
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	}

	const std::string &
	Core::applicationName () const noexcept
	{
		return m_applicationName;
	}

	const Version &
	Core::applicationVersion () const noexcept
	{
		return m_applicationVersion;
	}

	const std::string &
	Core::applicationOrganization () const noexcept
	{
		return m_applicationOrganization;
	}

	const std::string &
	Core::applicationDomain () const noexcept
	{
		return m_applicationDomain;
	}

	std::string
	Core::applicationFullIdentification () const noexcept
	{
		return m_applicationOrganization + " - " + m_applicationName + " (" + to_string(m_applicationVersion) + ")";
	}

	Arguments &
	Core::arguments () noexcept
	{
		return m_arguments;
	}

	const Arguments &
	Core::arguments () const noexcept
	{
		return m_arguments;
	}

	Help &
	Core::coreHelp () noexcept
	{
		return m_coreHelp;
	}

	const Help &
	Core::coreHelp () const noexcept
	{
		return m_coreHelp;
	}

	Help &
	Core::applicationHelp () noexcept
	{
		return m_applicationHelp;
	}

	const Help &
	Core::applicationHelp () const noexcept
	{
		return m_applicationHelp;
	}

	Tracer &
	Core::tracer () noexcept
	{
		return m_tracer;
	}

	const Tracer &
	Core::tracer () const noexcept
	{
		return m_tracer;
	}

	FileSystem &
	Core::fileSystem () noexcept
	{
		return m_fileSystem;
	}

	const FileSystem &
	Core::fileSystem () const noexcept
	{
		return m_fileSystem;
	}

	Settings &
	Core::coreSettings () noexcept
	{
		return m_coreSettings;
	}

	const Settings &
	Core::coreSettings () const noexcept
	{
		return m_coreSettings;
	}

	Settings &
	Core::applicationSettings () noexcept
	{
		return m_applicationSettings;
	}

	const Settings &
	Core::applicationSettings () const noexcept
	{
		return m_applicationSettings;
	}

	Console &
	Core::console () noexcept
	{
		return m_console;
	}

	const Console &
	Core::console () const noexcept
	{
		return m_console;
	}

	NetworkManager &
	Core::networkManager () noexcept
	{
		return m_networkManager;
	}

	const NetworkManager &
	Core::networkManager () const noexcept
	{
		return m_networkManager;
	}

	Resources::Manager &
	Core::resourceManager () noexcept
	{
		return m_resourceManager;
	}

	const Resources::Manager &
	Core::resourceManager () const noexcept
	{
		return m_resourceManager;
	}

	User &
	Core::user () noexcept
	{
		return m_user;
	}

	const User &
	Core::user () const noexcept
	{
		return m_user;
	}

	PlatformManager &
	Core::platformManager () noexcept
	{
		return m_platformManager;
	}

	const PlatformManager &
	Core::platformManager () const noexcept
	{
		return m_platformManager;
	}

	Vulkan::Instance &
	Core::vulkanInstance () noexcept
	{
		return m_vulkanInstance;
	}

	const Vulkan::Instance &
	Core::vulkanInstance () const noexcept
	{
		return m_vulkanInstance;
	}

	Window &
	Core::window () noexcept
	{
		return m_window;
	}

	const Window &
	Core::window () const noexcept
	{
		return m_window;
	}

	Input::Manager &
	Core::inputManager () noexcept
	{
		return m_inputManager;
	}

	const Input::Manager &
	Core::inputManager () const noexcept
	{
		return m_inputManager;
	}

	Renderer &
	Core::graphicsRenderer () noexcept
	{
		return m_graphicsRenderer;
	}

	const Renderer &
	Core::graphicsRenderer () const noexcept
	{
		return m_graphicsRenderer;
	}

	Vulkan::TransferManager &
	Core::graphicsTransferManager () noexcept
	{
		return m_graphicsTransferManager;
	}

	const Vulkan::TransferManager &
	Core::graphicsTransferManager () const noexcept
	{
		return m_graphicsTransferManager;
	}

	Graphics::RenderableInstance::VertexBufferFormatManager &
	Core::vertexBufferFormatManager () noexcept
	{
		return m_vertexBufferFormatManager;
	}

	const Graphics::RenderableInstance::VertexBufferFormatManager &
	Core::vertexBufferFormatManager () const noexcept
	{
		return m_vertexBufferFormatManager;
	}

	ExternalInput &
	Core::videoExternalInput () noexcept
	{
		return m_videoExternalInput;
	}

	const ExternalInput &
	Core::videoExternalInput () const noexcept
	{
		return m_videoExternalInput;
	}

	Physics::Manager &
	Core::physicsManager () noexcept
	{
		return m_physicsManager;
	}

	const Physics::Manager &
	Core::physicsManager () const noexcept
	{
		return m_physicsManager;
	}

	Vulkan::TransferManager &
	Core::physicsTransferManager () noexcept
	{
		return m_physicsTransferManager;
	}

	const Vulkan::TransferManager &
	Core::physicsTransferManager () const noexcept
	{
		return m_physicsTransferManager;
	}

	const Saphir::ShaderManager &
	Core::shaderManager () const noexcept
	{
		return m_shaderManager;
	}

	Saphir::ShaderCompiler &
	Core::shaderCompiler () noexcept
	{
		return m_shaderCompiler;
	}

	const Saphir::ShaderCompiler &
	Core::shaderCompiler () const noexcept
	{
		return m_shaderCompiler;
	}

	Saphir::ShaderManager &
	Core::shaderManager () noexcept
	{
		return m_shaderManager;
	}

	Audio::Manager &
	Core::audioManager () noexcept
	{
		return m_audioManager;
	}

	const Audio::Manager &
	Core::audioManager () const noexcept
	{
		return m_audioManager;
	}

	Audio::TrackMixer &
	Core::trackMixer () noexcept
	{
		return m_trackMixer;
	}

	const Audio::TrackMixer &
	Core::trackMixer () const noexcept
	{
		return m_trackMixer;
	}

	Audio::ExternalInput &
	Core::audioExternalInput () noexcept
	{
		return m_audioExternalInput;
	}

	const Audio::ExternalInput &
	Core::audioExternalInput () const noexcept
	{
		return m_audioExternalInput;
	}

	Overlay::Manager &
	Core::overlayManager () noexcept
	{
		return m_overlayManager;
	}

	const Overlay::Manager &
	Core::overlayManager () const noexcept
	{
		return m_overlayManager;
	}

	Notifier &
	Core::notifier () noexcept
	{
		return m_notifier;
	}

	const Notifier &
	Core::notifier () const noexcept
	{
		return m_notifier;
	}

	Scenes::Manager &
	Core::sceneManager () noexcept
	{
		return m_sceneManager;
	}

	const Scenes::Manager &
	Core::sceneManager () const noexcept
	{
		return m_sceneManager;
	}

	Dev::Manager &
	Core::devManager () noexcept
	{
		return m_devManager;
	}

	const Dev::Manager &
	Core::devManager () const noexcept
	{
		return m_devManager;
	}

	Core *
	Core::instance () noexcept
	{
		return s_instance;
	}

	void
	Core::sleep (int seconds) noexcept
	{
		std::cout << "\n *** Sleeping for " << seconds << " second(s) ... *** " "\n";

		std::this_thread::sleep_for(std::chrono::seconds(seconds));

		std::cout << "\n *** Restoring execution ... *** " "\n";
	}

	bool
	Core::onKeyPress (int key, int scanCode, int modifiers, bool repeat) noexcept
	{
		/* NOTE: We don't want to do something here and for now ... */

		/* NOTE: Let the user application consume the event. */
		return this->onAppKeyPress(key, scanCode, modifiers, repeat);
	}

	bool
	Core::onKeyRelease (int key, int scanCode, int modifiers) noexcept
	{
		switch ( key )
		{
			/* Direct keys reserved by core. */
			case KeyGraveAccent :
				m_console.enable();

				return true;

			case KeyEscape :
				this->stop();

				return true;

			case KeyF1 :
				if ( KeyboardController::isModifierKeyPressed(ModKeyShift, modifiers) )
				{
					m_audioManager.play(m_switchOnSound.get());

					if ( m_sceneManager.hasActiveScene() )
					{
						std::cout << "Scene content:" "\n" << m_sceneManager.activeScene()->getStatisticsString(true, true, true, true) << '\n';
					}
					else
					{
						std::cout << "No active scene !" << '\n';
					}

					return true;
				};
				break;

			case KeyF2 :
				if ( KeyboardController::isModifierKeyPressed(ModKeyShift, modifiers) )
				{
					m_audioManager.play(m_switchOnSound.get());

					m_sceneManager.refreshScenes();

					return true;
				}
				break;

			case KeyF9 :
				if ( KeyboardController::isModifierKeyPressed(ModKeyShift, modifiers) )
				{
					Tracer::info(ClassId, "Cleaning unused resources...");

					m_audioManager.play(m_switchOnSound.get());

					auto count = m_resourceManager.unloadUnusedResources();

					TraceInfo{ClassId} << count << " resources cleaned !";

					return true;
				}
				break;

			case KeyF10 :
				if ( KeyboardController::isModifierKeyPressed(ModKeyShift, modifiers) )
				{
					Core::sleep(3);

					return true;
				}
				break;

			case KeyF12 :
				if ( KeyboardController::isModifierKeyPressed(ModKeyShift, modifiers) )
				{
					m_window.setFullscreenMode(!m_window.isFullscreenMode());

					return true;
				}
				break;

			case KeyF3 :
			case KeyF4 :
			case KeyF5 :
			case KeyF6 :
			case KeyF7 :
			case KeyF8 :
			case KeyF11 :
				if ( KeyboardController::isModifierKeyPressed(ModKeyShift, modifiers) )
				{
					Tracer::info(ClassId, "Core reserved SHIFT+Fn shortcut hit.");

					return true;
				}
				break;

			/* NOTE: Let the user application consume the event. */
			default:
				break;
		}

		return this->onAppKeyRelease(key, scanCode, modifiers);
	}

	bool
	Core::onCharacterType (unsigned int unicode, int modifiers) noexcept
	{
		/* NOTE: Let the user application consume the event. */
		return this->onAppCharacterType(unicode, modifiers);
	}

	double
	Core::lifetime () const noexcept
	{
		return m_lifetime;
	}

	size_t
	Core::cycle () const noexcept
	{
		return m_cycle;
	}

	bool
	Core::screenshot (bool depth, bool stencil) noexcept
	{
		/* Gets the capture directory. */
		const auto captures = m_fileSystem.userDataDirectory("captures");

		if ( !captures.writable() )
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
		auto directory = m_fileSystem.userDataDirectory("framebuffer-snapshots");

		if ( !directory.exists() )
		{
			if ( !directory.create() )
			{
				TraceError{ClassId} << "Unable to create the directory '" << directory << "' !";

				return false;
			}
		}
		else
		{
			if ( !directory.writable() )
			{
				TraceError{ClassId} << "Unable to write into directory '" << directory << "' !";

				return false;
			}
		}

		return true;
	}

	void
	Core::setFlag (size_t flag, bool state) noexcept
	{
		if ( flag >= 8 && flag <= 15 )
		{
			m_flags[flag] = state;
		}
	}

	bool
	Core::getFlag (size_t flag) noexcept
	{
		if ( flag <= 15 )
		{
			return m_flags[flag];
		}

		return false;
	}

	bool
	Core::onNotification (const Libraries::Observable * observable, int notificationCode, const std::any & data) noexcept
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
					this->pause();
					break;

				case Window::OSRequestsToTerminate :
					this->stop();
					break;

				case Window::Created :
				case Window::Destroyed :
				case Window::Centered :
				case Window::OSNotifiesWindowMovedTo :
				case Window::OSNotifiesWindowSizeMaximized :
				case Window::OSNotifiesWindowSizeMinimized :
				case Window::OSNotifiesWindowResized :
				case Window::OSNotifiesFramebufferResized :
				case Window::OSRequestsToRescaleContentBy :
				case Window::OSRequestsToRefreshContent :
				default :
					TraceDebug{ClassId} << "Event #" << notificationCode << " from '" << Window::ClassId << "' ignored.";
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
				case Graphics::Renderer::SwapChainRecreated :
					if ( m_sceneManager.refreshScenes() )
					{
						Tracer::success(ClassId, "Scenes graphics pipelines has been refreshed.");
					}
					else
					{
						Tracer::error(ClassId, "Unable to refresh scenes graphics pipelines !");
					}
					break;

				case Graphics::Renderer::SwapChainCreated :
				case Graphics::Renderer::SwapChainDestroyed :
				default:
					TraceDebug{ClassId} << "Receiving an event from '" << Graphics::Renderer::ClassId << "' (code:" << notificationCode << ") ...";
					break;
			}

			return true;
		}


		if ( observable == &m_trackMixer )
		{
			TraceDebug{ClassId} << "Receiving an event from '" << Audio::TrackMixer::ClassId << "' (code:" << notificationCode << ") ...";

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

		auto tools = m_arguments.get(ToolsArg, ToolsLongArg).value();

		if ( tools == VulkanInformationToolName )
		{
			Tool::ShowVulkanInformation tool{m_arguments, m_vulkanInstance};

			return tool.execute();
		}

		if ( tools == PrintGeometryToolName )
		{
			Tool::GeometryDataPrinter tool{m_arguments};

			return tool.execute();
		}

		if ( tools == ConvertGeometryToolName )
		{
			Tracer::debug(ClassId, "FIXME: ...");

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
	// NOLINTEND(*-magic-numbers)
}
