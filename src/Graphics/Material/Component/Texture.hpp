/*
 * src/Graphics/Material/Component/Texture.hpp
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
#include <ostream>
#include <string>

/* Local inclusions for inheritances. */
#include "Interface.hpp"

/* Local inclusions for usages. */
#include "Libs/Math/Vector.hpp"
#include "Graphics/TextureResource/Abstract.hpp"
#include "Graphics/Types.hpp"
#include "Saphir/Keys.hpp"

/* Forward declarations */
namespace EmEn::Resources
{
	class Manager;
}

namespace EmEn::Graphics::Material::Component
{
	/**
	 * @brief The texture component type.
	 * @extends EmEn::Graphics::Material::Component::Interface This class describe a component type.
	 */
	class Texture : public Interface
	{
		public:

			static constexpr auto ClassId{"Texture"};

			/**
			 * @brief Constructs a texture component.
			 * @param samplerName A C-string for the name of the sampler uniform.
			 * @param variableName A string [std::move].
			 * @param texture A reference to a texture resource smart pointer.
			 * @param UVWChannel The texture channel to use on geometry. Default 0.
			 * @param UVWScale A reference to a vector to scale the texture coordinates. Default 1.0 in all directions.
			 * @param enableAlpha Enable the alpha channel for opacity/blending. Request a 4 channels texture. Default false.
			 */
			Texture (const char * samplerName, std::string variableName, const std::shared_ptr< TextureResource::Abstract > & texture, uint32_t UVWChannel = 0, const Libs::Math::Vector< 3, float > & UVWScale = {1.0F, 1.0F, 1.0F}, bool enableAlpha = false) noexcept;

			/**
			 * @brief Constructs a texture component from json data.
			 * @param samplerName A C-string for the name of the sampler uniform.
			 * @param variableName A string [std::move].
			 * @param data A reference to a json value.
			 * @param fillingType A reference to a texture filling type.
			 * @param resources A reference to the resource manager.
			 */
			Texture (const char * samplerName, std::string variableName, const Json::Value & data, const FillingType & fillingType, Resources::Manager & resources) noexcept;

			/** @copydoc EmEn::Graphics::Material::Component::Interface::create() */
			[[nodiscard]]
			bool create (Renderer & renderer, uint32_t & binding) noexcept override;

			/** @copydoc EmEn::Graphics::Material::Component::Interface::isCreated() */
			[[nodiscard]]
			bool
			isCreated () const noexcept override
			{
				if ( m_texture == nullptr )
				{
					return false;
				}

				return m_texture->isCreated();
			}

			/** @copydoc EmEn::Graphics::Material::Component::Interface::variableName() */
			[[nodiscard]]
			const std::string &
			variableName () const noexcept override
			{
				return m_variableName;
			}

			/** @copydoc EmEn::Graphics::Material::Component::Interface::type() */
			[[nodiscard]]
			Type
			type () const noexcept override
			{
				return Type::Texture;
			}

			/** @copydoc EmEn::Graphics::Material::Component::Interface::isOpaque() */
			[[nodiscard]]
			bool
			isOpaque () const noexcept override
			{
				return !m_alphaEnabled;
			}

			/** @copydoc EmEn::Graphics::Material::Component::Interface::textureResource() */
			[[nodiscard]]
			std::shared_ptr< TextureResource::Abstract >
			textureResource () const noexcept override
			{
				return m_texture;
			}

			/**
			 * @brief Sets a texture.
			 * @param texture A reference to a texture resource smart pointer.
			 * @return void
			 */
			void
			setTexture (const std::shared_ptr< TextureResource::Abstract > & texture) noexcept
			{
				m_texture = texture;
			}

			/**
			 * @brief Changes the texture channel.
			 * @param UVWChannel The texture channel to use on geometry.
			 * @return void
			 */
			void
			setUVWChannel (uint32_t UVWChannel) noexcept
			{
				m_UVWChannel = UVWChannel;
			}

			/**
			 * @brief Scales the texture coordinates.
			 * @param UVWScale A reference to a vector to scale the texture coordinates.
			 * @return void
			 */
			void
			setUVWScale (const Libs::Math::Vector< 3, float > & UVWScale) noexcept
			{
				m_UVWScale = UVWScale;
			}

			/**
			 * @brief Returns the texture channel.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t
			UVWChannel () const noexcept
			{
				return m_UVWChannel;
			}

			/**
			 * @brief Returns the texture coordinates scale.
			 * @return const Libraries::Math::Vector< 3, float > &
			 */
			[[nodiscard]]
			const Libs::Math::Vector< 3, float > &
			UVWScale () const noexcept
			{
				return m_UVWScale;
			}

			/**
			 * @brief Returns whether the texture is volumetric and needs 3D coordinates.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isVolumetricTexture () const noexcept
			{
				return m_texture->request3DTextureCoordinates();
			}

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
			void
			enableAlpha (bool state) noexcept
			{
				m_alphaEnabled = state;
			}

			/**
			 * @brief Returns whether the alpha channel of the texture is used for opacity/blending.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			alphaEnabled () const noexcept
			{
				return m_alphaEnabled;
			}

			/**
			 * @brief Returns the binding point for the texture.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t
			binding () const noexcept
			{
				return m_binding;
			}

			/**
			 * @brief Returns the name of the sampler uniform.
			 * @return const char *
			 */
			[[nodiscard]]
			const char *
			samplerName () const noexcept
			{
				return m_samplerName;
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const Texture & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend std::string to_string (const Texture & obj) noexcept;

		private:

			/* JSON key. */
			static constexpr auto JKResourceName{"Name"};
			static constexpr auto JKChannel{"Channel"};
			static constexpr auto JKUVWScale{"UVW"};
			static constexpr auto JKEnableAlpha{"EnableAlpha"};

			const char * m_samplerName;
			std::string m_variableName;
			std::shared_ptr< TextureResource::Abstract > m_texture{};
			Libs::Math::Vector< 3, float > m_UVWScale{1.0F, 1.0F, 1.0F};
			uint32_t m_UVWChannel{0};
			uint32_t m_binding{0};
			bool m_alphaEnabled{false};
	};
}
