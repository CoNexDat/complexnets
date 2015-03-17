ComplexNets++ Design DoC

# Architecture #

TODO: Architecture overview and diagrams

## ComplexNets ##

ComplexNets is the core reusable component of the system. It contains the reusable and extensible classes and interfaces that may be used for different purposes. The only dependency is Mili, a library briefly described below.

## UI ##

TODO: Nicolas

## Mili ##

Mili is a highly optimized Minimalistic Library that provides simple yet powerful functionalities, such as autonomous iterators, generic stl containers and helper methods. Mili was developed by FuDePAN and was slightly modified to suit ComplexNets needs.
High Level Design

## Design Goals ##

ComplexNets++ Library design has the following as main goals:

**Focus in both memory and time efficiency. Also, the user of the library (programmer) must be able to somehow “adjust” the tradeoff between these too**Focus in extensibility

In order to accomplish these requirements, the design of the graph and vertex classes is the key to success, and the solution is to build them really simple, and provide a very simple way of extension. The way of extension selected is Aspect Oriented Programming – to extend a given graph or vertex through adding aspects to it. This allows one user of the library to store information X and Y in his vertices, while user B stores information X and Z, reusing the overlapping code but not paying the memory or efficiency cost of the components they don’t intend to use.
Also, as inheritance and virtual methods are enemies of high performance and also impact on memory storage within the levels of memory efficiency we intend to achieve, the design minimizes inheritance and virtual methods in graph and vertex class. This way, all calls are resolved by the compiler, thus avoiding virtual table lookups for graphs and vertices in critical algorithms, and we get all the benefits of static polimorfism. The use of dynamic polimorfism is only recommended for factories or classes that aren’t called inside algorithms iterations.

## Extension through Aspects ##

For both the Graph and vertex class, the extension mechanism is Aspect Oriented Programming. There exist a base graph and vertex, as simple as possible, and then they are specialized through attaching different aspects. The interesting thing about this is that aspects are independent from each other, and any programmer can make a composition based upon any subsets of the available aspects. The following table illustrates how AOP is implemented in C++ through templates.

```
template<class NextAspect>
class Aspect1 : public NextAspect
{
       //class definition
}
   
template<class NextAspect>
class Aspect2 : public NextAspect
{
        //class definition
}
 
template<class NextAspect>
class Aspect3 : public NextAspect
{
        //class definition
}
 
class BaseClass
{
        //class definition
}
 
typedef SomeAspectsClass Aspect2<Aspect3<BaseClass>>;
```

This technique aligns itself with the design goals, in the sense that the type of SomeAspectsClass is resolved at compile time, therefore every reference to SomeAspectsClass will have been resolved at runtime.

The practical use of this is to create a simple graph and vertex class. Afterwards, if a weighted graph is needed, a WeightedAspect can be attached to graph or vertex. If also a directed graphs are needed, a DirectedAspect can be created. Later, a user of the library can decide to work with regular graphs (simpler, less memory usage), or weighted, or directed, or both weighted and directed by composing the different aspects as in the example above.

## Traversals ##

Before diving into calculations, it is understood that once a graph exists, people want to traverse it. That is why the library includes some traversal algorithms. They are also provided as an example of how to make extensible and reusable traversals. For example, if the intention is to traverse a graph without any particular order, the TraverserForward class can be used, and the only code the user has to create, is the visitor routine for executing on each vertex.

Here is the code of an example traversal class

```
template <class Graph, class Vertex, class Visitor>
class TraverserForward
{
public:
    static void traverse(Graph& graph, Visitor& visitor)
    {
        traverse(graph.verticesIterator(), visitor);
    }
    static void traverse(typename Graph::VerticesIterator iterator, Visitor& visitor)
    {
        bool keepTraversing = true;
        while (!iterator.end() && keepTraversing)
        {
            Vertex* v = *iterator;
            keepTraversing = visitor.visitVertex(v);
            ++iterator;
        }
    }
};

```

Then, a user can traverse the graph only by coding a visitor which implements the visitVertex method. This is great because of the following reasons:

**Write the traversal algorithms only once**Test the traversal algorithms only once and test the visitor separately
**If wrote a visitor and want to change the traversal, only change the traversal class. No need to re-test the visitor or the traversal because they are independently implemented and independently tested.**

Also, note that the algorithm is independent of the type of Graph and type of vertex, thanks to generic programming.
So at the moment of traversing a graph, if a new traversal is needed, a traverser class should be created that allows this same kind of extension.

## Calculations ##

