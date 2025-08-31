#include <bits/stdc++.h>

using namespace std;

namespace sudoku_solver {

namespace {  // Anonymous namespace for internal linkage.

constexpr char kEmptyCell = '.';

// Checks if placing a number in a given cell is valid according to Sudoku
// rules. A placement is valid if the number is not already present in the same
// row, column, or 3x3 subgrid.
bool IsValidPlacement(const vector<vector<char>>& board, int row, int col,
                      char num) {
  // Check if the number is already in the current row or column.
  for (int i = 0; i < board.size(); ++i) {
    if (board[row][i] == num || board[i][col] == num) {
      return false;
    }
  }

  // Check if the number is in the current 3x3 subgrid.
  int box_start_row = row - row % 3;
  int box_start_col = col - col % 3;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (board[i + box_start_row][j + box_start_col] == num) {
        return false;
      }
    }
  }

  return true;
}

// The main recursive solver function using a backtracking algorithm.
// It traverses the board, and for each empty cell, tries to place a valid
// number.
bool SolveSudokuRecursive(vector<vector<char>>& board, int row, int col) {
  // If we have moved past the last column, move to the next row.
  if (col == board[0].size()) {
    col = 0;
    row++;
  }

  // Base case: If we have moved past the last row, the puzzle is solved.
  if (row == board.size()) {
    return true;
  }

  // If the current cell is not empty, skip it and move to the next one.
  if (board[row][col] != kEmptyCell) {
    return SolveSudokuRecursive(board, row, col + 1);
  }

  // Recursive step: Try placing numbers 1 through 9 in the empty cell.
  for (char num = '1'; num <= '9'; ++num) {
    if (IsValidPlacement(board, row, col, num)) {
      // If the placement is valid, make the move.
      board[row][col] = num;

      // Recurse to the next cell.
      if (SolveSudokuRecursive(board, row, col + 1)) {
        return true;  // A solution was found down the recursion path.
      }
    }
  }

  // If no number leads to a solution, backtrack by resetting the cell.
  board[row][col] = kEmptyCell;
  return false;
}

}  // namespace

// Public-facing function that initiates the recursive solver.
bool SolveSudoku(vector<vector<char>> &board) {
  return SolveSudokuRecursive(board, 0, 0);
}

}  // namespace sudoku_solver
