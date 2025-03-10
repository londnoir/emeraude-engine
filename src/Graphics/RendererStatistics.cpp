/*
 * src/Graphics/RendererStatistics.cpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2025 - Sébastien Léon Claude Christian Bémelmans "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Emeraude-Engine; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Complete project and additional information can be found at :
 * https://github.com/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#include "RendererStatistics.hpp"

/* STL inclusions. */
#include <numeric>

namespace Emeraude::Graphics
{
	using namespace Libraries;

	RendererStatistics::RendererStatistics () noexcept
	{

	}

	void
	RendererStatistics::initialize (size_t averageRange) noexcept
	{
		m_averageRange = std::max< size_t >(averageRange, 3);

		for ( auto & stat : m_CPUStats )
		{
			stat.second.resize(m_averageRange, 0);
		}

		/* VULKAN_DEV */
		/*for ( auto & stat : m_GPUStats )
		{
			stat.first.create();
			stat.second.resize(m_averageRange, 0);
		}*/
	}

	void
	RendererStatistics::update () noexcept
	{
		for ( auto & stat : m_CPUStats )
		{
			const auto nanoseconds = stat.first.duration();

			stat.second[m_averageIndex] = nanoseconds;
		}

		/* VULKAN_DEV */
		/*for ( auto & stat : m_GPUStats )
		{
			const auto nanoseconds = stat.first.duration(true);

			stat.second[m_averageIndex] = nanoseconds;
		}*/

		m_averageIndex++;

		if ( m_averageIndex >= m_averageRange )
			m_averageIndex = 0;
	}

	void
	RendererStatistics::startStatistics (Type type) noexcept
	{
		const auto index = static_cast< size_t >(type);

		m_CPUStats[index].first.start();
		//m_GPUStats[index].first.begin();
	}

	void
	RendererStatistics::stopStatistics (Type type) noexcept
	{
		const auto index = static_cast< size_t >(type);

		//m_GPUStats[index].first.end();
		m_CPUStats[index].first.stop();
	}

	unsigned long int
	RendererStatistics::lastCPUStatistic (Type type) const noexcept
	{
		return m_CPUStats[static_cast< size_t >(type)].second[m_averageIndex];
	}

	unsigned long int
	RendererStatistics::lastGPUStatistic (Type /*type*/) const noexcept
	{
		/* VULKAN_DEV */
		//return m_GPUStats[static_cast< size_t >(type)].second[m_averageIndex];
		return 0;
	}

	double
	RendererStatistics::averageCPUStatistic (Type type) const noexcept
	{
		const auto stat = m_CPUStats[static_cast< size_t >(type)].second;

		return std::accumulate(stat.cbegin(), stat.cend(), 0) / static_cast< double >(stat.size());
	}

	double
	RendererStatistics::averageGPUStatistic (Type /*type*/) const noexcept
	{
		/* VULKAN_DEV */
		/*const auto stat = m_GPUStats[static_cast< size_t >(type)].second;

		return std::accumulate(stat.cbegin(), stat.cend(), 0) / static_cast< double >(stat.size());*/
		return 0;
	}
}
