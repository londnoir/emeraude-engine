/*
 * Emeraude/Animations/Interpolation.cpp
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

#include "Interpolation.hpp"

/* C/C++ standard libraries. */
#include <utility>

/* Local inclusion */
#include "Tracer.hpp"

namespace Emeraude::Animations
{
	using namespace Libraries;

	Variant
	Interpolation::linearInterpolate (const KeyFrames::const_iterator & itStart, const KeyFrames::const_iterator & itEnd, float factor) noexcept
	{
		if ( factor <= 0.0F )
		{
			return itStart->second.value();
		}

		if ( factor >= 1.0F )
		{
			return itEnd->second.value();
		}

		switch ( itStart->second.value().type() )
		{
			case Variant::Type::Integer8 :
				return Variant{static_cast< int8_t >(Math::linearInterpolation< float >(
					itStart->second.value().asInteger8(),
					itEnd->second.value().asInteger8(),
					factor
				))};

			case Variant::Type::UnsignedInteger8 :
				return Variant{static_cast< uint8_t >(Math::linearInterpolation< float >(
					itStart->second.value().asUnsignedInteger8(), 
					itEnd->second.value().asUnsignedInteger8(),
					factor
				))};

			case Variant::Type::Integer16 :
				return Variant{static_cast< int16_t >(Math::linearInterpolation< float >(
					itStart->second.value().asInteger16(),
					itEnd->second.value().asInteger16(),
					factor
				))};

			case Variant::Type::UnsignedInteger16 :
				return Variant{static_cast< uint16_t >(Math::linearInterpolation< float >(
					itStart->second.value().asUnsignedInteger16(), 
					itEnd->second.value().asUnsignedInteger16(),
					factor
				))};

			case Variant::Type::Integer32 :
				return Variant{static_cast< int32_t >(Math::linearInterpolation< double >(
					itStart->second.value().asInteger32(),
					itEnd->second.value().asInteger32(),
					factor
				))};

			case Variant::Type::UnsignedInteger32 :
				return Variant{static_cast< uint32_t >(Math::linearInterpolation< double >(
					itStart->second.value().asUnsignedInteger32(), 
					itEnd->second.value().asUnsignedInteger32(),
					factor
				))};

			case Variant::Type::Integer64 :
				return Variant{static_cast< int64_t >(Math::linearInterpolation< long double >(
					itStart->second.value().asInteger64(),
					itEnd->second.value().asInteger64(),
					factor
				))};

			case Variant::Type::UnsignedInteger64 :
				return Variant{static_cast< uint64_t >(Math::linearInterpolation< long double >(
					itStart->second.value().asUnsignedInteger64(), 
					itEnd->second.value().asUnsignedInteger64(),
					factor
				))};

			case Variant::Type::Float :
				return Variant{Math::linearInterpolation(
					itStart->second.value().asFloat(),
					itEnd->second.value().asFloat(),
					factor
				)};

			case Variant::Type::Double :
				return Variant{Math::linearInterpolation(
					itStart->second.value().asDouble(), 
					itEnd->second.value().asDouble(),
					factor
				)};

			case Variant::Type::LongDouble :
				return Variant{Math::linearInterpolation(
					itStart->second.value().asLongDouble(),
					itEnd->second.value().asLongDouble(), 
					factor
				)};

			case Variant::Type::Boolean :
			{
				const auto operandA = static_cast< float >(itStart->second.value().asBool());
				const auto operandB = static_cast< float >(itEnd->second.value().asBool());

				if ( Math::linearInterpolation(operandA, operandB, factor) > 0.5F ) // NOLINT(*-magic-numbers)
				{
					return Variant{true};
				}
			}
				return Variant{false};

			case Variant::Type::Vector2Float :
				return Variant{Math::linearInterpolation(
					itStart->second.value().asVector2Float(),
					itEnd->second.value().asVector2Float(), 
					factor
				)};

			case Variant::Type::Vector3Float :
				return Variant{Math::linearInterpolation(
					itStart->second.value().asVector3Float(),
					itEnd->second.value().asVector3Float(), 
					factor
				)};

			case Variant::Type::Vector4Float :
				return Variant{Math::linearInterpolation(
						itStart->second.value().asVector4Float(),
						itEnd->second.value().asVector4Float(), 
						factor
					)};

			case Variant::Type::Matrix2Float :
				return Variant{Math::linearInterpolation(
					itStart->second.value().asMatrix2Float(),
					itEnd->second.value().asMatrix2Float(), 
					factor
				)};

			case Variant::Type::Matrix3Float :
				return Variant{Math::linearInterpolation(
					itStart->second.value().asMatrix3Float(),
					itEnd->second.value().asMatrix3Float(), 
					factor
				)};

			case Variant::Type::Matrix4Float :
				return Variant{Math::linearInterpolation(
					itStart->second.value().asMatrix4Float(),
					itEnd->second.value().asMatrix4Float(), 
					factor
				)};

			case Variant::Type::CoordinatesFloat :
				return Variant{Math::Coordinates< float >::linearInterpolation(
					itStart->second.value().asCoordinatesFloat(),
					itEnd->second.value().asCoordinatesFloat(),
					factor
				)};

			case Variant::Type::Color :
				return Variant{PixelFactory::Color< float >::linearInterpolation(
					itStart->second.value().asColor(),
					itEnd->second.value().asColor(),
					static_cast< float >(factor)
				)};

			case Variant::Type::Null :
				return {};
		}

		return {};
	}

