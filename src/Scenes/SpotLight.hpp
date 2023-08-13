/*
 * Emeraude/Scenes/SpotLight.hpp
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

/* C/C++ standard libraries */
#include <string>
#include <sstream>
#include <iostream>
#include <memory>

/* Local inclusions for inheritances. */
#include "AbstractLightEmitter.hpp"

/* Local inclusions for usages. */
#include "Graphics/RenderTarget/ShadowMap/Texture2D.hpp"

namespace Emeraude::Scenes
{
	/**
	 * @brief Defines a scene spot light like an electrical light torch.
	 * @extends Emeraude::Scenes::AbstractLightEmitter The base class for each light type.
	 */
	class SpotLight final : public AbstractLightEmitter
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"SpotLight"};

			/** @brief Animatable Interface keys */
			static constexpr auto DiffuseColor = 0UL;
			static constexpr auto SpecularColor = 1UL;
			static constexpr auto Intensity = 2UL;
			static constexpr auto Radius = 3UL;
			static constexpr auto InnerAngle = 4UL;
			static constexpr auto OuterAngle = 5UL;

			static constexpr size_t ElementsCount = 4/* diffuse color */ + 4/* specular color */ + 4/* position */ + 4/* direction */ + 1/* radius */ + 1/* innerCosAngle */ + 1/* outerCosAngle */ + 1 /* PADDING */;
			static constexpr size_t ElementsSize = ElementsCount * sizeof(float);

			/**
			 * @brief Constructs a spot light.
			 * @param name The name of the component.
			 * @param parentEntity A reference to the parent entity.
			 */
			SpotLight (const std::string & name, const AbstractEntity & parentEntity) noexcept;

			/** @copydoc Emeraude::Scenes::AbstractComponent::getComponentType() */
			[[nodiscard]]
			const char * getComponentType () const noexcept override;

			/** @copydoc Emeraude::Scenes::AbstractLightEmitter::enableShadow() */
			void enableShadow (bool state, size_t overrideResolution = 0UL) noexcept override;

			/** @copydoc Emeraude::Scenes::AbstractLightEmitter::isShadowEnabled() */
			[[nodiscard]]
			bool isShadowEnabled () const noexcept override;

			/** @copydoc Emeraude::Scenes::AbstractLightEmitter::shadowMap() */
			[[nodiscard]]
			std::shared_ptr< Graphics::RenderTarget::ShadowMap::Abstract > shadowMap () const noexcept override;

			/**
			 * @brief Set the radius of light area.
			 * @param radius
			 */
			void setRadius (float radius) noexcept;

			/**
			 * @brief Sets the inner and the outer angles of the light cone.
			 * @param innerRadian The inner angle in radian of the cone where light is 100%.
			 * @param outerRadian The outer angle in radian of the cone until the light is off.
			 */
			void setConeAngles (float innerRadian, float outerRadian = 0.0F) noexcept;

			/**
			 * @brief Returns the radius of light area.
			 * @return float
			 */
			[[nodiscard]]
			float radius () const noexcept;

			/**
			 * @brief Returns the inner angle in radian of the cone where light is 100%.
			 * @return float
			 */
			[[nodiscard]]
			float innerAngle () const noexcept;

			/**
			 * @brief Returns the cosine of the inner cone angle.
			 * @return float
			 */
			[[nodiscard]]
			float innerCosAngle () const noexcept;

			/**
			 * @brief Returns the outer angle in radian of the cone until the light is off.
			 * @return float
			 */
			[[nodiscard]]
			float outerAngle () const noexcept;

			/**
			 * @brief Returns the cosine of the outer cone angle.
			 * @return float
			 */
			[[nodiscard]]
			float outerCosAngle () const noexcept;

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const SpotLight & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend std::string to_string (const SpotLight & obj) noexcept;

		private:

			/** @copydoc Emeraude::MasterControl::AbstractVirtualVideoDevice::onTargetConnected() */
			void onTargetConnected (AbstractVirtualVideoDevice * targetDevice) noexcept final;

			/** @copydoc Emeraude::Animations::AnimatableInterface::playAnimation() */
			bool playAnimation (Animations::id_t id, const Libraries::Variant & value) noexcept override;

			/**
			 * @brief Sets the inner angle of the cone where light is 100%.
			 * @param radian The angle in radian.
			 */
			void setInnerAngle (float radian) noexcept;

			/**
			 * @brief Sets the outer angle of the cone until the light is off.
			 * @param radian The angle in radian.
			 */
			void setOuterAngle (float radian) noexcept;

			std::shared_ptr< Graphics::RenderTarget::ShadowMap::Texture2D > m_shadowMap{};
			float m_radius{0.0F};
			float m_innerCosAngle{1.0F}; // spotCosCutoff OpenGL parameter
			float m_outerCosAngle{1.0F};
			float m_innerAngleRadians{0.0F};
			float m_outerAngleRadians{0.0F};
	};
}
