/*
 * src/Graphics/Types.hpp
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
#include <array>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <string>

/* Local usages. */
#include "Libs/PixelFactory/Pixmap.hpp"

namespace EmEn::Graphics
{
	/* Common expressions. */
	static constexpr auto NoneString{"None"};
	static constexpr auto InvalidString{"Invalid"};

	/** @brief The type of rendering to sort graphics pipeline. */
	enum class RenderTargetType : uint8_t
	{
		View,
		CubicView,
		ShadowMap,
		ShadowCubemap
	};

	/** @brief Defines the render type to sort out what involves the rendering. */
	enum class RenderPassType : uint32_t
	{
		/* No light code. */
		SimplePass,
		/* Split light pass code. */
		AmbientPass,
		DirectionalLightPass,
		DirectionalLightPassNoShadow,
		PointLightPass,
		PointLightPassNoShadow,
		SpotLightPass,
		SpotLightPassNoShadow,
		/* Enum value for invalid type. */
		None = std::numeric_limits< uint32_t >::max()
	};

	static constexpr auto SimplePassString{"SimplePass"};
	static constexpr auto AmbientPassString{"AmbientPass"};
	static constexpr auto DirectionalLightPassString{"DirectionalLightPass"};
	static constexpr auto DirectionalLightPassNoShadowString{"DirectionalLightPassNoShadow"};
	static constexpr auto PointLightPassString{"PointLightPass"};
	static constexpr auto PointLightPassNoShadowString{"PointLightPassNoShadow"};
	static constexpr auto SpotLightPassString{"SpotLightPass"};
	static constexpr auto SpotLightPassNoShadowString{"SpotLightPassNoShadow"};

	/**
	 * @brief Converts a light pass type enumeration value to the corresponding string.
	 * @param value The enumeration value.
	 * @return const char *
	 */
	[[nodiscard]]
	const char * to_cstring (RenderPassType value) noexcept;

	/**
	 * @brief Returns a string version of the enum value.
	 * @param value The enum value.
	 * @return std::string
	 */
	[[nodiscard]]
	inline
	std::string
	to_string (RenderPassType value) noexcept
	{
		return {to_cstring(value)};
	}

	/**
	 * @brief Converts a string to a light pass type enumeration value.
	 * @param value A reference to a string.
	 * @return RenderPassType
	 */
	[[nodiscard]]
	RenderPassType to_RenderPassType (const std::string & value) noexcept;

	/** @brief Defines the model matrices buffer type in video memory. */
	enum class ModelMatrixType : uint32_t
	{
		UniformBufferObject = 1,
		VertexBufferObject = 2,
		Invalid = std::numeric_limits< uint32_t >::max()
	};

	static constexpr auto UniformBufferObjectString{"UniformBufferObject"};
	static constexpr auto VertexBufferObjectString{"VertexBufferObject"};

	/**
	 * @brief Converts a model matrices type enumeration value to the corresponding string.
	 * @param value The enumeration value.
	 * @return const char *
	 */
	[[nodiscard]]
	const char * to_cstring (ModelMatrixType value) noexcept;

	/**
	 * @brief Returns a string version of the enum value.
	 * @param value The enum value.
	 * @return std::string
	 */
	[[nodiscard]]
	inline
	std::string
	to_string (ModelMatrixType value) noexcept
	{
		return {to_cstring(value)};
	}

	/**
	 * @brief Converts a string to a model matrix type enumeration value.
	 * @param value A reference to a string.
	 * @return ModelMatrixType
	 */
	[[nodiscard]]
	ModelMatrixType to_ModelMatrixType (const std::string & value) noexcept;

	/** @brief Defines a filling type for a material surface. */
	enum class FillingType : uint32_t
	{
		Value = 0,
		Color = 1,
		Gradient = 2,
		Texture = 3,
		VolumeTexture = 4,
		Cubemap = 5,
		AnimatedTexture = 6,
		AlphaChannelAsValue = 7,
		None = std::numeric_limits< uint32_t >::max()
	};

	static constexpr auto ValueString{"Value"};
	static constexpr auto ColorString{"Color"};
	static constexpr auto GradientString{"Gradient"};
	static constexpr auto TextureString{"Texture"};
	static constexpr auto VolumeTextureString{"VolumeTexture"};
	static constexpr auto CubemapString{"Cubemap"};
	static constexpr auto AnimatedTextureString{"AnimatedTexture"};
	static constexpr auto AlphaChannelAsValueString{"AlphaChannelAsValue"};

