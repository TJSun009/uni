#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//binary only needs 8 characters
char * decToBin(int decimal)
{
    char binary[9];
    binary[8] = '\0';

  if ((decimal>256)||decimal<0){
        printf("Number must be between 0 and 256");

        return binary;
    }

  while(decimal > 0 && decimal < 256)
  {
    int power = 7;

    for (int i = 0; i <sizeof(binary)/sizeof(char); i++)
    {
        if (decimal >= pow(2,power))
        {
            decimal -= pow(2,power);
            binary[i] = '1';
        }
        else
        {
            binary[i] = '0';
        }

        power -= 1;
    }

  }

    return binary;
}

int * strToBin(char * input){
    int size, i = 0;

    for(i = 0; i < sizeof(input)/sizeof(char); i++){
        int charNum = (int)input[i];
        if (charNum == '\0'){
            break;
        }
    }

    printf("i = %d", i);

    size = i + 1;


    int temp[size];

    for(i = 0; i < size - 1; i++){
        int charNum = (int)input[i];
        temp[i] = charNum;
    //printf("\n%d\n", temp[i]);
  }
    free(input);

    return temp;
    //returns memory address as well
}

char * binToStr(char * input){

    char binChar[9];

    binChar[8] = '\0';

    int length = strlen(input);

    printf("%d", length);

    char string[length];

    int i, j, k = 0;

    while (i < length){

        binChar[j] = input[i];

        if (j == 7){
            int charNum = (int) strtol(binChar, NULL, 2);
            string[k] = (char) charNum;
            k++;
            j = 0;
            i++;
        }
        i++;
        j++;
    }
    return string;
}
