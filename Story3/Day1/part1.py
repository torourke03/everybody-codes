import sys


def parse_input(filename: str = "everybody_codes_e3_q01_p1.txt") -> dict[int, list[str]]:
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
    
    for scale, colors in scales.items():
        color_vals = get_vals(colors)
        if color_vals[1] > color_vals[0] and color_vals[1] > color_vals[2]:
            total += scale
    
    print(total)
    return


if __name__ == "__main__":
    if len(sys.argv) != 2:
        main(parse_input())
    else:
        main(parse_input(sys.argv[1]))