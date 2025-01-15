/*
 * src/Libraries/VertexFactory/FileFormatMD3.hpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2024 - "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emeraude-Engine; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Complete project and additional information can be found at :
 * https://bitbucket.org/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#pragma once

/* Local inclusions for inheritances. */
#include "FileFormatInterface.hpp"

namespace Libraries::VertexFactory
{
	/**
	 * @brief 3D format from Quake 3 engine.
	 * @tparam data_t The data precision type.
	 * @extends Libraries::VertexFactory::FileFormatInterface
	 */
	template< typename data_t >
	requires (std::is_floating_point_v< data_t >)
	class FileFormatMD3 final : public FileFormatInterface< data_t >
	{
		public:

			/**
			 * @brief Constructs a MD3 file format.
			 */
			FileFormatMD3 () noexcept = default;

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
