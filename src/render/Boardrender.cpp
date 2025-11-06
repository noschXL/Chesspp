#include "Boardrender.hpp"

const raylib::Color Whitesquare = raylib::Color{0x52311e};
const raylib::Color Blacksquare = raylib::Color{0xc59562};

void InitPieceTexture(const char* path) {
  const raylib::Texture2D PieceTexture = raylib::Texture2D{path};
}

void DrawPiece(raylib::Rectangle aera, Piece piece) {
  
}
