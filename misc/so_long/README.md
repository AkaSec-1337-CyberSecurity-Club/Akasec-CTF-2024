# [**so_long**](#)

## Description:
* How long will it take you to escape the maze? Find the shortest path to the exit of the maze.

## Difficulty:
* Medium

## Objective:
The objective of this challenge is to solve a maze game, where the maze is represented as an image and the player must find the shortest path from the start to the exit.

## Deployment:
```sh
docker build -t so-long .
docker run -p 4441:4441 so-long
```

## Solution:
The solution involves connecting to the server and base64-encoded image. After decoding the image, determine the cell size by analyzing the colors of the start and exit squares. Extract the maze from the image and find the shortest path through it. Send the sequence of moves to the server and repeat this process for 1000 rounds. Upon completing all rounds, you will receive the flag.