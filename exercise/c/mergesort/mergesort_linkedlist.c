#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    int key;
    struct Node *next;
}Node;

Node * half_list(Node * head)
{
    Node *p1, *p2, *prev;
    p1=head;
    prev=head;
    p2=head;
    while (p2)
    {
        if (p2->next)
        {
            p2=p2->next->next;
            prev=p1;
            p1=p1->next;
        }
        else
            p2=p2->next;
    }
    return prev;
}

Node* mergesort(Node *p)
{

    Node *p1, *p2, *head, *bak, *pp2;

    if (!p || !(p->next))
        return p;
    
    p1=p;
    p2=half_list(p);
    pp2=NULL;
    if (p2)
    {
        pp2=p2->next;
        p2->next=NULL;
    }
    
    p1=mergesort(p1);
    p2=mergesort(pp2);
    
    if (!p1)
        return p2;
    if (!p2)
        return p1;
    head = NULL;
    bak = NULL;
    while (p1 && p2)
    {
        if (p1->key <= p2->key)
        {
            if (head)
                head->next = p1;
            head=p1;
            p1=p1->next;
        }
        else
        {
            if (head)
                head->next = p2;
            head=p2;
            p2=p2->next;
        }
        if (!bak)
            bak=head;
    }
    if (p1)
        head->next=p1;
    else
        head->next=p2;
    return bak;
}

int main( int argc, char **argv)
{

    int n,i;
    Node **head, *prev;
    *head=NULL;
    scanf("%d", &n);
    prev=NULL;
    for (i=0; i<n; i++)
    {
        Node * newNode=(Node *)malloc(sizeof(Node));
        scanf("%d", &newNode->key);
        newNode->next=NULL;
        if (*head==NULL)
            *head=newNode;
        if (prev)
            prev->next=newNode;
        prev=newNode;
    }

    prev=mergesort(*head);
    while (prev)
    {
        printf("%d ", prev->key);
        prev=prev->next;
    }
    
}
