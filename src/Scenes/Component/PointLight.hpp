/*
 * src/Scenes/Component/PointLight.hpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2025 - Sébastien Léon Claude Christian Bémelmans "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Emeraude-Engine; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Complete project and additional information can be found at :
 * https://github.com/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#pragma once

/* STL inclusions. */
#include <array>

/* Local inclusions for inheritances. */
#include "AbstractLightEmitter.hpp"

namespace EmEn::Scenes::Component
{
	/**
	 * @brief Defines a scene point light like a lamp bulb.
	 * @extends EmEn::Scenes::Component::AbstractLightEmitter The base class for each light type.
	 */
	class PointLight final : public AbstractLightEmitter
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"PointLight"};

			/**
			 * @brief Constructs a point light.
			 * @param name The name of the component.
			 * @param parentEntity A reference to the parent entity.
			 * @param shadowMapResolution Enable the shadow map by specifying the resolution. Default, no shadow map.
			 */
			PointLight (const std::string & name, const AbstractEntity & parentEntity, uint32_t shadowMapResolution = 0) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			PointLight (const PointLight & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			PointLight (PointLight && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return PointLight &
			 */
			PointLight & operator= (const PointLight & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return PointLight &
			 */
			PointLight & operator= (PointLight && copy) noexcept = delete;

			/**
			 * @brief Destructs a point light.
			 */
			~PointLight () override;

			/** @copydoc EmEn::Scenes::Component::Abstract::getComponentType() */
			[[nodiscard]]
			const char * getComponentType () const noexcept override;

			/** @copydoc EmEn::Scenes::Component::Abstract::boundingBox() const */
			[[nodiscard]]
			const Libs::Math::Cuboid< float > & boundingBox () const noexcept override;

			/** @copydoc EmEn::Scenes::Component::Abstract::boundingSphere() const */
			[[nodiscard]]
			const Libs::Math::Sphere< float > & boundingSphere () const noexcept override;

			/** @copydoc EmEn::Scenes::Component::Abstract::processLogics() */
			void processLogics (const Scene & scene) noexcept override;

			/** @copydoc EmEn::Scenes::Component::Abstract::move() */
			void move (const Libs::Math::CartesianFrame< float > & worldCoordinates) noexcept override;

			/** @copydoc EmEn::Scenes::Component::Abstract::shouldRemove() */
			bool shouldRemove () const noexcept override;

			/** @copydoc EmEn::Scenes::Component::AbstractLightEmitter::touch() */
			[[nodiscard]]
			bool touch (const Libs::Math::Vector< 3, float > & position) const noexcept override;

			/** @copydoc EmEn::Scenes::Component::AbstractLightEmitter::createOnHardware() */
			[[nodiscard]]
			bool createOnHardware (LightSet & lightSet, Graphics::Renderer & renderer, AVConsole::Manager & AVConsoleManager) noexcept override;

			/** @copydoc EmEn::Scenes::Component::AbstractLightEmitter::destroyFromHardware() */
			void destroyFromHardware () noexcept override;

			/** @copydoc EmEn::Scenes::Component::AbstractLightEmitter::shadowMap() */
			[[nodiscard]]
			std::shared_ptr< Graphics::RenderTarget::ShadowMap::Abstract > shadowMap () const noexcept override;

			/** @copydoc EmEn::Scenes::Component::AbstractLightEmitter::getUniformBlock() */
			[[nodiscard]]
			Saphir::Declaration::UniformBlock getUniformBlock (uint32_t set, uint32_t binding, bool useShadow) const noexcept override;

			/**
			 * @brief Set the radius of light area.
			 * @param radius
			 */
			void setRadius (float radius) noexcept;

			/**
			 * @brief Returns the radius of light area.
			 * @return float
			 */
			[[nodiscard]]
			float radius () const noexcept;

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const PointLight & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend std::string to_string (const PointLight & obj) noexcept;

		private:

			/** @copydoc EmEn::AVConsole::AbstractVirtualDevice::onTargetConnected() */
			void onTargetConnected (AbstractVirtualDevice * targetDevice) noexcept override;

			/** @copydoc EmEn::Animations::AnimatableInterface::playAnimation() */
			bool playAnimation (uint8_t animationID, const Libs::Variant & value, size_t cycle) noexcept override;

			/** @copydoc EmEn::Scenes::Component::AbstractLightEmitter::onVideoMemoryUpdate() */
			[[nodiscard]]
			bool
			onVideoMemoryUpdate (Vulkan::SharedUniformBuffer & UBO, uint32_t index) noexcept override
			{
				return UBO.writeElementData(index, m_buffer.data());
			}

			/** @copydoc EmEn::Scenes::Component::AbstractLightEmitter::onColorChange() */
			void onColorChange (const Libs::PixelFactory::Color< float > & color) noexcept override;

			/** @copydoc EmEn::Scenes::Component::AbstractLightEmitter::onIntensityChange() */
			void onIntensityChange (float intensity) noexcept override;

			/* Uniform buffer object offset to write data. */
			static constexpr auto ColorOffset{0UL};
			static constexpr auto PositionOffset{4UL};
			static constexpr auto IntensityOffset{8UL};
			static constexpr auto RadiusOffset{9UL};
			static constexpr auto LightMatrixOffset{16UL};

			std::shared_ptr< Graphics::RenderTarget::ShadowMap::Cubemap > m_shadowMap{};
			float m_radius{DefaultRadius};
			std::array< float, 4 + 4 + 4 + 16 > m_buffer{
				/* Light color. */
				this->color().red(), this->color().green(), this->color().blue(), 1.0F,
				/* Light position (Point) */
				0.0F, 0.0F, 0.0F, 1.0F, // NOTE: Put W to zero and the light will follows the camera.
				/* Light properties. */
				this->intensity(), m_radius, 0.0F, 0.0F,
				/* Light matrix. */
				1.0F, 0.0F, 0.0F, 0.0F,
				0.0F, 1.0F, 0.0F, 0.0F,
				0.0F, 0.0F, 1.0F, 0.0F,
				0.0F, 0.0F, 0.0F, 1.0F
			};
	};
}
