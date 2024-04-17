#include "linkedList.h"
#include "utility.h"
#include "render.h"
#include <iostream>
#include <ctime>

using namespace std;

Ref getNode(tile k)
{
    Ref p = new node;
    p->key = k;
    p->next = NULL;
    return p;
}

void insertNode(Ref& head, tile poke)
{
    Ref newNode = getNode(poke);
    if (head == nullptr) 
        head = newNode;
    else {
        Ref temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

Ref* convert2LinkedList(tile** table, int x, int y)
{
    Ref* headArray = new Ref [y];

    for (int i = 1; i <= y; i++) {
        Ref head = nullptr;
        Ref tail = nullptr;

        for (int j = 1; j <= x; j++) {
            tile value = table[i][j];
            Ref newNode = getNode(value);
            if (head == nullptr) 
            {
                head = newNode;
                tail = newNode;
            }
            else 
            {
                tail->next = newNode;
                tail = newNode;
            }
        }
        headArray[i] = head;
    }
    return headArray;
}

void displayList(Ref head) 
{
    Ref temp = head;
    while (temp != nullptr)
    {
        box(temp->key);
        temp = temp->next;
    }
}