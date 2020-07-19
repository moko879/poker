#pragma once

#include "card/card.h"
#include "poker/internal/poker_hand_calculator.h"
#include "poker/poker_hand_type.h"

#include <vector>

namespace poker {

// A poker hand compatible with any holdem-like game.  Cards can only ever be added
// to the hand, and the highest possible hand is used for comparisons.
class HoldemHand {
 public:
  HoldemHand();
  HoldemHand(const HoldemHand&) = default;
  HoldemHand(HoldemHand&&) = default;
  ~HoldemHand() = default;

  // Adds a card to this hand.
  void Add(const card::Card& card);

  // Returns the size of the hand.
  size_t Size() const;

  // Returns the current type of the hand.
  PokerHandType Type() const;

  // Comparison operators.
  bool operator<(const HoldemHand& hand) const;
  bool operator<=(const HoldemHand& hand) const;
  bool operator==(const HoldemHand& hand) const;
  bool operator!=(const HoldemHand& hand) const;

 private:
  std::vector<card::Card> cards_;
  internal::PokerHandCalculator calculator_;
};

} // namespace poker