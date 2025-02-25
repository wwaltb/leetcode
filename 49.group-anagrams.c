#include "uthash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// @leet start
int cmp_chars(const void* a, const void* b)
{
    return *(char*)a - *(char*)b;
}

int cmp_strlens(const void* a, const void* b)
{
    const char* str1 = *(const char**)a;
    const char* str2 = *(const char**)b;
    return (int)strlen(str1) - (int)strlen(str2);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes)
{
    qsort(strs, strsSize, sizeof(char*), cmp_strlens);
    int prev_len = 0;
    for (int i = 0; i < strsSize; i++) {
        int len = (int)strlen(strs[i]);
        if (len > prev_len) {
        }
        qsort(strs[i], len, sizeof(char), cmp_chars);
        printf("%s\n", strs[i]);
    }

    return NULL;
}
// @leet end
