#include <stdio.h>

#include "test.h"

int main(void){
    int x = twice(8);
    printf("The value is %i\n", x);
}

int twice(int x){
    return 2*x;
}
