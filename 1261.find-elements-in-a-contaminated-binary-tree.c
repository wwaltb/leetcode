#include "include/binarytree.h"
#include "include/uthash.h"

// @leet start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct HashEntry {
    int id;
    UT_hash_handle hh;
};

void __hashAddValue(struct HashEntry** values, int val)
{
    struct HashEntry* ent = malloc(sizeof(struct HashEntry));
    ent->id = val;
    HASH_ADD_INT(*values, id, ent);
}

void __hashDeleteValue(struct HashEntry** values, struct HashEntry* ent)
{
    HASH_DEL(*values, ent);
    free(ent);
}

typedef struct {
    struct TreeNode* root;
    struct HashEntry* values;
} FindElements;

/**
 * root has value 0, left nodes have value 2 * x + 1 and right nodes have
 * value 2 * x + 2
 *
 * recover the corrupted tree according to above rules and store the values in
 * the hash map
 */
void __findElementsRecoverAndHash(struct TreeNode* node, struct HashEntry** values)
{
    int x = node->val;
    __hashAddValue(values, x);
    if (node->left) {
        node->left->val = 2 * x + 1;
        __findElementsRecoverAndHash(node->left, values);
    }
    if (node->right) {
        node->right->val = 2 * x + 2;
        __findElementsRecoverAndHash(node->right, values);
    }
}

/**
 * Initializes obj with a contaminated tree and recovers it
 */
FindElements* findElementsCreate(struct TreeNode* root)
{
    FindElements* new = malloc(sizeof(FindElements));

    new->root = root;
    new->root->val = 0;
    new->values = NULL;
    __findElementsRecoverAndHash(new->root, &new->values);

    return new;
}

int findElementsFind(FindElements* obj, int target)
{
    struct HashEntry* ent;
    HASH_FIND_INT(obj->values, &target, ent);
    if (ent) {
        return 1;
    }

    return 0;
}

void findElementsFree(FindElements* obj)
{
    struct HashEntry *ent, *temp;
    HASH_ITER(hh, obj->values, ent, temp)
    {
        __hashDeleteValue(&obj->values, ent);
    }
    free(obj);
}

/**
 * Your FindElements struct will be instantiated and called as such:
 * FindElements* obj = findElementsCreate(root);
 * bool param_1 = findElementsFind(obj, target);

 * findElementsFree(obj);
*/
// @leet end
