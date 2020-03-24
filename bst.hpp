// Yusuf Pisan pisan@uw.edu
// 15 Jan 2018

// BST class
// Creates a BST to store values
// Uses Node which holds the Data
// Uses templates to store any type of Data
// binarysearchtreee.cpp file is included at the bottom of the .h file
// binarysearchtreee.cpp is part of the template, cannot be compiled separately

#ifndef BST_HPP
#define BST_HPP

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

using namespace std;

template<class T>
class BST {
    // display BST tree in a human-readable format
    friend ostream &operator<<(ostream &Out, const BST &Bst) {
        Bst.printSideways(Out, Bst.Root);
        Out << endl;
        Bst.printVertical(Out, Bst.Root);
        return Out;
    }

private:
    // Node for BST
    struct Node {
        T Data;
        struct Node *Left = nullptr;
        struct Node *Right = nullptr;

        explicit Node(T Val) {
            Data = Val;
        }
    };

    // refer to data type "struct Node" as Node
    using Node = struct Node;

    // root of the tree
    Node *Root{nullptr};

    //number of nodes in tree
    int Count = 0;

    // height of a Node, nullptr is 0, Root is 1, static, no access to 'this'
    static int getHeight(const Node *N) {
        if (N == nullptr)
            return 0;
        int LeftHeight = getHeight(N->Left);
        int RightHeight = getHeight(N->Right);
        if (LeftHeight > RightHeight)
            return 1 + LeftHeight;
        return 1 + RightHeight;
    }

    /**
     * print tree sideways with root on left
                  6
              2
                  5
          0
                  4
              1
                  3
     */
    static ostream &
    printSideways(ostream &Out, const Node *Curr, int Level = 0) {
        const static char SP = ' ';
        const static int ReadabilitySpaces = 4;
        if (!Curr)
            return Out;
        printSideways(Out, Curr->Right, ++Level);
        Out << setfill(SP) << setw(Level * ReadabilitySpaces) << SP;
        Out << Curr->Data << endl;
        printSideways(Out, Curr->Left, Level);
        return Out;
    }

    //helper method for printTreeLevel
    static ostream &centeredPrint(ostream &Out, int Space,
                                  const string &Str, char FillChar = ' ') {
        auto StrL = static_cast<int>(Str.length());
        int Extra = (Space - StrL) / 2;
        if (Extra > 0) {
            Out << setfill(FillChar) << setw(Extra + StrL) << Str;
            Out << setfill(FillChar) << setw(Space - Extra - StrL) << FillChar;
        } else {
            Out << setfill(FillChar) << setw(Space) << Str;
        }
        return Out;
    }

    /**
     * print tree with the root at top
     *
        _____0______
     __1___      __2___
    3     4     5     6
     *
    **/
    static ostream &printTreeLevel(ostream &Out, queue<const Node *> &Q,
                                   int Width, int Depth, int MaxDepth) {
        const static char SP = ' ';
        const static char UND = '_';
        int Nodes = 0;
        int MaxN = pow(2, Depth - 1);
        int SpaceForEachItem = Width * pow(2, MaxDepth - 1) / MaxN; // NOLINT
        string
                Bigspace = string(static_cast<uint64_t>(SpaceForEachItem / 4),
                                  SP);
        while (Nodes++ < MaxN) {
            const Node *Tp = Q.front();
            Node *TpL = nullptr;
            Node *TpR = nullptr;
            Q.pop();
            string Label = "N";
            if (Tp) {
                stringstream Ss;
                Ss << Tp->Data;
                Label = Ss.str();
                TpL = Tp->Left;
                TpR = Tp->Right;
            }
            char Filler = Depth == MaxDepth ? SP : UND;
            if (Depth == MaxDepth) {
                centeredPrint(Out, SpaceForEachItem, Label, Filler);
            } else {
                Out << Bigspace;
                centeredPrint(Out, SpaceForEachItem / 2, Label, Filler);
                Out << Bigspace;
                Q.push(TpL);
                Q.push(TpR);
            }
        }
        Out << endl;
        return Out;
    }

