#include "GamePiece.hpp"

#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "GameState.hpp"
using std::ostream;
using std::string;
using std::vector;

// helper, create card object, put in GameState data member for documentation
void GamePiece::MakeCard() const {
  GameCard card;
  card.player_name_ = player_name_;
  card.piece_type_ = piece_type_;
  game_state_->push(card);
}

// constructor
GamePiece::GamePiece(const string& player, const string& type, GameState* state) {
  player_name_ = player;
  piece_type_ = type;
  game_state_ = state;
  this->MakeCard();
}

// copy constructor
GamePiece::GamePiece(GamePiece& piece) {
  player_name_ = piece.player_name_;
  piece_type_ = piece.piece_type_;
  game_state_ = piece.game_state_;
  this->MakeCard();
}

// assignment
GamePiece& GamePiece::operator=(GamePiece const& piece) {
  game_state_->pop(*this);
  player_name_ = piece.player_name_;
  piece_type_ = piece.piece_type_;
  game_state_ = piece.game_state_;

  this->MakeCard();
  return *this;
}

// destructor
GamePiece::~GamePiece() { game_state_->pop(*this); }

// getters
int GamePiece::GetPower() const {
  if (piece_type_ == "Warrior") {
    return 5;
  } else if (piece_type_ == "Scout") {
    return 1;
  }
  // wizard
  else {
    return game_state_->NumPieces(player_name_, "Wizard");
  }

  return 0;
}

int GamePiece::GetSpeed() const {
  if (piece_type_ == "Warrior") {
    return 2;
  } else if (piece_type_ == "Scout") {
    return 8;
  }
  // wizard
  else {
    int enemy_cnt = (game_state_->NumType("Wizard")) -
                    game_state_->NumPieces(player_name_, "Wizard");
    if (enemy_cnt < 12)
      return 12 - enemy_cnt;
    else
      return 1;
  }

  return 0;
}

// Comparison oeprators
bool GamePiece::operator==(const GamePiece& piece) const {
  bool is_power_condition = this->GetPower() == piece.GetPower();
  bool is_speed_condition = this->GetSpeed() == piece.GetSpeed();

  if (is_power_condition && is_speed_condition) {
    return true;
  }
  return false;
}

bool GamePiece::operator!=(const GamePiece& piece) const {
  if (!(*this == piece)) {
    return true;
  }
  return false;
}

bool GamePiece::operator<(const GamePiece& piece) const {
  bool is_power_condition = this->GetPower() < piece.GetPower();
  bool is_speed_condition = this->GetSpeed() < piece.GetSpeed();

  if (is_power_condition) {
    return true;
  }
  if (this->GetPower() == piece.GetPower() && is_speed_condition) {
    return true;
  }

  return false;
}

bool GamePiece::operator>(const GamePiece& piece) const {
  if (!(*this < piece) && !(*this == piece)) {
    return true;
  }
  return false;
}

bool GamePiece::operator<=(const GamePiece& piece) const {
  if ((*this < piece) || (*this == piece)) {
    return true;
  }
  return false;
}

bool GamePiece::operator>=(const GamePiece& piece) const {
  if ((*this > piece) || (*this == piece)) {
    return true;
  }
  return false;
}

// streaming
ostream& operator<<(ostream& out, GamePiece const& piece) {
  out << "(" << piece.GetPlayer() << "," << piece.GetType() << ","
      << piece.GetPower() << "," << piece.GetSpeed() << ")";
  return out;
}