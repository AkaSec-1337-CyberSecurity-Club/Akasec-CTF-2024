import random


def initialize_maze(width, height):
    maze = [['1' for _ in range(width)] for _ in range(height)]
    return maze

def carve_passages_from(start_x, start_y, maze, width, height):
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    stack = [(start_x, start_y)]

    while stack:
        x, y = stack.pop()
        random.shuffle(directions)

        for dx, dy in directions:
            nx, ny = x + 2*dx, y + 2*dy
            if 1 <= nx < width-1 and 1 <= ny < height-1 and maze[ny][nx] == '1':
                maze[ny-dy][nx-dx] = '0'
                maze[ny][nx] = '0'
                stack.append((nx, ny))

def place_start_and_exit(maze, width, height):
    while True:
        sx, sy = random.randint(1, width-2), random.randint(1, height-2)
        if maze[sy][sx] == '0':
            maze[sy][sx] = 'S'
            break
    
    possible_exits = [(i, 0) for i in range(width) if maze[1][i] == '0'] + \
                     [(i, height-1) for i in range(width) if maze[height-2][i] == '0'] + \
                     [(0, i) for i in range(height) if maze[i][1] == '0'] + \
                     [(width-1, i) for i in range(height) if maze[i][width-2] == '0']
    
    ex, ey = random.choice(possible_exits)
    maze[ey][ex] = 'E'
    
    return sx, sy, ex, ey

def generate_maze(width, height):
    maze = initialize_maze(width, height)
    carve_passages_from(1, 1, maze, width, height)
    sx, sy, ex, ey = place_start_and_exit(maze, width, height)
    return maze
