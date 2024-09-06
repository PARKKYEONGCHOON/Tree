class Node {
    var value: Int
    var left: Node?
    var right: Node?
    var height: Int

    init(value: Int) {
        self.value = value
        self.height = 1
    }
}

class AVLTree {
    func insert(_ node: Node?, _ value: Int) -> Node? {
        guard let node = node else {
            return Node(value: value)
        }

        if value < node.value {
            node.left = insert(node.left, value)
        } else if value > node.value {
            node.right = insert(node.right, value)
        }

        node.height = 1 + max(height(node.left), height(node.right))

        let balance = getBalance(node)

        if balance > 1 && value < node.left!.value {
            return rightRotate(node)
        }
        if balance < -1 && value > node.right!.value {
            return leftRotate(node)
        }
        if balance > 1 && value > node.left!.value {
            node.left = leftRotate(node.left)
            return rightRotate(node)
        }
        if balance < -1 && value < node.right!.value {
            node.right = rightRotate(node.right)
            return leftRotate(node)
        }

        return node
    }

    func inorder(_ node: Node?) {
        if let node = node {
            inorder(node.left)
            print(node.value, terminator: " ")
            inorder(node.right)
        }
    }

    func height(_ node: Node?) -> Int {
        return node?.height ?? 0
    }

    func getBalance(_ node: Node?) -> Int {
        return height(node?.left) - height(node?.right)
    }

    func rightRotate(_ y: Node) -> Node {
        let x = y.left
        let T2 = x?.right

        x?.right = y
        y.left = T2

        y.height = max(height(y.left), height(y.right)) + 1
        x?.height = max(height(x?.left), height(x?.right)) + 1

        return x!
    }

    func leftRotate(_ x: Node) -> Node {
        let y = x.right
        let T2 = y?.left

        y?.left = x
        x.right = T2

        x.height = max(height(x.left), height(x.right)) + 1
        y?.height = max(height(y?.left), height(y?.right)) + 1

        return y!
    }
}

// Usage
let tree = AVLTree()
var root: Node? = nil
let values = [10, 20, 30, 40, 50, 25]

for value in values {
    root = tree.insert(root, value)
}

tree.inorder(root)  // Output: 10 20 25 30 40 50