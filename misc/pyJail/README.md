# [**pyJail**](#)

## Description:
* Sigh.. another python jail to escape.

## Difficulty:
* Easy

## Objective:
The objective of this challenge is to escape the jail by using only 16 characters of printable ascii.

## Deployment:
```sh
docker build -t py-jail .
docker run -p 4449:4449 py-jail
```

## Solution:
```python
𝘱𝘳𝘪𝘯𝘵(*𝘰𝘱𝘦𝘯("flag.txt"))
```