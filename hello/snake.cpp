#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

using namespace std;

// Color codes for cross-platform terminal colors
#ifdef _WIN32
#define COLOR_RED 12
#define COLOR_GREEN 10
#define COLOR_YELLOW 14
#define COLOR_BLUE 9
#define COLOR_MAGENTA 13
#define COLOR_CYAN 11
#define COLOR_WHITE 15
#define COLOR_GRAY 8
#define COLOR_RESET 7

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
#else
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN "\033[36m"
#define COLOR_WHITE "\033[37m"
#define COLOR_GRAY "\033[90m"
#define COLOR_RESET "\033[0m"

void setColor(const char* color) {
    cout << color;
}
#endif

bool gameover;
const int width = 60;  // Much wider
const int height = 30; // Much taller
int x, y, fruitX, fruitY, score;
vector<int> tailX, tailY; // Using vector for dynamic sizing
int nTail;

enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecton dir;

// Cross-platform keyboard input
int kbhit() {
#ifdef _WIN32
    return _kbhit();
#else
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
#endif
}

int getch() {
#ifdef _WIN32
    return _getch();
#else
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#endif
}

void Setup() {
    gameover = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 0;
    tailX.clear();
    tailY.clear();
    
    // Initialize with some tail segments for better visibility
    tailX.resize(100);
    tailY.resize(100);
}

void Draw() {
    system("clear"); // Use "cls" on Windows
    
    // Draw top border
#ifdef _WIN32
    setColor(COLOR_BLUE);
#else
    setColor(COLOR_BLUE);
#endif
    for (int i = 0; i < width + 2; i++)
        cout << "█";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Left border
            if (j == 0) {
#ifdef _WIN32
                setColor(COLOR_BLUE);
#else
                setColor(COLOR_BLUE);
#endif
                cout << "█";
            }

            // Snake head
            if (i == y && j == x) {
#ifdef _WIN32
                setColor(COLOR_GREEN);
#else
                setColor(COLOR_GREEN);
#endif
                cout << "■"; // Solid block for head
            }
            // Fruit
            else if (i == fruitY && j == fruitX) {
#ifdef _WIN32
                setColor(COLOR_RED);
#else
                setColor(COLOR_RED);
#endif
                cout << "●"; // Circle for fruit
            }
            // Snake body
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
#ifdef _WIN32
                        setColor(COLOR_YELLOW);
#else
                        setColor(COLOR_YELLOW);
#endif
                        cout << "□"; // Different block for body
                        print = true;
                    }
                }
                if (!print) {
                    // Checkerboard pattern - alternate between dark and light squares
                    bool isDarkSquare = ((i + j) % 2 == 0);
                    if (isDarkSquare) {
#ifdef _WIN32
                        setColor(COLOR_GRAY);
#else
                        setColor(COLOR_GRAY);
#endif
                        cout << "░"; // Light pattern for dark squares
                    } else {
#ifdef _WIN32
                        setColor(COLOR_WHITE);
#else
                        setColor(COLOR_WHITE);
#endif
                        cout << "▒"; // Darker pattern for light squares
                    }
                }
            }

            // Right border
            if (j == width - 1) {
#ifdef _WIN32
                setColor(COLOR_BLUE);
#else
                setColor(COLOR_BLUE);
#endif
                cout << "█";
            }
        }
        cout << endl;
    }

    // Draw bottom border
#ifdef _WIN32
    setColor(COLOR_BLUE);
#else
    setColor(COLOR_BLUE);
#endif
    for (int i = 0; i < width + 2; i++)
        cout << "█";
    cout << endl;

    // Score display
#ifdef _WIN32
    setColor(COLOR_CYAN);
#else
    setColor(COLOR_CYAN);
