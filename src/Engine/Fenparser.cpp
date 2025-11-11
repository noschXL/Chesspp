#include "Fenparser.hpp"
#include "BoardTypes.hpp"
#include <iostream>
#include <string>

const std::string lowercase = "prnbqk";
const std::string numbers = "12345678";

Board to_board(Fenstring fen) {
  Board board;
  
  int idx = 0;
  for (ulong i = 0; i < sizeof(fen); i++) {
    char currentchar = fen[i];
    std::cout << currentchar;
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
    }

    board.squares[idx] = piece;

    std::cout << ", " << idx << "\n";
    idx++;
  }

  return board;
}
