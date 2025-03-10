/*
 * src/Libraries/VertexFactory/FileFormatNative.hpp
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

/* Local inclusions for inheritances. */
#include "FileFormatInterface.hpp"

namespace Libraries::VertexFactory
{
	/**
	 * @brief Emeraude engine native geometry format.
	 * @tparam data_t The data precision type.
	 * @extends Libraries::VertexFactory::FileFormatInterface
	 */
	template< typename data_t >
	requires (std::is_floating_point_v< data_t >)
	class FileFormatNative final : public FileFormatInterface< data_t >
	{
		public:

			/**
			 * @brief Constructs a native file format.
			 */
			FileFormatNative () noexcept = default;

			/** @copydoc Libraries::VertexFactory::FileFormatInterface::readFile() */
			[[nodiscard]]
			bool
			readFile (const std::filesystem::path & filepath, Shape< data_t > & geometry, const ReadOptions & /*readOptions*/) noexcept override
			{
				geometry.clear();

				std::cerr << __PRETTY_FUNCTION__ << ", not yet implemented ! Cancelling the read of " << filepath << " file !" "\n";

				return false;
			}

			/** @copydoc Libraries::VertexFactory::FileFormatInterface::writeFile() */
			[[nodiscard]]
			bool
			writeFile (const std::filesystem::path & filepath, const Shape< data_t > & geometry) const noexcept override
			{
				if ( !geometry.isValid() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", geometry parameter is invalid !" "\n";

					return false;
				}

				std::cerr << __PRETTY_FUNCTION__ << ", not yet implemented ! File " << filepath << " is not created." "\n";

				return false;
			}
	};
}
