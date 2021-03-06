#include "card.h"

#include "gtest/gtest.h"

#include <sstream>

using namespace card;

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

// Test that we can construct a new card from a string_view.
TEST(CardTest, StringViewConstruction) {
  Card card(std::string_view("5c"));

  EXPECT_EQ(card.suit(), Suit::CLUBS);
  EXPECT_EQ(card.value(), Value::FIVE);
}

// Test that we assert for invalid length c-style strings.
TEST(CardTest, ConstructionCrashWrongCStringSize) {
  EXPECT_DEBUG_DEATH({
    Card card("");
  }, ".*");
}

// Test that we assert for invalid length strings.
TEST(CardTest, ConstructionCrashWrongStringSize) {
  EXPECT_DEBUG_DEATH({
    Card card(std::string(""));
  }, ".*");
}

// Test that we assert for invalid length string views.
TEST(CardTest, ConstructionCrashWrongStringViewSize) {
  EXPECT_DEBUG_DEATH({
    Card card(std::string_view(""));
  }, ".*");
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
    card = "??";
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

// Test that we can convert suits to characters.
TEST(SuitTest, SuitToChar) {
  EXPECT_EQ(SuitToChar(Suit::CLUBS), 'c');
  EXPECT_EQ(SuitToChar(Suit::DIAMONDS), 'd');
  EXPECT_EQ(SuitToChar(Suit::HEARTS), 'h');
  EXPECT_EQ(SuitToChar(Suit::SPADES), 's');
}

// Test that we can convert characters to suits.
TEST(SuitTest, SuitFromChar) {
  EXPECT_EQ(SuitFromChar('c'), Suit::CLUBS);
  EXPECT_EQ(SuitFromChar('C'), Suit::CLUBS);
  EXPECT_EQ(SuitFromChar('d'), Suit::DIAMONDS);
  EXPECT_EQ(SuitFromChar('D'), Suit::DIAMONDS);
  EXPECT_EQ(SuitFromChar('h'), Suit::HEARTS);
  EXPECT_EQ(SuitFromChar('H'), Suit::HEARTS);
  EXPECT_EQ(SuitFromChar('s'), Suit::SPADES);
  EXPECT_EQ(SuitFromChar('S'), Suit::SPADES);

  EXPECT_DEBUG_DEATH({
    (void)SuitFromChar('?');
  }, ".*");
}

// Test that we can output a suit to an output stream.
TEST(SuitTest, StreamOutput) {
  std::ostringstream sstream;
  sstream << Suit::SPADES;

  EXPECT_EQ(sstream.str(), "s");
}

// Test that we can convert values to characters.
TEST(ValueTest, ValueToChar) {
  EXPECT_EQ(ValueToChar(Value::TWO), '2');
  EXPECT_EQ(ValueToChar(Value::THREE), '3');
  EXPECT_EQ(ValueToChar(Value::FOUR), '4');
  EXPECT_EQ(ValueToChar(Value::FIVE), '5');
  EXPECT_EQ(ValueToChar(Value::SIX), '6');
  EXPECT_EQ(ValueToChar(Value::SEVEN), '7');
  EXPECT_EQ(ValueToChar(Value::EIGHT), '8');
  EXPECT_EQ(ValueToChar(Value::NINE), '9');
  EXPECT_EQ(ValueToChar(Value::TEN), 'T');
  EXPECT_EQ(ValueToChar(Value::JACK), 'J');
  EXPECT_EQ(ValueToChar(Value::QUEEN), 'Q');
  EXPECT_EQ(ValueToChar(Value::KING), 'K');
  EXPECT_EQ(ValueToChar(Value::ACE), 'A');
}

// Test that we can convert characters to values.
TEST(ValueTest, ValueFromChar) {
  EXPECT_EQ(ValueFromChar('2'), Value::TWO);
  EXPECT_EQ(ValueFromChar('3'), Value::THREE);
  EXPECT_EQ(ValueFromChar('4'), Value::FOUR);
  EXPECT_EQ(ValueFromChar('5'), Value::FIVE);
  EXPECT_EQ(ValueFromChar('6'), Value::SIX);
  EXPECT_EQ(ValueFromChar('7'), Value::SEVEN);
  EXPECT_EQ(ValueFromChar('8'), Value::EIGHT);
  EXPECT_EQ(ValueFromChar('9'), Value::NINE);
  EXPECT_EQ(ValueFromChar('T'), Value::TEN);
  EXPECT_EQ(ValueFromChar('t'), Value::TEN);
  EXPECT_EQ(ValueFromChar('J'), Value::JACK);
  EXPECT_EQ(ValueFromChar('j'), Value::JACK);
  EXPECT_EQ(ValueFromChar('Q'), Value::QUEEN);
  EXPECT_EQ(ValueFromChar('q'), Value::QUEEN);
  EXPECT_EQ(ValueFromChar('K'), Value::KING);
  EXPECT_EQ(ValueFromChar('k'), Value::KING);
  EXPECT_EQ(ValueFromChar('A'), Value::ACE);
  EXPECT_EQ(ValueFromChar('a'), Value::ACE);

  EXPECT_DEBUG_DEATH({
    (void)ValueFromChar('?');
  }, ".*");
}

// Test that we can output a suit to an output stream.
TEST(ValueTest, StreamOutput) {
  std::ostringstream sstream;
  sstream << Value::JACK;

  EXPECT_EQ(sstream.str(), "J");
}
