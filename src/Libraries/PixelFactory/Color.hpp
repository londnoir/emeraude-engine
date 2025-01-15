/*
 * src/Libraries/PixelFactory/Color.hpp
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

/* STL inclusions. */
#include <array>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <type_traits>

/* Local inclusions. */
#include "Libraries/Math/Base.hpp"
#include "Libraries/Math/Vector.hpp"
#include "Types.hpp"

namespace Libraries::PixelFactory
{
	/**
	 * @brief Defines a color which using an internal floating point data.
	 * @tparam float_t The type of floating point number. Default float.
	 */
	template< typename float_t = float >
	requires (std::is_floating_point_v< float_t >)
	class Color final
	{
		public:

			/** @brief Index accessor for red component. */
			static constexpr auto R{0UL};
			/** @brief Index accessor for green component. */
			static constexpr auto G{1UL};
			/** @brief Index accessor for blue component. */
			static constexpr auto B{2UL};
			/** @brief Index accessor for alpha component. */
			static constexpr auto A{3UL};

			/**
			 * @brief Constructs a default color (Black).
			 */
			constexpr Color () noexcept = default;

			/**
			 * @brief Constructs a color from float values.
			 * @param red Red component.
			 * @param green Green component.
			 * @param blue Blue component.
			 * @param alpha Alpha component. Default 1.0.
			 */
			constexpr
			Color (float_t red, float_t green, float_t blue, float_t alpha = 1) noexcept
				: m_components{Math::clampToUnit(red), Math::clampToUnit(green), Math::clampToUnit(blue), Math::clampToUnit(alpha)}
			{

			}

			/**
			 * @brief Constructs a color from a color and a new alpha component.
			 * @param color RGB component from another color.
			 * @param alpha Alpha component.
			 */
			constexpr
			Color (const Color & color, float_t alpha) noexcept
				: Color(color.m_components[R], color.m_components[G], color.m_components[B], Math::clampToUnit(alpha))
			{

			}

			/**
			 * @brief Constructs a color from a std::array
			 * @param data A reference to a static array containing the color component.
			 */
			constexpr
			explicit
			Color (const std::array< float_t, 4 > & data) noexcept
				: m_components(data)
			{

			}

			/**
			 * @brief Constructs a color from a std::array
			 * @param data A reference to a static array containing the color component.
			 */
			constexpr
			explicit
			Color (const std::array< float_t, 3 > & data) noexcept
				: Color(data[0], data[1], data[2])
			{

			}

			/**
			 * @brief Constructs a color from a vector 4.
			 * @param data A reference to a vector.
			 */
			constexpr
			explicit
			Color (const Math::Vector< 4, float_t > & data) noexcept
				: Color(data[Math::X], data[Math::Y], data[Math::Z], data[Math::W])
			{

			}

			/**
			 * @brief Constructs a color from a vector 3.
			 * @param data A reference to a vector.
			 */
			constexpr
			explicit
			Color (const Math::Vector< 3, float_t > & data) noexcept
				: Color(data[Math::X], data[Math::Y], data[Math::Z])
			{

			}

			/**
			 * @brief Performs an equality check.
			 * @param operand A reference to a color.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			operator== (const Color & operand) const noexcept
			{
				return
					Utility::equal(m_components[R], operand.m_components[R]) &&
					Utility::equal(m_components[G], operand.m_components[G]) &&
					Utility::equal(m_components[B], operand.m_components[B]) &&
					Utility::equal(m_components[A], operand.m_components[A]);
			}

			/**
			 * @brief Performs an inequality check.
			 * @param operand A reference to a color.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			operator!= (const Color & operand) const noexcept
			{
				return !this->operator==(operand);
			}

			/**
			 * @brief Performs an addition on color channels (RGB) and multiply alpha channel (A).
			 * @param operand A reference to a color.
			 * @return Color
			 */
			[[nodiscard]]
			Color
			operator+ (const Color & operand) const noexcept
			{
				return {
					Math::clampToUnit(m_components[R] + operand.m_components[R]),
					Math::clampToUnit(m_components[G] + operand.m_components[G]),
					Math::clampToUnit(m_components[B] + operand.m_components[B]),
					m_components[A] * operand.m_components[A]
				};
			}

			/**
			 * @brief Performs an addition on color channels (RGB) and multiply alpha channel (A).
			 * @param operand A reference to a color.
			 * @return Color &
			 */
			[[nodiscard]]
			Color &
			operator+= (const Color & operand) noexcept
			{
				/* Guard self assignment */
				if ( this != &operand )
				{
					m_components[R] = Math::clampToUnit(m_components[R] + operand.m_components[R]);
					m_components[G] = Math::clampToUnit(m_components[G] + operand.m_components[G]);
					m_components[B] = Math::clampToUnit(m_components[B] + operand.m_components[B]);
					m_components[A] = m_components[A] * operand.m_components[A];
				}

				return *this;
			}

			/**
			 * @brief Performs a subtraction on color channels (RGB) and multiply alpha channel (A).
			 * @param operand A reference to a color.
			 * @return Color
			 */
			[[nodiscard]]
			Color
			operator- (const Color & operand) const noexcept
			{
				return {
					Math::clampToUnit(m_components[R] - operand.m_components[R]),
					Math::clampToUnit(m_components[G] - operand.m_components[G]),
					Math::clampToUnit(m_components[B] - operand.m_components[B]),
					m_components[A] * operand.m_components[A]
				};
			}

			/**
			 * @brief Performs a subtraction on color channels (RGB) and multiply alpha channel (A).
			 * @param operand A reference to a color.
			 * @return Color &
			 */
			[[nodiscard]]
			Color &
			operator-= (const Color & operand) noexcept
			{
				/* Guard self assignment */
				if ( this != &operand )
				{
					m_components[R] = Math::clampToUnit(m_components[R] - operand.m_components[R]);
					m_components[G] = Math::clampToUnit(m_components[G] - operand.m_components[G]);
					m_components[B] = Math::clampToUnit(m_components[B] - operand.m_components[B]);
					m_components[A] = m_components[A] * operand.m_components[A];
				}

				return *this;
			}

			/**
			 * @brief Performs a multiplication on color channels (RGB) and multiply alpha channel (A).
			 * @param operand A reference to a color.
			 * @return Color
			 */
			[[nodiscard]]
			Color
			operator* (const Color & operand) const noexcept
			{
				return {
					m_components[R] * operand.m_components[R],
					m_components[G] * operand.m_components[G],
					m_components[B] * operand.m_components[B],
					m_components[A] * operand.m_components[A]
				};
			}

			/**
			 * @brief Performs a multiplication on color channels (RGB) and multiply alpha channel (A).
			 * @param operand A reference to a color.
			 * @return Color &
			 */
			[[nodiscard]]
			Color &
			operator*= (const Color & operand) noexcept
			{
				/* Guard self assignment */
				if ( this != &operand )
				{
					m_components[R] = m_components[R] * operand.m_components[R];
					m_components[G] = m_components[G] * operand.m_components[G];
					m_components[B] = m_components[B] * operand.m_components[B];
					m_components[A] = m_components[A] * operand.m_components[A];
				}

				return *this;
			}

			/**
			 * @brief Performs a division on color channels (RGB) and multiply alpha channel (A).
			 * @param operand A reference to a color.
			 * @return Color
			 */
			[[nodiscard]]
			Color
			operator/ (const Color & operand) const noexcept
			{
				return {
					operand.m_components[R] <= 0.0F ? 0.0F : m_components[R] / operand.m_components[R],
					operand.m_components[G] <= 0.0F ? 0.0F : m_components[G] / operand.m_components[G],
					operand.m_components[B] <= 0.0F ? 0.0F : m_components[B] / operand.m_components[B],
					m_components[A] * operand.m_components[A]
				};
			}

