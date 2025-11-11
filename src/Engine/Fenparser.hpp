#include "BoardTypes.hpp"
#include <string>
typedef std::string Fenstring;

Fenstring to_fen(Board board);
Board to_board(Fenstring fen);
