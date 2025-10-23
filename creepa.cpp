#include <iostream>
#include <cmath>
#include <unistd.h>  // for usleep

using namespace std;

int main() {
    cout << "\033[2J";

    while (true) {
        // Move cursor to top-left without clearing the screen
        cout << "\033[H";

            cout<<"creepa "<<endl;
            cout << "██  ██"<< endl <<"  ██  "<< endl<<" ████ "<<endl<<" █  █ ";


        usleep(20000);      // Sleep ~20ms (~50 FPS), adjust for smoothness/speed
    }

    return 0;
}