			/**
			 * @brief Performs a division on color channels (RGB) and multiply alpha channel (A).
			 * @param operand A reference to a color.
			 * @return Color &
			 */
			[[nodiscard]]
			Color &
			operator/= (const Color & operand) noexcept
			{
				/* Guard self assignment */
				if ( this != &operand )
				{
					m_components[R] = operand.m_components[R] <= 0.0F ? 0.0F : m_components[R] / operand.m_components[R];
					m_components[G] = operand.m_components[G] <= 0.0F ? 0.0F : m_components[G] / operand.m_components[G];
					m_components[B] = operand.m_components[B] <= 0.0F ? 0.0F : m_components[B] / operand.m_components[B];
					m_components[A] = m_components[A] * operand.m_components[A];
				}

				return *this;
			}

			/**
			 * @brief Adds a value to color channels (RGB).
			 * @param operand The value to add.
			 * @return Color
			 */
			[[nodiscard]]
			Color
			operator+ (float_t operand) const noexcept
			{
				return {
					Math::clampToUnit(m_components[R] + operand),
					Math::clampToUnit(m_components[G] + operand),
					Math::clampToUnit(m_components[B] + operand),
					m_components[A]
				};
			}

			/**
			 * @brief Adds a value to color channels (RGB).
			 * @param operand The value to add.
			 * @return Color &
			 */
			[[nodiscard]]
			Color &
			operator+= (float_t operand) noexcept
			{
				/* Guard self assignment */
				if ( this != &operand )
				{
					m_components[R] = Math::clampToUnit(m_components[R] + operand);
					m_components[G] = Math::clampToUnit(m_components[G] + operand);
					m_components[B] = Math::clampToUnit(m_components[B] + operand);
				}

				return *this;
			}

			/**
			 * @brief Subtracts a value from color channels (RGB).
			 * @param operand The value to subtract.
			 * @return Color
			 */
			[[nodiscard]]
			Color
			operator- (float_t operand) const noexcept
			{
				return {
					Math::clampToUnit(m_components[R] - operand),
					Math::clampToUnit(m_components[G] - operand),
					Math::clampToUnit(m_components[B] - operand),
					m_components[A]
				};
			}

			/**
			 * @brief Subtracts a value from color channels (RGB).
			 * @param operand The value to subtract.
			 * @return Color &
			 */
			[[nodiscard]]
			Color &
			operator-= (float_t operand) noexcept
			{
				/* Guard self assignment */
				if ( this != &operand )
				{
					m_components[R] = Math::clampToUnit(m_components[R] - operand);
					m_components[G] = Math::clampToUnit(m_components[G] - operand);
					m_components[B] = Math::clampToUnit(m_components[B] - operand);
				}

				return *this;
			}

			/**
			 * @brief Multiplies color channels (RGB) by a value.
			 * @param operand The value to multiply.
			 * @return Color
			 */
			[[nodiscard]]
			Color
			operator* (float_t operand) const noexcept
			{
				if ( operand < 0.0F && operand >= 1.0F )
				{
					return *this;
				}

				return {
					m_components[R] * operand,
					m_components[G] * operand,
					m_components[B] * operand,
					m_components[A]
				};
			}

			/**
			 * @brief Multiplies color channels (RGB) by a value.
			 * @param operand The value to multiply.
			 * @return Color &
			 */
			[[nodiscard]]
			Color &
			operator*= (float_t operand) noexcept
			{
				if ( operand >= 0.0F && operand < 1.0F )
				{
					m_components[R] = m_components[R] * operand;
					m_components[G] = m_components[G] * operand;
					m_components[B] = m_components[B] * operand;
				}

				return *this;
			}

			/**
			 * @brief Divides color channels (RGB) by a value.
			 * @param operand The value for the division.
			 * @return Color
			 */
			[[nodiscard]]
			Color
			operator/ (float_t operand) const noexcept
			{
				if ( operand <= 0.0F )
				{
					return *this;
				}

				return {
					m_components[R] / operand,
					m_components[G] / operand,
					m_components[B] / operand,
					m_components[A]
				};
			}

			/**
			 * @brief Divides color channels (RGB) by a value.
			 * @param operand The value for the division.
			 * @return Color &
			 */
			[[nodiscard]]
			Color &
			operator/= (float_t operand) noexcept
			{
				if ( !Utility::isZero(operand) )
				{
					m_components[R] = m_components[R] / operand;
					m_components[G] = m_components[G] / operand;
					m_components[B] = m_components[B] / operand;
				}
				else
				{
					std::cerr << __PRETTY_FUNCTION__ << ", division by zero !" "\n";
				}

				return *this;
			}

			/**
			 * @brief Returns color as a float vector 3.
			 * @tparam output_t The type of floating point number for vector data. Default float.
			 * @return Vector< 3, output_t >
			 */
			template< typename output_t = float >
			[[nodiscard]]
			Math::Vector< 3, output_t >
			toVector3 () const noexcept requires (std::is_floating_point_v< output_t >)
			{
				return {m_components[R], m_components[G], m_components[B]};
			}

			/**
			 * @brief Returns color as an integer vector 3.
			 * @tparam output_t The type of unsigned integer for vector data. Default uint8_t.
			 * @return Vector< 3, output_t >
			 */
			template< typename output_t = uint8_t >
			[[nodiscard]]
			Math::Vector< 3, output_t >
			toVector3 () const noexcept requires (std::is_integral_v< output_t >)
			{
				return {
					this->redInteger< output_t >(),
					this->greenInteger< output_t >(),
					this->blueInteger< output_t >()
				};
			}

			/**
			 * @brief Returns color as a float vector 4.
			 * @tparam output_t The type of floating point number for vector data. Default float.
			 * @return Vector< 4, output_t >
			 */
			template< typename output_t = float >
			[[nodiscard]]
			Math::Vector< 4, output_t >
			toVector4 () const noexcept requires (std::is_floating_point_v< output_t >)
			{
				return {m_components[R], m_components[G], m_components[B], m_components[A]};
			}

			/**
			 * @brief Returns color as an integer vector 4.
			 * @tparam output_t The type of unsigned integer for vector data. Default float.
			 * @return Vector< 4, output_t >
			 */
			template< typename output_t = uint8_t >
			[[nodiscard]]
			Math::Vector< 4, output_t >
			toVector3 () const noexcept requires (std::is_integral_v< output_t >)
			{
				return {
					this->redInteger< output_t >(),
					this->greenInteger< output_t >(),
					this->blueInteger< output_t >(),
					this->alphaInteger< output_t >()
				};
			}

			/**
			 * @brief Sets the red component.
			 * @param value The component value.
			 * @return void
			 */
			void
			setRed (float_t value) noexcept
			{
				m_components[R] = Math::clampToUnit(value);
			}

			/**
			 * @brief Sets the red component.
			 * @tparam input_t The type of unsigned integer data. Default uint8_t.
			 * @param value The component value.
			 * @return void
			 */
			template< typename input_t = uint8_t >
			void
			setRed (input_t value) noexcept requires (std::is_integral_v< input_t >)
			{
				m_components[R] = static_cast< float_t >(value) / std::numeric_limits< input_t >::max();
			}

