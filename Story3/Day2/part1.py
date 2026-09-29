import sys


def parse_input(filename: str = "everybody_codes_e3_q02_p1.txt") -> tuple[int, int]:
    start_pos = tuple()
    bone_pos = tuple()
    with open(filename) as f:
        lines = f.readlines()
        for i in range(len(lines)):
            if "@" in lines[i]:
                start_pos = (i, lines[i].index("@"))
            if "#" in lines[i]:
                bone_pos = (i, lines[i].index("#"))
    
    return bone_pos[0] - start_pos[0], bone_pos[1] - start_pos[1]


pos = (0, 0)
bone = tuple()
visited = set(tuple())
directions = [(-1, 0), (0, 1), (1, 0), (0, -1)]
total = 0
if len(sys.argv) > 1:
    bone = parse_input(sys.argv[1])
else:
    bone = parse_input()

direction = 0
visited.add(pos)
while pos != bone:
    if (pos[0] + directions[direction][0], pos[1] + directions[direction][1]) not in visited:
        pos = pos[0] + directions[direction][0], pos[1] + directions[direction][1]
        visited.add(pos)
        total += 1
        
    direction = (direction + 1) % len(directions)

print(total)