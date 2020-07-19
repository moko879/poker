#include "poker_hand_calculator.h"

#include "gtest/gtest.h"

#include <tuple>

using namespace poker;
using namespace poker::internal;

class PokerHandCalculatorTest
 : public ::testing::TestWithParam<std::tuple<std::string, std::string, PokerHandType, std::string>> {};

// Checks the expected classification of the parameterized hands.
TEST_P(PokerHandCalculatorTest, Check) {
  PokerHandCalculator calc;
  std::string hand = std::get<1>(GetParam());
  PokerHandType type_exp = std::get<2>(GetParam());
  std::string tie_breakers_exp = std::get<3>(GetParam());

  for(size_t i = 0; i < hand.size(); i += 2) {
    calc.Add(hand.substr(i, 2));
  }

  std::list<Value> tie_breakers;

  EXPECT_EQ(calc.Calculate(tie_breakers), type_exp);
  ASSERT_EQ(tie_breakers.size(), tie_breakers_exp.size());

  auto itr = tie_breakers.begin();
  for(size_t i = 0; i < tie_breakers_exp.size(); ++i, ++itr) {
    EXPECT_EQ(ValueToChar(*itr), tie_breakers_exp[i]);
  }
}

INSTANTIATE_TEST_SUITE_P(
        TestPokerHands,
        PokerHandCalculatorTest,
        ::testing::Values(
          // High card
          std::make_tuple("Empty", "", PokerHandType::HIGH_CARD, ""),
          std::make_tuple("OneCard", "2h", PokerHandType::HIGH_CARD, "2"),
          std::make_tuple("TwoCards", "2hAc", PokerHandType::HIGH_CARD, "A2"),
          std::make_tuple("SevenCards", "2h3d4d6c8hJcAc", PokerHandType::HIGH_CARD, "AJ864"),

          // Pair
          std::make_tuple("Pair", "ThTd", PokerHandType::PAIR, "T"),
          std::make_tuple("PairPlusLower", "AhAdKdQhJc", PokerHandType::PAIR, "AKQJ"),
          std::make_tuple("PairPlusHigher", "2d2c3h4d5c", PokerHandType::PAIR, "2543"),
          std::make_tuple("PairPlusMixed", "ThTs3c9hAsKd", PokerHandType::PAIR, "TAK9"),

          // Two pair
          std::make_tuple("TwoPair", "ThTd9d9h", PokerHandType::TWO_PAIR, "T9"),
          std::make_tuple("TwoPairPlusLower", "AhAdKhKd2s", PokerHandType::TWO_PAIR, "AK2"),
          std::make_tuple("TwoPairPlusHigher", "4h4s3d3s2hAh", PokerHandType::TWO_PAIR, "43A"),
          std::make_tuple("ThreePair", "ThTs9h9s8h8s", PokerHandType::TWO_PAIR, "T98"),

          // Three of a kind
          std::make_tuple("ThreeKind", "ThTdTc", PokerHandType::THREE_OF_A_KIND, "T"),
          std::make_tuple("ThreeKindPlusHigher", "KhKdKsAd", PokerHandType::THREE_OF_A_KIND, "KA"),
          std::make_tuple("ThreeKindPlusLower", "9h9d9s3d4h", PokerHandType::THREE_OF_A_KIND, "943"),
          std::make_tuple("ThreeKindMixed", "4h4d4s3d2dKh", PokerHandType::THREE_OF_A_KIND, "4K3"),

          // Straight
          std::make_tuple("Straight", "9cTdJhQsKc", PokerHandType::STRAIGHT, "K"),
          std::make_tuple("StraightMin", "Ah2d3h4c5s", PokerHandType::STRAIGHT, "5"),
          std::make_tuple("StraightMax", "TdJhQsKcAs", PokerHandType::STRAIGHT, "A"),
          std::make_tuple("StraightThreeKind", "4h5d6h7d8c8d8h", PokerHandType::STRAIGHT, "8"),

          // Flush
          std::make_tuple("Flush", "Ah4h6h9hTh", PokerHandType::FLUSH, "AT964"),
          std::make_tuple("FlushSix", "2d4d6d8dTdAd", PokerHandType::FLUSH, "AT864"),
          std::make_tuple("FlushPlusExtra", "2h4h6h8hThAd", PokerHandType::FLUSH, "T8642"),
          std::make_tuple("FlushStraight", "5s6h7s8s9sTs", PokerHandType::FLUSH, "T9875"),
          std::make_tuple("DoubleFlush", "4s6s7s8s9s3d6d7d8d9d", PokerHandType::FLUSH, "98764"),
          std::make_tuple("DoubleFlushFlipped", "4d6d7d8d9d3s6s7s8s9s", PokerHandType::FLUSH, "98764"),

          // Full house
          std::make_tuple("FullHouseHighLow", "AhAdAcThTc", PokerHandType::FULL_HOUSE, "AT"),
          std::make_tuple("FullHouseLowHigh", "ThTdTcAhAc", PokerHandType::FULL_HOUSE, "TA"),
          std::make_tuple("FullHouseFlush", "5h5d5cQhQcAhKhJh", PokerHandType::FULL_HOUSE, "5Q"),
          std::make_tuple("FullHouseStraight", "8h8d8c6h6c7d9cTh", PokerHandType::FULL_HOUSE, "86"),
          std::make_tuple("DoubleFullHouse", "8h8d8c6h6c6d7d7h9c9s", PokerHandType::FULL_HOUSE, "89"),

          // Four of a kind
          std::make_tuple("FourKind", "ThTdTsTc", PokerHandType::FOUR_OF_A_KIND, "T"),
          std::make_tuple("FourKindPlusHigher", "KhKdKsKcAd", PokerHandType::FOUR_OF_A_KIND, "KA"),
          std::make_tuple("FourKindPlusLower", "9h9d9s9c3d4h", PokerHandType::FOUR_OF_A_KIND, "94"),
          std::make_tuple("DoubleFourKind", "9h9d9s9c8d8h8c8s", PokerHandType::FOUR_OF_A_KIND, "98"),

          // Straight flush
          std::make_tuple("StraightFlush", "KsQsJsTs9s", PokerHandType::STRAIGHT_FLUSH, "K"),
          std::make_tuple("StraightFlushMin", "Ah2h3h4h5h", PokerHandType::STRAIGHT_FLUSH, "5"),
          std::make_tuple("StraightFlushMax", "AsKsQsJsTs", PokerHandType::STRAIGHT_FLUSH, "A"),
          std::make_tuple("StraightFlushFourKind", "6c7c8c9cTcThTdTs", PokerHandType::STRAIGHT_FLUSH, "T"),
          std::make_tuple("DoubleStraightFlush", "6c7c8c9cTc5d6d7d8d9d", PokerHandType::STRAIGHT_FLUSH, "T"),
          std::make_tuple("DoubleStraightFlushFlipped", "6d7d8d9dTd5c6c7c8c9c", PokerHandType::STRAIGHT_FLUSH, "T")
        ),
        [](const ::testing::TestParamInfo<PokerHandCalculatorTest::ParamType>& info) {
          return std::get<0>(info.param);
        });
