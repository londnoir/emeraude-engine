/*
 * Emeraude/Scenes/DirectionalLight.hpp
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
	 * @brief Defines a scene directional light like the sun.
	 * @extends Emeraude::Scenes::AbstractLightEmitter The base class for each light type.
	 */
	class DirectionalLight final : public AbstractLightEmitter
	{
		public:

			/** @brief Animatable Interface keys */
			static constexpr auto DiffuseColor = 0UL;
			static constexpr auto SpecularColor = 1UL;
			static constexpr auto Intensity = 2UL;

			static constexpr size_t ElementsCount = 4/* diffuse color */ + 4/* specular color */ + 4/* direction */;
			static constexpr size_t ElementsSize = ElementsCount * sizeof(float);

			/**
			 * @brief Constructs a directional light.
			 * @param name The name of the component.
			 * @param parentEntity A reference to the parent entity.
			 */
			DirectionalLight (const std::string & name, const AbstractEntity & parentEntity) noexcept;

			/** @copydoc Emeraude::Scenes::AbstractComponent::getComponentType() */
			[[nodiscard]]
			const char * getComponentType () const noexcept override;

			/** @copydoc Emeraude::Scenes::AbstractLightEmitter::enableShadow() */
			void enableShadow (bool state, size_t overrideResolution = 0) noexcept override;

			/** @copydoc Emeraude::Scenes::AbstractLightEmitter::isShadowEnabled() */
			[[nodiscard]]
			bool isShadowEnabled () const noexcept override;

			/** @copydoc Emeraude::Scenes::AbstractLightEmitter::shadowMap() */
			[[nodiscard]]
			std::shared_ptr< Graphics::RenderTarget::ShadowMap::Abstract > shadowMap () const noexcept override;

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const DirectionalLight & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend std::string to_string (const DirectionalLight & obj) noexcept;

		private:

			/** @copydoc Emeraude::MasterControl::AbstractVirtualVideoDevice::onTargetConnected() */
			void onTargetConnected (AbstractVirtualVideoDevice * targetDevice) noexcept final;

			/** @copydoc Emeraude::Animations::AnimatableInterface::playAnimation() */
			bool playAnimation (Animations::id_t id, const Libraries::Variant & value) noexcept override;

			std::shared_ptr< Graphics::RenderTarget::ShadowMap::Texture2D > m_shadowMap{};
	};
}
