import sys
from math import inf


def parse_input(filename: str = "everybody_codes_e3_q01_p2.txt") -> dict[int, list[str]]:
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
    shine_vals = dict()
    
    max_shine = 0
    for scale, colors in scales.items():
        color_vals = get_vals(colors)
        if color_vals[-1] in shine_vals.keys():
            x = shine_vals[color_vals[-1]]
            x.append((sum(color_vals[:-1]), scale))
        else:
            shine_vals[color_vals[-1]] = [(sum(color_vals[:-1]), scale)]
        if color_vals[-1] > max_shine:
            max_shine = color_vals[-1]
    
    lowest_color = inf
    for color_sum, scale in shine_vals[max_shine]:
        if color_sum < lowest_color:
            lowest_color = color_sum
            total = scale

    print(total)
    return


if __name__ == "__main__":
    if len(sys.argv) != 2:
        main(parse_input())
    else:
        main(parse_input(sys.argv[1]))