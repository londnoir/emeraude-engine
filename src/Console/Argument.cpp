#include "Argument.hpp"

/* STL inclusions. */
#include <cmath>

/* Local inclusions. */
#include <Tracer.hpp>

namespace Emeraude::Console
{
	Argument::Argument (bool value) noexcept
		: m_type(ArgumentType::Boolean),
		m_value(value)
	{

	}

	Argument::Argument (int32_t value) noexcept
		: m_type(ArgumentType::Integer),
		m_value(value)
	{

	}

	Argument::Argument (float value) noexcept
		: m_type(ArgumentType::Float),
		m_value(value)
	{

	}

	Argument::Argument (std::string value) noexcept
		: m_type(ArgumentType::String),
		m_value(std::move(value))
	{

	}

	bool
	Argument::asBoolean () const noexcept
	{
		if ( m_type == ArgumentType::Integer )
		{
			const auto value = std::any_cast< int32_t >(m_value);

			return value > 0;
		}

		if ( m_type == ArgumentType::Float )
		{
			const auto value = std::any_cast< float >(m_value);

			return value > 0.0F;
		}

		if ( m_type != ArgumentType::Boolean )
		{
			TraceWarning{ClassId} << "This argument is not a boolean !";

			return false;
		}

		return std::any_cast< bool >(m_value);
	}

	int32_t
	Argument::asInteger () const noexcept
	{
		if ( m_type == ArgumentType::Float )
		{
			const auto value = std::any_cast< float >(m_value);

			return static_cast< int32_t >(std::round(value));
		}

		if ( m_type != ArgumentType::Integer )
		{
			TraceWarning{ClassId} << "This argument is not an integer number !";

			return 0;
		}

		return std::any_cast< int32_t >(m_value);
	}

	float
	Argument::asFloat () const noexcept
	{
		if ( m_type != ArgumentType::Float )
		{
			TraceWarning{ClassId} << "This argument is not a floating point number !";

			return 0.0F;
		}

		return std::any_cast< float >(m_value);
	}

	std::string
	Argument::asString () const noexcept
	{
		if ( m_type != ArgumentType::String )
		{
			TraceWarning{ClassId} << "This argument is not a string !";

			return {};
		}

		return std::any_cast< std::string >(m_value);
	}
}
