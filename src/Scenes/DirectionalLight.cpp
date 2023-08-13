/*
 * Emeraude/Scenes/DirectionalLight.cpp
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

#include "DirectionalLight.hpp"

/* Local inclusions. */
#include "Scene.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Animations;
	using namespace Graphics;

	/** @brief Class identifier. */
	static constexpr auto ClassId{"DirectionalLight"};

	DirectionalLight::DirectionalLight (const std::string & name, const AbstractEntity & parentEntity) noexcept
		: AbstractLightEmitter(name, parentEntity)
	{

	}

	void
	DirectionalLight::onTargetConnected (AbstractVirtualVideoDevice * targetDevice) noexcept
	{
		const auto maxViewableDistance = RenderTarget::ShadowMap::Abstract::getMaxViewableDistance() * 8UL;

		targetDevice->updateDeviceFromCoordinates(this->getWorldCoordinates(), this->getWorldVelocity());
		targetDevice->updateProperties(false, maxViewableDistance, 0.0F);
	}

	bool
	DirectionalLight::playAnimation (Animations::id_t id, const Variant & value) noexcept
	{
		switch ( id )
		{
			case DiffuseColor :
				this->setDiffuseColor(value.asColor());
				return true;

			case Intensity :
				this->setIntensity(value.asFloat());
				return true;

			default:
				return false;
		}
	}

	void
	DirectionalLight::enableShadow (bool state, size_t overrideResolution) noexcept
	{
		auto & console = this->parentEntity().parentScene()->masterControlConsole();

		if ( state )
		{
			const auto resolution = overrideResolution ? overrideResolution : RenderTarget::ShadowMap::Abstract::getBaseResolution() * 4UL;

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
	DirectionalLight::isShadowEnabled () const noexcept
	{
		return m_shadowMap != nullptr;
	}

	std::shared_ptr< RenderTarget::ShadowMap::Abstract >
	DirectionalLight::shadowMap () const noexcept
	{
		return std::static_pointer_cast< RenderTarget::ShadowMap::Abstract >(m_shadowMap);
	}

	const char *
	DirectionalLight::getComponentType () const noexcept
	{
		return "DirectionalLight";
	}

	std::ostream &
	operator<< (std::ostream & out, const DirectionalLight & obj)
	{
		const auto worldCoordinates = obj.getWorldCoordinates();

		return out << "Directional light data ;\n"
			"Direction (World Space) : " << worldCoordinates.forwardVector().inversed() << "\n"
			"Color : " << obj.diffuseColor() << "\n"
			"Intensity : " << obj.intensity() << "\n"
			"Activity : " << ( obj.isEnabled() ? "true" : "false" ) << "\n"
			"Shadow caster : " << ( obj.isShadowEnabled() ? "true" : "false" ) << '\n';
	}

	std::string
	to_string (const DirectionalLight & obj) noexcept
	{
		return (std::stringstream{} << obj).str();
	}
}
