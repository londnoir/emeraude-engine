/*
 * Emeraude/Scenes/ParticlesEmitter.hpp
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

/* C/C++ standard libraries */
#include <string>
#include <sstream>
#include <iostream>
#include <memory>
#include <vector>
#include <set>

/* Local inclusions for inheritances. */
#include "AbstractComponent.hpp"

/* Local inclusions for usages. */
#include "Graphics/RenderableInstance/Multiple.hpp"
#include "Time/TimedEvent.hpp"
#include "Particle.hpp"

namespace Emeraude::Scenes
{
	/**
	 * @brief A class that build a particles generator with mesh or sprite instance.
	 * @extends Emeraude::Scenes::AbstractComponent The base class for each entity component.
	 */
	class ParticlesEmitter final : public AbstractComponent
	{
		public:

			/** @brief Animatable Interface key */
			static constexpr auto EmittingState = 0;
			static constexpr auto MaxParticlesGeneratePerUpdate = 1;
			static constexpr auto ParticlesLimit = 2;
			static constexpr auto MinimumParticlesLife = 3;
			static constexpr auto MaximumParticlesLife = 4;
			static constexpr auto MinimumParticlesSize = 5;
			static constexpr auto MaximumParticlesSize = 6;
			static constexpr auto ParticlesSizeUpdateFactor = 7;
			static constexpr auto Spreading = 8;
			static constexpr auto ChaosMagnitude = 9;

			/** @brief Class identifier. */
			static constexpr auto ClassId{"ParticlesEmitter"};

			/**
			 * @brief Construct a ParticlesEmitter resource.
			 * @param name The resource name.
			 * @param parentEntity A reference to the parent entity.
			 * @param renderable The rendered object by this particles emitter.
			 * @param instanceCount A fixed instance count.
			 */
			ParticlesEmitter (const std::string & name, const AbstractEntity & parentEntity, const std::shared_ptr< Graphics::Renderable::Interface > & renderable, size_t instanceCount) noexcept;

			/** @copydoc Emeraude::Scenes::AbstractComponent::getComponentType() */
			[[nodiscard]]
			const char * getComponentType () const noexcept override;

			/**
			 * @brief Returns the coordinates of the emitter space to locate particle in the world space.
			 * @return const Coordinates< float > &
			 */
			const Libraries::Math::Coordinates< float > & emitterSpace () const noexcept;

			/**
			 * @brief Returns the particle limit.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t particleLimit () const noexcept;

			/**
			 * @brief Sets the number of particle generated per engine update cycle.
			 * @param rate The rate of generation.
			 */
			void setParticlesRateGeneration (float rate) noexcept;

			/**
			 * @brief Returns the particle rate generation.
			 * @return float
			 */
			[[nodiscard]]
			float particleRateGeneration () const noexcept;

			/**
			 * @brief Sets the initial particle lifetime in engine cycles.
			 * @param lifetime The initial lifetime of a new particle.
			 */
			void setParticleLifetime (size_t lifetime) noexcept;

			/**
			 * @brief Sets the initial particle randomized lifetime in engine cycles.
			 * @param minimumLifetime The initial minimum lifetime of a new particle.
			 * @param maximumLifetime The initial maximum lifetime of a new particle.
			 */
			void setParticleLifetime (size_t minimumLifetime, size_t maximumLifetime) noexcept;

			/**
			 * @brief Returns the initial particle minimum lifetime in engine cycles.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t minimumParticleLifetime () const noexcept;

			/**
			 * @brief Returns the initial particle maximum lifetime in engine cycles.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t maximumParticleLifetime () const noexcept;

			/**
			 * @brief Sets the initial particle size.
			 * @param size The initial size of a new particle.
			 */
			void setParticleSize (float size) noexcept;

			/**
			 * @brief Sets the initial particle randomized lifetime in engine cycles.
			 * @param minimumSize The initial minimum size of a new particle.
			 * @param maximumSize The initial maximum size of a new particle.
			 */
			void setParticleSize (float minimumSize, float maximumSize) noexcept;

