#include <fstream>
#include <iostream>

#include "typedefs.h"

namespace graphpp
{
typedef struct Node
{
    Vertex* vertex;
    int currentDegree;
    Node* next;
    Node* prev;
} Node;

class Dllist
{
private:
    Node* head;
    Node* last;

public:
    Dllist()
    {
        head = nullptr;
        last = nullptr;
    }
    Node* getHead()
    {
        return head;
    }
    bool empty()
    {
        return head == nullptr;
    }
    int Size()
    {
        int i = 0;
        Node* curr = head;
        while (curr != nullptr)
        {
            curr = curr->next;
            i++;
        }
        return i;
    }

    // Inserts at the beginning with O(1)
    void Insert(Node* newNode)
    {
        // Insertion into an Empty List.
        if (empty())
        {
            head = newNode;
            last = newNode;
            newNode->prev = nullptr;
            newNode->next = nullptr;
            return;
        }

        // Inserting at the beggining
        newNode->prev = nullptr;
        newNode->next = head;
        head->prev = newNode;
        head = newNode;

        return;
    }

    // Removes a node with O(1)
    void Remove(Node* n)
    {
        if (n->prev != nullptr)
        {
            n->prev->next = n->next;
        }
        else
        {
            head = n->next;
        }
        if (n->next != nullptr)
        {
            n->next->prev = n->prev;
        }
        else
        {
            last = n->prev;
        }
    }
};
}
