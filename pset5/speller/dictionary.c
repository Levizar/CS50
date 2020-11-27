// Implements a dictionary's functionality

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"


bool isDictionaryLoaded = false;

int dictSize = 0;

unsigned int hash(const char *word);

unsigned int getKeyFromHash(unsigned int hash);

bool unload(void);

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    unsigned int hash;
    struct node *next;
} node;

// Number of buckets in hash table
const unsigned int N = 15;

// Hash table
node *table[N];

// Todo: debug check
// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // check if the dictionary is loaded
    if (!isDictionaryLoaded)
    {
        return false;
    }

    const char *wordPtr = word;
    char lowerCaseWord[LENGTH + 1];
    unsigned int i = 0;
    // Todo: there is a problem here -> "LA" ended up in "0/000 0/000...."
    while (*wordPtr != '\0')
    {
        lowerCaseWord[i] = (char) tolower(*wordPtr);
        wordPtr++;
    }
    lowerCaseWord[i] = '\0';

    // get the hash
    unsigned int hashCode = hash(word);
    // get the key
    unsigned int key = getKeyFromHash(hashCode);

    // check if there is a pointer for that key
    node *list = table[key];
    if (list == NULL)
    {
        return false;
    }

    // check through the linkedList for the same hash
    while (list != NULL)
    {
        // if same hash check the word (Simple hash could collide with other)
        if (hashCode == list->hash && !strcmp(list->word, lowerCaseWord))
        {
            return true;
        }
        // if not the same go to next node
        list = list->next;
    }
    // if not found before the linkedList end then it's not part of the list
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // simple hash by adding the int value of char
    unsigned int hash = 0;
    while (*word != '\0')
    {
        hash += (int) *word++;
    }
    return hash;
}

// get the key for this hash
unsigned int getKeyFromHash(unsigned int hash)
{
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // initialize the array pointer to avoid segmentation fault
    for (int i = 0; i < N; ++i)
    {
        table[i] = NULL;
    }

    //
    FILE *inputFile = fopen(dictionary, "r");
    if (inputFile == NULL)
    {
        printf("Could not open %s\n", dictionary);
        return false;
    }
    char bufferChar[1];


    // parse dictionary file
    unsigned int i;
    while (fread(bufferChar, sizeof(char), 1, inputFile))
    {
        // allocate memory for a new node
        node *newNode = malloc(sizeof(struct node));
        if (newNode == NULL)
        {
            unload();
            return false;
        }

        i = 0;
        while (bufferChar[0] != '\n')
        {
            newNode->word[i++] = bufferChar[0];
            fread(bufferChar, sizeof(char), 1, inputFile);
        }
        newNode->word[i] = '\0';
        newNode->hash = hash(newNode->word);
        newNode->next = NULL;
        unsigned int key = getKeyFromHash(newNode->hash);

        // get head and search for tail + attach new node to tail
        node *list = table[key];
        // insert into the link list of that key
        if (list == NULL)
        {
            table[key] = newNode;
        }
        else
        {
            // get the tail
            while (list->next != NULL)
            {
                list = list->next;
            }
            list->next = newNode;
        }

        // increase dictSize and go to next line
        dictSize++;
    }

    fclose(inputFile);
    isDictionaryLoaded = true;
    return isDictionaryLoaded;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dictSize;
}

void unloadLinkedListIterative(struct node *list)
{
    node *nextNode = NULL;
    while(list != NULL)
    {
        nextNode = list->next;
        free(list);
        list = nextNode;
    }

}

void UnloadLinkedListRecursive(struct node *list)
{
    if (list->next != NULL)
    {
        UnloadLinkedListRecursive(list->next);
        free(list);
    }
    else
    {
        free(list);
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; ++i)
    {
        if (table[i] != NULL)
        {
            unloadLinkedListIterative(table[i]);
        }
    }
    return true;
}