	Variant
	Interpolation::cosineInterpolate (const KeyFrames::const_iterator & itStart, const KeyFrames::const_iterator & itEnd, float factor) noexcept
	{
		if ( factor <= 0.0F )
		{
			return itStart->second.value();
		}

		if ( factor >= 1.0F )
		{
			return itEnd->second.value();
		}

		switch ( itStart->second.value().type() )
		{
			case Variant::Type::Integer8 :
				return Variant{static_cast< int8_t >(Math::cosineInterpolation< float >(
					itStart->second.value().asInteger8(),
					itEnd->second.value().asInteger8(),
					factor
				))};

			case Variant::Type::UnsignedInteger8 :
				return Variant{static_cast< uint8_t >(Math::cosineInterpolation< float >(
					itStart->second.value().asUnsignedInteger8(),
					itEnd->second.value().asUnsignedInteger8(),
					factor
				))};

			case Variant::Type::Integer16 :
				return Variant{static_cast< int16_t >(Math::cosineInterpolation< float >(
					itStart->second.value().asInteger16(),
					itEnd->second.value().asInteger16(),
					factor
				))};

			case Variant::Type::UnsignedInteger16 :
				return Variant{static_cast< uint16_t >(Math::cosineInterpolation< float >(
					itStart->second.value().asUnsignedInteger16(),
					itEnd->second.value().asUnsignedInteger16(),
					factor
				))};

			case Variant::Type::Integer32 :
				return Variant{static_cast< int32_t >(Math::cosineInterpolation< double > (
					itStart->second.value().asInteger32(),
					itEnd->second.value().asInteger32(),
					factor
				))};

			case Variant::Type::UnsignedInteger32 :
				return Variant{static_cast< uint32_t >(Math::cosineInterpolation< double >(
					itStart->second.value().asUnsignedInteger32(),
					itEnd->second.value().asUnsignedInteger32(),
					factor
				))};

			case Variant::Type::Integer64 :
				return Variant{static_cast< int64_t >(Math::cosineInterpolation< long double >(
					itStart->second.value().asInteger64(),
					itEnd->second.value().asInteger64(),
					factor
				))};

			case Variant::Type::UnsignedInteger64 :
				return Variant{static_cast< uint64_t >(Math::cosineInterpolation< long double >(
					itStart->second.value().asUnsignedInteger64(),
					itEnd->second.value().asUnsignedInteger64(),
					factor
				))};

			case Variant::Type::Float :
				return Variant{Math::cosineInterpolation(
					itStart->second.value().asFloat(),
					itEnd->second.value().asFloat(),
					factor
				)};

			case Variant::Type::Double :
				return Variant{Math::cosineInterpolation(
					itStart->second.value().asDouble(),
					itEnd->second.value().asDouble(),
					  factor
				  )};

			case Variant::Type::LongDouble :
				return Variant{Math::cosineInterpolation(
					itStart->second.value().asLongDouble(),
					itEnd->second.value().asLongDouble(),
					factor
				)};

			case Variant::Type::Boolean :
			{
				const auto operandA = static_cast< float >(itStart->second.value().asBool());
				const auto operandB = static_cast< float >(itEnd->second.value().asBool());

				if ( Math::cosineInterpolation(operandA, operandB, factor) > 0.5F)  // NOLINT(*-magic-numbers)
				{
					return Variant{true};
				}
			}
				return Variant{false};

			case Variant::Type::Vector2Float :
				return Variant{Math::cosineInterpolation(
					itStart->second.value().asVector2Float(),
					itEnd->second.value().asVector2Float(),
					factor
				)};

			case Variant::Type::Vector3Float :
				return Variant{Math::cosineInterpolation(
					itStart->second.value().asVector3Float(),
					itEnd->second.value().asVector3Float(),
					factor
				)};

			case Variant::Type::Vector4Float :
				return Variant{Math::cosineInterpolation(
					itStart->second.value().asVector4Float(),
					itEnd->second.value().asVector4Float(),
					factor
				)};

			case Variant::Type::Matrix2Float :
				return Variant{Math::cosineInterpolation(
					itStart->second.value().asMatrix2Float(),
					itEnd->second.value().asMatrix2Float(),
					factor
				)};

			case Variant::Type::Matrix3Float :
				return Variant{Math::cosineInterpolation(
					itStart->second.value().asMatrix3Float(),
					itEnd->second.value().asMatrix3Float(),
					factor
				)};

			case Variant::Type::Matrix4Float :
				return Variant{Math::cosineInterpolation(
					itStart->second.value().asMatrix4Float(),
					itEnd->second.value().asMatrix4Float(),
					factor
				)};

			case Variant::Type::CoordinatesFloat :
				return Variant{Math::Coordinates< float >::cosineInterpolation(
					itStart->second.value().asCoordinatesFloat(),
					itEnd->second.value().asCoordinatesFloat(),
					factor
				)};

			case Variant::Type::Color :
				return Variant{PixelFactory::Color< float >::cosineInterpolation(
					itStart->second.value().asColor(),
					itEnd->second.value().asColor(),
					static_cast< float >(factor)
				)};

			case Variant::Type::Null :
				return {};
		}

		return {};
	}

