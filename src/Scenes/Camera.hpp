/*
 * Emeraude/Scenes/Camera.hpp
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

#pragma once

/* C/C++ standard libraries. */
#include <string>
#include <array>
#include <memory>

/* Local inclusions for inheritances. */
#include "AbstractComponent.hpp"
#include "MasterControl/AbstractVirtualVideoDevice.hpp"

/* Local inclusions for usages. */
#include "Saphir/FramebufferEffectInterface.hpp"

namespace Emeraude::Scenes
{
	/**
	 * @brief This class defines a physical point of view to capture image in the world.
	 * @note PointOfView and Camera are not merged together, because the world can only one
	 * point of view but multiple cameras.
	 * @extends Emeraude::Scenes::AbstractComponent The base class for each entity component.
	 * @extends Emeraude::MasterControl::AbstractVirtualVideoDevice This is a virtual video device.
	 */
	class Camera final : public AbstractComponent, public MasterControl::AbstractVirtualVideoDevice
	{
		public:

			/** @brief Observable notification codes. */
			enum NotificationCode
			{
				LensEffectsChanged,
				/* Enumeration boundary. */
				MaxEnum
			};

			/**
			 * @brief Constructs a camera.
			 * @param name The name of the component.
			 * @param parentEntity A reference to the parent entity.
			 * @param perspective Use a perspective projection.
			 */
			Camera (const std::string & name, const AbstractEntity & parentEntity, bool perspective = true) noexcept;

			/** @copydoc Emeraude::Scenes::AbstractComponent::getComponentType() */
			[[nodiscard]]
			const char * getComponentType () const noexcept override;

			/** @copydoc Emeraude::MasterControl::AbstractVirtualVideoDevice::videoType() */
			[[nodiscard]]
			MasterControl::VideoType videoType () const noexcept override;

			/**
			 * @brief Sets the field of view in degrees.
			 * @param degrees A value between 0.0 and 360.0.
			 */
			void setFieldOfView (float degrees) noexcept;

			/**
			 * @brief Returns the field of view in degrees.
			 * @return float
			 */
			[[nodiscard]]
			float fieldOfView () const noexcept;

			/**
			 * @brief Returns whether the camera is using a perspective projection.
			 * @return bool
			 */
			[[nodiscard]]
			bool isPerspectiveProjection () const noexcept;

			/**
			 * @brief Returns whether the camera is using an orthographic projection.
			 * @return bool
			 */
			[[nodiscard]]
			bool isOrthographicProjection () const noexcept;

			/**
			 * @brief Sets a perspective projection.
			 * @param fov The field of view in degress.
			 * @param maxViewableDistance The distance of view. If not given, settings will be used.
			 */
			void setPerspectiveProjection (float fov, float maxViewableDistance = 0.0F) noexcept;

			/**
			 * @brief Sets an orthographic projection.
			 * @param size The size of the render.
			 */
			void setOrthographicProjection (float size) noexcept;

			/**
			 * @brief Updates the field of view with degrees.
			 * @return float
			 */
			inline
			void
			changeFieldOfView (float value) noexcept
			{
				this->setFieldOfView(m_distance + value);
			}

			/**
			 * @brief Returns the maximal distance of the view.
			 * @return float
			 */
			[[nodiscard]]
			float distance () const noexcept;

			/**
			 * @brief Sets the the maximal distance of the view.
			 * @param distance The maximal distance of the view.
			 */
			void setDistance (float distance) noexcept;

			/**
			 * @brief Returns the lense effect list.
			 * @return const Saphir::FramebufferEffectsList &
			 */
			[[nodiscard]]
			const Saphir::FramebufferEffectsList & lenseEffects () const noexcept;

			/**
			 * @brief Checks if a shader lense effect is present.
			 * @param effect The effect to test.
			 * @return bool
			 */
			[[nodiscard]]
			bool isLensEffectPresent (const std::shared_ptr< Saphir::FramebufferEffectInterface > & effect) const noexcept;

			/**
			 * @brief Adds a shader lense effect to the camera.
			 * @note This won't add the same effect twice.
			 * @param effect The effect to add.
			 */
			void addLensEffect (const std::shared_ptr< Saphir::FramebufferEffectInterface > & effect) noexcept;

			/**
			 * @brief Removes a shader lense effect from the camera.
			 * @param effect The effect to remove.
			 */
			void removeLensEffect (const std::shared_ptr< Saphir::FramebufferEffectInterface > & effect) noexcept;

			/** @brief Clears all shader lense effect of the camera. */
			void clearLensEffects () noexcept;

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const Camera & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend std::string to_string (const Camera & obj) noexcept;

		private:

			/* Flag names */
			static constexpr auto PerspectiveProjection = 0UL;

			/** @copydoc Emeraude::Scenes::AbstractComponent::move() */
			void move () noexcept override;

			/** @copydoc Emeraude::Scenes::AbstractComponent::processLogics() */
			void processLogics (const Scene & scene, size_t cycle) noexcept override;

			/** @copydoc Emeraude::MasterControl::AbstractVirtualDevice::updateDeviceFromCoordinates() */
			void updateDeviceFromCoordinates (const Libraries::Math::Coordinates< float > & worldCoordinates, const Libraries::Math::Vector< 3, float > & worldVelocity) noexcept override;

			/** @copydoc Emeraude::MasterControl::AbstractVirtualVideoDevice::updateProperties() */
			void updateProperties (bool isPerspectiveProjection, float distance, float fovOrNear) noexcept override;

			/** @copydoc Emeraude::MasterControl::AbstractVirtualVideoDevice::onTargetConnected() */
			void onTargetConnected (AbstractVirtualVideoDevice * targetDevice) noexcept override;

			/** @copydoc Emeraude::Animations::Interface::playAnimation() */
			bool playAnimation (Animations::id_t id, const Libraries::Variant & value) noexcept override;

			Saphir::FramebufferEffectsList m_lenseEffects{};
			float m_fov = 80.0F;
			float m_distance = 1024.0F;
			float m_controllerRSpeed = 1.0F;
			float m_controllerZoomSpeed = 0.4F;
			std::array< bool, 8 > m_flags{
				true/*PerspectiveProjection*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
