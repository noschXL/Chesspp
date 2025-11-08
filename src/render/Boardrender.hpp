#pragma once

#include "../../include/raylib-cpp.hpp"
#include "../Engine/BoardTypes.hpp"

#include <string>

void InitPieceTexture(std::string path);
void DrawBoard(Board board, raylib::Rectangle aera);
void DrawPiece(int index, raylib::Rectangle boardRect, Piece piece);
