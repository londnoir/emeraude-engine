/*
 * Emeraude/Vulkan/GraphicsShaderContainer.hpp
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
#include <string>

/* Local inclusions for usages. */
#include "Saphir/VertexShader.hpp"
#include "Saphir/TesselationControlShader.hpp"
#include "Saphir/TesselationEvaluationShader.hpp"
#include "Saphir/GeometryShader.hpp"
#include "Saphir/FragmentShader.hpp"

namespace Emeraude::Vulkan
{
	/**
	 * @brief The graphics shader container class.
	 */
	class GraphicsShaderContainer final
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"GraphicsShaderContainer"};

			/** 
			 * @brief Constructs a graphics shader container.
			 */
			GraphicsShaderContainer () noexcept = default;

			/**
			 * @brief Initializes the vertex shader and returns it.
			 * @param name A reference to a string.
			 * @return std::shared_ptr< Saphir::VertexShader >
			 */
			[[nodiscard]]
			std::shared_ptr< Saphir::VertexShader > initVertexShader (const std::string & name) noexcept;

			/**
			 * @brief Initializes the tesselation control shader and returns it.
			 * @param name A reference to a string.
			 * @return std::shared_ptr< Saphir::TesselationControlShader >
			 */
			[[nodiscard]]
			std::shared_ptr< Saphir::TesselationControlShader > initTesselationControlShader (const std::string & name) noexcept;

			/**
			 * @brief Initializes the tesselation evaluation shader and returns it.
			 * @param name A reference to a string.
			 * @return std::shared_ptr< Saphir::TesselationEvaluationShader >
			 */
			[[nodiscard]]
			std::shared_ptr< Saphir::TesselationEvaluationShader > initTesselationEvaluationShader (const std::string & name) noexcept;

			/**
			 * @brief Initializes the geometry shader and returns it.
			 * @param name A reference to a string.
			 * @return std::shared_ptr< Saphir::GeometryShader >
			 */
			[[nodiscard]]
			std::shared_ptr< Saphir::GeometryShader > initGeometryShader (const std::string & name) noexcept;

			/**
			 * @brief Initializes the fragment shader.
			 * @param name A reference to a string.
			 * @return std::shared_ptr< Saphir::FragmentShader >
			 */
			[[nodiscard]]
			std::shared_ptr< Saphir::FragmentShader > initFragmentShader (const std::string & name) noexcept;

			/**
			 * @brief Returns the vertex shader.
			 * @return std::shared_ptr< Saphir::VertexShader >
			 */
			[[nodiscard]]
			std::shared_ptr< Saphir::VertexShader > vertexShader () const noexcept;

			/**
			 * @brief Returns the tesselation control shader.
			 * @return std::shared_ptr< Saphir::TesselationControlShader >
			 */
			[[nodiscard]]
			std::shared_ptr< Saphir::TesselationControlShader > tesselationControlShader () const noexcept;

			/**
			 * @brief Returns the tesselation evaluation shader.
			 * @return std::shared_ptr< Saphir::TesselationEvaluationShader >
			 */
			[[nodiscard]]
			std::shared_ptr< Saphir::TesselationEvaluationShader > tesselationEvaluationShader () const noexcept;

			/**
			 * @brief Returns the geometry shader.
			 * @return std::shared_ptr< Saphir::GeometryShader >
			 */
			[[nodiscard]]
			std::shared_ptr< Saphir::GeometryShader > geometryShader () const noexcept;

			/**
			 * @brief Returns the fragment shader.
			 * @return std::shared_ptr< Saphir::FragmentShader >
			 */
			[[nodiscard]]
			std::shared_ptr< Saphir::FragmentShader > fragmentShader () const noexcept;

			/**
			 * @brief Returns the list of shaders.
			 * @return std::vector< std::shared_ptr< Saphir::AbstractShader > >
			 */
			[[nodiscard]]
			std::vector< std::shared_ptr< Saphir::AbstractShader > > getShaderList () const noexcept;

		private:

			std::shared_ptr< Saphir::VertexShader > m_vertexShader{};
			std::shared_ptr< Saphir::TesselationControlShader > m_tesselationControlShader{};
			std::shared_ptr< Saphir::TesselationEvaluationShader > m_tesselationEvaluationShader{};
			std::shared_ptr< Saphir::GeometryShader > m_geometryShader{};
			std::shared_ptr< Saphir::FragmentShader > m_fragmentShader{};
	};
}
