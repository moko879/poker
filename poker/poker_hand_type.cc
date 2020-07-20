#include "poker_hand_type.h"

namespace poker {

std::ostream& operator<<(std::ostream& out, const PokerHandType& s) {
  switch(s) {
    case PokerHandType::HIGH_CARD:
      return out << "HIGH_CARD";
    case PokerHandType::PAIR:
      return out << "PAIR";
    case PokerHandType::TWO_PAIR:
      return out << "TWO_PAIR";
    case PokerHandType::THREE_OF_A_KIND:
      return out << "THREE_OF_A_KIND";
    case PokerHandType::STRAIGHT:
      return out << "STRAIGHT";
    case PokerHandType::FLUSH:
      return out << "FLUSH";
    case PokerHandType::FULL_HOUSE:
      return out << "FULL_HOUSE";
    case PokerHandType::FOUR_OF_A_KIND:
      return out << "FOUR_OF_A_KIND";
    case PokerHandType::STRAIGHT_FLUSH:
      return out << "STRAIGHT_FLUSH";
  }
}

}