			/**
			 * @brief Returns the initial particle minimum size.
			 * @return float
			 */
			[[nodiscard]]
			float minimumParticlesSize () const noexcept;

			/**
			 * @brief Returns the initial particle maximum size.
			 * @return float
			 */
			[[nodiscard]]
			float maximumParticlesSize () const noexcept;

			/**
			 * @brief Sets a particle size update factor.
			 * @param factor A positive or negative value to vary the size.
			 */
			void setParticleSizeUpdateFactor (float factor) noexcept;

			/**
			 * @brief Returns the particle size update factor.
			 * @return float
			 */
			[[nodiscard]]
			float particleSizeUpdateFactor () const noexcept;

			/**
			 * @brief Sets a spreading radius for particle generation.
			 * @param radius The size of the radius.
			 */
			void setSpreadingRadius (float radius) noexcept;

			/**
			 * @brief Returns the spreading radius of the particle generation.
			 * @return float
			 */
			[[nodiscard]]
			float spreadingRadius () const noexcept;

			/**
			 * @brief Sets a chaos parameter.
			 * @param magnitude The chaos magnitude.
			 */
			void setChaos (float magnitude) noexcept;

			/**
			 * @brief Returns the chaos magnitude.
			 * @return float
			 */
			[[nodiscard]]
			float chaos () const noexcept;

			/**
			 * @brief Starts the particle emission.
			 * @param forMilliseconds A timeout to stop the emission automatically.
			 */
			void start (size_t forMilliseconds = 0UL) noexcept;

			/** @brief Stops the particle emission. */
			void stop () noexcept;

			/**
			 * @brief Returns the state of particle emission.
			 * @return bool
			 */
			[[nodiscard]]
			bool isEmitting () const noexcept;

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const ParticlesEmitter & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend std::string to_string (const ParticlesEmitter & obj) noexcept;

		private:

			/* Flag names. */
			static constexpr auto IsEmitting = 0UL;
			static constexpr auto GravityEnabled = 1UL;

			/** @copydoc Emeraude::Scenes::AbstractComponent::move() */
			void move () noexcept override;

			/** @copydoc Emeraude::Scenes::AbstractComponent::processLogics() */
			void processLogics (const Scene & scene, size_t cycle) noexcept override;

			/** @copydoc Emeraude::Animations::AnimatableInterface::playAnimation() */
			bool playAnimation (Animations::id_t id, const Libraries::Variant & value) noexcept override;

			bool setGeometry (const std::shared_ptr< Graphics::Geometry::Interface > & geometry) noexcept;

			bool setMaterial (const std::shared_ptr< Graphics::Material::Interface > & material) noexcept;

			[[nodiscard]]
			inline
			size_t
			getParticleLifetime () const noexcept
			{
				if ( m_minimumParticleLifetime >= m_maximumParticleLifetime )
					return m_minimumParticleLifetime;

				return Libraries::Utility::random(m_minimumParticleLifetime, m_maximumParticleLifetime);
			}

			[[nodiscard]]
			inline
			float
			getParticleSize () const noexcept
			{
				if ( m_minimumParticleSize >= m_maximumParticleSize )
					return m_minimumParticleSize;

				return Libraries::Utility::random(m_minimumParticleSize, m_maximumParticleSize);
			}

			std::shared_ptr< Graphics::RenderableInstance::Multiple > m_renderableInstance;
			Physics::PhysicalObjectProperties m_properties{};
			Libraries::Math::Coordinates< float > m_emitterSpace{};
			std::vector< Particle > m_particles{};
			std::unique_ptr< Libraries::Time::TimedEvent > m_timedEvent{};
			size_t m_particleLimit;
			float m_particleRateGeneration = 1.0F;
			size_t m_minimumParticleLifetime = 1;
			size_t m_maximumParticleLifetime = 1;
			float m_minimumParticleSize = 1.0F;
			float m_maximumParticleSize = 1.0F;
			float m_particleSizeUpdateFactor = 0.0F;
			float m_spreadingRadius = 1.0F;
			float m_chaosMagnitude = 0.0F;
			std::array< bool, 8 > m_flags{
				false/*IsEmitting*/,
				true/*GravityEnabled*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
