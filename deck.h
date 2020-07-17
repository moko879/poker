#include "card.h"

#include <vector>

namespace poker {
    
  class Deck {
   public:
    Deck();
   private:
    std::vector<Card> cards_;
  };

}