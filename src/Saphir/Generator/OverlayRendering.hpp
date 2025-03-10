/*
 * src/Saphir/Generator/OverlayRendering.hpp
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
#include <vector>
#include <memory>

/* Local inclusions for inheritances. */
#include "Abstract.hpp"

/* Local inclusions for usages. */
#include "Graphics/Geometry/IndexedVertexResource.hpp"
#include "Overlay/Manager.hpp"

namespace Emeraude::Saphir::Generator
{
	/**
	 * @brief This generator builds the graphics pipeline for the overlay rendering.
	 * @extends Emeraude::Saphir::Generator::Abstract This a generator.
	 */
	class OverlayRendering final : public Abstract
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"OverlayRendering"};

			/**
			 * @brief Constructs a graphics shader generator for a geometry.
			 * @param overlayManager A reference to the overlay manager.
			 * @param renderTarget A reference to a render target.
			 */
			OverlayRendering (Overlay::Manager & overlayManager, const std::shared_ptr< const Graphics::RenderTarget::Abstract > & renderTarget) noexcept;

			/** @copydoc Emeraude::Saphir::Generator::Abstract::materialEnabled() const */
			[[nodiscard]]
			bool
			materialEnabled () const noexcept override
			{
				return false;
			}

			/** @copydoc Emeraude::Saphir::Generator::Abstract::material() const */
			[[nodiscard]]
			const Graphics::Material::Interface *
			material () const noexcept override
			{
				return nullptr;
			}

			/** @copydoc Emeraude::Saphir::Generator::Abstract::geometry() const */
			[[nodiscard]]
			const Graphics::Geometry::Interface *
			geometry () const noexcept override
			{
				return m_overlayManager.surfaceGeometry().get();
			}

		private:

			/** @copydoc Emeraude::Saphir::Generator::Abstract::prepareUniformSets() */
			void
			prepareUniformSets (SetIndexes & setIndexes) noexcept override
			{
				setIndexes.enableSet(SetType::PerModel);
			}

			/** @copydoc Emeraude::Saphir::Generator::Abstract::onGenerateProgram() */
			[[nodiscard]]
			bool onGenerateProgram (Program & program) noexcept override;

			/** @copydoc Emeraude::Saphir::Generator::Abstract::onGenerateProgramLayout() */
			[[nodiscard]]
			bool onGenerateProgramLayout (const SetIndexes & setIndexes, std::vector< std::shared_ptr< Vulkan::DescriptorSetLayout > > & descriptorSetLayouts, std::vector< VkPushConstantRange > & pushConstantRanges) noexcept override;

			/** @copydoc Emeraude::Saphir::Generator::Abstract::onGraphicsPipelineConfiguration() */
			[[nodiscard]]
			bool onGraphicsPipelineConfiguration (const Program & program, Vulkan::GraphicsPipeline & graphicsPipeline) noexcept override;

			/**
			 * @brief Generates the vertex shader stage of the graphics pipeline.
			 * @param program A reference to the program being constructed.
			 * @return bool
			 */
			[[nodiscard]]
			bool generateVertexShader (Program & program) noexcept;

			/**
			 * @brief Generates the fragment shader stage of the graphics pipeline.
			 * @param program A reference to the program being constructed.
			 * @return bool
			 */
			[[nodiscard]]
			bool generateFragmentShader (Program & program) noexcept;

			Overlay::Manager & m_overlayManager;
	};
}
