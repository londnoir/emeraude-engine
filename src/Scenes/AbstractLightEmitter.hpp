/*
 * Emeraude/Scenes/AbstractLightEmitter.hpp
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
#include <string>
#include <memory>
#include <array>

/* Local inclusions for inheritances. */
#include "AbstractComponent.hpp"
#include "MasterControl/AbstractVirtualVideoDevice.hpp"

/* Local inclusions for usages. */
#include "PixelFactory/Color.hpp"
#include "Graphics/RenderTarget/ShadowMap/Abstract.hpp"

namespace Emeraude::Scenes
{
	/**
	 * @brief Base class of light emitters.
	 * @extends Emeraude::Scenes::AbstractComponent The base class for each entity component.
	 * @extends Emeraude::MasterControl::AbstractVirtualVideoDevice This can act as a virtual video device.
	 */
	class AbstractLightEmitter : public AbstractComponent, public MasterControl::AbstractVirtualVideoDevice
	{
		public:

			/**
			 * @brief Destructs the abstract light emitter.
			 */
			~AbstractLightEmitter () override = default;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractLightEmitter (const AbstractLightEmitter & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractLightEmitter (AbstractLightEmitter && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			AbstractLightEmitter & operator= (const AbstractLightEmitter & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			AbstractLightEmitter & operator= (AbstractLightEmitter && copy) noexcept = delete;

			/** @copydoc Emeraude::MasterControl::AbstractVirtualVideoDevice::videoType() */
			[[nodiscard]]
			MasterControl::VideoType videoType () const noexcept override;

			/**
			 * @brief Sets the state of the light.
			 * @param state The state.
			 * @return void
			 */
			void enable (bool state) noexcept;

			/**
			 * @brief Toggles the state of the light.
			 * @return bool
			 */
			bool toggle () noexcept;

			/**
			 * @brief Returns whether the light is emitting.
			 * @return bool
			 */
			[[nodiscard]]
			bool isEnabled () const noexcept;

			/**
			 * @brief Sets the three colors at once.
			 * @param color A color to apply.
			 * @return void
			 */
			void setColor (const Libraries::PixelFactory::Color< float > & color) noexcept;

			/**
			 * @brief Sets the indirect light color. This will be added to the whole ambient scene light.
			 * @param color A color to apply.
			 * @return void
			 */
			void setAmbientColor (const Libraries::PixelFactory::Color< float > & color) noexcept;

			/**
			 * @brief Sets the direct light color.
			 * @param color A color to apply.
			 * @return void
			 */
			void setDiffuseColor (const Libraries::PixelFactory::Color< float > & color) noexcept;

			/**
			 * @brief Sets the specular highlight color.
			 * @param color A color to apply.
			 * @return void
			 */
			void setSpecularColor (const Libraries::PixelFactory::Color< float > & color) noexcept;

			/**
			 * @brief Sets the intensity of the light. Default is one.
			 * @param intensity A scalar to multiply.
			 * @return void
			 */
			void setIntensity (float intensity) noexcept;

			/**
			 * @brief Returns the light ambient color.
			 * This could be added to the global ambient color of the scene depending of configuration.
			 * @return const Libraries::PixelFactory::Color< float > &
			 */
			[[nodiscard]]
			const Libraries::PixelFactory::Color< float > & ambientColor () const noexcept;

			/**
			 * @brief Returns the direct light color.
			 * @return const Libraries::PixelFactory::Color< float > &
			 */
			[[nodiscard]]
			const Libraries::PixelFactory::Color< float > & diffuseColor () const noexcept;

			/**
			 * @brief Returns the specular highlight color.
			 * @return const Libraries::PixelFactory::Color< float > &
			 */
			[[nodiscard]]
			const Libraries::PixelFactory::Color< float > & specularColor () const noexcept;

			/**
			 * @brief Returns the light intensity.
			 * @return float
			 */
			[[nodiscard]]
			float intensity () const noexcept;

			/**
			 * @brief Returns the matrix to compute the light space.
			 * @return Libraries::Math::Matrix< 4, float >
			 */
			[[nodiscard]]
			virtual Libraries::Math::Matrix< 4, float > getLightSpaceMatrix () const noexcept final;

			/**
			 * @brief Returns an intensified color by a value.
			 * @param color A reference to a color.
			 * @param intensity The intensity value.
			 * @return Libraries::Math::Vector< 4, float >
			 */
			static Libraries::Math::Vector< 4, float > intensifiedColor (const Libraries::PixelFactory::Color< float > & color, float intensity) noexcept;

			/**
			 * @brief Asks the light to create a shadow map for shadow casting.
			 * @param state Enable or disable the shadow map.
			 * @param overrideResolution Override the resolution settings.
			 * @return void
			 */
			virtual void enableShadow (bool state, size_t overrideResolution) noexcept = 0;

			/**
			 * @brief Returns whether the light is casting shadow.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isShadowEnabled () const noexcept = 0;

			/**
			 * @brief Gives access to the light shadow map.
			 * @return std::shared_ptr< Graphics::RenderTarget::ShadowMap::Abstract >
			 */
			[[nodiscard]]
			virtual std::shared_ptr< Graphics::RenderTarget::ShadowMap::Abstract > shadowMap () const noexcept = 0;

		protected:

			static constexpr auto ShadowMapName = "ShadowMap";

			/**
			 * @brief Constructs an abstract light emitter.
			 * @param name The name of the light.
			 * @param parentEntity A reference to the parent entity.
			 */
			AbstractLightEmitter (const std::string & name, const AbstractEntity & parentEntity) noexcept;

			/** @copydoc Emeraude::MasterControl::AbstractVirtualDevice::updateDeviceFromCoordinates() */
			void updateDeviceFromCoordinates (const Libraries::Math::Coordinates< float > & worldCoordinates, const Libraries::Math::Vector< 3, float > & worldVelocity) noexcept final;

			/** @copydoc Emeraude::MasterControl::AbstractVirtualVideoDevice::updateProperties() */
			void updateProperties (bool isPerspectiveProjection, float distance, float fovOrNear) noexcept final;

		private:

			/** @copydoc Emeraude::Scenes::AbstractComponent::move() */
			void move () noexcept final;

			/** @copydoc Emeraude::Scenes::AbstractComponent::processLogics() */
			void processLogics (const Scene & scene, size_t cycle) noexcept final;

			/* Flag names */
			static constexpr auto Enabled = 0UL;

			Libraries::PixelFactory::Color< float > m_ambientColor{Libraries::PixelFactory::Black};
			Libraries::PixelFactory::Color< float > m_diffuseColor{Libraries::PixelFactory::White};
			Libraries::PixelFactory::Color< float > m_specularColor{Libraries::PixelFactory::White};
			float m_intensity{1.0F};
			std::array< bool, 8 > m_flags{
				true/*Enabled*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
