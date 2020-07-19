#include "deck.h"

#include "gtest/gtest.h"

using namespace card;

class MockDeck : public Deck {
 public:
  MockDeck(size_t size) : size_(size) {}
  void Reset() override {}
  void Shuffle() override {}
  Card Draw() override { return Card(Value::TWO, Suit::SPADES); }
  bool Return(const Card&) override { return false; }
  size_t Size() const override { return size_; };

 private:
  size_t size_ = 0;
};

// Test the default behavior of the empty method for an empty deck.
TEST(DeckTest, DefaultEmptyPositive) {
  MockDeck deck(0);
  EXPECT_TRUE(deck.Empty());
}

// Test the default behavior of the empty method for a non-empty deck.
TEST(DeckTest, DefaultEmptyNegative) {
  MockDeck deck(1);
  EXPECT_FALSE(deck.Empty());
}