			/**
			 * @brief Sets the green component.
			 * @param value The component value.
			 * @return void
			 */
			void
			setGreen (float_t value) noexcept
			{
				m_components[G] = Math::clampToUnit(value);
			}

			/**
			 * @brief Sets the green component.
			 * @tparam input_t The type of unsigned integer data. Default uint8_t.
			 * @param value The component value.
			 * @return void
			 */
			template< typename input_t = uint8_t >
			void
			setGreen (input_t value) noexcept requires (std::is_integral_v< input_t >)
			{
				m_components[G] = static_cast< float_t >(value) / std::numeric_limits< input_t >::max();
			}

			/**
			 * @brief Sets the blue component.
			 * @param value The component value.
			 * @return void
			 */
			void
			setBlue (float_t value) noexcept
			{
				m_components[B] = Math::clampToUnit(value);
			}

			/**
			 * @brief Sets the blue component.
			 * @tparam input_t The type of unsigned integer data. Default uint8_t.
			 * @param value The component value.
			 * @return void
			 */
			template< typename input_t = uint8_t >
			void
			setBlue (input_t value) noexcept requires (std::is_integral_v< input_t >)
			{
				m_components[B] = static_cast< float_t >(value) / std::numeric_limits< input_t >::max();
			}

			/**
			 * @brief Sets the alpha component.
			 * @param value The component value.
			 * @return void
			 */
			void
			setAlpha (float_t value) noexcept
			{
				m_components[A] = Math::clampToUnit(value);
			}

			/**
			 * @brief Sets the alpha component.
			 * @tparam input_t The type of unsigned integer data. Default uint8_t.
			 * @param value The component value.
			 * @return void
			 */
			template< typename input_t = uint8_t >
			void
			setAlpha (input_t value) noexcept requires (std::is_integral_v< input_t >)
			{
				m_components[A] = static_cast< float_t >(value) / std::numeric_limits< input_t >::max();
			}

			/**
			 * @brief Sets RGB components at once.
			 * @param redValue The red component value.
			 * @param greenValue The blue component value.
			 * @param blueValue The green component value.
			 * @return void
			 */
			void
			setRGB (float_t redValue, float_t greenValue, float_t blueValue) noexcept
			{
				m_components[R] = Math::clampToUnit(redValue);
				m_components[G] = Math::clampToUnit(greenValue);
				m_components[B] = Math::clampToUnit(blueValue);
			}

			/**
			 * @brief Sets RGB components at once.
			 * @tparam input_t The type of unsigned integer data. Default uint8_t.
			 * @param redValue The red component value.
			 * @param greenValue The blue component value.
			 * @param blueValue The green component value.
			 * @return void
			 */
			template< typename input_t = uint8_t >
			void
			setRGB (input_t redValue, input_t greenValue, input_t blueValue) noexcept requires (std::is_integral_v< input_t >)
			{
				m_components[R] = static_cast< float_t >(redValue) / std::numeric_limits< input_t >::max();
				m_components[G] = static_cast< float_t >(greenValue) / std::numeric_limits< input_t >::max();
				m_components[B] = static_cast< float_t >(blueValue) / std::numeric_limits< input_t >::max();
			}

			/**
			 * @brief Sets RGBA components at once.
			 * @param redValue The red component value.
			 * @param greenValue The blue component value.
			 * @param blueValue The green component value.
			 * @param alphaValue The alpha component value.
			 * @return void
			 */
			void
			setRGBA (float_t redValue, float_t greenValue, float_t blueValue, float_t alphaValue) noexcept
			{
				m_components[R] = Math::clampToUnit(redValue);
				m_components[G] = Math::clampToUnit(greenValue);
				m_components[B] = Math::clampToUnit(blueValue);
				m_components[A] = Math::clampToUnit(alphaValue);
			}

			/**
			 * @brief Sets RGBA components at once.
			 * @tparam input_t The type of unsigned integer data. Default uint8_t.
			 * @param redValue The red component value.
			 * @param greenValue The blue component value.
			 * @param blueValue The green component value.
			 * @param alphaValue The alpha component value.
			 * @return void
			 */
			template< typename input_t = uint8_t >
			void
			setRGBA (input_t redValue, input_t greenValue, input_t blueValue, input_t alphaValue) noexcept requires (std::is_integral_v< input_t >)
			{
				m_components[R] = static_cast< float_t >(redValue) / std::numeric_limits< input_t >::max();
				m_components[G] = static_cast< float_t >(greenValue) / std::numeric_limits< input_t >::max();
				m_components[B] = static_cast< float_t >(blueValue) / std::numeric_limits< input_t >::max();
				m_components[A] = static_cast< float_t >(alphaValue) / std::numeric_limits< input_t >::max();
			}

			/**
			 * @brief Sets the color hue from HSV model.
			 * @param degree The angle of color. The angle will be rounded to 360.
			 * @return void
			 */
			void
			setHue (float_t degree) noexcept
			{
				this->updateFromHSV(std::fmod(degree, 360.0F), this->saturation(), this->value());
			}

			/**
			 * @brief Sets the color hue from HSV model.
			 * @param degree The angle of color. The angle will be rounded to 360.
			 * @return void
			 */
			void
			setHue (unsigned int degree) noexcept
			{
				this->updateFromHSV(degree % 360U, this->saturation(), this->value());
			}

			/**
			 * @brief Sets the saturation value from HSV model.
			 * @param saturation The color saturation. Will be clamped between 0 and 100.
			 * @return void
			 */
			void
			setSaturation (float_t saturation) noexcept
			{
				this->updateFromHSV(this->hue(), Math::clamp(saturation, 0.0F, 100.0F), this->value());
			}

			/**
			 * @brief Sets the saturation value from HSV model.
			 * @param saturation The color saturation. Will be clamped between 0 and 100.
			 * @return void
			 */
			void
			setSaturation (unsigned int saturation) noexcept
			{
				if ( saturation > 100 )
				{
					this->updateFromHSV(this->hue(), 100.0F, this->value());
				}
				else
				{
					this->updateFromHSV(this->hue(), static_cast< float_t >(saturation), this->value());
				}
			}

			/**
			 * @brief Sets the color value from HSV model.
			 * @param value The color value. Will be clamped between 0 and 100.
			 * @return void
			 */
			void
			setValue (float_t value) noexcept
			{
				this->updateFromHSV(this->hue(), this->saturation(), Math::clamp(value, 0.0F, 100.0F));
			}

			/**
			 * @brief Sets the color value from HSV model.
			 * @param value The color value. Will be clamped between 0 and 100.
			 * @return void
			 */
			void
			setValue (unsigned int value) noexcept
			{
				if ( value > 100 )
				{
					this->updateFromHSV(this->hue(), this->saturation(), 100.0F);
				}
				else
				{
					this->updateFromHSV(this->hue(), this->saturation(), static_cast< float_t >(value));
				}
			}

			/**
			 * @brief Returns the raw data.
			 * @return const data_t *
			 */
			[[nodiscard]]
			const float_t *
			data () const noexcept
			{
				return m_components.data();
			}

			/**
			 * @brief Returns the value of the red component.
			 * @return float_t
			 */
			[[nodiscard]]
			float_t
			red () const noexcept
			{
				return m_components[R];
			}

			/**
			 * @brief Returns the value of the red component multiplied by alpha.
			 * @return float_t
			 */
			[[nodiscard]]
			float_t
			redA () const noexcept
			{
				return m_components[R] * m_components[A];
			}

