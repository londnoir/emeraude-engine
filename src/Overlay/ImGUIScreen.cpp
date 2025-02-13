#include "ImGUIScreen.hpp"

#ifdef IMGUI_ENABLED

/* Third-party inclusions. */
#include "imgui.h"
#include "backends/imgui_impl_vulkan.h"
#include "backends/imgui_impl_glfw.h"

/* Local inclusions. */
#include "Vulkan/CommandBuffer.hpp"

namespace Emeraude::Overlay
{
	using namespace Vulkan;

	ImGUIScreen::ImGUIScreen (const std::string & name, const std::function< void () > & drawFunction) noexcept
		: NameableTrait(name), m_drawFunction(drawFunction)
	{

	}

	void
	ImGUIScreen::render (const CommandBuffer & commandBuffer) const noexcept
	{
		ImGui_ImplVulkan_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		m_drawFunction();

		ImGui::Render();

		ImDrawData * draw_data = ImGui::GetDrawData();

		ImGui_ImplVulkan_RenderDrawData(draw_data, commandBuffer.handle());
	}
}

#endif
