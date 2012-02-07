#ifndef SHELL_INDEX_H
#define SHELL_INDEX_H


namespace graphpp
{

template<class Vertex>
class DegreeComparator
{
public:
    bool operator()(Vertex* v1, Vertex* v2) const
    {
        bool ret = false;
        if (v1->degree() < v2->degree())
            ret = true;
        return ret;
    }
};


template <class Graph, class Vertex>
class ShellIndex
{


    typedef std::multimap<Vertex*, unsigned int, DegreeComparator<Vertex> > VertexByDegree;
    //typedef AutonomousIterator<VertexByDegree> VertexByDegreeIterator;

    typedef typename Graph::VerticesIterator VerticesIterator;
    typedef typename Graph::VerticesConstIterator VerticesConstIterator;
    typedef typename Vertex::VerticesConstIterator NeighbourConstIterator;
    typedef typename Vertex::VerticesIterator NeighbourIterator;

public:

    typedef std::map<typename Vertex::VertexId, unsigned int> ShellIndexContainer;
    typedef AutonomousIterator<ShellIndexContainer> ShellIndexIterator;

    ShellIndex(Graph& g)
    {
        initMap(g, shellIndex);
        initMultimapSet(g, vertexByDegree);
        calculateShellIndex();
    }

    ShellIndexIterator iterator()
    {
        return ShellIndexIterator(shellIndex);
    }

private:
    void calculateShellIndex()
    {
        typename VertexByDegree::iterator it = vertexByDegree.begin();
        Vertex* v;
        while (it != vertexByDegree.end())
        {
            v = it->first;
            shellIndex[v->getVertexId()] = it->second;
            NeighbourConstIterator neighborsIt = v->neighborsConstIterator();
            while (!neighborsIt.end())
            {
                if (vertexByDegree.find(*neighborsIt)->second > it->second)
                    vertexByDegree.find(*neighborsIt)->second -= 1;

                ++neighborsIt;
            }
            ++it;
        }
    }

    void initMap(Graph& g, ShellIndexContainer& shellIndex)
    {
        VerticesConstIterator it = g.verticesConstIterator();

        //initialize all elements in zero
        while (!it.end())
        {
            Vertex* v = *it;
            shellIndex.insert(std::pair<typename Vertex::VertexId, unsigned int>(v->getVertexId(), 0));
            ++it;
        }
    }

    void initMultimapSet(Graph& g, VertexByDegree& vertexByDegree)
    {
        VerticesConstIterator it = g.verticesConstIterator();

        //initialize all elements using the vertex id and the vertex degree
        while (!it.end())
        {
            Vertex* v = *it;
            vertexByDegree.insert(std::pair<Vertex* , unsigned int>(v, v->degree()));
            ++it;
        }
    }

    VertexByDegree vertexByDegree;
    ShellIndexContainer shellIndex;

};
}

#endif