	Variant
	Interpolation::cubeInterpolate (const KeyFrames::const_iterator & /*itStart*/, const KeyFrames::const_iterator & /*itEnd*/, float /*factor*/) noexcept
	{
		/* FIXME: Create the method. */
		return {};
	}

	void
	Interpolation::setRepeatness (int value) noexcept
	{
		m_repeat = value;
	}

	void
	Interpolation::setDuration (float time) noexcept
	{
		m_step = EngineUpdateCycleDuration< float > * (1.0F / time);
	}

	void
	Interpolation::setDurationInHertz (unsigned int time) noexcept
	{
		m_step = 1.0F / static_cast< float >(time);
	}

	void
	Interpolation::setNoise (float noise) noexcept
	{
		m_noise = noise;
	}

	bool
	Interpolation::isPlaying () const noexcept
	{
		return m_flags[IsPlaying];
	}

	bool
	Interpolation::isPaused () const noexcept
	{
		return !m_flags[IsPlaying];
	}

	bool
	Interpolation::isFinished () const noexcept
	{
		return ( m_repeat == 0 && Utility::equal< float >(m_currentTime, 1.0) );
	}

	void
	Interpolation::addKeyFrame (float offset, const Variant & value, Math::InterpolationType interpolation) noexcept
	{
		/* Sets the key frame at the end. */
		m_keyFrames.emplace(std::piecewise_construct, std::forward_as_tuple(Math::clampToUnit(offset)), std::forward_as_tuple(value, interpolation));
	}

	void
	Interpolation::setCurrentTime(float time) noexcept
	{
		m_currentTime = Math::clampToUnit(time);
	}

