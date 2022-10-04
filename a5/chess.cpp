#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "chessboard.hpp"

using namespace std;

int main() {
  ChessBoard board;

  board.squares[4][0] = make_unique<ChessBoard::King>(ChessBoard::Color::WHITE);
  board.squares[1][0] = make_unique<ChessBoard::Knight>(ChessBoard::Color::WHITE);
  board.squares[6][0] = make_unique<ChessBoard::Knight>(ChessBoard::Color::WHITE);

  board.squares[4][7] = make_unique<ChessBoard::King>(ChessBoard::Color::BLACK);
  board.squares[1][7] = make_unique<ChessBoard::Knight>(ChessBoard::Color::BLACK);
  board.squares[6][7] = make_unique<ChessBoard::Knight>(ChessBoard::Color::BLACK);
  board.print();

  cout << "Invalid moves:" << endl;
  board.move_piece("e3", "e2");
  board.move_piece("e1", "e3");
  board.move_piece("b1", "b2");
  cout << endl;

  cout << "A simulated game:" << endl;
  board.move_piece("e1", "e2");
  board.print();
  board.move_piece("g8", "h6");
  board.print();
  board.move_piece("b1", "c3");
  board.print();
  board.move_piece("h6", "g8");
  board.print();
  board.move_piece("c3", "d5");
  board.print();
  board.move_piece("g8", "h6");
  board.print();
  board.move_piece("d5", "f6");
  board.print();
  board.move_piece("h6", "g8");
  board.print();
  board.move_piece("f6", "e8");
  board.print();
}