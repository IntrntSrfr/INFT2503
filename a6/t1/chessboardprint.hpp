#pragma once

#include <string>

#include "chessboard.hpp"

class ChessBoardPrint {
  public:
    ChessBoard &board;

    ChessBoardPrint(ChessBoard &board_) : board(board_){

      board.on_no_piece = [](const std::string &square){
        std::cout << "no piece at " << square << std::endl;
      };
      
      board.on_lost_game = [](const ChessBoard::Color &color){
        std::cout << ((color == ChessBoard::Color::BLACK) ? "black" : "white") << " lost the game" << std::endl;
      };

      board.on_piece_move_invalid = [](const ChessBoard::Piece &piece, const std::string &from, const std::string &to){
        std::cout << "can not move " << piece.type() << " from " << from << " to " << to << std::endl;
      };

      board.on_piece_move = [](const ChessBoard::Piece &piece, const std::string &from, const std::string &to){
        std::cout << piece.type() << " is moving from " << from << " to " << to << std::endl;
      };

      board.on_piece_removed = [](const ChessBoard::Piece &piece, const std::string &square){
        std::cout << piece.type() << " is being removed from " << square << std::endl;
      };

      board.after_piece_move = [](const ChessBoard::Piece &piece, const std::string &to){
        std::cout << "moved " << piece.type() << " to " << to << std::endl;
      };
      
    }

    // print the chessboard
    void print() const {
      for(auto &square_col : board.squares){
        for(auto &cell : square_col){
          if(cell)
            std::cout << cell->type_short() << " ";
          else
            std::cout << "... ";
        }
        std::cout << '\n';
      }
    };
};
