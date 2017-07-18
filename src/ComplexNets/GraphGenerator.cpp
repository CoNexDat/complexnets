// This toolbox is licensed under the Academic Free License 3.0.
// Instituto Tecnológico de Buenos Aires (ITBA).
// Last modification: December 19th, 2012.

#include "GraphGenerator.h"
#include <cmath>
#include "ComplexNets/ConnectivityVerifier.h"
#include "ComplexNets/DirectedGraphFactory.h"
#include "ComplexNets/GraphFactory.h"
#include "ComplexNets/IGraphReader.h"
#include "ComplexNets/TraverserBFS.h"
#include "ComplexNets/WeightedGraphFactory.h"

using namespace graphpp;

typedef struct Position
{
    float x;
    float y;
} Position;

static const double PI = atan(1) * 4;
std::vector<Position> vertexesPositions;

GraphGenerator* GraphGenerator::instance = nullptr;

GraphGenerator::GraphGenerator(){};

GraphGenerator* GraphGenerator::getInstance()
{
    if (instance == nullptr)
    {
        instance = new GraphGenerator();
    }

    return instance;
}

Graph* GraphGenerator::generateGraphFromFile(std::string path, bool directed, bool multigraph)
{
    Graph* graph = new Graph(directed, multigraph);

    auto factory = new GraphFactory<Graph, Vertex>();
    auto reader = factory->createGraphReader();
    reader->read(*graph, path);

    delete reader;
    delete factory;

    return graph;
}

DirectedGraph* GraphGenerator::generateDirectedGraphFromFile(std::string path, bool multigraph)
{
    auto graph = new DirectedGraph(multigraph);

    auto factory = new DirectedGraphFactory<DirectedGraph, DirectedVertex>();
    auto reader = factory->createGraphReader();

    reader->read(*graph, path);

    delete reader;
    delete factory;

    return graph;
}

WeightedGraph* GraphGenerator::generateWeightedGraphFromFile(
    std::string path, bool directed, bool multigraph)
{
    auto graph = new WeightedGraph(directed, multigraph);

    auto factory = new WeightedGraphFactory<WeightedGraph, WeightedVertex>();
    auto reader = factory->createGraphReader();

    reader->read(*graph, path);

    delete reader;
    delete factory;

    return graph;
}

Graph* GraphGenerator::generateErdosRenyiGraph(unsigned int n, float p)
{
    auto graph = new Graph();

    for (unsigned int i = 1; i <= n; i++)
    {
        graph->addVertex(new Vertex(i));
    }

    for (unsigned int i = 1; i < n; i++)
    {
        Vertex* srcVertex = graph->getVertexById(i);

        for (unsigned int j = i + 1; j <= n; j++)
        {
            if ((float)rand() / RAND_MAX <= p)
            {
                Vertex* destVertex = graph->getVertexById(j);
                graph->addEdge(srcVertex, destVertex);
            }
        }
    }

    // Keep only the biggest component (at least n/2 vertexes)
    ConnectivityVerifier<Graph, Vertex> connectivityVerifier;
    connectivityVerifier.getBiggestComponent(graph);

    return graph;
}

Graph* GraphGenerator::generateBarabasiAlbertGraph(unsigned int m_0, unsigned int m, unsigned int n)
{
    auto graph = new Graph();
    // Create a K_M_0 graph
    for (unsigned int i = 1; i <= m_0; i++)
        graph->addVertex(new Vertex(i));
    for (unsigned int i = 1; i < m_0; i++)
    {
        Vertex* srcVertex = graph->getVertexById(i);
        for (unsigned int j = i + 1; j <= m_0; j++)
        {
            Vertex* destVertex = graph->getVertexById(j);
            graph->addEdge(srcVertex, destVertex);
        }
    }

    // Fill the array with k apparitions of each vertex where k is the degree of the vertex
    std::vector<unsigned int> vertexIndexes;
    for (unsigned int i = 1; i <= m_0; i++)
        for (unsigned int k = 0; k < m_0; k++)
            vertexIndexes.push_back(i);

    for (unsigned int i = m_0 + 1; i <= n; i++)
    {
        unsigned int k = 0;
        Vertex* newVertex = new Vertex(i);
        while (k < m)
        {
            unsigned int index = vertexIndexes[rand() % vertexIndexes.size()];
            Vertex* selectedVertex = graph->getVertexById(index);
            // It isn't the same vertex and it isn't connected
            if (index != i && !selectedVertex->isNeighbourOf(newVertex))
            {
                vertexIndexes.push_back(index);
                vertexIndexes.push_back(i);
                graph->addVertex(newVertex);
                graph->addEdge(selectedVertex, newVertex);
                k++;
            }
        }
    }
    vertexIndexes.clear();
    return graph;
}

