#pragma once

#include "card/card.h"
#include "poker/poker_hand_type.h"

#include <array>
#include <set>
#include <list>
#include <optional>

namespace poker {
namespace internal {

// Calculates an incrementally changing hand.
class PokerHandCalculator {
 public:
  void Add(const card::Card& card);
  void Remove(const card::Card& card);

  struct Result {
    PokerHandType type;
    std::list<card::Value> tie_breakers;
  };

  const Result& GetResult() const;

 private:
  struct TypeResult {
    bool value = false;
    std::list<card::Value> tie_breakers;
  };

  TypeResult HasStraightFlush() const;
  TypeResult HasFourOfAKind() const;
  TypeResult HasFullHouse() const;
  TypeResult HasFlush() const;
  TypeResult HasStraight() const;
  TypeResult HasThreeOfAKind() const;
  TypeResult HasTwoPair() const;
  TypeResult HasPair() const;
  TypeResult HasHighCard() const;

  std::array<std::set<card::Value>, 4> by_suit_;
  std::array<std::set<card::Suit>, 13> by_value_;
  mutable std::optional<Result> cached_;
};

} // namespace internal
} // namespace poker