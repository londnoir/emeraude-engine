/*
 * Emeraude/Overlay/Elements/Button.hpp
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
#include <functional>

/* Local inclusions for inheritances. */
#include "../Surface.hpp"
#include "Interface.hpp"
#include "Graphics/TextWriter.hpp"

namespace Emeraude::Overlay::Elements
{
	/**
	 * @brief The button form element.
	 * @extends Emeraude::Overlay::Surface This a visible element.
	 * @extends Emeraude::Overlay::Elements::UIInputInterface The is an user input element.
	 */
	class Button final : public Surface, public UIInputInterface
	{
		public:

			using Function = std::function< int (void) >;

			/** @brief Class identifier. */
			static constexpr auto ClassId{"UIButton"};

			/** @brief Default constructor. */
			Button () noexcept;

			/** @copydoc */
			void onPointerEnter (float x, float y) noexcept override;

			/** @copydoc  */
			void onPointerLeave (float x, float y) noexcept override;

			/** @copydoc  */
			void onButtonPress (float x, float y, int buttonNumber, int mods) noexcept override;

			/** @copydoc  */
			void onButtonRelease (float x, float y, int buttonNumber, int mods) noexcept override;

			/**
			 * @brief Gives acces to the TextWriter for configuration.
			 * @warning  Don't use it to write on the surface.
			 */
			Graphics::TextWriter & textWriter () noexcept;

			/**
			 * @brief Sets the label of the button.
			 * @note The label value.
			 */
			void setLabel (const std::string & label) noexcept;

			/**
			 * @brief Returns the label of the button.
			 * @return const std::string &
			 */
			[[nodiscard]]
			const std::string & label () const noexcept;

			/**
			 * @brief setImage
			 * @param image
			 */
			void setImage (const std::shared_ptr< Graphics::ImageResource > & image) noexcept;

			/**
			 * @brief image
			 * @return std::shared_ptr< Graphics::ImageResource >
			 */
			[[nodiscard]]
			const std::shared_ptr< Graphics::ImageResource > & image () const noexcept;

			/**
			 * @brief Sets a function to execute when the button is clicked.
			 * @param function
			 */
			void attachFunction (const Function & function) noexcept;

		private:

			/**
			 * @brief onDrawFinished
			 * @param pixmap
			 * @return bool
			 */
			bool onDrawFinished (Libraries::PixelFactory::Pixmap< uint8_t > & pixmap) noexcept final;

			std::shared_ptr< Graphics::ImageResource > m_image{};
			std::string m_label{};
			Graphics::TextWriter m_textWriter{};
			Function m_function{};
			Status m_status = Status::Normal;
	};
}
