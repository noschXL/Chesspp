#include "BoardTypes.hpp"
#include <cstdint>
#include <iostream>

PieceType Piece::GetType() {
  return static_cast<PieceType>(Piece::data & 0b00000111);
}
PieceColor Piece::GetColor() {
  return static_cast<PieceColor>(Piece::data & 0b00011000);
}

bool Piece::IsFlagSet(PieceFlag flag) {
  return (Piece::data & to_uint8(flag)) > 0;
}

bool Piece::IsWhite() {
  return Piece::GetColor() == PieceColor::White;
}

void Piece::SetFlag(PieceFlag flag, bool value) {
  uint8_t current = Piece::data & to_uint8(flag);
  Piece::data ^= current ^ value;
}

uint16_t Move::GetFrom() {
  return data >> 6 & 0b111111; 
}

uint16_t Move::GetTo() {
  return data & 0b111111; 
}

MoveFlag Move::GetFlag() {
  return (MoveFlag) (data >> 12 & 0b111111); 
}

bool Move::IsCapture() {
  return data >> 14;
}

bool Move::operator==(Move m) {
  return this->data == m.data;
}

bool Move::operator!=(Move m) {
  return !(this->data == m.data);
}


Board::Board() {
  squares.fill(Piece(to_uint8(PieceType::Empty)));
  whitesTurn = true;
}

void Board::MakeMove(Move move) {
  squares[move.GetTo()] = squares[move.GetFrom()];
  squares[move.GetFrom()] = Piece();
  moveHistory.push_back(move);
}

void Board::UnMakeMove() {
  if (moveHistory.empty()) {
    std::cerr << "WARNING: Board with empty moveHistory called UnMakeMove, did nothing\n";
    return;
  }
  Move move = moveHistory.back();
  
  Piece prevPiece;
  if (move.IsCapture()) {
    prevPiece = captures.back();
    captures.pop_back();
  }else{
    prevPiece = Piece();
  }
  moveHistory.pop_back();

  squares[move.GetFrom()] = squares[move.GetTo()];
  squares[move.GetTo()] = prevPiece;

}
