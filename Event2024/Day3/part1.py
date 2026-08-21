def main(filename: str) -> None:
    lines = []
    total = 0
    file = open(filename, "r")
    for line in file:
        lines.append(list(line.strip()))
    file.close()

    print(lines)
    subtotal = 0
    for line in lines:
        subtotal += line.count("#")
    total += subtotal


    while subtotal > 0:
        lines = reduce_map(lines)
        subtotal = 0
        for line in lines:
            subtotal += line.count("#")
        print(lines)
        total += subtotal

    print("Total:", total)
    return


def reduce_map(lines: list[list[str]]) -> list[list[str]]:
    reduced_lines = [l.copy() for l in lines]
    for row in range(len(lines)):
        for col in range(len(lines[row])):
            if lines[row][col] == "#":
                # Check if there's an . adjacent to the #
                if lines[row - 1][col] == "." or lines[row + 1][col] == "." or lines[row][col - 1] == "." or lines[row][col + 1] == ".":
                    reduced_lines[row][col] = "."
    return reduced_lines


if __name__ == '__main__':
    main("input2.txt")