There are several calculations partially or totally
**Degree Distribution**Strength Distribution
**Nearest neighbors degree**Clustering Coefficient
**Shell Index**Betweenness (Not working yet)

Each of these calculations has an associated generic interface, which is implemented for different kinds of graphs – also can be reused among graph types when the algorithm doesn’t vary between graph types.
As generally, for a given graph there exist a full set of calculations, the library also provides the IGraphFactory interface, to provide factories that exposes creation primitives for all basic algorithms for a given graph.

## Export and Import ##

Two interfaces are provided for importing and exporting, named IGraphReader and IGraphWriter.

# Low Level Design #

## Adjacency List Graph and Vertex ##

When modeling the Graph class, two things were mainly considered.

First, that the graph class shouldn’t depend upon a certain type of vertex. To enforce that, we propose an initial declaration of the AdjacencyListGraph as

```
template <class Vertex>
class AdjacencyListGraph

```

Where the template parameter Vertex is the vertex type.

The second desirable property for the graph class, is to be able to work with different types of containers for vertices. For example, the user may want to use either a set to quickly find vertices by their id, or use a vector to minimize space. This decision should be made by the client on a case by case basis, depending on the algorithms or processes to be performed over the graph. Then, the final AdjacencyListGraph declaration would be:

```
template <class Vertex, class VertexContainer = std::set<Vertex*, VertexComparator<Vertex> > >
class AdjacencyListGraph
```

Where Vertex is the vertex type, and VertexContainer is the container to be used to store the collection of vertices associated to the graph.

### Vertex Collection Operations ###

Once a VertexContainer type is specified, it is not trivial to perform operations over the collection in a generic mode, since stl containers don’t have a common interface. This is where MiLi minimalistic library helps us, with wrappers around collections operations, unifying them into a single interface. This way, in the AdjacencyListGraph class we write the following code to add a vertex to the collection:

```
insert_into(vertices, v);
```

where vertices is the vertex collection and v is the vertex to be added. insert\_into is a mili generic function that has the vertices collection type as template parameter, and automatically maps to the adequate template specialization implemented in mili.

### Iterating Vertices ###

Another non trivial problem, comes up when we consider how to expose the vertices to the library user. The user should have some way to access the vertices. Although, it would be a design risk to allow the user access to the vertices collection. First of all, because we would spread references to our data along the code, without being able to control its mutability. Then, passing the collection to the user would be a special way of coupling called “Data Coupling”, where the library and the client are tightly coupled through the structure of the data being passed. To solve this problem, we make use of the iterator pattern, and when the user asks to see the collection we provide him with a vertices iterator. An iterator is an object that potentially can give the user access to each element in the collection, but only as long as the user needs it. If the user asks for the iterator but doesn’t use it, no information will flow from library to client.

In order to provide a common iterator adjustable to all collection types, we use MiLi AutonomousIterator, which is a generic implementation of the iterator pattern, disregarding of the underlying collection type. This is nice because we abstract ourselves from how we are storing the data. VerticesIterator is a actually a typedef from AutonomousIterator generic specialization:

```
typedef AutonomousIterator<VertexContainer>  VerticesIterator;
```

Where VerticesContainer is the generic container template parameter, which will be resolved at compile time.

We provide VerticesIterator and also VErticesConstIterator which is typedef of CAutonomousIterator

&lt;VertexContainer&gt;

 as a constant iterator. Users should always use the constant iterator unless they are explicitly willing to modify the items in the collection. The advantage of this is that using VErticesConstIterator can avoid accidental modifications, because they will end in a compilation error, catching the bug even before running the program.

Once the user gets a VerticesIterator instance, it is very easy to iterate since it has the ++ and -- operators overloaded, to perform just as an stl operator, as in the following example

```
typename Graph::VerticesIterator iterator = graph.verticesIterator()
while (!iterator.end())
        {
             Vertex* v = *iterator;
             //do something with v
             ++iterator;
    }
```

Set based Vertex collections with custom comparators

When specifying the VerticesContainer type, for the particular case of the Set, we notice that the declaration is as the following

```
VertexContainer = std::set<Vertex*, VertexComparator<Vertex> > >
```

Where vertex comparator is a default comparator provided by the graph class. This comparator is the comparer method used by the set to determine store and sort the vertices, and to determine equality between vertices. VertexComparator uses the VErtexId property as comparison property. The user could simply write his own comparator, and specify it as template parameter of the Set as

```
std::set<Vertex*, MyCustomComparator<Vertex> > >
```

and the graph class shall use that set as storage.

### Finding Vertices ###

