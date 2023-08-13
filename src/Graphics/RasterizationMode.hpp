/*
 * Emeraude/Graphics/RasterizationMode.hpp
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
#include <string>

/* Local inclusions */
#include "Types.hpp"

namespace Emeraude::Graphics
{
	/**
	 * @brief Controls the way the Renderer will draw a geometry.
	 * @note The Renderer can override some configuration for all geometries.
	 */
	class RasterizationMode final
	{
		friend class Renderer;

		public:

			/** Default constructor. */
			RasterizationMode () noexcept = default;

			/** Copy constructor. */
			RasterizationMode (const RasterizationMode & copy) noexcept = default;

			/**
			 * This method will enable/disable functionnality from graphic API (ie OpenGL)
			 * while testing differences with the previous mode. If the new mode is totally the same
			 * to the old one, no graphic API calls will occurs.
			 *
			 * @param other The new mode to apply.
			 * @return RasterizationMode &
			 */
			RasterizationMode & operator= (const RasterizationMode & other) noexcept;

			/**
			 * Enables or not the inversion of triangle winding.
			 *
			 * @param state The state.
			 */
			void setInvertedTriangleWinding (bool state) noexcept;

			/**
			 * Sets how triangles will be rasterized on screen.
			 *
			 * @note This affect only triangle primitive.
			 * @param mode Mode of drawing the triangles.
			 */
			void setPolygonMode (PolygonMode mode) noexcept;

			/**
			 * Sets which sides of triangles will be ignored.
			 *
			 * @note This affect only triangle primitive.
			 * @param mode The side.
			 */
			void setCullingMode (CullingMode mode) noexcept;

			/**
			 * Sets polygon offset rendering parameters.
			 *
			 * @param state The state.
			 * @param factor Specifies a scale factor that is used to create a variable depth offset for each polygon. The initial value is 0.
			 * @param units Is multiplied by an implementation-specific value to create a constant depth offset. The initial value is 0.
			 */
			void setPolygonOffset (bool state, float factor = 0.0F, float units = 0.0F) noexcept;

			/**
			 * Sets how the object use the depth buffer.
			 *
			 * @param readState the renderer will perfom a depth test to discard or not fragments.
			 * @param writeState set if depth will be updated or not when fragments are written in frame buffer.
			 */
			void setDepthBufferStates (bool readState, bool writeState = true) noexcept;

			/**
			 * Sets how the object use the stencil buffer.
			 *
			 * @param readState the renderer will perfom a stencil test to discard or not fragments.
			 * @param writeState set if depth will be updated or not when fragments are written in frame buffer.
			 */
			void setStencilBufferStates (bool readState, bool writeState = true) noexcept;

			/** Reset OpenGL to default states. */
			void resetToDefaultStates () noexcept;

			/** Shows rasterization configuration. */
			friend std::ostream & operator<< (std::ostream & out, const RasterizationMode & obj);

			/**
			 * Override the triangle winding.
			 *
			 * @param overridingState Enable or disable the overriding state.
			 * @param counterClockwise The state of winding. True is Gl_CCW, false is GL_CW.
			 */
			static void overrideTriangleWinding (bool overridingState, bool counterClockwise) noexcept;

			/**
			 * Returns whether the triangle winding is overridden.
			 *
			 * @return bool
			 */
			[[nodiscard]]
			static bool isTriangleWindingOverriden () noexcept;

			/**
			 * Returns the overridden triangle winding.
			 *
			 * @return bool
			 */
			[[nodiscard]]
			static bool triangleWinding () noexcept;

			/**
			 * Override the way polygons will be draw on screen.
			 *
			 * @param overridingState Enable or disable the overriding state.
			 * @param mode The desired polygon mode. Default Fill.
			 */
			static void overridePolygonMode (bool overridingState, PolygonMode mode = PolygonMode::Fill) noexcept;

			/**
			 * Returns whether the polygon mode is overridden.
			 *
			 * @return bool
			 */
			[[nodiscard]]
			static bool isPolygonModeOverridden () noexcept;

			/**
			 * Returns the polygon overridden mode.
			 *
			 * @return OverriddenPolygonMode
			 */
			[[nodiscard]]
			static PolygonMode polygonMode () noexcept;

			/**
			 * Sets the way polygon will be culled during the render.
			 *
			 * @param overridingState Enable or disable the overriding state.
			 * @param mode The desired polygon mode. Default Back.
			 */
			static void overrideCullingMode (bool overridingState, CullingMode mode = CullingMode::Back) noexcept;

			/**
			 * Returns the current global culling mode.
			 *
			 * @return bool
			 */
			[[nodiscard]]
			static bool isCullingModeOverridden () noexcept;

			/**
			 * Returns the culling mode overridden.
			 *
			 * @return OverriddenCullingMode
			 */
			[[nodiscard]]
			static CullingMode cullingMode () noexcept;

			/**
			 * Sets the scale and units used to calculate depth values.
			 *
			 * @note This will override RasterizationMode objects configuration.
			 * @param overridingState Enable or disable the overriding state.
			 * @param offsetState The offset state. Default: false.
			 * @param factor Specifies a scale factor that is used to create a variable depth offset for each polygon. The initial value is 0.
			 * @param units Is multiplied by an implementation-specific value to create a constant depth offset. The initial value is 0.
			 */
			static void overridePolygonOffset (bool overridingState, bool offsetState = false, float factor = 0.0F, float units = 0.0F) noexcept;

			/**
			 * Returns whether the polygon offsetting is overridden.
			 *
			 * @return bool
			 */
			[[nodiscard]]
			static bool isPolygonOffsetOverriden () noexcept;

