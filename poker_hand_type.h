#pragma once

#include <ostream>

namespace poker {

enum class PokerHandType {
  HIGH_CARD,
  PAIR,
  TWO_PAIR,
  THREE_OF_A_KIND,
  STRAIGHT,
  FLUSH,
  FULL_HOUSE,
  FOUR_OF_A_KIND,
  STRAIGHT_FLUSH
};

std::ostream& operator<<(std::ostream& out, const PokerHandType& s);

} // namespace poker