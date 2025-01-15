/*
 * src/Scenes/Component/Camera.cpp
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

#include "Camera.hpp"

/* STL inclusions. */
#include <algorithm>
#include <cmath>
#include <memory>
#include <ostream>
#include <string>

/* Local inclusions. */
#include "Scenes/AbstractEntity.hpp"
#include "Abstract.hpp"
#include "Animations/Types.hpp"
#include "Graphics/RenderTarget/View/Texture2D.hpp"
#include "MasterControl/AbstractVirtualVideoDevice.hpp"
#include "MasterControl/Types.hpp"
#include "Libraries/Math/Base.hpp"
#include "Libraries/Math/CartesianFrame.hpp"
#include "Libraries/Math/Cuboid.hpp"
#include "Libraries/Math/Sphere.hpp"
#include "Libraries/Math/Vector.hpp"
#include "Saphir/FramebufferEffectInterface.hpp"
#include "Libraries/Variant.hpp"

namespace Emeraude::Scenes::Component
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Animations;
	using namespace Saphir;
	using namespace Graphics;

	Camera::Camera (const std::string & name, const AbstractEntity & parentEntity, bool perspective) noexcept
		: Abstract(name, parentEntity), AbstractVirtualVideoDevice(name, MasterControl::ConnexionType::Output)
	{
		this->setFlag(PerspectiveProjection, perspective);
	}

	const char *
	Camera::getComponentType () const noexcept
	{
		return ClassId;
	}

	const Cuboid< float > &
	Camera::boundingBox () const noexcept
	{
		return NullBoundingBox;
	}

	const Sphere< float > &
	Camera::boundingSphere () const noexcept
	{
		return NullBoundingSphere;
	}

	MasterControl::VideoType
	Camera::videoType () const noexcept
	{
		return MasterControl::VideoType::Camera;
	}

	bool
	Camera::isPerspectiveProjection () const noexcept
	{
		return this->isFlagEnabled(PerspectiveProjection);
	}

	bool
	Camera::isOrthographicProjection () const noexcept
	{
		return !this->isFlagEnabled(PerspectiveProjection);
	}

	void
	Camera::setPerspectiveProjection (float fov, float maxViewableDistance) noexcept
	{
		this->enableFlag(PerspectiveProjection);

		m_fov = std::abs(fov);

	    if ( maxViewableDistance > 0.0F )
	    {
	        m_distance = maxViewableDistance;
	    }

		this->updateProperties(true, m_distance, m_fov);
	}

	void
	Camera::setOrthographicProjection (float size) noexcept
	{
		this->disableFlag(PerspectiveProjection);

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
		m_fov = std::min(std::abs(degrees), FullRevolution< float >);

		if ( this->isPerspectiveProjection() )
		{
			this->updateProperties(true, m_distance, m_fov);
		}
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

		if ( this->isPerspectiveProjection() )
		{
			this->updateProperties(true, m_distance, m_fov);
		}
		else
		{
			this->updateProperties(false, m_distance, 0.0F);
		}
	}

	const FramebufferEffectsList &
	Camera::lensEffects () const noexcept
	{
		return m_lensEffects;
	}

	bool
	Camera::isLensEffectPresent (const std::shared_ptr< FramebufferEffectInterface > & effect) const noexcept
	{
		return m_lensEffects.contains(effect);
	}

	void
	Camera::addLensEffect (const std::shared_ptr< FramebufferEffectInterface > & effect) noexcept
	{
		/* We don't want to notify an effect twice. */
		if ( this->isLensEffectPresent(effect) )
		{
			return;
		}

		m_lensEffects.emplace(effect);

		this->notify(LensEffectsChanged);
	}

	void
	Camera::removeLensEffect (const std::shared_ptr< FramebufferEffectInterface > & effect) noexcept
	{
		const auto lensIt = m_lensEffects.find(effect);

		if (lensIt == m_lensEffects.cend() )
		{
			return;
		}

		m_lensEffects.erase(lensIt);

		this->notify(LensEffectsChanged);
	}

	void
	Camera::clearLensEffects () noexcept
	{
		if ( m_lensEffects.empty() )
		{
			return;
		}

		m_lensEffects.clear();

		this->notify(LensEffectsChanged);
	}

	void
	Camera::move (const CartesianFrame< float > & worldCoordinates) noexcept
	{
		this->updateDeviceFromCoordinates(worldCoordinates, this->getWorldVelocity());
	}

	void
	Camera::processLogics (const Scene & /*scene*/) noexcept
	{
		this->updateDeviceFromCoordinates(this->getWorldCoordinates(), this->getWorldVelocity());
	}

	bool
	Camera::shouldRemove () const noexcept
	{
		return false;
	}

	void
	Camera::updateDeviceFromCoordinates (const CartesianFrame< float > & worldCoordinates, const Vector< 3, float > & worldVelocity) noexcept
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
	Camera::updateProperties (bool isPerspectiveProjection, float distance, float fovOrNear) noexcept
	{
		if ( !this->hasOutputConnected() )
		{
			return;
		}

		for ( const auto & output : this->outputs() )
		{
			const auto videoDevice = std::dynamic_pointer_cast< AbstractVirtualVideoDevice >(output);

			videoDevice->updateProperties(isPerspectiveProjection, distance, fovOrNear);
		}
	}

	void
	Camera::onTargetConnected (AbstractVirtualVideoDevice * targetDevice) noexcept
	{
		/* Initialize the target device with coordinates and camera properties. */
		targetDevice->updateDeviceFromCoordinates(this->getWorldCoordinates(), this->getWorldVelocity());

		if ( this->isPerspectiveProjection() )
		{
			this->updateProperties(true, m_distance, m_fov);
		}
		else
		{
			this->updateProperties(false, m_distance, 0.0F);
		}
	}

	bool
	Camera::playAnimation (id_t /*identifier*/, const Variant & /*value*/) noexcept
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
			"Velocity: " << velocity << "\n"
			"Field of view: " << obj.fieldOfView() << "\n"
			"Size of view: " << obj.distance() << "\n";
	}

	std::string
	to_string (const Camera & obj) noexcept
	{
		std::stringstream output;

		output << obj;

		return output.str();
	}
}
