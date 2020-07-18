#pragma once

#include "card.h"
#include "deck.h"

#include <random>

namespace poker {

// This represents a deck that always provides random cards.  These decks never need to be shuffled.
// TODO: parameterize this by generator?
class RandomDeck : public Deck {
 public:
  // Creates a new random deck out.
  RandomDeck();
  // TODO: operators, other constructors

  void Reset() override;

  // This does nothing since we always draw randomly.
  void Shuffle() override;

  // Draws a random card remaining in the deck.  Asserts if the deck is empty.
  Card Draw() override;

  // Note: Runs in O(N) time where N is the number of discarded cards.
  bool Return(const Card&) override;

  size_t size() const override;

 private:
  size_t discarded_;
  std::vector<Card> cards_;
  std::default_random_engine generator_;
};

} // namespace poker