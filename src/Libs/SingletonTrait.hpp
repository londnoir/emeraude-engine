/*
 * src/Libs/SingletonTrait.hpp
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
#include <iostream>

namespace EmEn::Libs
{
	/**
	 * @brief Class for the singleton design pattern.
	 * @tparam singleton_t The the derived type of singleton class.
	 */
	template < typename singleton_t >
	class SingletonTrait
	{
		public:

			/**
			 * @brief Deleted copy constructor.
			 * @param other A reference to a singleton.
			 */
			SingletonTrait (const SingletonTrait & other) = delete;

			/**
			 * @brief Deleted move constructor.
			 * @param other A reference to a singleton.
			 */
			SingletonTrait (SingletonTrait && other) noexcept = delete;

			/**
			 * @brief Deleted assignment operator.
			 * @param other A reference to a singleton.
			 * @return SingletonTrait &
			 */
			SingletonTrait & operator= (const SingletonTrait & other) = delete;

			/**
			 * @brief Deleted move assignment operator.
			 * @param other A reference to a singleton.
			 * @return SingletonTrait &
			 */
			SingletonTrait & operator= (SingletonTrait && other) noexcept = delete;

			/**
			 * @brief Destructs the singleton.
			 */
			virtual ~SingletonTrait () = default;

			/**
			 * @brief Returns the instance.
			 * @return singleton_t *
			 */
			static
			singleton_t *
			instance () noexcept
			{
				if ( s_instance == nullptr )
				{
					if ( s_doNotRecreate )
					{
						std::cerr << __PRETTY_FUNCTION__ << ", FATAL ERROR: This Singleton cannot be reallocated !" "\n";
					}
					else
					{
						s_instance = new singleton_t();
					}
				}

				return s_instance;
			}

			/**
			 * @brief Destroys the instance.
			 * @param strict Disable the ability to recreate the singleton after deletion. Default true.
			 * @return void
			 */
			static
			void
			destroy (bool strict = true) noexcept
			{
				s_doNotRecreate = strict;

				if ( s_instance != nullptr )
				{
					delete s_instance;
					s_instance = nullptr;
				}
			}

		protected:

			/**
			 * @brief Constructs the singleton.
			 */
			SingletonTrait () noexcept = default;

		private:

			/* NOTE: These statics must be declared in .cpp file of children class.
			 * Example : template<> MyObject * Libs::Singleton< MyObject >::s_instance = nullptr;  */
			static singleton_t * s_instance;
			static bool s_doNotRecreate;
	};
}
