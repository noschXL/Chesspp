#pragma once

#include "../../include/raylib-cpp.hpp"
#include "../Engine/BoardTypes.hpp"

#include <string>

extern bool textureinitialized; 
extern raylib::Texture2D* pieceTexturePtr;

class BoardColors {
public:
  static const raylib::Color White;
  static const raylib::Color WhiteSquare;
  static const raylib::Color BlackSquare;
  static const raylib::Color HighlightSquare;
  static const raylib::Color MoveSquare;
};

void InitPieceTexture(std::string path);
void DrawBoard(Board board, raylib::Rectangle aera);
void DrawPiece(int index, raylib::Rectangle boardRect, Piece piece);
