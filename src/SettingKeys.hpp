/*
 * src/SettingKeys.hpp
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

#pragma once

namespace EmEn
{
	/* API */

		/* GLFW */
		static constexpr auto GLFWShowInformationKey{"API/GLFW/ShowInformation"}; // Logs
		static constexpr auto DefaultGLFWShowInformation{false};

		/* Vulkan */
		static constexpr auto VkShowInformationKey{"API/Vulkan/ShowInformation"}; // Logs
		static constexpr auto DefaultVkShowInformation{false};
		static constexpr auto VkCreateSurfaceWithGLFWKey{"API/Vulkan/CreateSurfaceWithGLFW"};
		static constexpr auto DefaultVkCreateSurfaceWithGLFW{true};

			/* Vulkan instance */
			static constexpr auto VkInstanceEnableDebugKey{"API/Vulkan/Instance/EnableDebug"};
			static constexpr auto DefaultVkInstanceEnableDebug{false};
			static constexpr auto VkInstanceRequestedValidationLayersKey{"API/Vulkan/Instance/RequestedValidationLayers"};
			static constexpr auto VkInstanceAvailableValidationLayersKey{"API/Vulkan/Instance/AvailableValidationLayers"};
			static constexpr auto VkInstanceUseDebugMessengerKey{"API/Vulkan/Instance/UseDebugMessenger"};
			static constexpr auto DefaultVkInstanceUseDebugMessenger{true};

			/* Vulkan device */
			static constexpr auto VkDeviceForceGPUKey{"API/Vulkan/Device/ForceGPU"};

		/* OpenAL */
		static constexpr auto OpenALShowInformationKey{"API/OpenAL/ShowInformation"}; // Logs
		static constexpr auto DefaultOpenALShowInformation{false};
		static constexpr auto OpenALUseEFXExtensionsKey{"API/OpenAL/UseEFXExtensions"};
		static constexpr auto DefaultOpenALUseEFXExtensions{true};
		static constexpr auto OpenALRefreshRateKey{"API/OpenAL/RefreshRate"};
		static constexpr auto DefaultOpenALRefreshRate{46};
		static constexpr auto OpenALSyncStateKey{"API/OpenAL/SyncState"};
		static constexpr auto DefaultOpenALSyncState{0};
		static constexpr auto OpenALMaxMonoSourceCountKey{"API/OpenAL/MaxMonoSourceCount"};
		static constexpr auto DefaultOpenALMaxMonoSourceCount{32};
		static constexpr auto OpenALMaxStereoSourceCountKey{"API/OpenAL/MaxStereoSourceCount"};
		static constexpr auto DefaultOpenALMaxStereoSourceCount{2};

	/* Core */
	static constexpr auto CoreShowInformationKey{"Core/ShowInformation"}; // Logs
	static constexpr auto DefaultCoreShowInformation{false};

		/* Tracer */
		static constexpr auto TracerPrintOnlyErrorsKey{"Core/Tracer/PrintOnlyErrors"};
		static constexpr auto DefaultPrintOnlyErrors{false};
		static constexpr auto TracerShowLocationKey{"Core/Tracer/ShowLocation"};
		static constexpr auto DefaultShowLocation{false};
		static constexpr auto TracerShowThreadInfosKey{"Core/Tracer/ShowThreadInfos"};
		static constexpr auto DefaultShowThreadInfos{false};

		/* Input manager */
		static constexpr auto InputShowInformationKey{"Core/Input/ShowInformation"}; // Logs
		static constexpr auto DefaultInputShowInformation{false};

		/* Resource manager */
		static constexpr auto ResourcesShowInformationKey{"Core/Resources/ShowInformation"}; // Logs
		static constexpr auto DefaultResourcesShowInformation{false};
		static constexpr auto ResourcesDownloadEnabledKey{"Core/Resources/DownloadEnabled"};
		static constexpr auto DefaultCoreResourcesDownloadEnabled{true};

		/* Audio layer */
		static constexpr auto AudioEnableKey{"Core/Audio/Enable"};
		static constexpr auto DefaultAudioEnable{true};
		static constexpr auto AudioPlaybackFrequencyKey{"Core/Audio/PlaybackFrequency"};
		static constexpr auto DefaultAudioPlaybackFrequency{48000};
		static constexpr auto AudioMasterVolumeKey{"Core/Audio/MasterVolume"};
		static constexpr auto DefaultAudioMasterVolume{0.75F};
		static constexpr auto AudioSFXVolumeKey{"Core/Audio/SFXVolume"};
		static constexpr auto DefaultAudioSFXVolume{0.6F};
		static constexpr auto AudioMusicVolumeKey{"Core/Audio/MusicVolume"};
		static constexpr auto DefaultAudioMusicVolume{0.5F};
		static constexpr auto AudioMusicChunkSizeKey{"Core/Audio/MusicChunkSize"};
		static constexpr auto DefaultAudioMusicChunkSize{8192};
		static constexpr auto AudioQuietConversionKey{"Core/Audio/QuietConversion"}; // Logs
		static constexpr auto DefaultAudioQuietConversion{true};

			/* Recorder */
			static constexpr auto RecorderFrequencyKey{"Core/Audio/Recorder/Frequency"};
			static constexpr auto DefaultRecorderFrequency{48000};
			static constexpr auto RecorderBufferSizeKey{"Core/Audio/Recorder/BufferSize"};
			static constexpr auto DefaultRecorderBufferSize{64};

		/* Video */
		static constexpr auto VideoSavePropertiesAtExitKey{"Core/Video/SavePropertiesAtExit"};
		static constexpr auto DefaultVideoSavePropertiesAtExit{true};
		static constexpr auto VideoPreferredMonitorKey{"Core/Video/PreferredMonitor"};
		static constexpr auto DefaultVideoPreferredMonitor{0};
		static constexpr auto VideoEnableVSyncKey{"Core/Video/EnableVSync"};
		static constexpr auto DefaultVideoEnableVSync{false};
		static constexpr auto VideoEnableDoubleBufferingKey{"Core/Video/EnableDoubleBuffering"}; // Not in use
		static constexpr auto DefaultEnableDoubleBuffering{false};
		static constexpr auto VideoEnableTripleBufferingKey{"Core/Video/EnableTripleBuffering"};
		static constexpr auto DefaultVideoEnableTripleBuffering{false};
		static constexpr auto VideoEnableSRGBKey{"Core/Video/EnableSRGB"}; // Not in use
		static constexpr auto DefaultEnableSRGB{false};

			/* Window */
			static constexpr auto VideoWindowShowInformationKey{"Core/Video/Window/ShowInformation"}; // Logs
			static constexpr auto DefaultVideoWindowShowInformation{false};
			static constexpr auto VideoWindowAlwaysCenterOnStartupKey{"Core/Video/Window/AlwaysCenterOnStartup"};
			static constexpr auto DefaultVideoWindowAlwaysCenterOnStartup{false};
			static constexpr auto VideoWindowFramelessKey{"Core/Video/Window/Frameless"};
			static constexpr auto DefaultVideoWindowFrameless{false};
			static constexpr auto VideoWindowXPositionKey{"Core/Video/Window/XPosition"};
			static constexpr auto DefaultVideoWindowXPosition{64};
			static constexpr auto VideoWindowYPositionKey{"Core/Video/Window/YPosition"};
			static constexpr auto DefaultVideoWindowYPosition{64};
			static constexpr auto VideoWindowWidthKey{"Core/Video/Window/Width"};
			static constexpr auto DefaultVideoWindowWidth{1280U};
			static constexpr auto VideoWindowHeightKey{"Core/Video/Window/Height"};
			static constexpr auto DefaultVideoWindowHeight{720U};
			static constexpr auto VideoWindowGammaKey{"Core/Video/Window/Gamma"};
			static constexpr auto DefaultVideoWindowGamma{1.0F};

			/* Fullscreen */
			static constexpr auto VideoFullscreenEnabledKey{"Core/Video/Fullscreen/Enabled"};
			static constexpr auto DefaultVideoFullscreenEnabled{false};
			static constexpr auto VideoFullscreenWidthKey{"Core/Video/Fullscreen/Width"};
			static constexpr auto DefaultVideoFullscreenWidth{1920U};
			static constexpr auto VideoFullscreenHeightKey{"Core/Video/Fullscreen/Height"};
			static constexpr auto DefaultVideoFullscreenHeight{1080U};
			static constexpr auto VideoFullscreenGammaKey{"Core/Video/Fullscreen/Gamma"};
			static constexpr auto DefaultVideoFullscreenGamma{1.0F};
			static constexpr auto VideoFullscreenRefreshRateKey{"Core/Video/Fullscreen/RefreshRate"};
			static constexpr auto DefaultVideoFullscreenRefreshRate{-1};

			/* Overlay */
			static constexpr auto VideoOverlayForceScaleXKey{"Core/Video/Overlay/ForceScaleX"};
			static constexpr auto VideoOverlayForceScaleYKey{"Core/Video/Overlay/ForceScaleY"};
			static constexpr auto DefaultVideoOverlayForceScale{0};

			/* Framebuffer */
			static constexpr auto VideoFramebufferRedBitsKey{"Core/Video/Framebuffer/RedBits"};
			static constexpr auto DefaultVideoFramebufferRedBits{8U};
			static constexpr auto VideoFramebufferGreenBitsKey{"Core/Video/Framebuffer/GreenBits"};
			static constexpr auto DefaultVideoFramebufferGreenBits{8U};
			static constexpr auto VideoFramebufferBlueBitsKey{"Core/Video/Framebuffer/BlueBits"};
			static constexpr auto DefaultVideoFramebufferBlueBits{8U};
			static constexpr auto VideoFramebufferAlphaBitsKey{"Core/Video/Framebuffer/AlphaBits"};
			static constexpr auto DefaultVideoFramebufferAlphaBits{8U};
			static constexpr auto VideoFramebufferDepthBitsKey{"Core/Video/Framebuffer/DepthBits"};
			static constexpr auto DefaultVideoFramebufferDepthBits{32U};
			static constexpr auto VideoFramebufferStencilBitsKey{"Core/Video/Framebuffer/StencilBits"};
			static constexpr auto DefaultVideoFramebufferStencilBits{0U};
			static constexpr auto VideoFramebufferSamplesKey{"Core/Video/Framebuffer/Samples"};
			static constexpr auto DefaultVideoFramebufferSamples{1U};
			static constexpr auto VideoFramebufferAntiAliasingKey{"Core/Video/Framebuffer/AntiAliasing"};
			static constexpr auto DefaultVideoAntiAliasing{"None"};
			static constexpr auto VideoFramebufferEnableMLAAKey{"Core/Video/Framebuffer/EnableMLAA"};
			static constexpr auto DefaultVideoEnableMLAA{false};

		/* Graphics */
		static constexpr auto GraphicsMaxViewableDistanceKey{"Core/Graphics/MaxViewableDistance"};
		static constexpr auto DefaultGraphicsMaxViewableDistance{100000.0F}; /* NOTE: 100 Km */
		static constexpr auto GraphicsFieldOfViewKey{"Core/Graphics/FieldOfView"};
		static constexpr auto DefaultGraphicsFieldOfView{85.0F}; /* NOTE: 100 Km */

			/* Texture */
			static constexpr auto GraphicsTextureMagFilteringKey{"Core/Graphics/Texture/MagFilter"};
			static constexpr auto GraphicsTextureMinFilteringKey{"Core/Graphics/Texture/MinFilter"};
			static constexpr auto GraphicsTextureMipFilteringKey{"Core/Graphics/Texture/MipFilter"};
			static constexpr auto DefaultGraphicsTextureFiltering{"nearest"};
			static constexpr auto GraphicsTextureMipMappingLevelsKey{"Core/Graphics/Texture/MipMappingLevels"};
			static constexpr auto DefaultGraphicsTextureMipMappingLevels{1};
			static constexpr auto GraphicsTextureAnisotropyLevelsKey{"Core/Graphics/Texture/AnisotropyLevels"};
			static constexpr auto DefaultGraphicsTextureAnisotropy{0};

			/* Shadow Mapping */
			static constexpr auto GraphicsShadowMappingEnabledKey{"Core/Graphics/ShadowMapping/Enabled"};
			static constexpr auto DefaultGraphicsShadowMappingEnabled{true};
			static constexpr auto GraphicsShadowMappingBaseResolutionKey{"Core/Graphics/ShadowMapping/BaseResolution"};
			static constexpr auto DefaultGraphicsShadowMappingBaseResolution{512U};
			static constexpr auto GraphicsShadowMappingPCFSampleKey{"Core/Graphics/ShadowMapping/PCFSample"};
			static constexpr auto DefaultGraphicsShadowMappingPCFSample{0U};
			static constexpr auto GraphicsShadowMappingPCFRadiusKey{"Core/Graphics/ShadowMapping/PCFRadius"};
			static constexpr auto DefaultGraphicsShadowMappingPCFRadius{1.0F};
			static constexpr auto GraphicsShadowMappingMaxDistanceKey{"Core/Graphics/ShadowMapping/MaxDistance"};
			static constexpr auto DefaultGraphicsShadowMappingMaxDistance{5000.0F}; /* NOTE: 5 Km */

			/* Shader */
			static constexpr auto ShowSourceCodeKey{"Core/Graphics/Shader/ShowSourceCode"}; // Logs
			static constexpr auto DefaultShowSourceCode{false};
			static constexpr auto SourceCodeCacheEnabledKey{"Core/Graphics/Shader/EnableSourceCodeCache"};
			static constexpr auto DefaultSourceCodeCacheEnabled{false};
			static constexpr auto BinaryCacheEnabledKey{"Core/Graphics/Shader/EnableBinaryCache"};
			static constexpr auto DefaultBinaryCacheEnabled{false};
			static constexpr auto NormalMappingEnabledKey{"Core/Graphics/Shader/EnableNormalMapping"};
			static constexpr auto DefaultNormalMappingEnabled{true};
			static constexpr auto HighQualityLightEnabledKey{"Core/Graphics/Shader/EnabledHighQualityLight"};
			static constexpr auto DefaultHighQualityLightEnabled{false};
			static constexpr auto HighQualityReflectionEnabledKey{"Core/Graphics/Shader/EnableHighQualityReflection"};
			static constexpr auto DefaultHighQualityReflectionEnabled{false};

		/* Physics */
		static constexpr auto EnablePhysicsAccelerationKey{"Core/Physics/EnableAcceleration"};
		static constexpr auto DefaultEnablePhysicsAcceleration{false};
}