    // helper function for displaying tree sideways, works recursively
    static ostream &printVertical(ostream &Out, Node *Curr) {
        const static int WIDTH = 6;  // must be even
        if (!Curr)
            return Out << "[__]";
        // figure out the maximum depth which determines how wide the tree is
        int MaxDepth = getHeight(Curr);
        queue<const Node *> Q;
        Q.push(Curr);
        for (int Depth = 1; Depth <= MaxDepth; ++Depth) {
            printTreeLevel(Out, Q, WIDTH, Depth, MaxDepth);
        }
        return Out;
    }

    //helper method for equals
    bool equalsHelper(Node *NodeA, Node *NodeB) const {
        if (NodeA == nullptr && NodeB == nullptr)
            return true;
        if (NodeA != nullptr && NodeB != nullptr) {
            bool SameData = NodeA->Data == NodeB->Data;
            return SameData && equalsHelper(NodeA->Left, NodeB->Left) &&
                   equalsHelper(NodeA->Right, NodeB->Right);
        }
        return false;
    }

    //helper method for clear
    void clearHelper(Node *N) {
        if (N != nullptr) {
            clearHelper(N->Left);
            clearHelper(N->Right);
            delete N;
        }
    }

    //helper method for rebalance, adds elements of BST to array inorder
    void rebalanceAdd(Node *N, int &Index, T *Arr) {
        if (N != nullptr) {
            rebalanceAdd(N->Left, Index, Arr);
            T CurrItem = N->Data;
            Arr[Index++] = CurrItem;
            rebalanceAdd(N->Right, Index, Arr);
        }
    }

    //helper method for rebalance, puts back elements of the array into BST
    Node *rebalanceHelper(const T *Arr, int Start, int End) {
        if (Start > End)
            return nullptr;
        int Mid = (Start + End) / 2;
        Node *NewRoot = new Node(Arr[Mid]);
        NewRoot->Left = rebalanceHelper(Arr, Start, Mid - 1);
        NewRoot->Right = rebalanceHelper(Arr, Mid + 1, End);
        return NewRoot;
    }

    //helper method for postorder travesal
    void postOrderHelper(void Visit(const T &Item), Node *NodePtr) const {
        if (NodePtr != nullptr) {
            postOrderHelper(Visit, NodePtr->Left);
            postOrderHelper(Visit, NodePtr->Right);
            T CurrItem = NodePtr->Data;
            Visit(CurrItem);
        }
    }

    //helper method for preorder travesal
    void preOrderHelper(void Visit(const T &Item), Node *NodePtr) const {
        if (NodePtr != nullptr) {
            T CurrItem = NodePtr->Data;
            Visit(CurrItem);
            preOrderHelper(Visit, NodePtr->Left);
            preOrderHelper(Visit, NodePtr->Right);
        }
    }

    //helper method for inorder travesal
    void inOrderHelper(void Visit(const T &Item), Node *NodePtr) const {
        if (NodePtr != nullptr) {
            inOrderHelper(Visit, NodePtr->Left);
            T CurrItem = NodePtr->Data;
            Visit(CurrItem);
            inOrderHelper(Visit, NodePtr->Right);
        }
    }

    Node *removeHelper(Node *Curr, const T &Item, bool &Success) {
        if (Curr == nullptr) {
            Success = false;
            return nullptr;
        }
        if (Item < Curr->Data)
            Curr->Left = removeHelper(Curr->Left, Item, Success);
        else if (Item > Curr->Data)
            Curr->Right = removeHelper(Curr->Right, Item, Success);
        else {
            Success = true;
            if (Curr->Left == nullptr) {
                Node *Tmp = Curr->Right;
                delete Curr;
                return Tmp;
            }
            if (Curr->Right == nullptr) {
                Node *Tmp = Curr->Left;
                delete Curr;
                return Tmp;
            }
            Node *Tmp = getLeftMostNode(Curr->Right);
            Curr->Data = Tmp->Data;
            Curr->Right = removeHelper(Curr->Right, Tmp->Data, Success);
        }
        return Curr;
    }

    //gets next inorder successor
    Node *getLeftMostNode(Node *N) {
        Node *Curr = N;
        while (Curr != nullptr && Curr->Left != nullptr)
            Curr = Curr->Left;
        return Curr;
    }

public:
    // constructor, empty tree
    BST() = default;

