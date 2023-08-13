/*
 * Emeraude/Saphir/Declaration/AbstractBufferBackedBlock.hpp
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
#include <vector>
#include <cstdint>

/* Local inclusions for inheritances. */
#include "BlockInterface.hpp"

/* Local inclusions for usages. */
#include "Member/BufferBackedBlock.hpp"
#include "Types.hpp"

namespace Emeraude::Saphir::Declaration
{
	/**
	 * @brief Base class for every GLSL Buffer-Backed blocks.
	 * @extends Emeraude::Saphir::BlockInterface
	 */
	class AbstractBufferBackedBlock : public BlockInterface
	{
		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractBufferBackedBlock (const AbstractBufferBackedBlock & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractBufferBackedBlock (AbstractBufferBackedBlock && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return AbstractBufferBackedBlock &
			 */
			AbstractBufferBackedBlock & operator= (const AbstractBufferBackedBlock & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return AbstractBufferBackedBlock &
			 */
			AbstractBufferBackedBlock & operator= (AbstractBufferBackedBlock && copy) noexcept = default;

			/**
			 * @brief Destructs the backed buffer block.
			 */
			~AbstractBufferBackedBlock () override = default;

			/** @copydoc Emeraude::Saphir::DeclarationInterface::isValid() */
			[[nodiscard]]
			bool isValid () const noexcept override;

			/** @copydoc Emeraude::Saphir::DeclarationInterface::bytes() */
			[[nodiscard]]
			size_t bytes () const noexcept final;

			/**
			 * @brief Gets the set index.
			 * @return uint32_t.
			 */
			[[nodiscard]]
			virtual uint32_t set () const noexcept final;

			/**
			 * @brief Gets the binding point.
			 * @return uint32_t.
			 */
			[[nodiscard]]
			virtual uint32_t binding () const noexcept final;

			/**
			 * @brief Sets matrix storage order.
			 * @param order
			 */
			virtual void setMatrixStorageOrder (MatrixStorageOrder matrixStorageOrder) noexcept final;

			/**
			 * @brief Gets matrix storage order.
			 * @return MatrixStorageOrder
			 */
			[[nodiscard]]
			virtual MatrixStorageOrder matrixStorageOrder () const noexcept final;

			/**
			 * @brief Adds a member to the block.
			 * @param type A C-string to set the type of the member. Use one of Keys::GLSL::* keyword.
			 * @param name A C-string to set the name of the member.
			 * @param layout The layout to use. Default nullptr.
			 */
			virtual bool addMember (VariableType type, Key name, Key layout = nullptr) noexcept final;

			/**
			 * @brief Adds a member to the block.
			 * @param structure A reference to a structure.
			 * @param layout The layout to use. Default nullptr.
			 */
			virtual bool addMember (const Structure & structure, Key layout = nullptr) noexcept final;

			/**
			 * @brief Adds an array member to the block.
			 * @param type A C-string to set the type of the member. Use one of Keys::GLSL::* keyword.
			 * @param name A C-string to set the name of the member.
			 * @param arraySize The size of the array.
			 * @param layout The layout to use. Default nullptr.
			 */
			virtual bool addArrayMember (VariableType type, Key name, size_t arraySize, Key layout = nullptr) noexcept final;

			/**
			 * @brief Adds an array member to the block.
			 * @param structure A reference to a structure.
			 * @param arraySize The size of the array.
			 * @param layout The layout to use. Default nullptr.
			 */
			virtual bool addArrayMember (const Structure & structure, size_t arraySize, Key layout = nullptr) noexcept final;

			/**
			 * @brief Returns the list of members.
			 * @return const std::vector< std::pair< Key, Member::BufferBackedBlock > > &
			 */
			[[nodiscard]]
			virtual const std::vector< std::pair< Key, Member::BufferBackedBlock > > & members () const noexcept final;

		protected:

			/**
			 * @brief Constructs a backed buffer block.
			 * @param set An integer to define in which set the buffer is.
			 * @param binding An integer to define at which point the buffer is bound.
			 * @param memoryLayout The type of video memory layout.
			 * @param name A C-string to set the name of the block.
			 * @param instanceName A C-string to set the name of the instance of the block. Default nullptr.
			 * @param arraySize Set the block as an array. Default 0.
			 */
			AbstractBufferBackedBlock (uint32_t set, uint32_t binding, MemoryLayout memoryLayout, Key name, Key instanceName = nullptr, size_t arraySize = 0) noexcept;

			/** @copydoc Emeraude::Saphir::BlockInterface::getLayoutQualifier() */
			virtual std::string getLayoutQualifier () const noexcept final;

		private:

			uint32_t m_set;
			uint32_t m_binding;
			MemoryLayout m_memoryLayout;
			MatrixStorageOrder m_matrixStorageOrder = MatrixStorageOrder::Default;
			std::vector< std::pair< Key, Member::BufferBackedBlock > > m_members{};
	};
}
