
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "llist.h"

#define MAX_CHAR 1000 // Line Length Maximum
#define MAX_COUNT 1000
#define REMOVE_COUNT 500

#define STRATEGY_FIRST "first"
#define STRATEGY_BEST "best"
#define STRATEGY_WORST "worst"

typedef struct _Block
{
    char *nameptr;
    int size;
} Block;

int strat;
FILE *outputFile;
int memoryAllocation = 0;

void nodePrint(void *mb, int name);

Block *getFreeBlock(int sizeOfWord, llist *list, char *strategy);

void purgeFromList(llist *list, llist *freed);

void fprintList(llist *list, void (*print)(void *, int), int name);

void mergeAndPush(llist *list, Block *data);

int main(int argc, char *argv[])
{
    // Seed Random Generator
    srand(time(0));

    llist *allocMBList = llist_create(NULL);
    llist *freedMBList = llist_create(NULL);

    // Get Arguments
    if (argc != 4)
    {
        printf("Invalid arguments!\n");
        return EXIT_FAILURE;
    }

    // Determine type of allocation strategy
    char *strategy = argv[3];
    if (strcmp(strategy, STRATEGY_FIRST) == 0)
    {
        strat = 0;
    }
    else if (strcmp(strategy, STRATEGY_BEST) == 0)
    {
        strat = 1;
    }
    else if (strcmp(strategy, STRATEGY_WORST) == 0)
    {
        strat = 2;
    }
    else
    {
        printf("Invalid Strategy!\n");
        return EXIT_FAILURE;
    }

    // Open output file
    outputFile = fopen(argv[2], "w");

    // Open File
    char *filename = argv[1];
    FILE *file;
    file = fopen(filename, "r");

    // Determine if file exists
    if (file == NULL)
    {
        printf("Could not find file %s!", filename);
        return EXIT_FAILURE;
    }

    // Loop through file
    char line[MAX_CHAR];
    char *word;
    size_t count = 0;
    while (fgets(line, MAX_CHAR, file) != NULL)
    {
        // Get word in current line
        word = strtok(line, "\n");
        size_t size = strlen(word) + 1;
        void *mb;

        // Add to list
        Block *block = getFreeBlock(size, freedMBList, strategy);
        if (block == NULL)
        {
            // Assign memory for string
            mb = sbrk(size);
            memoryAllocation += size;

            // Create new block
            block = (Block *)malloc(sizeof(Block));
        }
        else
        {
            mb = (void *)block->nameptr;
            // printf("mb: %p", mb);
        }
        strcpy((char *)mb, word);

        // Setup new block and allocate it
        block->nameptr = mb;
        block->size = size;
        llist_push(allocMBList, block);

        // Determine if it is time to purge
        count++;
        if (count >= MAX_COUNT)
        {
            count = 0;
            purgeFromList(allocMBList, freedMBList);
        }
    }

    fclose(file);

    // Save lists to output file
    fprintf(outputFile, "-- Total Memory Allocated --\nTotal: %i\n", memoryAllocation);
    fprintf(outputFile, "-- allocMBList (%i) --\n", llist_getSize(allocMBList));
    fprintList(allocMBList, nodePrint, 1);
    fprintf(outputFile, "-- freedMBList (%i) --\n", llist_getSize(freedMBList));
    fprintList(freedMBList, nodePrint, 0);

    // Display some stats on CLI
    printf("allocations list size: %i.\n", llist_getSize(allocMBList));
    printf("freed list size: %i.\n", llist_getSize(freedMBList));
    printf("memory allocated: %i\n", memoryAllocation);

    fclose(outputFile);

    return 0;
}

// Used by linked list to print
void nodePrint(void *mb, int name)
{
    Block *block = (Block *)mb;
    if (name == 1)
        fprintf(outputFile, "address=%p, size=%d, name=%s\n", block->nameptr, block->size, block->nameptr);
    else
        fprintf(outputFile, "address=%p, size=%d\n", block->nameptr, block->size);
}

