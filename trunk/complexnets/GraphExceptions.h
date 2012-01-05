#ifndef GRAPH_EXCEPTIONS_H
#define GRAPH_EXCEPTIONS_H

class GraphExceptionHierarchy {};
typedef GenericException<GraphExceptionHierarchy> GraphException;


/**
* Exception: DuplicateEdge
* ------------------------
* Description: Exception used when the user attempts to add an Edge that
* already exists in the graph that is not a multigraph
*/
DEFINE_SPECIFIC_EXCEPTION_TEXT(DuplicateEdge,
                               GraphExceptionHierarchy,
                               "Graph doesn't allow duplicate edges");
                               
                               
#endif
