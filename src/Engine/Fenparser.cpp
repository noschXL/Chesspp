#include "Fenparser.hpp"
#include "BoardTypes.hpp"
#include <iostream>
#include <string>

const std::string lowercase = "prnbqk";
const std::string numbers = "12345678";

Board to_board(Fenstring fen) {
  Board board;
  
  int idx = 0;
  std::cout << fen << "\n";
  for (ulong i = 0; i < fen.size(); i++) {
    char currentchar = fen[i];
    std::cout << currentchar << "\n";
    if (currentchar ==  '/') {
      continue;
    }
    if (numbers.find(currentchar) != std::string::npos) {
      int skips = currentchar - '0';
      idx += skips;
      continue;
    }
    Piece piece;
    switch (currentchar) {
      case 'p':
        piece = Piece(PieceColor::Black, PieceType::Pawn);
        break;
      case 'P':
        piece = Piece(PieceColor::White, PieceType::Pawn);
        break;
      case 'k':
        piece = Piece(PieceColor::Black, PieceType::King);
        break;
      case 'K':
        piece = Piece(PieceColor::White, PieceType::King);
        break;
      case 'b':
        piece = Piece(PieceColor::Black, PieceType::Bishop);
        break;
      case 'B':
        piece = Piece(PieceColor::White, PieceType::Bishop);
        break;
      case 'n':
        piece = Piece(PieceColor::Black, PieceType::Knight);
        break;
      case 'N':
        piece = Piece(PieceColor::White, PieceType::Knight);
        break;
      case 'r':
        piece = Piece(PieceColor::Black, PieceType::Rook);
        break;
      case 'R':
        piece = Piece(PieceColor::White, PieceType::Rook);
        break;
      case 'q':
        piece = Piece(PieceColor::Black, PieceType::Queen);
        break;
      case 'Q':
        piece = Piece(PieceColor::White, PieceType::Queen);
        break;
    }

    board.squares[idx] = piece;

    std::cout << idx << "\n";
    idx++;
  }

  return board;
}
