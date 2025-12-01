#pragma once

#include "../../include/raylib-cpp.hpp"
#include "../Engine/BoardTypes.hpp"

#include <string>

extern raylib::Rectangle boardRect;

void QueueBitBoardRender(uint64_t bitboard);
void InitRenderer(std::string texturepath);
void DrawAll(raylib::Window* window, Board board);
