/*
 * Emeraude/Overlay/Surface.cpp
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

#include "Surface.hpp"

/* Local inclusions */
#include "Manager.hpp"
#include "Graphics/Geometry/IndexedVertexResource.hpp"
#include "Graphics/ImageResource.hpp"
#include "Vulkan/Image.hpp"

namespace Emeraude::Overlay
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Graphics;

	Surface::Surface (float textureWidthProportion, float textureHeightProportion) noexcept
		: m_textureProportion(textureWidthProportion, textureHeightProportion)
	{

	}

	void
	Surface::setGeometry (float width, float height) noexcept
	{
		if ( width <= 0.0F || height <= 0.0F )
		{
			Tracer::warning(ClassId, "Invalid size !");

			return;
		}

		m_rectangle.setWidth(width);
		m_rectangle.setHeight(height);

		this->resize(Manager::screenWidth(), Manager::screenHeight());
	}

	void
	Surface::setGeometry (unsigned int width, unsigned int height) noexcept
	{
		this->setGeometry(Manager::screenWidth() / static_cast< float >(width), Manager::screenHeight() / static_cast< float >(height));
	}

	void
	Surface::setPosition (float x, float y) noexcept
	{
		m_rectangle.setOffsetX(x);
		m_rectangle.setOffsetY(y);
	}

	void
	Surface::setPosition (int x, int y) noexcept
	{
		this->setPosition(Manager::screenWidth() / static_cast< float >(x), Manager::screenHeight() / static_cast< float >(y));
	}

	void
	Surface::setPosition (Position position) noexcept
	{
		switch ( position )
		{
			case Position::Center :
				this->setPosition(0.0F, 0.0F);
				break;

			case Position::Bottom :
				this->setPosition(0.0F, -1.0F + m_rectangle.height());
				break;

			case Position::Top :
				this->setPosition(0.0F,  1.0F - m_rectangle.height());
				break;

			case Position::Left :
				this->setPosition(-1.0F + m_rectangle.width(), 0.0F);
				break;

			case Position::Right :
				this->setPosition(1.0F - m_rectangle.width(), 0.0F);
				break;

			case Position::BottomLeft :
				this->setPosition(-1.0F + m_rectangle.width(), -1.0F + m_rectangle.height());
				break;

			case Position::BottomRight :
				this->setPosition(1.0F - m_rectangle.width(), -1.0F + m_rectangle.height());
				break;

			case Position::TopLeft :
				this->setPosition(-1.0F + m_rectangle.width(), 1.0F - m_rectangle.height());
				break;

			case Position::TopRight :
				this->setPosition(1.0F - m_rectangle.width(), 1.0F - m_rectangle.height());
				break;
		}
	}

	Layouts::Main &
	Surface::rootLayout () noexcept
	{
		return m_rootLayout;
	}

	const Layouts::Main &
	Surface::rootLayout () const noexcept
	{
		return m_rootLayout;
	}

	const PixelFactory::Pixmap< uint8_t > &
	Surface::pixmap () const noexcept
	{
		return m_data;
	}

	PixelFactory::Pixmap< uint8_t > &
	Surface::pixmap () noexcept
	{
		return m_data;
	}

	void
	Surface::drawFinished () noexcept
	{
		/*if ( !this->onDrawFinished(m_data) )
			return;

		m_texture->requestUpdate(true);*/
	}

	bool
	Surface::updateVideoMemory () noexcept
	{
		/*if ( m_texture->isRequestingUpdate() )
		{
			if ( !m_texture->updateData(m_data) )
				return false;

			m_data.resetUpdatedRegion();
		}*/

		return true;
	}

	void
	Surface::render (Renderer &, const Program &) const noexcept
	{
		/*m_geometry->bind();

		program.sendUniform(Manager::SurfaceOffset, Vector< 3, float >(m_rectangle.offsetX(), m_rectangle.offsetY(), 1.0F));
		program.sendUniform(Manager::TextureOffset, m_textureOffset);

		program.bind(Samplers::PrimaryTexture, *m_texture, 0);

		m_geometry->draw();*/
	}

	float
	Surface::realWidth () const noexcept
	{
		return Manager::screenWidth() * m_rectangle.width();
	}

	float
	Surface::realHeight () const noexcept
	{
		return Manager::screenHeight() * m_rectangle.height();
	}

	float
	Surface::xOffset () const noexcept
	{
		return Manager::screenWidth() * (m_rectangle.offsetX() - m_rectangle.width() + 1.0F) * 0.5F;
	}

	float
	Surface::yOffset () const noexcept
	{
		return Manager::screenHeight() * (m_rectangle.offsetY() - m_rectangle.height() + 1.0F) * 0.5F;
	}

	const Vector< 2, float > &
	Surface::textureOffset () const noexcept
	{
		return m_textureOffset;
	}

	bool
	Surface::isBelow (float x, float y) const noexcept
	{
		/* Checks in X axis. */
		auto xA = this->xOffset();
		auto xB = xA + this->realWidth();

		if ( x < xA || x > xB )
			return false;

		/* Checks in Y axis. */
		auto yA = this->yOffset();
		auto yB = yA + this->realHeight();

		return !( y < yA || y > yB );
	}

	void
	Surface::onKeyPress (int key, int scanCode, int modifiers, bool repeat) noexcept
	{
		std::cout << "Key " << key << " (scanCode:" << scanCode << ") with mods " << modifiers << " pressed !" << std::endl;
	}

	void
	Surface::onKeyRelease (int key, int scanCode, int modifiers) noexcept
	{
		std::cout << "Key " << key << " (scanCode:" << scanCode << ") with mods " << modifiers << " released !" << std::endl;
	}

	void
	Surface::onCharacterType (unsigned int unicode, int modifiers) noexcept
	{
		std::cout << "Character " << unicode << " with mods " << modifiers << " typed !" << std::endl;
	}

	void
	Surface::onPointerEnter (float x, float y) noexcept
	{
		std::cout << "Entering surface at [" << x << ", " << y << "]." << std::endl;
	}

	void
	Surface::onPointerLeave (float x, float y) noexcept
	{
		std::cout << "Leaving surface at [" << x << ", " << y << "]." << std::endl;
	}

	void
	Surface::onPointerMove (float /*x*/, float /*y*/) noexcept
	{
		//std::cout << "Moving on surface at [" << x << ", " << y << "]." << std::endl;
	}

	void
	Surface::onButtonPress (float x, float y, int buttonNumber, int) noexcept
	{
		std::cout << "Mouse button " << buttonNumber << " pressed on surface at [" << x << ", " << y << "]." << std::endl;
	}

	void
	Surface::onButtonRelease (float x, float y, int buttonNumber, int) noexcept
	{
		std::cout << "Mouse button " << buttonNumber << " released on surface at [" << x << ", " << y << "]." << std::endl;
	}

	void
	Surface::onMouseWheel (float x, float y, float xOffset, float yOffset) noexcept
	{
		std::cout << "Mouse wheel offset  [" << xOffset << ", " << yOffset << "] on surface at [" << x << ", " << y << "]." << std::endl;
	}

	void
	Surface::setTextureOffsetX (float x) noexcept
	{
		m_textureOffset[X] = x;
	}

	void
	Surface::setTextureOffsetY (float y) noexcept
	{
		m_textureOffset[Y] = y;
	}

	void
	Surface::setTextureOffset (const Vector< 2, float > & offset) noexcept
	{
		m_textureOffset = offset;
	}

	bool
	Surface::onResize (const PixelFactory::Pixmap< uint8_t > &) noexcept
	{
		return true;
	}

	bool
	Surface::onDrawFinished (PixelFactory::Pixmap< uint8_t > &) noexcept
	{
		return true;
	}

	bool
	Surface::updateGeometry () noexcept
	{
		/*if ( m_geometry == nullptr )
		{
			m_geometry = IndexedVertexResource::generateSurface(m_rectangle.width(), m_rectangle.height(), true, m_textureProportion[X], m_textureProportion[Y], true);

			if ( m_geometry == nullptr )
			{
				Tracer::error(ClassId, "Unable to create the geometry of the surface in video memory !");

				return false;
			}
		}
		else
		{
			std::array< float, 4 * (3 + 2) > positions{
				/ * Bottom-left * /
				-m_rectangle.width(), -m_rectangle.height(), 0.0F, 0.0F, 0.0F,
				/ * Bottom-right * /
				 m_rectangle.width(), -m_rectangle.height(), 0.0F, m_textureProportion[X], 0.0F,
				/ * Top-right * /
				-m_rectangle.width(),  m_rectangle.height(), 0.0F, 0.0F, m_textureProportion[Y],
				/ * Top-left * /
				 m_rectangle.width(),  m_rectangle.height(), 0.0F, m_textureProportion[X], m_textureProportion[Y]
			};

			if  ( !m_geometry->update(positions.data(), positions.size()) )
			{
				Tracer::error(ClassId, "Unable to update the geometry of the surface in video memory !");

				return false;
			}
		}*/

		return true;
	}

	bool
	Surface::updateTexture (float windowWidth, float windowHeight) noexcept
	{
		/*const auto width = static_cast< size_t >(windowWidth * m_rectangle.width() * (1.0F / m_textureProportion[X]));
		const auto height = static_cast< size_t >(windowHeight * m_rectangle.height() * (1.0F / m_textureProportion[Y]));

		if ( !m_data.initialize(width, height, PixelFactory::Pixmap::RGBA) )
		{
			Tracer::error(ClassId, "Unable to allocate Pixmap for surface texture !");

			return false;
		}

		if ( m_texture != nullptr )
		{
			m_texture->destroy();
			m_texture.reset();
		}

		m_texture = std::make_shared< TextureRectangle >();

		if ( !m_texture->initialize(m_data) )
		{
			Tracer::error(ClassId, "Unable to create the texture of the surface in video memory !");

			return false;
		}*/

		return true;
	}

	bool
	Surface::resize (float windowWidth, float windowHeight) noexcept
	{
		if ( !this->updateGeometry() )
		{
			Tracer::error(ClassId, "Unable to create/update surface geometry !");

			return false;
		}

		if ( !this->updateTexture(windowWidth, windowHeight) )
		{
			Tracer::error(ClassId, "Unable to create/update surface texture !");

			return false;
		}

		return this->onResize(m_data);
	}
}
