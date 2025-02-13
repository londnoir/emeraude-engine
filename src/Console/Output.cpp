#include "Output.hpp"

namespace Emeraude::Console
{
	Output::Output (Severity severity, std::string message) noexcept
		: m_severity(severity), m_message(std::move(message))
	{

	}

	Output::Output (Severity severity, const std::stringstream & message) noexcept
		: m_severity(severity), m_message(message.str())
	{

	}
}