			/**
			 * @brief Returns the value of the red component in an unsigned integer type.
			 * @tparam output_t The type of unsigned integer data. Default uint8_t.
			 * @return output_t
			 */
			template< typename output_t = uint8_t >
			[[nodiscard]]
			output_t
			redInteger () const noexcept requires (std::is_integral_v< output_t >)
			{
				return this->convertFloatToInteger< output_t >(this->red());
			}

			/**
			 * @brief Returns the value of the red component multiplied by alpha in an unsigned integer type.
			 * @tparam output_t The type of unsigned integer data. Default uint8_t.
			 * @return output_t
			 */
			template< typename output_t = uint8_t >
			[[nodiscard]]
			output_t
			redAInteger () const noexcept requires (std::is_integral_v< output_t >)
			{
				return this->convertFloatToInteger< output_t >(this->redA());
			}

			/**
			 * @brief Returns the value of the green component.
			 * @return float_t
			 */
			[[nodiscard]]
			float_t
			green () const noexcept
			{
				return m_components[G];
			}

			/**
			 * @brief Returns the value of the green component multiplied by alpha.
			 * @return float_t
			 */
			[[nodiscard]]
			float_t
			greenA () const noexcept
			{
				return m_components[G] * m_components[A];
			}

			/**
			 * @brief Returns the value of the green component in an unsigned integer type.
			 * @tparam output_t The type of unsigned integer data. Default uint8_t.
			 * @return output_t
			 */
			template< typename output_t = uint8_t >
			[[nodiscard]]
			output_t
			greenInteger () const noexcept requires (std::is_integral_v< output_t >)
			{
				return this->convertFloatToInteger< output_t >(this->green());
			}

			/**
			 * @brief Returns the value of the green component multiplied by alpha in an unsigned integer type.
			 * @tparam output_t The type of unsigned integer data. Default uint8_t.
			 * @return output_t
			 */
			template< typename output_t = uint8_t >
			[[nodiscard]]
			output_t
			greenAInteger () const noexcept requires (std::is_integral_v< output_t >)
			{
				return this->convertFloatToInteger< output_t >(this->greenA());
			}

			/**
			 * @brief Returns the value of the blue component.
			 * @return float_t
			 */
			[[nodiscard]]
			float_t
			blue () const noexcept
			{
				return m_components[B];
			}

			/**
			 * @brief Returns the value of the blue component multiplied by alpha.
			 * @return float_t
			 */
			[[nodiscard]]
			float_t
			blueA () const noexcept
			{
				return m_components[B] * m_components[A];
			}

			/**
			 * @brief Returns the value of the blue component in an unsigned integer type.
			 * @tparam output_t The type of unsigned integer data. Default uint8_t.
			 * @return output_t
			 */
			template< typename output_t = uint8_t >
			[[nodiscard]]
			output_t
			blueInteger () const noexcept requires (std::is_integral_v< output_t >)
			{
				return this->convertFloatToInteger< output_t >(this->blue());
			}

			/**
			 * @brief Returns the value of the blue component multiplied by alpha in an unsigned integer type.
			 * @tparam output_t The type of unsigned integer data. Default uint8_t.
			 * @return output_t
			 */
			template< typename output_t = uint8_t >
			[[nodiscard]]
			output_t
			blueAInteger () const noexcept requires (std::is_integral_v< output_t >)
			{
				return this->convertFloatToInteger< output_t >(this->blueA());
			}

			/**
			 * @brief Returns the alpha component.
			 * @return float_t
			 */
			[[nodiscard]]
			float_t
			alpha () const noexcept
			{
				return m_components[A];
			}

			/**
			 * @brief Returns the value of the alpha component in an unsigned integer type.
			 * @tparam output_t The type of unsigned integer data. Default uint8_t.
			 * @return output_t
			 */
			template< typename output_t = uint8_t >
			[[nodiscard]]
			output_t
			alphaInteger () const noexcept requires (std::is_integral_v< output_t >)
			{
				return this->convertFloatToInteger< output_t >(this->alpha());
			}

			/**
			 * @brief Returns the average RGB as gray component.
			 * @return float_t
			 */
			[[nodiscard]]
			float_t
			gray () const noexcept
			{
				return (m_components[R] + m_components[G] + m_components[B]) / 3.0F;
			}

			/**
			 * @brief Returns the average RGB as gray component in an unsigned integer type.
			 * @tparam output_t The type of unsigned integer data. Default uint8_t.
			 * @return output_t
			 */
			template< typename output_t = uint8_t >
			[[nodiscard]]
			output_t
			grayInteger () const noexcept requires (std::is_integral_v< output_t >)
			{
				return this->convertFloatToInteger< output_t >(this->gray());
			}

			/**
			 * @brief Returns the RGB luminance.
			 * @param mode The conversion mode. Default LumaRec709.
			 * @param option Additional parameter for specific mode. Default 0.
			 * @return float_t
			 */
			[[nodiscard]]
			float_t
			luminance (GrayscaleConversionMode mode = GrayscaleConversionMode::LumaRec709, int option = 0) const noexcept
			{
				return Color::computeLuminance(m_components[R], m_components[G], m_components[B], mode, option);
			}

			/**
			 * @brief Returns the RGB luminance in an unsigned integer type.
			 * @tparam output_t The type of unsigned integer data. Default uint8_t.
			 * @param mode The conversion mode. Default LumaRec709.
			 * @param option Additional parameter for specific mode. Default 0.
			 * @return output_t
			 */
			template< typename output_t = uint8_t >
			[[nodiscard]]
			output_t
			luminanceInteger (GrayscaleConversionMode mode = GrayscaleConversionMode::LumaRec709, int option = 0) const noexcept requires (std::is_integral_v< output_t >)
			{
				return this->convertFloatToInteger< output_t >(this->luminance(mode, option));
			}

			/**
			 * @brief Returns the color hue [0-360] from HSV model.
			 * @return float_t
			 */
			[[nodiscard]]
			float_t
			hue () const noexcept
			{
				/* Minimum intensity over color component. */
				const auto min = std::min(m_components[R], std::min(m_components[G], m_components[B]));

				/* Max intensity over color component. */
				const auto max = std::max(m_components[R], std::max(m_components[G], m_components[B]));

				/* Compute the hue component */
				if ( Utility::equal(max, min) )
				{
					return 240.0F;
				}

				/* Intensity difference. */
				const auto delta = max - min;

				auto hue = 0.0F;

				/* Between yellow & magenta */
				if ( Utility::equal(max, m_components[R]) )
				{
					hue = (m_components[G] - m_components[B]) / delta;
				}
				/* Between cyan & yellow */
				else if ( Utility::equal(max, m_components[G]) )
				{
					hue = 2.0F + (m_components[B] - m_components[R]) / delta;
				}
				/* Between magenta & cyan */
				else if ( Utility::equal(max, m_components[B]) )
				{
					hue = 4.0F + (m_components[R] - m_components[G]) / delta;
				}

				hue *= 60.0F;

				/* Clamp to 0-360 */
				if ( hue < 0.0F )
				{
					hue += 360.0F;
				}
				else if ( hue > 360.0F )
				{
					hue -= 360.0F;
				}

				return hue;
			}

			/**
			 * @brief Returns the color saturation [0-100] from HSV model.
			 * @return float_t
			 */
			[[nodiscard]]
			float_t
			saturation () const noexcept
			{
				/* Minimum intensity over color component. */
				const auto min = std::min(m_components[R], std::min(m_components[G], m_components[B]));

				/* Max intensity over color component. */
				const auto max = std::max(m_components[R], std::max(m_components[G], m_components[B]));

				/* Intensity difference. */
				const auto delta = max - min;

				/* Compute the saturation component. */
				return Utility::isZero(max) ? 0.0F : (delta / max) * 100.0F;
			}

