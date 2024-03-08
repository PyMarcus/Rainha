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

int checkLine(int** matrix, int line_pos){
    for(int k = 0; k < COLUMN; k++){
        if(matrix[line_pos][k] == 8){
            return 0;
        }
    }
    for(int k = 0; k < COLUMN; k++){
        matrix[line_pos][k] = 1;
    }
    return 1;
}

int checkColumn(int** matrix, int column_pos){
    for(int k = 0; k < LINE; k++){
        if(matrix[k][column_pos] == 8){
            return 0;
        }
    }
    for(int k = 0; k < LINE; k++){
        matrix[k][column_pos] = 1;
    }
    return 1;
}

int main(){
    srand(time(NULL));
    int** matrix = createMatrix();
    printf("Normal matrix: %s", bar);
    show(matrix);
    for(int t = 0; t < LINE * COLUMN; t++){
        int* vet = addPosXandY();
        int checkA = 0;
        int checkB = 0;
        int checkC = 0;
        int checkD = 0;

        int x = vet[0], y = vet[1], m = x, n = y, o = x, p = y, e = x, r = y;

        int original_x = x;
        int original_y = y;
        // fill up ++ diagonal and -- diagonal
        for(int g = 0; g < LINE; g++){
            for(int k = 0; k < COLUMN; k++){
                if(g == (x + 1) && k == (y + 1)  && matrix[g][k] != 8){
                    if(matrix[g][k] == 8){
                            checkC = 0;
                            break;
                        }else{
                            checkC = 1;
                        }
                    x++; y++;
                   
                }else{
                    if(g == (m - 1) && k == (n - 1) && m > 0 && n > 0 && matrix[g][k] != 8){
                        if(matrix[g][k] == 8){
                            checkD = 0;
                            break;
                        }else{
                            checkD = 1;
                        }
                        m--; n--;
                        
                    }
                }
            }
        }
        // fill up +- diagonal and -+ diagonal
        for(int g = 0; g < LINE; g++){
            for(int k = 0; k < COLUMN; k++){
                if(g == (o + 1) && k == (p - 1) && p > 0 && o < LINE && matrix[g][k] != 8){
                    if(matrix[g][k] == 8){
                        checkA = 0;
                        break;
                    }else{
                        checkA = 1;
                    }
                    o++; p--;
                    
                }else{
                    if(g == (e - 1) && k == (r + 1) && e > 0 && r < LINE  && matrix[g][k] != 8){
                        if(matrix[g][k] == 8){
                            checkB = 0;
                            break;
                        }else{
                            checkB = 1;
                        }
                        e--; r++;
                        
                    }
                }
            }
        } 
        if(checkLine(matrix, original_x) && checkA && checkB && checkC && checkD && checkColumn(matrix, original_y)){
            matrix[original_x][original_y] = 8;
        }
        checkA = 0;
        checkB = 0;
        checkC = 0;
        checkD = 0;

    }
    printf(bar);
    show(matrix);
    return 0;
}

