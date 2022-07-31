#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>

#define DEF_DIM 3
#define DEF_WIN 3

using std::vector;
using std::fill;
using std::find;
using std::cout;
using std::ostream;

enum direction {ul,ur,dl,dr,u,d,l,r};

class Board
{
  int _dim;
  vector<char> _board;

 public:
  Board () : _board {' ',' ',' ',' ',' ',' ',' ',' ',' '}, _dim(DEF_DIM) {}
  Board (int dim) : _dim(dim)
  {
    for (int i = 0; i < _dim * _dim; ++i)
    {
      _board.push_back (' ');
    }
  }

  /**
   * Counts how many squares on the board are occupied
   * @return counter integer
   */
  const int get_taken_squares ()
  {
    int counter = 0;
    for (const auto value : _board)
    {
      (value != ' ') ? counter++ : counter = counter;
    }
    return counter;
  }

  const int get_dim () const {return _dim;}

  vector<char>& get_board () {return _board;}

  const char get_val (const int x, const int y) const
  {
    return _board[x * _dim + y];
  }

  void set_val (const int x, const int y, const char val)
  {
    if (x == -1 && y == -1) { return; } // does nothing if no empty squares
    // left.
    assert (val == 'O' || val == 'X' || val == ' ');
    _board[x * _dim + y] = val;
  }

  void reset_board ()
  {
    _board.clear();
    for (int i = 0; i < _dim * _dim; ++i)
    {
      _board.push_back (' ');
    }
  }

  bool board_is_full () const
  {
    return find (_board.begin(), _board.end(), ' ') == _board.end();
  }

  bool square_is_not_empty (const int x, const int y) const
  {
    return get_val (x,y) != ' ';
  }

  /**
   * Checks if there is a value in the adjacent square (defined by input
   * coordinates).
   * @param x - x coordinate of square to verify.
   * @param y - y coordinate of square to verify.
   * @param direction - direction to test.
   * @return true if test passes, else fail.
   */
  bool is_adjacent (const int x, const int y, direction dir) const;

  /**
   * Checks if the the adjacent value of square (defined by input
   * coordinates) is equal to square's value.
   * @param x - x coordinate of square to verify.
   * @param y - y coordinate of square to verify.
   * @param direction - direction to test.
   * @return true if test passes, else fail.
   */
  bool is_equal (const int x, const int y, direction dir) const;

  /**
   * Checks if the the n adjacent values of square (defined by input
   * coordinates) are equal to square's value.
   * @param x - x coordinate of square to verify.
   * @param y - y coordinate of square to verify.
   * @param direction - direction to test.
   * @return true if test passes, else fail.
   */
  bool n_in_a_row (const int x, const int y, direction dir) const;

  /**
   * pretty print of board
   */
  friend ostream& operator << (ostream& os, const Board& board);

};

#endif //_BOARD_H_