			/**
			 * @brief Returns the color value [0-100] from HSV model.
			 * @return float_t
			 */
			[[nodiscard]]
			float_t
			value () const noexcept
			{
				/* Compute the value component. */
				return std::max(m_components[R], std::max(m_components[G], m_components[B])) * 100.0F;
			}

			/**
			 * @brief Returns the luminance of a color.
			 * @param red The value of red component.
			 * @param green The value of green component.
			 * @param blue The value of blue component.
			 * @param mode The conversion mode. Default LumaRec709.
			 * @param option Additional parameter for specific mode. Default 0.
			 * @return float_t
			 */
			[[nodiscard]]
			static
			float_t
			computeLuminance (float_t red, float_t green, float_t blue, GrayscaleConversionMode mode = GrayscaleConversionMode::LumaRec709, int option = 0) noexcept
			{
				switch ( mode )
				{
					case GrayscaleConversionMode::Average :
						return (red + blue + green) / 3.0F;

					case GrayscaleConversionMode::LumaRec601_1 :
						return (red * LuminanceRec6011Red) + (green * LuminanceRec6011Green) + (blue * LuminanceRec6011Blue);

					case GrayscaleConversionMode::LumaRec709 :
						return (red * LuminanceRec709Red) + (green * LuminanceRec709Green) + (blue * LuminanceRec709Blue);

					case GrayscaleConversionMode::LumaITU :
						return (red * LuminanceITURed) + (green * LuminanceITUGreen) + (blue * LuminanceITUBlue);

					case GrayscaleConversionMode::Desaturation :
						return (std::max({red, green, blue}) + std::min({red, green, blue})) * 0.5F;

					case GrayscaleConversionMode::Decomposition :
						if ( option > 0 )
						{
							return std::max({red, green, blue});
						}

						return std::min({red, green, blue});

					case GrayscaleConversionMode::SingleChannel :
						switch ( option )
						{
							case 0 :
								return red;

							case 1 :
								return green;

							default :
								return blue;
						}

					case GrayscaleConversionMode::ShadesScale :
					{
						const auto average = (red + blue + green) / 3.0F;
						const auto range = static_cast< float_t >(option);

						return std::round(average / range) * range;
					}
				}

				return 0.0F;
			}

			/**
			 * @brief Returns the alpha blending between two colors.
			 * @param colorA A reference to a color for operand A.
			 * @param colorB A reference to a color for operand B.
			 * @param premultipliedAlpha Default false.
			 * @return data_t
			 */
			[[nodiscard]]
			static
			float_t
			alphaBlending (const Color & colorA, const Color & colorB, bool premultipliedAlpha = false)
			{
				if ( premultipliedAlpha )
				{
					return colorA.alpha() + colorB.alpha() - colorA.alpha() * colorB.alpha();
				}

				return colorA.alpha() * colorB.alpha();
			}

			/**
			 * @brief Performs a screen blending between two colors.
			 * @note Formula : f(a, b) = {1 - (1 - a) * (1 - b)}
			 * @param colorA A reference to a color for operand A.
			 * @param colorB A reference to a color for operand B.
			 * @param premultipliedAlpha Get alpha from a and b. Default false.
			 * @return Color
			 */
			[[nodiscard]]
			static
			Color
			screenBlending (const Color & colorA, const Color & colorB, bool premultipliedAlpha = false)
			{
				return {
					static_cast< float_t >(1) - (static_cast< float_t >(1) - colorA.red()) * (static_cast< float_t >(1) - colorB.red()),
					static_cast< float_t >(1) - (static_cast< float_t >(1) - colorA.green()) * (static_cast< float_t >(1) - colorB.green()),
					static_cast< float_t >(1) - (static_cast< float_t >(1) - colorA.blue()) * (static_cast< float_t >(1) - colorB.blue()),
					Color::alphaBlending(colorA, colorB, premultipliedAlpha)
				};
			}

			/**
			 * @brief Perform a screen blending between two colors.
			 * @note Formula : f(a, b) = (a < 0.5) ? {2 * a * b} OR {1 - 2 * (1 - a) * (1 - b)}
			 * @param colorA A reference to a color for operand A.
			 * @param colorB A reference to a color for operand B.
			 * @param premultipliedAlpha Get alpha from a and b. Default false.
			 * @return Color
			 */
			[[nodiscard]]
			static
			Color
			overlayBlending (const Color & colorA, const Color & colorB, bool premultipliedAlpha = false)
			{
				return {
					colorA.red() < static_cast< float_t >(0.5) ?
						static_cast< float_t >(2) * colorA.red() * colorB.red() :
						static_cast< float_t >(1) - static_cast< float_t >(2) * (static_cast< float_t >(1) - colorA.red()) * (static_cast< float_t >(1) - colorB.red()),
					colorA.green() < static_cast< float_t >(0.5) ?
						static_cast< float_t >(2) * colorA.green() * colorB.green() :
						static_cast< float_t >(1) - static_cast< float_t >(2) * (static_cast< float_t >(1) - colorA.green()) * (static_cast< float_t >(1) - colorB.green()),
					colorA.blue() < static_cast< float_t >(0.5) ?
						static_cast< float_t >(2) * colorA.blue() * colorB.blue() :
						static_cast< float_t >(1) - static_cast< float_t >(2) * (static_cast< float_t >(1) - colorA.blue()) * (static_cast< float_t >(1) - colorB.blue()),
					Color::alphaBlending(colorA, colorB, premultipliedAlpha)
				};
			}

			/**
			 * @brief Returns the differences between two colors.
			 * @note Formula : f(a, b) = max(a, b) - min(a, b)
			 * @param colorA A reference to a color for operand A.
			 * @param colorB A reference to a color for operand B.
			 * @param premultipliedAlpha Get alpha from a and b. Default false.
			 * @return Color
			 */
			[[nodiscard]]
			static
			Color
			difference (const Color & colorA, const Color & colorB, bool premultipliedAlpha = false)
			{
				return {
					std::max(colorA.red(), colorB.red()) - std::min(colorA.red(), colorB.red()),
					std::max(colorA.green(), colorB.green()) - std::min(colorA.green(), colorB.green()),
					std::max(colorA.blue(), colorB.blue()) - std::min(colorA.blue(), colorB.blue()),
					Color::alphaBlending(colorA, colorB, premultipliedAlpha)
				};
			}

			/**
			 * @brief Returns the darker components of two colors.
			 * @note Formula : f(a, b) = min(a, b)
			 * @param colorA A reference to a color for operand A.
			 * @param colorB A reference to a color for operand B.
			 * @param premultipliedAlpha Get alpha from a and b. Default false.
			 * @return Color
			 */
			[[nodiscard]]
			static
			Color
			darken (const Color & colorA, const Color & colorB, bool premultipliedAlpha = false)
			{
				return {
					std::min(colorA.red(), colorB.red()),
					std::min(colorA.green(), colorB.green()),
					std::min(colorA.blue(), colorB.blue()),
					Color::alphaBlending(colorA, colorB, premultipliedAlpha)
				};
			}