/*
 * HOT Extended Model
 * The Paper can be checked in:
 * http://cnet.fi.uba.ar/ignacio.alvarez-hamelin/pdf/model_internet_jiah_ns.pdf
 * m represents the number of edges in each new vertex (k in the paper)
 * n is the total nodes number
 * xi is the parameter used to select the neighbors for new vertex. (Theta in the paper)
 * q  represents the number of edges added in the graph after of connect a vertex. (q in the paper
 * as well)
 * r is the parameter used to selected the edges in the graph after of connect a vertex. (γ in the
 * paper)
 * t is the parameter that represent how many rounds until a new root selection (τ in the paper)
 *
 * Algorithm summary
 * Step 1) Create the first vertex with random position and set it as root
 * Step 2) Create new vertexes V with random positions and then connect to the vertixes U which
 * minimizes the euclidean distance from U to V and the hoops distance from U to root. This process
 * is repeated m times for each new vertex added.
 * Step 3) Create q new edges on the graph for the vertex added
 * Step 4) A new root is chosen with probability dependant on the node degree every t rounds. (@TODO)
 * */

Graph* GraphGenerator::generateHotExtendedGraph(
    unsigned int m, unsigned int n, float xi, unsigned int q, float r, unsigned int t)
{
    auto graph = new Graph();

    // add root vertex
    Vertex* root = new Vertex(0);
    graph->addVertex(root);

    addPosition(root);
    
    // for each of the nodes we will be adding to the graph
    for (unsigned i = 1; i < n; i++)
    {
        Vertex* v = new Vertex(i);
        addPosition(v);

        // setup minWeight, minVertex, minHop
        auto minWeight = distance(v, root);
        auto minVertex = root;
        auto minHop = 0;

        // TODO: consider how maxHop is computed

        // for hop j from 1 to maxHop
        for (unsigned hop = 1; hop <= maxHop; hop++)
        {
            auto nn = singleHopNN(j)
            nn->insert(v);

            auto neighbor = nn->get(v);
            auto weight = distance(v, neighbor) + xi * hop;

            if (weight < minWeight)
            {
                minWeight = weight;
                minVertex = neighbor;
                minHop = hop;
            }

            nn->delete(v)
        }

        auto nn = singleHopNN(minHop + 1);
        nn->insert(v);

        // TODO: update Ti to Tr?
        graph->addEdge(v, minVertex);

        nn = doubleHopNN(minHop + 1, minHop + 3)
        nn->insert(v);

        nn = doubleHopNN(minHop - 1, minHop + 1)
        nn->insert(v);

        std::pair minEdge;
        minWeight = INFINITY;
        minVertex = nullptr;

        v = nullptr;

        for (unsigned hop = 0; hop <= maxHop - 2; hop++)
        {
            for (auto const& k : singleHopNN(hop))
            {
                nn = doubleHopNN(hop, hop + 2);
                v = nn->get(k);
                
                auto weight = distance(k, v) - (r / n) * childCount(v);
                if (weight < minWeight)
                {
                    minWeight = weight;
                    minEdge = make_pair(k, v);
                    minVertex = v;
                }
            }
        }

        graph->addEdge(minEdge.first, minEdge.second);

        auto hp = 0;

        // TODO: see whiteboard
        for (auto const& j : BFS(root))
        {
            auto hj = computeWeightChange(j);
            if (hj > hp)
            {
                nn = doubleHopNN(hj - 2, hj);
                nn->delete(j);

                nn = doubleHopNN(hj, hj + 2);
                nn->delete(j);

                nn = singleHopNN(hj);
                nn->delete(j);

                nn = doubleHopNN(hp - 2, hp);
                nn->insert(j);

                nn = doubleHopNN(hp, hp + 2);
                nn->insert(j);

                nn = singleHopNN(hp);
                nn->insert(j);
            }
        }
    }
    return graph;
}

