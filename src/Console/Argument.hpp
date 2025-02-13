#pragma once

/* STL inclusions. */
#include <any>
#include <cstdint>
#include <string>
#include <vector>

namespace Emeraude::Console
{
	/**	@brief Type of console argument. */
	enum class ArgumentType
	{
		Undefined,
		Boolean,
		Integer,
		Float,
		String
	};

	/**
	 * @brief The console argument class.
	 */
	class Argument final
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"Argument"};

			/**
			 * @brief Constructs an undefined argument.
			 */
			Argument () noexcept = default;

			/**
			 * @brief Constructs a boolean argument.
			 * @param value The value
			 */
			Argument (bool value) noexcept;

			/**
			 * @brief Constructs an integer number argument.
			 * @param value The value
			 */
			Argument (int32_t value) noexcept;

			/**
			 * @brief Constructs a floating point number argument.
			 * @param value The value
			 */
			Argument (float value) noexcept;

			/**
			 * @brief Constructs a string argument.
			 * @param value The value
			 */
			Argument (std::string value) noexcept;

			/**
			 * @brief Returns the type of argument.
			 * @return ArgumentType
			 */
			[[nodiscard]]
			ArgumentType
			type () const noexcept
			{
				return m_type;
			}

			/**
			 * @brief Returns the raw value.
			 * @return const std::any &
			 */
			[[nodiscard]]
			const std::any &
			value () const noexcept
			{
				return m_value;
			}

			/**
			 * @brief Returns a boolean value.
			 * @return bool
			 */
			[[nodiscard]]
			bool asBoolean () const noexcept;

			/**
			 * @brief Returns an integer number.
			 * @return int32_t
			 */
			[[nodiscard]]
			int32_t asInteger () const noexcept;

			/**
			 * @brief Returns an integer floating point number.
			 * @return float
			 */
			[[nodiscard]]
			float asFloat () const noexcept;

			/**
			 * @brief Returns a string.
			 * @return std::string
			 */
			[[nodiscard]]
			std::string asString () const noexcept;

		private:

			ArgumentType m_type = ArgumentType::Undefined;
			std::any m_value;
	};

	using Arguments = std::vector< Argument >;
}
