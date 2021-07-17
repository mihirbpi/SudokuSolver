#include <stdio.h>
#define N 27
#define M 3

long long int num_backtracks = 0;

void print_puzzle_grid(int puzzle_grid[N][M]) {
  int i;

  for (i = 0; i < M*M; i++) {
      printf("[%d, %d, %d]", puzzle_grid[M*i][0], puzzle_grid[M*i][1], puzzle_grid[M*i][2]);
      printf(", ");
      printf("[%d, %d, %d]", puzzle_grid[M*i + 1][0], puzzle_grid[M*i + 1][1], puzzle_grid[M*i + 1][2]);
      printf(", ");
      printf("[%d, %d, %d]", puzzle_grid[M*i + 2][0], puzzle_grid[M*i + 2][1], puzzle_grid[M*i + 2][2]);
      printf("\n");
  }
}

int get_element(int i, int j, int puzzle_grid[N][M]) {
  return puzzle_grid[M * i + (j / M)][j % M];
}

void set_element(int i, int j, int e, int puzzle_grid[N][M]) {
  puzzle_grid[M * i + (j / M)][j % M] = e;
}

void clear_square(int i, int j, int puzzle_grid[N][M]) {
  puzzle_grid[M * i + (j / M)][j % M] = 0;
}

int is_empty(int i, int j, int puzzle_grid[N][M]) {

  if(get_element(i, j, puzzle_grid) == 0){
    return 1;
  }

  return 0;
}

int is_valid_element(int i, int j, int e, int puzzle_grid[N][M]) {
    int y, x;

    for (y = 0; y < M*M; y++) {

        if(y != i && get_element(y, j, puzzle_grid) == e) {
            return 0;
        }
    }

    for (x = 0; x < M*M; x++) {

        if(x != j && get_element(i, x, puzzle_grid) == e) {
            return 0;
        }
    }

    for (y = M * (i / M);  y < (M * (i / M)) + M; y++) {

        for (x = M * (j / M); x < (M * (j / M)) + M; x++) {

            if( x != i && x != j  && get_element(y, x, puzzle_grid) == e) {
                return 0;
            }
        }
    }
    return 1;
}

void make_implications(int puzzle_grid[N][M], int implications_list[M*M][M*M][M*M+1]) {
  int i, j, k, num, num_nonzeroes, guess;

  for (i = 0; i < M*M; i++) {

    for (j = 0; j < M*M; j++) {

        if (is_empty(i, j, puzzle_grid)) {

          for (num = 1; num < M*M+1; num++){

            if(is_valid_element(i, j, num, puzzle_grid) == 0){
              implications_list[i][j][num] = 0;
            }
          }

          num_nonzeroes = M*M;

          for (k = 1; k < M*M+1; k++) {

            if(implications_list[i][j][k] == 0){
                num_nonzeroes --;
            } else {
              guess = implications_list[i][j][k];
            }
          }

          if(num_nonzeroes == 1) {
            implications_list[i][j][0] = 1;
            set_element(i, j, guess, puzzle_grid);
          }
      }
    }
  }
}

void clear_implications(int puzzle_grid[N][M], int implications_list[M*M][M*M][M*M+1]) {
  int i, j, k;

  for (i = 0; i < M*M; i++) {

    for (j = 0; j < M*M; j++) {

      if(implications_list[i][j][0] == 1){
        clear_square(i, j, puzzle_grid);
      }
    }
  }

  for (i = 0; i < M*M; i++) {

    for (j = 0; j < M*M; j++) {

      for (k = 0; k < M*M+1; k++){
        implications_list[i][j][k] = k;
      }
    }
  }
}

int solve_sudoku(int puzzle_grid[N][M], int implications_list[M*M][M*M][M*M+1]) {
  int x, y, i, j, guess;

  i = -1;
  j = -1;

  for (y = 0; y < M*M; y++) {

    for (x = 0; x < M*M; x++) {

      if(is_empty(y, x, puzzle_grid)) {
        i = y;
        j = x;
      }
    }
  }

  if(i == -1 && j == -1) {
        return 1;
  }

  for (guess = 1; guess < M*M+1; guess++) {

    if(is_valid_element(i, j, guess, puzzle_grid)) {
      set_element(i, j, guess, puzzle_grid);
      make_implications(puzzle_grid, implications_list);

      if(solve_sudoku(puzzle_grid, implications_list)){
        return 1;
      } else {
        clear_implications(puzzle_grid, implications_list);
        clear_square(i, j, puzzle_grid);
        num_backtracks ++;
      }
    }
  }
  return 0;
}

char *check_puzzle(int puzzle_grid[N][M]){

  int i, j;

  for (i = 0; i < M*M; i++) {

    for (j = 0; j < M*M; j++) {

      if(is_valid_element(i, j, get_element(i, j, puzzle_grid), puzzle_grid) == 0) {
        return "False";
      }
    }
  }
  return "True";
}

int main(){

  int puzzle_grid[N][M] = {
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

  int implications_list[M*M][M*M][M*M+1] = {0};

  int i, j, k;

  for (i = 0; i < M*M; i++) {

    for (j = 0; j < M*M; j++) {

      for (k = 0; k < M*M+1; k++) {
        implications_list[i][j][k] = k;
      }
    }
  }

  printf("original puzzle: \n");
  print_puzzle_grid(puzzle_grid);
  solve_sudoku(puzzle_grid, implications_list);
  printf("solved puzzle: \n");
  print_puzzle_grid(puzzle_grid);
  printf("backtracks used: %lli \n", num_backtracks);
  printf("Is the puzzle indeed solved?: %s \n", check_puzzle(puzzle_grid));
  return 0;
}
