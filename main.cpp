#include <iostream>
#include <termios.h>
#include <unistd.h>

using namespace std;

int main() {
    termios oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);


    char input[5];

    read(STDIN_FILENO, input, 3);

    for (const char &c : input) {
        cout << "You pressed: " << c << endl;
    }

    // read(STDIN_FILENO, next, 2);

    // if (*input == '\x1b') {
    //     cout << "Arrow key?" << '\\\\' << input << endl;
    //     // cout << "Next: " << next[0] << next[1] << endl;
    // }


    // tcgetattr(STDIN_FILENO, &oldt);
    // newt = oldt;
    // newt.c_lflag &= ~(ICANON | ECHO);
    // tcsetattr(STDIN_FILENO, TCSADRAIN, &newt);

    // char button1;
    // read(STDIN_FILENO, &button1, 2);
    // write(STDIN_FILENO, &button1, 1);
    // cout << "\n" << endl;

    return 0;

}

