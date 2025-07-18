#include <iostream>
using namespace std;

int currentPlayer;
char currentMarker;
char markerP1, markerP2;

char board[3][3] = {
    {'1', '2', '3'},    
    {'4', '5', '6'},
    {'7', '8', '9'}
};

void drawBoard() {
    cout << "\n";
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << "\n";
    cout << "---|---|---\n";
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << "\n";
    cout << "---|---|---\n";
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << "\n";
    cout << "\n";
}

bool placeMarker(int slot) {
    int row = (slot - 1) / 3;
    int column = (slot - 1) % 3;

    if (board[row][column] != 'X' && board[row][column] != 'O') {
        board[row][column] = currentMarker;
        return true;
    }
    return false;
}

char checkWinner() {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][0];
    }

    // Check columns
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return board[0][i];
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[0][0];

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return board[0][2];

    return ' '; // No winner yet
}

void swapPlayerAndMarker() {
    if (currentMarker == markerP1) {
        currentMarker = markerP2;
        currentPlayer = 2;
    } else {
        currentMarker = markerP1;
        currentPlayer = 1;
    }
}

void game() {
    cout << "Player 1, choose your marker (X or O): ";
    cin >> markerP1;

    // Validate input
    while (markerP1 != 'X' && markerP1 != 'O') {
        cout << "Invalid marker! Choose 'X' or 'O': ";
        cin >> markerP1;
    }

    markerP2 = (markerP1 == 'X') ? 'O' : 'X';
    currentPlayer = 1;
    currentMarker = markerP1;

    drawBoard();

    for (int i = 0; i < 9; i++) {
        int slot;
        cout << "It's Player " << currentPlayer << "'s turn. Enter your slot (1-9): ";
        cin >> slot;

        if (slot < 1 || slot > 9) {
            cout << "Invalid slot! Please enter a number between 1 and 9.\n";
            i--;
            continue;
        }

        if (!placeMarker(slot)) {
            cout << "Slot already taken! Try again.\n";
            i--;
            continue;
        }

        drawBoard();

        char winner = checkWinner();
        if (winner == markerP1) {
            cout << "Player 1 wins! 🎉\n";
            return;
        } else if (winner == markerP2) {
            cout << "Player 2 wins! 🎉\n";
            return;
        }

        swapPlayerAndMarker();
    }

    cout << "It's a tie! 🤝\n";
}

int main() {
    game();
    return 0;
}

