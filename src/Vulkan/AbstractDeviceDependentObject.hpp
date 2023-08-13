/*
 * Emeraude/Vulkan/AbstractDeviceDependentObject.hpp
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

#pragma once

/* C/C++ standard libraries. */
#include <memory>

/* Local inclusions for inheritances. */
#include "AbstractObject.hpp"

namespace Emeraude::Vulkan
{
	class Device;

	/**
	 * @brief Base of all Vulkan API object dealing with a device.
	 * @extends Emeraude::Vulkan::AbstractObject The vulkan device dependent object is a vulkan object.
	 */
	class AbstractDeviceDependentObject : public AbstractObject
	{
		public:

			/**
			 * @brief Destructs a device related vulkan object.
			 */
			~AbstractDeviceDependentObject () override = default;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractDeviceDependentObject (const AbstractDeviceDependentObject & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractDeviceDependentObject (AbstractDeviceDependentObject && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			AbstractDeviceDependentObject & operator= (const AbstractDeviceDependentObject & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			AbstractDeviceDependentObject & operator= (AbstractDeviceDependentObject && copy) noexcept = default;

			/**
			 * @brief Returns the device responsible for this object.
			 * @return std::shared_ptr< Device >
			 */
			[[nodiscard]]
			virtual std::shared_ptr< Device > device () const noexcept final;

			/**
			 * @brief Returns whether a device is present.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool hasDevice () const noexcept final;

			/**
			 * @brief Successive calls to AbstractDeviceDependentObject::destroyFromHardware() and AbstractDeviceDependentObject::createOnHardware().
			 * @note If the destruction fails, the creation won't happens.
			 * @return bool
			 */
			virtual bool recreate () noexcept;

			/**
			 * @brief Creates the object in the device.
			 * @return bool
			 */
			virtual bool createOnHardware () noexcept = 0;

			/**
			 * @brief Removes the object from the device.
			 * @return bool
			 */
			virtual bool destroyFromHardware () noexcept = 0;

		protected:

			/**
			 * @brief Constructs a device related vulkan object.
			 * @param device A reference to the device smart pointer where the object will be used.
			 */
			explicit AbstractDeviceDependentObject (const std::shared_ptr< Device > & device) noexcept;

		private:

			std::shared_ptr< Device > m_device;
	};
}