			/**
			 * @brief Returns the lighter components of two colors.
			 * @note Formula : f(a, b) = max(a, b)
			 * @param colorA A reference to a color for operand A.
			 * @param colorB A reference to a color for operand B.
			 * @param premultipliedAlpha Get alpha from a and b. Default false.
			 * @return Color
			 */
			[[nodiscard]]
			static
			Color
			lighten (const Color & colorA, const Color & colorB, bool premultipliedAlpha = false)
			{
				return {
					std::max(colorA.red(), colorB.red()),
					std::max(colorA.green(), colorB.green()),
					std::max(colorA.blue(), colorB.blue()),
					Color::alphaBlending(colorA, colorB, premultipliedAlpha)
				};
			}

			/**
			 * @brief Perform a blend operation between two colors.
			 * @param colorA A reference to a color for operand A.
			 * @param colorB A reference to a color for operand B.
			 * @param mode The blend technics.
			 * @param opacity Additional blending for color B. Default 1.
			 * @return Color
			 */
			[[nodiscard]]
			static
			Color
			blend (const Color & colorA, const Color & colorB, DrawPixelMode mode, float_t opacity = 1) noexcept
			{
				switch ( mode )
				{
					case DrawPixelMode::Replace :
						return colorB;

					case DrawPixelMode::Normal :
						return Color::linearInterpolation(colorA, colorB, colorB.alpha() * opacity);

					case DrawPixelMode::Addition :
						return Color::linearInterpolation(colorA, colorA + colorB, colorB.alpha() * opacity);

					case DrawPixelMode::Subtract :
						return Color::linearInterpolation(colorA, colorA - colorB, colorB.alpha() * opacity);

					case DrawPixelMode::Multiply :
						return Color::linearInterpolation(colorA, colorA * colorB, colorB.alpha() * opacity);

					case DrawPixelMode::Divide :
						return Color::linearInterpolation(colorA, colorA / colorB, colorB.alpha() * opacity);

					case DrawPixelMode::Screen :
						return Color::linearInterpolation(colorA, Color::screenBlending(colorA, colorB), colorB.alpha() * opacity);

					case DrawPixelMode::Overlay :
						return Color::linearInterpolation(colorA, Color::overlayBlending(colorA, colorB), colorB.alpha() * opacity);

					case DrawPixelMode::Difference :
						return Color::linearInterpolation(colorA, Color::difference(colorA, colorB), colorB.alpha() * opacity);

					case DrawPixelMode::Darken :
						return Color::linearInterpolation(colorA, Color::darken(colorA, colorB), colorB.alpha() * opacity);

					case DrawPixelMode::Lighten :
						return Color::linearInterpolation(colorA, Color::lighten(colorA, colorB), colorB.alpha() * opacity);
				}

				return colorA;
			}

			/**
			 * @brief Returns a random color.
			 * @note This version use the C rand() function.
			 * @param min The minimum value for the RGB component.
			 * @param max The maximum value for the RGB component.
			 * @return Color
			 */
			[[nodiscard]]
			static
			Color
			quickRandom (float_t min = 0, float_t max = 1) noexcept
			{
				min = Math::clampToUnit(min);
				max = Math::clampToUnit(max);

				return {
					Utility::quickRandom(min, max),
					Utility::quickRandom(min, max),
					Utility::quickRandom(min, max),
					static_cast< float_t >(1)
				};
			}

			/**
			 * @brief Returns a random color.
			 * @param min The minimum value for the RGB component.
			 * @param max The maximum value for the RGB component.
			 * @return Color
			 */
			[[nodiscard]]
			static
			Color
			random (float_t min = 0, float_t max = 1) noexcept
			{
				min = Math::clampToUnit(min);
				max = Math::clampToUnit(max);

				return {
					Utility::random(min, max),
					Utility::random(min, max),
					Utility::random(min, max),
					static_cast< float_t >(1)
				};
			}

			/**
			 * @brief Performs a linear interpolation between two colors.
			 * @param colorA A reference to color for operand A.
			 * @param colorB A reference to color for operand B.
			 * @param factor The  interpolation factor.
			 * @return Color
			 */
			[[nodiscard]]
			static
			Color
			linearInterpolation (const Color & colorA, const Color & colorB, float_t factor) noexcept
			{
				if ( &colorA == &colorB )
				{
					return colorA;
				}

				return {
					Math::linearInterpolation(colorA.m_components[R], colorB.m_components[R], factor),
					Math::linearInterpolation(colorA.m_components[G], colorB.m_components[G], factor),
					Math::linearInterpolation(colorA.m_components[B], colorB.m_components[B], factor),
					Math::linearInterpolation(colorA.m_components[A], colorB.m_components[A], factor)
				};
			}

			/**
			 * @brief Performs a cosine interpolation between two colors.
			 * @param colorA A reference to color for operand A.
			 * @param colorB A reference to color for operand B.
			 * @param factor The  interpolation factor.
			 * @return Color
			 */
			[[nodiscard]]
			static
			Color
			cosineInterpolation (const Color & colorA, const Color & colorB, float_t factor) noexcept
			{
				if ( &colorA == &colorB )
				{
					return colorA;
				}

				return {
					Math::cosineInterpolation(colorA.m_components[R], colorB.m_components[R], factor),
					Math::cosineInterpolation(colorA.m_components[G], colorB.m_components[G], factor),
					Math::cosineInterpolation(colorA.m_components[B], colorB.m_components[B], factor),
					Math::cosineInterpolation(colorA.m_components[A], colorB.m_components[A], factor)
				};
			}

			/**
			 * @brief Performs a bi-linear interpolation between two colors.
			 * @param bottomLeft
			 * @param bottomRight
			 * @param topLeft
			 * @param topRight
			 * @param factorX
			 * @param factorY
			 * @return Color
			 */
			[[nodiscard]]
			static
			Color
			bilinearInterpolation (const Color & bottomLeft, const Color & bottomRight, const Color & topLeft, const Color & topRight, float_t factorX, float_t factorY) noexcept
			{
				return Color::linearInterpolation(
					Color::linearInterpolation(bottomLeft, bottomRight, factorX),
					Color::linearInterpolation(topLeft, topRight, factorX),
					factorY
				);
			}

			/**
			 * @brief Performs a bi-cosine interpolation between two colors.
			 * @param bottomLeft
			 * @param bottomRight
			 * @param topLeft
			 * @param topRight
			 * @param factorX
			 * @param factorY
			 * @return Color
			 */
			[[nodiscard]]
			static
			Color
			bicosineInterpolation (const Color & bottomLeft, const Color & bottomRight, const Color & topLeft, const Color & topRight, float_t factorX, float_t factorY) noexcept
			{
				return Color::cosineInterpolation(
					Color::cosineInterpolation(bottomLeft, bottomRight, factorX),
					Color::cosineInterpolation(topLeft, topRight, factorX),
					factorY
				);
			}

			/**
			 * @brief Copies the vector data inside a C-Array of float.
			 * @warning  The target must provide enough space.
			 * @param target The array target to fill the color.
			 * @return void
			 */
			void
			copy (float_t * target) const noexcept
			{
				target[0] = m_components[R];
				target[1] = m_components[G];
				target[2] = m_components[B];
				target[3] = m_components[A];
			}

			/**
			 * @brief Generates a GLSL compatible "vec3(r, g, b)" string representation of the color.
			 * @return std::string
			 */
			[[nodiscard]]
			std::string
			asGLSLVec3String () const noexcept
			{
				return (std::stringstream{} << "vec3(" << m_components[R] << ", " << m_components[G] << ", " << m_components[B] << ")").str();
			}

