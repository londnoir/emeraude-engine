/*
 * src/Scenes/SphericalInfluenceArea.hpp
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

/* Local inclusions for inheritances. */
#include "InfluenceAreaInterface.hpp"

/* Forward declarations. */
namespace Emeraude::Scenes
{
	class AbstractEntity;
}

namespace Emeraude::Scenes
{
	/**
	 * @brief Defines a spherical area of influence for a modifier.
	 * @extends Emeraude::Scenes::InfluenceAreaInterface The influence area base class.
	 */
	class SphericalInfluenceArea final : public InfluenceAreaInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"SphericalInfluenceArea"};

			/**
			 * @brief Constructs a spherical influence area.
			 * @param parentEntity A reference to the modifier parent scene entity.
			 */
			explicit SphericalInfluenceArea (const AbstractEntity & parentEntity) noexcept;

			/**
			 * @brief Constructs a spherical influence area.
			 * @param parentEntity A reference to the modifier parent scene entity.
			 * @param outerRadius The outer limit of influence, behind this radius the influence is null.
			 * @param innerRadius The inner limit of influence, below this radius the influence is 100%.
			 */
			SphericalInfluenceArea (const AbstractEntity & parentEntity, float outerRadius, float innerRadius) noexcept;

			/** @copydoc Emeraude::Scenes::InfluenceAreaInterface::isUnderInfluence(const Libraries::Math::CartesianFrame< float > &, const Libraries::Math::Sphere< float > &) */
			[[nodiscard]]
			bool isUnderInfluence (const Libraries::Math::CartesianFrame< float > & worldCoordinates, const Libraries::Math::Sphere< float > & worldBoundingSphere) const noexcept override;

			/** @copydoc Emeraude::Scenes::InfluenceAreaInterface::influenceStrength(const Libraries::Math::CartesianFrame< float > &, const Libraries::Math::Sphere< float > &) */
			[[nodiscard]]
			float influenceStrength (const Libraries::Math::CartesianFrame< float > & worldCoordinates, const Libraries::Math::Sphere< float > & worldBoundingSphere) const noexcept override;

			/** @copydoc Emeraude::Scenes::InfluenceAreaInterface::isUnderInfluence(const Libraries::Math::CartesianFrame< float > &, const Libraries::Math::Cuboid< float > &) */
			[[nodiscard]]
			bool isUnderInfluence (const Libraries::Math::CartesianFrame< float > & worldCoordinates, const Libraries::Math::Cuboid< float > & worldBoundingBox) const noexcept override;

			/** @copydoc Emeraude::Scenes::InfluenceAreaInterface::influenceStrength(const Libraries::Math::CartesianFrame< float > &, const Libraries::Math::Cuboid< float > &) */
			[[nodiscard]]
			float influenceStrength (const Libraries::Math::CartesianFrame< float > & worldCoordinates, const Libraries::Math::Cuboid< float > & worldBoundingBox) const noexcept override;

			/**
			 * @brief Sets the outer radius.
			 * @param radius The radius. Behind this radius the influence is null.
			 * @return void
			 */
			void setOuterRadius (float radius) noexcept;

			/**
			 * @brief Sets the inner radius.
			 * @param radius The radius. Below this radius the influence is 100%.
			 * @return void
			 */
			void setInnerRadius (float radius) noexcept;

			/**
			 * @brief Returns the outer radius.
			 * @return float
			 */
			[[nodiscard]]
			float outerRadius () const noexcept;

			/**
			 * @brief Returns the outer radius.
			 * @return float
			 */
			[[nodiscard]]
			float innerRadius () const noexcept;

		private:

			const AbstractEntity * m_parentEntity{nullptr};
			float m_outerRadius{1.0F};
			float m_innerRadius{0.0F};
	};
}
