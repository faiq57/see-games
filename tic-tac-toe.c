#include <stdio.h>

#define LENGTH 3
#define TRUE 1
#define FALSE 0
#define DRAW -1
#define EMPTY 0
#define CROSS 1
#define CIRCLE 2

void initialize_board(int piece[LENGTH][LENGTH]);
void print_board(int piece[LENGTH][LENGTH]);
void play(int piece[LENGTH][LENGTH]);
void place_piece(int piece[LENGTH][LENGTH], int turn);
void print_result(int win);
int determine_start(void);
int invalid_position(int row, int col);
int occupied(int piece[LENGTH][LENGTH], int row, int col);
int check_win(int piece[LENGTH][LENGTH]);
int check_win_row(int piece[LENGTH][LENGTH]);
int check_win_column(int piece[LENGTH][LENGTH]);
int check_win_diagonal(int piece[LENGTH][LENGTH]);
int check_draw(int piece[LENGTH][LENGTH]);
int change_turn(int turn);

int main(void) {
    int board[LENGTH][LENGTH];
    initialize_board(board);
    play(board);
    return 0;
}

void initialize_board(int piece[LENGTH][LENGTH]) {
    for (int row = 0; row < LENGTH; row++) {
        for (int col = 0; col < LENGTH; col++) {
            piece[row][col] = EMPTY;
        }
    }
}

void print_board(int piece[LENGTH][LENGTH]) {
    for (int row = 0; row < LENGTH; row++) {
        for (int col = 0; col < LENGTH; col++) {
            if (piece[row][col] == CROSS) {
                printf("X");
            }
            else if (piece[row][col] == CIRCLE) {
                printf("O");
            }
            else {
                printf(" ");
            }
            printf(" ");
        }
        printf("\n");
    }
}

void play(int piece[LENGTH][LENGTH]) {
    int turn = determine_start();
    int win = FALSE;
    while (!win) {
        place_piece(piece, turn);
        print_board(piece);
        win = check_win(piece);
        turn = change_turn(turn);
    }
    print_result(win);
}

int determine_start(void) {
    char first;
    printf("Who starts first? (X/O)\n");
    while (scanf(" %c", &first) != 1 || (first != 'X' && first != 'O')) {
        printf("Enter either 'X' or 'O' only!\n");
    }

    if (first == 'X') {
        return CROSS;
    }
    else {
        return CIRCLE;
    }
}

void place_piece(int piece[LENGTH][LENGTH], int turn) {
    int row;
    int col;

    printf("Where do you want to place your piece? ");
    while (scanf("%d %d", &col, &row) != 2 || invalid_position(row, col) || occupied(piece, row, col)) {
        printf("Enter a valid position for a %d by %d board!\n", LENGTH, LENGTH);
        printf("Where do you want to place your piece? ");
    }

    row--;
    col--;
    piece[row][col] = turn;
}

int invalid_position(int row, int col) {
    if (row <= 0 || row > LENGTH) {
        return 1;
    }
    else if (col <= 0 || col > LENGTH) {
        return 1;
    }
    return 0;
}

int occupied(int piece[LENGTH][LENGTH], int row, int col) {
    if (piece[row - 1][col - 1] != EMPTY) {
        return 1;
    }
    return 0;
}

int check_win(int piece[LENGTH][LENGTH]) {
    int win = check_win_row(piece);
    if (win != FALSE) {
        return win;
    }

    win = check_win_column(piece);
    if (win != FALSE) {
        return win;
    }

    win = check_win_diagonal(piece);
    if (win != FALSE) {
        return win;
    }

    return check_draw(piece);
}

int check_win_row(int piece[LENGTH][LENGTH]) {
    int win = piece[0][0];
    int row = 0;
    int col = 0;
    for (row = 0; row < LENGTH; row++) {
        if (win == EMPTY) {
            col++;
            if (col < LENGTH) {
                win = piece[0][col];
            }
        }
        if (win != piece[row][col]) {
            row = 0;
            col++;
            if (col < LENGTH) {
                win = piece[0][col];
            }
        }
        if (col >= LENGTH) {
            return FALSE;
        }
    }
    return win;
}

int check_win_column(int piece[LENGTH][LENGTH]) {
    int win = piece[0][0];
    int row = 0;
    int col = 0;

    for (col = 0; col < LENGTH; col++) {
        if (win == EMPTY) {
            row++;
            if (row < LENGTH) {
                win = piece[row][0];
            }
        }
        if (win != piece[row][col]) {
            col = 0;
            row++;
            if (row < LENGTH) {
                win = piece[row][0];
            }
        }
        if (row >= LENGTH) {
            return FALSE;
        }
    }
    return win;
}

int check_win_diagonal(int piece[LENGTH][LENGTH]) {
    int row = 0;
    int col = 0;
    int win = piece[row][col];

    while (row != LENGTH) {
        if (win != piece[row][col]) {
            break;
        }
        row++;
        col++;
    }
    if (row == LENGTH) {
        return piece[row - 1][col - 1];
    }

    row = 0;
    col = LENGTH - 1;
    win = piece [row][col];

    while (row != LENGTH) {
        if (win != piece[row][col]) {
            break;
        }
        row++;
        col--;
    }
    if (row == LENGTH) {
        return piece[row - 1][col + 1];
    }

    return FALSE;
}

int check_draw(int piece[LENGTH][LENGTH]) {
    for (int row = 0; row < LENGTH; row++) {
        for (int col = 0; col < LENGTH; col++) {
            if (piece[row][col] == EMPTY) {
                return FALSE;
            }
        }
    }
    return DRAW;
}

int change_turn(int turn) {
    if (turn == CROSS) {
        return CIRCLE;
    }
    else {
        return CROSS;
    }
}

void print_result(int win) {
    if (win == DRAW) {
        printf("The game ends in a draw!\n");
        return;
    }

    char winner;
    char loser;
    if (win == CROSS) {
        winner = 'X';
        loser = 'O';
    }
    else {
        winner = 'O';
        loser = 'X';
    }
    printf("'%c' won! Sucks to be '%c'!\n", winner, loser);
}
