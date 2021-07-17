#include <stdio.h>

long long int num_backtracks = 0;

void print_puzzle_grid(int puzzle_grid[27][3]) {
  int i;

  for (i = 0; i < 9; i++) {
      printf("[%d, %d, %d]", puzzle_grid[3*i][0], puzzle_grid[3*i][1], puzzle_grid[3*i][2]);
      printf(", ");
      printf("[%d, %d, %d]", puzzle_grid[3*i + 1][0], puzzle_grid[3*i + 1][1], puzzle_grid[3*i + 1][2]);
      printf(", ");
      printf("[%d, %d, %d]", puzzle_grid[3*i + 2][0], puzzle_grid[3*i + 2][1], puzzle_grid[3*i + 2][2]);
      printf("\n");
  }

}

int get_element(int i, int j, int puzzle_grid[27][3]) {
  return puzzle_grid[3 * i + (j / 3)][j % 3];
}

void set_element(int i, int j, int e, int puzzle_grid[27][3]) {
  puzzle_grid[3 * i + (j / 3)][j % 3] = e;
}

void clear_square(int i, int j, int puzzle_grid[27][3]) {
  puzzle_grid[3 * i + (j / 3)][j % 3] = 0;
}

int is_empty(int i, int j, int puzzle_grid[27][3]) {

  if(get_element(i, j, puzzle_grid) == 0){
    return 1;
  }

  return 0;
}

int is_valid_element(int i, int j, int e, int puzzle_grid[27][3]) {
    int y, x;

    for (y = 0; y < 9; y++) {

        if(y != i && get_element(y, j, puzzle_grid) == e) {
            return 0;
        }
    }

    for (x = 0; x < 9; x++) {

        if(x != j && get_element(i, x, puzzle_grid) == e) {
            return 0;
        }
    }

    for (y = 3 * (i / 3);  y < (3 * (i / 3)) + 3; y++){

        for (x = 3 * (j / 3); x < (3 * (j / 3)) + 3; x++){

            if( x != i && x != j  && get_element(y, x, puzzle_grid) == e) {
                return 0;
            }

        }
    }
    return 1;
}

int solve_sudoku(int puzzle_grid[27][3]) {
  int x, y, i, j, guess;

  i = -1;
  j = -1;

  for (y = 0; y < 9; y++) {

    for (x = 0; x < 9; x++) {

      if(is_empty(y, x, puzzle_grid)) {
        i = y;
        j = x;
      }
    }
  }

  if(i == -1 && j == -1) {
        return 1;
  }

  for (guess = 1; guess < 10; guess++) {

    if(is_valid_element(i, j, guess, puzzle_grid)) {
      set_element(i, j, guess, puzzle_grid);

      if(solve_sudoku(puzzle_grid)){
        return 1;
      } else {
        clear_square(i, j, puzzle_grid);
        num_backtracks ++;
      }
    }

  }
  return 0;
}

char *check_puzzle(int puzzle_grid[27][3]){

  int i, j;

  for (i = 0; i < 9; i++) {

    for (j = 0; j < 9; j++) {

      if(is_valid_element(i, j, get_element(i, j, puzzle_grid), puzzle_grid) == 0) {
        return "False";
      }
    }
  }
  return "True";
}

int main(){

  int puzzle_grid[27][3] = {
                 {0, 0, 7}, {6, 2, 0}, {0, 0, 0},
                 {0, 0, 8}, {0, 3, 0}, {6, 0, 0},
                 {0, 9, 2}, {4, 0, 7}, {0, 0, 0},

                 {0, 0, 0}, {0, 0, 0}, {2, 0, 0},
                 {0, 0, 0}, {0, 7, 0}, {0, 6, 1},
                 {0, 0, 0}, {0, 0, 0}, {0, 8, 0},

                 {0, 3, 0}, {0, 4, 0}, {0, 2, 0},
                 {0, 4, 0}, {0, 6, 9}, {8, 0, 0},
                 {1, 0, 0}, {0, 0, 0}, {0, 4, 7}
  };


  printf("original puzzle: \n");
  print_puzzle_grid(puzzle_grid);
  solve_sudoku(puzzle_grid);
  printf("solved puzzle: \n");
  print_puzzle_grid(puzzle_grid);
  printf("backtracks used: %lli \n", num_backtracks);
  printf("Is the puzzle indeed solved?: %s \n", check_puzzle(puzzle_grid));
  return 0;
}
