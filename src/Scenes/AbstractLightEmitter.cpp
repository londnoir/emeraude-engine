/*
 * Emeraude/Scenes/AbstractLightEmitter.cpp
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

#include "AbstractLightEmitter.hpp"

/* Local inclusions. */
#include "Graphics/ViewMatricesInterface.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Libraries::PixelFactory;
	using namespace Graphics;

	AbstractLightEmitter::AbstractLightEmitter (const std::string & name, const AbstractEntity & parentEntity) noexcept
		: AbstractComponent(name, parentEntity), MasterControl::AbstractVirtualVideoDevice(name, MasterControl::ConnexionType::Output)
	{

	}

	MasterControl::VideoType
	AbstractLightEmitter::videoType () const noexcept
	{
		return MasterControl::VideoType::Light;
	}

	void
	AbstractLightEmitter::enable (bool state) noexcept
	{
		m_flags[Enabled] = state;
	}

	bool
	AbstractLightEmitter::toggle () noexcept
	{
		return m_flags[Enabled] = !m_flags[Enabled];
	}

	bool
	AbstractLightEmitter::isEnabled () const noexcept
	{
		return m_flags[Enabled];
	}

	void
	AbstractLightEmitter::setColor (const Color< float > & color) noexcept
	{
		m_ambientColor = color * 0.05F;
		m_diffuseColor = color;
		m_specularColor = color;
	}

	void
	AbstractLightEmitter::setAmbientColor (const Color< float > & color) noexcept
	{
		m_ambientColor = color;
	}

	void
	AbstractLightEmitter::setDiffuseColor (const Color< float > & color) noexcept
	{
		m_diffuseColor = color;
	}

	void
	AbstractLightEmitter::setSpecularColor (const Color< float > & color) noexcept
	{
		m_specularColor = color;
	}

	void
	AbstractLightEmitter::setIntensity (float intensity) noexcept
	{
		m_intensity = intensity;
	}

	const Color< float > &
	AbstractLightEmitter::ambientColor () const noexcept
	{
		return m_ambientColor;
	}

	const Color< float > &
	AbstractLightEmitter::diffuseColor () const noexcept
	{
		return m_diffuseColor;
	}

	const Color< float > &
	AbstractLightEmitter::specularColor () const noexcept
	{
		return m_specularColor;
	}

	float
	AbstractLightEmitter::intensity () const noexcept
	{
		return m_intensity;
	}

	Vector< 4, float >
	AbstractLightEmitter::intensifiedColor (const Color< float > & color, float intensity) noexcept
	{
		return {color.red() * intensity, color.green() * intensity, color.blue() * intensity, 1.0F};
	}

	Matrix< 4, float >
	AbstractLightEmitter::getLightSpaceMatrix () const noexcept
	{
		if ( !this->isShadowEnabled() )
		{
			return Matrix< 4, float >::identity();
		}

		return RenderTarget::ShadowMap::Abstract::ScaleBiasMatrix * this->shadowMap()->viewMatrices().viewProjectionMatrix(0);
	}

	void
	AbstractLightEmitter::move () noexcept
	{
		if ( !this->isEnabled() )
		{
			return;
		}

		this->updateDeviceFromCoordinates(this->getWorldCoordinates(), this->getWorldVelocity());
	}

	void
	AbstractLightEmitter::processLogics (const Scene &, size_t cycle) noexcept
	{
		if ( !this->isEnabled() )
		{
			return;
		}

		this->updateAnimations(cycle);

		this->updateDeviceFromCoordinates(this->getWorldCoordinates(), this->getWorldVelocity());
	}

	void
	AbstractLightEmitter::updateDeviceFromCoordinates (const Coordinates< float > & worldCoordinates, const Vector< 3, float > & worldVelocity) noexcept
	{
		if ( !this->hasOutputConnected() )
		{
			return;
		}

		for ( const auto & output : this->outputs() )
		{
			output->updateDeviceFromCoordinates(worldCoordinates, worldVelocity);
		}
	}

	void
	AbstractLightEmitter::updateProperties (bool isPerspectiveProjection, float distance, float fovOrNear) noexcept
	{
		if ( !this->hasOutputConnected() )
		{
			return;
		}

		for ( const auto & output : this->outputs() )
		{
			auto videoDevice = std::dynamic_pointer_cast< MasterControl::AbstractVirtualVideoDevice >(output);

			videoDevice->updateProperties(isPerspectiveProjection, distance, fovOrNear);
		}
	}
}