	/**
	 * @brief Converts a filling type enumeration value to the corresponding string.
	 * @param value The enumeration value.
	 * @return const char *
	 */
	[[nodiscard]]
	const char * to_cstring (FillingType value) noexcept;

	/**
	 * @brief Returns a string version of the enum value.
	 * @param value The enum value.
	 * @return std::string
	 */
	[[nodiscard]]
	inline
	std::string
	to_string (FillingType value) noexcept
	{
		return {to_cstring(value)};
	}

	/**
	 * @brief Converts a string to a filling type enumeration value.
	 * @param value A reference to a string.
	 * @return FillingType
	 */
	[[nodiscard]]
	FillingType to_FillingType (const std::string & value) noexcept;

	/** @brief Defines a blending operation mode. */
	enum class BlendingMode : uint32_t
	{
		Normal = 0,
		Add = 1,
		Multiply = 2,
		Screen = 3,
		None = std::numeric_limits< uint32_t >::max()
	};

	static constexpr auto NormalBlendingString{"Normal"};
	static constexpr auto AddBlendingString{"Add"};
	static constexpr auto MultiplyBlendingString{"Multiply"};
	static constexpr auto ScreenBlendingString{"Screen"};

	/**
	 * @brief Converts a blending mode enumeration value to the corresponding string.
	 * @param value The enumeration value.
	 * @return const char *
	 */
	[[nodiscard]]
	const char * to_cstring (BlendingMode value) noexcept;

	/**
	 * @brief Returns a string version of the enum value.
	 * @param value The enum value.
	 * @return std::string
	 */
	[[nodiscard]]
	inline
	std::string
	to_string (BlendingMode value) noexcept
	{
		return {to_cstring(value)};
	}

	/**
	 * @brief Converts a string to a blending mode enumeration value.
	 * @param value A reference to a string.
	 * @return BlendingMode
	 */
	[[nodiscard]]
	BlendingMode to_BlendingMode (const std::string & value) noexcept;

	/** @brief Defines component type for material. */
	enum class ComponentType : uint32_t
	{
		Ambient = 0,
		Diffuse = 1,
		Specular = 2,
		Albedo = 3,
		AutoIllumination = 4,
		Opacity = 5,
		Normal = 6,
		Displacement = 7,
		Reflection = 8,
		Roughness = 9,
		Metalness = 10,
		Invalid = std::numeric_limits< uint32_t >::max()
	};

	static constexpr auto AmbientString{"Ambient"};
	static constexpr auto DiffuseString{"Diffuse"};
	static constexpr auto SpecularString{"Specular"};
	static constexpr auto AlbedoString{"Albedo"};
	static constexpr auto AutoIlluminationString{"AutoIlluminationColor"};
	static constexpr auto OpacityString{"Opacity"};
	static constexpr auto NormalString{"Normal"};
	static constexpr auto DisplacementString{"Displacement"};
	static constexpr auto ReflectionString{"Reflection"};
	static constexpr auto RoughnessString{"Roughness"};
	static constexpr auto MetalnessString{"Metalness"};

	/**
	 * @brief Converts a component type enumeration value to the corresponding string.
	 * @param value The enumeration value.
	 * @return const char *
	 */
	[[nodiscard]]
	const char * to_cstring (ComponentType value) noexcept;

	/**
	 * @brief Returns a string version of the enum value.
	 * @param value The enum value.
	 * @return std::string
	 */
	[[nodiscard]]
	inline
	std::string
	to_string (ComponentType value) noexcept
	{
		return {to_cstring(value)};
	}

	/**
	 * @brief Converts a string to a component type enumeration value.
	 * @param value A reference to a string.
	 * @return ComponentType
	 */
	[[nodiscard]]
	ComponentType to_ComponentType (const std::string & value) noexcept;

	/** @brief Defines the way the data are structured inside the VBO/IBO. */
	enum class Topology : uint32_t
	{
		PointList = 0,
		LineLine = 1,
		LineStrip = 2,
		TriangleList = 3,
		TriangleStrip = 4,
		TriangleFan = 5,
		LineListWithAdjacency = 6,
		LineStripWithAdjacency = 7,
		TriangleListWithAdjacency = 8,
		TriangleStripWithAdjacency = 9,
		PatchList = 10,
		CustomData = 11,
		Invalid = std::numeric_limits< uint32_t >::max()
	};

