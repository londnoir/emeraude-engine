/*
 * Emeraude/Scenes/LightSet.hpp
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
#include <set>
#include <memory>

/* Local inclusions */
#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "SpotLight.hpp"

namespace Emeraude::Graphics::TextureResource
{
	class TextureCubemap;
}

namespace Emeraude::Scenes
{
	/**  */

	/**
	 * @brief This class hold lights from a whole scene.
	 * @extends Libraries::Observable
	 */
	class LightSet final : public Libraries::Observable
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"LightSet"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/** @brief Observable notification codes. */
			enum NotificationCode
			{
				DirectionalLightAdded,
				PointLightAdded,
				SpotLightAdded,
				DirectionalLightRemoved,
				PointLightRemoved,
				SpotLightRemoved,
				/* Enumeration boundary. */
				MaxEnum
			};

			/**
			 * @brief Constructs a light set.
			 */
			LightSet () noexcept = default;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/**
			 * @brief Sets a base ambient light for the scene.
			 * @note This will have an effect even if no light are in the scene.
			 * @param color The color of the global base ambient light.
			 * @return void
			 */
			void setGlobalAmbientLight (const Libraries::PixelFactory::Color< float > & color) noexcept;

			/**
			 * @brief Sets a base ambient light for the scene using a cubemap for averaging the color.
			 * @note This will have an effect even if there is no are in the scene.
			 * @param cubemap Use the average color of the cubemap to set the global base ambient light.
			 * @param percent Set the amount of the retrieved color (intensity) from the cubemap.
			 * @return void
			 */
			void setGlobalAmbientLight (const std::shared_ptr< Graphics::TextureResource::TextureCubemap > & cubemap, float percent = 0.2F) noexcept;

			/**
			 * @brief When computing the final ambient lighting, use a fraction of
			 * light color instead of the ambient component of each light source.
			 * @param state Enable the computation.
			 * @param factor The percent of each color light. Default 10%.
			 * @return void
			 */
			void enableLightColorForAmbientGeneration (bool state, float factor = 0.1F) noexcept;

			/**
			 * @brief Enables the light distance for ambient generation.
			 * @param state The state.
			 * @return void
			 */
			void enableLightDistanceForAmbientGeneration (bool state) noexcept;

			/**
			 * @brief Adds a directional light.
			 * @param light A smart pointer to the scene directional light.
			 * @return void
			 */
			void add (const std::shared_ptr< DirectionalLight > & light) noexcept;

			/**
			 * @brief Adds a point light.
			 * @param light A smart pointer to the scene point light.
			 * @return void
			 */
			void add (const std::shared_ptr< PointLight > & light) noexcept;

			/**
			 * @brief Adds a spot light.
			 * @param light A smart pointer to the scene spot light.
			 * @return void
			 */
			void add (const std::shared_ptr< SpotLight > & light) noexcept;

			/**
			 * @brief Removes a directional light.
			 * @param light A smart pointer to the scene directional light.
			 * @return void
			 */
			void remove (const std::shared_ptr< DirectionalLight > & light) noexcept;

			/**
			 * @brief Removes a point light.
			 * @param light A smart pointer to the scene point light.
			 * @return void
			 */
			void remove (const std::shared_ptr< PointLight > & light) noexcept;

			/**
			 * @brief Removes a spot light.
			 * @param light A smart pointer to the scene spot light.
			 * @return void
			 */
			void remove (const std::shared_ptr< SpotLight > & light) noexcept;

			/**
			 * @brief Returns the base ambient light.
			 * @return const Color< float > &
			 */
			[[nodiscard]]
			const Libraries::PixelFactory::Color< float > & globalAmbientLight () const noexcept;

			/**
			 * @brief lights
			 * @return const std::set< std::shared_ptr< AbstractLightEmitter > > &
			 */
			[[nodiscard]]
			const std::set< std::shared_ptr< AbstractLightEmitter > > & lights () const noexcept;

			/**
			 * @brief Returns the fraction of light color for ambient calculation of each light.
			 * @return float
			 */
			[[nodiscard]]
			float lightColorFactorToAmbient () const noexcept;

			/**
			 * @brief Returns whether we use a fraction of the light color instead of
			 * the ambient component of each light for global ambien calculation.
			 * @return bool
			 */
			[[nodiscard]]
			bool useLightColorAsAmbient () const noexcept;

			/**
			 * @brief Returns whether we check the distance between the light radius and
			 * the camera to add or not the ambient component.
			 * @return bool
			 */
			[[nodiscard]]
			bool useLightDistance () const noexcept;

			/**
			 * @brief Computes the ambient light fraction to add to global ambient light.
			 * @tparam vectorData_t The data type to use for Vector. Default float.
			 * @param light The targeted light.
			 * @return Libraries::Math::Vector< 4, vectorData_t >
			 */
			template< typename vectorData_t = float >
			Libraries::Math::Vector< 4, vectorData_t >
			getLightAmbientAddition (const std::shared_ptr< AbstractLightEmitter > & light) const noexcept
			{
				if ( this->useLightColorAsAmbient() )
					return light->diffuseColor().toVector4< vectorData_t >() * this->lightColorFactorToAmbient();

				return light->ambientColor().toVector4< vectorData_t >();
			}

			/**
			 * @brief Removes all lights.
			 * @return void
			 */
			void clear () noexcept;

		private:

			/* Flag names */
			static constexpr auto UseLightColorAsAmbient = 0UL;
			static constexpr auto UseLightDistance = 1UL;

			std::set< std::shared_ptr< AbstractLightEmitter > > m_lights{};
			Libraries::PixelFactory::Color< float > m_globalAmbientLight = Libraries::PixelFactory::Black;
			float m_lightColorFactorToAmbient = 0.1F;
			std::array< bool, 8 > m_flags{
				false/*UseLightColorAsAmbient*/,
				false/*UseLightDistance*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
