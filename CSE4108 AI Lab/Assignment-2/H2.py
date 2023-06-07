# Goal configuration
goal_config = {
    1: (1, 1, 1),
    2: (2, 1, 2),
    3: (3, 1, 3),
    4: (4, 2, 3),
    5: (5, 3, 3),
    6: (6, 3, 2),
    7: (7, 3, 1),
    8: (8, 2, 1)
}

goal_blank = (2, 2)

# Target configuration
target_config = {
    1: (1, 1, 2),
    2: (2, 1, 3),
    3: (3, 2, 1),
    4: (4, 2, 3),
    5: (5, 3, 3),
    6: (6, 2, 2),
    7: (7, 3, 2),
    8: (8, 1, 1)
}

target_blank = (3, 1)

# Function to calculate the Manhattan distance between two cells
def manhattan_distance(cell1, cell2):
    x1, y1 = cell1[1:]
    x2, y2 = cell2[1:]
    return abs(x1 - x2) + abs(y1 - y2)

# Function to calculate the heuristic values
def calculate_heuristics():
    heuristics = []
    for tile in range(1, 9):
        tile_goal = goal_config[tile]
        tile_target = target_config[tile]
        distance = manhattan_distance(tile_goal, tile_target)
        heuristics.append(distance)
    return heuristics

# Calculate heuristics for each tile
heuristics = calculate_heuristics()

# Calculate the sum of heuristics
total_heuristic = sum(heuristics)

# Output
print("Heuristics:", total_heuristic)
