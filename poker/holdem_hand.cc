#include "holdem_hand.h"

using namespace poker;

using card::Card;
using card::Suit;
using card::Value;

HoldemHand::HoldemHand::HoldemHand() {}

void HoldemHand::Add(const Card& card) {
  cards_.push_back(card);
  calculator_.Add(card);
}

size_t HoldemHand::Size() const {
  return cards_.size();
}

PokerHandType HoldemHand::Type() const {
  return calculator_.GetResult().type;
}

bool HoldemHand::operator<(const HoldemHand& hand) const {
  return Type() < hand.Type() || (Type() == hand.Type() &&
    calculator_.GetResult().tie_breakers < hand.calculator_.GetResult().tie_breakers);
}
bool HoldemHand::operator<=(const HoldemHand& hand) const {
  return *this == hand || *this < hand;
}
bool HoldemHand::operator==(const HoldemHand& hand) const {
  return Type() == hand.Type() && calculator_.GetResult().tie_breakers == hand.calculator_.GetResult().tie_breakers;
}
bool HoldemHand::operator!=(const HoldemHand& hand) const {
  return !(*this == hand);
}
