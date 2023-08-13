/*
 * Emeraude/Graphics/Material/Component/TypeColor.hpp
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

/* Local inclusions for inheritances. */
#include "TypeInterface.hpp"

/* Local inclusions for usages. */
#include "PixelFactory/Color.hpp"
#include "FastJSON.hpp"

namespace Emeraude::Graphics::Material::Component
{
	/**
	 * @brief The color component type.
	 * @extends Emeraude::Graphics::Material::Component::TypeInterface This class describe a component type.
	 */
	class TypeColor : public TypeInterface
	{
		public:

			static constexpr auto ClassId{"TypeColor"};

			/**
			 * @brief Constructs a color component.
			 * @param variableName A reference to a string.
			 * @param color A reference to a color. Default black.
			 */
			explicit TypeColor (const std::string & variableName, const Libraries::PixelFactory::Color< float > & color = {}) noexcept;

			/**
			 * @brief Constructs a color component from json data.
			 * @param variableName A reference to a string.
			 * @param data A reference to a json value.
			 */
			TypeColor (const std::string & variableName, const Json::Value & data) noexcept;

			/** @copydoc Emeraude::Graphics::Material::AbstractComponent::create() */
			[[nodiscard]]
			bool create () noexcept override;

			/** @copydoc Emeraude::Graphics::Material::AbstractComponent::isCreated() */
			[[nodiscard]]
			bool isCreated () const noexcept override;

			/** @copydoc Emeraude::Graphics::Material::AbstractComponent::variableName() */
			[[nodiscard]]
			const std::string & variableName () const noexcept override;

			/** @copydoc Emeraude::Graphics::Material::AbstractComponent::type() */
			[[nodiscard]]
			Type type () const noexcept override;

			/** @copydoc Emeraude::Graphics::Material::ComponentInterface::requestBlending() */
			[[nodiscard]]
			bool isOpaque () const noexcept override;

			/**
			 * @brief Sets a new color.
			 * @param color A reference to a color.
			 * @return void
			 */
			void setColor (const Libraries::PixelFactory::Color< float > & color) noexcept;

			/**
			 * @brief Returns the current color.
			 * @return const Libraries::PixelFactory::Color< float > &
			 */
			[[nodiscard]]
			const Libraries::PixelFactory::Color< float > & color () const noexcept;

			/**
			 * @brief Returns the current color.
			 * @return const Libraries::PixelFactory::Color< float > &
			 */
			[[nodiscard]]
			Libraries::PixelFactory::Color< float > & color () noexcept;

			/**
			 * @brief Changes the opacity value of the color.
			 * @param value A opacity value between 0.0 and 1.0
			 * @return void
			 */
			void setOpacity (float value) noexcept;

			/**
			 * @brief Returns the opacity value of the color.
			 * @return float
			 */
			[[nodiscard]]
			float opacity () const noexcept;

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const TypeColor & obj);

			/**
			 * @brief Stringify the object.
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend std::string to_string (const TypeColor & obj) noexcept;

		private:

			std::string m_variableName;
			Libraries::PixelFactory::Color< float > m_color;
	};
}
