#include "uthash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// @leet start
struct HashEntry {
    int id;
    char* str;
    UT_hash_handle hh;
};

struct HashEntry* hashFind(struct HashEntry* head, int id)
{
    struct HashEntry* ent;
    HASH_FIND_INT(head, &id, ent);
    return ent;
}

void hashAdd(struct HashEntry** head, int id, char* str)
{
    struct HashEntry* ent = malloc(sizeof(struct HashEntry));
    ent->id = id;
    ent->str = str;
    HASH_ADD_INT(*head, id, ent);
}

void hashFree(struct HashEntry** head)
{
    struct HashEntry *ent, *temp;
    HASH_ITER(hh, *head, ent, temp)
    {
        HASH_DEL(*head, ent);
        free(ent);
    }
}

int cmp_chars(const void* a, const void* b)
{
    return *(char*)a - *(char*)b;
}

int cmp_by_str(const struct HashEntry* a, const struct HashEntry* b)
{
    return strcmp(a->str, b->str);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes)
{
    *returnSize = 0;
    int capacity = 10;
    char*** result = malloc(capacity * sizeof(char**));
    *returnColumnSizes = malloc(capacity * sizeof(int));

    // copy sorted strs into a hash with their index as the id
    struct HashEntry* strs_hash = NULL;

    for (int i = 0; i < strsSize; i++) {
        // create a copy of the str
        int len = (int)strlen(strs[i]);
        char* str_cpy = malloc((len + 1) * sizeof(char));
        strcpy(str_cpy, strs[i]);
        // sort its characters and add it to the hash
        qsort(str_cpy, len, sizeof(char), cmp_chars);
        hashAdd(&strs_hash, i, str_cpy);
    }

    // sort the hash by the strings alphabetically
    HASH_SORT(strs_hash, cmp_by_str);

    // create a result group
    int col_size = 0;
    int col_capacity = 4;
    char** result_col = malloc(col_capacity * sizeof(char*));

    char* prev_str = NULL;
    struct HashEntry* ent = strs_hash;
    // iterate through the hash strings and group duplicates, putting the real strings into result_col
    while (ent != NULL) {
        // first string in new group or grouped anagram, so add to result column
        if (prev_str == NULL || strcmp(prev_str, ent->str) == 0) {
            if (col_size == col_capacity) {
                col_capacity *= 2;
                result_col = realloc(result_col, col_capacity * sizeof(char*));
            }

            result_col[col_size] = strs[ent->id];
            col_size += 1;

            prev_str = ent->str;
            ent = ent->hh.next;
        }
        // otherwise, this is a new anagram group so add the last col and start a new one
        else {
            // add to result
            if (*returnSize == capacity) {
                capacity *= 2;
                result = realloc(result, capacity * sizeof(char**));
                *returnColumnSizes = realloc(*returnColumnSizes, capacity * sizeof(int));
            }
            result[*returnSize] = result_col;
            (*returnColumnSizes)[*returnSize] = col_size;
            *returnSize += 1;

            // reset result_col, add this string to it and clear prev_str
            col_size = 0;
            col_capacity = 4;
            result_col = malloc(col_capacity * sizeof(char*));

            prev_str = NULL;
        }
    }

    // add the last column to the result
    if (*returnSize == capacity) {
        capacity *= 2;
        result = realloc(result, capacity * sizeof(char**));
        *returnColumnSizes = realloc(*returnColumnSizes, capacity * sizeof(int));
    }
    result[*returnSize] = result_col;
    (*returnColumnSizes)[*returnSize] = col_size;
    *returnSize += 1;

    hashFree(&strs_hash);

    return result;
}
// @leet end
