using System;
using System.Collections.Generic;

class BTreeNode
{
    public List<int> Keys;
    public List<BTreeNode> Children;
    public bool Leaf;

    public BTreeNode(bool leaf)
    {
        Leaf = leaf;
        Keys = new List<int>();
        Children = new List<BTreeNode>();
    }
}

class BTree
{
    private int T;
    private BTreeNode root;

    public BTree(int t)
    {
        T = t;
        root = new BTreeNode(true);
    }

    public void Insert(int key)
    {
        BTreeNode r = root;
        if (r.Keys.Count == 2 * T - 1)
        {
            BTreeNode s = new BTreeNode(false);
            root = s;
            s.Children.Add(r);
            SplitChild(s, 0);
            InsertNonFull(s, key);
        }
        else
        {
            InsertNonFull(r, key);
        }
    }

    private void InsertNonFull(BTreeNode node, int key)
    {
        int i = node.Keys.Count - 1;
        if (node.Leaf)
        {
            node.Keys.Add(0);
            while (i >= 0 && key < node.Keys[i])
            {
                node.Keys[i + 1] = node.Keys[i];
                i--;
            }
            node.Keys[i + 1] = key;
        }
        else
        {
            while (i >= 0 && key < node.Keys[i])
                i--;
            i++;
            if (node.Children[i].Keys.Count == 2 * T - 1)
            {
                SplitChild(node, i);
                if (key > node.Keys[i])
                    i++;
            }
            InsertNonFull(node.Children[i], key);
        }
    }

    private void SplitChild(BTreeNode parent, int i)
    {
        BTreeNode y = parent.Children[i];
        BTreeNode z = new BTreeNode(y.Leaf);
        parent.Children.Insert(i + 1, z);
        parent.Keys.Insert(i, y.Keys[T - 1]);

        z.Keys.AddRange(y.Keys.GetRange(T, T - 1));
        y.Keys.RemoveRange(T - 1, T);

        if (!y.Leaf)
        {
            z.Children.AddRange(y.Children.GetRange(T, T));
            y.Children.RemoveRange(T, T);
        }
    }

    public void InorderTraversal(BTreeNode node)
    {
        for (int i = 0; i < node.Keys.Count; i++)
        {
            if (!node.Leaf)
                InorderTraversal(node.Children[i]);
            Console.Write(node.Keys[i] + " ");
        }
        if (!node.Leaf)
            InorderTraversal(node.Children[node.Keys.Count]);
    }

    public BTreeNode GetRoot() => root;
}

class Program
{
    static void Main()
    {
        BTree bTree = new BTree(3);
        int[] values = { 10, 20, 5, 6, 12, 30, 7, 17 };
        foreach (var value in values)
            bTree.Insert(value);

        bTree.InorderTraversal(bTree.GetRoot());  // Output: 5 6 7 10 12 17 20 30
    }
}