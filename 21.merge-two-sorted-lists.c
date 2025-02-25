#include "linkedlist.h"
#include <stdlib.h>

// @leet start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2)
{
    struct ListNode *head = NULL, *curr = NULL, *temp = NULL;
    while (list1) {
        // decide which value is next and insert it into ret list
        if (list2 == NULL || list1->val < list2->val) {
            temp = list1->next;
            list1->next = NULL;
            if (!head) {
                head = list1;
                curr = head;
            } else {
                curr->next = list1;
                curr = curr->next;
            }
            list1 = temp;
        } else {
            temp = list2->next;
            list2->next = NULL;
            if (!head) {
                head = list2;
                curr = head;
            } else {
                curr->next = list2;
                curr = curr->next;
            }
            list2 = temp;
        }
    }
    // can only be list2 values now, so append it to the ret list
    if (head == NULL) {
        head = list2;
    } else {
        curr->next = list2;
    }
    // return the head of the list
    return head;
}
// @leet end
