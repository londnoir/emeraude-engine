/*
 * Emeraude/Physics/PhysicalEnvironmentProperties.hpp
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

/* Local inclusions for usages. */
#include "Physics.hpp"

namespace Emeraude::Physics
{
	/**
	 * @brief The PhysicalEnvironmentProperties class
	 */
	class PhysicalEnvironmentProperties final
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"PhysicalEnvironmentProperties"};

			/**
			 * @brief Constructs physical environment properties.
			 * @param surfaceGravity The gravity at surface expressed in m/s².
			 * @param atmosphericDensity The atmospheric density expressed in kg/m³.
			 * @param planetRadius The radius of the planet environment in m.
			 */
			PhysicalEnvironmentProperties (float surfaceGravity, float atmosphericDensity, float planetRadius) noexcept;

			/**
			 * @brief Returns the gravity in m/s².
			 * @brief altitude The altitude in meters. Default at surface.
			 * @return float
			 */
			[[nodiscard]]
			float gravity (float altitude = 0.0F) const noexcept;

			/**
			 * @brief Returns the atmospheric density expressed in kg/m³.
			 * @param altitude The altitude in meters. Default at surface.
			 * @param temperature The ambient temperature in degree C°. Default 20.
			 * @return float
			 */
			[[nodiscard]]
			float atmosphericDensity (float altitude = 0.0F, float temperature = 20.0F) const noexcept; // NOLINT(*-magic-numbers)

			/**
			 * @brief Returns the planet radius in m.
			 * @return float
			 */
			[[nodiscard]]
			float planetRadius () const noexcept;

			/**
			 * @brief Returns earth environment properties.
			 * @return PhysicalEnvironmentProperties
			 */
			inline
			static
			PhysicalEnvironmentProperties
			Earth () noexcept
			{
				return {Gravity::Earth< float >, Density::EarthStandardAir< float >, Radius::Earth< float >};
			}

			/**
			 * @brief Returns moon environment properties.
			 * @return PhysicalEnvironmentProperties
			 */
			inline
			static
			PhysicalEnvironmentProperties
			Moon () noexcept
			{
				return {Gravity::Moon< float >, 0.0F, Radius::Moon< float >};
			}

			/**
			 * @brief Returns mars environment properties.
			 * @return PhysicalEnvironmentProperties
			 */
			inline
			static
			PhysicalEnvironmentProperties
			Mars () noexcept
			{
				return {Gravity::Mars< float >, 0.020F, Radius::Mars< float >}; // NOLINT(*-magic-numbers)
			}

			/**
			 * @brief Returns jupiter environment properties.
			 * @return PhysicalEnvironmentProperties
			 */
			inline
			static
			PhysicalEnvironmentProperties
			Jupiter () noexcept
			{
				return {Gravity::Jupiter< float >, 1.326F, Radius::Jupiter< float >}; // NOLINT(*-magic-numbers)
			}

			/**
			 * @brief Returns space environment properties.
			 * @return PhysicalEnvironmentProperties
			 */
			inline
			static
			PhysicalEnvironmentProperties
			Void () noexcept
			{
				return {0.0F, 0.0F, 0.0F};
			}

		private:

			float m_surfaceGravity;
			float m_atmosphericDensity;
			float m_planetRadius;
	};
}
