/*
 * Emeraude/Graphics/Renderable/AbstractBackground.hpp
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
#include <cstddef>
#include <string>

/* Local inclusions for inheritances. */
#include "Interface.hpp"

/* Local inclusions for usages. */
#include "Graphics/Geometry/IndexedVertexResource.hpp"

namespace Emeraude::Graphics::Renderable
{
	/**
	 * @brief The AbstractBackground class
	 * @extends Emeraude::Graphics::Renderable::Interface This class is a renderable object in the 3D world.
	 */
	class AbstractBackground : public Interface
	{
		public:

			/** @copydoc Emeraude::Graphics::Renderable::Interface::isReadyForInstantiation() */
			[[nodiscard]]
			bool isReadyForInstantiation () const noexcept final;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::boundingBox() */
			[[nodiscard]]
			const Libraries::Math::Cuboid< float > & boundingBox () const noexcept final;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::boundingSphere() */
			[[nodiscard]]
			const Libraries::Math::Sphere< float > & boundingSphere () const noexcept final;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::flags() */
			[[nodiscard]]
			int flags (size_t layerIndex) const noexcept final;

			/**
			 * @brief Sets the average color to represent the background.
			 * @param color A reference to a color.
			 */
			void setAverageColor (const Libraries::PixelFactory::Color< float > & color) noexcept;

			/**
			 * @brief Sets the light position.
			 * @param position A reference to a position vector.
			 */
			void setLightPosition (const Libraries::Math::Vector< 3, float > & position) noexcept;

			/**
			 * @brief Sets the light ambient color.
			 * @param color A reference to a color.
			 */
			void setLightAmbientColor (const Libraries::PixelFactory::Color< float > & color) noexcept;

			/**
			 * @brief Sets the light diffuse color.
			 * @param color A reference to a color.
			 */
			void setLightDiffuseColor (const Libraries::PixelFactory::Color< float > & color) noexcept;

			/**
			 * @brief Sets the light specular color.
			 * @param color A reference to a color.
			 */
			void setLightSpecularColor (const Libraries::PixelFactory::Color< float > & color) noexcept;

			/**
			 * @brief Returns the average color of the background.
			 * @return const Libraries::PixelFactory::Color< float > &
			 */
			[[nodiscard]]
			const Libraries::PixelFactory::Color< float > & averageColor () const noexcept;

			/**
			 * @brief Returns the light position.
			 * @return const Libraries::Math::Vector< 3, float > &
			 */
			[[nodiscard]]
			const Libraries::Math::Vector< 3, float > & lightPosition () const noexcept;

			/**
			 * @brief Returns the light ambient color.
			 * @return const Libraries::PixelFactory::Color< float > &
			 */
			[[nodiscard]]
			const Libraries::PixelFactory::Color< float > & lightAmbientColor () const noexcept;

			/**
			 * @brief Returns the light diffuse color.
			 * @return const Libraries::PixelFactory::Color< float > &
			 */
			[[nodiscard]]
			const Libraries::PixelFactory::Color< float > & lightDiffuseColor () const noexcept;

			/**
			 * @brief Returns the light specular color.
			 * @return const Libraries::PixelFactory::Color< float > &
			 */
			[[nodiscard]]
			const Libraries::PixelFactory::Color< float > & lightSpecularColor () const noexcept;

			/**
			 * @brief Creates and/or returns a skybox (cube) geometry.
			 * @return shared_ptr< Geometry::IndexedVertexResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< Geometry::IndexedVertexResource > getSkyboxGeometry () noexcept;

			/**
			 * @brief Creates and/or returns a skydome (sphere) geometry.
			 * @return shared_ptr< Geometry::IndexedVertexResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< Geometry::IndexedVertexResource > getSkydomeGeometry () noexcept;

		protected:

			/**
			 * @brief Constructs a renderable background.
			 * @param name A reference to a string for the resource name.
			 * @param resourceFlagBits The resource flag bits.
			 */
			explicit AbstractBackground (const std::string & name, uint32_t resourceFlagBits) noexcept;

			/**
			 * @brief Destructs the renderable background.
			 */
			~AbstractBackground () override = default;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::setReadyForInstanciation() */
			void setReadyForInstanciation (bool state) noexcept final;

		private:

			static constexpr auto SkyBoxGeometryName = "SkyboxGeometry";
			static constexpr auto DomeGeometryName = "DomeGeometry";

			/* FIXME: Set a correct size. */
			static constexpr auto SkySize = 512.0F;

			Libraries::PixelFactory::Color< float > m_averageColor{10.0F / 256.0F, 24.0F / 256.0F, 43.0F / 256.0F, 1.0F};
			Libraries::Math::Vector< 3, float > m_lightPosition{0.6666666666666666, 0.3333333333333333, 0.6666666666666666};
			Libraries::PixelFactory::Color< float > m_lightAmbientColor{0.0F, 0.0F, 0.13F, 1.0F};
			Libraries::PixelFactory::Color< float > m_lightDiffuseColor{1.0F, 1.0F, 1.0F, 1.0F};
			Libraries::PixelFactory::Color< float > m_lightSpecularColor{1.0F, 1.0F, 1.0F, 1.0F};
			int m_renderableFlags = 0;
	};
}