	static constexpr auto PointListString{"PointList"};
	static constexpr auto LineLineString{"LineLine"};
	static constexpr auto LineStripString{"LineStrip"};
	static constexpr auto TriangleListString{"TriangleList"};
	static constexpr auto TriangleStripString{"TriangleStrip"};
	static constexpr auto TriangleFanString{"TriangleFan"};
	static constexpr auto LineListWithAdjacencyString{"LineListWithAdjacency"};
	static constexpr auto LineStripWithAdjacencyString{"LineStripWithAdjacency"};
	static constexpr auto TriangleListWithAdjacencyString{"TriangleListWithAdjacency"};
	static constexpr auto TriangleStripWithAdjacencyString{"TriangleStripWithAdjacency"};
	static constexpr auto PatchListString{"PatchList"};
	static constexpr auto CustomDataString{"CustomData"};

	/**
	 * @brief Converts a topology type enumeration value to the corresponding string.
	 * @param value The enumeration value.
	 * @return const char *
	 */
	[[nodiscard]]
	const char * to_cstring (Topology value) noexcept;

	/**
	 * @brief Returns a string version of the enum value.
	 * @param value The enum value.
	 * @return std::string
	 */
	[[nodiscard]]
	inline
	std::string
	to_string (Topology value) noexcept
	{
		return {to_cstring(value)};
	}

	/**
	 * @brief Converts a string to a topology type enumeration value.
	 * @param value A reference to a string.
	 * @return Topology
	 */
	[[nodiscard]]
	Topology to_TopologyType (const std::string & value) noexcept;

	/** @brief Defines the way the geometry will be displayed on screen. */
	enum class PolygonMode : uint32_t
	{
		Fill = 0,
		Line = 1,
		Point = 2,
		FillRectangle = 3,
		Invalid = std::numeric_limits< uint32_t >::max()
	};

	static constexpr auto FillString{"Fill"};
	static constexpr auto LineString{"Line"};
	static constexpr auto PointString{"Point"};
	static constexpr auto FillRectangleString{"FillRectangle"};

	/**
	 * @brief Converts a polygon mode enumeration value to the corresponding string.
	 * @param value The enumeration value.
	 * @return const char *
	 */
	[[nodiscard]]
	const char * to_cstring (PolygonMode value) noexcept;

	/**
	 * @brief Returns a string version of the enum value.
	 * @param value The enum value.
	 * @return std::string
	 */
	[[nodiscard]]
	inline
	std::string
	to_string (PolygonMode value) noexcept
	{
		return {to_cstring(value)};
	}

	/**
	 * @brief Converts a string to a polygon mode enumeration value.
	 * @param value A reference to a string.
	 * @return PolygonMode
	 */
	[[nodiscard]]
	PolygonMode to_PolygonMode (const std::string & value) noexcept;

	/** @brief Defines the culling face method. */
	enum class CullingMode : uint32_t
	{
		None = 0,
		Back = 1,
		Front = 2,
		Both = 3,
		Invalid = std::numeric_limits< uint32_t >::max()
	};

	//static constexpr auto NoneString{"None"};
	static constexpr auto BackString{"Back"};
	static constexpr auto FrontString{"Front"};
	static constexpr auto BothString{"Both"};
	//static constexpr auto InvalidString{"Invalid"};

	/**
	 * @brief Converts a culling mode enumeration value to the corresponding string.
	 * @param value The enumeration value.
	 * @return const char *
	 */
	[[nodiscard]]
	const char * to_cstring (CullingMode value) noexcept;

	/**
	 * @brief Returns a string version of the enum value.
	 * @param value The enum value.
	 * @return std::string
	 */
	[[nodiscard]]
	inline
	std::string
	to_string (CullingMode value) noexcept
	{
		return {to_cstring(value)};
	}

	/**
	 * @brief Converts a string to a culling mode enumeration value.
	 * @param value A reference to a string.
	 * @return CullingMode
	 */
	[[nodiscard]]
	CullingMode to_CullingMode (const std::string & value) noexcept;

	/** @brief Defines a buffer type in a framebuffer. */
	enum class BufferType : uint32_t
	{
		ColorBuffer = 0,
		DepthBuffer = 1,
		StencilBuffer = 2,
		Invalid = std::numeric_limits< uint32_t >::max()
	};

