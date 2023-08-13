/*
 * Libraries/VertexFactory/ShapeBuilderOptions.hpp
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
#include <array>
#include <type_traits>

/* Local inclusions for usages. */
#include "Math/Vector.hpp"
#include "PixelFactory/Color.hpp"

namespace Libraries::VertexFactory
{
	/**
	 * @brief The shape builder options.
	 * @tparam type_t The data precision
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	class ShapeBuilderOptions final
	{
		public:

			/**
			 * @brief Constructs a shape builder options structure.
			 */
			ShapeBuilderOptions () noexcept = default;

			/**
			 * @brief Use global vertex color.
			 * @note This will disable the vertex color automatic generation.
			 * @param color A reference to vector 4.
			 * @return void
			 */
			void
			enableGlobalVertexColor (const Math::Vector< 4, type_t > & color) noexcept
			{
				m_globalVertexColor = color;
				m_flags[GlobalVertexColorEnabled] = true;
				m_flags[GenerateVertexColors] = false;
			}

			/**
			 * @brief Use global vertex color.
			 * @note This will disable the vertex color automatic generation.
			 * @param color A reference to PixelFactory color.
			 * @return void
			 */
			void
			enableGlobalVertexColor (const PixelFactory::Color< float > & color) noexcept
			{
				this->enableGlobalVertexColor(color.toVector4< type_t >());
			}

			/**
			 * @brief Disables the use of a global vertex color.
			 * @return void
			 */
			void
			disableGlobalVertexColor () noexcept
			{
				m_flags[GlobalVertexColorEnabled] = false;
			}

			/**
			 * @brief Returns whether a global vertex color is in use.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isGlobalVertexColorEnabled () const noexcept
			{
				return m_flags[GlobalVertexColorEnabled];
			}

			/**
			 * @brief Returns the global vertex color.
			 * @return const Math::Vector< 4, type_t > &
			 */
			[[nodiscard]]
			const Math::Vector< 4, type_t > &
			globalVertexColor () const noexcept
			{
				return m_globalVertexColor;
			}

			/**
			 * @brief Uses a global normal vector.
			 * @note This will disable the global normal.
			 * @param normal A reference to a vector 3.
			 * @return void
			 */
			void
			enableGlobalNormal (const Math::Vector< 3, type_t > & normal) noexcept
			{
				m_globalNormal = normal;
				m_flags[GenerateNormals] = false;
				m_flags[GlobalNormalEnabled] = true;
			}

			/**
			 * @brief Disables the use of a global normal vector.
			 * @return void
			 */
			void
			disableGlobalNormal () noexcept
			{
				m_flags[GlobalNormalEnabled] = false;
			}

			/**
			 * @brief Returns whether a global vertex color is in use.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isGlobalNormalEnabled () const noexcept
			{
				return m_flags[GlobalNormalEnabled];
			}

			/**
			 * @brief Returns the global vertex color.
			 * @return const Math::Vector< 3, type_t > &
			 */
			[[nodiscard]]
			const Math::Vector< 3, type_t > &
			globalNormal () const noexcept
			{
				return m_globalNormal;
			}

			/**
			 * @brief Sets uniform texture coordinates state.
			 * @param state The state.
			 * @return void
			 */
			void
			setUniformTextureCoordinates (bool state) noexcept
			{
				m_flags[UniformTextureCoordinates] = state;
			}

			/**
			 * @brief Sets texture coordinates multipliers.
			 * @param xMultiplier The multiplication factor on the X axis.
			 * @param yMultiplier The multiplication factor on the Y axis. Default Same as X.
			 * @param zMultiplier The multiplication factor on the Z axis. Default Same as Z.
			 * @return void
			 */
			void
			setTextureCoordinatesMultiplier (type_t xMultiplier, type_t yMultiplier = 0, type_t zMultiplier = 0) noexcept
			{
				m_textureCoordinatesMultiplier[Math::X] = std::abs(xMultiplier);
				m_textureCoordinatesMultiplier[Math::Y] = Utility::isZero(yMultiplier) ? m_textureCoordinatesMultiplier[Math::X] : std::abs(yMultiplier);
				m_textureCoordinatesMultiplier[Math::Z] = Utility::isZero(zMultiplier) ? m_textureCoordinatesMultiplier[Math::X] : std::abs(zMultiplier);
			}

			/**
			 * @brief Sets texture coordinates multipliers.
			 * @param multiplier A reference to a vector.
			 * @return void
			 */
			void
			setTextureCoordinatesMultiplier (const Math::Vector< 2, type_t > & multiplier) noexcept
			{
				this->setTextureCoordinatesMultiplier(multiplier[Math::X], multiplier[Math::Y]);
			}

			/**
			 * @brief Sets texture coordinates multipliers.
			 * @param multiplier A reference to a vector.
			 * @return void
			 */
			void
			setTextureCoordinatesMultiplier (const Math::Vector< 3, type_t > & multiplier) noexcept
			{
				this->setTextureCoordinatesMultiplier(multiplier[Math::X], multiplier[Math::Y], multiplier[Math::Z]);
			}

			/**
			 * @brief Returns the texture coordinates multiplier.
			 * @return const Math::Vector< 3, type_t > &
			 */
			[[nodiscard]]
			const Math::Vector< 3, type_t > &
			textureCoordinatesMultiplier () const noexcept
			{
				return m_textureCoordinatesMultiplier;
			}

			/**
			 * @brief Enables the data economy.
			 * @param state The state.
			 * @return void
			 */
			void
			enableDataEconomy (bool state) noexcept
			{
				m_flags[DataEconomyEnabled] = state;
			}

