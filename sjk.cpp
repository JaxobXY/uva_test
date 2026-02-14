#include <iostream>
#include <vector>
#include <sys/ioctl.h> 
#include <unistd.h>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

int getTerminalWidth() {
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) return 80;
    return w.ws_col;
}

void showLongGuide() {
    cout << "\n--- ULTIMATE ELEMENTARY CA GUIDE (Rules 0-255) ---\n";
    cout << "[Class 1: Uniformity] (Converge to all 0 or 1)\n";
    cout << "Rules: 0, 8, 32, 40, 128, 136, 160, 168, 232 (Majority), 255 (Solid)\n\n";
    
    cout << "[Class 2: Oscillation/Repetition] (Stable or repeating structures)\n";
    cout << "Rules: 1, 2, 3, 4 (Shifted), 7, 10, 15 (Stripes), 19, 24, 34, 38, 42, 46, \n";
    cout << "       50, 51 (Inverse), 76, 108, 123, 127, 190, 204 (Identical), 218, 250\n\n";
    
    cout << "[Class 3: Randomness/Chaos] (Aperiodic and seemingly random)\n";
    cout << "Rules: 18, 22, 30 (Chaos), 45, 60, 90 (Fractal), 105 (Mesh), 122, 126, \n";
    cout << "       129, 146, 150 (Complex Fractal), 161, 182\n\n";
    
    cout << "[Class 4: Complexity] (Turing Complete / Interacting structures)\n";
    cout << "Rules: 54, 110 (Universal), 124 (Mirror 110), 137, 193\n\n";
    
    cout << "[Special Logic & Textures]\n";
    cout << "Rule 184: Traffic flow logic - 1s are cars, 0s are gaps.\n";
    cout << "Rule 73:  'Castle Walls' - architectural blocks and lines.\n";
    cout << "Rule 62:  Sierpinski-like with complex interior structures.\n";
    cout << "Rule 101: Moving 'gliders' and persistent debris.\n";
    cout << "--------------------------------------------------\n";
}

void runAutomaton(int ruleNumber, int width, int rows, bool randomStart) {
    vector<int> current(width, 0);
    vector<int> next(width, 0);
    
    if (randomStart) {
        for (int j = 0; j < width; j++) current[j] = rand() % 2;
    } else {
        current[width / 2] = 1; // Single seed
    }

    cout << "\n--- Running Rule " << ruleNumber << " ---\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < width; j++) cout << (current[j] == 1 ? "█" : " ");
        cout << endl;

        // wrap-around boundaries
        for (int j = 0; j < width; j++) {
            int left  = current[(j - 1 + width) % width];
            int self  = current[j];
            int right = current[(j + 1) % width];
            int pattern = (left << 2) | (self << 1) | right;
            next[j] = (ruleNumber >> pattern) & 1;
        }

        current = next;
        usleep(25000); 
    }
}

int main() {
    srand(time(0)); // seed once

    int width = getTerminalWidth();
    int choice;

    while (true) {
        cout << "\n1. Rule 30 | 2. Rule 90 | 3. Rule 110 | 4. Rule 184 | 5. Custom | 6. Full Guide | 0. Exit\n";
        cout << "Selection: ";
        if (!(cin >> choice)) { cin.clear(); cin.ignore(1000, '\n'); continue; }
        if (choice == 0) break;
        if (choice == 6) { showLongGuide(); continue; }

        int rule = 0;
        if (choice == 5) { cout << "Rule (0-255): "; cin >> rule; }
        else { int p[] = {30, 90, 110, 184}; rule = p[choice - 1]; }

        int length, startMode;
        cout << "Length (rows): "; cin >> length;
        cout << "Start Mode (1: Single Seed, 2: Random Row): "; cin >> startMode;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        runAutomaton(rule, width, length, (startMode == 2));
    }
    return 0;
}
