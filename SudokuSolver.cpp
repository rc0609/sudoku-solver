/*
File title: SudokuSolver.cpp
Author: Ramisha Chowdhury
Breif Description: Project 6 This program will implement SudokuSolver class. 
This is the implementation.
*/

#include "SudokuSolver.hpp"
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>

SudokuSolver::SudokuSolver() //Default Constructor
{
    size_ = 9;
    board_ = new int *[size_];
    for (int i = 0; i < size_; i++)
    {
        board_[i] = new int[size_];
        for (int j = 0; j < size_; j++)
        {
            board_[i][j] = 0;
        }
    }
    solvable_ = false;

}

SudokuSolver::SudokuSolver(string input_file) //Parametirized constructor
{
    size_ = 9;
    board_ = new int *[size_];
    for (int i = 0; i < size_; i++)
    {
        board_[i] = new int[size_];
        for (int j = 0; j < size_; j++)
        {
            board_[i][j] = 0;
        }
    }

    std::ifstream fin(input_file);
    if (fin.fail())
    {
        std::cerr << "Error. File can not be opened.";
        exit(1);
    }

    std::string line;
    int r = 0;

    while (std::getline(fin, line))
    {
        int c = 0;
        std::stringstream ss(line);
        std::string temp;

        while (std::getline(ss, temp, ','))
        {
            board_[r][c] = std::stoi(temp);
            c++;
        }
        r++;
    }

    solvable_ = solve();
}

//Helper function
bool SudokuSolver::solve()
{
    Sudoku::Location empty_space = returnNextEmpty();

    if (empty_space.row == -1 && empty_space.col == -1)
    {
        return true;
    }

    for (int i = 1; i <= size_; i++)
    {
        if (checkLegalValue(i, empty_space))
        {
            board_[empty_space.row][empty_space.col] = i;

            if (solve())
            {
                return true;
            }

            board_[empty_space.row][empty_space.col] = 0;
        }
    }

    return false;
}

/**
    @return true if puzzle is solved, false otherwise 
*/
bool SudokuSolver::isPuzzleSolvable()
{
    return solvable_;
}

/**
    @post set the puzzle is solvable 
*/
void SudokuSolver::setSolvable()
{
    solvable_ = true;
}


/**
    @return the 2D pointer array representing the puzzle 
*/
int **SudokuSolver::getPuzzleNumbers()
{
    return board_;
}

/**
  @param: 2D array pointer representing the puzzle
  @post:  sets the  2D pointer array representing the puzzle to the value of the parameter 
*/
void SudokuSolver::setPuzzleNumbers(int **puzzle)
{
   size_ = 9;
    for (int i = 0; i < size_; i++)
    {
        for (int j = 0; j < size_; j++)
        {
            board_[i][j] = puzzle[i][j];
        }
    }
}

/**
  @return:  a Location object with the coordinates of the first 0 found in the 2D pointer array 
*/
Sudoku::Location SudokuSolver::returnNextEmpty()
{
    Sudoku::Location location{-1, -1};

    for (int i = 0; i < size_; i++)
    {
        for (int j = 0; j < size_; j++)
        {
            if (board_[i][j] == 0)
            {
                location = {i, j};
                return location;
            }
        }
    }
    return location;
}

/**
  @pre  : consist of 9 digits on each row separated by commas, and 9 rows separated by new line characters \n, 
          corresponding to a sudoku board. Empty squares contain the digit 0. 
  @param: value (1 - 9)
  @param: location on the puzzle
  @return:  returns true if the value parameter (which can take on values 1-9) can legally be placed at the given location 
            in the 2D array without breaking the rules of sudoku. returns false if placing value at location is not a legal move
    */
bool SudokuSolver::checkLegalValue(int value, Sudoku::Location location)
{
    int row = location.row;
    int col = location.col;

    for (int i = 0; i < size_; i++)
    {
        if (board_[row][i] == value)
        {
            return false;
        }
    }

    for (int i = 0; i < size_; i++)
    {
        if (board_[i][col] == value)
        {
            return false;
        }
    }

    int subgrid_size = sqrt(size_);
    int subgrid_row = row / subgrid_size;
    int subgrid_col = col / subgrid_size;

    for (int i = subgrid_row * subgrid_size; i < (subgrid_row + 1) * subgrid_size; i++)
    {
        for (int j = subgrid_col * subgrid_size; j < (subgrid_col + 1) * subgrid_size; j++)
        {
            if (board_[i][j] == value)
            {
                return false;
            }
        }
    }

    return true;
}



/** @return: display the puzzle, N is number and X represents empty
  */
void SudokuSolver::display()
{
    for (int i = 0; i < size_; i++)
    {
        for (int j = 0; j < size_; j++)
        {
            if (board_[i][j] == 0)
            {
                cout << "X ";
            }
            else
            {
                cout << board_[i][j] << " ";
            }
            if (j % 3 == 2 && j != size_ - 1)
            {
                cout << " | ";
            }
        }
        cout << endl;
        if (i % 3 == 2 && i != size_ - 1)
        {
            cout << "- - - - - - - - - - - -" << endl;
        }
    }
}
