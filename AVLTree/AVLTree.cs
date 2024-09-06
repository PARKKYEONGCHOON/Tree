using System;

class Node
{
    public int Value;
    public Node Left, Right;
    public int Height;

    public Node(int value)
    {
        Value = value;
        Height = 1;
    }
}

class AVLTree
{
    public Node Insert(Node node, int value)
    {
        if (node == null)
            return new Node(value);

        if (value < node.Value)
            node.Left = Insert(node.Left, value);
        else if (value > node.Value)
            node.Right = Insert(node.Right, value);

        node.Height = 1 + Math.Max(Height(node.Left), Height(node.Right));
        int balance = GetBalance(node);

        if (balance > 1 && value < node.Left.Value)
            return RightRotate(node);
        if (balance < -1 && value > node.Right.Value)
            return LeftRotate(node);
        if (balance > 1 && value > node.Left.Value)
        {
            node.Left = LeftRotate(node.Left);
            return RightRotate(node);
        }
        if (balance < -1 && value < node.Right.Value)
        {
            node.Right = RightRotate(node.Right);
            return LeftRotate(node);
        }

        return node;
    }

    public int Height(Node node) => node?.Height ?? 0;

    public int GetBalance(Node node) => node == null ? 0 : Height(node.Left) - Height(node.Right);

    public Node RightRotate(Node y)
    {
        Node x = y.Left;
        Node T2 = x.Right;
        x.Right = y;
        y.Left = T2;
        y.Height = Math.Max(Height(y.Left), Height(y.Right)) + 1;
        x.Height = Math.Max(Height(x.Left), Height(x.Right)) + 1;
        return x;
    }

    public Node LeftRotate(Node x)
    {
        Node y = x.Right;
        Node T2 = y.Left;
        y.Left = x;
        x.Right = T2;
        x.Height = Math.Max(Height(x.Left), Height(x.Right)) + 1;
        y.Height = Math.Max(Height(y.Left), Height(y.Right)) + 1;
        return y;
    }

    public void Inorder(Node root)
    {
        if (root != null)
        {
            Inorder(root.Left);
            Console.Write(root.Value + " ");
            Inorder(root.Right);
        }
    }
}

class Program
{
    static void Main()
    {
        AVLTree tree = new AVLTree();
        Node root = null;
        int[] values = { 10, 20, 30, 40, 50, 25 };

        foreach (var value in values)
            root = tree.Insert(root, value);

        tree.Inorder(root); // Output: 10 20 25 30 40 50
    }
}