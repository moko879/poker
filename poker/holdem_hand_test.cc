#include "holdem_hand.h"

#include "gtest/gtest.h"

#include <vector>

using namespace poker;

using card::Card;

// Test that we can construct a hand from a pair of card objects.
TEST(HoldemHandTest, ConstructCards) {
  std::pair<Card, Card> cards{"2h", "2s"};
  HoldemHand hand(cards);

  EXPECT_EQ(hand.DetailedPocketString(), "2h2s");
}

// Test that we can construct a hand from a string.
TEST(HoldemHandTest, ConstructString) {
  HoldemHand hand(std::string("3h3c"));

  EXPECT_EQ(hand.DetailedPocketString(), "3h3c");
}

// Test that we can construct a hand from a c-style string.
TEST(HoldemHandTest, ConstructCString) {
  HoldemHand hand("8c9c");

  EXPECT_EQ(hand.DetailedPocketString(), "8c9c");
}

// Test that we can construct a hand from a string_view.
TEST(HoldemHandTest, ConstructStringView) {
  HoldemHand hand(std::string_view("5d5s"));

  EXPECT_EQ(hand.DetailedPocketString(), "5d5s");
}

// Test the info we provide for a pocket pair.
TEST(HoldemHandTest, InfoPocketPair) {
  HoldemHand hand("AhAs");

  EXPECT_EQ(hand.GetType(), PokerHandType::PAIR);
  EXPECT_EQ(hand.PocketString(), "AA");
  EXPECT_EQ(hand.DetailedPocketString(), "AhAs");
}

// Test the info we provide for descending suited pocket cards.
TEST(HoldemHandTest, InfoSuitedDescending) {
  HoldemHand hand("AhKh");

  EXPECT_EQ(hand.GetType(), PokerHandType::HIGH_CARD);
  EXPECT_EQ(hand.PocketString(), "AKs");
  EXPECT_EQ(hand.DetailedPocketString(), "AhKh");
}

// Test the info we provide for ascending suited pocket cards.
TEST(HoldemHandTest, InfoSuitedAscending) {
  HoldemHand hand("KcAc");

  EXPECT_EQ(hand.GetType(), PokerHandType::HIGH_CARD);
  EXPECT_EQ(hand.PocketString(), "AKs");
  EXPECT_EQ(hand.DetailedPocketString(), "KcAc");
}

// Test the info we provide for ascending unsuited pocket cards.
TEST(HoldemHandTest, InfoUnsuitedDescending) {
  HoldemHand hand("KhQs");

  EXPECT_EQ(hand.GetType(), PokerHandType::HIGH_CARD);
  EXPECT_EQ(hand.PocketString(), "KQ");
  EXPECT_EQ(hand.DetailedPocketString(), "KhQs");
}

// Test the info we provide for ascending unsuited pocket cards.
TEST(HoldemHandTest, InfoUnsuitedAscending) {
  HoldemHand hand("QhKs");

  EXPECT_EQ(hand.GetType(), PokerHandType::HIGH_CARD);
  EXPECT_EQ(hand.PocketString(), "KQ");
  EXPECT_EQ(hand.DetailedPocketString(), "QhKs");
}

// Test that we can output the hand to an output stream.
TEST(HoldemHandTest, StreamOutput) {
  std::ostringstream sstream;
  HoldemHand hand("QhKs");
  sstream << HoldemHand("QhKs");

  EXPECT_EQ(sstream.str(), "QhKs");
}

// Test hands, parameterized by the two hands and the board.
class HoldemHandTest
 : public ::testing::TestWithParam<std::tuple<std::string, std::string, std::string, std::string>> {
  protected:
    HoldemHandTest()
     : hand1_(std::get<1>(GetParam())),
       hand2_(std::get<2>(GetParam())) {
      std::string board_str = std::get<3>(GetParam());
      for(size_t i = 0; i < board_str.size(); i += 2) {
        Card card(board_str.substr(i, 2));
        hand1_.AddBoardCard(card);
        hand2_.AddBoardCard(card);
      }

    }

    HoldemHand hand1_;
    HoldemHand hand2_;
 };

class HoldemHandDifferentTest : public HoldemHandTest {};

// Test the less than operator.
TEST_P(HoldemHandDifferentTest, LessThan) {
  EXPECT_LT(hand1_, hand2_);
}

// Test the less than or equal to operator.
TEST_P(HoldemHandDifferentTest, LessThanEqual) {
  EXPECT_LE(hand1_, hand2_);
}

// Test the not equals operator.
TEST_P(HoldemHandDifferentTest, NotEqual) {
  EXPECT_NE(hand1_, hand2_);
}

INSTANTIATE_TEST_SUITE_P(
        LessThanHands,
        HoldemHandDifferentTest,
        ::testing::Values(
          std::make_tuple("PocketPairs", "KhKs", "AhAs", ""),
          std::make_tuple("PocketHighCard", "AsQs", "AhKs", ""),
          std::make_tuple("FlopTrips", "9hTs", "8h8s", "8c9sTc"),
          std::make_tuple("RiverRoyalFlush", "2h2s", "KsQs", "2c2dTsJsAs")
        ),
        [](const ::testing::TestParamInfo<HoldemHandDifferentTest::ParamType>& info) {
          return std::get<0>(info.param);
        });

class HoldemHandSameTest : public HoldemHandTest {};

// Test the equals operator.
TEST_P(HoldemHandSameTest, EqualTo) {
  EXPECT_EQ(hand1_, hand2_);
}

INSTANTIATE_TEST_SUITE_P(
        IdenticalHands,
        HoldemHandSameTest,
        ::testing::Values(
          std::make_tuple("PocketPairs", "KhKs", "KcKd", ""),
          std::make_tuple("Board", "AsQs", "AhKh", "2c3c4c5c6c"),
          std::make_tuple("SameStraight", "8h9s", "9s9c", "8c7s6h5c")
        ),
        [](const ::testing::TestParamInfo<HoldemHandSameTest::ParamType>& info) {
          return std::get<0>(info.param);
        });
