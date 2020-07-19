#include "card.h"

#include <cassert>
#include <cstring>

namespace poker {

Card::Card()
  :  suit_(Suit::CLUBS), value_(Value::TWO) {}

Card::Card(Value value, Suit suit)
  :  suit_(suit), value_(value) {}

Card::Card(const char* str) {
  assert(strlen(str) == 2);
  value_ = ValueFromChar(str[0]);
  suit_ = SuitFromChar(str[1]);
}

Card::Card(const std::string& str) {
  assert(str.size() == 2);
  value_ = ValueFromChar(str[0]);
  suit_ = SuitFromChar(str[1]);
}

Card::Card(std::string_view str) {
  assert(str.size() == 2);
  value_ = ValueFromChar(str[0]);
  suit_ = SuitFromChar(str[1]);
}

Value Card::value() const {
  return value_;
}

Suit Card::suit() const {
  return suit_;
}

bool Card::operator==(const Card& card) const {
  return card.value() == value() && card.suit() == suit();
}
bool Card::operator!=(const Card& card) const {
  return card.value() != value() || card.suit() != suit();
}

std::ostream& operator<<(std::ostream& out, const Card& card) {
  return out
    << ValueToChar(card.value())
    << SuitToChar(card.suit());
}

std::ostream& operator<<(std::ostream& out, Suit s) {
  return out << SuitToChar(s);
}

std::ostream& operator<<(std::ostream& out, Value v) {
  return out << ValueToChar(v);
}


Suit SuitFromChar(char c) {
  switch(c) {
    case 'c':
    case 'C':
      return Suit::CLUBS;
    case 'd':
    case 'D':
      return Suit::DIAMONDS;
    case 'h':
    case 'H':
      return Suit::HEARTS;
    case 's':
    case 'S':
      return Suit::SPADES;
    default:
      assert(false);
      return Suit::CLUBS;
  }
}

Value ValueFromChar(char c) {
  switch(c) {
    case '2':
      return Value::TWO;
    case '3':
      return Value::THREE;
    case '4':
      return Value::FOUR;
    case '5':
      return Value::FIVE;
    case '6':
      return Value::SIX;
    case '7':
      return Value::SEVEN;
    case '8':
      return Value::EIGHT;
    case '9':
      return Value::NINE;
    case 't':
    case 'T':
      return Value::TEN;
    case 'j':
    case 'J':
      return Value::JACK;
    case 'q':
    case 'Q':
      return Value::QUEEN;
    case 'k':
    case 'K':
      return Value::KING;
    case 'a':
    case 'A':
      return Value::ACE;
    default:
      assert(false);
      return Value::TWO;
  }
}

char SuitToChar(Suit s) {
  switch(s) {
    case Suit::CLUBS:
      return 'c';
    case Suit::DIAMONDS:
      return 'd';
    case Suit::HEARTS:
      return 'h';
    case Suit::SPADES:
      return 's';
  }
}

char ValueToChar(Value v) {
  switch(v) {
    case Value::TWO:
      return '2';
    case Value::THREE:
      return '3';
    case Value::FOUR:
      return '4';
    case Value::FIVE:
      return '5';
    case Value::SIX:
      return '6';
    case Value::SEVEN:
      return '7';
    case Value::EIGHT:
      return '8';
    case Value::NINE:
      return '9';
    case Value::TEN:
      return 'T';
    case Value::JACK:
      return 'J';
    case Value::QUEEN:
      return 'Q';
    case Value::KING:
      return 'K';
    case Value::ACE:
      return 'A';
  }
}

} // namespace poker