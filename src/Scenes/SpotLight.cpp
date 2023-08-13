/*
 * Emeraude/Scenes/SpotLight.cpp
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

#include "SpotLight.hpp"

/* Local inclusions. */
#include "Scene.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Animations;
	using namespace Graphics;

	SpotLight::SpotLight (const std::string & name, const AbstractEntity & parentEntity) noexcept
		: AbstractLightEmitter(name, parentEntity)
	{
		this->setConeAngles(Radian(30.0F), Radian(35.0F));
	}

	void
	SpotLight::onTargetConnected (AbstractVirtualVideoDevice * targetDevice) noexcept
	{
		const auto maxViewableDistance = m_radius > 0.0F ? m_radius : RenderTarget::ShadowMap::Abstract::getMaxViewableDistance();
		const auto fov = Degree(2.0F * m_outerAngleRadians);

		targetDevice->updateDeviceFromCoordinates(this->getWorldCoordinates(), this->getWorldVelocity());
		targetDevice->updateProperties(true, maxViewableDistance, fov);
	}

	bool
	SpotLight::playAnimation (Animations::id_t id, const Variant & value) noexcept
	{
		switch ( id )
		{
			case DiffuseColor :
				this->setDiffuseColor(value.asColor());
				return true;

			case Intensity :
				this->setIntensity(value.asFloat());
				return true;

			case Radius :/* Local inclusions. */
				this->setRadius(value.asFloat());
				return true;

			case InnerAngle :
				this->setInnerAngle(value.asFloat());
				return true;

			case OuterAngle :
				this->setOuterAngle(value.asFloat());
				return true;
		}

		return false;
	}

	void
	SpotLight::enableShadow (bool state, size_t overrideResolution) noexcept
	{
		auto & console = this->parentEntity().parentScene()->masterControlConsole();

		if ( state )
		{
			const auto resolution = overrideResolution ? overrideResolution : RenderTarget::ShadowMap::Abstract::getBaseResolution() * 2UL;

			m_shadowMap = console.createRenderToShadowMap(this->name() + ShadowMapName, resolution);

			if ( m_shadowMap == nullptr )
			{
				Tracer::warning(ClassId, "Unable to create the render to shadow map !");

				return;
			}

			this->connect(m_shadowMap);
		}
		else
		{
			this->disconnect(m_shadowMap);

			console.removeVideoDevice(m_shadowMap);

			m_shadowMap.reset();
		}
	}

	bool
	SpotLight::isShadowEnabled () const noexcept
	{
		return m_shadowMap != nullptr;
	}

	std::shared_ptr< RenderTarget::ShadowMap::Abstract >
	SpotLight::shadowMap () const noexcept
	{
		return std::static_pointer_cast< RenderTarget::ShadowMap::Abstract >(m_shadowMap);
	}

	void
	SpotLight::setRadius (float radius) noexcept
	{
		m_radius = std::abs(radius);
	}

	void
	SpotLight::setConeAngles (float innerRadian, float outerRadian) noexcept
	{
		if ( outerRadian <= 0.0F )
			outerRadian = innerRadian;
		else if ( innerRadian > outerRadian )
			std::swap(innerRadian, outerRadian);

		this->setInnerAngle(innerRadian);

		this->setOuterAngle(outerRadian);
	}

	const char *
	SpotLight::getComponentType () const noexcept
	{
		return "SpotLight";
	}

	float
	SpotLight::radius () const noexcept
	{
		return m_radius;
	}

	float
	SpotLight::innerAngle () const noexcept
	{
		return m_innerAngleRadians;
	}

	float
	SpotLight::innerCosAngle () const noexcept
	{
		return m_innerCosAngle;
	}

	float
	SpotLight::outerAngle () const noexcept
	{
		return m_outerAngleRadians;
	}

	float
	SpotLight::outerCosAngle () const noexcept
	{
		return m_outerCosAngle;
	}

	void
	SpotLight::setInnerAngle (float radian) noexcept
	{
		m_innerAngleRadians = radian;
		m_innerCosAngle = std::cos(radian);
	}

	void
	SpotLight::setOuterAngle (float radian) noexcept
	{
		m_outerAngleRadians = radian;
		m_outerCosAngle = std::cos(radian);

		if ( m_shadowMap != nullptr )
		{
			const auto fov = Degree(2.0F * m_outerAngleRadians);
			const auto maxViewableDistance = RenderTarget::ShadowMap::Abstract::getMaxViewableDistance();

			this->updateProperties(true, maxViewableDistance, fov);
		}
	}

	std::ostream &
	operator<< (std::ostream & out, const SpotLight & obj)
	{
		const auto worldCoordinates = obj.getWorldCoordinates();

		return out << "Spot light data ;\n"
			"Position (World Space) : " << worldCoordinates.position() << "\n"
			"Direction (World Space) : " << worldCoordinates.forwardVector().inversed() << "\n"
			"Color : " << obj.diffuseColor() << "\n"
			"Intensity : " << obj.intensity() << "\n"
			"Radius : " << obj.m_radius << "\n"
			"Cone inner angle : " << obj.m_innerAngleRadians << "° (cosine : " << obj.m_innerCosAngle << " rad)\n"
			"Cone outer angle : " << obj.m_outerAngleRadians << "° (cosine : " << obj.m_outerCosAngle << " rad)\n"
			"Activity : " << ( obj.isEnabled() ? "true" : "false" ) << "\n"
			"Shadow caster : " << ( obj.isShadowEnabled() ? "true" : "false" ) << '\n';
	}

	std::string
	to_string (const SpotLight & obj) noexcept
	{
		return (std::stringstream{} << obj).str();
	}
}
