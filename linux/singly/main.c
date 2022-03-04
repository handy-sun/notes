#include "singlyLinkedList.h"
#include <stdio.h>
#include <stdlib.h>

int search_recursive(const int b[], int low, int high, int tar)
{
    if (low > high)
        return -1;

    int mid = low + (high - low) / 2;

    if (tar == b[mid])
        return mid;
    else if (tar < b[mid])
        return search_recursive(b, low, mid - 1, tar);
    else
        return search_recursive(b, mid + 1, high, tar);
}

int search(int* nums, int numsSize, int target)
{
    int left = 0;
    int right = numsSize - 1;
#ifdef RECURSIVE
    return search_recursive(nums, left, right, target);
#else
    int mid;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (nums[mid] == target)
            return mid;
        else if (nums[mid] < target)
            left += 1;
        else
            right -= 1;
    }
    return -1;
#endif
}

int main()
{
    int a[] = { 0, 1, 2, 3 };
	int len = sizeof(a) / sizeof(int);
	Node *testn = createList(a, len);
//    Node *n2 = insertNode(testn, 2, -4);
    Node *n2 = deleteNode(testn, 1);
//    printList(n2);
//	Node *nn = reverseList(testn);
//	printList(nn);

    int t[] = { -1, 0, 3, 5, 9, 12, 15};
    int len2 = sizeof(t) / sizeof(int);
    int x= search(t, len2, 4);
    printf("%d\n", x);
	return 0;
}
