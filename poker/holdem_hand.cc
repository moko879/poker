#include "holdem_hand.h"

using namespace poker;

using card::Card;
using card::Suit;
using card::Value;

HoldemHand::HoldemHand::HoldemHand()
 : evaluated_(true), type_(PokerHandType::HIGH_CARD) {}

void HoldemHand::Add(const Card& card) {
  cards_.push_back(card);
}

size_t HoldemHand::Size() const {
  return cards_.size();
}

PokerHandType HoldemHand::Type() const {
  Evaluate();
  return type_;
}

bool HoldemHand::operator<(const HoldemHand& hand) const {
  Evaluate();
  hand.Evaluate();
  return Type() < hand.Type() || (Type() == hand.Type() && tie_breakers_ < hand.tie_breakers_);
}
bool HoldemHand::operator<=(const HoldemHand& hand) const {
  return *this == hand || *this < hand;
}
bool HoldemHand::operator==(const HoldemHand& hand) const {
  Evaluate();
  hand.Evaluate();
  return Type() == hand.Type() && tie_breakers_ == hand.tie_breakers_;
}
bool HoldemHand::operator!=(const HoldemHand& hand) const {
  return !(*this == hand);
}

void HoldemHand::Evaluate() const {
  if(evaluated_) return;

/*
  std::array<std::set<Value>, 4> by_suit;
  std::array<std::set<Suit>, 13> by_value;

  for(auto& card: cards_) {
    by_suit[static_cast<int>(card.suit())].push(card.value());
    by_value[static_cast<int>(card.value())].push(card.suit());
  }

  evaluated_ = true;*/
}