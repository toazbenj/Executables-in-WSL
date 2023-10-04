#include "GameState.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "GamePiece.hpp"
using std::string;
using std::vector;

int GameState::NumPieces(const string& player_name) const {
  int cnt = 0;
  for (GameCard card : card_vec_) {
    if (card.player_name_ == player_name) {
      cnt++;
    }
  }
  return cnt;
}

int GameState::NumPieces(const string& player_name,
                         const string& piece_type) const {
  int cnt = 0;
  for (GameCard card : card_vec_) {
    if (card.player_name_ == player_name && card.piece_type_ == piece_type) {
      cnt++;
    }
  }
  return cnt;
}

// count pieces of certain type across all players
int GameState::NumType(const string& piece_type) const {
  int cnt = 0;
  for (GameCard card : card_vec_) {
    if (card.piece_type_ == piece_type) {
      cnt++;
    }
  }
  return cnt;
}

// remove card from GameState data member
void GameState::pop(GamePiece& piece) {
  // create matching card from piece
  GameCard pop_card;
  pop_card.player_name_ = piece.GetPlayer();
  pop_card.piece_type_ = piece.GetType();

  for (int i = 0; i < (int)card_vec_.size(); i++) {
    GameCard current_card = card_vec_.at(i);

    // if card matchees, remove from GameState data member
    if (current_card.player_name_ == pop_card.player_name_ &&
        current_card.piece_type_ == pop_card.piece_type_) {
      card_vec_.erase(card_vec_.begin() + i);
      break;
    }
  }
}