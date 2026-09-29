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
        if node.plug == self.left_soc and self.left_node is None:
            self.left_node = node
            return True
        elif self.left_node is not None and self.left_node.add_node(node):
            return True
        elif node.plug == self.right_soc and self.right_node is None:
            self.right_node = node
            return True
        elif self.right_node is not None and self.right_node.add_node(node):
            return True
        
        return False