def find_number_connectedways(matrix, x, y, color, visited):
    neighbors = get_neighbors(matrix, x, y)
    count = 1
    visited.append(node_key([x, y]))
    for n in neighbors:
        if node_key(n) not in visited:
            if get_color(matrix, n[0], n[1]) == color:
                count += find_number_connectedways(matrix, n[0], n[1], color, visited)

    return count


def find_maximum(grid):
    maximum = -10000
    for x in range(len(grid)):
        for y in range(len(grid[0])):
            visited = []
            color = get_color(grid, x, y)
            maximum = max(find_number_connectedways(grid, x, y, color, visited), maximum)
    return maximum


def get_neighbors(grid, x, y):
    neighbors = []
    if x - 1 >= 0:
        neighbors.append([x - 1, y])
    if y - 1 >= 0:
        neighbors.append([x, y - 1])
    if x + 1 < len(grid):
        neighbors.append([x + 1, y])
    if y + 1 < len(grid[0]):
        neighbors.append([x, y + 1])
    return neighbors


def get_color(grid, x, y):
    return grid[x][y]


def node_key(node):
    return str(node[0]) + str(node[1])


m, n = map(int, input().split())
matrix = []
for i in range(m):
    matrix.append(list(map(int, input().split())))
print(find_maximum(matrix))
