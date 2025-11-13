#pragma once

#include "../../include/raylib-cpp.hpp"
#include "../Engine/BoardTypes.hpp"

#include <string>

extern bool textureinitialized; 
extern raylib::Texture2D* pieceTexturePtr;


void InitPieceTexture(std::string path);
void DrawBoard(Board board, raylib::Rectangle aera);
void DrawPiece(int index, raylib::Rectangle boardRect, Piece piece);
