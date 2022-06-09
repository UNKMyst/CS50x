#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
// made by Josh Paclibar
// Instructions by CS50x

// prototype functions
void caesarCipher(char *, int);

int main(int argc, char *argv[])
{
    //validate key of user
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (isalpha(argv[1][i]) != 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    // Converts key to integer from alpha
    int key = atoi(argv[1]);

    // ask user input
    char *plaintext = get_string("Enter Text To Encrpyt: ");
    caesarCipher(plaintext, key);
}

void caesarCipher(char *t, int k)
{
    printf("ciphertext: ");
    //check each character of text
    for (int i = 0; t[i] != '\0'; i++)
    {
        //check if alphabet
        if (isalpha(t[i]) != 0)
        {
            // now check if Capital
            if (isupper(t[i]) != 0)
            {
                //Capital will now encrpyt
                printf("%c", ((t[i] - 'A' + k) % 26) + 'A');
            }
            // LowerCase will now encrpy
            else
            {
                printf("%c", ((t[i] - 'a' + k) % 26) + 'a');
            }
        }
        // will keep non alphabet characters
        else
        {
            printf("%c", t[i]);
        }
    }
    printf("\n");
}
