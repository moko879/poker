#include "random_deck.h"

using namespace poker;

RandomDeck::RandomDeck()
  : discarded_(0) {
    cards_.reserve(52);
    // TODO: Figure out a way to deal with enum iteration?
    for(size_t i = 0; i < 4; ++i) {
      for(size_t j = 2; j <= 14; ++j) {
        cards_.emplace_back(static_cast<Value>(j), static_cast<Suit>(i));
      }
    }
}

void RandomDeck::Reset() {
  discarded_ = 0;
}

void RandomDeck::Shuffle() {}

// Draws a random card remaining in the deck.
Card RandomDeck::Draw() {
  assert(discarded_ < cards_.size());

  std::uniform_int_distribution<size_t> distribution(0, size());

  size_t index = distribution(generator_);
  std::swap(cards_[index], cards_[discarded_]);
  ++discarded_;
  return cards_[discarded_ - 1];
}

bool RandomDeck::Return(const Card& card) {
  assert(discarded_ <= cards_.size());

  for(size_t i = 0; i < discarded_; ++i) {
    if(cards_[i] == card) {
      std::swap(cards_[i], cards_[discarded_ - 1]);
      --discarded_;
      return true;
    }
  }

  return false;
}

size_t RandomDeck::size() const {
  return cards_.size() - discarded_;
}


 //  std::uniform_int_distribution<size_t> distibution_;