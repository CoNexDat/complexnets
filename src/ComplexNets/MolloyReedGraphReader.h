// This toolbox is licensed under the Academic Free License 3.0.
// Instituto Tecnológico de Buenos Aires (ITBA).
// Last modification: December 16th, 2015.

#ifndef MOLLOYREEDGRAPHREADER_H
#define MOLLOYREEDGRAPHREADER_H

#include <math.h>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include "IGraphReader.h"

namespace graphpp
{
struct pair_hash
{
    inline std::size_t operator()(const std::pair<int, int>& v) const
    {
        return v.first * 31 + v.second;
    }
};

using namespace std;

template <class Graph, class Vertex>
class MolloyReedGraphReader : public IGraphReader<Graph, Vertex>
{
public:
    vector<unsigned int> vertexesFutureDegrees;

    typedef string FileName;
    typedef unsigned int LineNumber;
    typedef typename Vertex::VerticesIterator NeighborsIterator;

    virtual void read(Graph& graph, string source)
    {
        map<unsigned int, unsigned int> k;
        unsigned int degree, amount;
        ifstream sourceFile;
        sourceFile.open(source.c_str(), ios_base::in);

        if (!sourceFile)
            throw FileNotFoundException(source);

        string line;
        currentLineNumber = 1;
        while (getline(sourceFile, line))
        {
            string tree_str = line;
            character = tree_str.c_str();
            if (!isEmptyLine())
            {
                degree = readUnsignedInt();
                consume_whitespace();
                amount = readUnsignedInt();
                k[degree] = amount;
                consume_whitespace();
            }
            ++currentLineNumber;
        }

        sourceFile.close();

        molloyReedAlgorithm(graph, k);
    }

    LineNumber getLineNumber() const
    {
        return currentLineNumber;
    }

private:
    void Print(const vector<unsigned int>& v)
    {
        for (int i = 0; i < v.size(); i++)
        {
            cout << v[i] << endl;
        }
    }

    void printSet(const set<unsigned int>& s)
    {
        set<unsigned int>::const_iterator it = s.begin();
        for (; it != s.end(); it++)
        {
            cout << *it << endl;
        }
    }

