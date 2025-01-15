/*
 * src/Graphics/Material/Component/Interface.hpp
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
#include <cstdint>
#include <memory>
#include <string>

/* Local inclusions for usages. */
#include "Graphics/Types.hpp"

namespace Emeraude::Graphics
{
	namespace TextureResource
	{
		class Abstract;
	}

	class Renderer;
}

namespace Emeraude::Graphics::Material::Component
{
	/** @brief The component type enumeration. */
	enum class Type : uint8_t
	{
		Value,
		Color,
		Texture,
		None
	};

	/**
	 * @brief The component interface for material.
	 */
	class Interface
	{
		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Interface (const Interface & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Interface (Interface && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return Interface &
			 */
			Interface & operator= (const Interface & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return Interface &
			 */
			Interface & operator= (Interface && copy) noexcept = default;

			/**
			 * @brief Destructs the type interface.
			 */
			virtual ~Interface () = default;

			/**
			 * @brief Creates the underlying component resources.
			 * @param renderer A reference to the graphics renderer.
			 * @param binding A reference to a binding if requested.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool create (Renderer & renderer, uint32_t & binding) noexcept = 0;

			/**
			 * @brief Returns whether the component is created.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isCreated () const noexcept = 0;

			/**
			 * @brief Return the variable name.
			 * @return const std::string &
			 */
			[[nodiscard]]
			virtual const std::string & variableName () const noexcept = 0;

			/**
			 * @brief Returns the type of component.
			 * @return Type
			 */
			[[nodiscard]]
			virtual Type type () const noexcept = 0;

			/**
			 * @brief Returns whether this component is opaque.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isOpaque () const noexcept = 0;

			/**
			 * @brief Returns the texture resource.
			 * @return std::shared_ptr< TextureResource::Abstract >
			 */
			[[nodiscard]]
			virtual std::shared_ptr< TextureResource::Abstract > textureResource () const noexcept = 0;

		protected:

			/** 
			 * @brief Constructs a type interface.
			 */
			Interface () noexcept = default;
	};
}
