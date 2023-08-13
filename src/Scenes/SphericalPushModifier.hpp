/*
 * Emeraude/Scenes/SphericalPushModifier.hpp
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

/* Local inclusions for inheritances. */
#include "AbstractModifier.hpp"

namespace Emeraude::Scenes
{
	/**
	 * @brief Defines a spherical push modifier to make move physical object.
	 * @extends Emeraude::Scenes::AbstractLightEmitter The base class for modifier.
	 */
	class SphericalPushModifier final : public AbstractModifier
	{
		public:

			/** @brief Animable Interface key */
			static constexpr auto Magnitude = 0UL;

			/**
			 * @brief Constructs a spherical push modifier.
			 * @param name The name of the modifier.
			 * @param parentEntity A reference to the parent entity.
			 */
			SphericalPushModifier (const std::string & name, const AbstractEntity & parentEntity) noexcept;

			/** @copydoc Emeraude::Scenes::AbstractModifier::apply() */
			void apply (Physics::MovableTrait & movable) const noexcept override;

			/** @copydoc Emeraude::Scenes::AbstractComponent::getComponentType() */
			[[nodiscard]]
			const char * getComponentType () const noexcept override;

			/**
			 * @brief setMagnitude
			 * @param magnitude
			 */
			void setMagnitude (float magnitude) noexcept;

			/**
			 * @brief magnitude
			 * @return float
			 */
			[[nodiscard]]
			float magnitude () const noexcept;

		private:

			/** @copydoc Emeraude::Scenes::AbstractComponent::move() */
			void move () noexcept override;

			/** @copydoc Emeraude::Scenes::AbstractComponent::processLogics() */
			void processLogics (const Scene & scene, size_t cycle) noexcept override;

			/** @copydoc Emeraude::Animations::AnimatableInterface::playAnimation() */
			bool playAnimation (Animations::id_t id, const Libraries::Variant & value) noexcept override;

			float m_magnitude = 1.0F;
	};
}
