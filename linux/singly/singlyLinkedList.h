#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

//Definition for singly-linked list.
typedef struct ListNode
{
	int data;
	struct ListNode *next;
} Node;

Node *createList(int *arr, int arrLength);

struct SinglyLinkedList
{
	Node *m_list;
};
    // Node (*construture)(int *arr, int arrLength) = &createList;
Node *insertNode(Node *head, int n, int value);
Node *deleteNode(Node *head, int n);
	// Node *invertedDeleteNode(Node *head, int n);	//MySolution of LeetCode19 : (4ms, 8.4MB)
	// int searchNode(Node *head, int value);
	// void printList(Node *head);


void printList(Node* head);

Node *reverseList(Node* head);

#endif // SINGLY_LINKED_LIST_H
