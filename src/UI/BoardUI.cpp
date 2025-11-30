#include "../../include/raylib-cpp.hpp"
#include "../Engine/BoardTypes.hpp"
#include "BoardUI.hpp"
#include "../Render/Boardrender.hpp"
#include <algorithm>
#include <stdexcept>

static int selectedPieceIndex = -1;
static int droptimes = 0;
static bool dragging = false;


void DrawPieceAt(Piece* piece, float x, float y, float width, float height) {
  if (!textureinitialized) {
    throw std::runtime_error("PieceTexture was not initialized");
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

int GetMouseIndex(raylib::Rectangle boardRect) {

  raylib::Vector2 mp = raylib::Mouse::GetPosition();

  raylib::Vector2 relMousePos = {
    mp.x - boardRect.x,
    mp.y - boardRect.y,
  };

  if (
    0 > relMousePos.x ||
    0 > relMousePos.y ||
    boardRect.width < relMousePos.x ||
    boardRect.height < relMousePos.y
  ) {return -1;}

  int rowX = int(relMousePos.x) / int(boardRect.width / 8);
  int rowY = int(relMousePos.y) / int(boardRect.height / 8);

  int index = rowX + rowY * 8;

  index = (index < 0 || index > 63) ? -1 : index;

  return index;
}

Move HandleMouse(Board board, raylib::Rectangle boardRect) {

  bool mouseDown = raylib::Mouse::IsButtonDown(0);
  bool mouseReleased = raylib::Mouse::IsButtonReleased(0);
  raylib::Vector2 mousePos = raylib::Mouse::GetPosition();

  int mouseIndex = GetMouseIndex(boardRect);
  bool validIndex = mouseIndex != -1;

  bool pieceSelected = selectedPieceIndex != -1;
  bool onPiece = (validIndex && board.squares[mouseIndex].GetType() != PieceType::Empty);

  if (!pieceSelected && mouseDown && onPiece) {
    selectedPieceIndex = mouseIndex;
    dragging = true;
    droptimes = 0;
  }

  if (pieceSelected && dragging) {

    float squareSize = boardRect.width / 8;

    int selX = selectedPieceIndex % 8;
    int selY = selectedPieceIndex / 8;

    raylib::Rectangle selectedRect = {
      boardRect.x + selX * squareSize,
      boardRect.y + selY * squareSize,
      squareSize,
      squareSize
    };

    DrawRectangleRec(selectedRect, BoardColors::HighlightSquare);

    DrawPieceAt(
      &board.squares[selectedPieceIndex],
      mousePos.x - squareSize / 2,
      mousePos.y - squareSize / 2,
      squareSize,
      squareSize
    );

    if (mouseReleased) {

      dragging = false;

      if (!validIndex) {
        selectedPieceIndex = -1;
        return ErrorMove;
      }

      if (mouseIndex == selectedPieceIndex) {
        droptimes++;
        if ( droptimes >= 2) {
          selectedPieceIndex = -1;
        } 
        return ErrorMove;
      }

      Move m(selectedPieceIndex, mouseIndex, MoveFlag::Quiet);
      selectedPieceIndex = -1;
      return m;
    }
  }

  if (pieceSelected && !dragging) {
    float squareSize = boardRect.width / 8;
    int sx = selectedPieceIndex % 8;
    int sy = selectedPieceIndex / 8;

    raylib::Rectangle r = {
        boardRect.x + sx * squareSize,
        boardRect.y + sy * squareSize,
        squareSize,
        squareSize
    };
    DrawRectangleRec(r, BoardColors::HighlightSquare);
    DrawPieceAt(&board.squares[selectedPieceIndex], r.x, r.y, squareSize, squareSize);

    if (mouseReleased && validIndex && mouseIndex != selectedPieceIndex) {
        Move m(selectedPieceIndex, mouseIndex, MoveFlag::Quiet);
        selectedPieceIndex = -1;
        return m;
    }

    if (mouseDown && mouseIndex == selectedPieceIndex) {
      dragging = true; 
    }
  }

  return ErrorMove;
}
