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


def parse_input(filename: str = "everybody_codes_e2025_q18_p1.txt"):
    plants = []
    with open(filename) as f:
        groups = f.read().split("\n\n")
    
    for group in groups:
        plants.append(parse_plant(group.splitlines()))
    
    return plants


def calc_energy(plant: Plant, plants: list[Plant]) -> int:
    # Base case free branch
    if plant.branches[0][0] == -1:
        return 1
    
    energy = 0
    for branch in plant.branches:
        energy += calc_energy(plants[branch[0] - 1], plants) * branch[1]
    if energy < plant.thickness:
        energy = 0
    return energy


def main():
    total = 0
    plants = parse_input()
    
    total = calc_energy(plants[-1], plants)
    
    print("Total:", total)
    return


if __name__ == "__main__":
    main()