			/**
			 * @brief Generates a GLSL compatible "vec4(r, g, b, a)" string representation of the color.
			 * @return std::string
			 */
			[[nodiscard]]
			std::string
			asGLSLVec4String () const noexcept
			{
				return (std::stringstream{} << "vec4(" << m_components[R] << ", " << m_components[G] << ", " << m_components[B] << ", " << m_components[A] << ")").str();
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param color A reference to the object to print.
			 * @return std::ostream &
			 */
			friend
			std::ostream &
			operator<< (std::ostream & out, const Color & color)
			{
				using namespace std;

				return out << "Color(" << fixed << setprecision(4) << setw(6) << color.m_components[0] << ", " << setw(6) << color.m_components[1] << ", " << setw(6) << color.m_components[2] << ", " << setw(6) << color.m_components[3] << ')';
			}

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend
			std::string
			to_string (const Color & obj) noexcept
			{
				std::stringstream output;

				output << obj;

				return output.str();
			}

		private:

			/**
			 * @brief Converts float to integer component value.
			 * @tparam integer_t The integer type desired.
			 * @param value The value to convert.
			 * @return integer_t
			 */
			template< typename integer_t >
			integer_t
			convertFloatToInteger (float_t value) const noexcept
			{
				/* Internal type is 'float' */
				if constexpr ( sizeof(float_t) == 4 )
				{
					if constexpr ( sizeof(integer_t) == 8 )
					{
						return static_cast< integer_t >(static_cast< long double >(value) * std::numeric_limits<integer_t>::max());
					}
					else if constexpr ( sizeof(integer_t) == 4 )
					{
						return static_cast< integer_t >(static_cast< double >(value) * std::numeric_limits<integer_t>::max());
					}
					else
					{
						return static_cast< integer_t >(value * std::numeric_limits<integer_t>::max());
					}
				}

				/* Internal type is 'double' */
				if constexpr ( sizeof(float_t) == 8 )
				{
					if constexpr ( sizeof(integer_t) == 8 )
					{
						return static_cast< integer_t >(static_cast< long double >(value) * std::numeric_limits<integer_t>::max());
					}
					else
					{
						return static_cast< integer_t >(value * std::numeric_limits<integer_t>::max());
					}
				}

				/* Internal type is 'long double' */
				if constexpr ( sizeof(float_t) == 16 )
				{
					return static_cast< integer_t >(value * std::numeric_limits< integer_t >::max());
				}
				else
				{
					return 0;
				}
			}

			/**
			 * @brief Updates RGB components from HSV components modifications.
			 * @param hue The hue value from 0 to 360.
			 * @param saturation The saturation value from 0 to 100.
			 * @param value The intensity value from 0 to 100.
			 * @return void
			 */
			void
			updateFromHSV (float_t hue, float_t saturation, float_t value) noexcept
			{
				constexpr auto Min = static_cast< float_t >(0.01);
				constexpr auto Max = static_cast< float_t >(100);

				/* If there is no saturation, so there is no color, and we only use value. */
				if ( Utility::isZero(saturation) )
				{
					const auto luminance = value * Min;

					m_components[R] = luminance;
					m_components[G] = luminance;
					m_components[B] = luminance;
				}
				else
				{
					const auto tmp = std::round(hue / static_cast< float_t >(60));

					/* Sector 0 to 5 */
					const auto sector = static_cast< unsigned int >(tmp) % 6;

					/* Factorial part of hue */
					const auto factorial = tmp - sector;

					const auto magicA = value * (Max - saturation);
					const auto magicB = value * (Max - factorial * saturation);
					const auto magicC = value * (Max - (Max - factorial) * saturation);

					switch ( sector )
					{
						case 0 :
							this->setRGB(value * Min, magicC * Min, magicA * Min);
							break;

						case 1 :
							this->setRGB(magicB * Min, value * Min, magicA * Min);
							break;

						case 2 :
							this->setRGB(magicA * Min, value * Min, magicC * Min);
							break;

						case 3 :
							this->setRGB(magicA * Min, magicB * Min, value * Min);
							break;

						case 4 :
							this->setRGB(magicC * Min, magicA * Min, value * Min);
							break;

						case 5 :
						default :
							this->setRGB(value * Min, magicA * Min, magicC * Min);
							break;
					}
				}
			}

			std::array< float_t, 4 > m_components{0, 0, 0, 1};
	};

	using ColorF = Color< float >;
	using ColorD = Color< double >;
	using ColorLD = Color< long double >;

	/**
	 * @brief Helper to create a color from integer.
	 * @note With signed integer, negative number will count for 0.
	 * @tparam input_t The type of integer data. Default uint8_t.
	 * @tparam output_t The color data type. Default float.
	 * @param red Red component.
	 * @param green Green component.
	 * @param blue Blue component.
	 * @param alpha Alpha component.
	 * @return Color< output_t >
	 */
	template< typename input_t = uint8_t, typename output_t = float >
	[[nodiscard]]
	Color< output_t >
	ColorFromInteger (input_t red, input_t green, input_t blue, input_t alpha) noexcept requires (std::is_integral_v< input_t >, std::is_floating_point_v< output_t >)
	{
		return {
			static_cast< output_t >(red) / std::numeric_limits< input_t >::max(),
			static_cast< output_t >(green) / std::numeric_limits< input_t >::max(),
			static_cast< output_t >(blue) / std::numeric_limits< input_t >::max(),
			static_cast< output_t >(alpha) / std::numeric_limits< input_t >::max()
		};
	}

	/**
	 * @brief Helper to create a color from integer.
	 * @note With signed integer, negative number will count for 0.
	 * @tparam input_t The type of integer data. Default uint8_t.
	 * @tparam output_t The color data type. Default float.
	 * @param red Red component.
	 * @param green Green component.
	 * @param blue Blue component.
	 * @return Color< output_t >
	 */
	template< typename input_t = uint8_t, typename output_t = float >
	[[nodiscard]]
	Color< output_t >
	ColorFromInteger (input_t red, input_t green, input_t blue) noexcept requires (std::is_integral_v< input_t >, std::is_floating_point_v< output_t >)
	{
		return {
			static_cast< output_t >(red) / std::numeric_limits< input_t >::max(),
			static_cast< output_t >(green) / std::numeric_limits< input_t >::max(),
			static_cast< output_t >(blue) / std::numeric_limits< input_t >::max()
		};
	}

	/**
	 * @brief Helper to create a color from integer.
	 * @note With signed integer, negative number will count for 0.
	 * @tparam input_t The type of integer data. Default uint8_t.
	 * @tparam output_t The color data type. Default float.
	 * @param color A reference to a STL array.
	 * @return Color< output_t >
	 */
	template< typename input_t = uint8_t, typename output_t = float >
	[[nodiscard]]
	Color< output_t >
	ColorFromInteger (const std::array< input_t, 4 > & color) noexcept requires (std::is_integral_v< input_t >, std::is_floating_point_v< output_t >)
	{
		return {
			static_cast< output_t >(color[0]) / std::numeric_limits< input_t >::max(),
			static_cast< output_t >(color[1]) / std::numeric_limits< input_t >::max(),
			static_cast< output_t >(color[2]) / std::numeric_limits< input_t >::max(),
			static_cast< output_t >(color[3]) / std::numeric_limits< input_t >::max()
		};
	}

