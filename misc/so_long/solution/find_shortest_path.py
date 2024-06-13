import heapq


def find_positions(map_data):
    start = None
    end = None
    for y, line in enumerate(map_data):
        for x, char in enumerate(line):
            if char == 'S':
                start = (y, x)
            elif char == 'E':
                end = (y, x)
    return start, end

def heuristic(a, b):
    return max(abs(a[0] - b[0]), abs(a[1] - b[1]))

def a_star(map_data, start, end):
    rows, cols = len(map_data), len(map_data[0])
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1), (-1, -1), (-1, 1), (1, -1), (1, 1)]
    direction_names = ['up', 'down', 'left', 'right', 'up-left', 'up-right', 'down-left', 'down-right']
    
    def is_valid(y, x):
        return 0 <= y < rows and 0 <= x < cols and map_data[y][x] != '1'
    
    open_set = [(0 + heuristic(start, end), 0, start)]
    came_from = {}
    g_score = {start: 0}
    
    while open_set:
        _, current_g, current = heapq.heappop(open_set)
        
        if current == end:
            break
        
        for i, (dy, dx) in enumerate(directions):
            neighbor = (current[0] + dy, current[1] + dx)
            if is_valid(neighbor[0], neighbor[1]):
                tentative_g_score = current_g + 1
                if neighbor not in g_score or tentative_g_score < g_score[neighbor]:
                    g_score[neighbor] = tentative_g_score
                    f_score = tentative_g_score + heuristic(neighbor, end)
                    heapq.heappush(open_set, (f_score, tentative_g_score, neighbor))
                    came_from[neighbor] = (current, direction_names[i])
    
    path = []
    moves = []
    current = end
    while current in came_from:
        path.append(current)
        current, move = came_from[current]
        moves.append(move)
    if path:
        path.append(start)
        path.reverse()
        moves.reverse()
    
    return {'moves': moves, 'path': path}

def find_shortest_path(map_data):
    start, end = find_positions(map_data)
    if not start or not end:
        return None
    
    return a_star(map_data, start, end)
