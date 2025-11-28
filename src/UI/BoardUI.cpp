#include "../../include/raylib-cpp.hpp"
#include "../Engine/BoardTypes.hpp"
#include "BoardUI.hpp"
#include "../Render/Boardrender.hpp"
#include <stdexcept>
#include <iostream>

static Piece* selectedPiecePtr = nullptr;
static int selectedPieceIndex = -1;
static bool dragging = false;
static int dragOffsetX = -1;
static int dragOffsetY = -1;

static float relativeX = -1;
static float relativeY = -1;


void DrawPieceAt(Piece* piece, float x, float y, float width, float height) {
  if (!textureinitialized) {
    std::runtime_error("PieceTexture was not initialized");
  }
  PieceType type = piece->GetType();
  
  if (type == PieceType::Empty) {return;}
  
  raylib::Rectangle fromRect = {
    float(int(to_uint8(type)) * pieceWidth),
    float(int((to_uint8(piece->GetColor()) >> 3)) * pieceHeight),
    (float) pieceWidth,
    (float) pieceHeight
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

void DeSelectPiece() {
  if (selectedPiecePtr != nullptr) {
    selectedPiecePtr->SetFlag(PieceFlag::Highlight, false);
  }

  selectedPiecePtr = nullptr;
  selectedPieceIndex = -1;
}

void SelectPiece(Board board, int idx) {
  Piece* newPiecePtr = &board.squares[idx];

  if (selectedPiecePtr != nullptr) {
    DeSelectPiece();
  }
  selectedPiecePtr = newPiecePtr;
  selectedPieceIndex = idx;
}
void SelectPiece(Piece* pieceptr, raylib::Rectangle boardRect) {

  if (selectedPiecePtr != nullptr) {
    DeSelectPiece();
  }
  int rowX = int(relativeX) / int(boardRect.width / 8);
  int rowY = int(relativeY) / int(boardRect.height / 8);

  int index = rowX + rowY * 8;
  
  selectedPiecePtr = pieceptr;
  selectedPieceIndex = index;
  std::cout << "selected piece " << index << "\n";
}


raylib::Vector2 GetRelativeMousePos(raylib::Rectangle boardRect) {

  raylib::Vector2 mousePos = raylib::Mouse::GetPosition();

  relativeX = mousePos.x - boardRect.x;
  relativeY = mousePos.y - boardRect.y;

  return raylib::Vector2(relativeX, relativeY);
}

Piece* GetMousePiece(Board board, raylib::Rectangle boardRect) {

  raylib::Vector2 relMousePos = GetRelativeMousePos(boardRect);
  DebugVec(relMousePos);
  DebugRect(boardRect);

  if (
    0 > relMousePos.x ||
    0 > relMousePos.y ||
    boardRect.width < relMousePos.x ||
    boardRect.height < relMousePos.y
  ) {return nullptr;}

  int rowX = int(relativeX) / int(boardRect.width / 8);
  int rowY = int(relativeY) / int(boardRect.height / 8);

  int index = rowX + rowY * 8;

  Piece* newPiecePtr = &board.squares[index];

  return newPiecePtr;
}

void SelectPieceAtMouse(Board board, raylib::Rectangle boardRect) {
  
  Piece* Mousepiece = GetMousePiece(board, boardRect);
  if (Mousepiece == nullptr) {
    std::cout << "selected a nullptr\n";
  }
  SelectPiece(Mousepiece, boardRect);
}

void HideSelectedPiece(raylib::Rectangle boardRect) {
  int x = boardRect.x + (selectedPieceIndex % 8) * (boardRect.width / 8);
  int y = boardRect.y + floor(float(selectedPieceIndex) / 8) * (boardRect.height / 8);

  int row = selectedPieceIndex / 8;
  int col = selectedPieceIndex % 8;
  raylib::Color sqrcol = ((row + col) % 2 == 0) ? BoardColors::BlackSquare : BoardColors::WhiteSquare;

  if (selectedPiecePtr->IsFlagSet(PieceFlag::Highlight)) {
    sqrcol = BoardColors::HighlightSquare;
  }

  DrawRectangle(x, y, boardRect.width / 8, boardRect.height / 8, sqrcol);
}

Move HandleMouse(Board board, raylib::Rectangle boardRect) {
  bool down = raylib::Mouse::IsButtonDown(0);

  int x = raylib::Mouse::GetX();
  int y = raylib::Mouse::GetY();
  if (selectedPiecePtr == nullptr) { 
    if (down) {
      SelectPieceAtMouse(board, boardRect);
      dragging = true;
      std::cout << "dragging now\n";
    }
  }else {
    if (dragging) {
      if (!down) {
        dragging = false;
        std::cout << "stopped dragging\n";
      }
      HideSelectedPiece(boardRect);
      DrawPieceAt(selectedPiecePtr, x - dragOffsetX, y - dragOffsetY, boardRect.width / 8, boardRect.height / 8);
    }else{
      raylib::Vector2 relMousePos = GetRelativeMousePos(boardRect);

      if (
        0 > relMousePos.x ||
        0 > relMousePos.y ||
        boardRect.width < relMousePos.x ||
        boardRect.height < relMousePos.y
      )
      {return ErrorMove;}

      int rowX = int(relativeX) % int(boardRect.width / 8);
      int rowY = int(relativeY) / int(boardRect.height / 8);

      int index = rowX + rowY * 8;

      if (index != selectedPieceIndex) {
        Move move = {(uint16_t) selectedPieceIndex, (uint16_t) index, MoveFlag::Quiet};
        return move;
      }

      DeSelectPiece();
    }
  }
  return ErrorMove;
}
