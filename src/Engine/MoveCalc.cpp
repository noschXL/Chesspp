#include "MoveCalc.hpp"
#include "BoardTypes.hpp"
#include "../Render/Boardrender.hpp"
#include <cstdint>

MoveList GenerateRookMoves(Board board, int index) {
  //uint64_t enemyPieces = board.whitesTurn ? board.bitboards[BitBoard::Black] : board.bitboards[BitBoard::White];

  uint64_t pieceRow = to_ull(BitMasks::Row) << (8 * (index / 8));
  uint64_t pieceColumn = to_ull(BitMasks::Column) << (index % 8);

  QueueBitBoardRender(pieceRow | pieceColumn);

  board = board;
  index = index;

  return MoveList();

}