Although mili helped us to abstract a lot of things when parametrizing the underlying vertices container, mili doesn’t provide a common interface for finding elements in different collections. The graph class contains a mechanism to provide this. The vertex finding routine is invoked from the graph code, in the following method:

```
Vertex* getVertexById(VertexId id) const
{
        return VertexFinder<Vertex, VertexContainer>::find(id, vertices);
}
```

Where the find method is a static method of the VertexFinder class. If we go to the definition of the VertexFinder class, we’ll find two definitions:

The first one is the most generic one:

```
template <class Vertex, class Container>
class VertexFinder
```

Which is used by most containers as list and vector, and uses an iterator. When adding a new container, consider that this method works for any container where the iterator iterates through elements. It is not useful to use this class for sets, since we would be wasting the set funcionality. That’s why we introduce another declaration of the vertex finder class through a specialized template:

```
class VertexFinder<Vertex, std::set<Vertex*, VertexComparator<Vertex> > >
class VertexFinder
```


This C++ trick of declaring the class 2 times for different levels of genericness has the effect that when VertexFinder is called, the most specific specialization is called. Then, if the graph class uses set, the specialized set class will be called. Otherwise, the most generic class will be called. This is good since we don’t add if statements to select what find method to use, the compiler selects it itself at compile time.

### Adjacency List Vertex class ###

The AdjacencyListVertex class is the base and default vertex class provided with the library. It intends to provide basic vertex primitives and extension points and options.

First lets take a look to the type definitions inside the vertex class:

```
public:
    typedef unsigned int VertexId;
    typedef unsigned int Degree;
    typedef std::set<AdjacencyListVertex*> VertexContainer;
    typedef CAutonomousIterator<VertexContainer> VerticesConstIterator;
    typedef AutonomousIterator<VertexContainer> VerticesIterator;
```

These types are public because they are exposed by the vertex. Since the graph has a generic template of vertex, to reference the type of the vertex id, of the type of the VerticesIterator, the graph code calls typename Vertex::VerticesIterator. So, each vertex implementation must provide a definition of these 5 types the way it is more convenient for the vertex itself.

With the same spirit in which we expose the vertices of a graph through an iterator, the vertex exposes its neighbours through iterators too, in both const and non const versions, so developers should whenever possible, the const version to ensure const correctness throughout the code.

Currently the vertex class contains a “visited” tag for BFS and DFS algorithms. This shouldn’t be part of the vertex because we are forcing the user to use those bytes of storage even if he won’t use them. The solution to this is to remove the tag from the base vertex. The BFS and DFS visited tag can be implemented through the use of a hash table. Another option is to write a TaggableAspect around the vertex class, and a Tag based BFS (reuse the current in this case, in TraverseBFS class). TODO.

## Weighted Graph ##

### Design and AOP ###


Current weighted graph implementation was designed to be an extension of the base graph and vertex. By extension, we could mean inheritance, or some other kind of extension, since what we need is to reuse the existing code. But the inheritance approach has its drawbacks. Imagine that then we want to implement a directed graph: We would have the base graph code, and both the weighted extension and the directed extension. If we solve this by inheritance, a plausible inheritance chain would be Graph -> WeightedGraph -> DirectedGraph. This allows us to us a simple graph, or a weighted graph, or a weighted AND directed graph, but there is no way we can get an only directed graph.

As the weight and direction of a graph are cross cutting concerns, i.e. they don’t affect each other in respects of data structure, the alternative design chosen is to use aspect oriented programming. So we design the WeightedGraph or DirectedGraph or WeightedVertex as aspects, chunks of code that can be attached to a given class, interchanged and composed.

As the usual C++ language idiom for AOP internally uses inheritance for each aspect, the inception of a new aspect must be carefully thought. The risks are not high in terms of efficiency, since in the library we always use templates for the graph and vertex type, so the methods are invoked directly and not through virtual table. The actual risk is when we introduce and use several aspects over the vertex at once, because in terms of memory every inheritance level internally adds a delta of memory usage, which is small but for millions of vertices it can add up to a significant number.

### Weighted Graph Aspect ###

The weighted graph aspect is declared as a class, in the following way:

```
template <class WeightedVertex, class T>
class WeightedGraphAspect : public T
```

where WeightedVertex is the template parameter for the Vertex type to be used, and T is the next aspect in the chain. This can be confusing, as we see that WeightedGraphAspect also inherits from T. This is a mechanism to provide a very simple way of metaprogramming, where we create variable inheritance chains at compile time. When we instanciate this, we instanciate as WeightedAspect<DirectedAspect

