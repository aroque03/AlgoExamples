using System;
using System.Diagnostics;

namespace BinaryTreeBalancing
{
    /// <summary>
    /// AVL Tree node containing a key, left/right children, and height.
    /// </summary>
    class Node
    {
        public int Key;
        public Node Left;
        public Node Right;
        public int Height;

        public Node(int key)
        {
            Key = key;
            Left = null;
            Right = null;
            Height = 1;
        }
    }

    /// <summary>
    /// AVL Tree: a self-balancing binary search tree where the heights of
    /// the two child subtrees of any node differ by at most one. Insertions
    /// and deletions trigger rotations to restore balance.
    /// </summary>
    class AVLTree
    {
        public Node Root;
        public int Steps;

        public AVLTree()
        {
            Root = null;
            Steps = 0;
        }

        int Height(Node node)
        {
            return node == null ? 0 : node.Height;
        }

        int GetBalanceFactor(Node node)
        {
            return node == null ? 0 : Height(node.Left) - Height(node.Right);
        }

        /// <summary>
        /// Right rotation around node y.
        ///
        ///       y              x
        ///      / \            / \
        ///     x   T3  -->   T1   y
        ///    / \                / \
        ///   T1  T2            T2  T3
        /// </summary>
        Node RightRotate(Node y)
        {
            Steps++;
            Node x = y.Left;
            Node T2 = x.Right;

            x.Right = y;
            y.Left = T2;

            y.Height = Math.Max(Height(y.Left), Height(y.Right)) + 1;
            x.Height = Math.Max(Height(x.Left), Height(x.Right)) + 1;

            return x;
        }

        /// <summary>
        /// Left rotation around node x.
        ///
        ///     x                y
        ///    / \              / \
        ///   T1   y   -->    x   T3
        ///       / \        / \
        ///      T2  T3     T1  T2
        /// </summary>
        Node LeftRotate(Node x)
        {
            Steps++;
            Node y = x.Right;
            Node T2 = y.Left;

            y.Left = x;
            x.Right = T2;

            x.Height = Math.Max(Height(x.Left), Height(x.Right)) + 1;
            y.Height = Math.Max(Height(y.Left), Height(y.Right)) + 1;

            return y;
        }

        /// <summary>
        /// Inserts a key into the AVL tree and rebalances as needed.
        /// Four cases are handled:
        ///   Left-Left, Left-Right, Right-Right, Right-Left
        /// </summary>
        public void Insert(int key)
        {
            Root = InsertRec(Root, key);
        }

        Node InsertRec(Node node, int key)
        {
            Steps++;

            if (node == null)
                return new Node(key);

            if (key < node.Key)
                node.Left = InsertRec(node.Left, key);
            else if (key > node.Key)
                node.Right = InsertRec(node.Right, key);
            else
                return node; // Duplicate keys not allowed

            node.Height = Math.Max(Height(node.Left), Height(node.Right)) + 1;

            int balance = GetBalanceFactor(node);

            // Left-Left case
            if (balance > 1 && key < node.Left.Key)
                return RightRotate(node);

            // Right-Right case
            if (balance < -1 && key > node.Right.Key)
                return LeftRotate(node);

            // Left-Right case
            if (balance > 1 && key > node.Left.Key)
            {
                node.Left = LeftRotate(node.Left);
                return RightRotate(node);
            }

            // Right-Left case
            if (balance < -1 && key < node.Right.Key)
            {
                node.Right = RightRotate(node.Right);
                return LeftRotate(node);
            }

            return node;
        }

        /// <summary>
        /// Deletes a key from the AVL tree and rebalances as needed.
        /// </summary>
        public void Delete(int key)
        {
            Root = DeleteRec(Root, key);
        }

        Node DeleteRec(Node node, int key)
        {
            Steps++;

            if (node == null)
                return node;

            if (key < node.Key)
                node.Left = DeleteRec(node.Left, key);
            else if (key > node.Key)
                node.Right = DeleteRec(node.Right, key);
            else
            {
                // Node with one child or no child
                if (node.Left == null || node.Right == null)
                {
                    Node temp = node.Left ?? node.Right;
                    if (temp == null)
                    {
                        node = null;
                    }
                    else
                    {
                        node = temp;
                    }
                }
                else
                {
                    // Node with two children: get in-order successor
                    Node temp = MinValueNode(node.Right);
                    node.Key = temp.Key;
                    node.Right = DeleteRec(node.Right, temp.Key);
                }
            }

            if (node == null)
                return node;

            node.Height = Math.Max(Height(node.Left), Height(node.Right)) + 1;

            int balance = GetBalanceFactor(node);

            // Left-Left case
            if (balance > 1 && GetBalanceFactor(node.Left) >= 0)
                return RightRotate(node);

            // Left-Right case
            if (balance > 1 && GetBalanceFactor(node.Left) < 0)
            {
                node.Left = LeftRotate(node.Left);
                return RightRotate(node);
            }

            // Right-Right case
            if (balance < -1 && GetBalanceFactor(node.Right) <= 0)
                return LeftRotate(node);

            // Right-Left case
            if (balance < -1 && GetBalanceFactor(node.Right) > 0)
            {
                node.Right = RightRotate(node.Right);
                return LeftRotate(node);
            }

            return node;
        }

        Node MinValueNode(Node node)
        {
            Node current = node;
            while (current.Left != null)
            {
                Steps++;
                current = current.Left;
            }
            return current;
        }

