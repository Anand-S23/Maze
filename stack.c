#include "stack.h"

// makes a new node using malloc
node* CreateNode(int data, node* next)
{
    node* ret_node = (node *)malloc(sizeof(node));
    ret_node->data = data;
    ret_node->next = next;
    return ret_node;
}

// makes a new list with head of {0, NULL}
linked_list CreateList()
{
    linked_list ret_list;
    ret_list.head = CreateNode(0, NULL);
    return ret_list; 
} 

void Push(linked_list list, int data)
{
    node* in_node = CreateNode(data, NULL);

    in_node->next = list.head->next;
    list.head->next = in_node;
}

int Pop(linked_list list)
{
    int data = list.head->next->data;
    node *temp = list.head->next;
    list.head->next = list.head->next->next;
    free(temp);
    return data;
}
    
int Top(linked_list list)
{
    return list.head->next->data;
}

int Empty(linked_list list)
{
    return list.head->next == NULL;
}