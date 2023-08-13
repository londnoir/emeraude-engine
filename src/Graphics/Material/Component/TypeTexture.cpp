/*
 * Emeraude/Graphics/Material/Component/TypeTexture.cpp
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

#include "TypeTexture.hpp"

/* Local inclusions. */
#include "Tracer.hpp"
#include "Resources/Manager.hpp"
#include "Graphics/TextureResource/AnimatedTexture2D.hpp"
#include "Graphics/TextureResource/TextureCubemap.hpp"
#include "Graphics/TextureResource/Texture1D.hpp"
#include "Graphics/TextureResource/Texture2D.hpp"
#include "Graphics/TextureResource/Texture3D.hpp"

namespace Emeraude::Graphics::Material::Component
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Saphir;

	TypeTexture::TypeTexture (const std::string & variableName, const std::shared_ptr< TextureResource::Abstract > & texture, uint32_t UVWChannel, const Vector< 3, float > & UVWScale, bool enableAlpha) noexcept
		: m_variableName(variableName), m_texture(texture), m_UVWChannel(UVWChannel), m_UVWScale(UVWScale), m_alphaEnabled(enableAlpha)
	{

	}

	TypeTexture::TypeTexture (const std::string & variableName, const Json::Value & data, const FillingType & fillingType) noexcept
		: m_variableName(variableName)
	{
		if ( !data.isMember(JKResourceName) )
		{
			TraceError{ClassId} << "There is no '" << JKResourceName << "' key in Json structure !";

			return;
		}

		if ( !data[JKResourceName].isString() )
		{
			TraceError{ClassId} << "The key '" << JKResourceName << "' key in Json structure must be a string !";

			return;
		}

		const auto textureResourceName = data[JKResourceName].asString();

		/* Check the texture type. */
		switch ( fillingType )
		{
			case FillingType::Gradient :
				m_texture = Resources::Manager::instance()->texture1Ds().getResource(textureResourceName);
				break;

			case FillingType::Texture :
				m_texture = Resources::Manager::instance()->texture2Ds().getResource(textureResourceName);
				break;

			case FillingType::VolumeTexture :
				m_texture = Resources::Manager::instance()->texture3Ds().getResource(textureResourceName);
				break;

			case FillingType::Cubemap :
				m_texture = Resources::Manager::instance()->textureCubemaps().getResource(textureResourceName);
				break;

			case FillingType::AnimatedTexture :
				m_texture = Resources::Manager::instance()->animatedTextures().getResource(textureResourceName);
				break;

			case FillingType::Value :
			case FillingType::Color :
			case FillingType::AlphaChannelAsValue :
			case FillingType::None :
				Tracer::error(ClassId, "Invalid texture type !");

				return;
		}

		if ( m_texture == nullptr )
		{
			TraceError{ClassId} << "Unable to find " << to_cstring(fillingType) << " '" << textureResourceName << "' !";

			return;
		}

		/* Check the optionnal UVW channel. */
		if ( data.isMember(JKChannel) )
		{
			const auto & jsonNode = data[JKChannel];

			if ( jsonNode.isNumeric() )
			{
				m_UVWChannel = jsonNode.asUInt();
			}
			else
			{
				TraceWarning{ClassId} <<
					"The '" << JKChannel << "' key in Json structure is not numeric ! "
					"Leaving UVW channel to 0 ...";
			}
		}

		/* Check the optionnal UVW scale. */
		if ( data.isMember(JKUVWScale) )
		{
			const auto & jsonNode = data[JKUVWScale];

			if ( jsonNode.isArray() )
			{
				for ( auto index = 0; index < 3; index++ )
				{
					if ( !jsonNode[index].isNumeric() )
					{
						TraceError{ClassId} << "Json array #" << index << " value is not numeric !";

						break;
					}

					m_UVWScale[index] = jsonNode[index].asFloat();
				}
			}
			else
			{
				TraceError{ClassId} << "The '" << JKUVWScale << "' key must be a numeric value array ! ";
			}
		}

		if ( data.isMember(JKEnableAlpha) )
		{
			const auto & jsonNode = data[JKEnableAlpha];

			if ( jsonNode.isBool() )
				m_alphaEnabled = jsonNode.asBool();
			else
				TraceError{ClassId} << "The '" << JKEnableAlpha << "' key in Json structure is not a boolean !";
		}
	}

	bool
	TypeTexture::create () noexcept
	{
		if ( m_texture == nullptr )
			return false;

		if ( m_texture->isCreated() )
			return true;

		return m_texture->createOnHardware();
	}

	bool
	TypeTexture::isCreated () const noexcept
	{
		if ( m_texture == nullptr )
			return false;

		return m_texture->isCreated();
	}

	const std::string &
	TypeTexture::variableName () const noexcept
	{
		return m_variableName;
	}

	Type
	TypeTexture::type () const noexcept
	{
		return Type::Texture;
	}

	bool
	TypeTexture::isOpaque () const noexcept
	{
		return m_alphaEnabled ? false : true;
	}

	void
	TypeTexture::setTexture (const std::shared_ptr< TextureResource::Abstract > & texture) noexcept
	{
		m_texture = texture;
	}

	const std::shared_ptr< TextureResource::Abstract > &
	TypeTexture::texture () const noexcept
	{
		return m_texture;
	}

	void
	TypeTexture::setUVWChannel (uint32_t UVWChannel) noexcept
	{
		m_UVWChannel = UVWChannel;
	}

	uint32_t
	TypeTexture::UVWChannel () const noexcept
	{
		return m_UVWChannel;
	}

	void
	TypeTexture::setUVWScale (const Vector< 3, float > & UVWScale) noexcept
	{
		m_UVWScale = UVWScale;
	}

	const Vector< 3, float > &
	TypeTexture::UVWScale () const noexcept
	{
		return m_UVWScale;
	}

	bool
	TypeTexture::isVolumetricTexture () const noexcept
	{
		return m_texture->dimensions() >= 3;
	}

	Key
	TypeTexture::textureType () const noexcept
	{
		using namespace Saphir::Keys;

		if ( std::dynamic_pointer_cast< TextureResource::Texture2D >(m_texture) != nullptr )
			return GLSL::Sampler2D;

		if ( std::dynamic_pointer_cast< TextureResource::TextureCubemap >(m_texture) != nullptr )
			return GLSL::SamplerCube;

		if ( std::dynamic_pointer_cast< TextureResource::AnimatedTexture2D >(m_texture) != nullptr )
			return GLSL::Sampler2DArray;

		if ( std::dynamic_pointer_cast< TextureResource::Texture1D >(m_texture) != nullptr )
			return GLSL::Sampler1D;

		if ( std::dynamic_pointer_cast< TextureResource::Texture3D >(m_texture) != nullptr )
			return GLSL::Sampler3D;

		Tracer::error("TypeTexture", "Unable to determine texture type !");

		return nullptr;
	}

	void
	TypeTexture::enableAlpha (bool state) noexcept
	{
		m_alphaEnabled = state;
	}

	bool
	TypeTexture::alphaEnabled () const noexcept
	{
		return m_alphaEnabled;
	}

	std::ostream &
	operator<< (std::ostream & out, const TypeTexture & obj)
	{
		return out << obj.ClassId << "." "\n"
			"Variable name: " << obj.m_variableName << "\n"
			"Texture type (component level): " << obj.textureType() << "\n"
			"Is volumetric texture ? (component level): " << ( obj.isVolumetricTexture() ? "yes" : "no" ) << "\n"
			"Texture resource name: " << obj.m_texture->name() << "\n"
			"UVW scale: " << obj.m_UVWScale << "\n"
			"Alpha channel enabled: " << ( obj.m_alphaEnabled ? "yes" : "no" ) << "\n";
	}

	std::string
	to_string (const TypeTexture & obj) noexcept
	{
		return (std::stringstream{} << obj).str();
	}
}
