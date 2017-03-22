#ifndef GRAPHREADER_H
#define GRAPHREADER_H

#include <fstream>
#include <iostream>
#include <string>
#include "GraphExceptions.h"
#include "IGraphReader.h"

namespace graphpp
{
template <class Graph, class Vertex>
class GraphReader : public IGraphReader<Graph, Vertex>
{
public:
    // this typedefs are also present in the superclass. Any way to remove it?
    typedef std::string FileName;
    typedef unsigned int LineNumber;
    virtual void read(Graph& g, std::string source)
    {
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
                consume_whitespace();
                Vertex* sourceNode = loadVertex(g);
                consume_whitespace();

                if (*character != '\0')
                {
                    Vertex* destinationNode = loadVertex(g);
                    consume_whitespace();
                    if (*character != '\0')
                        throw MalformedLineException(getLineNumberText());
                    try
                    {
                        g.addEdge(sourceNode, destinationNode);
                    }
                    catch (const DuplicateEdge& ex)
                    {
                        // throw DuplicatedEdgeLoading(getLineNumberText());
                    }
                }
            }

            ++currentLineNumber;
        }

        sourceFile.close();
    }

    LineNumber getLineNumber() const
    {
        return currentLineNumber;
    }

private:
    std::string getLineNumberText() const
    {
        std::stringstream s;
        s << "Line: " << currentLineNumber;
        return s.str();
    }

    Vertex* loadVertex(Graph& g)
    {
        Vertex* vertex = new Vertex(readUnsignedInt());
        Vertex* vertexAux = vertex;
        if ((vertex = g.getVertexById(vertex->getVertexId())) != nullptr)
            delete vertexAux;
        else
        {
            vertex = vertexAux;
            g.addVertex(vertex);
        }

        return vertex;
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

    // TODO this method should be const
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
