class DSU:
    def __init__(self, n: int) -> None:
        """
        Initialize DSU with n elements.
        """
        self.parent : list[int] = []
        self.rank : list[int] = []
        self.size : list[int] = []        
        return
    
    def find(self, x: int) -> int:
        """
        Find the parent of the element x with path compression.
        """
        if self.parent[x] != x:
            val : int = self.parent[x]
            self.parent[x] = self.find(val)  # Path compression
            chk : int = self.parent[x]
        return chk
    
    def union(self, x: int, y: int) -> None:
        """
        Union two components represented by x and y with union by rank.
        """
        root_x: int = self.find(x)
        root_y: int = self.find(y)
        if root_x != root_y:
            if self.rank[root_x] < self.rank[root_y]:
                self.parent[root_x] = root_y
                self.size[root_y] = self.size[root_y] + self.size[root_x]
            elif self.rank[root_x] > self.rank[root_y]:
                self.parent[root_y] = root_x
                self.size[root_x] = self.size[root_x] +  self.size[root_y]
            else:
                self.parent[root_y] = root_x
                self.rank[root_x] = self.rank[root_x] + 1
                self.size[root_x] = self.size[root_x] + self.size[root_y]
        return

    def get_size(self, x: int) -> int:
        """
        Get the size of the component containing element x.
        """
        root: int = self.find(x)
        return self.size[root]

def main() :
    # Example usage:
    dsu: DSU = DSU(5)
    dsu.union(0, 1)
    dsu.union(1, 2)
    print(dsu.find(2))  # Output: 0 or 1

if __name__ == "__main__":
    main()
