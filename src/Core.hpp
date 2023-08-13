/*
 * Emeraude/Core.hpp
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
#include <array>
#include <functional>
#include <memory>
#include <string>
#include <vector>

/* Local inclusions for inheritances. */
#include "Input/KeyboardListenerInterface.hpp"
#include "ConsoleControllable.hpp"
#include "Observable.hpp"
#include "Observer.hpp"
#include "Time/TimedEventsInterface.hpp"

/* Local inclusions for usages. */
#include "Path/File.hpp"
#include "Version.hpp"
#include "emeraude_config.hpp"

/* Services */
#include "Arguments.hpp"
#include "Audio/ExternalInput.hpp"
#include "Audio/Manager.hpp"
#include "Audio/TrackMixer.hpp"
#include "Console.hpp"
#include "Dev/Manager.hpp"
#include "FileSystem.hpp"
#include "Graphics/ExternalInput.hpp"
#include "Graphics/RenderableInstance/VertexBufferFormatManager.hpp"
#include "Graphics/Renderer.hpp"
#include "Help.hpp"
#include "Input/Manager.hpp"
#include "NetworkManager.hpp"
#include "Notifier.hpp"
#include "Overlay/Manager.hpp"
#include "Physics/Manager.hpp"
#include "PlatformManager.hpp"
#include "Resources/Manager.hpp"
#include "Saphir/ShaderCompiler.hpp"
#include "Saphir/ShaderManager.hpp"
#include "Scenes/Manager.hpp"
#include "Settings.hpp"
#include "Tracer.hpp"
#include "User.hpp"
#include "Vulkan/Instance.hpp"
#include "Vulkan/TransferManager.hpp"
#include "Window.hpp"

namespace Emeraude
{
	/**
	 * @brief Core object of Emeraude-Engine. One of his main role is to hold all services.
	 * @note This class act as a singleton. So you can call from everywhere with Core::instance().
	 * @extends Emeraude::Input::KeyboardListenerInterface The core need to get events from the keyboard for low level interaction.
	 * @extends Emeraude::ConsoleControllable The core can be controlled by the console.
	 * @extends Libraries::Time::TimedEventsInterface The core manage the time of the engine.
	 * @extends Libraries::Observer The core is an observer.
	 * @extends Libraries::Observable The core is observable.
	 */
	class Core : private Input::KeyboardListenerInterface, private ConsoleControllable, private Libraries::Time::TimedEventsInterface, public Libraries::Observer, public Libraries::Observable
	{
		public:

			static constexpr auto LibraryOrganizationName = "londnoir@gmail.com";
			static constexpr auto LibraryName = ENGINE_NAME;
			static constexpr auto LibraryVersion = Libraries::Version(ENGINE_VERSION_MAJOR, ENGINE_VERSION_MINOR, ENGINE_VERSION_PATCH);
			static constexpr auto LibraryPlatform = PLATFORM_TARGETED;
			#ifdef __clang__
			#pragma clang diagnostic ignored "-Wdate-time"
			#endif
			static constexpr auto LibraryCompilationDate = __DATE__;

			/* Arguments keys */
			static constexpr auto ToolsArg = "-t";
			static constexpr auto ToolsLongArg = "--tools-mode";
			static constexpr auto VulkanInformationToolName = "vulkanInfo";
			static constexpr auto PrintGeometryToolName = "printGeometry";
			static constexpr auto ConvertGeometryToolName = "convertGeometry";

