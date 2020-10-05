// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 385;

unsigned int dictsize = 0;
bool loaded = false;
// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int index = hash(word);
    node *cursor = table[index];
    bool found = false;
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            found = true;
            break;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return found;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int length = strlen(word), hash = 0, i;
    for (i = 0; i < length && i < 5 ; i++)
    {
        char c = tolower(word[i]);

        hash = hash + ((int) c % 97) + 26 * i;  // for the first 5 letters differnt hashes

    }

    return hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    int index;
    FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return loaded;
    }

    char word[LENGTH];
    while (fscanf(inptr, "%s", word) != EOF)   //while eof the function repeats
    {
        index = hash(word);
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return loaded;

        }
        strcpy(n->word, word);
        n->next = NULL;


        dictsize++;
        if (table[index] == NULL)
        {
            table[index] = n;

        }
        else
        {
            n->next = table[index];
            table[index] = n;


        }

    }
    fclose(inptr);
    loaded = true;
    return loaded;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (loaded)
    {
        return dictsize;
    }
    else
    {
        return 0;
    }

}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next; //passes the next pointer to the cursor
            free(temp);
        }
    }
    return true;
}
