#pragma once

#include "card.h"
#include "poker_hand_type.h"

#include <array>
#include <set>
#include <list>

namespace poker {
namespace internal {

// Calculates an incrementally changing hand.
class PokerHandCalculator {
 public:
  void Add(const Card& card);
  void Remove(const Card& card);

  PokerHandType Calculate(std::list<Value>& tie_breakers) const;

 private:
  struct Result {
    bool value = false;
    std::list<Value> tie_breakers;
  };

  Result HasStraightFlush() const;
  Result HasFourOfAKind() const;
  Result HasFullHouse() const;
  Result HasFlush() const;
  Result HasStraight() const;
  Result HasThreeOfAKind() const;
  Result HasTwoPair() const;
  Result HasPair() const;
  Result CheckHighCard() const;

  std::array<std::set<Value>, 4> by_suit_;
  std::array<std::set<Suit>, 13> by_value_;
};

} // namespace internal
} // namespace poker