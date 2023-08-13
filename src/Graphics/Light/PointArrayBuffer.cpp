/*
 * Emeraude/Graphics/Light/PointArrayBuffer.cpp
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

#include "PointArrayBuffer.hpp"

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

	PointArrayBuffer::PointArrayBuffer (size_t maxLight, size_t HWAlignmentSize) noexcept
		: m_limit(maxLight), m_alignmentCount(HWAlignmentSize / 4), m_alignmentSize(HWAlignmentSize)
	{

	}

	size_t
	PointArrayBuffer::maxActivableLight () const noexcept
	{
		return MaxActivableLight;
	}

	RenderPassType
	PointArrayBuffer::renderPassType () const noexcept
	{
		return RenderPassType::PointLightPass;
	}

	bool
	PointArrayBuffer::initialize () noexcept
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
	PointArrayBuffer::addLightToAmbient (Vector< 4, float > & sceneAmbientColor, const LightSet & lightSet, const Vector< 3, float > & cameraPosition) const noexcept
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
	PointArrayBuffer::updateVideoMemory (const Matrix< 4, float > & viewMatrix) noexcept
	{
#ifdef VULKAN_DEV
		auto pointer = static_cast< float * >(m_uniformBufferObject.map(BufferAccessType::Write));

		auto lightStride = 0UL;

		for ( const auto & light : m_lights )
		{
			if ( !light->isEnabled() )
				continue;

			const Vector< 4, float > position{light->worldPosition(), 1.0F};

			auto offset = lightStride;

			/* Light diffuse color component (4 floats). */
			offset += UniformBufferObject::copy(AbstractLightEmitter::intensifiedColor(light->diffuseColor(), light->intensity()), pointer + offset);

			/* Light specular color component (4 floats). */
			offset += UniformBufferObject::copy(AbstractLightEmitter::intensifiedColor(light->specularColor(), light->intensity()), pointer + offset);

			/* Light position in world space (4 floats). */
			offset += UniformBufferObject::copy(position, pointer + offset);

			/* Light position in view space (4 floats). */
			offset += UniformBufferObject::copy(viewMatrix * position, pointer + offset);

			/* Light attenuation control (1 float). */
			offset += UniformBufferObject::copy(light->radius(), pointer + offset);

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
	PointArrayBuffer::clear () noexcept
	{
		m_lights.clear();
	}

	/*void
	PointArrayBuffer::activateShadowMap (const Program & program, size_t lightIndex, unsigned int & nextTextureUnit) const noexcept
	{
		if ( lightIndex >= m_lights.size() )
		{
			Tracer::warning(ClassId, "Buffer overflow !");

			return;
		}

		const auto & shadowMap = m_lights[lightIndex]->shadowMap();

		program.bind(Samplers::ShadowMap, shadowMap->image(), nextTextureUnit);

		const auto & viewProperties = shadowMap->viewProperties();
		program.sendUniform(Uniforms::NearFar, Math::Vector< 2, float >(viewProperties[Z], viewProperties[W]));
	}*/

	/*void
	PointArrayBuffer::activateShadowMap (const Program & program, const ModelMatricesUBO &, size_t lightIndex, unsigned int & nextTextureUnit) const noexcept
	{
		if ( lightIndex >= m_lights.size() )
		{
			Tracer::warning(ClassId, "Buffer overflow !");

			return;
		}

		const auto & shadowMap = m_lights[lightIndex]->shadowMap();

		program.bind(Samplers::ShadowMap, shadowMap->image(), nextTextureUnit);

		const auto & viewProperties = shadowMap->viewProperties();
		program.sendUniform(Uniforms::NearFar, Math::Vector< 2, float >(viewProperties[Z], viewProperties[W]));
	}*/

	void
	PointArrayBuffer::printMemoryRequirement () const noexcept
	{
		std::cout <<
			"Point lights UBO (" << m_alignmentCount << " floats, " << m_alignmentSize << " bytes) : " <<
			m_lights.size() << " lights, " <<
			m_lights.size() * m_alignmentCount << " floats, " <<
			m_lights.size() * m_alignmentSize << " bytes\n" <<
		std::endl;
	}

	bool
	PointArrayBuffer::addLight (const std::shared_ptr< PointLight > & light) noexcept
	{
		if ( std::find(m_lights.cbegin(), m_lights.cend(), light) != m_lights.cend() )
			return true;

		if ( m_lights.size() == m_limit )
			return false;

		m_lights.emplace_back(light);

		return true;
	}

	void
	PointArrayBuffer::removeLight (const std::shared_ptr< PointLight > & light) noexcept
	{
		auto it = std::find(m_lights.cbegin(), m_lights.cend(), light);

		if ( it != m_lights.cend() )
			m_lights.erase(it);
	}

	const std::vector< std::shared_ptr< PointLight > > &
	PointArrayBuffer::lights () const noexcept
	{
		return m_lights;
	}
}