	/**
	 * @brief Helper to create a color from integer.
	 * @note With signed integer, negative number will count for 0.
	 * @tparam input_t The type of integer data. Default uint8_t.
	 * @tparam output_t The color data type. Default float.
	 * @param color A reference to a STL array.
	 * @return Color< output_t >
	 */
	template< typename input_t = uint8_t, typename output_t = float >
	[[nodiscard]]
	Color< output_t >
	ColorFromInteger (const std::array< input_t, 3 > & color) noexcept requires (std::is_integral_v< input_t >, std::is_floating_point_v< output_t >)
	{
		return {
			static_cast< output_t >(color[0]) / std::numeric_limits< input_t >::max(),
			static_cast< output_t >(color[1]) / std::numeric_limits< input_t >::max(),
			static_cast< output_t >(color[2]) / std::numeric_limits< input_t >::max()
		};
	}

	/**
	 * @brief Helper to create a color from integer.
	 * @note With signed integer, negative number will count for 0.
	 * @tparam input_t The type of integer data. Default uint8_t.
	 * @tparam output_t The color data type. Default float.
	 * @param color A reference to a Vector.
	 * @return Color< output_t >
	 */
	template< typename input_t = uint8_t, typename output_t = float >
	[[nodiscard]]
	Color< output_t >
	ColorFromInteger (const Math::Vector< 4, input_t > & color) noexcept requires (std::is_integral_v< input_t >, std::is_floating_point_v< output_t >)
	{
		return {
			static_cast< output_t >(color.x()) / std::numeric_limits< input_t >::max(),
			static_cast< output_t >(color.y()) / std::numeric_limits< input_t >::max(),
			static_cast< output_t >(color.z()) / std::numeric_limits< input_t >::max(),
			static_cast< output_t >(color.w()) / std::numeric_limits< input_t >::max()
		};
	}

	/**
	 * @brief Helper to create a color from integer.
	 * @note With signed integer, negative number will count for 0.
	 * @tparam input_t The type of integer data. Default uint8_t.
	 * @tparam output_t The color data type. Default float.
	 * @param color A reference to a Vector.
	 * @return Color< output_t >
	 */
	template< typename input_t = uint8_t, typename output_t = float >
	[[nodiscard]]
	Color< output_t >
	ColorFromInteger (const Math::Vector< 3, input_t > & color) noexcept requires (std::is_integral_v< input_t >, std::is_floating_point_v< output_t >)
	{
		return {
			static_cast< output_t >(color.x()) / std::numeric_limits< input_t >::max(),
			static_cast< output_t >(color.y()) / std::numeric_limits< input_t >::max(),
			static_cast< output_t >(color.z()) / std::numeric_limits< input_t >::max()
		};
	}

	/* Predefined colors */
	static constexpr Color< float > White{1.0F, 1.0F, 1.0F, 1.0F};
	static constexpr Color< float > LightGrey{0.75F, 0.75F, 0.75F, 1.0F};
	static constexpr Color< float > Grey{0.5F, 0.5F, 0.5F, 1.0F};
	static constexpr Color< float > DarkGrey{0.25F, 0.25F, 0.25F, 1.0F};
	static constexpr Color< float > Black{0.0F, 0.0F, 0.0F, 1.0F};

	static constexpr Color< float > Red{1.0F, 0.0F, 0.0F, 1.0F};
	static constexpr Color< float > Green{0.0F, 1.0F, 0.0F, 1.0F};
	static constexpr Color< float > Blue{0.0F, 0.0F, 1.0F, 1.0F};
	static constexpr Color< float > Cyan{0.0F, 1.0F, 1.0F, 1.0F};
	static constexpr Color< float > Magenta{1.0F, 0.0F, 1.0F, 1.0F};
	static constexpr Color< float > Yellow{1.0F, 1.0F, 0.0F, 1.0F};

	static constexpr Color< float > LightRed{1.0F, 0.666F, 0.666F, 1.0F};
	static constexpr Color< float > LightGreen{0.666F, 1.0F, 0.666F, 1.0F};
	static constexpr Color< float > LightBlue{0.666F, 0.666F, 1.0F, 1.0F};
	static constexpr Color< float > LightCyan{0.666F, 1.0F, 1.0F, 1.0F};
	static constexpr Color< float > LightMagenta{1.0F, 0.666F, 1.0F, 1.0F};
	static constexpr Color< float > LightYellow{1.0F, 1.0F, 0.666F, 1.0F};

	static constexpr Color< float > DarkRed{0.333F, 0.0F, 0.0F, 1.0F};
	static constexpr Color< float > DarkGreen{0.0F, 0.333F, 0.0F, 1.0F};
	static constexpr Color< float > DarkBlue{0.0F, 0.0F, 0.333F, 1.0F};
	static constexpr Color< float > DarkCyan{0.0F, 0.333F, 0.333F, 1.0F};
	static constexpr Color< float > DarkMagenta{0.333F, 0.0F, 0.333F, 1.0F};
	static constexpr Color< float > DarkYellow{0.333F, 0.333F, 0.0F, 1.0F};

	static constexpr Color< float > TranslucentWhite{1.0F, 1.0F, 1.0F, 0.5F};
	static constexpr Color< float > TranslucentLightGrey{0.75F, 0.75F, 0.75F, 0.5F};
	static constexpr Color< float > TranslucentGrey{0.5F, 0.5F, 0.5F, 0.5F};
	static constexpr Color< float > TranslucentDarkGrey{0.25F, 0.25F, 0.25F, 0.5F};
	static constexpr Color< float > TranslucentBlack{0.0F, 0.0F, 0.0F, 0.5F};

	static constexpr Color< float > TranslucentRed{1.0F, 0.0F, 0.0F, 0.5F};
	static constexpr Color< float > TranslucentGreen{0.0F, 1.0F, 0.0F, 0.5F};
	static constexpr Color< float > TranslucentBlue{0.0F, 0.0F, 1.0F, 0.5F};
	static constexpr Color< float > TranslucentCyan{0.0F, 1.0F, 1.0F, 0.5F};
	static constexpr Color< float > TranslucentMagenta{1.0F, 0.0F, 1.0F, 0.5F};
	static constexpr Color< float > TranslucentYellow{1.0F, 1.0F, 0.0F, 0.5F};

	static constexpr Color< float > TranslucentLightRed{1.0F, 0.666F, 0.666F, 0.5F};
	static constexpr Color< float > TranslucentLightGreen{0.666F, 1.0F, 0.666F, 0.5F};
	static constexpr Color< float > TranslucentLightBlue{0.666F, 0.666F, 1.0F, 0.5F};
	static constexpr Color< float > TranslucentLightCyan{0.666F, 1.0F, 1.0F, 0.5F};
	static constexpr Color< float > TranslucentLightMagenta{1.0F, 0.666F, 1.0F, 0.5F};
	static constexpr Color< float > TranslucentLightYellow{1.0F, 1.0F, 0.666F, 0.5F};

	static constexpr Color< float > TranslucentDarkRed{0.333F, 0.0F, 0.0F, 0.5F};
	static constexpr Color< float > TranslucentDarkGreen{0.0F, 0.333F, 0.0F, 0.5F};
	static constexpr Color< float > TranslucentDarkBlue{0.0F, 0.0F, 0.333F, 0.5F};
	static constexpr Color< float > TranslucentDarkCyan{0.0F, 0.333F, 0.333F, 0.5F};
	static constexpr Color< float > TranslucentDarkMagenta{0.333F, 0.0F, 0.333F, 0.5F};
	static constexpr Color< float > TranslucentDarkYellow{0.333F, 0.333F, 0.0F, 0.5F};

	static constexpr Color< float > Transparent{0.0F, 0.0F, 0.0F, 0.0F};
}
