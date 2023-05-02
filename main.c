#include <stdio.h>
#include <string.h>

int concat(int num){
    static int aux = 0;
    aux =(aux * 10) + num  ;
    return aux;
}


int main(){

    char numbers[2];
    int num;

    printf("\nLongitud del array: %llu\n",sizeof(numbers));

    for(int x=0;x<sizeof(numbers);x++){
        printf("Enter %d  Number\n",  x+1 );
        scanf(" %c", &numbers[x]);
    }

    for(int x=0;x<sizeof(numbers);x++){
        num = concat(numbers[x]-48);
    }

    printf("EL numero es: %d\n",num);

}
