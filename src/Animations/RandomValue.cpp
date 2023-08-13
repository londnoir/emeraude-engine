/*
 * Emeraude/Animations/RandomValue.cpp
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

#include "RandomValue.hpp"

/* Local inclusions */
#include "Tracer.hpp"

namespace Emeraude::Animations
{
	using namespace Libraries;

	RandomValue::RandomValue (const Variant & minimum, const Variant & maximum) noexcept
	{
		this->setValue(minimum, maximum);
	}

	void
	RandomValue::setValue (const Variant & minimum, const Variant & maximum) noexcept
	{
		if ( minimum.type() != maximum.type() )
		{
			Tracer::error(ClassId, "Value should be the same type !");

			return;
		}

		m_minimumValue = minimum;
		m_maximumValue = maximum;
	}

	Variant
	RandomValue::getNextValue () noexcept
	{
		switch ( m_minimumValue.type() )
		{
			case Variant::Type::Integer8 :
				return Variant{static_cast< int8_t >(Utility::random(
					m_minimumValue.asInteger8(),
					m_maximumValue.asInteger8()
				))};

			case Variant::Type::UnsignedInteger8 :
				return Variant{static_cast< uint8_t >(Utility::random(
					m_minimumValue.asUnsignedInteger8(),
					m_maximumValue.asUnsignedInteger8()
				))};

			case Variant::Type::Integer16 :
				return Variant{static_cast< int16_t >(Utility::random(
					m_minimumValue.asInteger16(),
					m_maximumValue.asInteger16()
				))};

			case Variant::Type::UnsignedInteger16 :
				return Variant{static_cast< uint16_t >(Utility::random(
					m_minimumValue.asUnsignedInteger16(),
					m_maximumValue.asUnsignedInteger16()
				))};

			case Variant::Type::Integer32 :
				return Variant{static_cast< int32_t >(Utility::random(
					m_minimumValue.asInteger32(),
					m_maximumValue.asInteger32()
				))};

			case Variant::Type::UnsignedInteger32 :
				return Variant{static_cast< uint32_t >(Utility::random(
					m_minimumValue.asUnsignedInteger32(),
					m_maximumValue.asUnsignedInteger32()
				))};

			case Variant::Type::Integer64 :
				return Variant{static_cast< int64_t >(Utility::random(
					m_minimumValue.asInteger64(),
					m_maximumValue.asInteger64()
				))};

			case Variant::Type::UnsignedInteger64 :
				return Variant{static_cast< uint64_t >(Utility::random(
					m_minimumValue.asUnsignedInteger64(),
					m_maximumValue.asUnsignedInteger64()
				))};

			case Variant::Type::Float :
				return Variant{static_cast< float >(Utility::random(
					m_minimumValue.asFloat(),
					m_maximumValue.asFloat()
				))};

			case Variant::Type::Double :
				return Variant{static_cast< double >(Utility::random(
					m_minimumValue.asDouble(),
					m_maximumValue.asDouble()
				))};

			case Variant::Type::LongDouble :
				return Variant{static_cast< long double >(Utility::random(
					m_minimumValue.asLongDouble(),
					m_maximumValue.asLongDouble()
				))};

			case Variant::Type::Boolean :
				if ( Utility::random(0, 1) > 0 )
				{
					return Variant{true};
				}

				return Variant{false};

			case Variant::Type::Vector2Float :
				return Variant{Math::Vector< 2, float >(
					Utility::random(m_minimumValue.asFloat(), m_maximumValue.asFloat()),
					Utility::random(m_minimumValue.asFloat(), m_maximumValue.asFloat())
				)};

			case Variant::Type::Vector3Float :
				return Variant{Math::Vector< 3, float >(
					Utility::random(m_minimumValue.asFloat(), m_maximumValue.asFloat()),
					Utility::random(m_minimumValue.asFloat(), m_maximumValue.asFloat()),
					Utility::random(m_minimumValue.asFloat(), m_maximumValue.asFloat())
				)};

			case Variant::Type::Vector4Float :
				return Variant{Math::Vector< 4, float >(
					Utility::random(m_minimumValue.asFloat(), m_maximumValue.asFloat()),
					Utility::random(m_minimumValue.asFloat(), m_maximumValue.asFloat()),
					Utility::random(m_minimumValue.asFloat(), m_maximumValue.asFloat()),
					0.0F
				)};

			case Variant::Type::Matrix2Float :
			case Variant::Type::Matrix3Float :
			case Variant::Type::Matrix4Float :
				return {};

			case Variant::Type::CoordinatesFloat :
				return Variant{Math::Coordinates< float >(Math::Vector< 3, float >(
					Utility::random(m_minimumValue.asFloat(), m_maximumValue.asFloat()),
					Utility::random(m_minimumValue.asFloat(), m_maximumValue.asFloat()),
					Utility::random(m_minimumValue.asFloat(), m_maximumValue.asFloat())
				))};

			case Variant::Type::Color :
				return Variant{PixelFactory::Color< float >::random(
					m_minimumValue.asFloat(),
					m_maximumValue.asFloat()
				)};

			case Variant::Type::Null :
				return {};
		}

		return {};
	}

	bool
	RandomValue::isPlaying () const noexcept
	{
		return true;
	}

	bool
	RandomValue::isPaused () const noexcept
	{
		return false;
	}

	bool
	RandomValue::isFinished () const noexcept
	{
		return false;
	}

	bool
	RandomValue::play () noexcept
	{
		return true;
	}

	bool
	RandomValue::pause () noexcept
	{
		return false;
	}
}
