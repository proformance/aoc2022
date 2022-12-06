from os import environ

all_unique = lambda s, n : len(set(s[0:n])) == n

# Don't do recursion, stack will grow too big
#
# def fun(x, t):
#     return fun(x[1:], t) if not all_unique(x) else (len(t) - len(x) + 4)

def solve(input, distict_characters=4):
    i=distict_characters
    while not all_unique(input, distict_characters):
        input = input[1:]
        i+=1
    return i

def getSolutionPart1(input):
    return solve(input, distict_characters=4)

def getSolutionPart2(input):
    return solve(input, distict_characters=14)

with open('input.txt') as f:
    file_input = f.readline()

print('Python')
part = environ.get('part')

if part == 'part2':
    print(getSolutionPart2(file_input))
else:
    print(getSolutionPart1(file_input))