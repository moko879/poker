#include "random_deck.h"

#include "gtest/gtest.h"

using namespace poker;

// Test that we can construct a new random deck.
TEST(RandomDeckTest, Construction) {
  RandomDeck deck;

  EXPECT_EQ(deck.Size(), 52U);
}

// Test that we can draw a card.
TEST(RandomDeckTest, Draw) {
  RandomDeck deck;
  (void) deck.Draw();

  EXPECT_EQ(deck.Size(), 51U);
}

// Test that we crash if we try to draw on an empty deck.
TEST(RandomDeckTest, DrawEmpty) {
  RandomDeck deck;

  while(!deck.Empty()) (void)deck.Draw();
  ASSERT_EQ(deck.Size(), 0U);

  EXPECT_DEBUG_DEATH({ deck.Draw(); }, ".*");
  EXPECT_EQ(deck.Size(), 0U);
}

// Test that we can reset a deck after drawing a card.
TEST(RandomDeckTest, Reset) {
  RandomDeck deck;
  (void) deck.Draw();
  deck.Reset();

  EXPECT_EQ(deck.Size(), 52U);
}

// Test that we can reset a deck with no missing cards.
TEST(RandomDeckTest, ResetFull) {
  RandomDeck deck;
  deck.Reset();

  EXPECT_EQ(deck.Size(), 52U);
}

// Test that we can attempt to shuffle a deck, which should do nothing.
TEST(RandomDeckTest, Shuffle) {
  RandomDeck deck;
  (void) deck.Draw();
  deck.Shuffle();

  EXPECT_EQ(deck.Size(), 51U);
}

// Test that we can return a drawn card to the deck.
TEST(RandomDeckTest, ReturnPositive) {
  RandomDeck deck;
  Card card = deck.Draw();

  ASSERT_EQ(deck.Size(), 51U);
  EXPECT_TRUE(deck.Return(card));
  EXPECT_EQ(deck.Size(), 52U);
}

// Test that we can return a drawn card to the deck.
TEST(RandomDeckTest, ReturnNegative) {
  RandomDeck deck;
  Card card(Value::JACK, Suit::HEARTS);

  ASSERT_EQ(deck.Size(), 52U);
  EXPECT_FALSE(deck.Return(card));
  EXPECT_EQ(deck.Size(), 52U);
}
