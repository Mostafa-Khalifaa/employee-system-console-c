#include "input.h"
#include "platform.h"
#include <stdio.h>

#ifdef _WIN32
//فيها _getch() لقراءة زر واحد بدون انتظار Enter.
    #include <conio.h>
#endif

#ifndef _WIN32
    #include <termios.h>
    #include <unistd.h>
    static struct termios oldTermios;
    static struct termios newTermios;
#endif

void initInput(void) {
#ifndef _WIN32
    // Get current terminal settings
    tcgetattr(STDIN_FILENO, &oldTermios);

    // Copy to new settings
    newTermios = oldTermios;

    // Disable canonical mode and echo
    newTermios.c_lflag &= ~(ICANON | ECHO);

    // Set new settings
    tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);
#endif
}

void restoreInput(void) {
#ifndef _WIN32
    // Restore original terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
#endif
}

int getKeyPress(void) {
#ifdef _WIN32
    int ch = _getch();

    // Handle special keys (arrow keys, etc.)
    if (ch == 0 || ch == 224) {
        ch = _getch();
        // Swap arrow keys: RIGHT->DOWN, LEFT->UP
        if (ch == KEY_RIGHT) return KEY_DOWN;
        if (ch == KEY_LEFT) return KEY_UP;
        return ch;
    }

    return ch;
#else
    int ch = getchar();

    // Handle escape sequences for arrow keys
    if (ch == 27) { //'\n'
        int next = getchar();
        if (next == '[') {
            int arrow = getchar();
            switch (arrow) {
                case 'A': return KEY_UP;      // Up arrow
                case 'B': return KEY_DOWN;    // Down arrow
                case 'C': return KEY_DOWN;    // Right arrow -> DOWN
                case 'D': return KEY_UP;      // Left arrow -> UP
                case 'H': return KEY_HOME;
            }
        } else {
            // Just ESC key
            return KEY_ESC;
        }
    }

    // Enter key
    if (ch == 10) return KEY_ENTER;

    return ch;
#endif
}
