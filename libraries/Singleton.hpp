/*
 * Libraries/Singleton.hpp
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
#include <iostream>

namespace Libraries
{
	/**
	 * @brief Class for the singleton design pattern.
	 * @tparam singleton_t The the derived type of singleton class.
	 */
	template < typename singleton_t >
	class Singleton
	{
		public:

			/**
			 * @brief Deleted copy constructor.
			 * @param other A reference to a singleton.
			 */
			Singleton (const Singleton & other) = delete;

			/**
			 * @brief Deleted move constructor.
			 * @param other A reference to a singleton.
			 */
			Singleton (Singleton && other) noexcept = delete;

			/**
			 * @brief Deleted assignment operator.
			 * @param other A reference to a singleton.
			 * @return Singleton &
			 */
			Singleton & operator= (const Singleton & other) = delete;

			/**
			 * @brief Deleted move assignment operator.
			 * @param other A reference to a singleton.
			 * @return Singleton &
			 */
			Singleton & operator= (Singleton && other) noexcept = delete;

			/**
			 * @brief Destructs a singleton.
			 */
			virtual ~Singleton () = default;

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
			 * @brief Constructs a singleton.
			 */
			Singleton () noexcept = default;

		private:

			/* NOTE: These statics must be declared in .cpp file of children class.
			 * Example : template<> MyObject * Libraries::Singleton< MyObject >::s_instance = nullptr;  */
			static singleton_t * s_instance; // NOLINT NOTE: Singleton behavior
			static bool s_doNotRecreate;
	};
}
