#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

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

int main(){
    srand(time(NULL));
    printf("%d %d", *addPosXandY(), *addPosXandY());
    return 0;
}