    // constructor, tree with root
    explicit BST(const T &RootItem) {
        Root = new Node(RootItem);
        Count++;
    }

    // given an array of length n
    // create a tree to have all items in that array
    // with the minimum height (i.e. rebalance)
    // Assignment specification
    // NOLINTNEXTLINE
    BST(const T Arr[], int N) {
        Root = rebalanceHelper(Arr, 0, N - 1);
        Count = N;
    }

    // copy constructor
    BST(const BST<T> &Bst) {
        Root = copyConstructorHelper(Bst.Root);
        Count = Bst.Count;
    }

    //helper method for copy constructor
    Node *copyConstructorHelper(Node *NodeFrom) {
        if (NodeFrom == nullptr)
            return nullptr;
        Node *CopyNode = new Node(NodeFrom->Data);
        CopyNode->Left = copyConstructorHelper(NodeFrom->Left);
        CopyNode->Right = copyConstructorHelper(NodeFrom->Right);
        return CopyNode;
    }

    // destructor
    virtual ~BST() {
        clearHelper(Root);
        Count = 0;
    }

    // true if no nodes in BST
    bool isEmpty() const {
        return Root == nullptr;
    }

    // 0 if empty, 1 if only root, otherwise
    // height of root is max height of subtrees + 1
    int getHeight() const {
        return getHeight(Root);
    }

    // Number of nodes in BST
    int numberOfNodes() const {
        return Count;
    }

    // add a new item, return true if successful
    bool add(const T &Item) {
        Node *Parent = nullptr;
        Node *Curr = Root;
        while (Curr != nullptr) {
            Parent = Curr;
            if (Item == Curr->Data)
                return false;
            if (Item > Curr->Data) {
                Curr = Curr->Right;
            } else {
                Curr = Curr->Left;
            }
        }
        if (Parent == nullptr) {
            Root = new Node(Item);
            Count++;
            return true;
        }
        Node *NewNode = new Node(Item);
        if (Item < Parent->Data) {
            Parent->Left = NewNode;
        } else {
            Parent->Right = NewNode;
        }
        Count++;
        return true;
    }

    // remove item, return true if successful
    bool remove(const T &Item) {
        bool Success = false;
        Root = removeHelper(Root, Item, Success);
        if (Success)
            Count--;
        return Success;
    }

    // true if item is in BST
    bool contains(const T &Item) const {
        Node *Curr = Root;
        while (Curr != nullptr) {
            if (Item == Curr->Data)
                return true;
            if (Item < Curr->Data) {
                Curr = Curr->Left;
            } else {
                Curr = Curr->Right;
            }
        }
        return false;
    }

    // inorder traversal: left-root-right
    // takes a function that takes a single parameter of type T
    void inOrderTraverse(void Visit(const T &Item)) const {
        inOrderHelper(Visit, Root);
    }

    // preorder traversal: root-left-right
    void preOrderTraverse(void Visit(const T &Item)) const {
        preOrderHelper(Visit, Root);
    }

    // postorder traversal: left-right-root
    void postOrderTraverse(void Visit(const T &Item)) const {
        postOrderHelper(Visit, Root);
    }

    // create dynamic array, copy all the items to the array
    // and then read the array to re-create this tree from scratch
    // so that resulting tree is balanced
    void rebalance() {
        int NewCount = Count;
        T *Arr = new T[NewCount];
        int Start = 0;
        rebalanceAdd(Root, Start, Arr);
        clear();
        Root = rebalanceHelper(Arr, 0, NewCount - 1);
        Count = NewCount;
        delete[] Arr;
    }

    // delete all nodes in tree
    void clear() {
        clearHelper(Root);
        Root = nullptr;
        Count = 0;
    }

    // trees are equal if they have the same structure
    // AND the same item values at all the nodes
    bool operator==(const BST<T> &Other) const {
        return equalsHelper(Root, Other.Root);
    }

    // not == to each other
    bool operator!=(const BST<T> &Other) const {
        return !(*this == Other);
    }
};

#endif  // BST_HPP
