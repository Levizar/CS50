#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int validateTheKey(string key);

int main(int argc, string argv[])
{

    if (argc != 2)
    {
        printf("\nThe program requires one argument not less, not more\n");
        return 1;
    }

    string key = argv[1];
    // validate the key
    int keyValidationCode = validateTheKey(key);
    if (keyValidationCode == 1)
    {
        return 1;
    }

    // create the mapping
    int mapper[26];
    for (int i = 0; i < 26; ++i)
    {
        mapper[i] = tolower(key[i]) - 'a' - i;
    }

    // get the text to cipher
    string plainText = get_string("plaintext:");

    // cipher the given text
    string cipheredText = plainText;
    int cipheredTextLength = strlen(cipheredText);
    for (int j = 0; j < cipheredTextLength; ++j)
    {
        if (isalpha(cipheredText[j]))
        {
            int mapIndex = tolower(cipheredText[j]) - 'a';
            cipheredText[j] = cipheredText[j] + mapper[mapIndex];
        }
    }

    // print the ciphered text
    printf("ciphertext: %s\n", cipheredText);
    return 0;
}

int validateTheKey(string key)
{
    int keyLength = strlen(key);
    // check 26 char
    if (keyLength != 26)
    {
        printf("\nThe key length is supposed to be 26\n");
        return 1;
    }

    int checkingCharArr[26];
    for (int i = 0; i < 26; ++i)
    {
        checkingCharArr[i] = 0;
    }

    for (int j = 0; j < keyLength; ++j)
    {
        // check if alphabetical
        if (!isalpha(key[j]))
        {
            printf("\nThe key is suppose to only contain alphabetical character\n");
            return 1;
        }

        // check if characters appears only once
        int charMappingIndex = toupper(key[j]) - 'A';
        checkingCharArr[charMappingIndex]++;
        if (checkingCharArr[charMappingIndex] > 1)
        {
            printf("\nThe key is not supposed to contain duplicated character\n");
            return 1;
        }
    }

    return 0;
}