#endif
    cout << "Score: " << score << "   ";
    cout << "Length: " << nTail + 1 << "   ";
    
    // Direction indicator
    cout << "Direction: ";
    switch (dir) {
        case LEFT: cout << "LEFT"; break;
        case RIGHT: cout << "RIGHT"; break;
        case UP: cout << "UP"; break;
        case DOWN: cout << "DOWN"; break;
        default: cout << "STOP"; break;
    }
    cout << endl;
    
    // Instructions
#ifdef _WIN32
    setColor(COLOR_MAGENTA);
#else
    setColor(COLOR_MAGENTA);
#endif
    cout << "Controls: W=Up, A=Left, S=Down, D=Right, X=Exit" << endl;

    // Reset color
#ifdef _WIN32
    setColor(COLOR_RESET);
#else
    setColor(COLOR_RESET);
#endif
}

void Input() {
    if (kbhit()) {
        char key = getch();
        switch (key) {
            case 'a':
            case 'A':
                if (dir != RIGHT) dir = LEFT;
                break;
            case 'd':
            case 'D':
                if (dir != LEFT) dir = RIGHT;
                break;
            case 'w':
            case 'W':
                if (dir != DOWN) dir = UP;
                break;
            case 's':
            case 'S':
                if (dir != UP) dir = DOWN;
                break;
            case 'x':
            case 'X':
                gameover = true;
                break;
        }
    }
}

void PlaceFruit() {
    bool onSnake;
    do {
        onSnake = false;
        fruitX = rand() % width;
        fruitY = rand() % height;
        
        // Check if fruit overlaps with snake head
        if (fruitX == x && fruitY == y) onSnake = true;
        
        // Check if fruit overlaps with snake body
        for (int i = 0; i < nTail && !onSnake; i++) {
            if (fruitX == tailX[i] && fruitY == tailY[i]) onSnake = true;
        }
    } while (onSnake);
}

void Algorithm() {
    // Move tail segments
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

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
        case LEFT:  x--; break;
        case RIGHT: x++; break;
        case UP:    y--; break;
        case DOWN:  y++; break;
        default: break;
    }

    // Wall collision (wrap around)
    if (x >= width) x = 0;
    else if (x < 0) x = width - 1;
    if (y >= height) y = 0;
    else if (y < 0) y = height - 1;

    // Self collision check
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameover = true;
        }
    }

    // Fruit collection
    if (x == fruitX && y == fruitY) {
        score += 10;
        nTail++;
        // Ensure vectors are large enough
        if (nTail >= tailX.size()) {
            tailX.resize(tailX.size() + 50);
            tailY.resize(tailY.size() + 50);
        }
        PlaceFruit();
    }
}

int main() {
    srand(time(0)); // Seed random number generator
    Setup();
    
    cout << "Starting Snake Game..." << endl;
    cout << "Arena Size: " << width << " x " << height << endl;
#ifdef _WIN32
    Sleep(2000);
#else
    usleep(2000000);
#endif
    
    while (!gameover) {
        Draw();
        Input();
        Algorithm();
        
        // Game speed (adjust as needed)
#ifdef _WIN32
        Sleep(50); // Faster game for larger arena
#else
        usleep(50000); // 50ms
#endif
    }
    
    // Game over screen
    system("clear"); // Use "cls" on Windows
#ifdef _WIN32
    setColor(COLOR_RED);
#else
    setColor(COLOR_RED);
#endif
    cout << "██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗ " << endl;
    cout << "██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗" << endl;
    cout << "██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝" << endl;
    cout << "██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗" << endl;
    cout << "╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║" << endl;
    cout << " ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝" << endl;
    cout << endl;d
#ifdef _WIN32
    setColor(COLOR_CYAN);
#else
    setColor(COLOR_CYAN);
#endif
    cout << "Final Score: " << score << endl;
    cout << "Snake Length: " << nTail + 1 << endl;
#ifdef _WIN32
    setColor(COLOR_RESET);
#else
    setColor(COLOR_RESET);
#endif
    
    return 0;
}