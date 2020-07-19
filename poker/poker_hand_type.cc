#include "poker_hand_type.h"

namespace poker {

std::ostream& operator<<(std::ostream& out, const PokerHandType& s) {
  switch(s) {
    case PokerHandType::HIGH_CARD:
      out << "HIGH_CARD";
      break;
    case PokerHandType::PAIR:
      out << "PAIR";
      break;
    case PokerHandType::TWO_PAIR:
      out << "TWO_PAIR";
      break;
    case PokerHandType::THREE_OF_A_KIND:
      out << "THREE_OF_A_KIND";
      break;
    case PokerHandType::STRAIGHT:
      out << "STRAIGHT";
      break;
    case PokerHandType::FLUSH:
      out << "FLUSH";
      break;
    case PokerHandType::FULL_HOUSE:
      out << "FULL_HOUSE";
      break;
    case PokerHandType::FOUR_OF_A_KIND:
      out << "FOUR_OF_A_KIND";
      break;
    case PokerHandType::STRAIGHT_FLUSH:
      out << "STRAIGHT_FLUSH";
      break;
    default:
      out << "???";
      break;
  }
  return out;
}

}