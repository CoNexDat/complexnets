#ifndef ISHELL_INDEX_H
#define ISHELL_INDEX_H

namespace graphpp
{
template <class Graph, class Vertex>
class IShellIndex
{
public:
    typedef std::map<typename Vertex::VertexId, unsigned int> ShellIndexContainer;
    typedef AutonomousIterator<ShellIndexContainer> ShellIndexIterator;

    virtual ShellIndexIterator iterator() = 0;
};
}

#endif
