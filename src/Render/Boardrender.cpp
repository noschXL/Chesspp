#include "Boardrender.hpp"
#include <cmath>
#include <stdexcept>
#include <string>


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
