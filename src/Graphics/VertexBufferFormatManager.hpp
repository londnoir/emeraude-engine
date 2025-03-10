/*
 * src/Graphics/VertexBufferFormatManager.hpp
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
#include <cstddef>
#include <cstdint>
#include <array>
#include <memory>
#include <mutex>
#include <vector>

/* Local inclusions for usages. */
#include "VertexBufferFormat.hpp"

/* Forward declarations. */
namespace Emeraude
{
	namespace Graphics::Geometry
	{
		class Interface;
	}

	namespace Saphir
	{
		class VertexShader;
	}
}

namespace Emeraude::Graphics
{
	/**
	 * @brief The vertex buffer format manager service class.
	 * @extends Emeraude::ServiceInterface This is a service.
	 */
	class VertexBufferFormatManager final
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VertexBufferFormatManagerService"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs a vertex buffer format manager.
			 */
			VertexBufferFormatManager () noexcept = default;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			VertexBufferFormatManager (const VertexBufferFormatManager & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			VertexBufferFormatManager (VertexBufferFormatManager && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return VertexBufferFormatManager &
			 */
			VertexBufferFormatManager & operator= (const VertexBufferFormatManager & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return VertexBufferFormatManager &
			 */
			VertexBufferFormatManager & operator= (VertexBufferFormatManager && copy) noexcept = delete;

			/**
			 * @brief Destructs the vertex buffer format manager.
			 */
			~VertexBufferFormatManager () noexcept;

			/**
			 * @brief Enables the print into the console of generated format. (DEBUG).
			 * @param state
			 * @return void
			 */
			void
			enablePrintGeneratedFormat (bool state) noexcept
			{
				m_flags[PrintGeneratedFormat] = state;
			}

			/**
			 * @brief Returns a vertex buffer format from a vertex shader.
			 * @param geometry A reference to a geometry interface.
			 * @param vertexShader A reference to a vertex shader.
			 * @return std::shared_ptr< VertexBufferFormat >
			 */
			[[nodiscard]]
			std::shared_ptr< VertexBufferFormat > getVertexBufferFormat (const Geometry::Interface & geometry, const Saphir::VertexShader & vertexShader) noexcept;

			/**
			 * @brief Returns a string showing a VBO usage.
			 * @param geometry A reference to the geometry using the VBO.
			 * @param vertexBufferFormat A reference to the vertex buffer format using the VBO.
			 * @return std::string
			 */
			[[nodiscard]]
			static std::string getVertexBufferObjectUsage (const Geometry::Interface & geometry, VertexBufferFormat & vertexBufferFormat) noexcept;

		private:

			/**
			 * @brief Begins a binding declaration.
			 * @param binding The binding point.
			 * @return bool
			 */
			bool beginBinding (uint32_t binding) noexcept;

			/**
			 * @brief Declares a vertex attribute.
			 * @param attribute The vertex attribute type.
			 * @return bool
			 */
			bool declareAttribute (VertexAttributeType attribute) noexcept;

			/**
			 * @brief Declares a jump over an existing vertex attribute.
			 * @param attribute The vertex attribute type.
			 * @return void
			 */
			void declareJump (VertexAttributeType attribute) noexcept;

			/**
			 * @brief Ends the declaration of a binding.
			 * @param topology The geometry primitive to use.
			 * @param bufferFlags The vertex buffer object flags.
			 * @return bool
			 */
			bool endBinding (Graphics::Topology topology, uint32_t bufferFlags) noexcept;

			/**
			 * @brief resetBuildingParameters
			 * @return void
			 */
			void
			resetBuildingParameters () noexcept
			{
				m_vertexBufferFormat.reset();
				m_currentBinding = 0;
				m_bindingOffset = 0;
				m_bindingElementCount = 0;
			}

			/* Flag names */
			static constexpr auto Usable{0UL};
			static constexpr auto PrintGeneratedFormat{1UL};

			std::vector< std::shared_ptr< VertexBufferFormat > > m_vertexBufferFormats;
			/* Building parameters */
			std::mutex m_building;
			std::shared_ptr< VertexBufferFormat > m_vertexBufferFormat;
			uint32_t m_currentBinding{0};
			uint32_t m_bindingOffset{0};
			size_t m_bindingElementCount{0};
			std::array< bool, 8 > m_flags{
				false/*ServiceInitialized*/,
				false/*PrintGeneratedFormat*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
