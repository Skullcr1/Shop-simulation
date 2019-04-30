#ifndef HEADER_H
#define HEADER_H

// void create_empty_deque();
struct Node 
{ 
  int data; 
  struct Node *next;
  struct Node *previous; 
}; 

int firstElement(struct Node *head_ref);
int lastElement(struct Node *head_ref);
int addFront(struct Node** head_ref, int new_data);
int addRear(struct Node** head_ref, int new_data);
int delFront(struct Node **head_ref);
int delRear(struct Node **head_ref);
int removeDeque(struct Node **head_ref);
int isDequeFull();
int isDequeEmpty(struct Node **head_ref);
int printDeque(struct Node *head_ref);
struct Node *initializeDeque();

#endif