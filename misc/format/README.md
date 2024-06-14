# Challenge Name: Format

## Challenge Description

The goal of this challenge is to validate a user-provided string containing format specifiers. The allowed format specifiers are `%s`, `%d`, `%f`, and `%r`. The challenge script enforces the following rules:
- No other format specifiers are allowed.
- The number of `%s` specifiers cannot exceed `maxIterations + 1`.
- The number of `%d`, `%f`, and `%r` specifiers cannot exceed `maxIterations`.

The input string is checked against these rules, and if valid, it prints a formatted string using provided arguments.




## Files

1. `chall.py`: The main challenge script that validates the input string.
2. `generator.py`: The script that generates random arguments and the flag, saving them to `args.json`.

## How to Run the Challenge

1. **Generate Arguments:**  
   Run the `generator.py` script to create the `args.json` file containing the arguments.
   ```bash
   python3 generator.py
   ```

2. **Run the Challenge Script:**  
   Execute the `chall.py` script to start the challenge.
   ```bash
   python3 chall.py
   ```

## Solution Overview
- When you use all format specifiers and some of them are not compatible with the variable type, it will throw an error. If you test each specifier individually, it will throw one of two errors:
  - ```TypeError: must be real number, not str```: If the format specifier is incorrect, it will throw an error indicating that you did not provide the correct format specifier. 
  - ```TypeError: not all arguments converted during string formatting```: If the format specifier is correct but not compatible with the variable type, it will throw an error indicating that not all format specifiers are compatible.
  
  You can use these error messages to determine the correct format specifiers one by one. Since `%s` and `%r` can be compatible with all variable types, you should always start with `%f` or `%d`, and then test `%s` and `%r`.

The solution involves using a script (`solve.py`) that:
1. Sends a payload with different format specifiers to the challenge script.
2. Receives and interprets the response.
3. Iteratively builds the correct payload that passes all checks in `chall.py` and reveals the flag.

## How to Run the Solution

Execute the `solve.py` script to solve the challenge.
```bash
python3 solve.py
```

The script will interact with `chall.py`, testing various combinations of format specifiers until it finds the correct one that reveals the flag.
