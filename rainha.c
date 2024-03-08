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
 
    return 1;
}

int checkColumn(int** matrix, int column_pos){
    for(int k = 0; k < LINE; k++){
        if(matrix[k][column_pos] == 8){
            return 0;
        }
    }
   
    return 1;
}

int main(){
    srand(time(NULL));
    int** matrix = createMatrix();
    printf("Normal matrix: %s", bar);
    show(matrix);
    for(int t = 0; t < LINE * COLUMN; t++){
        int ll, uu;
        printf("Enter: i j or press -1 -1 to exit!%s", bar);
        scanf("%d %d", &ll, &uu);
        if(ll == -1 && uu == -1){
            break;
        }
        int vet[] = {ll, uu};
        int checkA = 1;
        int checkB = 1;
        int checkC = 1;
        int checkD = 1;

        int x = vet[0], y = vet[1];

        // fill up ++ diagonal and -- diagonal
        for(int i = x; i >= 0; i--){//10
            for(int j = y; j >= 0; j--){
                int __default = x - y;
                if(matrix[i][j] == 8 && (i - j == __default)){
                    checkA = 0;
                    break;
                }
            }
        }

        for(int i = x; i < LINE; i++){
            for(int j = y; j < COLUMN; j++){
                int __default = x - y;
                if(matrix[i][j] == 8 && (i - j == __default)){
                    checkB = 0;
                    break;
                }
            }
            
        }

        for(int i = x; i >= 0; i--){
            for(int j = y; j < COLUMN; j++){
                int __default = x - y;
                if(matrix[i][j] == 8 && (i - j == __default)){
                    checkC = 0;
                    break;
                }
            }
        }

        for(int i = x; i < LINE; i++){
            for(int j = y; j >= 0; j--){
                int __default = x - y;
                if(matrix[i][j] == 8 && (i - j == __default)){
                    checkD = 0;
                    break;
                }
            }
        }

        // fill up +- diagonal and -+ diagonal
        if(checkLine(matrix, x) && checkA && checkB && checkC && checkD && checkColumn(matrix, y)){
            matrix[x][y] = 8;
        }else{
            printf("checkA: %d - checkB: %d - checkC: %d - checkD: %d",checkA, checkB, checkC, checkD);
            printf("%s Invalid position! %s", bar, bar);
        }
        checkA = 1;
        checkB = 1;
        checkC = 1;
        checkD = 1;

    }
    printf(bar);
    show(matrix);
    return 0;
}

