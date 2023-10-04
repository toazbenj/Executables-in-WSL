#pragma once
#include <ostream>
#include <string>

class GameState;

// holds GamePiece attributes to be pushed into GameState data member
struct GameCard {
  std::string player_name_;
  std::string piece_type_;
};

class GamePiece {
 private:
  std::string player_name_;
  std::string piece_type_;
  GameState *game_state_;

 public:
  // helper for GameState documention
  void MakeCard() const;

  // constructors
  GamePiece(const std::string&, const std::string&, GameState *);
  GamePiece(GamePiece &);

  // assignment
  GamePiece &operator=(GamePiece const &);

  // destructor
  ~GamePiece();

  // getters
  const std::string GetPlayer() const { return player_name_; }
  std::string GetType() const { return piece_type_; }
  int GetPower() const;
  int GetSpeed() const;

  // comparison
  bool operator==(const GamePiece &) const;
  bool operator!=(const GamePiece &) const;
  bool operator<(const GamePiece &) const;
  bool operator>(const GamePiece &) const;
  bool operator<=(const GamePiece &) const;
  bool operator>=(const GamePiece &) const;

  // print
  friend std::ostream &operator<<(std::ostream &, GamePiece const&);
};

// print
std::ostream &operator<<(std::ostream &, GamePiece const&);