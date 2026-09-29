class Node:
    def __init__(self, val: int, plug: str, left_soc: str, right_soc: str, data: str):
        self.val = val
        self.plug = plug
        self.left_soc = left_soc
        self.right_soc = right_soc
        self.data = data
        self.left_node = None
        self.right_node = None

    def add_node(self, node: Node) -> bool:
        split_plug = node.plug.split()
        split_left_soc = self.left_soc.split()
        split_right_soc = self.right_soc.split()
        if (split_plug[0] == split_left_soc[0] or split_plug[1] == split_left_soc[1]) and self.left_node is None:
            self.left_node = node
            return True
        elif self.left_node is not None and self.left_node.add_node(node):
            return True
        elif (split_plug[0] == split_right_soc[0] or split_plug[1] == split_right_soc[1]) and self.right_node is None:
            self.right_node = node
            return True
        elif self.right_node is not None and self.right_node.add_node(node):
            return True

        return False


def parse_input(filename: str = "everybody_codes_e3_q03_p2.txt") -> list[Node]:
    nodes = []
    with open(filename) as f:
        lines = f.readlines()
    for line in lines:
        s = line.split(", ")
        nodes.append(Node(int(s[0].split("=")[1]), s[1].split("=")[1], s[2].split("=")[1], s[3].split("=")[1],
                          s[4].split("=")[1]))

    return nodes


# Based on https://www.geeksforgeeks.org/dsa/inorder-traversal-of-binary-tree/
def traverse_tree(node: Node, res: list[int]) -> None:
    if node is None:
        return

    traverse_tree(node.left_node, res)
    res.append(node.val)
    traverse_tree(node.right_node, res)


def main():
    total = 0
    nodes = parse_input()
    root = nodes[0]
    for node in nodes[1:]:
        root.add_node(node)

    vals = []
    traverse_tree(root, vals)
    for x in range(len(vals)):
        total += (x + 1) * vals[x]

    print(total)


if __name__ == "__main__":
    main()