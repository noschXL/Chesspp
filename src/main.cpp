#include "render/textures.hpp"

#include <iostream>

const Color Whitesquare = Color{244,210,156,255};
const Color Blacksquare = Color{187,117,71,255};

int main() {


  int screenWidth = 1980 / 2;
  int screenHeight = 1080 / 2;


  raylib::Window window(screenWidth, screenHeight, "raylib-cpp - basic window");

  window.SetFullscreen(true);

  SetTargetFPS(60);

  GenDefaultTexture();

  while (!window.ShouldClose()) {
    //float deltatime = GetFrameTime();
    std::cout << window.GetRenderHeight() << ", " << window.GetRenderWidth() << "\n";
    BeginDrawing();
    DrawText("hello", 100, 100, 20, WHITE);

    DrawRectangle(200, 200, 50, 50, Whitesquare);

    window.ClearBackground(BLACK);

    EndDrawing();
  }

  return 0;
}
