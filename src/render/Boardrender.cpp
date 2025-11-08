#include "Boardrender.hpp"
#include <cmath>
#include <stdexcept>
#include <string>

const raylib::Color Whitesquare = {0x52311e};
const raylib::Color Blacksquare = {0xc59562};
const raylib::Color Highlightsquare = {0xfbf236};
const raylib::Color Movesquare = {0x306082};

const raylib::Color White = {0xffffff};


raylib::Texture2D pieceTexture;
bool textureinitialized = false;

int pieceWidth = -1;
int pieceHeight = -1;


void InitPieceTexture(std::string path) {
  pieceTexture = raylib::Texture2D{path};
  pieceWidth = pieceTexture.width / 6;
  pieceHeight = pieceTexture.height / 2;
  textureinitialized = true;
}

void DrawPiece(int index, raylib::Rectangle boardRect, Piece piece) {
  if (textureinitialized) {
    throw std::runtime_error("texture was not initialized");
  }
  PieceType type = piece.GetType();

  
  float width = boardRect.width / 8;
  float height = boardRect.height / 8;

  float x = index % 8 * boardRect.width / 8;
  float y = std::floor(index / 8) * boardRect.height / 8;
  
  raylib::Rectangle drawAera = {
    x,
    y,
    width,
    height,
  };

  if (piece.IsFlagSet(PieceFlag::Highlight)) {
    DrawRectangleRec(drawAera, Highlightsquare);
  }

  if (piece.IsFlagSet(PieceFlag::CanMove)) {
    DrawRectangleRec(drawAera, Movesquare);
  }

  if (type == PieceType::Empty) {return;}

  
  raylib::Rectangle fromRect = {
    float(to_uint8(type) * pieceWidth),
    float((to_uint8(piece.GetColor())-1) * pieceHeight),
    float(pieceWidth),
    float(pieceHeight)
  };

  raylib::Vector2 origin = {0,0};

  DrawTexturePro(pieceTexture, fromRect, drawAera, origin, 0, WHITE);

}

void DrawBoard(Board board, raylib::Rectangle boardRect) {
  for (int i = 0; i < 64; i++) {
    Piece piece = board.squares[i];
    DrawPiece(i, boardRect, piece);
  }
}