    void molloyReedAlgorithm(Graph& graph, map<unsigned int, unsigned int> k)
    {
        int totalNodes = 0;
        int freeDegrees = 0;
        bool vertexesWithOneFreeDegreeFull = false;
        set<unsigned int> nodesSet;
        map<unsigned int, unsigned int> vertexesIdsDegrees;
        map<unsigned int, set<unsigned int>> nodesNotConnectedTo;
        vector<unsigned int> unconectedVertexesIds;
        vector<unsigned int> unconectedVertexesOneDegreeIds;
        vector<unsigned int> vertexesWithOneFreeDegree;
        vector<unsigned int> vertexesWithFreeDegrees;
        vector<unsigned int> vertexesWitNoFreeDegrees;
        vector<unsigned int> vertexesInTheGraph;
        unsigned int id = 0;
        unsigned int maxDegreeId = 0;
        unsigned int maxDegreeQuant = 0;

        map<unsigned int, unsigned int>::iterator it;

        unsigned int maxIndex = 0;
        unsigned int maxIndexOneDegree = 0;
        unsigned int maxDegreeIndex = 0;
        for (it = k.begin(); it != k.end(); it++)
        {
            cout << "key: " << it->first << " value: " << it->second << "\n";
            unsigned int quantityOfVertexes = it->second;
            unsigned int degrees = it->first;
            if (maxDegreeQuant < degrees)
            {
                if (degrees > 1)
                {
                    maxDegreeIndex = maxIndex;
                }
                else
                {
                    maxDegreeIndex = maxIndexOneDegree;
                }
                maxDegreeQuant = degrees;
                maxDegreeId = id;
            }
            for (unsigned int i = 0; i < quantityOfVertexes; i++)
            {
                vertexesIdsDegrees[id] = degrees;
                if (degrees == 1)
                {
                    unconectedVertexesOneDegreeIds.push_back(id);
                    maxIndexOneDegree++;
                }
                else
                {
                    unconectedVertexesIds.push_back(id);
                    maxIndex++;
                }
                nodesSet.insert(id);
                id++;
            }
        }

        for (int i = 0; i < id; i++)
        {
            set<unsigned int> newNodeSet = nodesSet;
            newNodeSet.erase(i);
            nodesNotConnectedTo[i] = newNodeSet;
        }
        cout << "maxDegreeQuant: " << maxDegreeQuant << "\n";
        totalNodes = id;
        freeDegrees = maxDegreeQuant;
        if (freeDegrees == 1)
        {
            vertexesWithOneFreeDegree.push_back(maxDegreeId);
            unconectedVertexesOneDegreeIds.erase(unconectedVertexesOneDegreeIds.begin() +
                                                 maxDegreeIndex);
        }
        else
        {
            vertexesWithFreeDegrees.push_back(maxDegreeId);
            unconectedVertexesIds.erase(unconectedVertexesIds.begin() + maxDegreeIndex);
        }
        cout << "asd1"
             << "\n";
        vertexesInTheGraph.push_back(maxDegreeId);

        Vertex* firstVertex = new Vertex(maxDegreeId);
        graph.addVertex(firstVertex);

        cout << "maxDegreeId: " << maxDegreeId << "\n";
        cout << "maxDegreeQuant: " << maxDegreeQuant << "\n";
        cout << "unconectedVertexesIds: \n";
        Print(unconectedVertexesIds);
        cout << "unconectedVertexesOneDegreeIds: \n";
        Print(unconectedVertexesOneDegreeIds);

        cout << "StartAlgorithm: \n\n";

        while (!unconectedVertexesIds.empty() || !unconectedVertexesOneDegreeIds.empty())
        {
            // cout << "unconectedVertexesIds: \n";
            // Print(unconectedVertexesIds);
            // cout << "unconectedVertexesOneDegreeIds: \n";
            // Print(unconectedVertexesOneDegreeIds);

            int unconectedSize;
            unsigned int nextVertexId;
            unsigned int nextVertexDegree;

            int index_new;
            if (!unconectedVertexesIds.empty())
            {
                unconectedSize = unconectedVertexesIds.size();
                index_new = rand() % unconectedSize;
                nextVertexId = unconectedVertexesIds[index_new];
                nextVertexDegree = vertexesIdsDegrees[nextVertexId];
                unconectedVertexesIds.erase(unconectedVertexesIds.begin() + index_new);
            }
            else
            {
                unconectedSize = unconectedVertexesOneDegreeIds.size();
                index_new = rand() % unconectedSize;
                nextVertexId = unconectedVertexesOneDegreeIds[index_new];
                nextVertexDegree = vertexesIdsDegrees[nextVertexId];
                unconectedVertexesOneDegreeIds.erase(unconectedVertexesOneDegreeIds.begin() +
                                                     index_new);
            }

            cout << "unconected is empty?: " << unconectedVertexesIds.empty() << "\n";
            cout << "unconectedSize: " << unconectedSize << "\n";
            cout << "nodeFromIndex: " << index_new << "\n";
            cout << "nodeFromId: " << nextVertexId << "\n";
            cout << "nodeFromDegree: " << nextVertexDegree << "\n";
            if (nextVertexDegree != 0)
            {
                vertexesIdsDegrees[nextVertexId] = nextVertexDegree - 1;
                int noFreeAndOneFreeSize =
                    vertexesWithOneFreeDegree.size() + vertexesWitNoFreeDegrees.size();
                if (noFreeAndOneFreeSize == vertexesInTheGraph.size())
                {
                    vertexesWithOneFreeDegreeFull = true;
                }

                unsigned int selectedId;
                int size;
                int index;
                if (vertexesWithOneFreeDegreeFull)
                {
                    size = vertexesWithOneFreeDegree.size();
                    if (size == 0)
                    {
                        break;
                    }
                    index = rand() % size;
                    selectedId = vertexesWithOneFreeDegree[index];
                }
                else
                {
                    size = vertexesWithFreeDegrees.size();
                    index = rand() % size;
                    selectedId = vertexesWithFreeDegrees[index];
                }
                cout << "nodeToIndex: " << index << "\n";
                cout << "nodeToId: " << selectedId << "\n";
                cout << "nodeToDegree: " << vertexesIdsDegrees[selectedId] << "\n";

                if (vertexesIdsDegrees[selectedId] == 0)
                {
                    vertexesWithOneFreeDegree.erase(vertexesWithOneFreeDegree.begin() + index);
                    vertexesWitNoFreeDegrees.push_back(selectedId);
                }
                else
                {
                    int degreesLeft = vertexesIdsDegrees[selectedId] - 1;
                    vertexesIdsDegrees[selectedId] = degreesLeft;
                    if (degreesLeft == 1)
                    {
                        vertexesWithFreeDegrees.erase(vertexesWithFreeDegrees.begin() + index);
                        vertexesWithOneFreeDegree.push_back(selectedId);
                    }
                    else if (degreesLeft == 0)
                    {
                        vertexesWithOneFreeDegree.erase(vertexesWithOneFreeDegree.begin() + index);
                        vertexesWitNoFreeDegrees.push_back(selectedId);
                    }
                    // cout << "vertexesWithFreeDegrees: \n";
                    // Print(vertexesWithFreeDegrees);
                    // cout << "vertexesWithOneFreeDegree: \n";
                    // Print(vertexesWithOneFreeDegree);
                    Vertex* existentVertex = graph.getVertexById(selectedId);
                    Vertex* newVertex = new Vertex(nextVertexId);
                    graph.addVertex(newVertex);
                    graph.addEdge(existentVertex, newVertex);

                    vertexesInTheGraph.push_back(nextVertexId);
                    nodesNotConnectedTo[selectedId].erase(nextVertexId);
                    nodesNotConnectedTo[nextVertexId].erase(selectedId);

                    if (nextVertexDegree - 1 == 0)
                    {
                        vertexesWitNoFreeDegrees.push_back(nextVertexId);
                    }
                    else if (nextVertexDegree - 1 == 1)
                    {
                        vertexesWithOneFreeDegree.push_back(nextVertexId);
                    }
                    else
                    {
                        vertexesWithFreeDegrees.push_back(nextVertexId);
                        vertexesWithOneFreeDegreeFull = false;
                    }
                }
            }
            // printVertexVector(graph, vertexesInTheGraph);
        }

        cout << "####################### Begin rewire! #######################: \n\n";
        while (!vertexesWithFreeDegrees.empty() || !vertexesWithOneFreeDegree.empty())
        {
            unsigned int index_new;
            unsigned int selectedId;
            unsigned int selectedDegrees;
            bool fromFreeDegrees;
            if (!vertexesWithFreeDegrees.empty())
            {
                index_new = rand() % vertexesWithFreeDegrees.size();
                selectedId = vertexesWithFreeDegrees[index_new];
                selectedDegrees = vertexesIdsDegrees[selectedId];
                fromFreeDegrees = true;
            }
            else
            {
                index_new = rand() % vertexesWithOneFreeDegree.size();
                selectedId = vertexesWithOneFreeDegree[index_new];
                selectedDegrees = vertexesIdsDegrees[selectedId];
                fromFreeDegrees = false;
            }
            cout << "fromFreeDegrees: " << fromFreeDegrees << "\n";
            cout << "selectedId: " << selectedId << "\n";
            cout << "selectedDegrees: " << selectedDegrees << "\n";
            cout << "nodesNotConnectedTo: "
                 << "\n";

            set<unsigned int> unconectedVertexes = nodesNotConnectedTo[selectedId];
            set<unsigned int>::const_iterator it(nodesNotConnectedTo[selectedId].begin());

            // printSet(unconectedVertexes);
            if (!unconectedVertexes.empty() && selectedDegrees != 0)
            {
                unsigned int willConnectIndex = rand() % unconectedVertexes.size();
                advance(it, willConnectIndex);
                unsigned int willConnect = *it;
                unsigned int willConnectDegrees = vertexesIdsDegrees[willConnect];
                if (willConnectDegrees != 0)
                {
                    if (fromFreeDegrees)
                    {
                        vertexesWithFreeDegrees.erase(vertexesWithFreeDegrees.begin() + index_new);
                    }
                    else
                    {
                        vertexesWithOneFreeDegree.erase(vertexesWithOneFreeDegree.begin() +
                                                        index_new);
                    }

                    if (selectedDegrees - 1 == 1)
                    {
                        vertexesWithOneFreeDegree.push_back(selectedId);
                    }
                    else if (selectedDegrees - 1 == 0)
                    {
                        vertexesWitNoFreeDegrees.push_back(selectedId);
                    }
                    vertexesIdsDegrees[selectedId] = selectedDegrees - 1;
                    vertexesIdsDegrees[willConnect] = willConnectDegrees - 1;
                    Vertex* existentVertexFrom = graph.getVertexById(selectedId);
                    Vertex* existentVertexTo = graph.getVertexById(willConnect);
                    graph.addEdge(existentVertexFrom, existentVertexTo);
                    nodesNotConnectedTo[selectedId].erase(willConnect);
                    nodesNotConnectedTo[willConnect].erase(selectedId);
                }
                else
                {
                    nodesNotConnectedTo[selectedId].erase(willConnect);
                }
            }
            else
            {
                nodesNotConnectedTo.erase(selectedId);
                if (fromFreeDegrees)
                {
                    vertexesWithFreeDegrees.erase(vertexesWithFreeDegrees.begin() + index_new);
                }
                else
                {
                    vertexesWithOneFreeDegree.erase(vertexesWithOneFreeDegree.begin() + index_new);
                }
                vertexesIdsDegrees[selectedId] = 0;
            }
            // printVertexVector(graph, vertexesInTheGraph);
        }
    }

