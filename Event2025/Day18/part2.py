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


def parse_input(filename: str = "everybody_codes_e2025_q18_p2.txt"):
    plants = []
    with open(filename) as f:
        groups = f.read().split("\n\n")
    
    test_cases = groups[-1].strip().splitlines()
    groups.pop()
    for group in groups:
        plants.append(parse_plant(group.splitlines()))
    
    return plants, test_cases


def calc_energy(plants: list[Plant], index: int, test_case: list[str]) -> int:
    # Base case free branch
    if plants[index].branches[0][0] == -1:
        return int(test_case[index])
    
    energy = 0
    for branch in plants[index].branches:
        energy += calc_energy(plants, branch[0] - 1, test_case) * branch[1]
    if energy < plants[index].thickness:
        energy = 0
    return energy


def main():
    plants, test_cases = parse_input()
    
    total = sum(calc_energy(plants, len(plants) - 1, test_cases[x].split()) for x in range(len(test_cases)))
    
    print("Total:", total)
    return


if __name__ == "__main__":
    main()