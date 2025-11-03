#include <cstdint>


enum class PieceType : uint8_t{
  Empty = 0,
  Pawn,
  Knight,
  Bishop,
  Rook,
  Queen,
  King
};

enum class PieceColor : uint8_t{
  White = 0b00000000,
  Black = 0b00001000,
};

enum class PieceFlag {
  Highlight = 0b00010000,
  CanMove   = 0b00100000,
  HasMoved  = 0b01000000,
  LastMoved = 0b10000000,
};


inline uint8_t to_uint8(PieceType type) { return static_cast<uint8_t>(type); }
inline uint8_t to_uint8(PieceColor color) { return static_cast<uint8_t>(color); }
inline uint8_t to_uint8(PieceFlag flag) { return static_cast<uint8_t>(flag); }

struct Piece {
  uint8_t data;
  
  Piece(uint8_t data) : data(data) {}
  Piece(PieceFlag flags, PieceColor color, PieceType type) : data(to_uint8(flags) | to_uint8(color) | to_uint8(type)) {}

  
  uint8_t GetType();
  uint8_t GetColor();
  uint8_t GetHighlight();
  uint8_t GetCanMove();
  uint8_t GetHasMoved();
  uint8_t GetLastMoved();

  
  void SetCanMove(bool value);
  void SetHighlight(bool value);
  void SetLastMoved(bool value);
  void SetHasMoved(bool value);
  void SetType(PieceType type);
  void SetColor(PieceColor color);
  void SetFlag(PieceFlag flag);
  
  
};

struct Board {
  Piece Squares[64];
  bool Castelign[4]; //topleft -> bottomright

};
// look at notes.md


