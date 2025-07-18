
#include <iostream>
#include <ncurses.h>   // For real-time keyboard input
#include <unistd.h>    // For usleep (to control game speed)
#include <cstdlib>     // For rand()
using namespace std;

// Game control
bool gameOver;
const int width = 40;
const int height = 20;

// Snake and fruit
int headX, headY, fruitX, fruitY, score, nTail;
int tailX[100], tailY[100];

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

// 1. Setup everything at the beginning
void Setup() {
    gameOver = false;
    dir = STOP;
    headX = width / 2;
    headY = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 0;
}

// 2. Draw the game
void Draw() {
    clear();
    cout << "SCORE: " << score << endl;

    for (int i = 0; i <= width; i++) cout << "-";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j <= width; j++) {
            if (j == 0 || j == width)
                cout << "|";
            else if (i == headY && j == headX)
                cout << "O";  // Snake head
            else if (i == fruitY && j == fruitX)
                cout << "*";  // Fruit
            else {
                bool printTail = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";  // Snake tail
                        printTail = true;
                        break;
                    }
                }
                if (!printTail) cout << " ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i <= width; i++) cout << "-";
    cout << endl;
}

// 3. Check if key is hit
int kbhit() {
    int ch = getch();
    if (ch != ERR) {
        ungetch(ch);
        return 1;
    }
    return 0;
}

// 4. Handle input
void Input() {
    usleep(150000);  // 0.15 sec delay
    nodelay(stdscr, TRUE);

    if (kbhit()) {
        switch (getch()) {
            case 'a': dir = LEFT; break;
            case 'd': dir = RIGHT; break;
            case 'w': dir = UP; break;
            case 's': dir = DOWN; break;
            case 'x': gameOver = true; break;  // Exit
        }
    }
}

// 5. Game logic
void Logic() {
    // Tail movement
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;

    tailX[0] = headX;
    tailY[0] = headY;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Move head
    switch (dir) {
        case LEFT:  headX--; break;
        case RIGHT: headX++; break;
        case UP:    headY--; break;
        case DOWN:  headY++; break;
        default: break;
    }

    // Check collisions
    if (headX <= 0 || headX >= width || headY < 0 || headY >= height)
        gameOver = true;

    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == headX && tailY[i] == headY)
            gameOver = true;
    }

    // Eat fruit
    if (headX == fruitX && headY == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

// 6. Welcome screen
void Welcome() {
    cout << "\n=========== WELCOME TO TERMINAL SNAKE GAME ===========\n";
    cout << "Use W A S D to move the snake\n";
    cout << "Eat the * to grow longer\n";
    cout << "Avoid walls and your own tail!\n";
    cout << "\nPress 'P' to start the game...\n";

    char c;
    do {
        cin >> c;
    } while (c != 'p' && c != 'P');
}

// 7. End screen
void GameOverScreen() {
    clear();
    cout << "\n=========== GAME OVER ===========\n";
    cout << "        Your Final Score: " << score << "\n";
    cout << "=================================\n";
    cout << "        Thanks for playing!\n\n";
    sleep(2);  // Pause so user sees the message
}

// 8. Main game loop
void Play() {
    initscr();      // Start ncurses mode
    noecho();       // Do not display typed characters
    curs_set(0);    // Hide cursor

    while (!gameOver) {
        Draw();
        Input();
        Logic();
        refresh();   // Refresh screen
    }

    endwin();  // End ncurses mode
}

// 9. Main function
int main() {
    Welcome();
    Setup();
    Play();
    GameOverScreen();
    return 0;
}

