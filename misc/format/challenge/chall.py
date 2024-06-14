import json
import re

def checker(input_string, args):
    print(input_string % tuple(args))

# Read the arguments from the file
with open('args.json', 'r') as file:
    args = json.load(file)

maxIterations = (len(args) - 1) // 4  # Number of iterations used in generate_args
input_string = input("Enter a string: ")
# Regex to find any format specifiers other than %s, %d, %f, and %r
other_specifiers_pattern = re.compile(r'%[^sdfr]')

if input_string.count("%s") > maxIterations + 1:
    print("Too many %s specifiers!")
elif input_string.count("%d") > maxIterations:
    print("Too many %d specifiers!")
elif input_string.count("%f") > maxIterations:
    print("Too many %f specifiers!")
elif input_string.count("%r") > maxIterations:
    print("Too many %r specifiers!")
elif other_specifiers_pattern.search(input_string):
    print("Unallowed format specifiers used!")
else:
    checker(input_string, args)
