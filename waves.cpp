#include <iostream>
#include <cmath>
#include <unistd.h>  // for usleep

using namespace std;

int main() {
    const int width = 80;           // Adjust for terminal width
    const int height = 24;          // Adjust for terminal height
    const double frequency = 0.15;  // Frequency of the sine wave
    const double amplitude = 7.0;   // Wave amplitude
    double phase = 0.0;

    // Clear screen once at start
    cout << "\033[2J";

    while (true) {
        // Move cursor to top-left without clearing the screen
        cout << "\033[H";

        // Loop over each row and column
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                double waveY = amplitude * sin(frequency * x + phase) + amplitude;
                double diff = y - waveY;

                // Select shading block based on vertical distance to waveY
                if (diff > -0.25 && diff <= 0.25)
                    cout << "█";   // Peak
                else if (diff > -0.75 && diff <= -0.25)
                    cout << "▓";   // Dark shade above peak
                else if (diff > -1.25 && diff <= -0.75)
                    cout << "▒";   // Medium shade
                else if (diff > -1.75 && diff <= -1.25)
                    cout << "░";   // Light shade above peak
                else if (diff > 0.25 && diff <= 0.75)
                    cout << "▓";   // Dark shade below peak
                else if (diff > 0.75 && diff <= 1.25)
                    cout << "▒";   // Medium shade below peak
                else if (diff > 1.25 && diff <= 1.75)
                    cout << "░";   // Light shade below peak
                else
                    cout << " ";   // Empty space
            }
            cout << "\n";
        }

        phase += 0.05;      // Advance phase slowly for smooth wave motion
        usleep(20000);      // Sleep ~20ms (~50 FPS), adjust for smoothness/speed
    }

    return 0;
}