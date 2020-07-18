#pragma once

namespace poker {

enum class Suit {
  CLUBS = 0,
  DIAMONDS = 1,
  HEARTS = 2,
  SPADES = 3
};

enum class Value {
  LOW_ACE = 1,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  TEN,
  JACK,
  QUEEN,
  KING,
  ACE,
};

// This is an immutable primitive class that represents a generic card.
// TODO: generalize this further for other types of games?
class Card {
 public:
  Card(Value value = Value::TWO, Suit suit = Suit::CLUBS);
  
  Card(const Card&) = default;
  Card& operator=(const Card&) = default;
  Card(Card&&) = default;
  Card& operator=(Card&&) = default;
  ~Card() = default;

  Value value() const;
  Suit suit() const;

  // Comparison operators.
  // TODO: Add ordering operators if we can settle on a semantic.
  bool operator==(const Card& card) const;
  bool operator!=(const Card& card) const;

 private:
  Suit suit_;
  Value value_;
};

} // namespace poker