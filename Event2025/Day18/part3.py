class Plant:
    def __init__(self, thickness: int, branches: list[tuple[int, int]]):
        self.thickness = thickness
        self.branches = branches


def parse_plant(group: list[str]) -> Plant:
    thickness = int(group[0].split()[-1][:-1])
    branches = []
    for line in group[1:]:
        split_line = line.split()
        if split_line[1] == "free":
            branch = (-1, int(split_line[-1]))
        else:
            branch = (int(split_line[4]), int(split_line[-1]))
        branches.append(branch)
    
    return Plant(thickness, branches)


def parse_input(filename: str = "everybody_codes_e2025_q18_p3.txt"):
    plants = []
    with open(filename) as f:
        groups = f.read().split("\n\n")

    test_cases = [[int(x) for x in string.split()] for string in groups[-1].strip().splitlines()]
    groups.pop()
    for group in groups:
        plants.append(parse_plant(group.splitlines()))
    
    return plants, test_cases


def calc_energy(plants: list[Plant], index: int, test_case: list[int]) -> int:
    # Base case free branch
    if plants[index].branches[0][0] == -1:
        return test_case[index]
    
    energy = 0
    for branch in plants[index].branches:
        energy += calc_energy(plants, branch[0] - 1, test_case) * branch[1]
    if energy < plants[index].thickness:
        energy = 0
    return energy


# The input data is done in a way that all free-branch plants only contribute positively or negatively
def find_max_case(plants: list[Plant]) -> list[int]:
    branch_start_index = 0
    for index, plant in enumerate(plants):
        if plant.branches[0][0] != -1:
            branch_start_index = index
            break
    
    max_case = [0] * branch_start_index
    for plant in plants[branch_start_index:]:
        for branch in plant.branches:
            if branch[0] <= branch_start_index:
                if branch[1] > 0:
                    max_case[branch[0] - 1] = 1
    
    return max_case


def main():
    total = 0
    plants, test_cases = parse_input()
    
    max_energy = calc_energy(plants, len(plants) - 1, find_max_case(plants))
    for test_case in test_cases:
        energy = calc_energy(plants, len(plants) - 1, test_case)
        if energy > 0:
            total += max_energy - energy
    
    print("Total:", total)
    return


if __name__ == "__main__":
    main()