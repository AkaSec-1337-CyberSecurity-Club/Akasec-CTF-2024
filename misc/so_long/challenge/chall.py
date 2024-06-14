import os
import random

from find_shortest_path import find_shortest_path
from map_generator import generate_maze
from map_to_image import create_maze_image, image_to_base64

rounds = 1000
min_size = 99
max_size = 499

FLAG = os.environ.get("FLAG", "AKASEC{this_is_a_fake_flag}")

print('''Welcome to so_long!

Your goal is to find the shortest path from the start point (green square) to the end point (red square).
You can move up, down, left, right, up-left, up-right, down-left, and down-right.
Insert your moves separated by spaces. For example: "up down-right right down".

Good luck!''')

for _ in range(rounds):
    print(f"\nRound {_ + 1}/{rounds}:")

    # generate random height and width, odd numbers
    width = random.randint(min_size, max_size)
    height = random.randint(min_size, max_size)
    if width % 2 == 0:
        width += 1
    if height % 2 == 0:
        height += 1
    
    # generate a maze
    maze = generate_maze(width, height)

    # create an image of the maze
    image = create_maze_image(maze)
    img_base64 = image_to_base64(image)
    print(img_base64)

    # find the shortest path
    shortest_path = find_shortest_path(maze)
    moves = shortest_path['moves']
    trajectory = shortest_path['path']

    # get moves to reach the exit
    print("Enter your moves:")
    user_moves = input().strip().split()

    # validate the moves
    if not all(move in ["up", "down", "left", "right", "up-left", "up-right", "down-left", "down-right"] for move in user_moves):
        print("Invalid move!")
        exit(1)
    
    # check if the user has made too many moves
    if len(user_moves) > len(moves):
        print("Too many moves!")
        exit(1)

    # validate the moves
    y, x = trajectory[0]
    for move in user_moves:
        dx, dy = {
            "up": (0, -1),
            "down": (0, 1),
            "left": (-1, 0),
            "right": (1, 0),
            "up-left": (-1, -1),
            "up-right": (1, -1),
            "down-left": (-1, 1),
            "down-right": (1, 1),
        }[move]
        x += dx
        y += dy
        if maze[y][x] == "1":
            print("Invalid move!")
            exit(1)
    if (y, x) == trajectory[-1]:
        print("Congratulations! You found the shortest path.")
        print("Moving on to the next round...")
    else:
        print("Wrong path!")
        exit(1)

print("Congratulations! You have completed all rounds.")
print("Here is your flag:")
print(FLAG)
