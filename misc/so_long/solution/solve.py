from find_shortest_path import find_shortest_path
from map_to_image import base64_to_image
from pwn import remote


def detect_square_size(image, color):
    pixels = image.load()
    width, height = image.size

    for y in range(height):
        for x in range(width):
            if pixels[x, y] == color:
                # Detect width and height of the square
                square_width = 0
                square_height = 0
                
                while x + square_width < width and pixels[x + square_width, y] == color:
                    square_width += 1
                
                while y + square_height < height and pixels[x, y + square_height] == color:
                    square_height += 1
                
                return square_width, square_height
    return None, None

def extract_maze_from_image(image):
    start_color = (0, 255, 0)  # Green
    exit_color = (255, 0, 0)  # Red
    wall_color = (0, 0, 0)  # Black
    path_color = (255, 255, 255)  # White

    cell_width, cell_height = detect_square_size(image, start_color)
    if cell_width is None or cell_height is None:
        cell_width, cell_height = detect_square_size(image, exit_color)
    if cell_width is None or cell_height is None:
        raise ValueError("Could not determine cell size")

    pixels = image.load()
    width, height = image.size

    maze = []
    for y in range(0, height, cell_height):
        row = []
        for x in range(0, width, cell_width):
            if pixels[x, y] == wall_color:
                row.append('1')
            elif pixels[x, y] == path_color:
                row.append('0')
            elif pixels[x, y] == start_color:
                row.append('S')
            elif pixels[x, y] == exit_color:
                row.append('E')
        maze.append(row)
    return maze

def connect_and_solve(host, port, rounds=1000):
    conn = remote(host, port)

    for round in range(1, rounds + 1):
        round_info = conn.recvuntil(b'/').decode()
        print(round_info.strip(), end='')
        rounds_info = conn.recvline().decode().strip()
        print(rounds_info)

        b64_image = conn.recvline().strip().decode()
        print(f"Base64 Image: {b64_image}")

        conn.recvline()  # Read 'Enter your moves:\n'
        
        # Decode the base64 image
        image = base64_to_image(b64_image)

        # Convert the image to a maze representation
        maze = extract_maze_from_image(image)

        # Find the shortest path
        moves = find_shortest_path(maze)['moves']

        # Print the moves before sending them
        moves_str = ' '.join(moves)
        print(f"Moves: {moves_str}")

        # Send the moves to the server
        conn.sendline(moves_str.encode())

        # Read 2 lines
        response = conn.recvline().decode().strip()
        response += "\n" + conn.recvline().decode().strip()
        print(f"Server Response: {response}")

        if 'Congratulations!' not in response:
            break

    print(conn.recvall().decode())

    conn.close()

if __name__ == "__main__":
    host = 'localhost'
    port = 4441
    connect_and_solve(host, port)
