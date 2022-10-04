#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class ChessBoard {
 public:
  enum class Color { WHITE, BLACK };

  class Piece {
   public:
    Piece() {}
    Piece(Color color_) { color = color_; };
    virtual ~Piece() {}

    Color color;
    std::string color_string() const {
      if (color == Color::WHITE)
        return "white";
      return "black";
    }
    std::string color_string_short() const {
      if(color == Color::WHITE)
        return "W";
      return "B";
    }

    /// Return color and type of the chess piece
    virtual std::string type() const = 0;
    virtual std::string type_short() const = 0;

    /// Returns true if the given chess piece move is valid
    virtual bool valid_move(int from_x, int from_y, int to_x,
                            int to_y) const = 0;
  };

  class King : public Piece {
   public:
    // missing implementations
    King(Color color_) { color = color_; }

    std::string type() const { return color_string() + " king"; }
    
    std::string type_short() const {return color_string_short() + "KI";}
    
    bool valid_move(int from_x, int from_y, int to_x, int to_y) const {
      return std::abs(from_x - to_x) < 2 && std::abs(from_y - to_y) < 2;
    };
  };

  class Knight : public Piece {
   public:
    Knight(Color color_) { color = color_; }

    // missing implementations
    std::string type() const { return color_string() + " knight"; }
    
    std::string type_short() const {return color_string_short() + "KN";}

    bool valid_move(int from_x, int from_y, int to_x, int to_y) const {
      return (std::abs(from_x - to_x) == 1 && std::abs(from_y - to_y) == 2) ||
             (std::abs(from_x - to_x) == 2 && std::abs(from_y - to_y) == 1);
    };
  };

  /// 8x8 squares occupied by 1 or 0 chess pieces
  std::vector<std::vector<std::unique_ptr<Piece>>> squares;

  ChessBoard() {
    // Initialize the squares stored in 8 columns and 8 rows:
    squares.resize(8);
    for (auto &square_column : squares) square_column.resize(8);
  }

  // print the chessboard
  void print() const {
    for(auto &square_col : squares){
      for(auto &cell : square_col){
        if(cell)
          std::cout << cell->type_short() << " ";
        else
          std::cout << "... ";
      }
      std::cout << '\n';
    }
  }

  /// Move a chess piece if it is a valid move.
  /// Does not test for check or checkmate.
  bool move_piece(const std::string &from, const std::string &to) {
    int from_x = from[0] - 'a';
    int from_y = std::stoi(std::string() + from[1]) - 1;
    int to_x = to[0] - 'a';
    int to_y = std::stoi(std::string() + to[1]) - 1;

    auto &piece_from = squares[from_x][from_y];
    if (!piece_from) {
      std::cout << "no piece at " << from << std::endl;
      return false;
    }

    if (!piece_from->valid_move(from_x, from_y, to_x, to_y)) {
      std::cout << "can not move " << piece_from->type() << " from " << from
                << " to " << to << std::endl;
      return false;
    }

    std::cout << piece_from->type() << " is moving from " << from << " to "
              << to << std::endl;
    auto &piece_to = squares[to_x][to_y];
    if (piece_to) {
      if (piece_from->color != piece_to->color) {
        std::cout << piece_to->type() << " is being removed from " << to
                  << std::endl;
        if (auto king = dynamic_cast<King *>(piece_to.get()))
          std::cout << king->color_string() << " lost the game" << std::endl;
      } else {
        // piece in the from square has the same color as the piece in the
        // to square
        std::cout << "can not move " << piece_from->type() << " from " << from
                  << " to " << to << std::endl;
        return false;
      }
    }
    piece_to = move(piece_from);
    return true;
  }
};
