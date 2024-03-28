#include <stdio.h>
#include <stdlib.h>


#define LINE 8
#define COLUMN 4

// tabuleiro de exemplo.
int matriz[LINE][COLUMN] = {
        {0, 0, 0, 0},
        {1, 0, 1, 0},
        {0, 8, 0, 0},
        {0, 0, 0, 0},
        {1, 0, 0, 2},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
};


// verifica se esta no ambito do tabuleiro ainda
int isValid(int i, int j){
    if(matriz[i][j] == 1 || i < 0 || j < 0 || i > LINE || j > COLUMN){
        return 0;
    }
    return 1;
}

// para retornar a posicaox e y
typedef struct {
    int x;
    int y;
} Position;


// obtem a posicao atual
Position* currentPosition(){
    Position* position = malloc(sizeof(Position));
    for(int i = 0; i < LINE; i++){
        for(int j = 0; j < COLUMN; j++){
            if(matriz[i][j] == 8){
                position->x = i;
                position->y = j;
                break;
            }
        }
    }
    return position;
}

// apenas exibe a matriz
void printM(){
    for(int i = 0; i < LINE; i++){
        for(int j = 0; j < COLUMN; j++){
            printf("%d", matriz[i][j]);
        }
        printf("\n");
    }
}

// move o personagem com base no codigo passado
void moveCharacter(int code){
    Position* current = currentPosition(); 
    int i = current->x;
    int j = current->y;
    int oldx = current->x;
    int oldy = current->y;
    switch(code){
        case 1:
            i --;
            j --;
            break;
        case 2:
            i--;
            break;
        case 3:
            i--;
            j++;
            break;
        case 4:
            j--;
            break;
        case 5:
            j++;
            break;
        case 6:
            i++;
            j--;
            break;
        case 7:
            i++;
            break;
        case 8:
            i++;
            j++;
            break;
    }
        //printf("DPS i: %d j: %d", i, j);

    if(isValid(i, j)){
        //printf("AQ %d %d ", i, j);
        if(matriz[i][j] == 2){
            printf("Voce venceu!!!\n");
            exit(0);
        }
        matriz[i][j] = 8;
        matriz[oldx][oldy] = 0;
    }else{
        printf("Posicao invalida\n");
    }

    printM();
}


int main(){
    // o personagem é o valor 8
    // os obstaculos é o valor 1
    // o objetivo é o 2
     
    int num;
    while(1){
        printf("Informe um numero de 1 a 8: ");
        scanf("%d", &num);
        moveCharacter(num);
    }

     return 0;
}