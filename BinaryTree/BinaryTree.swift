class Node {
    var value: Int
    var left: Node?
    var right: Node?

    init(value: Int) {
        self.value = value
        self.left = nil
        self.right = nil
    }
}

class BinaryTree {
    var root: Node?

    init() {
        root = nil
    }

    func insert(value: Int) {
        root = insertRec(node: root, value: value)
    }

    private func insertRec(node: Node?, value: Int) -> Node {
        guard let node = node else {
            return Node(value: value)
        }

        if value < node.value {
            node.left = insertRec(node: node.left, value: value)
        } else {
            node.right = insertRec(node: node.right, value: value)
        }

        return node
    }

    func inorderTraversal(node: Node?) {
        if let node = node {
            inorderTraversal(node: node.left)
            print(node.value, terminator: " ")
            inorderTraversal(node: node.right)
        }
    }
}

// Usage
let tree = BinaryTree()
tree.insert(value: 10)
tree.insert(value: 5)
tree.insert(value: 15)
tree.insert(value: 3)
tree.insert(value: 7)

tree.inorderTraversal(node: tree.root)