#include <stdlib.h>

// @leet start
int cmp(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
    int capacity = 4;
    int** result = malloc(capacity * sizeof(int*));
    *returnColumnSizes = malloc(capacity * sizeof(int));
    *returnSize = 0;

    qsort(nums, numsSize, sizeof(int), cmp);

    int i, j, k;
    for (i = 0; i < numsSize && nums[i] <= 0; i++) {
        // skip duplicate numbers
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }
        // search for solutions by moving two pointers
        j = i + 1;
        k = numsSize - 1;
        while (j < k) {
            int sum = nums[i] + nums[j] + nums[k];
            if (sum < 0) {
                // update j, skipping past duplicates
                do {
                    j++;
                } while (j < k && nums[j] == nums[j - 1]);
            } else if (sum > 0) {
                // update k, skipping past duplicates
                do {
                    k--;
                } while (j < k && nums[k] == nums[k + 1]);
            } else {
                // resize arrays if needed
                if (*returnSize == capacity) {
                    capacity *= 2;
                    result = realloc(result, capacity * sizeof(int*));
                    *returnColumnSizes = realloc(*returnColumnSizes, capacity * sizeof(int));
                }

                // insert solution array
                result[*returnSize] = malloc(3 * sizeof(int));
                result[*returnSize][0] = nums[i];
                result[*returnSize][1] = nums[j];
                result[*returnSize][2] = nums[k];
                // update return sizes
                (*returnColumnSizes)[*returnSize] = 3;
                (*returnSize)++;

                // update j and k, skipping past duplicates
                do {
                    j++;
                } while (j < k && nums[j] == nums[j - 1]);
                do {
                    k--;
                } while (j < k && nums[k] == nums[k + 1]);
            }
        }
    }

    return result;
}
// @leet end
