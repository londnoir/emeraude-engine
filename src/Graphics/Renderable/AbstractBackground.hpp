/*
 * src/Graphics/Renderable/AbstractBackground.hpp
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
#include <cstdint>
#include <memory>
#include <string>

/* Local inclusions for inheritances. */
#include "Interface.hpp"

/* Local inclusions for usages. */
#include "Libs/PixelFactory/Color.hpp"
#include "Graphics/Geometry/IndexedVertexResource.hpp"

namespace EmEn::Graphics::Renderable
{
	/**
	 * @brief An abstract class to define the far background of a scene.
	 * @extends EmEn::Graphics::Renderable::Interface This class is a renderable object in the 3D world.
	 */
	class AbstractBackground : public Interface
	{
		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractBackground (const AbstractBackground & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractBackground (AbstractBackground && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return AbstractBackground &
			 */
			AbstractBackground & operator= (const AbstractBackground & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return AbstractBackground &
			 */
			AbstractBackground & operator= (AbstractBackground && copy) noexcept = delete;

			/**
			 * @brief Destructs the renderable background.
			 */
			~AbstractBackground () override = default;

			/** @copydoc EmEn::Graphics::Renderable::Interface::boundingBox() */
			[[nodiscard]]
			const Libs::Math::Cuboid< float > & boundingBox () const noexcept final;

			/** @copydoc EmEn::Graphics::Renderable::Interface::boundingSphere() */
			[[nodiscard]]
			const Libs::Math::Sphere< float > & boundingSphere () const noexcept final;

			/**
			 * @brief Sets the average color to represent the background.
			 * @param color A reference to a color.
			 * @return void
			 */
			void setAverageColor (const Libs::PixelFactory::Color< float > & color) noexcept;

			/**
			 * @brief Sets the light position.
			 * @param position A reference to a position vector.
			 * @return void
			 */
			void setLightPosition (const Libs::Math::Vector< 3, float > & position) noexcept;

			/**
			 * @brief Sets the light ambient color.
			 * @param color A reference to a color.
			 * @return void
			 */
			void setLightAmbientColor (const Libs::PixelFactory::Color< float > & color) noexcept;

			/**
			 * @brief Sets the light diffuse color.
			 * @param color A reference to a color.
			 * @return void
			 */
			void setLightDiffuseColor (const Libs::PixelFactory::Color< float > & color) noexcept;

			/**
			 * @brief Sets the light specular color.
			 * @param color A reference to a color.
			 * @return void
			 */
			void setLightSpecularColor (const Libs::PixelFactory::Color< float > & color) noexcept;

			/**
			 * @brief Returns the average color of the background.
			 * @return const Libraries::PixelFactory::Color< float > &
			 */
			[[nodiscard]]
			const Libs::PixelFactory::Color< float > & averageColor () const noexcept;

			/**
			 * @brief Returns the light position.
			 * @return const Libraries::Math::Vector< 3, float > &
			 */
			[[nodiscard]]
			const Libs::Math::Vector< 3, float > & lightPosition () const noexcept;

			/**
			 * @brief Returns the light ambient color.
			 * @return const Libraries::PixelFactory::Color< float > &
			 */
			[[nodiscard]]
			const Libs::PixelFactory::Color< float > & lightAmbientColor () const noexcept;

			/**
			 * @brief Returns the light diffuse color.
			 * @return const Libraries::PixelFactory::Color< float > &
			 */
			[[nodiscard]]
			const Libs::PixelFactory::Color< float > & lightDiffuseColor () const noexcept;

			/**
			 * @brief Returns the light specular color.
			 * @return const Libraries::PixelFactory::Color< float > &
			 */
			[[nodiscard]]
			const Libs::PixelFactory::Color< float > & lightSpecularColor () const noexcept;

			/**
			 * @brief Creates and/or returns a sky box (cube) geometry.
			 * @return shared_ptr< Geometry::IndexedVertexResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< Geometry::IndexedVertexResource > getSkyBoxGeometry () noexcept;

			/**
			 * @brief Creates and/or returns a sky dome (sphere) geometry.
			 * @return shared_ptr< Geometry::IndexedVertexResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< Geometry::IndexedVertexResource > getSkyDomeGeometry () noexcept;

		protected:

			/**
			 * @brief Constructs a renderable background.
			 * @param name A reference to a string for the resource name.
			 * @param resourceFlagBits The resource flag bits.
			 */
			explicit AbstractBackground (const std::string & name, uint32_t resourceFlagBits) noexcept;

		private:

			static constexpr auto SkyBoxGeometryName{"SkyBoxGeometry"};
			static constexpr auto SkyDomeGeometryName{"SkyDomeGeometry"};

			/* FIXME: Set a correct size. */
			static constexpr auto SkySize{512.0F};

			Libs::PixelFactory::Color< float > m_averageColor{10.0F / 256.0F, 24.0F / 256.0F, 43.0F / 256.0F, 1.0F};
			Libs::Math::Vector< 3, float > m_lightPosition{0.6666F, 0.3333F, 0.6666F};
			Libs::PixelFactory::Color< float > m_lightAmbientColor{0.0F, 0.0F, 0.13F, 1.0F};
			Libs::PixelFactory::Color< float > m_lightDiffuseColor{1.0F, 1.0F, 1.0F, 1.0F};
			Libs::PixelFactory::Color< float > m_lightSpecularColor{1.0F, 1.0F, 1.0F, 1.0F};
	};
}
