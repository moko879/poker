#pragma once

#include "card.h"

#include <vector>

namespace card {

// This is an abstract interface defining how a deck should behave.    
class Deck {
 public:
  // Resets the deck to the original state.  In other words, this
  // returns all drawn cards back to the deck.
  virtual void Reset() = 0;

  // Shuffles a deck.
  virtual void Shuffle() = 0;

  // Draws a card from the deck.
  virtual Card Draw() = 0;

  // Returns a card to the deck.  Returns true on success or false if
  // this card doesn't belong in the deck.
  virtual bool Return(const Card&) = 0;

  // Returns the current number of cards still in the deck.
  virtual size_t Size() const = 0;

  // Returns true if the deck is empty.
  virtual bool Empty() const { return Size() == 0; }
};

} // namespace card