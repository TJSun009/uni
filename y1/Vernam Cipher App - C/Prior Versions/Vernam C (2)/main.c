#include "ciphers.h"
#include <time.h>

#define textSize 10000

void encrypt()
{
	char * temp = (char *) malloc(textSize);
	for(int i = 0; i < textSize; i++){
		temp[i] = '\0';
	}

	printf("\nEnter your Message: ");
	fgets(temp, textSize, stdin);

	int s_length;

	for(int i = 0; i < 100; i++){
		if(temp[i] == '\0'){
			s_length = i - 1;
			break;
		}
	}

	char string[s_length];

	for(int i = 0; i < s_length; i++){
		string[i] = temp[i];
	}

	free(temp);

	int binSize = s_length*8;

	char plaintextBinary[binSize];
	for(int i = 0; i < binSize; i++){
		plaintextBinary[i] = '\0';
	}

	strToBin(string, plaintextBinary);

	char padBinary[binSize+1];
	padBinary[binSize] = '\0';

	char ciphertextBinary[binSize+1];
	ciphertextBinary[binSize] = '\0';

	srand(time(0));

	for(int i = 0; i < binSize; i++)
	{
		//creating the random pad
		int x = rand();

		if(x > RAND_MAX/2)
		{
			padBinary[i] = '1';
		}
		else{
			padBinary[i] = '0';
		}
	}


	for(int i = 0; i < binSize; i++){
			bool x = false;
			bool y = false;

			if (plaintextBinary[i] == '1')
			{
				x = true;
			}

			if (padBinary[i] == '1')
			{
				y = true;
			}

			char output = '0';

			if(x ^ y)
			{
				output = '1';
			}

			ciphertextBinary[i] = output;
	}


	char padString[s_length+1];
	padString[s_length] = '\0';

	char plaintextString[s_length+1];
	plaintextString[s_length] = '\0';

	char ciphertextString[s_length+1];
	ciphertextString[s_length] = '\0';

	binToStr(plaintextBinary, plaintextString);

	binToStr(padBinary, padString);

	binToStr(ciphertextBinary, ciphertextString);

	plaintextString[s_length] = '\0';

	printf("\nPlaintext:  %s\nPad:        %s\nCiphertext: %s\n", plaintextString, padString, ciphertextString);

}

void decrypt()
{
	char * temp_c = (char *) malloc(textSize);
	char * temp_p = (char *) malloc(textSize);
	for(int i = 0; i < textSize; i++){
		temp_c[i] = '\0';
		temp_c[i] = '\0';
	}

	printf("\nEnter Ciphertext: ");
	fgets(temp_c, textSize-1, stdin);

	printf("\nEnter Pad: ");
   fgets(temp_p, textSize-1, stdin);

	int c_length, p_length;

	for(int i = 0; i < 100; i++){
		if(temp_c[i] == '\0'){
			c_length = i;
			break;
		}
	}

	for(int i = 0; i < 100; i++){
		if(temp_p[i] == '\0'){
			p_length = i;
			break;
		}
	}

	if(c_length == p_length){
        char p_string[p_length];
        //p_string[p_length] = '\0';
        char c_string[c_length];
        //c_string[c_length] = '\0';

        for(int i = 0; i < p_length; i++){
            p_string[i] = temp_p[i];
            c_string[i] = temp_c[i];
        }

        printf("p_string: %s", p_string);
        printf("c_string: %s", c_string);

        free(temp_c);
        free(temp_p);

        int binSize = (p_length-1)*8;

        printf("binSize: %d", binSize);

        char plaintextBinary[binSize+1];
        plaintextBinary[binSize] = '\0';

        char padBinary[binSize];
        strToBin(p_string, padBinary);

        char ciphertextBinary[binSize];
        strToBin(c_string, ciphertextBinary);

        for(int i = 0; i < binSize; i++){
                bool x = false;
                bool y = false;

                if (ciphertextBinary[i] == '1')
                {
                    x = true;
                }

                if (padBinary[i] == '1')
                {
                    y = true;
                }

                char output = '0';

                if(x ^ y)
                {
                    output = '1';
                }

                plaintextBinary[i] = output;
        }

         printf("\nplaintextBinary = %s", plaintextBinary);

        for (int i = 0; i < binLength(plaintextBinary); i++)
        {
           if (plaintextBinary[i] != '0')
           {
              char plaintextString[p_length];
              binToStr(plaintextBinary, plaintextString);
              printf("Length Plaintext: %d", sizeof(plaintextString));
              printf("\nPlaintext: %s\n", plaintextString);
              break;
           }
           else if(i == binLength(plaintextBinary) - 1)
           {
              printf("\nInvalid Entry\n");

           }
        }
    }
    else{
        printf("\nThe pad and the message text must be the same length.\n");
    }

}



int main()
{
    printf("Welcome to the Vernam Cipher.\n");

	bool quit = false;
	while (quit == false){
        printf("\nDo you wish to decrypt or encrypt(d/e):\n");

        char mode;

        scanf("%c", &mode);
        getchar();

        if (mode == 'e' || mode == 'E'){
            encrypt();
        }
        else if(mode == 'd' || mode == 'D'){
            decrypt();
        }
        else{
            printf("Invalid Input");
        }

        char end;

        printf("\nDo wish to quit?\nType q to quit \nType any value to continue:\n");

        scanf("%c", &end);
        getchar();

        if(end == 'q' || end == 'Q'){
            quit = true;
            mode = '\0';
        }
	}


	return 0;

}
