#include "card.h"

#include "gtest/gtest.h"

using namespace poker;

// Test that we can construct a new card.
TEST(Card, DefaultConstruction) {
  Card card;

  EXPECT_EQ(card.suit(), Suit::CLUBS);
  EXPECT_EQ(card.value(), Value::TWO);
}

// Test that we can construct a new card.
TEST(Card, Construction) {
  Card card(Value::TWO, Suit::SPADES);

  EXPECT_EQ(card.suit(), Suit::SPADES);
  EXPECT_EQ(card.value(), Value::TWO);
}

// Test that we can copy construct a new card.
TEST(Card, CopyConstruction) {
  Card card_orig(Value::THREE, Suit::SPADES);

  Card card(card_orig);

  EXPECT_EQ(card.suit(), Suit::SPADES);
  EXPECT_EQ(card.value(), Value::THREE);
}

// Test that we can move construct a new card.
TEST(Card, MoveConstruction) {
  Card card_orig(Value::TEN, Suit::SPADES);

  Card card(std::move(card_orig));

  EXPECT_EQ(card.suit(), Suit::SPADES);
  EXPECT_EQ(card.value(), Value::TEN);
}

// Test that we can copy a card to a different variable.
TEST(Card, CopyAssignment) {
  Card card_orig(Value::THREE, Suit::SPADES);
  Card card;

  card = card_orig;

  EXPECT_EQ(card.suit(), Suit::SPADES);
  EXPECT_EQ(card.value(), Value::THREE);
}

// Test that we can move a card to a different variable.
TEST(Card, MoveAssignment) {
  Card card_orig(Value::TEN, Suit::SPADES);
  Card card;

  card = std::move(card_orig);

  EXPECT_EQ(card.suit(), Suit::SPADES);
  EXPECT_EQ(card.value(), Value::TEN);
}

// Test that we can test two identical cards for equality.
TEST(Card, EqualPositive) {
  Card card1(Value::JACK, Suit::HEARTS);
  Card card2(Value::JACK, Suit::HEARTS);

  EXPECT_TRUE(card1 == card2);
  EXPECT_FALSE(card1 != card2);
}

// Test that we can test two cards with different suits for equality.
TEST(Card, EqualNegativeSuit) {
  Card card1(Value::JACK, Suit::HEARTS);
  Card card2(Value::JACK, Suit::SPADES);

  EXPECT_FALSE(card1 == card2);
  EXPECT_TRUE(card1 != card2);
}

// Test that we can test two cards with different values for equality.
TEST(Card, EqualNegativeValue) {
  Card card1(Value::ACE, Suit::SPADES);
  Card card2(Value::JACK, Suit::SPADES);

  EXPECT_FALSE(card1 == card2);
  EXPECT_TRUE(card1 != card2);
}