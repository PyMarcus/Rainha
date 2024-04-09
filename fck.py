import heapq


def get_neighbors(node, map):
    neighbors = []
    dx = [0, 1, 0, -1]
    dy = [-1, 0, 1, 0]
    for i in range(4):
        nx = node[0] + dx[i]
        ny = node[1] + dy[i]
        if 0 <= nx < len(map) and 0 <= ny < len(map[0]) and map[nx][ny] != 'X' and map[nx][ny] != "I":
            neighbors.append((nx, ny))
    return neighbors


def heuristic(node, target):
    import math
    return math.sqrt((node[0] - target[0]) ** 2 + (node[1] - target[1]) ** 2)


def a_star(map, start, target):
    open_list = []
    closed_list = set()

    start_node = (start[0], start[1], 0, heuristic(start, target), None)
    heapq.heappush(open_list, (start_node[2] + start_node[3], start_node))

    while open_list:
        _, current_node = heapq.heappop(open_list)

        if (current_node[0], current_node[1]) == target:
            path = []
            while current_node:
                path.append((current_node[0], current_node[1]))
                current_node = current_node[4]
            return path[::-1]

        closed_list.add((current_node[0], current_node[1]))

        for neighbor_pos in get_neighbors((current_node[0], current_node[1]), map):
            neighbor_node = (
            neighbor_pos[0], neighbor_pos[1], current_node[2] + 1, heuristic(neighbor_pos, target), current_node)
            if (neighbor_node[0], neighbor_node[1]) in closed_list:
                continue
            if neighbor_node not in open_list:
                heapq.heappush(open_list, (neighbor_node[2] + neighbor_node[3], neighbor_node))

    return None


def printMatrix():
    print('-' * 30)
    for i in range(len(map)):
        for j in range(len(map[0])):
            print(map[i][j], end=' ')
        print()
    print('-' * 30)


def clear_blocks():
    for r in range(len(map)):
        for k in range(len(map[0])):
            if map[r][k] == 'X':
                map[r][k] = '_'


map = [
    ['X', 'P' ,'_' ,'F', '_'],
    ['X','_',  '_' ,'_','I'],
    ['_' , '_' ,'X', '_', '_'],
    ['_','X','_','_', 'O']
]

start = (0, 1)
target = (3, 4)
enemy = (1, 4)

path = a_star(map, start, target)

if path:
    print("Caminho encontrado:")
    print(path)
    a = None
    b = None
    up_enemy = True
    for r in range(len(map)):
        for k in range(len(map[0])):
            if (r, k) in path:
                if up_enemy:
                    up_enemy = False
                    map[enemy[0]-1][enemy[1]] = 'I'
                    map[enemy[0]][enemy[1]] = '_'
                else:
                    up_enemy = True
                    map[enemy[0] - 1][enemy[1]] = '_'
                    map[enemy[0]][enemy[1]] = 'I'
                path = a_star(map, start, target)
                if a is not None:
                    map[a][b] = '*'
                if map[r][k] == 'F':
                    print("Conseguiu bonus")
                    clear_blocks()
                    path = a_star(map, (r, k), target)
                map[r][k] = 'P'
                a = r
                b = k
                printMatrix()

        print()
else:
    print("Não há caminho encontrado.")
