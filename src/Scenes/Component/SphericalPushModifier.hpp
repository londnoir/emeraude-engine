/*
 * src/Scenes/Component/SphericalPushModifier.hpp
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

/* STL inclusions. */
#include <string>

/* Local inclusions for inheritances. */
#include "AbstractModifier.hpp"

/* Local inclusions for usages. */
#include "Libraries/Math/CartesianFrame.hpp"
#include "Libraries/Math/Sphere.hpp"
#include "Libraries/Math/Cuboid.hpp"
#include "Libraries/Variant.hpp"
#include "Physics/MovableTrait.hpp"
#include "Abstract.hpp"
#include "Animations/Types.hpp"

namespace Emeraude::Scenes::Component
{
	/**
	 * @brief Defines a spherical push modifier to make move physical object.
	 * @extends Emeraude::Scenes::Component::AbstractModifier The base class for modifier.
	 */
	class SphericalPushModifier final : public AbstractModifier
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"SphericalPushModifier"};

			/** @brief Animatable Interface key */
			static constexpr auto Magnitude{0UL};

			/**
			 * @brief Constructs a spherical push modifier.
			 * @param name The name of the modifier.
			 * @param parentEntity A reference to the parent entity.
			 */
			SphericalPushModifier (const std::string & name, const AbstractEntity & parentEntity) noexcept;

			/** @copydoc Emeraude::Scenes::Component::Abstract::getComponentType() */
			[[nodiscard]]
			const char *
			getComponentType () const noexcept override
			{
				return ClassId;
			}

			/** @copydoc Emeraude::Scenes::Component::Abstract::boundingBox() const */
			[[nodiscard]]
			const Libraries::Math::Cuboid< float > &
			boundingBox () const noexcept override
			{
				return NullBoundingBox;
			}

			/** @copydoc Emeraude::Scenes::Component::Abstract::boundingSphere() const */
			[[nodiscard]]
			const Libraries::Math::Sphere< float > &
			boundingSphere () const noexcept override
			{
				return NullBoundingSphere;
			}

			/** @copydoc Emeraude::Scenes::Component::Abstract::processLogics() */
			void processLogics (const Scene & scene) noexcept override;

			/** @copydoc Emeraude::Scenes::Component::Abstract::move() */
			void move (const Libraries::Math::CartesianFrame< float > & worldCoordinates) noexcept override;

			/** @copydoc Emeraude::Scenes::Component::Abstract::shouldRemove() */
			bool shouldRemove () const noexcept override;

			/** @copydoc Emeraude::Scenes::Component::AbstractModifier::getForceAppliedToEntity(const Libraries::Math::CartesianFrame< float > &, const Libraries::Math::Sphere< float > &) */
			Libraries::Math::Vector< 3, float > getForceAppliedToEntity (const Libraries::Math::CartesianFrame< float > & worldCoordinates, const Libraries::Math::Sphere< float > & worldBoundingSphere) const noexcept override;

			/** @copydoc Emeraude::Scenes::Component::AbstractModifier::getForceAppliedToEntity(const Libraries::Math::CartesianFrame< float > &, const Libraries::Math::Cuboid< float > &) */
			Libraries::Math::Vector< 3, float > getForceAppliedToEntity (const Libraries::Math::CartesianFrame< float > & worldCoordinates, const Libraries::Math::Cuboid< float > & worldBoundingBox) const noexcept override;

			/**
			 * @brief Sets the constant push magnitude.
			 * @param magnitude The value
			 * @return void
			 */
			void
			setMagnitude (float magnitude) noexcept
			{
				m_magnitude = std::abs(magnitude);
			}

			/**
			 * @brief Returns the constant push magnitude.
			 * @return float
			 */
			[[nodiscard]]
			float
			magnitude () const noexcept
			{
				return m_magnitude;
			}

		private:

			/** @copydoc Emeraude::Animations::AnimatableInterface::playAnimation() */
			bool playAnimation (Animations::id_t identifier, const Libraries::Variant & value) noexcept override;

			float m_magnitude{1.0F};
	};
}