// Finds a freed memory block that matches the memory size based on implementation type
Block *getFreeBlock(int sizeOfWord, llist *list, char *strategy)
{
    int foundIndex = -1;
    Block *foundBlock = NULL;

    // Strategies
    if (strcmp(strategy, STRATEGY_FIRST) == 0)
    {
        // First
        size_t i;
        for (i = 0; i < llist_getSize(list); i++)
        {
            // Get current block in list
            Block *compareBlock = (Block *)llist_get(list, i);

            // Reached end of list
            if (compareBlock == NULL)
                break;

            if (compareBlock->size >= sizeOfWord)
            {
                // Found a large enough block
                foundIndex = i;
                foundBlock = compareBlock;
                break;
            }
        }
    }
    else if (strcmp(strategy, STRATEGY_BEST) == 0)
    {
        // Best
        int lowestDiff = MAX_CHAR;
        size_t i;
        for (i = 0; i < llist_getSize(list); i++)
        {
            // Get current block in list
            Block *compareBlock = (Block *)llist_get(list, i);

            // Reached end of list
            if (compareBlock == NULL)
                break;

            int difference = compareBlock->size - sizeOfWord;
            if ((difference < lowestDiff) && difference >= 0)
            {
                // New lowest difference found
                lowestDiff = difference;
                foundIndex = i;
                foundBlock = compareBlock;
            }
        }
    }
    else
    {
        // Worst
        int highestDiff = -1;
        size_t i;
        for (i = 0; i < llist_getSize(list); i++)
        {
            // Get current block in list
            Block *compareBlock = (Block *)llist_get(list, i);

            // Reached end of list
            if (compareBlock == NULL)
                break;

            int difference = compareBlock->size - sizeOfWord;
            if ((difference > highestDiff) && difference >= 0)
            {
                // New highest difference found
                highestDiff = difference;
                foundIndex = i;
                foundBlock = compareBlock;
            }
        }
    }

    if (foundIndex != -1)
    {
        // Determine Split
        if (foundBlock->size - sizeOfWord > 0)
        {
            // Make new block that is split
            Block *split = (Block *)malloc(sizeof(Block));
            split->nameptr = foundBlock->nameptr + sizeOfWord;
            split->size = foundBlock->size - sizeOfWord;

            // Add new split block to freed list
            llist_push(list, split);
        }

        // Remove block from freed list
        llist_popAt(list, foundIndex);
    }

    return foundBlock;
}

// Removes elements from list to freed
void purgeFromList(llist *list, llist *freed)
{
    int size;
    size_t i;
    // Remove up to REMOVE_COUNT amount of memory blocks from allocList
    for (i = 0; i < REMOVE_COUNT; i++)
    {
        size = llist_getSize(list);
        int randomChoice = rand() % (size);

        Block *removedBlock = (Block *)llist_popAt(list, randomChoice);
        mergeAndPush(freed, removedBlock);
    }
}

// Outputs memory block list to file
void fprintList(llist *list, void (*print)(void *, int), int name)
{
    struct node *curr = *list;
    while (curr != NULL)
    {
        print(curr->data, name);
        curr = curr->next;
    }
}

// Finds for consecutive addresses of given data and merges, otherwise adds to head
void mergeAndPush(llist *list, Block *data) {
    // Search through list for consecutive address
    size_t i;
    for (i = 0; i < llist_getSize(list); i++)
    {
        Block *comparisonBlock = (Block *) llist_get(list, i);

        if (comparisonBlock == NULL) {
            break;
        }

        // Check if block is after given
        if ((data->nameptr + data->size) == comparisonBlock->nameptr) {
            // Found following address
            printf("Merged two addresses!\n");
            data->size += comparisonBlock->size;
            // Combine Words
            strcat(data->nameptr, comparisonBlock->nameptr);
            llist_popAt(list, i);
            llist_push(list, data);
            return;
        }

        // Check if block is before given
        if ((comparisonBlock->nameptr + comparisonBlock->size) == data->nameptr) {
            // Found preceding address
            printf("Merged two addresses!\n");
            comparisonBlock->size += data->size;
            // Combine words
            strcat(comparisonBlock->nameptr, data->nameptr);
            return;
        }
    }
    // Failed to find consecutive address, add to list
    llist_push(list, data);
}
