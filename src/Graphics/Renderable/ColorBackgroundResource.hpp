/*
 * Emeraude/Graphics/Renderable/ColorBackgroundResource.hpp
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

/* C/C++ standard libraries */
#include <cstddef>
#include <string>

/* Local inclusions for inheritances. */
#include "AbstractBackground.hpp"

/* Local inclusions for usages. */
#include "PixelFactory/Color.hpp"

namespace Emeraude::Graphics::Renderable
{
	/**
	 * @brief The ColorBackground class.
	 * @extends Emeraude::Graphics::AbstractBackground The is a specialized background.
	 */
	class ColorBackgroundResource final : public AbstractBackground
	{
		friend class Resources::Container< ColorBackgroundResource >;

		using ResourceTrait::load;

		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"ColorBackgroundResource"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs a color background.
			 * @param name A reference to a string for the resource name.
			 * @param color A reference to a color.
			 * @param resourceFlagBits The resource flag bits. Default none.
			 */
			explicit ColorBackgroundResource (const std::string & name, const Libraries::PixelFactory::Color< float > & color, uint32_t resourceFlagBits = 0) noexcept;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Libraries::Resources::ResourceTrait::classLabel() */
			[[nodiscard]]
			const char * classLabel () const noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load() */
			bool load () noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load(const Json::Value &) */
			bool load (const Json::Value & data) noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::layerCount() */
			[[nodiscard]]
			size_t layerCount () const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::isOpaque() */
			[[nodiscard]]
			bool isOpaque (size_t layerIndex = 0UL) const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::geometry() */
			[[nodiscard]]
			const Geometry::Interface * geometry () const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::material() */
			[[nodiscard]]
			const Material::Interface * material (size_t layerIndex = 0UL) const noexcept override;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::prepareShaders() */
			[[nodiscard]]
			bool prepareShaders (const Geometry::Interface & geometry, const Material::Interface & material, RenderPassType renderPassType, bool enableInstancing, Vulkan::GraphicsShaderContainer & shaders) const noexcept override;

	private:

			static std::string s_label;
	};
}

/* Expose the resource manager as a convenient type. */
namespace Emeraude::Resources
{
	using ColorBackgrounds = Container< Graphics::Renderable::ColorBackgroundResource >;
}
