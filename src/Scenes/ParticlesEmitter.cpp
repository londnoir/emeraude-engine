/*
 * Emeraude/Scenes/ParticlesEmitter.cpp
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

#include "ParticlesEmitter.hpp"

/* Local inclusions */
#include "Scene.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Animations;
	using namespace Physics;
	using namespace Graphics;

	ParticlesEmitter::ParticlesEmitter (const std::string & name, const AbstractEntity & parentEntity, const std::shared_ptr< Renderable::Interface > & renderable, size_t instanceCount) noexcept
		: AbstractComponent(name, parentEntity), m_particleLimit(instanceCount)
	{

	}

	const char *
	ParticlesEmitter::getComponentType () const noexcept
	{
		return "ParticlesEmitter";
	}

	const Coordinates< float > &
	ParticlesEmitter::emitterSpace () const noexcept
	{
		return m_emitterSpace;
	}

	void
	ParticlesEmitter::move () noexcept
	{
		m_emitterSpace = this->getWorldCoordinates();
	}

	void
	ParticlesEmitter::processLogics (const Scene & scene, size_t cycle) noexcept
	{
		this->updateAnimations(cycle);

		/* [ERASE IN LOOP] */
		auto particleIt = m_particles.begin();

		while ( particleIt != m_particles.end() )
		{
			/* if he's dead we remove it, and we go to the next. */
			if ( particleIt->isDead() )
			{
				particleIt = m_particles.erase(particleIt);
			}
			else
			{
				/* Applies scene modifiers. */
				for ( const auto & modifier : scene.modifiers() )
					modifier->apply(*particleIt);

				particleIt->update(
					particleIt->updateVelocity(scene.physicalEnvironmentProperties()),
					m_particleSizeUpdateFactor,
					m_chaosMagnitude
				);

				++particleIt;
			}
		}

		/* Regeneration of particles. */
		if ( m_flags[IsEmitting] )
		{
			if ( m_particles.size() >= m_particleLimit )
				return;

			auto generateCount = static_cast< size_t >(m_particleRateGeneration);
			const auto remain = m_particleRateGeneration - generateCount;

			if ( remain > 0.0F )
			{
				const auto mod = static_cast< size_t >(std::round(1.0F / remain));

				if ( cycle % mod == 0 )
					generateCount++;
			}

			/* NOTE: No space to add new particle for now. */
			if ( generateCount == 0 )
				return;

			for ( size_t i = 0; i < generateCount; i++ )
				m_particles.emplace_back(*this, this->getParticleLifetime(), this->getParticleSize(), m_spreadingRadius);
		}
	}

	bool
	ParticlesEmitter::playAnimation (Animations::id_t id, const Variant & value) noexcept
	{
		switch ( id )
		{
			case EmittingState :
				m_flags[IsEmitting] = value.asBool();
				break;

			case MaxParticlesGeneratePerUpdate :
				m_particleRateGeneration = value.asFloat();
				break;

			case ParticlesLimit :
				m_particleRateGeneration = value.asFloat();
				break;

			case MinimumParticlesLife :
				m_minimumParticleLifetime = value.asUnsignedInteger32();
				break;

			case MaximumParticlesLife :
				m_maximumParticleLifetime = value.asUnsignedInteger32();
				break;

			case MinimumParticlesSize :
				m_minimumParticleSize = value.asFloat();
				break;

			case MaximumParticlesSize :
				m_maximumParticleSize = value.asFloat();
				break;

			case ParticlesSizeUpdateFactor :
				this->setParticleSizeUpdateFactor(value.asFloat());
				break;

			case Spreading :
				this->setSpreadingRadius(value.asFloat());
				break;

			case ChaosMagnitude :
				this->setChaos(value.asFloat());
				break;
		}

		return false;
	}

	size_t
	ParticlesEmitter::particleLimit () const noexcept
	{
		return m_particleLimit;
	}

	void
	ParticlesEmitter::setParticlesRateGeneration (float rate) noexcept
	{
		m_particleRateGeneration = rate;
	}

	float
	ParticlesEmitter::particleRateGeneration () const noexcept
	{
		return m_particleRateGeneration;
	}

	void
	ParticlesEmitter::setParticleLifetime (size_t lifetime) noexcept
	{
		if ( lifetime < 1 )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", the life parameter must at least be 1 !" << std::endl;

			return;
		}

		m_minimumParticleLifetime = lifetime;
		m_maximumParticleLifetime = lifetime;
	}
	void
	ParticlesEmitter::setParticleLifetime (size_t minimumLifetime, size_t maximumLifetime) noexcept
	{
		if ( minimumLifetime < 1 )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", the minLife parameter must at least be 1 !" << std::endl;

			return;
		}

		if ( maximumLifetime < 1 )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", the maxLife parameter must at least be 1 !" << std::endl;

			return;
		}

		if ( minimumLifetime < maximumLifetime )
		{
			m_minimumParticleLifetime = minimumLifetime;
			m_maximumParticleLifetime = maximumLifetime;
		}
		else
		{
			m_minimumParticleLifetime = minimumLifetime;
			m_maximumParticleLifetime = maximumLifetime;
		}
	}

	size_t
	ParticlesEmitter::minimumParticleLifetime () const noexcept
	{
		return m_minimumParticleLifetime;
	}

	size_t
	ParticlesEmitter::maximumParticleLifetime () const noexcept
	{
		return m_maximumParticleLifetime;
	}

	void
	ParticlesEmitter::setParticleSize (float size) noexcept
	{
		m_minimumParticleSize = size;
		m_maximumParticleSize = size;
	}

	void
	ParticlesEmitter::setParticleSize (float minimumSize, float maximumSize) noexcept
	{
		if ( minimumSize < maximumSize )
		{
			m_minimumParticleSize = minimumSize;
			m_maximumParticleSize = maximumSize;
		}
		else
		{
			m_minimumParticleSize = maximumSize;
			m_maximumParticleSize = minimumSize;
		}
	}

	float
	ParticlesEmitter::minimumParticlesSize () const noexcept
	{
		return m_minimumParticleSize;
	}

	float
	ParticlesEmitter::maximumParticlesSize () const noexcept
	{
		return m_maximumParticleSize;
	}

	void
	ParticlesEmitter::setParticleSizeUpdateFactor (float factor) noexcept
	{
		m_particleSizeUpdateFactor = factor;
	}

	float
	ParticlesEmitter::particleSizeUpdateFactor() const noexcept
	{
		return m_particleSizeUpdateFactor;
	}

	void
	ParticlesEmitter::setSpreadingRadius (float radius) noexcept
	{
		if ( radius < 0.0F )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", spreading radius must be greater or equal to zero." << std::endl;

			return;
		}

		m_spreadingRadius = radius;
	}

	float
	ParticlesEmitter::spreadingRadius () const noexcept
	{
		return m_spreadingRadius;
	}

	void
	ParticlesEmitter::setChaos (float magnitude) noexcept
	{
		m_chaosMagnitude = magnitude;
	}

	float
	ParticlesEmitter::chaos () const noexcept
	{
		return m_chaosMagnitude;
	}

	void
	ParticlesEmitter::start (size_t forMilliseconds) noexcept
	{
		m_flags[IsEmitting] = true;

		if ( forMilliseconds > 0 )
		{
			m_timedEvent = std::make_unique< Time::TimedEvent >(std::bind(&ParticlesEmitter::stop, this), forMilliseconds, true, false);
			m_timedEvent->start();
		}
	}

	void
	ParticlesEmitter::stop () noexcept
	{
		m_flags[IsEmitting] = false;
	}

	bool
	ParticlesEmitter::isEmitting () const noexcept
	{
		return m_flags[IsEmitting];
	}

	bool
	ParticlesEmitter::setGeometry (const std::shared_ptr< Geometry::Interface > &) noexcept
	{
		Tracer::debug(ClassId, "This method should not be used from here !");

		return false;
	}

	bool
	ParticlesEmitter::setMaterial (const std::shared_ptr< Material::Interface > &) noexcept
	{
		Tracer::debug(ClassId, "This method should not be used from here !");

		return false;
	}

	std::ostream &
	operator<< (std::ostream & out, const ParticlesEmitter & obj)
	{
		return out <<
			"Particles Generator data :\n"
			"Enabled : " << ( obj.m_flags[ParticlesEmitter::IsEmitting] ? "yes" : "no" ) << "\n"
			"Particles rate generation : " << obj.m_particleRateGeneration << "\n"
			"Particles limit : " << obj.m_particleLimit << "\n"
			"Particles min life : " << obj.m_minimumParticleLifetime << "\n"
			"Particles max life : " << obj.m_maximumParticleLifetime << "\n"
			"Particles min size : " << obj.m_minimumParticleSize << "\n"
			"Particles max size : " << obj.m_maximumParticleSize << "\n"
			"Particles size update factor : " << obj.m_particleSizeUpdateFactor << "\n"
			"Spreading : " << obj.m_spreadingRadius << "\n"
			"Chaos magnitude : " << obj.m_chaosMagnitude << "\n"
			"Living particles : " << obj.m_particles.size() << '\n';
	}

	std::string
	to_string (const ParticlesEmitter & obj) noexcept
	{
		return (std::stringstream{} << obj).str();
	}
}
