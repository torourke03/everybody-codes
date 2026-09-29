import sys


def parse_input(filename: str = "everybody_codes_e3_q01_p3.txt") -> dict[int, list[str]]:
    scales = {}
    with open(filename) as f:
        lines = f.readlines()
        for line in lines:
            val = int(line.split(":")[0])
            colors = line.split(":")[1].split()
            scales[val] = colors

    return scales


def get_vals(colors: list[str]) -> list[int]:
    vals = []
    for color in colors:
        bin_str = ""
        for c in color:
            if c.isupper():
                bin_str += "1"
            else:
                bin_str += "0"
        vals.append(int(bin_str, base=2))

    return vals


def main(scales: dict[int, list[str]]) -> None:
    total = 0
    groups = {x: [] for x in range(6)}
    
    for scale, colors in scales.items():
        color_vals = get_vals(colors)
        shine = color_vals[-1]
        if shine >= 33:
            if color_vals[1] < color_vals[0] > color_vals[2]:
                groups[0].append(scale)
            if color_vals[0] < color_vals[1] > color_vals[2]:
                groups[1].append(scale)
            if color_vals[0] < color_vals[2] > color_vals[1]:
                groups[2].append(scale)
        if shine <= 30:
            if color_vals[1] < color_vals[0] > color_vals[2]:
                groups[3].append(scale)
            if color_vals[0] < color_vals[1] > color_vals[2]:
                groups[4].append(scale)
            if color_vals[0] < color_vals[2] > color_vals[1]:
                groups[5].append(scale)
    
    max_size = 0
    for sums in groups.values():
        if len(sums) > max_size:
            max_size = len(sums)
            total = sum(sums)

    print(total)
    return


if __name__ == "__main__":
    if len(sys.argv) != 2:
        main(parse_input())
    else:
        main(parse_input(sys.argv[1]))