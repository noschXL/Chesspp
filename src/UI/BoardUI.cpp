#include "../../include/raylib-cpp.hpp"
#include "../Engine/BoardTypes.hpp"
#include "BoardUI.hpp"
#include "../Render/Boardrender.hpp"
#include <stdexcept>

//static Piece* selectedPiecePtr;

void DrawPieceAt(Piece piece, float x, float y, float width, float height) {
  if (!textureinitialized) {
    std::runtime_error("PieceTexture was not initialized");
  }
  PieceType type = piece.GetType();
  
  raylib::Rectangle drawAera = {
    x,
    y,
    width,
    height,
  };
  
  if (type == PieceType::Empty) {return;}
  
  float pieceWidth = 2000.0 / 6.0;
  float pieceHeight = 668 / 6.0;

  raylib::Rectangle fromRect = {
    float(int(to_uint8(type)) * pieceWidth),
    float(int((to_uint8(piece.GetColor()) >> 3)) * pieceHeight),
    pieceWidth,
    pieceHeight
  };

  raylib::Vector2 origin = {0,0};


  DrawTexturePro(*pieceTexturePtr, fromRect, drawAera, origin, 0, WHITE);
}
