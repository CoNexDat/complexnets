#pragma once

namespace graphpp
{
template <class Graph, class Vertex>
class IShellIndex
{
public:
    typedef std::map<typename Vertex::VertexId, unsigned int> ShellIndexContainer;
    typedef AutonomousIterator<ShellIndexContainer> ShellIndexIterator;
    
    virtual ShellIndexIterator iterator() = 0;

    virtual ~IShellIndex() {}
};
}  // namespace graphpp
