#include <stdlib.h>
#include <stdio.h>
#include "singlyLinkedList.h"


// SinglyLinkedList::SinglyLinkedList(int *arr, int arrLength)
// {
// 	m_list = createList(arr, arrLength);			
// 	printList(m_list);
// }

// SinglyLinkedList::~SinglyLinkedList()
// {
// 	Node *bak;
// 	while (m_list->next != NULL)
// 	{
// 		bak = m_list;
// 		printf("值为 %x 的地址为: %x 此处内存将被释放\n", m_list->data, m_list);
// 		m_list = m_list->next;
// 		free(bak);
// 		bak = NULL;
// 	}
// 	printf("值为 %x 的地址为: %x 此处内存将被释放(尾节点)\n", m_list->data, m_list);
// 	free(m_list);
// 	m_list = NULL;
// }

Node* insertNode(Node *head, int n, int value)
{
    Node *temp = head;
    Node *pNew = (Node *)malloc(sizeof(Node));
    if (n == 0) {
        pNew->data = value;
        pNew->next = head;
        return pNew;
    }

    for (int i = 0; i < n - 1 && temp->next != NULL; i++) {
        temp = temp->next;
    }

    pNew->data = value;
    pNew->next = temp->next;
    temp->next = pNew;

    return head;
}

Node* deleteNode(Node *head, int n)
{
    Node *temp = head;
    Node *delNode;
    // head
    if (n == 0) {
        head = head->next;
        free(temp);
        temp = NULL;
        return head;
    }

    for (int i = 0; i < n - 1 && temp->next->next != NULL; i++) {
        temp = temp->next;
    }

    delNode = temp->next;
    temp->next = temp->next->next;

    free(delNode);
    delNode = NULL;
    return head;
}

// Node *SinglyLinkedList::invertedDeleteNode(Node *head, int n)
// {
// 	int length = 1;
// 	Node *bak = head;
// 	while (bak->next != NULL)
// 	{
// 		bak = bak->next;
// 		length++;
// 	}
// 	int seq = length + 1 - n;
// 	return deleteNode(head, seq);
// }

// int SinglyLinkedList::searchNode(Node *head, int value)
// {
// 	int sequence = 1;
// 	while (head->data != value)
// 	{
// 		head = head->next;
// 		sequence++;
// 	}
// 	return sequence;
// }

void printList(Node* head)
{
	while (head->next != NULL)
	{
		printf("%d (%p -> %p)\n", head->data, head, head->next);
		head = head->next;
	}
	printf("%d (%p -> %p)\n", head->data, head, head->next);
}

Node* createList(int *arr, int arrLength)
{
	//head->头节点, tail->尾节点, p->读取新值的节点
	Node *head, *tail, *p;
	head = (Node *)malloc(sizeof(Node));
	head->data = *arr;
	head->next = NULL;
	tail = head;

	for (int i = 1; i < arrLength; i++)
	{
		p = (Node *)malloc(sizeof(Node));
		p->data = arr[i];
		p->next = NULL; //注意不要使链表最后一节点next成野指针

		tail->next = p;
		tail = p;
	}
	return head;
}

Node* reverseList(Node* head) 
{
	Node *newList = NULL;
	Node *p;
	while (head)
	{
		p = head->next;
		head->next = newList;
		newList = head;
		head = p;
	}
	return newList;
}
