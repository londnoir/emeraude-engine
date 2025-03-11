/*
 * src/Window.linux.cpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2025 - Sébastien Léon Claude Christian Bémelmans "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Emeraude-Engine; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Complete project and additional information can be found at :
 * https://github.com/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#include "Window.hpp"

#if IS_LINUX

/* Third-party inclusions. */
#define GLFW_EXPOSE_NATIVE_X11
//#define GLFW_EXPOSE_NATIVE_WAYLAND
#include "GLFW/glfw3native.h"

#include <xcb/xcb.h>
#include <vulkan/vulkan_xcb.h>
//#include <vulkan/vulkan_wayland.h>

#ifdef GTK3_ENABLED
	#include <gtk/gtk.h>
	#include <gdk/gdkx.h>
#endif

/* NOTE: Under linux, including X.h defines the MACRO "Success"
 * and enter in conflicts with Severity enum. */
#undef Success

/* Local inclusions. */
#include "Vulkan/Utility.hpp"
#include "Vulkan/Instance.hpp"
#include "Vulkan/Surface.hpp"
#include "PrimaryServices.hpp"

namespace EmEn
{
	using namespace Vulkan;

	bool
	Window::createSurface (bool useNativeCode) noexcept
	{
		VkResult result = VK_SUCCESS;

		VkSurfaceKHR surfaceHandle{VK_NULL_HANDLE};

		if ( useNativeCode )
		{
			VkXcbSurfaceCreateInfoKHR createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
			createInfo.pNext = nullptr;
			createInfo.flags = 0; // VkXcbSurfaceCreateFlagsKHR
			createInfo.connection = nullptr; // xcb_connection_t *
			createInfo.window = glfwGetX11Window(m_handle.get()); // xcb_window_t

			result = vkCreateXcbSurfaceKHR(m_instance.handle(), &createInfo, nullptr, &surfaceHandle);
		}
		else
		{
			result = glfwCreateWindowSurface(m_instance.handle(), m_handle.get(), nullptr, &surfaceHandle);
		}

		if ( result != VK_SUCCESS )
		{
			TraceFatal{ClassId} << "Unable to create the Vulkan surface : " << Vulkan::vkResultToCString(result) << " !";

			return false;
		}

		m_surface = std::make_unique< Surface >(m_instance, surfaceHandle);
		m_surface->setIdentifier(ClassId, "OSVideoFramebuffer", "Surface");

		return true;
	}

	void
	Window::disableTitleBar () noexcept
	{
		::Display * display = glfwGetX11Display();
		::Window window = glfwGetX11Window(m_handle.get());

		XSetWindowAttributes attributes;
		attributes.override_redirect = True;
		XChangeWindowAttributes(display, window, CWOverrideRedirect, &attributes);
	}

#ifdef GTK3_ENABLED
	void
	gtkRealizeCallback (GtkWidget * widget, gpointer user) noexcept
	{
		gtk_widget_set_window(widget, static_cast< GdkWindow * >(user));
	}

	bool
	Window::initializeNativeWindow () noexcept
	{
		auto argc = m_primaryServices.arguments().getArgc();
		auto argv = m_primaryServices.arguments().getArgv();

		if ( gtk_init_check(&argc, &argv) == 0 )
		{
			return false;
		}

		//Display * glfwGetX11Display(void)

		GdkDisplay * display = gdk_display_get_default();

		if ( display == nullptr )
		{
			return false;
		}

		GdkWindow * gdkWindow = gdk_x11_window_foreign_new_for_display(display, glfwGetX11Window(m_handle.get()));

		if ( gdkWindow == nullptr )
		{
			return false;
		}

		GtkWidget * widget = gtk_widget_new(GTK_TYPE_WINDOW, nullptr);

		if ( widget == nullptr )
		{
			return false;
		}

		g_signal_connect(widget, "realize", G_CALLBACK(gtkRealizeCallback), gdkWindow);

		gtk_widget_set_has_window(widget, TRUE);
		gtk_widget_realize(widget);

		m_gtkWindow = GTK_WINDOW(widget);

		return true;
	}
#else
	bool
	Window::initializeNativeWindow () noexcept
	{
		return false;
	}
#endif

	void
	Window::releaseNativeWindow () noexcept
	{
		m_gtkWindow = nullptr;
	}

	GtkWindow *
	Window::getGtkWindow () const noexcept
	{
		return m_gtkWindow;
	}
}

#endif
