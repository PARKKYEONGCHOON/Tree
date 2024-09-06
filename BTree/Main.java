package study.Tree.BTree;

import java.util.ArrayList;

class BTreeNode {
    ArrayList<Integer> keys;
    ArrayList<BTreeNode> children;
    boolean leaf;

    BTreeNode(boolean leaf) {
        this.leaf = leaf;
        keys = new ArrayList<>();
        children = new ArrayList<>();
    }
}

class BTree {
    private BTreeNode root;
    private int t;

    BTree(int t) {
        this.t = t;
        root = new BTreeNode(true);
    }

    void insert(int key) {
        BTreeNode r = root;
        if (r.keys.size() == 2 * t - 1) {
            BTreeNode s = new BTreeNode(false);
            root = s;
            s.children.add(r);
            splitChild(s, 0);
            insertNonFull(s, key);
        } else {
            insertNonFull(r, key);
        }
    }

    private void insertNonFull(BTreeNode node, int key) {
        int i = node.keys.size() - 1;
        if (node.leaf) {
            node.keys.add(0);
            while (i >= 0 && key < node.keys.get(i)) {
                node.keys.set(i + 1, node.keys.get(i));
                i--;
            }
            node.keys.set(i + 1, key);
        } else {
            while (i >= 0 && key < node.keys.get(i))
                i--;
            i++;
            if (node.children.get(i).keys.size() == 2 * t - 1) {
                splitChild(node, i);
                if (key > node.keys.get(i))
                    i++;
            }
            insertNonFull(node.children.get(i), key);
        }
    }

    private void splitChild(BTreeNode parent, int i) {
        BTreeNode y = parent.children.get(i);
        BTreeNode z = new BTreeNode(y.leaf);
        parent.children.add(i + 1, z);
        parent.keys.add(i, y.keys.get(t - 1));

        for (int j = 0; j < t - 1; j++)
            z.keys.add(y.keys.remove(t));

        if (!y.leaf) {
            for (int j = 0; j < t; j++)
                z.children.add(y.children.remove(t));
        }
    }

    void inorderTraversal(BTreeNode node) {
        for (int i = 0; i < node.keys.size(); i++) {
            if (!node.leaf)
                inorderTraversal(node.children.get(i));
            System.out.print(node.keys.get(i) + " ");
        }
        if (!node.leaf)
            inorderTraversal(node.children.get(node.keys.size()));
    }

    BTreeNode getRoot() {
        return root;
    }
}

public class Main {
    public static void main(String[] args) {
        BTree bTree = new BTree(3);
        int[] values = {10, 20, 5, 6, 12, 30, 7, 17};
        for (int value : values)
            bTree.insert(value);

        bTree.inorderTraversal(bTree.getRoot());  // Output: 5 6 7 10 12 17 20 30
    }
}
