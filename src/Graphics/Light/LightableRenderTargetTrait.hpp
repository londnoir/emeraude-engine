/*
 * Emeraude/Graphics/Light/LightableRenderTargetTrait.hpp
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

/* Local inclusions for usages. */
#include "Scenes/LightSet.hpp"
#include "Processor.hpp"

namespace Emeraude::Graphics::Light
{
	/**
	 * @brief The lightable trait for render target.
	 */
	class LightableRenderTargetTrait
	{
		public:

			/**&
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			LightableRenderTargetTrait (const LightableRenderTargetTrait & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			LightableRenderTargetTrait (LightableRenderTargetTrait && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return LightableRenderTargetTrait &
			 */
			LightableRenderTargetTrait & operator= (const LightableRenderTargetTrait & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return LightableRenderTargetTrait &
			 */
			LightableRenderTargetTrait & operator= (LightableRenderTargetTrait && copy) noexcept = delete;
			
			/** 
			 * @brief Destructs the lightable render target trait.
			 */
			virtual ~LightableRenderTargetTrait () = default;
			
			/**
			 * @brief Sets the scene light set to the view.
			 * @param lightSet A reference to smart pointer of the scene light set.
			 * @return void
			 */
			virtual void setLightSet (const std::shared_ptr< Scenes::LightSet > & lightSet) noexcept final;

			/**
			 * @brief Returns the const access to the light processor of the view.
			 * @return const Processor *
			 */
			[[nodiscard]]
			virtual const Processor & lightProcessor () const noexcept final;

			/**
			 * @brief Returns the access to the light processor of the view.
			 * @return Processor *
			 */
			[[nodiscard]]
			virtual Processor & lightProcessor () noexcept final;

		protected:

			/** 
			 * @brief Constructs a lightable render target trait.
			 */
			LightableRenderTargetTrait () noexcept = default;
			
		private:

			Processor m_lightProcessor{};
	};
}
