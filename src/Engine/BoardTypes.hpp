#pragma once
#include <cstdint>
#include <array>


enum class PieceType : uint8_t{
  King,
  Queen,
  Bishop,
  Knight,
  Rook,
  Pawn,
  Empty,
};

enum class PieceColor : uint8_t{
  White = 0b00000000,
  Black = 0b00001000,
};

enum class PieceFlag {
  None = 0,
  Highlight = 0b00010000,
  CanMove   = 0b00100000,
  HasMoved  = 0b01000000,
  LastMoved = 0b10000000,
};

enum class MoveFlag {
  Promotion = 0b1 << 15,
  Capture = 0b1 << 14,
  Special1 = 0b1 << 13,
  Special2 = 0b1 << 12,
};

inline uint8_t to_uint8(PieceType type) { return static_cast<uint8_t>(type)&0b00000111; }
inline uint8_t to_uint8(PieceColor color) { return static_cast<uint8_t>(color)&0b00001000; }
inline uint8_t to_uint8(PieceFlag flag) { return static_cast<uint8_t>(flag)&0b11110000; }
inline uint8_t to_uint16(MoveFlag flag) { return static_cast<uint16_t>(flag); }

class Piece { 
  uint8_t data;
  
public:
  Piece() : data(to_uint8(PieceType::Empty)) {};
  Piece(uint8_t data) : data(data) {}
  Piece(PieceColor color, PieceType type) : data(to_uint8(color) | to_uint8(type)) {}  
  Piece(PieceFlag flags, PieceColor color, PieceType type) : data(to_uint8(flags) | to_uint8(color) | to_uint8(type)) {}

    Piece(const Piece&) = default;
    Piece& operator=(const Piece&) = default;

  
  PieceType GetType();
  PieceColor GetColor();
  bool IsFlagSet (PieceFlag flag);
  
  void SetFlag(PieceFlag flag, bool value);
  
};

class Move {
  uint16_t data;

public:
  Move(uint16_t data) : data(data) {}
  Move(uint16_t from, uint16_t to, MoveFlag flags) : data(to_uint16(flags) | from << 6 | to) {}

  uint16_t GetFrom();
  uint16_t GetTo();
  bool GetSpecial1();
  bool GetSpecial2();
  bool GetCapture();
  bool GetPromotion();
  
  void SetFrom(uint8_t idx);
  void SetTo(uint8_t idx);
  void SetSpecial1(bool value);
  void SetSpecial2(bool value);
  void SetCapture(bool value);
  void SetPromotion(bool value);

};

struct Board {
  std::array<Piece, 64> squares;
  std::array<bool, 4> Castelrights; //topleft -> bottomright
  
  Board();

};
// look at notes.md


