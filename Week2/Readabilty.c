#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
// made by Paclibar, Josh
// hehez B)

// prototype functions
int allCounts(string text);
void printGrade(int grade);
int colemanLiauIndex(int a, int b, int c);

int l, w, s, index;


int main(void)
{
    string phrase = get_string("Text: ");
    allCounts(phrase);
    colemanLiauIndex(l, w, s);
    printGrade(index);
}

int allCounts(string text)
{
    int letters = 0;
    int words = 1;
    int sentenz = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        // checking if is a letter
        if (isalpha(text[i]) > 0)
        {
            letters++;
        }
        // checking if space
        if (text[i] == ' ')
        {
            words++;
        }
        // checking if end of sentence
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentenz++;
        }
    }
    return l = letters, w = words, s = sentenz;
}

int colemanLiauIndex(int a, int b, int c)
{
    // was given in instruction
    return index = round(0.0588 * (a / ((float)b / 100)) - 0.296 * (c / ((float)b / 100)) - 15.8);
}

void printGrade(int grade)
{
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}
