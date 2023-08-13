/*
 * Emeraude/Graphics/Material/Component/TypeInterface.hpp
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
#include <string>

/* Local inclusions for usages. */
#include "Graphics/Types.hpp"
#include "FastJSON.hpp"

namespace Emeraude::Graphics::Material::Component
{
	/** @brief The component type enumeration. */
	enum class Type
	{
		Value,
		Color,
		Texture,
		None
	};

	/**
	 * @brief The component interface for material.
	 */
	class TypeInterface
	{
		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			TypeInterface (const TypeInterface & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			TypeInterface (TypeInterface && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return TypeInterface &
			 */
			TypeInterface & operator= (const TypeInterface & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return TypeInterface &
			 */
			TypeInterface & operator= (TypeInterface && copy) noexcept = default;

			/**
			 * @brief Destructs the type interface.
			 */
			virtual ~TypeInterface () = default;

			/**
			 * @brief Creates the underlying component resources.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool create () noexcept = 0;

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
			 * @brief Parses the base of a component structure.
			 * @param data A reference to the json value.
			 * @param fillingType A reference to filling type to complete, if succeed.
			 * @param componentData A reference to component data to complete, if succeed.
			 * @return bool
			 */
			[[nodiscard]]
			static bool parseBase (const Json::Value & data, FillingType & fillingType, Json::Value & componentData) noexcept;

			/**
			 * @brief Parses a component as a value.
			 * @param data A reference to the json value.
			 * @param componentType A C-String point to the targeted component.
			 * @param value A reference to the value to complete, if succeed.
			 * @return bool
			 */
			[[nodiscard]]
			static bool getComponentAsValue (const Json::Value & data, const char * componentType, float & value) noexcept;

		protected:

			/** 
			 * @brief Constructs a type interface.
			 */
			TypeInterface () noexcept = default;

		private:

			/* JSON key. */
			static constexpr auto JKType = "Type";
			static constexpr auto JKData = "Data";
	};
}
