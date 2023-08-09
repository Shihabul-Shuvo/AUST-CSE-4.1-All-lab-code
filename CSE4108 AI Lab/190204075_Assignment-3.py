from queue import PriorityQueue

def greedy_bfs(start_node, goal_node, heuristic):
    open_list = PriorityQueue()
    open_list.put((heuristic[start_node], start_node))

    closed_list = []
    path = {}

    while not open_list.empty():
        current_node = open_list.get()[1]

        if current_node == goal_node:
            # Reconstruct the path
            final_path = []
            while current_node in path:
                final_path.append(current_node)
                current_node = path[current_node]
            final_path.append(start_node)
            final_path.reverse()
            return final_path

        closed_list.append(current_node)

        for neighbor in graph[current_node]:
            if neighbor not in closed_list:
                open_list.put((heuristic[neighbor], neighbor))
                path[neighbor] = current_node

    return None

# Graph representation (adjacency list)
graph = {
    'A': ['B', 'C'],
    'B': ['D', 'E'],
    'C': ['F'],
    'D': [],
    'E': ['F'],
    'F': []
}

# Heuristic values for each node
heuristic = {
    'A': 5,
    'B': 3,
    'C': 2,
    'D': 7,
    'E': 4,
    'F': 1
}

start_node = 'A'
goal_node = 'F'

path = greedy_bfs(start_node, goal_node, heuristic)

if path is not None:
    print("Path found:", ' -> '.join(path))
else:
    print("No path found")
