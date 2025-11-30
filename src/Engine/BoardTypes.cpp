#include "BoardTypes.hpp"
#include <cstdint>
#include <iostream>
#include <stdexcept>

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

  Piece* piece = &squares[move.GetFrom()];


  BitBoard color = piece->GetColor() == PieceColor::White ? BitBoard::White : BitBoard::Black;
  uint64_t cbitboard = bitboards[color];

  cbitboard &= ~(to_ull(BitMasks::First) >> move.GetFrom());
  cbitboard |= to_ull(BitMasks::First) >> move.GetTo();

  bitboards[color] = cbitboard;

  BitBoard pb;

  switch (piece->GetType()) {
    case PieceType::Pawn:
      pb = BitBoard::Pawn;
    case PieceType::Bishop:
      pb = BitBoard::Bishop;
    case PieceType::Knight:
      pb = BitBoard::Knight;
    case PieceType::Rook:
      pb = BitBoard::Rook;
    case PieceType::Queen:
      pb = BitBoard::Queen;
    case PieceType::King:
      pb = BitBoard::King;
    default:
      throw std::runtime_error("well, you moved an empty Square, good job Mr. Dumbass!");
  }
  
  uint64_t pbitboard = bitboards[pb];

  pbitboard &= ~(to_ull(BitMasks::First) >> move.GetFrom());
  pbitboard |= to_ull(BitMasks::First) >> move.GetTo();

  bitboards[pb] = pbitboard;

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
  Piece* piece = &squares[move.GetTo()];


  BitBoard color = piece->GetColor() == PieceColor::White ? BitBoard::White : BitBoard::Black;
  uint64_t cbitboard = bitboards[color];

  cbitboard &= ~(to_ull(BitMasks::First) >> move.GetFrom());
  cbitboard |= to_ull(BitMasks::First) >> move.GetTo();

  bitboards[color] = cbitboard;

  BitBoard pb;

  switch (piece->GetType()) {
    case PieceType::Pawn:
      pb = BitBoard::Pawn;
    case PieceType::Bishop:
      pb = BitBoard::Bishop;
    case PieceType::Knight:
      pb = BitBoard::Knight;
    case PieceType::Rook:
      pb = BitBoard::Rook;
    case PieceType::Queen:
      pb = BitBoard::Queen;
    case PieceType::King:
      pb = BitBoard::King;
    default:
      throw std::runtime_error("well, you moved an empty Square, good job Mr. Dumbass!");
  }
  
  uint64_t pbitboard = bitboards[pb];

  pbitboard &= ~(to_ull(BitMasks::First) >> move.GetTo());
  pbitboard |= to_ull(BitMasks::First) >> move.GetFrom();

  bitboards[pb] = pbitboard;
  moveHistory.pop_back();

  squares[move.GetFrom()] = squares[move.GetTo()];
  squares[move.GetTo()] = prevPiece;

}
