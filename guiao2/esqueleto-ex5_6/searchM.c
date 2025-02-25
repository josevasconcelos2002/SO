#include "matrix.h"
#define VALUE 3

int main(int argc, char *argv[]) {

    // generate random matrix
    int **matrix = createMatrix();

    // print matrix
    printMatrix(matrix);

    int exists = valueExists(matrix, VALUE);
    if(exists){
        printf("Value %d exists!\n", VALUE);
        printf("\nLINES WITH %d\n", VALUE);
        linesWithValue(matrix, VALUE);
    }
    else
        printf("Value %d does not exist!\n", VALUE);
    
    
    
    // free matrix
    for (int i = 0; i < ROWS; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}