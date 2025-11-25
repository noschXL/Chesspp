#pragma once

#include "../../include/raylib-cpp.hpp"
#include "../Engine/BoardTypes.hpp"

#include <string>

extern raylib::Rectangle boardRect;

void InitRenderer(std::string texturepath);
void DrawAll(raylib::Window* window, Board board);
