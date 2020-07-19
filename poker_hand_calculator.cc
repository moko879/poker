#include "poker_hand_calculator.h"

#include <optional>

using namespace poker;
using namespace poker::internal;

void PokerHandCalculator::Add(const Card& card) {
  auto suit_result = by_suit_[static_cast<int>(card.suit())].insert(card.value());
  assert(suit_result.second);
  
  auto value_result = by_value_[static_cast<int>(card.value())].insert(card.suit());
  assert(value_result.second);
}
void PokerHandCalculator::Remove(const Card& card) {
  auto suit_result = by_suit_[static_cast<int>(card.suit())].erase(card.value());
  assert(suit_result == 1);

  auto value_result = by_value_[static_cast<int>(card.value())].erase(card.suit());
  assert(value_result == 1);
}

PokerHandType PokerHandCalculator::Calculate(std::list<Value>& tie_breakers) const {
  PokerHandCalculator::Result result;
  if(result = HasStraightFlush(); result.value) {
    tie_breakers = std::move(result.tie_breakers);
    return PokerHandType::STRAIGHT_FLUSH;
  } else if(result = HasFourOfAKind(); result.value) {
    tie_breakers = std::move(result.tie_breakers);
    return PokerHandType::FOUR_OF_A_KIND;
  } else if(result = HasFullHouse(); result.value) {
    tie_breakers = std::move(result.tie_breakers);
    return PokerHandType::FULL_HOUSE;
  } else if(result = HasFlush(); result.value) {
    tie_breakers = std::move(result.tie_breakers);
    return PokerHandType::FLUSH;
  } else if(result = HasStraight(); result.value) {
    tie_breakers = std::move(result.tie_breakers);
    return PokerHandType::STRAIGHT;
  } else if(result = HasThreeOfAKind(); result.value) {
    tie_breakers = std::move(result.tie_breakers);
    return PokerHandType::THREE_OF_A_KIND;
  } else if(result = HasTwoPair(); result.value) {
    tie_breakers = std::move(result.tie_breakers);
    return PokerHandType::TWO_PAIR;
  } else if(result = HasPair(); result.value) {
    tie_breakers = std::move(result.tie_breakers);
    return PokerHandType::PAIR;
  } else {
    result = CheckHighCard();
    tie_breakers = std::move(result.tie_breakers);
    return PokerHandType::HIGH_CARD; 
  }
}

