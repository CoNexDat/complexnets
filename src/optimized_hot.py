# coding: utf-8
from collections import defaultdict
from random import random
import math
import sys

import logging as l
l.basicConfig(format="%(message)s", level=l.DEBUG)



class Vertex(object):

    def __init__(self, id):
        self.id = id
        self.position = (random(), random())

    def __repr__(self):
        return "Vertex<%s>(%s, %s)" % (self.id, self.position[0], self.position[1])


class Graph(object):

    def __init__(self):
        self.vertices = {}

    def __repr__(self):
        return "Graph(%s)" % self.vertices

    def add_vertex(self, v):
        self.vertices[v] = []

    def add_edge(self, v1, v2):
        self.vertices[v1].append(v2)
        self.vertices[v2].append(v1)

    def breadth_first_search(self, root):
        visited = set()
        q = [root]

        while q:
            v = q.pop(0)
            visited.add(v)
            for j in self.vertices[v]:
                if j not in visited:
                    q.append(j)
            yield v


def export(graph, file_obj):
    for v in graph.vertices:
        for j in graph.vertices[v]:
            file_obj.write("%s\t%s\n" % (v.id, j.id))


# HOT Extended Model
# The Paper can be checked in:
# http://cnet.fi.uba.ar/ignacio.alvarez-hamelin/pdf/model_internet_jiah_ns.pdf
#
# m:
#   number of edges in each new vertex (k in the paper)
# n:
#   total number of nodes
# xi:
#   parameter used to select the neighbors for new vertex. (theta in the paper)
# q:
#   number of edges added in the graph after of connect a vertex. (q in the paper)
# r:
#   parameter used to select the edges in the graph after connecting a vertex (γ in the paper)
# t:
#   parameter that represents how many rounds to do until a new root selection (τ in the paper)

def hot_extended(m, n, xi, q, r, t):

    graph = Graph()

    # first we add the root vertex
    root = Vertex(0)
    graph.add_vertex(root)
    
    # we then proceed to add the n-1 remaining nodes
    for i in range(1, n):

        # we add the new vertex with a random position
        v = Vertex(i)
        graph.add_vertex(v)

        w_min = distance(v, root)
        v_min = root
        h_min = 0

        h_max = 0;

        # for hop j from 1 to h_max
        for j in range(1, h_max):

            # we insert our new vertex in the delaunay for each hop
            d_j = delaunay(j)
            d_j.insert(v)

            # we get the nearest neighbor of v in this hop
            neighbor = d_j.nearest_neighbor(v)

            # we compute the weighted distance to this neighbor
            w = distance(v, neighbor) + xi * j

            # if this is the nearest neighbor up to this hop, update the min neighbor
            if w < w_min:
                w_min = w
                v_min = neighbor
                h_min = j

            # leave delaunay for hop as we without changes
            d_j.remove(v)

        # we will connect v to a neighbor that is at hop h_min, so add it to the next hop delaunay
        delaunay(h_min + 1).insert(v)

        # connect v with its nearest weighted neighbor
        # @question: why do we add a single edge here?
        graph.add_edge(v, v_min)

        # this should end the step 1 described in the paper
        # @question: shouldn't we add m new edges (q in the paper)?

        # now v should be available in the delaunay for hops pairs 1+ and 1-
        delaunay(h_min + 1, h_min + 3).insert(v)
        delaunay(h_min - 1, h_min + 1).insert(v)

        # this should be the start of step 2 described in the paper
        e_min = None
        w_min = float('inf')
        v_min = None

        for j in range(0, h_max - 2):

            for k in delaunay(j):

                d_ = delaunay(hop, hop + 2)
                v = d_.nearest_neighbor(k)
                
                # @question: how do we compute child count here? we need to mark the parent edge somehow to skip it
                w = distance(k, v) - (r / n) * child_count(v);

                if w < w_min:
                    w_min = w
                    v_min = v
                    e_min = (k, v)

        # graph.add_edge(*e_min);
        # @question: why do we add a single edge here instead of q?

        hp = 0

        for j in graph.breadth_first_search(root):
            # @question: is this where we compute T(j)?

            hj = weight_change(j);

            if (hj > hp):
                delaunay(hj - 2, hj).remove(j)
                delaunay(hj, hj + 2).remove(j)
                delaunay(hj).remove(j)

                delaunay(hp - 2, hp).insert(j)
                delaunay(hp, hp + 2).insert(j)
                delaunay(hp).insert(j)

                # @question: shouldn't this be hp = hj?
                hj = hp

        # @question: original algorithm should change root from time to time? this changes hop calculation

    return graph

def distance(v1, v2):
    return math.hypot(v2.position[0] - v1.position[0], v2.position[1] - v1.position[1])

def weight_change(v):
    return 0 # stub

def child_count(v):
    return float('inf') # stub


class Delaunay(object): # stub for now

    def __init__(self):
        self.vertices = []

    def insert(self, v):
        self.vertices.append(v)

    def remove(self, v):
        self.vertices.remove(v)

    def nearest_neighbor(self, v):
        min_d = float('inf')
        min_w = None

        for w in self.vertices:
            if v == w:
                continue

            d = distance(v, w)
            if d < min_d:
                min_d = d
                min_w = w

        return min_w


delaunay_map = defaultdict(Delaunay)

def delaunay(hop, hop_s=None):
    key = (hop, hop_s)
    return delaunay_map[key]


if __name__ == "__main__":
    g = hot_extended(2, 10, 0.3, 2, 0.2, 0.1)
    # export(g, sys.stdout)
