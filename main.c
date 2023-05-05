#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int concat(int num ){

    static int aux = 0;

    if(num!=-1){
        aux =(aux * 10) + num  ;
    }else{
        aux=0;
    }
    return aux;
}


int main(){


    char numbers[15][7];
    int num;

    printf("\nLongitud del array: %llu\n",sizeof(numbers));

    int i = sizeof(numbers)-1;
    char action;



    for(int x=0;x<sizeof(numbers);x++){
        printf("Enter %d Position Number\n",  x+1 );
        scanf(" %c", &numbers[x]);
    }


    for(int x=0;x<sizeof(numbers);x++){
        num = concat(numbers[x]-48);
    }



//    printf("EL numero es: %d\n",num);



//    concat(-1);
//
//
//    for(int x=0;x<sizeof(numbers);x++){
//        printf("Enter %d Position Number\n",  x+1 );
//        scanf(" %c", &numbers[x]);
//    }
//
//
//    for(int x=0;x<sizeof(numbers);x++){
//        num = concat(numbers[x]-48);
//    }

    printf("EL numero es: %d\n",num);


    switch (num) {
        case 1:
            printf("EL numero es: el uno frrr\n");
            break;

        default:
            printf("No exite esa opcion");


    }

}
