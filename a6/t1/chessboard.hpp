#pragma once

#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <functional>


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
      if (color == Color::WHITE) return "white";
      return "black";
    }
    std::string color_string_short() const {
      if (color == Color::WHITE) return "W";
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

    std::string type_short() const { return color_string_short() + "KI"; }

    bool valid_move(int from_x, int from_y, int to_x, int to_y) const {
      return std::abs(from_x - to_x) < 2 && std::abs(from_y - to_y) < 2;
    };
  };

  class Knight : public Piece {
   public:
    Knight(Color color_) { color = color_; }

    // missing implementations
    std::string type() const { return color_string() + " knight"; }

    std::string type_short() const { return color_string_short() + "KN"; }

    bool valid_move(int from_x, int from_y, int to_x, int to_y) const {
      return (std::abs(from_x - to_x) == 1 && std::abs(from_y - to_y) == 2) ||
             (std::abs(from_x - to_x) == 2 && std::abs(from_y - to_y) == 1);
    };
  };

  /// 8x8 squares occupied by 1 or 0 chess pieces
  std::vector<std::vector<std::unique_ptr<Piece>>> squares;

  std::function<void(const std::string &square)> on_no_piece;
  std::function<void(const Piece &piece, const std::string &from, const std::string &to)> on_piece_move_invalid;
  std::function<void(const Piece &piece, const std::string &from, const std::string &to)> on_piece_move;
  std::function<void(const Piece &piece, const std::string &square)> on_piece_removed;
  std::function<void(const Color &color)> on_lost_game;
  
  std::function<void(const Piece &piece, const std::string &to)> after_piece_move;

  ChessBoard() {
    // Initialize the squares stored in 8 columns and 8 rows:
    squares.resize(8);
    for (auto &square_column : squares) square_column.resize(8);
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
      if(on_no_piece) on_no_piece(from);
      return false;
    }

    if (!piece_from->valid_move(from_x, from_y, to_x, to_y)) {
      if(on_piece_move_invalid) on_piece_move_invalid(*piece_from, from, to);
      return false;
    }

    if(on_piece_move) on_piece_move(*piece_from, from, to);
    auto &piece_to = squares[to_x][to_y];
    
    if (piece_to) {
      if (piece_from->color != piece_to->color) {
        if(on_piece_removed) on_piece_removed(*piece_to, to);
        if (auto king = dynamic_cast<King *>(piece_to.get()))
          if(on_lost_game) on_lost_game(king->color);
      } else {
        // piece in the from square has the same color as the piece in the
        // to square
        if(on_piece_move_invalid) on_piece_move_invalid(*piece_from, from, to);
        return false;
      }
    }

    piece_to = std::move(piece_from);
    if(after_piece_move) after_piece_move(*piece_to, to);
    return true;
  }
};
