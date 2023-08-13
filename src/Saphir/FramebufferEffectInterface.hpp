/*
 * Emeraude/Saphir/FramebufferEffectInterface.hpp
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
#include <set>

/* Local inclusions */
/* VULKAN_DEV */
//#include "Program.hpp"

/* Forward declarations. */
namespace Emeraude::Graphics
{
	class PostProcessor;
}

namespace Emeraude::Saphir
{
	/* Forward declarations. */
	class ShaderGenerator;

	/**
	 * @brief The framebuffer effect interface.
	 */
	class FramebufferEffectInterface
	{
		friend class Emeraude::Graphics::PostProcessor;

		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			FramebufferEffectInterface (const FramebufferEffectInterface & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			FramebufferEffectInterface (FramebufferEffectInterface && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return FramebufferEffectInterface &
			 */
			FramebufferEffectInterface & operator= (const FramebufferEffectInterface & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return FramebufferEffectInterface &
			 */
			FramebufferEffectInterface & operator= (FramebufferEffectInterface && copy) noexcept = default;
			
			/** 
			 * @brief Destructs the framebuffer effect interface.
			 */
			virtual ~FramebufferEffectInterface () = default;

			/**
			 * @brief Activate will bind or send data to the program for this effect.
			 * @warning Old OpenGL behavior
			 * @param program A reference to the Program.
			 * @param nextTextureUnit A reference to a texture unit counter.
			 * @return bool
			 */
			//virtual void activate (const Program & program, unsigned int & nextTextureUnit) const noexcept;

		protected:

			/** 
			 * @brief Constructs a framebuffer effect interface.
			 */
			FramebufferEffectInterface () noexcept = default;
			
			/**
			 * @brief Says if this effect is overriding the way fragment are fetched from the color buffer.
			 * @note Override this method to return true for the final effect.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool overrideFragmentFetching () const noexcept;

			/**
			 * @brief Says this shader needs screen coordinates. Geometry texture coordinates attribute will be available.
			 * @note Override this method to return true for the final effect.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool requestScreenCoordinates () const noexcept;

			/**
			 * @brief Says this shader needs screen sizes. em_FrameSize will be available.
			 * @note Override this method to return true for the final effect.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool requestScreenSize () const noexcept;

			/**
			 * @brief Generates shader effect code.
			 * @param generator A reference to the ShaderGenerator.
			 * @param samples Hint on the output interfaces samples usage.
			 * @return bool
			 */
			virtual bool generate (ShaderGenerator & generator, int samples) const noexcept = 0;
	};

	using FramebufferEffectsList = std::set< std::shared_ptr< FramebufferEffectInterface > >;
}
