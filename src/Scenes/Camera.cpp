/*
 * Emeraude/Scenes/Camera.cpp
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

#include "Camera.hpp"

/* C/C++ standard libraries. */
#include <cmath>

/* Local inclusions. */
#include "Tracer.hpp"
#include "Graphics/RenderTarget/View/Texture2D.hpp"
#include "Scene.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Animations;
	using namespace Saphir;
	using namespace Graphics;

	Camera::Camera (const std::string & name, const AbstractEntity & parentEntity, bool perspective) noexcept
		: AbstractComponent(name, parentEntity), MasterControl::AbstractVirtualVideoDevice(name, MasterControl::ConnexionType::Output)
	{
		m_flags[PerspectiveProjection] = perspective;

		if ( perspective )
			m_distance = RenderTarget::View::Texture2D::getMaxViewableDistance();
	}

	const char *
	Camera::getComponentType () const noexcept
	{
		return "Camera";
	}

	MasterControl::VideoType
	Camera::videoType () const noexcept
	{
		return MasterControl::VideoType::Camera;
	}

	bool
	Camera::isPerspectiveProjection () const noexcept
	{
		return m_flags[PerspectiveProjection];
	}

	bool
	Camera::isOrthographicProjection () const noexcept
	{
		return !m_flags[PerspectiveProjection];
	}

	void
	Camera::setPerspectiveProjection (float fov, float maxViewableDistance) noexcept
	{
		m_flags[PerspectiveProjection] = true;
		m_fov = std::abs(fov);
		m_distance = maxViewableDistance != 0.0F ? std::abs(maxViewableDistance) : RenderTarget::View::Texture2D::getMaxViewableDistance();

		this->updateProperties(true, m_distance, m_fov);
	}

	void
	Camera::setOrthographicProjection (float size) noexcept
	{
		m_flags[PerspectiveProjection] = false;
		m_distance = std::abs(size);

		this->updateProperties(false, m_distance, 0.0F);
	}

	float
	Camera::fieldOfView () const noexcept
	{
		return m_fov;
	}

	void
	Camera::setFieldOfView (float degrees) noexcept
	{
		m_fov = std::min(std::abs(degrees), 360.0F);

		if ( m_flags[PerspectiveProjection] )
			this->updateProperties(true, m_distance, m_fov);
	}

	float
	Camera::distance () const noexcept
	{
		return m_distance;
	}

	void
	Camera::setDistance (float distance) noexcept
	{
		m_distance = std::abs(distance);

		if ( m_flags[PerspectiveProjection] )
			this->updateProperties(true, m_distance, m_fov);
		else
			this->updateProperties(false, m_distance, 0.0F);
	}

	const FramebufferEffectsList &
	Camera::lenseEffects () const noexcept
	{
		return m_lenseEffects;
	}

	bool
	Camera::isLensEffectPresent (const std::shared_ptr< FramebufferEffectInterface > & effect) const noexcept
	{
		return m_lenseEffects.find(effect) != m_lenseEffects.cend();
	}

	void
	Camera::addLensEffect (const std::shared_ptr< FramebufferEffectInterface > & effect) noexcept
	{
		/* We don't want to notify an effect twice. */
		if ( this->isLensEffectPresent(effect) )
			return;

		m_lenseEffects.emplace(effect);

		this->notify(LensEffectsChanged);
	}

	void
	Camera::removeLensEffect (const std::shared_ptr< FramebufferEffectInterface > & effect) noexcept
	{
		auto it = m_lenseEffects.find(effect);

		if ( it == m_lenseEffects.end() )
			return;

		m_lenseEffects.erase(it);

		this->notify(LensEffectsChanged);
	}

	void
	Camera::clearLensEffects () noexcept
	{
		if ( m_lenseEffects.size() == 0 )
			return;

		m_lenseEffects.clear();

		this->notify(LensEffectsChanged);
	}

	void
	Camera::move () noexcept
	{
		this->updateDeviceFromCoordinates(this->getWorldCoordinates(), this->getWorldVelocity());
	}

	void
	Camera::processLogics (const Scene &, size_t) noexcept
	{
		this->updateDeviceFromCoordinates(this->getWorldCoordinates(), this->getWorldVelocity());
	}

	void
	Camera::updateDeviceFromCoordinates (const Coordinates< float > & worldCoordinates, const Vector< 3, float > & worldVelocity) noexcept
	{
		if ( !this->hasOutputConnected() )
			return;

		for ( const auto & output : this->outputs() )
			output->updateDeviceFromCoordinates(worldCoordinates, worldVelocity);
	}

	void
	Camera::updateProperties (bool isPerspectiveProjection, float distance, float fovOrNear) noexcept
	{
		if ( !this->hasOutputConnected() )
			return;

		for ( const auto & output : this->outputs() )
		{
			auto videoDevice = std::dynamic_pointer_cast< AbstractVirtualVideoDevice >(output);

			videoDevice->updateProperties(isPerspectiveProjection, distance, fovOrNear);
		}
	}

	void
	Camera::onTargetConnected (AbstractVirtualVideoDevice * targetDevice) noexcept
	{
		/* Initialize the target device with coordinates and camera properties. */
		targetDevice->updateDeviceFromCoordinates(this->getWorldCoordinates(), this->getWorldVelocity());

		if ( m_flags[PerspectiveProjection] )
			this->updateProperties(true, m_distance, m_fov);
		else
			this->updateProperties(false, m_distance, 0.0F);
	}

	bool
	Camera::playAnimation (Animations::id_t, const Variant &) noexcept
	{
		return false;
	}

	std::ostream &
	operator<< (std::ostream & out, const Camera & obj)
	{
		const auto coordinates = obj.getWorldCoordinates();
		const auto velocity = obj.getWorldVelocity();

		return out <<
			"Video Listener information" "\n"
			"Position: " << coordinates.position() << "\n"
			"Forward: " << coordinates.forwardVector() << "\n"
			"Upward: " << coordinates.upwardVector() << "\n"
			"Velocity: " << velocity << "\n"
			"Field of view: " << obj.m_fov << "\n"
			"Size of view: " << obj.m_distance << "\n";
	}

	std::string
	to_string (const Camera & obj) noexcept
	{
		return (std::stringstream{} << obj).str();
	}
}
