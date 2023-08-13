/*
 * Libraries/GameTools/CardDeck.hpp
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
#include <algorithm>
#include <cstddef>
#include <memory>
#include <random>
#include <vector>

/* Local inclusions for usages. */
#include "CardHand.hpp"

namespace Libraries::GameTools
{
	/**
	 * @brief The CardDeck class.
	 */
	class [[maybe_unused]] CardDeck final
	{
		public:

			enum class Where
			{
				Top,
				Bottom,
				Randomly
			};

			/**
			 * @brief Construct a card deck.
			 * @param handCount The number of hands.
			 * @param cardCount The number of cards. Default 52.
			 */
			explicit CardDeck (size_t handCount, size_t cardCount = 52) noexcept; // NOLINT(*-magic-numbers)

			/**
			 * @brief Shuffles the deck.
			 */
			void shuffle () noexcept;

			/**
			 * @brief Shuffles the discarded cards.
			 */
			void shuffleDiscardedCards () noexcept;

			/**
			 * @brief Reconstructs the deck entirely.
			 */
			void reset () noexcept;

			/**
			 * @brief Picks a card from the deck.
			 * @param hand A reference to a hand smart pointer.
			 * @param where From where to pick the card from the deck. Default from top.
			 * @return bool
			 */
			inline
			bool
			pickFromDeck (const std::shared_ptr< CardHand > & hand, Where where = Where::Top) noexcept
			{
				return this->pick(m_deck, hand, where);
			}

			/**
			 * @brief Picks a card from the discardPile.
			 * @param hand A reference to a hand smart pointer.
			 * @param pick From where to pick the card from the deck. Default from top.
			 * @return bool
			 */
			inline
			bool
			pickFromDiscardedPile (const std::shared_ptr< CardHand > & hand, Where where = Where::Top) noexcept
			{
				return this->pick(m_discardPile, hand, where);
			}

			/**
			 * @brief Releases a card to the deck.
			 * @param hand A reference to a hand smart pointer.
			 * @param card The card from the hand.
			 * @param where Where to put the card. Default top.
			 * @return bool
			 */
			inline
			bool
			release (const std::shared_ptr< CardHand > & hand, size_t card, Where where = Where::Top) noexcept
			{
				return this->insert(m_deck, hand, card, where);
			}

			/**
			 * @brief Discards a card.
			 * @param hand A reference to a hand smart pointer.
			 * @param card The card from the hand.
			 * @param where Where to put the card. Default top.
			 * @return bool
			 */
			inline
			bool
			discard (const std::shared_ptr< CardHand > & hand, size_t card, Where where = Where::Top) noexcept
			{
				return this->insert(m_discardPile, hand, card, where);
			}

			/**
			 * @brief Returns the card limit of the game.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t cardLimit () const noexcept;

			/**
			 * @brief Returns the number of hands.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t handCount () const noexcept;

			/**
			 * @brief Returns the hand list.
			 * @return const std::vector< std::shared_ptr< CardHand > > &
			 */
			[[nodiscard]]
			const std::vector< std::shared_ptr< CardHand > > & hands () const noexcept;

			/**
			 * @brief Returns the number of remaining cards in the deck.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t deckCardCount () const noexcept;

			/**
			 * @brief Returns the deck cards.
			 * @return const std::vector< size_t > &
			 */
			[[nodiscard]]
			const std::vector< size_t > & deckCards () const noexcept;

			/**
			 * @brief Returns the number of cards in the discard pile.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t discardedCardCount () const noexcept;

			/**
			 * @brief Returns the discarded cards.
			 * @return const std::vector< size_t > &
			 */
			[[nodiscard]]
			const std::vector< size_t > & discardedCards () const noexcept;

		private:

			/**
			 * @brief Picks a card from a pile.
			 * @param pile A reference to the target pile.
			 * @param hand A reference to a hand smart pointer.
			 * @param where Where to put the card.
			 * @return bool
			 */
			bool pick (std::vector< size_t > & pile, const std::shared_ptr< CardHand > & hand, Where where) noexcept;

			/**
			 * @brief Inserts a card to a pile.
			 * @param pile A reference to the target pile.
			 * @param hand A reference to a hand smart pointer.
			 * @param card The card from the hand.
			 * @param where Where to put the card.
			 * @return bool
			 */
			bool insert (std::vector< size_t > & pile, const std::shared_ptr< CardHand > & hand, size_t card, Where where) noexcept;

			size_t m_cardCount;
			std::vector< std::shared_ptr< CardHand > > m_hands{};
			std::vector< size_t > m_deck{};
			std::vector< size_t > m_discardPile{};
			std::mt19937 m_randomEngine{std::random_device{}()};
	};
}
