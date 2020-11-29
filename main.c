#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

//unsigned int hashCode(const char *word, const unsigned int N);


int main()
{
    char *hello = "HELLO, WORLD!\nHOLY MOLLY!\0";
    char *h2 = hello;
    unsigned int length = strlen(hello);
    char *lowerCaseWord = malloc(length * sizeof(char) + 1);
    int i = 0;
    while (*(h2+i) != '\n'){
        *(lowerCaseWord + i) = *(h2+i);
//        h2++;
        i++;
    }
    *(lowerCaseWord + i) = '\0';
    printf("1: %s\n", hello);
    printf("2: %s\n", h2);
    printf("3: %s", lowerCaseWord);
    free(lowerCaseWord);
    if (lowerCaseWord)
    {
      printf("diff than null");
    }

    return 0;
}

