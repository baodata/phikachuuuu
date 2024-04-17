#pragma once
#include "utility.h"

typedef struct node* Ref;
struct node 
{
	tile key;
	Ref next;
};

Ref getNode(tile k);
void insertNode(Ref& head, tile poke);
Ref* convert2LinkedList(tile** table, int x, int y);
void displayList(Ref head);