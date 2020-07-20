#include "holdem_hand.h"
#include "util/assert.h"

#include <sstream>

using card::Card;
using card::Suit;
using card::Value;

namespace poker {

void HoldemHand::Initialize(const std::pair<card::Card, card::Card>& pocket) {
  pocket_ = pocket;
  calculator_.Add(pocket.first);
  calculator_.Add(pocket.second);  
}

HoldemHand::HoldemHand::HoldemHand(const std::pair<Card, Card>& pocket) {
  Initialize(pocket);
}

HoldemHand::HoldemHand(const char* str) {
  CHECK(strlen(str) == 4);
  std::string_view str_view(str);
  Initialize({str_view.substr(0,2), str_view.substr(2,2)});
}

HoldemHand::HoldemHand(const std::string& str) {
  CHECK(str.size() == 4);
  std::string_view str_view(str);
  Initialize({str_view.substr(0,2), str_view.substr(2,2)});
}

HoldemHand::HoldemHand(std::string_view str) {
  CHECK(str.size() == 4);
  Initialize({str.substr(0,2), str.substr(2,2)});
}

void HoldemHand::AddBoardCard(const Card& card) {
  calculator_.Add(card);
}

PokerHandType HoldemHand::GetType() const {
  return calculator_.GetResult().type;
}

std::string HoldemHand::PocketString() const {
  std::string str;
  if(pocket_.first.value() >= pocket_.second.value()) {
    str += ValueToChar(pocket_.first.value());
    str += ValueToChar(pocket_.second.value());
  } else {
    str += ValueToChar(pocket_.second.value());
    str += ValueToChar(pocket_.first.value());
  }
  if(pocket_.first.suit() == pocket_.second.suit()) {
    str += 's';
  }
  return str;
}

std::string HoldemHand::DetailedPocketString() const {
  std::ostringstream sstream;
  sstream << pocket_.first << pocket_.second;
  return sstream.str();
}

bool HoldemHand::operator<(const HoldemHand& hand) const {
  return GetType() < hand.GetType() || (GetType() == hand.GetType() &&
    calculator_.GetResult().tie_breakers < hand.calculator_.GetResult().tie_breakers);
}
bool HoldemHand::operator<=(const HoldemHand& hand) const {
  return *this == hand || *this < hand;
}
bool HoldemHand::operator>(const HoldemHand& hand) const {
  return (hand < *this);
}
bool HoldemHand::operator>=(const HoldemHand& hand) const {
  return (hand <= *this);
}
bool HoldemHand::operator==(const HoldemHand& hand) const {
  return GetType() == hand.GetType() && calculator_.GetResult().tie_breakers == hand.calculator_.GetResult().tie_breakers;
}
bool HoldemHand::operator!=(const HoldemHand& hand) const {
  return !(*this == hand);
}

std::ostream& operator<<(std::ostream& out, const HoldemHand& hand) {
  return out << hand.DetailedPocketString();
}

} // namespace poker