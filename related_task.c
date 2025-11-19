
void swap(int *a, int *b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

void swap2(int *a , int *b){
*a = *a * *b;
*b = *a / *b;
*a = *a / *b;

}

void swap3(int *a , int *b){

*a = *a ^ *b;
*b = *a ^ *b;
*a = *a ^ *b;

}

void TwoDarray(int arr[][3], int rows) {
    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < 3; j++) {
            arr[i][j] = arr[i][j] * 2;
        }
    }


    printf("modified array:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < 3; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}