    // Given a vector with node ids, print for each one it's id, actual degree and free degrees.
    void printVertexVector(Graph& graph, vector<unsigned int> vec)
    {
        Vertex* v;
        for (unsigned int i = 0; i < vec.size(); i++)
        {
            v = graph.getVertexById(vec[i]);
            cout << "The vertex " << vec[i] << " has " << v->degree() << " neighbours\n";
        }
    }

    int openDegrees(Vertex* vertex)
    {
        return vertexesFutureDegrees[vertex->getVertexId() - 1] - vertex->degree();
    }

    std::string getLineNumberText() const
    {
        std::stringstream s;
        s << "Line: " << currentLineNumber;
        return s.str();
    }

    unsigned int readUnsignedInt()
    {
        unsigned int ret = 0;
        if (!in_range(*character, '0', '9'))
            throw UnsignedIntegerMalformedException(getLineNumberText());
        else
        {
            std::string branchLenStr;
            while (in_range(*character, '0', '9'))
            {
                branchLenStr += *character;
                ++character;
            }

            if (!from_string<unsigned int>(branchLenStr, ret))
                throw UnsignedIntegerMalformedException(getLineNumberText());
        }
        return ret;
    }

    bool isEmptyLine()
    {
        bool ret = false;
        consume_whitespace();
        if (*character == '\0')
            ret = true;
        return ret;
    }

    void consume_whitespace()
    {
        while (*character == ' ' || *character == '\t') ++character;
    }

    LineNumber currentLineNumber;
    const char* character;
};
}

#endif
