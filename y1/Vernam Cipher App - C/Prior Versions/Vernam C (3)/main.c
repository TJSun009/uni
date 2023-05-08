#include "ciphers.h"

int main()
{
    char * locale = setlocale(LC_ALL, "en_UK.UTF-8");

    printf("Welcome to the Vernam Cipher.\n............................");

    printf("\nescCharacters %s", escCharacters);

    printf("\nANSII chars > 127: ");

    for(int i = 127; i < 256; i++)
    {
        printf("%d = %c", i, (char)i);
    }
    printf("\n");

	bool quit = false;
	while (quit == false){
        printf("\nOptions:\n\n -----------------------\n |Encrypt    - Type E  |\n |Decrypt    - Type D  |\n |View Data  - Type V  |\n |Quit       - Type Q  |\n -----------------------\n\n Choose Option: ");

        char mode;

        scanf("%c", &mode);
        getchar();

        if (mode == 'e' || mode == 'E'){
            encrypt();
        }
        else if(mode == 'd' || mode == 'D'){
            decrypt();
        }
        else if(mode == 'v' || mode == 'V'){
            system("Vernam_Data.txt");
            /*printf(" Type Any Key to Continue.");
            getchar();*/

        }
        else if(mode == 'q' || mode == 'Q'){
            quit = true;
        }
        else{
            printf("Invalid Input\n--------------------\n\n\n");
        }

        system("cls");
	}


	return 0;

}