	bool
	Interpolation::play () noexcept
	{
		if ( m_keyFrames.size() < 2 )
		{
			Tracer::error(ClassId, "Incomplete animation !");

			return false;
		}

		/* Sets at least one turn ! */
		if ( m_repeat == 0 )
		{
			m_repeat = 1;
		}

		/* Checks animation completeness. */
		auto front = m_keyFrames.begin();

		if ( Utility::different< float >(front->first, 0.0) )
		{
			m_keyFrames.emplace(0, front->second);
		}

		auto back = m_keyFrames.cbegin();

		if ( Utility::different< float >(back->first, 1.0) )
		{
			m_keyFrames.emplace(1, back->second);
		}

		m_flags[IsPlaying] = true;

		return true;
	}

	bool
	Interpolation::pause () noexcept
	{
		if ( m_flags[IsPlaying] )
		{
			m_flags[IsPlaying] = false;

			return true;
		}

		return false;
	}

	Variant
	Interpolation::getNextValue () noexcept
	{
		if ( !m_flags[IsPlaying] )
		{
			return {};
		}

		Variant result;

		/* Gets the current interval for interpolating values. */
		if ( m_keyFrames.size() > 2 )
		{
			/* Prepare parameters for interpolate() */
			KeyFrames::const_iterator itStart{};
			KeyFrames::const_iterator itEnd{};

			for ( itStart = m_keyFrames.cbegin(); itStart != m_keyFrames.cend(); ++itStart )
			{
				itEnd = std::next(itStart);

				if ( m_currentTime >= itStart->first && ( m_currentTime < itEnd->first || m_currentTime - itEnd->first < 0 ) )
				{
					break;
				}
			}

			/* Rescale global time on the selected segment
			 *
			 *	 |---------|X-------|---------|
			 *	0.0	   0.33			   1.0
			 *
			 * 	must become something like 0.01. */
			auto scaledTime = Math::clampToUnit((1.0F / (itEnd->first - itStart->first)) * (m_currentTime - itStart->first));

			/* Interpolate the targeted value. */
			switch ( itStart->second.interpolation() )
			{
				case Math::InterpolationType::Linear :
					result = this->linearInterpolate(itStart, itEnd, scaledTime);
					break;

				case Math::InterpolationType::Cosine :
					result = this->cosineInterpolate(itStart, itEnd, scaledTime);
					break;

				case Math::InterpolationType::Cubic :
					result = this->cubeInterpolate(itStart, itEnd, scaledTime);
					break;
			}
		}
		else
		{
			auto itStart = m_keyFrames.cbegin();

			/* Interpolate the targeted value. */
			switch ( itStart->second.interpolation() )
			{
				case Math::InterpolationType::Linear :
					result = this->linearInterpolate(itStart, --m_keyFrames.cend(), m_currentTime);
					break;

				case Math::InterpolationType::Cosine :
					result = this->cosineInterpolate(itStart, --m_keyFrames.cend(), m_currentTime);
					break;

				case Math::InterpolationType::Cubic :
					result = this->cubeInterpolate(itStart, --m_keyFrames.cend(), m_currentTime);
					break;
			}
		}

		/* Advance the time. */
		m_currentTime += m_step;

		/* Checks for the end of cycle. */
		if ( m_currentTime >= 1.0F )
		{
			/* Loop. */
			if ( m_repeat < 0 )
			{
				m_currentTime = 0.0F;
			}
			/* Limited cycles. */
			else
			{
				if ( m_repeat > 0 )
				{
					m_repeat--;

					m_currentTime = 0.0F;
				}
				else
				{
					m_flags[IsPlaying] = false;

					m_currentTime = 1.0F;
				}
			}
		}

		return result;
	}

	std::ostream &
	operator<< (std::ostream & out, const Interpolation & obj)
	{
		for ( auto it = obj.m_keyFrames.cbegin(); it != obj.m_keyFrames.cend(); ++it )
		{
			out <<
				"Frame #" << std::distance(obj.m_keyFrames.cbegin(), it) << " (" << it->first << ")\n"
				"Value : " << it->second.value() << '\n';
		}

		return out;
	}

	std::string
	to_string (const Interpolation & obj) noexcept
	{
		return (std::stringstream{} << obj).str();
	}
}
