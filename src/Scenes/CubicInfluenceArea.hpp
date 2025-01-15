/*
 * src/Scenes/CubicInfluenceArea.hpp
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

/* Local inclusions for usages. */
#include "Libraries/Math/Vector.hpp"

/* Forward declarations. */
namespace Emeraude::Scenes
{
	class AbstractEntity;
}

namespace Emeraude::Scenes
{
	/**
	 * @brief Defines a cubic area of influence for a modifier.
	 * @extends Emeraude::Scenes::InfluenceAreaInterface The influence area base class.
	 */
	class CubicInfluenceArea final : public InfluenceAreaInterface
	{
		public:

			/**
			 * @brief Constructs a cubic influence area.
			 * @param parentEntity A reference to the modifier parent scene entity.
			 * @param size Unidirectional size of the area.
			 */
			explicit CubicInfluenceArea (const AbstractEntity & parentEntity, float size = 1.0F) noexcept;

			/**
			 * @brief Constructs a cubic influence area.
			 * @param parentEntity A reference to the modifier parent scene entity.
			 * @param xSize Size of the area in X axis.
			 * @param ySize Size of the area in Y axis.
			 * @param zSize Size of the area in Z axis.
			 */
			CubicInfluenceArea (const AbstractEntity & parentEntity, float xSize, float ySize, float zSize) noexcept;

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
			 * @brief Sets the size of the area.
			 * @param size Unidirectional size of the area.
			 * @return void
			 */
			void setSize (float size) noexcept;

			/**
			 * @brief Sets the size of the area.
			 * @param xSize Size of the area in X axis.
			 * @param ySize Size of the area in Y axis.
			 * @param zSize Size of the area in Z axis.
			 * @return void
			 */
			void setSize (float xSize, float ySize, float zSize) noexcept;

			/**
			 * @brief Returns the size in X axis.
			 * @return float
			 */
			[[nodiscard]]
			float xSize () const noexcept;

			/**
			 * @brief Returns the size in Y axis.
			 * @return float
			 */
			[[nodiscard]]
			float ySize () const noexcept;

			/**
			 * @brief Returns the size in Z axis.
			 * @return float
			 */
			[[nodiscard]]
			float zSize () const noexcept;

		private:

			/**
			 * @brief Gets position in the modifier space.
			 * @param position A reference to a vector.
			 * @return Libraries::Math::Vector< 4, float >
			 */
			[[nodiscard]]
			Libraries::Math::Vector< 4, float > getPositionInModifierSpace (const Libraries::Math::Vector< 3, float > & position) const noexcept;

			const AbstractEntity * m_parentEntity{nullptr};
			float m_xSize;
			float m_ySize;
			float m_zSize;
	};
}