	static constexpr auto ColorBufferString{"ColorBuffer"};
	static constexpr auto DepthBufferString{"DepthBuffer"};
	static constexpr auto StencilBufferString{"StencilBuffer"};

	/**
	 * @brief Converts a buffer type enumeration value to the corresponding string.
	 * @param value The enumeration value.
	 * @return const char *
	 */
	[[nodiscard]]
	const char * to_cstring (BufferType value) noexcept;

	/**
	 * @brief Returns a string version of the enum value.
	 * @param value The enum value.
	 * @return std::string
	 */
	[[nodiscard]]
	inline
	std::string
	to_string (BufferType value) noexcept
	{
		return {to_cstring(value)};
	}

	/**
	 * @brief Converts a string to a buffer type enumeration value.
	 * @param value A reference to a string.
	 * @return BufferType
	 */
	[[nodiscard]]
	BufferType to_BufferType (const std::string & value) noexcept;

	/** @brief UBO alignment for matrix. */
	static constexpr auto Matrix4Alignment{16UL};
	/** @brief UBO alignment for vector. */
	static constexpr auto VectorAlignment{4UL};

	/** @brief Defines vertex attribute types. */
	enum class VertexAttributeType : uint32_t
	{
		Position = 0U,
		Tangent = 1U,
		Binormal = 2U,
		Normal = 3U,
		Primary2DTextureCoordinates = 4U,
		Primary3DTextureCoordinates = 5U,
		Secondary2DTextureCoordinates = 6U,
		Secondary3DTextureCoordinates = 7U,
		VertexColor = 8U,
		ModelMatrixR0 = 9U,
		ModelMatrixR1 = 10U,
		ModelMatrixR2 = 11U,
		ModelMatrixR3 = 12U,
		NormalModelMatrixR0 = 13U,
		NormalModelMatrixR1 = 14U,
		NormalModelMatrixR2 = 15U,
		ModelPosition = 16U,
		ModelScaling = 17U
	};

	static constexpr auto PositionString{"Position"};
	static constexpr auto TangentString{"Tangent"};
	static constexpr auto BinormalString{"Binormal"};
	//static constexpr auto NormalString{"Normal"};
	static constexpr auto VertexColorString{"VertexColor"};
	static constexpr auto Primary2DTextureCoordinatesString{"Primary2DTextureCoordinates"};
	static constexpr auto Primary3DTextureCoordinatesString{"Primary3DTextureCoordinates"};
	static constexpr auto Secondary2DTextureCoordinatesString{"Secondary2DTextureCoordinates"};
	static constexpr auto Secondary3DTextureCoordinatesString{"Secondary3DTextureCoordinates"};
	static constexpr auto ModelMatrixString{"ModelMatrix"};
	static constexpr auto NormalModelMatrixString{"NormalModelMatrix"};
	static constexpr auto ModelPositionString{"ModelPosition"};
	static constexpr auto ModelScalingString{"ModelScaling"};

	/**
	 * @brief Converts a vertex attribute type enumeration value to the corresponding string.
	 * @param value The enumeration value.
	 * @return const char *
	 */
	[[nodiscard]]
	const char * to_cstring (VertexAttributeType value) noexcept;

	/**
	 * @brief Returns a string version of the enum value.
	 * @param value The enum value.
	 * @return std::string
	 */
	[[nodiscard]]
	inline
	std::string
	to_string (VertexAttributeType value) noexcept
	{
		return {to_cstring(value)};
	}

	/**
	 * @brief Converts a string to a vertex attribute type enumeration value.
	 * @param value A reference to a string.
	 * @return VertexAttributeType
	 */
	[[nodiscard]]
	VertexAttributeType to_VertexAttributeType (const std::string & value) noexcept;

	/**
	 * @brief Returns the attribute type size (number of element).
	 * @param type The type of attribute.
	 * @return uint32_t
	 */
	[[nodiscard]]
	constexpr
	uint32_t
	getAttributeSize (VertexAttributeType type) noexcept
	{
		switch ( type )
		{
			case VertexAttributeType::VertexColor :
			/* NOTE: mat4 is four successive vec4 */
			case VertexAttributeType::ModelMatrixR0 :
			case VertexAttributeType::ModelMatrixR1 :
			case VertexAttributeType::ModelMatrixR2 :
			case VertexAttributeType::ModelMatrixR3 :
				return 4;

			case VertexAttributeType::Position :
			case VertexAttributeType::Tangent :
			case VertexAttributeType::Binormal :
			case VertexAttributeType::Normal :
			case VertexAttributeType::Primary3DTextureCoordinates :
			case VertexAttributeType::Secondary3DTextureCoordinates :
			/* NOTE: mat3 is three successive vec3 */
			case VertexAttributeType::NormalModelMatrixR0 :
			case VertexAttributeType::NormalModelMatrixR1 :
			case VertexAttributeType::NormalModelMatrixR2 :
			case VertexAttributeType::ModelPosition :
			case VertexAttributeType::ModelScaling :
				return 3;

			case VertexAttributeType::Primary2DTextureCoordinates :
			case VertexAttributeType::Secondary2DTextureCoordinates :
				return 2;

			default:
				return 0;
		}
	}

