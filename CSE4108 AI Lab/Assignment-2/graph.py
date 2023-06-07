def find_path_length(graph, start, end, acc_distance=0):
    if start == end:
        return acc_distance

    if not graph[start]:
        return float('inf')

    min_distance = float('inf')
    for neighbor, weight in graph[start]:
        length = find_path_length(graph, neighbor, end, acc_distance + weight)
        min_distance = min(min_distance, length)

    return min_distance


graph = {
    'i': [('a', 35), ('b', 45)],
    'a': [('c', 22), ('d', 32)],
    'b': [('d', 28), ('e', 36), ('f', 27)],
    'c': [('d', 31), ('g', 47)],
    'd': [('g', 30)],
    'e': [('g', 26)],
    'g': []
}



path_length = find_path_length(graph, 'a', 'g')


print("Length of the path between 'a' and 'g':", path_length)
