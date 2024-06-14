import base64
from io import BytesIO

from PIL import Image, ImageDraw


def calculate_cell_size(width, height, max_dimension=2000):
    cell_size_width = max_dimension // width
    cell_size_height = max_dimension // height
    return min(cell_size_width, cell_size_height)

def create_maze_image(maze, max_dimension=2000, wall_color=(0, 0, 0), path_color=(255, 255, 255), start_color=(0, 255, 0), exit_color=(255, 0, 0)):
    height = len(maze)
    width = len(maze[0])

    cell_size = calculate_cell_size(width, height, max_dimension)
    img_width = width * cell_size
    img_height = height * cell_size

    image = Image.new("RGB", (img_width, img_height), path_color)
    draw = ImageDraw.Draw(image)

    for y, row in enumerate(maze):
        for x, cell in enumerate(row):
            color = path_color
            if cell == '1':
                color = wall_color
            elif cell == 'S':
                color = start_color
            elif cell == 'E':
                color = exit_color
            
            x0 = x * cell_size
            y0 = y * cell_size
            x1 = x0 + cell_size
            y1 = y0 + cell_size

            draw.rectangle([x0, y0, x1, y1], fill=color)

    return image

def image_to_base64(image):
    buffered = BytesIO()
    image.save(buffered, format="PNG")
    img_str = base64.b64encode(buffered.getvalue()).decode("utf-8")
    return img_str

def base64_to_image(img_str):
    img_data = base64.b64decode(img_str)
    image = Image.open(BytesIO(img_data))
    return image
