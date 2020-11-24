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

unsigned int getKey(unsigned int hash);

bool unload(void);

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    unsigned int hash;
    struct node *next;
} node;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // check if the dictionary is loaded
    if (!isDictionaryLoaded)
    {
        return false;
    }

    // lowering the input word
    unsigned int length = strlen(word);
    char lowerCaseWord[length];
    for (int i = 0; i <= length; ++i)
    {
        lowerCaseWord[i] = (char) tolower(word[i]);
    }

    // get the hash
    unsigned int hashCode = hash(word);
    // get the key
    unsigned int key = getKey(hashCode);

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
            strcmp(lowerCaseWord, list->word);
            return true;
        }
        // if not the same go to next node
        list = list->next;
    }
    // if not found before the linkedList queue then it's not there
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // simple hash by adding the int value of char
    unsigned int hash = 0;
    for (char *c = word; *c != '\0'; c++)
    {
        hash += (int) *c;
    }
    return hash;
}

// get the key for this hash
unsigned int getKey(unsigned int hash)
{
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char *word = malloc(LENGTH * sizeof(char) + 1);
    if (word == NULL)
    {
        return false;
    }

    char *pt = dictionary;
    unsigned int i;
    // TODO: parse dictionary
    while (*dictionary)
    {
        // read a word
        i = 0;
        while (*pt != '\n')
        {
            word[i++] = *pt;
        }
        word[i] = '\0';

        unsigned int hashCode = hash(word);
        unsigned int key = getKey(hashCode);

        // get the first node for that key
        node *list = table[key];
        // insert into the link list of that key
        while (list != NULL)
        {
            // get next node
            list = list->next;
        }
        list = malloc(sizeof(struct node));
        if(list == NULL)
        {
            free(word);
            unload();
            return false;
        }
        // todo : copy the string to node.word
        list->word[i]

        // increase dictSize

        // next word


    }

    free(word);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dictSize;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}
