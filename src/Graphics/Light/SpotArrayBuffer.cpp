/*
 * Emeraude/Graphics/Light/SpotArrayBuffer.cpp
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

#include "SpotArrayBuffer.hpp"

/* Local inclusions */
#include "Tracer.hpp"
#include "Scenes/AbstractEntity.hpp"
#include "Scenes/LightSet.hpp"
#include "Saphir/Keys.hpp"

namespace Emeraude::Graphics::Light
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Saphir;
	using namespace Saphir::Keys;
	using namespace Scenes;

	SpotArrayBuffer::SpotArrayBuffer (size_t maxLight, size_t HWAlignmentSize) noexcept
		: m_limit(maxLight), m_alignmentCount(HWAlignmentSize / 4), m_alignmentSize(HWAlignmentSize)
	{

	}

	size_t
	SpotArrayBuffer::maxActivableLight () const noexcept
	{
		return MaxActivableLight;
	}

	RenderPassType
	SpotArrayBuffer::renderPassType () const noexcept
	{
		return RenderPassType::SpotLightPass;
	}

	bool
	SpotArrayBuffer::initialize () noexcept
	{
		#ifdef VULKAN_DEV
		if ( !m_uniformBufferObject.allocateMappableMemory(m_limit * m_alignmentSize, BufferAccessType::Write) )
		{
			Tracer::error(ClassId, "Unable to allocate multipass UBO !");

			return false;
		}
#endif

		return true;
	}

	void
	SpotArrayBuffer::addLightToAmbient (Vector< 4, float > & sceneAmbientColor, const LightSet & lightSet, const Vector< 3, float > & cameraPosition) const noexcept
	{
		if ( lightSet.useLightDistance() )
		{
			for ( const auto & light : m_lights )
			{
				if ( !light->isEnabled() )
					continue;

				auto distance = Vector< 3, float >::distance(cameraPosition, light->parentEntity().getWorldCoordinates().position());

				if ( distance <= light->radius() )
				{
					auto factor = (light->radius() - distance) / light->radius();

					sceneAmbientColor += lightSet.getLightAmbientAddition(light) * factor;
				}
			}
		}
		else
		{
			for ( const auto & light : m_lights )
			{
				if ( !light->isEnabled() )
					continue;

				sceneAmbientColor += lightSet.getLightAmbientAddition(light);
			}
		}
	}

	bool
	SpotArrayBuffer::updateVideoMemory (const Matrix< 4, float > & viewMatrix) noexcept
	{
		#ifdef VULKAN_DEV
		auto pointer = static_cast< float * >(m_uniformBufferObject.map(BufferAccessType::Write));

		auto lightStride = 0UL;

		for ( const auto & light : m_lights )
		{
			if ( !light->isEnabled() )
				continue;

			const Vector< 4, float > position{light->worldPosition(), 1.0F};
			const Vector< 4, float > direction{light->worldDirection().inverse(), 0.0F};

			auto offset = lightStride;

			/* Light diffuse color component (4 floats). */
			offset += UniformBufferObject::copy(AbstractLightEmitter::intensifiedColor(light->diffuseColor(), light->intensity()), pointer + offset);

			/* Light specular color component (4 floats). */
			offset += UniformBufferObject::copy(AbstractLightEmitter::intensifiedColor(light->specularColor(), light->intensity()), pointer + offset);

			/* Light position in world space (4 floats). */
			offset += UniformBufferObject::copy(position, pointer + offset);

			/* Light position in view space (4 floats). */
			offset += UniformBufferObject::copy(viewMatrix * position, pointer + offset);

			/* Light direction in world space (4 floats). */
			offset += UniformBufferObject::copy(direction, pointer + offset);

			/* Light direction in view space (4 floats). */
			offset += UniformBufferObject::copy(viewMatrix * direction, pointer + offset);

			/* Light attenuation control (1 float), cone inner angle (1 float) and cone outer angle (1 float) packed into a vec3(). */
			offset += UniformBufferObject::copy(Vector< 3, float >{light->radius(), light->innerCosAngle(), light->outerCosAngle()}, pointer + offset);

			/* Light matrix (16 floats.) */
			/*offset += */UniformBufferObject::copy(light->getLightSpaceMatrix(), pointer + offset);

			/* Alignment offset. */
			lightStride += m_alignmentCount;
		}

		m_uniformBufferObject.unmap();
#endif
		return true;
	}

	void
	SpotArrayBuffer::clear () noexcept
	{
		m_lights.clear();
	}

	/*void
	SpotArrayBuffer::activateShadowMap (const Program & program, size_t lightIndex, unsigned int & nextTextureUnit) const noexcept
	{
		if ( lightIndex >= m_lights.size() )
		{
			Tracer::warning(ClassId, "Buffer overflow !");

			return;
		}

		program.bind(Samplers::ShadowMap, m_lights[lightIndex]->shadowMap()->image(), nextTextureUnit);
	}*/

	/*void
	SpotArrayBuffer::activateShadowMap (const Program & program, const ModelMatricesUBO & modelMatrices, size_t lightIndex, unsigned int & nextTextureUnit) const noexcept
	{
		if ( lightIndex >= m_lights.size() )
		{
			Tracer::warning(ClassId, "Buffer overflow !");

			return;
		}

		const auto & light = m_lights[lightIndex];

		modelMatrices.updateVideoMemoryWithShadowMap(*light->shadowMap());

		program.bind(Samplers::ShadowMap, light->shadowMap()->image(), nextTextureUnit);
	}*/

	void
	SpotArrayBuffer::printMemoryRequirement () const noexcept
	{
		std::cout <<
			"Spot lights UBO (" << m_alignmentCount << " floats, " << m_alignmentSize << " bytes) : " <<
			m_lights.size() << " lights, " <<
			m_lights.size() * m_alignmentCount << " floats, " <<
			m_lights.size() * m_alignmentSize << " bytes\n" <<
		std::endl;
	}

	bool
	SpotArrayBuffer::addLight (const std::shared_ptr< SpotLight > & light) noexcept
	{
		if ( std::find(m_lights.cbegin(), m_lights.cend(), light) != m_lights.cend() )
			return true;

		if ( m_lights.size() == m_limit )
			return false;

		m_lights.emplace_back(light);

		return true;
	}

	void
	SpotArrayBuffer::removeLight (const std::shared_ptr< SpotLight > & light) noexcept
	{
		auto it = std::find(m_lights.cbegin(), m_lights.cend(), light);

		if ( it != m_lights.cend() )
			m_lights.erase(it);
	}

	const std::vector< std::shared_ptr< SpotLight > > &
	SpotArrayBuffer::lights () const noexcept
	{
		return m_lights;
	}
}
