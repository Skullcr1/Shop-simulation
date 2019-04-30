#include <stdio.h>
#include <stdlib.h>
#include "header.h"


/** Deque - function file.
 * addFront- adds data at the beggining of deque. PARAMETERS - 
 * addEnd- adds data at the end of deque
 * delFront - removes data from beggining
 * delRear - removes data from rear
 * removeDeque - removes everything from deque
 * printDeque - prints every element
 * firstElement - gets first element
 * lastElement - gets last element
 * 
 * 
*/

int isInitialized = 0; //for deque checking

struct Node* initializeDeque()
{
    
    isInitialized = 1;
    return NULL;
}

int isDequeEmpty(struct Node **head_ref)
{
    if(isInitialized == 0) return 1;
    if(*head_ref == NULL)           //checking if there is no node
    {
        printf("empty deque\n");
        return 2;
    }
    printf("not empty deque\n");
    return 0;
}

int isDequeFull()
{
    if(isInitialized == 0) return 1;
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    if(new_node == NULL)
        {
            printf("deque is full\n");
            return 0;
        }

    printf("deque is not full\n");        
    free(new_node);
    return 0;
}

int addFront(struct Node** head_ref, int new_data) // adds a new node at the beggining 
{  
    if(isInitialized == 0) return 1;
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node)); /* allocate node */

    new_node->data = new_data; /* put in the data  */
    new_node->previous = NULL; 
    new_node->next = (*head_ref);  /* make next of new node as head */
    (*head_ref) = new_node;  /* make next of new node as head */

    return 0;
    } 
  
int addRear(struct Node** head_ref, int new_data) //adds at end
{ 
    if(isInitialized == 0) return 1;
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node)); 
    struct Node *tail = *head_ref;  
    
    new_node->data  = new_data; 
    new_node->next = NULL; /* new node is going to be the last node, so make next of it as NULL */
    if (*head_ref == NULL) /* if the deque is empty, then make the new node as head */
    { 
       *head_ref = new_node; 
       return 0; 
    } 
    while (tail->next != NULL) tail = tail->next;  //traverse till the end
    tail ->next = new_node; // add new node to the last node
    new_node ->previous = tail; // attach previous with new node
    return 0; 
    } 

int delFront(struct Node **head_ref) //deletes front node
{
    if(isInitialized == 0) return 1;
    struct Node *current = *head_ref;

    if(current == NULL) return 1;
    *head_ref = current->next;    //2nd node - head 
    free(current);                //deleting 1st node
    return 0;
    }   

int delRear(struct Node **head_ref) //deletes last node
{
    struct Node *current = *head_ref;
    struct Node *last = *head_ref;
    struct Node *check = *head_ref;
   
    if(isInitialized == 0) return 1;
    if(*head_ref == NULL)           //checking if there is no node
    {
        return 1;
    }
    while(current ->next !=NULL)    //traversing to the end of deque
    {
        last = current;
        current = current ->next;
        current ->previous = check;
    } 
    if(current == *head_ref)        //if current is last one we make head NULL and delete node
    {
        *head_ref = NULL;
        free(current);
        return 1;
    }
    last ->next = NULL;             //last node loses connection with previous
    free(current);
    return 0;
        }

int removeDeque(struct Node **head_ref) //deletes everything (starting at beggining)
{
    if(isInitialized == 0) return 1;
    struct Node *current = *head_ref;
    struct Node *next; 

    while (current != NULL)        //traversing and deleting nodes
    { 
        next = current->next;   //
        free(current); 
        current->previous = NULL;
        current = next; 
    } 
    *head_ref = NULL;               //if there's everything already deleted we point head to NULL
    isInitialized = 0;
    printf("Deque is destroyed \n");
    return 0;
        } 

int printDeque(struct Node *head_ref) //function to print deque elements (to check correctness)
{ 
    if(isInitialized == 0) return 1;
    struct Node *temp;
    temp = head_ref;
    while(temp != NULL)
    {
        printf("%d\n", temp->data); 
        temp = temp->next;                
    }
    } 

int firstElement(struct Node *head_ref) //function to print deque elements (to check correctness)
{ 
    if(isInitialized == 0) return 1;
    struct Node *temp;
    temp = head_ref;
    if(temp != NULL)
    {
        printf("%d\n", temp->data); 
        temp = temp->next;                 
    }
    return 0;
    } 

int lastElement(struct Node *head_ref) //function to print deque elements (to check correctness)
{ 
    if(isInitialized == 0) return 1;
    struct Node *temp;
    temp = head_ref;
    if(temp == NULL) return 1;
    while(temp ->next != NULL) temp = temp ->next;
    printf("%d\n", temp->data); 
    } 