	/** @brief Defines cubemap faces. */
	enum class CubemapFace : size_t
	{
		PositiveX = 0,
		NegativeX = 1,
		PositiveY = 2,
		NegativeY = 3,
		PositiveZ = 4,
		NegativeZ = 5
	};

	static constexpr auto PositiveXString{"PositiveX"};
	static constexpr auto NegativeXString{"NegativeX"};
	static constexpr auto PositiveYString{"PositiveY"};
	static constexpr auto NegativeYString{"NegativeY"};
	static constexpr auto PositiveZString{"PositiveZ"};
	static constexpr auto NegativeZString{"NegativeZ"};

	static auto constexpr CubemapFaceCount{6UL};

	static constexpr std::array< const char * const, CubemapFaceCount > CubemapFaceNames{
		PositiveXString, NegativeXString,
		PositiveYString, NegativeYString,
		PositiveZString, NegativeZString
	};

	using CubemapPixmaps = std::array< Libs::PixelFactory::Pixmap< uint8_t >, CubemapFaceCount >;

	/**
	 * @brief Converts a cubemap face enumeration value to the corresponding string.
	 * @param value The enumeration value.
	 * @return const char *
	 */
	[[nodiscard]]
	const char * to_cstring (CubemapFace value) noexcept;

	/**
	 * @brief Returns a string version of the enum value.
	 * @param value The enum value.
	 * @return std::string
	 */
	[[nodiscard]]
	inline
	std::string
	to_string (CubemapFace value) noexcept
	{
		return {to_cstring(value)};
	}

	/**
	 * @brief Converts a string to a cubemap face enumeration value.
	 * @param value A reference to a string.
	 * @return CubemapFace
	 */
	[[nodiscard]]
	CubemapFace to_CubemapFace (const std::string & value) noexcept;

	static constexpr std::array< CubemapFace, 6 > CubemapFaceIndexes = {{
		CubemapFace::PositiveX, CubemapFace::NegativeX,
		CubemapFace::PositiveY, CubemapFace::NegativeY,
		CubemapFace::PositiveZ, CubemapFace::NegativeZ
	}};

	/** @brief Defines sampler filter quality. */
	enum class FilterQuality : uint8_t
	{
		None,
		Custom,
		Linear,
		Bilinear,
		Trilinear
	};

	static constexpr auto CustomString{"Custom"};
	static constexpr auto LinearString{"Linear"};
	static constexpr auto BilinearString{"Bilinear"};
	static constexpr auto TrilinearString{"Trilinear"};

	/**
	 * @brief Converts a filter quality enumeration value to the corresponding string.
	 * @param value The enumeration value.
	 * @return const char *
	 */
	[[nodiscard]]
	const char * to_cstring (FilterQuality value) noexcept;

	/**
	 * @brief Returns a string version of the enum value.
	 * @param value The enum value.
	 * @return std::string
	 */
	[[nodiscard]]
	inline
	std::string
	to_string (FilterQuality value) noexcept
	{
		return {to_cstring(value)};
	}

	/**
	 * @brief Converts a string to a filter quality enumeration value.
	 * @param value A reference to a string.
	 * @return FilterQuality
	 */
	[[nodiscard]]
	FilterQuality to_FilterQuality (const std::string & value) noexcept;

	/**
	 * @brief The "point to" enumeration following the Vulkan default world axis.
	 */
	enum class PointTo : uint8_t
	{
		/** @brief Point to following the X+ axis (right) = {1, 0, 0}. */
		PositiveX = 0,
		/** @brief Point to following the X- axis (left) = {-1, 0, 0}. */
		NegativeX = 1,
		/** @brief Point to following the Y+ axis (bottom) = {0, 1, 0}. */
		PositiveY = 2,
		/** @brief Point to following the Y- axis (up) = {0, -1, 0}. */
		NegativeY = 3,
		/** @brief Point to following the Z+ axis (front) = {0, 0, 1}. */
		PositiveZ = 4,
		/** @brief Point to following the Z- axis (back, in screen depth) = {0, 0, -1}. */
		NegativeZ = 5
	};

