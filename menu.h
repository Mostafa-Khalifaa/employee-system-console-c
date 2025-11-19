#ifndef menu
#define menu

#include "color.h"

#define MAX_MENU_ITEMS 3
#define MENU_ITEM_WIDTH 20
#define MENU_ITEM_HEIGHT 3

typedef enum {
    MENU_NEW,
    MENU_DISPLAY,
    MENU_EXIT
} MenuItem;

// Initialize menu system
void initMenu(void);

// Draw the complete menu
void drawMenu(int selectedItem);

// Draw a single menu button
void drawMenuButton(int x, int y, const char* text, int isSelected);

// Handle menu navigation and selection
MenuItem handleMenuInput(void);

// Run the main menu loop
void runMainMenu(void);

#endif // menu
