/*
 * Emeraude/Graphics/RenderableInstance/VertexBufferFormatManager.hpp
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
#include <vector>
#include <array>
#include <mutex>

/* Local inclusions for inheritances. */
#include "ServiceInterface.hpp"

/* Local inclusions for usages. */
#include "VertexBufferFormat.hpp"

/* Forward declarations. */
namespace Emeraude::Graphics
{
	namespace Geometry
	{
		class Interface;
	}

	namespace Material
	{
		class Interface;
	}
}

namespace Emeraude::Graphics::RenderableInstance
{
	/**
	 * @brief The vertex buffer format manager service class.
	 * @extends Emeraude::ServiceInterface This is a service.
	 */
	class VertexBufferFormatManager final : public ServiceInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VertexBufferFormatManagerService"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs the vertex buffer format manager.
			 */
			VertexBufferFormatManager () noexcept;

			/**
			 * @brief Destructs the vertex buffer format manager.
			 */
			~VertexBufferFormatManager ();

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::ServiceInterface::usable() */
			[[nodiscard]]
			bool usable () const noexcept override;

			/**
			 * @brief Enables the print into the console of generated format. (DEBUG).
			 * @param state
			 * @return void
			 */
			void enablePrintGeneratedFormat (bool state) noexcept;

			/**
			 * @brief Returns a vertex buffer format from a vertex shader.
			 * @param geometry A reference to a geometry interface.
			 * @param vertexShader A reference to a vertex shader.
			 * @return std::shared_ptr< VertexBufferFormat >
			 */
			[[nodiscard]]
			std::shared_ptr< VertexBufferFormat > getVertexBufferFormat (const Geometry::Interface & geometry, const Saphir::VertexShader & vertexShader) noexcept;

			/**
			 * @brief Returns the instance of the vertex buffer format manager.
			 * @return Renderer *
			 */
			[[nodiscard]]
			static VertexBufferFormatManager * instance () noexcept;

			/**
			 * @brief Returns a string showing a VBO usage.
			 * @param geometry A reference to the geometry using the VBO.
			 * @param vertexBufferFormat A reference to the vertex buffer format using the VBO.
			 * @return std::string
			 */
			[[nodiscard]]
			static std::string getVertexBufferObjectUsage (const Geometry::Interface & geometry, VertexBufferFormat & vertexBufferFormat) noexcept;

		private:

			/** @copydoc Emeraude::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc Emeraude::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

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
			void resetBuildingParameters () noexcept;

			/* Flag names */
			static constexpr auto Usable = 0UL;
			static constexpr auto PrintGeneratedFormat = 1UL;

			static VertexBufferFormatManager * s_instance; // NOLINT NOTE: Singleton behavior

			std::vector< std::shared_ptr< VertexBufferFormat > > m_vertexBufferFormats{};
			/* Building parameters */
			std::mutex m_building{};
			std::shared_ptr< VertexBufferFormat > m_vertexBufferFormat{};
			uint32_t m_currentBinding{0};
			uint32_t m_bindingOffset{0};
			size_t m_bindingElementCount{0};
			std::array< bool, 8 > m_flags{
				false/*Usable*/,
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
