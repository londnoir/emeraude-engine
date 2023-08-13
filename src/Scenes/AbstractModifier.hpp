/*
 * Emeraude/Scenes/AbstractModifier.hpp
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
#include <memory>

/* Local inclusions for inheritances. */
#include "AbstractComponent.hpp"

/* Local inclusions for usages. */
#include "Physics/MovableTrait.hpp"
#include "CubicInfluenceArea.hpp"
#include "SphericalInfluenceArea.hpp"

namespace Emeraude::Scenes
{
	/**
	 * @brief The AbstractModifier class
	 * @extends Emeraude::Scenes::AbstractComponent The base class for each entity component.
	 */
	class AbstractModifier : public AbstractComponent
	{
		public:

			/**
			 * @brief Creates a cubic influence area a attach it to the modifier.
			 * @param size The cube size in all directions.
			 * @return shared_ptr< CubicInfluenceArea >
			 */
			virtual std::shared_ptr< CubicInfluenceArea > createCubicInfluenceArea (float size) noexcept final;

			/**
			 * @brief Creates a cubic influence area a attach it to the modifier.
			 * @param xSize The cube size in the X axis.
			 * @param ySize The cube size in the Y axis.
			 * @param zSize The cube size in the Z axis.
			 * @return shared_ptr< CubicInfluenceArea >
			 */
			virtual std::shared_ptr< CubicInfluenceArea > createCubicInfluenceArea (float xSize, float ySize, float zSize) noexcept final;

			/**
			 * @brief Creates a spherical influence area a attach it to the modifier.
			 * @param outerRadius The outer radius of the sphere.
			 * @param innerRadius The inner radius of the sphere.
			 * @return shared_ptr< SphericalInfluenceArea >
			 */
			virtual std::shared_ptr< SphericalInfluenceArea > createSphericalInfluenceArea (float outerRadius, float innerRadius = 0.0F) noexcept final;

			/**
			 * @brief Returns whether a influence area is attached to the modifier.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool hasInfluenceArea () const noexcept final;

			/**
			 * @brief Returns the influence area interface of the modifier.
			 * @warning  can be null !
			 * @return shared_ptr< InfluenceAreaInterface >
			 */
			[[nodiscard]]
			virtual std::shared_ptr< InfluenceAreaInterface > influenceArea () const noexcept final;

			/** @brief Removes the influence area. */
			virtual void removeInfluenceArea () noexcept final;

			/**
			 * @brief Applies the modifier to a scene node.
			 * @param movable A reference to a movable things in the scene.
			 */
			virtual void apply (Physics::MovableTrait & movable) const noexcept = 0;

		protected:

			/**
			 * @brief Constructs a modifier.
			 * @param name The name of the modifier.
			 * @param parentEntity A reference to the parent entity.
			 */
			AbstractModifier (const std::string & name, const AbstractEntity & parentEntity) noexcept;

			/** @brief Defaulted virtual destructor. */
			~AbstractModifier () override = default;

			/**
			 * @brief Adds an influence area to limit the modifier.
			 * @param influenceArea A reference to a influence area interface smart pointer.
			 */
			virtual void addInfluenceArea (const std::shared_ptr< InfluenceAreaInterface > & influenceArea) noexcept final;

		private:

			std::shared_ptr< InfluenceAreaInterface > m_influenceArea{};
	};
}
