#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


int binLength(char * input)
{
	int binSize = 0;
	while(binSize >= 0){
		if(input[binSize] != '0' && input[binSize] != '1'){
			break;
		}
		binSize++;
	}
	return binSize;
}

int strLength(char * input)
{
	int charSize = 0;
	while (charSize >= 0){
        char x = (int)input[charSize];
		if(( x > 127) || (x < 32)){
			break;
		}
        charSize++;
	}
	return charSize;
}

char * decToBin(int decimal)
{
	char binary[8];

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

	char * ptr = binary;

	return ptr;
}

int binToDec(char * input)
{
   int length = binLength(input);
   printf("binLength = %d", length);
   int decimal = 0;

   for (int i = 0; i < length; i++)
   {
      if(input[length - (i+1)] == '1')
      {
         decimal += (int)pow(2, i);
      }
   }
   return decimal;
}


void binToStr(char * input, char * output)
{
	char binChar[8];

	int length = binLength(input);

	int s_length = length/8;

	int i = 0, j = 0, k = 0;

	while (k < s_length){
		binChar[j] = input[i];

		if (j == 7){
         printf("\nbinChar %d: %d\n", k, binToDec(binChar));

			int charNum = binToDec(binChar);
			printf("\ncharNum = %d\n", charNum);

			char escCharacters[] = {'γ','Γ','Δ','β','δ','ε','Θ','η','ζ','Λ','θ','ι','ξ','ο','π','ρ','ς','σ','τ','υ','φ','χ','ψ','ω','ϑ','℘','ϖ'};

			if (charNum < 32)
         {
            output[k] = escCharacters[charNum];
         }
         else
         {
            output[k] = (char)charNum;
         }


			k++;
			i++;
			j = 0;
		}
		i++;
		j++;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
void strToBin(char * input, char * binary){

   char escCharacters[] = {'γ','Γ','Δ','β','δ','ε','Θ','η','ζ','Λ','θ','ι','ξ','ο','π','ρ','ς','σ','τ','υ','φ','χ','ψ','ω','ϑ','℘','ϖ'};

	int size = strLength(input);

	int temp[size];

	for (int i = 0; i < size; i++){
		int charNum = (int)input[i];
		temp[i] = charNum;
	}

	int x = 0;

	for(int i = 0; i < size; i++){
      char * bin;
      if(temp[i] < 32)
      {
         for (int e = 0; i < sizeof(escCharacters); i++)
         {
            if (escCharacters[e] == input[i])
            {
               bin = decToBin(e);
            }

         }
      }
      else
      {
         bin = decToBin(temp[i]);
      }
		int j = 0;
		while (j < 8)
		{
			binary[x] = bin[j];
			x++;
			j++;
		}
	}

}

