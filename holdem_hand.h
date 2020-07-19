#pragma once

#include "card/card.h"

#include <vector>

namespace poker {

enum class PokerHandType {
  HIGH_CARD,
  PAIR,
  TWO_PAIR,
  THREE_OF_A_KIND,
  STRAIGHT,
  FLUSH,
  FULLHOUSE,
  FOUR_OF_A_KIND,
  STRAIGHT_FLUSH
};

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
  void Evaluate() const;

  std::vector<card::Card> cards_;

  // Cached evaluation of the hand.  Only calculated on-demand for efficiency.
  mutable bool evaluated_;
  mutable PokerHandType type_;
  mutable std::vector<card::Value> tie_breakers_;
};

} // namespace poker