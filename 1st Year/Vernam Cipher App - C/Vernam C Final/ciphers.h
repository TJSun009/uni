#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define textSize 10000

void strToDec(char String[], size_t length, int nums[])
{

    for (int i = 0; i < length; i++)
    {
        nums[i] = (int)String[i];
    }
}

void decToStr(int input[], size_t length,char String[])
{

    for (int i = 0; i < length; i++)
    {

        String[i] = (char)input[i];
    }
}

void encrypt()
{
    char * locale = setlocale(LC_ALL, "");

	char temp[textSize];
	for(int i = 0; i < textSize; i++){
		temp[i] = '\0';
	}

	printf("\n Enter your Message: ");
	fgets(temp, textSize, stdin);

	int s_length;

	for(int i = 0; i < 100; i++){
		if(temp[i] == '\0'){
			s_length = i - 1;
			break;
		}
	}

	char plaintext[s_length+1];
	plaintext[s_length] = '\0';

	for(int i = 0; i < s_length; i++)
    {
		plaintext[i] = temp[i];
	}

	int asciiVals[s_length];
    strToDec(plaintext, sizeof(plaintext)/sizeof(plaintext[0])-1, asciiVals);

	char asciiValsString[s_length + 1];
	asciiValsString[s_length] = '\0';

	decToStr(asciiVals, sizeof(asciiVals)/sizeof(asciiVals[0]), asciiValsString);

	int padNums[s_length];
	int cipherNums[s_length];

	char padString[s_length+1];
	padString[s_length] = '\0';
	char ciphertextString[s_length+1];
    ciphertextString[s_length] = '\0';

	srand(time(0));

	for(int i = 0; i < s_length; i++)
	{
		//creating the random pad and performing cipher
        int x = 0;
        int c = 0;

		while(c < 32 || x < 32)
        {
            x = rand()%128;
            c = (x)^(asciiVals[i]);
        }

        padNums[i] = x;
        cipherNums[i] = c;

	}

    decToStr(padNums, sizeof(padNums)/sizeof(padNums[0]), padString);

    decToStr(cipherNums, sizeof(cipherNums)/sizeof(cipherNums[0]), ciphertextString);

	printf("\n Plaintext:  %s\n Pad:        %s\n Ciphertext: %s\n", plaintext, padString, ciphertextString);


    char save;

	printf("\n\n Save Data?\n Save - Type S\n Continue - Type Any Character\n\n ");
	scanf("%c", &save);

	if(save == 'S'||save == 's')
    {
        bool saved = false;

        while(saved == false)
        {
            time_t rawtime = time(NULL);

            struct tm *tm_ptr = localtime(&rawtime);

            if (rawtime == -1 || tm_ptr == NULL)
            {
                char response;
                printf(" Failed to Save.\n Retry - Type R\n Continue - Type Any Character\n ");
                scanf("%c", &response);

                if(response == 'R' || response == 'r')
                {
                    saved = true;
                }
            }
            else
            {
                char tmFormat[256] = {0};

                strftime(tmFormat, 256, "%c", tm_ptr);

                FILE *dataFile;

                dataFile = fopen("Vernam_Data.txt", "a+");

                fprintf(dataFile, "\nSaved %s\n--------------\nCiphertext: |%s|\nPad: |%s|\n", tmFormat, ciphertextString, padString);

                fclose(dataFile);

                saved = true;
            }

        }
    }

    printf("\n Type Any Key to Continue.\n ");
    getchar();
    printf(" ");
}

void decrypt()
{

    char * locale = setlocale(LC_ALL, "");

    bool done = false;

	char temp_c[textSize];
	char temp_p[textSize];

	for(int i = 0; i < textSize; i++){
		temp_c[i] = '\0';
		temp_c[i] = '\0';
	}

    while(!done)
    {
        printf("\n Enter Ciphertext: ");
        fgets(temp_c, textSize-1, stdin);

        printf("\n Enter Pad: ");
        fgets(temp_p, textSize-1, stdin);

        int c_length, p_length;

        for(int i = 0; i < textSize; i++){
            if(temp_c[i] == '\0'){
                c_length = i;
                c_length--;
                break;
            }
        }

        for(int i = 0; i < textSize; i++){
            if(temp_p[i] == '\0'){
                p_length = i;
                p_length--;
                break;
            }
        }

        if(c_length == p_length){
            char pad[c_length];
            char ciphertext[c_length];
            for(int i = 0; i < p_length; i++)
            {
                pad[i] = temp_p[i];
                ciphertext[i] = temp_c[i];
            }
            int padNums[c_length];
            int cipherNums[c_length];
            int plainNums[c_length];

            char plaintextString[c_length+1];
            plaintextString[c_length] = '\0';

            strToDec(pad, sizeof(pad)/sizeof(pad[0]), padNums);
            strToDec(ciphertext, sizeof(ciphertext)/sizeof(ciphertext[0]), cipherNums);

            for(int i = 0; i < c_length; i++)
            {
                plainNums[i] = padNums[i] ^ cipherNums[i];
            }

            decToStr(plainNums, sizeof(plainNums)/sizeof(plainNums[0]), plaintextString);
            printf("\n Plaintext: %s\n", plaintextString);

            done = true;
        }
        else
        {
            printf("\n Pad and Ciphertext not equal length.\n Try Again\n ");
        }
    }


    printf(" Type Any Key to Continue.\n ");
    getchar();
    printf(" ");

}
