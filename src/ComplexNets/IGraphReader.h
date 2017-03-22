#ifndef IGRAPH_READER_H
#define IGRAPH_READER_H

#include "mili/mili.h"

class GraphLoadExceptionHierarchy
{
};

typedef GenericException<GraphLoadExceptionHierarchy> GraphLoadException;

DEFINE_SPECIFIC_EXCEPTION_TEXT(
    FileNotFoundException, GraphLoadExceptionHierarchy, "File could not found.");

DEFINE_SPECIFIC_EXCEPTION_TEXT(
    MalformedLineException, GraphLoadExceptionHierarchy, "Line is malformed.");

DEFINE_SPECIFIC_EXCEPTION_TEXT(
    UnsignedIntegerMalformedException,
    GraphLoadExceptionHierarchy,
    "The characters parsed do not represent a valid unsigned integer.");

DEFINE_SPECIFIC_EXCEPTION_TEXT(
    MalformedDoubleException,
    GraphLoadExceptionHierarchy,
    "The characters parsed do not represent a valid double.");

DEFINE_SPECIFIC_EXCEPTION_TEXT(
    DuplicatedEdgeLoading, GraphLoadExceptionHierarchy, "Graph does not allow duplicated edges.");

namespace graphpp
{
template <class Graph, class Vertex>
class IGraphReader
{
public:
    typedef std::string FileName;
    typedef unsigned int LineNumber;
    virtual void read(Graph& g, std::string source) = 0;

    virtual ~IGraphReader()
    {
    }
};
}

#endif