			/**
			 * @brief Returns whether the data economy is enabled.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			dataEconomyEnabled () const noexcept
			{
				return m_flags[DataEconomyEnabled];
			}

			/**
			 * @brief Sets the center of the shape at bottom.
			 * @param state The state.
			 * @return void
			 */
			void
			setCenterAtBottom (bool state) noexcept
			{
				m_flags[CenterAtBottom] = state;
			}

			/**
			 * @brief Returns whether the geometry must be centered at bottom.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isCenteredAtBottom () const noexcept
			{
				return m_flags[CenterAtBottom];
			}

			/**
			 * @brief Enables or disables the vertex color automatic generation from position.
			 * @note This will disable the global vertex color.
			 * @param state The state.
			 * @return void
			 */
			void
			enableVertexColorGeneration (bool state) noexcept
			{
				if ( state )
					m_flags[GlobalVertexColorEnabled] = false;

				m_flags[GenerateVertexColors] = state;
			}

			/**
			 * @brief Returns whether the vertex color automatic generation is enabled.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isVertexColorGenerationEnabled () const noexcept
			{
				return m_flags[GenerateVertexColors];
			}

			/**
			 * @brief Enables or disables the normal generation from position.
			 * @note This will disable the global normal.
			 * @param state The state.
			 * @return void
			 */
			void
			enableNormalGeneration (bool state) noexcept
			{
				if ( state )
					m_flags[GlobalNormalEnabled] = false;

				m_flags[GenerateNormals] = state;
			}

			/**
			 * @brief Returns whether normal generation is enabled.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isNormalGenerationEnabled () const noexcept
			{
				return m_flags[GenerateNormals];
			}

			/**
			 * @brief Enables or disables the geometry flipping at the end of generation.
			 * @param state The state.
			 * @return void
			 */
			void
			enableGeometryFlipping (bool state) noexcept
			{
				m_flags[FlipGeometry] = state;
			}

			/**
			 * @brief Returns whether the geometry flipping is enabled.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isGeometryFlippingEnabled () const noexcept
			{
				return m_flags[FlipGeometry];
			}

			/**
			 * @brief Resets the construction.
			 * @return void
			 */
			void
			reset () noexcept
			{
				m_globalVertexColor = {0.5, 0.5, 0.5, 1};
				m_globalNormal.reset();
				m_textureCoordinatesMultiplier = {1, 1, 1};

				m_flags[GlobalVertexColorEnabled] = false;
				m_flags[GlobalNormalEnabled] = false;
				m_flags[DataEconomyEnabled] = true;
				m_flags[CenterAtBottom] = false;
				m_flags[UniformTextureCoordinates] = false;
				m_flags[GenerateVertexColors] = true;
				m_flags[GenerateNormals] = true;
				m_flags[FlipGeometry] = false;
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return ostream &
			 */
			friend
			std::ostream &
			operator<< (std::ostream & out, const ShapeBuilderOptions & obj)
			{
				using namespace std;

				return out <<
					"Shape builder options:" "\n"
					"Global vertex color enabled : " << ( obj.m_flags[GlobalVertexColorEnabled] ? "Yes" : "No" ) << "\n"
					"Global vertex color : " << obj.m_globalVertexColor << "\n"
					"Global normal enabled : " << ( obj.m_flags[GlobalNormalEnabled] ? "Yes" : "No" ) << "\n"
					"Global Normal vector : " << obj.m_globalNormal << "\n"
					"Data economy enabled : " << ( obj.m_flags[DataEconomyEnabled] ? "Yes" : "No" ) << "\n"
					"Center at bottom : " << ( obj.m_flags[CenterAtBottom] ? "Yes" : "No" ) << "\n"
					"Uniform texture coordinates : " << ( obj.m_flags[UniformTextureCoordinates] ? "Yes" : "No" ) << "\n"
					"Generate vertex colors : " << ( obj.m_flags[GenerateVertexColors] ? "Yes" : "No" ) << "\n"
					"Generate normals : " << ( obj.m_flags[GenerateNormals] ? "Yes" : "No" ) << "\n"
					"UVW multipliers : " << obj.m_textureCoordinatesMultiplier << "\n"
				;
			}

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend
			std::string
			to_string (const ShapeBuilderOptions & obj) noexcept
			{
				return (std::stringstream{} << obj).str();
			}

		private:

			/* Flag names. */
			static constexpr auto GlobalVertexColorEnabled = 0UL;
			static constexpr auto GlobalNormalEnabled = 1UL;
			static constexpr auto DataEconomyEnabled = 2UL;
			static constexpr auto CenterAtBottom = 3UL;
			static constexpr auto UniformTextureCoordinates = 4UL;
			static constexpr auto GenerateVertexColors = 5UL;
			static constexpr auto GenerateNormals = 6UL;
			static constexpr auto FlipGeometry = 7UL;

			Math::Vector< 4, type_t > m_globalVertexColor{0.5, 0.5, 0.5, 1};
			Math::Vector< 3, type_t > m_globalNormal{};
			Math::Vector< 3, type_t > m_textureCoordinatesMultiplier{1, 1, 1};
			std::array< bool, 8 > m_flags{
				false/*GlobalVertexColorEnabled*/,
				false/*GlobalNormalEnabled*/,
				true/*DataEconomyEnabled*/,
				false/*CenterAtBottom*/,
				false/*UniformTextureCoordinates*/,
				true/*GenerateVertexColors*/,
				true/*GenerateNormals*/,
				false/*FlipGeometry*/
			};
	};
}