        /// <summary>
        /// In-order traversal: visits nodes in ascending key order.
        /// </summary>
        public void InOrderTraversal(Node node, Action<int> visit)
        {
            if (node != null)
            {
                InOrderTraversal(node.Left, visit);
                visit(node.Key);
                InOrderTraversal(node.Right, visit);
            }
        }

        /// <summary>
        /// Prints the tree structure with indentation to visualize balance.
        /// </summary>
        public void PrintTree(Node node, string indent = "", bool isRight = false)
        {
            if (node == null)
                return;

            Console.Write(indent);
            if (indent.Length > 0)
            {
                Console.Write(isRight ? "├── " : "└── ");
                indent += isRight ? "│   " : "    ";
            }

            Console.WriteLine($"{node.Key} (h={node.Height}, bf={GetBalanceFactor(node)})");

            PrintTree(node.Right, indent, true);
            PrintTree(node.Left, indent, false);
        }

        /// <summary>
        /// Verifies that the AVL property holds for every node in the tree.
        /// Returns true if the tree is properly balanced.
        /// </summary>
        public bool VerifyBalance(Node node)
        {
            if (node == null)
                return true;

            int balance = GetBalanceFactor(node);
            if (Math.Abs(balance) > 1)
                return false;

            return VerifyBalance(node.Left) && VerifyBalance(node.Right);
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("=== AVL Tree (Self-Balancing Binary Search Tree) ===\n");

            AVLTree tree = new AVLTree();

            // Insert values 1-15 in order. Without balancing this would
            // degenerate into a linked list. The AVL rotations keep it balanced.
            int[] values = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

            // Other test arrays (uncomment to try):
            // int[] values = { 10, 20, 30, 40, 50, 25 };
            // int[] values = { 9, 5, 10, 0, 6, 11, -1, 1, 2 };
            // int[] values = { 50, 25, 75, 10, 30, 60, 80, 5, 15, 27, 55, 1 };

            Console.WriteLine("--- Insertion Phase ---\n");
            Console.Write("Inserting values: ");
            Console.WriteLine(string.Join(", ", values));
            Console.WriteLine();

            Stopwatch sw = Stopwatch.StartNew();

            foreach (int val in values)
            {
                tree.Insert(val);
            }

            sw.Stop();

            Console.WriteLine("Tree structure after insertions:");
            tree.PrintTree(tree.Root);
            Console.WriteLine();

            Console.Write("In-order traversal: ");
            tree.InOrderTraversal(tree.Root, key => Console.Write(key + " "));
            Console.WriteLine();

            bool balanced = tree.VerifyBalance(tree.Root);
            Console.WriteLine($"Tree is balanced: {balanced}");
            Console.WriteLine($"Steps (insertions): {tree.Steps}");
            Console.WriteLine($"Elapsed time: {sw.Elapsed.TotalMilliseconds:F4} ms " +
                              $"({sw.ElapsedTicks * 1000000 / Stopwatch.Frequency} μs)");

            // --- Deletion Phase ---
            Console.WriteLine("\n--- Deletion Phase ---\n");

            int[] toDelete = { 3, 7, 12 };
            Console.Write("Deleting values: ");
            Console.WriteLine(string.Join(", ", toDelete));
            Console.WriteLine();

            tree.Steps = 0;
            Stopwatch sw2 = Stopwatch.StartNew();

            foreach (int val in toDelete)
            {
                tree.Delete(val);
            }

            sw2.Stop();

            Console.WriteLine("Tree structure after deletions:");
            tree.PrintTree(tree.Root);
            Console.WriteLine();

            Console.Write("In-order traversal: ");
            tree.InOrderTraversal(tree.Root, key => Console.Write(key + " "));
            Console.WriteLine();

            balanced = tree.VerifyBalance(tree.Root);
            Console.WriteLine($"Tree is balanced: {balanced}");
            Console.WriteLine($"Steps (deletions): {tree.Steps}");
            Console.WriteLine($"Elapsed time: {sw2.Elapsed.TotalMilliseconds:F4} ms " +
                              $"({sw2.ElapsedTicks * 1000000 / Stopwatch.Frequency} μs)");

            // --- Stress Test with larger dataset ---
            Console.WriteLine("\n--- Stress Test (1000 sequential inserts) ---\n");

            AVLTree bigTree = new AVLTree();
            Stopwatch sw3 = Stopwatch.StartNew();

            for (int i = 1; i <= 1000; i++)
            {
                bigTree.Insert(i);
            }

            sw3.Stop();

            balanced = bigTree.VerifyBalance(bigTree.Root);
            Console.WriteLine($"Inserted 1000 sequential values");
            Console.WriteLine($"Tree is balanced: {balanced}");
            Console.WriteLine($"Root key: {bigTree.Root.Key}");
            Console.WriteLine($"Tree height: {bigTree.Root.Height}");
            Console.WriteLine($"Steps: {bigTree.Steps}");
            Console.WriteLine($"Elapsed time: {sw3.Elapsed.TotalMilliseconds:F4} ms " +
                              $"({sw3.ElapsedTicks * 1000000 / Stopwatch.Frequency} μs)");
            Console.WriteLine($"Theoretical max AVL height for 1000 nodes: ~14 (actual: {bigTree.Root.Height})");
        }
    }
}
