# -*- coding: <ascii> -*-
# This is an ENCODING DECLARATION
# This does not include the PEP484 type hints for now and this will require
# further enhancement however we can use it for lexical analysis for now.
from typing import List, Tuple

# Is class included in the set of features we need to implement ?
class DisjointSetUnion:
    def __init__(self, n: int):
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, x: int) -> int:
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x: int, y: int) -> None:
        root_x = self.find(x)
        root_y = self.find(y)

        if root_x == root_y:
            return

        if self.rank[root_x] < self.rank[root_y]:
            self.parent[root_x] = root_y
        elif self.rank[root_x] > self.rank[root_y]:
            self.parent[root_y] = root_x
        else:
            self.parent[root_y] = root_x
            self.rank[root_x] += 1

def kruskal(graph: List[Tuple[int, int, int]], num_nodes: int) -> List[Tuple[int, int, int]]:
    graph.sort(key=lambda x: x[2])  # Sort edges by weight
    dsu = DisjointSetUnion(num_nodes)
    mst = []

    for edge in graph:
        u, v, weight = edge
        if dsu.find(u) != dsu.find(v):
            mst.append(edge)
            dsu.union(u, v)

    return mst

if __name__ == "__main__":
    # Example graph represented as list of edges (u, v, weight)
    # Here, we have 5 nodes (0, 1, 2, 3, 4) and 7 edges
    # (node1, node2, weight)
    graph = [
        (0, 1, 5),
        (0, 2, 10),
        (0, 3, 8),
        (1, 3, 7),
        (1, 4, 6),
        (2, 4, 4),
        (3, 4, 3)
    ]

    # Run Kruskal's algorithm to find minimum spanning tree
    mst = kruskal(graph, 5)

    # Print the minimum spanning tree
    print("Minimum Spanning Tree (Kruskal's Algorithm):")
    for edge in mst:
        print(edge)
