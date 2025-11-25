#include "../../include/raylib-cpp.hpp"
#include "../Engine/BoardTypes.hpp"
#include "BoardUI.hpp"
#include "../Render/Boardrender.hpp"
#include <stdexcept>

static Piece* selectedPiecePtr = nullptr;
static int selectedPieceIndex = -1;
static bool dragging = false;
static int dragOffsetX = -1;
static int dragOffsetY = -1;

void DrawPieceAt(Piece* piece, float x, float y, float width, float height) {
  if (!textureinitialized) {
    std::runtime_error("PieceTexture was not initialized");
  }
  PieceType type = piece->GetType();
  
  if (type == PieceType::Empty) {return;}
  
  float pieceWidth = 2000.0 / 6.0;
  float pieceHeight = 668 / 6.0;

  raylib::Rectangle fromRect = {
    float(int(to_uint8(type)) * pieceWidth),
    float(int((to_uint8(piece->GetColor()) >> 3)) * pieceHeight),
    pieceWidth,
    pieceHeight
  };

  raylib::Rectangle toRect = {
    x,
    y,
    width,
    height
  };

  raylib::Vector2 origin = {0,0};


  DrawTexturePro(*pieceTexturePtr, fromRect, toRect, origin, 0, WHITE);

}

void SelectPieceAt(Board board, float x, float y, raylib::Rectangle boardRect, bool whiteToMove) {

  float relativeX = boardRect.x - x;
  float relativeY = boardRect.y - y;

  if (relativeX < 0 || relativeY < 0 || relativeX > boardRect.width || relativeY > boardRect.height) {return;}

  int rowX = int(relativeX) % int(boardRect.width / 8);
  int rowY = int(relativeY) / int(boardRect.height / 8);

  int index = rowX + rowY * 8;


  Piece* newPiecePtr = &board.squares[index];
  
  if (newPiecePtr->IsWhite() != whiteToMove) {return;}

  bool isSamePiece = newPiecePtr == selectedPiecePtr;

  selectedPiecePtr->SetFlag(PieceFlag::Highlight, false);
  
  if (!isSamePiece) {
    newPiecePtr->SetFlag(PieceFlag::Highlight, true);
  }

  selectedPiecePtr = (newPiecePtr == selectedPiecePtr) ? nullptr : newPiecePtr;
  selectedPieceIndex = (newPiecePtr == selectedPiecePtr) ? -1 : index;

  selectedPiecePtr->SetFlag(PieceFlag::Highlight, true);

  dragOffsetX = (newPiecePtr == selectedPiecePtr) ? raylib::Mouse::GetX() - (rowX * boardRect.width / 8) : -1;
  dragOffsetY = (newPiecePtr == selectedPiecePtr) ? raylib::Mouse::GetY() - (rowY * boardRect.height / 8) : -1;
  
}

void HidePieceAt(raylib::Rectangle boardRect, int index) {
  int x = boardRect.x + (index % 8) * (boardRect.width / 8);
  int y = boardRect.y + floor(float(index) / 8) * (boardRect.height / 8);

  int row = index / 8;
  int col = index % 8;
  raylib::Color sqrcol = ((row + col) % 2 == 0) ? BoardColors::BlackSquare : BoardColors::WhiteSquare;
  DrawRectangle(x, y, boardRect.width / 8, boardRect.height / 8, sqrcol);
}

void HandleMouse(Board board, raylib::Rectangle boardRect, bool whiteToMove) {
  bool pressed = raylib::Mouse::IsButtonPressed(0);
  bool down = raylib::Mouse::IsButtonDown(0);
  bool released = raylib::Mouse::IsButtonReleased(0);

  int x = raylib::Mouse::GetX();
  int y = raylib::Mouse::GetY();
  if (selectedPiecePtr == nullptr) {

      
    if (pressed) {
      SelectPieceAt(board, float(x), float(y), boardRect, whiteToMove);
    }else if (down) {
      SelectPieceAt(board, float(x), float(y), boardRect, whiteToMove);
      dragging = true;
    }
  }

  else {
    if (dragging) {
      HidePieceAt(boardRect, selectedPieceIndex);
      DrawPieceAt(selectedPiecePtr, x - dragOffsetX, y - dragOffsetY, boardRect.width / 8, boardRect.height / 8);
      if (released) {
        dragging = false;
      }
    }
  }

}
