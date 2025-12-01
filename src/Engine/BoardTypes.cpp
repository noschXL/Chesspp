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
  return data >> 14 & 1;
}

bool Move::operator==(Move m) {
  return this->data == m.data;
}

bool Move::operator!=(Move m) {
  return !(this->data == m.data);
}


Board::Board() {
  squares.fill(Piece());
  bitboards.fill(0ULL);
  whitesTurn = true;
}

std::array<BitBoard, 2> GetPieceBitBoards(Piece* piece) {
  std::array<BitBoard, 2> returnvalue;
  
  BitBoard pb;

  switch (piece->GetType()) {
    case PieceType::Pawn:
      pb = BitBoard::Pawn;
      break;
    case PieceType::Bishop:
      pb = BitBoard::Bishop;
      break;
    case PieceType::Knight:
      pb = BitBoard::Knight;
      break;
    case PieceType::Rook:
      pb = BitBoard::Rook;
      break;
    case PieceType::Queen:
      pb = BitBoard::Queen;
      break;
    case PieceType::King:
      pb = BitBoard::King;
      break;
    default:
      throw std::runtime_error("well, you moved an empty Square, good job Mr. Dumbass!");
  }
  
  BitBoard color = piece->GetColor() == PieceColor::White ? BitBoard::White : BitBoard::Black;

  returnvalue[0] = color;
  returnvalue[1] = pb;

  return returnvalue;
}

void Board::MakeMove(Move move) {

  Piece* piece = &squares[move.GetFrom()];

  auto pieceBitboards = GetPieceBitBoards(piece);

  BitBoard color = pieceBitboards[0];
  BitBoard pb = pieceBitboards[1];

  uint64_t cbitboard = bitboards[color];
  cbitboard &= ~(to_ull(BitMasks::First) << move.GetFrom());
  cbitboard |= to_ull(BitMasks::First) << move.GetTo();
  bitboards[color] = cbitboard;



  uint64_t pbitboard = bitboards[pb];
  pbitboard &= ~(to_ull(BitMasks::First) << move.GetFrom());
  pbitboard |= to_ull(BitMasks::First) << move.GetTo();
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
  Piece* piece = &squares[move.GetTo()];

  // ----- BITBOARDS -------

  auto pieceBitboards = GetPieceBitBoards(piece);

  BitBoard color = pieceBitboards[0];
  BitBoard pb = pieceBitboards[1];

  uint64_t cbitboard = bitboards[color];
  cbitboard &= ~(to_ull(BitMasks::First) << move.GetTo());
  cbitboard |= to_ull(BitMasks::First) << move.GetFrom();
  bitboards[color] = cbitboard;


  uint64_t pbitboard = bitboards[pb];
  pbitboard &= ~(to_ull(BitMasks::First) << move.GetTo());
  pbitboard |= to_ull(BitMasks::First) << move.GetFrom();
  bitboards[pb] = pbitboard;

  // ------ END BITBOARDS -------

  squares[move.GetFrom()] = squares[move.GetTo()];
  squares[move.GetTo()] = Piece();
  moveHistory.pop_back();
  

  
  if (move.IsCapture()) {
    Piece* prevPiece;
    prevPiece = &captures.back();
    captures.pop_back();
    squares[move.GetFrom()] = *prevPiece;
    
    // ----- BITBOARDS -------

    auto pieceBitboards = GetPieceBitBoards(prevPiece);

    BitBoard color = pieceBitboards[0];
    BitBoard pb = pieceBitboards[1];

    uint64_t cbitboard = bitboards[color];
    cbitboard |= to_ull(BitMasks::First) << move.GetFrom();
    bitboards[color] = cbitboard;


    uint64_t pbitboard = bitboards[pb];
    pbitboard |= to_ull(BitMasks::First) << move.GetFrom();
    bitboards[pb] = pbitboard;

    // ------ END BITBOARDS -------

  }

}
