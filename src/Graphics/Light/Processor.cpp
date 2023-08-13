/*
 * Emeraude/Graphics/Light/Processor.cpp
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

#include "Processor.hpp"

/* Local inclusions */
#include "Tracer.hpp"
#include "Saphir/Keys.hpp"
#include "Graphics/Renderer.hpp"

namespace Emeraude::Graphics::Light
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Saphir;
	using namespace Saphir::Keys;
	using namespace Scenes;

	Processor::Processor (size_t maxDirectionalCount, size_t maxPointCount, size_t maxSpotCount) noexcept
		: m_directionalLightArrayBuffer(maxDirectionalCount), m_pointLightArrayBuffer(maxPointCount), m_spotLightArrayBuffer(maxSpotCount)
	{

	}

	void
	Processor::enableLighting (bool state) noexcept
	{
		m_flags[IsLightingEnabled] = state;
	}

	bool
	Processor::toggleLighting () noexcept
	{
		return m_flags[IsLightingEnabled] = !m_flags[IsLightingEnabled];
	}

	bool
	Processor::isLightingEnabled () const noexcept
	{
		return m_flags[IsLightingEnabled];
	}

	void
	Processor::enableShadowing (bool state) noexcept
	{
		m_flags[IsShadowingEnabled] = state;
	}

	bool
	Processor::toggleShadowing () noexcept
	{
		return m_flags[IsShadowingEnabled] = !m_flags[IsShadowingEnabled];
	}

	bool
	Processor::isShadowingEnabled () const noexcept
	{
		return m_flags[IsShadowingEnabled];
	}

	void
	Processor::setLightSet (const std::shared_ptr< LightSet > & lightSet) noexcept
	{
		/* Erase previous light passes. */
		m_directionalLightArrayBuffer.clear();
		m_pointLightArrayBuffer.clear();
		m_spotLightArrayBuffer.clear();

		/* Sets the new light set */
		m_lightSet = lightSet;

		/* Updates existing lights from the light set */
		for ( const auto & light : m_lightSet->lights() )
		{
			const auto directionalLight = std::dynamic_pointer_cast< DirectionalLight >(light);

			if ( directionalLight != nullptr )
			{
				m_directionalLightArrayBuffer.addLight(directionalLight);

				continue;
			}

			const auto pointLight = std::dynamic_pointer_cast< PointLight >(light);

			if ( pointLight != nullptr )
			{
				m_pointLightArrayBuffer.addLight(pointLight);

				continue;
			}

			const auto spotLight = std::dynamic_pointer_cast< SpotLight >(light);

			if ( spotLight != nullptr )
			{
				m_spotLightArrayBuffer.addLight(spotLight);

				continue;
			}
		}

		/* Observer light set for further light adding or removing. */
		this->observe(m_lightSet.get());
	}

	std::shared_ptr< LightSet >
	Processor::lightSet () const noexcept
	{
		return m_lightSet;
	}

	bool
	Processor::initialize () noexcept
	{
		if ( !m_directionalLightArrayBuffer.initialize() )
		{
			Tracer::error(ClassId, "Unable to initialize directional lights buffer !");

			return false;
		}

		if ( !m_pointLightArrayBuffer.initialize() )
		{
			Tracer::error(ClassId, "Unable to initialize point lights buffer !");

			return false;
		}

		if ( !m_spotLightArrayBuffer.initialize() )
		{
			Tracer::error(ClassId, "Unable to initialize spot lights buffer !");

			return false;
		}

		return true;
	}

	bool
	Processor::updateVideoMemory (const Matrix< 4, float > & view) noexcept
	{
		if ( m_lightSet == nullptr )
		{
			Tracer::error(ClassId, "No LightSet bound to this Processor to update local buffers !");

			return false;
		}

		if ( !this->isLightingEnabled() )
			return true;

		/* NOTE: Only useful for point and spotlights. */
		const auto inverseView = view.inverse();
		const auto cameraPosition = Vector< 3, float >{inverseView[M4x4Col3Row0], inverseView[M4x4Col3Row1], inverseView[M4x4Col3Row2]};

		/* Init the global ambient light level. */
		m_ambientLight = m_lightSet->globalAmbientLight().toVector4< float >();

		m_directionalLightArrayBuffer.addLightToAmbient(m_ambientLight, *m_lightSet, cameraPosition);

		m_pointLightArrayBuffer.addLightToAmbient(m_ambientLight, *m_lightSet, cameraPosition);

		m_spotLightArrayBuffer.addLightToAmbient(m_ambientLight, *m_lightSet, cameraPosition);

		if ( !m_directionalLightArrayBuffer.updateVideoMemory(view) )
		{
			Tracer::error(ClassId, "Unable to update directional lights buffer video memory !");

			return false;
		}

		if ( !m_pointLightArrayBuffer.updateVideoMemory(view) )
		{
			Tracer::error(ClassId, "Unable to update point lights buffer video memory !");

			return false;
		}

		if ( !m_spotLightArrayBuffer.updateVideoMemory(view) )
		{
			Tracer::error(ClassId, "Unable to update spot lights buffer video memory !");

			return false;
		}

		return true;
	}

	/*void
	Processor::enableAmbientLight (const Program & program) const noexcept
	{
		program.sendUniform(Uniforms::AmbientLight, this->isLightingEnabled() ? m_ambientLight : Vector< 4, float >{1.0F, 1.0F, 1.0F, 1.0F});
	}*/

	void
	Processor::renderLightPasses (Renderer & renderer, const Sphere< float > & modelRadius, const std::function< void (RenderPassType renderPassType, const ArrayBufferInterface & lightBuffer, size_t lightIndex, bool isShadowEnabled) > & render) const noexcept
	{
#ifdef VULKAN_DEV
		if ( !this->isLightingEnabled() )
			return;

		/* Keep previous configuration. */
		GLint previousDepthFunc;

		glGetIntegerv(GL_DEPTH_FUNC, &previousDepthFunc);

		auto previousBlendingMode = renderer.blendingMode();

		/* Sets depth buffer to less or equal to recover
		 * the same geometry with blending mode set to ADD. */
		glDepthFunc(GL_LEQUAL);

		renderer.setBlendingMode(BlendingMode::Add);

		/* Render throught every directional lights... */
		for ( auto it = m_directionalLightArrayBuffer.lights().cbegin(); it != m_directionalLightArrayBuffer.lights().cend(); ++it )
		{
			auto & light = (*it);

			if ( !light->isEnabled() )
				continue;

			render(
				RenderPassType::DirectionalLightPass,
				m_directionalLightArrayBuffer,
				std::distance(m_directionalLightArrayBuffer.lights().cbegin(), it),
				this->isShadowingEnabled() && light->isShadowEnabled()
			);
		}

		/* ... Then throught every point lights. */
		for ( auto it = m_pointLightArrayBuffer.lights().cbegin(); it != m_pointLightArrayBuffer.lights().cend(); ++it )
		{
			auto & light = (*it);

			if ( !light->isEnabled() )
				continue;

			if ( light->radius() > 0.0F && !modelRadius.isCollidingWith(light->worldPosition(), light->radius()) )
				continue;

			render(
				RenderPassType::PointLightPass,
				m_pointLightArrayBuffer,
				std::distance(m_pointLightArrayBuffer.lights().cbegin(), it),
				this->isShadowingEnabled() && light->isShadowEnabled()
			);
		}

		/* ... And finally throught every spot lights. */
		for ( auto it = m_spotLightArrayBuffer.lights().cbegin(); it != m_spotLightArrayBuffer.lights().cend(); ++it )
		{
			auto & light = (*it);

			if ( !light->isEnabled() )
				continue;

			if ( light->radius() > 0.0F && !modelRadius.isCollidingWith(light->worldPosition(), light->radius()) )
				continue;

			/* FIXME: Use spot direction to discard a out of sight render ! */

			render(
				RenderPassType::SpotLightPass,
				m_spotLightArrayBuffer,
				std::distance(m_spotLightArrayBuffer.lights().cbegin(), it),
				this->isShadowingEnabled() && light->isShadowEnabled()
			);
		}

		/* Restore configuration. */
		glDepthFunc(static_cast< GLenum>(previousDepthFunc));

		renderer.setBlendingMode(previousBlendingMode);
#endif
	}

	bool
	Processor::onNotification (const Observable * observable, int notificationCode, const std::any & data) noexcept
	{
		if ( observable->is(LightSet::ClassUID) )
		{
			switch ( notificationCode )
			{
				case LightSet::DirectionalLightAdded :
					if ( !m_directionalLightArrayBuffer.addLight(std::any_cast< std::shared_ptr< DirectionalLight > >(data)) )
						Tracer::warning(ClassId, "Directional light limit reached !");
					break;

				case LightSet::PointLightAdded :
					if ( !m_pointLightArrayBuffer.addLight(std::any_cast< std::shared_ptr< PointLight > >(data)) )
						Tracer::warning(ClassId, "Point light limit reached !");
					break;

				case LightSet::SpotLightAdded :
					if ( !m_spotLightArrayBuffer.addLight(std::any_cast< std::shared_ptr< SpotLight > >(data)) )
						Tracer::warning(ClassId, "Spot light limit reached !");
					break;

				case LightSet::DirectionalLightRemoved :
					m_directionalLightArrayBuffer.removeLight(std::any_cast< std::shared_ptr< DirectionalLight > >(data));
					break;

				case LightSet::PointLightRemoved :
					m_pointLightArrayBuffer.removeLight(std::any_cast< std::shared_ptr< PointLight > >(data));
					break;

				case LightSet::SpotLightRemoved :
					m_spotLightArrayBuffer.removeLight(std::any_cast< std::shared_ptr< SpotLight > >(data));
					break;

				default:
					TraceDebug{ClassId} << "Event #" << notificationCode << " from the light set ignored.";
					break;
			}

			return true;
		}

#ifdef DEBUG
		/* NOTE: Don't know what is it, goodbye ! */
		TraceInfo{ClassId} <<
			"Received an unhandled event from observable @" << observable << " (code:" << notificationCode << ") ! "
			"Forgetting it ...";
#endif

		return false;
	}
}
