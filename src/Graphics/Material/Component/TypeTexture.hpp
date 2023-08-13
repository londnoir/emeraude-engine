/*
 * Emeraude/Graphics/Material/Component/TypeTexture.hpp
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
#include "TypeInterface.hpp"

/* Local inclusions for usages. */
#include "Graphics/TextureResource/Abstract.hpp"
#include "Graphics/Types.hpp"
#include "FastJSON.hpp"
#include "Math/Vector.hpp"
#include "Saphir/Keys.hpp"

namespace Emeraude::Graphics::Material::Component
{
	/**
	 * @brief The texture component type.
	 * @extends Emeraude::Graphics::Material::Component::TypeInterface This class describe a component type.
	 */
	class TypeTexture : public TypeInterface
	{
		public:

			static constexpr auto ClassId{"TypeTexture"};

			/**
			 * @brief Constructs a texture component.
			 * @param variableName A reference to a string.
			 * @param texture A reference to a texture resource smart pointer.
			 * @param UVWChannel The texture channel to use on geometry. Default 0.
			 * @param UVWScale A reference to a vector to scale the texture coordinates. Default 1.0 in all directions.
			 * @param enableAlpha Enable the alpha channel for opacity/blending. Request a 4 channels texture. Default false.
			 */
			TypeTexture (const std::string & variableName, const std::shared_ptr< TextureResource::Abstract > & texture, uint32_t UVWChannel = 0, const Libraries::Math::Vector< 3, float > & UVWScale = {1.0F, 1.0F, 1.0F}, bool enableAlpha = false) noexcept;

			/**
			 * @brief Constructs a texture component from json data.
			 * @param variableName A reference to a string.
			 * @param data A reference to a json value.
			 * @param fillingType A reference to a texture filling type.
			 */
			TypeTexture (const std::string & variableName, const Json::Value & data, const FillingType & fillingType) noexcept;

			/** @copydoc Emeraude::Graphics::Material::ComponentInterface::create() */
			[[nodiscard]]
			bool create () noexcept override;

			/** @copydoc Emeraude::Graphics::Material::ComponentInterface::isCreated() */
			[[nodiscard]]
			bool isCreated () const noexcept override;

			/** @copydoc Emeraude::Graphics::Material::ComponentInterface::variableName() */
			[[nodiscard]]
			const std::string & variableName () const noexcept override;

			/** @copydoc Emeraude::Graphics::Material::ComponentInterface::type() */
			[[nodiscard]]
			Type type () const noexcept override;

			/** @copydoc Emeraude::Graphics::Material::ComponentInterface::requestBlending() */
			[[nodiscard]]
			bool isOpaque () const noexcept override;

			/**
			 * @brief Sets a texture.
			 * @param texture A reference to a texture resource smart pointer.
			 * @return void
			 */
			void setTexture (const std::shared_ptr< TextureResource::Abstract > & texture) noexcept;

			/**
			 * @brief Changes the texture channel.
			 * @param UVWChannel The texture channel to use on geometry.
			 * @return void
			 */
			void setUVWChannel (uint32_t UVWChannel) noexcept;

			/**
			 * @brief Scales the texture coordinates.
			 * @param UVWScale A reference to a vector to scale the texture coordinates.
			 * @return void
			 */
			void setUVWScale (const Libraries::Math::Vector< 3, float > & UVWScale) noexcept;

			/**
			 * @brief Returns the texture resource.
			 * @return const std::shared_ptr< TextureResource::Abstract > &
			 */
			[[nodiscard]]
			const std::shared_ptr< TextureResource::Abstract > & texture () const noexcept;

			/**
			 * @brief Returns the texture channel.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t UVWChannel () const noexcept;

			/**
			 * @brief Returns the texture coordinates scale.
			 * @return const Libraries::Math::Vector< 3, float > &
			 */
			[[nodiscard]]
			const Libraries::Math::Vector< 3, float > & UVWScale () const noexcept;

			/**
			 * @brief Returns whether the texture is volumetric and needs 3D coordinates.
			 * @return bool
			 */
			[[nodiscard]]
			bool isVolumetricTexture () const noexcept;

			/**
			 * @brief Returns the GLSL type of texture.
			 * @return Saphir::Key
			 */
			[[nodiscard]]
			Saphir::Key textureType () const noexcept;

			/**
			 * @brief Enables the alpha channel of the texture for opacity/blending.
			 * @param state The state.
			 * @return void
			 */
			void enableAlpha (bool state) noexcept;

			/**
			 * @brief Returns whethe the alpha channel of the texture is used for opacity/blending.
			 * @return bool
			 */
			[[nodiscard]]
			bool alphaEnabled () const noexcept;

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const TypeTexture & obj);

			/**
			 * @brief Stringify the object.
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend std::string to_string (const TypeTexture & obj) noexcept;

		private:

			/* JSON key. */
			static constexpr auto JKResourceName = "Name";
			static constexpr auto JKChannel = "Channel";
			static constexpr auto JKUVWScale = "UVW";
			static constexpr auto JKEnableAlpha = "EnableAlpha";

			std::string m_variableName;
			std::shared_ptr< TextureResource::Abstract > m_texture{};
			uint32_t m_UVWChannel{0};
			Libraries::Math::Vector< 3, float > m_UVWScale{1.0F, 1.0F, 1.0F};
			bool m_alphaEnabled{false};
	};
}
