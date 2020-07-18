#include "card.h"

#include "gtest/gtest.h"

#include <sstream>

using namespace poker;

// Test that we can construct a new card.
TEST(CardTest, DefaultConstruction) {
  Card card;

  EXPECT_EQ(card.suit(), Suit::CLUBS);
  EXPECT_EQ(card.value(), Value::TWO);
}

// Test that we can construct a new card.
TEST(CardTest, Construction) {
  Card card(Value::TWO, Suit::SPADES);

  EXPECT_EQ(card.suit(), Suit::SPADES);
  EXPECT_EQ(card.value(), Value::TWO);
}

// Test that we can construct a new card from a c-string.
TEST(CardTest, CStringConstruction) {
  Card card("Jh");

  EXPECT_EQ(card.suit(), Suit::HEARTS);
  EXPECT_EQ(card.value(), Value::JACK);
}

// Test that we can construct a new card from a string.
TEST(CardTest, StringConstruction) {
  Card card(std::string("9d"));

  EXPECT_EQ(card.suit(), Suit::DIAMONDS);
  EXPECT_EQ(card.value(), Value::NINE);
}

// Test that we can copy construct a new card.
TEST(CardTest, CopyConstruction) {
  Card card_orig(Value::THREE, Suit::SPADES);

  Card card(card_orig);

  EXPECT_EQ(card.suit(), Suit::SPADES);
  EXPECT_EQ(card.value(), Value::THREE);
}

// Test that we can move construct a new card.
TEST(CardTest, MoveConstruction) {
  Card card_orig(Value::TEN, Suit::SPADES);

  Card card(std::move(card_orig));

  EXPECT_EQ(card.suit(), Suit::SPADES);
  EXPECT_EQ(card.value(), Value::TEN);
}

// Test that we can copy a card to a different variable.
TEST(CardTest, CopyAssignment) {
  Card card_orig(Value::THREE, Suit::SPADES);
  Card card;

  card = card_orig;

  EXPECT_EQ(card.suit(), Suit::SPADES);
  EXPECT_EQ(card.value(), Value::THREE);
}

// Test that we can move a card to a different variable.
TEST(CardTest, MoveAssignment) {
  Card card_orig(Value::TEN, Suit::SPADES);
  Card card;

  card = std::move(card_orig);

  EXPECT_EQ(card.suit(), Suit::SPADES);
  EXPECT_EQ(card.value(), Value::TEN);
}

// Test that we can assign a card from a c-string.
TEST(CardTest, CStringAssignment) {
  Card card;

  card = "4s";

  EXPECT_EQ(card.suit(), Suit::SPADES);
  EXPECT_EQ(card.value(), Value::FOUR);
}

// Test that we can assign a card from a string.
TEST(CardTest, StringAssignment) {
  Card card;

  card = std::string("4s");

  EXPECT_EQ(card.suit(), Suit::SPADES);
  EXPECT_EQ(card.value(), Value::FOUR);
}

// Test that we crash for an invalid string.
TEST(CardTest, StringAssignmentCrashInvalid) {
  Card card;

  EXPECT_DEBUG_DEATH({
    card = "xx";
  }, ".*");
}

// Test that we crash for an invalid string.
TEST(CardTest, StringAssignmentCrashWrongSize) {
  Card card;

  EXPECT_DEBUG_DEATH({
    card = "";
  }, ".*");
}

// Test that we can test two identical cards for equality.
TEST(CardTest, EqualPositive) {
  Card card1(Value::JACK, Suit::HEARTS);
  Card card2(Value::JACK, Suit::HEARTS);

  EXPECT_TRUE(card1 == card2);
  EXPECT_FALSE(card1 != card2);
}

// Test that we can test two cards with different suits for equality.
TEST(CardTest, EqualNegativeSuit) {
  Card card1(Value::JACK, Suit::HEARTS);
  Card card2(Value::JACK, Suit::SPADES);

  EXPECT_FALSE(card1 == card2);
  EXPECT_TRUE(card1 != card2);
}

// Test that we can test two cards with different values for equality.
TEST(CardTest, EqualNegativeValue) {
  Card card1(Value::ACE, Suit::SPADES);
  Card card2(Value::JACK, Suit::SPADES);

  EXPECT_FALSE(card1 == card2);
  EXPECT_TRUE(card1 != card2);
}

// Test that we can output the card to an output stream.
TEST(CardTest, StreamOutput) {
  std::ostringstream sstream;
  sstream << Card(Value::ACE, Suit::HEARTS);

  EXPECT_EQ(sstream.str(), "Ah");
}

// TODO: Test to/from string conversions.