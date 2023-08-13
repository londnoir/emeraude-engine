/*
 * Libraries/GameTools/CardDeck.cpp
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

#include "CardDeck.hpp"

/* C/C++ standard libraries. */
#include <random>

/* Local inclusions. */
#include "Utility.hpp"

namespace Libraries::GameTools
{
	CardDeck::CardDeck (size_t handCount, size_t cardCount) noexcept
		: m_cardCount(cardCount)
	{
		/* Initialize each hand. */
		m_hands.resize(handCount);

		std::generate(m_hands.begin(), m_hands.end(), [cardCount] () {
			return std::make_shared< CardHand >(cardCount);
		});

		/* Reserve space in the discard pile. */
		m_discardPile.reserve(m_cardCount);

		/* Set the initial state. */
		this->reset();
	}

	void
	CardDeck::shuffle () noexcept
	{
		std::shuffle(m_deck.begin(), m_deck.end(), m_randomEngine);
	}

	void
	CardDeck::shuffleDiscardedCards () noexcept
	{
		std::shuffle(m_discardPile.begin(), m_discardPile.end(), m_randomEngine);
	}

	void
	CardDeck::reset () noexcept
	{
		/* Reset all hands. */
		for ( auto & hand : m_hands )
		{
			hand->m_cards.clear();
		}

		/* Replenish the deck. */
		m_deck.resize(m_cardCount);

		std::generate(m_deck.begin(), m_deck.end(), [number = 0] () mutable {
			return number++;
		});

		/* Reset discard pile. */
		m_discardPile.clear();

		/* Set a new seed for the random engine. */
		{
			const auto seed = std::random_device{}();

			m_randomEngine.seed(seed);
		}
	}

	bool
	CardDeck::pick (std::vector< size_t > & pile, const std::shared_ptr< CardHand > & hand, Where where) noexcept
	{
		if ( hand == nullptr )
		{
			return false;
		}

		if ( std::find(m_hands.cbegin(), m_hands.cend(), hand) == m_hands.end() )
		{
			return false;
		}

		/* NOTE: No more card. */
		if ( pile.empty() )
		{
			return false;
		}

		std::vector< size_t >::iterator pickedIterator;

		switch ( where )
		{
			case Where::Top :
				pickedIterator = pile.begin();
				break;

			case Where::Bottom :
				pickedIterator = std::prev(pile.end());

				break;

			case Where::Randomly :
				pickedIterator = pile.begin() + std::uniform_int_distribution{0, static_cast< int >(pile.size() - 1)}(m_randomEngine);
				break;
		}

		const auto pickedCard = *pickedIterator;

		/* NOTE: Remove it from the targeted pile. */
		pile.erase(pickedIterator);

		/* NOTE: Push it to the hand. */
		hand->m_cards.push_back(pickedCard);

		return true;
	}

	bool
	CardDeck::insert (std::vector< size_t > & pile, const std::shared_ptr< CardHand > & hand, size_t card, Where where) noexcept
	{
		if ( hand == nullptr )
		{
			return false;
		}

		if ( std::find(m_hands.cbegin(), m_hands.cend(), hand) == m_hands.end() )
		{
			return false;
		}

		auto & handCards = hand->m_cards;

		/* NOTE: No card in hand. */
		if ( handCards.empty() )
		{
			return false;
		}

		/* NOTE: The card is not in hand. */
		auto pickedIterator = std::find(handCards.begin(), handCards.end(), card);

		if ( pickedIterator == handCards.end() )
		{
			return false;
		}

		/* NOTE: Remove it from the hand. */
		handCards.erase(pickedIterator);

		/* NOTE: Push it to the targeted pile. */
		switch ( where )
		{
			case Where::Top :
				pile.insert(pile.begin(), card);
				break;

			case Where::Bottom :
				pile.push_back(card);
				break;

			case Where::Randomly :
				const auto randomPosition = pile.begin() + std::uniform_int_distribution{0, static_cast< int >(pile.size() - 1)}(m_randomEngine);

				pile.insert(randomPosition, card);
				break;
		}

		return true;
	}

	size_t
	CardDeck::cardLimit () const noexcept
	{
		return m_cardCount;
	}

	const std::vector< std::shared_ptr< CardHand > > &
	CardDeck::hands () const noexcept
	{
		return m_hands;
	}

	size_t
	CardDeck::handCount () const noexcept
	{
		return m_hands.size();
	}

	size_t
	CardDeck::deckCardCount () const noexcept
	{
		return m_deck.size();
	}

	const std::vector< size_t > &
	CardDeck::deckCards () const noexcept
	{
		return m_deck;
	}

	size_t
	CardDeck::discardedCardCount () const noexcept
	{
		return m_discardPile.size();
	}

	const std::vector< size_t > &
	CardDeck::discardedCards () const noexcept
	{
		return m_discardPile;
	}
}