			/** @brief Class identifier. */
			static constexpr auto ClassId{"Core"};

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
			enum class StartupMode: int
			{
				Error,
				ToolsMode,
				ShowHelp,
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
			Core & operator= (const Core & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			Core & operator= (Core && copy) noexcept = delete;

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
			virtual bool run () noexcept final;

			/**
			 * @brief Pauses the engine main loop.
			 * @return void
			 */
			virtual void pause () noexcept final;

			/**
			 * @brief Resumes the engine main loop.
			 * @return void
			 */
			virtual void resume () noexcept final;

			/**
			 * @brief Stops the engine. This method fire the event to stop the execution.
			 * @note Beyond this function everything will stop until full exit.
			 * This will call first Core::onStop().
			 * @return void
			 */
			virtual void stop () noexcept final;

			/**
			 * @brief Analyzes files dropped in the handle of the engine.
			 * It can be used to load Scene in JSON format for example.
			 * @param filePaths A reference to a vector of file paths.
			 * @return void
			 */
			virtual void openFiles (const std::vector< Libraries::Path::File > & filePaths) noexcept final;

			/**
			 * @brief This function hang the engine and executes a system command.
			 * @param command A reference to a string holding a command to execute by the system.
			 * @return void
			 */
			virtual void hangExecution (const std::string & command) noexcept final;

			/**
			 * @brief Returns the application name.
			 * @return const string &
			 */
			[[nodiscard]]
			virtual const std::string & applicationName () const noexcept final;

			/**
			 * @brief Returns the application version.
			 * @return const Libraries::Version &
			 */
			[[nodiscard]]
			virtual const Libraries::Version & applicationVersion () const noexcept final;

			/**
			 * @brief Returns the application organization name.
			 * @return const std::string &
			 */
			[[nodiscard]]
			virtual const std::string & applicationOrganization () const noexcept final;

			/**
			 * @brief Returns the application domain.
			 * @return const std::string &
			 */
			[[nodiscard]]
			virtual const std::string & applicationDomain () const noexcept final;

			/**
			 * @brief Returns the application identification.
			 * @return std::string
			 */
			[[nodiscard]]
			virtual std::string applicationFullIdentification () const noexcept final;

			//<editor-fold desc="Services">

			/**
			 * @brief Returns the reference to the arguments service.
			 * @return Arguments &
			 */
			[[nodiscard]]
			virtual Arguments & arguments () noexcept final;

			/**
			 * @brief Returns the reference to the arguments service.
			 * @return const Arguments &
			 */
			[[nodiscard]]
			virtual const Arguments & arguments () const noexcept final;

			/**
			 * @brief Returns the reference to the core help service.
			 * @return Help &
			 */
			[[nodiscard]]
			virtual Help & coreHelp () noexcept final;

			/**
			 * @brief Returns the reference to the core help service.
			 * @return const Help &
			 */
			[[nodiscard]]
			virtual const Help & coreHelp () const noexcept final;

			/**
			 * @brief Returns the reference to the application help service.
			 * @return Help &
			 */
			[[nodiscard]]
			virtual Help & applicationHelp () noexcept final;

			/**
			 * @brief Returns the reference to the application help service.
			 * @return const Help &
			 */
			[[nodiscard]]
			virtual const Help & applicationHelp () const noexcept final;

			/**
			 * @brief Returns the reference to the tracer service.
			 * @return Tracer &
			 */
			[[nodiscard]]
			virtual Tracer & tracer () noexcept final;

			/**
			 * @brief Returns the reference to the tracer service.
			 * @return const Tracer &
			 */
			[[nodiscard]]
			virtual const Tracer & tracer () const noexcept final;

			/**
			 * @brief Returns the reference to the file system service.
			 * @return FileSystem &
			 */
			[[nodiscard]]
			virtual FileSystem & fileSystem () noexcept final;

			/**
			 * @brief Returns the reference to the file system service.
			 * @return const FileSystem &
			 */
			[[nodiscard]]
			virtual const FileSystem & fileSystem () const noexcept final;

			/**
			 * @brief Returns the reference to the core settings service.
			 * @return Settings &
			 */
			[[nodiscard]]
			virtual Settings & coreSettings () noexcept final;

			/**
			 * @brief Returns the reference to the core settings service.
			 * @return const Settings &
			 */
			[[nodiscard]]
			virtual const Settings & coreSettings () const noexcept final;

			/**
			 * @brief Returns the reference to the application settings service.
			 * @return Settings &
			 */
			[[nodiscard]]
			virtual Settings & applicationSettings () noexcept final;

			/**
			 * @brief Returns the reference to the application settings service.
			 * @return const Settings &
			 */
			[[nodiscard]]
			virtual const Settings & applicationSettings () const noexcept final;

			/**
			 * @brief Returns the reference to the console service.
			 * @return Console &
			 */
			[[nodiscard]]
			virtual Console & console () noexcept final;

			/**
			 * @brief Returns the reference to the console service.
			 * @return const Console &
			 */
			[[nodiscard]]
			virtual const Console & console () const noexcept final;

			/**
			 * @brief Returns the reference to the download manager service.
			 * @return NetworkManager &
			 */
			[[nodiscard]]
			virtual NetworkManager & networkManager () noexcept final;

			/**
			 * @brief Returns the reference to the download manager service.
			 * @return const NetworkManager &
			 */
			[[nodiscard]]
			virtual const NetworkManager & networkManager () const noexcept final;

			/**
			 * @brief Returns the reference to the resource manager service.
			 * @return Resources::Manager &
			 */
			[[nodiscard]]
			virtual Resources::Manager & resourceManager () noexcept final;

			/**
			 * @brief Returns the reference to the resource manager service.
			 * @return const Resources::Manager &
			 */
			[[nodiscard]]
			virtual const Resources::Manager & resourceManager () const noexcept final;

			/**
			 * @brief Returns the reference to the user service.
			 * @return User &
			 */
			[[nodiscard]]
			virtual User & user () noexcept final;

			/**
			 * @brief Returns the reference to the user service.
			 * @return const User &
			 */
			[[nodiscard]]
			virtual const User & user () const noexcept final;

			/**
			 * @brief Returns the reference to the platform manager service.
			 * @return PlatformManager &
			 */
			[[nodiscard]]
			virtual PlatformManager & platformManager () noexcept final;

			/**
			 * @brief Returns the reference to the platform manager service.
			 * @return const PlatformManager &
			 */
			[[nodiscard]]
			virtual const PlatformManager & platformManager () const noexcept final;

			/**
			 * @brief Returns the reference to the Vulkan instance service.
			 * @return Instance &
			 */
			[[nodiscard]]
			virtual Vulkan::Instance & vulkanInstance () noexcept final;

			/**
			 * @brief Returns the reference to the Vulkan instance service.
			 * @return const Instance &
			 */
			[[nodiscard]]
			virtual const Vulkan::Instance & vulkanInstance () const noexcept final;

			/**
			 * @brief Returns the reference to the handle service.
			 * @return Window &
			 */
			[[nodiscard]]
			virtual Window & window () noexcept final;

			/**
			 * @brief Returns the reference to the handle service.
			 * @return const Window &
			 */
			[[nodiscard]]
			virtual const Window & window () const noexcept final;

			/**
			 * @brief Returns the reference to the input manager service.
			 * @return Manager &
			 */
			[[nodiscard]]
			virtual Input::Manager & inputManager () noexcept final;

			/**
			 * @brief Returns the reference to the input manager service.
			 * @return const Manager &
			 */
			[[nodiscard]]
			virtual const Input::Manager & inputManager () const noexcept final;

			/**
			 * @brief Returns the reference to the graphics renderer service.
			 * @return Graphics::Renderer &
			 */
			[[nodiscard]]
			virtual Graphics::Renderer & graphicsRenderer () noexcept final;

			/**
			 * @brief Returns the reference to the graphics renderer service.
			 * @return const Graphics::Renderer &
			 */
			[[nodiscard]]
			virtual const Graphics::Renderer & graphicsRenderer () const noexcept final;

			/**
			 * @brief Returns the reference to the graphics transfer manager.
			 * @return Vulkan::TransferManager &
			 */
			[[nodiscard]]
			virtual Vulkan::TransferManager & graphicsTransferManager () noexcept final;

			/**
			 * @brief Returns the reference to the graphics transfer manager.
			 * @return const Vulkan::TransferManager &
			 */
			[[nodiscard]]
			virtual const Vulkan::TransferManager & graphicsTransferManager () const noexcept final;

			/**
			 * @brief Returns the reference to the vertex buffer format manager service.
			 * @return Graphics::RenderableInstance::VertexBufferFormatManager &
			 */
			[[nodiscard]]
			virtual Graphics::RenderableInstance::VertexBufferFormatManager & vertexBufferFormatManager () noexcept final;

			/**
			 * @brief Returns the reference to the vertex buffer format manager service.
			 * @return const Graphics::RenderableInstance::VertexBufferFormatManager &
			 */
			[[nodiscard]]
			virtual const Graphics::RenderableInstance::VertexBufferFormatManager & vertexBufferFormatManager () const noexcept final;

			/**
			 * @brief Returns the reference to the video external input service.
			 * @return Graphics::ExternalInput &
			 */
			[[nodiscard]]
			virtual Graphics::ExternalInput & videoExternalInput () noexcept final;

			/**
			 * @brief Returns the reference to the video external input service.
			 * @return const Graphics::ExternalInput &
			 */
			[[nodiscard]]
			virtual const Graphics::ExternalInput & videoExternalInput () const noexcept final;

			/**
			 * @brief Returns the reference to the physics manager service.
			 * @return Physics::Manager &
			 */
			[[nodiscard]]
			virtual Physics::Manager & physicsManager () noexcept final;

			/**
			 * @brief Returns the reference to the physics manager service.
			 * @return const Physics::Manager &
			 */
			[[nodiscard]]
			virtual const Physics::Manager & physicsManager () const noexcept final;

			/**
			 * @brief Returns the reference to the physics transfer manager.
			 * @return Vulkan::TransferManager &
			 */
			[[nodiscard]]
			virtual Vulkan::TransferManager & physicsTransferManager () noexcept final;

			/**
			 * @brief Returns the reference to the physics transfer manager.
			 * @return const Vulkan::TransferManager &
			 */
			[[nodiscard]]
			virtual const Vulkan::TransferManager & physicsTransferManager () const noexcept final;

			/**
			 * @brief Returns the reference to the shader compiler service.
			 * @return ShaderCompiler &
			 */
			[[nodiscard]]
			virtual Saphir::ShaderCompiler & shaderCompiler () noexcept final;

			/**
			 * @brief Returns the reference to the shader compiler service.
			 * @return const ShaderCompiler &
			 */
			[[nodiscard]]
			virtual const Saphir::ShaderCompiler & shaderCompiler () const noexcept final;

			/**
			 * @brief Returns the reference to the shader manager service.
			 * @return ShaderManager &
			 */
			[[nodiscard]]
			virtual Saphir::ShaderManager & shaderManager () noexcept final;

			/**
			 * @brief Returns the reference to the shader manager service.
			 * @return const ShaderManager &
			 */
			[[nodiscard]]
			virtual const Saphir::ShaderManager & shaderManager () const noexcept final;

			/**
			 * @brief Returns the reference to the audio manager service.
			 * @return Audio::Manager &
			 */
			[[nodiscard]]
			virtual Audio::Manager & audioManager () noexcept final;

			/**
			 * @brief Returns the reference to the audio manager service.
			 * @return const Audio::Manager &
			 */
			[[nodiscard]]
			virtual const Audio::Manager & audioManager () const noexcept final;

			/**
			 * @brief Returns the reference to the track mixer service.
			 * @return TrackMixer &
			 */
			[[nodiscard]]
			virtual Audio::TrackMixer & trackMixer () noexcept final;

			/**
			 * @brief Returns the reference to the track mixer service.
			 * @return const TrackMixer &
			 */
			[[nodiscard]]
			virtual const Audio::TrackMixer & trackMixer () const noexcept final;

			/**
			 * @brief Returns the reference to the audio external input service.
			 * @return ExternalInput &
			 */
			[[nodiscard]]
			virtual Audio::ExternalInput & audioExternalInput () noexcept final;

			/**
			 * @brief Returns the reference to the audio external input service.
			 * @return const ExternalInput &
			 */
			[[nodiscard]]
			virtual const Audio::ExternalInput & audioExternalInput () const noexcept final;

			/**
			 * @brief Returns the reference to the overlay manager service.
			 * @return Manager &
			 */
			[[nodiscard]]
			virtual Overlay::Manager & overlayManager () noexcept final;

			/**
			 * @brief Returns the reference to the overlay manager service.
			 * @return const Manager &
			 */
			[[nodiscard]]
			virtual const Overlay::Manager & overlayManager () const noexcept final;

			/**
			 * @brief Returns the reference to the notifier service.
			 * @return Notifier &
			 */
			[[nodiscard]]
			virtual Notifier & notifier () noexcept final;

			/**
			 * @brief Returns the reference to the notifier service.
			 * @return const Notifier &
			 */
			[[nodiscard]]
			virtual const Notifier & notifier () const noexcept final;

			/**
			 * @brief Returns the reference to the scene manager service.
			 * @return Manager &
			 */
			[[nodiscard]]
			virtual Scenes::Manager & sceneManager () noexcept final;

			/**
			 * @brief Returns the reference to the scene manager service.
			 * @return const Manager &
			 */
			[[nodiscard]]
			virtual const Scenes::Manager & sceneManager () const noexcept final;

			/**
			 * @brief Returns the reference to the dev manager service.
			 * @return Manager &
			 */
			[[nodiscard]]
			virtual Dev::Manager & devManager () noexcept final;

			/**
			 * @brief Returns the reference to the dev manager service.
			 * @return const Manager &
			 */
			[[nodiscard]]
			virtual const Dev::Manager & devManager () const noexcept final;

			//</editor-fold>

			/**
			 * @brief Returns the Core singleton.
			 * @return Core *
			 */
			[[nodiscard]]
			static Core * instance () noexcept;

			/**
			 * @brief Pauses execution for n seconds.
			 * @note Debug purpose only.
			 * @param seconds The number of seconds to wait.
			 */
			static void sleep (int seconds) noexcept;

		protected:

			/**
			 * @brief Constructs the engine core.
			 * @param argc The number of arguments from the command line.
			 * @param argv The value of arguments from the command line.
			 * @param applicationName The name of the application using the engine. Default "UnknownApplication".
			 * @param applicationVersion A reference to a version of the application. Default 0.0.0.
			 * @param applicationOrganization The name of the application organization. Default "UnknownOrganization".
			 * @param applicationDomain The domain of the application. Default "localhost".
			 */
			explicit Core (int argc = 0, const char * argv[] = nullptr, const char * applicationName = "UnknownApplication", const Libraries::Version & applicationVersion = {0, 0, 0}, const char * applicationOrganization = "UnknownOrganization", const char * applicationDomain = "localhost") noexcept;

			/**
			 * @brief Returns the execution time of the engine in milliseconds.
			 * @return double
			 */
			[[nodiscard]]
			virtual double lifetime () const noexcept final;

			/**
			 * @brief Returns the number of cycles executed by the engine.
			 * @return size_t
			 */
			[[nodiscard]]
			virtual size_t cycle () const noexcept final;

			/**
			 * @brief Takes a screenshot and save it to captures folder of the current OS user.
			 * @param depth a boolean to capture Z-Depth in a aside file. Default is false.
			 * @param stencil a boolean to capture stencil in a aside file. Default is false.
			 * @return bool
			 */
			virtual bool screenshot (bool depth = false, bool stencil = false) noexcept final;

			/**
			 * @brief Returns a captures of every framebuffer.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool dumpFramebuffer () const noexcept final;

			/**
			 * @brief Sets a flag value for user application.
			 * @param flag The flag. Must be between 8 and 15.
			 * @param state The state.
			 */
			virtual void setFlag (size_t flag, bool state) noexcept final;

			/**
			 * @brief Returns a flags value.
			 * @param flag The flag. Can be from 0 to 15.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool getFlag (size_t flag) noexcept final;

			/**
			 * @brief Quits application from console.
			 * @note Console function.
			 * @return int
			 */
			virtual int CFQuit (const std::vector< std::string > & parameters) noexcept final;

		private:

			/** @copydoc Emeraude::Input::KeyboardListenerInterface::onKeyPress() */
			bool onKeyPress (int key, int scanCode, int modifiers, bool repeat) noexcept final;

			/** @copydoc Emeraude::Input::KeyboardListenerInterface::onKeyRelease() */
			bool onKeyRelease (int key, int scanCode, int modifiers) noexcept final;

			/** @copydoc Emeraude::Input::KeyboardListenerInterface::onCharacterType() */
			bool onCharacterType (unsigned int unicode, int modifiers) noexcept final;

			/** @copydoc Libraries::Observer::onNotification() */
			[[nodiscard]]
			bool onNotification (const Libraries::Observable * observable, int notificationCode, const std::any & data) noexcept final;

			/**
			 * @brief Initializes the core level of the engine.
			 * @details After that function, the graphics render, the audio manager and
			 * the input manager will be available.
			 * If this method returns false, the engine won't execute.
			 * @return bool
			 */
			virtual bool initializeCoreLevel () noexcept final;

			/**
			 * @brief Initializes the core screen.
			 * @return bool
			 */
			virtual bool initializeCoreScreen () noexcept final;

			/**
			 * @brief [THREAD] Main function to update scene logics.
			 * @param milliseconds The number of milliseconds per cycle.
			 * @return void
			 */
			virtual void processLogicsTask (double milliseconds) noexcept final;

			/**
			 * @brief Terminates the engine execution.
			 * @return unsigned int
			 */
			virtual unsigned int terminate () noexcept final;

			/**
			 * @brief Executes a special mode with the engine.
			 * @return bool
			 */
			virtual bool executeToolsMode () noexcept final;

			/**
			 * @brief showStatistics
			 * @param elapsedTime
			 * @return void
			 */
			virtual void showStatistics (double elapsedTime) const noexcept final;

			/**
			 * @brief Returns a suitable settings file.
			 * @param filename A reference to a string for the file name.
			 * @param argumentName A reference to a string for an argument to override the file.
			 * @return Libraries::Path::File
			 */
			[[nodiscard]]
			virtual Libraries::Path::File getSettingFile (const std::string & filename, const std::string & argumentName) noexcept final;

			/**
			 * @brief Called before the initialization of secondary services. This is the moment to show application information without starting.
			 * @note If the method return "true", the application will stop.
			 * @param arguments A reference to the arguments.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool readArgumentsBeforeInitialization (const Arguments & arguments) noexcept = 0;

			/**
			 * @brief Called just after the Core engine initialization. It should be used for extra initialization.
			 * @note If this function return false, the engine won't execute.
			 * @return bool
			 */
			virtual bool onInitialize () noexcept = 0;

			/**
			 * @brief Called before entering the main loop. All Services are available at this point.
			 * It should be used to build a scene.
			 * @note If this function return false, the main loop won't execute.
			 * @return bool
			 */
			virtual bool onStart () noexcept = 0;

			/**
			 * @brief Called in every logics processing cycle.
			 * @warning This come from a different thread.
			 * @param cycle The current cycle number.
			 * @return void
			 */
			virtual void onProcessLogics (size_t cycle) noexcept = 0;

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
			 * @brief Called after exiting the main loop.
			 * @note This is the moment to cleanup resources.
			 * @return void
			 */
			virtual void onTermination () noexcept = 0;

			/**
			 * @brief Event sent to the application when a key is pressed.
			 * @note The Core has priority on these events.
			 * @param key The keyboard universal key code.
			 * @param scanCode The system-dependent key code.
			 * @param modifiers The modifier keys mask.
			 * @return bool
			 */
			virtual bool onAppKeyPress (int key, int scanCode, int modifiers, bool repeat) noexcept = 0;

			/**
			 * @brief Event sent to the application when a key is released.
			 * @note The Core has priority on these events.
			 * @param key The keyboard universal key code.
			 * @param scanCode The system-dependent key code.
			 * @param modifiers The modifier keys mask.
			 * @return bool
			 */
			virtual bool onAppKeyRelease (int key, int scanCode, int modifiers) noexcept = 0;

			/**
			 * @brief Event sent to the application when a unicode char is typed.
			 * @note The Core has priority on these events.
			 * @param unicode The unicode.
			 * @param modifiers The state of modifiers key.
			 * @return bool
			 */
			virtual bool onAppCharacterType (unsigned int unicode, int modifiers) noexcept = 0;

			/**
			 * @brief Called when a notification is not handled by the core engine.
			 * @note If this function return false, the observer will be automatically detached.
			 * @param observable The observable responsible of the notification.
			 * @param notificationCode Code of notification.
			 * @param data Pointer to possible data.
			 * @return bool
			 */
			virtual bool onAppNotification (const Libraries::Observable * observable, int notificationCode, const std::any & data) noexcept = 0;

			/**
			 * @brief Called when files has been loaded.
			 * @param filePaths A reference to a vector of file paths.
			 * @return void
			 */
			virtual void onOpenFiles (const std::vector< Libraries::Path::File > & filePaths) noexcept = 0;

			/* Flag names */
			static constexpr auto IsRunning = 0UL;
			static constexpr auto Paused = 1UL;
			static constexpr auto LifetimeUsesRealTime = 2UL;

			static constexpr auto CoreSettingsFilename = "CoreConfig.json";
			static constexpr auto ApplicationSettingsFilename = "ApplicationConfig.json";

			static Core * s_instance; // NOLINT NOTE: Singleton behavior

			std::string m_applicationName;
			Libraries::Version m_applicationVersion;
			std::string m_applicationOrganization;
			std::string m_applicationDomain;
			/* Primary services */
			Arguments m_arguments;
			Help m_coreHelp{"Core help"};
			Help m_applicationHelp{"Application help"};
			Tracer m_tracer{m_arguments, m_coreSettings};
			FileSystem m_fileSystem{m_arguments, m_applicationName};
			Settings m_coreSettings{m_arguments, SettingsType::Core, "Core settings"};
			Settings m_applicationSettings{m_arguments, SettingsType::Application, "Application settings"};
			Console m_console{m_arguments, m_fileSystem, m_coreSettings, m_inputManager, m_overlayManager};
			NetworkManager m_networkManager{m_arguments, m_fileSystem, m_coreSettings};
			Resources::Manager m_resourceManager{m_arguments, m_fileSystem, m_coreSettings, m_networkManager};
			User m_user{m_applicationSettings};
			/* Secondary services */
			PlatformManager m_platformManager{m_arguments, m_coreSettings};
			Vulkan::Instance m_vulkanInstance{m_arguments, m_coreSettings};
			Window m_window{m_arguments, m_coreSettings, m_vulkanInstance, this->applicationFullIdentification()};
			Input::Manager m_inputManager{m_arguments, m_fileSystem, m_coreSettings, m_window};
			Graphics::Renderer m_graphicsRenderer{m_arguments, m_coreSettings, m_vulkanInstance, m_window, m_vertexBufferFormatManager};
			Vulkan::TransferManager m_graphicsTransferManager{m_arguments, m_coreSettings, Vulkan::TransferType::Graphics};
			Graphics::RenderableInstance::VertexBufferFormatManager m_vertexBufferFormatManager{};
			Graphics::ExternalInput m_videoExternalInput{m_arguments, m_coreSettings};
			Physics::Manager m_physicsManager{m_arguments, m_coreSettings, m_vulkanInstance};
			Vulkan::TransferManager m_physicsTransferManager{m_arguments, m_coreSettings, Vulkan::TransferType::Physics};
			Saphir::ShaderCompiler m_shaderCompiler{m_arguments, m_coreSettings};
			Saphir::ShaderManager m_shaderManager{m_arguments, m_fileSystem, m_coreSettings, m_shaderCompiler};
			Audio::Manager m_audioManager{m_arguments, m_coreSettings};
			Audio::TrackMixer m_trackMixer{m_arguments, m_coreSettings, m_resourceManager, m_audioManager};
			Audio::ExternalInput m_audioExternalInput{m_arguments, m_coreSettings};
			Overlay::Manager m_overlayManager{m_arguments, m_coreSettings, m_window, m_graphicsRenderer};
			Notifier m_notifier{m_coreSettings, m_overlayManager};
			Scenes::Manager m_sceneManager{m_arguments, m_coreSettings, m_applicationSettings, m_resourceManager, m_graphicsRenderer};
			Dev::Manager m_devManager{m_fileSystem, m_coreSettings, m_resourceManager, m_window, m_graphicsRenderer};
			/* Next members */
			std::vector< ServiceInterface * > m_primaryServicesEnabled{};
			std::vector< ServiceInterface * > m_secondaryServicesEnabled{};
			std::mutex m_processLogicsMutex{};
			double m_lifetime{0.0};
			size_t m_cycle{0};
			Libraries::Time::TimerID m_logicsUpdateTimerID{0};
			StartupMode m_startupMode{StartupMode::Continue};
			std::array< bool, 16 > m_flags{ // NOLINT(*-magic-numbers)
				true/*IsRunning*/,
				false/*Paused*/,
				true/*LifetimeUsesRealTime*/,
				true/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
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

			/* FIXME: Removes these preloaded resources ! */
			std::shared_ptr< Audio::SoundResource > m_switchOnSound{};
			std::shared_ptr< Audio::SoundResource > m_switchOffSound{};
			std::shared_ptr< Audio::SoundResource > m_captureSound{};
			std::shared_ptr< Overlay::Elements::Text > m_statisticsDisplay{};
	};
}
