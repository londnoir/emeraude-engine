/*
 * Libraries/ParallelizableProcess.hpp
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
#include <mutex>
#include <stack>
#include <thread>
#include <vector>

namespace Libraries
{
	/**
	 * @brief This class is intended to be inherited by an object which need threaded tasks.
	 */
	template< typename data_t >
	class ParallelizableProcess
	{
		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			ParallelizableProcess (const ParallelizableProcess & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			ParallelizableProcess (ParallelizableProcess && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return ParallelizableProcess &
			 */
			ParallelizableProcess & operator= (const ParallelizableProcess & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return ParallelizableProcess &
			 */
			ParallelizableProcess & operator= (ParallelizableProcess && copy) noexcept = default;

			/**
			 * @brief Destructs the parallelizable process.
			 */
			virtual ~ParallelizableProcess () = default;

			/**
			 * @brief Creates the task.
			 * @param data A reference to data.
			 * @return void
			 */
			virtual
			void
			createTask (const data_t & data) noexcept final
			{
				/* Adding works to the queue. */
				{
					const std::lock_guard< std::mutex > lock{m_mutex};

					m_pendingJobs.emplace(data);
				}

				/* Try to execute a worker if room there.
				 * Current worker ID to pass to process function. */
				for ( auto & worker : m_workers )
				{
					if ( worker.joinable() )
					{
						continue;
					}

					worker = std::thread{[this] () {
						data_t data{};

						while ( this->getNextJob(data) )
						{
							if ( !this->task(data) )
							{
								break;
							}
						}
					}};

					break;
				}
			}

			/**
			 * @brief Waits for all job to finish.
			 * @return void
			 */
			virtual
			void
			waitForAllJobsDone () noexcept final
			{
				for ( auto & worker : m_workers )
				{
					if ( !worker.joinable() )
					{
						continue;
					}

					worker.join();
				}
			}

		protected:

			/**
			 * @brief Constructs a parallelizable process.
			 * @param workersCount The number of workers. Default max thread.
			 */
			explicit
			ParallelizableProcess (size_t workersCount = std::thread::hardware_concurrency()) noexcept
				: m_workers(workersCount)
			{

			}

			/**
			 * @brief This method takes care to pull out from the queue the next job.
			 * @return bool
			 */
			virtual
			bool
			getNextJob (data_t & data) noexcept final
			{
				const std::lock_guard< std::mutex > lock{m_mutex};

				if ( !m_pendingJobs.empty() )
				{
					/* Copy data outside this function. */
					data = m_pendingJobs.top();

					/* Removes it from the queue. */
					m_pendingJobs.pop();

					return true;
				}

				return false;
			}

			/**
			 * @brief The process to build in child class.
			 * @tparam data_t The data type.
			 * @param data A reference to the data.
			 * @return void
			 */
			virtual bool task (const data_t & data) noexcept = 0;

		private:

			std::vector< std::thread > m_workers{};
			std::stack< data_t > m_pendingJobs{};
			std::mutex m_mutex{};
	};
}
