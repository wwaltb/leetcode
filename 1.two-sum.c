#include "include/binarytree.h"
#include "include/uthash.h"

// @leet start
struct HashEntry {
    int num;
    int index;
    UT_hash_handle hh;
};

struct HashEntry* numsHash = NULL;

void hashAdd(int num, int index)
{
    struct HashEntry* ent = malloc(sizeof(struct HashEntry));
    ent->num = num;
    ent->index = index;
    HASH_ADD_INT(numsHash, num, ent);
}

void hashDeleteAll()
{
    struct HashEntry *ent, *tmp;
    HASH_ITER(hh, numsHash, ent, tmp)
    {
        HASH_DEL(numsHash, ent);
        free(ent);
    }
}

struct HashEntry* hashFind(int num)
{
    struct HashEntry* ent;
    HASH_FIND_INT(numsHash, &num, ent);
    if (ent) {
        return ent;
    }
    return NULL;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
    *returnSize = 2;
    int* result = malloc(*returnSize * sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        struct HashEntry* ent = hashFind(target - nums[i]);
        if (ent) {
            result[0] = ent->index;
            result[1] = i;
        }
        hashAdd(nums[i], i);
    }
    hashDeleteAll();
    return result;
}
// @leet end
