/*
 * Emeraude/Graphics/RenderableInstance/VertexBufferFormatManager.cpp
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

#include "VertexBufferFormatManager.hpp"

/* Local inclusions. */
#include "Graphics/Geometry/Interface.hpp"
#include "Tracer.hpp"

namespace Emeraude::Graphics::RenderableInstance
{
	const size_t VertexBufferFormatManager::ClassUID{Observable::getClassUID()};
	VertexBufferFormatManager * VertexBufferFormatManager::s_instance{nullptr}; // NOLINT NOTE: Singleton behavior

	VertexBufferFormatManager::VertexBufferFormatManager () noexcept
		: ServiceInterface(ClassId)
	{
		if ( s_instance != nullptr )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", constructor called twice !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

			std::terminate();
		}

		s_instance = this;
	}

	VertexBufferFormatManager::~VertexBufferFormatManager ()
	{
		s_instance = nullptr;
	}

	VertexBufferFormatManager *
	VertexBufferFormatManager::instance () noexcept
	{
		return s_instance;
	}

	bool
	VertexBufferFormatManager::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	VertexBufferFormatManager::usable () const noexcept
	{
		return m_flags[Usable];
	}

	void
	VertexBufferFormatManager::enablePrintGeneratedFormat (bool state) noexcept
	{
		m_flags[PrintGeneratedFormat] = state;
	}

	bool
	VertexBufferFormatManager::beginBinding (uint32_t binding) noexcept
	{
		if ( m_vertexBufferFormat == nullptr )
		{
			Tracer::error(ClassId, "No vertex buffer format is currently built !");

			return false;
		}

		/* NOTE: Check the binding index. */
		if ( m_vertexBufferFormat->binding(binding) != nullptr )
		{
			TraceError{ClassId} << "Binding index " << binding << " already declared !";

			return false;
		}

		m_currentBinding = binding;
		m_bindingOffset = 0;
		m_bindingElementCount = 0;

		return true;
	}

	bool
	VertexBufferFormatManager::declareAttribute (VertexAttributeType attribute) noexcept
	{
		if ( m_vertexBufferFormat == nullptr )
			return false;

		const std::array< VkFormat, 5 > formats{
			VK_FORMAT_UNDEFINED,
			VK_FORMAT_R32_SFLOAT,
			VK_FORMAT_R32G32_SFLOAT,
			VK_FORMAT_R32G32B32_SFLOAT,
			VK_FORMAT_R32G32B32A32_SFLOAT
		};

		const auto attributeSize = Graphics::attributeSize(attribute);

		if ( attributeSize == 0 )
		{
			TraceError{ClassId} << "Unhandled vertex attribute type '" << to_string(attribute) << "' !";

			return false;
		}

		m_vertexBufferFormat->setInputAttribute(
			static_cast< uint32_t >(attribute),
			m_currentBinding,
			formats[attributeSize],
			m_bindingOffset
		);

		/* Advancing with offset and elements count. */
		m_bindingOffset += attributeSize * sizeof(float);
		m_bindingElementCount += attributeSize;

		return true;
	}

	void
	VertexBufferFormatManager::declareJump (VertexAttributeType attribute) noexcept
	{
		const auto attributeSize = Graphics::attributeSize(attribute);

		if ( attributeSize )
			m_bindingOffset += attributeSize * sizeof(float);
		else
			TraceError{ClassId} << "Unhandled vertex attribute type '" << to_string(attribute) << "' !";
	}

	bool
	VertexBufferFormatManager::endBinding (Graphics::Topology topology, uint32_t bufferFlags) noexcept
	{
		if ( m_vertexBufferFormat == nullptr )
			return false;

		/* NOTE: Save the whole binding in an index. */
		m_vertexBufferFormat->setBinding(
			m_currentBinding,
			m_bindingOffset,
			bufferFlags & PerInstance ? VK_VERTEX_INPUT_RATE_INSTANCE : VK_VERTEX_INPUT_RATE_VERTEX
		);

		/* NOTE: Creates the binding format. */
		m_vertexBufferFormat->saveBindingData(
			m_currentBinding,
			m_bindingElementCount,
			topology,
			bufferFlags
		);

		return true;
	}

	void
	VertexBufferFormatManager::resetBuildingParameters () noexcept
	{
		m_vertexBufferFormat.reset();
		m_currentBinding = 0;
		m_bindingOffset = 0;
		m_bindingElementCount = 0;
	}

	std::shared_ptr< VertexBufferFormat >
	VertexBufferFormatManager::getVertexBufferFormat (const Geometry::Interface & geometry, const Saphir::VertexShader & vertexShader) noexcept
	{
		const std::lock_guard lock{m_building};
		
		m_vertexBufferFormat = std::make_shared< VertexBufferFormat >();
		
		{
			const auto & requestedVertexAttributes = vertexShader.vertexAttributes();

			/* VBO format for vertices. */
			{
				this->beginBinding(0);

				if ( requestedVertexAttributes.contains(VertexAttributeType::Position) )
					this->declareAttribute(VertexAttributeType::Position);
				else
					this->declareJump(VertexAttributeType::Position);

				/* Check the uses of the full tangent space or normals. */
				if (
					requestedVertexAttributes.contains(VertexAttributeType::Tangent) &&
					requestedVertexAttributes.contains(VertexAttributeType::Binormal) &&
					requestedVertexAttributes.contains(VertexAttributeType::Normal)
				)
				{
					if ( !geometry.tangentSpaceEnabled() )
					{
						TraceError{ClassId} <<
							"The vertex shader '" << vertexShader.name() << "' needs tangent space, "
							"but the geometry '" << geometry.name() << "' do not provide it.";

						return nullptr;
					}

					this->declareAttribute(VertexAttributeType::Tangent);
					this->declareAttribute(VertexAttributeType::Binormal);
					this->declareAttribute(VertexAttributeType::Normal);
				}
				else if ( requestedVertexAttributes.contains(VertexAttributeType::Normal) )
				{
					if ( !geometry.normalEnabled() )
					{
						TraceError{ClassId} <<
							"The vertex shader '" << vertexShader.name() << "' needs normal attributes, "
							"but the geometry '" << geometry.name() << "' do not provide these.";

						return nullptr;
					}

					/* Check for attribute presence to jump over. */
					if ( geometry.tangentSpaceEnabled() )
					{
						this->declareJump(VertexAttributeType::Tangent);
						this->declareJump(VertexAttributeType::Binormal);
					}

					this->declareAttribute(VertexAttributeType::Normal);
				}
				else
				{
					/* Check for attribute presence to jump over. */
					if ( geometry.tangentSpaceEnabled() )
					{
						this->declareJump(VertexAttributeType::Tangent);
						this->declareJump(VertexAttributeType::Binormal);
						this->declareJump(VertexAttributeType::Normal);
					}
					else if ( geometry.normalEnabled() )
					{
						this->declareJump(VertexAttributeType::Normal);
					}
				}

				/* Check for primary texture coordinates conformance. */
				if (
					requestedVertexAttributes.contains(VertexAttributeType::Primary2DTextureCoordinates) ||
					requestedVertexAttributes.contains(VertexAttributeType::Primary3DTextureCoordinates)
				)
				{
					if ( requestedVertexAttributes.contains(VertexAttributeType::Primary2DTextureCoordinates) )
					{
						if ( !geometry.primaryTextureCoordinatesEnabled() )
						{
							TraceError{ClassId} <<
								"The vertex shader '" << vertexShader.name() << "' needs 2D primary texture coordinates attributes, "
								"but the geometry '" << geometry.name() << "' do not provide these.";

							return nullptr;
						}

						this->declareAttribute(VertexAttributeType::Primary2DTextureCoordinates);
					}
					else
					{
						if ( !geometry.primaryTextureCoordinates3DEnabled() )
						{
							TraceError{ClassId} <<
								"The vertex shader '" << vertexShader.name() << "' needs 3D primary texture coordinates attributes version, "
								"but the geometry '" << geometry.name() << "' do not provide these.";

							return nullptr;
						}

						this->declareAttribute(VertexAttributeType::Primary3DTextureCoordinates);
					}
				}
				else if ( geometry.primaryTextureCoordinatesEnabled() )
				{
					if ( geometry.primaryTextureCoordinates3DEnabled() )
						this->declareJump(VertexAttributeType::Primary3DTextureCoordinates);
					else
						this->declareJump(VertexAttributeType::Primary2DTextureCoordinates);
				}

				/* Check for secondary texture coordinates conformance. */
				if (
					requestedVertexAttributes.contains(VertexAttributeType::Secondary2DTextureCoordinates) ||
					requestedVertexAttributes.contains(VertexAttributeType::Secondary3DTextureCoordinates)
				)
				{
					if ( requestedVertexAttributes.contains(VertexAttributeType::Secondary2DTextureCoordinates) )
					{
						if ( !geometry.secondaryTextureCoordinatesEnabled() )
						{
							TraceError{ClassId} <<
								"The vertex shader '" << vertexShader.name() << "' needs 2D secondary texture coordinates attributes, "
								"but the geometry '" << geometry.name() << "' do not provide these.";

							return nullptr;
						}

						this->declareAttribute(VertexAttributeType::Secondary2DTextureCoordinates);
					}
					else
					{
						if ( !geometry.secondaryTextureCoordinates3DEnabled() )
						{
							TraceError{ClassId} <<
								"The vertex shader '" << vertexShader.name() << "' needs 3D secondary texture coordinates attributes version, "
								"but the geometry '" << geometry.name() << "' do not provide these.";

							return nullptr;
						}

						this->declareAttribute(VertexAttributeType::Secondary3DTextureCoordinates);
					}
				}
				else if ( geometry.secondaryTextureCoordinatesEnabled() )
				{
					if ( geometry.secondaryTextureCoordinates3DEnabled() )
						this->declareJump(VertexAttributeType::Secondary3DTextureCoordinates);
					else
						this->declareJump(VertexAttributeType::Secondary2DTextureCoordinates);
				}

				/* Checking the vertex color */
				if ( requestedVertexAttributes.contains(VertexAttributeType::VertexColor) )
				{
					if ( !geometry.vertexColorEnabled() )
					{
						TraceError{ClassId} <<
							"The vertex shader '" << vertexShader.name() << "' needs vertex color attributes, "
							"but the geometry '" << geometry.name() << "' do not provide these.";

						return nullptr;
					}

					this->declareAttribute(VertexAttributeType::VertexColor);
				}
				else
				{
					/* Check for attribute presence to jump over. */
					if ( geometry.vertexColorEnabled() )
						this->declareJump(VertexAttributeType::VertexColor);
				}

				uint32_t bufferFlags{0};

				if ( geometry.useDynamicVertexBuffer() )
					bufferFlags |= IsDynamicVertexBuffer;

				if ( geometry.useAbsolutePosition() )
					bufferFlags |= IsPositionAbsolute;

				if ( geometry.usePrimitiveRestart() )
					bufferFlags |= RequestPrimitiveRestart;

				this->endBinding(geometry.topology(), bufferFlags);
			}

			/* VBO format for model matrices. */
			if ( vertexShader.instancingEnabled() )
			{
				this->beginBinding(1);

				/* NOTE: Matrix 4x4 declaration. */
				if ( requestedVertexAttributes.contains(VertexAttributeType::ModelMatrixR0) )
				{
					this->declareAttribute(VertexAttributeType::ModelMatrixR0);
					this->declareAttribute(VertexAttributeType::ModelMatrixR1);
					this->declareAttribute(VertexAttributeType::ModelMatrixR2);
					this->declareAttribute(VertexAttributeType::ModelMatrixR3);
				}
				else
				{
					this->declareJump(VertexAttributeType::ModelMatrixR0);
					this->declareJump(VertexAttributeType::ModelMatrixR1);
					this->declareJump(VertexAttributeType::ModelMatrixR2);
					this->declareJump(VertexAttributeType::ModelMatrixR3);
				}

				/* Check the uses of the full tangent space or normals. */
				if ( requestedVertexAttributes.contains(VertexAttributeType::NormalModelMatrixR0) )
				{
					/* NOTE: Matrix 3x3 declaration. */
					this->declareAttribute(VertexAttributeType::NormalModelMatrixR0);
					this->declareAttribute(VertexAttributeType::NormalModelMatrixR1);
					this->declareAttribute(VertexAttributeType::NormalModelMatrixR2);
				}
				else
				{
					/* Check for attribute presence to jump over. */
					this->declareJump(VertexAttributeType::NormalModelMatrixR0);
					this->declareJump(VertexAttributeType::NormalModelMatrixR1);
					this->declareJump(VertexAttributeType::NormalModelMatrixR2);
				}

				this->endBinding(Graphics::Topology::CustomData, PerInstance | IsDynamicVertexBuffer);
			}
		}

		const auto vertexBufferFormat = m_vertexBufferFormats.emplace_back(m_vertexBufferFormat);

		this->resetBuildingParameters();

		if ( m_flags[PrintGeneratedFormat] )
		{
			TraceInfo{ClassId} << "Geometry flags : " "\n" <<
				Geometry::getFlagsString(geometry.flagBits()) << "\n" <<
				*vertexBufferFormat <<
				VertexBufferFormatManager::getVertexBufferObjectUsage(geometry, *vertexBufferFormat);
		}

		return vertexBufferFormat;
	}

	std::string
	VertexBufferFormatManager::getVertexBufferObjectUsage (const Geometry::Interface & geometry, VertexBufferFormat & vertexBufferFormat) noexcept
	{
		std::stringstream ss{};

		size_t elementCount = 3;

		ss << "VBO #0 enabled vertex attribute layout :" "\n\n" <<
			( vertexBufferFormat.isPresent(VertexAttributeType::Position) ? "[3:position]" : "{3:position}" );

		if ( geometry.tangentSpaceEnabled() )
		{
			elementCount += 9;

			ss << ( vertexBufferFormat.isPresent(VertexAttributeType::Tangent) ? "[3:tangent]" : "{3:tangent}" );
			ss << ( vertexBufferFormat.isPresent(VertexAttributeType::Binormal) ? "[3:binormal]" : "{3:binormal}" );
			ss << ( vertexBufferFormat.isPresent(VertexAttributeType::Normal) ? "[3:normal]" : "{3:normal}" );
		}
		else if ( geometry.normalEnabled() )
		{
			elementCount += 3;

			ss << ( vertexBufferFormat.isPresent(VertexAttributeType::Normal) ? "[3:normal]" : "{3:normal}" );
		}

		if ( geometry.primaryTextureCoordinatesEnabled() )
		{
			if ( geometry.primaryTextureCoordinates3DEnabled() )
			{
				elementCount += 3;

				ss << ( vertexBufferFormat.isPresent(VertexAttributeType::Primary3DTextureCoordinates) ? "[3:priTexCoord]" : "{3:priTexCoord}" );
			}
			else
			{
				elementCount += 2;

				ss << ( vertexBufferFormat.isPresent(VertexAttributeType::Primary2DTextureCoordinates) ? "[2:priTexCoord]" : "{2:priTexCoord}" );
			}
		}

		if ( geometry.secondaryTextureCoordinatesEnabled() )
		{
			if ( geometry.secondaryTextureCoordinates3DEnabled() )
			{
				elementCount += 3;

				ss << ( vertexBufferFormat.isPresent(VertexAttributeType::Secondary3DTextureCoordinates) ? "[3:secTexCoord]" : "{3:secTexCoord}" );
			}
			else
			{
				elementCount += 2;

				ss << ( vertexBufferFormat.isPresent(VertexAttributeType::Secondary2DTextureCoordinates) ? "[2:secTexCoord]" : "{2:secTexCoord}" );
			}
		}

		if ( geometry.vertexColorEnabled() )
		{
			elementCount += 4;

			ss << ( vertexBufferFormat.isPresent(VertexAttributeType::VertexColor) ? "[4:color]" : "{4:color}" );
		}

		ss << "\n";

		const auto VBOElementCount = geometry.vertexBufferObject()->vertexElementCount();

		if ( VBOElementCount != elementCount )
			TraceError{ClassId} << "Element count per vertex mismatch between VBO (" << VBOElementCount << ") and the declaration from geometry flags (" << elementCount << ") !";

		return ss.str();
	}

	bool
	VertexBufferFormatManager::onInitialize () noexcept
	{
		m_flags[Usable] = true;

		return true;
	}

	bool
	VertexBufferFormatManager::onTerminate () noexcept
	{
		const std::lock_guard lock{m_building};

		m_vertexBufferFormats.clear();

		return true;
	}
}
