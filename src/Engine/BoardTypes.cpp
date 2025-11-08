#include "BoardTypes.hpp"
#include <cstdint>

PieceType Piece::GetType() {
  return static_cast<PieceType>(Piece::data & 0b00000111);
}
PieceColor Piece::GetColor() {
  return static_cast<PieceColor>(Piece::data & 0b00011000);
}

bool Piece::IsFlagSet(PieceFlag flag) {
  return (Piece::data & to_uint8(flag)) > 0;
}

void Piece::SetFlag(PieceFlag flag, bool value) {
  uint8_t current = Piece::data & to_uint8(flag);
  Piece::data ^= current ^ value;
}


Board::Board() {
  squares.fill(Piece(0));
}
