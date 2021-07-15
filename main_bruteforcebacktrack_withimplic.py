puzzle_grid = [[0, 0, 7], [6, 2, 0], [0, 0, 0],
               [0, 0, 8], [0, 3, 0], [6, 0, 0],
               [0, 9, 2], [4, 0, 7], [0, 0, 0],

               [0, 0, 0], [0, 0, 0], [2, 0, 0],
               [0, 0, 0], [0, 7, 0], [0, 6, 1],
               [0, 0, 0], [0, 0, 0], [0, 8, 0],

               [0, 3, 0], [0, 4, 0], [0, 2, 0],
               [0, 4, 0], [0, 6, 9], [8, 0, 0],
               [1, 0, 0], [0, 0, 0], [0, 4, 7]]

num_backtracks = 0
implications_list = []

def print_puzzle_grid():
    global puzzle_grid

    for i in range(0, 9):
        print(str(puzzle_grid[3 * i]) + ", " + str(puzzle_grid[3 * i + 1]) + ", " + str(puzzle_grid[3 * i + 2]) + "\n")

def get_element(i, j):
    global puzzle_grid
    return puzzle_grid[3 * i + (j // 3)][j % 3]

def set_element(i , j, e):
    global puzzle_grid
    puzzle_grid[3 * i + (j // 3)][j % 3] = e

def clear_square(i , j):
    global puzzle_grid
    puzzle_grid[3 * i + (j // 3)][j % 3] = 0

def is_empty(i, j):
    return get_element(i, j) == 0

def is_valid_element(i, j, e):

    for y in range(0, 9):

        if(y != i and get_element(y, j) == e):
            return False

    for x in range (0, 9):

        if(x != j and get_element(i, x) == e):
            return False

    for y in range(3 * (i // 3), (3 * (i // 3)) + 3):

        for x in range(3 * (j // 3), (3 * (j // 3)) + 3):

            if( x != i and x != j  and get_element(y, x) == e):
                return False
    return True

def first_empty_square():

    for i in range(0, 9):

        for j in range(0, 9):

            if(is_empty(i, j)):
                return i, j

    return -1, -1

def make_implications():

    global implications_list

    for i in range(0, 9):

        for j in range(0, 9):

            if(is_empty(i, j)):
                valid_values_set = {1, 2, 3, 4, 5, 6, 7, 8, 9}

                for num in range(1, 10):

                    if(not is_valid_element(i, j, num)):
                        valid_values_set.remove(num)

                if(len(valid_values_set) == 1):
                    implications_list.append([i, j, valid_values_set])
                    set_element(i, j, valid_values_set.pop())

def clear_implications():
    global implications_list

    for elem in implications_list:
        clear_square(elem[0], elem[1])

    implications_list = []

def solve_sudoku():
    global num_backtracks

    i = -1
    j = -1

    for y in range(0, 9):

        for x in range(0, 9):

            if(is_empty(y, x)):
                i = y
                j = x

    if(i == -1 and j == -1):
        return True

    for guess in range(1, 10):

        if(is_valid_element(i, j, guess)):
            set_element(i, j, guess)

            make_implications()

            if(solve_sudoku()):
                return True
            else:
                clear_implications()
                clear_square(i, j)
                num_backtracks += 1

    return False

def check_puzzle():

    for i in range(0, 9):

        for j in range(0, 9):

            if(not is_valid_element(i, j, get_element(i, j))):
                return False
    return True

print("original puzzle: \n")
print_puzzle_grid()
solve_sudoku()
print("solved puzzle: \n")
print_puzzle_grid()
print("backtracks used: ", num_backtracks)
print("Is the puzzle indeed solved?: ", check_puzzle())
