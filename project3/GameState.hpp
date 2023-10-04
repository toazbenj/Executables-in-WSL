#pragma once
#include <string>
#include <vector>

#include "GamePiece.hpp"

class GameState {
 private:
  std::vector<GameCard> card_vec_;

 public:
  // by player
  int NumPieces(const std::string&) const;
  // by player and type
  int NumPieces(const std::string&, const std::string&) const;
  // total in play
  int NumPieces() const { return card_vec_.size(); }
  // by type for all players
  int NumType(const std::string&) const;

  void push(GameCard& card) { card_vec_.push_back(card); }
  void pop(GamePiece& piece);
  const std::vector<GameCard> GetVec() const { return card_vec_; }
};