#include "Engine/BoardTypes.hpp"

#include "Render/Renderer.hpp"
#include "UI/BoardUI.hpp"

#include "Engine/Fenparser.hpp"

#include <iostream>
#include <filesystem>

const Fenstring startpos = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

int main() {

  int screenWidth = 1980 / 2;
  int screenHeight = 1080 / 2;

  auto cwd = std::filesystem::current_path();
  std::cout << cwd << "\n";

  
  raylib::Window window(screenWidth, screenHeight, "Chesspp");

  InitRenderer((cwd / "src/Render/assets/pieces.png").string());
  
  window.SetFullscreen(true);

  SetTargetFPS(60);

  Board board = to_board(startpos);
  
  while (!window.ShouldClose()) {
    // float deltatime = GetFrameTime();
    BeginDrawing();

    window.ClearBackground(DARKGRAY);
    
    DrawAll(&window, board);
    Move m = HandleMouse(board, boardRect);

    if (m != ErrorMove) {
      board.MakeMove(m);
    }

    bool zPressed = raylib::Keyboard::IsKeyPressed(KEY_Y); // Letter Y cuz of kb layout
    bool ctrlDown = raylib::Keyboard::IsKeyDown(KEY_LEFT_CONTROL);

    if (zPressed && ctrlDown){
      board.UnMakeMove();
    }

    EndDrawing();
  }

  return 0;
}
