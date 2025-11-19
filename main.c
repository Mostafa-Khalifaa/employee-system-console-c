#include <stdio.h>
#include <stdlib.h>
#include "screen.h"
#include "input.h"
#include "menu.h"

int main() {
    // Initialize input system (important for Linux)
    initInput();

    // Run the main menu
    runMainMenu();

    // Restore input settings before exit
    restoreInput();



    ////////////////////////////////////////////////////////////////////////////////

        int a = 5, b = 10;
    int a2 =10 , b2 = 20;
    int a3 = 30 , b3 = 40;

    printf("Before swap: a = %d, b = %d\n", a, b);
    swap(&a, &b);

    printf("After swap1(add and sub): a = %d, b = %d\n", a, b);

//////////////////////////////////////////////////////////////////////
printf("Before swap: a = %d, b = %d\n", a2, b2);
    swap2(&a2, &b2);

    printf("After swap2(multi and div): a = %d, b = %d\n", a2, b2);
    /////////////////////////////////////////////////////
printf("Before swap: a = %d, b = %d\n", a3, b3);
    swap3(&a3, &b3);

    printf("After swap3(xor): a = %d, b = %d\n", a3, b3);
    ////////////////////////////////////////////////////

        int arr[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    TwoDarray(arr, 2);

    return 0;



}
