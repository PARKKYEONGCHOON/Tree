class BTreeNode:
    def __init__(self, leaf=False):
        self.leaf = leaf
        self.keys = []
        self.children = []

class BTree:
    def __init__(self, t):
        self.root = BTreeNode(True)
        self.t = t  # 최소 차수

    def search(self, node, key):
        i = 0
        while i < len(node.keys) and key > node.keys[i]:
            i += 1
        if i < len(node.keys) and key == node.keys[i]:
            return (node, i)
        elif node.leaf:
            return None
        else:
            return self.search(node.children[i], key)

    def insert(self, key):
        root = self.root
        if len(root.keys) == 2 * self.t - 1:
            s = BTreeNode()
            self.root = s
            s.children.append(root)
            self.split_child(s, 0)
            self.insert_non_full(s, key)
        else:
            self.insert_non_full(root, key)

    def insert_non_full(self, node, key):
        i = len(node.keys) - 1
        if node.leaf:
            node.keys.append(0)
            while i >= 0 and key < node.keys[i]:
                node.keys[i + 1] = node.keys[i]
                i -= 1
            node.keys[i + 1] = key
        else:
            while i >= 0 and key < node.keys[i]:
                i -= 1
            i += 1
            if len(node.children[i].keys) == 2 * self.t - 1:
                self.split_child(node, i)
                if key > node.keys[i]:
                    i += 1
            self.insert_non_full(node.children[i], key)

    def split_child(self, parent, i):
        t = self.t
        node = parent.children[i]
        new_node = BTreeNode(node.leaf)
        parent.children.insert(i + 1, new_node)
        parent.keys.insert(i, node.keys[t - 1])
        new_node.keys = node.keys[t:(2 * t - 1)]
        node.keys = node.keys[0:(t - 1)]
        if not node.leaf:
            new_node.children = node.children[t:(2 * t)]
            node.children = node.children[0:(t - 1)]

    def inorder_traversal(self, node):
        i = 0
        for i in range(len(node.keys)):
            if not node.leaf:
                self.inorder_traversal(node.children[i])
            print(node.keys[i], end=" ")
        if not node.leaf:
            self.inorder_traversal(node.children[i + 1])

# Usage
b_tree = BTree(3)
values = [10, 20, 5, 6, 12, 30, 7, 17]
for v in values:
    b_tree.insert(v)

b_tree.inorder_traversal(b_tree.root)  # Output: 5 6 7 10 12 17 20 30