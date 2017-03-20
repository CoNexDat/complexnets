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
    bool debug = false;

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
        std::ofstream outfile;
        if (debug)
        {
            outfile.open("log.txt", std::ios_base::app);
            outfile << "Inserting: " << newNode->vertex->getVertexId() << "("
                    << newNode->currentDegree << ") \n";
            Node* it = head;
            while (it != nullptr)
            {
                outfile << it->vertex->getVertexId() << "(" << it->currentDegree << ") ";
                it = it->next;
            }
            outfile << "\n";
        }

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
        if (debug)
        {
            outfile.flush();
            outfile.close();
        }
        return;
    }

    // Removes a node with O(1)
    void Remove(Node* n)
    {
        std::ofstream outfile;
        if (debug)
        {
            outfile.open("log.txt", std::ios_base::app);
            outfile << "Removing: " << n->vertex->getVertexId() << "(" << n->currentDegree
                    << ") \n";
            Node* it = head;
            while (it != nullptr)
            {
                outfile << it->vertex->getVertexId() << "(" << it->currentDegree << ") ";
                it = it->next;
            }
            outfile << "\n";
        }

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
        if (debug)
        {
            outfile.flush();
            outfile.close();
        }
    }
};
}
