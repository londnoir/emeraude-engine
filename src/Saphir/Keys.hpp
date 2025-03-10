/*
 * src/Saphir/Keys.hpp
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
#include <string>

namespace Emeraude::Saphir
{
	using Key = const char *;

	/** @brief Shaders common grammar. */
	namespace Keys
	{
		/** @brief GLSL standard variables naming. */
		namespace GLSL
		{
			namespace Define
			{
				static constexpr auto Version = "#version";
				static constexpr auto Extension = "#extension";
				static constexpr auto Line = "#line";
			}

			namespace Profile
			{
				static constexpr auto Core = "core";
				static constexpr auto Compatibility = "compatibility";
				static constexpr auto EmbeddedSystem = "es";
			}

			namespace Extension
			{
				static constexpr auto All = "all";
				static constexpr auto Enable = "enable";
				static constexpr auto Require = "require";
				static constexpr auto Warn = "warn";
				static constexpr auto Disable = "disable";
			}

			namespace Macro
			{
				static constexpr auto File = "__FILE__";
				static constexpr auto Line = "__LINE__";
				static constexpr auto Version = "__VERSION__";
				static constexpr auto GLCoreProfile = "GL_core_profile";
				static constexpr auto GLCompatibilityProfile = "GL_compatibility_profile";
			}

			namespace Primitive
			{
				static constexpr auto Points = "points";
				static constexpr auto Lines = "lines";
				static constexpr auto LineAdjacency = "lines_adjacency";
				static constexpr auto LineStrip = "line_strip";
				static constexpr auto Triangles = "triangles";
				static constexpr auto TrianglesAdjacency = "triangles_adjacency";
				static constexpr auto TriangleStrip = "triangle_strip";
			}

			/* Flow controls */
			static constexpr auto Break = "break";
			static constexpr auto Continue = "continue";
			static constexpr auto Do = "do";
			static constexpr auto For = "for";
			static constexpr auto While = "while";
			static constexpr auto Switch = "switch";
			static constexpr auto Case = "case";
			static constexpr auto Default = "default";
			static constexpr auto If = "if";
			static constexpr auto Else = "else";
			static constexpr auto Discard = "discard";
			static constexpr auto Return = "return";

			/* Qualifiers */
			static constexpr auto Const = "const";
			static constexpr auto Uniform = "uniform";
			static constexpr auto In = "in";
			static constexpr auto Out = "out";
			static constexpr auto InOut = "inout";
			static constexpr auto Buffer = "buffer";
			static constexpr auto Shared = "shared";
			static constexpr auto Packed = "packed";
			static constexpr auto Std140 = "std140";
			static constexpr auto Std430 = "std430";
			static constexpr auto Attribute = "attribute";
			static constexpr auto Varying = "varying";
			static constexpr auto Coherent = "coherent";
			static constexpr auto Volatile = "volatile";
			static constexpr auto Restrict = "restrict";
			static constexpr auto ReadOnly = "readonly";
			static constexpr auto WriteOnly = "writeonly";
			static constexpr auto Layout = "layout";
			static constexpr auto Centroid = "centroid";
			static constexpr auto Flat = "flat";
			static constexpr auto Smooth = "smooth";
			static constexpr auto NoPerspective = "noperspective";
			static constexpr auto Patch = "patch";
			static constexpr auto Sample = "sample";
			static constexpr auto Invariant = "invariant";
			static constexpr auto Precise = "precise";
			static constexpr auto Subroutine = "subroutine";
			static constexpr auto Struct = "struct";

			/* Layout parameters */
			static constexpr auto Set = "set";
			static constexpr auto Binding = "binding";
			static constexpr auto Location = "location";
			static constexpr auto ColumnMajor = "column_major";
			static constexpr auto RowMajor = "row_major";
			static constexpr auto Align = "align";
			static constexpr auto Offset = "offset";
			static constexpr auto MaxVertices = "max_vertices";
			static constexpr auto PushConstant = "push_constant";
			static constexpr auto ConstantId = "constant_id";

			/* Precisions */
			static constexpr auto Precision = "precision";
			static constexpr auto Low = "lowp";
			static constexpr auto Medium = "mediump";
			static constexpr auto High = "highp";

			/* Literal types */
			static constexpr auto Void = "void";
			static constexpr auto Float = "float";
			static constexpr auto Double = "double";
			static constexpr auto UnsignedInteger = "uint";
			static constexpr auto Integer = "int";
			static constexpr auto AtomicUnsignedInteger = "atomic_uint";
			static constexpr auto Boolean = "bool";
			static constexpr auto True = "true";
			static constexpr auto False = "false";

			/* Const literal types */
			static constexpr auto ConstFloat = "const float";
			static constexpr auto ConstDouble = "const double";
			static constexpr auto ConstUnsignedInteger = "const uint";
			static constexpr auto ConstInteger = "const int";

			/* Vector (Float) types */
			static constexpr auto FloatVector2 = "vec2";
			static constexpr auto FloatVector3 = "vec3";
			static constexpr auto FloatVector4 = "vec4";
			/* Vector (Double) types */
			static constexpr auto DoubleVector2 = "dvec2";
			static constexpr auto DoubleVector3 = "dvec3";
			static constexpr auto DoubleVector4 = "dvec4";
			/* Vector (Unsigned integer) types */
			static constexpr auto UIntVector2 = "uvec2";
			static constexpr auto UIntVector3 = "uvec3";
			static constexpr auto UIntVector4 = "uvec4";
			/* Vector (Signed integer) types */
			static constexpr auto SIntVector2 = "ivec2";
			static constexpr auto SIntVector3 = "ivec3";
			static constexpr auto SIntVector4 = "ivec4";
			/* Vector (Boolean) types */
			static constexpr auto BooleanVector2 = "bvec2";
			static constexpr auto BooleanVector3 = "bvec3";
			static constexpr auto BooleanVector4 = "bvec4";

			/* Const vector (Float) types */
			static constexpr auto ConstFloatVector2 = "const vec2";
			static constexpr auto ConstFloatVector3 = "const vec3";
			static constexpr auto ConstFloatVector4 = "const vec4";
			/* Const vector (Double) types */
			static constexpr auto ConstDoubleVector2 = "const dvec2";
			static constexpr auto ConstDoubleVector3 = "const dvec3";
			static constexpr auto ConstDoubleVector4 = "const dvec4";
			/* Const vector (Unsigned integer) types */
			static constexpr auto ConstUIntVector2 = "const uvec2";
			static constexpr auto ConstUIntVector3 = "const uvec3";
			static constexpr auto ConstUIntVector4 = "const uvec4";
			/* Const vector (Signed integer) types */
			static constexpr auto ConstSIntVector2 = "const ivec2";
			static constexpr auto ConstSIntVector3 = "const ivec3";
			static constexpr auto ConstSIntVector4 = "const ivec4";
			/* Const vector (Boolean) types */
			static constexpr auto ConstBooleanVector2 = "const bvec2";
			static constexpr auto ConstBooleanVector3 = "const bvec3";
			static constexpr auto ConstBooleanVector4 = "const bvec4";

			/* Matrix (Float) types */
			static constexpr auto Matrix2 = "mat2";
			static constexpr auto Matrix3 = "mat3";
			static constexpr auto Matrix4 = "mat4";
			static constexpr auto Matrix2x2 = "mat2x2";
			static constexpr auto Matrix2x3 = "mat2x3";
			static constexpr auto Matrix2x4 = "mat2x4";
			static constexpr auto Matrix3x3 = "mat3x3";
			static constexpr auto Matrix3x2 = "mat3x2";
			static constexpr auto Matrix3x4 = "mat3x4";
			static constexpr auto Matrix4x2 = "mat4x2";
			static constexpr auto Matrix4x3 = "mat4x3";
			static constexpr auto Matrix4x4 = "mat4x4";
			/* Matrix (Double) types */
			static constexpr auto DoubleMatrix2 = "dmat2";
			static constexpr auto DoubleMatrix3 = "dmat3";
			static constexpr auto DoubleMatrix4 = "dmat4";
			static constexpr auto DoubleMatrix2x2 = "dmat2x2";
			static constexpr auto DoubleMatrix2x3 = "dmat2x3";
			static constexpr auto DoubleMatrix2x4 = "dmat2x4";
			static constexpr auto DoubleMatrix3x3 = "dmat3x3";
			static constexpr auto DoubleMatrix3x2 = "dmat3x2";
			static constexpr auto DoubleMatrix3x4 = "dmat3x4";
			static constexpr auto DoubleMatrix4x2 = "dmat4x2";
			static constexpr auto DoubleMatrix4x3 = "dmat4x3";
			static constexpr auto DoubleMatrix4x4 = "dmat4x4";

			/* Const matrix (Float) types */
			static constexpr auto ConstMatrix2 = "const mat2";
			static constexpr auto ConstMatrix3 = "const mat3";
			static constexpr auto ConstMatrix4 = "const mat4";
			static constexpr auto ConstMatrix2x2 = "const mat2x2";
			static constexpr auto ConstMatrix2x3 = "const mat2x3";
			static constexpr auto ConstMatrix2x4 = "const mat2x4";
			static constexpr auto ConstMatrix3x3 = "const mat3x3";
			static constexpr auto ConstMatrix3x2 = "const mat3x2";
			static constexpr auto ConstMatrix3x4 = "const mat3x4";
			static constexpr auto ConstMatrix4x2 = "const mat4x2";
			static constexpr auto ConstMatrix4x3 = "const mat4x3";
			static constexpr auto ConstMatrix4x4 = "const mat4x4";
			/* Const matrix (Double) types */
			static constexpr auto ConstDoubleMatrix2 = "const dmat2";
			static constexpr auto ConstDoubleMatrix3 = "const dmat3";
			static constexpr auto ConstDoubleMatrix4 = "const dmat4";
			static constexpr auto ConstDoubleMatrix2x2 = "const dmat2x2";
			static constexpr auto ConstDoubleMatrix2x3 = "const dmat2x3";
			static constexpr auto ConstDoubleMatrix2x4 = "const dmat2x4";
			static constexpr auto ConstDoubleMatrix3x3 = "const dmat3x3";
			static constexpr auto ConstDoubleMatrix3x2 = "const dmat3x2";
			static constexpr auto ConstDoubleMatrix3x4 = "const dmat3x4";
			static constexpr auto ConstDoubleMatrix4x2 = "const dmat4x2";
			static constexpr auto ConstDoubleMatrix4x3 = "const dmat4x3";
			static constexpr auto ConstDoubleMatrix4x4 = "const dmat4x4";

			/* Sampler (Float) types */
			static constexpr auto Sampler1D = "sampler1D";
			static constexpr auto Sampler1DArray = "sampler1DArray";
			static constexpr auto Sampler2D = "sampler2D";
			static constexpr auto Sampler2DArray = "sampler2DArray";
			static constexpr auto Sampler2DMS = "sampler2DMS";
			static constexpr auto Sampler2DMSArray = "sampler2DMSArray";
			static constexpr auto Sampler3D = "sampler3D";
			static constexpr auto SamplerCube = "samplerCube";
			static constexpr auto SamplerCubeArray = "samplerCubeArray";
			static constexpr auto SamplerBuffer = "samplerBuffer";
			/* Sampler (Unsigned integer) types */
			static constexpr auto UIntSamplerBuffer = "usamplerBuffer";
			static constexpr auto UIntSamplerCubeArray = "usamplerCubeArray";
			static constexpr auto UIntSamplerCube = "usamplerCube";
			static constexpr auto UIntSampler3D = "usampler3D";
			static constexpr auto UIntSampler2DMSArray = "usampler2DMSArray";
			static constexpr auto UIntSampler2DMS = "usampler2DMS";
			static constexpr auto UIntSampler2DRectangle = "usampler2DRect";
			static constexpr auto UIntSampler2D = "usampler2D";
			static constexpr auto UIntSampler2DArray = "usampler2DArray";
			static constexpr auto UIntSampler1D = "usampler1D";
			static constexpr auto UIntSampler1DArray = "usampler1DArray";
			/* Sampler (Signed integer) types */
			static constexpr auto SIntSamplerBuffer = "isamplerBuffer";
			static constexpr auto SIntSamplerCubeArray = "isamplerCubeArray";
			static constexpr auto SIntSamplerCube = "isamplerCube";
			static constexpr auto SIntSampler3D = "isampler3D";
			static constexpr auto SIntSampler2DMSArray = "isampler2DMSArray";
			static constexpr auto SIntSampler2DMS = "isampler2DMS";
			static constexpr auto SIntSampler2DRectangle = "isampler2DRect";
			static constexpr auto SIntSampler2D = "isampler2D";
			static constexpr auto SIntSampler2DArray = "isampler2DArray";
			static constexpr auto SIntSampler1D = "isampler1D";
			static constexpr auto SIntSampler1DArray = "isampler1DArray";

			/* Shadow sampler (Float only) types */
			static constexpr auto Sampler1DShadow = "sampler1DShadow";
			static constexpr auto Sampler1DArrayShadow = "sampler1DArrayShadow";
			static constexpr auto Sampler2DShadow = "sampler2DShadow";
			static constexpr auto Sampler2DArrayShadow = "sampler2DArrayShadow";
			static constexpr auto Sampler2DRectangle = "sampler2DRect";
			static constexpr auto Sampler2DRectangleShadow = "sampler2DRectShadow";
			static constexpr auto SamplerCubeShadow = "samplerCubeShadow";
			static constexpr auto SamplerCubeArrayShadow = "samplerCubeArrayShadow";

			/* Image (Float) types */
			static constexpr auto Image1D = "image1D";
			static constexpr auto Image1DArray = "image1DArray";
			static constexpr auto Image2D = "image2D";
			static constexpr auto Image2DArray = "image2DArray";
			static constexpr auto Image2DRectangle = "image2DRect";
			static constexpr auto Image2DMS = "image2DMS";
			static constexpr auto Image2DMSArray = "image2DMSArray";
			static constexpr auto Image3D = "image3D";
			static constexpr auto ImageCube = "imageCube";
			static constexpr auto ImageCubeArray = "imageCubeArray";
			static constexpr auto ImageBuffer = "imageBuffer";
			/* Image (Unsigned integer) types */
			static constexpr auto UIntImage1D = "uimage1D";
			static constexpr auto UIntImage1DArray = "uimage1DArray";
			static constexpr auto UIntImage2D = "uimage2D";
			static constexpr auto UIntImage2DArray = "uimage2DArray";
			static constexpr auto UIntImage2DRectangle = "uimage2DRect";
			static constexpr auto UIntImage2DMS = "uimage2DMS";
			static constexpr auto UIntImage2DMSArray = "uimage2DMSArray";
			static constexpr auto UIntImage3D = "uimage3D";
			static constexpr auto UIntImageCube = "uimageCube";
			static constexpr auto UIntImageCubeArray = "uimageCubeArray";
			static constexpr auto UIntImageBuffer = "uimageBuffer";
			/* Image (Signed integer) types */
			static constexpr auto SIntImage1D = "iimage1D";
			static constexpr auto SIntImage1DArray = "iimage1DArray";
			static constexpr auto SIntImage2D = "iimage2D";
			static constexpr auto SIntImage2DArray = "iimage2DArray";
			static constexpr auto SIntImage2DRectangle = "iimage2DRect";
			static constexpr auto SIntImage2DMS = "iimage2DMS";
			static constexpr auto SIntImage2DMSArray = "iimage2DMSArray";
			static constexpr auto SIntImage3D = "iimage3D";
			static constexpr auto SIntImageCube = "iimageCube";
			static constexpr auto SIntImageCubeArray = "iimageCubeArray";
			static constexpr auto SIntImageBuffer = "iimageBuffer";

			/* === Vulkan only ==== */

			/* Texture (Float) types */
			static constexpr auto Texture1D = "texture1D";
			static constexpr auto Texture2D = "texture2D";
			static constexpr auto Texture3D = "texture3D";
			static constexpr auto TextureCube = "textureCube";
			static constexpr auto Texture2DRectangle = "texture2DRect";
			static constexpr auto Texture1DArray = "texture1DArray";
			static constexpr auto Texture2DArray = "texture2DArray";
			static constexpr auto TextureCubeArray = "textureCubeArray";
			static constexpr auto TextureBuffer = "textureBuffer";
			static constexpr auto Texture2DMS = "texture2DMS";
			static constexpr auto Texture2DMSArray = "texture2DMSArray";
			/* Texture (Unsigned integer) types */
			static constexpr auto UIntTexture1D = "utexture1D";
			static constexpr auto UIntTexture2D = "utexture2D";
			static constexpr auto UIntTexture3D = "utexture3D";
			static constexpr auto UIntTextureCube = "utextureCube";
			static constexpr auto UIntTexture2DRectangle = "utexture2DRect";
			static constexpr auto UIntTexture1DArray = "utexture1DArray";
			static constexpr auto UIntTexture2DArray = "utexture2DArray";
			static constexpr auto UIntTextureCubeArray = "utextureCubeArray";
			static constexpr auto UIntTextureBuffer = "utextureBuffer";
			static constexpr auto UIntTexture2DMS = "utexture2DMS";
			static constexpr auto UIntTexture2DMSArray = "utexture2DMSArray";
			/* Texture (Signed integer) types */
			static constexpr auto SIntTexture1D = "itexture1D";
			static constexpr auto SIntTexture2D = "itexture2D";
			static constexpr auto SIntTexture3D = "itexture3D";
			static constexpr auto SIntTextureCube = "itextureCube";
			static constexpr auto SIntTexture2DRectangle = "itexture2DRect";
			static constexpr auto SIntTexture1DArray = "itexture1DArray";
			static constexpr auto SIntTexture2DArray = "itexture2DArray";
			static constexpr auto SIntTextureCubeArray = "itextureCubeArray";
			static constexpr auto SIntTextureBuffer = "itextureBuffer";
			static constexpr auto SIntTexture2DMS = "itexture2DMS";
			static constexpr auto SIntTexture2DMSArray = "itexture2DMSArray";

			/* Additional sampler types */
			static constexpr auto Sampler = "sampler";
			static constexpr auto SamplerShadow = "samplerShadow";

			/* Subpass (Float) types */
			static constexpr auto SubpassInput = "subpassInput";
			static constexpr auto SubpassInputMS = "subpassInputMS";
			/* Subpass (Unsigned integer) types */
			static constexpr auto UIntSubpassInput = "usubpassInput";
			static constexpr auto UIntSubpassInputMS = "usubpassInputMS";
			/* Subpass (Signed integer) types */
			static constexpr auto SIntSubpassInput = "isubpassInput";
			static constexpr auto SIntSubpassInputMS = "isubpassInputMS";

			/* === Reserved === */

			static constexpr auto _Common = "common";
			static constexpr auto _Partition = "partition";
			static constexpr auto _Active = "active";
			static constexpr auto _ASM = "asm";
			static constexpr auto _Class = "class";
			static constexpr auto _Union = "union";
			static constexpr auto _Enum = "enum";
			static constexpr auto _Typedef = "typedef";
			static constexpr auto _Template = "template";
			static constexpr auto _This = "this";
			static constexpr auto _Resource = "resource";
			static constexpr auto _Goto = "goto";
			static constexpr auto _Inline = "inline";
			static constexpr auto _NoInline = "noinline";
			static constexpr auto _Public = "public";
			static constexpr auto _Static = "static";
			static constexpr auto _Extern = "extern";
			static constexpr auto _External = "external";
			static constexpr auto _Interface = "interface";
			static constexpr auto _Long = "long";
			static constexpr auto _Short = "short";
			static constexpr auto _Half = "half";
			static constexpr auto _Fixed = "fixed";
			static constexpr auto _Unsigned = "unsigned";
			static constexpr auto _Superp = "superp";
			static constexpr auto _Input = "input";
			static constexpr auto _Output = "output";
			static constexpr auto _HalfVector2 = "hvec2";
			static constexpr auto _HalfVector3 = "hvec3";
			static constexpr auto _HalfVector4 = "hvec4";
			static constexpr auto _FloatVector2 = "fvec2";
			static constexpr auto _FloatVector3 = "fvec3";
			static constexpr auto _FloatVector4 = "fvec4";
			static constexpr auto _Filter = "filter";
			static constexpr auto _SizeOf = "sizeof";
			static constexpr auto _Cast = "cast";
			static constexpr auto _Namespace = "namespace";
			static constexpr auto _Using = "using";
			static constexpr auto _Sampler3DRectangle = "sampler3DRect";

			namespace _Qualifier
			{
				static constexpr auto Uniform = "uniform";
				static constexpr auto In = "in";
				static constexpr auto ConstIn = "const in";
				static constexpr auto Out = "out";
				static constexpr auto InOut = "inout";
				static constexpr auto Layout = "layout";
				static constexpr auto Const = "const";
				static constexpr auto Precision = "precision";
				static constexpr auto Location = "location";
				static constexpr auto Buffer = "buffer";
				static constexpr auto ColumnMajor = "column_major";
				static constexpr auto RowMajor = "row_major";
				static constexpr auto Set = "set";
				static constexpr auto Binding = "binding";
				static constexpr auto Align = "align";
				static constexpr auto Offset = "offset";
				static constexpr auto Struct = "struct";
				static constexpr auto MaxVertices = "max_vertices";
				static constexpr auto PushConstant = "push_constant";
				static constexpr auto ConstantId = "constant_id";

				namespace _Interpolation
				{
					static constexpr auto Flat = "flat";
					static constexpr auto Smooth = "smooth";
					static constexpr auto NoPerspective = "noperspective";
					static constexpr auto Centroid = "centroid";
				}

				namespace _Memory
				{
					static constexpr auto Coherent = "coherent";
					static constexpr auto Volatile = "volatile";
					static constexpr auto Restrict = "restrict";
					static constexpr auto ReadOny = "readonly";
					static constexpr auto WriteOnly = "writeonly";
					static constexpr auto Shared = "shared";
					static constexpr auto Packed = "packed";
					static constexpr auto Std140 = "std140";
					static constexpr auto Std430 = "std430";
				}
			}

			namespace Vertex
			{
				/*
					in int gl_VertexID;
					in int gl_InstanceID;
					in int gl_DrawID; // Requires GLSL 4.60 or ARB_shader_draw_parameters
					in int gl_BaseVertex; // Requires GLSL 4.60 or ARB_shader_draw_parameters
					in int gl_BaseInstance; // Requires GLSL 4.60 or ARB_shader_draw_parameters
				*/
				namespace In
				{
					static constexpr auto VertexID = "gl_VertexID";
					static constexpr auto InstanceID = "gl_InstanceID";
					static constexpr auto DrawID = "gl_DrawID"; // Requires GLSL 4.60 or ARB_shader_draw_parameters
					static constexpr auto BaseVertex = "gl_BaseVertex"; // Requires GLSL 4.60 or ARB_shader_draw_parameters
					static constexpr auto BaseInstance = "gl_BaseInstance"; // Requires GLSL 4.60 or ARB_shader_draw_parameters
				}
				/*
					out gl_PerVertex
					{
					  vec4 gl_Position;
					  float gl_PointSize;
					  float gl_ClipDistance[];
					};
				*/
				namespace Out
				{
					static constexpr auto Position = "gl_Position";
					static constexpr auto PointSize = "gl_PointSize";
					static constexpr auto ClipDistance = "gl_ClipDistance";
				}
			}

			namespace Tesselation
			{
				namespace In
				{

				}

				namespace Out
				{

				}
			}

			namespace Geometry
			{
				/*
					in gl_PerVertex
					{
					  vec4 gl_Position;
					  float gl_PointSize;
					  float gl_ClipDistance[];
					} gl_in[];

					in int gl_PrimitiveIDIn;
					in int gl_InvocationID; // Requires GLSL 4.0 or ARB_gpu_shader5
				*/
				namespace In
				{
					static constexpr auto In = "gl_in";
					static constexpr auto Position = "gl_Position";
					static constexpr auto PointSize = "gl_PointSize";
					static constexpr auto ClipDistance = "gl_ClipDistance";
					static constexpr auto IndexedPosition = "gl_in[index].gl_Position";
					static constexpr auto IndexedPointSize = "gl_in[index].gl_PointSize";
					static constexpr auto IndexedClipDistance = "gl_in[index].gl_ClipDistance";
					static constexpr auto PrimitiveIDIn = "gl_PrimitiveIDIn";
					static constexpr auto InvocationID = "gl_InvocationID";
				}
				/*
					out gl_PerVertex
					{
					  vec4 gl_Position;
					  float gl_PointSize;
					  float gl_ClipDistance[];
					};
					out int gl_PrimitiveID;
					out int gl_Layer;
					out int gl_ViewportIndex; // Requires GL 4.1 or ARB_viewport_array.
				*/
				namespace Out
				{
					static constexpr auto Position = "gl_Position";
					static constexpr auto PointSize = "gl_PointSize";
					static constexpr auto ClipDistance = "gl_ClipDistance";
					static constexpr auto PrimitiveID = "gl_PrimitiveID";
					static constexpr auto Layer = "gl_Layer";
					static constexpr auto ViewportIndex = "gl_ViewportIndex";
				}

				namespace Function
				{
					static constexpr auto EmitStreamVertex = "EmitStreamVertex";
					static constexpr auto EndStreamPrimitive = "EndStreamPrimitive";
					static constexpr auto EmitVertex = "EmitVertex";
					static constexpr auto EndPrimitive = "EndPrimitive";
				}
			}

			namespace Fragment
			{
				/*
					in vec4 gl_FragCoord;
					in bool gl_FrontFacing;
					in vec2 gl_PointCoord;
					in int gl_SampleID;
					in vec2 gl_SamplePosition;
					in int gl_SampleMaskIn[];
					in float gl_ClipDistance[];
					in int gl_PrimitiveID;
					in int gl_Layer;
					in int gl_ViewportIndex;
				*/
				namespace In
				{
					static constexpr auto FragCoord = "gl_FragCoord";
					static constexpr auto FrontFacing = "gl_FrontFacing";
					static constexpr auto PointCoord = "gl_PointCoord";
					static constexpr auto SampleID = "gl_SampleID";
					static constexpr auto SamplePosition = "gl_SamplePosition";
					static constexpr auto SampleMaskIn = "gl_SampleMaskIn"; // []
					static constexpr auto ClipDistance = "gl_ClipDistance"; // []
					static constexpr auto PrimitiveID = "gl_PrimitiveID";
					static constexpr auto Layer = "gl_Layer";
					static constexpr auto ViewportIndex = "gl_ViewportIndex";
				}
				/*
					out float gl_FragDepth;
					out int gl_SampleMask[];
				*/
				namespace Out
				{
					static constexpr auto FragDepth = "gl_FragDepth";
					static constexpr auto SampleMask = "gl_SampleMask";
					static constexpr auto FragColor = "gl_FragColor";
				}
			}

			namespace Functions
			{
				static constexpr auto Length = "length";
			}
		}

		/** Vertex attributes naming convention. */

		/**
		 * @brief The name of fixed vertex attributes in Saphir.
		 * @note See Emeraude::Graphics::VertexAttributeType for predefined vertex attribute in geometry.
		 * Use Emeraude::Saphir::getVertexAttributeVariableName() to convert a attribute type to one of these variables.
		 */
		namespace Attribute
		{
			static constexpr auto Position{"vaVertex"};
			static constexpr auto Tangent{"vaTangent"};
			static constexpr auto Binormal{"vaBinormal"};
			static constexpr auto Normal{"vaNormal"};
			static constexpr auto Color{"vaColor"};
			static constexpr auto Primary2DTextureCoordinates{"va2DTexCoord0"};
			static constexpr auto Primary3DTextureCoordinates{"va3DTexCoord0"};
			static constexpr auto Secondary2DTextureCoordinates{"va2DTexCoord1"};
			static constexpr auto Secondary3DTextureCoordinates{"va3DTexCoord1"};
			static constexpr auto ModelMatrix{"vaModelMatrix"};
			static constexpr auto NormalModelMatrix{"vaNormalModelMatrix"};
			static constexpr auto ModelPosition{"vaModelPosition"};
			static constexpr auto ModelScaling{"vaModelScaling"};
		}

		/** @brief Structures naming convention. */
		namespace Struct
		{
			static constexpr auto CubemapFace{"CubemapFace"};
		}

		/** @brief Uniforms naming convention. */
		namespace Uniform
		{
			/* Generic */
			static constexpr auto PrimarySampler{"uPrimarySampler"};
			static constexpr auto SecondarySampler{"uSecondarySampler"};
			/* Material specific */
			static constexpr auto AmbientSampler{"uAmbientSampler"};
			static constexpr auto DiffuseSampler{"uDiffuseSampler"};
			static constexpr auto SpecularSampler{"uSpecularSampler"};
			static constexpr auto AutoIlluminationSampler{"uAutoIlluminationSampler"};
			static constexpr auto NormalSampler{"uNormalSampler"};
			static constexpr auto ReflectionSampler{"uReflectionSampler"};
			static constexpr auto OpacitySampler{"uOpacitySampler"};
			static constexpr auto ShadowMapSampler{"uShadowMapSampler"};
		}

		/** @brief Uniforms block variables naming convention. */
		namespace UniformBlock
		{
			static constexpr auto View{"ubView"};
			static constexpr auto Material{"ubMaterial"};
			static constexpr auto Light{"ubLight"};

			namespace Type
			{
				static constexpr auto View{"View"};
				static constexpr auto CubemapView{"CubemapView"};
				static constexpr auto BasicMaterial{"BasicMaterial"};
				static constexpr auto StandardMaterial{"StandardMaterial"};
				static constexpr auto DirectionalLight{"DirectionalLight"};
				static constexpr auto PointLight{"PointLight"};
				static constexpr auto SpotLight{"SpotLight"};
			}

			namespace Component
			{
				/* Generic */
				static constexpr auto Instance{"instance"};
				static constexpr auto Amount{"amount"};
				static constexpr auto Scale{"scale"};
				/* View specific */
				static constexpr auto ProjectionMatrix{"projectionMatrix"};
				static constexpr auto PositionWorldSpace{"positionWorldSpace"};
				static constexpr auto Velocity = "velocity";
				static constexpr auto ViewProperties{"viewProperties"};
				static constexpr auto AmbientLightColor{"ambientLightColor"};
				static constexpr auto AmbientLightIntensity{"ambientLightIntensity"};
				/* Material specific */
				static constexpr auto AmbientColor{"ambientColor"};
				static constexpr auto DiffuseColor{"diffuseColor"};
				static constexpr auto SpecularColor{"specularColor"};
				static constexpr auto Shininess{"shininess"};
				static constexpr auto AutoIlluminationColor{"autoIlluminationColor"};
				static constexpr auto AutoIlluminationAmount{"autoIlluminationAmount"};
				static constexpr auto Opacity{"opacity"};
				static constexpr auto NormalScale{"normalScale"};
				static constexpr auto ReflectionAmount{"reflectionAmount"};
				/* Light specific */
				static constexpr auto Color{"color"};
				//static constexpr auto PositionWorldSpace{"positionWorldSpace"}; // Shared with View
				static constexpr auto DirectionWorldSpace{"directionWorldSpace"};
				static constexpr auto Intensity{"intensity"};
				static constexpr auto Radius{"radius"};
				static constexpr auto InnerCosAngle{"innerCosAngle"};
				static constexpr auto OuterCosAngle{"outerCosAngle"};
				static constexpr auto ViewProjectionMatrix{"viewProjectionMatrix"};
			}
		}

		/** @brief Push constant variables naming convention. */
		namespace PushConstant
		{
			static constexpr auto Matrices{"pcMatrices"};
			static constexpr auto Overlay{"pcOverlay"};

			namespace Type
			{
				static constexpr auto Matrices{"Matrices"};
				static constexpr auto Overlay{"Overlay"};
			}

			namespace Component
			{
				/* NOTE : Regular 3D rendering. */
				static constexpr auto ViewMatrix{"viewMatrix"};
				static constexpr auto ModelMatrix{"modelMatrix"};
				static constexpr auto ViewProjectionMatrix{"viewProjectionMatrix"};
				static constexpr auto ModelViewProjectionMatrix{"modelViewProjectionMatrix"};
				/* NOTE : Specific (overlay, ...) rendering. */
				static constexpr auto TransformationMatrix{"transformationMatrix"};
			}
		}

		/** @brief Interstage variables naming convention. */
		namespace ShaderVariable
		{
			static constexpr auto PositionWorldSpace{"svPositionWorldSpace"};
			static constexpr auto GLPositionWorldSpace{"gl_Position@WorldSpace"}; /* NOTE: Must never appear in real code. */
			static constexpr auto PositionViewSpace{"svPositionViewSpace"};
			static constexpr auto PositionTextureSpace{"svPositionTextureSpace"};
			static constexpr auto PositionScreenSpace{"gl_Position"};
			static constexpr auto PrimaryVertexColor{"svPrimaryVertexColor"};
			static constexpr auto SecondaryVertexColor{"svSecondaryVertexColor"};
			static constexpr auto Primary2DTextureCoordinates{"sv2DTexCoord0"};
			static constexpr auto Primary3DTextureCoordinates{"sv3DTexCoord0"};
			static constexpr auto Secondary2DTextureCoordinates{"sv2DTexCoord1"};
			static constexpr auto Secondary3DTextureCoordinates{"sv3DTexCoord1"};
			static constexpr auto ReflectionTextureCoordinates{"svReflectionTexCoord"};
			static constexpr auto TangentWorldSpace{"svTangentWorldSpace"};
			static constexpr auto TangentViewSpace{"svTangentViewSpace"};
			static constexpr auto BinormalWorldSpace{"svBinormalWorldSpace"};
			static constexpr auto BinormalViewSpace{"svBinormalViewSpace"};
			static constexpr auto NormalWorldSpace{"svNormalWorldSpace"};
			static constexpr auto NormalViewSpace{"svNormalViewSpace"};
			static constexpr auto SpriteModelMatrix{"svSpriteModelMatrix"};
			static constexpr auto ModelViewMatrix{"svModelViewMatrix"};
			static constexpr auto NormalMatrix{"svNormalMatrix"};
			static constexpr auto ModelViewProjectionMatrix{"svModelViewProjectionMatrix"};
			static constexpr auto WorldTBNMatrix{"svWorldTBNMatrix"};
			static constexpr auto ViewTBNMatrix{"svViewTBNMatrix"};
			static constexpr auto WorldToTangentMatrix{"svWorldToTangent"};
			static constexpr auto OutputFragment{"svOutputFragment"};
			static constexpr auto FragCoord{"svFragCoord"};
			static constexpr auto Light{"svLight"};
		}

		/** @brief Shader block variables naming convention. */
		namespace ShaderBlock
		{
			namespace Component
			{
				static constexpr auto AttenuationFactor = "AttenuationFactor";
				static constexpr auto SpotFactor = "SpotFactor";
				static constexpr auto DirectionWorldSpace = "directionWorldSpace";
				static constexpr auto DirectionViewSpace = "directionViewSpace";
				static constexpr auto DirectionTextureSpace = "directionTextureSpace";
				static constexpr auto ViewDirectionTextureSpace = "viewDirectionTextureSpace";
				static constexpr auto PositionLightSpace = "positionLightSpace";
			}
		}
	}

	/**
	* @brief Returns a variable from the current matrix push constant.
	* @param componentName The push constant component name. See Keys::PushConstant::Component.
	* @return std::string
	*/
	[[nodiscard]]
	std::string
	MatrixPC (const char * componentName) noexcept;

	/**
	* @brief Returns a variable from the current overlay push constant.
	* @param componentName The push constant component name. See Keys::PushConstant::Component.
	* @return std::string
	*/
	[[nodiscard]]
	std::string
	OverlayPC (const char * componentName) noexcept;

	/**
	 * @brief Returns the full variable name from a view uniform block.
	 * @param componentName The uniform block component name. See Keys::UniformBlock::Component.
	 * @return std::string
	 */
	[[nodiscard]]
	std::string ViewUB (const char * componentName) noexcept;

	/**
	 * @brief Returns the full variable name from an indexed view uniform block.
	 * @param memberName The uniform block component name. See Keys::UniformBlock::Component.
	 * @param indexVariableName The index in the array.
	 * @param componentName The uniform block component name. See Keys::UniformBlock::Component.
	 * @return std::string
	 */
	[[nodiscard]]
	std::string CubeViewUB (const char * memberName, const char * indexVariableName, const char * componentName) noexcept;

	/**
	 * @brief Returns the full variable name from a material uniform block.
	 * @param componentName The uniform block component name. See Keys::UniformBlock::Component.
	 * @return std::string
	 */
	[[nodiscard]]
	std::string MaterialUB (const char * componentName) noexcept;

	/**
	 * @brief Returns a variable from the current light uniform block.
	 * @param componentName The uniform block component name. See Keys::UniformBlock::Component.
	 * @return std::string
	 */
	[[nodiscard]]
	std::string LightUB (const char * componentName) noexcept;
}
