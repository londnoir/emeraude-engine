/*
 * Emeraude/Saphir/Declaration/Types.hpp
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
#include <cstddef>

/* Local inclusions for usages. */
#include "Saphir/Keys.hpp"

namespace Emeraude::Saphir::Declaration
{
	/**
	 * @brief The GLSL variable type enumerations.
	 * @note The enumeration is used to compute size in bytes for declarations.
	 */
	enum class VariableType
	{
		Void,
		Float,
		Double,
		UnsignedInteger,
		Integer,
		AtomicUnsignedInteger,
		Boolean,
		FloatVector2,
		FloatVector3,
		FloatVector4,
		DoubleVector2,
		DoubleVector3,
		DoubleVector4,
		UIntVector2,
		UIntVector3,
		UIntVector4,
		SIntVector2,
		SIntVector3,
		SIntVector4,
		BooleanVector2,
		BooleanVector3,
		BooleanVector4,
		Matrix2,
		Matrix3,
		Matrix4,
		Matrix2x2,
		Matrix2x3,
		Matrix2x4,
		Matrix3x3,
		Matrix3x2,
		Matrix3x4,
		Matrix4x2,
		Matrix4x3,
		Matrix4x4,
		DoubleMatrix2,
		DoubleMatrix3,
		DoubleMatrix4,
		DoubleMatrix2x2,
		DoubleMatrix2x3,
		DoubleMatrix2x4,
		DoubleMatrix3x3,
		DoubleMatrix3x2,
		DoubleMatrix3x4,
		DoubleMatrix4x2,
		DoubleMatrix4x3,
		DoubleMatrix4x4,
		Sampler1D,
		Sampler1DArray,
		Sampler2D,
		Sampler2DArray,
		Sampler2DMS,
		Sampler2DMSArray,
		Sampler3D,
		SamplerCube,
		SamplerCubeArray,
		SamplerBuffer,
		UIntSamplerBuffer,
		UIntSamplerCubeArray,
		UIntSamplerCube,
		UIntSampler3D,
		UIntSampler2DMSArray,
		UIntSampler2DMS,
		UIntSampler2DRectangle,
		UIntSampler2D,
		UIntSampler2DArray,
		UIntSampler1D,
		UIntSampler1DArray,
		SIntSamplerBuffer,
		SIntSamplerCubeArray,
		SIntSamplerCube,
		SIntSampler3D,
		SIntSampler2DMSArray,
		SIntSampler2DMS,
		SIntSampler2DRectangle,
		SIntSampler2D,
		SIntSampler2DArray,
		SIntSampler1D,
		SIntSampler1DArray,
		Sampler1DShadow,
		Sampler1DArrayShadow,
		Sampler2DShadow,
		Sampler2DArrayShadow,
		Sampler2DRectangle,
		Sampler2DRectangleShadow,
		SamplerCubeShadow,
		SamplerCubeArrayShadow,
		Image1D,
		Image1DArray,
		Image2D,
		Image2DArray,
		Image2DRectangle,
		Image2DMS,
		Image2DMSArray,
		Image3D,
		ImageCube,
		ImageCubeArray,
		ImageBuffer,
		UIntImage1D,
		UIntImage1DArray,
		UIntImage2D,
		UIntImage2DArray,
		UIntImage2DRectangle,
		UIntImage2DMS,
		UIntImage2DMSArray,
		UIntImage3D,
		UIntImageCube,
		UIntImageCubeArray,
		UIntImageBuffer,
		SIntImage1D,
		SIntImage1DArray,
		SIntImage2D,
		SIntImage2DArray,
		SIntImage2DRectangle,
		SIntImage2DMS,
		SIntImage2DMSArray,
		SIntImage3D,
		SIntImageCube,
		SIntImageCubeArray,
		SIntImageBuffer,
		Texture1D,
		Texture2D,
		Texture3D,
		TextureCube,
		Texture2DRectangle,
		Texture1DArray,
		Texture2DArray,
		TextureCubeArray,
		TextureBuffer,
		Texture2DMS,
		Texture2DMSArray,
		UIntTexture1D,
		UIntTexture2D,
		UIntTexture3D,
		UIntTextureCube,
		UIntTexture2DRectangle,
		UIntTexture1DArray,
		UIntTexture2DArray,
		UIntTextureCubeArray,
		UIntTextureBuffer,
		UIntTexture2DMS,
		UIntTexture2DMSArray,
		SIntTexture1D,
		SIntTexture2D,
		SIntTexture3D,
		SIntTextureCube,
		SIntTexture2DRectangle,
		SIntTexture1DArray,
		SIntTexture2DArray,
		SIntTextureCubeArray,
		SIntTextureBuffer,
		SIntTexture2DMS,
		SIntTexture2DMSArray,
		Sampler,
		SamplerShadow,
		SubpassInput,
		SubpassInputMS,
		UIntSubpassInput,
		UIntSubpassInputMS,
		SIntSubpassInput,
		SIntSubpassInputMS,
		Structure
	};

	/**
	 * @brief Converts a variable type to GLSL type string.
	 * @param type The variable type.
	 * @return Key
	 */
	[[nodiscard]]
	Key to_cstring (VariableType type) noexcept;

	/**
	 * @brief Returns the size in bytes from a GLSL type.
	 * @param type The variable type.
	 * @return size_t
	 */
	[[nodiscard]]
	size_t size_bytes (VariableType type) noexcept;

	/**
	 * @brief The GLSL memory layout enumeration.
	 */
	enum class MemoryLayout
	{
		Shared,
		Packed,
		Std140,
		Std430
	};

	/**
	 * @brief The GLSL matrix storage order enumeration.
	 */
	enum class MatrixStorageOrder
	{
		Default, /* This won't add any code. */
		ColumnMajor, /* This is the real GLSL default. */
		RowMajor
	};
}
