// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
// As the function check the first three characters of the word the total number of
// buckets required is 26 * 26 * 26 * 26 = 11456976881376
const unsigned int N = 456976;

// Hash table
node *table[N];

// Count number of words in dictionary
unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int bucket_index = hash(word);

    // Set the search_word node pointer to point to the second element (if it exists) in the linked
    // list inside bucket_index element of the table array
    node *search_word = table[bucket_index]->next;

    while (search_word != NULL)
    {
        if (strcasecmp(search_word->word, word) == 0)
        {
            // Word exists in dictionary
            return true;
        }

        // Move to next element in linked list
        search_word = search_word->next;
    }
    // If word does not exist in linked list
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // If the word does not have atleast two letters to hash
    if (strchr(word, '\'') != NULL)
    {
        unsigned int hash_value = (toupper(word[0]) - 'A');
        return hash_value;
    }

    else if (strlen(word) < 4)
    {
        if (strlen(word) == 3)
        {
            unsigned int hash_value = 676 * (toupper(word[0]) - 'A') +
                                      26 * (toupper(word[1]) - 'A') + (toupper(word[2]) - 'A');
            return hash_value;
        }
        else if (strlen(word) == 2)
        {
            unsigned int hash_value = 26 * (toupper(word[0]) - 'A') + (toupper(word[1]) - 'A');
            return hash_value;
        }

        else
        {
            unsigned int hash_value = (toupper(word[0]) - 'A');
            return hash_value;
        }
    }

    /* In all other cases use the first 3 letters of the word to generate a hash

    Examples:
    AAA -> 0 (0 + 0 + 0)
    AAB -> 1 (0 + 0 + 1)
    ABA -> 26 (0 + 26 * 1 + 0)
    ZZZ -> 17575 (676 * 25 + 26 * 25 + 25)
    */
    else
    {
        unsigned int hash_value = 17576 * (toupper(word[0]) - 'A') +
                                  676 * (toupper(word[1]) - 'A') + 26 * (toupper(word[2]) - 'A') +
                                  (toupper(word[3]) - 'A');
        return hash_value;
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the dictionary file and check if file is opened succesfully
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Could not open dictionary for reading.");
        return false;
    }

    char buffer[LENGTH + 1];

    // Set all first elements of hash table array to point to NULL
    for (int i = 0; i < N; i++)
    {
        table[i] = malloc(sizeof(node));
        if (table[i] == NULL)
        {
            return false;
        }
        table[i]->next = NULL;
    }

    while (fscanf(dict, "%s", buffer) != EOF)
    {
        // Allocate memory for a new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // Set the dictionary word as the value of the word attribute of the node
        strcpy(n->word, buffer);

        // Hash the word to get the index of the linked list to insert the word into the hash table
        int bucket_index = hash(buffer);

        /*
        Firstly we set the next attribute of new node to point to what table[bucket_index]->next
        actually points to:

        - When new node is the second element in the linked list directly next to the hash table
        array element, we end up setting it to point to NULL as currently table[bucket_index]->next
        actually points to NULL.

        - When new node is any other new element into the linked list inside an element of the hash
        table array, we end up setting it to point to the list that the hash table array element
        points to and effectively append the element into the list.
        */
        n->next = table[bucket_index]->next;
        table[bucket_index]->next = n;

        // Increment word_count in dictionary
        word_count++;
    }

    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i]->next;
        node *tmp = cursor;

        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);

            tmp = cursor;
        }
        free(table[i]);
    }
    return true;
}
