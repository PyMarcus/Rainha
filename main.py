from math import sqrt
from queue import PriorityQueue
from typing import Any

from pyamaze import maze, agent, COLOR

start_x_position: int = 1
start_y_position: int = 1
end_x_position: int = 10
end_y_position: int = 10


def h_store(startx: int, starty: int,
            endx: int, endy: int) -> float:
    x: float = (endx - startx) ** 2
    y: float = (endy - starty) ** 2
    return sqrt(x + y)


def a_star(mazze: maze) -> dict[Any, tuple[int, int] | Any]:
    # matriz de distancias com todos os valores infinitos
    f_score = {position: float("inf") for position in mazze.grid}
    # definicao do valor inicial de passos como 0
    start_position = (start_x_position, start_y_position)
    g_score = {start_position: 0}
    f_score[start_position] = g_score[start_position] + h_store(start_x_position, start_y_position,
                                                                end_x_position, end_y_position)
    q = PriorityQueue()
    content = (f_score[start_position],  h_store(start_x_position, start_y_position,
                                                                end_x_position, end_y_position),
               start_position)

    q.put(content)
    path = {}
    while not q.empty():
        distance, trig, celula = q.get()
        if celula == (end_x_position, end_y_position):
            break

        for direction in "NSEW":
            if mazze.maze_map[celula][direction] == 1:
                line, column = celula
                next_celula = None
                if direction == "N":
                    next_celula = (line-1, column)
                elif direction == "S":
                    next_celula = (line+1, column)
                elif direction == "E":
                    next_celula = (line, column+1)
                elif direction == "W":
                    next_celula = (line, column-1)
                next_gscore = g_score[celula] + 1
                next_fscore = next_gscore + h_store(next_celula[0], next_celula[1],
                                                    end_x_position, end_y_position)
                if next_fscore < f_score[next_celula]:
                    f_score[next_celula] = next_fscore
                    g_score[next_celula] = next_gscore
                    content = (next_fscore, h_store(next_celula[0], next_celula[1],
                                                        end_x_position, end_y_position),next_celula)
                    q.put(content)
                    path[next_celula] = celula
    final_path = {}
    analyzed = (end_x_position, end_y_position)
    while analyzed != start_position:
        final_path[path[analyzed]] = analyzed
        analyzed = path[analyzed]
    return final_path


if __name__ == '__main__':
    mazze = maze()
    mazze.CreateMaze(6, 6)
    character = agent(mazze, start_x_position, start_y_position, filled=True, footprints=True)
    destiny = agent(mazze, filled=True, footprints=True, color=COLOR.red)
    result = a_star(mazze)
    mazze.tracePath({character: result}, delay=300)
    mazze.run()
