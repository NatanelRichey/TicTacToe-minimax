#ifndef _GAME_H_
#define _GAME_H_

#include "board.h"
#include <iostream>

#define WELCOME_MSG "Welcome to TicTacToe"
#define OP_MSG "Please select opponent (CPU,P2P): "
#define DIM_MSG "Please select board size: "

using std::cout;
using std::endl;
using std::cin;
using std::pair;

class Game
{
  Board _board;
  int _dim = DEF_DIM;
  char _turn = 'O';
  char _player_side;
  char _cpu_side;
  std::string _game_choice;
  char _winner = 'd';

 public:
  Game ()
  {
    cout << WELCOME_MSG << endl << endl;
    cout << DIM_MSG << endl;
    cin >> _dim;
    Board board(_dim);
    _board = board;
  }

  const char get_turn () const { return _turn; }

  /**
   * runs game interface. resets board and offers opponent selection.
   */
  void run ();

  /**
   * calls appropriate gameplay function based on opponent selection.
   */
  void select_opponent ();

  /**
   * runs a CPU turn until game is over, then offers replay option.
   */
  void run_cpu_game ();

  /**
   * runs a P2P turn until game is over, then offers replay option.
   */
  void run_p2p_game ();

  /**
   * runs P2P turn. offers choice to player, validates and then adds the
   * input if valid.
   */
  void run_p2p_turn ();

  pair<int,int> get_turn_selection () const;

  /**
   * checks whether game has been won, use the n_in_a_row() function of
   * class board.
   * @param board - Board object passed by reference.
   * @return true if game has been won, else false.
   */
  bool win (const Board& board);

  /**
   * checks whether value of given square is valid. valid input is a
   * coordinate of a square within the dimentions of the board, and that has a value.
   * @param x - x coordinate.
   * @param y - y coordinate.
   * @return true if input is valid, else false
   */
  bool validate_input (const int x, const int y) const
  {
    return _board.square_is_not_empty (x,y) || x < 0 || x > _dim - 1 || y <
    0 || y > _dim - 1;
  }
  Board& get_board () {return _board; }
  void validate_and_add_input (pair<int, int> &selection, const char side);

  /**
   * Identifies whether board is won, loss, or draw. Assigns value to each
   * result. Essential to minimax algorithm.
   * @param x - x coordinate.
   * @return board evaluation as integer.
   */
  int evaluate_board (Board &board);

  /**
   * Each possible turn is mapped on a "game tree". The function recursively
   * traverses the tree and calculates the maximum/minimum game path.
   * @param board - Board object passed by reference.
   * @param depth - depth of game tree to start the recursion from.
   * @param is_maxi - boolean value whether maximum score or minimum score
   * must be achieved.
   * @return maximum/minimum score as integer
   */
  int minimax (Board& board, int depth, bool is_maxi);

  /**
   * Uses minimax function to calculate the best possible move for
   * "maximizer" player (in our case the CPU).
   * @param board - Board object passed by reference.
   * @return pair of integers - coordinates of the suggested square.
   */
  pair<int, int> find_best_move (Board &board);

  /**
   * runs CPU turn. offers choice to player, validates and then adds the
   * input if valid. On CPU's turn, calculates best available move using
   * find_best_move() and the validates and adds the input if valid.
   */
  void run_cpu_turn ();

  void print_end_game_msg ();

  bool is_not_over ();

  void play_again ();

};

#endif //_GAME_H_
