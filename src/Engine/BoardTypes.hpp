#pragma once
#include <cstdint>


enum class PieceType : uint8_t{
  Empty,
  Pawn,
  Knight,
  Bishop,
  Rook,
  Queen,
  King
};

enum class PieceColor : uint8_t{
  White = 0b00000000,
  Black = 0b00001000,
};

enum class PieceFlag {
  Highlight = 0b00010000,
  CanMove   = 0b00100000,
  HasMoved  = 0b01000000,
  LastMoved = 0b10000000,
};

enum class MoveFlag {
  Promotion = 0b1 << 16,
  Capture = 0b1 << 15,
  Special1 = 0b1 << 14,
  Special2 = 0b1 << 13,
};

inline uint8_t to_uint8(PieceType type) { return static_cast<uint8_t>(type); }
inline uint8_t to_uint8(PieceColor color) { return static_cast<uint8_t>(color); }
inline uint8_t to_uint8(PieceFlag flag) { return static_cast<uint8_t>(flag); }
inline uint8_t to_uint8(MoveFlag flag) { return static_cast<uint8_t>(flag); }

class Piece { 
  uint8_t data;
  
public:
  Piece(uint8_t data) : data(data) {}
  Piece(PieceFlag flags, PieceColor color, PieceType type) : data(to_uint8(flags) | to_uint8(color) | to_uint8(type)) {}

  
  uint8_t GetType();
  uint8_t GetColor();
  uint8_t GetFlag(PieceFlag flag);

  
  void SetCanMove(bool value);
  void SetHighlight(bool value);
  void SetLastMoved(bool value);
  void SetHasMoved(bool value);
  void SetType(PieceType type);
  void SetColor(PieceColor color);
  void SetFlag(PieceFlag flag);
  
};

class Move {
  uint16_t data;

public:
  Move(uint8_t data) : data(data) {}
  Move(uint8_t from, uint8_t to, MoveFlag flags) : data(to_uint8(flags) | from << 6 | to) {}

};

class Board {
  Piece squares[64];
  bool Castelrights[4]; //topleft -> bottomright
  


};
// look at notes.md