			/**
			 * Returns the polygon offset factor.
			 *
			 * @return float
			 */
			[[nodiscard]]
			static float polygonOffsetFactor () noexcept;

			/**
			 * Returns the polygon offset units.
			 *
			 * @return float
			 */
			[[nodiscard]]
			static float polygonOffsetUnits () noexcept;

			/**
			 * Override how the the depth buffer is used.
			 *
			 * @param overridingState Enable or disable the overriding state.
			 * @param readState the renderer will perfom a depth test to discard or not fragments. Default: true.
			 * @param writeState set if depth will be updated or not when fragments are written in frame buffer. Default: true.
			 */
			static void overrideDepthBufferStates (bool overridingState, bool readState = true, bool writeState = true) noexcept;

			/**
			 * Returns whether the depth configuration is overridden.
			 *
			 * @return bool
			 */
			[[nodiscard]]
			static bool isDepthBufferStatesOverriden () noexcept;

			/**
			 * Checks if the depth buffer reading is enabled.
			 *
			 * @note If disabled, no depth test is currently performed and everythin is draw on top of the render.
			 * @return bool
			 */
			[[nodiscard]]
			static bool isDepthBufferReadingEnabled () noexcept;

			/**
			 * Checks if the depth buffer writting is enabled.
			 *
			 * @note If disabled, each polygon draw will not apperars in depth buffer and could be erased during the render.
			 * @return bool
			 */
			[[nodiscard]]
			static bool isDepthBufferWrittingEnabled () noexcept;

			/**
			 * Override how the the depth buffer is used.
			 *
			 * @param overridingState Enable or disable the overriding state.
			 * @param readState the renderer will perfom a depth test to discard or not fragments. Default: true.
			 * @param writeState set if depth will be updated or not when fragments are written in frame buffer. Default: true.
			 */
			static void overrideStencilBufferStates (bool overridingState, bool readState = true, bool writeState = true) noexcept;

			/**
			 * Returns whether the stencil configuration is overridden.
			 *
			 * @return bool
			 */
			[[nodiscard]]
			static bool isStencilBufferStatesOverriden () noexcept;

			/**
			 * Checks if the stencil buffer reading is enabled.
			 *
			 * @return bool
			 */
			[[nodiscard]]
			static bool isStencilBufferReadingEnabled () noexcept;

			/**
			 * Checks if the stencil buffer writting is enabled.
			 *
			 * @return bool
			 */
			[[nodiscard]]
			static bool isStencilBufferWrittingEnabled () noexcept;

			/**
			 * Control the writting of each component (RGBA) in the color buffer.
			 *
			 * @param redState The red color channel.
			 * @param greenState The green color channel.
			 * @param blueState The blue color channel.
			 * @param alphaState The alpha channel.
			 */
			static void enableColorBufferWritting (bool redState, bool greenState, bool blueState, bool alphaState) noexcept;

			/**
			 * Control the writting in the color buffer.
			 *
			 * @param state The state.
			 */
			static
			inline
			void
			enableColorBufferWritting (bool state) noexcept
			{
				RasterizationMode::enableColorBufferWritting(state, state, state, state);
			}

			/**
			 * Checks if writting on the color buffer is enabled
			 *
			 * @param strict If true, all component must be activated.
			 * @return bool
			 */
			[[nodiscard]]
			static bool isColorBufferWrittingEnabled (bool strict = false) noexcept;

			/**
			 * Returns the writting status of red component in the color buffer.
			 *
			 * @return bool
			 */
			[[nodiscard]]
			static bool isRedColorBufferWrittingEnabled () noexcept;

			/**
			 * Returns the writting status of green component in the color buffer.
			 *
			 * @return bool
			 */
			[[nodiscard]]
			static bool isGreenColorBufferWrittingEnabled () noexcept;

			/**
			 * Returns the writting status of blue component in the color buffer.
			 *
			 * @return bool
			 */
			[[nodiscard]]
			static bool isBlueColorBufferWrittingEnabled () noexcept;

			/**
			 * Returns the writting status of alpha component in the color buffer.
			 *
			 * @return bool
			 */
			[[nodiscard]]
			static bool isAlphaColorBufferWrittingEnabled () noexcept;

		private:

			/* Flag names. */
			static constexpr auto CounterClockwise = 0UL;
			static constexpr auto DepthTestEnabled = 1UL;
			static constexpr auto DepthWriteEnabled = 2UL;
			static constexpr auto StencilTestEnabled = 3UL;
			static constexpr auto StencilWriteEnabled = 4UL;
			static constexpr auto PolygonOffsetEnabled = 5UL;

			static bool s_isTriangleWindingOverridden;
			static bool s_isPolygonModeOverridden;
			static bool s_isCullingModeOverridden;
			static bool s_isDepthBufferStatesOverridden;
			static bool s_isStencilBufferStatesOverridden;
			static bool s_isPolygonOffsetModeOverridden;

			PolygonMode m_polygonMode = PolygonMode::Fill;
			CullingMode m_cullingMode = CullingMode::Back;
			float m_polygonOffsetFactor = 0.0F;
			float m_polygonOffsetUnits = 0.0F;
			std::array< bool, 8 > m_flags {
				true/*CounterClockWise*/,
				true/*DepthTestEnabled*/,
				true/*DepthWriteEnabled*/,
				true/*StencilTestEnabled*/,
				true/*StencilWriteEnabled*/,
				false/*PolygonOffsetEnabled*/,
				false/*UNUSED*/
			};
	};
}
