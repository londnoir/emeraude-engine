/*
 * src/Scenes/Component/AbstractModifier.hpp
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

#pragma once

/* STL inclusions. */
#include <memory>
#include <string>

/* Local inclusions for inheritances. */
#include "Abstract.hpp"

/* Local inclusions for usages. */
#include "Scenes/CubicInfluenceArea.hpp"
#include "Scenes/SphericalInfluenceArea.hpp"
#include "Scenes/InfluenceAreaInterface.hpp"

namespace Emeraude::Scenes::Component
{
	/**
	 * @brief The AbstractModifier class
	 * @extends Emeraude::Scenes::Component::Abstract The base class for each entity component.
	 */
	class AbstractModifier : public Abstract
	{
		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractModifier (const AbstractModifier & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractModifier (AbstractModifier && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return AbstractModifier &
			 */
			AbstractModifier & operator= (const AbstractModifier & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return AbstractModifier &
			 */
			AbstractModifier & operator= (AbstractModifier && copy) noexcept = delete;

			/**
			 * @brief Defaulted virtual destructor.
			 */
			~AbstractModifier () override = default;

			/**
			 * @brief Creates a cubic influence area and attaches it to the modifier.
			 * @param size The cube size in all directions.
			 * @return shared_ptr< CubicInfluenceArea >
			 */
			std::shared_ptr< CubicInfluenceArea >
			createCubicInfluenceArea (float size) noexcept
			{
				auto influenceArea = std::make_shared< CubicInfluenceArea >(this->parentEntity(), size);

				this->setInfluenceArea(influenceArea);

				return influenceArea;
			}

			/**
			 * @brief Creates a cubic influence area and attaches it to the modifier.
			 * @param xSize The cube size in the X axis.
			 * @param ySize The cube size in the Y axis.
			 * @param zSize The cube size in the Z axis.
			 * @return shared_ptr< CubicInfluenceArea >
			 */
			std::shared_ptr< CubicInfluenceArea >
			createCubicInfluenceArea (float xSize, float ySize, float zSize) noexcept
			{
				auto influenceArea = std::make_shared< CubicInfluenceArea >(this->parentEntity(), xSize, ySize, zSize);

				this->setInfluenceArea(influenceArea);

				return influenceArea;
			}

			/**
			 * @brief Creates a spherical influence area and attaches it to the modifier.
			 * @param outerRadius The outer radius of the sphere.
			 * @param innerRadius The inner radius of the sphere.
			 * @return shared_ptr< SphericalInfluenceArea >
			 */
			std::shared_ptr< SphericalInfluenceArea >
			createSphericalInfluenceArea (float outerRadius, float innerRadius = 0.0F) noexcept
			{
				auto influenceArea = std::make_shared< SphericalInfluenceArea >(this->parentEntity(), outerRadius, innerRadius);

				this->setInfluenceArea(influenceArea);

				return influenceArea;
			}

			/**
			 * @brief Returns whether an influence area is attached to the modifier.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			hasInfluenceArea () const noexcept
			{
				return m_influenceArea != nullptr;
			}

			/**
			 * @brief Returns the influence area interface of the modifier.
			 * @warning  can be null !
			 * @return shared_ptr< InfluenceAreaInterface >
			 */
			[[nodiscard]]
			std::shared_ptr< InfluenceAreaInterface >
			influenceArea () const noexcept
			{
				return m_influenceArea;
			}

			/**
			 * @brief Returns the force applied to an entity.
			 * @param worldCoordinates A reference to a cartesian frame.
			 * @param worldBoundingSphere A reference to a sphere.
			 * @return Libraries::Math::Vector< 3, float >
			 */
			virtual Libraries::Math::Vector< 3, float > getForceAppliedToEntity (const Libraries::Math::CartesianFrame< float > & worldCoordinates, const Libraries::Math::Sphere< float > & worldBoundingSphere) const noexcept = 0;

			/**
			 * @brief Returns the force applied to an entity.
			 * @param worldCoordinates A reference to a cartesian frame.
			 * @param worldBoundingBox A reference to a sphere.
			 * @return Libraries::Math::Vector< 3, float >
			 */
			virtual Libraries::Math::Vector< 3, float > getForceAppliedToEntity (const Libraries::Math::CartesianFrame< float > & worldCoordinates, const Libraries::Math::Cuboid< float > & worldBoundingBox) const noexcept = 0;

		protected:

			/**
			 * @brief Constructs a modifier.
			 * @param name The name of the modifier.
			 * @param parentEntity A reference to the parent entity.
			 */
			AbstractModifier (const std::string & name, const AbstractEntity & parentEntity) noexcept;
			
			/**
			 * @brief Adds an influence area to limit the modifier.
			 * @param influenceArea A reference to an influence area interface smart pointer.
			 */
			void
			setInfluenceArea (const std::shared_ptr< InfluenceAreaInterface > & influenceArea) noexcept
			{
				m_influenceArea = influenceArea;
			}

			/**
			 * @brief Removes the influence area.
			 * @return void
			 */
			void
			removeInfluenceArea () noexcept
			{
				m_influenceArea.reset();
			}

		private:

			std::shared_ptr< InfluenceAreaInterface > m_influenceArea;
	};
}
