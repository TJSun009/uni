#include "ciphers.h"

int main()
{
    /*int input;
    printf("Enter a decimal number: ");
    scanf("%d", &input);
    char * dec = decToBin(input);

    for(int i = 0; i < sizeof(dec)/sizeof(char); i++){
    printf("%c", dec[i]);
    }

    char * string = malloc(100 * sizeof(char));
    printf("\n\nEnter a String: ");
    scanf("\n%s", string);
    int * p = strToBin(string);

    for(int i = 0; i < sizeof(p)/sizeof(char); i++){
    if (p[i] != '\0'){
    printf("\n%d\n", p[i]);
    }
    }
    free(string);

    char * binary =  malloc(100 * sizeof(char));*/

    int ascii = 105;

    //printf("\nSize binary: %d", (int)sizeof(binary));

    /*printf("\n\nEnter a Binary value: ");
    scanf("\n%s", binary);*/
    char * x = binToStr("0110100001101000");

    printf("%s", decToBin(104));

    printf("\n%d\n", (int)sizeof(x));

    printf("%s", x);

    printf("\n\n");

    for(int i = 0; i < sizeof(x); i++){
    printf("%c", x[i]);
    }

    return 0;

}