	/**
	 * @brief The Shape enum.
	 */
	enum class ShapeType : uint8_t
	{
		Custom,
		Triangle,
		Quad,
		Cube,
		Sphere,
		GeodesicSphere,
		Cylinder,
		Cone,
		Disk,
		Torus,
		Tetrahedron,
		Hexahedron,
		Octahedron,
		Dodecahedron,
		Icosahedron,
		Arrow,
		Axis
	};

	//static constexpr auto CustomString{"Custom"};
	static constexpr auto TriangleString{"ShapeTriangle"};
	static constexpr auto QuadString{"Quad"};
	static constexpr auto CubeString{"Cube"};
	static constexpr auto SphereString{"Sphere"};
	static constexpr auto GeodesicSphereString{"GeodesicSphere"};
	static constexpr auto CylinderString{"Cylinder"};
	static constexpr auto ConeString{"Cone"};
	static constexpr auto DiskString{"Disk"};
	static constexpr auto TorusString{"Torus"};
	static constexpr auto TetrahedronString{"Tetrahedron"};
	static constexpr auto HexahedronString{"Hexahedron"};
	static constexpr auto OctahedronString{"Octahedron"};
	static constexpr auto DodecahedronString{"Dodecahedron"};
	static constexpr auto IcosahedronString{"Icosahedron"};
	static constexpr auto ArrowString{"Arrow"};
	static constexpr auto AxisString{"Axis"};

	/**
	 * @brief Converts a shape type enumeration value to the corresponding string.
	 * @param value The enumeration value.
	 * @return const char *
	 */
	[[nodiscard]]
	const char * to_cstring (ShapeType value) noexcept;

	/**
	 * @brief Returns a string version of the enum value.
	 * @param value The enum value.
	 * @return std::string
	 */
	[[nodiscard]]
	inline
	std::string
	to_string (ShapeType value) noexcept
	{
		return {to_cstring(value)};
	}

	/**
	 * @brief Converts a string to a filter quality enumeration value.
	 * @param value A reference to a string.
	 * @return FilterQuality
	 */
	[[nodiscard]]
	ShapeType to_ShapeType (const std::string & value) noexcept;

	/**
	 * @brief Light type enumeration.
	 */
	enum class LightType : uint8_t
	{
		Directional = 0,
		Point = 1,
		Spot = 2
	};

	static constexpr auto DirectionalLightString{"DirectionalLight"};
	static constexpr auto PointLightString{"PointLight"};
	static constexpr auto SpotLightString{"SpotLight"};

	/**
	 * @brief Returns a C-String version of the enum value.
	 * @param type The enum value.
	 * @return const char *
	 */
	[[nodiscard]]
	const char * to_cstring (LightType type) noexcept;

	/**
	 * @brief Returns a string version of the enum value.
	 * @param type The enum value.
	 * @return std::string
	 */
	[[nodiscard]]
	inline
	std::string
	to_string (LightType type) noexcept
	{
		return {to_cstring(type)};
	}

	/**
	 * @brief Light type enumeration.
	 */
	enum class AntiAliasingType : uint8_t
	{
		/** @brief Multi-Sample Anti-Aliasing.
		 * @note Slow */
		MSAA = 0,
		/** @brief SuperSampling Anti-Aliasing.
		 * @note Slow */
		SSAA = 1,
		/** @brief Temporal Approximate Anti-Aliasing
		 * @note Medium */
		TXAA = 2,
		/** @brief Fast Approximate Anti-Aliasing
		 * @note Fast */
		FXAA = 3,
		/** @brief Subpixel Morphological Anti-Aliasing
		 * @note Fast */
		SMAA = 4,
		/** @brief Temporal Anti-Aliasing
		 * @note Fast */
		TAA = 5
	};

	static constexpr auto MSAAString{"MSAA"};
	static constexpr auto SSAAString{"SSAA"};
	static constexpr auto TXAAString{"TXAA"};
	static constexpr auto FXAAString{"FXAA"};
	static constexpr auto SMAAString{"SMAA"};
	static constexpr auto TAAString{"TAA"};

