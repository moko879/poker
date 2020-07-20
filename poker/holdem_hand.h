#pragma once

#include "card/card.h"
#include "poker/internal/poker_hand_calculator.h"
#include "poker/poker_hand_type.h"

#include <vector>
#include <string_view>

namespace poker {

// A poker hand compatible with any holdem-like game.  Cards can only ever be added
// to the hand, and the highest possible hand is used for comparisons.
class HoldemHand {
 public:
  HoldemHand(const std::pair<card::Card, card::Card>& pocket);
  HoldemHand(const char* str);
  HoldemHand(const std::string& str);
  HoldemHand(std::string_view str);

  HoldemHand(const HoldemHand&) = delete;
  HoldemHand(HoldemHand&&) = delete;
  ~HoldemHand() = default;

  // Adds a card to this hand.
  void AddBoardCard(const card::Card& card);

  // Returns the current type of the hand.
  PokerHandType GetType() const;

  // Returns the classification of the pocket cards.
  std::string PocketString() const;

  // Returns a string representing the detailed pocket cards.
  std::string DetailedPocketString() const;

  // Comparison operators.
  bool operator<(const HoldemHand& hand) const;
  bool operator<=(const HoldemHand& hand) const;
  bool operator==(const HoldemHand& hand) const;
  bool operator!=(const HoldemHand& hand) const;

  // I/O operators.
  friend std::ostream& operator<<(std::ostream& out, const HoldemHand& hand);

 private:
  std::pair<card::Card, card::Card> pocket_;
  internal::PokerHandCalculator calculator_;

  void Initialize(const std::pair<card::Card, card::Card>& pocket);
};

} // namespace poker