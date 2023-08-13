/*
 * Libraries/Math/DeterminantAverage.hpp
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
#include <cmath>
#include <map>
#include <type_traits>
#include <vector>

/* Local inclusions */
#include "Base.hpp"

namespace Libraries::Math
{
	template< typename data_t = float, std::enable_if_t< std::is_arithmetic_v< data_t >, bool > = false >
	class [[maybe_unused]] DeterminantAverage final
	{
		public:

			/**
			 * @brief Constructs the default tolerance computer.
			 */
			DeterminantAverage () noexcept = default;

			/**
			 * @brief Constructs the tolerance computer.
			 * @param values An array of initial values to check.
			 * @param tolerance The tolerance value.
			 */
			DeterminantAverage (const std::vector< data_t > & values, data_t tolerance) noexcept
				: m_values(values), m_tolerance(tolerance)
			{

			}

			/**
			 * @brief Sets the tolerance to use.
			 * @param tolerance The tolerance value.
			 * @return void
			 */
			void
			setTolerance (data_t tolerance) noexcept
			{
				m_tolerance = std::max(0, tolerance);
			}

			/**
			 * @brief Adds a value to the list.
			 * @param value A number to average.
			 * @return void
			 */
			void
			addValue (data_t value) noexcept
			{
				m_values.emplace_back(value);
			}

			/**
			 * @brief Replaces all values.
			 * @param values An array of values to check.
			 * @return void
			 */
			void
			setValues (const std::vector< data_t > & values) noexcept
			{
				this->clear();

				m_values = values;
			}

			/**
			 * @brief Computes the average.
			 * @return bool
			 */
			bool
			compute () noexcept
			{
				if ( m_values.empty() )
				{
					return false;
				}

				const auto limit = m_values.size();

				struct Couple
				{
					size_t indexA;
					size_t indexB;
					bool isValid;
				};

				/* NOTE : Tableau provisoire contenant les couples. */
				std::vector< Couple > couples{};
				couples.reserve(limit * 2);

				for ( size_t indexA = 0; indexA < limit; indexA++ )
				{
					const auto valueA = m_values[indexA];

					/* NOTE : On boucle sur le même tableau, mais à partir de l'index précédent +1. */
					for ( auto indexB = indexA + 1; indexB < limit; indexB++ )
					{
						const auto valueB = m_values[indexB];

						/* NOTE : On calcule la différence entre les deux
						 * et si ça dépasse la tolérance de l'analyse, le jeton est 0, sinon 1. */
						const auto isValid = Math::difference(valueA, valueB) <= m_tolerance;

						/* NOTE : On indique le jeton retenu pour les 2 intensités */
						couples.emplace_back(Couple{indexA, indexB, isValid});

					}
				}

				/* NOTE : Tableau provisoire contenant le nombre de jetons récoltés par valeur. */
				std::vector< unsigned int > tokens(limit, 0);

				/* NOTE : On comptabilise le nombre de jetons pour chaque valeur. */
				for ( const auto & couple : couples )
				{
					if ( !couple.isValid )
					{
						continue;
					}

					tokens[couple.indexA]++;
					tokens[couple.indexB]++;
				}

				/* NOTE : On vérifie quel test à reçu le plus de jetons. */
				const auto maxTokens = *std::max_element(tokens.cbegin(), tokens.cend());

				if ( maxTokens == 0 )
				{
					return false;
				}

				/* NOTE : On complète le tableau des indices retenus.
				 * Retenu si le nombre de jetons atteint le max. */
				m_retainedIndexes.resize(limit);

				for ( size_t index = 0; index < limit; index++ )
				{
					m_retainedIndexes[index] = tokens[index] == maxTokens;
				}

				/* NOTE : On constitue un tableau avec seulement les valeurs retenues. */
				m_retainedValues.reserve(limit);

				for ( size_t index = 0; index < limit; index++ )
				{
					if ( m_retainedIndexes[index] )
					{
						m_retainedValues.emplace_back(m_values[index]);
					}
				}

				/* NOTE : On calcule la moyenne et on assigne à l'intensité finale de l'analyse. */
				if ( m_retainedValues.empty() )
				{
					return false;
				}

				m_average = Math::average(m_retainedValues);

				return true;
			}

			/**
			 * @brief Clears all values except tolerance.
			 * @return void
			 */
			void
			clear () noexcept
			{
				m_values.clear();
				m_retainedIndexes.clear();
				m_retainedValues.clear();
				m_average = 0;
			}

			/**
			 * @brief Returns whether one or more values have been removed.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isValueRemoved () const noexcept
			{
				return std::any_of(m_retainedIndexes.cbegin(), m_retainedIndexes.cend(), [] (auto isRetained) {
					return !isRetained;
				});
			}

			/**
			 * @brief Returns whether all values have been removed.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isAllValuesRemoved () const noexcept
			{
				return std::all_of(m_retainedIndexes.cbegin(), m_retainedIndexes.cend(), [] (auto isRetained) {
					return !isRetained;
				});
			}

			/**
			 * @brief Returns the number of removed values.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			getRemovedValueCount () const noexcept
			{
				return m_values.size() - m_retainedValues.size();
			}

			/**
			 * @brief Returns the used tolerance in computation.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			getTolerance () const noexcept
			{
				return m_tolerance;
			}

			/**
			 * @brief Returns an array with all values involved in the computation.
			 * @return const std::vector< data_t > &
			 */
			[[nodiscard]]
			const std::vector< data_t > &
			getValues () const noexcept
			{
				return m_values;
			}

			/**
			 * @brief Returns an associative array with the keys as an index into array
			 * from DeterminantAverage::getValues() and the values as a boolean
			 * for the retention state.
			 * @return const std::vector< bool > &
			 */
			[[nodiscard]]
			const std::vector< bool > &
			getRetainedIndexes () const noexcept
			{
				return m_retainedIndexes;
			}

			/**
			 * @brief Returns an array with all retained values.
			 * @return const std::vector< data_t > &
			 */
			[[nodiscard]]
			const std::vector< data_t > &
			getRetainedValues () const noexcept
			{
				return m_retainedValues;
			}

			/**
			 * @brief Returns the average of retained values.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			getAverage () const noexcept
			{
				return m_average;
			}

		private:

			std::vector< data_t > m_values{};
			std::vector< bool > m_retainedIndexes{};
			std::vector< data_t > m_retainedValues{};
			data_t m_tolerance{0};
			data_t m_average{0};
	};
}
