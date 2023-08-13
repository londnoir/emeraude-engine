/*
 * Emeraude/Scenes/LightSet.cpp
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

#include "LightSet.hpp"

/* Local inclusions */
#include "Graphics/TextureResource/TextureCubemap.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Libraries::PixelFactory;
	using namespace Graphics;

	const size_t LightSet::ClassUID{Observable::getClassUID()};

	bool
	LightSet::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	void
	LightSet::setGlobalAmbientLight (const Color< float > & color) noexcept
	{
		m_globalAmbientLight = color;
	}

	void
	LightSet::setGlobalAmbientLight (const std::shared_ptr< TextureResource::TextureCubemap > & cubemap, float percent) noexcept
	{
		m_globalAmbientLight = cubemap->averageColor() * clampToUnit(percent);
	}

	void
	LightSet::enableLightColorForAmbientGeneration (bool state, float factor) noexcept
	{
		m_flags[UseLightColorAsAmbient] = state;
		m_lightColorFactorToAmbient = clampToUnit(factor);
	}

	void
	LightSet::enableLightDistanceForAmbientGeneration (bool state) noexcept
	{
		m_flags[UseLightDistance] = state;
	}

	void
	LightSet::add (const std::shared_ptr< DirectionalLight > & light) noexcept
	{
		m_lights.emplace(light);

		this->notify(DirectionalLightAdded, light);
	}

	void
	LightSet::add (const std::shared_ptr< PointLight > & light) noexcept
	{
		m_lights.emplace(light);

		this->notify(PointLightAdded, light);
	}

	void
	LightSet::add (const std::shared_ptr< SpotLight > & light) noexcept
	{
		m_lights.emplace(light);

		this->notify(SpotLightAdded, light);
	}

	void
	LightSet::remove (const std::shared_ptr< DirectionalLight > & light) noexcept
	{
		m_lights.erase(light);

		this->notify(DirectionalLightRemoved, light);
	}

	void
	LightSet::remove (const std::shared_ptr< PointLight > & light) noexcept
	{
		m_lights.erase(light);

		this->notify(PointLightRemoved, light);
	}

	void
	LightSet::remove (const std::shared_ptr< SpotLight > & light) noexcept
	{
		m_lights.erase(light);

		this->notify(SpotLightRemoved, light);
	}

	const Color< float > &
	LightSet::globalAmbientLight () const noexcept
	{
		return m_globalAmbientLight;
	}

	const std::set< std::shared_ptr< AbstractLightEmitter > > &
	LightSet::lights () const noexcept
	{
		return m_lights;
	}

	float
	LightSet::lightColorFactorToAmbient () const noexcept
	{
		return m_lightColorFactorToAmbient;
	}

	bool
	LightSet::useLightColorAsAmbient () const noexcept
	{
		return m_flags[UseLightColorAsAmbient];
	}

	bool
	LightSet::useLightDistance () const noexcept
	{
		return m_flags[UseLightDistance];
	}

	void
	LightSet::clear () noexcept
	{
		m_lights.clear();
		m_globalAmbientLight = Black;
		m_lightColorFactorToAmbient = 0.1F;
	}
}