Graph* GraphGenerator::generateMolloyReedGraph(std::string path)
{
    Graph* graph = new Graph(false, false);

    auto reader = new MolloyReedGraphReader<Graph, Vertex>();
    reader->read(*graph, path);

    delete reader;

    return graph;
}

/*
 * Computes the distance in a hiperbolic space between two points
 */

inline double GraphGenerator::hiperbolicDistance(PolarPosition p1, PolarPosition p2)
{
    return acosh(
        cosh(p1.r) * cosh(p2.r) -
        sinh(p1.r) * sinh(p2.r) * cos(fmod(abs(p1.theta - p2.theta), PI)));
}

/*
 * Computes random polar hyperbolic coordinates
 */
inline GraphGenerator::PolarPosition GraphGenerator::getRandomHyperbolicCoordinates(
    float a, double maxr)
{
    PolarPosition pos;
    // generate theta in [0, 2pi]
    pos.theta = ((double)rand() / (double)RAND_MAX) * 2 * PI;
    // select a radius in (0, r)
    double u = ((double)rand() / (double)RAND_MAX);
    pos.r = acosh(u * (cosh(maxr * a) - 1) + 1) / a;
    return pos;
}

inline double GraphGenerator::getMaxRadius(int i, float a, float c)
{
    return log((double)i / c) / a;
}

double GraphGenerator::getExpectedAvgNodeDeg(unsigned int i, float fa, float fc)
{
    double a = (double)fa;
    double amh = a - 0.5;
    double c = (double)fc;
    double R = getMaxRadius(i, fa, fc);
    double c1 = 2 * pow(a, 3) / (PI * (pow(amh, 3)) * (pow(2 * a - 0.5, 3)));
    double c2 = (2 * a - PI * (amh)) / (2 * PI * amh);
    double c3 = a / (PI * pow(amh, 2));
    double c4 = (a / (PI * amh)) * (1 + a / (2 * pow(amh, 2)));
    return 2 * a * c * (c1 * exp(amh * R) - c2 * a * pow(R, 2) - R * c3 - c4);
}

/*
 * Papadopoulos Hiperbolic Graph Model
 * n is the total nodes number
 * a is the radial density of the graph.
 * c is the a parameter that determines the average degree of the graph.
 * */
Graph* GraphGenerator::generateHiperbolicGraph(unsigned int n, float a, float c)
{
    Graph* graph = new Graph(false, false);
    std::vector<PolarPosition> vPolarPos;
    PolarPosition sentinel;
    vPolarPos.push_back(sentinel);
    for (unsigned int i = 1; i <= n; i++)
    {
        Vertex* src = new Vertex(i);
        graph->addVertex(src);
        // compute the current disk radius
        double maxr = getMaxRadius(i, a, c);
        bool hasNeighbours = false;
        PolarPosition pos;
        do
        {
            pos = getRandomHyperbolicCoordinates(a, maxr);
            for (unsigned int j = 1; j < i; j++)
            {
                PolarPosition other = vPolarPos[j];
                if (hiperbolicDistance(pos, other) < maxr)
                {
                    hasNeighbours = true;
                    graph->addEdge(src, graph->getVertexById(j));
                }
            }
        } while (!hasNeighbours && i != 1);
        vPolarPos.push_back(pos);
    }
    return graph;
}
