class DSU:
    def __init__(self, n):
        """
        Initialize DSU with n elements.
        """
        self.parent = [i for i in range(n)]
        self.rank = [0] * n
        self.size = [1] * n  # Size of each component
    
    def find(self, x):
        """
        Find the parent of the element x with path compression.
        """
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])  # Path compression
        return self.parent[x]
    
    def union(self, x, y):
        """
        Union two components represented by x and y with union by rank.
        """
        root_x = self.find(x)
        root_y = self.find(y)
        if root_x != root_y:
            if self.rank[root_x] < self.rank[root_y]:
                self.parent[root_x] = root_y
                self.size[root_y] += self.size[root_x]
            elif self.rank[root_x] > self.rank[root_y]:
                self.parent[root_y] = root_x
                self.size[root_x] += self.size[root_y]
            else:
                self.parent[root_y] = root_x
                self.rank[root_x] += 1
                self.size[root_x] += self.size[root_y]

    def get_size(self, x):
        """
        Get the size of the component containing element x.
        """
        root = self.find(x)
        return self.size[root]

# Example usage:
dsu = DSU(5)
dsu.union(0, 1)
dsu.union(1, 2)
print(dsu.find(2))  # Output: 0 or 1
