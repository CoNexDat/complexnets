#ifndef SIMPLE_TEXT_GRAPH_READER_H
#define SIMPLE_TEXT_GRAPH_READER_H

#include <string>
#include <fstream>
#include <iostream>
#include "GraphReader.h"
#include "mili/mili.h"

class GraphLoadExceptionHierarchy {};

typedef GenericException<GraphLoadExceptionHierarchy> GraphLoadException;


DEFINE_SPECIFIC_EXCEPTION_TEXT(FileNotFoundException,
                               GraphLoadExceptionHierarchy,
                               "File not found.");

DEFINE_SPECIFIC_EXCEPTION_TEXT(UnsignedIntegerMalformedException,
                               GraphLoadExceptionHierarchy,
                               "The characters parsed are not a valid unsigned integer.");

DEFINE_SPECIFIC_EXCEPTION_TEXT(MalformedDoubleException,
                               GraphLoadExceptionHierarchy,
                               "The characters parsed are not a valid unsigned integer.");


namespace graphpp
{
typedef std::string FileName;
typedef unsigned int LineNumber;

template <class Graph, class Vertex>
class SimpleTextGraphReader : public GraphReader<Graph, Vertex, FileName>
{
public:

    virtual void read(Graph& g, const FileName& source)
    {
        std::ifstream sourceFile;

        sourceFile.open(source.c_str(), std::ios_base::in);

        if (!sourceFile)
            throw FileNotFoundException();

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
                    g.addEdge(sourceNode, destinationNode);
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

    Vertex* loadVertex(Graph& g)
    {
        Vertex* vertex = new Vertex(readUnsignedInt());
        Vertex* vertexAux = vertex;
        if ((vertex = g.getVertexById(vertex->getVertexId())) != NULL)
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
            throw UnsignedIntegerMalformedException();
        else
        {
            std::string branchLenStr;
            while (in_range(*character, '0', '9'))
            {
                branchLenStr += *character;
                ++character;
            }

            if (!from_string(branchLenStr, ret))
                throw UnsignedIntegerMalformedException();
        }
        return ret;
    }

    //TODO this method should be const
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

    double consume_weigth()
    {
        consume_whitespace();
        double ret = 0.0;
        std::string branchLenStr;
        while (in_range(*character, '0', '9') || *character == '.')
        {
            branchLenStr += *character;
            ++character;
        }

        if (!from_string(branchLenStr, ret))
            throw MalformedDoubleException();

        return ret;
    }


    LineNumber currentLineNumber;
    const char* character;
};
}

#endif
