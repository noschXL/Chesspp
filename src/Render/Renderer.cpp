#include "Renderer.hpp"
#include "../../include/raylib-cpp.hpp"
#include "Boardrender.hpp"
#include "../Engine/BoardTypes.hpp"

#include <iostream>
#include <string>

void InitRenderer(std::string texturepath) {
  InitPieceTexture(texturepath);
}

void DrawAll(raylib::Window* window, Board board) {

  int w = window->GetRenderWidth(); 
  int h = window->GetRenderHeight();
  int largest = fmax(w,h);
  int smallest = fmin(w,h);


  raylib::Rectangle boardrect;
  
  if (smallest == h) {
    boardrect = raylib::Rectangle{
      float(largest - smallest) / 2,
      0,
      float(smallest),
      float(smallest)
    };
  
  }else{
    boardrect = raylib::Rectangle{
      0,
      float(largest - smallest) / 2,
      float(smallest),
      float(smallest)
    };
  
  }

  DrawBoard(board, boardrect);
}
