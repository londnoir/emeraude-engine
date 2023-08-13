/*
 * Emeraude/Graphics/RendererStatistics.hpp
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
#include <vector>

/* Local inclusions */
#include "Time/ElapsedTime.hpp"
/* VULKAN_DEV */
//#include "QueryTimeElapsed.hpp"

namespace Emeraude::Graphics
{
	/**
	 * @brief The RendererStatistics class
	 */
	class RendererStatistics final
	{
		public:

			enum class Type : size_t
			{
				ShadowMap = 0UL,
				RenderToTarget = 1UL,
				Frame = 2UL,
				Overlay = 3UL
			};

			/** @brief Default constructor. */
			RendererStatistics () noexcept;

			/**
			 * @brief Initializes counters.
			 * @param averageRange The number of stat taken to make the average.
			 */
			void initialize (size_t averageRange = 30) noexcept;

			/** @brief Updates the average statistics. */
			void update () noexcept;

			/**
			 * @brief Starts a statistic.
			 * @param type The type of statistic taken.
			 */
			void startStatistics (Type type) noexcept;

			/**
			 * @brief Stops a statistic.
			 * @param type The type of statistic taken.
			 */
			void stopStatistics (Type type) noexcept;

			/**
			 * @brief lastCPUStatistic
			 * @param type
			 * @return unsigned long int
			 */
			[[nodiscard]]
			unsigned long int lastCPUStatistic (Type type) const noexcept;

			/**
			 * @brief lastGPUStatistic
			 * @param type
			 * @return unsigned long int
			 */
			[[nodiscard]]
			unsigned long int lastGPUStatistic (Type type) const noexcept;

			/**
			 * @brief averageCPUStatistic
			 * @param type
			 * @return double
			 */
			[[nodiscard]]
			double averageCPUStatistic (Type type) const noexcept;

			/**
			 * @brief averageGPUStatistic
			 * @param type
			 * @return double
			 */
			[[nodiscard]]
			double averageGPUStatistic (Type type) const noexcept;

		private:

			std::array< std::pair< Libraries::Time::ElapsedTime< std::chrono::high_resolution_clock >, std::vector< unsigned long int > >, 4 > m_CPUStats{};
			/* VULKAN_DEV */
			//std::array< std::pair< QueryTimeElapsed, std::vector< unsigned long int > >, 4 > m_GPUStats{};
			size_t m_averageRange = 1;
			size_t m_averageIndex = 0;
	};
}
