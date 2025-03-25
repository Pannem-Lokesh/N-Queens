#include <stdio.h>
#include <stdlib.h>

// Function to print the chessboard
void printSolution(int **board, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%c ", board[i][j] ? 'Q' : '.');
        printf("\n");
    }
    printf("\n");
}

// Function to check if placing a queen at (row, col) is safe
int isSafe(int **board, int row, int col, int N) {
    // Check the column
    for (int i = 0; i < row; i++)
        if (board[i][col])
            return 0;

    // Check upper-left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return 0;

    // Check upper-right diagonal
    for (int i = row, j = col; i >= 0 && j < N; i--, j++)
        if (board[i][j])
            return 0;

    return 1;
}

// Recursive function to solve the N-Queens problem
int solveNQueens(int **board, int row, int N) {
    if (row == N) { // All queens are placed
        printSolution(board, N);
        return 1;
    }

    int found = 0;
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col, N)) {
            board[row][col] = 1; // Place queen
            found |= solveNQueens(board, row + 1, N);
            board[row][col] = 0; // Backtrack
        }
    }
    return found;
}

void solve(int N) {
    // Allocate memory for NxN board dynamically
    int **board = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
        board[i] = (int *)calloc(N, sizeof(int));

    if (!solveNQueens(board, 0, N))
        printf("No solution exists\n");

    // Free dynamically allocated memory
    for (int i = 0; i < N; i++)
        free(board[i]);
    free(board);
}

int main() {
    int N;
    printf("Enter the size of the chessboard (N): ");
    scanf("%d", &N);

    if (N < 1) {
        printf("Invalid board size. N must be >= 1.\n");
        return 1;
    }

    solve(N);
return 0;
}