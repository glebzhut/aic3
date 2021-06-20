#include "classes.h"
using namespace std;

//Node for Splay Tree
template<typename T>
class SplayTreeNode
{
public:
    //Constructor
    SplayTreeNode(T dataArg) :left(nullptr), right(nullptr), parent(nullptr), data(dataArg) {}

    SplayTreeNode* left;
    SplayTreeNode* right;
    SplayTreeNode* parent;
    T data;
};

//Splay Tree Class
template<typename T>
class SplayTree
{
private:
    SplayTreeNode<T>* root_;
    //Function splay
    void Splay(SplayTreeNode<T>* node)
    {
        while (node->parent)
        {
            if (!node->parent->parent)
            {
                if (node->parent->right == node)
                    LeftRotate(node->parent);
                else RightRotate(node->parent);
            }
            else if (node->parent->left == node && node->parent->parent->left == node->parent)
            {
                RightRotate(node->parent->parent);
                RightRotate(node->parent);
            }
            else if (node->parent->right == node && node->parent->parent->right == node->parent)
            {
                LeftRotate(node->parent->parent);
                LeftRotate(node->parent);
            }
            else if (node->parent->right == node && node->parent->parent->left == node->parent)
            {
                LeftRotate(node->parent);
                RightRotate(node->parent);
            }
            else
            {
                RightRotate(node->parent);
                LeftRotate(node->parent);
            }
        }
    };

    //Right rotate function
    void RightRotate(SplayTreeNode<T>* node)
    {
        SplayTreeNode<T>* y = node->left;

        if (y)
        {
            node->left = y->right;
            if (y->right)
                y->right->parent = node;
            y->parent = node->parent;
        }

        if (!node->parent)
            root_ = y;
        else if (node == node->parent->left)
            node->parent->left = y;
        else node->parent->right = y;
        y->right = node;
        node->parent = y;
    };

    //Left rotate function
    void LeftRotate(SplayTreeNode<T>* node)
    {
        SplayTreeNode<T>* y = node->right;

        if (y)
        {
            node->right = y->left;
            if (y->left)
                y->left->parent = node;
            y->parent = node->parent;
        }
        if (!node->parent)
            root_ = y;
        else if (node == node->parent->left)
            node->parent->left = y;
        else node->parent->right = y;
        y->left = node;
        node->parent = y;
    };

    //Function for finding the lowest element in left sub tree
    SplayTreeNode<T>* LeftSubTreeMin(SplayTreeNode<T>* localRoot) const
    {
        auto ptr = localRoot;
        while (ptr->left)
            ptr = ptr->left;
        return ptr;
    };

    //Function for finding the highest element in right sub tree
    SplayTreeNode<T>* RightSubTreeMax(SplayTreeNode<T>* localRoot)  const
    {
        auto ptr = localRoot;
        while (ptr->right)
            ptr = ptr->right;
        return ptr;
    };

    //Finding the highest element in both sub trees
    SplayTreeNode<T>* Successor(SplayTreeNode<T>* node) const
    {
        if (node->right)
            return RightSubTreeMax(node);
        auto ptr = node->parent;
        while (ptr && node == ptr->right)
        {
            node = ptr;
            ptr = ptr->parent;
        }
        return ptr;
    };

    //Finding the lowest element in both sub trees
    SplayTreeNode<T>* Predecessor(SplayTreeNode<T>* node) const
    {
        if (node->left)
            return LeftSubTreeMin(node);
        auto ptr = node->parent;
        while (ptr && node == ptr->left)
        {
            node = ptr;
            ptr = ptr->parent;
        }
        return ptr;
    };

    //Finding key in tree
    SplayTreeNode<T>* Search(T& key)
    {
        auto ptr = root_;
        while (ptr)
        {
            if (key == ptr->data)
            {
                Splay(ptr);
                return ptr;
            }

            if (key < ptr->data)
                ptr = ptr->left;
            else if (key > ptr->data)
                ptr = ptr->right;
        }
        return nullptr;
    };

    //Swap function
    void Swap(SplayTreeNode<T>* where, SplayTreeNode<T>* what)
    {
        if (!where->parent)
            root_ = what;
        else if (where == where->parent->left)
            where->parent->left = what;
        else where->parent->right = what;

        if (what)
            what->parent = where->parent;
    };

