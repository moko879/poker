#pragma once

#include <ostream>
#include <string_view>

namespace card {

enum class Suit {
  CLUBS = 0,
  DIAMONDS,
  HEARTS,
  SPADES
};

enum class Value {
  TWO = 0,
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
  ACE
};

// ostream enum operators.
std::ostream& operator<<(std::ostream& out, Suit s);
std::ostream& operator<<(std::ostream& out, Value v);

// Converts a case-insensitive character to a suit.
Suit SuitFromChar(char c);

// Converts a case-insensitive character to a value.
Value ValueFromChar(char c);

// Converts a suit to a character.
char SuitToChar(Suit s);

// Converts a value to a character.
char ValueToChar(Value v);

// This is an immutable primitive class that represents a generic card.
// TODO: generalize this further for other types of games?
class Card {
 public:
  // Defaults to 2c.
  Card();
  Card(Value value, Suit suit);
  Card(const char* str);
  Card(const std::string& str);
  Card(std::string_view str);
  
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

  // I/O operators.
  friend std::ostream& operator<<(std::ostream& out, const Card& card);

 private:
  Suit suit_;
  Value value_;
};

} // namespace card