&lt;Graph&gt;

 >, so this, in the eyes of the compiler, would be as if there is a class WeightedAspect that inherits from DirectedAspect, which inherits from Graph class. The powerful part of this is that any combination is allowed.

Inside the aspect code, we can do three things:

Add data or state: Add instance variables, and use them to hold a state
Override methods: When rewriting a method, functionality is added to the aspect. It is very important to call the base aspect’s method in the aspect overriden code, since each other aspect may have added code on that method. When developing aspects, we must always consider that every aspect adds functionality, so if we don’t call the base class method we may introduce bugs because the other aspects won’t be called
Add new methods for this specific aspect. This happens for example in WeightedGraphASpect, where we add a new method with the following declaration

```
void addEdge(WeightedVertex* s, WeightedVertex* d, Weight weight)


So that when we add an edge, a weight is considered. This can also be seen in WeightedVertex implementation of the AddVertex method:

void addEdge(WeightedVertexAspect<T>* other, Weight weight)
{
        T::template addEdge<WeightedVertexAspect<T> >(other);
        weights.insert(std::pair<VertexId, Weight>(other->getVertexId(), weight));
}
```


Where even if we add a new overload to addEdge, we call the original instance method on the T class, so that it is executed in the other aspects that may exist.

### Graph Calculations Factory ###

There is a simple abstract factory with the following definition

```
template<class Graph, class Vertex>
class IGraphFactory
{
public:
    virtual IBetweenness<Graph, Vertex>* createBetweenness(Graph& g) = 0;
    virtual IClusteringCoefficient<Graph, Vertex>* createClusteringCoefficient() = 0;
    virtual INearestNeighborsDegree<Graph, Vertex>* createNearestNeighborsDegree() = 0;
    virtual IShellIndex<Graph, Vertex>* createShellIndex(Graph& g) = 0;
    virtual IGraphReader<Graph, Vertex>* createGraphReader() = 0;
    virtual DegreeDistribution<Graph, Vertex>* createDegreeDistribution(Graph& g) = 0;
};
```

The goal of this is that for a certain type of graph, we may use the set of algorithms A, and for another type of graph we may use a set of algorithms B. A user of the library would have to determine each time which is the correct betweenness or clustering coefficient implementation and that may lead to mistakes. So as a way so that programmers can very easily get to the algorithms, we create this interface. Then, when a type of graph is going to be widely used, for example a weighted graph, we implement a class that implements IGRaphFactory, and creates instances of all the algorithms that should be run on weighted graphs. Of course, if more flexibility is needed and a programmer wants to run a different algorithm over a graph, he can instanciate the algorithm manually and run it - it is just an easy ramp-up mechanism.

Also, as the factories are generic, a user could use the regular graph implementation over a WeightedGraph, but it would execte the algorithms for unweighted graph as expected.
UI

# Engineering practices #


## Design practices: RDD ##

When designing new functionality, the design process should be the same as used for the initial design, which is based in Responsibility Driven Design.

Object-oriented design typically is quite exploratory and iterative. Unless designers are building (or rebuilding) an application with which they are intimately familiar , a clear vision of the key classes does not exist. Creating a model requires understanding system requirements as well as skill in identifying and creating objects. Building consensus and developing a common vocabulary among team members is important. Initially, designers look for classes of key objects, trying out a variety of schemes to discover the most natural and reasonable way to abstract the system into objects.

Responsibility-driven design focuses on what actions must get accomplished, and which objects will accomplish them. How each action is accomplished is deferred. A good starting point for
defining an object is describing its role and purpose in the application. Details of internal structure and specific algorithms can be worked out once roles and responsibilities are better
understood.

A responsibility is a cohesive subset of the behavior defined by an object. An object’s responsibilities are high-level statements about both the knowledge it maintains and the
operations it supports. An analogy between designing objects and writing a report can clarify
the intent of listing each object responsibilities. An object’s responsibilities are analogous to
major topic headings in an outline for a report. The purpose of developing an outline (and then a
detailed outline) before writing a report are to map out the topics to be covered in the report and
their order of presentation. Similarly, the purpose of outlining an object’s responsibilities are to
understand its role in the application before fleshing out the details. A good way to determine an
object’s responsibilities are to answer these questions: What does this object need to know in
order to accomplish each goal it is involved with? What steps towards accomplishing each goal
should this object be responsible for?

Objects do not exist in isolation. Object-oriented applications of even moderate size can consist
of hundreds if not thousands of cooperating objects. A collaboration is a request made by one
object to another. An object will fulfill some responsibilities itself. Fulfilling other responsibilities likely requires collaboration with a number of other objects.