    //Function for interactive finding elements
    SplayTreeNode<T>* ChooseNode(SplayTreeNode<T>* current_node) const
    {
        int position = 0;
        bool end = false;

        while (!end)
        {
            system("cls");
            cout << "Parent Node: ";
            if (current_node->parent)
            {
                cout << current_node->parent->data;
            }
            cout << endl;
            if (position == 0)
                cout << "-> Current Node: " << current_node->data << endl;
            else cout << "   Current Node: " << current_node->data << endl;
            if (position == 1)
            {
                if (current_node->left)
                    cout << "-> Left Node " << current_node->left->data << endl;
                else
                    cout << "-> NULL" << endl;
            }
            else
            {
                if (current_node->left)
                    cout << "   Left Node " << current_node->left->data << endl;
                else
                    cout << "   NULL" << endl;
            }
            if (position == 2)
            {
                if (current_node->right)
                    cout << "-> Right Node " << current_node->right->data << endl;
                else
                    cout << "-> NULL" << endl;
            }
            else
            {
                if (current_node->right)
                    cout << "   Right Node " << current_node->right->data << endl;
                else
                    cout << "   NULL" << endl;
            }
            if (position == 3)
                cout << "-> Back;" << endl;
            else cout << "   Back;" << endl;

            char key;
            key = _getch();
            if ((int)key != 13)
            {
                if ((int)key == -32)
                {
                    key = _getch();
                    if ((int)key == 72)
                    {
                        if (position > 0)
                            position--;
                        else position = 3;
                    }

                    if ((int)key == 80)
                    {
                        if (position < 3)
                            position++;
                        else position = 0;
                    }
                }
            }
            else
            {
                switch (position)
                {
                case 0:
                    return current_node;
                case 1:
                    if (current_node->left)
                        return ChooseNode(current_node->left);
                    break;
                case 2:
                    if (current_node->right)
                        return ChooseNode(current_node->right);
                    break;
                default:
                    if (current_node->parent)
                        return ChooseNode(current_node->parent);
                    break;
                }
            }
        }
    }

    //Function for outputting nodes of tree
    void PrintNode(SplayTreeNode<T>* curr)
    {
        if (curr)
        {
            cout << curr->data << " Left: {";
            PrintNode(curr->left);
            cout << ", ";
            PrintNode(curr->right);
            cout << "}";
        }
        else cout << "NULL";
    }
public:
    //Constructor
    SplayTree() : root_(nullptr) {}

    //Adding new element to Splay Tree
    void Insert(T dataArg)
    {
        SplayTreeNode<T>* prev = nullptr;
        SplayTreeNode<T>* ptr = root_;

        while (ptr)
        {
            prev = ptr;
            if (dataArg > ptr->data)
                ptr = ptr->right;
            else ptr = ptr->left;
        }

        SplayTreeNode<T>* newNode = new SplayTreeNode<T>(dataArg);
        newNode->left = newNode->right = nullptr;
        newNode->parent = prev;

        if (!prev)
            root_ = newNode;
        else if (dataArg > prev->data)
            prev->right = newNode;
        else prev->left = newNode;

        Splay(newNode);
    };

    //Remove element key from Splay Tree
    void Remove(T& key)
    {
        auto forDelete = Search(key);

        if (forDelete)
        {
            if (!forDelete->right)
                Swap(forDelete, forDelete->left);
            else if (!forDelete->left)
                Swap(forDelete, forDelete->right);
            else
            {
                auto ptr = LeftSubTreeMin(forDelete->right);

                if (ptr->parent != forDelete)
                {
                    Swap(ptr, ptr->right);
                    ptr->right = forDelete->right;
                    ptr->parent = forDelete->left;
                }

                Swap(forDelete, ptr);
                ptr->left = forDelete->left;
                ptr->left->parent = ptr;
                Splay(ptr);
            }
            delete forDelete;
        }
    };

    //Finding the lowest element of Splay Tree 
    T Min() const
    {
        return LeftSubTreeMin(root_)->data;
    };

    //Finding the highest element of Splay Tree  
    T Max() const
    {
        return RightSubTreeMax(root_)->data;
    };

    //If Splay Tree contains key return true
    bool At(T& key)
    {
        return Search(key) != nullptr;
    };

    //Function for merging to two Splay Trees
    void Merge(SplayTree<T>& tree)
    {
        if (this->Min() > tree.Max())
        {
            tree.Splay(tree.RightSubTreeMax(tree.root_));
            tree.root_->right = root_;
            root_ = tree.root_;
        }
        else if (this->Max() < tree.Min())
        {
            this->Splay(this->RightSubTreeMax(this->root_));
            root_->right = tree.root_;
        }
    };

    //Function for dividision tree into parts
    SplayTree<T> split(T& key)
    {
        Splay(Search(key));
        SplayTree<T> tree;
        tree.root_ = root_->right;
        root_->right = nullptr;

        return tree;
    };

    //Function for outputtin Splay Tree in console
    void print() const
    {
        if (root_)
            SplayTreeNode<T>* p = ChooseNode(root_);
        else cout << "Nothing" << endl;
    }

    void Print()
    {
        PrintNode(root_);
    }
};

//Main program function
int main()
{
    SplayTree<Group> A;
    int  n;
    cout << "Enter number groups" << endl;
    cin >> n;
    cin.ignore();
    cout << endl;
    string name;
    for (int i = 0; i < n; i++)
    {
        cout << i + 1 << "-th group name:" << endl;
        getline(cin, name);
        cout << i + 1 << "-th group student:" << endl;
        string models;
        getline(cin, models);
        A.Insert(Group(name, Parse(models)));
    }
    A.print();
    A.Print();
    return 0;
}
