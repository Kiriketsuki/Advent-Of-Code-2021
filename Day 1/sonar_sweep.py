# Long list of number. Iterate through and check if curr > prev. Increase count

import os

file_path = os.path.join(os.path.dirname(__file__), 'input.txt')

# read lines and remove newline
with open(file_path) as f:
    lines = f.readlines()
    for i, line in enumerate(lines):
        lines[i] = line.strip()


counter = -1 # to deal with the first input not having a greater one
prev = float('-inf')

for i in lines:
    curr = float(i)
    if curr > prev:
        counter += 1
    prev = curr

print(counter)