## Design Principles ##

Besides the use of design patterns as a way to enrich and empower the design, it is highly desired in this library to follow the SOLID design principles and the demeter law while designing and coding. It is proven that software that holds these principles has an amazing extensibility and maintainability power. Here is a brief of the principles

**SRP - Single Responsibility Principle: states that every object should have a single responsibility, and that responsibility should be entirely encapsulated by the class. All its services should be narrowly aligned with that responsibility.**OCP - Open-Closed Principle: states that software entities (classes, modules, functions, etc.) should be open for extension, but closed for modification, that is, such an entity can allow its behaviour to be modified without altering its source code.
**LSP - Liskov Substitution Principle: is a particular definition of a subtyping relation, called (strong) behavioral subtyping, and states that given q(x) to be a property provable about objects x of type T, then q(y) should be true for objects y of type S where S is a subtype of T.**ISP - Interface Segregation Principle: supports the idea that many client specific interfaces are better than one general purpose interface.
**DIP - Dependency Inversion Principle: states that High-level modules should not depend on low-level modules, both should depend on abstractions, and that abstractions should not depend upon details, details should depend upon abstractions.**LoD - Law of Demeter: Law of Demeter, object oriented principle used to accomplish loose coupling. The Law of Demeter for functions requires that a method m of an object O may only invoke the methods of the following kinds of objects:

#O itself
#m's parameters
#Any objects created/instantiated within m
#O's direct component objects
#A global variable, accessible by O, in the scope of m


## Coding Conventions ##

Some things to consider while coding:

**const-correctness: Mutable objects when explicitly needed. If they won’t be changed, const them for compiler optimizations. Also, methods should be static when not using internal state, const when using but not changing internal state, and regular when changing internal state**sign-correctness: If we use positive numbers for example, declare them as unsigned int
**Use references as much as possible. Minimize pointers and pointer arithmetic**Never pass objects by value, this is really expensive. Always by reference, except when they are native types as int or long
**Do not return containers, nor accept them by value:
```
vector getVector(); // WRONG
void setVector(vector v); // WRONG
```
Instead, use references:
```
getVector(vector& v); // v is output
void setVector(const vector& v); // v is // input
```**Receiving native data types: do not use & - You'd be using a useless indirection.
```
void setParams(const float& speed); //BAD
void setParams(float speed); // GOOD
```
**Do not use the return value of methods for error codes, use exception handling instead. Build an exception hierarchy that inherit from MiLi GenericException as in GraphExceptions.h
Typedef the types as self-documenting method**Use astyle before each commit:
Use the following command line:
```
astyle --options=none --convert-tabs -bSKpUH -k1 *.h *.cpp
```
you can use –-recursive from the top directory
NOTE: use version >= 2.02, not the one from Ubuntu
**Casting: Always prefer in this order
#Function-style cast: foo = int(x);
#Static cast: foo = static\_cast**

<bar\_type>

(x);
#Dynamic\_cast: This shouldn’t be needed
#C-style cast: foo = (foo\_type)x; This is abolished, except for calling c code which is not the case of the library

## Testing ##

ComplexNets is highly unit-tested, in order to assure and maintain the quality of the code. Every change must have its related unit test in order to keep being able to track the correctness of the code automatically. Unit tests are implemented through Google Testing Framework for C++.

We didn’t still need the use of GoogleMock, but in case of needing it for creating mock objects, just uncomment the GoogleMock line in TestsMain.cpp.

All classes and all code paths in the library should have a unit test associated. In order to maintain that, the following actions must be taken:

**When adding new functionalities or features, write a new unit test:**Use an example of other unit test and create the cpp file
**Add the cpp file to the CMakeLists.txt file**run cmake CMakeLists.txt
/8run make
**run ./tests and check the results**When changing code, verify that all tests pass before committing to ensure no regression. If new code paths are added, a new test cases should be added to the feature’s unit tests.
**Regularly run the code coverage and CodeMetrics sh scripts, that should generate code coverage and metrics reports. cccc, gcov and lcov should be installed. Important things from this reports that should be enforced or checked are:
#Line Coverage: we should have always above 90% of code coverage for the library project (the UI separate and because of QT won’t get to that coverage).
#Function coverage: Always above 90% as well
#LoC, LoT: Usually the number of lines of code is the same order of magnitude as the lines of test code. If lines or code are much greater, it might be good to check the coverage**Design: If a class is difficult to unit test, it reflects a design issue. When designing the classes we must always think about how it will be tested.