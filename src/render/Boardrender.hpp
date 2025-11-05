#pragma once

#include "../../include/raylib-cpp.hpp"

const raylib::Color Whitesquare;
const raylib::Color Blacksquare;

class Spritesheet {
  raylib::Texture image;
  raylib::Vector2 spritesize;

public:
  Spritesheet();
};
