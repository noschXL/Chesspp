#include "Boardrender.hpp"
#include <cmath>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <iostream>
#include <sys/types.h>
#include <vector>

static std::vector<uint64_t> bitboardQueue;

static raylib::Texture2D pieceTexture;
raylib::Texture2D* pieceTexturePtr = nullptr;
bool textureinitialized = false;

int pieceWidth = -1;
int pieceHeight = -1;

const raylib::Color BoardColors::White          = {0xffffffff};
const raylib::Color BoardColors::WhiteSquare     = {0x52311eff};
const raylib::Color BoardColors::BlackSquare     = {0xc59562ff};
const raylib::Color BoardColors::HighlightSquare = {0xfbf236ff};
const raylib::Color BoardColors::MoveSquare      = {0x306082ff};
const raylib::Color BoardColors::Blue            = {0x5fcde4aa};

void DebugVec(raylib::Vector2 vec) {
  std::cout
  << "Vector2: "
  << vec.x
  << " "
  << vec.y
  << "\n";
}

void DebugRect(raylib::Rectangle rect) {
  std::cout
  << "Rect: "
  << rect.x
  << " "
  << rect.y
  << " "
  << rect.width
  << " "
  << rect.height
  << "\n";
}

void DebugBitBoard(uint64_t bb) {
  std::cout << (bb >> 56 & 0xFF) << "\n"
            << (bb >> 48 & 0xFF) << "\n"
            << (bb >> 40 & 0xFF) << "\n"
            << (bb >> 32 & 0xFF) << "\n"
            << (bb >> 24 & 0xFF) << "\n"
            << (bb >> 16 & 0xFF) << "\n"
            << (bb >> 8 & 0xFF) << "\n"
            << (bb >> 0 & 0xFF) << "\n";
}

void QueueBitBoardRender(uint64_t bitboard) {
  bitboardQueue.push_back(bitboard);
}

void DrawBitBoard(raylib::Rectangle boardRect, uint64_t bitboard) {
  for (int i = 0; i < 64; i++) {
    if (!(bitboard >> i & 0b1)) {continue;}
    
    raylib::Rectangle sqrRect = {
      boardRect.x + boardRect.width / 8 * (i % 8),
      boardRect.y + boardRect.height / 8 * (i / 8),
      boardRect.width / 8,
      boardRect.height / 8,
    };

    DrawRectangleRec(sqrRect, BoardColors::Blue);

  }
}

void DrawAllBitBoardOverlays (raylib::Rectangle boardRect) {
  for (uint64_t bb: bitboardQueue) {
    DrawBitBoard(boardRect, bb);
  }

  while (!bitboardQueue.empty()) {bitboardQueue.pop_back();}


}

void InitPieceTexture(std::string path) {
  pieceTexture = raylib::Texture2D{path};
  pieceTexture.GenMipmaps();
  pieceTexture.SetFilter(TEXTURE_FILTER_TRILINEAR); 
  pieceTexturePtr = &pieceTexture;
  pieceWidth = pieceTexture.width / 6;
  pieceHeight = pieceTexture.height / 2;
  textureinitialized = true;
}

void DrawPiece(int index, raylib::Rectangle boardRect, Piece piece) {
  if (!textureinitialized) {
    throw std::runtime_error("texture was not initialized");
  }
  PieceType type = piece.GetType();

  
  float width = boardRect.width / 8;
  float height = boardRect.height / 8;

  float x = index % 8 * boardRect.width / 8;
  float y = std::floor(index / 8) * boardRect.height / 8;
  
  raylib::Rectangle drawAera = {
    x + boardRect.x,
    y + boardRect.y,
    width,
    height,
  };
 
  

  if (piece.IsFlagSet(PieceFlag::Highlight)) {
    DrawRectangleRec(drawAera, BoardColors::HighlightSquare);
  }

  if (piece.IsFlagSet(PieceFlag::CanMove)) {
    DrawRectangleRec(drawAera, BoardColors::MoveSquare);
  }

  if (type == PieceType::Empty) {return;}
  
  raylib::Rectangle fromRect = {
    float(int(to_uint8(type)) * pieceWidth),
    float(int((to_uint8(piece.GetColor()) >> 3)) * pieceHeight),
    float(pieceWidth),
    float(pieceHeight)
  };

  raylib::Vector2 origin = {0,0};


  DrawTexturePro(*pieceTexturePtr, fromRect, drawAera, origin, 0, WHITE);
}

void DrawBoard(Board board, raylib::Rectangle boardRect) {
  for (int i = 0; i < 64; i++) {

    int x = boardRect.x + (i % 8) * (boardRect.width / 8);
    int y = boardRect.y + floor((float)i / 8) * (boardRect.height / 8);

    int row = i / 8;
    int col = i % 8;
    raylib::Color sqrcol = ((row + col) % 2 == 0) ? BoardColors::BlackSquare : BoardColors::WhiteSquare;
    DrawRectangle(x, y, boardRect.width / 8, boardRect.height / 8, sqrcol);

    Piece piece = board.squares[i];
    DrawPiece(i, boardRect, piece);
  }
}
