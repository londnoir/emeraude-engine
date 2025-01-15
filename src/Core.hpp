/*
 * src/Core.hpp
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

#pragma once

/* Engine configuration file. */
#include "emeraude_config.hpp"

/* STL inclusions. */
#include <cstddef>
#include <cstdint>
#include <array>
#include <vector>
#include <string>
#include <any>

/* Local inclusions for inheritances. */
#include "Input/KeyboardListenerInterface.hpp"
#include "ConsoleControllable.hpp"
#include "Libraries/ObserverTrait.hpp"
#include "Libraries/ObservableTrait.hpp"

/* Local inclusions for usages. */
#include "Identification.hpp"
#include "Help.hpp"
#include "PrimaryServices.hpp"
#include "Console.hpp"
#include "NetworkManager.hpp"
#include "User.hpp"
#include "Resources/Manager.hpp"
#include "PlatformManager.hpp"
#include "Window.hpp"
#include "Graphics/ExternalInput.hpp"
#include "Physics/Manager.hpp"
#include "Audio/Manager.hpp"
#include "Audio/TrackMixer.hpp"
#include "Audio/ExternalInput.hpp"
#include "Notifier.hpp"
#include "Scenes/Manager.hpp"
#include "Vulkan/Instance.hpp"
#include "Input/Manager.hpp"
#include "Graphics/Renderer.hpp"
#include "Overlay/Manager.hpp"

