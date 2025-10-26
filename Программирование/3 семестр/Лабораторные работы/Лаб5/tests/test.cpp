//
// Created by admin on 26.10.2025.
//
#include <stdio.h>
using namespace std;
const int MAXSIZE = 100;

struct Stack {
    char data[MAXSIZE];
    int size;
};

void Push(Stack &S, char x) {
    if (S.size == MAXSIZE) {
        printf("Стек переполнен");
        return;
    }
    S.data[S.size] = x;
    S.size++;
}

char Pop(Stack &S) {
    if (S.size == 0) {
        printf("Стек пуст");
        return char(255);
    }
    S.size--;
    return S.data[S.size];
}







struct Node {
    char data;
    Node *next,*prev;
};
typedef Node *PNode;

struct Stack {
Pnode Head,Tail;
};


void Push(Stack &S,char x) {
    Pnode NewNode;
    NewNode = new Node;
    NewNode->data=x;
    NewNode->next=S.Head;
    NewNode->prev=NULL;
    if (S.Head) {
        S.Head->prev=NewNode;}
    S.Head = NewNode;
    if (!S.Tail) S.Tail = S.Head;


}

char Pop(Stack &S) {
PNode TopNode = S.Head;
    char x;
    if (!TopNode) return char (255);
    x=TopNode->data;
    S.Head = TopNode->next;
    if (S.Head) S.Head ->prev = NULL;
    else S.Tail = NULL;
    delete TopNode;
    return x;



}




// Очереди

struct Queue {
int data[MAXSIZE];
    int size,head,tail;
    Queue():size(0),head(0),tail(-1){};
};


void pushQueue (Queue &Q,int x) {
    if (Q.size==MAXSIZE) {

        return;
    }
Q.tail++;
    if (Q.tail>=MAXSIZE) Q.tail = 0;
    Q.data[Q.tail]=x;
    Q.size++;
}

char removeQueue(Queue &Q) {
    int temp;
    if (Q.size==0) {
    return 32767; //error
    }
    temp=Q.data[Q.head];
    Q.head++;
    if (Q.head>=MAXSIZE) Q.head =0;
    Q.size--;
    return temp;
}














