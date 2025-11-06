#pragma once

#include "../../include/raylib-cpp.hpp"
#include "../Engine/BoardTypes.hpp"


extern const raylib::Color Whitesquare;
extern const raylib::Color Blacksquare;
extern const raylib::Texture2D PieceTexture;

void InitPieceTexture(const char* path);
void DrawBoard(raylib::Rectangle aera);
void DrawPiece(raylib::Rectangle aera, Piece piece);
void DrawAll();
