#include "card.h"

using namespace poker;

Card::Card(Value value, Suit suit)
  :  suit_(suit), value_(value) {}

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
