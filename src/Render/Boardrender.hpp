#pragma once

#include "../../include/raylib-cpp.hpp"
#include "../Engine/BoardTypes.hpp"

#include <cstdint>
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
  static const raylib::Color Blue;
};

extern int pieceWidth;
extern int pieceHeight;

void InitPieceTexture(std::string path);

void DrawBoard(Board board, raylib::Rectangle aera);
void DrawPiece(int index, raylib::Rectangle boardRect, Piece piece);

void DebugRect(raylib::Rectangle rect);
void DebugVec(raylib::Vector2 vec);
void DebugBitBoard(uint64_t bb);

void DrawAllBitBoardOverlays(raylib::Rectangle boardRect);
void QueueBitBoardRender(uint64_t bitboard);
