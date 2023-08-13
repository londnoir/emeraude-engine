/*
 * Emeraude/Graphics/Light/Processor.hpp
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
#include <array>
#include <functional>

/* Local inclusions for inheritances. */
#include "Observer.hpp"

/* Local inclusions for usages. */
#include "Scenes/LightSet.hpp"
#include "DirectionalArrayBuffer.hpp"
#include "PointArrayBuffer.hpp"
#include "SpotArrayBuffer.hpp"

/* Forward declarations. */
namespace Emeraude::Graphics
{
	class Renderer;
}

namespace Emeraude::Graphics::Light
{
	/**
	 * @brief This single pass light processor. This version render an object with all light in one pass.
	 * @note This version is limited to 8 lights per frame. 2 directionals, 3 points and 3 spots.
	 * @warning Due to uniforms limitation in GLSL, some heavy shaders may fails.
	 * @extends Libraries::Observer This class must observer light events.
	 */
	class Processor final : public Libraries::Observer
	{
		public:

			static constexpr auto ClassId{"LightProcessor"};

			/**
			 * @brief Constructs a light processor.
			 * @param maxDirectionalCount The max number of directional light in the buffer. Default 64.
			 * @param maxPointCount The max number of omnidirectional light in the buffer. Default 64.
			 * @param maxSpotCount The max number of spotlight in the buffer. Default 64.
			 */
			explicit Processor (size_t maxDirectionalCount = 64, size_t maxPointCount = 64, size_t maxSpotCount = 64) noexcept;

			/**
			 * @brief Enables or disable the lighting state.
			 * This doesn't touch the individual light state.
			 * @param state The state.
			 */
			void enableLighting (bool state) noexcept;

			/**
			 * @brief Toggles the lighting.
			 * @return bool, the new state.
			 */
			bool toggleLighting  () noexcept;

			/**
			 * @brief Gets the lighting state of the processor.
			 * @return bool
			 */
			[[nodiscard]]
			bool isLightingEnabled () const noexcept;

			/**
			 * @brief Enables or disable the shadow state.
			 * This doesn't touch the individual light state.
			 * @param state The state.
			 */
			void enableShadowing (bool state) noexcept;

			/**
			 * @brief Toggles the shadowing.
			 * @return bool, the new state.
			 */
			bool toggleShadowing () noexcept;

			/**
			 * @brief Gets the shadow state of the processor.
			 * @return bool
			 */
			[[nodiscard]]
			bool isShadowingEnabled () const noexcept;

			/**
			 * @brief Sets a scene light set to the light processor.
			 * @param lightSet A smart pointer to the scene light set.
			 */
			void setLightSet (const std::shared_ptr< Scenes::LightSet > & lightSet) noexcept;

			/**
			 * @brief Gets the light set or nullptr_t.
			 * @return shared_ptr< LightSet >
			 */
			[[nodiscard]]
			std::shared_ptr< Scenes::LightSet > lightSet () const noexcept;

			/**
			 * @brief Initializes light processor video memory.
			 * @return bool
			 */
			[[nodiscard]]
			bool initialize () noexcept;

			/**
			 * @brief Updates the UBOs in the video memory.
			 * @note This should be done before every frame render.
			 * @param view A reference to a view matrix.
			 * @return bool
			 */
			bool updateVideoMemory (const Libraries::Math::Matrix< 4, float > & view) noexcept;

			/**
			 * @brief Enables ambient light property to a program.
			 * @note Do nothing if IsLightEnabled is false.
			 * @param program The current program.
			 */
			//void enableAmbientLight (const Program & program) const noexcept;

			/**
			 * @brief Calls a function per light to render an object.
			 * @note This should be enabled after the ambient pass.
			 * @param renderer A referencer to the renderer.
			 * @param modelRadius A reference to the model radius of the object being rendered.
			 * @param render A function to repeat for each light.
			 */
			void renderLightPasses (Renderer & renderer, const Libraries::Math::Sphere< float > & modelRadius, const std::function< void(RenderPassType renderPassType, const ArrayBufferInterface & lightBuffer, size_t lightIndex, bool isShadowEnabled) > & render) const noexcept;

		private:

			/* Flag names. */
			static constexpr auto IsLightingEnabled = 0UL;
			static constexpr auto IsShadowingEnabled = 1UL;
			static constexpr auto UpdateMultipassBuffer = 2UL;
			static constexpr auto UpdateSinglepassBuffer = 3UL;

			/** @copydoc Libraries::Observer::onNotification() */
			[[nodiscard]]
			bool onNotification (const Libraries::Observable * observable, int notificationCode, const std::any & data) noexcept override;

			std::shared_ptr< Scenes::LightSet > m_lightSet{};
			Libraries::Math::Vector< 4, float > m_ambientLight{};
			DirectionalArrayBuffer m_directionalLightArrayBuffer;
			PointArrayBuffer m_pointLightArrayBuffer;
			SpotArrayBuffer m_spotLightArrayBuffer;
			std::array< bool, 8 > m_flags{
				true/*IsLightingEnabled*/,
				true/*IsShadowingEnabled*/,
				true/*UpdateMultipassBuffer*/,
				true/*UpdateSinglepassBuffer*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
