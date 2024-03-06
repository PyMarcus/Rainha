#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define LINE 4
#define COLUMN 4
#define bar "\n"

// create a random number [0...3] => (4 numbers)
int randInt(){
    sleep(0.04);
    return rand() % 4;
}

// add ij into matrix
int* addPosXandY(){
    int* xy = (int*)malloc(2 * sizeof(int));
    if(xy == NULL){
        printf("Fail to memory allocation");
        exit(EXIT_FAILURE);
    }
    xy[0] = randInt();
    xy[1] = randInt();
    return xy;
}

int** createMatrix(){
    int** matrix = (int**)malloc(LINE * sizeof(int *));
    for(int i = 0; i < LINE; i++){
        matrix[i] = (int *)malloc(COLUMN * sizeof(int));
        for(int j = 0; j < COLUMN; j++){
            matrix[i][j] = 0;
        }
    }    
    return matrix;
}

void show(int** matrix){
    for(int i = 0; i < LINE; i++){
        for(int j = 0; j < COLUMN; j++){
            printf("%d ", matrix[i][j]);
        }printf(bar);
    }
}

int checkLine(int* line){
    for(int i = 0; i < COLUMN; i++){
        if(line[i] == 1) return 0;
    }
    return 1;
}

int checkColumn(int* column){
    for(int i = 0; i < LINE; i++){
        if(column[i] == 1) return 0;
    }
    return 1;
}

int checkDiagonal(int* diagonal, int size){
    for(int i = 0; i < size; i++){
        if(diagonal[i] == 1) return 0;
    }
    return 1;
}

int main(){
    srand(time(NULL));
    int** matrix = createMatrix();
    printf("Normal matrix: %s", bar);
    show(matrix);
    return 0;
}

