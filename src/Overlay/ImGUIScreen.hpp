#pragma once

/* Application configuration. */
#include "emeraude_config.hpp"

#ifdef IMGUI_ENABLED

/* STL inclusions. */
#include <array>
#include <string>
#include <functional>

/* Local inclusions for inheritances. */
#include "Libraries/NameableTrait.hpp"

/* Forward declarations. */
namespace Emeraude::Vulkan
{
	class CommandBuffer;
}

namespace Emeraude::Overlay
{
	/**
	 * @brief The ImGUI screen specific class.
	 * @exception Libraries::NameableTrait A UI screen have a name.
	 */
	class ImGUIScreen final : public Libraries::NameableTrait
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"ImGUIScreen"};

			/**
			 * @brief Constructs an ImGUI screen.
			 * @param name A reference to a string.
			 * @param drawFunction A reference to a function.
			 */
			ImGUIScreen (const std::string & name, const std::function< void () > & drawFunction) noexcept;

			/**
			 * @brief Sets the UI screen visibility.
			 * @param state The state
			 * @return void
			 */
			void
			setVisibility (bool state) noexcept
			{
				m_flags[IsVisible] = state;
			}

			/**
			 * @brief Returns whether the UI screen is visible.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isVisible () const noexcept
			{
				return m_flags[IsVisible];
			}

			/**
			 * @brief Renders the screen.
			 * @param commandBuffer A reference to a vulkan command buffer;
			 * @return void
			 */
			void render (const Vulkan::CommandBuffer & commandBuffer) const noexcept;

		private:

			/* Flag names. */
			static constexpr auto IsVisible{0UL};

			std::function< void () > m_drawFunction;
			std::array< bool, 8 > m_flags{
				false/*IsVisible*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}

#endif
