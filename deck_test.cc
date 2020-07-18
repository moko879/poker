#include "deck.h"

#include "gtest/gtest.h"

using namespace poker;

class MockDeck : public Deck {
 public:
  MockDeck(size_t size) : size_(size) {}
  void Reset() override {}
  void Shuffle() override {}
  Card Draw() override { return Card(Value::TWO, Suit::SPADES); }
  bool Return(const Card&) override { return false; }
  size_t size() const override { return size_; };

 private:
  size_t size_ = 0;
};

// Test the default behavior of the empty method for an empty deck.
TEST(Deck, DefaultEmptyPositive) {
  MockDeck deck(0);
  EXPECT_TRUE(deck.empty());
}

// Test the default behavior of the empty method for a non-empty deck.
TEST(Deck, DefaultEmptyNegative) {
  MockDeck deck(1);
  EXPECT_FALSE(deck.empty());
}