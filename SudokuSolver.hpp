/*
File title: SudokuSolver.hpp
Author: Ramisha Chowdhury
Breif Description: Project 6 This program will implement SudokuSolver class. 
This is the interface.
*/

#ifndef SUDOKU_SOLVER_HPP_
#define SUDOKU_SOLVER_HPP_

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
using namespace std;


//We define Location within the Sudoku namespace.
//To use Location, you must specify the namespace Sudoku::Location
//Just like you do when using the standard namespace std::
namespace Sudoku
{ 
  struct Location
  {
    int row;
    int col;
  };
}

class SudokuSolver
{
public:
  SudokuSolver(); //default constructor

  /**
  @pre  : consist of 9 digits on each row separated by commas, and 9 rows separated by new line characters \n, 
          corresponding to a sudoku board. Empty squares contain the digit 0. 
  @param: the name of the input file
  @post:  Reads the input file and solve it and records whether the puzzle has a solution or not 
    */
  SudokuSolver(string input_file); //parameterized constructor


  //Helper function
  bool solve();

  /**
     @return true if puzzle is solved, false otherwise */
  bool isPuzzleSolvable();

  /**
     @post set the puzzle is solvable */
  void setSolvable();


 /**
     @return the 2D pointer array representing the puzzle */
  int **getPuzzleNumbers();


/**
  @param: 2D array pointer representing the puzzle
  @post:  sets the  2D pointer array representing the puzzle to the value of the parameter 
    */
  void setPuzzleNumbers(int **puzzle);

/**
  @return:  a Location object with the coordinates of the first 0 found in the 2D pointer array 
    */
  Sudoku::Location returnNextEmpty();

  /**
  @pre  : consist of 9 digits on each row separated by commas, and 9 rows separated by new line characters \n, 
          corresponding to a sudoku board. Empty squares contain the digit 0. 
  @param: value (1 - 9)
  @param: location on the puzzle
  @return:  returns true if the value parameter (which can take on values 1-9) can legally be placed at the given location 
            in the 2D array without breaking the rules of sudoku. returns false if placing value at location is not a legal move
    */
  bool checkLegalValue(int value, Sudoku::Location location);

  /** @return: display the puzzle, N is number and X represents empty
  */
  void display();

private:
  int **board_;
  int size_;
  bool solvable_;
};

#endif
