#pragma once

#include "../../include/raylib-cpp.hpp"
#include "../Engine/BoardTypes.hpp"

#include <string>

void InitRenderer(std::string texturepath);
void DrawAll(raylib::Window* window, Board board);