namespace Emeraude
{
	/**
	 * @brief Core object of Emeraude-Engine. One of his main role is to hold all services.
	 * @note This class act as a singleton. So you can call from everywhere with Core::instance().
	 * @extends Emeraude::Input::KeyboardListenerInterface The core need to get events from the keyboard for low level interaction.
	 * @extends Emeraude::ConsoleControllable The core can be controlled by the console.
	 * @extends Libraries::ObserverTrait The core is an observer.
	 * @extends Libraries::ObservableTrait The core is observable.
	 */
	class Core : private Input::KeyboardListenerInterface, private ConsoleControllable, public Libraries::ObserverTrait, public Libraries::ObservableTrait
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"Core"};

			/* Arguments keys */
			static constexpr auto ToolsArg{"-t"};
			static constexpr auto ToolsLongArg{"--tools-mode"};
			static constexpr auto VulkanInformationToolName{"vulkanInfo"};
			static constexpr auto PrintGeometryToolName{"printGeometry"};
			static constexpr auto ConvertGeometryToolName{"convertGeometry"};

			/** @brief Observable notification codes. */
			enum NotificationCode
			{
				ExecutionStarted,
				ExecutionPaused,
				ExecutionResumed,
				ExecutionStopped,
				/* Enumeration boundary. */
				MaxEnum
			};

			/** @brief Defines the engine startup mode. */
			enum class StartupMode : uint8_t
			{
				Error,
				ToolsMode,
				Continue
			};

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Core (const Core & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Core (Core && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			Core &operator= (const Core & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			Core &operator= (Core && copy) noexcept = delete;

			/**
			 * @brief Destructs the engine core.
			 */
			~Core () override;

			/**
			 * @brief Runs the engine main loop.
			 * @note This will call the private method Core::initializeCoreLevel(),
			 * which calls consecutively Core::onInitialize() right after
			 * the core initialization, then Core::onStart().
			 * Finally at the loop exit, this will call the private methode Core::terminate(),
			 * which call Core::onTermination().
			 * @return bool
			 */
			[[nodiscard]]
			bool run () noexcept;

			/**
			 * @brief Pauses the engine main loop.
			 * @return void
			 */
			void pause () noexcept;

			/**
			 * @brief Resumes the engine main loop.
			 * @return void
			 */
			void resume () noexcept;

			/**
			 * @brief Stops the engine. This method fire the event to stop the execution.
			 * @note Beyond this function everything will stop until full exit.
			 * This will call first Core::onStop().
			 * @return void
			 */
			void stop () noexcept;

			/**
			 * @brief Analyzes files dropped in the handle of the engine.
			 * It can be used to load Scene in JSON format for example.
			 * @param filepaths A reference to a vector of filesystem paths.
			 * @return void
			 */
			void openFiles (const std::vector< std::filesystem::path > & filepaths) noexcept;

			/**
			 * @brief This function hang the engine and executes a system command.
			 * @param command A reference to a string holding a command to execute by the system.
			 * @return void
			 */
			void hangExecution (const std::string & command) noexcept;

			/**
			 * @brief Sends a message to the notifier.
			 * @param message A reference to a string.
			 * @param duration The delay of the message staying on screen. Default 3 seconds.
			 * @return void
			 */
			void
			notifyUser (const std::string & message, uint32_t duration = Notifier::DefaultDuration) noexcept
			{
				if ( !this->notifier().push(message, duration) )
				{
					Tracer::info("DisabledNotifier", message);
				}
			}

			/**
			 * @brief Sends a message to the notifier.
			 * @param message A reference to a blob.
			 * @param duration The delay of the message staying on screen. Default 3 seconds.
			 * @return void
			 */
			void
			notifyUser (const Libraries::BlobTrait & message, uint32_t duration = Notifier::DefaultDuration) noexcept
			{
				const auto messageStr = message.get();

				if ( !this->notifier().push(messageStr, duration) )
				{
					Tracer::info(ClassId, messageStr);
				}
			}

			/**
			 * @brief Tells whether the application should only print the help.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			showHelp () const noexcept
			{
				return m_flags[ShowHelp];
			}

			/**
			 * @brief Returns the application identification structure.
			 * @return const Identification &
			 */
			[[nodiscard]]
			const Identification &
			identification () const noexcept
			{
				return m_identification;
			}

			/**
			 * @brief Returns the reference to the help service.
			 * @return const Help &
			 */
			[[nodiscard]]
			const Help &
			coreHelp () const noexcept
			{
				return m_coreHelp;
			}

			/**
			 * @brief Returns the primary services
			 * @return const PrimaryServices &
			 */
			[[nodiscard]]
			const PrimaryServices &
			primaryServices () const noexcept
			{
				return m_primaryServices;
			}

			/**
			 * @brief Returns the primary services
			 * @return const PrimaryServices &
			 */
			[[nodiscard]]
			PrimaryServices &
			primaryServices () noexcept
			{
				return m_primaryServices;
			}

			/**
			 * @brief Returns the reference to the console service.
			 * @return Console &
			 */
			[[nodiscard]]
			Console &
			console () noexcept
			{
				return m_console;
			}

			/**
			 * @brief Returns the reference to the console service.
			 * @return const Console &
			 */
			[[nodiscard]]
			const Console &
			console () const noexcept
			{
				return m_console;
			}

			/**
			 * @brief Returns the reference to the download manager service.
			 * @return NetworkManager &
			 */
			[[nodiscard]]
			NetworkManager &
			networkManager () noexcept
			{
				return m_networkManager;
			}

			/**
			 * @brief Returns the reference to the download manager service.
			 * @return const NetworkManager &
			 */
			[[nodiscard]]
			const NetworkManager &
			networkManager () const noexcept
			{
				return m_networkManager;
			}

			/**
			 * @brief Returns the reference to the resource manager service.
			 * @return Resources::Manager &
			 */
			[[nodiscard]]
			Resources::Manager &
			resourceManager () noexcept
			{
				return m_resourceManager;
			}

			/**
			 * @brief Returns the reference to the resource manager service.
			 * @return const Resources::Manager &
			 */
			[[nodiscard]]
			const Resources::Manager &
			resourceManager () const noexcept
			{
				return m_resourceManager;
			}

			/**
			 * @brief Returns the reference to the user service.
			 * @return User &
			 */
			[[nodiscard]]
			User &
			user () noexcept
			{
				return m_user;
			}

			/**
			 * @brief Returns the reference to the user service.
			 * @return const User &
			 */
			[[nodiscard]]
			const User &
			user () const noexcept
			{
				return m_user;
			}

			/**
			 * @brief Returns the reference to the platform manager service.
			 * @return PlatformManager &
			 */
			[[nodiscard]]
			PlatformManager &
			platformManager () noexcept
			{
				return m_platformManager;
			}

			/**
			 * @brief Returns the reference to the platform manager service.
			 * @return const PlatformManager &
			 */
			[[nodiscard]]
			const PlatformManager &
			platformManager () const noexcept
			{
				return m_platformManager;
			}

			/**
			 * @brief Returns the reference to the Vulkan instance service.
			 * @return Instance &
			 */
			[[nodiscard]]
			Vulkan::Instance &
			vulkanInstance () noexcept
			{
				return m_vulkanInstance;
			}

			/**
			 * @brief Returns the reference to the Vulkan instance service.
			 * @return const Instance &
			 */
			[[nodiscard]]
			const Vulkan::Instance &
			vulkanInstance () const noexcept
			{
				return m_vulkanInstance;
			}

			/**
			 * @brief Returns the reference to the handle service.
			 * @return Window &
			 */
			[[nodiscard]]
			Window &
			window () noexcept
			{
				return m_window;
			}

			/**
			 * @brief Returns the reference to the handle service.
			 * @return const Window &
			 */
			[[nodiscard]]
			const Window &
			window () const noexcept
			{
				return m_window;
			}

			/**
			 * @brief Returns the reference to the input manager service.
			 * @return Manager &
			 */
			[[nodiscard]]
			Input::Manager &
			inputManager () noexcept
			{
				return m_inputManager;
			}

			/**
			 * @brief Returns the reference to the input manager service.
			 * @return const Manager &
			 */
			[[nodiscard]]
			const Input::Manager &
			inputManager () const noexcept
			{
				return m_inputManager;
			}

			/**
			 * @brief Returns the reference to the graphics renderer service.
			 * @return Graphics::Renderer &
			 */
			[[nodiscard]]
			Graphics::Renderer &
			graphicsRenderer () noexcept
			{
				return m_graphicsRenderer;
			}

			/**
			 * @brief Returns the reference to the graphics renderer service.
			 * @return const Graphics::Renderer &
			 */
			[[nodiscard]]
			const Graphics::Renderer &
			graphicsRenderer () const noexcept
			{
				return m_graphicsRenderer;
			}

			/**
			 * @brief Returns the reference to the video external input service.
			 * @return Graphics::ExternalInput &
			 */
			[[nodiscard]]
			Graphics::ExternalInput &
			videoExternalInput () noexcept
			{
				return m_videoExternalInput;
			}

			/**
			 * @brief Returns the reference to the video external input service.
			 * @return const Graphics::ExternalInput &
			 */
			[[nodiscard]]
			const Graphics::ExternalInput &
			videoExternalInput () const noexcept
			{
				return m_videoExternalInput;
			}

			/**
			 * @brief Returns the reference to the physics manager service.
			 * @return Physics::Manager &
			 */
			[[nodiscard]]
			Physics::Manager &
			physicsManager () noexcept
			{
				return m_physicsManager;
			}

			/**
			 * @brief Returns the reference to the physics manager service.
			 * @return const Physics::Manager &
			 */
			[[nodiscard]]
			const Physics::Manager &
			physicsManager () const noexcept
			{
				return m_physicsManager;
			}

			/**
			 * @brief Returns the reference to the audio manager service.
			 * @return Audio::Manager &
			 */
			[[nodiscard]]
			Audio::Manager &
			audioManager () noexcept
			{
				return m_audioManager;
			}

			/**
			 * @brief Returns the reference to the audio manager service.
			 * @return const Audio::Manager &
			 */
			[[nodiscard]]
			const Audio::Manager &
			audioManager () const noexcept
			{
				return m_audioManager;
			}

			/**
			 * @brief Returns the reference to the track mixer service.
			 * @return Audio::TrackMixer &
			 */
			[[nodiscard]]
			Audio::TrackMixer &
			trackMixer () noexcept
			{
				return m_trackMixer;
			}

			/**
			 * @brief Returns the reference to the track mixer service.
			 * @return const Audio::TrackMixer &
			 */
			[[nodiscard]]
			const Audio::TrackMixer &
			trackMixer () const noexcept
			{
				return m_trackMixer;
			}

			/**
			 * @brief Returns the reference to the audio external input service.
			 * @return Audio::ExternalInput &
			 */
			[[nodiscard]]
			Audio::ExternalInput &
			audioExternalInput () noexcept
			{
				return m_audioExternalInput;
			}

			/**
			 * @brief Returns the reference to the audio external input service.
			 * @return const Audio::ExternalInput &
			 */
			[[nodiscard]]
			const Audio::ExternalInput &
			audioExternalInput () const noexcept
			{
				return m_audioExternalInput;
			}

			/**
			 * @brief Returns the reference to the overlay manager service.
			 * @return Overlay::Manager &
			 */
			[[nodiscard]]
			Overlay::Manager &
			overlayManager () noexcept
			{
				return m_overlayManager;
			}

			/**
			 * @brief Returns the reference to the overlay manager service.
			 * @return const Overlay::Manager &
			 */
			[[nodiscard]]
			const Overlay::Manager &
			overlayManager () const noexcept
			{
				return m_overlayManager;
			}

			/**
			 * @brief Returns the reference to the notifier service.
			 * @return Notifier &
			 */
			[[nodiscard]]
			Notifier &
			notifier () noexcept
			{
				return m_notifier;
			}

			/**
			 * @brief Returns the reference to the notifier service.
			 * @return const Notifier &
			 */
			[[nodiscard]]
			const Notifier &
			notifier () const noexcept
			{
				return m_notifier;
			}

			/**
			 * @brief Returns the reference to the scene manager service.
			 * @return Scenes::Manager &
			 */
			[[nodiscard]]
			Scenes::Manager &
			sceneManager () noexcept
			{
				return m_sceneManager;
			}

			/**
			 * @brief Returns the reference to the scene manager service.
			 * @return const Scenes::Manager &
			 */
			[[nodiscard]]
			const Scenes::Manager &
			sceneManager () const noexcept
			{
				return m_sceneManager;
			}

			/**
			 * @brief Returns the Core singleton.
			 * @return Core *
			 */
			[[nodiscard]]
			static
			Core *
			instance () noexcept
			{
				return s_instance;
			}

		protected:

#if IS_WINDOWS
	        /**
             * @brief Constructs the engine core.
             * @param argc The argument count from the standard C/C++ main() function.
             * @param wargv The argument values from the standard C/C++ main() function.
             * @param applicationName The name of the application using the engine. Default "UnknownApplication".
             * @param applicationVersion A reference to a version of the application. Default 0.0.0.
             * @param applicationOrganization The name of the application organization. Default "UnknownOrganization".
             * @param applicationDomain The domain of the application. Default "unknown.org".
             */
	        Core (int argc, wchar_t * * wargv, const char * applicationName = "UnknownApplication", const Libraries::Version & applicationVersion = {0, 0, 0}, const char * applicationOrganization = "UnknownOrganization", const char * applicationDomain = "unknown.org") noexcept;
#else
			/**
			 * @brief Constructs the engine core.
			 * @param argc The argument count from the standard C/C++ main() function.
			 * @param argv The argument values from the standard C/C++ main() function.
			 * @param applicationName The name of the application using the engine. Default "UnknownApplication".
			 * @param applicationVersion A reference to a version of the application. Default 0.0.0.
			 * @param applicationOrganization The name of the application organization. Default "UnknownOrganization".
			 * @param applicationDomain The domain of the application. Default "localhost".
			 */
			Core (int argc, char * * argv, const char * applicationName = "UnknownApplication", const Libraries::Version & applicationVersion = {0, 0, 0}, const char * applicationOrganization = "UnknownOrganization", const char * applicationDomain = "localhost") noexcept;
#endif

			/**
			 * @brief Returns the execution time of the engine in microseconds.
			 * @return uint64_t
			 */
			[[nodiscard]]
			uint64_t
			lifetime () const noexcept
			{
				return m_lifetime;
			}

			/**
			 * @brief Returns the number of cycles executed by the engine.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			cycle () const noexcept
			{
				return m_cycle;
			}

			/**
			 * @brief Takes a screenshot and save it to captures folder of the current OS user.
			 * @param depth a boolean to capture Z-Depth in an aside file. Default is false.
			 * @param stencil a boolean to capture stencil in an aside file. Default is false.
			 * @return bool
			 */
			bool screenshot (bool depth = false, bool stencil = false) noexcept;

			/**
			 * @brief Returns a captures of every framebuffer.
			 * @return bool
			 */
			[[nodiscard]]
			bool dumpFramebuffer () const noexcept;

			/**
			 * @brief Sets a flag value for user application.
			 * @param flag The flag. Must be between 8 and 15.
			 * @param state The state.
			 */
			void
			setFlag (size_t flag, bool state) noexcept
			{
				if ( flag >= 8 && flag <= 15 )
				{
					m_flags[flag] = state;
				}
			}

			/**
			 * @brief Returns a flags value.
			 * @param flag The flag. Can be from 0 to 15.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			getFlag (size_t flag) const noexcept
			{
				if ( flag <= 15 )
				{
					return m_flags[flag];
				}

				return false;
			}

		private:

			/** @copydoc Emeraude::Input::KeyboardListenerInterface::onKeyPress() */
			bool onKeyPress (int32_t key, int32_t scancode, int32_t modifiers, bool repeat) noexcept final;

			/** @copydoc Emeraude::Input::KeyboardListenerInterface::onKeyRelease() */
			bool onKeyRelease (int32_t key, int32_t scancode, int32_t modifiers) noexcept final;

			/** @copydoc Emeraude::Input::KeyboardListenerInterface::onCharacterType() */
			bool onCharacterType (uint32_t unicode) noexcept final;

			/** @copydoc Libraries::ObserverTrait::onNotification() */
			[[nodiscard]]
			bool onNotification (const Libraries::ObservableTrait * observable, int notificationCode, const std::any & data) noexcept final;

			/**
			 * @brief Called in every main loop cycle.
			 * @return void
			 */
			virtual void onMainLoopCycle () const noexcept;

			/**
			 * @brief Initializes the core level of the engine.
			 * @details After that function, the graphics render, the audio manager and
			 * the input manager will be available.
			 * If this method returns false, the engine won't execute.
			 * @return bool
			 */
			bool initializeCoreLevel () noexcept;

			/**
			 * @brief Initializes the core screen.
			 * @return bool
			 */
			bool initializeCoreScreen () noexcept;

			/**
			 * @brief Performs the logics task.
			 * @return void
			 */
			void logicsTask () noexcept;

			/**
			 * @brief Performs the rendering task.
			 * @return void
			 */
			void renderingTask () noexcept;

			/**
			 * @brief Terminates the engine execution.
			 * @return unsigned int
			 */
			unsigned int terminate () noexcept;

			/**
			 * @brief Executes a special mode with the engine.
			 * @return bool
			 */
			bool executeToolsMode () noexcept;

			/**
			 * @brief showStatistics
			 * @param elapsedTime
			 * @return void
			 */
			void showStatistics (double elapsedTime) const noexcept;

			/**
			 * @brief Checks for message to display in a dialog.
			 * @return void
			 */
			void checkForDialogMessages () noexcept;

			/**
			 * @brief Overridable event when a shader fails to compile.
			 * @param shaderIdentifier A reference to a string.
			 * @param sourceCode A reference to a string.
			 * @return void
			 */
			virtual
			void
			onShaderCompilationFailed (const std::string & shaderIdentifier, const std::string & sourceCode) noexcept
			{
				this->notifyUser(Libraries::BlobTrait{} << "Shader '" << shaderIdentifier << "' compilation failed !");

				m_messages.emplace(sourceCode);
			}

			/**
			 * @brief Called before the initialization of secondary services. This is the moment to show application information without starting.
			 * @note If the method return "true", the application will stop.
			 * @param arguments A reference to the arguments.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool readArgumentsBeforeInitialization (const Arguments & arguments) noexcept = 0;

			/**
			 * @brief Called before entering the main loop. All Services are available at this point.
			 * @note If this function return false, the main loop won't execute.
			 * @return bool
			 */
			virtual bool onStart () noexcept = 0;

			/**
			 * @brief Called in every logics processing cycle.
			 * @warning This come from a different thread.
			 * @param engineCycle The current engine cycle number.
			 * @return void
			 */
			virtual void onProcessLogics (size_t engineCycle) noexcept = 0;

			/**
			 * @brief Called when the core engine is paused.
			 * @return void
			 */
			virtual void onPause () noexcept = 0;

			/**
			 * @brief Called when the core engine is resumed.
			 * @return void
			 */
			virtual void onResume () noexcept = 0;

			/**
			 * @brief Called before exiting the main loop.
			 * @note This is the moment to stop all pending action.
			 * @return void
			 */
			virtual void onStop () noexcept = 0;

			/**
			 * @brief Event sent to the application when a key is pressed.
			 * @note The Core has priority on these events.
			 * @param key The keyboard universal key code. I.e, QWERTY keyboard 'A' key gives the ASCII code '65' on all platform.
			 * @param scancode The OS dependent scancode.
			 * @param modifiers The modifier keys mask.
			 * @param repeat Indicate if the key is repeated.
			 * @return bool
			 */
			virtual bool onAppKeyPress (int32_t key, int32_t scancode, int32_t modifiers, bool repeat) noexcept = 0;

			/**
			 * @brief Event sent to the application when a key is released.
			 * @note The Core has priority on these events.
			 * @param key The keyboard universal key code. I.e, QWERTY keyboard 'A' key gives the ASCII code '65' on all platform.
			 * @param scancode The OS dependent scancode.
			 * @param modifiers The modifier keys mask.
			 * @return bool
			 */
			virtual bool onAppKeyRelease (int32_t key, int32_t scancode, int32_t modifiers) noexcept = 0;

			/**
			 * @brief Event sent to the application when a Unicode char is typed.
			 * @note The Core has priority on these events.
			 * @param unicode The Unicode.
			 * @return bool
			 */
			virtual bool onAppCharacterType (uint32_t unicode) noexcept = 0;

			/**
			 * @brief Called when a notification is not handled by the core engine.
			 * @note If this function return false, the observer will be automatically detached.
			 * @param observable The observable responsible for the notification.
			 * @param notificationCode Code of notification.
			 * @param data Pointer to possible data.
			 * @return bool
			 */
			virtual bool onAppNotification (const Libraries::ObservableTrait * observable, int notificationCode, const std::any & data) noexcept = 0;

			/**
			 * @brief Called when files has been loaded.
			 * @param filepaths A reference to a vector of filesystem paths.
			 * @return void
			 */
			virtual void onOpenFiles (const std::vector< std::filesystem::path > & filepaths) noexcept = 0;

			/* Flag names */
			static constexpr auto IsMainLoopRunning{0UL};
			static constexpr auto IsLogicsLoopRunning{1UL};
			static constexpr auto IsRenderingLoopRunning{2UL};
			static constexpr auto Pausable{3UL};
			static constexpr auto Paused{4UL};
			static constexpr auto ShowHelp{5UL};

			static Core * s_instance;

			Identification m_identification;
			Help m_coreHelp{"Core engine"};
			PrimaryServices m_primaryServices;
			Console m_console{m_primaryServices, m_inputManager, m_overlayManager};
			NetworkManager m_networkManager{m_primaryServices};
			Resources::Manager m_resourceManager{m_primaryServices, m_networkManager};
			User m_user{m_primaryServices};
			PlatformManager m_platformManager{m_primaryServices};
			Vulkan::Instance m_vulkanInstance{m_primaryServices};
			Window m_window{m_primaryServices, m_vulkanInstance, m_identification};
			Input::Manager m_inputManager{m_primaryServices, m_window};
			Graphics::Renderer m_graphicsRenderer{m_primaryServices, m_vulkanInstance, m_window};
			Graphics::ExternalInput m_videoExternalInput;
			Physics::Manager m_physicsManager{m_primaryServices, m_vulkanInstance};
			Audio::Manager m_audioManager{m_primaryServices, m_resourceManager};
			Audio::TrackMixer m_trackMixer{m_primaryServices, m_resourceManager, m_audioManager};
			Audio::ExternalInput m_audioExternalInput{m_primaryServices};
			Overlay::Manager m_overlayManager{m_primaryServices, m_window, m_graphicsRenderer};
			Notifier m_notifier{m_overlayManager};
			Scenes::Manager m_sceneManager{m_primaryServices, m_resourceManager, m_graphicsRenderer, m_audioManager};
			std::vector< ServiceInterface * > m_primaryServicesEnabled;
			std::vector< ServiceInterface * > m_secondaryServicesEnabled;
			std::thread m_logicsThread;
			std::thread m_renderingThread;
			uint64_t m_lifetime{0};
			size_t m_cycle{0};
			StartupMode m_startupMode{StartupMode::Continue};
			/* TODO: Set messages in ImGUI. */
			std::queue< std::string > m_messages;
			std::array< bool, 16 > m_flags{
				true/*IsMainLoopRunning*/,
				true/*IsLogicsLoopRunning*/,
				true/*IsRenderingLoopRunning*/,
				false/*Pausable*/,
				false/*Paused*/,
				false/*ShowHelp*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				/* Flags for user application. */
				false/*RESERVED*/,
				false/*RESERVED*/,
				false/*RESERVED*/,
				false/*RESERVED*/,
				false/*RESERVED*/,
				false/*RESERVED*/,
				false/*RESERVED*/,
				false/*RESERVED*/,
			};
	};
}
