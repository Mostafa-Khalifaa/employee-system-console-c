#include "menu.h"
#include "screen.h"
#include "draw.h"
#include "input.h"
#include "cursor.h"
#include "employee.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MENU_START_X 30
#define MENU_START_Y 8

static const char* menuItems[MAX_MENU_ITEMS] = {
    "New",
    "Display",
    "Exit"
};

void initMenu(void) {
    clearScreen();
    initEmployeeSystem(); // Initialize employee system
}

// Draws one button in the menu (with border and centered text)
void drawMenuButton(int x, int y, const char* text, int isSelected) {
    Color borderColor = isSelected ? BLUE : WHITE;
    Color textColor = WHITE;

    // Draw top border
    moveCursor(x, y);
    setColor(borderColor);
    printf("+");
    for (int i = 0; i < MENU_ITEM_WIDTH - 2; i++) {
        printf("-");
    }
    printf("+");
    resetColor();

    // Draw middle with text
    moveCursor(x, y + 1);
    setColor(borderColor);
    printf("| ");

    // Center the text
    setColor(textColor);
    int padding = (MENU_ITEM_WIDTH - 4 - strlen(text)) / 2;
    for (int i = 0; i < padding; i++) printf(" ");
    printf("%s", text);
    for (int i = 0; i < MENU_ITEM_WIDTH - 4 - strlen(text) - padding; i++) printf(" ");

    setColor(borderColor);
    printf(" |");
    resetColor();

    // Draw bottom border
    moveCursor(x, y + 2);
    setColor(borderColor);
    printf("+");
    for (int i = 0; i < MENU_ITEM_WIDTH - 2; i++) {
        printf("-");
    }
    printf("+");
    resetColor();
}

void drawMenu(int selectedItem) {
    clearScreen();

    // Draw title
    drawText(MENU_START_X, 2, "=== Main Menu ===", CYAN);

    // Draw menu items
    int currentY = MENU_START_Y;
    for (int i = 0; i < MAX_MENU_ITEMS; i++) {
        drawMenuButton(MENU_START_X, currentY, menuItems[i], i == selectedItem);
        currentY += MENU_ITEM_HEIGHT + 2;
    }

    // Draw instructions
    drawText(10, 22, "Use UP/DOWN arrows to navigate, Enter to select, ESC/Home to go back", YELLOW);
}

// Handles keyboard navigation
MenuItem handleMenuInput(void) {
    int selectedItem = 0;
    drawMenu(selectedItem);

    while (1) {
        int key = getKeyPress();

        if (key == KEY_UP) {
            selectedItem--;
            if (selectedItem < 0) selectedItem = MAX_MENU_ITEMS - 1;
            drawMenu(selectedItem);
        }
        else if (key == KEY_DOWN) {
            selectedItem++;
            if (selectedItem >= MAX_MENU_ITEMS) selectedItem = 0;
            drawMenu(selectedItem);
        }
        else if (key == KEY_ENTER) {
            return (MenuItem)selectedItem;
        }
        else if (key == KEY_ESC || key == KEY_HOME) {
            return MENU_EXIT;
        }
    }
}

// Function to read a line of input with visible characters
void readLine(char* buffer, int maxLength) {
    int i = 0;

    // Temporarily restore normal input mode so text is visible
    restoreInput();

    // Read input
    fgets(buffer, maxLength, stdin);

    // Remove newline character
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    // Re-enable special input mode for menu navigation
    initInput();
}

// Handle adding new employees
void handleNewOption(void) {
    char choice;

    do {
        char name[50];
        char position[50];
        char salaryStr[20];
        float salary;

        clearScreen();
        drawText(5, 2, "=== Add New Employee ===", CYAN);

        // Get employee name
        drawText(5, 4, "Enter employee name: ", GREEN);
        moveCursor(27, 4);
        setColor(WHITE);
        readLine(name, sizeof(name));
        resetColor();

        // Get employee position
        drawText(5, 6, "Enter job position: ", GREEN);
        moveCursor(26, 6);
        setColor(WHITE);
        readLine(position, sizeof(position));
        resetColor();

        // Get employee salary
        drawText(5, 8, "Enter salary: ", GREEN);
        moveCursor(20, 8);
        setColor(WHITE);
        readLine(salaryStr, sizeof(salaryStr));
        salary = atof(salaryStr); // Convert string to float
        resetColor();

        // Try to add the employee
        if (addEmployee(name, position, salary)) {
            drawText(5, 10, "Employee added successfully!", GREEN);
        } else {
            drawText(5, 10, "Error: Cannot add more employees (limit reached)!", RED);
        }

        // Ask if user wants to add another employee
        drawText(5, 12, "Do you want to add another employee? (Y/N): ", YELLOW);
        moveCursor(51, 12);
        setColor(WHITE);

        // Wait for Y or N key
        while (1) {
            int key = getKeyPress();
            if (key == 'y' || key == 'Y') {
                choice = 'Y';
                break;
            } else if (key == 'n' || key == 'N') {
                choice = 'N';
                break;
            }
        }
        resetColor();

    } while (choice == 'Y');
}

// Handle displaying all employees
void handleDisplayOption(void) {
    clearScreen();
    drawText(5, 2, "=== Employee List ===", CYAN);

    int count = getEmployeeCount();

    if (count == 0) {
        drawText(5, 4, "No employees found!", YELLOW);
        drawText(5, 6, "Please add employees first.", WHITE);
    } else {
        // Display total count
        char countMsg[50];
        sprintf(countMsg, "Total Employees: %d", count);
        drawText(5, 4, countMsg, GREEN);

        // Display table header
        drawText(5, 6, "ID   Name                Position            Salary", MAGENTA);
        drawText(5, 7, "---------------------------------------------------", MAGENTA);

        // Display each employee
        int y = 8;
        for (int i = 0; i < count; i++) {
            Employee* emp = getEmployee(i);
            if (emp != NULL) {
                char line[100];
                sprintf(line, "%-4d %-20s %-20s $%.2f",
                        emp->id, emp->name, emp->position, emp->salary);
                drawText(5, y, line, WHITE);
                y++;

                // Prevent going off screen
                if (y > 20) {
                    drawText(5, 21, "... (More employees not shown)", YELLOW);
                    break;
                }
            }
        }
    }

    drawText(5, 23, "Press Enter or ESC to return to menu...", GREEN);
    resetColor();

    // Wait for key press
    while (1) {
        int key = getKeyPress();
        if (key == KEY_ENTER || key == KEY_ESC || key == KEY_HOME) {
            break;
        }
    }
}

// Run the main menu loop
void runMainMenu(void) {
    while (1) {
        MenuItem selected = handleMenuInput();

        switch (selected) {
            case MENU_NEW:
                handleNewOption();
                break;

            case MENU_DISPLAY:
                handleDisplayOption();
                break;

            case MENU_EXIT:
                clearScreen();
                drawText(30, 10, "Goodbye!", GREEN);
                delaySeconds(1);
                clearScreen();
                return;
        }
    }
}
