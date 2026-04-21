#include <iostream>
#include <ctime>
#include <cassert>

using namespace std;

void displayBoard(const int board[9][9]) {
    cout << "Sudoku Board: " << endl;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool isValid(const int board[9][9], int row, int col, int num) {
    for (int i = 0; i < 9; ++i) {
        if (board[row][i] == num) {
            return false;
        }
    }

    for (int i = 0; i < 9; ++i) {
        if (board[i][col] == num) {
            return false;
        }
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = startRow; i < startRow + 3; ++i) {
        for (int j = startCol; j < startCol + 3; ++j) {
            if (board[i][j] == num) {
                return false;
            }
        }
    }

    return true;
}


bool solveSudoku(int board[9][9]) {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= 9; ++num) {
                    if (isValid(board, row, col, num)) {
                        board[row][col] = num;
                        if (solveSudoku(board)) {
                            return true;
                        }
                        board[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}


void generateBoard(int board[9][9]) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            board[i][j] = 0;
        }
    }
    solveSudoku(board);
}


void removeNumbers(int board[9][9], int cellsToRemove) {
    srand(time(0));

    while (cellsToRemove > 0) {
        int row = rand() % 9;
        int col = rand() % 9;

        if (board[row][col] != 0) {
            board[row][col] = 0;
            --cellsToRemove;
        }
    }
}


bool isSolved(const int board[9][9]) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}


bool handleUserInput(int board[9][9], int row, int col, int num) {
    if (board[row][col] != 0) {
        cout << "Cell already filled! Try a different cell." << endl;
        return false;
    }

    if (isValid(board, row, col, num)) {
        board[row][col] = num;
        return true;
    }
    else {
        cout << "Invalid move! The number " << num << " cannot be placed at (" << row + 1 << ", " << col + 1 << ")." << endl;
        return false;
    }
}

// Test case to check board generation
void testGenerateBoard() {
    int board[9][9];
    generateBoard(board);

    // Check that the board is solvable
    assert(solveSudoku(board) == true);
    cout << "testGenerateBoard passed!" << endl;
}



// Test case for solving Sudoku
void testSolveSudoku() {
    int board[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    assert(solveSudoku(board) == true); // This should be solvable
    cout << "testSolveSudoku passed!" << endl;
}

// Test case 1: Basic solvable Sudoku puzzle
void testSolveSudoku1() {
    int board[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    assert(solveSudoku(board) == true);
    cout << "testSolveSudoku1 passed!" << endl;
}

// Test case 2: Empty board (should be solvable)
void testSolveSudoku2() {
    int board[9][9] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    assert(solveSudoku(board) == true);
    cout << "testSolveSudoku2 passed!" << endl;
}

// Test case 3: One missing number in each row and column
void testSolveSudoku3() {
    int board[9][9] = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };
    assert(solveSudoku(board) == true);
    cout << "testSolveSudoku3 passed!" << endl;
}

// Test case 4: Single missing number
void testSolveSudoku4() {
    int board[9][9] = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 0}
    };
    assert(solveSudoku(board) == true);
    cout << "testSolveSudoku4 passed!" << endl;
}

// Test case 5: Two numbers missing in one row
void testSolveSudoku5() {
    int board[9][9] = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 0}
    };
    assert(solveSudoku(board) == true);
    cout << "testSolveSudoku5 passed!" << endl;
}

// Test case 6: Easy puzzle with obvious solutions
void testSolveSudoku6() {
    int board[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    assert(solveSudoku(board) == true);
    cout << "testSolveSudoku6 passed!" << endl;
}

// Test case 7: Medium difficulty puzzle
void testSolveSudoku7() {
    int board[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    assert(solveSudoku(board) == true);
    cout << "testSolveSudoku7 passed!" << endl;
}

// Test case 8: Harder puzzle
void testSolveSudoku8() {
    int board[9][9] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    assert(solveSudoku(board) == true);
    cout << "testSolveSudoku8 passed!" << endl;
}





int main() {

    testGenerateBoard();
    testSolveSudoku();
    testSolveSudoku1();
    testSolveSudoku2();
    testSolveSudoku3();
    testSolveSudoku4();
    testSolveSudoku5();
    testSolveSudoku6();
    testSolveSudoku7();
    testSolveSudoku8();


    int board[9][9];
    int difficultyLevel;

    cout << "Enter difficulty level (1 - Easy, 2 - Medium, 3 - Hard): ";
    cin >> difficultyLevel;

    generateBoard(board);

    int cellsToRemove = 0;
    switch (difficultyLevel) {
    case 1:
        cellsToRemove = 30;
        break;
    case 2:
        cellsToRemove = 40;
        break;
    case 3:
        cellsToRemove = 50;
        break;
    default:
        cout << "Invalid difficulty level! Setting to Easy." << endl;
        cellsToRemove = 30;
    }
    removeNumbers(board, cellsToRemove);

    int row, col, num;
    while (!isSolved(board)) {
        displayBoard(board);

        cout << " (To exit enter row(-1), col(-1), num(-1)) " << endl
            << "Enter row (1-9), column (1-9), and number (1-9): ";
        cin >> row >> col >> num;
        if (row == -1 && col == -1 && num == -1) {
            exit(0);
        }

        row -= 1;
        col -= 1;

        if (row >= 0 && row < 9 && col >= 0 && col < 9 && num >= 1 && num <= 9) {
            handleUserInput(board, row, col, num);
        }
        else {
            cout << "Invalid input! Please enter values within the correct range." << endl;
        }
    }

    cout << "Congratulations! Sudoku solved!" << endl;
    displayBoard(board);

    return 0;
}