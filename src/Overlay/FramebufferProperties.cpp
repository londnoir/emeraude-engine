/*
 * src/Overlay/FramebufferProperties.cpp
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

#include "FramebufferProperties.hpp"

/* STL inclusions. */
#include <array>
#include <cmath>
#include <cstdint>
#include <ostream>
#include <sstream>
#include <string>

namespace Emeraude::Overlay
{
	FramebufferProperties::FramebufferProperties (uint32_t width, uint32_t height, float scaleX, float scaleY) noexcept
		: m_resolution{width, height}, m_scaleX(scaleX), m_scaleY(scaleY)
	{
		this->updateScaledResolution();
	}

	FramebufferProperties::FramebufferProperties (const std::array< uint32_t, 2 > & data, float scaleX, float scaleY) noexcept
		: m_resolution(data), m_scaleX(scaleX), m_scaleY(scaleY)
	{
		this->updateScaledResolution();
	}

	void
	FramebufferProperties::updateProperties (uint32_t width, uint32_t height, float scaleX, float scaleY) noexcept
	{
		m_resolution[0] = width;
		m_resolution[1] = height;

		this->setScale(scaleX, scaleY);
	}

	void
	FramebufferProperties::updateProperties (const std::array< uint32_t, 2 > & data, float scaleX, float scaleY) noexcept
	{
		m_resolution = data;

		this->setScale(scaleX, scaleY);
	}

	void
	FramebufferProperties::updateScaledResolution () noexcept
	{
		if ( m_scaleX <= 0.0F )
		{
			m_scaleX = 1.0F;
		}

		if ( m_scaleY <= 0.0F )
		{
			m_scaleY = 1.0F;
		}

		m_inverseScaleX = 1.0F / m_scaleX;
		m_inverseScaleY = 1.0F / m_scaleY;

		const auto scaledWidth = std::floor(static_cast< float >(m_resolution[0]) * m_inverseScaleX);
		const auto scaledHeight = std::floor(static_cast< float >(m_resolution[1]) * m_inverseScaleY);

		m_scaledResolution[0] = static_cast< uint32_t >(scaledWidth);
		m_scaledResolution[1] = static_cast< uint32_t >(scaledHeight);
	}

	void
	FramebufferProperties::setResolution (uint32_t width, uint32_t height) noexcept
	{
		m_resolution[0] = width;
		m_resolution[1] = height;

		this->updateScaledResolution();
	}

	void
	FramebufferProperties::setResolution (const std::array< uint32_t, 2 > & data) noexcept
	{
		m_resolution = data;

		this->updateScaledResolution();
	}

	void
	FramebufferProperties::setScale (float scaleX, float scaleY) noexcept
	{
		m_scaleX = scaleX;
		m_scaleY = scaleY;

		this->updateScaledResolution();
	}

	void
	FramebufferProperties::setScale (float scale) noexcept
	{
		m_scaleX = scale;
		m_scaleY = scale;

		this->updateScaledResolution();
	}

	void
	FramebufferProperties::reset () noexcept
	{
		m_resolution[0] = 0;
		m_resolution[1] = 0;
		m_scaledResolution[0] = 0;
		m_scaledResolution[1] = 0;
		m_scaleX = 1.0F;
		m_scaleY = 1.0F;
		m_inverseScaleX = 1.0F;
		m_inverseScaleY = 1.0F;
	}

	bool
	FramebufferProperties::isValid () const noexcept
	{
		return m_resolution[0] * m_resolution[1] != 0;
	}

	const std::array< uint32_t, 2 > &
	FramebufferProperties::resolution () const noexcept
	{
		return m_resolution;
	}

	uint32_t
	FramebufferProperties::width () const noexcept
	{
		return m_resolution[0];
	}

	uint32_t
	FramebufferProperties::height () const noexcept
	{
		return m_resolution[1];
	}

	float
	FramebufferProperties::scaleX () const noexcept
	{
		return m_scaleX;
	}

	float
	FramebufferProperties::scaleY () const noexcept
	{
		return m_scaleY;
	}

	float
	FramebufferProperties::inverseScaleX () const noexcept
	{
		return m_inverseScaleX;
	}

	float
	FramebufferProperties::inverseScaleY () const noexcept
	{
		return m_inverseScaleY;
	}

	const std::array< uint32_t, 2 > &
	FramebufferProperties::scaledResolution () const noexcept
	{
		return m_scaledResolution;
	}

	uint32_t
	FramebufferProperties::scaledWidth () const noexcept
	{
		return m_scaledResolution[0];
	}

	uint32_t
	FramebufferProperties::scaledHeight () const noexcept
	{
		return m_scaledResolution[1];
	}

	std::ostream &
	operator<< (std::ostream & out, const FramebufferProperties & obj)
	{
		return out <<
			"Resolution: " << obj.width() << "x" << obj.height() << "px" "\n"
			"Scale X: " << obj.scaleX() << ", Scale Y: " << obj.scaleY() << "\n"
			"Scaled resolution: " << obj.scaledWidth() << "x" << obj.scaledHeight() << "pt" "\n";
	}

	std::string
	to_string (const FramebufferProperties & obj) noexcept
	{
		std::stringstream output;

		output << obj;

		return output.str();
	}
}