PokerHandCalculator::Result PokerHandCalculator::HasStraightFlush() const {
  int best_high_card = -1;
  for(int i = 0; i < 4; ++i) {
    if(by_suit_[i].size() < 5) continue;

    int high_card = 12;
    int size = 0;
    bool ace = false;
    for(auto itr = by_suit_[i].rbegin(); itr != by_suit_[i].rend(); ++itr) {
      // Bail once we can't produce a better straight flush.
      if(high_card <= best_high_card) break;

      // Check if this is an ace.
      if(*itr == Value::ACE) ace = true;

      // Upate the straight flush or reset it.
      if(high_card == static_cast<int>(*itr) + size) {
        ++size;
        if(size == 5) break;
      } else {
        high_card = static_cast<int>(*itr);
        size = 1;
      }
    }

    // Handle low ace exception.
    if(size == 4 && ace &&
       high_card == static_cast<int>(Value::FIVE)) {
      ++size;
    }

    if(size == 5) {
      best_high_card = std::max(high_card, best_high_card);
    }
  }

  return {
    .value = (best_high_card > 0),
    .tie_breakers = { static_cast<Value>(best_high_card) }
  };
}
PokerHandCalculator::Result PokerHandCalculator::HasFourOfAKind() const {
  Result result;
  std::optional<Value> primary = std::nullopt;
  std::optional<Value> secondary = std::nullopt;
  for(int i = 12; i >= 0; --i) {
    if(!primary && by_value_[i].size() == 4) {
      primary = static_cast<Value>(i);
    } else if(!secondary && !by_value_[i].empty()) {
      secondary = static_cast<Value>(i);
    }
  }
  if(!primary) {
    return result;
  }

  result.tie_breakers.push_back(*primary);
  if(secondary) {
    result.tie_breakers.push_back(*secondary);
  }
  result.value = true;
  return result;
}
PokerHandCalculator::Result PokerHandCalculator::HasFullHouse() const {
  Result result;
  std::optional<Value> primary = std::nullopt;
  std::optional<Value> secondary = std::nullopt;
  for(int i = 12; i >= 0; --i) {
    if(!primary && by_value_[i].size() == 3) {
      primary = static_cast<Value>(i);
    } else if(!secondary && by_value_[i].size() >= 2) {
      secondary = static_cast<Value>(i);
    }
  }
  if(!primary || !secondary) {
    return result;
  }

  result.tie_breakers.push_back(*primary);
  result.tie_breakers.push_back(*secondary);
  result.value = true;
  return result;
}
PokerHandCalculator::Result PokerHandCalculator::HasFlush() const {
  Result result;
  for(int i = 0; i < 4; ++i) {
    if(by_suit_[i].size() < 5) continue;

    std::list<Value> tie_breakers;
    for(auto itr = by_suit_[i].rbegin(); itr != by_suit_[i].rend(); ++itr) {
      tie_breakers.push_back(*itr);
      if(tie_breakers.size() == 5) break;
    }
    if(result.tie_breakers.empty() || result.tie_breakers < tie_breakers) {
      result.tie_breakers = std::move(tie_breakers);
      result.value = true;
    }
  }

  return result;
}
PokerHandCalculator::Result PokerHandCalculator::HasStraight() const {
  int high_card = 12;
  int size = 0;
  for(int i = 12; i >= 0; --i) {
    if(by_value_[i].empty()) continue;

    if(high_card == i + size) {
      ++size;
      if(size == 5) break;
    } else {
      high_card = i;
      size = 1;
    }
  }

  // Handle low ace exception.
  if(size == 4 &&
     high_card == static_cast<int>(Value::FIVE) &&
     !by_value_[static_cast<int>(Value::ACE)].empty()) {
    ++size;
  }

  return {
    .value = (size == 5),
    .tie_breakers = { static_cast<Value>(high_card) }
  };
}
PokerHandCalculator::Result PokerHandCalculator::HasThreeOfAKind() const {
  Result result;
  std::optional<Value> primary = std::nullopt;
  std::optional<Value> secondary = std::nullopt;
  std::optional<Value> tertiary = std::nullopt;
  for(int i = 12; i >= 0; --i) {
    if(!primary && by_value_[i].size() >= 3) {
      primary = static_cast<Value>(i);
    } else if(!secondary && !by_value_[i].empty()) {
      secondary = static_cast<Value>(i);
      if(by_value_[i].size() >= 2) {
        tertiary = static_cast<Value>(i);
      }
    } else if(!tertiary && !by_value_[i].empty()) {
      tertiary = static_cast<Value>(i);
    }
  }
  if(!primary) {
    return result;
  }

  result.tie_breakers.push_back(*primary);
  if(secondary) {
    result.tie_breakers.push_back(*secondary);
  }
  if(tertiary) {
    result.tie_breakers.push_back(*tertiary);
  }
  result.value = true;
  return result;
}
PokerHandCalculator::Result PokerHandCalculator::HasTwoPair() const {
  Result result;
  std::optional<Value> high_pair = std::nullopt;
  std::optional<Value> low_pair = std::nullopt;
  std::optional<Value> high_card = std::nullopt;
  for(int i = 12; i >= 0; --i) {
    if(!high_pair && by_value_[i].size() == 2) {
      high_pair = static_cast<Value>(i);
    } else if(!low_pair && by_value_[i].size() == 2) {
      low_pair = static_cast<Value>(i);
    } else if(!high_card && !by_value_[i].empty()) {
      high_card = static_cast<Value>(i);
    }
  }
  if(!high_pair || !low_pair) {
    return result;
  }

  result.tie_breakers.push_back(*high_pair);
  result.tie_breakers.push_back(*low_pair);

  if(high_card) {
    result.tie_breakers.push_back(*high_card);
  }
  result.value = true;
  return result;
}
PokerHandCalculator::Result PokerHandCalculator::HasPair() const {
  Result result;
  std::optional<Value> pair = std::nullopt;
  for(int i = 12; i >= 0; --i) {
    if(!pair && by_value_[i].size() == 2) {
      pair = static_cast<Value>(i);
    } else {
      for(size_t j = 0; j < by_value_[i].size() && result.tie_breakers.size() < 3; ++j) {
        result.tie_breakers.push_back(static_cast<Value>(i));
      }
    }
  }
  if(!pair) {
    return result;
  }

  result.tie_breakers.push_front(*pair);
  result.value = true;
  return result;
}
PokerHandCalculator::Result PokerHandCalculator::CheckHighCard() const {
  Result result;
  for(int i = 12; i >= 0; --i) {
    if(result.tie_breakers.size() >= 5) break;

    for(size_t j = 0; j < by_value_[i].size() && result.tie_breakers.size() < 5; ++j) {
      result.tie_breakers.push_back(static_cast<Value>(i));
    }
  }

  result.value = true;
  return result;
}