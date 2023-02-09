// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

int count = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    if (table[index] == NULL)
    {
        return false;
    }

    if (strcasecmp(table[index]->word, word) == 0)
    {
        return true;
    }
    else
    {
        node *curr;
        curr = table[index]->next;
        if (curr == NULL)
        {
            return false;
        }

        while (curr != NULL)
        {
            if (strcasecmp(curr->word, word) == 0)
            {
                return true;
            }
            curr = curr->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *fp;
    fp = fopen(dictionary, "r");
    char new_word[LENGTH +1];

    if (fp == NULL)
    {
        return false;
    }

    while(fscanf(fp, "%s", new_word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, new_word);
        n->next = NULL;
        int index = hash(new_word);

        if (table[index] == NULL)
        {
            table[index] = n;
            count += 1;
        }
        else
        {
            node *curr;
            curr = table[index];
            while (curr->next != NULL)
            {
                curr = curr->next;
            }
            curr->next = n;
            count +=1;
        }
    }
    fclose(fp);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count;
}


void free_ll(node *n)
{
    node *tmp;

    while (n != NULL)
    {
        tmp = n;
        n = n->next;
        free(tmp);
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        free_ll(table[i]);
    }
    return true;
}
