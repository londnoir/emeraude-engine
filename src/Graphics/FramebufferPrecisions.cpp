/*
 * Emeraude/Graphics/FramebufferPrecisions.cpp
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

#include "FramebufferPrecisions.hpp"

namespace Emeraude::Graphics
{
	FramebufferPrecisions::FramebufferPrecisions (uint32_t redBits, uint32_t greenBits, uint32_t blueBits, uint32_t alphaBits, uint32_t depthBits, uint32_t stencilBits, uint32_t samples) noexcept
		: m_redBits(redBits), m_greenBits(greenBits), m_blueBits(blueBits), m_alphaBits(alphaBits), m_depthBits(depthBits), m_stencilBits(stencilBits), m_samples(samples)
	{

	}

	uint32_t
	FramebufferPrecisions::redBits () const noexcept
	{
		return m_redBits;
	}

	uint32_t
	FramebufferPrecisions::greenBits () const noexcept
	{
		return m_greenBits;
	}

	uint32_t
	FramebufferPrecisions::blueBits () const noexcept
	{
		return m_blueBits;
	}

	uint32_t
	FramebufferPrecisions::alphaBits () const noexcept
	{
		return m_alphaBits;
	}

	uint32_t
	FramebufferPrecisions::colorBits () const noexcept
	{
		return m_redBits + m_greenBits + m_blueBits + m_alphaBits;
	}

	uint32_t
	FramebufferPrecisions::depthBits () const noexcept
	{
		return m_depthBits;
	}

	uint32_t
	FramebufferPrecisions::stencilBits () const noexcept
	{
		return m_stencilBits;
	}

	uint32_t
	FramebufferPrecisions::samples () const noexcept
	{
		return m_samples;
	}
}