	/**
	 * @brief Returns a C-String version of the enum value.
	 * @param type The enum value.
	 * @return const char *
	 */
	[[nodiscard]]
	const char * to_cstring (AntiAliasingType type) noexcept;

	/**
	 * @brief Returns a string version of the enum value.
	 * @param type The enum value.
	 * @return std::string
	 */
	[[nodiscard]]
	inline
	std::string
	to_string (AntiAliasingType type) noexcept
	{
		return {to_cstring(type)};
	}

	/**
	 * @brief Vertex color generation mode.
	 */
	enum class VertexColorGenMode : uint8_t
	{
		UseGlobal = 0,
		UseRandom = 1,
		GenerateFromCoords = 2
	};

	/**
	 * @brief Custom screen resolution.
	 */
	enum class ScreenResolutionCustom : uint8_t
	{
		/** @brief 352x288 (?:?). */
		CIF,
		/** @brief 480x320 (3:2) */
		HVGA,
		/** @brief 800x480 (5:3) */
		WVGA,
		/** @brief 1024x600 (?:?). */
		WSVGA,
		/** @brief 1280x768 (5:3) */
		WXGA,
		/** @brief 1280x1024 (5:4). */
		SXGA,
		/** @brief 1920x1920 (1:1) */
		SQFHD,
		/** @brief 2560x2048 (5:4). */
		QSXGA,
		/** @brief 3200x2048 (?:?). */
		WQSXGA
	};

	/**
	 * @brief Standard 4:3 screen resolution.
	 */
	enum class ScreenResolution4_3: uint8_t
	{
		/** @brief 320x240. */
		QVGA,
		/** @brief 384x288. */
		SIF,
		/** @brief 640x480. */
		VGA,
		/** @brief 768x576. */
		PAL,
		/** @brief 800x600. */
		SVGA,
		/** @brief 1024x768. */
		XGA,
		/** @brief 1152x864. */
		XGAPlus,
		/** @brief 1280x960. */
		QuadVGA,
		/** @brief 1400x1050. */
		SXGAPlus,
		/** @brief 1600x1200. */
		UXGA,
		/** @brief 2048x1536. */
		QXGA,
		/** @brief 3200x2400. */
		QUXGA
	};

	/**
	 * @brief Standard 16:10 screen resolution.
	 */
	enum class ScreenResolution16_10 : uint8_t
	{
		/** @brief 320x200. */
		CGA,
		/** @brief 1280x800. */
		WXGA,
		/** @brief 1440x900. */
		WXGAPlus,
		/** @brief 1680x1050. */
		WSXGAPlus,
		/** @brief 1920x1200. */
		WUXGA,
		/** @brief 2560x1600. */
		WQXGA,
		/** @brief 3840x2400. */
		WQUXGA
	};

	/**
	 * @brief Standard 16:9 screen resolution.
	 */
	enum class ScreenResolution16_9 : uint8_t
	{
		/** @brief 854x480 (NTSC, 480p) */
		FWVGA,
		/** @brief 720x480 (480p). */
		Standard,
		/** @brief 1024x576 (PAL, 576p) */
		WSVGA,
		/** @brief 1280x720 (HD Ready, 720p). */
		HD,
		/** @brief 1366x768. */
		FWXGA,
		/** @brief 1600x900. */
		WSXGA,
		/** @brief 1920x1080 (FullHD, 1080p). */
		FullHD,
		/** @brief 2560x1440. */
		WQHD,
		/** @brief 3840x2160 (UHD, 4K, 2160p). */
		UHD4K,
		/** @brief 5120x2880 (UHD, 4K, 2880p). */
		UHD5K,
		/** @brief 7680x4320 (UHD, 8K, 4320p). */
		UHD8K
	};

	/**
	 * @brief Standard 17:9 screen resolution.
	 */
	enum class ScreenResolution17_9 : uint8_t
	{
		/** @brief 2048x1080. */
		DCI2K,
		/** @brief 4096x2160. */
		DCI4K,
		/** @brief 8192x4320. */
		FullFormat8K
	};

	/**
	 * @brief Standard 21:9 (7:3) screen resolution.
	 */
	enum class ScreenResolution21_9 : uint8_t
	{
		/** @brief 2560x1080. */
		UWFHD,
		/** @brief 3440x1440. */
		UWQHD,
		/** @brief 5120x2160. */
		Ultrawide5K
	};
}
