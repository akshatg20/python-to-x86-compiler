# This does not include the PEP484 type hints for now and this will require
# further enhancement however we can use it for lexical analysis for now.
def dijkstra(graph, start):
    # Initialize distances to all nodes as infinity except the start node
    distances = {node: float('inf') for node in graph}
    distances[start] = 0

    # Set to keep track of visited nodes
    visited = set()

    while len(visited) < len(graph):
        # Find the node with the smallest distance that hasn't been visited
        min_distance = float('inf')
        min_node = None
        for node, distance in distances.items():
            if node not in visited and distance < min_distance:
                min_distance = distance
                min_node = node

        # Mark the current node as visited
        visited.add(min_node)

        # Update distances to neighbors of the current node
        for neighbor, weight in graph[min_node].items():
            distance = distances[min_node] + weight
            # Update distance if shorter path is found
            if distance < distances[neighbor]:
                distances[neighbor] = distance

    return distances

if __name__ == "__main__":
    # Example graph
    graph = {
        'A': {'B': 1, 'C': 4},
        'B': {'A': 1, 'C': 2, 'D': 5},
        'C': {'A': 4, 'B': 2, 'D': 1},
        'D': {'B': 5, 'C': 1}
    }

    # Starting node
    start_node = 'A'

    # Run Dijkstra's algorithm
    shortest_distances = dijkstra(graph, start_node)

    # Print shortest distances from start node to all other nodes
    print("Shortest distances from node", start_node)
    for node, distance in shortest_distances.items():
        print(node, ":", distance)
