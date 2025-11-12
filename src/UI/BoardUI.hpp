#include "../../include/raylib-cpp.hpp"
#include "../Engine/BoardTypes.hpp"

#include <string>
#include <vector>

void DrawPieceAt(Piece piece, float x, float y, float width, float height);

void SelectPieceAt(float x, float y,
                   raylib::Rectangle boardRect, 
                   bool whiteToMove, 
                   std::vector<Move> Movelist);

  void DrawDebug(std::string data, raylib::Rectangle boardrect);

void HandleMouse(raylib::Rectangle boardRect, bool whiteToMove, std::vector<Move> Movelist);
