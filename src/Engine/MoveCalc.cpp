#include "MoveCalc.hpp"
#include "BoardTypes.hpp"

MoveList GenerateRookMoves(Board board, int index) {
  uint64_t enemyPieces = board.whitesTurn ? board.bitboards[BitBoard::Black] : board.bitboards[BitBoard::White];


}
