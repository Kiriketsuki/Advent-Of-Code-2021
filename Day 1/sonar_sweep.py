# Long list of number. Iterate through and check if curr > prev. Increase count

# * part 1
import os

file_path = os.path.join(os.path.dirname(__file__), 'input.txt')

# read lines and remove newline
with open(file_path) as f:
    lines = f.readlines()
    for i, line in enumerate(lines):
        lines[i] = line.strip()

def count_bigger(arr):
    counter = -1 # to deal with the first input not having a greater one
    prev = float('-inf')

    for i in arr:
        curr = float(i)
        if curr > prev:
            counter += 1
        prev = curr

    return counter

print(count_bigger(lines))

# * part 2

to_subtract = 0
new_array = []

for i in range(2, len(lines)): 
    sum = int(lines[i-2]) + int(lines[i-1]) + int(lines[i])
    new_array.append(sum)

print(count_bigger(new_array))

