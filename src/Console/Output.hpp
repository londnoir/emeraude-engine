#pragma once

/* STL inclusions. */
#include <string>
#include <sstream>
#include <vector>

/* Local inclusions for usages. */
#include "../Types.hpp"

namespace Emeraude::Console
{
	/**
	 * @brief Console output class to return command execution info.
	 */
	class Output final
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"ConsoleOutput"};

			/**
			 * @brief Constructs a console return message.
			 * @param severity The message severity.
			 * @param message A string [std::move].
			 */
			Output (Severity severity, std::string message) noexcept;

			/**
			 * @brief Constructs a console return message.
			 * @param severity The message severity.
			 * @param message A reference to a string stream.
			 */
			Output (Severity severity, const std::stringstream & message) noexcept;

			/**
			 * @brief Returns the message severity.
			 * @return Severity
			 */
			[[nodiscard]]
			Severity
			severity () const noexcept
			{
				return m_severity;
			}

			/**
			 * @brief Returns the message.
			 * @return const std::string &
			 */
			[[nodiscard]]
			const std::string &
			message () const noexcept
			{
				return m_message;
			}

		private:

			Severity m_severity;
			std::string m_message;
	};

	using Outputs = std::vector< Output >;
}
