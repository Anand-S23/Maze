#ifndef STACK_H
#define STACK_H

typedef struct node
{
    int data;
    struct node* next;
} node;

typedef struct linked_list
{
    node* head;
} linked_list;

node* CreateNode(int data, node *next);
linked_list CreateList(); 
void Push(linked_list list, int data);
int Pop(linked_list list);
int Top(linked_list list);
int Empty(linked_list list);

#endif