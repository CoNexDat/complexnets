// This toolbox is licensed under the Academic Free License 3.0.
// Instituto Tecnológico de Buenos Aires (ITBA).
// Last modification: December 16th, 2015.

#ifndef MOLLOYREEDGRAPHREADER_H
#define MOLLOYREEDGRAPHREADER_H

#include <math.h>
#include <fstream>
#include <iostream>
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

template <class Graph, class Vertex>
class MolloyReedGraphReader : public IGraphReader<Graph, Vertex>
{
public:
    std::vector<unsigned int> vertexesFutureDegrees;

    typedef std::string FileName;
    typedef unsigned int LineNumber;
    typedef typename Vertex::VerticesIterator NeighborsIterator;

    virtual void read(Graph& graph, std::string source)
    {
        std::map<unsigned int, unsigned int> k;
        unsigned int degree, amount;
        std::ifstream sourceFile;
        sourceFile.open(source.c_str(), std::ios_base::in);

        if (!sourceFile)
            throw FileNotFoundException(source);

        std::string line;
        currentLineNumber = 1;
        while (getline(sourceFile, line))
        {
            std::string tree_str = line;
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
    void Print(const std::vector<unsigned int>& vec)
    {
        for (auto& v : vec)
            std::cout << v << std::endl;
    }

    void printSet(const std::set<unsigned int>& set)
    {
        for (auto& v : set)
            std::cout << v << std::endl;
    }

    void molloyReedAlgorithm(Graph& graph, std::map<unsigned int, unsigned int> k)
    {
        int totalNodes = 0;
        int freeDegrees = 0;
        bool vertexesWithOneFreeDegreeFull = false;
        std::set<unsigned int> nodesSet;
        std::map<unsigned int, unsigned int> vertexesIdsDegrees;
        std::map<unsigned int, std::set<unsigned int>> nodesNotConnectedTo;
        std::vector<unsigned int> unconectedVertexesIds;
        std::vector<unsigned int> unconectedVertexesOneDegreeIds;
        std::vector<unsigned int> vertexesWithOneFreeDegree;
        std::vector<unsigned int> vertexesWithFreeDegrees;
        std::vector<unsigned int> vertexesWitNoFreeDegrees;
        std::vector<unsigned int> vertexesInTheGraph;
        unsigned int id = 0;
        unsigned int maxDegreeId = 0;
        unsigned int maxDegreeQuant = 0;

        std::map<unsigned int, unsigned int>::iterator it;

        unsigned int maxIndex = 0;
        unsigned int maxIndexOneDegree = 0;
        unsigned int maxDegreeIndex = 0;
        for (it = k.begin(); it != k.end(); it++)
        {
            std::cout << "key: " << it->first << " value: " << it->second << "\n";
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
            std::set<unsigned int> newNodeSet = nodesSet;
            newNodeSet.erase(i);
            nodesNotConnectedTo[i] = newNodeSet;
        }
        std::cout << "maxDegreeQuant: " << maxDegreeQuant << std::endl;
        totalNodes = id;
        freeDegrees = maxDegreeQuant;
        if (freeDegrees == 1)
        {
            vertexesWithOneFreeDegree.push_back(maxDegreeId);
            unconectedVertexesOneDegreeIds.erase(
                unconectedVertexesOneDegreeIds.begin() + maxDegreeIndex);
        }
        else
        {
            vertexesWithFreeDegrees.push_back(maxDegreeId);
            unconectedVertexesIds.erase(unconectedVertexesIds.begin() + maxDegreeIndex);
        }
        vertexesInTheGraph.push_back(maxDegreeId);

        Vertex* firstVertex = new Vertex(maxDegreeId);
        graph.addVertex(firstVertex);

        std::cout << "maxDegreeId: " << maxDegreeId << std::endl;
        std::cout << "maxDegreeQuant: " << maxDegreeQuant << std::endl;
        std::cout << "unconectedVertexesIds:" << std::endl;
        Print(unconectedVertexesIds);
        std::cout << "unconectedVertexesOneDegreeIds:" << std::endl;
        Print(unconectedVertexesOneDegreeIds);

        std::cout << "StartAlgorithm: \n\n";

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
                unconectedVertexesOneDegreeIds.erase(
                    unconectedVertexesOneDegreeIds.begin() + index_new);
            }

            std::cout << "unconected is empty?: " << unconectedVertexesIds.empty() << "\n";
            std::cout << "unconectedSize: " << unconectedSize << "\n";
            std::cout << "nodeFromIndex: " << index_new << "\n";
            std::cout << "nodeFromId: " << nextVertexId << "\n";
            std::cout << "nodeFromDegree: " << nextVertexDegree << "\n";

            if (nextVertexDegree != 0)
            {
                vertexesIdsDegrees[nextVertexId] = nextVertexDegree - 1;
                size_t noFreeAndOneFreeSize =
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

                std::cout << "nodeToIndex: " << index << "\n";
                std::cout << "nodeToId: " << selectedId << "\n";
                std::cout << "nodeToDegree: " << vertexesIdsDegrees[selectedId] << "\n";

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

        std::cout << "####################### Begin rewire! #######################: \n\n";
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
            std::cout << "fromFreeDegrees: " << fromFreeDegrees << "\n";
            std::cout << "selectedId: " << selectedId << "\n";
            std::cout << "selectedDegrees: " << selectedDegrees << "\n";
            std::cout << "nodesNotConnectedTo: "
                      << "\n";

            std::set<unsigned int> unconectedVertexes = nodesNotConnectedTo[selectedId];
            std::set<unsigned int>::const_iterator it(nodesNotConnectedTo[selectedId].begin());

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
                        vertexesWithOneFreeDegree.erase(
                            vertexesWithOneFreeDegree.begin() + index_new);
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
    void printVertexVector(Graph& graph, std::vector<unsigned int> vec)
    {
        Vertex* v;
        for (unsigned int i = 0; i < vec.size(); i++)
        {
            v = graph.getVertexById(vec[i]);
            std::cout << "The vertex " << vec[i] << " has " << v->degree() << " neighbours\n";
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
        while (*character == ' ' || *character == '\t')
            ++character;
    }

    LineNumber currentLineNumber;
    const char* character;
};
}

#endif
