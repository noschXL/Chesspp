#include "Engine/BoardTypes.hpp"
#include "render/Renderer.hpp"
#include "Engine/Fenparser.hpp"

#include <iostream>
#include <filesystem>
#include <string>


const Fenstring startpos = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

int main() {

  int screenWidth = 1980 / 2;
  int screenHeight = 1080 / 2;

  auto cwd = std::filesystem::current_path();
  std::cout << cwd << "\n";

  
  raylib::Window window(screenWidth, screenHeight, "raylib-cpp - basic window");

  InitRenderer((cwd / "src/render/assets/pieces.png").string());
  
  window.SetFullscreen(true);

  SetTargetFPS(60);


  Board board = to_board(startpos);
  board.squares[0] = Piece(PieceFlag::None, PieceColor::White, PieceType::Queen);
  
  while (!window.ShouldClose()) {
    // float deltatime = GetFrameTime();
    BeginDrawing();
    
    window.ClearBackground(BLACK);
    
    DrawAll(&window, board);


    EndDrawing();
  }

  return 0;
}
