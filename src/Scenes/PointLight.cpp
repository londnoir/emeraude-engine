/*
 * Emeraude/Scenes/PointLight.cpp
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

#include "PointLight.hpp"

/* Local inclusions. */
#include "Scene.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Animations;
	using namespace Graphics;

	PointLight::PointLight (const std::string & name, const AbstractEntity & parentEntity) noexcept
		: AbstractLightEmitter(name, parentEntity)
	{

	}

	void
	PointLight::onTargetConnected (AbstractVirtualVideoDevice * targetDevice) noexcept
	{
		const auto maxViewableDistance = m_radius > 0.0F ? m_radius : RenderTarget::ShadowMap::Abstract::getMaxViewableDistance();

		targetDevice->updateDeviceFromCoordinates(this->getWorldCoordinates(), this->getWorldVelocity());
		targetDevice->updateProperties(true, maxViewableDistance, 90.0F);
	}

	bool
	PointLight::playAnimation (Animations::id_t id, const Variant & value) noexcept
	{
		switch ( id )
		{
			case DiffuseColor :
				this->setDiffuseColor(value.asColor());
				return true;

			case Intensity :
				this->setIntensity(value.asFloat());
				return true;

			case Radius :
				this->setRadius(value.asFloat());
				return true;
		}

		return false;
	}

	void
	PointLight::enableShadow (bool state, size_t overrideResolution) noexcept
	{
		auto & console = this->parentEntity().parentScene()->masterControlConsole();

		if ( state )
		{
			const auto resolution = overrideResolution ? overrideResolution : RenderTarget::ShadowMap::Abstract::getBaseResolution();

			m_shadowMap = console.createRenderToCubicShadowMap(this->name() + ShadowMapName, resolution);

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
	PointLight::isShadowEnabled () const noexcept
	{
		return m_shadowMap != nullptr;
	}

	std::shared_ptr< RenderTarget::ShadowMap::Abstract >
	PointLight::shadowMap () const noexcept
	{
		return std::static_pointer_cast< RenderTarget::ShadowMap::Abstract >(m_shadowMap);
	}

	const char *
	PointLight::getComponentType () const noexcept
	{
		return "PointLight";
	}

	void
	PointLight::setRadius (float radius) noexcept
	{
		m_radius = std::abs(radius);
	}

	float
	PointLight::radius () const noexcept
	{
		return m_radius;
	}

	std::ostream &
	operator<< (std::ostream & out, const PointLight & obj)
	{
		const auto worldCoordinates = obj.getWorldCoordinates();

		return out << "Point light data ;\n"
			"Position (World Space) : " << worldCoordinates.position() << "\n"
			"Color : " << obj.diffuseColor() << "\n"
			"Intensity : " << obj.intensity() << "\n"
			"Radius : " << obj.m_radius << "\n"
			"Activity : " << ( obj.isEnabled() ? "true" : "false" ) << "\n"
			"Shadow caster : " << ( obj.isShadowEnabled() ? "true" : "false" ) << '\n';
	}

	std::string
	to_string (const PointLight & obj) noexcept
	{
		return (std::stringstream{} << obj).str();
	}
}
