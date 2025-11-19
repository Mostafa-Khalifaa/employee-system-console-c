#ifndef input
#define input

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_HOME 71

// Initialize input system (for Linux terminal settings)
void initInput(void);

// Restore input settings (for Linux)
void restoreInput(void);

// Get a key press (cross-platform)
int getKeyPress(void);

#endif // input
